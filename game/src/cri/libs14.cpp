// Phase 5 slice libs14: CRI middleware below the game's file and sound layers -- PS2RNA (the IOP sound output:
// handle table, IOP calls, the per-handle server step), the SJX / DTX IOP glue, the PFS-on-CVFS bridge, ROFS (the
// read-only file system over the CVM image: the interface wrappers, handle read / stop / close, the work-area
// setup, the status poll and the read watchdog, the dcf / pfs dispatch to the image) and a set of small Sofdec / SFX
// helpers (handle state, parameters, frame descriptors, the SFXINFE table).
// p3fes_handgen bodies (game/include/p3fes/game/hg_cpu.h); every statement, charge and check point is the
// generator's. The roles come from reading the instructions; the RofsHandle offsets are libs14::rofs_hn constants
// in game/include/p3fes/game/libs14.h (each equals the literal it replaces). Names are symbols/ names (ADR-0009).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs14.h"

namespace p3fes::recomp_gen {
void fn_DTR_ExecServer_00559140(p3fes::EEContext&);
void fn_DTR_Stop_005593a8(p3fes::EEContext&);
void fn_DTX_CallUrpc_00559c10(p3fes::EEContext&);
void fn_DTX_Init_00559aa8(p3fes::EEContext&);
void fn_PFSCVFS_GetPfsTbl_005658a8(p3fes::EEContext&);
void fn_PS2RNA_Create_00560758(p3fes::EEContext&);
void fn_PS2RNA_ExecServer_00561138(p3fes::EEContext&);
void fn_PS2RNA_InitIopSnd_00560298(p3fes::EEContext&);
void fn_RFHN_GetStatG_00565fe8(p3fes::EEContext&);
void fn_RFHN_IsUseImgHn_00565b18(p3fes::EEContext&);
void fn_RFHN_ReopenHn_00565a78(p3fes::EEContext&);
void fn_RFHN_ReqRdG_00565e10(p3fes::EEContext&);
void fn_RFHN_StopTrG_00566180(p3fes::EEContext&);
void fn_RFHN_WaitCompleteReq_005658b8(p3fes::EEContext&);
void fn_RFIF_InitOvl_005662f0(p3fes::EEContext&);
void fn_RFMAI_InitG_00567858(p3fes::EEContext&);
void fn_RFMAI_ReadWG_00569538(p3fes::EEContext&);
void fn_RFPFS_PfsWait_0056ab78(p3fes::EEContext&);
void fn_RFPFS_SetPfsTbl_0056ad28(p3fes::EEContext&);
void fn_ROFS_AddVolume_005663d8(p3fes::EEContext&);
void fn_ROFS_Close_005666e0(p3fes::EEContext&);
void fn_ROFS_ExecServer_00566778(p3fes::EEContext&);
void fn_ROFS_GetFileSiz_005667d0(p3fes::EEContext&);
void fn_ROFS_GetStat_005667a8(p3fes::EEContext&);
void fn_ROFS_GetVolumeInf_005669d8(p3fes::EEContext&);
void fn_ROFS_Init_00567820(p3fes::EEContext&);
void fn_ROFS_Open_005665d0(p3fes::EEContext&);
void fn_ROFS_ReqRd_00566708(p3fes::EEContext&);
void fn_ROFS_SetDir_00566b08(p3fes::EEContext&);
void fn_RSU_Init_0056d6e8(p3fes::EEContext&);
void fn_SRD_ExecServer_00558500(p3fes::EEContext&);
void fn_WTLS_get_table_2_0059fd60(p3fes::EEContext&);
void fn___divdi3_0052eeb0(p3fes::EEContext&);
void fn___floatdisf_0052eb60(p3fes::EEContext&);
void fn___muldi3_0052ea78(p3fes::EEContext&);
void fn_coshl_8_00565850(p3fes::EEContext&);
void fn_cvFsExecServer_00556608(p3fes::EEContext&);
void fn_cvFsGetStat_00556668(p3fes::EEContext&);
void fn_cvFsReqRd_005564e0(p3fes::EEContext&);
void fn_cvFsSeek_00556478(p3fes::EEContext&);
void fn_dcfExecServer_0056a698(p3fes::EEContext&);
void fn_dcfGetNumTr_0056a790(p3fes::EEContext&);
void fn_dcfGetSctLen_0056a730(p3fes::EEContext&);
void fn_dcfGetStat_0056a6d0(p3fes::EEContext&);
void fn_dcfInit_0056a530(p3fes::EEContext&);
void fn_dcfReqRdBlk_0056a860(p3fes::EEContext&);
void fn_dcfReqRdCda_0056aa98(p3fes::EEContext&);
void fn_dcfReqRd_0056a600(p3fes::EEContext&);
void fn_dcfSeek_0056a540(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_pfsCvfsExecServer_00565888(p3fes::EEContext&);
void fn_pfsCvfsGetNumTr_00565838(p3fes::EEContext&);
void fn_pfsCvfsGetSctLen_00565820(p3fes::EEContext&);
void fn_pfsCvfsGetStat_005657d0(p3fes::EEContext&);
void fn_pfsCvfsReqRd_005657a0(p3fes::EEContext&);
void fn_pfsCvfsSeek_00565730(p3fes::EEContext&);
void fn_rfmai_isDvdRomAccess_00567478(p3fes::EEContext&);
void fn_rfmai_updateHnStat_00568710(p3fes::EEContext&);
void fn_rfpfs_parentSeek_0056acb8(p3fes::EEContext&);
void fn_rfpfs_waitRdComplete_0056ac28(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_11_00567810(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_12_0056ad38(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_13_0056c8b8(p3fes::EEContext&);
void fn_sscanf_00523b40(p3fes::EEContext&);
void fn_strncmp_00524670(p3fes::EEContext&);
void fn_sub_539848_00539848(p3fes::EEContext&);
void fn_sub_539850_00539850(p3fes::EEContext&);
void fn_sub_53AE08_0053ae08(p3fes::EEContext&);
void fn_sub_53ED00_0053ed00(p3fes::EEContext&);
void fn_sub_53F268_0053f268(p3fes::EEContext&);
void fn_sub_53F298_0053f298(p3fes::EEContext&);
void fn_sub_53F2D8_0053f2d8(p3fes::EEContext&);
void fn_sub_5416E8_005416e8(p3fes::EEContext&);
void fn_sub_541760_00541760(p3fes::EEContext&);
void fn_sub_545158_00545158(p3fes::EEContext&);
void fn_sub_5451B0_005451b0(p3fes::EEContext&);
void fn_sub_545208_00545208(p3fes::EEContext&);
void fn_sub_5453D8_005453d8(p3fes::EEContext&);
void fn_sub_545448_00545448(p3fes::EEContext&);
void fn_sub_545570_00545570(p3fes::EEContext&);
void fn_sub_545838_00545838(p3fes::EEContext&);
void fn_sub_545B90_00545b90(p3fes::EEContext&);
void fn_sub_555898_00555898(p3fes::EEContext&);
void fn_sub_556A00_00556a00(p3fes::EEContext&);
void fn_sub_556AC0_00556ac0(p3fes::EEContext&);
void fn_sub_5577B8_005577b8(p3fes::EEContext&);
void fn_sub_559138_00559138(p3fes::EEContext&);
void fn_sub_559280_00559280(p3fes::EEContext&);
void fn_sub_559370_00559370(p3fes::EEContext&);
void fn_sub_559398_00559398(p3fes::EEContext&);
void fn_sub_559D18_00559d18(p3fes::EEContext&);
void fn_sub_55DB58_0055db58(p3fes::EEContext&);
void fn_sub_55FB20_0055fb20(p3fes::EEContext&);
void fn_sub_55FB98_0055fb98(p3fes::EEContext&);
void fn_sub_560AF8_00560af8(p3fes::EEContext&);
void fn_sub_560C88_00560c88(p3fes::EEContext&);
void fn_sub_560D20_00560d20(p3fes::EEContext&);
void fn_sub_560EB0_00560eb0(p3fes::EEContext&);
void fn_sub_560F18_00560f18(p3fes::EEContext&);
void fn_sub_560F78_00560f78(p3fes::EEContext&);
void fn_sub_561258_00561258(p3fes::EEContext&);
void fn_sub_561390_00561390(p3fes::EEContext&);
void fn_sub_561728_00561728(p3fes::EEContext&);
void fn_sub_561740_00561740(p3fes::EEContext&);
void fn_sub_5617C0_005617c0(p3fes::EEContext&);
void fn_sub_5617D8_005617d8(p3fes::EEContext&);
void fn_sub_561970_00561970(p3fes::EEContext&);
void fn_sub_562388_00562388(p3fes::EEContext&);
void fn_sub_563D20_00563d20(p3fes::EEContext&);
void fn_sub_563E30_00563e30(p3fes::EEContext&);
void fn_sub_563E68_00563e68(p3fes::EEContext&);
void fn_sub_563FE0_00563fe0(p3fes::EEContext&);
void fn_sub_564218_00564218(p3fes::EEContext&);
void fn_sub_5642D0_005642d0(p3fes::EEContext&);
void fn_sub_564360_00564360(p3fes::EEContext&);
void fn_sub_564400_00564400(p3fes::EEContext&);
void fn_sub_564510_00564510(p3fes::EEContext&);
void fn_sub_564738_00564738(p3fes::EEContext&);
void fn_sub_565BC0_00565bc0(p3fes::EEContext&);
void fn_sub_5662C8_005662c8(p3fes::EEContext&);
void fn_sub_5664F8_005664f8(p3fes::EEContext&);
void fn_sub_567AF0_00567af0(p3fes::EEContext&);
void fn_sub_567BE0_00567be0(p3fes::EEContext&);
void fn_sub_568A78_00568a78(p3fes::EEContext&);
void fn_sub_568AC0_00568ac0(p3fes::EEContext&);
void fn_sub_568B80_00568b80(p3fes::EEContext&);
void fn_sub_568BC8_00568bc8(p3fes::EEContext&);
void fn_sub_569700_00569700(p3fes::EEContext&);
void fn_sub_569718_00569718(p3fes::EEContext&);
void fn_sub_569730_00569730(p3fes::EEContext&);
void fn_sub_569810_00569810(p3fes::EEContext&);
void fn_sub_569F60_00569f60(p3fes::EEContext&);
void fn_sub_56A040_0056a040(p3fes::EEContext&);
void fn_sub_56A7F0_0056a7f0(p3fes::EEContext&);
void fn_sub_56DDE0_0056dde0(p3fes::EEContext&);
void fn_sub_570248_00570248(p3fes::EEContext&);
void fn_sub_5703B8_005703b8(p3fes::EEContext&);
void fn_sub_57BAF0_0057baf0(p3fes::EEContext&);
void fn_sub_588360_00588360(p3fes::EEContext&);
void fn_sub_58BE40_0058be40(p3fes::EEContext&);
void fn_sub_58C060_0058c060(p3fes::EEContext&);
void fn_sub_58C100_0058c100(p3fes::EEContext&);
void fn_sub_58C118_0058c118(p3fes::EEContext&);
void fn_sub_593140_00593140(p3fes::EEContext&);
void fn_sub_593200_00593200(p3fes::EEContext&);
void fn_sub_593408_00593408(p3fes::EEContext&);
void fn_sub_593468_00593468(p3fes::EEContext&);
void fn_sub_593B38_00593b38(p3fes::EEContext&);
void fn_sub_593FD0_00593fd0(p3fes::EEContext&);
void fn_sub_595868_00595868(p3fes::EEContext&);
void fn_sub_5958F8_005958f8(p3fes::EEContext&);
void fn_sub_5959E0_005959e0(p3fes::EEContext&);
void fn_sub_596760_00596760(p3fes::EEContext&);
void fn_sub_596B68_00596b68(p3fes::EEContext&);
void fn_sub_597878_00597878(p3fes::EEContext&);
void fn_sub_5978E8_005978e8(p3fes::EEContext&);
void fn_sub_597A18_00597a18(p3fes::EEContext&);
void fn_sub_5985F8_005985f8(p3fes::EEContext&);
void fn_sub_598980_00598980(p3fes::EEContext&);
void fn_sub_599020_00599020(p3fes::EEContext&);
void fn_sub_599240_00599240(p3fes::EEContext&);
void fn_sub_599408_00599408(p3fes::EEContext&);
void fn_sub_59A298_0059a298(p3fes::EEContext&);
void fn_sub_59A458_0059a458(p3fes::EEContext&);
void fn_sub_59A600_0059a600(p3fes::EEContext&);
void fn_sub_59AD40_0059ad40(p3fes::EEContext&);
void fn_sub_59AE88_0059ae88(p3fes::EEContext&);
void fn_sub_59B398_0059b398(p3fes::EEContext&);
void fn_sub_59B3A8_0059b3a8(p3fes::EEContext&);
void fn_sub_59B458_0059b458(p3fes::EEContext&);
void fn_sub_59BC20_0059bc20(p3fes::EEContext&);
void fn_sub_59EA18_0059ea18(p3fes::EEContext&);
void fn_sub_59EA80_0059ea80(p3fes::EEContext&);
void fn_sub_59EC08_0059ec08(p3fes::EEContext&);
void fn_sub_59ED78_0059ed78(p3fes::EEContext&);
void fn_sub_59EE18_0059ee18(p3fes::EEContext&);
void fn_sub_59EE38_0059ee38(p3fes::EEContext&);
void fn_sub_59EF08_0059ef08(p3fes::EEContext&);
void fn_sub_59EF28_0059ef28(p3fes::EEContext&);
void fn_sub_59EF48_0059ef48(p3fes::EEContext&);
void fn_sub_59EF68_0059ef68(p3fes::EEContext&);
void fn_sub_59F320_0059f320(p3fes::EEContext&);
void fn_sub_59F3D8_0059f3d8(p3fes::EEContext&);
void fn_sub_59F8F8_0059f8f8(p3fes::EEContext&);
void fn_sub_59F968_0059f968(p3fes::EEContext&);
void fn_sub_59FD10_0059fd10(p3fes::EEContext&);
void fn_sub_59FE50_0059fe50(p3fes::EEContext&);
void fn_sub_59FFC8_0059ffc8(p3fes::EEContext&);
void fn_sub_5A0048_005a0048(p3fes::EEContext&);
void fn_sub_5A04F0_005a04f0(p3fes::EEContext&);
void fn_sub_5A0608_005a0608(p3fes::EEContext&);
void fn_sub_5A07E0_005a07e0(p3fes::EEContext&);
void fn_sub_5A0BB0_005a0bb0(p3fes::EEContext&);
void fn_sub_5A10E8_005a10e8(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x0053ED00 sub_53ED00 -- 508 bytes; frame 0x70: s0 sp+0x30, s1 sp+0x38, s2 sp+0x40, s3 sp+0x48, s4 sp+0x50, s5 sp+0x58, ra sp+0x60
// CRI ADX side, one-shot convert through stream joints (SJ): creates a 1024-byte SJ on 0x7881F0 (sub_562388) and
//   two 32-byte SJs on 0x7885F0 / 0x788610 (sub_561970), a converter on them (sub_545208), feeds it a1..a3
//   (sub_545838 / sub_545448 / sub_545B90), then moves the produced chunk to the output SJ at a0+20: get chunk
//   (vtable +24) from both, memcpy, put chunk (vtable +32) back -- an empty chunk or a short output spins forever, as
//   the original does -- and destroys everything (sub_545570, sub_5453D8, vtable +12, sub_5451B0).
void sub_53ED00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053ed00
    enter(ctx, 55);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s0, sp, 0x30);
    s0 = 0x790000;
    sd(s1, sp, 0x38);
    s1 = a0;
    sd(s2, sp, 0x40);
    s2 = a1;
    sd(s3, sp, 0x48);
    s3 = a2;
    sd(s4, sp, 0x50);
    s4 = a3;
    sd(s5, sp, 0x58);
    sd(ra, sp, 0x60);
    s0 = addiu(s0, -31248);  // &0x7885F0
    jal(ctx, 0x53ED34u, gen::fn_sub_545158_00545158);
    a0 = 0x790000;
    a2 = 0;
    a0 = addiu(a0, -32272);  // &0x7881F0
    a1 = 1024;
    jal(ctx, 0x53ED48u, gen::fn_sub_562388_00562388);
    a1 = 32;
    a0 = s0;
    s5 = v0;
    jal(ctx, 0x53ED58u, gen::fn_sub_561970_00561970);
    a0 = addiu(s0, 32);  // &0x788610
    a1 = 32;
    link(ctx, 0x53ED68u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x0);
    call(ctx, gen::fn_sub_561970_00561970);
    lw(s0, s1, 20);
    a1 = sp;
    a0 = 2;
    a2 = s5;
    link(ctx, 0x53ED80u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x4);
    call(ctx, gen::fn_sub_545208_00545208);
    a1 = s2;
    s1 = v0;
    a2 = s3;
    a3 = s4;
    a0 = s1;
    jal(ctx, 0x53ED98u, gen::fn_sub_545838_00545838);
    a0 = s1;
    jal(ctx, 0x53EDA0u, gen::fn_sub_545448_00545448);
    jal(ctx, 0x53EDA8u, gen::fn_sub_545B90_00545b90);
    lw(v1, s5, 0);
    s3 = addiu(sp, 0x10);
    a2 = 1024;
    a0 = s5;
    lw(v0, v1, 24);
    a1 = 1;
    a3 = s3;
    jalr(ctx, 0x53EDC8u, v0.u());
    lw(a2, sp, 0x14);
    if (a2 == 0) {
        // 0x0053eddc
        charge(ctx, 1);
        for (;;) {
            // 0x0053ede0
            charge(ctx, 7);
            backedge(ctx);
        }
    }
    lw(v0, s0, 0);
    // 0x0053ee00
    charge(ctx, 11);
    s2 = addiu(sp, 0x20);
    a0 = s0;
    a1 = 0;
    lw(v1, v0, 24);
    a3 = s2;
    jalr(ctx, 0x53EE10u, v1.u());
    lw(v0, sp, 0x24);
    lw(a2, sp, 0x14);
    v0 = slt(v0, a2);
    lw(a0, sp, 0x20);
    if (v0 != 0) {
        // 0x0053ee2c
        charge(ctx, 1);
        for (;;) {
            // 0x0053ee30
            charge(ctx, 7);
            backedge(ctx);
        }
    }
    // 0x0053ee50
    charge(ctx, 43);
    link(ctx, 0x53EE50u);  // $ra first: the delay slot below depends on it
    lw(a1, sp, 0x10);
    call(ctx, gen::fn_memcpy_00521250);
    lw(v1, s5, 0);
    a2 = s3;
    a0 = s5;
    lw(v0, v1, 32);
    a1 = 0;
    jalr(ctx, 0x53EE68u, v0.u());
    lw(v1, s0, 0);
    a2 = s2;
    a1 = 1;
    lw(v0, v1, 32);
    a0 = s0;
    jalr(ctx, 0x53EE80u, v0.u());
    a0 = s1;
    jal(ctx, 0x53EE88u, gen::fn_sub_545570_00545570);
    a0 = s1;
    jal(ctx, 0x53EE90u, gen::fn_sub_5453D8_005453d8);
    lw(v1, s5, 0);
    lw(v0, v1, 12);
    a0 = s5;
    jalr(ctx, 0x53EEA0u, v0.u());
    lw(a0, sp, 0x4);
    lw(v1, a0, 0);
    lw(v0, v1, 12);
    jalr(ctx, 0x53EEB4u, v0.u());
    lw(a0, sp, 0x0);
    lw(v1, a0, 0);
    lw(v0, v1, 12);
    jalr(ctx, 0x53EEC8u, v0.u());
    jal(ctx, 0x53EED0u, gen::fn_sub_5451B0_005451b0);
    ld(s0, sp, 0x30);
    ld(s1, sp, 0x38);
    ld(s2, sp, 0x40);
    ld(s3, sp, 0x48);
    ld(s4, sp, 0x50);
    ld(s5, sp, 0x58);
    ld(ra, sp, 0x60);
    sp = addiu(sp, 0x70);
}

// 0x0053F268 sub_53F268 -- 48 bytes; frame 0x10: ra sp+0x0
// A null handle reports "E02080851 ...: parameter error" through sub_53AE08; otherwise sub_55DB58(handle+148).
void sub_53F268(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f268
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0053f288
        charge(ctx, 4);
        lw(a0, a0, 148);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        gen::fn_sub_55DB58_0055db58(ctx);  // tail call
        return;
    }
    // 0x0053f274
    charge(ctx, 5);
    a0 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 9160);  // "E02080851 adxt_SetSeamlessLp: parameter error"
    sp = addiu(sp, 0x10);
    gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
}

// 0x0053F298 sub_53F298 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// sub_53F2D8(a0, a1) between sub_539848 / sub_539850 (the enter / leave pair around it).
void sub_53F298(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053f298
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x53F2ACu, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x53F2B8u, gen::fn_sub_53F2D8_0053f2d8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x00560298 PS2RNA_InitIopSnd -- 220 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// PS2RNA, IOP sound setup (skipped while the IOP flag 0x7A93F8 == 1 and the count 0x7A93F0 <= 0): the
//   BASE_SFREQ option (sub_555898; 48000 when absent) goes to the IOP (DTX_CallUrpc 12); the reply is kept in 0x7A9438
//   and selects the channel-mode words 0x7A9430[] / 0x7A9434; 0x7A9424 / 0x7A9428 are cleared.
void PS2RNA_InitIopSnd(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00560298
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x20);
    lw(v1, v0, -27656);  // 0x7A93F8
    a0 = 1;
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x18);
    if (v1 == a0) {
        // 0x005602b4
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        ld(s0, sp, 0x10);
        if (i64(v1) > 0) {
            goto L_005602c4;
        }
        // 0x00560368 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_005602c4:
    charge(ctx, 12);
    a0 = 0x7C0000;
    a1 = sp;
    a0 = addiu(a0, 25960);  // "BASE_SFREQ"
    jal(ctx, 0x5602CCu, gen::fn_sub_555898_00555898);
    v1 = 0x7B0000;
    a0 = 12;
    a1 = addiu(sp, 0x4);
    a2 = 1;
    a3 = addiu(sp, 0x8);
    t0 = 1;
    s0 = addiu(v1, -27592);  // &0x7A9438
    if (v0 != 0) {
        // 0x00560300
        charge(ctx, 1);
        v0 = 0xBB80;
    } else {
        // 0x005602f4
        charge(ctx, 2);
        lw(v0, sp, 0x0);
    }
    // 0x00560304
    charge(ctx, 18);
    link(ctx, 0x560304u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x4);
    call(ctx, gen::fn_DTX_CallUrpc_00559c10);
    a0 = 0x7B0000;
    v1 = 4;
    a0 = addiu(a0, -27600);  // &0x7A9430
    if (v0 != 0) v1 = 0;
    a1 = sll(v0, 2);
    t1 = addu(v1, a0);
    v1 = 0x7B0000;
    a2 = addu(a1, a0);
    a1 = 2;
    t0 = a0;
    a0 = 0x7B0000;
    a3 = 1;
    sw(v0, s0, 0);
    sw(zero, v1, -27612);  // 0x7A9424
    sw(zero, a0, -27608);  // 0x7A9428
    if (v0 != a1) {
        // 0x00560358
        charge(ctx, 3);
        v0 = 1;
        sw(v0, a2, 0);
        sw(zero, t1, 0);
    } else {
        // 0x0056034c
        charge(ctx, 3);
        sw(a3, t0, 4);
        sw(a3, t0, 0);
    }
    // 0x00560364
    charge(ctx, 1);
    ld(s0, sp, 0x10);
    // 0x00560368 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00560758 PS2RNA_Create -- 928 bytes; frame 0x60: s1 sp+0x28, s2 sp+0x30, s3 sp+0x38, s6 sp+0x50, s0 sp+0x20, s4 sp+0x40, s5 sp+0x48, ra sp+0x58
// PS2RNA handle creation: takes the first free slot of the 16 x 100-byte table at 0x7AB850 (byte +0 = used).
//   Without IOP sound it only marks the slot. Otherwise: clears it, one PSJ per channel (sub_55FB20; failure:
//   "E1072601", freeing the made ones with sub_55FB98), the IOP-side object (DTX_CallUrpc 8; failure "E0100401"),
//   one DTR per channel (sub_559280; failure "E1072602", unwinding with sub_559370 / DTX_CallUrpc 9 / sub_55FB98),
//   then the input SJs at +24.., the state bytes +80..+91, the counters +56.. / +64.., +40 = the first SJ's data +
//   free count (vtable +36 lines 1 and 0), +44 = 0x4000, and marks the slot used.
void PS2RNA_Create(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00560758
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 0x7B0000;
    sd(s1, sp, 0x28);
    s1 = 0;
    sd(s2, sp, 0x30);
    s2 = a1;
    sd(s3, sp, 0x38);
    s3 = addiu(v0, -18352);  // &0x7AB850
    sd(s6, sp, 0x50);
    sd(s0, sp, 0x20);
    sd(s4, sp, 0x40);
    sd(s5, sp, 0x48);
    sd(ra, sp, 0x58);
    lb(v0, s3, 0);  // 0x7AB850
    s6 = a0;
    if (v0 != 0) {
        // 0x00560798
        charge(ctx, 2);
        a0 = s3;
        v1 = s3;
        for (;;) {
            // 0x005607a0
            charge(ctx, 5);
            s1 = addiu(s1, 1);
            a0 = addiu(a0, 100);
            v0 = slti(s1, 16);
            v1 = addiu(v1, 100);
            if (v0 != 0) {
                // 0x005607b4
                charge(ctx, 4);
                lb(v0, a0, 0);
                s3 = v1;
                if (v0 != 0) {
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x005607c4
    charge(ctx, 3);
    v1 = 16;
    v0 = 0;
    if (s1 != v1) {
        // 0x005607d0
        charge(ctx, 5);
        v0 = 0x7B0000;
        v1 = 1;
        lw(a0, v0, -27656);  // 0x7A93F8
        if (a0 != v1) {
            a0 = s3;
        } else {
            // 0x005607e4
            charge(ctx, 4);
            v0 = 0x7B0000;
            lw(v1, v0, -27664);  // 0x7A93F0
            if (i64(v1) > 0) {
                a0 = s3;
                goto L_00560800;
            }
            // 0x005607f4
            charge(ctx, 3);
            sb(a0, s3, 0);
            v0 = s3;
            // 0x00560ad0 (the shared epilogue, written out on this path)
            charge(ctx, 10);
            ld(s0, sp, 0x20);
            ld(s1, sp, 0x28);
            ld(s2, sp, 0x30);
            ld(s3, sp, 0x38);
            ld(s4, sp, 0x40);
            ld(s5, sp, 0x48);
            ld(s6, sp, 0x50);
            ld(ra, sp, 0x58);
            sp = addiu(sp, 0x60);
            return;
        }
    L_00560800:
        charge(ctx, 6);
        a1 = 0;
        a2 = 100;
        s1 = 0;
        jal(ctx, 0x560808u, gen::fn_memset_00521408);
        sw(s2, s3, 4);
        if (i64(s2) > 0) {
            // 0x00560818
            charge(ctx, 4);
            s4 = addiu(s3, 8);
            s5 = 0x7C0000;
            s0 = s4;
            for (;;) {
                // 0x00560828
                charge(ctx, 5);
                jal(ctx, 0x560828u, gen::fn_sub_55FB20_0055fb20);
                sw(v0, s0, 0);
                s0 = addiu(s0, 4);
                if (v0 == 0) {
                    goto L_0056083c_11;
                }
                // 0x00560880
                charge(ctx, 4);
                s1 = addiu(s1, 1);
                v0 = slt(s1, s2);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00560890
        charge(ctx, 4);
        sw(s2, sp, 0x0);
        s1 = 0;
        sw(zero, sp, 0x4);
        if (i64(s2) > 0) {
            // 0x005608a0
            charge(ctx, 2);
            a2 = addiu(sp, 0x8);
            a1 = addiu(s3, 8);
            for (;;) {
                // 0x005608a8
                charge(ctx, 8);
                lw(v0, a1, 0);
                a1 = addiu(a1, 4);
                s1 = addiu(s1, 1);
                lw(v1, v0, 4);
                a0 = slt(s1, s2);
                sw(v1, a2, 0);
                a2 = addiu(a2, 4);
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x005608c8
        charge(ctx, 8);
        a0 = 8;
        a1 = sp;
        a2 = 4;
        a3 = addiu(sp, 0x10);
        t0 = 1;
        jal(ctx, 0x5608D8u, gen::fn_DTX_CallUrpc_00559c10);
        sw(v0, s3, 32);
        if (v0 != 0) {
            // 0x00560900
            charge(ctx, 2);
            s1 = 0;
            if (i64(s2) > 0) {
                // 0x00560908
                charge(ctx, 4);
                s4 = addiu(s3, 8);
                s5 = 0x7C0000;
                s0 = addiu(s3, 16);
                v0 = sll(s1, 2);
                for (;;) {
                    // 0x00560918
                    charge(ctx, 11);
                    s1 = addiu(s1, 1);
                    v1 = addu(s4, v0);
                    v0 = addu(v0, s6);
                    lw(a2, v1, 0);
                    lw(a0, v0, 0);
                    link(ctx, 0x56092Cu);  // $ra first: the delay slot below depends on it
                    lw(a1, a2, 8);
                    call(ctx, gen::fn_sub_559280_00559280);
                    v1 = slt(s1, s2);
                    sw(v0, s0, 0);
                    s0 = addiu(s0, 4);
                    if (v0 == 0) {
                        goto L_00560944_26;
                    }
                    // 0x005609d0
                    charge(ctx, 2);
                    v0 = sll(s1, 2);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x005609d8
            charge(ctx, 2);
            s1 = 0;
            if (i64(s2) > 0) {
                // 0x005609e0
                charge(ctx, 2);
                a1 = addiu(s3, 24);
                a0 = s6;
                for (;;) {
                    // 0x005609e8
                    charge(ctx, 7);
                    lw(v1, a0, 0);
                    a0 = addiu(a0, 4);
                    s1 = addiu(s1, 1);
                    v0 = slt(s1, s2);
                    sw(v1, a1, 0);
                    a1 = addiu(a1, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00560a04
            charge(ctx, 17);
            sb(zero, s3, 80);
            v0 = 0x7B0000;
            sb(zero, s3, 81);
            v0 = addiu(v0, -27592);  // &0x7A9438
            sb(s2, s3, 82);
            sb(s2, s3, 83);
            sb(zero, s3, 84);
            sb(zero, s3, 85);
            sw(zero, s3, 56);
            lbu(v1, v0, 0);  // 0x7A9438
            sw(zero, s3, 60);
            sb(v1, s3, 86);
            lbu(a0, v0, 0);  // 0x7A9438
            sb(zero, s3, 91);
            sb(a0, s3, 87);
            sb(zero, s3, 90);
            if (i64(s2) > 0) {
                // 0x00560a48
                charge(ctx, 4);
                s1 = s2;
                a1 = addiu(s3, 8);
                a0 = 64;
                for (;;) {
                    // 0x00560a58
                    charge(ctx, 7);
                    v0 = addu(s3, a0);
                    v1 = addu(a1, a0);
                    s1 = addiu(s1, -1);
                    sw(zero, v0, 0);
                    a0 = addiu(a0, 4);
                    sw(zero, v1, 0);
                    if (s1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00560a74
            charge(ctx, 23);
            s1 = 1;
            sb(zero, s3, 88);
            sb(s1, s3, 89);
            sw(zero, s3, 92);
            lw(a0, s6, 0);
            sw(zero, s3, 96);
            lw(v1, a0, 0);
            sw(zero, s3, 36);
            lw(v0, v1, 36);
            a1 = 1;
            jalr(ctx, 0x560A98u, v0.u());
            lw(a0, s6, 0);
            s0 = v0;
            lw(v1, a0, 0);
            lw(v0, v1, 36);
            a1 = 0;
            jalr(ctx, 0x560AB0u, v0.u());
            v1 = 16384;
            s0 = addu(s0, v0);
            v0 = s3;
            sw(s0, s3, 40);
            sw(v1, s3, 44);
            sb(s1, s3, 0);
        } else {
            // 0x005608e8
            charge(ctx, 5);
            a0 = 0x7C0000;
            a0 = addiu(a0, 26016);  // "E0100401: can't create PS2RNA of IOP\n"
            jal(ctx, 0x5608ECu, gen::fn_sub_541760_00541760);
            v0 = 0;
        }
    }
    // 0x00560ad0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(s6, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
    return;
L_0056083c_11:
    charge(ctx, 4);
    a0 = addiu(s5, 25976);
    jal(ctx, 0x56083Cu, gen::fn_sub_541760_00541760);
    v0 = 0;
    if (i64(s2) > 0) {
        // 0x0056084c
        charge(ctx, 3);
        s1 = s4;
        s0 = s2;
        lw(v0, s1, 0);
        for (;;) {
            // 0x00560858
            charge(ctx, 3);
            s1 = addiu(s1, 4);
            a0 = v0;
            if (v0 != 0) {
                // 0x00560864
                charge(ctx, 2);
                jal(ctx, 0x560864u, gen::fn_sub_55FB98_0055fb98);
            }
            // 0x0056086c
            charge(ctx, 3);
            s0 = addiu(s0, -1);
            if (s0 == 0) {
                break;
            }
            lw(v0, s1, 0);
            backedge(ctx);
        }
        // 0x00560878
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00560ad0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(s6, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
    return;
L_00560944_26:
    charge(ctx, 5);
    a0 = addiu(s5, 26056);
    s5 = 0;
    jal(ctx, 0x560948u, gen::fn_sub_541760_00541760);
    v0 = 0;
    if (i64(s2) > 0) {
        // 0x00560958
        charge(ctx, 4);
        s1 = s4;
        s0 = addiu(s3, 16);
        lw(v0, s0, 0);
        for (;;) {
            // 0x00560968
            charge(ctx, 3);
            s0 = addiu(s0, 4);
            a0 = v0;
            if (v0 != 0) {
                // 0x00560974
                charge(ctx, 2);
                jal(ctx, 0x560974u, gen::fn_sub_559370_00559370);
            }
            // 0x0056097c
            charge(ctx, 3);
            lw(v0, s3, 32);
            a0 = 9;
            if (v0 != 0) {
                // 0x00560988
                charge(ctx, 6);
                a1 = sp;
                a2 = 1;
                a3 = 0;
                t0 = 0;
                link(ctx, 0x560998u);  // $ra first: the delay slot below depends on it
                sw(v0, sp, 0x0);
                call(ctx, gen::fn_DTX_CallUrpc_00559c10);
            }
            // 0x005609a0
            charge(ctx, 3);
            lw(a0, s1, 0);
            s1 = addiu(s1, 4);
            if (a0 != 0) {
                // 0x005609ac
                charge(ctx, 2);
                jal(ctx, 0x5609ACu, gen::fn_sub_55FB98_0055fb98);
            }
            // 0x005609b4
            charge(ctx, 4);
            s5 = addiu(s5, 1);
            v0 = slt(s5, s2);
            if (v0 == 0) {
                break;
            }
            lw(v0, s0, 0);
            backedge(ctx);
        }
        // 0x005609c4
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00560ad0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(s6, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
}

// 0x00560AF8 sub_560AF8 -- 232 bytes; frame 0x30: s1 sp+0x18, s0 sp+0x10, s2 sp+0x20, ra sp+0x28
// PS2RNA handle destruction: with IOP sound, every channel's DTR (sub_559370), the IOP object (DTX_CallUrpc 9)
//   and every PSJ (sub_55FB98); the used byte is cleared on both paths.
void sub_560AF8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00560af8
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x30);
    lw(v1, v0, -27656);  // 0x7A93F8
    a1 = 1;
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s0, sp, 0x10);
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x28);
    if (v1 == a1) {
        // 0x00560b20
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        if (i64(v1) > 0) {
            goto L_00560b30;
        }
        sb(zero, s1, 0);
        // 0x00560bc8 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s0, sp, 0x10);
        ld(s1, sp, 0x18);
        ld(s2, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        return;
    }
L_00560b30:
    charge(ctx, 3);
    lw(v1, s1, 4);
    s2 = 0;
    if (i64(v1) > 0) {
        // 0x00560b3c
        charge(ctx, 3);
        s0 = addiu(s1, 16);
        lw(a0, s0, 0);
        for (;;) {
            // 0x00560b48
            charge(ctx, 2);
            s0 = addiu(s0, 4);
            if (a0 != 0) {
                // 0x00560b50
                charge(ctx, 3);
                jal(ctx, 0x560B50u, gen::fn_sub_559370_00559370);
                lw(v1, s1, 4);
            }
            // 0x00560b5c
            charge(ctx, 4);
            s2 = addiu(s2, 1);
            v0 = slt(s2, v1);
            if (v0 == 0) {
                break;
            }
            lw(a0, s0, 0);
            backedge(ctx);
        }
    }
    // 0x00560b6c
    charge(ctx, 11);
    lw(v0, s1, 32);
    a0 = 9;
    a1 = sp;
    a2 = 1;
    a3 = 0;
    t0 = 0;
    link(ctx, 0x560B84u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x0);
    call(ctx, gen::fn_DTX_CallUrpc_00559c10);
    lw(v1, s1, 4);
    s2 = 0;
    if (i64(v1) > 0) {
        // 0x00560b98
        charge(ctx, 2);
        s0 = addiu(s1, 8);
        lw(a0, s0, 0);
        for (;;) {
            // 0x00560ba0
            charge(ctx, 2);
            s0 = addiu(s0, 4);
            if (a0 != 0) {
                // 0x00560ba8
                charge(ctx, 3);
                jal(ctx, 0x560BA8u, gen::fn_sub_55FB98_0055fb98);
                lw(v1, s1, 4);
            }
            // 0x00560bb4
            charge(ctx, 4);
            s2 = addiu(s2, 1);
            v0 = slt(s2, v1);
            if (v0 == 0) {
                break;
            }
            lw(a0, s0, 0);
            backedge(ctx);
        }
    }
    // 0x00560bc4
    charge(ctx, 1);
    sb(zero, s1, 0);
    // 0x00560bc8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00560C88 sub_560C88 -- 152 bytes; frame 0x30: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, ra sp+0x20
// PS2RNA play switch (+88, gated by IOP sound): any value but 1 also stops each channel's DTR (DTR_Stop) and
//   sets +89 = 1, +88 = 0.
void sub_560C88(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00560c88
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x7B0000;
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s0, sp, 0x0);
    a2 = 1;
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    lw(v1, v0, -27656);  // 0x7A93F8
    lb(a0, s2, 82);
    if (v1 == a2) {
        // 0x00560cb8
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        ld(s0, sp, 0x0);
        if (i64(v1) > 0) {
            goto L_00560cc8;
        }
        // 0x00560d08 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_00560cc8:
    charge(ctx, 2);
    sb(a1, s2, 88);
    if (a1 != a2) {
        // 0x00560cd0
        charge(ctx, 2);
        ld(s0, sp, 0x0);
        if (i64(a0) > 0) {
            // 0x00560cd8
            charge(ctx, 4);
            s1 = a0;
            s3 = 1;
            s0 = addiu(s2, 16);
            for (;;) {
                // 0x00560ce8
                charge(ctx, 7);
                lw(a0, s0, 0);
                s0 = addiu(s0, 4);
                s1 = addiu(s1, -1);
                jal(ctx, 0x560CF0u, gen::fn_DTR_Stop_005593a8);
                sb(s3, s2, 89);
                sb(zero, s2, 88);
                if (s1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            goto L_00560d04;
        }
        // 0x00560d08 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_00560d04:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x00560d08 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00560D20 sub_560D20 -- 44 bytes; leaf frame (no stack)
// PS2RNA: stores a1 in byte +80 (gated by IOP sound).
void sub_560D20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00560d20
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    a2 = 1;
    lw(v1, v0, -27656);  // 0x7A93F8
    if (v1 != a2) {
        sb(a1, a0, 80);
    } else {
        // 0x00560d34
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        if (i64(v1) > 0) {
            sb(a1, a0, 80);
        }
    }
    // 0x00560d44 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00560EB0 sub_560EB0 -- 100 bytes; frame 0x10: ra sp+0x0
// PS2RNA: (0x4000 - the first channel's SJ line-0 count (vtable +36)) / 2, gated by IOP sound (else 0).
void sub_560EB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00560eb0
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, -27656);  // 0x7A93F8
    a1 = 1;
    sd(ra, sp, 0x0);
    a2 = a0;
    if (v1 == a1) {
        // 0x00560ecc
        charge(ctx, 4);
        a0 = 0x7B0000;
        lw(v1, a0, -27664);  // 0x7A93F0
        v0 = 0;
        if (i64(v1) > 0) {
            goto L_00560edc;
        }
        // 0x00560f08 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_00560edc:
    charge(ctx, 11);
    lw(v0, a2, 8);
    lw(a0, v0, 8);
    lw(v1, a0, 0);
    lw(v0, v1, 36);
    a1 = 0;
    jalr(ctx, 0x560EECu, v0.u());
    v1 = 16384;
    v1 = subu(v1, v0);
    v0 = srl(v1, 31);
    v1 = addu(v1, v0);
    v0 = sra(v1, 1);
    // 0x00560f08 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00560F18 sub_560F18 -- 92 bytes; frame 0x10: ra sp+0x0
// PS2RNA: the first channel's SJ line-0 count (vtable +36) / 2, gated by IOP sound (else 0).
void sub_560F18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00560f18
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, -27656);  // 0x7A93F8
    a1 = 1;
    sd(ra, sp, 0x0);
    a2 = a0;
    if (v1 == a1) {
        // 0x00560f34
        charge(ctx, 4);
        a0 = 0x7B0000;
        lw(v1, a0, -27664);  // 0x7A93F0
        v0 = 0;
        if (i64(v1) > 0) {
            goto L_00560f44;
        }
        // 0x00560f68 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_00560f44:
    charge(ctx, 9);
    lw(v0, a2, 8);
    lw(a0, v0, 8);
    lw(v1, a0, 0);
    lw(v0, v1, 36);
    a1 = 0;
    jalr(ctx, 0x560F54u, v0.u());
    v1 = srl(v0, 31);
    v1 = addu(v1, v0);
    v0 = sra(v1, 1);
    // 0x00560f68 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00560F78 sub_560F78 -- 444 bytes; frame 0x40: s1 sp+0x18, s0 sp+0x10, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, ra sp+0x38
// PS2RNA per-handle server step: when +88 == 1, counts the channels whose DTR state (sub_559138) is not 1 and
//   whose SJ holds exactly +44 bytes; when every channel does, each channel's buffer is taken whole (get chunk,
//   vtable +24, len 0x7FFFFFFF), put back on line 0 and taken again (a length other than +44 spins forever), put back
//   (vtable +32), +91 cleared and the DTR restarted (sub_559398).
void sub_560F78(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00560f78
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v1 = 1;
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s0, sp, 0x10);
    sd(s2, sp, 0x20);
    sd(s3, sp, 0x28);
    sd(s4, sp, 0x30);
    sd(ra, sp, 0x38);
    lb(v0, s1, 88);
    ld(s0, sp, 0x10);
    if (v0 == v1) {
        // 0x00560fa8
        charge(ctx, 5);
        lb(v0, s1, 82);
        s2 = 0;
        lbu(v1, s1, 82);
        s3 = 0;
        if (i64(v0) > 0) {
            // 0x00560fbc
            charge(ctx, 3);
            s4 = 1;
            s0 = addiu(s1, 8);
            for (;;) {
                // 0x00560fc8
                charge(ctx, 4);
                link(ctx, 0x560FC8u);  // $ra first: the delay slot below depends on it
                lw(a0, s0, 8);
                call(ctx, gen::fn_sub_559138_00559138);
                a1 = 0;
                if (v0 != s4) {
                    // 0x00560fd8
                    charge(ctx, 10);
                    lw(v0, s0, 0);
                    lw(a0, v0, 8);
                    lw(v1, a0, 0);
                    lw(v0, v1, 36);
                    jalr(ctx, 0x560FE8u, v0.u());
                    lw(v1, s1, 44);
                    a0 = addiu(s2, 1);
                    v0 = v0 ^ v1;
                    if (v0 == 0) s2 = a0;
                }
                // 0x00561000
                charge(ctx, 6);
                lb(v0, s1, 82);
                s3 = addiu(s3, 1);
                s0 = addiu(s0, 4);
                v0 = slt(s3, v0);
                lbu(v1, s1, 82);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00561018
        charge(ctx, 4);
        v0 = sll(v1, 24);
        v0 = sra(v0, 24);
        ld(s0, sp, 0x10);
        if (s2 == v0) {
            // 0x00561028
            charge(ctx, 2);
            s3 = 0;
            if (i64(s2) > 0) {
                // 0x00561030
                charge(ctx, 4);
                s2 = addiu(s1, 16);
                s0 = addiu(s1, 8);
                lw(v0, s0, 0);
                for (;;) {
                    // 0x00561040
                    charge(ctx, 29);
                    a2 = 0x7FFF0000;
                    a3 = sp;
                    a1 = 0;
                    lw(a0, v0, 8);
                    lw(v1, a0, 0);
                    lw(v0, v1, 24);
                    a2 = a2 | 0xFFFF;
                    jalr(ctx, 0x561058u, v0.u());
                    lw(a3, s0, 0);
                    a2 = sp;
                    lw(a0, a3, 8);
                    lw(v1, a0, 0);
                    lw(v0, v1, 32);
                    a1 = 0;
                    jalr(ctx, 0x561074u, v0.u());
                    lw(v1, s0, 0);
                    a2 = 0x7FFF0000;
                    a1 = 0;
                    lw(a0, v1, 8);
                    a2 = a2 | 0xFFFF;
                    lw(v1, a0, 0);
                    lw(v0, v1, 24);
                    a3 = sp;
                    jalr(ctx, 0x561098u, v0.u());
                    a1 = 0;
                    lw(v1, sp, 0x4);
                    lw(v0, s1, 44);
                    a2 = sp;
                    if (v1 != v0) {
                        goto L_005610b4_10;
                    }
                    // 0x005610d8
                    charge(ctx, 15);
                    lw(v0, s0, 0);
                    s0 = addiu(s0, 4);
                    lw(a0, v0, 8);
                    lw(v1, a0, 0);
                    lw(v0, v1, 32);
                    s3 = addiu(s3, 1);
                    jalr(ctx, 0x5610ECu, v0.u());
                    sb(zero, s1, 91);
                    lw(a0, s2, 0);
                    s2 = addiu(s2, 4);
                    jal(ctx, 0x5610FCu, gen::fn_sub_559398_00559398);
                    lb(v0, s1, 82);
                    v0 = slt(s3, v0);
                    if (v0 == 0) {
                        break;
                    }
                    lw(v0, s0, 0);
                    backedge(ctx);
                }
                // 0x00561114
                charge(ctx, 1);
                ld(s0, sp, 0x10);
            }
        }
    }
    // 0x00561118 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
    return;
L_005610b4_10:
    charge(ctx, 1);
    for (;;) {
        // 0x005610b8
        charge(ctx, 7);
        backedge(ctx);
    }
}

// 0x00561138 PS2RNA_ExecServer -- 164 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// PS2RNA server (gated by IOP sound): raises the nesting count (sub_561728), steps every used slot of the
//   16-slot table (sub_560F78), lowers the count (sub_561740), then DTR_ExecServer and sub_564510.
void PS2RNA_ExecServer(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561138
    enter(ctx, 9);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x20);
    lw(v1, v0, -27656);  // 0x7A93F8
    a0 = 1;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    if (v1 == a0) {
        // 0x0056115c
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        ld(s0, sp, 0x0);
        if (i64(v1) > 0) {
            goto L_0056116c;
        }
        // 0x005611c8
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_0056116c:
    charge(ctx, 5);
    s2 = 1;
    jal(ctx, 0x56116Cu, gen::fn_sub_561728_00561728);
    v0 = 0x7B0000;
    s0 = addiu(v0, -18352);  // &0x7AB850
    s1 = 15;
    for (;;) {
        // 0x00561180
        charge(ctx, 3);
        lb(v0, s0, 0);
        if (v0 != s2) {
            s1 = addiu(s1, -1);
        } else {
            // 0x0056118c
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x56118Cu, gen::fn_sub_560F78_00560f78);
            s1 = addiu(s1, -1);
        }
        // 0x00561198
        charge(ctx, 2);
        s0 = addiu(s0, 100);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005611a0
    charge(ctx, 10);
    jal(ctx, 0x5611A0u, gen::fn_sub_561740_00561740);
    jal(ctx, 0x5611A8u, gen::fn_DTR_ExecServer_00559140);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_564510_00564510(ctx);  // tail call
}

// 0x00561258 sub_561258 -- 120 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// PS2RNA sampling frequency (+48, gated by IOP sound): stores a1; when 48000 is not a multiple of it, first
//   prints "PS2RNA: Warning : IOP load is high!" (sub_5416E8). A zero divisor reaches the divide-by-zero break.
void sub_561258(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561258
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x20);
    lw(v1, v0, -27656);  // 0x7A93F8
    a2 = 1;
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(ra, sp, 0x10);
    if (v1 == a2) {
        // 0x00561280
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        if (i64(v1) > 0) {
            goto L_00561290;
        }
        ld(s0, sp, 0x0);
        // 0x005612c0 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_00561290:
    charge(ctx, 3);
    v0 = 0xBB80;
    if (s0 == 0) {
        brk(ctx, 0x561298u, 0x7u);
    }
    // 0x0056129c
    charge(ctx, 4);
    div(v0, s0);
    mfhi(v1);
    if (v1 == 0) {
        sw(s0, s1, 48);
    } else {
        // 0x005612ac
        charge(ctx, 4);
        a0 = 0x7C0000;
        a0 = addiu(a0, 26248);  // &0x7C6688
        jal(ctx, 0x5612B0u, gen::fn_sub_5416E8_005416e8);
        sw(s0, s1, 48);
    }
    // 0x005612bc
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x005612c0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00561390 sub_561390 -- 80 bytes; frame 0x10: ra sp+0x0
// PS2RNA_SetBitPerSmpl (gated by IOP sound): only 16 bps; anything else reports "not support %d bps"
//   (sub_541760).
void sub_561390(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00561390
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, -27656);  // 0x7A93F8
    a0 = 1;
    sd(ra, sp, 0x0);
    a2 = a1;
    if (v1 == a0) {
        // 0x005613ac
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        ld(ra, sp, 0x0);
        if (i64(v1) > 0) {
            goto L_005613bc;
        }
        // 0x005613d8 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_005613bc:
    charge(ctx, 3);
    v0 = 16;
    ld(ra, sp, 0x0);
    if (a2 != v0) {
        // 0x005613c8
        charge(ctx, 4);
        a0 = 0x7C0000;
        a0 = addiu(a0, 26312);  // "PS2RNA_SetBitPerSmpl: not support %d bps\n"
        jal(ctx, 0x5613CCu, gen::fn_sub_541760_00541760);
        ld(ra, sp, 0x0);
    }
    // 0x005613d8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00561728 sub_561728 -- 24 bytes; leaf frame (no stack)
// Raises the PS2RNA server nesting count 0x7AC768.
void sub_561728(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00561728
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    v1 = addiu(v1, -14488);  // &0x7AC768
    lw(v0, v1, 0);  // 0x7AC768
    v0 = addiu(v0, 1);
    sw(v0, v1, 0);  // 0x7AC768
}

// 0x00561740 sub_561740 -- 24 bytes; leaf frame (no stack)
// Lowers the PS2RNA server nesting count 0x7AC768.
void sub_561740(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00561740
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    v1 = addiu(v1, -14488);  // &0x7AC768
    lw(v0, v1, 0);  // 0x7AC768
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x7AC768
}

// 0x00563D20 sub_563D20 -- 172 bytes; leaf frame (no stack)
// Seven hex digits at a0 to a value through the digit table 0x7B18F0 (value = value * 16 + digit).
void sub_563D20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x00563d20
    enter(ctx, 43);  // entry check point + this block's cycles
    lb(v0, a0, 0);
    a2 = 0x7B0000;
    lb(v1, a0, 1);
    a2 = addiu(a2, 6384);  // &0x7B18F0
    v0 = sll(v0, 2);
    lb(a1, a0, 2);
    v0 = addu(v0, a2);
    v1 = sll(v1, 2);
    lw(t1, v0, 0);
    v1 = addu(v1, a2);
    lw(a3, v1, 0);
    a1 = sll(a1, 2);
    lb(v0, a0, 3);
    v1 = sll(t1, 4);
    a1 = addu(a1, a2);
    t1 = addu(v1, a3);
    lw(t0, a1, 0);
    a1 = sll(t1, 4);
    lb(v1, a0, 4);
    v0 = sll(v0, 2);
    v0 = addu(v0, a2);
    t1 = addu(a1, t0);
    lw(a3, v0, 0);
    v1 = sll(v1, 2);
    lb(v0, a0, 5);
    a1 = sll(t1, 4);
    v1 = addu(v1, a2);
    t1 = addu(a1, a3);
    lw(t0, v1, 0);
    v0 = sll(v0, 2);
    lb(v1, a0, 6);
    a0 = sll(t1, 4);
    v0 = addu(v0, a2);
    t1 = addu(a0, t0);
    lw(a1, v0, 0);
    v0 = sll(t1, 4);
    v1 = sll(v1, 2);
    v1 = addu(v1, a2);
    t1 = addu(v0, a1);
    lw(a0, v1, 0);
    v0 = sll(t1, 4);
    v0 = addu(v0, a0);
}

// 0x00563E68 sub_563E68 -- 208 bytes; frame 0x40: s3 sp+0x18, s0 sp+0x0, s2 sp+0x10, s4 sp+0x20, s5 sp+0x28, s1 sp+0x8, ra sp+0x30
// Tagged-block search in the area {base, size} at a0: each block is a 16-byte header (7-char tag, 7 hex
//   digits of body size at +8, sub_563D20) and its body. A block tagged a1 (strncmp 7) is copied to a3
//   (sub_563E30) and returned; a block tagged a2 (when a2 != 0) or the area's end returns 0. a3's two words are
//   cleared first.
void sub_563E68(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00563e68
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    s5 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x30);
    sw(zero, s3, 0);
    sw(zero, s3, 4);
    lw(v0, a0, 0);
    lw(v1, a0, 4);
    s0 = v0;
    s4 = addu(v0, v1);
    for (;;) {
        // 0x00563ed8
        charge(ctx, 3);
        s1 = sltu(s0, s4);
        v0 = 0;
        if (s1 == 0) {
            goto L_00563f10;
        }
        // 0x00563ee4
        charge(ctx, 8);
        a0 = s0;
        a1 = s5;
        a2 = 7;
        jal(ctx, 0x563EECu, gen::fn_strncmp_00524670);
        a0 = s0;
        a1 = s2;
        a2 = 7;
        if (v0 == 0) {
            goto L_00563f04_6;
        }
        backedge(ctx);
        // 0x00563eb0
        charge(ctx, 2);
        if (s2 != 0) {
            // 0x00563eb8
            charge(ctx, 4);
            jal(ctx, 0x563EB8u, gen::fn_strncmp_00524670);
            if (v0 != 0) {
                goto L_00563ec8;
            }
            ld(s0, sp, 0x0);
            break;
        }
    L_00563ec8:
        charge(ctx, 4);
        a0 = addiu(s0, 8);
        jal(ctx, 0x563EC8u, gen::fn_sub_563D20_00563d20);
        v0 = addu(s0, v0);
        s0 = addiu(v0, 16);
    }
    // 0x00563f18 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
    return;
L_00563f04_6:
    charge(ctx, 3);
    a1 = s3;
    jal(ctx, 0x563F04u, gen::fn_sub_563E30_00563e30);
    v0 = 0;
L_00563f10:
    charge(ctx, 2);
    if (s1 != 0) v0 = s0;
    ld(s0, sp, 0x0);
    // 0x00563f18 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00563FE0 sub_563FE0 -- 84 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// IOP call 34 with three words through the RPC buffer 0x999C00; returns the reply word 0x999D00.
void sub_563FE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00563fe0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x9A0000;
    sd(s0, sp, 0x0);
    s0 = 0x9A0000;
    v0 = addiu(v0, -25600);  // &0x999C00
    sd(ra, sp, 0x8);
    s0 = addiu(s0, -25344);  // &0x999D00
    sw(a0, v0, 0);  // 0x999C00
    sw(a1, v0, 4);  // 0x999C04
    a1 = v0;
    sw(a2, v0, 8);  // 0x999C08
    a2 = 3;
    a3 = s0;
    a0 = 34;
    t0 = 1;
    jal(ctx, 0x564018u, gen::fn_DTX_CallUrpc_00559c10);
    lw(v0, s0, 0);  // 0x999D00
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00564218 sub_564218 -- 80 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// IOP call 41 with two words through the RPC buffer 0x999C00; returns the reply word 0x999D00.
void sub_564218(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564218
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x9A0000;
    sd(s0, sp, 0x0);
    s0 = 0x9A0000;
    v0 = addiu(v0, -25600);  // &0x999C00
    sd(ra, sp, 0x8);
    s0 = addiu(s0, -25344);  // &0x999D00
    sw(a0, v0, 0);  // 0x999C00
    sw(a1, v0, 4);  // 0x999C04
    a1 = v0;
    a3 = s0;
    a0 = 41;
    a2 = 2;
    t0 = 1;
    jal(ctx, 0x56424Cu, gen::fn_DTX_CallUrpc_00559c10);
    lw(v0, s0, 0);  // 0x999D00
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005642D0 sub_5642D0 -- 80 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Reference-counted DTX_Init (count 0x7B1AB4; the first caller initialises).
void sub_5642D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005642d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x7B0000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 6836);  // &0x7B1AB4
    sd(ra, sp, 0x8);
    v1 = 0x7B0000;
    lw(a0, s0, 0);  // 0x7B1AB4
    v1 = addiu(v1, 6832);  // "hl|"
    lw(v0, v1, 0);  // 0x7B1AB0
    v0 = addiu(a0, 1);
    if (a0 == 0) {
        // 0x005642fc
        charge(ctx, 4);
        jal(ctx, 0x5642FCu, gen::fn_DTX_Init_00559aa8);
        lw(a0, s0, 0);
        v0 = addiu(a0, 1);
    }
    // 0x0056430c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x8);
    sw(v0, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00564360 sub_564360 -- 156 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// SJX return path (data ref, an IOP-reply handler): for each of the a1->count 16-byte records after the
//   count word, a record whose byte +0 is 0 puts its chunk (+8) back into its entry's SJ (vtable +32, line byte +1);
//   between sub_5617C0 / sub_5617D8. A null a1 spins forever.
void sub_564360(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00564360
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    if (s0 == 0) {
        for (;;) {
            // 0x00564378
            charge(ctx, 7);
            backedge(ctx);
        }
    }
    // 0x00564398
    charge(ctx, 4);
    link(ctx, 0x564398u);  // $ra first: the delay slot below depends on it
    lw(s1, s0, 0);
    call(ctx, gen::fn_sub_5617C0_005617c0);
    if (i64(s1) <= 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x005643a8
        charge(ctx, 2);
        a1 = s0;
        for (;;) {
            // 0x005643b0
            charge(ctx, 4);
            s0 = addiu(a1, 16);
            lb(v0, s0, 0);
            if (v0 != 0) {
                s1 = addiu(s1, -1);
            } else {
                // 0x005643c0
                charge(ctx, 8);
                lw(v0, a1, 20);
                a2 = addiu(a1, 24);
                lw(a0, v0, 4);
                lw(v1, a0, 0);
                lw(v0, v1, 32);
                jt = v0.u();  // the target, read before the delay slot
                link(ctx, 0x5643D4u);  // $ra = the return address
                lb(a1, a1, 17);
                call_ptr(ctx, jt);
                s1 = addiu(s1, -1);
            }
            // 0x005643e0
            charge(ctx, 2);
            a1 = s0;
            if (s1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005643e8
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x005643ec
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_5617D8_005617d8(ctx);  // tail call
}

// 0x00564400 sub_564400 -- 272 bytes; frame 0x60: s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s5 sp+0x38, s6 sp+0x40, s7 sp+0x48, s0 sp+0x10, s4 sp+0x30, ra sp+0x50
// SJX gather (data ref): for each used entry of the 32 x 20-byte table 0x7B1AD0, takes chunks (get chunk,
//   vtable +24, line +12, len 0x7FFFFFFF) into 16-byte records after a1's count word until a chunk is empty or 128
//   records are written, then stores the count; between sub_5617C0 / sub_5617D8.
void sub_564400(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564400
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    s2 = 0;
    sd(s3, sp, 0x28);
    s3 = 0;
    sd(s5, sp, 0x38);
    sd(s6, sp, 0x40);
    s6 = a1;
    sd(s7, sp, 0x48);
    s7 = 1;
    sd(s0, sp, 0x10);
    sd(s4, sp, 0x30);
    sd(ra, sp, 0x50);
    s5 = addiu(s6, 16);
    jal(ctx, 0x564438u, gen::fn_sub_5617C0_005617c0);
    v0 = 0x7B0000;
    s1 = addiu(v0, 6864);  // &0x7B1AD0
    for (;;) {
        // 0x00564448
        charge(ctx, 3);
        lb(v0, s1, 0);
        if (v0 != s7) {
            s3 = addiu(s3, 1);
        } else {
            // 0x00564454
            charge(ctx, 4);
            v0 = sll(s2, 4);
            s4 = 128;
            s0 = addu(v0, s5);
            for (;;) {
                // 0x00564498
                charge(ctx, 2);
                a2 = 0x7FFF0000;
                if (s2 == s4) {
                    break;
                }
                // 0x005644a0
                charge(ctx, 10);
                lw(a0, s1, 4);
                lw(a1, s1, 12);
                a2 = a2 | 0xFFFF;
                lw(v1, a0, 0);
                lw(v0, v1, 24);
                a3 = sp;
                jalr(ctx, 0x5644B4u, v0.u());
                lw(v1, sp, 0x4);
                if (v1 == 0) {
                    goto L_005644c8_6;
                }
                sb(zero, s0, 0);
                backedge(ctx);
                // 0x00564468
                charge(ctx, 12);
                s2 = addiu(s2, 1);
                lbu(v0, s1, 12);
                lw(v1, s1, 16);
                sb(v0, s0, 1);
                sw(v1, s0, 4);
                lhu(v0, s1, 2);
                ldl(v1, sp, 0x7);
                ldr(v1, sp, 0x0);
                sdl(v1, s0, 15);
                sdr(v1, s0, 8);
                sh(v0, s0, 2);
                s0 = addiu(s0, 16);
            }
            break;
        }
    L_005644cc:
        charge(ctx, 3);
        v0 = slti(s3, 32);
        s1 = addiu(s1, 20);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005644d8
    charge(ctx, 14);
    jal(ctx, 0x5644D8u, gen::fn_sub_5617D8_005617d8);
    sw(s2, s6, 0);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(s6, sp, 0x40);
    ld(s7, sp, 0x48);
    ld(ra, sp, 0x50);
    sp = addiu(sp, 0x60);
    return;
L_005644c8_6:
    charge(ctx, 1);
    s3 = addiu(s3, 1);
    goto L_005644cc;
}

// 0x00564510 sub_564510 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk to sub_559D18.
void sub_564510(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00564510
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_559D18_00559d18(ctx);  // tail call
}

// 0x00564738 sub_564738 -- 248 bytes; frame 0x40: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, ra sp+0x30
// SJX creation: the first free slot of the 32 x 20-byte table 0x7B1AD0 gets (sj, a1, a2) and the IOP object
//   (DTX_CallUrpc 0 with {sj, a1, a2, slot}); failure prints "E0100401 ... SJX of IOP" and returns 0.
void sub_564738(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564738
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x7B0000;
    sd(s0, sp, 0x10);
    s0 = addiu(v0, 6864);  // &0x7B1AD0
    sd(s1, sp, 0x18);
    s1 = a2;
    sd(s2, sp, 0x20);
    s2 = a1;
    sd(s3, sp, 0x28);
    s3 = a0;
    sd(ra, sp, 0x30);
    lb(v0, s0, 0);  // 0x7B1AD0
    a0 = 0;
    if (v0 != 0) {
        // 0x00564770
        charge(ctx, 2);
        a1 = s0;
        v1 = s0;
        for (;;) {
            // 0x00564778
            charge(ctx, 5);
            a0 = addiu(a0, 1);
            a1 = addiu(a1, 20);
            v0 = slti(a0, 32);
            v1 = addiu(v1, 20);
            if (v0 != 0) {
                // 0x0056478c
                charge(ctx, 4);
                lb(v0, a1, 0);
                s0 = v1;
                if (v0 != 0) {
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x0056479c
    charge(ctx, 3);
    v1 = 32;
    v0 = 0;
    if (a0 != v1) {
        // 0x005647a8
        charge(ctx, 19);
        a0 = s0;
        a1 = 0;
        a2 = 20;
        jal(ctx, 0x5647B0u, gen::fn_memset_00521408);
        sw(s3, s0, 4);
        sw(s1, s0, 12);
        a0 = 0;
        sw(s2, s0, 8);
        a1 = sp;
        a2 = 4;
        a3 = sp;
        t0 = 1;
        sw(s3, sp, 0x0);
        sw(s2, sp, 0x4);
        sw(s1, sp, 0x8);
        link(ctx, 0x5647E4u);  // $ra first: the delay slot below depends on it
        sw(s0, sp, 0xC);
        call(ctx, gen::fn_DTX_CallUrpc_00559c10);
        sw(v0, s0, 16);
        if (v0 != 0) {
            // 0x00564808
            charge(ctx, 3);
            v1 = 1;
            v0 = s0;
            sb(v1, s0, 0);
        } else {
            // 0x005647f4
            charge(ctx, 5);
            a0 = 0x7C0000;
            a0 = addiu(a0, 27936);  // "E0100401: can't create SJX of IOP\n"
            jal(ctx, 0x5647F8u, gen::fn_sub_541760_00541760);
            v0 = 0;
        }
    }
    // 0x00564814 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00565730 pfsCvfsSeek -- 88 bytes; frame 0x10: ra sp+0x0
// PFS table seek on CVFS: origin 0 / 1 / 2 to cvFsSeek; any other reports -100 (sub_569730,
//   pfs_cvfs.c:132).
void pfsCvfsSeek(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00565730
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 1;
    sd(ra, sp, 0x0);
    if (a2 != v0) {
        // 0x00565740
        charge(ctx, 2);
        v0 = 0;
        if (a2 == 0) {
            goto L_00565778;
        }
        // 0x00565748
        charge(ctx, 3);
        v0 = 2;
        cc = a2 == v0;  // the condition, before the delay slot changes it
        a2 = 0x7C0000;
        if (cc) {
            goto L_00565778;
        }
        // 0x00565754
        charge(ctx, 9);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 28608);  // "../../pfs_cvfs.c"
        a2 = addiu(a2, 28632);
        a1 = 132;
        a3 = 0;
        t0 = si(-100);
        sp = addiu(sp, 0x10);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
L_00565778:
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    a2 = v0;
    sp = addiu(sp, 0x10);
    gen::fn_cvFsSeek_00556478(ctx);  // tail call
}

// 0x005657A0 pfsCvfsReqRd -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk to cvFsReqRd.
void pfsCvfsReqRd(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005657a0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_cvFsReqRd_005564e0(ctx);  // tail call
}

// 0x005657D0 pfsCvfsGetStat -- 76 bytes; frame 0x10: ra sp+0x0
// cvFsGetStat with the status folded to 0 / 1 / 2, anything else 3 (error).
void pfsCvfsGetStat(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005657d0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x5657D8u, gen::fn_cvFsGetStat_00556668);
    a0 = v0;
    v1 = 1;
    ld(ra, sp, 0x0);
    if (a0 != v1) {
        // 0x005657f0
        charge(ctx, 2);
        if (a0 == 0) {
            v0 = 0;
        } else {
            // 0x005657f8
            charge(ctx, 3);
            v1 = 2;
            if (a0 != v1) {
                // 0x00565804
                charge(ctx, 2);
                v0 = 3;
            }
        }
    }
    // 0x00565814 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00565820 pfsCvfsGetSctLen -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk to sub_556A00.
void pfsCvfsGetSctLen(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00565820
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_556A00_00556a00(ctx);  // tail call
}

// 0x00565838 pfsCvfsGetNumTr -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk to sub_556AC0.
void pfsCvfsGetNumTr(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00565838
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_556AC0_00556ac0(ctx);  // tail call
}

// 0x00565850 coshl_8 -- 52 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// sub_5577B8; when it returns 0, pfsCvfsGetNumTr (the FLIRT name is a mismatch).
void coshl_8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00565850
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x56585Cu, gen::fn_sub_5577B8_005577b8);
    a0 = s0;
    if (v0 == 0) {
        // 0x0056586c
        charge(ctx, 2);
        jal(ctx, 0x56586Cu, gen::fn_pfsCvfsGetNumTr_00565838);
    }
    // 0x00565874 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00565888 pfsCvfsExecServer -- 28 bytes; frame 0x10: ra sp+0x0
// cvFsExecServer, then sub_56DDE0 (SRD_ExecServer).
void pfsCvfsExecServer(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00565888
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x565890u, gen::fn_cvFsExecServer_00556608);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_56DDE0_0056dde0(ctx);  // tail call
}

// 0x00565BC0 sub_565BC0 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ROFS handle close: an active handle (+52) with a busy transfer (stat +56 == 2) is stopped (RFHN_StopTrG);
//   req_state (+54) and active are cleared. A null handle does nothing.
void sub_565BC0(EEContext& ctx) {
    using namespace hg;
    namespace hn = libs14::rofs_hn;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00565bc0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 != 0) {
        // 0x00565bd4
        charge(ctx, 3);
        lh(v0, s0, hn::kActive);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 2;
        if (!cc) {
            // 0x00565be0
            charge(ctx, 3);
            lh(v1, s0, hn::kStat);
            if (v1 != v0) {
                sh(zero, s0, hn::kReqState);
            } else {
                // 0x00565bec
                charge(ctx, 3);
                jal(ctx, 0x565BECu, gen::fn_RFHN_StopTrG_00566180);
                sh(zero, s0, hn::kReqState);
            }
            // 0x00565bf8
            charge(ctx, 1);
            sh(zero, s0, hn::kActive);
        }
    }
    // 0x00565bfc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00565E10 RFHN_ReqRdG -- 472 bytes; frame 0x30: s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s1 sp+0x8, ra sp+0x20
// ROFS handle read request: a null or inactive handle reports -101 (sub_569730, rofs_hn.c:367 / 370), a
//   missing volume -101 (383). A pending request, an image handle in use (RFHN_IsUseImgHn) or a busy volume (+20 > 0)
//   returns -200. The count is clamped to the file end (at the end: stat 1, 0). The read goes to the pfs table's
//   slot +48 (dcfReqRdCda: lba offset, image handle, ...); a started read records buf / count / stat 2 / req_state 1
//   and returns its sectors; none started gives stat 1 and -204, an error -200.
void RFHN_ReqRdG(EEContext& ctx) {
    using namespace hg;
    namespace hn = libs14::rofs_hn;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00565e10
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    s3 = a2;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x20);
    if (s0 == 0) {
        // 0x00565e38
        charge(ctx, 14);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 28648);  // "../../rofs_hn.c"
        ld(s1, sp, 0x8);
        a2 = addiu(a2, 28696);  // "RFHN_ReqRdG"
        ld(s2, sp, 0x10);
        a1 = 367;
        ld(s3, sp, 0x18);
        a3 = 0;
        ld(ra, sp, 0x20);
        t0 = si(-101);
        sp = addiu(sp, 0x30);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    // 0x00565e70
    charge(ctx, 4);
    lh(s1, s0, hn::kActive);
    v0 = 1;
    a2 = 0x7C0000;
    if (s1 != v0) {
        // 0x00565e80
        charge(ctx, 13);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 28648);  // "../../rofs_hn.c"
        ld(s1, sp, 0x8);
        a2 = addiu(a2, 28696);
        ld(s2, sp, 0x10);
        a1 = 370;
        ld(s3, sp, 0x18);
        a3 = 0;
        ld(ra, sp, 0x20);
        t0 = si(-101);
        sp = addiu(sp, 0x30);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    // 0x00565eb8
    charge(ctx, 3);
    lh(v1, s0, hn::kReqState);
    v0 = si(-200);
    if (v1 == s1) {
        // 0x00565fcc (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
    // 0x00565ec4
    charge(ctx, 4);
    a1 = 0;
    jal(ctx, 0x565EC4u, gen::fn_RFHN_IsUseImgHn_00565b18);
    if (v0 == s1) {
        // 0x00565ed4
        charge(ctx, 2);
        v0 = si(-200);
        // 0x00565fcc (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
    lw(t1, s0, hn::kVol);
    // 0x00565ee0
    charge(ctx, 2);
    if (t1 == 0) {
        // 0x00565ee8
        charge(ctx, 14);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 28648);  // "../../rofs_hn.c"
        ld(s1, sp, 0x8);
        a2 = addiu(a2, 28696);  // "RFHN_ReqRdG"
        ld(s2, sp, 0x10);
        a1 = 383;
        ld(s3, sp, 0x18);
        a3 = 0;
        ld(ra, sp, 0x20);
        t0 = si(-101);
        sp = addiu(sp, 0x30);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    lh(v1, t1, 20);
    // 0x00565f20
    charge(ctx, 2);
    v0 = si(-200);
    if (i64(v1) <= 0) {
        // 0x00565f28
        charge(ctx, 8);
        lw(a0, s0, hn::kStartLba);
        lw(v0, s0, hn::kPosSct);
        lw(v1, s0, hn::kSizeSct);
        a2 = addu(a0, v0);
        a0 = addu(a0, v1);
        v0 = slt(a2, a0);
        if (v0 == 0) {
            sh(s1, s0, hn::kStat);
        } else {
            // 0x00565f48
            charge(ctx, 6);
            v0 = addu(a2, s2);
            v1 = subu(a0, a2);
            v0 = slt(a0, v0);
            if (v0 != 0) s2 = v1;
            if (i64(s2) <= 0) {
                // 0x00565f60
                charge(ctx, 1);
                sh(s1, s0, hn::kStat);
                goto L_00565f64;
            }
            lw(v0, s0, hn::kRofs);
            // 0x00565f70
            charge(ctx, 10);
            a3 = s2;
            lw(a1, t1, 0);
            t0 = s3;
            lw(v1, v0, 56);
            lw(v0, v1, 48);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x565F84u);  // $ra = the return address
            lw(a0, t1, 4);
            call_ptr(ctx, jt);
            v1 = v0;
            v0 = si(-200);
            if (i64(v1) >= 0) {
                // 0x00565f98
                charge(ctx, 2);
                v0 = 2;
                if (v1 == 0) {
                    // 0x00565fc0
                    charge(ctx, 1);
                    sh(s1, s0, hn::kStat);
                } else {
                    // 0x00565fa0
                    charge(ctx, 8);
                    sw(s3, s0, hn::kBuf);
                    sw(s2, s0, hn::kReqSct);
                    sh(v0, s0, hn::kStat);
                    sh(s1, s0, hn::kReqState);
                    sw(zero, s0, hn::kRdSct);
                    sw(zero, s0, hn::kRdRemBytes);
                    sw(v1, s0, hn::kRdAccepted);
                }
                // 0x00565fc4
                charge(ctx, 2);
                v0 = si(-204);
                if (v1 != 0) v0 = v1;
            }
            // 0x00565fcc (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(ra, sp, 0x20);
            sp = addiu(sp, 0x30);
            return;
        }
    L_00565f64:
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00565fcc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00566180 RFHN_StopTrG -- 324 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ROFS transfer stop: null handle, inactive handle and missing volume report -101 (sub_569730,
//   rofs_hn.c:520 / 524 / 528). A busy handle (stat 2) with a pending request is stopped through the pfs table's
//   slot +20 between sub_569700 / sub_569718 (sub_569718's result), req_state = 2; a busy handle without a request
//   gets req_state = 2 and 1, a handle that is not busy stat = 0 and 2.
void RFHN_StopTrG(EEContext& ctx) {
    using namespace hg;
    namespace hn = libs14::rofs_hn;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00566180
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    if (s0 == 0) {
        // 0x00566198
        charge(ctx, 12);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 28648);  // "../../rofs_hn.c"
        ld(s1, sp, 0x8);
        a2 = addiu(a2, 28760);  // "RFHN_StopTrG"
        ld(ra, sp, 0x10);
        a1 = 520;
        a3 = 0;
        t0 = si(-101);
        sp = addiu(sp, 0x20);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    // 0x005661c8
    charge(ctx, 3);
    lh(v0, s0, hn::kActive);
    if (v0 == 0) {
        // 0x005661d4
        charge(ctx, 12);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 28648);  // "../../rofs_hn.c"
        ld(s1, sp, 0x8);
        a2 = addiu(a2, 28760);  // "RFHN_StopTrG"
        ld(ra, sp, 0x10);
        a1 = 524;
        a3 = 0;
        t0 = si(-101);
        sp = addiu(sp, 0x20);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    lw(v0, s0, hn::kVol);
    // 0x00566208
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x00566210
        charge(ctx, 12);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 28648);  // "../../rofs_hn.c"
        ld(s1, sp, 0x8);
        a2 = addiu(a2, 28760);  // "RFHN_StopTrG"
        ld(ra, sp, 0x10);
        a1 = 528;
        a3 = 0;
        t0 = si(-101);
        sp = addiu(sp, 0x20);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    lh(s1, s0, hn::kStat);
    // 0x00566240
    charge(ctx, 3);
    v0 = 2;
    if (s1 != v0) {
        // 0x0056624c
        charge(ctx, 2);
        sh(zero, s0, hn::kStat);
        // 0x005662b0 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    lh(v1, s0, hn::kReqState);
    // 0x00566258
    charge(ctx, 3);
    v0 = 1;
    if (v1 != v0) {
        // 0x00566264
        charge(ctx, 2);
        sh(s1, s0, hn::kReqState);
        // 0x005662b0 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00566270
    charge(ctx, 15);
    jal(ctx, 0x566270u, gen::fn_sub_569700_00569700);
    lw(v0, s0, hn::kRofs);
    lw(v1, s0, hn::kVol);
    lw(a1, v0, 56);
    lw(v0, a1, 20);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x566288u);  // $ra = the return address
    lw(a0, v1, 0);
    call_ptr(ctx, jt);
    sh(s1, s0, hn::kReqState);
    a0 = s0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_569718_00569718(ctx);  // tail call
}

// 0x005662F0 RFIF_InitOvl -- 48 bytes; frame 0x10: ra sp+0x0
// Selects the ROFS interface table (RFMAI_fs_lif_tbl -> 0x7B26F8) and calls its init slot +12 (RFMAI_InitG).
void RFIF_InitOvl(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005662f0
    enter(ctx, 12);  // entry check point + this block's cycles
    v1 = 0x7C0000;
    sp = addiu(sp, -0x10);
    v1 = addiu(v1, 29232);  // &RFMAI_fs_lif_tbl
    v0 = 0x7B0000;
    sd(ra, sp, 0x0);
    sw(v1, v0, 9976);  // 0x7B26F8
    lw(v0, v1, 12);  // 0x7C723C
    a1 = v1;
    jalr(ctx, 0x56630Cu, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005663D8 ROFS_AddVolume -- 172 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// sub_569810, then the interface table's slot +24 (add volume); on success sub_5662C8. No table: -203
//   (sub_569730, rofs_if.c:163).
void ROFS_AddVolume(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005663d8
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x5663F4u, gen::fn_sub_569810_00569810);
    v0 = 0x7B0000;
    a0 = s0;
    lw(v0, v0, 9976);  // 0x7B26F8
    a1 = s1;
    a2 = s2;
    a3 = 0;
    t0 = si(-203);
    if (v0 == 0) {
        // 0x00566458
        charge(ctx, 11);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 28776);  // "../../rofs_if.c"
        ld(s1, sp, 0x8);
        a2 = addiu(a2, 28816);  // "ROFS_AddVolume"
        ld(s2, sp, 0x10);
        a1 = 163;
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    // 0x0056641c
    charge(ctx, 6);
    lw(v0, v0, 24);
    jalr(ctx, 0x566420u, v0.u());
    s0 = v0;
    v0 = s0;
    if (s0 != 0) {
        // 0x00566434
        charge(ctx, 3);
        jal(ctx, 0x566434u, gen::fn_sub_5662C8_005662c8);
        v0 = s0;
    }
    // 0x00566440 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005664F8 sub_5664F8 -- 112 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ROFS_SetDefVolume (per its error string): sub_569810, then the interface table's slot +32; no table: -203
//   (rofs_if.c:193).
void sub_5664F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005664f8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x566504u, gen::fn_sub_569810_00569810);
    v0 = 0x7B0000;
    a2 = 0x7C0000;
    lw(v0, v0, 9976);  // 0x7B26F8
    a0 = s0;
    a2 = addiu(a2, 28848);  // "ROFS_SetDefVolume"
    a1 = 193;
    a3 = 0;
    t0 = si(-203);
    if (v0 != 0) {
        // 0x00566530
        charge(ctx, 7);
        lw(v0, v0, 32);
        jalr(ctx, 0x566534u, v0.u());
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00566550
    charge(ctx, 6);
    a0 = 0x7C0000;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    a0 = addiu(a0, 28776);  // "../../rofs_if.c"
    sp = addiu(sp, 0x10);
    gen::fn_sub_569730_00569730(ctx);  // tail call
}

// 0x005665D0 ROFS_Open -- 128 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// sub_569810, then the interface table's slot +40 (open); no table: -203 (rofs_if.c:224), returns 0.
void ROFS_Open(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005665d0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x5665E4u, gen::fn_sub_569810_00569810);
    v0 = 0x7B0000;
    a2 = 0x7C0000;
    lw(v0, v0, 9976);  // 0x7B26F8
    a0 = s0;
    a1 = s1;
    a3 = 0;
    a2 = addiu(a2, 28896);  // "ROFS_Open"
    t0 = si(-203);
    if (v0 == 0) {
        // 0x00566628
        charge(ctx, 6);
        a0 = 0x7C0000;
        a1 = 224;
        a0 = addiu(a0, 28776);  // "../../rofs_if.c"
        jal(ctx, 0x566630u, gen::fn_sub_569730_00569730);
        v0 = 0;
        ld(s0, sp, 0x0);
    } else {
        // 0x00566610
        charge(ctx, 5);
        lw(v0, v0, 40);
        jalr(ctx, 0x566614u, v0.u());
        ld(s0, sp, 0x0);
    }
    // 0x00566640 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005666E0 ROFS_Close -- 40 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// sub_569810, then the handle close (sub_565BC0).
void ROFS_Close(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005666e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5666ECu, gen::fn_sub_569810_00569810);
    ld(ra, sp, 0x8);
    a0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_565BC0_00565bc0(ctx);  // tail call
}

// 0x00566708 ROFS_ReqRd -- 72 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// sub_569810, then RFHN_ReqRdG(handle, sectors, buf).
void ROFS_ReqRd(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00566708
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x566724u, gen::fn_sub_569810_00569810);
    ld(ra, sp, 0x18);
    a0 = s0;
    a1 = s1;
    ld(s1, sp, 0x8);
    a2 = s2;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    gen::fn_RFHN_ReqRdG_00565e10(ctx);  // tail call
}

// 0x00566778 ROFS_ExecServer -- 44 bytes; frame 0x10: ra sp+0x0
// The interface table's server slot +48, when a table is set.
void ROFS_ExecServer(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00566778
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 9976);  // 0x7B26F8
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056678c
        charge(ctx, 3);
        lw(v0, v0, 48);
        jalr(ctx, 0x566790u, v0.u());
    }
    // 0x00566798 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005667A8 ROFS_GetStat -- 40 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// sub_569810, then RFHN_GetStatG.
void ROFS_GetStat(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005667a8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5667B4u, gen::fn_sub_569810_00569810);
    ld(ra, sp, 0x8);
    a0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_RFHN_GetStatG_00565fe8(ctx);  // tail call
}

// 0x005667D0 ROFS_GetFileSiz -- 116 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// sub_569810, then the interface table's slot +52; no table: -203 (rofs_if.c:314).
void ROFS_GetFileSiz(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005667d0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5667DCu, gen::fn_sub_569810_00569810);
    v0 = 0x7B0000;
    a2 = 0x7C0000;
    lw(v0, v0, 9976);  // 0x7B26F8
    a0 = s0;
    a2 = addiu(a2, 28928);  // "ROFS_GetFileSiz"
    a1 = 0;
    a3 = 0;
    t0 = si(-203);
    if (v0 != 0) {
        // 0x00566808
        charge(ctx, 7);
        lw(v0, v0, 52);
        jalr(ctx, 0x56680Cu, v0.u());
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00566828
    charge(ctx, 7);
    a0 = 0x7C0000;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    a0 = addiu(a0, 28776);  // "../../rofs_if.c"
    a1 = 314;
    sp = addiu(sp, 0x10);
    gen::fn_sub_569730_00569730(ctx);  // tail call
}

// 0x005669D8 ROFS_GetVolumeInf -- 128 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// sub_569810, then the interface table's slot +56; no table: -203 (rofs_if.c:387).
void ROFS_GetVolumeInf(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005669d8
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x5669ECu, gen::fn_sub_569810_00569810);
    v0 = 0x7B0000;
    a2 = 0x7C0000;
    lw(v0, v0, 9976);  // 0x7B26F8
    a0 = s0;
    a1 = s1;
    a2 = addiu(a2, 28968);  // "ROFS_GetVolumeInf"
    a3 = 0;
    t0 = si(-203);
    if (v0 != 0) {
        // 0x00566a18
        charge(ctx, 8);
        lw(v0, v0, 56);
        jalr(ctx, 0x566A1Cu, v0.u());
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00566a38
    charge(ctx, 8);
    a0 = 0x7C0000;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a0 = addiu(a0, 28776);  // "../../rofs_if.c"
    ld(ra, sp, 0x10);
    a1 = 387;
    sp = addiu(sp, 0x20);
    gen::fn_sub_569730_00569730(ctx);  // tail call
}

// 0x00566B08 ROFS_SetDir -- 128 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// sub_569810, then the interface table's slot +64 (set directory); no table: -203 (rofs_if.c:424).
void ROFS_SetDir(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00566b08
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x566B1Cu, gen::fn_sub_569810_00569810);
    v0 = 0x7B0000;
    a2 = 0x7C0000;
    lw(v0, v0, 9976);  // 0x7B26F8
    a0 = s0;
    a1 = s1;
    a2 = addiu(a2, 29008);  // "ROFS_SetDir"
    a3 = 0;
    t0 = si(-203);
    if (v0 != 0) {
        // 0x00566b48
        charge(ctx, 8);
        lw(v0, v0, 64);
        jalr(ctx, 0x566B4Cu, v0.u());
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00566b68
    charge(ctx, 8);
    a0 = 0x7C0000;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a0 = addiu(a0, 28776);  // "../../rofs_if.c"
    ld(ra, sp, 0x10);
    a1 = 424;
    sp = addiu(sp, 0x20);
    gen::fn_sub_569730_00569730(ctx);  // tail call
}

// 0x00567478 rfmai_isDvdRomAccess -- 72 bytes; frame 0x10: ra sp+0x0
// 1 when the pfs seek (slot +8) of the image handle to its end (origin 2) returns 0x7FFFFFFF: the whole
//   disc rather than a file. A null handle gives 0.
void rfmai_isDvdRomAccess(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00567478
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0;
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00567488
        charge(ctx, 11);
        v0 = 0x7B0000;
        a1 = 0;
        lw(a3, v0, 9984);  // g_rofs_work
        lw(v1, a3, 56);
        lw(v0, v1, 8);
        a2 = 2;
        jalr(ctx, 0x56749Cu, v0.u());
        v1 = 0x7FFF0000;
        v1 = v1 | 0xFFFF;
        v0 = v0 ^ v1;
        v0 = sltiu(v0, 1);
    }
    // 0x005674b4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00567810 sceLibgcc32GetErxEntries_11 -- 12 bytes; leaf frame (no stack)
// Returns the ROFS version string 0x7C7200 ("ROFS Ver.1.77 ...").
void sceLibgcc32GetErxEntries_11(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00567810
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7C0000;
    v0 = addiu(v0, 29184);  // "\nROFS Ver.1.77 Build:Mar  2 2005 11:30:59\n"
}

// 0x00567820 ROFS_Init -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Keeps the version string in 0x99A0E0, sub_569810, then RFIF_InitOvl.
void ROFS_Init(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00567820
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x56782Cu, gen::fn_sceLibgcc32GetErxEntries_11_00567810);
    v1 = 0x9A0000;
    v1 = addiu(v1, -24352);  // &0x99A0E0
    link(ctx, 0x56783Cu);  // $ra first: the delay slot below depends on it
    sw(v0, v1, 0);
    call(ctx, gen::fn_sub_569810_00569810);
    a0 = s0;
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_RFIF_InitOvl_005662f0(ctx);  // tail call
}

// 0x00567858 RFMAI_InitG -- 660 bytes; frame 0x50: s0 sp+0x0, s6 sp+0x30, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s7 sp+0x38, ra sp+0x40
// ROFS work-area setup from the config a0 {max handles, max volumes, max dirs >= 3, work buffer} and a1:
//   checks (-100), sub_567AF0, the dcf table's init (-203 on failure), the 8-aligned work area (g_rofs_work) cleared
//   for handles+1 (60 B each, from +4236), volumes (52 B) and directory records; the pfs functions (sub_567BE0), three
//   sub_569F60 settings, the 64-aligned sector buffer (+72), every handle's rofs link, the system handle reopened and
//   closed, RSU_Init, ready flag +0 = 1.
void RFMAI_InitG(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00567858
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s6, sp, 0x30);
    s6 = a1;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(s7, sp, 0x38);
    sd(ra, sp, 0x40);
    if (s0 != 0) {
        // 0x0056788c
        charge(ctx, 2);
        if (s6 == 0) {
            goto L_00567894;
        }
        lw(v1, s0, 12);
        // 0x005678a0
        charge(ctx, 2);
        v0 = si(-100);
        if (v1 == 0) {
        L_00567ac0:
            charge(ctx, 1);
            ld(s0, sp, 0x0);
        } else {
            // 0x005678a8
            charge(ctx, 3);
            lw(v1, s0, 0);
            if (i64(v1) <= 0) {
                ld(s0, sp, 0x0);
            } else {
                // 0x005678b4
                charge(ctx, 3);
                lw(v1, s0, 4);
                if (i64(v1) <= 0) {
                    ld(s0, sp, 0x0);
                } else {
                    // 0x005678c0
                    charge(ctx, 4);
                    lw(v1, s0, 8);
                    v1 = slti(v1, 3);
                    if (v1 != 0) {
                        ld(s0, sp, 0x0);
                    } else {
                        // 0x005678d0
                        charge(ctx, 10);
                        jal(ctx, 0x5678D0u, gen::fn_sub_567AF0_00567af0);
                        jal(ctx, 0x5678D8u, gen::fn_sceLibgcc32GetErxEntries_12_0056ad38);
                        s5 = v0;
                        lw(v0, s5, 0);
                        jalr(ctx, 0x5678E8u, v0.u());
                        cc = v0 != 0;  // the condition, before the delay slot changes it
                        v0 = si(-203);
                        if (cc) {
                            goto L_00567ac0;
                        }
                        // 0x005678f8
                        charge(ctx, 60);
                        lw(s3, s0, 8);
                        a0 = si(-8);
                        lw(s2, s0, 4);
                        s7 = 0x7B0000;
                        v0 = sll(s3, 1);
                        lw(s1, s0, 0);
                        v0 = addu(v0, s3);
                        lw(a2, s0, 12);
                        v0 = sll(v0, 4);
                        s0 = sll(s1, 4);
                        v0 = addiu(v0, 76);
                        s0 = subu(s0, s1);
                        mult(v0, v0, s2);
                        v1 = addiu(a2, 7);
                        s0 = sll(s0, 2);
                        v1 = v1 & a0;
                        a2 = subu(v1, a2);
                        s1 = addiu(s1, 1);
                        a0 = v1;
                        s4 = addiu(s7, 9984);  // &g_rofs_work
                        s0 = addu(s0, v0);
                        a1 = 0;
                        s0 = addiu(s0, 4364);
                        sw(v1, s4, 0);  // g_rofs_work
                        s0 = subu(s0, a2);
                        a2 = s0;
                        jal(ctx, 0x56795Cu, gen::fn_memset_00521408);
                        lw(v1, s4, 0);  // g_rofs_work
                        a0 = sll(s1, 4);
                        v0 = sll(s2, 1);
                        a0 = subu(a0, s1);
                        v0 = addu(v0, s2);
                        a0 = sll(a0, 2);
                        v0 = sll(v0, 2);
                        a0 = addu(v1, a0);
                        v0 = addu(v0, s2);
                        a0 = addiu(a0, 4236);
                        v0 = sll(v0, 2);
                        v0 = addu(a0, v0);
                        a2 = addiu(v1, 4236);
                        a3 = addiu(v1, 4296);
                        a1 = 0xC350;
                        sw(a0, v1, 40);
                        sw(v0, v1, 48);
                        sw(s3, v1, 12);
                        sw(s0, v1, 16);
                        sw(a1, v1, 28);
                        sw(a2, v1, 32);
                        sw(a3, v1, 36);
                        sw(zero, v1, 0);
                        sw(s1, v1, 4);
                        sw(s2, v1, 8);
                        sw(zero, v1, 20);
                        sw(zero, v1, 24);
                        link(ctx, 0x5679D0u);  // $ra first: the delay slot below depends on it
                        sw(zero, v1, 44);
                        call(ctx, gen::fn_PFSCVFS_GetPfsTbl_005658a8);
                        a0 = v0;
                        jal(ctx, 0x5679D8u, gen::fn_sub_567BE0_00567be0);
                        if (v0 == 0) {
                            // 0x005679e8
                            charge(ctx, 25);
                            lw(v0, s4, 0);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            sw(s5, v0, 56);
                            sw(s6, v0, 60);
                            sw(zero, v0, 68);
                            link(ctx, 0x567A04u);  // $ra first: the delay slot below depends on it
                            sw(zero, v0, 64);
                            call(ctx, gen::fn_sub_569F60_00569f60);
                            a0 = 0;
                            a1 = 1;
                            a2 = 0;
                            jal(ctx, 0x567A14u, gen::fn_sub_569F60_00569f60);
                            a0 = 0;
                            a1 = 2;
                            a2 = 1;
                            jal(ctx, 0x567A24u, gen::fn_sub_569F60_00569f60);
                            lw(a1, s4, 0);
                            v1 = si(-64);
                            v0 = addiu(a1, 139);
                            lw(a2, a1, 4);
                            v0 = v0 & v1;
                            a0 = addiu(a1, 4236);
                            sw(v0, a1, 72);
                            if (i64(a2) > 0) {
                                // 0x00567a4c
                                charge(ctx, 3);
                                v0 = a1;
                                a1 = a2;
                                for (;;) {
                                    // 0x00567a58
                                    charge(ctx, 7);
                                    a1 = addiu(a1, -1);
                                    sh(zero, a0, 52);
                                    sw(v0, a0, 8);
                                    a0 = addiu(a0, 60);
                                    if (a1 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                            }
                            // 0x00567a74
                            charge(ctx, 19);
                            s0 = addiu(s7, 9984);
                            a1 = 0;
                            lw(v0, s0, 0);
                            a2 = 0;
                            a3 = 0;
                            t0 = 0;
                            link(ctx, 0x567A8Cu);  // $ra first: the delay slot below depends on it
                            lw(a0, v0, 32);
                            call(ctx, gen::fn_RFHN_ReopenHn_00565a78);
                            lw(v1, s0, 0);
                            link(ctx, 0x567A98u);  // $ra first: the delay slot below depends on it
                            lw(a0, v1, 32);
                            call(ctx, gen::fn_sub_565BC0_00565bc0);
                            v0 = 0x7B0000;
                            v0 = addiu(v0, 9992);  // &0x7B2708
                            link(ctx, 0x567AA8u);  // $ra first: the delay slot below depends on it
                            sw(zero, v0, 0);
                            call(ctx, gen::fn_RSU_Init_0056d6e8);
                            lw(a0, s0, 0);
                            v1 = 1;
                            v0 = 0;
                            sw(v1, a0, 0);
                            goto L_00567ac0;
                        }
                        ld(s0, sp, 0x0);
                    }
                }
            }
        }
        // 0x00567ac4 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(s6, sp, 0x30);
        ld(s7, sp, 0x38);
        ld(ra, sp, 0x40);
        sp = addiu(sp, 0x50);
        return;
    }
L_00567894:
    charge(ctx, 2);
    v0 = si(-100);
    goto L_00567ac0;
}

// 0x00567BE0 sub_567BE0 -- 120 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Installs the pfs function table a0 (g_rofs_work+52, RFPFS_SetPfsTbl) and the dcf table (+56); a null
//   table reports -100 (rofs_mai.c:942).
void sub_567BE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00567be0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = a0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    if (v1 == 0) {
        // 0x00567bf4
        charge(ctx, 11);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
        ld(ra, sp, 0x8);
        a2 = addiu(a2, 29376);  // "RFMAI_SetPfsFuncTblG"
        a1 = 942;
        a3 = 0;
        t0 = si(-100);
        sp = addiu(sp, 0x10);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    // 0x00567c20
    charge(ctx, 14);
    s0 = 0x7B0000;
    s0 = addiu(s0, 9984);  // &g_rofs_work
    lw(v0, s0, 0);  // g_rofs_work
    link(ctx, 0x567C2Cu);  // $ra first: the delay slot below depends on it
    sw(v1, v0, 52);
    call(ctx, gen::fn_RFPFS_SetPfsTbl_0056ad28);
    jal(ctx, 0x567C34u, gen::fn_sceLibgcc32GetErxEntries_12_0056ad38);
    lw(v1, s0, 0);  // g_rofs_work
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sw(v0, v1, 56);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x00568710 rfmai_updateHnStat -- 552 bytes; frame 0x50: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, ra sp+0x40
// Polls a busy handle's image read (pfs GetStat, slot +28): 1 -> the transferred bytes (slot +56) must equal
//   the accepted sectors (+44) * 2048, then pos and rd_sct advance, stat 1, req_state 0; 2 -> the partial bytes
//   (+40) = transferred % 2048; 3 -> stat 3, err -202, "read error ?" when error reports are on (sub_56A040);
//   0 -> idle. A null image handle reports -1000 (rofs_mai.c:1502).
void rfmai_updateHnStat(EEContext& ctx) {
    using namespace hg;
    namespace hn = libs14::rofs_hn;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00568710
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0;
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    sd(s3, sp, 0x28);
    sd(s4, sp, 0x30);
    sd(s5, sp, 0x38);
    sd(ra, sp, 0x40);
    if (s0 != 0) {
        // 0x0056873c
        charge(ctx, 3);
        lw(a0, s0, hn::kVol);
        s5 = 0x7B0000;
        if (a0 != 0) {
            // 0x00568748
            charge(ctx, 9);
            lw(s1, a0, 0);
            s3 = addiu(s5, 9984);
            lw(v0, s3, 0);
            lw(v1, v0, 56);
            lw(v0, v1, 28);
            a0 = s1;
            jalr(ctx, 0x56875Cu, v0.u());
            s2 = v0;
            if (s1 == 0) {
                // 0x005688f0
                charge(ctx, 8);
                a0 = 0x7C0000;
                a2 = 0x7C0000;
                a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
                a2 = addiu(a2, 29736);  // "updateHnStat"
                a1 = 1502;
                a3 = 0;
                t0 = si(-1000);
                jal(ctx, 0x568908u, gen::fn_sub_569730_00569730);
            L_00568910:
                charge(ctx, 1);
                v0 = s2;
            } else {
                // 0x0056876c
                charge(ctx, 3);
                s4 = 1;
                v0 = slti(s2, 2);
                if (s2 == s4) {
                    // 0x005687b8
                    charge(ctx, 9);
                    lw(v0, s3, 0);
                    lw(v1, v0, 56);
                    lw(v0, v1, 56);
                    a0 = s1;
                    jalr(ctx, 0x5687C4u, v0.u());
                    lw(a0, s0, hn::kRdAccepted);
                    v1 = sll(a0, 11);
                    cc = v0 != v1;  // the condition, before the delay slot changes it
                    v0 = 3;
                    if (!cc) {
                        // 0x005687dc
                        charge(ctx, 10);
                        lw(v0, s0, hn::kRdSct);
                        lw(v1, s0, hn::kPosSct);
                        v0 = addu(v0, a0);
                        sw(zero, s0, hn::kRdRemBytes);
                        v1 = addu(v1, a0);
                        sw(v0, s0, hn::kRdSct);
                        sw(v1, s0, hn::kPosSct);
                        sh(s2, s0, hn::kStat);
                        sh(zero, s0, hn::kReqState);
                        goto L_00568910;
                    }
                L_00568828:
                    charge(ctx, 4);
                    v1 = si(-202);
                    sh(v0, s0, hn::kStat);
                    sh(v1, s0, hn::kErr);
                L_005688b8:
                    charge(ctx, 4);
                    lw(v0, s5, 9984);
                    lw(v1, v0, 64);
                    a0 = 0x7C0000;
                    if (v1 == 0) {
                        goto L_00568910;
                    }
                    // 0x005688c8
                    charge(ctx, 5);
                    a2 = 0x7C0000;
                    lh(t0, s0, hn::kErr);
                    a0 = addiu(a0, 29352);
                    a2 = addiu(a2, 29736);  // "updateHnStat"
                    a1 = 1496;
                L_005688dc:
                    charge(ctx, 4);
                    a3 = 0;
                    jal(ctx, 0x5688DCu, gen::fn_sub_569730_00569730);
                    v0 = s2;
                } else {
                    // 0x00568778
                    charge(ctx, 2);
                    v1 = 2;
                    if (v0 != 0) {
                        // 0x00568780
                        charge(ctx, 2);
                        v0 = s2 & 0xFF;
                        if (s2 != 0) {
                            // 0x00568788
                            charge(ctx, 2);
                            v1 = 2;
                            goto L_005688b0;
                        }
                        // 0x005687a8
                        charge(ctx, 3);
                        sh(zero, s0, hn::kReqState);
                        sh(zero, s0, hn::kStat);
                        goto L_00568910;
                    }
                    // 0x00568790
                    charge(ctx, 2);
                    v0 = 3;
                    if (s2 == v1) {
                        // 0x00568808
                        charge(ctx, 7);
                        lw(v0, s3, 0);
                        lw(v1, v0, 56);
                        lw(v0, v1, 56);
                        a0 = s1;
                        jalr(ctx, 0x568814u, v0.u());
                        if (i64(v0) < 0) {
                            // 0x00568824
                            charge(ctx, 1);
                            v0 = 3;
                            goto L_00568828;
                        }
                        // 0x00568838
                        charge(ctx, 11);
                        v1 = dsll32(v0, 0);
                        v1 = dsra32(v1, 0);
                        a1 = addiu(v1, 2047);
                        a0 = slti(v1, 0);
                        v0 = v1;
                        if (a0 != 0) v0 = a1;
                        v0 = sra(v0, 11);
                        v0 = sll(v0, 11);
                        v1 = subu(v1, v0);
                        sw(v1, s0, hn::kRdRemBytes);
                        goto L_00568910;
                    }
                    // 0x00568798
                    charge(ctx, 2);
                    cc = s2 == v0;  // the condition, before the delay slot changes it
                    v0 = s2 & 0xFF;
                    if (!cc) {
                        // 0x005687a0
                        charge(ctx, 2);
                        v1 = 2;
                    L_005688b0:
                        charge(ctx, 2);
                        sh(v0, s0, hn::kStat);
                        sh(v1, s0, hn::kReqState);
                        goto L_005688b8;
                    }
                    // 0x00568868
                    charge(ctx, 11);
                    v0 = si(-202);
                    sh(v1, s0, hn::kReqState);
                    sh(v0, s0, hn::kErr);
                    a0 = 0;
                    sh(s2, s0, hn::kStat);
                    a1 = 1;
                    a2 = sp;
                    jal(ctx, 0x568880u, gen::fn_sub_56A040_0056a040);
                    lw(v1, sp, 0x0);
                    v0 = s2;
                    if (v1 == s4) {
                        // 0x00568894
                        charge(ctx, 7);
                        a0 = 0x7C0000;
                        a2 = 0x7C0000;
                        lh(t0, s0, hn::kErr);
                        a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
                        a2 = addiu(a2, 29720);  // "read error ?"
                        a1 = 1484;
                        goto L_005688dc;
                    }
                }
            }
        }
    }
    // 0x00568914 (the shared epilogue, written out on this path)
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

// 0x00568AC0 sub_568AC0 -- 192 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Read watchdog for the wait loops: when g_rofs_work+20 moved more than the limit +28 since the last check
//   (0x99A0D8), the transferred count (slot +56) must have grown since 0x99A0D0, else 0 (stalled); a poll counter
//   0x99A0DC is capped at 0x800 (reset when +20 != 0). Returns 1 to keep waiting.
void sub_568AC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00568ac0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    if (a0 != 0) {
        // 0x00568adc
        charge(ctx, 11);
        v0 = 0x7B0000;
        s2 = 0x9A0000;
        lw(a1, v0, 9984);  // g_rofs_work
        s1 = addiu(s2, -24368);  // &0x99A0D0
        lw(v1, s1, 8);  // 0x99A0D8
        lw(s0, a1, 20);
        lw(v0, a1, 28);
        v1 = subu(s0, v1);
        v0 = sltu(v0, v1);
        v1 = addiu(s2, -24368);  // &0x99A0D0
        if (v0 != 0) {
            // 0x00568b08
            charge(ctx, 9);
            lw(v1, a1, 56);
            lw(v0, v1, 56);
            jalr(ctx, 0x568B10u, v0.u());
            ld(v1, s1, 0);
            a0 = v0;
            v1 = a0 - v1;
            v0 = 0;
            if (i64(v1) > 0) {
                // 0x00568b2c
                charge(ctx, 3);
                sd(a0, s1, 0);
                sw(s0, s1, 8);
                v1 = addiu(s2, -24368);
                goto L_00568b38;
            }
            // 0x00568b68 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(ra, sp, 0x18);
            sp = addiu(sp, 0x20);
            return;
        }
    L_00568b38:
        charge(ctx, 4);
        lw(v0, v1, 12);
        v0 = sltiu(v0, 2049);
        a0 = addiu(s2, -24368);
        if (v0 == 0) {
            // 0x00568b48
            charge(ctx, 2);
            v0 = 0;
            if (s0 != 0) {
                // 0x00568b50
                charge(ctx, 2);
                sw(zero, v1, 12);
                a0 = addiu(s2, -24368);
                goto L_00568b58;
            }
            // 0x00568b68 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(ra, sp, 0x18);
            sp = addiu(sp, 0x20);
            return;
        }
    L_00568b58:
        charge(ctx, 4);
        v0 = 1;
        lw(v1, a0, 12);
        v1 = addiu(v1, 1);
        sw(v1, a0, 12);
    }
    // 0x00568b68 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00568B80 sub_568B80 -- 68 bytes; frame 0x10: ra sp+0x0
// sub_568BC8's 64-bit result clamped to 0x7FFFFFFF; negative results are returned as they are.
void sub_568B80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00568b80
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x568B88u, gen::fn_sub_568BC8_00568bc8);
    v1 = v0;
    a1 = 0x7FFF0000;
    a1 = a1 | 0xFFFF;
    v0 = dsll32(v1, 0);
    v0 = dsra32(v0, 0);
    a0 = slt(a1, v1);
    if (i64(v1) >= 0) {
        // 0x00568bac
        charge(ctx, 3);
        if (a0 != 0) v1 = a1;
        v0 = dsll32(v1, 0);
        v0 = dsra32(v0, 0);
    }
    // 0x00568bb8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00569538 RFMAI_ReadWG -- 456 bytes; frame 0x40: s1 sp+0x18, s2 sp+0x20, s0 sp+0x10, s3 sp+0x28, ra sp+0x30
// Synchronous sector read through the system handle: argument checks (-100, rofs_mai.c:2028 / 2031),
//   RFHN_ReopenHn(lba, sectors), RFHN_ReqRdG, RFHN_WaitCompleteReq between sub_569700 / sub_569718, then the system
//   handle is closed; failures report through sub_569730 when sub_56A040 says reports are on (-200, the request's
//   or the wait's error).
void RFMAI_ReadWG(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00569538
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x18);
    s1 = a2;
    sd(s2, sp, 0x20);
    s2 = a3;
    sd(s0, sp, 0x10);
    sd(s3, sp, 0x28);
    sd(ra, sp, 0x30);
    if (a0 != 0) {
        // 0x0056955c
        charge(ctx, 2);
        if (s2 == 0) {
            goto L_00569564;
        }
        lw(v0, a0, 0);
        // 0x00569580
        charge(ctx, 2);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 0x7B0000;
        if (cc) {
            // 0x005695b0
            charge(ctx, 11);
            t0 = a0;
            s3 = addiu(v0, 9984);
            a3 = sll(s1, 11);
            lw(v0, s3, 0);
            a2 = a1;
            a1 = 0;
            link(ctx, 0x5695C8u);  // $ra first: the delay slot below depends on it
            lw(a0, v0, 32);
            call(ctx, gen::fn_RFHN_ReopenHn_00565a78);
            s0 = v0;
            a1 = s1;
            if (s0 != 0) {
                // 0x00569628
                charge(ctx, 6);
                a2 = s2;
                a0 = s0;
                jal(ctx, 0x56962Cu, gen::fn_RFHN_ReqRdG_00565e10);
                s1 = v0;
                if (i64(s1) < 0) {
                    // 0x00569640
                    charge(ctx, 11);
                    lw(v0, s3, 0);
                    link(ctx, 0x569644u);  // $ra first: the delay slot below depends on it
                    lw(a0, v0, 32);
                    call(ctx, gen::fn_sub_565BC0_00565bc0);
                    a0 = 0;
                    a1 = 2;
                    a2 = sp;
                    jal(ctx, 0x569654u, gen::fn_sub_56A040_0056a040);
                    v1 = 1;
                    lw(v0, sp, 0x0);
                    cc = v0 != v1;  // the condition, before the delay slot changes it
                    v0 = s1;
                    if (cc) {
                        goto L_005696e4;
                    }
                    // 0x0056966c
                    charge(ctx, 7);
                    a0 = 0x7C0000;
                    a2 = 0x7C0000;
                    a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
                    a2 = addiu(a2, 29936);  // "RFHN_ReqRdG"
                    t0 = s1;
                    a1 = 2056;
                    goto L_005696cc;
                }
                // 0x00569688
                charge(ctx, 12);
                a0 = s0;
                jal(ctx, 0x569688u, gen::fn_sub_569700_00569700);
                a0 = s0;
                jal(ctx, 0x569690u, gen::fn_RFHN_WaitCompleteReq_005658b8);
                a0 = s0;
                s2 = v0;
                jal(ctx, 0x56969Cu, gen::fn_sub_569718_00569718);
                lw(v0, s3, 0);
                link(ctx, 0x5696A8u);  // $ra first: the delay slot below depends on it
                lw(a0, v0, 32);
                call(ctx, gen::fn_sub_565BC0_00565bc0);
                a0 = 0x7C0000;
                if (s2 == 0) {
                    // 0x005696e0
                    charge(ctx, 1);
                    v0 = s1;
                L_005696e4:
                    charge(ctx, 1);
                    ld(s0, sp, 0x10);
                } else {
                    // 0x005696b8
                    charge(ctx, 5);
                    a2 = 0x7C0000;
                    a0 = addiu(a0, 29352);
                    a2 = addiu(a2, 29952);  // "RFHN_WaitCompleteReq"
                    t0 = s2;
                    a1 = 2075;
                L_005696cc:
                    charge(ctx, 4);
                    a3 = 0;
                    jal(ctx, 0x5696CCu, gen::fn_sub_569730_00569730);
                    ld(s0, sp, 0x10);
                }
            } else {
                // 0x005695dc
                charge(ctx, 8);
                a0 = 0;
                a1 = 2;
                a2 = sp;
                jal(ctx, 0x5695E4u, gen::fn_sub_56A040_0056a040);
                v1 = 1;
                lw(v0, sp, 0x0);
                if (v0 != v1) {
                    v0 = si(-200);
                    goto L_005696e4;
                }
                // 0x005695fc
                charge(ctx, 10);
                a0 = 0x7C0000;
                a2 = 0x7C0000;
                a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
                a2 = addiu(a2, 29920);  // "RFMAI_ReadWG"
                a1 = 2040;
                a3 = 0;
                t0 = si(-200);
                jal(ctx, 0x569614u, gen::fn_sub_569730_00569730);
                ld(s0, sp, 0x10);
            }
        } else {
            // 0x00569588
            charge(ctx, 5);
            a0 = 0x7C0000;
            a2 = 0x7C0000;
            a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
            a2 = addiu(a2, 29920);  // "RFMAI_ReadWG"
            a1 = 2031;
        L_0056959c:
            charge(ctx, 5);
            a3 = 0;
            t0 = si(-100);
            jal(ctx, 0x5695A0u, gen::fn_sub_569730_00569730);
            ld(s0, sp, 0x10);
        }
        // 0x005696e8 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s1, sp, 0x18);
        ld(s2, sp, 0x20);
        ld(s3, sp, 0x28);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        return;
    }
L_00569564:
    charge(ctx, 6);
    a0 = 0x7C0000;
    a2 = 0x7C0000;
    a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
    a2 = addiu(a2, 29920);  // "RFMAI_ReadWG"
    a1 = 2028;
    goto L_0056959c;
}

// 0x0056A530 dcfInit -- 8 bytes; leaf frame (no stack)
// Returns 0.
void dcfInit(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0056a530
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0056A540 dcfSeek -- 96 bytes; frame 0x10: ra sp+0x0
// The pfs table's (g_rofs_pfs_tbl) seek slot +24; no table or slot: -203 (rofs_pfs.c:155).
void dcfSeek(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056a540
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10248);  // g_rofs_pfs_tbl
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056a554
        charge(ctx, 3);
        lw(v0, v0, 24);
        if (v0 == 0) {
            a0 = 0x7C0000;
            goto L_0056a57c;
        }
        // 0x0056a560
        charge(ctx, 5);
        jalr(ctx, 0x56A560u, v0.u());
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0056a578
    charge(ctx, 1);
    a0 = 0x7C0000;
L_0056a57c:
    charge(ctx, 9);
    a2 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 30216);
    a2 = addiu(a2, 30240);  // "dcfSeek"
    a1 = 155;
    a3 = 0;
    t0 = si(-203);
    sp = addiu(sp, 0x10);
    gen::fn_sub_569730_00569730(ctx);  // tail call
}

// 0x0056A600 dcfReqRd -- 96 bytes; frame 0x10: ra sp+0x0
// The pfs table's read-request slot +32; no table or slot: -203 (rofs_pfs.c:184).
void dcfReqRd(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056a600
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10248);  // g_rofs_pfs_tbl
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056a614
        charge(ctx, 3);
        lw(v0, v0, 32);
        if (v0 == 0) {
            a0 = 0x7C0000;
            goto L_0056a63c;
        }
        // 0x0056a620
        charge(ctx, 5);
        jalr(ctx, 0x56A620u, v0.u());
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0056a638
    charge(ctx, 1);
    a0 = 0x7C0000;
L_0056a63c:
    charge(ctx, 9);
    a2 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 30216);
    a2 = addiu(a2, 30256);  // "dcfReqRd"
    a1 = 184;
    a3 = 0;
    t0 = si(-203);
    sp = addiu(sp, 0x10);
    gen::fn_sub_569730_00569730(ctx);  // tail call
}

// 0x0056A698 dcfExecServer -- 52 bytes; frame 0x10: ra sp+0x0
// The pfs table's server slot +0, when set.
void dcfExecServer(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056a698
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10248);  // g_rofs_pfs_tbl
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056a6ac
        charge(ctx, 3);
        lw(v0, v0, 0);
        if (v0 != 0) {
            // 0x0056a6b8
            charge(ctx, 2);
            jalr(ctx, 0x56A6B8u, v0.u());
            goto L_0056a6c0;
        }
        ld(ra, sp, 0x0);
        // 0x0056a6c4 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_0056a6c0:
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    // 0x0056a6c4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x0056A6D0 dcfGetStat -- 96 bytes; frame 0x10: ra sp+0x0
// The pfs table's status slot +44; no table or slot: -203 reported (rofs_pfs.c:224) and 3 (error) returned.
void dcfGetStat(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056a6d0
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10248);  // g_rofs_pfs_tbl
    sd(ra, sp, 0x0);
    if (v0 == 0) {
        // 0x0056a700
        charge(ctx, 1);
        a0 = 0x7C0000;
    L_0056a704:
        charge(ctx, 9);
        a2 = 0x7C0000;
        a0 = addiu(a0, 30216);
        a2 = addiu(a2, 30272);  // "dcfGetStat"
        a1 = 224;
        a3 = 0;
        t0 = si(-203);
        jal(ctx, 0x56A718u, gen::fn_sub_569730_00569730);
        v0 = 3;
        ld(ra, sp, 0x0);
    } else {
        // 0x0056a6e4
        charge(ctx, 3);
        lw(v0, v0, 44);
        if (v0 == 0) {
            a0 = 0x7C0000;
            goto L_0056a704;
        }
        // 0x0056a6f0
        charge(ctx, 4);
        jalr(ctx, 0x56A6F0u, v0.u());
        ld(ra, sp, 0x0);
    }
    // 0x0056a728 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x0056A730 dcfGetSctLen -- 96 bytes; frame 0x10: ra sp+0x0
// The pfs table's sector-length slot +48; no table or slot: -203 (rofs_pfs.c:239).
void dcfGetSctLen(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056a730
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10248);  // g_rofs_pfs_tbl
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056a744
        charge(ctx, 3);
        lw(v0, v0, 48);
        if (v0 == 0) {
            a0 = 0x7C0000;
            goto L_0056a76c;
        }
        // 0x0056a750
        charge(ctx, 5);
        jalr(ctx, 0x56A750u, v0.u());
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0056a768
    charge(ctx, 1);
    a0 = 0x7C0000;
L_0056a76c:
    charge(ctx, 9);
    a2 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 30216);
    a2 = addiu(a2, 30288);  // "dcfGetSctLen"
    a1 = 239;
    a3 = 0;
    t0 = si(-203);
    sp = addiu(sp, 0x10);
    gen::fn_sub_569730_00569730(ctx);  // tail call
}

// 0x0056A790 dcfGetNumTr -- 96 bytes; frame 0x10: ra sp+0x0
// The pfs table's transferred-count slot +56; no table or slot: -203 (rofs_pfs.c:253).
void dcfGetNumTr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056a790
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10248);  // g_rofs_pfs_tbl
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056a7a4
        charge(ctx, 3);
        lw(v0, v0, 56);
        if (v0 == 0) {
            a0 = 0x7C0000;
            goto L_0056a7cc;
        }
        // 0x0056a7b0
        charge(ctx, 5);
        jalr(ctx, 0x56A7B0u, v0.u());
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0056a7c8
    charge(ctx, 1);
    a0 = 0x7C0000;
L_0056a7cc:
    charge(ctx, 9);
    a2 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 30216);
    a2 = addiu(a2, 30304);  // "dcfGetNumTr"
    a1 = 253;
    a3 = 0;
    t0 = si(-203);
    sp = addiu(sp, 0x10);
    gen::fn_sub_569730_00569730(ctx);  // tail call
}

// 0x0056A7F0 sub_56A7F0 -- 112 bytes; frame 0x10: ra sp+0x0
// The transferred count, 64-bit slot +104 when set, else dcfGetNumTr; no table or a negative count: -203
//   (rofs_pfs.c:284).
void sub_56A7F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056a7f0
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10248);  // g_rofs_pfs_tbl
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056a804
        charge(ctx, 3);
        lw(v0, v0, 104);
        if (v0 == 0) {
            // 0x0056a820
            charge(ctx, 3);
            jal(ctx, 0x56A820u, gen::fn_dcfGetNumTr_0056a790);
            v1 = v0;
        } else {
            // 0x0056a810
            charge(ctx, 4);
            jalr(ctx, 0x56A810u, v0.u());
            v1 = v0;
        }
        // 0x0056a82c
        charge(ctx, 2);
        v0 = v1;
        if (i64(v1) < 0) {
            goto L_0056a834;
        }
        // 0x0056a854 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_0056a834:
    charge(ctx, 8);
    a0 = 0x7C0000;
    a2 = 0x7C0000;
    a0 = addiu(a0, 30216);  // "../../rofs_pfs.c"
    a2 = addiu(a2, 30320);  // "dcfGetNumTr64"
    a1 = 284;
    a3 = 0;
    t0 = si(-203);
    jal(ctx, 0x56A84Cu, gen::fn_sub_569730_00569730);
    // 0x0056a854 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056A860 dcfReqRdBlk -- 380 bytes; frame 0x30: s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s0 sp+0x0, ra sp+0x28
// Block read request: null handle / buffer -100; the pfs sector length (dcfGetSctLen, <= 0: -202), a seek to
//   the block (rfpfs_parentSeek; its error reported), then dcfReqRd of sectors * 2048 / sctlen; a positive result
//   is returned in 2048-byte blocks.
void dcfReqRdBlk(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056a860
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s4, sp, 0x20);
    s4 = a2;
    sd(s0, sp, 0x0);
    a3 = 0;
    sd(ra, sp, 0x28);
    a1 = 299;
    if (s1 != 0) {
        // 0x0056a898
        charge(ctx, 2);
        if (s3 == 0) {
            goto L_0056a8a0;
        }
        // 0x0056a8d8
        charge(ctx, 11);
        jal(ctx, 0x56A8D8u, gen::fn_dcfGetSctLen_0056a730);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        s0 = v0;
        a0 = addiu(a0, 30216);  // "../../rofs_pfs.c"
        a2 = addiu(a2, 30288);  // "dcfGetSctLen"
        a1 = 304;
        a3 = 0;
        t0 = si(-202);
        if (i64(s0) <= 0) {
            // 0x0056a904
            charge(ctx, 8);
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(s4, sp, 0x20);
            ld(ra, sp, 0x28);
            sp = addiu(sp, 0x30);
            gen::fn_sub_569730_00569730(ctx);  // tail call
            return;
        }
        // 0x0056a928
        charge(ctx, 11);
        a1 = s2;
        a0 = s1;
        a2 = s0;
        jal(ctx, 0x56A930u, gen::fn_rfpfs_parentSeek_0056acb8);
        v1 = sll(s4, 11);
        a0 = s1;
        a2 = s3;
        t0 = v0;
        a1 = 310;
        a3 = 0;
        if (v0 != 0) {
            // 0x0056a954
            charge(ctx, 12);
            a0 = 0x7C0000;
            a2 = 0x7C0000;
            ld(s0, sp, 0x0);
            a0 = addiu(a0, 30216);  // "../../rofs_pfs.c"
            ld(s1, sp, 0x8);
            a2 = addiu(a2, 30352);  // "parentSeek"
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(s4, sp, 0x20);
            ld(ra, sp, 0x28);
            sp = addiu(sp, 0x30);
            gen::fn_sub_569730_00569730(ctx);  // tail call
            return;
        }
        // 0x0056a988
        charge(ctx, 3);
        div(v1, s0);
        if (s0 == 0) {
            brk(ctx, 0x56A990u, 0x7u);
        }
        // 0x0056a994
        charge(ctx, 6);
        mflo(a1);
        jal(ctx, 0x56A998u, gen::fn_dcfReqRd_0056a600);
        v1 = v0;
        mult(a2, v1, s0);
        if (i64(v1) > 0) {
            // 0x0056a9ac
            charge(ctx, 4);
            v0 = slti(a2, 0);
            v1 = addiu(a2, 2047);
            if (v0 != 0) a2 = v1;
            v0 = sra(a2, 11);
        }
        // 0x0056a9bc (the shared epilogue, written out on this path)
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
L_0056a8a0:
    charge(ctx, 13);
    a0 = 0x7C0000;
    a2 = 0x7C0000;
    ld(s0, sp, 0x0);
    a0 = addiu(a0, 30216);  // "../../rofs_pfs.c"
    ld(s1, sp, 0x8);
    a2 = addiu(a2, 30336);  // "dcfReqRdBlk"
    ld(s2, sp, 0x10);
    t0 = si(-100);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    gen::fn_sub_569730_00569730(ctx);  // tail call
}

// 0x0056AA98 dcfReqRdCda -- 40 bytes; frame 0x10: ra sp+0x0
// dcfReqRdBlk(handle, lba + offset, sectors, buf): the CVM data offset a0 is added here.
void dcfReqRdCda(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056aa98
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = addu(a2, a0);
    sd(ra, sp, 0x0);
    a0 = a1;
    a2 = a3;
    a3 = t0;
    ld(ra, sp, 0x0);
    a1 = v0;
    sp = addiu(sp, 0x10);
    gen::fn_dcfReqRdBlk_0056a860(ctx);  // tail call
}

// 0x0056AC28 rfpfs_waitRdComplete -- 140 bytes; frame 0x30: s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, ra sp+0x20
// Waits for the image read: sub_568A78, then while dcfGetStat says busy (2): dcfExecServer, RFPFS_PfsWait
//   and the watchdog (sub_568AC0; stalled -> the handle's req_state = 2, 0). Done (1) returns 1, anything else 0.
void rfpfs_waitRdComplete(EEContext& ctx) {
    using namespace hg;
    namespace hn = libs14::rofs_hn;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0056ac28
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = 1;
    sd(s3, sp, 0x18);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    s3 = 2;
    jal(ctx, 0x56AC48u, gen::fn_sub_568A78_00568a78);
    for (;;) {
        // 0x0056ac50
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x56AC50u, gen::fn_dcfGetStat_0056a6d0);
        s0 = v0;
        if (s0 == s2) {
            ld(s0, sp, 0x0);
        } else {
            // 0x0056ac64
            charge(ctx, 2);
            v0 = 0;
            if (s0 == 0) {
                goto L_0056ac98;
            }
            // 0x0056ac6c
            charge(ctx, 2);
            if (s0 == s3) {
                // 0x0056ac74
                charge(ctx, 8);
                jal(ctx, 0x56AC74u, gen::fn_dcfExecServer_0056a698);
                jal(ctx, 0x56AC7Cu, gen::fn_RFPFS_PfsWait_0056ab78);
                a0 = s1;
                jal(ctx, 0x56AC84u, gen::fn_sub_568AC0_00568ac0);
                cc = v0 == s2;  // the condition, before the delay slot changes it
                v0 = 0;
                if (!cc) {
                    goto L_0056ac94_5;
                }
                backedge(ctx);
                continue;
            }
            ld(s0, sp, 0x0);
        }
        break;
    }
    // 0x0056ac9c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    return;
L_0056ac94_5:
    charge(ctx, 1);
    sh(s0, s1, hn::kReqState);
L_0056ac98:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0056ac9c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0056ACB8 rfpfs_parentSeek -- 112 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Seeks the image to lba * 2048 / sctlen (64-bit __divdi3) with dcfSeek: 0 when it lands, -205 when not,
//   -100 for a negative lba.
void rfpfs_parentSeek(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056acb8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    a1 = a2;
    a0 = v1;
    sd(s0, sp, 0x0);
    a0 = dsll(a0, 11);
    sd(ra, sp, 0x10);
    v0 = si(-100);
    if (i64(v1) >= 0) {
        // 0x0056ace4
        charge(ctx, 12);
        jal(ctx, 0x56ACE4u, gen::fn___divdi3_0052eeb0);
        a2 = 0;
        s0 = dsll32(v0, 0);
        s0 = dsra32(s0, 0);
        a0 = s1;
        a1 = s0;
        jal(ctx, 0x56ACFCu, gen::fn_dcfSeek_0056a540);
        v1 = si(-205);
        v0 = v0 ^ s0;
        if (v0 == 0) v1 = 0;
        v0 = v1;
    }
    // 0x0056ad14 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0056AD38 sceLibgcc32GetErxEntries_12 -- 12 bytes; leaf frame (no stack)
// Returns the dcf function table g_rofs_dcf_tbl (0x7C75C8).
void sceLibgcc32GetErxEntries_12(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0056ad38
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7C0000;
    v0 = addiu(v0, 30152);  // &g_rofs_dcf_tbl
}

// 0x0056C8B8 sceLibgcc32GetErxEntries_13 -- 12 bytes; leaf frame (no stack)
// Returns 0x7B2878.
void sceLibgcc32GetErxEntries_13(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0056c8b8
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    v0 = addiu(v0, 10360);  // &0x7B2878
}

// 0x0056DDE0 sub_56DDE0 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk to SRD_ExecServer.
void sub_56DDE0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0056dde0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_SRD_ExecServer_00558500(ctx);  // tail call
}

// 0x00570248 sub_570248 -- 172 bytes; leaf frame (no stack)
// MPEG picture sizes from the sequence header record: width / height = the 12-bit values (+4 / +8) with the
//   extension bits (+80 / +84) << 12, macroblock columns (w + 15) >> 4, rows (h + 15) >> 4 when progressive (+72 == 1)
//   else (h + 31) >> 5, doubled for a frame picture (+280 == 3); the sizes in pixels and their halves at +948...
void sub_570248(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00570248
    enter(ctx, 19);  // entry check point + this block's cycles
    t1 = a0;
    t0 = 1;
    lw(a0, t1, 80);
    lw(v1, t1, 4);
    lw(v0, t1, 84);
    a0 = sll(a0, 12);
    lw(a2, t1, 8);
    a0 = a0 | v1;
    v0 = sll(v0, 12);
    v1 = addiu(a0, 15);
    a2 = v0 | a2;
    lw(a3, t1, 72);
    a1 = addiu(a2, 15);
    v1 = srl(v1, 4);
    a1 = srl(a1, 4);
    sw(v1, t1, 716);
    sw(a0, t1, 708);
    sw(a2, t1, 712);
    if (a3 != t0) {
        // 0x005702a0
        charge(ctx, 4);
        lw(v1, t1, 280);
        v0 = 3;
        cc = v1 != v0;  // the condition, before the delay slot changes it
        v0 = addiu(a2, 31);
        if (cc) {
            // 0x005702c0
            charge(ctx, 1);
            v0 = srl(v0, 5);
        } else {
            // 0x005702b0
            charge(ctx, 3);
            v0 = srl(v0, 5);
            v0 = sll(v0, 1);
        }
        // 0x005702c4
        charge(ctx, 1);
        sw(v0, t1, 720);
    } else {
        // 0x00570294
        charge(ctx, 2);
        sw(a1, t1, 720);
    }
    // 0x005702c8 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    lw(v1, t1, 716);
    lw(a0, t1, 720);
    v1 = sll(v1, 4);
    a0 = sll(a0, 4);
    a1 = sra(v1, 1);
    v0 = sra(a0, 1);
    sw(a1, t1, 956);
    sw(v0, t1, 960);
    sw(v1, t1, 948);
    sw(a0, t1, 952);
}

// 0x005703B8 sub_5703B8 -- 8 bytes; leaf frame (no stack)
// Empty (returns at once).
void sub_5703B8(EEContext& ctx) {
    using namespace hg;
    // 0x005703b8
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x00593140 sub_593140 -- 192 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// Sofdec: takes a frame (sub_593B38) for the handle; fills it (sub_593200), copies the picture's two words
//   (+20 / +24) into the handle (+4012 / +4016) and checks it (sub_59AE88); in mode 2 (+88) the frame's +88 and *a2
//   get sub_593FD0. No frame or a failed check: *a1 = 0.
void sub_593140(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00593140
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    s3 = addiu(s0, 3376);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    s4 = a2;
    jal(ctx, 0x593168u, gen::fn_sub_593B38_00593b38);
    s2 = v0;
    a0 = s0;
    a1 = s2;
    a2 = s1;
    if (s2 != 0) {
        // 0x00593184
        charge(ctx, 12);
        jal(ctx, 0x593184u, gen::fn_sub_593200_00593200);
        lw(v0, s1, 0);
        a0 = s0;
        lw(a2, v0, 20);
        a1 = v0;
        sw(a2, s3, 636);
        lw(v1, v0, 24);
        link(ctx, 0x5931A4u);  // $ra first: the delay slot below depends on it
        sw(v1, s3, 640);
        call(ctx, gen::fn_sub_59AE88_0059ae88);
        v1 = 2;
        if (v0 == 0) {
            goto L_005931b4;
        }
        // 0x005931c0
        charge(ctx, 3);
        lw(v0, s0, 88);
        if (v0 != v1) {
            v0 = 0;
        } else {
            // 0x005931cc
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x5931CCu, gen::fn_sub_593FD0_00593fd0);
            sw(v0, s2, 88);
            sw(v0, s4, 0);
            v0 = 0;
        }
        // 0x005931e0 (the shared epilogue, written out on this path)
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
L_005931b4:
    charge(ctx, 2);
    sw(zero, s1, 0);
    // 0x005931e0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00593408 sub_593408 -- 96 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// sub_593468 under the SFD lock (sub_58C100 / sub_58C118).
void sub_593408(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00593408
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(s1, sp, 0x18);
    s1 = a2;
    sd(s2, sp, 0x20);
    s2 = a0;
    sd(ra, sp, 0x28);
    a0 = sp;
    jal(ctx, 0x593428u, gen::fn_sub_58C100_0058c100);
    a0 = s2;
    a1 = s0;
    a2 = s1;
    jal(ctx, 0x593438u, gen::fn_sub_593468_00593468);
    a0 = sp;
    s0 = v0;
    jal(ctx, 0x593444u, gen::fn_sub_58C118_0058c118);
    v0 = s0;
    ld(s1, sp, 0x18);
    ld(s0, sp, 0x10);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00595868 sub_595868 -- 140 bytes; frame 0x10: ra sp+0x0
// Reference count at +84: a1 1 adds (the first user calls sub_5958F8), 0 releases (the last one calls it),
//   2 calls it when the status +72 is 4; returns 0 otherwise.
void sub_595868(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00595868
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = a1;
    v0 = 1;
    sd(ra, sp, 0x0);
    v1 = a0;
    a3 = 0;
    if (a2 == v0) {
        // 0x005958b0
        charge(ctx, 4);
        lw(v0, v1, 84);
        v0 = addiu(v0, 1);
        sw(v0, v1, 84);
        if (v0 == a2) {
            // 0x005958c0
            charge(ctx, 2);
        L_005958d8:
            charge(ctx, 3);
            jal(ctx, 0x5958D8u, gen::fn_sub_5958F8_005958f8);
            a3 = v0;
        }
    L_005958e4:
        charge(ctx, 1);
        ld(ra, sp, 0x0);
    L_005958e8:
        charge(ctx, 1);
        v0 = a3;
    } else {
        // 0x00595884
        charge(ctx, 2);
        if (a2 == 0) {
            lw(v0, v1, 84);
            // 0x005958c8
            charge(ctx, 3);
            v0 = addiu(v0, -1);
            sw(v0, v1, 84);
            if (v0 == 0) {
                // 0x005958d4
                charge(ctx, 1);
                a1 = 0;
                goto L_005958d8;
            }
            goto L_005958e4;
        }
        // 0x0059588c
        charge(ctx, 3);
        v0 = 2;
        ld(ra, sp, 0x0);
        if (a2 != v0) {
            goto L_005958e8;
        }
        // 0x00595898
        charge(ctx, 4);
        lw(v1, v1, 72);
        v0 = 4;
        cc = v1 != v0;  // the condition, before the delay slot changes it
        v0 = a3;
        if (!cc) {
            // 0x005958a8
            charge(ctx, 2);
            goto L_005958d8;
        }
    }
    // 0x005958ec (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x005959E0 sub_5959E0 -- 112 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// SFD entry point: while sub_58C060 reports an error state, error -16776892 (sub_58BE40); else sub_59B398
//   and sub_588360, 0.
void sub_5959E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005959e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x5959F4u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x00595a08
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x144;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00595a20
    charge(ctx, 12);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x595A24u, gen::fn_sub_59B398_0059b398);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x595A30u, gen::fn_sub_588360_00588360);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00596760 sub_596760 -- 184 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Input-buffer full check: the current input record (116-byte records at +4896, index +8136), its SJ's line-1
//   count (vtable +36) >= 80 % of the record's capacity (+12) or >= sub_599408(handle, 70).
void sub_596760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00596760
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(v0, s1, 8136);
    s0 = sll(v0, 3);
    s0 = subu(s0, v0);
    s0 = sll(s0, 2);
    s0 = addu(s0, v0);
    s0 = sll(s0, 2);
    s0 = addu(s1, s0);
    s0 = addiu(s0, 4896);
    lw(a0, s0, 4);
    lw(v1, a0, 0);
    lw(v0, v1, 36);
    a1 = 1;
    jalr(ctx, 0x5967A4u, v0.u());
    a0 = s1;
    lw(a2, s0, 12);
    s2 = v0;
    v1 = 100;
    a1 = 70;
    v0 = sll(a2, 2);
    if (v1 == 0) {
        brk(ctx, 0x5967C8u, 0x7u);
    }
    // 0x005967cc
    charge(ctx, 7);
    v0 = addu(v0, a2);
    v0 = sll(v0, 4);
    div(v0, v1);
    mflo(v0);
    v0 = slt(s2, v0);
    if (v0 == 0) {
        v0 = 1;
    } else {
        // 0x005967e8
        charge(ctx, 5);
        jal(ctx, 0x5967E8u, gen::fn_sub_599408_00599408);
        v1 = slt(s2, v0);
        v0 = 0;
        if (v1 == 0) {
            // 0x005967fc
            charge(ctx, 1);
            v0 = 1;
        }
    }
    // 0x00596800 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00596B68 sub_596B68 -- 188 bytes; frame 0x30: s0 sp+0x20, ra sp+0x28
// Under the SFD lock, classifies the 8 open handles (0x7B4774) by status +72 (0 idle; 6 or negative: ended;
//   else running) and stores the overall state in 0x7B4708: 1 any running, 2 only ended, 0 none.
void sub_596B68(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00596b68
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x20);
    sd(ra, sp, 0x28);
    a0 = addiu(sp, 0x10);
    jal(ctx, 0x596B74u, gen::fn_sub_58C100_0058c100);
    sw(zero, sp, 0x0);
    v0 = 0x7B0000;
    sw(zero, sp, 0x4);
    a2 = addiu(v0, 18292);  // &0x7B4774
    sw(zero, sp, 0x8);
    a3 = 6;
    a1 = 7;
    lw(v0, a2, 0);  // 0x7B4774
    for (;;) {
        // 0x00596ba0
        charge(ctx, 2);
        a2 = addiu(a2, 4);
        if (v0 != 0) {
            // 0x00596ba8
            charge(ctx, 3);
            lw(v0, v0, 72);
            s0 = 0;
            if (v0 != 0) {
                // 0x00596bb4
                charge(ctx, 2);
                s0 = 2;
                if (v0 != a3) {
                    // 0x00596bbc
                    charge(ctx, 2);
                    s0 = 1;
                    if (i64(v0) < 0) {
                        // 0x00596bc4
                        charge(ctx, 1);
                        s0 = 2;
                    }
                }
            }
            // 0x00596bc8
            charge(ctx, 5);
            v0 = sll(s0, 2);
            a0 = addu(sp, v0);
            lw(v1, a0, 0);
            v1 = addiu(v1, 1);
            sw(v1, a0, 0);
        }
        // 0x00596bdc
        charge(ctx, 3);
        a1 = addiu(a1, -1);
        if (i64(a1) < 0) {
            break;
        }
        lw(v0, a2, 0);
        backedge(ctx);
    }
    // 0x00596be8
    charge(ctx, 3);
    lw(v0, sp, 0x4);
    s0 = 1;
    if (v0 == 0) {
        // 0x00596bf4
        charge(ctx, 3);
        lw(v0, sp, 0x8);
        s0 = 2;
        if (v0 == 0) s0 = 0;
    }
    // 0x00596c00
    charge(ctx, 9);
    v0 = 0x7B0000;
    a0 = addiu(sp, 0x10);
    link(ctx, 0x596C08u);  // $ra first: the delay slot below depends on it
    sw(s0, v0, 18184);
    call(ctx, gen::fn_sub_58C118_0058c118);
    ld(ra, sp, 0x28);
    v0 = s0;
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00597878 sub_597878 -- 108 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// SFD parameter 9 (sub_59BC20(handle, 0, 9, a1, 0)); error -16776908 while sub_58C060 reports one.
void sub_597878(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00597878
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x59788Cu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    a3 = s0;
    a1 = a1 | 0x134;
    a2 = 9;
    t0 = 0;
    if (v0 != 0) {
        // 0x005978b0
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x005978c8
    charge(ctx, 7);
    a0 = s1;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    a1 = 0;
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_59BC20_0059bc20(ctx);  // tail call
}

// 0x005978E8 sub_5978E8 -- 124 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// SFD parameter 10 (sub_59BC20(handle, 0, 10, a1, a2)); error -16776907 while sub_58C060 reports one.
void sub_5978E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005978e8
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x597904u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = s1;
    a3 = s0;
    t0 = s2;
    a1 = a1 | 0x135;
    a2 = 10;
    if (v0 == 0) {
        // 0x00597948
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        a1 = 0;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_59BC20_0059bc20(ctx);  // tail call
        return;
    }
    // 0x00597928
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    a0 = 0;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x00597A18 sub_597A18 -- 136 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10, f20 sp+0x18
// Clock sample: +14216 = sub_59B3A8, +14224 = sub_59B458, +14232 = +2408; when the time moved since +14208,
//   the rate (+14224 * +2408) / (+14216 - +14208) as a float at +14236 (__muldi3, __floatdisf).
void sub_597A18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f20{ctx, 20};
    // 0x00597a18
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    link(ctx, 0x597A2Cu);  // $ra first: the delay slot below depends on it
    swc1(f20, sp, 0x18);
    call(ctx, gen::fn_sub_59B3A8_0059b3a8);
    link(ctx, 0x597A34u);  // $ra first: the delay slot below depends on it
    sd(v0, s0, 14216);
    call(ctx, gen::fn_sub_59B458_0059b458);
    lw(a2, s0, 2408);
    ld(a0, s0, 14216);
    a1 = v0;
    ld(v1, s0, 14208);
    sw(a2, s0, 14232);
    s1 = a0 - v1;
    sd(v0, s0, 14224);
    if (s1 != 0) {
        // 0x00597a5c
        charge(ctx, 11);
        a0 = a2;
        jal(ctx, 0x597A5Cu, gen::fn___muldi3_0052ea78);
        a0 = v0;
        jal(ctx, 0x597A64u, gen::fn___floatdisf_0052eb60);
        a0 = s1;
        mov_s(f20, f0);
        jal(ctx, 0x597A70u, gen::fn___floatdisf_0052eb60);
        div_s(f20, f20, f0);
        swc1(f20, s0, 14236);
    }
    // 0x00597a88 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005985F8 sub_5985F8 -- 20 bytes; leaf frame (no stack)
// *a1 = (*a0 == 1).
void sub_5985F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x005985f8
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, 0);
    v1 = v0 ^ 0x1;
    if (v1 != 0) v0 = 0;
    sw(v0, a1, 0);
}

// 0x00598980 sub_598980 -- 108 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// *a1 = 1 when the handle is ready (sub_5985F8) and has +3520 set or +3496 > 0; else 0.
void sub_598980(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00598980
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = a1;
    sd(ra, sp, 0x20);
    a1 = sp;
    sw(zero, s1, 0);
    if (s0 != 0) {
        // 0x005989a4
        charge(ctx, 5);
        jal(ctx, 0x5989A4u, gen::fn_sub_5985F8_005985f8);
        lw(v0, sp, 0x0);
        if (v0 != 0) {
            // 0x005989b8
            charge(ctx, 3);
            lw(v0, s0, 3520);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 1;
            if (!cc) {
                // 0x005989c4
                charge(ctx, 3);
                lw(v0, s0, 3496);
                ld(s0, sp, 0x10);
                if (i64(v0) > 0) {
                    // 0x005989d0
                    charge(ctx, 1);
                    v0 = 1;
                    goto L_005989d4;
                }
                // 0x005989dc (the shared epilogue, written out on this path)
                charge(ctx, 4);
                ld(s1, sp, 0x18);
                ld(ra, sp, 0x20);
                sp = addiu(sp, 0x30);
                return;
            }
        L_005989d4:
            charge(ctx, 1);
            sw(v0, s1, 0);
            goto L_005989d8;
        }
        ld(s0, sp, 0x10);
        // 0x005989dc (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_005989d8:
    charge(ctx, 1);
    ld(s0, sp, 0x10);
    // 0x005989dc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00599020 sub_599020 -- 132 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The target count +3496 of the record at +14000: +3536 when positive; else sub_57BAF0 when the sizes +3524 /
//   +3528 (their defaults +3500 / +3504 when not positive) are both positive; else +4.
void sub_599020(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00599020
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    lw(s0, a0, 14000);
    lw(v0, s0, 3536);
    if (i64(v0) > 0) {
        sw(v0, s0, 3496);
    } else {
        // 0x0059903c
        charge(ctx, 4);
        lw(a0, s0, 3524);
        lw(a2, s0, 3528);
        lw(a1, s0, 3532);
        if (i64(a0) > 0) {
            // 0x0059904c
            charge(ctx, 2);
            if (i64(a2) <= 0) {
                goto L_00599054;
            }
        L_00599088:
            charge(ctx, 3);
            jal(ctx, 0x599088u, gen::fn_sub_57BAF0_0057baf0);
            sw(v0, s0, 3496);
            // 0x00599094 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(s0, sp, 0x0);
            ld(ra, sp, 0x8);
            sp = addiu(sp, 0x10);
            return;
        }
    L_00599054:
        charge(ctx, 3);
        lw(v0, s0, 4);
        if (i64(v0) > 0) {
            sw(v0, s0, 3496);
        } else {
            // 0x00599060
            charge(ctx, 2);
            if (i64(a0) <= 0) {
                lw(a0, s0, 3500);
            }
            // 0x00599068
            charge(ctx, 2);
            if (i64(a2) <= 0) {
                // 0x00599070
                charge(ctx, 2);
                lw(a2, s0, 3504);
                lw(a1, s0, 3508);
            }
            // 0x00599078
            charge(ctx, 2);
            if (i64(a0) <= 0) {
                sw(v0, s0, 3496);
            } else {
                // 0x00599080
                charge(ctx, 2);
                if (i64(a2) > 0) {
                    goto L_00599088;
                }
                sw(v0, s0, 3496);
            }
        }
    }
    // 0x00599094 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0059A298 sub_59A298 -- 72 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// sub_59A458; when it returns nonzero, *a1 = -2, *a2 = 1 and 0.
void sub_59A298(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059a298
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a2;
    jal(ctx, 0x59A2ACu, gen::fn_sub_59A458_0059a458);
    v1 = 1;
    if (v0 != 0) {
        // 0x0059a2bc
        charge(ctx, 4);
        v0 = si(-2);
        sw(v0, s0, 0);
        v0 = 0;
        sw(v1, s1, 0);
    }
    // 0x0059a2cc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0059A600 sub_59A600 -- 240 bytes; frame 0x30: s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s0 sp+0x0, ra sp+0x28
// SFD: stores (a1, a2, a3) at +4100 / +4116 / +4120 and sets parameters 15 and 71 (sub_599240): 5 / 0 with
//   a1, 1 / 1 without; error -16776919 while sub_58C060 reports one.
void sub_59A600(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059a600
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s4, sp, 0x20);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x28);
    s4 = a2;
    jal(ctx, 0x59A628u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x0059a63c
        charge(ctx, 9);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x129;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x0059a660
    charge(ctx, 2);
    s0 = addiu(s1, 3376);
    if (s2 == 0) {
        // 0x0059a6a0
        charge(ctx, 12);
        a1 = 71;
        a2 = 1;
        a0 = s1;
        jal(ctx, 0x59A6A8u, gen::fn_sub_599240_00599240);
        a0 = s1;
        a1 = 15;
        a2 = 1;
        jal(ctx, 0x59A6B8u, gen::fn_sub_599240_00599240);
        sw(s3, s0, 744);
        sw(s4, s0, 740);
        sw(zero, s0, 724);
        ld(s0, sp, 0x0);
    } else {
        // 0x0059a668
        charge(ctx, 13);
        sw(s3, s0, 744);
        a1 = 15;
        sw(s2, s0, 724);
        a2 = 5;
        sw(s4, s0, 740);
        a0 = s1;
        jal(ctx, 0x59A67Cu, gen::fn_sub_599240_00599240);
        a0 = s1;
        a1 = 71;
        a2 = 0;
        jal(ctx, 0x59A68Cu, gen::fn_sub_599240_00599240);
        ld(s0, sp, 0x0);
    }
    // 0x0059a6d0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = 0;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0059AD40 sub_59AD40 -- 60 bytes; leaf frame (no stack)
// Frame rate of the handle: with a rate index (+2336), *a1 = 1000 and *a2 = 0x7CA2C0[index]; else 0 and
//   29970; returns 1000 or 29970.
void sub_59AD40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0059ad40
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, 2336);
    v1 = sll(v0, 2);
    if (v0 == 0) {
        // 0x0059ad4c
        charge(ctx, 4);
        v0 = 29970;
        sw(zero, a1, 0);
        sw(v0, a2, 0);
        return;
    }
    // 0x0059ad60
    charge(ctx, 7);
    at = 0x7D0000;
    at = addu(at, v1);
    lw(v1, at, -23872);
    v0 = 1000;
    sw(v0, a1, 0);
    sw(v1, a2, 0);
}

// 0x0059EC08 sub_59EC08 -- 364 bytes; frame 0x10: ra sp+0x0
// SFX conversion dispatch: when sub_59ED78 accepts component a2, +52 = a2 and the converter for it runs (1, 2,
//   4, 5, 11 / 13, 21; jump table 0x7CA680); others report "E201311 ...: compo is not support." (sub_59FD10).
void sub_59EC08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ec08
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0059ec20
    charge(ctx, 13);
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    s2 = a1;
    a1 = s1;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x18);
    s0 = a0;
    jal(ctx, 0x59EC40u, gen::fn_sub_59ED78_0059ed78);
    v1 = 1;
    if (v0 != v1) {
        ld(s0, sp, 0x0);
        // 0x0059ed60
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0059ec54
    charge(ctx, 3);
    v0 = sltiu(s1, 101);
    sw(s1, s0, 52);
    if (v0 != 0) {
        // 0x0059ec60
        charge(ctx, 6);
        v0 = sll(s1, 2);
        v1 = 0x7D0000;
        v1 = addu(v1, v0);
        lw(v1, v1, -22912);
        switch (v1.u()) {
        case 0x59EC78u:  // table[11, 13]
            // 0x0059ec78
            charge(ctx, 8);
            a0 = s0;
            ld(s0, sp, 0x0);
            a1 = s2;
            ld(s2, sp, 0x10);
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x18);
            sp = addiu(sp, 0x20);
            gen::fn_sub_59EE18_0059ee18(ctx);  // tail call
            return;
        case 0x59EC98u:  // table[2]
            // 0x0059ec98
            charge(ctx, 8);
            a0 = s0;
            ld(s0, sp, 0x0);
            a1 = s2;
            ld(s2, sp, 0x10);
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x18);
            sp = addiu(sp, 0x20);
            gen::fn_sub_59EF08_0059ef08(ctx);  // tail call
            return;
        case 0x59ECB8u:  // table[4]
            // 0x0059ecb8
            charge(ctx, 8);
            a0 = s0;
            ld(s0, sp, 0x0);
            a1 = s2;
            ld(s2, sp, 0x10);
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x18);
            sp = addiu(sp, 0x20);
            gen::fn_sub_59EF28_0059ef28(ctx);  // tail call
            return;
        case 0x59ECD8u:  // table[5]
            // 0x0059ecd8
            charge(ctx, 8);
            a0 = s0;
            ld(s0, sp, 0x0);
            a1 = s2;
            ld(s2, sp, 0x10);
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x18);
            sp = addiu(sp, 0x20);
            gen::fn_sub_59EF48_0059ef48(ctx);  // tail call
            return;
        case 0x59ECF8u:  // table[21]
            // 0x0059ecf8
            charge(ctx, 8);
            a0 = s0;
            ld(s0, sp, 0x0);
            a1 = s2;
            ld(s2, sp, 0x10);
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x18);
            sp = addiu(sp, 0x20);
            gen::fn_sub_59EF68_0059ef68(ctx);  // tail call
            return;
        case 0x59ED18u:  // table[1]
            // 0x0059ed18
            charge(ctx, 8);
            a0 = s0;
            ld(s0, sp, 0x0);
            a1 = s2;
            ld(s2, sp, 0x10);
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x18);
            sp = addiu(sp, 0x20);
            gen::fn_sub_59EE38_0059ee38(ctx);  // tail call
            return;
        case 0x59ED38u:  // table[0, 3, 6, 7, 8, 9, 10, 12, 14, 15, 16, 17, 18, 19, 20, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100]
        L_0059ed38:
            charge(ctx, 10);
            a0 = s0;
            ld(s0, sp, 0x0);
            a1 = s2;
            ld(s2, sp, 0x10);
            a2 = 0x7D0000;
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x18);
            a2 = addiu(a2, -22976);  // "E201311: sfxcnv_MakeTable : compo is not support."
            sp = addiu(sp, 0x20);
            gen::fn_sub_59FD10_0059fd10(ctx);  // tail call
            return;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    goto L_0059ed38;
}

// 0x0059EE18 sub_59EE18 -- 32 bytes; frame 0x10: ra sp+0x0
// sub_5A07E0(a0+36, a1+76, a0+56).
void sub_59EE18(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ee18
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a2, a0, 56);
    lw(a1, a1, 76);
    lw(a0, a0, 36);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5A07E0_005a07e0(ctx);  // tail call
}

// 0x0059F320 sub_59F320 -- 180 bytes; frame 0xA0: s0 sp+0x70, s2 sp+0x80, s3 sp+0x88, s1 sp+0x78, ra sp+0x90
// Builds a 68-byte frame descriptor on the stack (memset, sub_59F3D8), the extra word (+56 when a3 == 1) and
//   +80; sub_59EA80(a2) when sub_5A0048 says so; then the callback +104 (desc, a2, {extra, +80}) when set.
void sub_59F320(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059f320
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(s0, sp, 0x70);
    s0 = a1;
    sd(s2, sp, 0x80);
    s2 = a0;
    sd(s3, sp, 0x88);
    s3 = a2;
    a0 = sp;
    a1 = 0;
    a2 = 68;
    sd(s1, sp, 0x78);
    sd(ra, sp, 0x90);
    s1 = a3;
    jal(ctx, 0x59F350u, gen::fn_memset_00521408);
    a0 = s2;
    a1 = s0;
    a2 = sp;
    jal(ctx, 0x59F360u, gen::fn_sub_59F3D8_0059f3d8);
    a0 = s2;
    v0 = 1;
    v1 = 0;
    if (s1 == v0) {
        // 0x0059f378
        charge(ctx, 1);
        lw(v1, s2, 56);
    }
    // 0x0059f37c
    charge(ctx, 7);
    lw(v0, s2, 80);
    sw(v1, sp, 0x50);
    link(ctx, 0x59F384u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x54);
    call(ctx, gen::fn_sub_5A0048_005a0048);
    v1 = 1;
    a0 = s3;
    if (v0 == v1) {
        // 0x0059f398
        charge(ctx, 2);
        jal(ctx, 0x59F398u, gen::fn_sub_59EA80_0059ea80);
    }
    // 0x0059f3a0
    charge(ctx, 3);
    lw(v0, s2, 104);
    a1 = s3;
    if (v0 != 0) {
        // 0x0059f3ac
        charge(ctx, 3);
        a0 = sp;
        a2 = addiu(sp, 0x50);
        jalr(ctx, 0x59F3B0u, v0.u());
    }
    // 0x0059f3b8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x70);
    ld(s1, sp, 0x78);
    ld(s2, sp, 0x80);
    ld(s3, sp, 0x88);
    ld(ra, sp, 0x90);
    sp = addiu(sp, 0xA0);
}

// 0x0059F3D8 sub_59F3D8 -- 316 bytes; frame 0x10: ra sp+0x0
// Frame descriptor by format *a1: 1 / 2 one plane (address, pitch +68, sizes), 3 three planes (the chroma
//   pitches halved); others report "E4111901 ...: frame format is invalid." (sub_59FD10).
void sub_59F3D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0059f3d8
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, a1, 0);
    sp = addiu(sp, -0x10);
    v0 = 2;
    sd(ra, sp, 0x0);
    if (v1 == v0) {
        // 0x0059f448
        charge(ctx, 11);
        v0 = 1;
        lw(v1, a1, 4);
        sw(v0, a2, 0);
        sw(v1, a2, 4);
        lw(v0, a1, 68);
        sw(v0, a2, 8);
        lw(v1, a1, 12);
        sw(v1, a2, 12);
        lw(v0, a1, 8);
        sw(v0, a2, 16);
        // 0x0059f508 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0059f3ec
    charge(ctx, 3);
    v0 = sltiu(v1, 3);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 3;
    if (!cc) {
        // 0x0059f3f8
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x0059f404
            charge(ctx, 2);
            a2 = 0x7D0000;
            goto L_0059f4f8;
        }
        sw(v1, a2, 0);
        // 0x0059f420
        charge(ctx, 9);
        lw(v0, a1, 4);
        lw(v1, a1, 68);
        sw(v0, a2, 4);
        sw(v1, a2, 8);
        lw(v0, a1, 12);
        sw(v0, a2, 12);
        lw(v1, a1, 8);
        sw(v1, a2, 16);
        // 0x0059f508 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0059f410
    charge(ctx, 2);
    if (v1 != v0) {
        // 0x0059f418
        charge(ctx, 2);
        a2 = 0x7D0000;
    L_0059f4f8:
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        a2 = addiu(a2, -22336);
        sp = addiu(sp, 0x10);
        gen::fn_sub_59FD10_0059fd10(ctx);  // tail call
        return;
    }
    sw(v1, a2, 0);
    // 0x0059f478
    charge(ctx, 31);
    lw(v0, a1, 4);
    lw(v1, a1, 68);
    sw(v0, a2, 4);
    sw(v1, a2, 8);
    lw(v0, a1, 20);
    lw(v1, a1, 12);
    sw(v0, a2, 20);
    sw(v1, a2, 12);
    lw(v0, a1, 36);
    lw(v1, a1, 8);
    sw(v0, a2, 36);
    sw(v1, a2, 16);
    lw(v0, a1, 68);
    v1 = srl(v0, 31);
    v0 = addu(v0, v1);
    v0 = sra(v0, 1);
    sw(v0, a2, 24);
    lw(v1, a1, 28);
    sw(v1, a2, 28);
    lw(a0, a1, 24);
    sw(a0, a2, 32);
    lw(v0, a1, 68);
    v1 = srl(v0, 31);
    v0 = addu(v0, v1);
    v0 = sra(v0, 1);
    sw(v0, a2, 40);
    lw(v1, a1, 44);
    sw(v1, a2, 44);
    lw(v0, a1, 40);
    sw(v0, a2, 48);
    // 0x0059f508 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0059F8F8 sub_59F8F8 -- 112 bytes; leaf frame (no stack)
// Work sizes for a w x h picture (a0 * a1) by format a2: 0 and 65 two planes, 49 one, others none; *a3 =
//   8 * h + 8, *a4 / *a5 the plane sizes; returns their sum + 8 * h + 101.
void sub_59F8F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13};
    // 0x0059f8f8
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    v1 = 49;
    t4 = slti(a2, 50);
    t5 = addiu(v0, 8);
    mult(t2, a1, a0);
    t3 = 0;
    if (a2 != v1) {
        // 0x0059f914
        charge(ctx, 2);
        v0 = 65;
        if (t4 == 0) {
            // 0x0059f930
            charge(ctx, 2);
            if (a2 != v0) {
                t2 = 0;
                // 0x0059f948
                charge(ctx, 1);
                t3 = 0;
            } else {
                // 0x0059f938
                charge(ctx, 1);
                mult(t2, a1, a0);
            L_0059f93c:
                charge(ctx, 2);
                t3 = t2;
            }
        } else {
            // 0x0059f91c
            charge(ctx, 2);
            if (a2 == 0) {
                mult(t2, a1, a0);
                goto L_0059f93c;
            }
            // 0x0059f924
            charge(ctx, 2);
            t2 = 0;
        }
    }
    // 0x0059f94c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = addu(t5, t2);
    sw(t5, a3, 0);
    v0 = addu(v0, t3);
    sw(t2, t0, 0);
    v0 = addiu(v0, 93);
    sw(t3, t1, 0);
}

// 0x0059F968 sub_59F968 -- 8 bytes; leaf frame (no stack)
// Returns 17.
void sub_59F968(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059f968
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 17;
}

// 0x0059FD60 WTLS_get_table_2 -- 12 bytes; leaf frame (no stack)
// Returns the word at 0x7B4934.
void WTLS_get_table_2(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x0059fd60
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    lw(v0, v1, 18740);  // 0x7B4934
}

// 0x0059FE50 sub_59FE50 -- 8 bytes; leaf frame (no stack)
// Stores a1 at +52.
void sub_59FE50(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x0059fe50
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, 52);
}

// 0x0059FFC8 sub_59FFC8 -- 60 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// sub_59EA18(a0+48, a1, a2, a3), then +52 = 0 (sub_59FE50).
void sub_59FFC8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059ffc8
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = a1 & 0xFF;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    a2 = a2 & 0xFF;
    a3 = a3 & 0xFF;
    link(ctx, 0x59FFE4u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 48);
    call(ctx, gen::fn_sub_59EA18_0059ea18);
    a0 = s0;
    ld(ra, sp, 0x8);
    a1 = 0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59FE50_0059fe50(ctx);  // tail call
}

// 0x005A0048 sub_5A0048 -- 8 bytes; leaf frame (no stack)
// Returns the word at +100.
void sub_5A0048(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005a0048
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 100);
}

// 0x005A04F0 sub_5A04F0 -- 276 bytes; frame 0x60: s3 sp+0x48, s1 sp+0x38, s2 sp+0x40, s4 sp+0x50, s0 sp+0x30, ra sp+0x58
// SFXINFE lookup: the ZMFSIZE entry (sub_5A0608) gives the record size ("%lx", sscanf); record a1 of the
//   ZMFDATA entry is read with "%lx %lx %lx" into *a2 / *a3. No ZMFSIZE: (0, 0x7FFFFFFF); no ZMFDATA: *a2 =
//   0x7FFFFFFF.
void sub_5A04F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005a04f0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 0x7D0000;
    v1 = 0x7D0000;
    sd(s3, sp, 0x48);
    s3 = addiu(v0, -21976);  // "SFXINFE"
    sd(s1, sp, 0x38);
    sd(s2, sp, 0x40);
    s2 = a1;
    sd(s4, sp, 0x50);
    s4 = a3;
    a1 = addiu(v1, -21960);  // "ZMFSIZE"
    s1 = a2;
    a3 = sp;
    t0 = addiu(sp, 0x4);
    a2 = s3;
    sd(s0, sp, 0x30);
    sd(ra, sp, 0x58);
    s0 = a0;
    jal(ctx, 0x5A0534u, gen::fn_sub_5A0608_005a0608);
    a1 = 0x7D0000;
    lw(v0, sp, 0x0);
    v1 = 0x7FFF0000;
    a2 = addiu(sp, 0x8);
    a1 = addiu(a1, -21952);  // "%lx"
    v1 = v1 | 0xFFFF;
    a0 = v0;
    if (v0 != 0) {
        // 0x005a0568
        charge(ctx, 14);
        jal(ctx, 0x5A0568u, gen::fn_sscanf_00523b40);
        a1 = 0x7D0000;
        a1 = addiu(a1, -21944);  // "ZMFDATA"
        a0 = s0;
        a2 = s3;
        a3 = sp;
        t0 = addiu(sp, 0x4);
        jal(ctx, 0x5A0584u, gen::fn_sub_5A0608_005a0608);
        a1 = s2;
        lw(s0, sp, 0x0);
        v0 = 0x7FFF0000;
        v0 = v0 | 0xFFFF;
        if (s0 != 0) {
            // 0x005a05a8
            charge(ctx, 15);
            link(ctx, 0x5A05A8u);  // $ra first: the delay slot below depends on it
            ld(a0, sp, 0x8);
            call(ctx, gen::fn___muldi3_0052ea78);
            a1 = 0x7D0000;
            v0 = dsll32(v0, 0);
            v0 = dsra32(v0, 0);
            a1 = addiu(a1, -21936);  // "%lx %lx %lx"
            a0 = addu(s0, v0);
            a2 = addiu(sp, 0x10);
            a3 = addiu(sp, 0x18);
            t0 = addiu(sp, 0x20);
            jal(ctx, 0x5A05CCu, gen::fn_sscanf_00523b40);
            lw(v1, sp, 0x18);
            lw(v0, sp, 0x20);
            sw(v1, s1, 0);
            sw(v0, s4, 0);
        } else {
            // 0x005a05a0
            charge(ctx, 2);
            sw(v0, s1, 0);
        }
    } else {
        // 0x005a055c
        charge(ctx, 3);
        sw(zero, s1, 0);
        sw(v1, s4, 0);
    }
    // 0x005a05e4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x30);
    ld(s1, sp, 0x38);
    ld(s2, sp, 0x40);
    ld(s3, sp, 0x48);
    ld(s4, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
}

// 0x005A0BB0 sub_5A0BB0 -- 44 bytes; leaf frame (no stack)
// 1 when either float +60 or +64 is nonzero.
void sub_5A0BB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x005a0bb0
    enter(ctx, 6);  // entry check point + this block's cycles
    mtc1(zero, f2);
    v0 = 1;
    lwc1(f0, a0, 60);
    c_eq_s(f0, f2);
    lwc1(f1, a0, 64);
    if (cond(ctx)) {
        // 0x005a0bc8
        charge(ctx, 3);
        c_eq_s(f1, f2);
        if (cond(ctx)) {
            v0 = 0;
        }
    }
    // 0x005a0bd4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005A10E8 sub_5A10E8 -- 12 bytes; leaf frame (no stack)
// Stores a1 at (+36)->+4.
void sub_5A10E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x005a10e8
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, 36);
    sw(a1, v0, 4);
}

}  // namespace p3fes::game
