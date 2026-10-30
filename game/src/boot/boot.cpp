// Phase 5 slice boot (boot.h has the boot sequence): main, the kwln root task and its draw passes, the new-game data,
// the H_FileSetup_* set-up tasks, the GS upload packet builders and the task-tree dump, 0x191D10-0x1997A0.
// Started from p3fes_handgen's bodies (register for register, block for block as the recompiled ones: frame, spills,
// $ra links, cycle charges, check points; game/include/p3fes/game/hg_cpu.h) and made readable on top: a role comment
// per function, named offsets (boot.h), structured control flow. Every path keeps the original's statements, charges
// and check points in order (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"); tests/game/test_boot.cpp pairs them.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/boot.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_H_FileSetup_UpdateChoiceDataFileSetupTask_00192b50(p3fes::EEContext&);
void fn_H_FileSetup_UpdateHikitugiDataProcTask_00193020(p3fes::EEContext&);
void fn_H_FileSetup_UpdateHonpenItemTblDataReadTask_001923b0(p3fes::EEContext&);
void fn_K_Field_Init_001b90f0(p3fes::EEContext&);
void fn_K_SceneDraw_CreateTasks_0019f730(p3fes::EEContext&);
void fn_RpPDSRegisterPipe_0046a830(p3fes::EEContext&);
void fn_RpSkySelectDeepZBuffer_004d82a0(p3fes::EEContext&);
void fn_RwEngineOpen_004ca700(p3fes::EEContext&);
void fn_RwEngineSetVideoMode_004ca600(p3fes::EEContext&);
void fn_RwEngineStart_004ca640(p3fes::EEContext&);
void fn_RwResourcesSetArenaSize_004c4c00(p3fes::EEContext&);
void fn_Y_McProc_CreateMcProcDrawTask_00420340(p3fes::EEContext&);
void fn__rwDMAAddPkt_004d5000(p3fes::EEContext&);
void fn__rwDMAPreAlloc_004d6ab0(p3fes::EEContext&);
void fn_datClearFlagAll_0016f2e0(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datItemTblSetSections_0016c2f0(p3fes::EEContext&);
void fn_datSetDaysSinceApr5_0016ef70(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_dbgPrintDrawScreen_00104420(p3fes::EEContext&);
void fn_gmRoot_CreateGameRootTask_002664c0(p3fes::EEContext&);
void fn_initAndLoop_001939b0(p3fes::EEContext&);
void fn_kwlnCreateMainCamera_00195c80(p3fes::EEContext&);
void fn_kwlnInitRenderer_00197350(p3fes::EEContext&);
void fn_kwlnInstallVsyncFieldGate_0019d360(p3fes::EEContext&);
void fn_kwlnMain_001984c0(p3fes::EEContext&);
void fn_kwlnRootCreateShowRasterTask_00199360(p3fes::EEContext&);
void fn_kwlnRootCreateTask_00198940(p3fes::EEContext&);
void fn_kwlnRootUpdate2DDrawPreEndTask_00198b10(p3fes::EEContext&);
void fn_kwlnRootUpdateDrawBustupProcTask_001993a0(p3fes::EEContext&);
void fn_kwlnRootUpdateEtcDrawTask_00198f90(p3fes::EEContext&);
void fn_kwlnRootUpdateTask_00198650(p3fes::EEContext&);
void fn_kwlnSetFlags_00198610(p3fes::EEContext&);
void fn_kwlnSetupMainCameraViewport_00195980(p3fes::EEContext&);
void fn_kwlnTaskAddChild_00195550(p3fes::EEContext&);
void fn_kwlnTaskCreateWithAutoPriority_00194b80(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskExists_00195460(p3fes::EEContext&);
void fn_kwlnTaskGetState_00195290(p3fes::EEContext&);
void fn_kwlnTaskInit_00194c50(p3fes::EEContext&);
void fn_main_00193980(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_scePrintf_00505e48(p3fes::EEContext&);
void fn_scrSetIntReturnVal_0035f060(p3fes::EEContext&);
void fn_sub_103580_00103580(p3fes::EEContext&);
void fn_sub_1040F0_001040f0(p3fes::EEContext&);
void fn_sub_1043B0_001043b0(p3fes::EEContext&);
void fn_sub_104D10_00104d10(p3fes::EEContext&);
void fn_sub_1058A0_001058a0(p3fes::EEContext&);
void fn_sub_107060_00107060(p3fes::EEContext&);
void fn_sub_108F70_00108f70(p3fes::EEContext&);
void fn_sub_109CA0_00109ca0(p3fes::EEContext&);
void fn_sub_109DF0_00109df0(p3fes::EEContext&);
void fn_sub_16C470_0016c470(p3fes::EEContext&);
void fn_sub_16C5F0_0016c5f0(p3fes::EEContext&);
void fn_sub_16C670_0016c670(p3fes::EEContext&);
void fn_sub_16CDF0_0016cdf0(p3fes::EEContext&);
void fn_sub_16CEF0_0016cef0(p3fes::EEContext&);
void fn_sub_16CF40_0016cf40(p3fes::EEContext&);
void fn_sub_16CF90_0016cf90(p3fes::EEContext&);
void fn_sub_16CFE0_0016cfe0(p3fes::EEContext&);
void fn_sub_16D090_0016d090(p3fes::EEContext&);
void fn_sub_16D160_0016d160(p3fes::EEContext&);
void fn_sub_16D230_0016d230(p3fes::EEContext&);
void fn_sub_16D6B0_0016d6b0(p3fes::EEContext&);
void fn_sub_16D8B0_0016d8b0(p3fes::EEContext&);
void fn_sub_16D930_0016d930(p3fes::EEContext&);
void fn_sub_16D980_0016d980(p3fes::EEContext&);
void fn_sub_16DA50_0016da50(p3fes::EEContext&);
void fn_sub_16DB70_0016db70(p3fes::EEContext&);
void fn_sub_16E930_0016e930(p3fes::EEContext&);
void fn_sub_16E990_0016e990(p3fes::EEContext&);
void fn_sub_16F150_0016f150(p3fes::EEContext&);
void fn_sub_16F180_0016f180(p3fes::EEContext&);
void fn_sub_16F320_0016f320(p3fes::EEContext&);
void fn_sub_16F380_0016f380(p3fes::EEContext&);
void fn_sub_16F3E0_0016f3e0(p3fes::EEContext&);
void fn_sub_16F450_0016f450(p3fes::EEContext&);
void fn_sub_16FEA0_0016fea0(p3fes::EEContext&);
void fn_sub_170860_00170860(p3fes::EEContext&);
void fn_sub_170B20_00170b20(p3fes::EEContext&);
void fn_sub_170B90_00170b90(p3fes::EEContext&);
void fn_sub_1754A0_001754a0(p3fes::EEContext&);
void fn_sub_1755C0_001755c0(p3fes::EEContext&);
void fn_sub_175820_00175820(p3fes::EEContext&);
void fn_sub_175BE0_00175be0(p3fes::EEContext&);
void fn_sub_175C70_00175c70(p3fes::EEContext&);
void fn_sub_176680_00176680(p3fes::EEContext&);
void fn_sub_1773D0_001773d0(p3fes::EEContext&);
void fn_sub_1779A0_001779a0(p3fes::EEContext&);
void fn_sub_177CE0_00177ce0(p3fes::EEContext&);
void fn_sub_17ADF0_0017adf0(p3fes::EEContext&);
void fn_sub_17B160_0017b160(p3fes::EEContext&);
void fn_sub_17B1A0_0017b1a0(p3fes::EEContext&);
void fn_sub_17B2A0_0017b2a0(p3fes::EEContext&);
void fn_sub_17C190_0017c190(p3fes::EEContext&);
void fn_sub_17C280_0017c280(p3fes::EEContext&);
void fn_sub_17CD30_0017cd30(p3fes::EEContext&);
void fn_sub_17D3C0_0017d3c0(p3fes::EEContext&);
void fn_sub_17D7B0_0017d7b0(p3fes::EEContext&);
void fn_sub_17D7C0_0017d7c0(p3fes::EEContext&);
void fn_sub_17D7F0_0017d7f0(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_182C50_00182c50(p3fes::EEContext&);
void fn_sub_1830C0_001830c0(p3fes::EEContext&);
void fn_sub_1919C0_001919c0(p3fes::EEContext&);
void fn_sub_191AF0_00191af0(p3fes::EEContext&);
void fn_sub_191D10_00191d10(p3fes::EEContext&);
void fn_sub_191D70_00191d70(p3fes::EEContext&);
void fn_sub_191E60_00191e60(p3fes::EEContext&);
void fn_sub_191EC0_00191ec0(p3fes::EEContext&);
void fn_sub_192160_00192160(p3fes::EEContext&);
void fn_sub_1921D0_001921d0(p3fes::EEContext&);
void fn_sub_192230_00192230(p3fes::EEContext&);
void fn_sub_1922A0_001922a0(p3fes::EEContext&);
void fn_sub_192310_00192310(p3fes::EEContext&);
void fn_sub_192370_00192370(p3fes::EEContext&);
void fn_sub_192480_00192480(p3fes::EEContext&);
void fn_sub_1924D0_001924d0(p3fes::EEContext&);
void fn_sub_192570_00192570(p3fes::EEContext&);
void fn_sub_1926A0_001926a0(p3fes::EEContext&);
void fn_sub_192710_00192710(p3fes::EEContext&);
void fn_sub_1927B0_001927b0(p3fes::EEContext&);
void fn_sub_1928A0_001928a0(p3fes::EEContext&);
void fn_sub_1928D0_001928d0(p3fes::EEContext&);
void fn_sub_192980_00192980(p3fes::EEContext&);
void fn_sub_192A70_00192a70(p3fes::EEContext&);
void fn_sub_192AA0_00192aa0(p3fes::EEContext&);
void fn_sub_192DB0_00192db0(p3fes::EEContext&);
void fn_sub_192DE0_00192de0(p3fes::EEContext&);
void fn_sub_192E70_00192e70(p3fes::EEContext&);
void fn_sub_193320_00193320(p3fes::EEContext&);
void fn_sub_1933D0_001933d0(p3fes::EEContext&);
void fn_sub_193460_00193460(p3fes::EEContext&);
void fn_sub_1938B0_001938b0(p3fes::EEContext&);
void fn_sub_1938E0_001938e0(p3fes::EEContext&);
void fn_sub_194750_00194750(p3fes::EEContext&);
void fn_sub_1948B0_001948b0(p3fes::EEContext&);
void fn_sub_195DE0_00195de0(p3fes::EEContext&);
void fn_sub_196770_00196770(p3fes::EEContext&);
void fn_sub_1967D0_001967d0(p3fes::EEContext&);
void fn_sub_197F80_00197f80(p3fes::EEContext&);
void fn_sub_198540_00198540(p3fes::EEContext&);
void fn_sub_198560_00198560(p3fes::EEContext&);
void fn_sub_198570_00198570(p3fes::EEContext&);
void fn_sub_198580_00198580(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_1985A0_001985a0(p3fes::EEContext&);
void fn_sub_1985B0_001985b0(p3fes::EEContext&);
void fn_sub_1985D0_001985d0(p3fes::EEContext&);
void fn_sub_1985E0_001985e0(p3fes::EEContext&);
void fn_sub_1988F0_001988f0(p3fes::EEContext&);
void fn_sub_198B50_00198b50(p3fes::EEContext&);
void fn_sub_198B90_00198b90(p3fes::EEContext&);
void fn_sub_198BD0_00198bd0(p3fes::EEContext&);
void fn_sub_198DD0_00198dd0(p3fes::EEContext&);
void fn_sub_198E10_00198e10(p3fes::EEContext&);
void fn_sub_198E50_00198e50(p3fes::EEContext&);
void fn_sub_199080_00199080(p3fes::EEContext&);
void fn_sub_1990C0_001990c0(p3fes::EEContext&);
void fn_sub_199100_00199100(p3fes::EEContext&);
void fn_sub_1993D0_001993d0(p3fes::EEContext&);
void fn_sub_199410_00199410(p3fes::EEContext&);
void fn_sub_199440_00199440(p3fes::EEContext&);
void fn_sub_1996C0_001996c0(p3fes::EEContext&);
void fn_sub_199700_00199700(p3fes::EEContext&);
void fn_sub_1997A0_001997a0(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_19D400_0019d400(p3fes::EEContext&);
void fn_sub_1CD7A0_001cd7a0(p3fes::EEContext&);
void fn_sub_1FA0D0_001fa0d0(p3fes::EEContext&);
void fn_sub_1FC1F0_001fc1f0(p3fes::EEContext&);
void fn_sub_25B440_0025b440(p3fes::EEContext&);
void fn_sub_35ABA0_0035aba0(p3fes::EEContext&);
void fn_sub_3B5AB0_003b5ab0(p3fes::EEContext&);
void fn_sub_45F7D0_0045f7d0(p3fes::EEContext&);
void fn_sub_4661B0_004661b0(p3fes::EEContext&);
void fn_sub_468C50_00468c50(p3fes::EEContext&);
void fn_sub_46A530_0046a530(p3fes::EEContext&);
void fn_sub_46A750_0046a750(p3fes::EEContext&);
void fn_sub_473590_00473590(p3fes::EEContext&);
void fn_sub_488FE0_00488fe0(p3fes::EEContext&);
void fn_sub_48A1A0_0048a1a0(p3fes::EEContext&);
void fn_sub_48DCF0_0048dcf0(p3fes::EEContext&);
void fn_sub_48F030_0048f030(p3fes::EEContext&);
void fn_sub_4944B0_004944b0(p3fes::EEContext&);
void fn_sub_494760_00494760(p3fes::EEContext&);
void fn_sub_4947C0_004947c0(p3fes::EEContext&);
void fn_sub_49A400_0049a400(p3fes::EEContext&);
void fn_sub_49A980_0049a980(p3fes::EEContext&);
void fn_sub_49C160_0049c160(p3fes::EEContext&);
void fn_sub_49C3D0_0049c3d0(p3fes::EEContext&);
void fn_sub_4A9F20_004a9f20(p3fes::EEContext&);
void fn_sub_4AA390_004aa390(p3fes::EEContext&);
void fn_sub_4AA3D0_004aa3d0(p3fes::EEContext&);
void fn_sub_4AA550_004aa550(p3fes::EEContext&);
void fn_sub_4AC860_004ac860(p3fes::EEContext&);
void fn_sub_4B6350_004b6350(p3fes::EEContext&);
void fn_sub_4B6640_004b6640(p3fes::EEContext&);
void fn_sub_4B8830_004b8830(p3fes::EEContext&);
void fn_sub_4C9D70_004c9d70(p3fes::EEContext&);
void fn_sub_4C9DB0_004c9db0(p3fes::EEContext&);
void fn_sub_4C9F90_004c9f90(p3fes::EEContext&);
void fn_sub_4CA030_004ca030(p3fes::EEContext&);
void fn_sub_4CA090_004ca090(p3fes::EEContext&);
void fn_sub_4CA560_004ca560(p3fes::EEContext&);
void fn_sub_4CA5B0_004ca5b0(p3fes::EEContext&);
void fn_sub_4CA850_004ca850(p3fes::EEContext&);
void fn_sub_4CAF10_004caf10(p3fes::EEContext&);
void fn_sub_4CAF80_004caf80(p3fes::EEContext&);
void fn_sub_4CB890_004cb890(p3fes::EEContext&);
void fn_sub_4CB930_004cb930(p3fes::EEContext&);
void fn_sub_4CCD50_004ccd50(p3fes::EEContext&);
void fn_sub_4CDE90_004cde90(p3fes::EEContext&);
void fn_sub_4CE0F0_004ce0f0(p3fes::EEContext&);
void fn_sub_4D1840_004d1840(p3fes::EEContext&);
void fn_sub_4F1E10_004f1e10(p3fes::EEContext&);
void fn_sub_4F1E20_004f1e20(p3fes::EEContext&);
void fn_sub_4F8E10_004f8e10(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x00191D10 sub_191D10 -- 84 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_191D10(n, size) [H_Calloc]: H_Malloc(n * size) (sub_191AF0), then memset(block, 0, n * size); returns the block
// (no check for a failed allocation). Caller: sub_187E20.
void sub_191D10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00191d10
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    mult(s0, a1, a0);
    a0 = s0;
    jal(ctx, 0x191D28u, gen::fn_sub_191AF0_00191af0);
    s1 = v0;
    a0 = s1;
    a1 = 0;
    a2 = s0;
    jal(ctx, 0x191D40u, gen::fn_memset_00521408);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00191D70 sub_191D70 -- 232 bytes; frame 0x60: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq)
// sub_191D70(raster, data, width_qw, height) [kwlnRasterUpload]: uploads an image to a raster's GS memory through
// RenderWare's DMA queue. sub_4F1E20 reads the raster's GS base / format words into two stack slots; the base (low 14
// bits of the halfword at sp+0x58) is the BITBLTBUF destination. The packet goes to the static buffer 0x846F00
// (kUploadPacket) through sub_191E60; images taller than 448 lines (height * 16 > 448 bytes of rows) pass the
// remainder as a second strip. Then _rwDMAAddPkt(0x846F00, 0x102) queues it. Caller: sub_10A860.
void sub_191D70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00191d70
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    s2 = a1;
    s1 = a2;
    s0 = a3;
    a1 = addiu(sp, 0x5C);
    a2 = addiu(sp, 0x58);
    jal(ctx, 0x191D98u, gen::fn_sub_4F1E20_004f1e20);
    lhu(v0, sp, 0x58);
    a0 = v0 & 0x3FFF;
    t2 = sll(s0, 4);
    at = sltiu(t2, 449);
    if (at == 0) {
        // 0x00191dec
        charge(ctx, 13);
        sd(zero, sp, 0x0);
        v0 = addiu(t2, -448);
        sd(v0, sp, 0x8);
        t1 = sll(s1, 4);
        a1 = 0x840000;
        a1 = addiu(a1, 28416);  // &0x846F00
        a2 = s2;
        a3 = 0;
        t0 = 0;
        t2 = 448;
        t3 = 0;
        jal(ctx, 0x191E18u, gen::fn_sub_191E60_00191e60);
    } else {
        // 0x00191db8
        charge(ctx, 13);
        sd(zero, sp, 0x0);
        sd(zero, sp, 0x8);
        t1 = sll(s1, 4);
        a1 = 0x840000;
        a1 = addiu(a1, 28416);  // &0x846F00
        a2 = s2;
        a3 = 0;
        t0 = 0;
        t3 = 0;
        jal(ctx, 0x191DDCu, gen::fn_sub_191E60_00191e60);
    }
    // 0x00191e20
    charge(ctx, 4);
    a0 = 0x840000;
    a0 = addiu(a0, 28416);  // &0x846F00
    if (a0 != 0) {
        // 0x00191e30
        charge(ctx, 3);
        a1 = 258;
        jal(ctx, 0x191E34u, gen::fn__rwDMAAddPkt_004d5000);
    }
    // 0x00191e3c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x60);
}

// 0x00191E60 sub_191E60 -- 88 bytes; frame 0x30: ra sp+0x20
// sub_191E60 [kwlnBuildUploadPacketFixed]: sub_191EC0 with the buffer width fixed at 1024 (a3 = 1024); moves $a3..$t3
// up by one and the two stack arguments into its own outgoing slots.
void sub_191E60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00191e60
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    t6 = a3;
    t5 = t0;
    t4 = t1;
    v1 = t2;
    sd(t3, sp, 0x0);
    lw(v0, sp, 0x30);
    sd(v0, sp, 0x8);
    lw(v0, sp, 0x38);
    sd(v0, sp, 0x10);
    a3 = 1024;
    t0 = t6;
    t1 = t5;
    t2 = t4;
    t3 = v1;
    jal(ctx, 0x191EA0u, gen::fn_sub_191EC0_00191ec0);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00191EC0 sub_191EC0 -- 672 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_191EC0 [kwlnBuildUploadPacket]: builds a GS image-transfer DMA chain in `packet` (a1): a DMA cnt tag + an A+D
// GIF tag, BITBLTBUF (destination base / width / PSMCT32), TRXREG (16 x height), then for each of the `slices` slices
// a cnt tag + GIF tag + TRXPOS + TRXDIR (host -> local) and a ref tag pointing at the slice's data (IMAGE mode GIF
// tag, EOP on the last slice), and an end tag. The register writers are sub_192160 (DMA tag), sub_1921D0 (GIF tag),
// sub_192230 (BITBLTBUF), sub_1922A0 (TRXPOS), sub_192310 (TRXREG), sub_192370 (TRXDIR). Every slice is 96 bytes.
void sub_191EC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00191ec0
    enter(ctx, 43);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s7 = a2;
    s5 = a3;
    fp = t0;
    s1 = t2;
    s6 = sra(s1, 4);
    s0 = sra(t3, 4);
    sw(t1, sp, 0xAC);
    a0 = s2;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    t0 = 1;
    t1 = 0;
    t2 = 3;
    jal(ctx, 0x191F2Cu, gen::fn_sub_192160_00192160);
    a0 = addiu(s2, 16);
    a1 = 14;
    a2 = 1;
    a3 = 0;
    t0 = 0;
    t1 = 0;
    t2 = 0;
    t3 = 2;
    jal(ctx, 0x191F54u, gen::fn_sub_1921D0_001921d0);
    v0 = addiu(s1, 63);
    v1 = sra(v0, 6);
    if (i64(v0) < 0) {
        // 0x00191f6c
        charge(ctx, 2);
        v0 = addiu(v0, 63);
        v1 = sra(v0, 6);
    }
    // 0x00191f74
    charge(ctx, 5);
    v0 = sll(v1, 6);
    a2 = dsll32(v1, 6);
    a2 = dsra32(a2, 6);
    if (i64(v0) < 0) {
        // 0x00191f88
        charge(ctx, 2);
        v0 = addiu(v0, 63);
        a2 = sra(v0, 6);
    }
    // 0x00191f90
    charge(ctx, 28);
    a0 = addiu(s2, 32);
    a1 = s3;
    a3 = 0;
    jal(ctx, 0x191F9Cu, gen::fn_sub_192230_00192230);
    a2 = sll(s0, 4);
    a0 = addiu(s2, 48);
    a1 = 16;
    jal(ctx, 0x191FB0u, gen::fn_sub_192310_00192310);
    s4 = addiu(s2, 64);
    lw(v0, sp, 0xC0);
    a0 = sra(v0, 4);
    lw(v0, sp, 0xB0);
    v1 = sra(v0, 4);
    v0 = addu(s0, a0);
    mult(v0, s5, v0);
    mult(v0, v1, v0);
    v1 = addu(s7, v0);
    lw(v0, sp, 0xB8);
    v0 = sra(v0, 4);
    mult1(v0, s5, v0);
    s1 = addu(v1, v0);
    s3 = 0;
    v0 = sll(s0, 10);
    s2 = sra(v0, 4);
    if (i64(v0) < 0) {
        // 0x00192000
        charge(ctx, 2);
        v0 = addiu(v0, 15);
        s2 = sra(v0, 4);
    }
    // 0x00192008
    charge(ctx, 4);
    mult(s7, s5, s0);
    mult1(s5, s5, a0);
    for (;;) {
        // 0x001920fc
        charge(ctx, 3);
        v0 = slt(s3, s6);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00192018
        charge(ctx, 57);
        v0 = addiu(s6, -1);
        s0 = s3 ^ v0;
        s0 = sltiu(s0, 1);
        a0 = s4;
        a1 = 0;
        a2 = 0;
        a3 = 0;
        t0 = 1;
        t1 = 0;
        t2 = 4;
        jal(ctx, 0x192040u, gen::fn_sub_192160_00192160);
        a0 = addiu(s4, 16);
        a1 = 14;
        a2 = 1;
        a3 = 0;
        t0 = 0;
        t1 = 0;
        t2 = 0;
        t3 = 2;
        jal(ctx, 0x192068u, gen::fn_sub_1921D0_001921d0);
        v0 = sll(s3, 4);
        a2 = addu(fp, v0);
        a0 = addiu(s4, 32);
        a1 = 0;
        lw(a3, sp, 0xAC);
        jal(ctx, 0x192084u, gen::fn_sub_1922A0_001922a0);
        a0 = addiu(s4, 48);
        a1 = 0;
        jal(ctx, 0x192094u, gen::fn_sub_192370_00192370);
        a0 = addiu(s4, 64);
        a1 = 0;
        a2 = 0;
        a3 = 2;
        t0 = 0;
        t1 = 0;
        t2 = s0;
        t3 = s2;
        jal(ctx, 0x1920BCu, gen::fn_sub_1921D0_001921d0);
        a2 = dsll32(s1, 4);
        a2 = dsrl32(a2, 4);
        a0 = addiu(s4, 80);
        a1 = 0;
        a3 = 0;
        t0 = 3;
        t1 = 0;
        t2 = s2;
        jal(ctx, 0x1920E4u, gen::fn_sub_192160_00192160);
        s4 = addiu(s4, 96);
        v0 = addu(s1, s7);
        s1 = addu(v0, s5);
        s3 = addiu(s3, 1);
    }
    // 0x00192108
    charge(ctx, 22);
    a0 = s4;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    t0 = 7;
    t1 = 0;
    t2 = 0;
    jal(ctx, 0x192124u, gen::fn_sub_192160_00192160);
    ld(ra, sp, 0x90);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x00192160 sub_192160 -- 108 bytes; leaf frame (no stack)
// sub_192160(dst, spr, addr, irq, id, pce, qwc) [kwlnSetDmaTag]: stores one 64-bit DMAC source-chain tag:
// QWC (bits 0..15) | PCE << 26 | ID << 28 | IRQ << 31 | ADDR (16-aligned, bits 32..62) | SPR << 63.
void sub_192160(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    // 0x00192160
    enter(ctx, 27);  // entry check point + this block's cycles
    v1 = si(-16);
    v1 = a2 & v1;
    v1 = dsll32(v1, 0);
    v1 = dsrl32(v1, 0);
    a2 = dsll32(v1, 0);
    v1 = dsll32(a1, 0);
    v1 = dsrl32(v1, 0);
    v1 = dsll32(v1, 31);
    a1 = v1 | a2;
    v1 = dsll32(a3, 0);
    v1 = dsrl32(v1, 0);
    v1 = dsll(v1, 31);
    a1 = v1 | a1;
    v1 = dsll32(t0, 0);
    v1 = dsrl32(v1, 0);
    v1 = dsll(v1, 28);
    a1 = v1 | a1;
    v1 = dsll32(t1, 0);
    v1 = dsrl32(v1, 0);
    v1 = dsll(v1, 26);
    a1 = v1 | a1;
    v1 = dsll32(t2, 0);
    v1 = dsrl32(v1, 0);
    v1 = v1 | a1;
    sd(v1, a0, 0);
}

// 0x001921D0 sub_1921D0 -- 96 bytes; leaf frame (no stack)
// sub_1921D0(dst, regs64, nreg, flg, prim, pre, eop, nloop) [kwlnSetGifTag]: stores one 128-bit GIF tag: NLOOP | EOP
// << 15 in word 0; PRE << 14 | PRIM << 15 | FLG << 26 | NREG << 28 in word 1 (bits 46..63 of the tag); REGS in words
// 2..3. Called with regs 14 (A+D) and nreg 1 for register packets, flg 2 (IMAGE) for image data.
void sub_1921D0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x001921d0
    enter(ctx, 24);  // entry check point + this block's cycles
    v1 = sll(t2, 15);
    v1 = v1 | t3;
    sw(v1, a0, 0);
    t1 = sll(t1, 14);
    v1 = sll(t0, 15);
    t0 = t1 | v1;
    v1 = sll(a3, 26);
    a3 = v1 | t0;
    v1 = sll(a2, 28);
    v1 = v1 | a3;
    sw(v1, a0, 4);
    v1 = 0xFFFF;
    v1 = dsll(v1, 16);
    v1 = v1 | 0xFFFF;
    v1 = a1 & v1;
    v1 = dsll32(v1, 0);
    v1 = dsra32(v1, 0);
    sw(v1, a0, 8);
    v1 = dsrl32(a1, 0);
    v1 = dsll32(v1, 0);
    v1 = dsra32(v1, 0);
    sw(v1, a0, 12);
}

// 0x00192230 sub_192230 -- 108 bytes; leaf frame (no stack)
// sub_192230(dst, dbp, dbw, dpsm) [kwlnSetBitBltBuf]: an A+D pair for BITBLTBUF (register 0x50): DBP << 32 | DBW << 48
// | DPSM << 56.
void sub_192230(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00192230
    enter(ctx, 27);  // entry check point + this block's cycles
    v1 = dsll32(a3, 0);
    v1 = dsrl32(v1, 0);
    a3 = dsll32(v1, 24);
    v1 = dsll32(a2, 0);
    v1 = dsrl32(v1, 0);
    v1 = dsll32(v1, 16);
    a2 = a3 | v1;
    v1 = dsll32(a1, 0);
    v1 = dsrl32(v1, 0);
    v1 = dsll32(v1, 0);
    a1 = v1 | a2;
    v1 = 0xFFFF;
    v1 = dsll(v1, 16);
    v1 = v1 | 0xFFFF;
    v1 = a1 & v1;
    v1 = dsll32(v1, 0);
    v1 = dsra32(v1, 0);
    sw(v1, a0, 0);
    v1 = dsrl32(a1, 0);
    v1 = dsll32(v1, 0);
    v1 = dsra32(v1, 0);
    sw(v1, a0, 4);
    v1 = 80;
    sw(v1, a0, 8);
    sw(zero, a0, 12);
}

// 0x001922A0 sub_1922A0 -- 108 bytes; leaf frame (no stack)
// sub_1922A0(dst, dir, dsax, dsay) [kwlnSetTrxPos]: an A+D pair for TRXPOS (register 0x51): DSAX << 32 | DSAY << 48
// | DIR << 59.
void sub_1922A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x001922a0
    enter(ctx, 27);  // entry check point + this block's cycles
    v1 = dsll32(a1, 0);
    v1 = dsrl32(v1, 0);
    a1 = dsll32(v1, 27);
    v1 = dsll32(a3, 0);
    v1 = dsrl32(v1, 0);
    v1 = dsll32(v1, 16);
    a1 = a1 | v1;
    v1 = dsll32(a2, 0);
    v1 = dsrl32(v1, 0);
    v1 = dsll32(v1, 0);
    a1 = v1 | a1;
    v1 = 0xFFFF;
    v1 = dsll(v1, 16);
    v1 = v1 | 0xFFFF;
    v1 = a1 & v1;
    v1 = dsll32(v1, 0);
    v1 = dsra32(v1, 0);
    sw(v1, a0, 0);
    v1 = dsrl32(a1, 0);
    v1 = dsll32(v1, 0);
    v1 = dsra32(v1, 0);
    sw(v1, a0, 4);
    v1 = 81;
    sw(v1, a0, 8);
    sw(zero, a0, 12);
}

// 0x00192310 sub_192310 -- 88 bytes; leaf frame (no stack)
// sub_192310(dst, rrw, rrh) [kwlnSetTrxReg]: an A+D pair for TRXREG (register 0x52): RRW | RRH << 32.
void sub_192310(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00192310
    enter(ctx, 22);  // entry check point + this block's cycles
    v1 = dsll32(a2, 0);
    v1 = dsrl32(v1, 0);
    a2 = dsll32(v1, 0);
    v1 = dsll32(a1, 0);
    v1 = dsrl32(v1, 0);
    a1 = a2 | v1;
    v1 = 0xFFFF;
    v1 = dsll(v1, 16);
    v1 = v1 | 0xFFFF;
    v1 = a1 & v1;
    v1 = dsll32(v1, 0);
    v1 = dsra32(v1, 0);
    sw(v1, a0, 0);
    v1 = dsrl32(a1, 0);
    v1 = dsll32(v1, 0);
    v1 = dsra32(v1, 0);
    sw(v1, a0, 4);
    v1 = 82;
    sw(v1, a0, 8);
    sw(zero, a0, 12);
}

// 0x00192370 sub_192370 -- 60 bytes; leaf frame (no stack)
// sub_192370(dst, xdir) [kwlnSetTrxDir]: an A+D pair for TRXDIR (register 0x53): XDIR (0 = host -> local).
void sub_192370(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00192370
    enter(ctx, 15);  // entry check point + this block's cycles
    a1 = dsll32(a1, 0);
    a1 = dsrl32(a1, 0);
    v1 = 0xFFFF;
    v1 = dsll(v1, 16);
    v1 = v1 | 0xFFFF;
    v1 = a1 & v1;
    v1 = dsll32(v1, 0);
    v1 = dsra32(v1, 0);
    sw(v1, a0, 0);
    sw(zero, a0, 4);
    v1 = 83;
    sw(v1, a0, 8);
    sw(zero, a0, 12);
}

// 0x001923B0 H_FileSetup_UpdateHonpenItemTblDataReadTask -- 204 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// H_FileSetup_UpdateHonpenItemTblDataReadTask(task): update callback of the "HonpenItemTblDataRead" task (created by
// sub_1924D0): loads The Journey's item table. Work (12 bytes): +0 step, +4 the file node.
//   step 0: node = H_Cdvd_Request("event/itemtbl.bin", 0), step 1;
//   step 1: once H_Cdvd_IsFileLoaded(node) == 1, memcpy the whole file (node +0x110 data, +0x118 size) to the item
//           table 0x83BB30, H_Cdvd_Destroy, node = 0, datItemTblSetSections() (the 14 section pointers), return -1
//           (the task ends);
//   other steps: wait. Returns 0 while running.
void H_FileSetup_UpdateHonpenItemTblDataReadTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001923b0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    using namespace boot;
    lw(s0, a0, task::kWork);  // s0 = work
    lw(v1, s0, fs::kStep);
    v0 = 1;
    bool loaded = false;  // host-side: which tail runs (the original's shared "return 0" block or the copy)
    if (v1 != v0) {
        // 0x001923d0: steps other than 1
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x001923e0: step 0 -- request the file (not an archive)
            charge(ctx, 11);
            a0 = 0x5E0000;
            a0 = addiu(a0, 19552);  // "event/itemtbl.bin"
            a1 = 0;
            jal(ctx, 0x1923ECu, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s0, fs::kNode);
            lw(v0, s0, fs::kStep);
            v0 = addiu(v0, 1);
            sw(v0, s0, fs::kStep);
        } else {
            // 0x001923d8
            charge(ctx, 2);
        }
    } else {
        // 0x0019240c: step 1 -- wait for the read
        charge(ctx, 6);
        lw(a0, s0, fs::kNode);
        jal(ctx, 0x192410u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
        v1 = 1;
        loaded = v0 == v1;
    }
    if (!loaded) {
        // 0x00192464: keep running
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00192424: copy the whole file to the item table, drop the node, set the section pointers; the task ends
        charge(ctx, 16);
        lw(v0, s0, fs::kNode);
        lw(a2, v0, node::kSize);
        a0 = 0x840000;
        a0 = addiu(a0, -17616);  // &0x83BB30 (kItemTbl)
        lw(a1, v0, node::kData);
        jal(ctx, 0x192438u, gen::fn_memcpy_00521250);
        lw(a0, s0, fs::kNode);
        jal(ctx, 0x192444u, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, s0, fs::kNode);
        jal(ctx, 0x192450u, gen::fn_datItemTblSetSections_0016c2f0);
        v0 = si(-1);
    }
    // 0x00192468 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00192480 sub_192480 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_192480(task) [H_FileSetup_DestroyItemTblReadTask]: destroy callback of "HonpenItemTblDataRead": destroys the
// file node if one is still held (work +4), then frees the work through RwFree (the slot 0x96017C).
void sub_192480(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00192480
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    using namespace boot;
    lw(s0, a0, task::kWork);
    lw(a0, s0, fs::kNode);
    if (a0 != 0) {
        // 0x0019249c
        charge(ctx, 3);
        jal(ctx, 0x19249Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, s0, fs::kNode);
    }
    // 0x001924a8
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x1924B4u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001924D0 sub_1924D0 -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1924D0(parent) [H_FileSetup_CreateHonpenItemTblReadTask]: RwCalloc(1, 12) work (the slot 0x960184, hint
// 0x40000), then kwlnTaskCreateWithAutoPriority(parent, 0x106F, "HonpenItemTblDataRead",
// H_FileSetup_UpdateHonpenItemTblDataReadTask, sub_192480, work); 0 when either fails. Listed in the step tables
// 0x5E4D00 / 0x5E4D20 (no direct caller).
void sub_1924D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001924d0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 1;
    a1 = 12;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, boot::rw::kCallocSlot);  // 0x960184 RwCalloc(1, size, 0x40000)
    jalr(ctx, 0x1924F4u, v0.u());
    if (v0 != 0) {
        // 0x00192510
        charge(ctx, 13);
        a0 = s0;
        a1 = boot::fs::kTaskPriority;  // 0x106F
        a2 = 0x5E0000;
        a2 = addiu(a2, 19584);  // "HonpenItemTblDataRead"
        a3 = 0x190000;
        a3 = addiu(a3, 9136);  // &H_FileSetup_UpdateHonpenItemTblDataReadTask
        t0 = 0x190000;
        t0 = addiu(t0, 9344);  // &sub_192480
        t1 = v0;
        jal(ctx, 0x192534u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        if (v0 == 0) {
            // 0x00192544
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00192504
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00192550 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00192570 sub_192570 -- 296 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_192570(task) [H_FileSetup_UpdateGojitudanItemTblDataReadTask]: The Answer's item-table read ("Gojitudan" =
// the epilogue): as H_FileSetup_UpdateHonpenItemTblDataReadTask but two files: step 0 requests
// "event/AEGIS_itemtbl.bin" (work +4) and "event/AEGIS_seq.bin" (work +8); step 1 waits for BOTH, copies the item
// table to 0x83BB30 and the sequence table to 0x83AB30, destroys both nodes, datItemTblSetSections(), returns -1.
void sub_192570(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00192570
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    using namespace boot;
    lw(s0, a0, task::kWork);  // s0 = work
    lw(v1, s0, fs::kStep);
    v0 = 1;
    bool loaded = false;  // host-side: both files are in (the copy runs) or not (the shared "return 0" block)
    if (v1 != v0) {
        // 0x00192590: steps other than 1
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x001925a0: step 0 -- request both files
            charge(ctx, 17);
            a0 = 0x5E0000;
            a0 = addiu(a0, 19616);  // "event/AEGIS_itemtbl.bin"
            a1 = 0;
            jal(ctx, 0x1925ACu, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s0, fs::kNode);
            a0 = 0x5E0000;
            a0 = addiu(a0, 19648);  // "event/AEGIS_seq.bin"
            a1 = 0;
            jal(ctx, 0x1925C4u, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s0, fs::kNode2);
            lw(v0, s0, fs::kStep);
            v0 = addiu(v0, 1);
            sw(v0, s0, fs::kStep);
        } else {
            // 0x00192598
            charge(ctx, 2);
        }
    } else {
        // 0x001925e4: step 1 -- wait for the item table, then for the sequence table
        charge(ctx, 6);
        lw(a0, s0, fs::kNode);
        jal(ctx, 0x1925E8u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
        v1 = 1;
        if (v0 == v1) {
            // 0x001925fc
            charge(ctx, 6);
            lw(a0, s0, fs::kNode2);
            jal(ctx, 0x192600u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            v1 = 1;
            loaded = v0 == v1;
        }
    }
    if (!loaded) {
        // 0x00192680: keep running
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00192614: both copied whole, both nodes dropped, the section pointers set; the task ends
        charge(ctx, 27);
        lw(v0, s0, fs::kNode);
        lw(a2, v0, node::kSize);
        a0 = 0x840000;
        a0 = addiu(a0, -17616);  // &0x83BB30 (kItemTbl)
        lw(a1, v0, node::kData);
        jal(ctx, 0x192628u, gen::fn_memcpy_00521250);
        lw(v0, s0, fs::kNode2);
        lw(a2, v0, node::kSize);
        a0 = 0x840000;
        a0 = addiu(a0, -21712);  // &0x83AB30 (kAegisSeq)
        lw(a1, v0, node::kData);
        jal(ctx, 0x192644u, gen::fn_memcpy_00521250);
        lw(a0, s0, fs::kNode);
        jal(ctx, 0x192650u, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, s0, fs::kNode);
        lw(a0, s0, fs::kNode2);
        jal(ctx, 0x192660u, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, s0, fs::kNode2);
        jal(ctx, 0x19266Cu, gen::fn_datItemTblSetSections_0016c2f0);
        v0 = si(-1);
    }
    // 0x00192684 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001926A0 sub_1926A0 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1926A0(task) [H_FileSetup_DestroyGojitudanItemTblReadTask]: destroy callback of "GojitudanItemTblDataRead":
// destroys the nodes still held (work +4, +8), then RwFree(work).
void sub_1926A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001926a0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    using namespace boot;
    lw(s0, a0, task::kWork);
    lw(a0, s0, fs::kNode);
    if (a0 != 0) {
        // 0x001926bc
        charge(ctx, 3);
        jal(ctx, 0x1926BCu, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, s0, fs::kNode);
    }
    // 0x001926c8
    charge(ctx, 3);
    lw(a0, s0, fs::kNode2);
    if (a0 != 0) {
        // 0x001926d4
        charge(ctx, 3);
        jal(ctx, 0x1926D4u, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, s0, fs::kNode2);
    }
    // 0x001926e0
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x1926ECu, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00192710 sub_192710 -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_192710(parent) [H_FileSetup_CreateGojitudanItemTblReadTask]: as sub_1924D0 for "GojitudanItemTblDataRead"
// (sub_192570 / sub_1926A0).
void sub_192710(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00192710
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 1;
    a1 = 12;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, boot::rw::kCallocSlot);  // 0x960184 RwCalloc(1, size, 0x40000)
    jalr(ctx, 0x192734u, v0.u());
    if (v0 != 0) {
        // 0x00192750
        charge(ctx, 13);
        a0 = s0;
        a1 = boot::fs::kTaskPriority;  // 0x106F
        a2 = 0x5E0000;
        a2 = addiu(a2, 19680);  // "GojitudanItemTblDataRead"
        a3 = 0x190000;
        a3 = addiu(a3, 9584);  // &sub_192570
        t0 = 0x190000;
        t0 = addiu(t0, 9888);  // &sub_1926A0
        t1 = v0;
        jal(ctx, 0x192774u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        if (v0 == 0) {
            // 0x00192784
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00192744
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00192790 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001927B0 sub_1927B0 -- 232 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1927B0(task) [H_FileSetup_UpdateHonpenFileSetupTask] ("HonpenFileSetup", The Journey): runs the creators of the
// step table 0x5E4D00 (copied to the frame: up to four creator pointers, 0-terminated) one after the other. Work:
// +0 phase (0 create the next, 1 wait), +4 step index, +8 the running sub-task.
//   phase 0: creator = table[step]; none left -> return -1 (setup done); else work+8 = creator(task) (through jalr:
//            $a0 is still the task), phase 1;
//   phase 1: when kwlnTaskGetState(sub-task) == 3 (ending), step++, phase 0.
// The Journey's table holds sub_1924D0 (the item-table read).
void sub_1927B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x001927b0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    using namespace boot;
    lw(s0, a0, task::kWork);  // s0 = work
    v0 = 0x5E0000;
    lwc1(f3, v0, 19712);  // 0x5E4D00: the step table (four words, through the FPU)
    v0 = 0x5E0000;
    lwc1(f2, v0, 19716);  // 0x5E4D04
    v0 = 0x5E0000;
    lwc1(f1, v0, 19720);  // 0x5E4D08
    v0 = 0x5E0000;
    lwc1(f0, v0, 19724);  // 0x5E4D0C
    swc1(f3, sp, 0x20);
    swc1(f2, sp, 0x24);
    swc1(f1, sp, 0x28);
    swc1(f0, sp, 0x2C);
    lw(v1, s0, fs::kStep);
    v0 = 1;
    bool done = false;  // host-side: the table ran out (return -1) instead of the shared "return 0" block
    if (v1 == v0) {
        // 0x00192858: phase 1 -- wait for the step's task to end, then the next step
        charge(ctx, 6);
        lw(a0, s0, fs::kSubTask);
        jal(ctx, 0x19285Cu, gen::fn_kwlnTaskGetState_00195290);
        v1 = 3;  // ending
        if (v0 == v1) {
            // 0x00192870
            charge(ctx, 4);
            lw(v0, s0, fs::kStepIndex);
            v0 = addiu(v0, 1);
            sw(v0, s0, fs::kStepIndex);
            sw(zero, s0, fs::kStep);
        }
    } else {
        // 0x00192800
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x00192808: other phases wait
            charge(ctx, 2);
        } else {
            // 0x00192810: phase 0 -- the next creator from the table in the frame
            charge(ctx, 7);
            lw(v0, s0, fs::kStepIndex);
            v0 = sll(v0, 2);
            v0 = addu(v0, sp);
            v0 = addiu(v0, 32);
            lw(v0, v0, 0);
            if (v0 != 0) {
                // 0x00192838: creator(task) -- $a0 still holds the task (the parent)
                charge(ctx, 8);
                jalr(ctx, 0x192838u, v0.u());
                sw(v0, s0, fs::kSubTask);
                lw(v0, s0, fs::kStep);
                v0 = addiu(v0, 1);
                sw(v0, s0, fs::kStep);
            } else {
                // 0x0019282c: no step left -- the set-up is done
                charge(ctx, 3);
                v0 = si(-1);
                done = true;
            }
        }
    }
    if (!done) {
        // 0x00192880: keep running
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x00192884 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001928A0 sub_1928A0 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1928A0(task) [H_FileSetup_DestroyFileSetupTask]: destroy callback of "HonpenFileSetup": RwFree(work).
void sub_1928A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001928a0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    v0 = 0x960000;
    lw(v0, v0, boot::rw::kFreeSlot);  // 0x96017C RwFree(work)
    jalr(ctx, 0x1928B4u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001928D0 sub_1928D0 -- 164 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1928D0() [H_FileSetup_CreateHonpenFileSetupTask]: creates the root-level "HonpenFileSetup" task (sub_1927B0 /
// sub_1928A0, priority 0x106F, 12-byte work) and on success sets the scenario to The Journey (sub_17D7F0(0)).
// Caller: sub_265030 (the title's new-game / continue path).
void sub_1928D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001928d0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 1;
    a1 = 12;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, boot::rw::kCallocSlot);  // 0x960184 RwCalloc(1, size, 0x40000)
    jalr(ctx, 0x1928F0u, v0.u());
    if (v0 != 0) {
        // 0x0019290c
        charge(ctx, 14);
        a0 = 0;
        a1 = boot::fs::kTaskPriority;  // 0x106F
        a2 = 0x5E0000;
        a2 = addiu(a2, 19728);  // "HonpenFileSetup"
        a3 = 0x190000;
        a3 = addiu(a3, 10160);  // &sub_1927B0
        t0 = 0x190000;
        t0 = addiu(t0, 10400);  // &sub_1928A0
        t1 = v0;
        jal(ctx, 0x192930u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        s0 = v0;
        if (s0 != 0) {
            // 0x00192950
            charge(ctx, 4);
            a0 = 0;
            jal(ctx, 0x192954u, gen::fn_sub_17D7F0_0017d7f0);
            v0 = s0;
        } else {
            // 0x00192944
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00192900
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00192960 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00192980 sub_192980 -- 232 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// sub_192980(task) [H_FileSetup_UpdateGojitudanFileSetupTask] ("GojitudanFileSetup", The Answer): sub_1927B0 over
// the step table 0x5E4D20 (sub_192710, the AEGIS item-table read).
void sub_192980(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x00192980
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    using namespace boot;
    lw(s0, a0, task::kWork);  // s0 = work
    v0 = 0x5E0000;
    lwc1(f3, v0, 19744);  // 0x5E4D20: the step table (four words, through the FPU)
    v0 = 0x5E0000;
    lwc1(f2, v0, 19748);  // 0x5E4D24
    v0 = 0x5E0000;
    lwc1(f1, v0, 19752);  // 0x5E4D28
    v0 = 0x5E0000;
    lwc1(f0, v0, 19756);  // 0x5E4D2C
    swc1(f3, sp, 0x20);
    swc1(f2, sp, 0x24);
    swc1(f1, sp, 0x28);
    swc1(f0, sp, 0x2C);
    lw(v1, s0, fs::kStep);
    v0 = 1;
    bool done = false;  // host-side: the table ran out (return -1) instead of the shared "return 0" block
    if (v1 == v0) {
        // 0x00192a28: phase 1 -- wait for the step's task to end, then the next step
        charge(ctx, 6);
        lw(a0, s0, fs::kSubTask);
        jal(ctx, 0x192A2Cu, gen::fn_kwlnTaskGetState_00195290);
        v1 = 3;  // ending
        if (v0 == v1) {
            // 0x00192a40
            charge(ctx, 4);
            lw(v0, s0, fs::kStepIndex);
            v0 = addiu(v0, 1);
            sw(v0, s0, fs::kStepIndex);
            sw(zero, s0, fs::kStep);
        }
    } else {
        // 0x001929d0
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x001929d8: other phases wait
            charge(ctx, 2);
        } else {
            // 0x001929e0: phase 0 -- the next creator from the table in the frame
            charge(ctx, 7);
            lw(v0, s0, fs::kStepIndex);
            v0 = sll(v0, 2);
            v0 = addu(v0, sp);
            v0 = addiu(v0, 32);
            lw(v0, v0, 0);
            if (v0 != 0) {
                // 0x00192a08: creator(task) -- $a0 still holds the task (the parent)
                charge(ctx, 8);
                jalr(ctx, 0x192A08u, v0.u());
                sw(v0, s0, fs::kSubTask);
                lw(v0, s0, fs::kStep);
                v0 = addiu(v0, 1);
                sw(v0, s0, fs::kStep);
            } else {
                // 0x001929fc: no step left -- the set-up is done
                charge(ctx, 3);
                v0 = si(-1);
                done = true;
            }
        }
    }
    if (!done) {
        // 0x00192a50: keep running
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x00192a54 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00192A70 sub_192A70 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_192A70(task): destroy callback of "GojitudanFileSetup": RwFree(work).
void sub_192A70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00192a70
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    v0 = 0x960000;
    lw(v0, v0, boot::rw::kFreeSlot);  // 0x96017C RwFree(work)
    jalr(ctx, 0x192A84u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00192AA0 sub_192AA0 -- 164 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_192AA0() [H_FileSetup_CreateGojitudanFileSetupTask]: creates "GojitudanFileSetup" (sub_192980 / sub_192A70)
// and on success sets the scenario to The Answer (sub_17D7F0(1)). Caller: sub_265030.
void sub_192AA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00192aa0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 1;
    a1 = 12;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, boot::rw::kCallocSlot);  // 0x960184 RwCalloc(1, size, 0x40000)
    jalr(ctx, 0x192AC0u, v0.u());
    if (v0 != 0) {
        // 0x00192adc
        charge(ctx, 14);
        a0 = 0;
        a1 = boot::fs::kTaskPriority;  // 0x106F
        a2 = 0x5E0000;
        a2 = addiu(a2, 19760);  // "GojitudanFileSetup"
        a3 = 0x190000;
        a3 = addiu(a3, 10624);  // &sub_192980
        t0 = 0x190000;
        t0 = addiu(t0, 10864);  // &sub_192A70
        t1 = v0;
        jal(ctx, 0x192B00u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        s0 = v0;
        if (s0 != 0) {
            // 0x00192b20
            charge(ctx, 4);
            a0 = 1;
            jal(ctx, 0x192B24u, gen::fn_sub_17D7F0_0017d7f0);
            v0 = s0;
        } else {
            // 0x00192b14
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00192ad0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00192b30 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00192B50 H_FileSetup_UpdateChoiceDataFileSetupTask -- 608 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// H_FileSetup_UpdateChoiceDataFileSetupTask(task) ("ChoiceDataFileSetup", the debug boot's scenario prompt, created by
// sub_192DE0 from kwlnRootUpdateTask state 5). Work (12 bytes): +0 step, +4 the choice (0 The Journey, 1 The Answer),
// +8 the setup task.
//   step 0: step 1;
//   step 1: confirm (gPadFlags 0x7E094E & 0x40) creates "HonpenFileSetup" (choice 0, scenario 0) or
//           "GojitudanFileSetup" (choice 1, scenario 1) inline (the bodies of sub_1928D0 / sub_192AA0), keeps it in
//           +8, step 2; else down (word_7E0952 & 0x1000) or up (& 0x4000) toggles the choice ((c + 1) & 1); then the
//           two menu strings 0x7CC0D8 / 0x7CC0DC (copied to the frame) are drawn: sub_104D10((4.0, 4.0), 0x7CC0E0,
//           string[choice]) (the debug printer);
//   step 2: when kwlnTaskGetState(+8) == 3 the task ends (-1).
void H_FileSetup_UpdateChoiceDataFileSetupTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00192b50
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    using namespace boot;
    lw(s0, a0, task::kWork);  // s0 = work
    lw(v1, s0, fs::kStep);
    v0 = 2;
    bool chosen_done = false;  // host-side: step 2 saw the set-up task end (return -1)
    if (v1 != v0) {
        // 0x00192b74
        charge(ctx, 3);
        a0 = 1;  // also RwCalloc's count below
        if (v1 == a0) {
            // 0x00192b9c: step 1 -- the prompt
            charge(ctx, 9);
            lwc1(f1, gp, -27672);  // 0x7CC0D8 (kChoiceNames[0]: "HONPEN")
            lwc1(f0, gp, -27668);  // 0x7CC0DC (kChoiceNames[1]: "GOJITUDAN")
            swc1(f1, sp, 0x30);
            swc1(f0, sp, 0x34);
            v0 = 0x7E0000;
            lhu(v0, v0, 2382);  // gPadFlags (0x7E094E)
            v0 = v0 & 0x40;     // confirm
            if (v0 == 0) {
                // 0x00192cec: no confirm -- a newly pressed up or down toggles the choice
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v1, v0, 2386);  // 0x7E0952 (newly pressed)
                v0 = v1 & 0x1000;   // up
                if (v0 == 0) {
                    // 0x00192d1c
                    charge(ctx, 3);
                    v0 = v1 & 0x4000;  // down
                    if (v0 != 0) {
                        // 0x00192d28
                        charge(ctx, 5);
                        lw(v0, s0, fs::kChoice);
                        v0 = addiu(v0, 1);
                        sw(v0, s0, fs::kChoice);
                        v0 = v0 & 0x1;
                        sw(v0, s0, fs::kChoice);
                    }
                } else {
                    // 0x00192d00
                    charge(ctx, 7);
                    lw(v0, s0, fs::kChoice);
                    v0 = addiu(v0, 1);
                    sw(v0, s0, fs::kChoice);
                    v0 = v0 & 0x1;
                    sw(v0, s0, fs::kChoice);
                }
            } else {
                // 0x00192bc0: confirm -- create the scenario's file set-up task inline
                charge(ctx, 3);
                lw(v0, s0, fs::kChoice);
                if (v0 == 0) {
                    // 0x00192bd4: The Journey (sub_1928D0's body)
                    charge(ctx, 8);
                    a1 = 12;
                    a2 = 0x40000;
                    v0 = 0x960000;
                    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc(1, 12)
                    jalr(ctx, 0x192BE4u, v0.u());
                    if (v0 != 0) {
                        // 0x00192c00
                        charge(ctx, 14);
                        a0 = 0;
                        a1 = 4207;
                        a2 = 0x5E0000;
                        a2 = addiu(a2, 19728);  // "HonpenFileSetup"
                        a3 = 0x190000;
                        a3 = addiu(a3, 10160);  // &sub_1927B0
                        t0 = 0x190000;
                        t0 = addiu(t0, 10400);  // &sub_1928A0
                        t1 = v0;
                        jal(ctx, 0x192C24u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
                        s1 = v0;
                        if (s1 != 0) {
                            // 0x00192c44
                            charge(ctx, 3);
                            a0 = 0;
                            jal(ctx, 0x192C48u, gen::fn_sub_17D7F0_0017d7f0);
                        } else {
                            // 0x00192c38
                            charge(ctx, 3);
                            s1 = 0;
                        }
                    } else {
                        // 0x00192bf4
                        charge(ctx, 3);
                        s1 = 0;
                    }
                    // 0x00192c50
                    charge(ctx, 3);
                    sw(s1, s0, fs::kSubTask);
                } else {
                    // 0x00192bcc / 0x00192c5c: The Answer (sub_192AA0's body)
                    charge(ctx, 2);
                    charge(ctx, 8);
                    a1 = 12;
                    a2 = 0x40000;
                    v0 = 0x960000;
                    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc(1, 12)
                    jalr(ctx, 0x192C6Cu, v0.u());
                    if (v0 != 0) {
                        // 0x00192c88
                        charge(ctx, 14);
                        a0 = 0;
                        a1 = 4207;
                        a2 = 0x5E0000;
                        a2 = addiu(a2, 19760);  // "GojitudanFileSetup"
                        a3 = 0x190000;
                        a3 = addiu(a3, 10624);  // &sub_192980
                        t0 = 0x190000;
                        t0 = addiu(t0, 10864);  // &sub_192A70
                        t1 = v0;
                        jal(ctx, 0x192CACu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
                        s1 = v0;
                        if (s1 != 0) {
                            // 0x00192ccc
                            charge(ctx, 3);
                            a0 = 1;
                            jal(ctx, 0x192CD0u, gen::fn_sub_17D7F0_0017d7f0);
                        } else {
                            // 0x00192cc0
                            charge(ctx, 3);
                            s1 = 0;
                        }
                    } else {
                        // 0x00192c7c
                        charge(ctx, 3);
                        s1 = 0;
                    }
                    // 0x00192cd8
                    charge(ctx, 1);
                    sw(s1, s0, fs::kSubTask);
                }
                // 0x00192cdc
                charge(ctx, 4);
                v0 = 2;
                sw(v0, s0, fs::kStep);
            }
            // 0x00192d3c: draw the current choice's name at (4.0, 4.0) -- two floats passed in $a0
            charge(ctx, 13);
            v0 = 0x40800000;  // 4.0f
            sw(v0, sp, 0x38);
            sw(v0, sp, 0x3C);
            lw(v0, s0, fs::kChoice);
            v0 = sll(v0, 2);
            v0 = addu(v0, sp);
            ld(a0, sp, 0x38);
            a1 = addiu(gp, -27664);  // "%s"
            lw(a2, v0, 48);          // the name in the frame copy
            jal(ctx, 0x192D60u, gen::fn_sub_104D10_00104d10);
        } else {
            // 0x00192b80
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00192b90: step 0 -> 1
                charge(ctx, 3);
                sw(a0, s0, fs::kStep);
            } else {
                // 0x00192b88
                charge(ctx, 2);
            }
        }
    } else {
        // 0x00192d70: step 2 -- wait for the set-up task to end
        charge(ctx, 6);
        lw(a0, s0, fs::kSubTask);
        jal(ctx, 0x192D74u, gen::fn_kwlnTaskGetState_00195290);
        v1 = 3;
        chosen_done = v0 == v1;
    }
    if (!chosen_done) {
        // 0x00192d94: keep running
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00192d88: the task ends
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x00192d98 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00192DB0 sub_192DB0 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_192DB0(task): destroy callback of "ChoiceDataFileSetup": RwFree(work).
void sub_192DB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00192db0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    v0 = 0x960000;
    lw(v0, v0, boot::rw::kFreeSlot);  // 0x96017C RwFree(work)
    jalr(ctx, 0x192DC4u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00192DE0 sub_192DE0 -- 136 bytes; frame 0x10: ra sp+0x0
// sub_192DE0() [H_FileSetup_CreateChoiceDataFileSetupTask]: creates the root-level "ChoiceDataFileSetup" task
// (H_FileSetup_UpdateChoiceDataFileSetupTask / sub_192DB0, priority 0x106F, 12-byte work). Caller:
// kwlnRootUpdateTask state 5.
void sub_192DE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00192de0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 1;
    a1 = 12;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, boot::rw::kCallocSlot);  // 0x960184 RwCalloc(1, size, 0x40000)
    jalr(ctx, 0x192DFCu, v0.u());
    if (v0 != 0) {
        // 0x00192e18
        charge(ctx, 13);
        a0 = 0;
        a1 = boot::fs::kTaskPriority;  // 0x106F
        a2 = 0x5E0000;
        a2 = addiu(a2, 19808);  // "ChoiceDataFileSetup"
        a3 = 0x190000;
        a3 = addiu(a3, 11088);  // &H_FileSetup_UpdateChoiceDataFileSetupTask
        t0 = 0x190000;
        t0 = addiu(t0, 11696);  // &sub_192DB0
        t1 = v0;
        jal(ctx, 0x192E3Cu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        if (v0 == 0) {
            // 0x00192e4c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00192e0c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00192e58 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00192E70 sub_192E70 -- 420 bytes; frame 0x120: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_192E70() [H_FileSetup_ApplyHikitugiData]: applies Persona 3 carry-over data (the buffers the carry-over load
// filled through sub_17A430, gp words 0x7CE050..0x7CE05C): the hero record *0x7CE050 gives the three social stats
// (+60 / +62 / +64 -> sub_16CFE0 / sub_16D090 / sub_16D160 on unit 1); every flag of the 0-terminated list 0x5E4D80
// (40 words, copied to the frame; the loop stops at the first 0 or at 256) takes its value from the old flag bitmap
// *0x7CE058 (datSetFlag(f, bit f)); every compendium entry of *0x7CE054 (256 x 52 bytes) whose first halfword has bit
// 0 set is rebuilt from its persona id (+2) in a fresh 52-byte record (memset, sub_176680), bit 0 set, and stored with
// sub_17CD30 (the compendium store).
void sub_192E70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00192e70
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a2 = 0x5E0000;
    a2 = addiu(a2, 19840);  // &0x5E4D80
    a1 = addiu(sp, 0x80);
    a0 = 20;
    for (;;) {
        // 0x00192e94
        charge(ctx, 9);
        lw(v1, a2, 0);
        lw(v0, a2, 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00192eb8
    charge(ctx, 16);
    lw(s0, gp, -19616);  // 0x7CE050
    a0 = 1;
    lh(a1, s0, 60);
    jal(ctx, 0x192EC4u, gen::fn_sub_16CFE0_0016cfe0);
    a0 = 1;
    lh(a1, s0, 62);
    jal(ctx, 0x192ED4u, gen::fn_sub_16D090_0016d090);
    a0 = 1;
    lh(a1, s0, 64);
    jal(ctx, 0x192EE4u, gen::fn_sub_16D160_0016d160);
    s0 = 0;
    for (;;) {
        // 0x00192f68
        charge(ctx, 3);
        v1 = slti(s0, 256);
        if (v1 != 0) {
            backedge(ctx);
            // 0x00192ef8
            charge(ctx, 6);
            v1 = sll(s0, 2);
            v1 = addu(v1, sp);
            v1 = addiu(v1, 128);
            lw(a0, v1, 0);
            if (a0 != 0) {
                // 0x00192f10
                charge(ctx, 3);
                v0 = sra(a0, 5);
                if (i64(a0) < 0) {
                    // 0x00192f1c
                    charge(ctx, 2);
                    v0 = addiu(a0, 31);
                    v0 = sra(v0, 5);
                }
                // 0x00192f24
                charge(ctx, 6);
                v1 = sll(v0, 2);
                lw(v0, gp, -19608);  // 0x7CE058
                a1 = addu(v0, v1);
                v1 = a0 & 0x1F;
                if (i64(a0) < 0) {
                    // 0x00192f3c
                    charge(ctx, 2);
                    if (v1 != 0) {
                        // 0x00192f44
                        charge(ctx, 1);
                        v1 = addiu(v1, -32);
                    }
                }
                // 0x00192f48
                charge(ctx, 8);
                v0 = 1;
                v1 = sllv(v0, v1);
                lw(v0, a1, 0);
                v0 = v1 & v0;
                a1 = sltu(0, v0);
                jal(ctx, 0x192F5Cu, gen::fn_datSetFlag_0016f1f0);
                s0 = addiu(s0, 1);
                continue;
            }
        }
        break;
    }
    // 0x00192f74
    charge(ctx, 4);
    lw(s0, gp, -19612);  // 0x7CE054
    s1 = 0;
    for (;;) {
        // 0x00192fec
        charge(ctx, 3);
        v1 = slti(s1, 256);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00192f84
        charge(ctx, 10);
        v1 = sll(s1, 1);
        v1 = addu(v1, s1);
        v1 = sll(v1, 2);
        v1 = addu(v1, s1);
        v1 = sll(v1, 2);
        s2 = addu(s0, v1);
        lhu(v1, s2, 0);
        v1 = v1 & 0x1;
        if (v1 != 0) {
            // 0x00192fac
            charge(ctx, 15);
            a0 = addiu(sp, 0x40);
            a1 = 0;
            a2 = 52;
            jal(ctx, 0x192FB8u, gen::fn_memset_00521408);
            a0 = addiu(sp, 0x40);
            lhu(a1, s2, 2);
            jal(ctx, 0x192FC8u, gen::fn_sub_176680_00176680);
            lhu(v0, sp, 0x40);
            v0 = v0 | 0x1;
            sh(v0, sp, 0x40);
            a0 = addiu(sp, 0x40);
            jal(ctx, 0x192FE0u, gen::fn_sub_17CD30_0017cd30);
        }
        // 0x00192fe8
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00192ff8
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x120);
}

// 0x00193020 H_FileSetup_UpdateHikitugiDataProcTask -- 768 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// H_FileSetup_UpdateHikitugiDataProcTask(task) ("HikitugiDataProc", the carry-over prompt of a new game; created by
// sub_1933D0 from a script command). Work: +0 step, +4 result (1 loaded, -1 none), +8 the card task.
//   step 0: frees any old carry-over buffers (gp 0x7CE050..0x7CE05C through RwFree) and allocates fresh ones
//           (RwCalloc 80 / 13,312 / 704 / 44 bytes: the hero record, the compendium, the flags, block 24), clears the
//           loaded word 0x7CDFFC, sets the carry-over mode word 0x7CE00C = 1, starts the card browser
//           Y_McProc_CreateMcProcDrawTask(task, 0), step 1;
//   step 1: when the card task ends (state 3): mode word = 0; loaded -> result 1, sub_192E70 applies the data;
//           else result -1; either way the buffers are freed and cleared, step 3;
//   step 3: -1 (the task ends). Returns 0 otherwise.
void H_FileSetup_UpdateHikitugiDataProcTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00193020
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    using namespace boot;
    s2 = a0;  // the task (the card browser's parent)
    lw(s1, a0, task::kWork);  // s1 = work
    lw(v1, s1, fs::kStep);
    v0 = 3;
    if (v1 == v0) {
        // 0x001932f4: step 3 -- done
        charge(ctx, 3);
        v0 = si(-1);
    } else {
        // 0x0019304c
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x00193190: step 1 -- wait for the card browser to end
            charge(ctx, 6);
            lw(a0, s1, fs::kCardTask);
            jal(ctx, 0x193194u, gen::fn_kwlnTaskGetState_00195290);
            v1 = 3;
            if (v0 == v1) {
                // 0x001931a8
                charge(ctx, 4);
                sw(zero, gp, -19684);  // 0x7CE00C kHikitugiMode = 0
                lw(v0, gp, -19700);  // 0x7CDFFC kHikitugiLoaded
                if (v0 == 0) {
                    // 0x0019325c: nothing loaded -- free the buffers, result -1
                    charge(ctx, 3);
                    lw(a0, gp, -19616);  // 0x7CE050
                    if (a0 != 0) {
                        // 0x00193268
                        charge(ctx, 4);
                        v0 = 0x960000;
                        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
                        jalr(ctx, 0x193270u, v0.u());
                    }
                    // 0x00193278
                    charge(ctx, 3);
                    lw(a0, gp, -19612);  // 0x7CE054
                    if (a0 != 0) {
                        // 0x00193284
                        charge(ctx, 4);
                        v0 = 0x960000;
                        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
                        jalr(ctx, 0x19328Cu, v0.u());
                    }
                    // 0x00193294
                    charge(ctx, 3);
                    lw(a0, gp, -19608);  // 0x7CE058
                    if (a0 != 0) {
                        // 0x001932a0
                        charge(ctx, 4);
                        v0 = 0x960000;
                        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
                        jalr(ctx, 0x1932A8u, v0.u());
                    }
                    // 0x001932b0
                    charge(ctx, 3);
                    lw(a0, gp, -19604);  // 0x7CE05C
                    if (a0 != 0) {
                        // 0x001932bc
                        charge(ctx, 4);
                        v0 = 0x960000;
                        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
                        jalr(ctx, 0x1932C4u, v0.u());
                    }
                    // 0x001932cc
                    charge(ctx, 10);
                    sw(zero, gp, -19616);  // 0x7CE050
                    sw(zero, gp, -19612);  // 0x7CE054
                    sw(zero, gp, -19608);  // 0x7CE058
                    sw(zero, gp, -19604);  // 0x7CE05C
                    v0 = si(-1);
                    sw(v0, s1, fs::kResult);
                    v0 = 3;
                    sw(v0, s1, fs::kStep);
                } else {
                    // 0x001931b8: a save was loaded -- result 1, apply it, free the buffers
                    charge(ctx, 8);
                    v0 = 1;
                    sw(v0, s1, fs::kResult);
                    jal(ctx, 0x1931C0u, gen::fn_sub_192E70_00192e70);
                    sw(zero, gp, -19700);  // 0x7CDFFC
                    lw(a0, gp, -19616);  // 0x7CE050
                    if (a0 != 0) {
                        // 0x001931d8
                        charge(ctx, 4);
                        v0 = 0x960000;
                        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
                        jalr(ctx, 0x1931E0u, v0.u());
                    }
                    // 0x001931e8
                    charge(ctx, 3);
                    lw(a0, gp, -19612);  // 0x7CE054
                    if (a0 != 0) {
                        // 0x001931f4
                        charge(ctx, 4);
                        v0 = 0x960000;
                        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
                        jalr(ctx, 0x1931FCu, v0.u());
                    }
                    // 0x00193204
                    charge(ctx, 3);
                    lw(a0, gp, -19608);  // 0x7CE058
                    if (a0 != 0) {
                        // 0x00193210
                        charge(ctx, 4);
                        v0 = 0x960000;
                        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
                        jalr(ctx, 0x193218u, v0.u());
                    }
                    // 0x00193220
                    charge(ctx, 3);
                    lw(a0, gp, -19604);  // 0x7CE05C
                    if (a0 != 0) {
                        // 0x0019322c
                        charge(ctx, 4);
                        v0 = 0x960000;
                        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
                        jalr(ctx, 0x193234u, v0.u());
                    }
                    // 0x0019323c
                    charge(ctx, 8);
                    sw(zero, gp, -19616);  // 0x7CE050
                    sw(zero, gp, -19612);  // 0x7CE054
                    sw(zero, gp, -19608);  // 0x7CE058
                    sw(zero, gp, -19604);  // 0x7CE05C
                    v0 = 3;
                    sw(v0, s1, fs::kStep);
                }
            }
        } else {
            // 0x00193058
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00193068: step 0 -- fresh carry-over buffers, carry-over mode on, open the card browser
                charge(ctx, 3);
                lw(a0, gp, -19616);  // 0x7CE050
                if (a0 != 0) {
                    // 0x00193074
                    charge(ctx, 4);
                    v0 = 0x960000;
                    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
                    jalr(ctx, 0x19307Cu, v0.u());
                }
                // 0x00193084
                charge(ctx, 3);
                lw(a0, gp, -19612);  // 0x7CE054
                if (a0 != 0) {
                    // 0x00193090
                    charge(ctx, 4);
                    v0 = 0x960000;
                    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
                    jalr(ctx, 0x193098u, v0.u());
                }
                // 0x001930a0
                charge(ctx, 3);
                lw(a0, gp, -19608);  // 0x7CE058
                if (a0 != 0) {
                    // 0x001930ac
                    charge(ctx, 4);
                    v0 = 0x960000;
                    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
                    jalr(ctx, 0x1930B4u, v0.u());
                }
                // 0x001930bc
                charge(ctx, 3);
                lw(a0, gp, -19604);  // 0x7CE05C
                if (a0 != 0) {
                    // 0x001930c8
                    charge(ctx, 4);
                    v0 = 0x960000;
                    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
                    jalr(ctx, 0x1930D0u, v0.u());
                }
                // 0x001930d8
                charge(ctx, 46);
                sw(zero, gp, -19616);  // 0x7CE050
                sw(zero, gp, -19612);  // 0x7CE054
                sw(zero, gp, -19608);  // 0x7CE058
                sw(zero, gp, -19604);  // 0x7CE05C
                s0 = 0x960000;
                s0 = addiu(s0, 388);  // &0x960184
                a0 = 1;
                a1 = 80;  // the hero record (block 2)
                a2 = 0x40000;
                lw(v0, s0, 0);  // 0x960184
                jalr(ctx, 0x193100u, v0.u());
                sw(v0, gp, -19616);  // 0x7CE050
                a0 = 1;
                a1 = 13312;  // the compendium (block 16: 256 x 52)
                a2 = 0x40000;
                lw(v0, s0, 0);  // 0x960184
                jalr(ctx, 0x19311Cu, v0.u());
                sw(v0, gp, -19612);  // 0x7CE054
                a0 = 1;
                a1 = 704;  // the flags (block 17)
                a2 = 0x40000;
                lw(v0, s0, 0);  // 0x960184
                jalr(ctx, 0x193138u, v0.u());
                sw(v0, gp, -19608);  // 0x7CE058
                a0 = 1;
                a1 = 44;  // block 24
                a2 = 0x40000;
                lw(v0, s0, 0);  // 0x960184
                jalr(ctx, 0x193154u, v0.u());
                sw(v0, gp, -19604);  // 0x7CE05C
                sw(zero, gp, -19700);  // 0x7CDFFC
                v0 = 1;
                sw(v0, gp, -19684);  // 0x7CE00C kHikitugiMode = 1
                a0 = s2;
                a1 = 0;
                jal(ctx, 0x193174u, gen::fn_Y_McProc_CreateMcProcDrawTask_00420340);
                sw(v0, s1, fs::kCardTask);
                v0 = 1;
                sw(v0, s1, fs::kStep);
            } else {
                // 0x00193060
                charge(ctx, 2);
            }
        }
        // 0x00193300
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x00193304 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00193320 sub_193320 -- 168 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_193320(task): destroy callback of "HikitugiDataProc": frees the four carry-over buffers still allocated, then
// the work.
void sub_193320(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00193320
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(a0, gp, -19616);  // 0x7CE050
    if (a0 != 0) {
        // 0x0019333c
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, boot::rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x193344u, v0.u());
    }
    // 0x0019334c
    charge(ctx, 3);
    lw(a0, gp, -19612);  // 0x7CE054
    if (a0 != 0) {
        // 0x00193358
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, boot::rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x193360u, v0.u());
    }
    // 0x00193368
    charge(ctx, 3);
    lw(a0, gp, -19608);  // 0x7CE058
    if (a0 != 0) {
        // 0x00193374
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, boot::rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x19337Cu, v0.u());
    }
    // 0x00193384
    charge(ctx, 3);
    lw(a0, gp, -19604);  // 0x7CE05C
    if (a0 != 0) {
        // 0x00193390
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, boot::rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x193398u, v0.u());
    }
    // 0x001933a0
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, boot::rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x1933ACu, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001933D0 sub_1933D0 -- 136 bytes; frame 0x10: ra sp+0x0
// sub_1933D0() [H_FileSetup_StartHikitugiDataProc]: a script command (no direct caller): creates "HikitugiDataProc"
// (priority 0x106F) and keeps it in 0x7CE060 (0 on failure); returns 1 (the command is done).
void sub_1933D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001933d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 1;
    a1 = 12;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, boot::rw::kCallocSlot);  // 0x960184 RwCalloc(1, size, 0x40000)
    jalr(ctx, 0x1933ECu, v0.u());
    if (v0 != 0) {
        // 0x00193408
        charge(ctx, 13);
        a0 = 0;
        a1 = boot::fs::kTaskPriority;  // 0x106F
        a2 = 0x5E0000;
        a2 = addiu(a2, 20000);  // "HikitugiDataProc"
        a3 = 0x190000;
        a3 = addiu(a3, 12320);  // &H_FileSetup_UpdateHikitugiDataProcTask
        t0 = 0x190000;
        t0 = addiu(t0, 13088);  // &sub_193320
        t1 = v0;
        jal(ctx, 0x19342Cu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        if (v0 == 0) {
            // 0x0019343c
            charge(ctx, 1);
            v0 = 0;
        }
    } else {
        // 0x001933fc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00193440 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    sw(v0, gp, -19600);  // 0x7CE060
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00193460 sub_193460 -- 132 bytes; frame 0x10: ra sp+0x0
// sub_193460() [H_FileSetup_WaitHikitugiDataProc]: the matching wait command: when the task in 0x7CE060 is ending
// (state 3) clears the word and returns 1; else returns 0 and, once the task's result is known, reports it to the
// script (scrSetIntReturnVal(1) loaded / 0 none).
void sub_193460(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00193460
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, -19600);  // 0x7CE060
    jal(ctx, 0x19346Cu, gen::fn_kwlnTaskGetState_00195290);
    v1 = 3;
    if (v0 != v1) {
        // 0x00193490
        charge(ctx, 6);
        lw(v0, gp, -19600);  // 0x7CE060
        lw(v0, v0, 60);
        lw(v1, v0, 4);
        a0 = 1;
        if (v1 != a0) {
            // 0x001934b8
            charge(ctx, 3);
            v0 = si(-1);
            if (v1 == v0) {
                // 0x001934c4
                charge(ctx, 3);
                a0 = 0;
                jal(ctx, 0x1934C8u, gen::fn_scrSetIntReturnVal_0035f060);
            }
        } else {
            // 0x001934a8
            charge(ctx, 4);
            jal(ctx, 0x1934A8u, gen::fn_scrSetIntReturnVal_0035f060);
        }
        // 0x001934d0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00193480
        charge(ctx, 4);
        sw(zero, gp, -19600);  // 0x7CE060
        v0 = 1;
    }
    // 0x001934d4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001938B0 sub_1938B0 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1938B0(task): destroy callback of "H_TstDvdChkDraw": RwFree(work).
void sub_1938B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001938b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    v0 = 0x960000;
    lw(v0, v0, boot::rw::kFreeSlot);  // 0x96017C RwFree(work)
    jalr(ctx, 0x1938C4u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001938E0 sub_1938E0 -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1938E0(parent) [H_FileSetup_CreateTstDvdChkDrawTask]: creates the disc check task "H_TstDvdChkDraw"
// (H_FileSetup_UpdateTstDvdChkDrawTask, which stays recompiled: it calls sceCd* itself) with a 5,152-byte work.
// Caller: sub_265030.
void sub_1938E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001938e0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 1;
    a1 = 5152;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, boot::rw::kCallocSlot);  // 0x960184 RwCalloc(1, size, 0x40000)
    jalr(ctx, 0x193904u, v0.u());
    if (v0 != 0) {
        // 0x00193920
        charge(ctx, 13);
        a0 = s0;
        a1 = boot::fs::kTaskPriority;  // 0x106F
        a2 = 0x5E0000;
        a2 = addiu(a2, 20080);  // "H_TstDvdChkDraw"
        a3 = 0x190000;
        a3 = addiu(a3, 13552);  // &H_FileSetup_UpdateTstDvdChkDrawTask
        t0 = 0x190000;
        t0 = addiu(t0, 14512);  // &sub_1938B0
        t1 = v0;
        jal(ctx, 0x193944u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        if (v0 == 0) {
            // 0x00193954
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00193914
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00193960 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00193980 main -- 32 bytes; frame 0x10: ra sp+0x0
// main(argc, argv): printf("jpx235\n") (the build tag), then initAndLoop(0). Never returns (kwlnMain loops forever).
void main(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00193980
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = addiu(gp, -27656);  // "jpx235\n"
    jal(ctx, 0x19398Cu, gen::fn_printf_005225a8);
    a0 = 0;
    jal(ctx, 0x193998u, gen::fn_initAndLoop_001939b0);  // does not return
}

// 0x001939B0 initAndLoop -- 16 bytes; frame 0x10: ra sp+0x0
// initAndLoop(): kwlnMain() (tail of main; the frame keeps $ra for the never-taken return).
void initAndLoop(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x001939b0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1939B8u, gen::fn_kwlnMain_001984c0);  // does not return
}

// 0x00194750 sub_194750 -- 344 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_194750(task, depth) [kwlnTaskPrintTree]: prints one task of the "process tree" debug dump and recurses: "%s+-%s
// [%d]" (the indent string 0x847E50, the name, the priority), " <S>" when paused (state bit 5), " <!P>" when its
// pads are neutral (bit 4), a newline; then the first child (+0x50) one level deeper -- the indent column at depth
// gets '|' when the task has a next sibling, ' ' otherwise -- and the next sibling (+0x54) at the same depth.
void sub_194750(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00194750
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = 0x5E0000;
    a0 = addiu(a0, 20168);  // "%s+-%s [%d]"
    a1 = 0x840000;
    a1 = addiu(a1, 32336);  // &0x847E50
    a2 = s1;
    lw(a3, s1, 32);
    jal(ctx, 0x194784u, gen::fn_printf_005225a8);
    lw(v0, s1, 28);
    v0 = v0 & 0x20;
    if (v0 != 0) {
        // 0x0019479c
        charge(ctx, 3);
        a0 = addiu(gp, -27640);  // " <S>"
        jal(ctx, 0x1947A0u, gen::fn_printf_005225a8);
    }
    // 0x001947a8
    charge(ctx, 4);
    lw(v0, s1, 28);
    v0 = v0 & 0x10;
    if (v0 != 0) {
        // 0x001947b8
        charge(ctx, 3);
        a0 = addiu(gp, -27632);  // " <!P>"
        jal(ctx, 0x1947BCu, gen::fn_printf_005225a8);
    }
    // 0x001947c4
    charge(ctx, 6);
    a0 = addiu(gp, -27624);  // "\n"
    jal(ctx, 0x1947C8u, gen::fn_printf_005225a8);
    lw(v1, s1, 80);
    if (v1 != 0) {
        // 0x001947dc
        charge(ctx, 3);
        lw(v0, s1, 76);
        if (v0 != 0) {
            // 0x001947fc
            charge(ctx, 3);
            lw(v0, s1, 84);
            if (v0 != 0) {
                // 0x00194828
                charge(ctx, 6);
                a0 = 124;
                v1 = sll(s0, 2);
                v0 = 0x840000;
                v0 = addiu(v0, 32336);  // &0x847E50
                v0 = addu(v0, v1);
                sb(a0, v0, 0);
            } else {
                // 0x00194808
                charge(ctx, 8);
                a0 = 32;
                v1 = sll(s0, 2);
                v0 = 0x840000;
                v0 = addiu(v0, 32336);  // &0x847E50
                v0 = addu(v0, v1);
                sb(a0, v0, 0);
            }
        } else {
            // 0x001947e8
            charge(ctx, 5);
            v1 = 32;
            v0 = 0x840000;
            sb(v1, v0, 32336);  // 0x847E50
        }
        // 0x00194840
        charge(ctx, 13);
        s2 = sll(s0, 2);
        v0 = 0x840000;
        v0 = addiu(v0, 32340);  // &0x847E54
        v0 = addu(v0, s2);
        sb(zero, v0, 0);
        a1 = addiu(s0, 1);
        lw(a0, s1, 80);
        jal(ctx, 0x19485Cu, gen::fn_sub_194750_00194750);
        v1 = 0x840000;
        v1 = addiu(v1, 32336);  // &0x847E50
        v1 = addu(v1, s2);
        sb(zero, v1, 0);
    }
    // 0x00194874
    charge(ctx, 3);
    lw(a0, s1, 84);
    if (a0 != 0) {
        // 0x00194880
        charge(ctx, 3);
        a1 = s0;
        jal(ctx, 0x194884u, gen::fn_sub_194750_00194750);
    }
    // 0x0019488c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001948B0 sub_1948B0 -- 292 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1948B0() [kwlnTaskPrintAll]: "<<< process tree >>>": the root tasks (parent +0x4C == 0) of the starting,
// running and ending lists through sub_194750, after filling the 64-byte indent buffer 0x847E50 with spaces.
// Callers: H_Malloc's failure path, sub_3B5AB0.
void sub_1948B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001948b0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0x5E0000;
    a0 = addiu(a0, 20192);  // "<<< process tree >>>\n"
    jal(ctx, 0x1948C4u, gen::fn_printf_005225a8);
    a1 = 0;
    a0 = 32;
    v1 = 0x840000;
    v1 = addiu(v1, 32336);  // &0x847E50
    for (;;) {
        // 0x001948f0
        charge(ctx, 4);
        v0 = slti(a1, 64);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001948e4
        charge(ctx, 3);
        v0 = addu(v1, a1);
        sb(a0, v0, 0);
        a1 = addiu(a1, 1);
    }
    // 0x00194900
    charge(ctx, 3);
    lw(s0, gp, -19596);  // gKwlnTaskStartingList
    for (;;) {
        // 0x00194934
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0019490c
        charge(ctx, 3);
        lw(v0, s0, 76);
        if (v0 == 0) {
            // 0x00194918
            charge(ctx, 6);
            v0 = 0x840000;
            sb(zero, v0, 32336);  // 0x847E50
            a0 = s0;
            a1 = 0;
            jal(ctx, 0x194928u, gen::fn_sub_194750_00194750);
        }
        // 0x00194930
        charge(ctx, 1);
        lw(s0, s0, 64);
    }
    // 0x0019493c
    charge(ctx, 3);
    lw(s0, gp, -19572);  // gKwlnTaskRunningList
    for (;;) {
        // 0x00194970
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00194948
        charge(ctx, 3);
        lw(v0, s0, 76);
        if (v0 == 0) {
            // 0x00194954
            charge(ctx, 6);
            v0 = 0x840000;
            sb(zero, v0, 32336);  // 0x847E50
            a0 = s0;
            a1 = 0;
            jal(ctx, 0x194964u, gen::fn_sub_194750_00194750);
        }
        // 0x0019496c
        charge(ctx, 1);
        lw(s0, s0, 64);
    }
    // 0x00194978
    charge(ctx, 3);
    lw(s0, gp, -19584);  // gKwlnTaskEndingList
    for (;;) {
        // 0x001949ac
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00194984
        charge(ctx, 3);
        lw(v0, s0, 76);
        if (v0 == 0) {
            // 0x00194990
            charge(ctx, 6);
            v0 = 0x840000;
            sb(zero, v0, 32336);  // 0x847E50
            a0 = s0;
            a1 = 0;
            jal(ctx, 0x1949A0u, gen::fn_sub_194750_00194750);
        }
        // 0x001949a8
        charge(ctx, 1);
        lw(s0, s0, 64);
    }
    // 0x001949b4
    charge(ctx, 8);
    a0 = addiu(gp, -27648);  // "\n\n"
    jal(ctx, 0x1949B8u, gen::fn_printf_005225a8);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00195980 kwlnSetupMainCameraViewport -- 764 bytes; frame 0x80: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// kwlnSetupMainCameraViewport(camera, rect{x, y, w, h}*, view_scale $f13): (re)builds the camera's rasters for a
// viewport. The first call remembers the current raster size (camera +96 = the frame-buffer raster, +100 = the Z
// raster; raster +12 / +16 = width / height) in 0x847E90..0x847E9C; a null rect means the whole raster (built in
// 0x847EA0..0x847EAC); in an exclusive video mode (mode info flag bit 0: sub_4CA5B0 / sub_4CA560, the current video
// mode and its info) the rect becomes {0, 0, mode width, mode height}. With a positive size: both rasters are
// destroyed (sub_4CDE90) and recreated (sub_4CE0F0(w, h, 0, 2 camera / 1 Z)); on success the view window is set
// (sub_4C9F90) to (scale * v, v) in the exclusive mode, else scaled by the raster's aspect ratio; on failure the
// remembered size is rebuilt instead. Caller: kwlnInitRenderer.
void kwlnSetupMainCameraViewport(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00195980
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s1 = a0;
    s0 = a1;
    mov_s(f21, f12);
    mov_s(f20, f13);
    if (s1 != 0) {
        // 0x001959b8: remember the camera's raster size the first time (0x847E90: {x, y, w, h})
        charge(ctx, 4);
        v0 = 0x840000;
        lw(v0, v0, 32408);  // 0x847E98
        bool remembered = false;  // host-side: both remembered words are set (skip 0x1959d8)
        if (v0 != 0) {
            // 0x001959c8
            charge(ctx, 4);
            v0 = 0x840000;
            lw(v0, v0, 32412);  // 0x847E9C
            remembered = v0 != 0;
        }
        if (!remembered) {
            // 0x001959d8
            charge(ctx, 11);
            v0 = 0x840000;
            sw(zero, v0, 32404);  // 0x847E94
            v0 = 0x840000;
            sw(zero, v0, 32400);  // 0x847E90
            lw(a0, s1, 96);
            lw(v1, a0, 12);
            v0 = 0x840000;
            sw(v1, v0, 32408);  // 0x847E98
            lw(v1, a0, 16);
            v0 = 0x840000;
            sw(v1, v0, 32412);  // 0x847E9C
        }
        // 0x00195a04: the current video mode's info into sp+0x60 (w, h, ..., flags at +0x6C)
        charge(ctx, 8);
        jal(ctx, 0x195A04u, gen::fn_sub_4CA5B0_004ca5b0);
        a0 = addiu(sp, 0x60);
        a1 = v0;
        jal(ctx, 0x195A14u, gen::fn_sub_4CA560_004ca560);
        if (s0 == 0) {
            // 0x00195a24
            charge(ctx, 13);
            s0 = 0x840000;
            s0 = addiu(s0, 32416);  // &0x847EA0
            lw(a1, s1, 96);
            lw(a0, a1, 12);
            v1 = 0x840000;
            sw(a0, v1, 32424);  // 0x847EA8
            lw(a0, a1, 16);
            v1 = 0x840000;
            sw(a0, v1, 32428);  // 0x847EAC
            v1 = 0x840000;
            sw(zero, v1, 32420);  // 0x847EA4
            v1 = 0x840000;
            sw(zero, v1, 32416);  // 0x847EA0
        }
        // 0x00195a58
        charge(ctx, 4);
        lw(v1, sp, 0x6C);
        v1 = v1 & 0x1;
        if (v1 != 0) {
            // 0x00195a68
            charge(ctx, 6);
            sw(zero, s0, 4);
            sw(zero, s0, 0);
            lw(v1, sp, 0x60);
            sw(v1, s0, 8);
            lw(v1, sp, 0x64);
            sw(v1, s0, 12);
        }
        // 0x00195a80
        charge(ctx, 3);
        lw(v1, s0, 8);
        if (i64(v1) > 0) {
            // 0x00195a8c
            charge(ctx, 3);
            lw(v1, s0, 12);
            if (i64(v1) > 0) {
                // 0x00195a98
                charge(ctx, 3);
                lw(a0, s1, 96);
                if (a0 != 0) {
                    // 0x00195aa4
                    charge(ctx, 2);
                    jal(ctx, 0x195AA4u, gen::fn_sub_4CDE90_004cde90);
                }
                // 0x00195aac
                charge(ctx, 3);
                lw(a0, s1, 100);
                if (a0 != 0) {
                    // 0x00195ab8
                    charge(ctx, 2);
                    jal(ctx, 0x195AB8u, gen::fn_sub_4CDE90_004cde90);
                }
                // 0x00195ac0
                charge(ctx, 16);
                lw(a0, s0, 8);
                lw(a1, s0, 12);
                a2 = 0;
                a3 = 2;
                jal(ctx, 0x195AD0u, gen::fn_sub_4CE0F0_004ce0f0);
                s3 = v0;
                lw(a0, s0, 8);
                lw(a1, s0, 12);
                a2 = 0;
                a3 = 1;
                jal(ctx, 0x195AECu, gen::fn_sub_4CE0F0_004ce0f0);
                s2 = v0;
                bool both = false;  // host-side: both new rasters exist
                if (s3 != 0) {
                    // 0x00195b00
                    charge(ctx, 2);
                    both = s2 != 0;
                }
                if (both) {
                    // 0x00195b08: keep them, set the view window
                    charge(ctx, 4);
                    sw(s3, s1, 96);
                    sw(s2, s1, 100);
                    // 0x00195b98
                    charge(ctx, 4);
                    lw(v0, sp, 0x6C);
                    v0 = v0 & 0x1;
                    if (v0 == 0) {
                        // 0x00195bbc
                        charge(ctx, 10);
                        lw(v0, s1, 96);
                        lw(v0, v0, 12);
                        sw(v0, s0, 8);
                        lw(v0, s1, 96);
                        lw(v1, v0, 16);
                        sw(v1, s0, 12);
                        lw(v0, s0, 8);
                        at = slt(v1, v0);
                        if (at == 0) {
                            // 0x00195c1c
                            charge(ctx, 10);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                            mul_s(f1, f0, f21);
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                            div_s(f0, f1, f0);
                            swc1(f0, sp, 0x78);
                            swc1(f21, sp, 0x7C);
                        } else {
                            // 0x00195be4
                            charge(ctx, 14);
                            swc1(f21, sp, 0x78);
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                            mul_s(f1, f0, f21);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                            div_s(f0, f1, f0);
                            swc1(f0, sp, 0x7C);
                        }
                    } else {
                        // 0x00195ba8
                        charge(ctx, 5);
                        mul_s(f0, f21, f20);
                        swc1(f0, sp, 0x78);
                        swc1(f21, sp, 0x7C);
                    }
                    // 0x00195c44
                    charge(ctx, 4);
                    a0 = s1;
                    a1 = addiu(sp, 0x78);
                    jal(ctx, 0x195C4Cu, gen::fn_sub_4C9F90_004c9f90);
                    // 0x00195c54 (the shared epilogue, written out on this path)
                    charge(ctx, 10);
                    ld(ra, sp, 0x50);
                    lq(s3, sp, 0x40);
                    lq(s2, sp, 0x30);
                    lq(s1, sp, 0x20);
                    lq(s0, sp, 0x10);
                    lwc1(f21, sp, 0x4);
                    lwc1(f20, sp, 0x0);
                    sp = addiu(sp, 0x80);
                    return;
                }
                // 0x00195b18: a raster failed -- free what was made, rebuild at the remembered size
                charge(ctx, 2);
                if (s3 != 0) {
                    // 0x00195b20
                    charge(ctx, 3);
                    a0 = s3;
                    jal(ctx, 0x195B24u, gen::fn_sub_4CDE90_004cde90);
                }
                // 0x00195b2c
                charge(ctx, 2);
                if (s2 != 0) {
                    // 0x00195b34
                    charge(ctx, 3);
                    a0 = s2;
                    jal(ctx, 0x195B38u, gen::fn_sub_4CDE90_004cde90);
                }
                // 0x00195b40
                charge(ctx, 22);
                v0 = 0x840000;
                lw(v0, v0, 32408);  // 0x847E98
                sw(v0, s0, 8);
                v0 = 0x840000;
                lw(a1, v0, 32412);  // 0x847E9C
                sw(a1, s0, 12);
                lw(a0, s0, 8);
                a2 = 0;
                a3 = 2;
                jal(ctx, 0x195B64u, gen::fn_sub_4CE0F0_004ce0f0);
                s2 = v0;
                lw(a0, s0, 8);
                lw(a1, s0, 12);
                a2 = 0;
                a3 = 1;
                jal(ctx, 0x195B80u, gen::fn_sub_4CE0F0_004ce0f0);
                sw(s2, s1, 96);
                sw(v0, s1, 100);
            }
        }
    }
    // 0x00195c54 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00195C80 kwlnCreateMainCamera -- 344 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// kwlnCreateMainCamera(width, height, zbuffer): a camera (sub_4CA090), a frame attached to it (sub_4CAF10 +
// sub_4D1840), the frame-buffer raster at camera +96 (sub_4CE0F0(w, h, 0, 2)) and, when `zbuffer`, the Z raster at +100
// (type 1). Returns the camera when everything exists; otherwise destroys what was made (frame, rasters, camera:
// sub_4CAF80 / sub_4CDE90 / sub_4CA030) and returns 0. Caller: kwlnInitRenderer (640 x 448, Z on).
void kwlnCreateMainCamera(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00195c80
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;  // width
    s2 = a1;  // height
    s0 = a2;  // with a Z buffer
    jal(ctx, 0x195CA4u, gen::fn_sub_4CA090_004ca090);  // the camera
    s1 = v0;
    bool complete = false;  // host-side: camera, frame, colour raster and (when asked) Z raster all exist
    if (s1 != 0) {
        // 0x00195cb8: a frame for it, the colour raster (type 2) at +96, the Z raster (type 1) at +100
        charge(ctx, 15);
        jal(ctx, 0x195CB8u, gen::fn_sub_4CAF10_004caf10);
        a0 = s1;
        a1 = v0;
        jal(ctx, 0x195CC8u, gen::fn_sub_4D1840_004d1840);
        a0 = s3;
        a1 = s2;
        a2 = 0;
        a3 = 2;
        jal(ctx, 0x195CE0u, gen::fn_sub_4CE0F0_004ce0f0);
        sw(v0, s1, 96);
        if (s0 != 0) {
            // 0x00195cf4
            charge(ctx, 7);
            a0 = s3;
            a1 = s2;
            a2 = 0;
            a3 = 1;
            jal(ctx, 0x195D04u, gen::fn_sub_4CE0F0_004ce0f0);
            sw(v0, s1, 100);
        }
        // 0x00195d10: the checks
        charge(ctx, 3);
        lw(v0, s1, 4);  // the frame
        if (v0 != 0) {
            // 0x00195d1c
            charge(ctx, 3);
            lw(v0, s1, 96);  // the colour raster
            if (v0 != 0) {
                // 0x00195d28
                charge(ctx, 2);
                if (s0 != 0) {
                    // 0x00195d30
                    charge(ctx, 3);
                    lw(v0, s1, 100);  // the Z raster
                    complete = v0 != 0;
                } else {
                    complete = true;
                }
            }
        }
    }
    if (complete) {
        // 0x00195d3c
        charge(ctx, 3);
        v0 = s1;
        // 0x00195db8 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
    // 0x00195d48: undo what was made, return 0
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x00195d50
        charge(ctx, 3);
        lw(s0, s1, 4);
        if (s0 != 0) {
            // 0x00195d5c
            charge(ctx, 7);
            a0 = s1;
            a1 = 0;
            jal(ctx, 0x195D64u, gen::fn_sub_4D1840_004d1840);
            a0 = s0;
            jal(ctx, 0x195D70u, gen::fn_sub_4CAF80_004caf80);
        }
        // 0x00195d78
        charge(ctx, 3);
        lw(a0, s1, 96);
        if (a0 != 0) {
            // 0x00195d84
            charge(ctx, 3);
            jal(ctx, 0x195D84u, gen::fn_sub_4CDE90_004cde90);
            sw(zero, s1, 96);
        }
        // 0x00195d90
        charge(ctx, 3);
        lw(a0, s1, 100);
        if (a0 != 0) {
            // 0x00195d9c
            charge(ctx, 3);
            jal(ctx, 0x195D9Cu, gen::fn_sub_4CDE90_004cde90);
            sw(zero, s1, 100);
        }
        // 0x00195da8
        charge(ctx, 3);
        a0 = s1;
        jal(ctx, 0x195DACu, gen::fn_sub_4CA030_004ca030);
    }
    // 0x00195db4
    charge(ctx, 1);
    v0 = 0;
    // 0x00195db8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00196770 sub_196770 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_196770() [kwlnSaveRenderStates]: reads RenderWare render states 0..17 into 0x847EB0[0..17] through the
// RwRenderStateGet slot (0x960094). Callers: the debug printer's draws, kwlnInitMain.
void sub_196770(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00196770
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    for (;;) {
        // 0x001967b0
        charge(ctx, 3);
        v1 = slti(s0, 18);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00196788
        charge(ctx, 10);
        v1 = sll(s0, 2);
        v0 = 0x840000;
        v0 = addiu(v0, 32432);  // &0x847EB0
        a1 = addu(v0, v1);
        a0 = s0;
        v0 = 0x960000;
        lw(v0, v0, 148);  // pfn_RwRenderStateGet
        jalr(ctx, 0x1967A4u, v0.u());
        s0 = addiu(s0, 1);
    }
    // 0x001967bc
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001967D0 sub_1967D0 -- 2064 bytes; frame 0x570: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1967D0() [kwlnInitGameDataNewCycle]: the new-cycle reset of a cleared game started again (caller sub_188900):
// the steps of sub_195DE0 in The Journey's form (day 2, the Journey persona table 0x5E4F20), but carrying over:
//   * kept: counter 47 (the play time, sub_16F380 / restored with sub_16F3E0), flags 387..393, the flags of the
//     0-terminated list 0x5E4F60 (copied to the frame: up to 200 ids) with their values, and sub_1755C0's value
//     (given back through sub_1754A0);
//   * the clear counter is incremented (sub_17D7C0(sub_17D7B0() + 1));
//   * the hero (unit 1) keeps his records: only his persona is re-given and HP / SP / condition refilled; units 2..10
//     are reset as in sub_195DE0; no new starting stock, no K_Field_Init / sub_1CD7A0;
//   * at the end flags 4880 and 5149 are set.
void sub_1967D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001967d0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x570);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a2 = 0x5E0000;
    a2 = addiu(a2, 20320);  // &0x5E4F60
    a1 = addiu(sp, 0x40);
    a0 = 61;
    for (;;) {
        // 0x001967f4
        charge(ctx, 9);
        lw(v1, a2, 0);
        lw(v0, a2, 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00196818
    charge(ctx, 12);
    a0 = 47;
    jal(ctx, 0x19681Cu, gen::fn_sub_16F380_0016f380);
    s1 = v0;
    jal(ctx, 0x196828u, gen::fn_sub_17D7B0_0017d7b0);
    a0 = addiu(v0, 1);
    jal(ctx, 0x196834u, gen::fn_sub_17D7C0_0017d7c0);
    s0 = 0;
    for (;;) {
        // 0x00196864
        charge(ctx, 3);
        v0 = slti(s0, 7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00196848
        charge(ctx, 7);
        a0 = addiu(s0, 387);
        jal(ctx, 0x19684Cu, gen::fn_datGetFlag_0016f190);
        v1 = sll(s0, 2);
        v1 = addu(v1, sp);
        sw(v0, v1, 1360);
        s0 = addiu(s0, 1);
    }
    // 0x00196870
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x001968a8
        charge(ctx, 3);
        v0 = slti(s0, 200);
        if (v0 != 0) {
            backedge(ctx);
            // 0x0019687c
            charge(ctx, 6);
            s2 = sll(s0, 2);
            v0 = addu(s2, sp);
            v0 = addiu(v0, 64);
            lw(a0, v0, 0);
            if (a0 != 0) {
                // 0x00196894
                charge(ctx, 5);
                jal(ctx, 0x196894u, gen::fn_datGetFlag_0016f190);
                v1 = addu(s2, sp);
                sw(v0, v1, 560);
                s0 = addiu(s0, 1);
                continue;
            }
        }
        break;
    }
    // 0x001968b4
    charge(ctx, 50);
    jal(ctx, 0x1968B4u, gen::fn_sub_17C280_0017c280);
    jal(ctx, 0x1968BCu, gen::fn_sub_17ADF0_0017adf0);
    jal(ctx, 0x1968C4u, gen::fn_sub_1755C0_001755c0);
    s2 = v0 & 0xFFFF;
    a0 = 1;
    jal(ctx, 0x1968D4u, gen::fn_sub_175BE0_00175be0);
    a0 = 1;
    v0 = 0x5E0000;
    lhu(a1, v0, 20256);  // 0x5E4F20
    jal(ctx, 0x1968E8u, gen::fn_sub_175820_00175820);
    a0 = 1;
    a1 = 0;
    jal(ctx, 0x1968F8u, gen::fn_sub_16D6B0_0016d6b0);
    a0 = 1;
    a1 = 0;
    jal(ctx, 0x196908u, gen::fn_sub_16D8B0_0016d8b0);
    a0 = 1;
    jal(ctx, 0x196914u, gen::fn_sub_16C5F0_0016c5f0);
    a1 = dsll32(v0, 16);
    a1 = dsra32(a1, 16);
    a0 = 1;
    jal(ctx, 0x196928u, gen::fn_sub_16CF40_0016cf40);
    a0 = 1;
    jal(ctx, 0x196934u, gen::fn_sub_16C670_0016c670);
    a1 = dsll32(v0, 16);
    a1 = dsra32(a1, 16);
    a0 = 1;
    jal(ctx, 0x196948u, gen::fn_sub_16CF90_0016cf90);
    a0 = 1;
    a1 = 32;
    jal(ctx, 0x196958u, gen::fn_sub_16D930_0016d930);
    a0 = 1;
    a1 = 32;
    jal(ctx, 0x196968u, gen::fn_sub_16D980_0016d980);
    s0 = 2;
    for (;;) {
        // 0x00196b8c
        charge(ctx, 3);
        v0 = slti(s0, 11);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0019697c
        charge(ctx, 7);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x196984u, gen::fn_sub_16CDF0_0016cdf0);
        a1 = 1;
        if (s0 == a1) {
            // 0x00196998
            charge(ctx, 4);
            a0 = dsll32(s0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x1969A0u, gen::fn_sub_16CEF0_0016cef0);
        }
        // 0x001969a8
        charge(ctx, 3);
        v0 = 1;
        if (s0 == v0) {
            // 0x001969b4
            charge(ctx, 5);
            a0 = dsll32(s0, 16);
            a0 = dsra32(a0, 16);
            a1 = 0;
            jal(ctx, 0x1969C0u, gen::fn_sub_16D230_0016d230);
        }
        // 0x001969c8
        charge(ctx, 104);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        a1 = 0;
        jal(ctx, 0x1969D4u, gen::fn_sub_16CF40_0016cf40);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        a1 = 0;
        jal(ctx, 0x1969E8u, gen::fn_sub_16CF90_0016cf90);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        a1 = 0;
        jal(ctx, 0x1969FCu, gen::fn_sub_16CFE0_0016cfe0);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        a1 = 0;
        jal(ctx, 0x196A10u, gen::fn_sub_16D090_0016d090);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        a1 = 0;
        jal(ctx, 0x196A24u, gen::fn_sub_16D160_0016d160);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        a1 = 0;
        jal(ctx, 0x196A38u, gen::fn_sub_16D6B0_0016d6b0);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        a1 = 0;
        jal(ctx, 0x196A4Cu, gen::fn_sub_16D8B0_0016d8b0);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        a1 = 0;
        a2 = si(-1);
        jal(ctx, 0x196A64u, gen::fn_sub_16DA50_0016da50);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        a1 = 1;
        a2 = si(-1);
        jal(ctx, 0x196A7Cu, gen::fn_sub_16DA50_0016da50);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        a1 = 2;
        a2 = si(-1);
        jal(ctx, 0x196A94u, gen::fn_sub_16DA50_0016da50);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        a1 = 3;
        a2 = si(-1);
        jal(ctx, 0x196AACu, gen::fn_sub_16DA50_0016da50);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x196ABCu, gen::fn_sub_175BE0_00175be0);
        a0 = s0 & 0xFFFF;
        v1 = sll(s0, 1);
        v0 = 0x5E0000;
        v0 = addiu(v0, 20256);  // &0x5E4F20
        v0 = addu(v0, v1);
        lhu(a1, v0, -2);
        jal(ctx, 0x196ADCu, gen::fn_sub_175820_00175820);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x196AECu, gen::fn_sub_16C5F0_0016c5f0);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x196B04u, gen::fn_sub_16CF40_0016cf40);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x196B14u, gen::fn_sub_16C670_0016c670);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x196B2Cu, gen::fn_sub_16CF90_0016cf90);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        a1 = 32;
        jal(ctx, 0x196B40u, gen::fn_sub_16D930_0016d930);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        a1 = 32;
        jal(ctx, 0x196B54u, gen::fn_sub_16D980_0016d980);
        v0 = 1;
        if (s0 != v0) {
            // 0x00196b68
            charge(ctx, 8);
            a0 = dsll32(s0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x196B70u, gen::fn_sub_16C470_0016c470);
            a1 = v0 & 0xFF;
            a0 = s0;
            jal(ctx, 0x196B80u, gen::fn_sub_177CE0_00177ce0);
        }
        // 0x00196b88
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00196b98
    charge(ctx, 22);
    jal(ctx, 0x196B98u, gen::fn_datClearFlagAll_0016f2e0);
    jal(ctx, 0x196BA0u, gen::fn_sub_16F450_0016f450);
    jal(ctx, 0x196BA8u, gen::fn_sub_16F320_0016f320);
    a0 = 0;
    jal(ctx, 0x196BB4u, gen::fn_sub_16F150_0016f150);
    a0 = 2;
    jal(ctx, 0x196BC0u, gen::fn_datSetDaysSinceApr5_0016ef70);
    a0 = 2563;
    a1 = 1;
    jal(ctx, 0x196BD0u, gen::fn_datSetFlag_0016f1f0);
    a0 = 0;
    jal(ctx, 0x196BDCu, gen::fn_sub_16F180_0016f180);
    s0 = 0;
    for (;;) {
        // 0x00196e24
        charge(ctx, 3);
        v0 = slti(s0, 20);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00196bf0
        charge(ctx, 141);
        a0 = si(-1);
        a1 = s0;
        a2 = 0;
        jal(ctx, 0x196BFCu, gen::fn_sub_16FEA0_0016fea0);
        a0 = 258;
        a1 = s0;
        a2 = 0;
        jal(ctx, 0x196C10u, gen::fn_sub_16FEA0_0016fea0);
        a0 = 259;
        a1 = s0;
        a2 = 0;
        jal(ctx, 0x196C24u, gen::fn_sub_16FEA0_0016fea0);
        a0 = 260;
        a1 = s0;
        a2 = 0;
        jal(ctx, 0x196C38u, gen::fn_sub_16FEA0_0016fea0);
        a0 = 261;
        a1 = s0;
        a2 = 0;
        jal(ctx, 0x196C4Cu, gen::fn_sub_16FEA0_0016fea0);
        a0 = 262;
        a1 = s0;
        a2 = 0;
        jal(ctx, 0x196C60u, gen::fn_sub_16FEA0_0016fea0);
        a0 = 263;
        a1 = s0;
        a2 = 0;
        jal(ctx, 0x196C74u, gen::fn_sub_16FEA0_0016fea0);
        a0 = 264;
        a1 = s0;
        a2 = 0;
        jal(ctx, 0x196C88u, gen::fn_sub_16FEA0_0016fea0);
        a0 = 265;
        a1 = s0;
        a2 = 0;
        jal(ctx, 0x196C9Cu, gen::fn_sub_16FEA0_0016fea0);
        a0 = 266;
        a1 = s0;
        a2 = 0;
        jal(ctx, 0x196CB0u, gen::fn_sub_16FEA0_0016fea0);
        a0 = 2;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x196CC4u, gen::fn_sub_170B20_00170b20);
        a0 = 2;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x196CD8u, gen::fn_sub_170B90_00170b90);
        a0 = 3;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x196CECu, gen::fn_sub_170B20_00170b20);
        a0 = 3;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x196D00u, gen::fn_sub_170B90_00170b90);
        a0 = 4;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x196D14u, gen::fn_sub_170B20_00170b20);
        a0 = 4;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x196D28u, gen::fn_sub_170B90_00170b90);
        a0 = 5;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x196D3Cu, gen::fn_sub_170B20_00170b20);
        a0 = 5;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x196D50u, gen::fn_sub_170B90_00170b90);
        a0 = 6;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x196D64u, gen::fn_sub_170B20_00170b20);
        a0 = 6;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x196D78u, gen::fn_sub_170B90_00170b90);
        a0 = 7;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x196D8Cu, gen::fn_sub_170B20_00170b20);
        a0 = 7;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x196DA0u, gen::fn_sub_170B90_00170b90);
        a0 = 8;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x196DB4u, gen::fn_sub_170B20_00170b20);
        a0 = 8;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x196DC8u, gen::fn_sub_170B90_00170b90);
        a0 = 9;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x196DDCu, gen::fn_sub_170B20_00170b20);
        a0 = 9;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x196DF0u, gen::fn_sub_170B90_00170b90);
        a0 = 10;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x196E04u, gen::fn_sub_170B20_00170b20);
        a0 = 10;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x196E18u, gen::fn_sub_170B90_00170b90);
        s0 = addiu(s0, 1);
    }
    // 0x00196e30
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x00196e78
        charge(ctx, 3);
        v0 = slti(s0, 300);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00196e3c
        charge(ctx, 15);
        v0 = addiu(s0, 4000);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        a0 = 1;
        a2 = 0;
        jal(ctx, 0x196E50u, gen::fn_sub_170860_00170860);
        v0 = addiu(s0, 4000);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        a0 = si(-1);
        a2 = 0;
        jal(ctx, 0x196E6Cu, gen::fn_sub_170860_00170860);
        s0 = addiu(s0, 1);
    }
    // 0x00196e84
    charge(ctx, 39);
    jal(ctx, 0x196E84u, gen::fn_sub_1779A0_001779a0);
    jal(ctx, 0x196E8Cu, gen::fn_sub_1FA0D0_001fa0d0);
    jal(ctx, 0x196E94u, gen::fn_sub_1FC1F0_001fc1f0);
    a0 = 0;
    a1 = 0;
    jal(ctx, 0x196EA4u, gen::fn_sub_16E990_0016e990);
    a0 = 1;
    a1 = 0;
    jal(ctx, 0x196EB4u, gen::fn_sub_16E990_0016e990);
    a0 = 2;
    a1 = 0;
    jal(ctx, 0x196EC4u, gen::fn_sub_16E990_0016e990);
    a0 = 3;
    a1 = 0;
    jal(ctx, 0x196ED4u, gen::fn_sub_16E990_0016e990);
    jal(ctx, 0x196EDCu, gen::fn_sub_17B160_0017b160);
    jal(ctx, 0x196EE4u, gen::fn_sub_17B1A0_0017b1a0);
    jal(ctx, 0x196EECu, gen::fn_sub_25B440_0025b440);
    jal(ctx, 0x196EF4u, gen::fn_sub_17D3C0_0017d3c0);
    jal(ctx, 0x196EFCu, gen::fn_sub_17C190_0017c190);
    jal(ctx, 0x196F04u, gen::fn_sub_17B2A0_0017b2a0);
    jal(ctx, 0x196F0Cu, gen::fn_sub_16DB70_0016db70);
    s0 = 0;
    for (;;) {
        // 0x00196f3c
        charge(ctx, 3);
        v0 = slti(s0, 7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00196f20
        charge(ctx, 7);
        a0 = addiu(s0, 387);
        v0 = sll(s0, 2);
        v0 = addu(v0, sp);
        lw(a1, v0, 1360);
        jal(ctx, 0x196F30u, gen::fn_datSetFlag_0016f1f0);
        s0 = addiu(s0, 1);
    }
    // 0x00196f48
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x00196f7c
        charge(ctx, 3);
        v0 = slti(s0, 200);
        if (v0 != 0) {
            backedge(ctx);
            // 0x00196f54
            charge(ctx, 6);
            v0 = sll(s0, 2);
            v1 = addu(v0, sp);
            v0 = addiu(v1, 64);
            lw(a0, v0, 0);
            if (a0 != 0) {
                // 0x00196f6c
                charge(ctx, 4);
                lw(a1, v1, 560);
                jal(ctx, 0x196F70u, gen::fn_datSetFlag_0016f1f0);
                s0 = addiu(s0, 1);
                continue;
            }
        }
        break;
    }
    // 0x00196f88
    charge(ctx, 22);
    a0 = s2;
    jal(ctx, 0x196F8Cu, gen::fn_sub_1754A0_001754a0);
    a0 = 4880;
    a1 = 1;
    jal(ctx, 0x196F9Cu, gen::fn_datSetFlag_0016f1f0);
    a0 = 5149;
    a1 = 1;
    jal(ctx, 0x196FACu, gen::fn_datSetFlag_0016f1f0);
    a0 = 47;
    a1 = s1;
    jal(ctx, 0x196FBCu, gen::fn_sub_16F3E0_0016f3e0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x570);
}

// 0x00197350 kwlnInitRenderer -- 3108 bytes; frame 0x4B0: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// kwlnInitRenderer(): the RenderWare bring-up of the boot (docs/ANALYSIS/10_frame_loop_gs.md section 1.3): RW engine
// init with the H_Malloc memory functions and an 8 MiB arena, RpPDS + the 33 PDS pipelines, the world / spline / skin /
// anim / PTank plugins, RwEngineOpen, RpSkySelectDeepZBuffer(0) (16-bit Z), RwEngineSetVideoMode(82: 640 x 448 x 32
// interlaced), RwResourcesSetArenaSize(0x380000), sub_35ABA0, _rwDMAPreAlloc(0x280000, 0x400, 0), RwEngineStart (the
// GS initialisation), kwlnInstallVsyncFieldGate; the world (RpWorldCreate, bbox +-150) into 0x7CE0A0[*0x7CE0CC] and
// three lights into 0x7CE0A8 / 0x7CE0AC / 0x7CE0B0; the main camera (kwlnCreateMainCamera(640, 448, 1)) with far
// 25600 / near 20 and kwlnSetupMainCameraViewport -> g_kwlnMainCamera 0x7CE0C0; Rt2dOpen; two RW heap blocks; the
// image formats (K_Abort "Cannot register image file format" on failure).
void kwlnInitRenderer(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x00197350
    enter(ctx, 528);  // entry check point + this block's cycles
    sp = addiu(sp, -0x4B0);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 32;
    a1 = a0;
    jal(ctx, 0x19736Cu, gen::fn_sub_4AC860_004ac860);
    jal(ctx, 0x197374u, gen::fn_sub_1040F0_001040f0);
    a0 = v0;
    a1 = 0;
    a2 = 0x800000;
    jal(ctx, 0x197388u, gen::fn_sub_4CA850_004ca850);
    a0 = 7;
    jal(ctx, 0x197394u, gen::fn_sub_46A750_0046a750);
    v0 = 0x6B0000;
    v0 = addiu(v0, 20256);  // &pds_matpipe_def_1
    sw(v0, sp, 0x490);
    v0 = 4097;
    sw(v0, sp, 0x498);
    v0 = 1;
    sw(v0, sp, 0x49C);
    sw(zero, sp, 0x494);
    sw(zero, sp, 0x4A0);
    a0 = addiu(sp, 0x490);
    jal(ctx, 0x1973C4u, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 20400);  // &0x6B4FB0
    sw(v0, sp, 0x470);
    v0 = 4098;
    sw(v0, sp, 0x478);
    v0 = 2;
    sw(v0, sp, 0x47C);
    v0 = 4097;
    sw(v0, sp, 0x474);
    sw(zero, sp, 0x480);
    a0 = addiu(sp, 0x470);
    jal(ctx, 0x1973F8u, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 20432);  // &0x6B4FD0
    sw(v0, sp, 0x450);
    v0 = 4099;
    sw(v0, sp, 0x458);
    v0 = 2;
    sw(v0, sp, 0x45C);
    v0 = 4097;
    sw(v0, sp, 0x454);
    sw(zero, sp, 0x460);
    a0 = addiu(sp, 0x450);
    jal(ctx, 0x19742Cu, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 20464);  // &pds_matpipe_def_4
    sw(v0, sp, 0x430);
    v0 = 4;
    sw(v0, sp, 0x438);
    v0 = 1;
    sw(v0, sp, 0x43C);
    sw(zero, sp, 0x434);
    sw(zero, sp, 0x440);
    a0 = addiu(sp, 0x430);
    jal(ctx, 0x19745Cu, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 20608);  // &pds_matpipe_def_5
    sw(v0, sp, 0x410);
    v0 = 5;
    sw(v0, sp, 0x418);
    v0 = 1;
    sw(v0, sp, 0x41C);
    sw(zero, sp, 0x414);
    sw(zero, sp, 0x420);
    a0 = addiu(sp, 0x410);
    jal(ctx, 0x19748Cu, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 20752);  // &0x6B5110
    sw(v0, sp, 0x3F0);
    v0 = 6;
    sw(v0, sp, 0x3F8);
    v0 = 2;
    sw(v0, sp, 0x3FC);
    v0 = 4;
    sw(v0, sp, 0x3F4);
    sw(zero, sp, 0x400);
    a0 = addiu(sp, 0x3F0);
    jal(ctx, 0x1974C0u, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 20784);  // &0x6B5130
    sw(v0, sp, 0x3D0);
    v0 = 7;
    sw(v0, sp, 0x3D8);
    v0 = 2;
    sw(v0, sp, 0x3DC);
    v0 = 5;
    sw(v0, sp, 0x3D4);
    sw(zero, sp, 0x3E0);
    a0 = addiu(sp, 0x3D0);
    jal(ctx, 0x1974F4u, gen::fn_RpPDSRegisterPipe_0046a830);
    jal(ctx, 0x1974FCu, gen::fn_sub_49A980_0049a980);
    jal(ctx, 0x197504u, gen::fn_sub_45F7D0_0045f7d0);
    jal(ctx, 0x19750Cu, gen::fn_sub_48DCF0_0048dcf0);
    jal(ctx, 0x197514u, gen::fn_sub_468C50_00468c50);
    v0 = 0x6B0000;
    v0 = addiu(v0, 20960);  // &pds_matpipe_def_1100b
    sw(v0, sp, 0x3B0);
    v0 = 0x10000;
    v0 = v0 | 0x100B;
    sw(v0, sp, 0x3B8);
    v0 = 1;
    sw(v0, sp, 0x3BC);
    sw(zero, sp, 0x3B4);
    sw(zero, sp, 0x3C0);
    a0 = addiu(sp, 0x3B0);
    jal(ctx, 0x197548u, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 21104);  // &pds_matpipe_def_1100c
    sw(v0, sp, 0x390);
    v0 = 0x10000;
    v0 = v0 | 0x100C;
    sw(v0, sp, 0x398);
    v0 = 1;
    sw(v0, sp, 0x39C);
    sw(zero, sp, 0x394);
    sw(zero, sp, 0x3A0);
    a0 = addiu(sp, 0x390);
    jal(ctx, 0x19757Cu, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 21248);  // &0x6B5300
    sw(v0, sp, 0x370);
    v1 = 0x10000;
    v0 = v1 | 0x100D;
    sw(v0, sp, 0x378);
    v0 = 2;
    sw(v0, sp, 0x37C);
    v0 = v1 | 0x100B;
    sw(v0, sp, 0x374);
    sw(zero, sp, 0x380);
    a0 = addiu(sp, 0x370);
    jal(ctx, 0x1975B4u, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 21280);  // &0x6B5320
    sw(v0, sp, 0x350);
    v1 = 0x10000;
    v0 = v1 | 0x100E;
    sw(v0, sp, 0x358);
    v0 = 2;
    sw(v0, sp, 0x35C);
    v0 = v1 | 0x100C;
    sw(v0, sp, 0x354);
    sw(zero, sp, 0x360);
    a0 = addiu(sp, 0x350);
    jal(ctx, 0x1975ECu, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 21312);  // &0x6B5340
    sw(v0, sp, 0x330);
    v1 = 0x10000;
    v0 = v1 | 0x100F;
    sw(v0, sp, 0x338);
    v0 = 2;
    sw(v0, sp, 0x33C);
    v0 = v1 | 0x100B;
    sw(v0, sp, 0x334);
    sw(zero, sp, 0x340);
    a0 = addiu(sp, 0x330);
    jal(ctx, 0x197624u, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 21344);  // &0x6B5360
    sw(v0, sp, 0x310);
    v1 = 0x10000;
    v0 = v1 | 0x1010;
    sw(v0, sp, 0x318);
    v0 = 2;
    sw(v0, sp, 0x31C);
    v0 = v1 | 0x100C;
    sw(v0, sp, 0x314);
    sw(zero, sp, 0x320);
    a0 = addiu(sp, 0x310);
    jal(ctx, 0x19765Cu, gen::fn_RpPDSRegisterPipe_0046a830);
    jal(ctx, 0x197664u, gen::fn_sub_4B6640_004b6640);
    jal(ctx, 0x19766Cu, gen::fn_sub_4661B0_004661b0);
    jal(ctx, 0x197674u, gen::fn_sub_48A1A0_0048a1a0);
    v0 = 0x6B0000;
    v0 = addiu(v0, 21408);  // &pds_matpipe_def_10001
    sw(v0, sp, 0x2F0);
    v0 = 0x10000;
    v0 = v0 | 0x1001;
    sw(v0, sp, 0x2F8);
    v0 = 1;
    sw(v0, sp, 0x2FC);
    sw(zero, sp, 0x2F4);
    sw(zero, sp, 0x300);
    a0 = addiu(sp, 0x2F0);
    jal(ctx, 0x1976A8u, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 21552);  // &0x6B5430
    sw(v0, sp, 0x2D0);
    v1 = 0x10000;
    v0 = v1 | 0x1002;
    sw(v0, sp, 0x2D8);
    v0 = 2;
    sw(v0, sp, 0x2DC);
    v0 = v1 | 0x1001;
    sw(v0, sp, 0x2D4);
    sw(zero, sp, 0x2E0);
    a0 = addiu(sp, 0x2D0);
    jal(ctx, 0x1976E0u, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 21760);  // &pds_matpipe_def_11011
    sw(v0, sp, 0x2B0);
    v0 = 0x10000;
    v0 = v0 | 0x1011;
    sw(v0, sp, 0x2B8);
    v0 = 1;
    sw(v0, sp, 0x2BC);
    sw(zero, sp, 0x2B4);
    sw(zero, sp, 0x2C0);
    a0 = addiu(sp, 0x2B0);
    jal(ctx, 0x197714u, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 21904);  // &pds_matpipe_def_11012
    sw(v0, sp, 0x290);
    v0 = 0x10000;
    v0 = v0 | 0x1012;
    sw(v0, sp, 0x298);
    v0 = 1;
    sw(v0, sp, 0x29C);
    sw(zero, sp, 0x294);
    sw(zero, sp, 0x2A0);
    a0 = addiu(sp, 0x290);
    jal(ctx, 0x197748u, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 22048);  // &0x6B5620
    sw(v0, sp, 0x270);
    v1 = 0x10000;
    v0 = v1 | 0x1013;
    sw(v0, sp, 0x278);
    v0 = 2;
    sw(v0, sp, 0x27C);
    v0 = v1 | 0x1011;
    sw(v0, sp, 0x274);
    sw(zero, sp, 0x280);
    a0 = addiu(sp, 0x270);
    jal(ctx, 0x197780u, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 22080);  // &0x6B5640
    sw(v0, sp, 0x250);
    v1 = 0x10000;
    v0 = v1 | 0x1014;
    sw(v0, sp, 0x258);
    v0 = 2;
    sw(v0, sp, 0x25C);
    v0 = v1 | 0x1012;
    sw(v0, sp, 0x254);
    sw(zero, sp, 0x260);
    a0 = addiu(sp, 0x250);
    jal(ctx, 0x1977B8u, gen::fn_RpPDSRegisterPipe_0046a830);
    jal(ctx, 0x1977C0u, gen::fn_sub_46A530_0046a530);
    jal(ctx, 0x1977C8u, gen::fn_sub_4B8830_004b8830);
    jal(ctx, 0x1977D0u, gen::fn_sub_4F8E10_004f8e10);
    v0 = 0x6B0000;
    v0 = addiu(v0, 23264);  // &0x6B5AE0
    sw(v0, sp, 0x230);
    v0 = 0x10000;
    v0 = v0 | 0x1F;
    sw(v0, sp, 0x238);
    v0 = 2;
    sw(v0, sp, 0x23C);
    sw(zero, sp, 0x234);
    sw(zero, sp, 0x240);
    a0 = addiu(sp, 0x230);
    jal(ctx, 0x197804u, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 23120);  // &pds_matpipe_def_10020
    sw(v0, sp, 0x210);
    v0 = 0x10000;
    v0 = v0 | 0x20;
    sw(v0, sp, 0x218);
    v0 = 1;
    sw(v0, sp, 0x21C);
    sw(zero, sp, 0x214);
    sw(zero, sp, 0x220);
    a0 = addiu(sp, 0x210);
    jal(ctx, 0x197838u, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 23296);  // &pds_matpipe_def_10021
    sw(v0, sp, 0x1F0);
    v0 = 0x10000;
    v0 = v0 | 0x21;
    sw(v0, sp, 0x1F8);
    v0 = 1;
    sw(v0, sp, 0x1FC);
    sw(zero, sp, 0x1F4);
    sw(zero, sp, 0x200);
    a0 = addiu(sp, 0x1F0);
    jal(ctx, 0x19786Cu, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 23440);  // &pds_matpipe_def_10022
    sw(v0, sp, 0x1D0);
    v0 = 0x10000;
    v0 = v0 | 0x22;
    sw(v0, sp, 0x1D8);
    v0 = 1;
    sw(v0, sp, 0x1DC);
    sw(zero, sp, 0x1D4);
    sw(zero, sp, 0x1E0);
    a0 = addiu(sp, 0x1D0);
    jal(ctx, 0x1978A0u, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 23584);  // &pds_matpipe_def_10023
    sw(v0, sp, 0x1B0);
    v0 = 0x10000;
    v0 = v0 | 0x23;
    sw(v0, sp, 0x1B8);
    v0 = 1;
    sw(v0, sp, 0x1BC);
    sw(zero, sp, 0x1B4);
    sw(zero, sp, 0x1C0);
    a0 = addiu(sp, 0x1B0);
    jal(ctx, 0x1978D4u, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 23728);  // &pds_matpipe_def_10024
    sw(v0, sp, 0x190);
    v0 = 0x10000;
    v0 = v0 | 0x24;
    sw(v0, sp, 0x198);
    v0 = 1;
    sw(v0, sp, 0x19C);
    sw(zero, sp, 0x194);
    sw(zero, sp, 0x1A0);
    a0 = addiu(sp, 0x190);
    jal(ctx, 0x197908u, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 23920);  // &pds_matpipe_def_1002a
    sw(v0, sp, 0x170);
    v0 = 0x10000;
    v0 = v0 | 0x2A;
    sw(v0, sp, 0x178);
    v0 = 1;
    sw(v0, sp, 0x17C);
    sw(zero, sp, 0x174);
    sw(zero, sp, 0x180);
    a0 = addiu(sp, 0x170);
    jal(ctx, 0x19793Cu, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 24064);  // &pds_matpipe_def_1002b
    sw(v0, sp, 0x150);
    v0 = 0x10000;
    v0 = v0 | 0x2B;
    sw(v0, sp, 0x158);
    v0 = 1;
    sw(v0, sp, 0x15C);
    sw(zero, sp, 0x154);
    sw(zero, sp, 0x160);
    a0 = addiu(sp, 0x150);
    jal(ctx, 0x197970u, gen::fn_RpPDSRegisterPipe_0046a830);
    jal(ctx, 0x197978u, gen::fn_sub_473590_00473590);
    v0 = 0x6B0000;
    v0 = addiu(v0, 22848);  // &pds_matpipe_def_1001d
    sw(v0, sp, 0x130);
    v0 = 0x10000;
    v0 = v0 | 0x1D;
    sw(v0, sp, 0x138);
    v0 = 1;
    sw(v0, sp, 0x13C);
    sw(zero, sp, 0x134);
    sw(zero, sp, 0x140);
    a0 = addiu(sp, 0x130);
    jal(ctx, 0x1979ACu, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 22992);  // &0x6B59D0
    sw(v0, sp, 0x110);
    v1 = 0x10000;
    v0 = v1 | 0x1E;
    sw(v0, sp, 0x118);
    v0 = 2;
    sw(v0, sp, 0x11C);
    v0 = v1 | 0x1D;
    sw(v0, sp, 0x114);
    sw(zero, sp, 0x120);
    a0 = addiu(sp, 0x110);
    jal(ctx, 0x1979E4u, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 22512);  // &pds_matpipe_def_1001b
    sw(v0, sp, 0xF0);
    v0 = 0x10000;
    v0 = v0 | 0x1B;
    sw(v0, sp, 0xF8);
    v0 = 1;
    sw(v0, sp, 0xFC);
    sw(zero, sp, 0xF4);
    sw(zero, sp, 0x100);
    a0 = addiu(sp, 0xF0);
    jal(ctx, 0x197A18u, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 22656);  // &0x6B5880
    sw(v0, sp, 0xD0);
    v1 = 0x10000;
    v0 = v1 | 0x1C;
    sw(v0, sp, 0xD8);
    v0 = 2;
    sw(v0, sp, 0xDC);
    v0 = v1 | 0x1B;
    sw(v0, sp, 0xD4);
    sw(zero, sp, 0xE0);
    a0 = addiu(sp, 0xD0);
    jal(ctx, 0x197A50u, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 22176);  // &pds_matpipe_def_10019
    sw(v0, sp, 0xB0);
    v0 = 0x10000;
    v0 = v0 | 0x19;
    sw(v0, sp, 0xB8);
    v0 = 1;
    sw(v0, sp, 0xBC);
    sw(zero, sp, 0xB4);
    sw(zero, sp, 0xC0);
    a0 = addiu(sp, 0xB0);
    jal(ctx, 0x197A84u, gen::fn_RpPDSRegisterPipe_0046a830);
    v0 = 0x6B0000;
    v0 = addiu(v0, 22320);  // &0x6B5730
    sw(v0, sp, 0x90);
    v1 = 0x10000;
    v0 = v1 | 0x1A;
    sw(v0, sp, 0x98);
    v0 = 2;
    sw(v0, sp, 0x9C);
    v0 = v1 | 0x19;
    sw(v0, sp, 0x94);
    sw(zero, sp, 0xA0);
    a0 = addiu(sp, 0x90);
    jal(ctx, 0x197ABCu, gen::fn_RpPDSRegisterPipe_0046a830);
    jal(ctx, 0x197AC4u, gen::fn_sub_488FE0_00488fe0);
    jal(ctx, 0x197ACCu, gen::fn_sub_48F030_0048f030);
    sw(zero, sp, 0x4AC);
    a0 = addiu(sp, 0x4AC);
    jal(ctx, 0x197ADCu, gen::fn_RwEngineOpen_004ca700);
    a0 = 0;
    jal(ctx, 0x197AE8u, gen::fn_RpSkySelectDeepZBuffer_004d82a0);
    a0 = 82;
    jal(ctx, 0x197AF4u, gen::fn_RwEngineSetVideoMode_004ca600);
    a0 = 0x380000;
    jal(ctx, 0x197B00u, gen::fn_RwResourcesSetArenaSize_004c4c00);
    jal(ctx, 0x197B08u, gen::fn_sub_35ABA0_0035aba0);
    a0 = 0x280000;
    a1 = 1024;
    a2 = 0;
    jal(ctx, 0x197B1Cu, gen::fn__rwDMAPreAlloc_004d6ab0);
    jal(ctx, 0x197B24u, gen::fn_RwEngineStart_004ca640);
    jal(ctx, 0x197B2Cu, gen::fn_kwlnInstallVsyncFieldGate_0019d360);
    v0 = lui(0xC316);
    sw(v0, sp, 0x84);
    sw(v0, sp, 0x80);
    sw(v0, sp, 0x7C);
    v0 = 0x43160000;
    sw(v0, sp, 0x78);
    sw(v0, sp, 0x74);
    sw(v0, sp, 0x70);
    a0 = addiu(sp, 0x70);
    jal(ctx, 0x197B58u, gen::fn_sub_49A400_0049a400);
    lw(v1, gp, -19492);  // 0x7CE0CC
    a0 = sll(v1, 2);
    v1 = addiu(gp, -19536);  // &0x7CE0A0
    v1 = addu(v1, a0);
    sw(v0, v1, 0);
    s1 = v0;
    a0 = 2;
    jal(ctx, 0x197B7Cu, gen::fn_sub_4947C0_004947c0);
    s0 = v0;
    if (v0 != 0) {
        // 0x00197b90
        charge(ctx, 9);
        a0 = s0;
        a1 = 0x680000;
        a1 = addiu(a1, -31552);  // &0x6784C0
        jal(ctx, 0x197B9Cu, gen::fn_sub_4944B0_004944b0);
        a0 = s1;
        a1 = s0;
        jal(ctx, 0x197BACu, gen::fn_sub_49C3D0_0049c3d0);
    }
    // 0x00197bb4
    charge(ctx, 12);
    sw(s0, gp, -19528);  // 0x7CE0A8
    lw(v0, gp, -19492);  // 0x7CE0CC
    v1 = sll(v0, 2);
    v0 = addiu(gp, -19536);  // &0x7CE0A0
    v0 = addu(v0, v1);
    lw(s1, v0, 0);
    a0 = 1;
    jal(ctx, 0x197BD0u, gen::fn_sub_4947C0_004947c0);
    s2 = v0;
    bool made = false;  // host-side: the light and its frame exist (else 0 is stored)
    if (v0 != 0) {
        // 0x00197be4
        charge(ctx, 5);
        jal(ctx, 0x197BE4u, gen::fn_sub_4CAF10_004caf10);
        s0 = v0;
        if (v0 == 0) {
            // 0x00197c48
            charge(ctx, 3);
            a0 = s2;
            jal(ctx, 0x197C4Cu, gen::fn_sub_494760_00494760);
        } else {
            // 0x00197bf8
            charge(ctx, 20);
            v0 = 1;
            sb(v0, s2, 2);
            a0 = s0;
            jal(ctx, 0x197C04u, gen::fn_sub_4CB930_004cb930);
            a0 = s2;
            a1 = s0;
            jal(ctx, 0x197C14u, gen::fn_sub_4D1840_004d1840);
            a0 = s2;
            a1 = 0x680000;
            a1 = addiu(a1, -31504);  // &0x6784F0
            jal(ctx, 0x197C28u, gen::fn_sub_4944B0_004944b0);
            a0 = s1;
            a1 = s2;
            jal(ctx, 0x197C38u, gen::fn_sub_49C3D0_0049c3d0);
            made = true;
        }
    }
    if (!made) {
        // 0x00197c54: no light
        charge(ctx, 1);
        s2 = 0;
    }
    // 0x00197c58: the second light -> 0x7CE0AC
    charge(ctx, 12);
    sw(s2, gp, -19524);  // 0x7CE0AC
    lw(v0, gp, -19492);  // 0x7CE0CC
    v1 = sll(v0, 2);
    v0 = addiu(gp, -19536);  // &0x7CE0A0
    v0 = addu(v0, v1);
    lw(s1, v0, 0);
    a0 = 1;
    jal(ctx, 0x197C74u, gen::fn_sub_4947C0_004947c0);
    s2 = v0;
    made = false;
    if (v0 != 0) {
        // 0x00197c88
        charge(ctx, 5);
        jal(ctx, 0x197C88u, gen::fn_sub_4CAF10_004caf10);
        s0 = v0;
        if (v0 == 0) {
            // 0x00197d20
            charge(ctx, 3);
            a0 = s2;
            jal(ctx, 0x197D24u, gen::fn_sub_494760_00494760);
        } else {
            // 0x00197c9c
            charge(ctx, 33);
            v0 = 1;
            sb(v0, s2, 2);
            v0 = 0x41C80000;
            mtc1(v0, f12);
            a0 = s0;
            a1 = 0x680000;
            a1 = addiu(a1, -31536);  // &0x6784D0
            a2 = 0;
            jal(ctx, 0x197CBCu, gen::fn_sub_4CB890_004cb890);
            v0 = 0x432A0000;
            mtc1(v0, f12);
            a0 = s0;
            a1 = 0x680000;
            a1 = addiu(a1, -31520);  // &0x6784E0
            a2 = 2;
            jal(ctx, 0x197CDCu, gen::fn_sub_4CB890_004cb890);
            a0 = s2;
            a1 = s0;
            jal(ctx, 0x197CECu, gen::fn_sub_4D1840_004d1840);
            a0 = s2;
            a1 = 0x680000;
            a1 = addiu(a1, -31488);  // &0x678500
            jal(ctx, 0x197D00u, gen::fn_sub_4944B0_004944b0);
            a0 = s1;
            a1 = s2;
            jal(ctx, 0x197D10u, gen::fn_sub_49C3D0_0049c3d0);
            made = true;
        }
    }
    if (!made) {
        // 0x00197d2c: no light
        charge(ctx, 1);
        s2 = 0;
    }
    // 0x00197d30: the third light -> 0x7CE0B0
    charge(ctx, 20);
    sw(s2, gp, -19520);  // 0x7CE0B0
    lw(v0, gp, -19492);  // 0x7CE0CC
    v1 = sll(v0, 2);
    v0 = addiu(gp, -19536);  // &0x7CE0A0
    v0 = addu(v0, v1);
    lw(s1, v0, 0);
    jal(ctx, 0x197D48u, gen::fn_sub_4CA5B0_004ca5b0);
    a0 = addiu(sp, 0x50);
    a1 = v0;
    jal(ctx, 0x197D58u, gen::fn_sub_4CA560_004ca560);
    lw(a0, sp, 0x50);
    lw(a1, sp, 0x54);
    a2 = 1;
    jal(ctx, 0x197D6Cu, gen::fn_kwlnCreateMainCamera_00195c80);
    s0 = v0;
    if (v0 != 0) {
        // 0x00197d80
        charge(ctx, 29);
        v0 = 0x46C80000;
        mtc1(v0, f12);
        a0 = s0;
        jal(ctx, 0x197D8Cu, gen::fn_sub_4C9DB0_004c9db0);
        v0 = 0x41A00000;
        mtc1(v0, f12);
        a0 = s0;
        jal(ctx, 0x197DA0u, gen::fn_sub_4C9D70_004c9d70);
        a0 = s1;
        a1 = s0;
        jal(ctx, 0x197DB0u, gen::fn_sub_49C160_0049c160);
        sw(zero, sp, 0x40);
        sw(zero, sp, 0x44);
        lw(v0, sp, 0x50);
        sw(v0, sp, 0x48);
        lw(v0, sp, 0x54);
        sw(v0, sp, 0x4C);
        v0 = 0x3F000000;
        mtc1(v0, f12);
        a0 = s0;
        a1 = addiu(sp, 0x40);
        lwc1(f13, gp, -32724);  // 0x7CAD1C
        jal(ctx, 0x197DE4u, gen::fn_kwlnSetupMainCameraViewport_00195980);
        lwc1(f0, gp, -32720);  // 0x7CAD20
        swc1(f0, s0, 136);
    }
    // 0x00197df4
    charge(ctx, 65);
    sw(s0, gp, -19504);  // g_kwlnMainCamera
    jal(ctx, 0x197DF8u, gen::fn_sub_4F1E10_004f1e10);
    lw(a2, s0, 96);
    lw(v1, s0, 100);
    a0 = 0x680000;
    a0 = addiu(a0, -30912);  // "--->camera raster depth %d %d %d\n"
    a1 = v0;
    lw(a2, a2, 20);
    lw(a3, v1, 20);
    jal(ctx, 0x197E1Cu, gen::fn_printf_005225a8);
    lw(a0, gp, -19504);  // g_kwlnMainCamera
    jal(ctx, 0x197E28u, gen::fn_sub_4AA550_004aa550);
    v0 = 0x3F000000;
    mtc1(v0, f12);
    jal(ctx, 0x197E38u, gen::fn_sub_4AA390_004aa390);
    lw(v0, gp, -19504);  // g_kwlnMainCamera
    lwc1(f1, gp, -32716);  // 0x7CAD24
    lwc1(f0, v0, 128);
    mul_s(f12, f1, f0);
    jal(ctx, 0x197E50u, gen::fn_sub_4AA3D0_004aa3d0);
    mtc1(zero, f12);
    v0 = 0x44200000;
    mtc1(v0, f14);
    v0 = 0x43E00000;
    mtc1(v0, f15);
    mov_s(f13, f12);
    jal(ctx, 0x197E70u, gen::fn_sub_4A9F20_004a9f20);
    jal(ctx, 0x197E78u, gen::fn_sub_4B6350_004b6350);
    s0 = 0x960000;
    s0 = addiu(s0, 376);  // &0x960178
    a0 = 0xC000;
    a1 = 0x40000;
    lw(v0, s0, 0);  // 0x960178
    jalr(ctx, 0x197E94u, v0.u());
    v1 = 0x960000;
    sw(v0, v1, -2692);  // 0x95F57C
    v1 = 12288;
    v0 = 0x960000;
    sw(v1, v0, -2688);  // 0x95F580
    a0 = 0xA0000;
    a1 = 0x40000;
    lw(v0, s0, 0);  // 0x960178
    jalr(ctx, 0x197EBCu, v0.u());
    a0 = v0;
    a1 = 0xA0000;
    jal(ctx, 0x197ECCu, gen::fn_sub_1919C0_001919c0);
    a0 = addiu(gp, -27620);  // "bmp"
    a1 = 0x4C0000;
    a1 = addiu(a1, -23904);  // &sub_4BA2A0
    a2 = 0x4C0000;
    a2 = addiu(a2, -21168);  // &sub_4BAD50
    jal(ctx, 0x197EE8u, gen::fn_sub_4CCD50_004ccd50);
    if (v0 != 0) {
        // 0x00197f04
        charge(ctx, 9);
        a0 = addiu(gp, -27616);  // "tmx"
        a1 = 0x110000;
        a1 = addiu(a1, -6912);  // &sub_10E500
        a2 = 0x110000;
        a2 = addiu(a2, -6672);  // &sub_10E5F0
        jal(ctx, 0x197F18u, gen::fn_sub_4CCD50_004ccd50);
        if (v0 != 0) {
            // 0x00197f34
            charge(ctx, 1);
            v1 = 1;
        } else {
            // 0x00197f28
            charge(ctx, 3);
            v1 = 0;
        }
    } else {
        // 0x00197ef8
        charge(ctx, 3);
        v1 = 0;
    }
    // 0x00197f38
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x00197f40
        charge(ctx, 6);
        a0 = 0x680000;
        a0 = addiu(a0, -30864);  // "Cannot register image file format"
        a1 = addiu(gp, -27608);  // "kwln.c"
        a2 = 1224;
        jal(ctx, 0x197F50u, gen::fn_sub_19D400_0019d400);
    }
    // 0x00197f58 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x4B0);
}

// 0x00197F80 sub_197F80 -- 48 bytes; frame 0x10: ra sp+0x0
// sub_197F80(obj, text) [kwlnAdxErrorPrint]: scePrintf(text); scePrintf("\n") (0x7CC120). Installed as a callback
// (data reference only).
void sub_197F80(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00197f80
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x197F8Cu, gen::fn_scePrintf_00505e48);
    a0 = addiu(gp, -27600);  // &0x7CC120
    jal(ctx, 0x197F98u, gen::fn_scePrintf_00505e48);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00198540 sub_198540 -- 24 bytes; leaf frame (no stack)
// sub_198540(i) [kwlnGetWorld]: returns 0x7CE0A0[i] (the world table; index *0x7CE0CC is the current one).
void sub_198540(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00198540
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = sll(a0, 2);
    v0 = addiu(gp, -19536);  // &0x7CE0A0
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
}

// 0x00198560 sub_198560 -- 12 bytes; leaf frame (no stack)
// sub_198560() [kwlnGetLight0]: the first light kwlnInitRenderer made (0x7CE0A8).
void sub_198560(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x00198560
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, gp, -19528);  // 0x7CE0A8
}

// 0x00198570 sub_198570 -- 12 bytes; leaf frame (no stack)
// sub_198570() [kwlnGetLight1]: the second light (0x7CE0AC).
void sub_198570(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x00198570
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, gp, -19524);  // 0x7CE0AC
}

// 0x00198580 sub_198580 -- 12 bytes; leaf frame (no stack)
// sub_198580() [kwlnGetLight2]: the third light (0x7CE0B0).
void sub_198580(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x00198580
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, gp, -19520);  // 0x7CE0B0
}

// 0x00198590 sub_198590 -- 12 bytes; leaf frame (no stack)
// sub_198590() [kwlnGetMainCamera]: g_kwlnMainCamera (0x7CE0C0); 208 callers (every draw task).
void sub_198590(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x00198590
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, gp, -19504);  // g_kwlnMainCamera
}

