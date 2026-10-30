// Phase 5 slice libs4: CRI ROFS, the pure parts: the file handle (create, reopen, seek, tell, status, transfer
// counts), the volume record helpers, the error reporter and last-error, the work-area flags, the ISO 9660 record
// copiers, the CVM header parsers (CVMH / CVMF / ZONE), the PFS lock and wait helpers, ROCI's interface getters
// (0x5658A8-0x56CA78, 0x56DD50-0x56DDF8).
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

// 0x005658A8 PFSCVFS_GetPfsTbl -- 12 bytes; leaf frame (no stack)
// The PFS-over-cvFs device table (0x7C6F50: exec server, seek, ..., the pfsCvfs* functions). [PFSCVFS_GetPfsTbl]
void PFSCVFS_GetPfsTbl(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x005658a8
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7C0000;
    v0 = addiu(v0, 28496);  // &g_pfscvfs_tbl
}

// 0x00565970 rfhn_setHandle -- 172 bytes; frame 0x40: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, ra sp+0x30
// Fill a ROFS handle: open, the directory entry index and the first sector, the 64-bit size split into its two words
//   (sub_569BE8), the size in sectors (bytes + 2047) >> 11, the volume record; every transfer count and state 0.
//   Returns 1, or what sub_569BE8 left when there is no handle. [rfhn_setHandle]
void rfhn_setHandle(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00565970
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = a1;
    sd(s2, sp, 0x20);
    s2 = a2;
    a0 = a3;
    a1 = sp;
    a2 = addiu(sp, 0x4);
    sd(s3, sp, 0x28);
    sd(ra, sp, 0x30);
    s3 = t0;
    jal(ctx, 0x5659A0u, gen::fn_sub_569BE8_00569be8);
    lw(a1, sp, 0x4);
    if (s0 != 0) {
        // 0x005659b0
        charge(ctx, 20);
        v0 = 1;
        lw(a0, sp, 0x0);
        v1 = addiu(a1, 2047);
        sh(v0, s0, rofs_hn::kActive);
        v1 = srl(v1, 11);
        sw(s1, s0, rofs_hn::kDirIdx);
        sw(s2, s0, rofs_hn::kStartLba);
        sw(a0, s0, rofs_hn::kSizeHi);
        sw(v1, s0, rofs_hn::kSizeSct);
        sw(s3, s0, rofs_hn::kVol);
        sh(zero, s0, rofs_hn::kErr);
        sw(zero, s0, rofs_hn::kPosSct);
        sw(a1, s0, rofs_hn::kSizeLo);
        sw(zero, s0, rofs_hn::kReqSct);
        sw(zero, s0, rofs_hn::kRdSct);
        sw(zero, s0, rofs_hn::kRdRemBytes);
        sw(zero, s0, rofs_hn::kSctLen);
        sw(zero, s0, rofs_hn::kBuf);
        sh(zero, s0, rofs_hn::kReqState);
        sh(zero, s0, rofs_hn::kStat);
    }
    // 0x00565a00 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00565A20 RFHN_CreateHnG -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Create a handle: a free handle (+52 == 0) and a volume record with an image handle get filled (rfhn_setHandle);
//   else 0. [RFHN_CreateHnG]
void RFHN_CreateHnG(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00565a20
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t1 = t0;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 != 0) {
        // 0x00565a38
        charge(ctx, 2);
        if (t1 == 0) {
            goto L_00565a40;
        }
        lh(v1, s0, rofs_hn::kActive);
        // 0x00565a48
        charge(ctx, 2);
        v0 = 0;
        if (v1 != 0) {
        L_00565a68:
            charge(ctx, 1);
            ld(s0, sp, 0x0);
        } else {
            // 0x00565a50
            charge(ctx, 3);
            lw(v1, t1, 0);
            if (v1 != 0) {
                // 0x00565a5c
                charge(ctx, 3);
                jal(ctx, 0x565A5Cu, gen::fn_rfhn_setHandle_00565970);
                v0 = s0;
                goto L_00565a68;
            }
            ld(s0, sp, 0x0);
        }
        // 0x00565a6c (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_00565a40:
    charge(ctx, 2);
    v0 = 0;
    goto L_00565a68;
}

// 0x00565A78 RFHN_ReopenHn -- 68 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Reopen a handle that is not busy (+54 != 1): filled again; else 0. [RFHN_ReopenHn]
void RFHN_ReopenHn(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00565a78
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 != 0) {
        // 0x00565a90
        charge(ctx, 4);
        lh(t1, s0, rofs_hn::kReqState);
        v1 = 1;
        if (t1 != v1) {
            // 0x00565aa0
            charge(ctx, 3);
            jal(ctx, 0x565AA0u, gen::fn_rfhn_setHandle_00565970);
            v0 = s0;
            goto L_00565aac;
        }
        ld(s0, sp, 0x0);
        // 0x00565ab0 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_00565aac:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x00565ab0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00565AC0 RFHN_CreateDirhn -- 84 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Create a directory handle: 72 bytes cleared, +4 = the directory size (>= 0); else 0. [RFHN_CreateDirhn]
void RFHN_CreateDirhn(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00565ac0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    if (s0 != 0) {
        // 0x00565ae0
        charge(ctx, 2);
        a1 = 0;
        if (i64(s1) >= 0) {
            // 0x00565ae8
            charge(ctx, 6);
            a2 = 72;
            jal(ctx, 0x565AE8u, gen::fn_memset_00521408);
            sw(zero, s0, rofs_dirhn::kZero0);
            sw(s1, s0, rofs_dirhn::kDirSize);
            v0 = s0;
            sw(zero, s0, rofs_dirhn::kZero8);
        }
    }
    // 0x00565b00 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00565B18 RFHN_IsUseImgHn -- 120 bytes; leaf frame (no stack)
// Is an image handle in use: over the volume's open handles (60-byte records from +4236, the count at +4) the first
//   transferring one (+54 == 1) whose volume's image handle is this one; it defaults to the handle's own volume's.
//   [RFHN_IsUseImgHn]
// As compiled, a transferring handle without a volume record counts but does not advance (the same handle is looked
//   at again until the count runs out).
void RFHN_IsUseImgHn(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00565b18
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
    if (a0 != 0) {
        // 0x00565b20
        charge(ctx, 2);
        if (a1 != 0) {
            lw(v0, a0, 8);
        } else {
            // 0x00565b28
            charge(ctx, 3);
            lw(v0, a0, 28);
            lw(a1, v0, 0);
            lw(v0, a0, 8);
        }
        // 0x00565b34
        charge(ctx, 4);
        a2 = 0;
        lw(v1, v0, 4);
        a0 = addiu(v0, 4236);
        if (i64(v1) > 0) {
            // 0x00565b44
            charge(ctx, 3);
            a3 = v1;
            t0 = 1;
            lh(v0, a0, 54);
            for (;;) {
                // 0x00565b50
                charge(ctx, 2);
                if (v0 != t0) {
                    a0 = addiu(a0, 60);
                } else {
                    // 0x00565b58
                    charge(ctx, 3);
                    lw(v1, a0, 28);
                    if (v1 == 0) {
                        a2 = addiu(a2, 1);
                    L_00565b78:
                        charge(ctx, 3);
                        v0 = slt(a2, a3);
                        if (v0 == 0) {
                            goto L_00565b84;
                        }
                        lh(v0, a0, 54);
                        backedge(ctx);
                        continue;
                    }
                    // 0x00565b64
                    charge(ctx, 3);
                    lw(v1, v1, 0);
                    v0 = 1;
                    if (v1 != a1) {
                        // 0x00565b70
                        charge(ctx, 1);
                        a0 = addiu(a0, 60);
                        goto L_00565b74;
                    }
                    break;
                }
            L_00565b74:
                charge(ctx, 1);
                a2 = addiu(a2, 1);
                goto L_00565b78;
            }
            // 0x00565b88 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
    L_00565b84:
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x00565b88 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00565C10 ROFS_Seek -- 356 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, ra sp+0x18
// Seek a handle in sectors: origin 0 (start), 1 (current, +20) or 2 (end, the size +24); outside 0..size, a closed
//   handle or a bad origin are reported (-101 / -205, named by its texts); returns the new position. [ROFS_Seek]
void ROFS_Seek(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00565c10
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a1;
    jal(ctx, 0x565C2Cu, gen::fn_sub_569810_00569810);
    if (s1 == 0) {
        // 0x00565c3c
        charge(ctx, 13);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 28648);  // "../../rofs_hn.c"
        ld(s1, sp, 0x8);
        a2 = addiu(a2, 28664);  // "ROFS_Seek"
        ld(s2, sp, 0x10);
        a1 = 302;
        ld(ra, sp, 0x18);
        a3 = 0;
        t0 = si(-101);
        sp = addiu(sp, 0x20);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    lh(v1, s1, rofs_hn::kActive);
    // 0x00565c70
    charge(ctx, 3);
    v0 = 1;
    a0 = 0x7C0000;
    if (v1 != v0) {
        // 0x00565c7c
        charge(ctx, 12);
        a2 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 28648);
        ld(s1, sp, 0x8);
        a2 = addiu(a2, 28664);  // "ROFS_Seek"
        ld(s2, sp, 0x10);
        a1 = 305;
        ld(ra, sp, 0x18);
        a3 = 0;
        t0 = si(-101);
        sp = addiu(sp, 0x20);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    // 0x00565cb0
    charge(ctx, 2);
    lw(a0, s1, rofs_hn::kSizeSct);
    if (s0 != v1) {
        // 0x00565cb8
        charge(ctx, 2);
        v1 = s2;
        if (s0 == 0) {
            goto L_00565d14;
        }
        // 0x00565cc0
        charge(ctx, 3);
        v0 = 2;
        a2 = 0x7C0000;
        if (s0 == v0) {
            // 0x00565d10
            charge(ctx, 1);
            v1 = addu(a0, s2);
            goto L_00565d14;
        }
        // 0x00565ccc
        charge(ctx, 12);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 28648);  // "../../rofs_hn.c"
        ld(s1, sp, 0x8);
        a2 = addiu(a2, 28664);
        ld(s2, sp, 0x10);
        a1 = 324;
        ld(ra, sp, 0x18);
        a3 = 0;
        t0 = si(-205);
        sp = addiu(sp, 0x20);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    // 0x00565d00
    charge(ctx, 3);
    lw(v0, s1, rofs_hn::kPosSct);
    v1 = addu(v0, s2);
L_00565d14:
    charge(ctx, 2);
    v0 = slt(a0, v1);
    if (i64(v1) >= 0) {
        // 0x00565d1c
        charge(ctx, 2);
        if (v0 != 0) {
            goto L_00565d24;
        }
        sw(v1, s1, rofs_hn::kPosSct);
        // 0x00565d58
        charge(ctx, 7);
        v0 = v1;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_00565d24:
    charge(ctx, 13);
    a0 = 0x7C0000;
    a2 = 0x7C0000;
    ld(s0, sp, 0x0);
    a0 = addiu(a0, 28648);  // "../../rofs_hn.c"
    ld(s1, sp, 0x8);
    a2 = addiu(a2, 28664);  // "ROFS_Seek"
    ld(s2, sp, 0x10);
    a1 = 329;
    ld(ra, sp, 0x18);
    a3 = 0;
    t0 = si(-205);
    sp = addiu(sp, 0x20);
    gen::fn_sub_569730_00569730(ctx);  // tail call
}

// 0x00565D78 ROFS_Tell -- 148 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// A handle's position in sectors (+20); a closed handle reports -101. [ROFS_Tell]
void ROFS_Tell(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00565d78
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x565D84u, gen::fn_sub_569810_00569810);
    a0 = 0x7C0000;
    a2 = 0x7C0000;
    a0 = addiu(a0, 28648);  // "../../rofs_hn.c"
    a2 = addiu(a2, 28680);  // "ROFS_Tell"
    a1 = 348;
    a3 = 0;
    t0 = si(-101);
    v1 = 1;
    if (s0 == 0) {
        // 0x00565db0
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    // 0x00565dc0
    charge(ctx, 3);
    lh(v0, s0, rofs_hn::kActive);
    a0 = 0x7C0000;
    if (v0 == v1) {
        // 0x00565df8
        charge(ctx, 5);
        lw(v0, s0, rofs_hn::kPosSct);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00565dcc
    charge(ctx, 10);
    a2 = 0x7C0000;
    ld(s0, sp, 0x0);
    a0 = addiu(a0, 28648);
    ld(ra, sp, 0x8);
    a2 = addiu(a2, 28680);  // "ROFS_Tell"
    a1 = 351;
    a3 = 0;
    t0 = si(-101);
    sp = addiu(sp, 0x10);
    gen::fn_sub_569730_00569730(ctx);  // tail call
}

// 0x00565FE8 RFHN_GetStatG -- 100 bytes; frame 0x10: ra sp+0x0
// A handle's status (+56: 0 idle, 1 complete, 2 transferring, 3 error); no handle / a closed one: reported, 3.
//   [RFHN_GetStatG]
void RFHN_GetStatG(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00565fe8
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00565ff4
        charge(ctx, 6);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        a0 = addiu(a0, 28648);  // "../../rofs_hn.c"
        a2 = addiu(a2, 28712);  // "RFHN_GetStatG"
        a1 = 463;
        goto L_00566030;
    }
    // 0x00566010
    charge(ctx, 3);
    lh(v0, a0, 52);
    if (v0 != 0) {
        lh(v0, a0, 56);
    } else {
        // 0x0056601c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        a0 = addiu(a0, 28648);  // "../../rofs_hn.c"
        a2 = addiu(a2, 28712);  // "RFHN_GetStatG"
        a1 = 467;
    L_00566030:
        charge(ctx, 4);
        a3 = 0;
        t0 = si(-101);
        jal(ctx, 0x566034u, gen::fn_sub_569730_00569730);
        v0 = 3;
    }
    // 0x00566040 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00566050 ROFS_GetNumTr -- 156 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Bytes transferred: sectors read (+36) << 11 + the remainder (+40); a closed handle reports -101. [ROFS_GetNumTr]
void ROFS_GetNumTr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00566050
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x56605Cu, gen::fn_sub_569810_00569810);
    a0 = 0x7C0000;
    a2 = 0x7C0000;
    a0 = addiu(a0, 28648);  // "../../rofs_hn.c"
    a2 = addiu(a2, 28728);  // "ROFS_GetNumTr"
    a1 = 485;
    a3 = 0;
    t0 = si(-101);
    if (s0 == 0) {
        // 0x00566084
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    // 0x00566098
    charge(ctx, 3);
    lh(v0, s0, rofs_hn::kActive);
    if (v0 != 0) {
        lw(v0, s0, rofs_hn::kRdSct);
        // 0x005660d0
        charge(ctx, 7);
        lw(v1, s0, rofs_hn::kRdRemBytes);
        v0 = sll(v0, 11);
        ld(ra, sp, 0x8);
        ld(s0, sp, 0x0);
        v0 = addu(v0, v1);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005660a4
    charge(ctx, 11);
    a0 = 0x7C0000;
    a2 = 0x7C0000;
    ld(s0, sp, 0x0);
    a0 = addiu(a0, 28648);  // "../../rofs_hn.c"
    ld(ra, sp, 0x8);
    a2 = addiu(a2, 28728);  // "ROFS_GetNumTr"
    a1 = 488;
    a3 = 0;
    t0 = si(-101);
    sp = addiu(sp, 0x10);
    gen::fn_sub_569730_00569730(ctx);  // tail call
}

// 0x005660F0 sub_5660F0 -- 140 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The same count for the 64-bit API (named by its text 'ROFS_GetNumTr64'). [ROFS_GetNumTr64]
void sub_5660F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005660f0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5660FCu, gen::fn_sub_569810_00569810);
    a0 = 0x7C0000;
    a2 = 0x7C0000;
    a0 = addiu(a0, 28648);  // "../../rofs_hn.c"
    a2 = addiu(a2, 28744);  // "ROFS_GetNumTr64"
    a1 = 503;
    a3 = 0;
    t0 = si(-101);
    if (s0 != 0) {
        // 0x00566124
        charge(ctx, 3);
        lh(v0, s0, rofs_hn::kActive);
        if (v0 == 0) {
            // 0x00566130
            charge(ctx, 7);
            a0 = 0x7C0000;
            a2 = 0x7C0000;
            a0 = addiu(a0, 28648);  // "../../rofs_hn.c"
            a2 = addiu(a2, 28744);  // "ROFS_GetNumTr64"
            a1 = 506;
            a3 = 0;
            t0 = si(-101);
            goto L_0056614c;
        }
        lw(v0, s0, rofs_hn::kRdSct);
        // 0x00566160
        charge(ctx, 3);
        lw(v1, s0, rofs_hn::kRdRemBytes);
        v0 = sll(v0, 11);
        v0 = addu(v0, v1);
        // 0x0056616c (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_0056614c:
    charge(ctx, 4);
    jal(ctx, 0x56614Cu, gen::fn_sub_569730_00569730);
    // daddu v0: a 64-bit move to itself (no effect)
    // 0x0056616c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005662C8 sub_5662C8 -- 36 bytes; frame 0x10: ra sp+0x0
// Wait twice (the PFS busy wait, 7,551 empty iterations each). [rfif_Wait2]
void sub_5662C8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005662c8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x5662D0u, gen::fn_sub_56DDF8_0056ddf8);
    jal(ctx, 0x5662D8u, gen::fn_sub_56DDF8_0056ddf8);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005669B8 sub_5669B8 -- 32 bytes; frame 0x10: ra sp+0x0
// The sector size: 2048 (the last error cleared first). [rofs_GetSctLen]
void sub_5669B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005669b8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x5669C0u, gen::fn_sub_569810_00569810);
    ld(ra, sp, 0x0);
    v0 = 2048;
    sp = addiu(sp, 0x10);
}

// 0x00567430 rfmai_delVolume -- 68 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Delete a volume record: 52 bytes cleared; it stops being the default volume (work +44). [rfmai_delVolume]
void rfmai_delVolume(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00567430
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 != 0) {
        // 0x00567444
        charge(ctx, 3);
        a1 = 0;
        a2 = 52;
        jal(ctx, 0x567448u, gen::fn_memset_00521408);
    }
    // 0x00567450
    charge(ctx, 5);
    v0 = 0x7B0000;
    lw(v0, v0, 9984);  // g_rofs_work
    lw(v1, v0, 44);
    if (s0 == v1) {
        sw(zero, v0, 44);
    }
    // 0x00567464
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005675C8 rfmai_setCvmfInfo -- 228 bytes; frame 0x30: s1 sp+0x18, s0 sp+0x10, ra sp+0x20
// Default CVM information for whole-disc access: the 1904-byte header info and the 44-byte zone info cleared, one
//   zone, the data at sector 0, 2048-byte sectors, the maximal size (0x7FFFFFFFFFFFFFFF) stored through sub_569960.
//   [rfmai_setCvmfInfo]
void rfmai_setCvmfInfo(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005675c8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = si(-1);
    v0 = dsrl(v0, 1);
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(ra, sp, 0x20);
    sd(v0, sp, 0x0);
    if (s1 != 0) {
        // 0x005675f0
        charge(ctx, 2);
        a1 = 0;
        if (s0 == 0) {
            goto L_005675f8;
        }
        // 0x00567600
        charge(ctx, 38);
        a2 = 1904;
        jal(ctx, 0x567600u, gen::fn_memset_00521408);
        a0 = s0;
        a1 = 0;
        a2 = 44;
        jal(ctx, 0x567610u, gen::fn_memset_00521408);
        a0 = 0;
        a2 = sp;
        a1 = 1;
        a3 = s1;
        jal(ctx, 0x567624u, gen::fn_sub_569960_00569960);
        v1 = 1;
        t2 = 2048;
        v0 = 2;
        t0 = 4;
        t1 = 16;
        sw(v1, s1, 100);
        a3 = addiu(s0, 36);
        sw(zero, s1, 112);
        a0 = 0;
        sw(v1, s1, 20);
        a1 = 1;
        sb(v1, s1, 96);
        a2 = sp;
        sb(zero, s1, 97);
        sw(zero, s1, 104);
        sw(zero, s1, 108);
        sw(v0, s0, 0);
        sb(t0, s0, 6);
        sb(t1, s0, 7);
        sw(t2, s0, 16);
        sb(zero, s0, 4);
        sb(zero, s0, 5);
        sb(zero, s0, 8);
        sw(t2, s0, 12);
        link(ctx, 0x56768Cu);  // $ra first: the delay slot below depends on it
        sw(zero, s0, 32);
        call(ctx, gen::fn_sub_569960_00569960);
        v0 = 0;
        // 0x00567698 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x10);
        ld(s1, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_005675f8:
    charge(ctx, 2);
    v0 = si(-100);
    // 0x00567698 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00568A78 sub_568A78 -- 68 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Start a read wait: the 16-byte wait state (0x99A0D0) cleared and the current work time (+20) noted.
//   [rfmai_StartWait]
void sub_568A78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00568a78
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(s0, sp, 0x0);
    s0 = 0x9A0000;
    s0 = addiu(s0, -24368);  // &0x99A0D0
    a2 = 16;
    sd(ra, sp, 0x8);
    a0 = s0;
    jal(ctx, 0x568A94u, gen::fn_memset_00521408);
    v1 = 0x7B0000;
    lw(v0, v1, 9984);  // g_rofs_work
    ld(ra, sp, 0x8);
    lw(a0, v0, 20);
    sw(a0, s0, 8);  // 0x99A0D8
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00569518 sub_569518 -- 32 bytes; leaf frame (no stack)
// Set the error callback {function, object} in the ROFS work (+64 / +68). [rfmai_SetErrFunc]
void sub_569518(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00569518
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    lw(v0, v0, 9984);  // g_rofs_work
    if (v0 != 0) {
        // 0x00569528
        charge(ctx, 2);
        sw(a1, v0, 68);
        sw(a0, v0, 64);
    }
    // 0x00569530 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00569700 sub_569700 -- 20 bytes; leaf frame (no stack)
// Count a handle's volume in use: the u16 at +20 of its volume record (+28) up; returns the new count. [rfmai_IncUse]
void sub_569700(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00569700
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, a0, rofs_hn::kVol);
    lhu(v0, v1, 20);
    v0 = addiu(v0, 1);
    sh(v0, v1, 20);
}

// 0x00569718 sub_569718 -- 20 bytes; leaf frame (no stack)
// Count it down again. [rfmai_DecUse]
void sub_569718(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00569718
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, a0, rofs_hn::kVol);
    lhu(v0, v1, 20);
    v0 = addiu(v0, -1);
    sh(v0, v1, 20);
}

// 0x00569730 sub_569730 -- 220 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// ROFS error: with an error callback set, the text "(code)function[detail]#file:line" (or without the detail) is
//   printed into 0x99A0E8 and passed to it; the code is kept as the last error (0x7B2704) and returned (no work area:
//   -203). [rfmai_CallErr]
void sub_569730(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00569730
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s2, sp, 0x10);
    s2 = 0x7B0000;
    lw(v0, s2, 9984);  // g_rofs_work
    sd(s0, sp, 0x0);
    s0 = t0;
    sd(s1, sp, 0x8);
    t0 = a3;
    sd(ra, sp, 0x18);
    if (v0 != 0) {
        // 0x00569768
        charge(ctx, 3);
        lw(v0, v0, 64);
        v1 = 0x7B0000;
        if (v0 != 0) {
            // 0x00569774
            charge(ctx, 2);
            t2 = sll(a1, 16);
            if (t0 == 0) {
                // 0x005697a8
                charge(ctx, 11);
                t1 = sll(a1, 16);
                a1 = 0x7C0000;
                s1 = 0x9A0000;
                a3 = a2;
                t0 = a0;
                a0 = addiu(s1, -24344);  // &0x99A0E8
                a1 = addiu(a1, 30000);  // "(%d)%s#%s:%d"
                t1 = sra(t1, 16);
                a2 = s0;
                jal(ctx, 0x5697C8u, gen::fn_sprintf_00523ac8);
                lw(v1, s2, 9984);
            } else {
                // 0x0056977c
                charge(ctx, 11);
                a1 = 0x7C0000;
                s1 = 0x9A0000;
                a3 = a2;
                t1 = a0;
                a0 = addiu(s1, -24344);  // &0x99A0E8
                a1 = addiu(a1, 29976);  // "(%d)%s[%s]#%s:%d"
                t2 = sra(t2, 16);
                a2 = s0;
                jal(ctx, 0x569798u, gen::fn_sprintf_00523ac8);
                lw(v1, s2, 9984);
            }
            // 0x005697d4
            charge(ctx, 6);
            a1 = addiu(s1, -24344);
            a2 = s0;
            lw(v0, v1, 64);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x5697E0u);  // $ra = the return address
            lw(a0, v1, 68);
            call_ptr(ctx, jt);
            v1 = 0x7B0000;
        }
        // 0x005697ec
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x00569758
        charge(ctx, 4);
        v1 = 0x7B0000;
        s0 = si(-203);
        v0 = si(-203);
    }
    // 0x005697f0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sw(s0, v1, 9988);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00569810 sub_569810 -- 12 bytes; leaf frame (no stack)
// Clear the last error (0x7B2704). [rfmai_ClrErr]
void sub_569810(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2};
    // 0x00569810
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sw(zero, v0, 9988);  // 0x7B2704
}

// 0x00569820 __errno_10 -- 12 bytes; leaf frame (no stack)
// The last error. [rfmai_GetLastErr]
void __errno_10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00569820
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    lw(v0, v1, 9988);  // 0x7B2704
}

// 0x00569830 sub_569830 -- 20 bytes; frame 0x10: ra sp+0x0
// The last error (public). [rofs_GetLastErr]
void sub_569830(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00569830
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn___errno_10_00569820(ctx);  // tail call
}

// 0x00569950 sub_569950 -- 16 bytes; leaf frame (no stack)
// The work area's time counter (+20). [rfmai_GetTime]
void sub_569950(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00569950
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    lw(v1, v0, 9984);  // g_rofs_work
    lw(v0, v1, 20);
}

// 0x00569960 sub_569960 -- 400 bytes; frame 0x30: s3 sp+0x18, s4 sp+0x20, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x28
// 64-bit / 32-bit arithmetic on a {lo, hi} pair: op 0 set, 1 add, 2 sub, 3 mul, 4 div, 5 mod; width 1 = 64 bits
//   through sub_569BD0 / sub_569BE8 and libgcc, 0 or 2 = 32 bits; other ops -1. [rfmai_Calc64]
void sub_569960(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00569960
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 1;
    sd(s3, sp, 0x18);
    s3 = a0;
    sd(s4, sp, 0x20);
    s4 = a3;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x28);
    if (a1 != v0) {
        // 0x00569a38
        charge(ctx, 2);
        lw(a3, s4, 0);
        if (a1 != 0) {
            // 0x00569a40
            charge(ctx, 3);
            v1 = 2;
            v0 = 0;
            if (a1 == v1) {
                goto L_00569a4c;
            }
            // 0x00569ad0 (the shared epilogue, written out on this path)
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
    L_00569a4c:
        charge(ctx, 3);
        v0 = sltiu(s3, 6);
        lw(a2, a2, 0);
        if (v0 == 0) {
            // 0x00569ac0
            charge(ctx, 2);
            v0 = si(-1);
        } else {
            // 0x00569a58
            charge(ctx, 6);
            v0 = sll(s3, 2);
            v1 = 0x7C0000;
            v1 = addu(v1, v0);
            lw(v1, v1, 30080);
            switch (v1.u()) {
            case 0x569A70u:  // table[0]
                // 0x00569a70
                charge(ctx, 2);
                a3 = a2;
                break;
            case 0x569A78u:  // table[1]
                // 0x00569a78
                charge(ctx, 2);
                a3 = addu(a3, a2);
                break;
            case 0x569A80u:  // table[2]
                // 0x00569a80
                charge(ctx, 2);
                a3 = subu(a3, a2);
                break;
            case 0x569A88u:  // table[3]
                // 0x00569a88
                charge(ctx, 2);
                mult(a3, a3, a2);
                break;
            case 0x569A90u:  // table[4]
                // 0x00569a90
                charge(ctx, 3);
                divu(a3, a2);
                if (a2 == 0) {
                    brk(ctx, 0x569A98u, 0x7u);
                }
                // 0x00569a9c
                charge(ctx, 3);
                mflo(v0);
                a3 = v0;
                break;
            case 0x569AA8u:  // table[5]
                // 0x00569aa8
                charge(ctx, 3);
                divu(a3, a2);
                if (a2 == 0) {
                    brk(ctx, 0x569AB0u, 0x7u);
                }
                // 0x00569ab4
                charge(ctx, 3);
                mfhi(v0);
                a3 = v0;
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v1.u());
                return;
            }
            // 0x00569ac8
            charge(ctx, 2);
            sw(a3, s4, 0);
            v0 = 0;
        }
    } else {
        // 0x0056998c
        charge(ctx, 13);
        lw(s1, a2, 4);
        lw(s0, a2, 0);
        lw(a0, s4, 0);
        link(ctx, 0x569998u);  // $ra first: the delay slot below depends on it
        lw(a1, s4, 4);
        call(ctx, gen::fn_sub_569BD0_00569bd0);
        a0 = s0;
        a1 = s1;
        s2 = v0;
        jal(ctx, 0x5699A8u, gen::fn_sub_569BD0_00569bd0);
        a1 = v0;
        v0 = sltiu(s3, 6);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = si(-1);
        if (!cc) {
            // 0x005699c0
            charge(ctx, 6);
            v0 = sll(s3, 2);
            v1 = 0x7C0000;
            v1 = addu(v1, v0);
            lw(v1, v1, 30048);
            switch (v1.u()) {
            case 0x5699D8u:  // table[0]
                // 0x005699d8
                charge(ctx, 2);
                s2 = a1;
                break;
            case 0x5699E0u:  // table[1]
                // 0x005699e0
                charge(ctx, 2);
                s2 = s2 + a1;
                break;
            case 0x5699E8u:  // table[2]
                // 0x005699e8
                charge(ctx, 2);
                s2 = s2 - a1;
                break;
            case 0x5699F0u:  // table[3]
                // 0x005699f0
                charge(ctx, 4);
                a0 = s2;
                jal(ctx, 0x5699F0u, gen::fn___muldi3_0052ea78);
                s2 = v0;
                break;
            case 0x569A00u:  // table[4]
                // 0x00569a00
                charge(ctx, 4);
                a0 = s2;
                jal(ctx, 0x569A00u, gen::fn___divdi3_0052eeb0);
                s2 = v0;
                break;
            case 0x569A10u:  // table[5]
                // 0x00569a10
                charge(ctx, 3);
                a0 = s2;
                jal(ctx, 0x569A10u, gen::fn___moddi3_0052f6a0);
                s2 = v0;
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v1.u());
                return;
            }
            // 0x00569a1c
            charge(ctx, 6);
            a1 = s4;
            a0 = s2;
            a2 = addiu(a1, 4);
            jal(ctx, 0x569A24u, gen::fn_sub_569BE8_00569be8);
            v0 = 0;
        }
    }
    // 0x00569ad0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00569AF0 sub_569AF0 -- 108 bytes; leaf frame (no stack)
// Read a big-endian {u32, u32} pair into two words (no caller in the binary). [rfmai_GetBe64]
void sub_569AF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00569af0
    enter(ctx, 27);  // entry check point + this block's cycles
    lw(a3, a0, 0);
    lbu(v0, a0, 0);
    v1 = srl(a3, 8);
    a3 = srl(a3, 24);
    a2 = v1;
    v1 = v1 & 0xFF;
    v1 = sll(v1, 16);
    v0 = sll(v0, 24);
    a2 = a2 & 0xFF00;
    v0 = v0 | a3;
    a2 = a2 | v1;
    v0 = v0 | a2;
    sw(v0, a1, 0);
    lw(a2, a0, 4);
    lbu(v0, a0, 4);
    v1 = srl(a2, 8);
    a2 = srl(a2, 24);
    a0 = v1;
    v1 = v1 & 0xFF;
    v0 = sll(v0, 24);
    a0 = a0 & 0xFF00;
    v1 = sll(v1, 16);
    v0 = v0 | a2;
    a0 = a0 | v1;
    v0 = v0 | a0;
    sw(v0, a1, 4);
}

// 0x00569B60 sub_569B60 -- 108 bytes; leaf frame (no stack)
// Byte-swap two words in place (no caller in the binary). [rfmai_SwapBe64]
void sub_569B60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    // 0x00569b60
    enter(ctx, 27);  // entry check point + this block's cycles
    lw(t1, a0, 0);
    lw(t2, a0, 4);
    a3 = srl(t1, 8);
    lbu(v1, a0, 0);
    t0 = srl(t2, 8);
    lbu(v0, a0, 4);
    a1 = srl(t1, 8);
    t1 = srl(t1, 24);
    a2 = srl(t2, 8);
    t2 = srl(t2, 24);
    a3 = a3 & 0xFF;
    t0 = t0 & 0xFF;
    v1 = sll(v1, 24);
    a1 = a1 & 0xFF00;
    a3 = sll(a3, 16);
    v0 = sll(v0, 24);
    a2 = a2 & 0xFF00;
    t0 = sll(t0, 16);
    v1 = v1 | t1;
    a1 = a1 | a3;
    v0 = v0 | t2;
    a2 = a2 | t0;
    v1 = v1 | a1;
    v0 = v0 | a2;
    sw(v0, a0, 4);
    sw(v1, a0, 0);
}

// 0x00569C00 rfmai_decipherSectors -- 40 bytes; frame 0x10: ra sp+0x0
// Decipher n sectors of a volume: RSU_Decipher(buf, n << 11, 2048, sector, the volume's key (+36), 8).
//   [rfmai_decipherSectors]
void rfmai_decipherSectors(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00569c00
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = addiu(a0, 36);
    sd(ra, sp, 0x0);
    t1 = 8;
    a0 = a1;
    a1 = sll(a2, 11);
    ld(ra, sp, 0x0);
    a2 = 2048;
    sp = addiu(sp, 0x10);
    gen::fn_RSU_Decipher_0056d900(ctx);  // tail call
}

// 0x00569F40 sub_569F40 -- 32 bytes; leaf frame (no stack)
// Set the read timeout in the work area (+28 = 10000 x n). [rfmai_SetTimeout]
void sub_569F40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00569f40
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    lw(v1, v0, 9984);  // g_rofs_work
    v0 = 10000;
    if (v1 != 0) {
        // 0x00569f50
        charge(ctx, 2);
        mult(v0, a0, v0);
        sw(v0, v1, 28);
    }
    // 0x00569f58 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00569F60 sub_569F60 -- 220 bytes; leaf frame (no stack)
// Set a work-area flag (+24): 1 -> bit 0, 2 -> bit 1, 0 -> bit 10 (clearing it only when it is set is refused: -100);
//   other kinds -100. [rfmai_SetFlag]
void sub_569F60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00569f60
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 1;
    if (a1 == v1) {
        // 0x00569fd8
        charge(ctx, 2);
        cc = a2 != v1;  // the condition, before the delay slot changes it
        v1 = 0x7B0000;
        if (cc) {
            // 0x00569ff8
            charge(ctx, 2);
            a1 = si(-2);
        L_0056a024:
            charge(ctx, 4);
            lw(a0, v1, 9984);
            lw(v0, a0, 24);
            v0 = v0 & a1;
            sw(v0, a0, 24);
        } else {
            // 0x00569fe0
            charge(ctx, 6);
            v0 = 0x7B0000;
            lw(a0, v0, 9984);  // g_rofs_work
            lw(v1, a0, 24);
            v1 = v1 | 0x1;
            sw(v1, a0, 24);
        }
        // 0x0056a034 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x00569f6c
    charge(ctx, 2);
    v0 = 2;
    if (a1 != 0) {
        // 0x00569f74
        charge(ctx, 2);
        cc = a1 == v0;  // the condition, before the delay slot changes it
        v0 = si(-100);
        if (!cc) {
            // 0x00569f7c (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
        // 0x0056a000
        charge(ctx, 2);
        cc = a2 != v1;  // the condition, before the delay slot changes it
        v1 = 0x7B0000;
        if (cc) {
            // 0x0056a020
            charge(ctx, 1);
            a1 = si(-3);
            goto L_0056a024;
        }
        // 0x0056a008
        charge(ctx, 6);
        v0 = 0x7B0000;
        lw(a0, v0, 9984);  // g_rofs_work
        lw(v1, a0, 24);
        v1 = v1 | 0x2;
        sw(v1, a0, 24);
        // 0x0056a034 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x00569f88
    charge(ctx, 2);
    v0 = 1;
    if (a2 == 0) {
        // 0x00569f90
        charge(ctx, 6);
        v1 = 0x7B0000;
        lw(a1, v1, 9984);  // g_rofs_work
        lw(a0, a1, 24);
        v1 = a0 & 0x400;
        v0 = si(-100);
        if (v1 != 0) {
            backedge(ctx);
            // 0x00569f7c (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
        // 0x00569fa8
        charge(ctx, 4);
        v0 = si(-1025);
        v0 = a0 & v0;
        sw(v0, a1, 24);
        v0 = 1;
        goto L_00569fb8;
    }
L_00569fb8:
    charge(ctx, 2);
    if (a2 != v0) {
        v0 = 0;
        backedge(ctx);
        // 0x00569f7c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x00569fc0
    charge(ctx, 6);
    v0 = 0x7B0000;
    lw(a0, v0, 9984);  // g_rofs_work
    lw(v1, a0, 24);
    v1 = v1 | 0x400;
    sw(v1, a0, 24);
    // 0x0056a034 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = 0;
}

// 0x0056A040 sub_56A040 -- 100 bytes; leaf frame (no stack)
// Get a work-area flag: 1 -> bit 0, 2 -> bit 1, 0 -> bit 10; other kinds -100. [rfmai_GetFlag]
void sub_56A040(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0056a040
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 1;
    cc = a1 == v0;  // the condition, before the delay slot changes it
    v0 = 0x7B0000;
    if (cc) {
        // 0x0056a078
        charge(ctx, 4);
        lw(a0, v0, 9984);
        lw(v1, a0, 24);
        v1 = v1 & 0x1;
        // 0x0056a098 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        sw(v1, a2, 0);
        v0 = 0;
        return;
    }
    // 0x0056a04c
    charge(ctx, 2);
    lw(a0, v0, 9984);
    if (a1 == 0) {
        // 0x0056a068
        charge(ctx, 3);
        lw(v1, a0, 24);
        v1 = v1 & 0x400;
    L_0056a094:
        charge(ctx, 1);
        v1 = sltu(0, v1);
        // 0x0056a098 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        sw(v1, a2, 0);
        v0 = 0;
        return;
    }
    // 0x0056a054
    charge(ctx, 3);
    v0 = 2;
    if (a1 != v0) {
        // 0x0056a060
        charge(ctx, 2);
        v0 = si(-100);
        return;
    }
    v0 = 0x7B0000;
    // 0x0056a088
    charge(ctx, 3);
    lw(a0, v0, 9984);
    lw(v1, a0, 24);
    v1 = v1 & 0x2;
    goto L_0056a094;
}

// 0x0056A0A8 rfmai_copyStructCdVd -- 672 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Copy an ISO 9660 primary volume descriptor field by field (39 fields, the offset table 0x7B2710) from the sector
//   into its record. [rfmai_copyStructCdVd]
void rfmai_copyStructCdVd(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056a0a8
    enter(ctx, 168);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x9A0000;
    sd(s0, sp, 0x0);
    s0 = 0x7B0000;
    s0 = addiu(s0, 10000);  // &0x7B2710
    sd(s1, sp, 0x8);
    sw(a1, v0, -24088);  // 0x99A1E8
    a1 = s0;
    s1 = a0;
    sd(ra, sp, 0x10);
    a2 = 0;
    jal(ctx, 0x56A0D0u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 1);
    a1 = s0;
    a2 = 1;
    jal(ctx, 0x56A0E0u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 6);
    a1 = s0;
    a2 = 2;
    jal(ctx, 0x56A0F0u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 7);
    a1 = s0;
    a2 = 3;
    jal(ctx, 0x56A100u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 8);
    a1 = s0;
    a2 = 4;
    jal(ctx, 0x56A110u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 40);
    a1 = s0;
    a2 = 5;
    jal(ctx, 0x56A120u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 72);
    a1 = s0;
    a2 = 6;
    jal(ctx, 0x56A130u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 80);
    a1 = s0;
    a2 = 7;
    jal(ctx, 0x56A140u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 84);
    a1 = s0;
    a2 = 8;
    jal(ctx, 0x56A150u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 88);
    a1 = s0;
    a2 = 9;
    jal(ctx, 0x56A160u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 92);
    a1 = s0;
    a2 = 10;
    jal(ctx, 0x56A170u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 120);
    a1 = s0;
    a2 = 11;
    jal(ctx, 0x56A180u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 122);
    a1 = s0;
    a2 = 12;
    jal(ctx, 0x56A190u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 124);
    a1 = s0;
    a2 = 13;
    jal(ctx, 0x56A1A0u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 126);
    a1 = s0;
    a2 = 14;
    jal(ctx, 0x56A1B0u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 128);
    a1 = s0;
    a2 = 15;
    jal(ctx, 0x56A1C0u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 130);
    a1 = s0;
    a2 = 16;
    jal(ctx, 0x56A1D0u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 132);
    a1 = s0;
    a2 = 17;
    jal(ctx, 0x56A1E0u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 136);
    a1 = s0;
    a2 = 18;
    jal(ctx, 0x56A1F0u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 140);
    a1 = s0;
    a2 = 19;
    jal(ctx, 0x56A200u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 144);
    a1 = s0;
    a2 = 20;
    jal(ctx, 0x56A210u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 148);
    a1 = s0;
    a2 = 21;
    jal(ctx, 0x56A220u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 152);
    a1 = s0;
    a2 = 22;
    jal(ctx, 0x56A230u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 156);
    a1 = s0;
    a2 = 23;
    jal(ctx, 0x56A240u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 190);
    a1 = s0;
    a2 = 24;
    jal(ctx, 0x56A250u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 318);
    a1 = s0;
    a2 = 25;
    jal(ctx, 0x56A260u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 446);
    a1 = s0;
    a2 = 26;
    jal(ctx, 0x56A270u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 574);
    a1 = s0;
    a2 = 27;
    jal(ctx, 0x56A280u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 702);
    a1 = s0;
    a2 = 28;
    jal(ctx, 0x56A290u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 739);
    a1 = s0;
    a2 = 29;
    jal(ctx, 0x56A2A0u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 776);
    a1 = s0;
    a2 = 30;
    jal(ctx, 0x56A2B0u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 813);
    a1 = s0;
    a2 = 31;
    jal(ctx, 0x56A2C0u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 830);
    a1 = s0;
    a2 = 32;
    jal(ctx, 0x56A2D0u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 847);
    a1 = s0;
    a2 = 33;
    jal(ctx, 0x56A2E0u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 864);
    a1 = s0;
    a2 = 34;
    jal(ctx, 0x56A2F0u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 881);
    a1 = s0;
    a2 = 35;
    jal(ctx, 0x56A300u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 882);
    a1 = s0;
    a2 = 36;
    jal(ctx, 0x56A310u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 883);
    a1 = s0;
    a2 = 37;
    jal(ctx, 0x56A320u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s1, 1395);
    a1 = s0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a2 = 38;
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_56A4F8_0056a4f8(ctx);  // tail call
}

// 0x0056A348 RFMAI_CopyStructCdDr -- 288 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Copy an ISO 9660 directory record (14 fields, table 0x7B27B0) into the static record 0x99A1F0 and return it.
//   [RFMAI_CopyStructCdDr]
// The big-endian halves of the extent, size and sequence number are copied raw (no byte swap).
void RFMAI_CopyStructCdDr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056a348
    enter(ctx, 72);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x9A0000;
    sd(s0, sp, 0x0);
    s0 = 0x9A0000;
    sd(s1, sp, 0x8);
    s1 = 0x7B0000;
    s0 = addiu(s0, -24080);  // &0x99A1F0
    s1 = addiu(s1, 10160);  // &0x7B27B0
    sw(a0, v0, -24088);  // 0x99A1E8
    a0 = s0;
    a1 = s1;
    sd(ra, sp, 0x10);
    a2 = 0;
    jal(ctx, 0x56A378u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s0, 1);  // &0x99A1F1
    a1 = s1;
    a2 = 1;
    jal(ctx, 0x56A388u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s0, 4);  // &0x99A1F4
    a1 = s1;
    a2 = 2;
    jal(ctx, 0x56A398u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s0, 8);  // &0x99A1F8
    a1 = s1;
    a2 = 3;
    jal(ctx, 0x56A3A8u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s0, 12);  // &0x99A1FC
    a1 = s1;
    a2 = 4;
    jal(ctx, 0x56A3B8u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s0, 16);  // &0x99A200
    a1 = s1;
    a2 = 5;
    jal(ctx, 0x56A3C8u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s0, 20);  // &0x99A204
    a1 = s1;
    a2 = 6;
    jal(ctx, 0x56A3D8u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s0, 27);  // &0x99A20B
    a1 = s1;
    a2 = 7;
    jal(ctx, 0x56A3E8u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s0, 28);  // &0x99A20C
    a1 = s1;
    a2 = 8;
    jal(ctx, 0x56A3F8u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s0, 29);  // &0x99A20D
    a1 = s1;
    a2 = 9;
    jal(ctx, 0x56A408u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s0, 30);  // &0x99A20E
    a1 = s1;
    a2 = 10;
    jal(ctx, 0x56A418u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s0, 32);  // &0x99A210
    a1 = s1;
    a2 = 11;
    jal(ctx, 0x56A428u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s0, 34);  // &0x99A212
    a1 = s1;
    a2 = 12;
    jal(ctx, 0x56A438u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s0, 35);  // &0x99A213
    a1 = s1;
    a2 = 13;
    jal(ctx, 0x56A448u, gen::fn_sub_56A4F8_0056a4f8);
    v0 = s0;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0056A468 RFMAI_CopyStructCdPt -- 144 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Copy an ISO 9660 path table record (5 fields, table 0x7B27F0) into the static record 0x99A1F0.
//   [RFMAI_CopyStructCdPt]
void RFMAI_CopyStructCdPt(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056a468
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x9A0000;
    sd(s0, sp, 0x0);
    s0 = 0x9A0000;
    sd(s1, sp, 0x8);
    s1 = 0x7B0000;
    s0 = addiu(s0, -24080);  // &0x99A1F0
    s1 = addiu(s1, 10224);  // &0x7B27F0
    sw(a0, v0, -24088);  // 0x99A1E8
    a0 = s0;
    a1 = s1;
    sd(ra, sp, 0x10);
    a2 = 0;
    jal(ctx, 0x56A498u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s0, 1);  // &0x99A1F1
    a1 = s1;
    a2 = 1;
    jal(ctx, 0x56A4A8u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s0, 4);  // &0x99A1F4
    a1 = s1;
    a2 = 2;
    jal(ctx, 0x56A4B8u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s0, 8);  // &0x99A1F8
    a1 = s1;
    a2 = 3;
    jal(ctx, 0x56A4C8u, gen::fn_sub_56A4F8_0056a4f8);
    a0 = addiu(s0, 10);  // &0x99A1FA
    a1 = s1;
    a2 = 4;
    jal(ctx, 0x56A4D8u, gen::fn_sub_56A4F8_0056a4f8);
    v0 = s0;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0056A4F8 sub_56A4F8 -- 52 bytes; frame 0x10: ra sp+0x0
// Copy field n of the source (0x99A1E8) through an offset table: memcpy(dst, src + table[n], table[n + 1] -
//   table[n]). [rfmai_CopyField]
void sub_56A4F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056a4f8
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = sll(a2, 2);
    sd(ra, sp, 0x0);
    a2 = addu(a2, a1);
    v0 = 0x9A0000;
    lw(v1, a2, 0);
    lw(a1, v0, -24088);  // 0x99A1E8
    lw(a2, a2, 4);
    ld(ra, sp, 0x0);
    a1 = addu(a1, v1);
    a2 = subu(a2, v1);
    sp = addiu(sp, 0x10);
    gen::fn_memcpy_00521250(ctx);  // tail call
}

// 0x0056AB78 RFPFS_PfsWait -- 20 bytes; frame 0x10: ra sp+0x0
// The PFS wait (7,551 empty iterations). [RFPFS_PfsWait]
void RFPFS_PfsWait(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0056ab78
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_56DDF8_0056ddf8(ctx);  // tail call
}

// 0x0056AB90 RFPFS_PfsLock -- 80 bytes; frame 0x10: ra sp+0x0
// Take the PFS lock: 0, or reported -202 when it was held. [RFPFS_PfsLock]
void RFPFS_PfsLock(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056ab90
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x56AB98u, gen::fn_coshl_9_0056dd80);
    a0 = 0x7C0000;
    a2 = 0x7C0000;
    v1 = 1;
    a0 = addiu(a0, 30216);  // "../../rofs_pfs.c"
    a2 = addiu(a2, 30400);  // "RFPFS_PfsLock"
    a1 = 419;
    a3 = 0;
    t0 = si(-202);
    if (v0 == v1) {
        // 0x0056abd0
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        v0 = 0;
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0056abc4
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_569730_00569730(ctx);  // tail call
}

// 0x0056ABE0 sub_56ABE0 -- 20 bytes; frame 0x10: ra sp+0x0
// Release the PFS lock. [rfpfs_PfsUnlock]
void sub_56ABE0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0056abe0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_56DDC8_0056ddc8(ctx);  // tail call
}

// 0x0056ABF8 sub_56ABF8 -- 20 bytes; frame 0x10: ra sp+0x0
// ROFS's server lock (the SVM lock, type 1). [rfpfs_LockSvr]
void sub_56ABF8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0056abf8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_atan2l_9_0056dd50(ctx);  // tail call
}

// 0x0056AC10 sub_56AC10 -- 20 bytes; frame 0x10: ra sp+0x0
// ROFS's server unlock. [rfpfs_UnlockSvr]
void sub_56AC10(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0056ac10
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_cosl_9_0056dd68(ctx);  // tail call
}

// 0x0056AD28 RFPFS_SetPfsTbl -- 12 bytes; leaf frame (no stack)
// Set the PFS device table (0x7B2808). [RFPFS_SetPfsTbl]
void RFPFS_SetPfsTbl(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0056ad28
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sw(a0, v0, 10248);  // g_rofs_pfs_tbl
}

// 0x0056AD48 cvmh_GetSize -- 108 bytes; leaf frame (no stack)
// Read a big-endian 64-bit size {hi, lo} into {lo, hi}. [cvmh_GetSize]
void cvmh_GetSize(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0056ad48
    enter(ctx, 27);  // entry check point + this block's cycles
    lw(a3, a0, 0);
    lbu(v0, a0, 0);
    v1 = srl(a3, 8);
    a3 = srl(a3, 24);
    a2 = v1;
    v1 = v1 & 0xFF;
    v1 = sll(v1, 16);
    v0 = sll(v0, 24);
    a2 = a2 & 0xFF00;
    v0 = v0 | a3;
    a2 = a2 | v1;
    v0 = v0 | a2;
    sw(v0, a1, 4);
    lw(a2, a0, 4);
    lbu(v0, a0, 4);
    v1 = srl(a2, 8);
    a2 = srl(a2, 24);
    a0 = v1;
    v1 = v1 & 0xFF;
    v0 = sll(v0, 24);
    a0 = a0 & 0xFF00;
    v1 = sll(v1, 16);
    v0 = v0 | a2;
    a0 = a0 | v1;
    v0 = v0 | a0;
    sw(v0, a1, 0);
}

// 0x0056ADB8 sub_56ADB8 -- 36 bytes; leaf frame (no stack)
// Copy 4 bytes. [cvmh_Copy4]
void sub_56ADB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0056adb8
    enter(ctx, 9);  // entry check point + this block's cycles
    lbu(v0, a0, 0);
    sb(v0, a1, 0);
    lbu(v1, a0, 1);
    sb(v1, a1, 1);
    lbu(v0, a0, 2);
    sb(v0, a1, 2);
    lbu(v1, a0, 3);
    sb(v1, a1, 3);
}

// 0x0056ADE0 sub_56ADE0 -- 60 bytes; leaf frame (no stack)
// Copy 7 bytes (a date). [cvmh_Copy7]
void sub_56ADE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0056ade0
    enter(ctx, 15);  // entry check point + this block's cycles
    lbu(v0, a0, 0);
    sb(v0, a1, 0);
    lbu(v1, a0, 1);
    sb(v1, a1, 1);
    lbu(v0, a0, 2);
    sb(v0, a1, 2);
    lbu(v1, a0, 3);
    sb(v1, a1, 3);
    lbu(v0, a0, 4);
    sb(v0, a1, 4);
    lbu(v1, a0, 5);
    sb(v1, a1, 5);
    lbu(v0, a0, 6);
    sb(v0, a1, 6);
}

// 0x0056AE20 cvmh_AnalyMainHdrCvm -- 520 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Parse a CVM main header (big-endian): the size, the date, the version, flags, the 64-byte ID, the zone count
//   (+100), the zone select (+104) and the data sector offset (+108) into the 1904-byte info. [cvmh_AnalyMainHdrCvm]
void cvmh_AnalyMainHdrCvm(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056ae20
    enter(ctx, 130);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    a0 = addiu(s0, 16);
    jal(ctx, 0x56AE38u, gen::fn_cvmh_GetSize_0056ad48);
    a0 = addiu(s0, 24);
    a1 = addiu(s1, 8);
    jal(ctx, 0x56AE44u, gen::fn_sub_56ADE0_0056ade0);
    a0 = addiu(s0, 32);
    a1 = addiu(s1, 16);
    jal(ctx, 0x56AE50u, gen::fn_sub_56ADB8_0056adb8);
    t0 = addiu(s0, 36);
    lw(a1, t0, 0);
    a0 = addiu(s0, 108);
    lbu(v0, t0, 0);
    t0 = addiu(s0, 40);
    v1 = srl(a1, 8);
    a1 = srl(a1, 24);
    a2 = v1;
    v1 = v1 & 0xFF;
    v1 = sll(v1, 16);
    v0 = sll(v0, 24);
    a2 = a2 & 0xFF00;
    v0 = v0 | a1;
    a2 = a2 | v1;
    a1 = addiu(s1, 92);
    v0 = v0 | a2;
    sw(v0, s1, cvm_info::kFlags);
    lw(a3, t0, 0);
    lbu(v0, t0, 0);
    v1 = srl(a3, 8);
    a3 = srl(a3, 24);
    a2 = v1;
    v1 = v1 & 0xFF;
    v1 = sll(v1, 16);
    v0 = sll(v0, 24);
    a2 = a2 & 0xFF00;
    v0 = v0 | a3;
    a2 = a2 | v1;
    v0 = v0 | a2;
    sw(v0, s1, cvm_info::kWord24);
    ldl(v0, s0, 51);
    ldr(v0, s0, 44);
    ldl(v1, s0, 59);
    ldr(v1, s0, 52);
    ldl(a2, s0, 67);
    ldr(a2, s0, 60);
    ldl(a3, s0, 75);
    ldr(a3, s0, 68);
    sdl(v0, s1, 35);
    sdr(v0, s1, 28);
    sdl(v1, s1, 43);
    sdr(v1, s1, 36);
    sdl(a2, s1, 51);
    sdr(a2, s1, 44);
    sdl(a3, s1, 59);
    sdr(a3, s1, 52);
    ldl(v0, s0, 83);
    ldr(v0, s0, 76);
    ldl(v1, s0, 91);
    ldr(v1, s0, 84);
    ldl(a2, s0, 99);
    ldr(a2, s0, 92);
    ldl(a3, s0, 107);
    ldr(a3, s0, 100);
    sdl(v0, s1, 67);
    sdr(v0, s1, 60);
    sdl(v1, s1, 75);
    sdr(v1, s1, 68);
    sdl(a2, s1, 83);
    sdr(a2, s1, 76);
    sdl(a3, s1, 91);
    sdr(a3, s1, 84);
    link(ctx, 0x56AF50u);  // $ra first: the delay slot below depends on it
    sb(zero, s1, cvm_info::kIdEnd);
    call(ctx, gen::fn_sub_56ADB8_0056adb8);
    lbu(a0, s0, cvm_main::kByte112);
    t0 = addiu(s0, 116);
    ld(ra, sp, 0x10);
    sb(a0, s1, cvm_info::kByte96);
    v0 = 0;
    lbu(v1, s0, cvm_main::kByte113);
    sb(v1, s1, cvm_info::kByte97);
    lw(a2, t0, 0);
    lbu(v1, t0, 0);
    t0 = addiu(s0, 120);
    a0 = sra(a2, 8);
    a2 = srl(a2, 24);
    a1 = a0;
    a0 = a0 & 0xFF;
    a0 = sll(a0, 16);
    v1 = sll(v1, 24);
    a1 = a1 & 0xFF00;
    v1 = v1 | a2;
    a1 = a1 | a0;
    v1 = v1 | a1;
    sw(v1, s1, cvm_info::kNumZones);
    lw(a2, t0, 0);
    lbu(v1, t0, 0);
    t0 = addiu(s0, 124);
    a0 = sra(a2, 8);
    a2 = srl(a2, 24);
    a1 = a0;
    a0 = a0 & 0xFF;
    a0 = sll(a0, 16);
    v1 = sll(v1, 24);
    a1 = a1 & 0xFF00;
    v1 = v1 | a2;
    a1 = a1 | a0;
    ld(s0, sp, 0x0);
    v1 = v1 | a1;
    sw(v1, s1, cvm_info::kZoneSel);
    lw(a2, t0, 0);
    lbu(v1, t0, 0);
    a0 = sra(a2, 8);
    a2 = srl(a2, 24);
    a1 = a0;
    a0 = a0 & 0xFF;
    a0 = sll(a0, 16);
    v1 = sll(v1, 24);
    a1 = a1 & 0xFF00;
    v1 = v1 | a2;
    a1 = a1 | a0;
    v1 = v1 | a1;
    sw(v1, s1, cvm_info::kDataSct);
    ld(s1, sp, 0x8);
    sp = addiu(sp, 0x20);
}

// 0x0056B028 cvmh_AnalyCvmHdr -- 164 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Parse a CVMH header: the main part at +12, then the zone table at +256 (one big-endian u32 per zone) into info
//   +112. [cvmh_AnalyCvmHdr]
void cvmh_AnalyCvmHdr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056b028
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    a0 = addiu(s0, 12);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x56B040u, gen::fn_cvmh_AnalyMainHdrCvm_0056ae20);
    if (v0 != 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0056b050
        charge(ctx, 4);
        lw(v0, s1, 100);
        a2 = addiu(s0, 256);
        t0 = 0;
        if (i64(v0) > 0) {
            // 0x0056b060
            charge(ctx, 2);
            a3 = addiu(s1, 112);
            for (;;) {
                // 0x0056b068
                charge(ctx, 19);
                lw(a1, a2, 0);
                t0 = addiu(t0, 1);
                lbu(v0, a2, 0);
                a2 = addiu(a2, 4);
                v1 = sra(a1, 8);
                a1 = srl(a1, 24);
                a0 = v1;
                v1 = v1 & 0xFF;
                v0 = sll(v0, 24);
                a0 = a0 & 0xFF00;
                v1 = sll(v1, 16);
                v0 = v0 | a1;
                a0 = a0 | v1;
                v0 = v0 | a0;
                sw(v0, a3, 0);
                lw(v0, s1, 100);
                v0 = slt(t0, v0);
                a3 = addiu(a3, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0056b0b4
        charge(ctx, 2);
        v0 = 0;
        ld(s0, sp, 0x0);
    }
    // 0x0056b0bc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0056B0D0 cvmh_GetZoneDataLoc -- 88 bytes; frame 0x10: ra sp+0x0
// Read a zone's data location: a big-endian sector and a 64-bit size. [cvmh_GetZoneDataLoc]
void cvmh_GetZoneDataLoc(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056b0d0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    a0 = addiu(v0, 4);
    t0 = a1;
    lw(a3, v0, 0);
    a1 = addiu(t0, 4);
    lbu(v1, v0, 0);
    v0 = sra(a3, 8);
    a3 = srl(a3, 24);
    a2 = v0;
    v0 = v0 & 0xFF;
    v0 = sll(v0, 16);
    v1 = sll(v1, 24);
    a2 = a2 & 0xFF00;
    v1 = v1 | a3;
    a2 = a2 | v0;
    ld(ra, sp, 0x0);
    v1 = v1 | a2;
    sw(v1, t0, 0);
    sp = addiu(sp, 0x10);
    gen::fn_cvmh_GetSize_0056ad48(ctx);  // tail call
}

// 0x0056B128 cvmh_AnalyZoneHdr -- 280 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Parse a ZONE header: the sector length, the 5 flag bytes, two words, the two data locations. [cvmh_AnalyZoneHdr]
void cvmh_AnalyZoneHdr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056b128
    enter(ctx, 70);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    t0 = addiu(s0, 12);
    a0 = addiu(s0, 32);
    a1 = addiu(s1, 20);
    lw(a3, t0, 0);
    lbu(v0, t0, 0);
    t0 = addiu(s0, 24);
    v1 = srl(a3, 8);
    a3 = srl(a3, 24);
    a2 = v1;
    v1 = v1 & 0xFF;
    v1 = sll(v1, 16);
    v0 = sll(v0, 24);
    a2 = a2 & 0xFF00;
    v0 = v0 | a3;
    a2 = a2 | v1;
    v0 = v0 | a2;
    sw(v0, s1, zone_info::kWord0);
    lbu(v1, s0, zone_hdr::kFlag0);
    sb(v1, s1, zone_info::kFlag0);
    lbu(v0, s0, zone_hdr::kFlag1);
    sb(v0, s1, zone_info::kFlag1);
    lbu(v1, s0, zone_hdr::kFlag2);
    sb(v1, s1, zone_info::kFlag2);
    lbu(v0, s0, zone_hdr::kFlag3);
    sb(v0, s1, zone_info::kFlag3);
    lbu(v1, s0, zone_hdr::kFlag4);
    sb(v1, s1, zone_info::kFlag4);
    lw(a3, t0, 0);
    lbu(v0, t0, 0);
    t0 = addiu(s0, 28);
    v1 = sra(a3, 8);
    a3 = srl(a3, 24);
    a2 = v1;
    v1 = v1 & 0xFF;
    v1 = sll(v1, 16);
    v0 = sll(v0, 24);
    a2 = a2 & 0xFF00;
    v0 = v0 | a3;
    a2 = a2 | v1;
    v0 = v0 | a2;
    sw(v0, s1, zone_info::kWord12);
    lw(a3, t0, 0);
    lbu(v0, t0, 0);
    v1 = sra(a3, 8);
    a3 = srl(a3, 24);
    a2 = v1;
    v1 = v1 & 0xFF;
    v1 = sll(v1, 16);
    v0 = sll(v0, 24);
    a2 = a2 & 0xFF00;
    v0 = v0 | a3;
    a2 = a2 | v1;
    v0 = v0 | a2;
    link(ctx, 0x56B214u);  // $ra first: the delay slot below depends on it
    sw(v0, s1, zone_info::kWord16);
    call(ctx, gen::fn_cvmh_GetZoneDataLoc_0056b0d0);
    a0 = addiu(s0, 44);
    a1 = addiu(s1, 32);
    jal(ctx, 0x56B220u, gen::fn_cvmh_GetZoneDataLoc_0056b0d0);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0056B240 CVMH_AnalyCvmHdr -- 188 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Analyse a CVM header (1904-byte info cleared): magic 'CVMH' -> cvmh_AnalyCvmHdr, 'CIMF' -> the CD CRAFT image form
//   (sub_56B690); else -2. [CVMH_AnalyCvmHdr]
// The CD CRAFT magic is 'CIMF' (0x43494D46); the disc's three CVMs are 'CVMH'.
void CVMH_AnalyCvmHdr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056b240
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 1904;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    a1 = 0;
    sd(ra, sp, 0x10);
    a0 = s1;
    jal(ctx, 0x56B260u, gen::fn_memset_00521408);
    lw(a1, s0, 0);
    a3 = 0x43490000;
    lbu(a2, s0, 0);
    t0 = 0x43560000;
    v0 = srl(a1, 8);
    a1 = srl(a1, 24);
    v1 = v0;
    v0 = v0 & 0xFF;
    a2 = sll(a2, 24);
    v1 = v1 & 0xFF00;
    v0 = sll(v0, 16);
    a2 = a2 | a1;
    v1 = v1 | v0;
    a3 = a3 | 0x4D46;
    a2 = a2 | v1;
    a0 = s0;
    a1 = s1;
    t0 = t0 | 0x4D48;
    if (a2 != a3) {
        // 0x0056b2c8
        charge(ctx, 2);
        if (a2 != t0) {
            v0 = si(-2);
            // 0x0056b2e8
            charge(ctx, 1);
            ld(s0, sp, 0x0);
        } else {
            // 0x0056b2d0
            charge(ctx, 5);
            a0 = s0;
            a1 = s1;
            jal(ctx, 0x56B2D4u, gen::fn_cvmh_AnalyCvmHdr_0056b028);
            ld(s0, sp, 0x0);
        }
    } else {
        // 0x0056b2b4
        charge(ctx, 4);
        jal(ctx, 0x56B2B4u, gen::fn_sub_56B690_0056b690);
        ld(s0, sp, 0x0);
    }
    // 0x0056b2ec (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0056B300 CVMH_AnalyZoneHdr -- 188 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Analyse a zone header (44-byte info cleared): 'ZONE' -> cvmh_AnalyZoneHdr, 'CIMF' -> the CD CRAFT form
//   (sub_56B6E0); else -2. [CVMH_AnalyZoneHdr]
void CVMH_AnalyZoneHdr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056b300
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 44;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    a1 = 0;
    sd(ra, sp, 0x10);
    a0 = s1;
    jal(ctx, 0x56B320u, gen::fn_memset_00521408);
    lw(a1, s0, 0);
    a3 = 0x43490000;
    lbu(a2, s0, 0);
    t0 = 0x5A4F0000;
    v0 = srl(a1, 8);
    a1 = srl(a1, 24);
    v1 = v0;
    v0 = v0 & 0xFF;
    a2 = sll(a2, 24);
    v1 = v1 & 0xFF00;
    v0 = sll(v0, 16);
    a2 = a2 | a1;
    v1 = v1 | v0;
    a3 = a3 | 0x4D46;
    a2 = a2 | v1;
    a0 = s0;
    a1 = s1;
    t0 = t0 | 0x4E45;
    if (a2 != a3) {
        // 0x0056b388
        charge(ctx, 2);
        if (a2 != t0) {
            v0 = si(-2);
            // 0x0056b3a8
            charge(ctx, 1);
            ld(s0, sp, 0x0);
        } else {
            // 0x0056b390
            charge(ctx, 5);
            a0 = s0;
            a1 = s1;
            jal(ctx, 0x56B394u, gen::fn_cvmh_AnalyZoneHdr_0056b128);
            ld(s0, sp, 0x0);
        }
    } else {
        // 0x0056b374
        charge(ctx, 4);
        jal(ctx, 0x56B374u, gen::fn_sub_56B6E0_0056b6e0);
        ld(s0, sp, 0x0);
    }
    // 0x0056b3ac (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0056B3C0 sub_56B3C0 -- 356 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// The same 64 / 32-bit arithmetic on CVM sizes (op 0 clears the 8 bytes first). [cvmh_Calc64]
void sub_56B3C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056b3c0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 1;
    sd(s1, sp, 0x8);
    s1 = a3;
    sd(s0, sp, 0x0);
    t0 = a0;
    sd(ra, sp, 0x10);
    if (a1 == v0) {
        // 0x0056b3e0
        charge(ctx, 4);
        v0 = sltiu(t0, 6);
        ld(s0, a2, 0);
        ld(a0, s1, 0);
        if (v0 == 0) {
            goto L_0056b500;
        }
        // 0x0056b3f0
        charge(ctx, 6);
        v0 = sll(t0, 2);
        v1 = 0x7C0000;
        v1 = addu(v1, v0);
        lw(v1, v1, 30416);
        switch (v1.u()) {
        case 0x56B408u:  // table[0]
            // 0x0056b408
            charge(ctx, 6);
            a0 = s1;
            a1 = 0;
            a2 = 8;
            jal(ctx, 0x56B410u, gen::fn_memset_00521408);
            a0 = s0;
            break;
        case 0x56B420u:  // table[1]
            // 0x0056b420
            charge(ctx, 2);
            a0 = a0 + s0;
            break;
        case 0x56B428u:  // table[2]
            // 0x0056b428
            charge(ctx, 2);
            a0 = a0 - s0;
            break;
        case 0x56B430u:  // table[3]
            // 0x0056b430
            charge(ctx, 4);
            a1 = s0;
            jal(ctx, 0x56B430u, gen::fn___muldi3_0052ea78);
            a0 = v0;
            break;
        case 0x56B440u:  // table[4]
            // 0x0056b440
            charge(ctx, 4);
            a1 = s0;
            jal(ctx, 0x56B440u, gen::fn___divdi3_0052eeb0);
            a0 = v0;
            break;
        case 0x56B450u:  // table[5]
            // 0x0056b450
            charge(ctx, 3);
            a1 = s0;
            jal(ctx, 0x56B450u, gen::fn___moddi3_0052f6a0);
            a0 = v0;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
        // 0x0056b45c
        charge(ctx, 2);
        sd(a0, s1, 0);
        goto L_0056b50c;
    }
    // 0x0056b468
    charge(ctx, 2);
    lw(a3, s1, 0);
    if (a1 != 0) {
        // 0x0056b470
        charge(ctx, 3);
        v1 = 2;
        v0 = 0;
        if (a1 == v1) {
            goto L_0056b47c;
        }
        // 0x0056b510 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_0056b47c:
    charge(ctx, 3);
    v0 = sltiu(t0, 6);
    lw(s0, a2, 0);
    if (v0 == 0) {
    L_0056b500:
        charge(ctx, 2);
        v0 = si(-1);
    } else {
        // 0x0056b488
        charge(ctx, 6);
        v0 = sll(t0, 2);
        v1 = 0x7C0000;
        v1 = addu(v1, v0);
        lw(v1, v1, 30448);
        switch (v1.u()) {
        case 0x56B4A0u:  // table[0]
            // 0x0056b4a0
            charge(ctx, 6);
            a0 = s1;
            a1 = 0;
            a2 = 8;
            jal(ctx, 0x56B4A8u, gen::fn_memset_00521408);
            a3 = s0;
            break;
        case 0x56B4B8u:  // table[1]
            // 0x0056b4b8
            charge(ctx, 2);
            a3 = addu(a3, s0);
            break;
        case 0x56B4C0u:  // table[2]
            // 0x0056b4c0
            charge(ctx, 2);
            a3 = subu(a3, s0);
            break;
        case 0x56B4C8u:  // table[3]
            // 0x0056b4c8
            charge(ctx, 2);
            mult(a3, a3, s0);
            break;
        case 0x56B4D0u:  // table[4]
            // 0x0056b4d0
            charge(ctx, 3);
            divu(a3, s0);
            if (s0 == 0) {
                brk(ctx, 0x56B4D8u, 0x7u);
            }
            // 0x0056b4dc
            charge(ctx, 3);
            mflo(v0);
            a3 = v0;
            break;
        case 0x56B4E8u:  // table[5]
            // 0x0056b4e8
            charge(ctx, 3);
            divu(a3, s0);
            if (s0 == 0) {
                brk(ctx, 0x56B4F0u, 0x7u);
            }
            // 0x0056b4f4
            charge(ctx, 3);
            mfhi(v0);
            a3 = v0;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
        // 0x0056b508
        charge(ctx, 1);
        sw(a3, s1, 0);
    L_0056b50c:
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x0056b510 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0056B528 sub_56B528 -- 360 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// A 'CIMF' (CD CRAFT) image's main info: the size (+4, big-endian, + 8), "SFORCRI CD CRAFT" as the ID, one zone, the
//   data offset (+32 + 352,816) / 2048. [cvmh_AnalyMainHdrCimf]
void sub_56B528(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056b528
    enter(ctx, 90);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(ra, sp, 0x20);
    t0 = addiu(s1, 4);
    a2 = sp;
    a0 = 0;
    lw(a3, t0, 0);
    a1 = 0;
    lbu(v0, t0, 0);
    v1 = srl(a3, 8);
    a3 = srl(a3, 24);
    t0 = v1;
    v1 = v1 & 0xFF;
    v1 = sll(v1, 16);
    v0 = sll(v0, 24);
    t0 = t0 & 0xFF00;
    v0 = v0 | a3;
    t0 = t0 | v1;
    a3 = s0;
    v0 = v0 | t0;
    v0 = addiu(v0, 8);
    link(ctx, 0x56B588u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x0);
    call(ctx, gen::fn_sub_56B3C0_0056b3c0);
    v1 = 0x524F0000;
    a3 = addiu(s0, 16);
    a1 = 1;
    v1 = v1 | 0x4653;
    v0 = 16;
    a0 = 0x7C0000;
    sb(v0, a3, 1);
    v0 = 0;
    sb(zero, a3, 3);
    t0 = addiu(s1, 36);
    sb(zero, a3, 0);
    a2 = 4;
    sb(zero, a3, 2);
    a3 = addiu(s0, 92);
    sw(a1, s0, 20);
    sw(v1, s0, 24);
    t3 = addiu(a0, 30472);  // "CRI CD CRAFT"
    ldl(v1, t3, 7);  // 0x7C770F
    ldr(v1, t3, 0);  // 0x7C7708
    lw(t1, t3, 8);  // 0x7C7710
    lb(t2, t3, 12);  // 0x7C7714
    sdl(v1, s0, 35);
    sdr(v1, s0, 28);
    sw(t1, s0, 36);
    sb(t2, s0, 40);
    ld(ra, sp, 0x20);
    lbu(v1, t0, 1);
    sb(v1, a3, 0);
    lbu(a0, t0, 2);
    sb(a0, a3, 1);
    lbu(v1, t0, 3);
    t0 = addiu(s1, 32);
    sb(zero, a3, 3);
    sb(v1, a3, 2);
    sw(a1, s0, 100);
    sb(a1, s0, 96);
    sb(a2, s0, 97);
    sw(zero, s0, 104);
    ld(s1, sp, 0x18);
    lw(a2, t0, 0);
    lbu(a0, t0, 0);
    v1 = sra(a2, 8);
    a2 = srl(a2, 24);
    a1 = v1;
    v1 = v1 & 0xFF;
    v1 = sll(v1, 16);
    a0 = sll(a0, 24);
    a1 = a1 & 0xFF00;
    a0 = a0 | a2;
    a1 = a1 | v1;
    a0 = a0 | a1;
    v1 = 0x50000;
    v1 = v1 | 0x6230;
    v1 = addu(v1, a0);
    at = 0x50000;
    at = at | 0x6A2F;
    a0 = addu(at, a0);
    a1 = slti(v1, 0);
    if (a1 != 0) v1 = a0;
    v1 = sra(v1, 11);
    sw(v1, s0, 108);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x30);
}

// 0x0056B690 sub_56B690 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// A 'CIMF' image's header: the four static locations (0x99B230..0x99B23C) cleared, the main info, zone 0's table
//   entry 0. [cvmh_AnalyCimfHdr]
void sub_56B690(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056b690
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x9A0000;
    v1 = 0x9A0000;
    a2 = 0x9A0000;
    a3 = 0x9A0000;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a1;
    sw(zero, v0, -19920);  // 0x99B230
    sw(zero, v1, -19916);  // 0x99B234
    sw(zero, a2, -19912);  // 0x99B238
    link(ctx, 0x56B6BCu);  // $ra first: the delay slot below depends on it
    sw(zero, a3, -19908);
    call(ctx, gen::fn_sub_56B528_0056b528);
    if (v0 == 0) {
        sw(zero, s0, 112);
    }
    // 0x0056b6cc
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0056B6E0 sub_56B6E0 -- 568 bytes; frame 0x40: s2 sp+0x20, s3 sp+0x28, s0 sp+0x10, s1 sp+0x18, s4 sp+0x30, ra sp+0x38
// A 'CIMF' image's zone info: the mode (1 -> 0, 2 -> 1, 4 -> 2; other modes -4), 2352 / 2450-byte raw sectors, the
//   two data locations (each also kept in 0x99B230..0x99B23C). [cvmh_AnalyCimfZoneHdr]
void sub_56B6E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0056b6e0
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 3;
    sd(s2, sp, 0x20);
    s2 = a1;
    sd(s3, sp, 0x28);
    s3 = a0;
    sd(s0, sp, 0x10);
    a2 = 2;
    sd(s1, sp, 0x18);
    sd(s4, sp, 0x30);
    sd(ra, sp, 0x38);
    sw(v0, s2, 0);
    v0 = addiu(s3, 16);
    sb(zero, s2, 4);
    lw(a0, v0, 0);
    lbu(a1, v0, 0);
    v0 = srl(a0, 8);
    a0 = srl(a0, 24);
    v1 = v0;
    v0 = v0 & 0xFF;
    a1 = sll(a1, 24);
    v1 = v1 & 0xFF00;
    v0 = sll(v0, 16);
    a1 = a1 | a0;
    v1 = v1 | v0;
    a0 = a1 | v1;
    v1 = a0;
    sw(a0, sp, 0x0);
    if (v1 == a2) {
        // 0x0056b798
        charge(ctx, 3);
        a2 = 1;
        s4 = si(-3);
    L_0056b7b0:
        charge(ctx, 83);
        v0 = 4;
        v1 = si(-8);
        a0 = 1;
        a1 = 2352;
        a3 = 2450;
        sb(a2, s2, 5);
        sb(v0, s2, 6);
        v0 = addiu(s3, 28);
        sb(a0, s2, 8);
        a0 = 0;
        sw(a1, s2, 12);
        a1 = 0;
        sw(a3, s2, 16);
        a3 = addiu(s2, 24);
        sb(v1, s2, 7);
        a2 = sp;
        lw(t1, v0, 0);
        lbu(v1, v0, 0);
        v0 = sra(t1, 8);
        t1 = srl(t1, 24);
        t0 = v0;
        v0 = v0 & 0xFF;
        v0 = sll(v0, 16);
        v1 = sll(v1, 24);
        t0 = t0 & 0xFF00;
        v1 = v1 | t1;
        t0 = t0 | v0;
        sw(zero, sp, 0x0);
        v1 = v1 | t0;
        t2 = addiu(v1, 16);
        v1 = addiu(v1, 2063);
        t0 = slti(t2, 0);
        v0 = t2;
        if (t0 != 0) v0 = v1;
        s1 = sra(v0, 11);
        s0 = s1;
        sw(s0, s2, 20);
        v0 = sll(s0, 11);
        s1 = subu(t2, v0);
        jal(ctx, 0x56B848u, gen::fn_sub_56B3C0_0056b3c0);
        v1 = 0x9A0000;
        v0 = 0x9A0000;
        sw(s0, v1, -19920);  // 0x99B230
        sw(s1, v0, -19916);  // 0x99B234
        v0 = addiu(s3, 32);
        a3 = addiu(s2, 36);
        a0 = 0;
        lw(t1, v0, 0);
        a1 = 0;
        lbu(v1, v0, 0);
        a2 = sp;
        v0 = sra(t1, 8);
        t1 = srl(t1, 24);
        t0 = v0;
        v0 = v0 & 0xFF;
        v0 = sll(v0, 16);
        v1 = sll(v1, 24);
        t0 = t0 & 0xFF00;
        v1 = v1 | t1;
        t0 = t0 | v0;
        sw(zero, sp, 0x0);
        v1 = v1 | t0;
        t2 = 0x50000;
        t2 = t2 | 0x6230;
        t2 = addu(t2, v1);
        at = 0x50000;
        at = at | 0x6A2F;
        v1 = addu(at, v1);
        t0 = slti(t2, 0);
        v0 = t2;
        if (t0 != 0) v0 = v1;
        s1 = sra(v0, 11);
        s0 = s1;
        sw(s0, s2, 32);
        v0 = sll(s0, 11);
        s1 = subu(t2, v0);
        jal(ctx, 0x56B8DCu, gen::fn_sub_56B3C0_0056b3c0);
        v1 = 0x9A0000;
        v0 = 0x9A0000;
        sw(s0, v1, -19912);  // 0x99B238
        sw(s1, v0, -19908);  // 0x99B23C
        v0 = s4;
        ld(s0, sp, 0x10);
    } else {
        // 0x0056b754
        charge(ctx, 3);
        v0 = sltiu(v1, 3);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 4;
        if (cc) {
            // 0x0056b778
            charge(ctx, 2);
            cc = a0 == v0;  // the condition, before the delay slot changes it
            v0 = si(-4);
            if (cc) {
                // 0x0056b7a8
                charge(ctx, 2);
                a2 = 2;
                s4 = si(-3);
                goto L_0056b7b0;
            }
            // 0x0056b780
            charge(ctx, 2);
            ld(s0, sp, 0x10);
        } else {
            // 0x0056b760
            charge(ctx, 3);
            v0 = 1;
            cc = v1 == v0;  // the condition, before the delay slot changes it
            v0 = si(-4);
            if (cc) {
                // 0x0056b788
                charge(ctx, 3);
                a2 = 0;
                s4 = 0;
                goto L_0056b7b0;
            }
            // 0x0056b76c
            charge(ctx, 2);
            ld(s0, sp, 0x10);
        }
    }
    // 0x0056b8fc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x0056B918 sub_56B918 -- 104 bytes; leaf frame (no stack)
// Byte offset of sector n in a 'CIMF' image: 2048-byte sectors before the second location, 2352-byte ones from it on
//   (the statics of sub_56B6E0). [cvmh_CimfSctToOfs]
void sub_56B918(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0056b918
    enter(ctx, 7);  // entry check point + this block's cycles
    v1 = 0x9A0000;
    lw(v0, v1, -19912);  // 0x99B238
    a1 = subu(a0, v0);
    a2 = sll(v0, 11);
    v0 = slt(a0, v0);
    if (v0 == 0) {
        // 0x0056b934
        charge(ctx, 5);
        v1 = 2352;
        a0 = 0x9A0000;
        mult(v1, a1, v1);
        lw(v0, a0, -19908);  // 0x99B23C
        // 0x0056b96c (the shared epilogue, written out on this path)
        charge(ctx, 3);
        v0 = addu(a2, v0);
        v0 = addu(v0, v1);
        return;
    }
    v1 = 0x9A0000;
    // 0x0056b948
    charge(ctx, 6);
    lw(v0, v1, -19920);
    a1 = subu(a0, v0);
    a2 = sll(v0, 11);
    v0 = slt(a0, v0);
    v1 = 2352;
    if (v0 != 0) {
        // 0x0056b978
        charge(ctx, 2);
        v0 = sll(a0, 11);
        return;
    }
    // 0x0056b960
    charge(ctx, 3);
    a0 = 0x9A0000;
    mult(v1, a1, v1);
    lw(v0, a0, -19916);  // 0x99B234
    // 0x0056b96c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = addu(a2, v0);
    v0 = addu(v0, v1);
}

// 0x0056C878 sub_56C878 -- 12 bytes; leaf frame (no stack)
// ROCI's version text. [roci_GetVersion]
void sub_56C878(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0056c878
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7C0000;
    v0 = addiu(v0, 30568);  // "\nROCI Ver.1.15 Build:Mar  2 2005 11:31:01\n"
}

// 0x0056C888 ROCI_GetInterface -- 48 bytes; frame 0x10: ra sp+0x0
// ROCI interface: the version text noted (0x99B240), the method table 0x7B2810. [ROCI_GetInterface]
void ROCI_GetInterface(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056c888
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x56C890u, gen::fn_sub_56C878_0056c878);
    v1 = 0x9A0000;
    ld(ra, sp, 0x0);
    v1 = addiu(v1, -19904);  // &0x99B240
    a0 = 0x7B0000;
    sw(v0, v1, 0);  // 0x99B240
    v0 = addiu(a0, 10256);  // &g_roci_vtbl
    sp = addiu(sp, 0x10);
}

// 0x0056C8E0 sub_56C8E0 -- 8 bytes; leaf frame (no stack)
// ROCI method: nothing. [roci_Nop]
void sub_56C8E0(EEContext& ctx) {
    using namespace hg;
    // 0x0056c8e0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0056CA08 sub_56CA08 -- 20 bytes; frame 0x10: ra sp+0x0
// ROCI method: the sector size (2048). [roci_GetSctLen]
void sub_56CA08(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0056ca08
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5669B8_005669b8(ctx);  // tail call
}

// 0x0056CA78 sub_56CA78 -- 8 bytes; leaf frame (no stack)
// ROCI method: 0. [roci_Zero]
void sub_56CA78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0056ca78
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0056DD50 atan2l_9 -- 20 bytes; frame 0x10: ra sp+0x0
// ROFS's lock: the SVM lock, type 1. [rofs_Lock]
void atan2l_9(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0056dd50
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564978_00564978(ctx);  // tail call
}

// 0x0056DD68 cosl_9 -- 20 bytes; frame 0x10: ra sp+0x0
// ROFS's unlock: the SVM unlock, type 1. [rofs_Unlock]
void cosl_9(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0056dd68
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564990_00564990(ctx);  // tail call
}

// 0x0056DD80 coshl_9 -- 72 bytes; frame 0x10: ra sp+0x8, s0 sp+0x0
// ROFS's PFS lock: spin while the lock word (__errno_4, 0x5584F0) reads 1, then the SVM lock; returns whether the
//   word is no longer 1. [rofs_PfsLock]
void coshl_9(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056dd80
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x8);
    sd(s0, sp, 0x0);
    s0 = 1;
    for (;;) {
        // 0x0056dd90
        charge(ctx, 4);
        jal(ctx, 0x56DD90u, gen::fn___errno_4_005584f0);
        if (v0 != s0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0056dda0
    charge(ctx, 10);
    jal(ctx, 0x56DDA0u, gen::fn_sub_564978_00564978);
    jal(ctx, 0x56DDA8u, gen::fn___errno_4_005584f0);
    v0 = v0 ^ 0x1;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    v0 = sltu(0, v0);
    sp = addiu(sp, 0x10);
}

// 0x0056DDC8 sub_56DDC8 -- 20 bytes; frame 0x10: ra sp+0x0
// ROFS's PFS unlock: the SVM unlock, type 1. [rofs_PfsUnlock]
void sub_56DDC8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0056ddc8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564990_00564990(ctx);  // tail call
}

// 0x0056DDF8 sub_56DDF8 -- 44 bytes; leaf frame (no stack)
// Busy wait: 7,551 empty iterations (count 1..0x1D80); returns 0. [rofs_Wait]
void sub_56DDF8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x0056ddf8
    enter(ctx, 2);  // entry check point + this block's cycles
    v1 = 0;
    v1 = addiu(v1, 1);
    for (;;) {
        // 0x0056de00
        charge(ctx, 7);
        v0 = sltiu(v1, 7552);
        if (v0 == 0) {
            break;
        }
        v1 = addiu(v1, 1);
        backedge(ctx);
    }
    // 0x0056de1c
    charge(ctx, 2);
}

}  // namespace p3fes::game