// 0x001985A0 sub_1985A0 -- 12 bytes; leaf frame (no stack)
// sub_1985A0() [kwlnGetClearColor]: &0x7CE128, the RGBA the draw-begin tasks clear the camera with.
void sub_1985A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x001985a0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = addiu(gp, -19400);  // &0x7CE128
}

// 0x001985B0 sub_1985B0 -- 24 bytes; leaf frame (no stack)
// sub_1985B0(r, g, b, a) [kwlnSetClearColor]: stores the four bytes of the clear colour 0x7CE128..0x7CE12B.
void sub_1985B0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x001985b0
    enter(ctx, 6);  // entry check point + this block's cycles
    sb(a0, gp, -19400);  // 0x7CE128
    sb(a1, gp, -19399);  // 0x7CE129
    sb(a2, gp, -19398);  // 0x7CE12A
    sb(a3, gp, -19397);  // 0x7CE12B
}

// 0x001985D0 sub_1985D0 -- 12 bytes; leaf frame (no stack)
// sub_1985D0() [kwlnGetBaseClearColor]: &0x7CE124, the unscaled clear colour (sub_19F8F0 scales it into 0x7CE128).
void sub_1985D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x001985d0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = addiu(gp, -19404);  // &0x7CE124
}

// 0x001985E0 sub_1985E0 -- 24 bytes; leaf frame (no stack)
// sub_1985E0(r, g, b, a) [kwlnSetBaseClearColor]: stores the base clear colour 0x7CE124..0x7CE127.
void sub_1985E0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x001985e0
    enter(ctx, 6);  // entry check point + this block's cycles
    sb(a0, gp, -19404);  // 0x7CE124
    sb(a1, gp, -19403);  // 0x7CE125
    sb(a2, gp, -19402);  // 0x7CE126
    sb(a3, gp, -19401);  // 0x7CE127
}

// 0x00198650 kwlnRootUpdateTask -- 672 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// kwlnRootUpdateTask(task) ("rootProc", the root of every task): a jump-table state machine on work +0 (work +4 = the
// game root task / the prompt task):
//   0: sub_103580 (pad update); once sub_109DF0(0) reports ready: K_SceneDraw_CreateTasks, sub_199440 (the 3-D
//      pipeline task), then the frame's draw-pass tasks as children, in draw order: 2D Draw Begin (sub_198B50), 2D
//      Draw Pre End, 2D Draw End, 3D on 2D Zclear, 3D on 2D Draw Begin, 3D on 2D Draw End, drawBustupProc, etc Draw
//      Begin, etc Draw, etc Draw End, <<< show raster >>>; state 1;
//   1: sub_103580; 0x7CE12C = 0; state 2;
//   2: when no game root runs (+4 == 0): kwlnSetFlags(0x80000000, 0), 0x7CE114 = 1, gmRoot_CreateGameRootTask(task);
//      state 3;
//   3: when the game root has died: +4 = 0, state 2 (the game restarts its root);
//   4: return -1 (the root ends: kwlnMain then makes a new one: a soft reset);
//   5: kwlnSetFlags(0x80000000, 0), +4 = sub_192DE0() (the scenario prompt), state 6;
//   6: when the prompt task is gone: sub_195DE0 (new-game data), +4 = 0, state 2.
void kwlnRootUpdateTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00198650
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    using namespace boot;
    s1 = a0;  // the root task
    lw(s0, a0, task::kWork);  // s0 = work: +0 state, +4 the game root / the prompt task
    lw(v0, s0, 0);
    at = sltiu(v0, 7);
    bool ended = false;  // host-side: state 4 returns -1; every other path runs the shared "return 0" block
    if (at != 0) {
        // 0x00198678
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 27184);  // &0x7B6A30
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x198694u:  // table[0]
            // 0x00198694: state 0 -- wait until sub_109DF0(0) is ready
            charge(ctx, 7);
            jal(ctx, 0x198694u, gen::fn_sub_103580_00103580);
            a0 = 0;
            jal(ctx, 0x1986A0u, gen::fn_sub_109DF0_00109df0);
            if (v0 != 0) {
                // 0x001986b0: the frame's draw tasks, created as children in draw order
                charge(ctx, 77);
                a0 = s1;
                jal(ctx, 0x1986B4u, gen::fn_K_SceneDraw_CreateTasks_0019f730);
                a0 = s1;
                jal(ctx, 0x1986C0u, gen::fn_sub_199440_00199440);
                jal(ctx, 0x1986C8u, gen::fn_sub_198B50_00198b50);
                a0 = s1;
                a1 = v0;
                jal(ctx, 0x1986D8u, gen::fn_kwlnTaskAddChild_00195550);
                jal(ctx, 0x1986E0u, gen::fn_sub_198B90_00198b90);
                a0 = s1;
                a1 = v0;
                jal(ctx, 0x1986F0u, gen::fn_kwlnTaskAddChild_00195550);
                jal(ctx, 0x1986F8u, gen::fn_sub_198BD0_00198bd0);
                a0 = s1;
                a1 = v0;
                jal(ctx, 0x198708u, gen::fn_kwlnTaskAddChild_00195550);
                jal(ctx, 0x198710u, gen::fn_sub_198DD0_00198dd0);
                a0 = s1;
                a1 = v0;
                jal(ctx, 0x198720u, gen::fn_kwlnTaskAddChild_00195550);
                jal(ctx, 0x198728u, gen::fn_sub_198E10_00198e10);
                a0 = s1;
                a1 = v0;
                jal(ctx, 0x198738u, gen::fn_kwlnTaskAddChild_00195550);
                jal(ctx, 0x198740u, gen::fn_sub_198E50_00198e50);
                a0 = s1;
                a1 = v0;
                jal(ctx, 0x198750u, gen::fn_kwlnTaskAddChild_00195550);
                jal(ctx, 0x198758u, gen::fn_sub_1993D0_001993d0);
                a0 = s1;
                a1 = v0;
                jal(ctx, 0x198768u, gen::fn_kwlnTaskAddChild_00195550);
                jal(ctx, 0x198770u, gen::fn_sub_199080_00199080);
                a0 = s1;
                a1 = v0;
                jal(ctx, 0x198780u, gen::fn_kwlnTaskAddChild_00195550);
                jal(ctx, 0x198788u, gen::fn_sub_1990C0_001990c0);
                a0 = s1;
                a1 = v0;
                jal(ctx, 0x198798u, gen::fn_kwlnTaskAddChild_00195550);
                jal(ctx, 0x1987A0u, gen::fn_sub_199100_00199100);
                a0 = s1;
                a1 = v0;
                jal(ctx, 0x1987B0u, gen::fn_kwlnTaskAddChild_00195550);
                jal(ctx, 0x1987B8u, gen::fn_kwlnRootCreateShowRasterTask_00199360);
                a0 = s1;
                a1 = v0;
                jal(ctx, 0x1987C8u, gen::fn_kwlnTaskAddChild_00195550);
                lw(v0, s0, 0);
                v0 = addiu(v0, 1);
                sw(v0, s0, 0);
            }
            break;
        case 0x1987E4u:  // table[1]
            // 0x001987e4: state 1
            charge(ctx, 8);
            jal(ctx, 0x1987E4u, gen::fn_sub_103580_00103580);
            sw(zero, gp, -19396);  // 0x7CE12C
            lw(v0, s0, 0);
            v0 = addiu(v0, 1);
            sw(v0, s0, 0);
            break;
        case 0x198804u:  // table[2]
            // 0x00198804: state 2 -- start the game root unless one runs
            charge(ctx, 3);
            lw(v0, s0, 4);
            if (v0 == 0) {
                // 0x00198810
                charge(ctx, 9);
                a0 = lui(0x8000);
                a1 = 0;
                jal(ctx, 0x198818u, gen::fn_kwlnSetFlags_00198610);
                v0 = 1;
                sw(v0, gp, -19420);  // 0x7CE114
                a0 = s1;
                jal(ctx, 0x19882Cu, gen::fn_gmRoot_CreateGameRootTask_002664c0);
            }
            // 0x00198834
            charge(ctx, 4);
            v0 = 3;
            sw(v0, s0, 0);
            break;
        case 0x198844u:  // table[3]
            // 0x00198844: state 3 -- a dead game root sends the root back to state 2
            charge(ctx, 3);
            lw(a0, s0, 4);
            if (a0 != 0) {
                // 0x00198850
                charge(ctx, 4);
                jal(ctx, 0x198850u, gen::fn_kwlnTaskExists_00195460);
                if (v0 == 0) {
                    // 0x00198860
                    charge(ctx, 5);
                    sw(zero, s0, 4);
                    v0 = 2;
                    sw(v0, s0, 0);
                }
            }
            break;
        case 0x198874u:  // table[4]
            // 0x00198874: state 4 -- the root ends (kwlnMain makes a new one: a soft reset)
            charge(ctx, 3);
            v0 = si(-1);
            ended = true;
            break;
        case 0x198880u:  // table[5]
            // 0x00198880: state 5 -- the scenario prompt (ChoiceDataFileSetup)
            charge(ctx, 11);
            a0 = lui(0x8000);
            a1 = 0;
            jal(ctx, 0x198888u, gen::fn_kwlnSetFlags_00198610);
            jal(ctx, 0x198890u, gen::fn_sub_192DE0_00192de0);
            sw(v0, s0, 4);
            v0 = 6;
            sw(v0, s0, 0);
            break;
        case 0x1988ACu:  // table[6]
            // 0x001988ac: state 6 -- prompt gone: the new-game data, then state 2
            charge(ctx, 5);
            lw(a0, s0, 4);
            jal(ctx, 0x1988B0u, gen::fn_kwlnTaskExists_00195460);
            if (v0 == 0) {
                // 0x001988c0
                charge(ctx, 5);
                jal(ctx, 0x1988C0u, gen::fn_sub_195DE0_00195de0);
                sw(zero, s0, 4);
                v0 = 2;
                sw(v0, s0, 0);
            }
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    }
    if (!ended) {
        // 0x001988d4: keep running (also a state >= 7)
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x001988d8 (the shared epilogue)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001988F0 sub_1988F0 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1988F0(task) [kwlnRootDestroyTask]: destroy callback of "rootProc": sub_108F70, sub_3B5AB0, RwFree(work).
void sub_1988F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001988f0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x198900u, gen::fn_sub_108F70_00108f70);
    jal(ctx, 0x198908u, gen::fn_sub_3B5AB0_003b5ab0);
    lw(a0, s0, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x19891Cu, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00198940 kwlnRootCreateTask -- 160 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// kwlnRootCreateTask(): RwCalloc(1, 8) work, kwlnTaskInit("rootProc", 0, kwlnRootUpdateTask, sub_1988F0, work), then
// sub_109CA0(0, 1) and sub_109CA0(1, 2); returns the task (0 when the allocation fails). Caller: kwlnMain.
void kwlnRootCreateTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00198940
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 1;
    a1 = 8;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x198960u, v0.u());
    if (v0 != 0) {
        // 0x0019897c
        charge(ctx, 20);
        a0 = 0x680000;
        a0 = addiu(a0, -30776);  // "rootProc"
        a1 = 0;
        a2 = 0x1A0000;
        a2 = addiu(a2, -31152);  // &kwlnRootUpdateTask
        a3 = 0x1A0000;
        a3 = addiu(a3, -30480);  // &sub_1988F0
        t0 = v0;
        jal(ctx, 0x19899Cu, gen::fn_kwlnTaskInit_00194c50);
        s0 = v0;
        a0 = 0;
        a1 = 1;
        jal(ctx, 0x1989B0u, gen::fn_sub_109CA0_00109ca0);
        a0 = 1;
        a1 = 2;
        jal(ctx, 0x1989C0u, gen::fn_sub_109CA0_00109ca0);
        v0 = s0;
    } else {
        // 0x00198970
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001989cc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00198B10 kwlnRootUpdate2DDrawPreEndTask -- 12 bytes; leaf frame (no stack)
// kwlnRootUpdate2DDrawPreEndTask(task): "2D Draw Pre End" (priority 0x146F): nothing (returns 0: keep running).
void kwlnRootUpdate2DDrawPreEndTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00198b10
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00198B50 sub_198B50 -- 60 bytes; frame 0x10: ra sp+0x0
// sub_198B50() [kwlnRootCreate2DDrawBeginTask]: kwlnTaskInit("2D Draw Begin", 0x1064 (4196), kwlnRootUpdate2DDrawBeginTask,
// 0, 0).
void sub_198B50(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00198b50
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x680000;
    a0 = addiu(a0, -30744);  // "2D Draw Begin"
    a1 = 4196;
    a2 = 0x1A0000;
    a2 = addiu(a2, -30240);  // &kwlnRootUpdate2DDrawBeginTask
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x198B74u, gen::fn_kwlnTaskInit_00194c50);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00198B90 sub_198B90 -- 60 bytes; frame 0x10: ra sp+0x0
// sub_198B90() [kwlnRootCreate2DDrawPreEndTask]: kwlnTaskInit("2D Draw Pre End", 0x146F (5231),
// kwlnRootUpdate2DDrawPreEndTask, 0, 0).
void sub_198B90(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00198b90
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x680000;
    a0 = addiu(a0, -30720);  // "2D Draw Pre End"
    a1 = 5231;
    a2 = 0x1A0000;
    a2 = addiu(a2, -29936);  // &kwlnRootUpdate2DDrawPreEndTask
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x198BB4u, gen::fn_kwlnTaskInit_00194c50);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00198BD0 sub_198BD0 -- 60 bytes; frame 0x10: ra sp+0x0
// sub_198BD0() [kwlnRootCreate2DDrawEndTask]: kwlnTaskInit("2D Draw End", 0x1479 (5241), kwlnRootUpdate2DDrawEndTask, 0, 0).
void sub_198BD0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00198bd0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x680000;
    a0 = addiu(a0, -30704);  // "2D Draw End"
    a1 = 5241;
    a2 = 0x1A0000;
    a2 = addiu(a2, -29920);  // &kwlnRootUpdate2DDrawEndTask
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x198BF4u, gen::fn_kwlnTaskInit_00194c50);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00198DD0 sub_198DD0 -- 60 bytes; frame 0x10: ra sp+0x0
// sub_198DD0() [kwlnRootCreate3DOn2DZClearTask]: kwlnTaskInit("3D on 2D Zclear", 0x147B (5243),
// kwlnRootUpdate3DOn2DZClearTask, 0, 0).
void sub_198DD0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00198dd0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x680000;
    a0 = addiu(a0, -30688);  // "3D on 2D Zclear"
    a1 = 5243;
    a2 = 0x1A0000;
    a2 = addiu(a2, -29680);  // &kwlnRootUpdate3DOn2DZClearTask
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x198DF4u, gen::fn_kwlnTaskInit_00194c50);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00198E10 sub_198E10 -- 60 bytes; frame 0x10: ra sp+0x0
// sub_198E10() [kwlnRootCreate3DOn2DDrawBeginTask]: kwlnTaskInit("3D on 2D Draw Begin", 0x147D (5245),
// kwlnRootUpdate3DOn2DDrawBeginTask, 0, 0).
void sub_198E10(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00198e10
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x680000;
    a0 = addiu(a0, -30672);  // "3D on 2D Draw Begin"
    a1 = 5245;
    a2 = 0x1A0000;
    a2 = addiu(a2, -29600);  // &kwlnRootUpdate3DOn2DDrawBeginTask
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x198E34u, gen::fn_kwlnTaskInit_00194c50);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00198E50 sub_198E50 -- 60 bytes; frame 0x10: ra sp+0x0
// sub_198E50() [kwlnRootCreate3DOn2DDrawEndTask]: kwlnTaskInit("3D on 2D Draw End", 0x18B0 (6320),
// kwlnRootUpdate3DOn2DDrawEndTask, 0, 0).
void sub_198E50(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00198e50
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x680000;
    a0 = addiu(a0, -30640);  // "3D on 2D Draw End"
    a1 = 6320;
    a2 = 0x1A0000;
    a2 = addiu(a2, -29408);  // &kwlnRootUpdate3DOn2DDrawEndTask
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x198E74u, gen::fn_kwlnTaskInit_00194c50);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00198F90 kwlnRootUpdateEtcDrawTask -- 52 bytes; frame 0x10: ra sp+0x0
// kwlnRootUpdateEtcDrawTask(task): "etc Draw" (priority 0x18BF): sub_107060 (the fade), dbgPrintDrawScreen,
// sub_1043B0 (the debug printer's reset); returns 0.
void kwlnRootUpdateEtcDrawTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00198f90
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x198F98u, gen::fn_sub_107060_00107060);
    jal(ctx, 0x198FA0u, gen::fn_dbgPrintDrawScreen_00104420);
    jal(ctx, 0x198FA8u, gen::fn_sub_1043B0_001043b0);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00199080 sub_199080 -- 60 bytes; frame 0x10: ra sp+0x0
// sub_199080() [kwlnRootCreateEtcDrawBeginTask]: kwlnTaskInit("etc Draw Begin", 0x18B3 (6323), kwlnRootUpdateEtcDrawBeginTask,
// 0, 0).
void sub_199080(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00199080
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x680000;
    a0 = addiu(a0, -30616);  // "etc Draw Begin"
    a1 = 6323;
    a2 = 0x1A0000;
    a2 = addiu(a2, -29040);  // &kwlnRootUpdateEtcDrawBeginTask
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x1990A4u, gen::fn_kwlnTaskInit_00194c50);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001990C0 sub_1990C0 -- 60 bytes; frame 0x10: ra sp+0x0
// sub_1990C0() [kwlnRootCreateEtcDrawTask]: kwlnTaskInit("etc Draw", 0x18BF (6335), kwlnRootUpdateEtcDrawTask, 0, 0).
void sub_1990C0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001990c0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x680000;
    a0 = addiu(a0, -30600);  // "etc Draw"
    a1 = 6335;
    a2 = 0x1A0000;
    a2 = addiu(a2, -28784);  // &kwlnRootUpdateEtcDrawTask
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x1990E4u, gen::fn_kwlnTaskInit_00194c50);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00199100 sub_199100 -- 60 bytes; frame 0x10: ra sp+0x0
// sub_199100() [kwlnRootCreateEtcDrawEndTask]: kwlnTaskInit("etc Draw End", 0x1CD3 (7379), kwlnRootUpdateDrawEndTask, 0, 0).
void sub_199100(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00199100
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x680000;
    a0 = addiu(a0, -30584);  // "etc Draw End"
    a1 = 7379;
    a2 = 0x1A0000;
    a2 = addiu(a2, -28720);  // &kwlnRootUpdateDrawEndTask
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x199124u, gen::fn_kwlnTaskInit_00194c50);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00199360 kwlnRootCreateShowRasterTask -- 60 bytes; frame 0x10: ra sp+0x0
// kwlnRootCreateShowRasterTask(): kwlnTaskInit("<<< show raster >>>", 0x1CE4 (7396), kwlnRootUpdateShowRasterTask, 0, 0):
// the last task of every frame (the flip; stays recompiled: it reads and clears T0 itself).
void kwlnRootCreateShowRasterTask(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00199360
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x680000;
    a0 = addiu(a0, -30560);  // "<<< show raster >>>"
    a1 = 7396;
    a2 = 0x1A0000;
    a2 = addiu(a2, -28352);  // &kwlnRootUpdateShowRasterTask
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x199384u, gen::fn_kwlnTaskInit_00194c50);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001993A0 kwlnRootUpdateDrawBustupProcTask -- 36 bytes; frame 0x10: ra sp+0x0
// kwlnRootUpdateDrawBustupProcTask(task): "drawBustupProc" (priority 0x149C): sub_1058A0 (the bust-up banks); 0.
void kwlnRootUpdateDrawBustupProcTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001993a0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1993A8u, gen::fn_sub_1058A0_001058a0);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001993D0 sub_1993D0 -- 60 bytes; frame 0x10: ra sp+0x0
// sub_1993D0() [kwlnRootCreateDrawBustupProcTask]: kwlnTaskInit("drawBustupProc", 0x149C (5276),
// kwlnRootUpdateDrawBustupProcTask, 0, 0).
void sub_1993D0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001993d0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x680000;
    a0 = addiu(a0, -30536);  // "drawBustupProc"
    a1 = 5276;
    a2 = 0x1A0000;
    a2 = addiu(a2, -27744);  // &kwlnRootUpdateDrawBustupProcTask
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x1993F4u, gen::fn_kwlnTaskInit_00194c50);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00199410 sub_199410 -- 48 bytes; frame 0x10: ra sp+0x0
// sub_199410(task) [K_SPipe_DestroyTask]: destroy callback of the 3-D pipeline task: RwFree(work), clears its
// singleton word 0x7CE134.
void sub_199410(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00199410
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x199424u, v0.u());
    sw(zero, gp, -19388);  // 0x7CE134
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00199440 sub_199440 -- 224 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_199440(parent) [K_SPipe_CreateTask] (k_spipe.c): K_Assert(line 118) when the singleton 0x7CE134 exists; RwCalloc
// 8-byte work, kwlnTaskCreate(parent, 0x7CC138, 5, no update, sub_199410, work) -> 0x7CE134; work = {*0x7CE11C,
// *0x7CE118}; then its children: "shadow node(camera all clear)" (sub_1997A0), "3D Draw Begin" (sub_1996C0), "3D Draw
// End" (sub_199700).
void sub_199440(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00199440
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, -19388);  // 0x7CE134
    if (v0 != 0) {
        // 0x00199460
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, -30520);  // "k_spipe.c"
        a1 = 118;
        jal(ctx, 0x19946Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00199474
    charge(ctx, 10);
    a0 = 1;
    a1 = 8;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x199488u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001994a8
        charge(ctx, 24);
        a0 = s1;
        a1 = addiu(gp, -27576);  // "3D Draw"
        a2 = 5;
        a3 = 0;
        t0 = 0x1A0000;
        t0 = addiu(t0, -27632);  // &sub_199410
        t1 = s0;
        jal(ctx, 0x1994C4u, gen::fn_kwlnTaskCreate_00194b20);
        sw(v0, gp, -19388);  // 0x7CE134
        lw(v0, gp, -19412);  // 0x7CE11C
        sw(v0, s0, 0);
        lw(v0, gp, -19416);  // 0x7CE118
        sw(v0, s0, 4);
        lw(a0, gp, -19388);  // 0x7CE134
        jal(ctx, 0x1994E4u, gen::fn_sub_1997A0_001997a0);
        lw(a0, gp, -19388);  // 0x7CE134
        jal(ctx, 0x1994F0u, gen::fn_sub_1996C0_001996c0);
        lw(a0, gp, -19388);  // 0x7CE134
        jal(ctx, 0x1994FCu, gen::fn_sub_199700_00199700);
        lw(v0, gp, -19388);  // 0x7CE134
    } else {
        // 0x0019949c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00199508 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001996C0 sub_1996C0 -- 60 bytes; frame 0x10: ra sp+0x0
// sub_1996C0(parent) [K_SPipe_Create3DDrawBeginTask]: kwlnTaskCreate(parent, "3D Draw Begin", 0x832 (2098),
// K_SPipe_Update3DDrwBeginTask, 0, 0).
void sub_1996C0(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001996c0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 0x680000;
    a1 = addiu(a1, -30504);  // "3D Draw Begin"
    a2 = 2098;
    a3 = 0x1A0000;
    a3 = addiu(a3, -27360);  // &K_SPipe_Update3DDrwBeginTask
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x1996E4u, gen::fn_kwlnTaskCreate_00194b20);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00199700 sub_199700 -- 60 bytes; frame 0x10: ra sp+0x0
// sub_199700(parent) [K_SPipe_Create3DDrawEndTask]: kwlnTaskCreate(parent, "3D Draw End", 0x1047 (4167),
// K_SPipe_Update3DDrwEndTask, 0, 0).
void sub_199700(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00199700
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 0x680000;
    a1 = addiu(a1, -30488);  // "3D Draw End"
    a2 = 4167;
    a3 = 0x1A0000;
    a3 = addiu(a3, -27152);  // &K_SPipe_Update3DDrwEndTask
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x199724u, gen::fn_kwlnTaskCreate_00194b20);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001997A0 sub_1997A0 -- 60 bytes; frame 0x10: ra sp+0x0
// sub_1997A0(parent) [K_SPipe_CreateShadowNodeTask]: kwlnTaskCreate(parent, "shadow node(camera all clear)", 0x815
// (2069), kwlnRootUpdateShadowNodeCameraTask, 0, 0): the first draw task of a frame.
void sub_1997A0(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001997a0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 0x680000;
    a1 = addiu(a1, -30464);  // "shadow node(camera all clear)"
    a2 = 2069;
    a3 = 0x1A0000;
    a3 = addiu(a3, -26816);  // &kwlnRootUpdateShadowNodeCameraTask
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x1997C4u, gen::fn_kwlnTaskCreate_00194b20);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
