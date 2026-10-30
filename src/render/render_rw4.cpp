// Slice render_rw4: RenderWare, fourth pass (docs/ANALYSIS/22_rendering.md; the group overview and the record layouts
// are in game/include/p3fes/game/render_rw4.h). Every body started as p3fes_handgen's output and keeps the recompiled
// body's registers, frame, spills, $ra links, cycle charges and check points statement for statement
// (game/include/p3fes/game/hg_cpu.h); what was added is the role of each function, the role of each block, the
// names of the record offsets and the RW globals. sub_* keep their symbols/functions.json names; proposed names are
// in brackets (symbols/deltas/render_rw4.sym).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/render_rw4.h"

namespace p3fes::recomp_gen {
void fn_DIntr_0050d3a0(p3fes::EEContext&);
void fn_EIntr_0050d3f0(p3fes::EEContext&);
void fn_RpSkyTexCacheAccessRaster_004f1020(p3fes::EEContext&);
void fn_RwResourcesSetArenaSize_004c4c00(p3fes::EEContext&);
void fn_SyncDCache_00503a58(p3fes::EEContext&);
void fn___udivdi3_0052fe98(p3fes::EEContext&);
void fn__rwDMAAddPURef_004d51c0(p3fes::EEContext&);
void fn__rwDMAForceBufferSwap_004d4df0(p3fes::EEContext&);
void fn__rwDMAOpenGIFPkt_004d54e0(p3fes::EEContext&);
void fn__rwDeviceSystemRequest_004ca3e0(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_meshHeaderForAllMeshes_00495f10(p3fes::EEContext&);
void fn_qsort_005225f8(p3fes::EEContext&);
void fn_sceDmaGetChan_004fa8f0(p3fes::EEContext&);
void fn_sceGsExecStoreImage_004f9e28(p3fes::EEContext&);
void fn_sceGsSetDefStoreImage_004f9ce8(p3fes::EEContext&);
void fn_sceGsSyncPath_004f99d0(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_skyFillInPktForUpLoadAlignedContiguousRectangle_004ef020(p3fes::EEContext&);
void fn_sub_4733C0_004733c0(p3fes::EEContext&);
void fn_sub_47B280_0047b280(p3fes::EEContext&);
void fn_sub_47B750_0047b750(p3fes::EEContext&);
void fn_sub_47BB40_0047bb40(p3fes::EEContext&);
void fn_sub_47BE10_0047be10(p3fes::EEContext&);
void fn_sub_4933D0_004933d0(p3fes::EEContext&);
void fn_sub_495320_00495320(p3fes::EEContext&);
void fn_sub_4959C0_004959c0(p3fes::EEContext&);
void fn_sub_495B10_00495b10(p3fes::EEContext&);
void fn_sub_495C20_00495c20(p3fes::EEContext&);
void fn_sub_495CF0_00495cf0(p3fes::EEContext&);
void fn_sub_4967A0_004967a0(p3fes::EEContext&);
void fn_sub_496BE0_00496be0(p3fes::EEContext&);
void fn_sub_496CD0_00496cd0(p3fes::EEContext&);
void fn_sub_497600_00497600(p3fes::EEContext&);
void fn_sub_4982B0_004982b0(p3fes::EEContext&);
void fn_sub_498720_00498720(p3fes::EEContext&);
void fn_sub_498E70_00498e70(p3fes::EEContext&);
void fn_sub_499140_00499140(p3fes::EEContext&);
void fn_sub_49CC30_0049cc30(p3fes::EEContext&);
void fn_sub_49E5A0_0049e5a0(p3fes::EEContext&);
void fn_sub_4A08F0_004a08f0(p3fes::EEContext&);
void fn_sub_4A0CE0_004a0ce0(p3fes::EEContext&);
void fn_sub_4AB0E0_004ab0e0(p3fes::EEContext&);
void fn_sub_4B91B0_004b91b0(p3fes::EEContext&);
void fn_sub_4C0240_004c0240(p3fes::EEContext&);
void fn_sub_4C0370_004c0370(p3fes::EEContext&);
void fn_sub_4C03D0_004c03d0(p3fes::EEContext&);
void fn_sub_4C0420_004c0420(p3fes::EEContext&);
void fn_sub_4C0470_004c0470(p3fes::EEContext&);
void fn_sub_4C06B0_004c06b0(p3fes::EEContext&);
void fn_sub_4C0820_004c0820(p3fes::EEContext&);
void fn_sub_4C12D0_004c12d0(p3fes::EEContext&);
void fn_sub_4C1450_004c1450(p3fes::EEContext&);
void fn_sub_4C15A0_004c15a0(p3fes::EEContext&);
void fn_sub_4C1600_004c1600(p3fes::EEContext&);
void fn_sub_4C1750_004c1750(p3fes::EEContext&);
void fn_sub_4C17F0_004c17f0(p3fes::EEContext&);
void fn_sub_4C1820_004c1820(p3fes::EEContext&);
void fn_sub_4C1850_004c1850(p3fes::EEContext&);
void fn_sub_4C18B0_004c18b0(p3fes::EEContext&);
void fn_sub_4C1910_004c1910(p3fes::EEContext&);
void fn_sub_4C1970_004c1970(p3fes::EEContext&);
void fn_sub_4C19F0_004c19f0(p3fes::EEContext&);
void fn_sub_4C1C50_004c1c50(p3fes::EEContext&);
void fn_sub_4C1D10_004c1d10(p3fes::EEContext&);
void fn_sub_4C1E70_004c1e70(p3fes::EEContext&);
void fn_sub_4C20B0_004c20b0(p3fes::EEContext&);
void fn_sub_4C2200_004c2200(p3fes::EEContext&);
void fn_sub_4C2A30_004c2a30(p3fes::EEContext&);
void fn_sub_4C2A70_004c2a70(p3fes::EEContext&);
void fn_sub_4C2AC0_004c2ac0(p3fes::EEContext&);
void fn_sub_4C2B20_004c2b20(p3fes::EEContext&);
void fn_sub_4C2B90_004c2b90(p3fes::EEContext&);
void fn_sub_4C2C00_004c2c00(p3fes::EEContext&);
void fn_sub_4C2CC0_004c2cc0(p3fes::EEContext&);
void fn_sub_4C2CF0_004c2cf0(p3fes::EEContext&);
void fn_sub_4C2D20_004c2d20(p3fes::EEContext&);
void fn_sub_4C2F10_004c2f10(p3fes::EEContext&);
void fn_sub_4C2F30_004c2f30(p3fes::EEContext&);
void fn_sub_4C2FB0_004c2fb0(p3fes::EEContext&);
void fn_sub_4C2FC0_004c2fc0(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);
void fn_sub_4C35D0_004c35d0(p3fes::EEContext&);
void fn_sub_4C3880_004c3880(p3fes::EEContext&);
void fn_sub_4C38C0_004c38c0(p3fes::EEContext&);
void fn_sub_4C3960_004c3960(p3fes::EEContext&);
void fn_sub_4C3970_004c3970(p3fes::EEContext&);
void fn_sub_4C3B50_004c3b50(p3fes::EEContext&);
void fn_sub_4C3B60_004c3b60(p3fes::EEContext&);
void fn_sub_4C3B70_004c3b70(p3fes::EEContext&);
void fn_sub_4C3C30_004c3c30(p3fes::EEContext&);
void fn_sub_4C4080_004c4080(p3fes::EEContext&);
void fn_sub_4C4200_004c4200(p3fes::EEContext&);
void fn_sub_4C43B0_004c43b0(p3fes::EEContext&);
void fn_sub_4C45F0_004c45f0(p3fes::EEContext&);
void fn_sub_4C46F0_004c46f0(p3fes::EEContext&);
void fn_sub_4C4750_004c4750(p3fes::EEContext&);
void fn_sub_4C47E0_004c47e0(p3fes::EEContext&);
void fn_sub_4C4890_004c4890(p3fes::EEContext&);
void fn_sub_4C4930_004c4930(p3fes::EEContext&);
void fn_sub_4C4D20_004c4d20(p3fes::EEContext&);
void fn_sub_4C4D70_004c4d70(p3fes::EEContext&);
void fn_sub_4C4EB0_004c4eb0(p3fes::EEContext&);
void fn_sub_4C4F30_004c4f30(p3fes::EEContext&);
void fn_sub_4C4F90_004c4f90(p3fes::EEContext&);
void fn_sub_4C5090_004c5090(p3fes::EEContext&);
void fn_sub_4C5140_004c5140(p3fes::EEContext&);
void fn_sub_4C5250_004c5250(p3fes::EEContext&);
void fn_sub_4C53F0_004c53f0(p3fes::EEContext&);
void fn_sub_4C5620_004c5620(p3fes::EEContext&);
void fn_sub_4C5780_004c5780(p3fes::EEContext&);
void fn_sub_4C58A0_004c58a0(p3fes::EEContext&);
void fn_sub_4C5A50_004c5a50(p3fes::EEContext&);
void fn_sub_4C5C30_004c5c30(p3fes::EEContext&);
void fn_sub_4C5CB0_004c5cb0(p3fes::EEContext&);
void fn_sub_4C5D30_004c5d30(p3fes::EEContext&);
void fn_sub_4C5EA0_004c5ea0(p3fes::EEContext&);
void fn_sub_4C5F70_004c5f70(p3fes::EEContext&);
void fn_sub_4C6000_004c6000(p3fes::EEContext&);
void fn_sub_4C6140_004c6140(p3fes::EEContext&);
void fn_sub_4C6150_004c6150(p3fes::EEContext&);
void fn_sub_4C6160_004c6160(p3fes::EEContext&);
void fn_sub_4C61B0_004c61b0(p3fes::EEContext&);
void fn_sub_4C64B0_004c64b0(p3fes::EEContext&);
void fn_sub_4C6560_004c6560(p3fes::EEContext&);
void fn_sub_4C65D0_004c65d0(p3fes::EEContext&);
void fn_sub_4C6DF0_004c6df0(p3fes::EEContext&);
void fn_sub_4C6E50_004c6e50(p3fes::EEContext&);
void fn_sub_4C6E60_004c6e60(p3fes::EEContext&);
void fn_sub_4C6F30_004c6f30(p3fes::EEContext&);
void fn_sub_4C7410_004c7410(p3fes::EEContext&);
void fn_sub_4C7460_004c7460(p3fes::EEContext&);
void fn_sub_4C78A0_004c78a0(p3fes::EEContext&);
void fn_sub_4C7CF0_004c7cf0(p3fes::EEContext&);
void fn_sub_4C7D00_004c7d00(p3fes::EEContext&);
void fn_sub_4C7D30_004c7d30(p3fes::EEContext&);
void fn_sub_4C7D80_004c7d80(p3fes::EEContext&);
void fn_sub_4C81A0_004c81a0(p3fes::EEContext&);
void fn_sub_4C81D0_004c81d0(p3fes::EEContext&);
void fn_sub_4C8240_004c8240(p3fes::EEContext&);
void fn_sub_4C83C0_004c83c0(p3fes::EEContext&);
void fn_sub_4C8650_004c8650(p3fes::EEContext&);
void fn_sub_4C8680_004c8680(p3fes::EEContext&);
void fn_sub_4CA500_004ca500(p3fes::EEContext&);
void fn_sub_4CA9B0_004ca9b0(p3fes::EEContext&);
void fn_sub_4CAA50_004caa50(p3fes::EEContext&);
void fn_sub_4CAAC0_004caac0(p3fes::EEContext&);
void fn_sub_4CAB70_004cab70(p3fes::EEContext&);
void fn_sub_4CACE0_004cace0(p3fes::EEContext&);
void fn_sub_4CAD30_004cad30(p3fes::EEContext&);
void fn_sub_4CAE40_004cae40(p3fes::EEContext&);
void fn_sub_4CAF10_004caf10(p3fes::EEContext&);
void fn_sub_4CAF80_004caf80(p3fes::EEContext&);
void fn_sub_4CB050_004cb050(p3fes::EEContext&);
void fn_sub_4CB1B0_004cb1b0(p3fes::EEContext&);
void fn_sub_4CB270_004cb270(p3fes::EEContext&);
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);
void fn_sub_4CB340_004cb340(p3fes::EEContext&);
void fn_sub_4CB350_004cb350(p3fes::EEContext&);
void fn_sub_4CB420_004cb420(p3fes::EEContext&);
void fn_sub_4CB590_004cb590(p3fes::EEContext&);
void fn_sub_4CB6E0_004cb6e0(p3fes::EEContext&);
void fn_sub_4CB750_004cb750(p3fes::EEContext&);
void fn_sub_4CB890_004cb890(p3fes::EEContext&);
void fn_sub_4CB930_004cb930(p3fes::EEContext&);
void fn_sub_4CB9F0_004cb9f0(p3fes::EEContext&);
void fn_sub_4CBF20_004cbf20(p3fes::EEContext&);
void fn_sub_4CC1D0_004cc1d0(p3fes::EEContext&);
void fn_sub_4CD620_004cd620(p3fes::EEContext&);
void fn_sub_4CDE00_004cde00(p3fes::EEContext&);
void fn_sub_4CDE40_004cde40(p3fes::EEContext&);
void fn_sub_4CDE90_004cde90(p3fes::EEContext&);
void fn_sub_4CDF00_004cdf00(p3fes::EEContext&);
void fn_sub_4CDF30_004cdf30(p3fes::EEContext&);
void fn_sub_4CDF80_004cdf80(p3fes::EEContext&);
void fn_sub_4CE050_004ce050(p3fes::EEContext&);
void fn_sub_4CE0F0_004ce0f0(p3fes::EEContext&);
void fn_sub_4CE200_004ce200(p3fes::EEContext&);
void fn_sub_4CE250_004ce250(p3fes::EEContext&);
void fn_sub_4CE2C0_004ce2c0(p3fes::EEContext&);
void fn_sub_4CEFB0_004cefb0(p3fes::EEContext&);
void fn_sub_4CF0A0_004cf0a0(p3fes::EEContext&);
void fn_sub_4CF1B0_004cf1b0(p3fes::EEContext&);
void fn_sub_4CF340_004cf340(p3fes::EEContext&);
void fn_sub_4D09D0_004d09d0(p3fes::EEContext&);
void fn_sub_4D0B60_004d0b60(p3fes::EEContext&);
void fn_sub_4D0B80_004d0b80(p3fes::EEContext&);
void fn_sub_4D0BA0_004d0ba0(p3fes::EEContext&);
void fn_sub_4D0BC0_004d0bc0(p3fes::EEContext&);
void fn_sub_4D0C30_004d0c30(p3fes::EEContext&);
void fn_sub_4D0D10_004d0d10(p3fes::EEContext&);
void fn_sub_4D0DC0_004d0dc0(p3fes::EEContext&);
void fn_sub_4D0E40_004d0e40(p3fes::EEContext&);
void fn_sub_4D0F00_004d0f00(p3fes::EEContext&);
void fn_sub_4D1070_004d1070(p3fes::EEContext&);
void fn_sub_4D1110_004d1110(p3fes::EEContext&);
void fn_sub_4D1170_004d1170(p3fes::EEContext&);
void fn_sub_4D11F0_004d11f0(p3fes::EEContext&);
void fn_sub_4D1210_004d1210(p3fes::EEContext&);
void fn_sub_4D1260_004d1260(p3fes::EEContext&);
void fn_sub_4D13B0_004d13b0(p3fes::EEContext&);
void fn_sub_4D1420_004d1420(p3fes::EEContext&);
void fn_sub_4D15E0_004d15e0(p3fes::EEContext&);
void fn_sub_4D5FE0_004d5fe0(p3fes::EEContext&);
void fn_sub_4D6250_004d6250(p3fes::EEContext&);
void fn_sub_4D6B60_004d6b60(p3fes::EEContext&);
void fn_sub_4DB200_004db200(p3fes::EEContext&);
void fn_sub_4DD480_004dd480(p3fes::EEContext&);
void fn_sub_4DD700_004dd700(p3fes::EEContext&);
void fn_sub_4DE0A0_004de0a0(p3fes::EEContext&);
void fn_sub_4E4180_004e4180(p3fes::EEContext&);
void fn_sub_4E4560_004e4560(p3fes::EEContext&);
void fn_sub_4E46C0_004e46c0(p3fes::EEContext&);
void fn_sub_4E4A90_004e4a90(p3fes::EEContext&);
void fn_sub_4E4C20_004e4c20(p3fes::EEContext&);
void fn_sub_4E4E90_004e4e90(p3fes::EEContext&);
void fn_sub_4E53E0_004e53e0(p3fes::EEContext&);
void fn_sub_4E6D60_004e6d60(p3fes::EEContext&);
void fn_sub_4E8610_004e8610(p3fes::EEContext&);
void fn_sub_4EF540_004ef540(p3fes::EEContext&);
void fn_sub_4EF770_004ef770(p3fes::EEContext&);
void fn_sub_4EFA00_004efa00(p3fes::EEContext&);
void fn_sub_4F1540_004f1540(p3fes::EEContext&);
void fn_sub_4F61C0_004f61c0(p3fes::EEContext&);
void fn_triStripExtend_00497130(p3fes::EEContext&);
void fn_triStripTakeTriangle_00496f60(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace rw4;  // the RenderWare record offsets (render_rw4.h)

// sub_4DE0A0 [skyRasterLock] -- the sky driver's raster lock (standard function 15)
// ($a0 = the pixel pointer out, $a1 = the raster, $a2 = the lock flags) A camera / GS-resident raster locked
// for reading is read back from GS memory: the DMA buffers swapped and synced (_rwDMAForceBufferSwap,
// sceGsSyncPath), a buffer from the raster's extension, the store-image transfer (sceGsSetDefStoreImage /
// sceDmaGetChan / sceGsExecStoreImage) and SyncDCache; textures lock their memory image (sub_4DD480 /
// sub_4DD700 / sub_4DB200), level by level; unsupported combinations are errors. Hardware is only touched in
// the callees (sceGs* / sceDma*).
// 0x004DE0A0 sub_4DE0A0 -- 3132 bytes; frame 0xD0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4DE0A0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004de0a0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    s7 = a0;
    sq(s5, sp, 0x50);
    a0 = 1;
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    v1 = s3 & 0xFF00;
    sq(s0, sp, 0x0);
    v1 = sra(v1, 8);
    lbu(v0, a1, 32);
    s2 = v1 & 0xFF;
    v1 = v0 & 0x7;
    s0 = a1;
    if (v1 == a0) {
        // 0x004de338
        charge(ctx, 9);
        sw(a0, sp, 0x98);
        v0 = lui(0x8000);
        a0 = v0 | 0xE;
        jal(ctx, 0x4DE340u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x9C);
        a0 = addiu(sp, 0x98);
        jal(ctx, 0x4DE34Cu, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x004de0f0
        charge(ctx, 3);
        v0 = 5;
        if (v1 == v0) {
            // 0x004de214
            charge(ctx, 5);
            lbu(v0, s0, 33);
            lw(v1, gp, -16968);  // 0x7CEAA8
            v0 = v0 & 0x80;
            s1 = addu(s0, v1);
            if (v0 != 0) {
                // 0x004de954
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004de228
                charge(ctx, 3);
                v0 = s3 & 0xF9;
                if (v0 != 0) {
                    // 0x004de95c
                    charge(ctx, 9);
                    sw(a0, sp, 0xB0);
                    v0 = lui(0x8000);
                    a0 = v0 | 0xE;
                    jal(ctx, 0x4DE964u, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0xB4);
                    a0 = addiu(sp, 0xB0);
                    jal(ctx, 0x4DE970u, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                } else {
                    // 0x004de234
                    charge(ctx, 3);
                    lw(v0, s1, 88);
                    if (v0 == 0) {
                        // 0x004de980
                        charge(ctx, 9);
                        sw(a0, sp, 0xA8);
                        v0 = lui(0x8000);
                        a0 = v0 | 0xE;
                        jal(ctx, 0x4DE988u, gen::fn_sub_4C1D10_004c1d10);
                        sw(v0, sp, 0xAC);
                        a0 = addiu(sp, 0xA8);
                        jal(ctx, 0x4DE994u, gen::fn_sub_4C1C50_004c1c50);
                        v0 = 0;
                    } else {
                        // 0x004de240
                        charge(ctx, 3);
                        v0 = s2 & 0xFF;
                        if (v0 != 0) {
                            // 0x004de9a4
                            charge(ctx, 9);
                            sw(a0, sp, 0xA0);
                            v0 = lui(0x8000);
                            a0 = v0 | 0xF;
                            jal(ctx, 0x4DE9ACu, gen::fn_sub_4C1D10_004c1d10);
                            sw(v0, sp, 0xA4);
                            a0 = addiu(sp, 0xA0);
                            jal(ctx, 0x4DE9B8u, gen::fn_sub_4C1C50_004c1c50);
                            v0 = 0;
                        } else {
                            // 0x004de24c
                            charge(ctx, 3);
                            lw(v0, s0, 4);
                            if (v0 != 0) {
                                // 0x004de258
                                charge(ctx, 3);
                                v0 = v0 & 0xF;
                                if (v0 != 0) {
                                    goto L_004de9c8;
                                }
                                // 0x004de264
                                charge(ctx, 22);
                                jal(ctx, 0x4DE264u, gen::fn__rwDMAForceBufferSwap_004d4df0);
                                jal(ctx, 0x4DE26Cu, gen::fn__rwDMAForceBufferSwap_004d4df0);
                                a0 = 0;
                                a1 = 0;
                                jal(ctx, 0x4DE278u, gen::fn_sceGsSyncPath_004f99d0);
                                lw(a0, s0, 4);
                                lw(v1, s0, 12);
                                lw(v0, s0, 20);
                                lw(s5, s0, 16);
                                lh(s3, s0, 30);
                                s2 = a0;
                                mult(v1, v1, v0);
                                v0 = 0xF0000;
                                v1 = sra(v1, 3);
                                v0 = v0 | 0xFFF0;
                                div(v0, v1);
                                mflo(s4);
                                at = slt(s4, s5);
                                if (at == 0) {
                                    // 0x004de2f0
                                    charge(ctx, 1);
                                    s4 = s5;
                                L_004de2f4:
                                    charge(ctx, 5);
                                    mult(v0, s5, v1);
                                    a1 = addu(a0, v0);
                                    jal(ctx, 0x4DE2F8u, gen::fn_SyncDCache_00503a58);
                                    if (s5 != 0) {
                                        // 0x004de9e0
                                        charge(ctx, 2);
                                        s6 = 0x960000;
                                        s6 = addiu(s6, 21296);  // &0x965330
                                        for (;;) {
                                            // 0x004de9e8
                                            charge(ctx, 30);
                                            lw(a3, s1, 8);
                                            v0 = s3 & 0x7FF;
                                            t1 = dsll32(v0, 16);
                                            t3 = dsll32(s4, 16);
                                            lh(v0, s0, 28);
                                            a0 = 0x960000;
                                            lh(t2, s0, 12);
                                            t1 = dsra32(t1, 16);
                                            t3 = dsra32(t3, 16);
                                            a0 = addiu(a0, 21184);  // &0x9652C0
                                            v1 = srl(a3, 14);
                                            a1 = a3 & 0x3FFF;
                                            v1 = v1 & 0x3F;
                                            a1 = dsll32(a1, 16);
                                            a2 = dsll32(v1, 16);
                                            v0 = v0 & 0x7FF;
                                            v1 = srl(a3, 20);
                                            t0 = dsll32(v0, 16);
                                            v1 = v1 & 0x3F;
                                            a1 = dsra32(a1, 16);
                                            a3 = dsll32(v1, 16);
                                            a2 = dsra32(a2, 16);
                                            a3 = dsra32(a3, 16);
                                            t0 = dsra32(t0, 16);
                                            jal(ctx, 0x4DEA44u, gen::fn_sceGsSetDefStoreImage_004f9ce8);
                                            a0 = 0x960000;
                                            a1 = s6;
                                            a0 = addiu(a0, 21184);  // &0x9652C0
                                            jal(ctx, 0x4DEA54u, gen::fn_SyncDCache_00503a58);
                                            for (;;) {
                                                // 0x004dea60
                                                charge(ctx, 7);
                                                a0 = 1;
                                                jal(ctx, 0x4DEA60u, gen::fn_sceDmaGetChan_004fa8f0);
                                                lw(v0, v0, 0);
                                                v0 = v0 & 0x100;
                                                if (v0 == 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                            // 0x004dea7c
                                            charge(ctx, 1);
                                            for (;;) {
                                                // 0x004dea80
                                                charge(ctx, 7);
                                                a0 = 2;
                                                jal(ctx, 0x4DEA80u, gen::fn_sceDmaGetChan_004fa8f0);
                                                lw(v0, v0, 0);
                                                v0 = v0 & 0x100;
                                                if (v0 == 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                            // 0x004dea9c
                                            charge(ctx, 10);
                                            a0 = 0;
                                            a1 = 0;
                                            jal(ctx, 0x4DEAA0u, gen::fn_sceGsSyncPath_004f99d0);
                                            a0 = 0x960000;
                                            a1 = s2;
                                            a0 = addiu(a0, 21184);  // &0x9652C0
                                            jal(ctx, 0x4DEAB0u, gen::fn_sceGsExecStoreImage_004f9e28);
                                            v1 = si(-1);
                                            if (v0 != v1) {
                                                // 0x004deac4
                                                charge(ctx, 1);
                                                goto L_004deac8;
                                            }
                                            // 0x004deb08
                                            charge(ctx, 7);
                                            a0 = 0x960000;
                                            a1 = s2;
                                            a0 = addiu(a0, 21184);  // &0x9652C0
                                            jal(ctx, 0x4DEB10u, gen::fn_sceGsExecStoreImage_004f9e28);
                                            v1 = si(-1);
                                            if (v0 == v1) {
                                                break;
                                            }
                                            backedge(ctx);
                                        L_004deac8:
                                            charge(ctx, 10);
                                            lw(v1, s0, 12);
                                            lw(v0, s0, 20);
                                            s5 = subu(s5, s4);
                                            s3 = addu(s3, s4);
                                            mult(v0, v1, v0);
                                            v0 = sra(v0, 3);
                                            mult(v0, s4, v0);
                                            at = slt(s5, s4);
                                            s2 = addu(s2, v0);
                                            if (at != 0) {
                                                // 0x004deaf0
                                                charge(ctx, 2);
                                                s4 = s5;
                                            }
                                            // 0x004deaf8
                                            charge(ctx, 2);
                                            if (s5 == 0) {
                                                goto L_004deb00_90;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x004deb24
                                        charge(ctx, 2);
                                        v0 = 0;
                                    } else {
                                        // 0x004de308
                                        charge(ctx, 1);
                                        lw(v1, s0, 12);
                                    L_004de30c:
                                        charge(ctx, 11);
                                        lw(v0, s0, 20);
                                        mult(v1, v1, v0);
                                        v1 = sra(v1, 3);
                                        v0 = 1;
                                        sw(v1, s0, 24);
                                        lw(v1, s0, 4);
                                        sw(v1, s7, 0);
                                        lbu(v1, s0, 34);
                                        v1 = v1 | 0x2;
                                        sb(v1, s0, 34);
                                    }
                                } else {
                                    // 0x004de2bc
                                    charge(ctx, 4);
                                    mult(v0, s4, v1);
                                    v0 = v0 & 0xF;
                                    if (v0 != 0) {
                                        for (;;) {
                                            // 0x004de2cc
                                            charge(ctx, 7);
                                            s4 = addiu(s4, -1);
                                            mult(v0, s4, v1);
                                            v0 = v0 & 0xF;
                                            if (v0 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x004de2e8
                                        charge(ctx, 2);
                                    }
                                    // 0x004de9d0
                                    charge(ctx, 2);
                                    if (s4 != 0) {
                                        backedge(ctx);
                                        goto L_004de2f4;
                                    }
                                    // 0x004de9d8
                                    charge(ctx, 2);
                                    v0 = 0;
                                }
                                // 0x004decb0 (the shared epilogue, written out on this path)
                                charge(ctx, 11);
                                ld(ra, sp, 0x80);
                                lq(s7, sp, 0x70);
                                lq(s6, sp, 0x60);
                                lq(s5, sp, 0x50);
                                lq(s4, sp, 0x40);
                                lq(s3, sp, 0x30);
                                lq(s2, sp, 0x20);
                                lq(s1, sp, 0x10);
                                lq(s0, sp, 0x0);
                                sp = addiu(sp, 0xD0);
                                return;
                            }
                        L_004de9c8:
                            charge(ctx, 2);
                            v0 = 0;
                        }
                    }
                }
            }
        } else {
            // 0x004de0fc
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x004de110
                charge(ctx, 3);
                v0 = s3 & 0xF9;
                if (v0 != 0) {
                    // 0x004de79c
                    charge(ctx, 9);
                    sw(a0, sp, 0xC0);
                    v0 = lui(0x8000);
                    a0 = v0 | 0xE;
                    jal(ctx, 0x4DE7A4u, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0xC4);
                    a0 = addiu(sp, 0xC0);
                    jal(ctx, 0x4DE7B0u, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                } else {
                    // 0x004de11c
                    charge(ctx, 3);
                    v0 = s2 & 0xFF;
                    if (v0 != 0) {
                        // 0x004de7c0
                        charge(ctx, 9);
                        sw(a0, sp, 0xB8);
                        v0 = lui(0x8000);
                        a0 = v0 | 0xF;
                        jal(ctx, 0x4DE7C8u, gen::fn_sub_4C1D10_004c1d10);
                        sw(v0, sp, 0xBC);
                        a0 = addiu(sp, 0xB8);
                        jal(ctx, 0x4DE7D4u, gen::fn_sub_4C1C50_004c1c50);
                        v0 = 0;
                    } else {
                        // 0x004de128
                        charge(ctx, 3);
                        lw(v0, s0, 4);
                        if (v0 != 0) {
                            // 0x004de134
                            charge(ctx, 3);
                            v0 = v0 & 0xF;
                            if (v0 != 0) {
                                goto L_004de7e4;
                            }
                            // 0x004de140
                            charge(ctx, 22);
                            jal(ctx, 0x4DE140u, gen::fn__rwDMAForceBufferSwap_004d4df0);
                            jal(ctx, 0x4DE148u, gen::fn__rwDMAForceBufferSwap_004d4df0);
                            a0 = 0;
                            a1 = 0;
                            jal(ctx, 0x4DE154u, gen::fn_sceGsSyncPath_004f99d0);
                            lw(a0, s0, 4);
                            lw(v1, s0, 12);
                            lw(v0, s0, 20);
                            lw(s4, s0, 16);
                            lh(s2, s0, 30);
                            s1 = a0;
                            mult(v1, v1, v0);
                            v0 = 0xF0000;
                            v1 = sra(v1, 3);
                            v0 = v0 | 0xFFF0;
                            div(v0, v1);
                            mflo(s3);
                            at = slt(s3, s4);
                            if (at == 0) {
                                // 0x004de1cc
                                charge(ctx, 1);
                                s3 = s4;
                            L_004de1d0:
                                charge(ctx, 5);
                                mult(v0, s4, v1);
                                a1 = addu(a0, v0);
                                jal(ctx, 0x4DE1D4u, gen::fn_SyncDCache_00503a58);
                                if (s4 != 0) {
                                    // 0x004de7fc
                                    charge(ctx, 2);
                                    s5 = 0x960000;
                                    s5 = addiu(s5, 21296);  // &0x965330
                                    for (;;) {
                                        // 0x004de804
                                        charge(ctx, 33);
                                        ld(a3, gp, -17080);  // 0x7CEA38
                                        v0 = s2 & 0x7FF;
                                        a2 = 0x3F0000;
                                        t1 = dsll32(v0, 16);
                                        a1 = 0x3F000000;
                                        t3 = dsll32(s3, 16);
                                        a0 = 0x960000;
                                        lh(v1, s0, 28);
                                        lh(t2, s0, 12);
                                        t1 = dsra32(t1, 16);
                                        t3 = dsra32(t3, 16);
                                        a0 = addiu(a0, 21184);  // &0x9652C0
                                        v0 = a3 & a1;
                                        a2 = a3 & a2;
                                        a3 = a3 & 0x1FF;
                                        a1 = dsra(a2, 16);
                                        a2 = dsll32(a1, 16);
                                        a3 = dsll(a3, 5);
                                        a1 = dsll32(a3, 16);
                                        v0 = dsra(v0, 24);
                                        a3 = dsll32(v0, 16);
                                        a2 = dsra32(a2, 16);
                                        v0 = v1 & 0x7FF;
                                        a1 = dsra32(a1, 16);
                                        t0 = dsll32(v0, 16);
                                        a3 = dsra32(a3, 16);
                                        t0 = dsra32(t0, 16);
                                        jal(ctx, 0x4DE86Cu, gen::fn_sceGsSetDefStoreImage_004f9ce8);
                                        a0 = 0x960000;
                                        a1 = s5;
                                        a0 = addiu(a0, 21184);  // &0x9652C0
                                        jal(ctx, 0x4DE87Cu, gen::fn_SyncDCache_00503a58);
                                        for (;;) {
                                            // 0x004de888
                                            charge(ctx, 7);
                                            a0 = 1;
                                            jal(ctx, 0x4DE888u, gen::fn_sceDmaGetChan_004fa8f0);
                                            lw(v0, v0, 0);
                                            v0 = v0 & 0x100;
                                            if (v0 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x004de8a4
                                        charge(ctx, 1);
                                        for (;;) {
                                            // 0x004de8a8
                                            charge(ctx, 7);
                                            a0 = 2;
                                            jal(ctx, 0x4DE8A8u, gen::fn_sceDmaGetChan_004fa8f0);
                                            lw(v0, v0, 0);
                                            v0 = v0 & 0x100;
                                            if (v0 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x004de8c4
                                        charge(ctx, 10);
                                        a0 = 0;
                                        a1 = 0;
                                        jal(ctx, 0x4DE8C8u, gen::fn_sceGsSyncPath_004f99d0);
                                        a0 = 0x960000;
                                        a1 = s1;
                                        a0 = addiu(a0, 21184);  // &0x9652C0
                                        jal(ctx, 0x4DE8D8u, gen::fn_sceGsExecStoreImage_004f9e28);
                                        v1 = si(-1);
                                        if (v0 != v1) {
                                            // 0x004de8ec
                                            charge(ctx, 1);
                                            goto L_004de8f0;
                                        }
                                        // 0x004de930
                                        charge(ctx, 7);
                                        a0 = 0x960000;
                                        a1 = s1;
                                        a0 = addiu(a0, 21184);  // &0x9652C0
                                        jal(ctx, 0x4DE938u, gen::fn_sceGsExecStoreImage_004f9e28);
                                        v1 = si(-1);
                                        if (v0 == v1) {
                                            break;
                                        }
                                        backedge(ctx);
                                    L_004de8f0:
                                        charge(ctx, 10);
                                        lw(v1, s0, 12);
                                        lw(v0, s0, 20);
                                        s4 = subu(s4, s3);
                                        s2 = addu(s2, s3);
                                        mult(v0, v1, v0);
                                        v0 = sra(v0, 3);
                                        mult(v0, s3, v0);
                                        at = slt(s4, s3);
                                        s1 = addu(s1, v0);
                                        if (at != 0) {
                                            // 0x004de918
                                            charge(ctx, 2);
                                            s3 = s4;
                                        }
                                        // 0x004de920
                                        charge(ctx, 2);
                                        if (s4 == 0) {
                                            goto L_004de928_70;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004de94c
                                    charge(ctx, 2);
                                    v0 = 0;
                                } else {
                                    // 0x004de1e4
                                    charge(ctx, 1);
                                    lw(v1, s0, 12);
                                L_004de1e8:
                                    charge(ctx, 11);
                                    lw(v0, s0, 20);
                                    mult(v1, v1, v0);
                                    v1 = sra(v1, 3);
                                    v0 = 1;
                                    sw(v1, s0, 24);
                                    lw(v1, s0, 4);
                                    sw(v1, s7, 0);
                                    lbu(v1, s0, 34);
                                    v1 = v1 | 0x2;
                                    sb(v1, s0, 34);
                                }
                            } else {
                                // 0x004de198
                                charge(ctx, 4);
                                mult(v0, s3, v1);
                                v0 = v0 & 0xF;
                                if (v0 != 0) {
                                    for (;;) {
                                        // 0x004de1a8
                                        charge(ctx, 7);
                                        s3 = addiu(s3, -1);
                                        mult(v0, s3, v1);
                                        v0 = v0 & 0xF;
                                        if (v0 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004de1c4
                                    charge(ctx, 2);
                                }
                                // 0x004de7ec
                                charge(ctx, 2);
                                if (s3 != 0) {
                                    backedge(ctx);
                                    goto L_004de1d0;
                                }
                                // 0x004de7f4
                                charge(ctx, 2);
                                v0 = 0;
                            }
                            // 0x004decb0 (the shared epilogue, written out on this path)
                            charge(ctx, 11);
                            ld(ra, sp, 0x80);
                            lq(s7, sp, 0x70);
                            lq(s6, sp, 0x60);
                            lq(s5, sp, 0x50);
                            lq(s4, sp, 0x40);
                            lq(s3, sp, 0x30);
                            lq(s2, sp, 0x20);
                            lq(s1, sp, 0x10);
                            lq(s0, sp, 0x0);
                            sp = addiu(sp, 0xD0);
                            return;
                        }
                    L_004de7e4:
                        charge(ctx, 2);
                        v0 = 0;
                    }
                }
            } else {
                // 0x004de108
                charge(ctx, 2);
                lw(v0, gp, -16968);  // 0x7CEAA8
                // 0x004de360
                charge(ctx, 7);
                s4 = s2 & 0xFF;
                s5 = addu(s0, v0);
                lbu(v0, s5, 22);
                v0 = sra(v0, 2);
                at = slt(v0, s4);
                if (at != 0) {
                    // 0x004deb2c
                    charge(ctx, 9);
                    sw(a0, sp, 0x90);
                    v0 = lui(0x8000);
                    a0 = v0 | 0xF;
                    jal(ctx, 0x4DEB34u, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0x94);
                    a0 = addiu(sp, 0x90);
                    jal(ctx, 0x4DEB40u, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                } else {
                    // 0x004de37c
                    charge(ctx, 3);
                    s1 = s3 & 0x1;
                    if (s1 != 0) {
                        // 0x004deb50
                        charge(ctx, 4);
                        a0 = s0;
                        jal(ctx, 0x4DEB50u, gen::fn_sub_4F1540_004f1540);
                        lbu(a1, s5, 54);
                        backedge(ctx);
                    } else {
                        // 0x004de388
                        charge(ctx, 1);
                        lbu(a1, s5, 54);
                    }
                    // 0x004de38c
                    charge(ctx, 3);
                    v0 = a1 & 0x1;
                    if (v0 != 0) {
                        // 0x004deb60
                        charge(ctx, 14);
                        lw(v0, s5, 8);
                        a2 = addiu(sp, 0xCC);
                        a3 = addiu(sp, 0xC8);
                        v0 = srl(v0, 20);
                        a0 = v0 & 0x3F;
                        jal(ctx, 0x4DEB70u, gen::fn_sub_4DB200_004db200);
                        lw(v1, s0, 0);
                        at = slt(0, s4);
                        lw(a2, s0, 12);
                        lw(a1, s0, 16);
                        lw(a0, v1, 12);
                        lw(v1, v1, 16);
                        v0 = 0;
                        if (at != 0) {
                            // 0x004deb98
                            charge(ctx, 1);
                            t2 = si(-16);
                            for (;;) {
                                // 0x004deb9c
                                charge(ctx, 4);
                                lw(t1, sp, 0xCC);
                                at = slt(a0, t1);
                                if (at == 0) {
                                    // 0x004debb4
                                    charge(ctx, 1);
                                    t0 = a0;
                                } else {
                                    // 0x004debac
                                    charge(ctx, 2);
                                    t0 = t1;
                                }
                                // 0x004debb8
                                charge(ctx, 23);
                                lw(a3, sp, 0xC8);
                                at = slt(v1, a3);
                                if (at == 0) t1 = v1;
                                mult(t0, t0, t1);
                                lw(a3, s0, 20);
                                mult(a3, a3, t0);
                                v0 = addiu(v0, 1);
                                v0 = v0 & 0xFF;
                                a2 = sra(a2, 1);
                                a0 = sra(a0, 1);
                                a1 = sra(a1, 1);
                                v1 = sra(v1, 1);
                                lw(t0, s0, 4);
                                a3 = sra(a3, 3);
                                t1 = addiu(a3, 15);
                                t1 = t1 & t2;
                                a3 = slt(v0, s4);
                                t0 = addu(t0, t1);
                                sw(t0, s0, 4);
                                lw(t0, s0, 4);
                                t0 = addiu(t0, 80);
                                sw(t0, s0, 4);
                                if (a3 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                        }
                        // 0x004dec14
                        charge(ctx, 10);
                        lw(v1, sp, 0xCC);
                        at = slt(a0, v1);
                        if (at == 0) v1 = a0;
                        lw(v0, s0, 20);
                        mult(v0, v0, v1);
                        v0 = sra(v0, 3);
                        sw(v0, s0, 24);
                        sw(a2, s0, 12);
                        sw(a1, s0, 16);
                        backedge(ctx);
                    } else {
                        // 0x004de398
                        charge(ctx, 6);
                        lw(v0, s0, 0);
                        at = slt(0, s4);
                        lw(a1, v0, 12);
                        lw(a0, v0, 16);
                        a2 = 0;
                        if (at != 0) {
                            // 0x004de3b0
                            charge(ctx, 3);
                            at = sltiu(s4, 9);
                            v1 = addiu(s4, -8);
                            if (at == 0) {
                                // 0x004de3bc
                                charge(ctx, 1);
                                v0 = si(-16);
                                for (;;) {
                                    // 0x004de3c0
                                    charge(ctx, 172);
                                    lw(a3, s0, 20);
                                    mult(a3, a3, a1);
                                    a3 = sra(a3, 3);
                                    sw(a3, s0, 24);
                                    lw(a3, s0, 4);
                                    a3 = addiu(a3, 15);
                                    a3 = a3 & v0;
                                    sw(a3, s0, 4);
                                    lw(a3, s0, 24);
                                    mult1(t1, a3, a0);
                                    t0 = sra(a1, 1);
                                    lw(a3, s0, 4);
                                    a3 = addu(a3, t1);
                                    sw(a3, s0, 4);
                                    lw(a3, s0, 12);
                                    a3 = sra(a3, 1);
                                    sw(a3, s0, 12);
                                    lw(a3, s0, 16);
                                    a3 = sra(a3, 1);
                                    sw(a3, s0, 16);
                                    lw(a3, s0, 20);
                                    mult(a3, a3, t0);
                                    a3 = sra(a3, 3);
                                    t0 = sra(a0, 1);
                                    sw(a3, s0, 24);
                                    lw(a3, s0, 4);
                                    a3 = addiu(a3, 15);
                                    a3 = a3 & v0;
                                    sw(a3, s0, 4);
                                    lw(a3, s0, 24);
                                    mult1(t1, a3, t0);
                                    lw(a3, s0, 4);
                                    t0 = sra(a1, 2);
                                    a3 = addu(a3, t1);
                                    sw(a3, s0, 4);
                                    lw(a3, s0, 12);
                                    a3 = sra(a3, 1);
                                    sw(a3, s0, 12);
                                    lw(a3, s0, 16);
                                    a3 = sra(a3, 1);
                                    sw(a3, s0, 16);
                                    lw(a3, s0, 20);
                                    mult(a3, a3, t0);
                                    a3 = sra(a3, 3);
                                    t0 = sra(a0, 2);
                                    sw(a3, s0, 24);
                                    lw(a3, s0, 4);
                                    a3 = addiu(a3, 15);
                                    a3 = a3 & v0;
                                    sw(a3, s0, 4);
                                    lw(a3, s0, 24);
                                    mult1(t1, a3, t0);
                                    lw(a3, s0, 4);
                                    t0 = sra(a1, 3);
                                    a3 = addu(a3, t1);
                                    sw(a3, s0, 4);
                                    lw(a3, s0, 12);
                                    a3 = sra(a3, 1);
                                    sw(a3, s0, 12);
                                    lw(a3, s0, 16);
                                    a3 = sra(a3, 1);
                                    sw(a3, s0, 16);
                                    lw(a3, s0, 20);
                                    mult(a3, a3, t0);
                                    a3 = sra(a3, 3);
                                    t0 = sra(a0, 3);
                                    sw(a3, s0, 24);
                                    lw(a3, s0, 4);
                                    a3 = addiu(a3, 15);
                                    a3 = a3 & v0;
                                    sw(a3, s0, 4);
                                    lw(a3, s0, 24);
                                    mult1(t1, a3, t0);
                                    lw(a3, s0, 4);
                                    t0 = sra(a1, 4);
                                    a3 = addu(a3, t1);
                                    sw(a3, s0, 4);
                                    lw(a3, s0, 12);
                                    a3 = sra(a3, 1);
                                    sw(a3, s0, 12);
                                    lw(a3, s0, 16);
                                    a3 = sra(a3, 1);
                                    sw(a3, s0, 16);
                                    lw(a3, s0, 20);
                                    mult(a3, a3, t0);
                                    a3 = sra(a3, 3);
                                    t0 = sra(a0, 4);
                                    sw(a3, s0, 24);
                                    lw(a3, s0, 4);
                                    a3 = addiu(a3, 15);
                                    a3 = a3 & v0;
                                    sw(a3, s0, 4);
                                    lw(a3, s0, 24);
                                    mult1(t1, a3, t0);
                                    lw(a3, s0, 4);
                                    t0 = sra(a1, 5);
                                    a3 = addu(a3, t1);
                                    sw(a3, s0, 4);
                                    lw(a3, s0, 12);
                                    a3 = sra(a3, 1);
                                    sw(a3, s0, 12);
                                    lw(a3, s0, 16);
                                    a3 = sra(a3, 1);
                                    sw(a3, s0, 16);
                                    lw(a3, s0, 20);
                                    mult(a3, a3, t0);
                                    a3 = sra(a3, 3);
                                    t0 = sra(a0, 5);
                                    sw(a3, s0, 24);
                                    lw(a3, s0, 4);
                                    a3 = addiu(a3, 15);
                                    a3 = a3 & v0;
                                    sw(a3, s0, 4);
                                    lw(a3, s0, 24);
                                    mult1(t1, a3, t0);
                                    lw(a3, s0, 4);
                                    t0 = sra(a1, 6);
                                    a3 = addu(a3, t1);
                                    sw(a3, s0, 4);
                                    lw(a3, s0, 12);
                                    a3 = sra(a3, 1);
                                    sw(a3, s0, 12);
                                    lw(a3, s0, 16);
                                    a3 = sra(a3, 1);
                                    sw(a3, s0, 16);
                                    lw(a3, s0, 20);
                                    mult(a3, a3, t0);
                                    a3 = sra(a3, 3);
                                    t0 = sra(a0, 6);
                                    sw(a3, s0, 24);
                                    lw(a3, s0, 4);
                                    a3 = addiu(a3, 15);
                                    a3 = a3 & v0;
                                    sw(a3, s0, 4);
                                    lw(a3, s0, 24);
                                    mult1(t1, a3, t0);
                                    lw(a3, s0, 4);
                                    t0 = sra(a1, 7);
                                    a3 = addu(a3, t1);
                                    sw(a3, s0, 4);
                                    lw(a3, s0, 12);
                                    a3 = sra(a3, 1);
                                    sw(a3, s0, 12);
                                    lw(a3, s0, 16);
                                    a3 = sra(a3, 1);
                                    sw(a3, s0, 16);
                                    lw(a3, s0, 20);
                                    mult(a3, a3, t0);
                                    a3 = sra(a3, 3);
                                    t0 = sra(a0, 7);
                                    sw(a3, s0, 24);
                                    lw(a3, s0, 4);
                                    a3 = addiu(a3, 15);
                                    a3 = a3 & v0;
                                    sw(a3, s0, 4);
                                    lw(a3, s0, 24);
                                    mult1(t1, a3, t0);
                                    a2 = addiu(a2, 8);
                                    lw(t0, s0, 4);
                                    a2 = a2 & 0xFF;
                                    a3 = slt(a2, v1);
                                    a1 = sra(a1, 8);
                                    a0 = sra(a0, 8);
                                    t0 = addu(t0, t1);
                                    sw(t0, s0, 4);
                                    lw(t0, s0, 12);
                                    t0 = sra(t0, 1);
                                    sw(t0, s0, 12);
                                    lw(t0, s0, 16);
                                    t0 = sra(t0, 1);
                                    sw(t0, s0, 16);
                                    if (a3 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                            }
                            // 0x004de670
                            charge(ctx, 4);
                            v0 = a2 & 0xFF;
                            at = slt(v0, s4);
                            if (at != 0) {
                                // 0x004de680
                                charge(ctx, 1);
                                t0 = si(-16);
                                for (;;) {
                                    // 0x004de684
                                    charge(ctx, 25);
                                    lw(v0, s0, 20);
                                    mult(v0, v0, a1);
                                    v0 = sra(v0, 3);
                                    sw(v0, s0, 24);
                                    lw(v0, s0, 4);
                                    v0 = addiu(v0, 15);
                                    v0 = v0 & t0;
                                    sw(v0, s0, 4);
                                    lw(v0, s0, 24);
                                    mult1(a3, v0, a0);
                                    lw(v1, s0, 4);
                                    v0 = addiu(a2, 1);
                                    a1 = sra(a1, 1);
                                    a2 = v0 & 0xFF;
                                    a0 = sra(a0, 1);
                                    v0 = slt(a2, s4);
                                    v1 = addu(v1, a3);
                                    sw(v1, s0, 4);
                                    lw(v1, s0, 12);
                                    v1 = sra(v1, 1);
                                    sw(v1, s0, 12);
                                    lw(v1, s0, 16);
                                    v1 = sra(v1, 1);
                                    sw(v1, s0, 16);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                            }
                        }
                        // 0x004de6e8
                        charge(ctx, 9);
                        lw(v1, s0, 4);
                        v0 = si(-16);
                        v1 = addiu(v1, 15);
                        v0 = v1 & v0;
                        sw(v0, s0, 4);
                        lw(v0, s0, 20);
                        mult(v0, v0, a1);
                        v0 = sra(v0, 3);
                        sw(v0, s0, 24);
                    }
                    // 0x004de70c
                    charge(ctx, 3);
                    v0 = s3 & 0x2;
                    if (v0 != 0) {
                        // 0x004de718
                        charge(ctx, 4);
                        lbu(a1, s5, 54);
                        v1 = a1 & 0x2;
                        if (v1 != 0) {
                            // 0x004dec3c
                            charge(ctx, 6);
                            lw(a0, s5, 8);
                            v1 = 19;
                            a0 = srl(a0, 20);
                            a0 = a0 & 0x3F;
                            if (a0 != v1) {
                                backedge(ctx);
                                goto L_004de728;
                            }
                            // 0x004dec54
                            charge(ctx, 4);
                            lw(v1, s0, 24);
                            v1 = slti(v1, 16);
                            if (v1 != 0) {
                                backedge(ctx);
                                goto L_004de728;
                            }
                            // 0x004dec64
                            charge(ctx, 3);
                            v1 = s3 & 0x8;
                            if (v1 != 0) {
                                backedge(ctx);
                                goto L_004de728;
                            }
                            // 0x004dec70
                            charge(ctx, 4);
                            a0 = s0;
                            jal(ctx, 0x4DEC70u, gen::fn_sub_4DD480_004dd480);
                            lw(v1, s0, 4);
                            backedge(ctx);
                            goto L_004de774;
                        }
                    L_004de728:
                        charge(ctx, 3);
                        v1 = a1 & 0x4;
                        if (v1 != 0) {
                            // 0x004de734
                            charge(ctx, 6);
                            lw(a0, s5, 8);
                            v1 = 20;
                            a0 = srl(a0, 20);
                            a0 = a0 & 0x3F;
                            if (a0 == v1) {
                                // 0x004de74c
                                charge(ctx, 4);
                                lw(v1, s0, 24);
                                v1 = slti(v1, 16);
                                if (v1 == 0) {
                                    // 0x004de75c
                                    charge(ctx, 3);
                                    v1 = s3 & 0x8;
                                    if (v1 == 0) {
                                        // 0x004de768
                                        charge(ctx, 2);
                                        a0 = s0;
                                        jal(ctx, 0x4DE768u, gen::fn_sub_4DD700_004dd700);
                                    }
                                }
                            }
                        }
                    }
                    // 0x004de770
                    charge(ctx, 1);
                    lw(v1, s0, 4);
                L_004de774:
                    charge(ctx, 3);
                    sw(v1, s7, 0);
                    sb(s2, s5, 53);
                    if (v0 != 0) {
                        // 0x004dec80
                        charge(ctx, 4);
                        lbu(v0, s0, 34);
                        v0 = v0 | 0x2;
                        sb(v0, s0, 34);
                        backedge(ctx);
                    }
                    // 0x004de780
                    charge(ctx, 2);
                    if (s1 != 0) {
                        // 0x004dec90
                        charge(ctx, 4);
                        lbu(v0, s0, 34);
                        v0 = v0 | 0x4;
                        sb(v0, s0, 34);
                        backedge(ctx);
                    }
                    // 0x004de788
                    charge(ctx, 3);
                    v0 = s3 & 0x8;
                    if (v0 != 0) {
                        // 0x004deca0
                        charge(ctx, 4);
                        lbu(v0, s0, 34);
                        v0 = v0 | 0x20;
                        sb(v0, s0, 34);
                        backedge(ctx);
                    }
                    // 0x004de794
                    charge(ctx, 2);
                    v0 = 1;
                }
            }
        }
    }
    // 0x004decb0 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
    return;
L_004de928_70:
    charge(ctx, 2);
    lw(v1, s0, 12);
    backedge(ctx);
    goto L_004de1e8;
L_004deb00_90:
    charge(ctx, 2);
    lw(v1, s0, 12);
    backedge(ctx);
    goto L_004de30c;
}

// sub_4E53E0 [skyRasterRender] -- draws a raster into the current context at a point (standard function 17)
// ($a0 = the destination context, $a1 = the source raster, $a2 = a rectangle / point record; standard function 17 via
// 0x9600FC) The source raster is made resident in the GS texture cache (RpSkyTexCacheAccessRaster); a raster whose
// upload description is out of date is set up again (sub_4E4E90); the sprite is built in the DMA packet layer between
// DIntr and EIntr (sub_4E4180 / sub_4E4560 / sub_4E46C0, _rwDMAAddPURef keeps the raster's packets referenced while the
// DMA runs); a sub-raster draws through its parent (sub_4CDE00 / sub_4CE200). The driver's raster extension lives at
// raster + gp 0x7CEAA8; the PS2 driver globals at 0x7CEAE0 / 0x7CEAE8 / 0x7CEAF0 hold the current context, its
// frame-buffer description and the packet state.
// 0x004E53E0 sub_4E53E0 -- 6520 bytes; frame 0xD0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq)
void sub_4E53E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004e53e0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    lw(v0, gp, -16968);  // 0x7CEAA8
    s7 = addu(a0, v0);
    lbu(v0, s7, 54);
    v0 = v0 & 0x6;
    s4 = a0;
    if (v0 == 0) {
        // 0x004e542c
        charge(ctx, 30);
        fp = addiu(sp, 0xB4);
        sw(zero, sp, 0xB0);
        sw(zero, fp, 0x0);
        v0 = addiu(sp, 0xB8);
        lw(v1, s4, 12);
        s6 = addiu(sp, 0xBC);
        lw(a2, gp, -16896);  // 0x7CEAF0
        s0 = addiu(sp, 0xC8);
        s2 = addiu(sp, 0xCC);
        a0 = addiu(sp, 0xB0);
        sw(v1, v0, 0);
        lw(v0, s4, 16);
        sw(v0, s6, 0);
        lh(v1, a2, 28);
        lw(v0, a1, 0);
        v0 = addu(v0, v1);
        sw(v0, sp, 0xC0);
        lw(v0, a1, 4);
        lh(v1, a2, 30);
        a1 = addiu(sp, 0xC0);
        v1 = addu(v0, v1);
        v0 = addiu(sp, 0xC4);
        sw(v1, v0, 0);
        lw(v0, s4, 12);
        sw(v0, s0, 0);
        lw(v0, s4, 16);
        link(ctx, 0x4E5494u);  // $ra first: the delay slot below depends on it
        sw(v0, s2, 0);
        call(ctx, gen::fn_sub_4E4A90_004e4a90);
        if (v0 == 0) {
            // 0x004e69c8
            charge(ctx, 2);
            v0 = 1;
        } else {
            // 0x004e54a4
            charge(ctx, 5);
            lbu(v0, s4, 32);
            v0 = addiu(v0, -1);
            at = sltiu(v0, 2);
            if (at != 0) {
                // 0x004e69d0
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004e54b8
                charge(ctx, 5);
                lw(v0, gp, -16896);  // 0x7CEAF0
                v1 = 1;
                lbu(a0, v0, 32);
                if (a0 == v1) {
                    // 0x004e69bc
                    charge(ctx, 1);
                    v0 = 0;
                L_004e69c0:
                    charge(ctx, 2);
                } else {
                    // 0x004e54cc
                    charge(ctx, 3);
                    v1 = 4;
                    if (a0 != v1) {
                        // 0x004e54d8
                        charge(ctx, 2);
                        if (a0 == 0) {
                            goto L_004e565c;
                        }
                        // 0x004e54e0
                        charge(ctx, 3);
                        v0 = 2;
                        if (a0 != v0) {
                            // 0x004e54ec
                            charge(ctx, 2);
                            v0 = 0;
                            goto L_004e69c0;
                        }
                        // 0x004e54f4
                        charge(ctx, 9);
                        v0 = addiu(sp, 0xC4);
                        lw(s3, fp, 0x0);
                        lw(s2, v0, 0);
                        lw(v0, s6, 0);
                        s5 = addu(s3, v0);
                        jal(ctx, 0x4E5504u, gen::fn_sub_4E4180_004e4180);
                        v1 = subu(s5, s3);
                        if (v1 != 0) {
                            for (;;) {
                                // 0x004e5518
                                charge(ctx, 3);
                                at = sltiu(v1, 65);
                                s1 = v1;
                                if (at == 0) {
                                    // 0x004e5524
                                    charge(ctx, 1);
                                    s1 = 64;
                                }
                                // 0x004e5528
                                charge(ctx, 4);
                                at = sltiu(v1, 65);
                                sw(s3, fp, 0x0);
                                sw(s1, s6, 0);
                                if (at == 0) {
                                    // 0x004e5538
                                    charge(ctx, 2);
                                    s1 = addiu(s1, -1);
                                }
                                // 0x004e5540
                                charge(ctx, 51);
                                lw(v1, gp, -16912);  // 0x7CEAE0
                                v0 = addiu(gp, -16904);  // &0x7CEAE8
                                v1 = sll(v1, 2);
                                v0 = addu(v0, v1);
                                link(ctx, 0x4E5550u);  // $ra first: the delay slot below depends on it
                                lw(a0, v0, 0);
                                call(ctx, gen::fn_sub_4F1540_004f1540);
                                lw(v1, gp, -16912);  // 0x7CEAE0
                                v0 = addiu(gp, -16904);  // &0x7CEAE8
                                a1 = s4;
                                v1 = sll(v1, 2);
                                v0 = addu(v0, v1);
                                lw(a0, v0, 0);
                                a2 = addiu(sp, 0xB0);
                                jal(ctx, 0x4E5570u, gen::fn_sub_4CE050_004ce050);
                                lw(v1, gp, -16912);  // 0x7CEAE0
                                v0 = addiu(gp, -16904);  // &0x7CEAE8
                                v1 = sll(v1, 2);
                                v0 = addu(v0, v1);
                                link(ctx, 0x4E5588u);  // $ra first: the delay slot below depends on it
                                lw(a0, v0, 0);
                                call(ctx, gen::fn_sub_4E4E90_004e4e90);
                                lw(v1, gp, -16912);  // 0x7CEAE0
                                v0 = addiu(gp, -16904);  // &0x7CEAE8
                                v1 = sll(v1, 2);
                                v0 = addu(v0, v1);
                                lw(a0, v0, 0);
                                a1 = 0;
                                jal(ctx, 0x4E55A4u, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
                                lw(a0, sp, 0xC0);
                                v0 = 1;
                                t0 = 8;
                                a3 = addu(s2, s1);
                                a1 = s2;
                                t1 = t0;
                                sd(v0, sp, 0x0);
                                v0 = addiu(sp, 0xB8);
                                lw(a2, s0, 0);
                                lw(v1, v0, 0);
                                a2 = addu(a0, a2);
                                lw(v0, s6, 0);
                                v1 = sll(v1, 4);
                                t2 = addiu(v1, -8);
                                v0 = sll(v0, 4);
                                t3 = addiu(v0, -8);
                                jal(ctx, 0x4E55E8u, gen::fn_sub_4E4560_004e4560);
                                lw(v0, gp, -16912);  // 0x7CEAE0
                                s3 = addu(s3, s1);
                                v1 = subu(s5, s3);
                                s2 = addu(s2, s1);
                                v0 = v0 ^ 0x1;
                                sw(v0, gp, -16912);  // 0x7CEAE0
                                if (v1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004e560c
                            charge(ctx, 1);
                        }
                        // 0x004e5610
                        charge(ctx, 15);
                        jal(ctx, 0x4E5610u, gen::fn_sub_4E46C0_004e46c0);
                        jal(ctx, 0x4E5618u, gen::fn_DIntr_0050d3a0);
                        lw(v0, s7, 0);
                        v0 = addiu(v0, 1);
                        link(ctx, 0x4E5628u);  // $ra first: the delay slot below depends on it
                        sw(v0, s7, 0);
                        call(ctx, gen::fn_EIntr_0050d3f0);
                        lw(v1, s7, 4);
                        v0 = 1;
                        v1 = addiu(v1, 1);
                        sw(v1, s7, 4);
                        lw(v1, s7, 4);
                        if (v1 != v0) {
                        L_004e69a8:
                            charge(ctx, 1);
                            v0 = 1;
                        } else {
                            // 0x004e564c
                            charge(ctx, 4);
                            a0 = s7;
                            jal(ctx, 0x4E564Cu, gen::fn__rwDMAAddPURef_004d51c0);
                            v0 = 1;
                        }
                        // 0x004e69ac
                        charge(ctx, 2);
                        // 0x004e6d28 (the shared epilogue, written out on this path)
                        charge(ctx, 12);
                        ld(ra, sp, 0xA0);
                        lq(fp, sp, 0x90);
                        lq(s7, sp, 0x80);
                        lq(s6, sp, 0x70);
                        lq(s5, sp, 0x60);
                        lq(s4, sp, 0x50);
                        lq(s3, sp, 0x40);
                        lq(s2, sp, 0x30);
                        lq(s1, sp, 0x20);
                        lq(s0, sp, 0x10);
                        sp = addiu(sp, 0xD0);
                        return;
                    }
                L_004e565c:
                    charge(ctx, 3);
                    lw(v1, v0, 4);
                    a0 = addiu(v0, 4);
                    if (v1 != 0) {
                        // 0x004e5668
                        charge(ctx, 3);
                        lw(v1, s4, 4);
                        if (v1 == 0) {
                            goto L_004e69d8;
                        }
                        // 0x004e5674
                        charge(ctx, 20);
                        lw(a3, s4, 20);
                        v1 = addiu(sp, 0xC4);
                        lw(t1, gp, -16896);  // 0x7CEAF0
                        a1 = 4;
                        lw(a2, sp, 0xC0);
                        lw(v1, v1, 0);
                        a3 = addiu(a3, 7);
                        s7 = sra(a3, 3);
                        lw(t0, t1, 20);
                        lh(a3, t1, 28);
                        t0 = addiu(t0, 7);
                        a2 = subu(a2, a3);
                        sw(a2, sp, 0xC0);
                        lh(a2, t1, 30);
                        a2 = subu(v1, a2);
                        v1 = addiu(sp, 0xC4);
                        sw(a2, v1, 0);
                        lw(v1, s4, 20);
                        s6 = sra(t0, 3);
                        if (v1 != a1) {
                            // 0x004e56fc
                            charge(ctx, 5);
                            lw(v1, s4, 24);
                            lw(a1, s0, 0);
                            divu(v1, s7);
                            mflo(a2);
                            s3 = subu(a2, a1);
                        } else {
                            // 0x004e56c4
                            charge(ctx, 4);
                            lw(a1, s0, 0);
                            lw(v1, s4, 24);
                            a2 = sra(a1, 1);
                            if (i64(a1) < 0) {
                                // 0x004e56d4
                                charge(ctx, 2);
                                a2 = addiu(a1, 1);
                                a2 = sra(a2, 1);
                            }
                            // 0x004e56dc
                            charge(ctx, 6);
                            s3 = subu(v1, a2);
                            lw(a2, sp, 0xB0);
                            a2 = a2 & 0x1;
                            a2 = a2 & a1;
                            if (a2 != 0) {
                                // 0x004e56f4
                                charge(ctx, 2);
                                s3 = addiu(s3, -1);
                            }
                        }
                        // 0x004e5710
                        charge(ctx, 10);
                        lw(v0, v0, 24);
                        a2 = sll(s6, 2);
                        a2 = addu(a2, s6);
                        a2 = sll(a2, 1);
                        a3 = addu(s7, a2);
                        a2 = 21;
                        divu(v0, s6);
                        mflo(t0);
                        s1 = subu(t0, a1);
                        if (a3 == a2) {
                            // 0x004e6168
                            charge(ctx, 5);
                            lbu(v0, s4, 34);
                            v0 = v0 & 0x2;
                            s5 = sltu(0, v0);
                            if (s5 == 0) {
                                // 0x004e6ce8
                                charge(ctx, 6);
                                a0 = s4;
                                a1 = 0;
                                a2 = 2;
                                jal(ctx, 0x4E6CF0u, gen::fn_sub_4CE200_004ce200);
                                lw(a1, gp, -16896);  // 0x7CEAF0
                                backedge(ctx);
                            } else {
                                // 0x004e617c
                                charge(ctx, 1);
                                lw(a1, gp, -16896);  // 0x7CEAF0
                            }
                            // 0x004e6180
                            charge(ctx, 13);
                            v0 = addiu(sp, 0xC4);
                            lw(v0, v0, 0);
                            lw(v1, a1, 24);
                            mult(a0, v1, v0);
                            lw(v1, a1, 4);
                            lw(v0, sp, 0xC0);
                            a0 = addu(v1, a0);
                            mult1(v0, s6, v0);
                            lw(v1, s4, 20);
                            t2 = addu(a0, v0);
                            v0 = 8;
                            if (v1 != v0) {
                                // 0x004e6400
                                charge(ctx, 12);
                                lw(v0, fp, 0x0);
                                lw(v1, s4, 24);
                                mult(a2, v1, v0);
                                lw(a1, s4, 4);
                                lw(a0, sp, 0xB0);
                                lbu(v1, s4, 35);
                                v0 = 1;
                                a1 = addu(a1, a2);
                                a0 = sra(a0, 1);
                                v1 = v1 & 0xF;
                                t0 = addu(a1, a0);
                                if (v1 != v0) {
                                    // 0x004e6540
                                    charge(ctx, 5);
                                    lw(v1, s2, 0);
                                    lw(a3, s4, 8);
                                    v0 = addiu(v1, -1);
                                    sw(v0, s2, 0);
                                    if (v1 != 0) {
                                        // 0x004e6554
                                        charge(ctx, 5);
                                        a2 = sll(s1, 1);
                                        v1 = 128;
                                        v0 = 0xFF0000;
                                        a0 = 0xF80000;
                                        a1 = lui(0xFF00);
                                        for (;;) {
                                            // 0x004e6568
                                            charge(ctx, 4);
                                            lw(t3, sp, 0xB0);
                                            t3 = t3 & 0x1;
                                            lw(t1, s0, 0);
                                            if (t3 != 0) {
                                                // 0x004e6578
                                                charge(ctx, 11);
                                                lbu(t3, t0, 0);
                                                at = 0x7F000000;
                                                at = at | 0x1;
                                                t3 = sra(t3, 4);
                                                t3 = sll(t3, 2);
                                                t3 = addu(a3, t3);
                                                lw(t7, t3, 0);
                                                t3 = t7 & a1;
                                                at = sltu(t3, at);
                                                if (at != 0) {
                                                    // 0x004e65d0
                                                    charge(ctx, 38);
                                                    lhu(t4, t2, 0);
                                                    t6 = srl(t3, 24);
                                                    t5 = subu(v1, t6);
                                                    t3 = t4 & 0x8000;
                                                    t3 = sra(t3, 8);
                                                    mult(s7, t3, t5);
                                                    mult1(t3, t6, t6);
                                                    s6 = addiu(t3, 8192);
                                                    t3 = t7 & v0;
                                                    s1 = srl(t3, 16);
                                                    t3 = addu(s6, s7);
                                                    t3 = t3 & 0x4000;
                                                    t3 = sll(t3, 1);
                                                    mult(s1, t6, s1);
                                                    s1 = t4 & 0x7C00;
                                                    s6 = sra(s1, 7);
                                                    maddu(s6, s6, t5);
                                                    s1 = t7 & 0xFF00;
                                                    s1 = srl(s1, 8);
                                                    s6 = s6 & 0x7C00;
                                                    t3 = addu(t3, s6);
                                                    mult1(s1, t6, s1);
                                                    s1 = t4 & 0x3E0;
                                                    s1 = sra(s1, 2);
                                                    t4 = t4 & 0x1F;
                                                    maddu(s1, s1, t5);
                                                    t4 = sll(t4, 3);
                                                    s1 = s1 & 0x7C00;
                                                    s1 = srl(s1, 5);
                                                    t3 = addu(s1, t3);
                                                    mult(t4, t4, t5);
                                                    t4 = t7 & 0xFF;
                                                    maddu(t4, t6, t4);
                                                    t4 = t4 & 0x7C00;
                                                    t4 = srl(t4, 10);
                                                    t3 = addu(t4, t3);
                                                    sh(t3, t2, 0);
                                                } else {
                                                    // 0x004e65a4
                                                    charge(ctx, 11);
                                                    t4 = t7 & a0;
                                                    t3 = t7 & 0xF800;
                                                    t5 = srl(t4, 9);
                                                    t4 = srl(t3, 6);
                                                    t5 = t5 | 0x8000;
                                                    t3 = t7 & 0xF8;
                                                    t4 = t5 | t4;
                                                    t3 = srl(t3, 3);
                                                    t3 = t3 | t4;
                                                    sh(t3, t2, 0);
                                                }
                                                // 0x004e6668
                                                charge(ctx, 4);
                                                t2 = addiu(t2, 2);
                                                t0 = addiu(t0, 1);
                                                t1 = addiu(t1, -1);
                                            }
                                            // 0x004e6678
                                            charge(ctx, 3);
                                            at = slti(t1, 2);
                                            if (at == 0) {
                                                // 0x004e6684
                                                charge(ctx, 1);
                                                for (;;) {
                                                    // 0x004e6688
                                                    charge(ctx, 11);
                                                    lbu(t3, t0, 0);
                                                    at = 0x7F000000;
                                                    at = at | 0x1;
                                                    t3 = t3 & 0xF;
                                                    t3 = sll(t3, 2);
                                                    t3 = addu(a3, t3);
                                                    lw(t7, t3, 0);
                                                    t3 = t7 & a1;
                                                    at = sltu(t3, at);
                                                    if (at != 0) {
                                                        // 0x004e66e0
                                                        charge(ctx, 38);
                                                        lhu(t4, t2, 0);
                                                        t6 = srl(t3, 24);
                                                        t5 = subu(v1, t6);
                                                        t3 = t4 & 0x8000;
                                                        t3 = sra(t3, 8);
                                                        mult(s7, t3, t5);
                                                        mult1(t3, t6, t6);
                                                        s6 = addiu(t3, 8192);
                                                        t3 = t7 & v0;
                                                        s1 = srl(t3, 16);
                                                        t3 = addu(s6, s7);
                                                        t3 = t3 & 0x4000;
                                                        t3 = sll(t3, 1);
                                                        mult(s1, t6, s1);
                                                        s1 = t4 & 0x7C00;
                                                        s6 = sra(s1, 7);
                                                        maddu(s6, s6, t5);
                                                        s1 = t7 & 0xFF00;
                                                        s1 = srl(s1, 8);
                                                        s6 = s6 & 0x7C00;
                                                        t3 = addu(t3, s6);
                                                        mult1(s1, t6, s1);
                                                        s1 = t4 & 0x3E0;
                                                        s1 = sra(s1, 2);
                                                        t4 = t4 & 0x1F;
                                                        maddu(s1, s1, t5);
                                                        t4 = sll(t4, 3);
                                                        s1 = s1 & 0x7C00;
                                                        s1 = srl(s1, 5);
                                                        t3 = addu(s1, t3);
                                                        mult(t4, t4, t5);
                                                        t4 = t7 & 0xFF;
                                                        maddu(t4, t6, t4);
                                                        t4 = t4 & 0x7C00;
                                                        t4 = srl(t4, 10);
                                                        t3 = addu(t4, t3);
                                                        sh(t3, t2, 0);
                                                    } else {
                                                        // 0x004e66b4
                                                        charge(ctx, 11);
                                                        t4 = t7 & a0;
                                                        t3 = t7 & 0xF800;
                                                        t5 = srl(t4, 9);
                                                        t4 = srl(t3, 6);
                                                        t5 = t5 | 0x8000;
                                                        t3 = t7 & 0xF8;
                                                        t4 = t5 | t4;
                                                        t3 = srl(t3, 3);
                                                        t3 = t3 | t4;
                                                        sh(t3, t2, 0);
                                                    }
                                                    // 0x004e6778
                                                    charge(ctx, 11);
                                                    lbu(t3, t0, 0);
                                                    at = 0x7F000000;
                                                    at = at | 0x1;
                                                    t3 = sra(t3, 4);
                                                    t3 = sll(t3, 2);
                                                    t3 = addu(a3, t3);
                                                    lw(t7, t3, 0);
                                                    t3 = t7 & a1;
                                                    at = sltu(t3, at);
                                                    if (at != 0) {
                                                        // 0x004e67d0
                                                        charge(ctx, 38);
                                                        lhu(t4, t2, 2);
                                                        t6 = srl(t3, 24);
                                                        t5 = subu(v1, t6);
                                                        t3 = t4 & 0x8000;
                                                        t3 = sra(t3, 8);
                                                        mult(s7, t3, t5);
                                                        mult1(t3, t6, t6);
                                                        s6 = addiu(t3, 8192);
                                                        t3 = t7 & v0;
                                                        s1 = srl(t3, 16);
                                                        t3 = addu(s6, s7);
                                                        t3 = t3 & 0x4000;
                                                        t3 = sll(t3, 1);
                                                        mult(s1, t6, s1);
                                                        s1 = t4 & 0x7C00;
                                                        s6 = sra(s1, 7);
                                                        maddu(s6, s6, t5);
                                                        s1 = t7 & 0xFF00;
                                                        s1 = srl(s1, 8);
                                                        s6 = s6 & 0x7C00;
                                                        t3 = addu(t3, s6);
                                                        mult1(s1, t6, s1);
                                                        s1 = t4 & 0x3E0;
                                                        s1 = sra(s1, 2);
                                                        t4 = t4 & 0x1F;
                                                        maddu(s1, s1, t5);
                                                        t4 = sll(t4, 3);
                                                        s1 = s1 & 0x7C00;
                                                        s1 = srl(s1, 5);
                                                        t3 = addu(s1, t3);
                                                        mult(t4, t4, t5);
                                                        t4 = t7 & 0xFF;
                                                        maddu(t4, t6, t4);
                                                        t4 = t4 & 0x7C00;
                                                        t4 = srl(t4, 10);
                                                        t3 = addu(t4, t3);
                                                        sh(t3, t2, 2);
                                                    } else {
                                                        // 0x004e67a4
                                                        charge(ctx, 11);
                                                        t4 = t7 & a0;
                                                        t3 = t7 & 0xF800;
                                                        t5 = srl(t4, 9);
                                                        t4 = srl(t3, 6);
                                                        t5 = t5 | 0x8000;
                                                        t3 = t7 & 0xF8;
                                                        t4 = t5 | t4;
                                                        t3 = srl(t3, 3);
                                                        t3 = t3 | t4;
                                                        sh(t3, t2, 2);
                                                    }
                                                    // 0x004e6868
                                                    charge(ctx, 5);
                                                    t1 = addiu(t1, -2);
                                                    at = slti(t1, 2);
                                                    t2 = addiu(t2, 4);
                                                    t0 = addiu(t0, 1);
                                                    if (at != 0) {
                                                        break;
                                                    }
                                                    backedge(ctx);
                                                }
                                                // 0x004e687c
                                                charge(ctx, 1);
                                            }
                                            // 0x004e6880
                                            charge(ctx, 2);
                                            if (i64(t1) > 0) {
                                                // 0x004e6888
                                                charge(ctx, 11);
                                                lbu(t1, t0, 0);
                                                at = 0x7F000000;
                                                at = at | 0x1;
                                                t1 = t1 & 0xF;
                                                t1 = sll(t1, 2);
                                                t1 = addu(a3, t1);
                                                lw(t6, t1, 0);
                                                t1 = t6 & a1;
                                                at = sltu(t1, at);
                                                if (at != 0) {
                                                    // 0x004e68e0
                                                    charge(ctx, 38);
                                                    lhu(t3, t2, 0);
                                                    t5 = srl(t1, 24);
                                                    t4 = subu(v1, t5);
                                                    t1 = t3 & 0x8000;
                                                    t1 = sra(t1, 8);
                                                    mult(s6, t1, t4);
                                                    mult1(t1, t5, t5);
                                                    s1 = addiu(t1, 8192);
                                                    t1 = t6 & v0;
                                                    t7 = srl(t1, 16);
                                                    t1 = addu(s1, s6);
                                                    t1 = t1 & 0x4000;
                                                    t1 = sll(t1, 1);
                                                    mult(t7, t5, t7);
                                                    t7 = t3 & 0x7C00;
                                                    s1 = sra(t7, 7);
                                                    maddu(s1, s1, t4);
                                                    t7 = t6 & 0xFF00;
                                                    t7 = srl(t7, 8);
                                                    s1 = s1 & 0x7C00;
                                                    t1 = addu(t1, s1);
                                                    mult1(t7, t5, t7);
                                                    t7 = t3 & 0x3E0;
                                                    t7 = sra(t7, 2);
                                                    t3 = t3 & 0x1F;
                                                    maddu(t7, t7, t4);
                                                    t3 = sll(t3, 3);
                                                    t7 = t7 & 0x7C00;
                                                    t7 = srl(t7, 5);
                                                    t7 = addu(t7, t1);
                                                    mult(t1, t3, t4);
                                                    t1 = t6 & 0xFF;
                                                    maddu(t1, t5, t1);
                                                    t1 = t1 & 0x7C00;
                                                    t1 = srl(t1, 10);
                                                    t1 = addu(t1, t7);
                                                    sh(t1, t2, 0);
                                                } else {
                                                    // 0x004e68b4
                                                    charge(ctx, 11);
                                                    t3 = t6 & a0;
                                                    t1 = t6 & 0xF800;
                                                    t4 = srl(t3, 9);
                                                    t3 = srl(t1, 6);
                                                    t4 = t4 | 0x8000;
                                                    t1 = t6 & 0xF8;
                                                    t3 = t4 | t3;
                                                    t1 = srl(t1, 3);
                                                    t1 = t1 | t3;
                                                    sh(t1, t2, 0);
                                                }
                                                // 0x004e6978
                                                charge(ctx, 2);
                                                t2 = addiu(t2, 2);
                                            }
                                            // 0x004e6980
                                            charge(ctx, 6);
                                            lw(t3, s2, 0);
                                            t0 = addu(t0, s3);
                                            t2 = addu(t2, a2);
                                            t1 = addiu(t3, -1);
                                            sw(t1, s2, 0);
                                            if (t3 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                    }
                                } else {
                                    // 0x004e6430
                                    charge(ctx, 5);
                                    lw(a0, s2, 0);
                                    lw(v1, s4, 8);
                                    v0 = addiu(a0, -1);
                                    sw(v0, s2, 0);
                                    if (a0 != 0) {
                                        // 0x004e6444
                                        charge(ctx, 1);
                                        v0 = sll(s1, 1);
                                        for (;;) {
                                            // 0x004e6448
                                            charge(ctx, 4);
                                            lw(a1, sp, 0xB0);
                                            a1 = a1 & 0x1;
                                            lw(a0, s0, 0);
                                            if (a1 != 0) {
                                                // 0x004e6458
                                                charge(ctx, 8);
                                                lbu(a1, t0, 0);
                                                a1 = sra(a1, 4);
                                                a1 = sll(a1, 1);
                                                a1 = addu(v1, a1);
                                                lhu(a2, a1, 0);
                                                a1 = a2 & 0x8000;
                                                if (a1 != 0) {
                                                    // 0x004e6d08
                                                    charge(ctx, 2);
                                                    sh(a2, t2, 0);
                                                    backedge(ctx);
                                                }
                                                // 0x004e6478
                                                charge(ctx, 4);
                                                t2 = addiu(t2, 2);
                                                t0 = addiu(t0, 1);
                                                a0 = addiu(a0, -1);
                                            }
                                            // 0x004e6488
                                            charge(ctx, 3);
                                            at = slti(a0, 2);
                                            if (at == 0) {
                                                // 0x004e6494
                                                charge(ctx, 1);
                                                for (;;) {
                                                    // 0x004e6498
                                                    charge(ctx, 8);
                                                    lbu(a1, t0, 0);
                                                    a1 = a1 & 0xF;
                                                    a1 = sll(a1, 1);
                                                    a1 = addu(v1, a1);
                                                    lhu(a2, a1, 0);
                                                    a1 = a2 & 0x8000;
                                                    if (a1 != 0) {
                                                        // 0x004e6d10
                                                        charge(ctx, 2);
                                                        sh(a2, t2, 0);
                                                        backedge(ctx);
                                                    }
                                                    // 0x004e64b8
                                                    charge(ctx, 8);
                                                    lbu(a1, t0, 0);
                                                    a1 = sra(a1, 4);
                                                    a1 = sll(a1, 1);
                                                    a1 = addu(v1, a1);
                                                    lhu(a2, a1, 0);
                                                    a1 = a2 & 0x8000;
                                                    if (a1 != 0) {
                                                        // 0x004e6d18
                                                        charge(ctx, 2);
                                                        sh(a2, t2, 2);
                                                        backedge(ctx);
                                                    }
                                                    // 0x004e64d8
                                                    charge(ctx, 5);
                                                    a0 = addiu(a0, -2);
                                                    at = slti(a0, 2);
                                                    t2 = addiu(t2, 4);
                                                    t0 = addiu(t0, 1);
                                                    if (at != 0) {
                                                        break;
                                                    }
                                                    backedge(ctx);
                                                }
                                                // 0x004e64ec
                                                charge(ctx, 1);
                                            }
                                            // 0x004e64f0
                                            charge(ctx, 2);
                                            if (i64(a0) > 0) {
                                                // 0x004e64f8
                                                charge(ctx, 8);
                                                lbu(a0, t0, 0);
                                                a0 = a0 & 0xF;
                                                a0 = sll(a0, 1);
                                                a0 = addu(v1, a0);
                                                lhu(a1, a0, 0);
                                                a0 = a1 & 0x8000;
                                                if (a0 != 0) {
                                                    // 0x004e6d20
                                                    charge(ctx, 2);
                                                    sh(a1, t2, 0);
                                                    backedge(ctx);
                                                }
                                                // 0x004e6518
                                                charge(ctx, 2);
                                                t2 = addiu(t2, 2);
                                            }
                                            // 0x004e6520
                                            charge(ctx, 6);
                                            lw(a1, s2, 0);
                                            t0 = addu(t0, s3);
                                            t2 = addu(t2, v0);
                                            a0 = addiu(a1, -1);
                                            sw(a0, s2, 0);
                                            if (a1 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x004e6538
                                        charge(ctx, 2);
                                    }
                                }
                            } else {
                                // 0x004e61b4
                                charge(ctx, 13);
                                lw(v0, fp, 0x0);
                                lw(v1, s4, 24);
                                mult(a0, v1, v0);
                                lw(v1, s4, 4);
                                lw(v0, sp, 0xB0);
                                v1 = addu(v1, a0);
                                mult1(v0, s7, v0);
                                lbu(a0, s4, 35);
                                v0 = addu(v1, v0);
                                v1 = 1;
                                a0 = a0 & 0xF;
                                if (a0 != v1) {
                                    // 0x004e6280
                                    charge(ctx, 5);
                                    lw(a0, s2, 0);
                                    lw(t6, s4, 8);
                                    v1 = addiu(a0, -1);
                                    sw(v1, s2, 0);
                                    if (a0 != 0) {
                                        // 0x004e6294
                                        charge(ctx, 5);
                                        t5 = sll(s1, 1);
                                        a3 = 128;
                                        a0 = 0xFF0000;
                                        t1 = 0xF80000;
                                        t3 = lui(0xFF00);
                                        for (;;) {
                                            // 0x004e62a8
                                            charge(ctx, 3);
                                            lw(v1, s0, 0);
                                            t7 = addiu(v1, -1);
                                            if (v1 != 0) {
                                                // 0x004e62b4
                                                charge(ctx, 1);
                                                for (;;) {
                                                    // 0x004e62b8
                                                    charge(ctx, 17);
                                                    lbu(t0, v0, 0);
                                                    at = 0x7F000000;
                                                    at = at | 0x1;
                                                    v1 = t0 & 0x10;
                                                    a2 = t0 & 0xE7;
                                                    a1 = sra(v1, 1);
                                                    v1 = t0 & 0x8;
                                                    a1 = a2 | a1;
                                                    v1 = sll(v1, 1);
                                                    v1 = v1 | a1;
                                                    v1 = sll(v1, 2);
                                                    a1 = addu(t6, v1);
                                                    lw(t4, a1, 0);
                                                    v1 = t4 & t3;
                                                    at = sltu(v1, at);
                                                    if (at != 0) {
                                                        // 0x004e6330
                                                        charge(ctx, 38);
                                                        lhu(a1, t2, 0);
                                                        t0 = srl(v1, 24);
                                                        a2 = subu(a3, t0);
                                                        v1 = a1 & 0x8000;
                                                        v1 = sra(v1, 8);
                                                        mult(s7, v1, a2);
                                                        mult1(v1, t0, t0);
                                                        s6 = addiu(v1, 8192);
                                                        v1 = a1 & 0x7C00;
                                                        s1 = sra(v1, 7);
                                                        v1 = addu(s7, s6);
                                                        v1 = v1 & 0x4000;
                                                        v1 = sll(v1, 1);
                                                        mult(s1, s1, a2);
                                                        s1 = t4 & a0;
                                                        s6 = srl(s1, 16);
                                                        maddu(s6, t0, s6);
                                                        s1 = a1 & 0x3E0;
                                                        s1 = sra(s1, 2);
                                                        s6 = s6 & 0x7C00;
                                                        v1 = addu(v1, s6);
                                                        mult1(s1, s1, a2);
                                                        s1 = t4 & 0xFF00;
                                                        a1 = a1 & 0x1F;
                                                        s1 = srl(s1, 8);
                                                        a1 = sll(a1, 3);
                                                        maddu(s1, t0, s1);
                                                        s1 = s1 & 0x7C00;
                                                        s1 = srl(s1, 5);
                                                        v1 = addu(s1, v1);
                                                        mult(a1, a1, a2);
                                                        a1 = t4 & 0xFF;
                                                        maddu(a1, t0, a1);
                                                        a1 = a1 & 0x7C00;
                                                        a1 = srl(a1, 10);
                                                        v1 = addu(a1, v1);
                                                        sh(v1, t2, 0);
                                                    } else {
                                                        // 0x004e62fc
                                                        charge(ctx, 12);
                                                        lw(t0, a1, 0);
                                                        a1 = t0 & t1;
                                                        v1 = t0 & 0xF800;
                                                        a2 = srl(a1, 9);
                                                        a1 = srl(v1, 6);
                                                        a2 = a2 | 0x8000;
                                                        v1 = t0 & 0xF8;
                                                        a1 = a2 | a1;
                                                        v1 = srl(v1, 3);
                                                        v1 = v1 | a1;
                                                        sh(v1, t2, 0);
                                                    }
                                                    // 0x004e63c8
                                                    charge(ctx, 5);
                                                    v1 = t7;
                                                    t2 = addiu(t2, 2);
                                                    v0 = addiu(v0, 1);
                                                    t7 = addiu(t7, -1);
                                                    if (v1 == 0) {
                                                        break;
                                                    }
                                                    backedge(ctx);
                                                }
                                                // 0x004e63dc
                                                charge(ctx, 1);
                                            }
                                            // 0x004e63e0
                                            charge(ctx, 6);
                                            lw(a1, s2, 0);
                                            v0 = addu(v0, s3);
                                            t2 = addu(t2, t5);
                                            v1 = addiu(a1, -1);
                                            sw(v1, s2, 0);
                                            if (a1 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x004e63f8
                                        charge(ctx, 2);
                                    }
                                } else {
                                    // 0x004e61e8
                                    charge(ctx, 5);
                                    lw(a1, s2, 0);
                                    lw(a0, s4, 8);
                                    v1 = addiu(a1, -1);
                                    sw(v1, s2, 0);
                                    if (a1 != 0) {
                                        // 0x004e61fc
                                        charge(ctx, 1);
                                        v1 = sll(s1, 1);
                                        for (;;) {
                                            // 0x004e6200
                                            charge(ctx, 3);
                                            lw(a2, s0, 0);
                                            a1 = addiu(a2, -1);
                                            if (a2 != 0) {
                                                // 0x004e620c
                                                charge(ctx, 1);
                                                for (;;) {
                                                    // 0x004e6210
                                                    charge(ctx, 14);
                                                    lbu(t1, v0, 0);
                                                    a2 = t1 & 0x10;
                                                    t0 = t1 & 0xE7;
                                                    a3 = sra(a2, 1);
                                                    a2 = t1 & 0x8;
                                                    a3 = t0 | a3;
                                                    a2 = sll(a2, 1);
                                                    a2 = a2 | a3;
                                                    a2 = sll(a2, 1);
                                                    a2 = addu(a0, a2);
                                                    lhu(a3, a2, 0);
                                                    a2 = a3 & 0x8000;
                                                    if (a2 != 0) {
                                                        // 0x004e6d00
                                                        charge(ctx, 2);
                                                        sh(a3, t2, 0);
                                                        backedge(ctx);
                                                    }
                                                    // 0x004e6248
                                                    charge(ctx, 5);
                                                    a2 = a1;
                                                    t2 = addiu(t2, 2);
                                                    v0 = addiu(v0, 1);
                                                    a1 = addiu(a1, -1);
                                                    if (a2 == 0) {
                                                        break;
                                                    }
                                                    backedge(ctx);
                                                }
                                                // 0x004e625c
                                                charge(ctx, 1);
                                            }
                                            // 0x004e6260
                                            charge(ctx, 6);
                                            lw(a2, s2, 0);
                                            v0 = addu(v0, s3);
                                            t2 = addu(t2, v1);
                                            a1 = addiu(a2, -1);
                                            sw(a1, s2, 0);
                                            if (a2 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x004e6278
                                        charge(ctx, 2);
                                    }
                                }
                            }
                            // 0x004e6998
                            charge(ctx, 2);
                            if (s5 == 0) {
                                // 0x004e69a0
                                charge(ctx, 2);
                                a0 = s4;
                                jal(ctx, 0x4E69A0u, gen::fn_sub_4CDE00_004cde00);
                            }
                            goto L_004e69a8;
                        }
                        // 0x004e5738
                        charge(ctx, 3);
                        a1 = 22;
                        if (a3 == a1) {
                            // 0x004e60c0
                            charge(ctx, 19);
                            a1 = addiu(sp, 0xC4);
                            lw(a1, a1, 0);
                            mult(a1, v0, a1);
                            lw(a0, a0, 0);
                            lw(v0, sp, 0xC0);
                            a1 = addu(a0, a1);
                            mult1(v0, s6, v0);
                            lw(a0, fp, 0x0);
                            v0 = addu(a1, v0);
                            mult(a1, v1, a0);
                            lw(a0, s4, 4);
                            lw(v1, sp, 0xB0);
                            a1 = addu(a0, a1);
                            mult1(v1, s7, v1);
                            lw(a0, s2, 0);
                            t0 = addu(a1, v1);
                            v1 = addiu(a0, -1);
                            sw(v1, s2, 0);
                            if (a0 != 0) {
                                // 0x004e610c
                                charge(ctx, 2);
                                a2 = sll(s3, 1);
                                a1 = sll(s1, 1);
                                for (;;) {
                                    // 0x004e6114
                                    charge(ctx, 3);
                                    lw(v1, s0, 0);
                                    a3 = addiu(v1, -1);
                                    if (v1 != 0) {
                                        for (;;) {
                                            // 0x004e6120
                                            charge(ctx, 4);
                                            lhu(a0, t0, 0);
                                            v1 = a0 & 0x8000;
                                            if (v1 != 0) {
                                                // 0x004e6ce0
                                                charge(ctx, 2);
                                                sh(a0, v0, 0);
                                                backedge(ctx);
                                            }
                                            // 0x004e6130
                                            charge(ctx, 5);
                                            v1 = a3;
                                            v0 = addiu(v0, 2);
                                            t0 = addiu(t0, 2);
                                            a3 = addiu(a3, -1);
                                            if (v1 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x004e6144
                                        charge(ctx, 1);
                                    }
                                    // 0x004e6148
                                    charge(ctx, 6);
                                    lw(a0, s2, 0);
                                    t0 = addu(t0, a2);
                                    v0 = addu(v0, a1);
                                    v1 = addiu(a0, -1);
                                    sw(v1, s2, 0);
                                    if (a0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004e6160
                                charge(ctx, 2);
                            }
                            goto L_004e69a8;
                        }
                        // 0x004e5744
                        charge(ctx, 3);
                        a1 = 24;
                        if (a3 == a1) {
                            // 0x004e5f38
                            charge(ctx, 19);
                            a1 = addiu(sp, 0xC4);
                            lw(a1, a1, 0);
                            mult(a1, v0, a1);
                            lw(a0, a0, 0);
                            lw(v0, sp, 0xC0);
                            a1 = addu(a0, a1);
                            mult1(a0, s6, v0);
                            lw(v0, fp, 0x0);
                            t7 = addu(a1, a0);
                            mult(a0, v1, v0);
                            lw(v1, s4, 4);
                            lw(v0, sp, 0xB0);
                            a0 = addu(v1, a0);
                            mult1(v0, s7, v0);
                            lw(v1, s2, 0);
                            t6 = addu(a0, v0);
                            v0 = addiu(v1, -1);
                            sw(v0, s2, 0);
                            if (v1 != 0) {
                                // 0x004e5f84
                                charge(ctx, 6);
                                t4 = sll(s3, 2);
                                t3 = sll(s1, 1);
                                a2 = 128;
                                v1 = 0xFF0000;
                                t0 = 0xF80000;
                                t1 = lui(0xFF00);
                                for (;;) {
                                    // 0x004e5f9c
                                    charge(ctx, 3);
                                    lw(v0, s0, 0);
                                    t5 = addiu(v0, -1);
                                    if (v0 != 0) {
                                        for (;;) {
                                            // 0x004e5fa8
                                            charge(ctx, 7);
                                            lw(t2, t6, 0);
                                            at = 0x7F000000;
                                            at = at | 0x1;
                                            v0 = t2 & t1;
                                            at = sltu(v0, at);
                                            if (at != 0) {
                                                // 0x004e5ff0
                                                charge(ctx, 38);
                                                lhu(a0, t7, 0);
                                                a3 = srl(v0, 24);
                                                a1 = subu(a2, a3);
                                                v0 = a0 & 0x8000;
                                                v0 = sra(v0, 8);
                                                mult(s4, v0, a1);
                                                mult1(v0, a3, a3);
                                                s3 = addiu(v0, 8192);
                                                v0 = t2 & v1;
                                                s1 = srl(v0, 16);
                                                v0 = addu(s3, s4);
                                                v0 = v0 & 0x4000;
                                                v0 = sll(v0, 1);
                                                mult(s1, s1, a3);
                                                s1 = a0 & 0x7C00;
                                                s3 = sra(s1, 7);
                                                maddu(s3, s3, a1);
                                                s1 = t2 & 0xFF00;
                                                s1 = srl(s1, 8);
                                                s3 = s3 & 0x7C00;
                                                v0 = addu(v0, s3);
                                                mult1(s1, s1, a3);
                                                s1 = a0 & 0x3E0;
                                                s1 = sra(s1, 2);
                                                a0 = a0 & 0x1F;
                                                maddu(s1, s1, a1);
                                                a0 = sll(a0, 3);
                                                s1 = s1 & 0x7C00;
                                                s1 = srl(s1, 5);
                                                s1 = addu(s1, v0);
                                                mult(v0, a0, a1);
                                                v0 = t2 & 0xFF;
                                                maddu(v0, v0, a3);
                                                v0 = v0 & 0x7C00;
                                                v0 = srl(v0, 10);
                                                v0 = addu(v0, s1);
                                                sh(v0, t7, 0);
                                            } else {
                                                // 0x004e5fc4
                                                charge(ctx, 11);
                                                a0 = t2 & t0;
                                                v0 = t2 & 0xF800;
                                                a1 = srl(a0, 9);
                                                a0 = srl(v0, 6);
                                                a1 = a1 | 0x8000;
                                                v0 = t2 & 0xF8;
                                                a0 = a1 | a0;
                                                v0 = srl(v0, 3);
                                                v0 = v0 | a0;
                                                sh(v0, t7, 0);
                                            }
                                            // 0x004e6088
                                            charge(ctx, 5);
                                            v0 = t5;
                                            t7 = addiu(t7, 2);
                                            t6 = addiu(t6, 4);
                                            t5 = addiu(t5, -1);
                                            if (v0 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x004e609c
                                        charge(ctx, 1);
                                    }
                                    // 0x004e60a0
                                    charge(ctx, 6);
                                    lw(a0, s2, 0);
                                    t6 = addu(t6, t4);
                                    t7 = addu(t7, t3);
                                    v0 = addiu(a0, -1);
                                    sw(v0, s2, 0);
                                    if (a0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004e60b8
                                charge(ctx, 2);
                            }
                            goto L_004e69a8;
                        }
                        // 0x004e5750
                        charge(ctx, 3);
                        a1 = 41;
                        if (a3 == a1) {
                            // 0x004e5988
                            charge(ctx, 5);
                            lbu(v0, s4, 34);
                            v0 = v0 & 0x2;
                            s5 = sltu(0, v0);
                            if (s5 == 0) {
                                // 0x004e6a10
                                charge(ctx, 6);
                                a0 = s4;
                                a1 = 0;
                                a2 = 2;
                                jal(ctx, 0x4E6A18u, gen::fn_sub_4CE200_004ce200);
                                lw(a1, gp, -16896);  // 0x7CEAF0
                                backedge(ctx);
                            } else {
                                // 0x004e599c
                                charge(ctx, 1);
                                lw(a1, gp, -16896);  // 0x7CEAF0
                            }
                            // 0x004e59a0
                            charge(ctx, 13);
                            v0 = addiu(sp, 0xC4);
                            lw(v0, v0, 0);
                            lw(v1, a1, 24);
                            mult(a0, v1, v0);
                            lw(v1, a1, 4);
                            lw(v0, sp, 0xC0);
                            a0 = addu(v1, a0);
                            mult1(v0, s6, v0);
                            lw(v1, s4, 20);
                            t1 = addu(a0, v0);
                            v0 = 8;
                            if (v1 != v0) {
                                // 0x004e5b50
                                charge(ctx, 12);
                                lw(v0, fp, 0x0);
                                lw(v1, s4, 24);
                                mult(a2, v1, v0);
                                lw(a1, s4, 4);
                                lw(a0, sp, 0xB0);
                                lbu(v1, s4, 35);
                                v0 = 1;
                                a1 = addu(a1, a2);
                                a0 = sra(a0, 1);
                                v1 = v1 & 0xF;
                                a3 = addu(a1, a0);
                                if (v1 != v0) {
                                    // 0x004e5c98
                                    charge(ctx, 5);
                                    lw(v1, s2, 0);
                                    lw(a2, s4, 8);
                                    v0 = addiu(v1, -1);
                                    sw(v0, s2, 0);
                                    if (v1 != 0) {
                                        // 0x004e5cac
                                        charge(ctx, 4);
                                        a1 = sll(s1, 2);
                                        a0 = lui(0xFF00);
                                        v1 = 128;
                                        v0 = 0xFF0000;
                                        for (;;) {
                                            // 0x004e5cbc
                                            charge(ctx, 4);
                                            lw(t2, sp, 0xB0);
                                            t2 = t2 & 0x1;
                                            lw(t0, s0, 0);
                                            if (t2 != 0) {
                                                // 0x004e5ccc
                                                charge(ctx, 10);
                                                lbu(t2, a3, 0);
                                                at = 0x7F000000;
                                                at = at | 0x1;
                                                t2 = sra(t2, 4);
                                                t2 = sll(t2, 2);
                                                t2 = addu(a2, t2);
                                                lw(t6, t2, 0);
                                                at = sltu(t6, at);
                                                if (at != 0) {
                                                    // 0x004e5d00
                                                    charge(ctx, 38);
                                                    t2 = t6 & a0;
                                                    t5 = srl(t2, 24);
                                                    lw(t3, t1, 0);
                                                    t2 = t6 & v0;
                                                    t4 = subu(v1, t5);
                                                    t2 = srl(t2, 16);
                                                    mult(t2, t5, t2);
                                                    t7 = t3 & v0;
                                                    t2 = t3 & a0;
                                                    s1 = srl(t7, 16);
                                                    t7 = srl(t2, 24);
                                                    maddu(t2, s1, t4);
                                                    t2 = t2 & 0x7F80;
                                                    t2 = sll(t2, 9);
                                                    mult1(t7, t7, t4);
                                                    maddu(s1, t5, t5);
                                                    t7 = t6 & 0xFF00;
                                                    t7 = srl(t7, 8);
                                                    s1 = s1 & 0x7F80;
                                                    s1 = sll(s1, 17);
                                                    t2 = addu(s1, t2);
                                                    mult(t7, t5, t7);
                                                    t6 = t6 & 0xFF;
                                                    t7 = t3 & 0xFF00;
                                                    t7 = srl(t7, 8);
                                                    maddu(t7, t7, t4);
                                                    t7 = t7 & 0x7F80;
                                                    t7 = sll(t7, 1);
                                                    t7 = addu(t7, t2);
                                                    mult1(t2, t5, t6);
                                                    t2 = t3 & 0xFF;
                                                    maddu(t2, t2, t4);
                                                    t2 = t2 & 0x7F80;
                                                    t2 = srl(t2, 7);
                                                    t2 = addu(t2, t7);
                                                    sw(t2, t1, 0);
                                                } else {
                                                    // 0x004e5cf4
                                                    charge(ctx, 2);
                                                    sw(t6, t1, 0);
                                                }
                                                // 0x004e5d98
                                                charge(ctx, 4);
                                                t1 = addiu(t1, 4);
                                                a3 = addiu(a3, 1);
                                                t0 = addiu(t0, -1);
                                            }
                                            // 0x004e5da8
                                            charge(ctx, 3);
                                            at = slti(t0, 2);
                                            if (at == 0) {
                                                // 0x004e5db4
                                                charge(ctx, 1);
                                                for (;;) {
                                                    // 0x004e5db8
                                                    charge(ctx, 10);
                                                    lbu(t2, a3, 0);
                                                    at = 0x7F000000;
                                                    at = at | 0x1;
                                                    t2 = t2 & 0xF;
                                                    t2 = sll(t2, 2);
                                                    t2 = addu(a2, t2);
                                                    lw(t6, t2, 0);
                                                    at = sltu(t6, at);
                                                    if (at != 0) {
                                                        // 0x004e6bb0
                                                        charge(ctx, 38);
                                                        t2 = t6 & a0;
                                                        t5 = srl(t2, 24);
                                                        lw(t3, t1, 0);
                                                        t2 = t6 & v0;
                                                        t4 = subu(v1, t5);
                                                        t2 = srl(t2, 16);
                                                        mult(t2, t5, t2);
                                                        t7 = t3 & v0;
                                                        t2 = t3 & a0;
                                                        s1 = srl(t7, 16);
                                                        t7 = srl(t2, 24);
                                                        maddu(t2, s1, t4);
                                                        t2 = t2 & 0x7F80;
                                                        t2 = sll(t2, 9);
                                                        mult1(t7, t7, t4);
                                                        maddu(s1, t5, t5);
                                                        t7 = t6 & 0xFF00;
                                                        t7 = srl(t7, 8);
                                                        s1 = s1 & 0x7F80;
                                                        s1 = sll(s1, 17);
                                                        t2 = addu(s1, t2);
                                                        mult(t7, t5, t7);
                                                        t6 = t6 & 0xFF;
                                                        t7 = t3 & 0xFF00;
                                                        t7 = srl(t7, 8);
                                                        maddu(t7, t7, t4);
                                                        t7 = t7 & 0x7F80;
                                                        t7 = sll(t7, 1);
                                                        t7 = addu(t7, t2);
                                                        mult1(t2, t5, t6);
                                                        t2 = t3 & 0xFF;
                                                        maddu(t2, t2, t4);
                                                        t2 = t2 & 0x7F80;
                                                        t2 = srl(t2, 7);
                                                        t2 = addu(t2, t7);
                                                        sw(t2, t1, 0);
                                                        backedge(ctx);
                                                    } else {
                                                        // 0x004e5de0
                                                        charge(ctx, 2);
                                                        sw(t6, t1, 0);
                                                    }
                                                    // 0x004e5de8
                                                    charge(ctx, 10);
                                                    lbu(t2, a3, 0);
                                                    at = 0x7F000000;
                                                    at = at | 0x1;
                                                    t2 = sra(t2, 4);
                                                    t2 = sll(t2, 2);
                                                    t2 = addu(a2, t2);
                                                    lw(t6, t2, 0);
                                                    at = sltu(t6, at);
                                                    if (at != 0) {
                                                        // 0x004e6c48
                                                        charge(ctx, 38);
                                                        t2 = t6 & a0;
                                                        t5 = srl(t2, 24);
                                                        lw(t3, t1, 4);
                                                        t2 = t6 & v0;
                                                        t4 = subu(v1, t5);
                                                        t2 = srl(t2, 16);
                                                        mult(t2, t5, t2);
                                                        t7 = t3 & v0;
                                                        t2 = t3 & a0;
                                                        s1 = srl(t7, 16);
                                                        t7 = srl(t2, 24);
                                                        maddu(t2, s1, t4);
                                                        t2 = t2 & 0x7F80;
                                                        t2 = sll(t2, 9);
                                                        mult1(t7, t7, t4);
                                                        maddu(s1, t5, t5);
                                                        t7 = t6 & 0xFF00;
                                                        t7 = srl(t7, 8);
                                                        s1 = s1 & 0x7F80;
                                                        s1 = sll(s1, 17);
                                                        t2 = addu(s1, t2);
                                                        mult(t7, t5, t7);
                                                        t6 = t6 & 0xFF;
                                                        t7 = t3 & 0xFF00;
                                                        t7 = srl(t7, 8);
                                                        maddu(t7, t7, t4);
                                                        t7 = t7 & 0x7F80;
                                                        t7 = sll(t7, 1);
                                                        t7 = addu(t7, t2);
                                                        mult1(t2, t5, t6);
                                                        t2 = t3 & 0xFF;
                                                        maddu(t2, t2, t4);
                                                        t2 = t2 & 0x7F80;
                                                        t2 = srl(t2, 7);
                                                        t2 = addu(t2, t7);
                                                        sw(t2, t1, 4);
                                                        backedge(ctx);
                                                    } else {
                                                        // 0x004e5e10
                                                        charge(ctx, 2);
                                                        sw(t6, t1, 4);
                                                    }
                                                    // 0x004e5e18
                                                    charge(ctx, 5);
                                                    t0 = addiu(t0, -2);
                                                    at = slti(t0, 2);
                                                    t1 = addiu(t1, 8);
                                                    a3 = addiu(a3, 1);
                                                    if (at != 0) {
                                                        break;
                                                    }
                                                    backedge(ctx);
                                                }
                                                // 0x004e5e2c
                                                charge(ctx, 1);
                                            }
                                            // 0x004e5e30
                                            charge(ctx, 2);
                                            if (i64(t0) > 0) {
                                                // 0x004e5e38
                                                charge(ctx, 10);
                                                lbu(t0, a3, 0);
                                                at = 0x7F000000;
                                                at = at | 0x1;
                                                t0 = t0 & 0xF;
                                                t0 = sll(t0, 2);
                                                t0 = addu(a2, t0);
                                                lw(t5, t0, 0);
                                                at = sltu(t5, at);
                                                if (at != 0) {
                                                    // 0x004e5e68
                                                    charge(ctx, 38);
                                                    t0 = t5 & a0;
                                                    t4 = srl(t0, 24);
                                                    lw(t2, t1, 0);
                                                    t0 = t5 & v0;
                                                    t3 = subu(v1, t4);
                                                    t0 = srl(t0, 16);
                                                    mult(t0, t4, t0);
                                                    t6 = t2 & v0;
                                                    t0 = t2 & a0;
                                                    t7 = srl(t6, 16);
                                                    t6 = srl(t0, 24);
                                                    maddu(t0, t7, t3);
                                                    t0 = t0 & 0x7F80;
                                                    t0 = sll(t0, 9);
                                                    mult1(t6, t6, t3);
                                                    maddu(t7, t4, t4);
                                                    t6 = t5 & 0xFF00;
                                                    t6 = srl(t6, 8);
                                                    t7 = t7 & 0x7F80;
                                                    t7 = sll(t7, 17);
                                                    t0 = addu(t7, t0);
                                                    mult(t6, t4, t6);
                                                    t5 = t5 & 0xFF;
                                                    t6 = t2 & 0xFF00;
                                                    t6 = srl(t6, 8);
                                                    maddu(t6, t6, t3);
                                                    t6 = t6 & 0x7F80;
                                                    t6 = sll(t6, 1);
                                                    t6 = addu(t6, t0);
                                                    mult1(t0, t4, t5);
                                                    t0 = t2 & 0xFF;
                                                    maddu(t0, t0, t3);
                                                    t0 = t0 & 0x7F80;
                                                    t0 = srl(t0, 7);
                                                    t0 = addu(t0, t6);
                                                    sw(t0, t1, 0);
                                                } else {
                                                    // 0x004e5e60
                                                    charge(ctx, 2);
                                                    sw(t5, t1, 0);
                                                }
                                                // 0x004e5f00
                                                charge(ctx, 2);
                                                t1 = addiu(t1, 4);
                                            }
                                            // 0x004e5f08
                                            charge(ctx, 6);
                                            lw(t2, s2, 0);
                                            a3 = addu(a3, s3);
                                            t1 = addu(t1, a1);
                                            t0 = addiu(t2, -1);
                                            sw(t0, s2, 0);
                                            if (t2 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                    }
                                } else {
                                    // 0x004e5b80
                                    charge(ctx, 5);
                                    lw(v1, s2, 0);
                                    lw(a0, s4, 8);
                                    v0 = addiu(v1, -1);
                                    sw(v0, s2, 0);
                                    if (v1 != 0) {
                                        // 0x004e5b94
                                        charge(ctx, 2);
                                        v1 = sll(s1, 2);
                                        v0 = lui(0x8000);
                                        for (;;) {
                                            // 0x004e5b9c
                                            charge(ctx, 4);
                                            lw(a2, sp, 0xB0);
                                            a2 = a2 & 0x1;
                                            lw(a1, s0, 0);
                                            if (a2 != 0) {
                                                // 0x004e5bac
                                                charge(ctx, 8);
                                                lbu(a2, a3, 0);
                                                a2 = sra(a2, 4);
                                                a2 = sll(a2, 1);
                                                a2 = addu(a0, a2);
                                                lhu(t2, a2, 0);
                                                a2 = t2 & 0x8000;
                                                if (a2 != 0) {
                                                    // 0x004e6af0
                                                    charge(ctx, 11);
                                                    a2 = t2 & 0x7C00;
                                                    t0 = sll(a2, 9);
                                                    a2 = t2 & 0x3E0;
                                                    t0 = t0 | v0;
                                                    a2 = sll(a2, 6);
                                                    t0 = t0 | a2;
                                                    a2 = t2 & 0x1F;
                                                    a2 = sll(a2, 3);
                                                    a2 = a2 | t0;
                                                    sw(a2, t1, 0);
                                                    backedge(ctx);
                                                } else {
                                                    // 0x004e5bcc
                                                    charge(ctx, 1);
                                                }
                                                // 0x004e5bd0
                                                charge(ctx, 4);
                                                t1 = addiu(t1, 4);
                                                a3 = addiu(a3, 1);
                                                a1 = addiu(a1, -1);
                                            }
                                            // 0x004e5be0
                                            charge(ctx, 3);
                                            at = slti(a1, 2);
                                            if (at == 0) {
                                                // 0x004e5bec
                                                charge(ctx, 1);
                                                for (;;) {
                                                    // 0x004e5bf0
                                                    charge(ctx, 8);
                                                    lbu(a2, a3, 0);
                                                    a2 = a2 & 0xF;
                                                    a2 = sll(a2, 1);
                                                    a2 = addu(a0, a2);
                                                    lhu(t2, a2, 0);
                                                    a2 = t2 & 0x8000;
                                                    if (a2 != 0) {
                                                        // 0x004e6b20
                                                        charge(ctx, 11);
                                                        a2 = t2 & 0x7C00;
                                                        t0 = sll(a2, 9);
                                                        a2 = t2 & 0x3E0;
                                                        t0 = t0 | v0;
                                                        a2 = sll(a2, 6);
                                                        t0 = t0 | a2;
                                                        a2 = t2 & 0x1F;
                                                        a2 = sll(a2, 3);
                                                        a2 = a2 | t0;
                                                        sw(a2, t1, 0);
                                                        backedge(ctx);
                                                    }
                                                    // 0x004e5c10
                                                    charge(ctx, 8);
                                                    lbu(a2, a3, 0);
                                                    a2 = sra(a2, 4);
                                                    a2 = sll(a2, 1);
                                                    a2 = addu(a0, a2);
                                                    lhu(t2, a2, 0);
                                                    a2 = t2 & 0x8000;
                                                    if (a2 != 0) {
                                                        // 0x004e6b50
                                                        charge(ctx, 11);
                                                        a2 = t2 & 0x7C00;
                                                        t0 = sll(a2, 9);
                                                        a2 = t2 & 0x3E0;
                                                        t0 = t0 | v0;
                                                        a2 = sll(a2, 6);
                                                        t0 = t0 | a2;
                                                        a2 = t2 & 0x1F;
                                                        a2 = sll(a2, 3);
                                                        a2 = a2 | t0;
                                                        sw(a2, t1, 4);
                                                        backedge(ctx);
                                                    }
                                                    // 0x004e5c30
                                                    charge(ctx, 5);
                                                    a1 = addiu(a1, -2);
                                                    at = slti(a1, 2);
                                                    t1 = addiu(t1, 8);
                                                    a3 = addiu(a3, 1);
                                                    if (at != 0) {
                                                        break;
                                                    }
                                                    backedge(ctx);
                                                }
                                                // 0x004e5c44
                                                charge(ctx, 1);
                                            }
                                            // 0x004e5c48
                                            charge(ctx, 2);
                                            if (i64(a1) > 0) {
                                                // 0x004e5c50
                                                charge(ctx, 8);
                                                lbu(a1, a3, 0);
                                                a1 = a1 & 0xF;
                                                a1 = sll(a1, 1);
                                                a1 = addu(a0, a1);
                                                lhu(t0, a1, 0);
                                                a1 = t0 & 0x8000;
                                                if (a1 != 0) {
                                                    // 0x004e6b80
                                                    charge(ctx, 11);
                                                    a1 = t0 & 0x7C00;
                                                    a2 = sll(a1, 9);
                                                    a1 = t0 & 0x3E0;
                                                    a2 = a2 | v0;
                                                    a1 = sll(a1, 6);
                                                    a2 = a2 | a1;
                                                    a1 = t0 & 0x1F;
                                                    a1 = sll(a1, 3);
                                                    a1 = a1 | a2;
                                                    sw(a1, t1, 0);
                                                    backedge(ctx);
                                                }
                                                // 0x004e5c70
                                                charge(ctx, 2);
                                                t1 = addiu(t1, 4);
                                            }
                                            // 0x004e5c78
                                            charge(ctx, 6);
                                            lw(a2, s2, 0);
                                            a3 = addu(a3, s3);
                                            t1 = addu(t1, v1);
                                            a1 = addiu(a2, -1);
                                            sw(a1, s2, 0);
                                            if (a2 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x004e5c90
                                        charge(ctx, 2);
                                    }
                                }
                            } else {
                                // 0x004e59d4
                                charge(ctx, 13);
                                lw(v0, fp, 0x0);
                                lw(v1, s4, 24);
                                mult(a0, v1, v0);
                                lw(v1, s4, 4);
                                lw(v0, sp, 0xB0);
                                a0 = addu(v1, a0);
                                mult1(v0, s7, v0);
                                lbu(v1, s4, 35);
                                t6 = addu(a0, v0);
                                v0 = 1;
                                v1 = v1 & 0xF;
                                if (v1 != v0) {
                                    // 0x004e5aa0
                                    charge(ctx, 5);
                                    lw(v1, s2, 0);
                                    lw(t4, s4, 8);
                                    v0 = addiu(v1, -1);
                                    sw(v0, s2, 0);
                                    if (v1 != 0) {
                                        // 0x004e5ab4
                                        charge(ctx, 4);
                                        t3 = sll(s1, 2);
                                        t0 = lui(0xFF00);
                                        a2 = 128;
                                        v1 = 0xFF0000;
                                        for (;;) {
                                            // 0x004e5ac4
                                            charge(ctx, 3);
                                            lw(v0, s0, 0);
                                            t5 = addiu(v0, -1);
                                            if (v0 != 0) {
                                                for (;;) {
                                                    // 0x004e5ad0
                                                    charge(ctx, 16);
                                                    lbu(a3, t6, 0);
                                                    at = 0x7F000000;
                                                    at = at | 0x1;
                                                    v0 = a3 & 0x10;
                                                    a1 = a3 & 0xE7;
                                                    a0 = sra(v0, 1);
                                                    v0 = a3 & 0x8;
                                                    a0 = a1 | a0;
                                                    v0 = sll(v0, 1);
                                                    v0 = v0 | a0;
                                                    v0 = sll(v0, 2);
                                                    v0 = addu(t4, v0);
                                                    lw(t2, v0, 0);
                                                    at = sltu(t2, at);
                                                    if (at != 0) {
                                                        // 0x004e6a58
                                                        charge(ctx, 38);
                                                        lw(a0, t1, 0);
                                                        v0 = t2 & t0;
                                                        a3 = srl(v0, 24);
                                                        a1 = subu(a2, a3);
                                                        v0 = a0 & v1;
                                                        v0 = srl(v0, 16);
                                                        mult(v0, v0, a1);
                                                        v0 = t2 & v1;
                                                        s1 = srl(v0, 16);
                                                        v0 = a0 & t0;
                                                        t7 = srl(v0, 24);
                                                        maddu(v0, a3, s1);
                                                        v0 = v0 & 0x7F80;
                                                        v0 = sll(v0, 9);
                                                        mult1(t7, t7, a1);
                                                        maddu(s1, a3, a3);
                                                        t7 = a0 & 0xFF00;
                                                        t7 = srl(t7, 8);
                                                        s1 = s1 & 0x7F80;
                                                        s1 = sll(s1, 17);
                                                        v0 = addu(s1, v0);
                                                        mult(t7, t7, a1);
                                                        a0 = a0 & 0xFF;
                                                        t7 = t2 & 0xFF00;
                                                        t7 = srl(t7, 8);
                                                        maddu(t7, a3, t7);
                                                        t7 = t7 & 0x7F80;
                                                        t7 = sll(t7, 1);
                                                        t7 = addu(t7, v0);
                                                        mult1(v0, a0, a1);
                                                        v0 = t2 & 0xFF;
                                                        maddu(v0, a3, v0);
                                                        v0 = v0 & 0x7F80;
                                                        v0 = srl(v0, 7);
                                                        v0 = addu(v0, t7);
                                                        sw(v0, t1, 0);
                                                        backedge(ctx);
                                                    } else {
                                                        // 0x004e5b10
                                                        charge(ctx, 2);
                                                        sw(t2, t1, 0);
                                                    }
                                                    // 0x004e5b18
                                                    charge(ctx, 5);
                                                    v0 = t5;
                                                    t1 = addiu(t1, 4);
                                                    t6 = addiu(t6, 1);
                                                    t5 = addiu(t5, -1);
                                                    if (v0 == 0) {
                                                        break;
                                                    }
                                                    backedge(ctx);
                                                }
                                                // 0x004e5b2c
                                                charge(ctx, 1);
                                            }
                                            // 0x004e5b30
                                            charge(ctx, 6);
                                            lw(a0, s2, 0);
                                            t6 = addu(t6, s3);
                                            t1 = addu(t1, t3);
                                            v0 = addiu(a0, -1);
                                            sw(v0, s2, 0);
                                            if (a0 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x004e5b48
                                        charge(ctx, 2);
                                    }
                                } else {
                                    // 0x004e5a08
                                    charge(ctx, 5);
                                    lw(a0, s2, 0);
                                    lw(v1, s4, 8);
                                    v0 = addiu(a0, -1);
                                    sw(v0, s2, 0);
                                    if (a0 != 0) {
                                        // 0x004e5a1c
                                        charge(ctx, 2);
                                        v0 = sll(s1, 2);
                                        t0 = lui(0x8000);
                                        for (;;) {
                                            // 0x004e5a24
                                            charge(ctx, 3);
                                            lw(a1, s0, 0);
                                            a0 = addiu(a1, -1);
                                            if (a1 != 0) {
                                                for (;;) {
                                                    // 0x004e5a30
                                                    charge(ctx, 14);
                                                    lbu(t2, t6, 0);
                                                    a1 = t2 & 0x10;
                                                    a3 = t2 & 0xE7;
                                                    a2 = sra(a1, 1);
                                                    a1 = t2 & 0x8;
                                                    a2 = a3 | a2;
                                                    a1 = sll(a1, 1);
                                                    a1 = a1 | a2;
                                                    a1 = sll(a1, 1);
                                                    a1 = addu(v1, a1);
                                                    lhu(t2, a1, 0);
                                                    a1 = t2 & 0x8000;
                                                    if (a1 != 0) {
                                                        // 0x004e6a28
                                                        charge(ctx, 11);
                                                        a2 = t2 & 0x7C00;
                                                        a1 = t2 & 0x3E0;
                                                        a3 = sll(a2, 9);
                                                        a2 = sll(a1, 6);
                                                        a3 = a3 | t0;
                                                        a1 = t2 & 0x1F;
                                                        a2 = a3 | a2;
                                                        a1 = sll(a1, 3);
                                                        a1 = a1 | a2;
                                                        sw(a1, t1, 0);
                                                        backedge(ctx);
                                                    }
                                                    // 0x004e5a68
                                                    charge(ctx, 5);
                                                    a1 = a0;
                                                    t1 = addiu(t1, 4);
                                                    t6 = addiu(t6, 1);
                                                    a0 = addiu(a0, -1);
                                                    if (a1 == 0) {
                                                        break;
                                                    }
                                                    backedge(ctx);
                                                }
                                                // 0x004e5a7c
                                                charge(ctx, 1);
                                            }
                                            // 0x004e5a80
                                            charge(ctx, 6);
                                            lw(a1, s2, 0);
                                            t6 = addu(t6, s3);
                                            t1 = addu(t1, v0);
                                            a0 = addiu(a1, -1);
                                            sw(a0, s2, 0);
                                            if (a1 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x004e5a98
                                        charge(ctx, 2);
                                    }
                                }
                            }
                            // 0x004e5f20
                            charge(ctx, 2);
                            if (s5 == 0) {
                                // 0x004e5f28
                                charge(ctx, 4);
                                a0 = s4;
                                jal(ctx, 0x4E5F28u, gen::fn_sub_4CDE00_004cde00);
                            }
                            goto L_004e69a8;
                        }
                        // 0x004e575c
                        charge(ctx, 3);
                        a1 = 42;
                        if (a3 == a1) {
                            // 0x004e58d8
                            charge(ctx, 19);
                            a1 = addiu(sp, 0xC4);
                            lw(a1, a1, 0);
                            mult(a1, v0, a1);
                            lw(a0, a0, 0);
                            lw(v0, sp, 0xC0);
                            a1 = addu(a0, a1);
                            mult1(a0, s6, v0);
                            lw(v0, fp, 0x0);
                            a0 = addu(a1, a0);
                            mult(a1, v1, v0);
                            lw(v1, s4, 4);
                            lw(v0, sp, 0xB0);
                            v1 = addu(v1, a1);
                            mult1(v0, s7, v0);
                            lw(a1, s2, 0);
                            v0 = addu(v1, v0);
                            v1 = addiu(a1, -1);
                            sw(v1, s2, 0);
                            if (a1 != 0) {
                                // 0x004e5924
                                charge(ctx, 3);
                                t2 = sll(s3, 1);
                                t1 = sll(s1, 2);
                                a3 = lui(0x8000);
                                for (;;) {
                                    // 0x004e5930
                                    charge(ctx, 3);
                                    lw(v1, s0, 0);
                                    t3 = addiu(v1, -1);
                                    if (v1 != 0) {
                                        // 0x004e593c
                                        charge(ctx, 1);
                                        for (;;) {
                                            // 0x004e5940
                                            charge(ctx, 4);
                                            lhu(t0, v0, 0);
                                            v1 = t0 & 0x8000;
                                            if (v1 != 0) {
                                                // 0x004e69e0
                                                charge(ctx, 11);
                                                a1 = t0 & 0x7C00;
                                                v1 = t0 & 0x3E0;
                                                a2 = sll(a1, 9);
                                                a1 = sll(v1, 6);
                                                a2 = a2 | a3;
                                                v1 = t0 & 0x1F;
                                                a1 = a2 | a1;
                                                v1 = sll(v1, 3);
                                                v1 = v1 | a1;
                                                sw(v1, a0, 0);
                                                backedge(ctx);
                                            }
                                            // 0x004e5950
                                            charge(ctx, 5);
                                            v1 = t3;
                                            a0 = addiu(a0, 4);
                                            v0 = addiu(v0, 2);
                                            t3 = addiu(t3, -1);
                                            if (v1 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x004e5964
                                        charge(ctx, 1);
                                    }
                                    // 0x004e5968
                                    charge(ctx, 6);
                                    lw(a1, s2, 0);
                                    v0 = addu(v0, t2);
                                    a0 = addu(a0, t1);
                                    v1 = addiu(a1, -1);
                                    sw(v1, s2, 0);
                                    if (a1 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004e5980
                                charge(ctx, 2);
                            }
                            goto L_004e69a8;
                        }
                        // 0x004e5768
                        charge(ctx, 3);
                        a1 = 44;
                        if (a3 == a1) {
                            // 0x004e577c
                            charge(ctx, 19);
                            a1 = addiu(sp, 0xC4);
                            lw(a1, a1, 0);
                            mult(a1, v0, a1);
                            lw(a0, a0, 0);
                            lw(v0, sp, 0xC0);
                            a1 = addu(a0, a1);
                            mult1(a0, s6, v0);
                            lw(v0, fp, 0x0);
                            t3 = addu(a1, a0);
                            mult(a0, v1, v0);
                            lw(v1, s4, 4);
                            lw(v0, sp, 0xB0);
                            a0 = addu(v1, a0);
                            mult1(v0, s7, v0);
                            lw(v1, s2, 0);
                            t4 = addu(a0, v0);
                            v0 = addiu(v1, -1);
                            sw(v0, s2, 0);
                            if (v1 != 0) {
                                // 0x004e57c8
                                charge(ctx, 5);
                                t2 = sll(s3, 2);
                                t1 = sll(s1, 2);
                                a3 = lui(0xFF00);
                                a1 = 128;
                                v0 = 0xFF0000;
                                for (;;) {
                                    // 0x004e57dc
                                    charge(ctx, 3);
                                    lw(v1, s0, 0);
                                    t5 = addiu(v1, -1);
                                    if (v1 != 0) {
                                        for (;;) {
                                            // 0x004e57e8
                                            charge(ctx, 6);
                                            lw(t0, t4, 0);
                                            at = 0x7F000000;
                                            at = at | 0x1;
                                            at = sltu(t0, at);
                                            if (at != 0) {
                                                // 0x004e5808
                                                charge(ctx, 38);
                                                v1 = t0 & a3;
                                                a2 = srl(v1, 24);
                                                t6 = t0 & v0;
                                                lw(v1, t3, 0);
                                                t6 = srl(t6, 16);
                                                a0 = subu(a1, a2);
                                                mult(t6, t6, a2);
                                                t7 = v1 & v0;
                                                t6 = v1 & a3;
                                                t7 = srl(t7, 16);
                                                t6 = srl(t6, 24);
                                                maddu(t7, t7, a0);
                                                t7 = t7 & 0x7F80;
                                                s1 = sll(t7, 9);
                                                mult1(t6, t6, a0);
                                                maddu(t7, a2, a2);
                                                t6 = t0 & 0xFF00;
                                                t6 = srl(t6, 8);
                                                t7 = t7 & 0x7F80;
                                                t7 = sll(t7, 17);
                                                t7 = addu(t7, s1);
                                                mult(t6, t6, a2);
                                                t0 = t0 & 0xFF;
                                                t6 = v1 & 0xFF00;
                                                t6 = srl(t6, 8);
                                                maddu(t6, t6, a0);
                                                t6 = t6 & 0x7F80;
                                                t6 = sll(t6, 1);
                                                t6 = addu(t6, t7);
                                                mult1(a2, t0, a2);
                                                v1 = v1 & 0xFF;
                                                maddu(v1, v1, a0);
                                                v1 = v1 & 0x7F80;
                                                v1 = srl(v1, 7);
                                                v1 = addu(v1, t6);
                                                sw(v1, t3, 0);
                                            } else {
                                                // 0x004e5800
                                                charge(ctx, 2);
                                                sw(t0, t3, 0);
                                            }
                                            // 0x004e58a0
                                            charge(ctx, 5);
                                            v1 = t5;
                                            t3 = addiu(t3, 4);
                                            t4 = addiu(t4, 4);
                                            t5 = addiu(t5, -1);
                                            if (v1 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x004e58b4
                                        charge(ctx, 1);
                                    }
                                    // 0x004e58b8
                                    charge(ctx, 6);
                                    lw(a0, s2, 0);
                                    t4 = addu(t4, t2);
                                    t3 = addu(t3, t1);
                                    v1 = addiu(a0, -1);
                                    sw(v1, s2, 0);
                                    if (a0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004e58d0
                                charge(ctx, 2);
                            }
                            goto L_004e69a8;
                        }
                        // 0x004e5774
                        charge(ctx, 2);
                        v0 = 0;
                        // 0x004e69b4
                        charge(ctx, 2);
                        // 0x004e6d28 (the shared epilogue, written out on this path)
                        charge(ctx, 12);
                        ld(ra, sp, 0xA0);
                        lq(fp, sp, 0x90);
                        lq(s7, sp, 0x80);
                        lq(s6, sp, 0x70);
                        lq(s5, sp, 0x60);
                        lq(s4, sp, 0x50);
                        lq(s3, sp, 0x40);
                        lq(s2, sp, 0x30);
                        lq(s1, sp, 0x20);
                        lq(s0, sp, 0x10);
                        sp = addiu(sp, 0xD0);
                        return;
                    }
                L_004e69d8:
                    charge(ctx, 2);
                    v0 = 0;
                }
            }
        }
    } else {
        // 0x004e5424
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004e6d28 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0xD0);
}

// sub_4E6D60 [skyRasterRenderScaled] -- draws a raster scaled into a rectangle (standard function 18)
// ($a0 = the destination context, $a1 = the source raster, $a2 = a rectangle / point record; standard function 18 via
// 0x960100) The source raster is made resident in the GS texture cache (RpSkyTexCacheAccessRaster); a raster whose
// upload description is out of date is set up again (sub_4E4E90); the sprite is built in the DMA packet layer between
// DIntr and EIntr (sub_4E4180 / sub_4E4560 / sub_4E46C0, _rwDMAAddPURef keeps the raster's packets referenced while the
// DMA runs); a sub-raster draws through its parent (sub_4CDE00 / sub_4CE200). The driver's raster extension lives at
// raster + gp 0x7CEAA8; the PS2 driver globals at 0x7CEAE0 / 0x7CEAE8 / 0x7CEAF0 hold the current context, its
// frame-buffer description and the packet state.
// 0x004E6D60 sub_4E6D60 -- 6312 bytes; frame 0x100: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq)
void sub_4E6D60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004e6d60
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    lw(v0, gp, -16968);  // 0x7CEAA8
    v0 = addu(a0, v0);
    sw(v0, sp, 0xD0);
    lbu(v0, v0, 54);
    v0 = v0 & 0x6;
    s7 = a0;
    if (v0 != 0) {
        // 0x004e6da8
        charge(ctx, 2);
        v0 = 0;
        goto L_004e85d8;
    }
    // 0x004e6db0
    charge(ctx, 30);
    v0 = addiu(sp, 0xE4);
    sw(zero, sp, 0xE0);
    sw(zero, v0, 0);
    s6 = addiu(sp, 0xEC);
    lw(v1, s7, 12);
    v0 = addiu(sp, 0xE8);
    lw(a2, gp, -16896);  // 0x7CEAF0
    t2 = addiu(sp, 0xF4);
    s2 = addiu(sp, 0xFC);
    a0 = addiu(sp, 0xE0);
    sw(v1, v0, 0);
    lw(v0, s7, 16);
    sw(v0, s6, 0);
    lh(v1, a2, 28);
    lw(v0, a1, 0);
    v0 = addu(v0, v1);
    sw(v0, sp, 0xF0);
    lh(v1, a2, 30);
    lw(v0, a1, 4);
    v0 = addu(v0, v1);
    sw(v0, t2, 0);
    lw(v1, a1, 8);
    v0 = addiu(sp, 0xF8);
    sw(v1, v0, 0);
    lw(v0, a1, 12);
    sw(v0, s2, 0);
    a1 = addiu(sp, 0xF0);
    jal(ctx, 0x4E6E18u, gen::fn_sub_4E4C20_004e4c20);
    if (v0 != 0) {
        // 0x004e6e28
        charge(ctx, 5);
        lbu(v0, s7, 32);
        v0 = addiu(v0, -1);
        at = sltiu(v0, 2);
        if (at != 0) {
            // 0x004e8010
            charge(ctx, 2);
            v0 = 0;
            goto L_004e85d8;
        }
        // 0x004e6e3c
        charge(ctx, 5);
        lw(v1, gp, -16896);  // 0x7CEAF0
        v0 = 1;
        lbu(a0, v1, 32);
        if (a0 == v0) {
            // 0x004e7ff0
            charge(ctx, 1);
            v0 = 0;
        L_004e7ff4:
            charge(ctx, 2);
            goto L_004e85d8;
        }
        // 0x004e6e50
        charge(ctx, 3);
        v0 = 4;
        if (a0 != v0) {
            // 0x004e6e5c
            charge(ctx, 2);
            if (a0 == 0) {
                goto L_004e7014;
            }
            // 0x004e6e64
            charge(ctx, 3);
            v0 = 2;
            if (a0 != v0) {
                // 0x004e6e70
                charge(ctx, 2);
                v0 = 0;
                goto L_004e7ff4;
            }
            // 0x004e6e78
            charge(ctx, 11);
            v0 = addiu(sp, 0xE4);
            lw(v1, t2, 0);
            lw(fp, s2, 0);
            lw(s3, v0, 0);
            lw(s4, s6, 0);
            s2 = sll(v1, 16);
            s5 = addu(s3, s4);
            jal(ctx, 0x4E6E90u, gen::fn_sub_4E4180_004e4180);
            v1 = subu(s5, s3);
            if (v1 != 0) {
                for (;;) {
                    // 0x004e6ea4
                    charge(ctx, 3);
                    at = sltiu(v1, 65);
                    s1 = v1;
                    if (at == 0) {
                        // 0x004e6eb0
                        charge(ctx, 2);
                        s1 = 64;
                    }
                    // 0x004e6eb8
                    charge(ctx, 5);
                    v0 = addiu(sp, 0xE4);
                    at = sltiu(v1, 65);
                    sw(s3, v0, 0);
                    sw(s1, s6, 0);
                    if (at == 0) {
                        // 0x004e6ecc
                        charge(ctx, 1);
                        s1 = addiu(s1, -1);
                    }
                    // 0x004e6ed0
                    charge(ctx, 57);
                    v0 = sll(s1, 16);
                    mult(v0, v0, fp);
                    lw(v1, gp, -16912);  // 0x7CEAE0
                    divu(v0, s4);
                    v1 = sll(v1, 2);
                    v0 = addiu(gp, -16904);  // &0x7CEAE8
                    v0 = addu(v0, v1);
                    mflo(s0);
                    link(ctx, 0x4E6EF0u);  // $ra first: the delay slot below depends on it
                    lw(a0, v0, 0);
                    call(ctx, gen::fn_sub_4F1540_004f1540);
                    lw(v1, gp, -16912);  // 0x7CEAE0
                    v0 = addiu(gp, -16904);  // &0x7CEAE8
                    a1 = s7;
                    v1 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    lw(a0, v0, 0);
                    a2 = addiu(sp, 0xE0);
                    jal(ctx, 0x4E6F10u, gen::fn_sub_4CE050_004ce050);
                    lw(v1, gp, -16912);  // 0x7CEAE0
                    v0 = addiu(gp, -16904);  // &0x7CEAE8
                    v1 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    link(ctx, 0x4E6F28u);  // $ra first: the delay slot below depends on it
                    lw(a0, v0, 0);
                    call(ctx, gen::fn_sub_4E4E90_004e4e90);
                    lw(v1, gp, -16912);  // 0x7CEAE0
                    v0 = addiu(gp, -16904);  // &0x7CEAE8
                    v1 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    lw(a0, v0, 0);
                    a1 = 0;
                    jal(ctx, 0x4E6F44u, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
                    lw(a0, sp, 0xF0);
                    v0 = addu(s2, s0);
                    v1 = 1;
                    a3 = srl(v0, 16);
                    t0 = 8;
                    v0 = addiu(sp, 0xF8);
                    a1 = srl(s2, 16);
                    t1 = t0;
                    sd(v1, sp, 0x0);
                    lw(a2, v0, 0);
                    v0 = addiu(sp, 0xE8);
                    a2 = addu(a0, a2);
                    lw(v1, v0, 0);
                    lw(v0, s6, 0);
                    v1 = sll(v1, 4);
                    t2 = addiu(v1, -8);
                    v0 = sll(v0, 4);
                    t3 = addiu(v0, -8);
                    jal(ctx, 0x4E6F90u, gen::fn_sub_4E4560_004e4560);
                    lw(v0, gp, -16912);  // 0x7CEAE0
                    s3 = addu(s3, s1);
                    v1 = subu(s5, s3);
                    s2 = addu(s2, s0);
                    v0 = v0 ^ 0x1;
                    sw(v0, gp, -16912);  // 0x7CEAE0
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004e6fb4
                charge(ctx, 1);
            }
            // 0x004e6fb8
            charge(ctx, 19);
            jal(ctx, 0x4E6FB8u, gen::fn_sub_4E46C0_004e46c0);
            jal(ctx, 0x4E6FC0u, gen::fn_DIntr_0050d3a0);
            lw(v0, sp, 0xD0);
            lw(v0, v0, 0);
            v1 = addiu(v0, 1);
            lw(v0, sp, 0xD0);
            link(ctx, 0x4E6FD8u);  // $ra first: the delay slot below depends on it
            sw(v1, v0, 0);
            call(ctx, gen::fn_EIntr_0050d3f0);
            lw(v0, sp, 0xD0);
            v1 = 1;
            lw(v0, v0, 4);
            a0 = addiu(v0, 1);
            lw(v0, sp, 0xD0);
            sw(a0, v0, 4);
            lw(v0, v0, 4);
            if (v0 != v1) {
            L_004e7ffc:
                charge(ctx, 1);
                v0 = 1;
            } else {
                // 0x004e7004
                charge(ctx, 4);
                link(ctx, 0x4E7004u);  // $ra first: the delay slot below depends on it
                lw(a0, sp, 0xD0);
                call(ctx, gen::fn__rwDMAAddPURef_004d51c0);
                v0 = 1;
            }
            // 0x004e8000
            charge(ctx, 2);
            goto L_004e85d8;
        }
    L_004e7014:
        charge(ctx, 3);
        lw(v0, v1, 4);
        a0 = addiu(v1, 4);
        if (v0 != 0) {
            // 0x004e7020
            charge(ctx, 3);
            lw(v0, s7, 4);
            if (v0 == 0) {
                goto L_004e8018;
            }
            // 0x004e702c
            charge(ctx, 36);
            v0 = addiu(sp, 0xE8);
            lw(t1, gp, -16896);  // 0x7CEAF0
            lw(s5, v0, 0);
            lw(a2, sp, 0xF0);
            lw(v1, s7, 20);
            lw(a1, t2, 0);
            lw(s1, s6, 0);
            lh(a3, t1, 28);
            lw(v0, s2, 0);
            lw(t0, t1, 20);
            a2 = subu(a2, a3);
            sq(v0, sp, 0xB0);
            v0 = addiu(sp, 0xF8);
            sw(a2, sp, 0xF0);
            lw(s0, v0, 0);
            lh(a2, t1, 30);
            v0 = addiu(v1, 7);
            v1 = sra(v0, 3);
            a1 = subu(a1, a2);
            lq(v0, sp, 0xB0);
            sw(a1, t2, 0);
            lw(a2, t1, 24);
            lw(a1, t2, 0);
            s4 = subu(0, v0);
            v0 = addiu(t0, 7);
            v0 = sra(v0, 3);
            mult(a2, a2, a1);
            lw(a1, a0, 0);
            lw(a0, sp, 0xF0);
            a2 = addu(a1, a2);
            mult1(a0, v0, a0);
            lw(a1, s7, 20);
            s3 = addu(a2, a0);
            a0 = 4;
            if (a1 != a0) {
                // 0x004e70d8
                charge(ctx, 9);
                a0 = addiu(sp, 0xE4);
                lw(a1, s7, 24);
                lw(a0, a0, 0);
                mult(a2, a1, a0);
                lw(a1, s7, 4);
                lw(a0, sp, 0xE0);
                a1 = addu(a1, a2);
                mult1(a0, v1, a0);
                s6 = addu(a1, a0);
            } else {
                // 0x004e70bc
                charge(ctx, 7);
                a0 = addiu(sp, 0xE4);
                lw(a1, s7, 24);
                lw(a0, a0, 0);
                mult(a1, a1, a0);
                lw(a0, s7, 4);
                s6 = addu(a0, a1);
            }
            // 0x004e70fc
            charge(ctx, 7);
            a1 = sll(v0, 2);
            a0 = 21;
            v0 = addu(a1, v0);
            v0 = sll(v0, 1);
            v1 = addu(v1, v0);
            if (v1 == a0) {
                // 0x004e79f0
                charge(ctx, 5);
                lbu(v0, s7, 34);
                v0 = v0 & 0x2;
                fp = sltu(0, v0);
                if (fp == 0) {
                    // 0x004e8438
                    charge(ctx, 6);
                    a0 = s7;
                    a1 = 0;
                    a2 = 2;
                    jal(ctx, 0x4E8440u, gen::fn_sub_4CE200_004ce200);
                    lw(v1, s7, 20);
                    backedge(ctx);
                } else {
                    // 0x004e7a04
                    charge(ctx, 1);
                    lw(v1, s7, 20);
                }
                // 0x004e7a08
                charge(ctx, 3);
                v0 = 8;
                if (v1 != v0) {
                    // 0x004e7c58
                    charge(ctx, 5);
                    lbu(v1, s7, 35);
                    v0 = 1;
                    v1 = v1 & 0xF;
                    if (v1 != v0) {
                        // 0x004e7d48
                        charge(ctx, 5);
                        lw(a0, s2, 0);
                        lw(v0, s7, 8);
                        v1 = addiu(a0, -1);
                        sw(v1, s2, 0);
                        if (a0 != 0) {
                            // 0x004e7d5c
                            charge(ctx, 6);
                            v1 = subu(0, s0);
                            t3 = lui(0xFF00);
                            sw(v1, sp, 0xC0);
                            t8 = 128;
                            t9 = 0xFF0000;
                            t7 = 0xF80000;
                            for (;;) {
                                // 0x004e7d74
                                charge(ctx, 7);
                                a0 = addiu(sp, 0xF8);
                                lw(v1, sp, 0xE0);
                                lw(a3, a0, 0);
                                a2 = s3;
                                lw(a0, sp, 0xC0);
                                a1 = addiu(a3, -1);
                                if (a3 != 0) {
                                    for (;;) {
                                        // 0x004e7d90
                                        charge(ctx, 3);
                                        a3 = v1 & 0x1;
                                        if (a3 != 0) {
                                            // 0x004e7ea0
                                            charge(ctx, 13);
                                            a3 = srl(v1, 1);
                                            a3 = addu(s6, a3);
                                            at = 0x7F000000;
                                            lbu(a3, a3, 0);
                                            at = at | 0x1;
                                            a3 = sra(a3, 4);
                                            a3 = sll(a3, 2);
                                            a3 = addu(v0, a3);
                                            lw(t2, a3, 0);
                                            a3 = t2 & t3;
                                            at = sltu(a3, at);
                                            if (at != 0) {
                                                // 0x004e7f00
                                                charge(ctx, 38);
                                                t1 = srl(a3, 24);
                                                lhu(a3, a2, 0);
                                                t0 = subu(t8, t1);
                                                t4 = a3 & 0x8000;
                                                t4 = sra(t4, 8);
                                                mult(t6, t4, t0);
                                                mult1(t4, t1, t1);
                                                t5 = addiu(t4, 8192);
                                                t4 = a3 & 0x7C00;
                                                t5 = addu(t6, t5);
                                                t5 = t5 & 0x4000;
                                                t4 = sra(t4, 7);
                                                t5 = sll(t5, 1);
                                                mult(t4, t4, t0);
                                                t6 = a3 & 0x3E0;
                                                t6 = sra(t6, 2);
                                                t4 = t2 & t9;
                                                t4 = srl(t4, 16);
                                                maddu(t4, t1, t4);
                                                t4 = t4 & 0x7C00;
                                                t4 = addu(t5, t4);
                                                mult1(t5, t6, t0);
                                                t5 = a3 & 0x1F;
                                                a3 = t2 & 0xFF00;
                                                t5 = sll(t5, 3);
                                                a3 = srl(a3, 8);
                                                maddu(a3, t1, a3);
                                                a3 = a3 & 0x7C00;
                                                a3 = srl(a3, 5);
                                                a3 = addu(a3, t4);
                                                mult(t0, t5, t0);
                                                t0 = t2 & 0xFF;
                                                maddu(t0, t1, t0);
                                                t0 = t0 & 0x7C00;
                                                t0 = srl(t0, 10);
                                                a3 = addu(t0, a3);
                                                sh(a3, a2, 0);
                                            } else {
                                                // 0x004e7ed4
                                                charge(ctx, 11);
                                                t0 = t2 & t7;
                                                a3 = t2 & 0xF800;
                                                t1 = srl(t0, 9);
                                                t0 = srl(a3, 6);
                                                t1 = t1 | 0x8000;
                                                a3 = t2 & 0xF8;
                                                t0 = t1 | t0;
                                                a3 = srl(a3, 3);
                                                a3 = a3 | t0;
                                                sh(a3, a2, 0);
                                            }
                                        } else {
                                            // 0x004e7d9c
                                            charge(ctx, 13);
                                            a3 = srl(v1, 1);
                                            at = 0x7F000000;
                                            a3 = addu(s6, a3);
                                            at = at | 0x1;
                                            lbu(a3, a3, 0);
                                            a3 = a3 & 0xF;
                                            a3 = sll(a3, 2);
                                            a3 = addu(v0, a3);
                                            lw(t2, a3, 0);
                                            a3 = t2 & t3;
                                            at = sltu(a3, at);
                                            if (at != 0) {
                                                // 0x004e7e00
                                                charge(ctx, 39);
                                                t1 = srl(a3, 24);
                                                lhu(a3, a2, 0);
                                                t0 = subu(t8, t1);
                                                t4 = a3 & 0x8000;
                                                t4 = sra(t4, 8);
                                                mult(t6, t4, t0);
                                                mult1(t4, t1, t1);
                                                t5 = addiu(t4, 8192);
                                                t4 = a3 & 0x7C00;
                                                t5 = addu(t6, t5);
                                                t5 = t5 & 0x4000;
                                                t4 = sra(t4, 7);
                                                t5 = sll(t5, 1);
                                                mult(t4, t4, t0);
                                                t6 = a3 & 0x3E0;
                                                t6 = sra(t6, 2);
                                                t4 = t2 & t9;
                                                t4 = srl(t4, 16);
                                                maddu(t4, t1, t4);
                                                t4 = t4 & 0x7C00;
                                                t4 = addu(t5, t4);
                                                mult1(t5, t6, t0);
                                                t5 = a3 & 0x1F;
                                                a3 = t2 & 0xFF00;
                                                t5 = sll(t5, 3);
                                                a3 = srl(a3, 8);
                                                maddu(a3, t1, a3);
                                                a3 = a3 & 0x7C00;
                                                a3 = srl(a3, 5);
                                                a3 = addu(a3, t4);
                                                mult(t0, t5, t0);
                                                t0 = t2 & 0xFF;
                                                maddu(t0, t1, t0);
                                                t0 = t0 & 0x7C00;
                                                t0 = srl(t0, 10);
                                                a3 = addu(t0, a3);
                                                sh(a3, a2, 0);
                                            } else {
                                                // 0x004e7dd0
                                                charge(ctx, 11);
                                                t0 = t2 & t7;
                                                a3 = t2 & 0xF800;
                                                t1 = srl(t0, 9);
                                                t0 = srl(a3, 6);
                                                t1 = t1 | 0x8000;
                                                a3 = t2 & 0xF8;
                                                t0 = t1 | t0;
                                                a3 = srl(a3, 3);
                                                a3 = a3 | t0;
                                                sh(a3, a2, 0);
                                            }
                                        }
                                        // 0x004e7f98
                                        charge(ctx, 3);
                                        a0 = addu(a0, s5);
                                        a2 = addiu(a2, 2);
                                        if (i64(a0) <= 0) {
                                            // 0x004e8578
                                            charge(ctx, 1);
                                            a3 = a1;
                                        } else {
                                            // 0x004e7fa4
                                            charge(ctx, 1);
                                            for (;;) {
                                                // 0x004e7fa8
                                                charge(ctx, 7);
                                                a0 = subu(a0, s0);
                                                v1 = addiu(v1, 1);
                                                if (i64(a0) <= 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                            // 0x004e7fc4
                                            charge(ctx, 2);
                                            a3 = a1;
                                        }
                                        // 0x004e857c
                                        charge(ctx, 2);
                                        a1 = addiu(a1, -1);
                                        if (a3 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e8584
                                    charge(ctx, 1);
                                }
                                // 0x004e8588
                                charge(ctx, 5);
                                lw(v1, gp, -16896);  // 0x7CEAF0
                                s4 = addu(s4, s1);
                                lw(v1, v1, 24);
                                s3 = addu(s3, v1);
                                if (i64(s4) > 0) {
                                    // 0x004e859c
                                    charge(ctx, 1);
                                    lw(a0, s7, 24);
                                    for (;;) {
                                        // 0x004e85a0
                                        charge(ctx, 7);
                                        lq(v1, sp, 0xB0);
                                        s6 = addu(s6, a0);
                                        s4 = subu(s4, v1);
                                        if (i64(s4) <= 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e85bc
                                    charge(ctx, 1);
                                }
                                // 0x004e85c0
                                charge(ctx, 4);
                                lw(a0, s2, 0);
                                v1 = addiu(a0, -1);
                                sw(v1, s2, 0);
                                if (a0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004e85d0
                            charge(ctx, 2);
                            backedge(ctx);
                        }
                    } else {
                        // 0x004e7c6c
                        charge(ctx, 5);
                        lw(a0, s2, 0);
                        lw(v0, s7, 8);
                        v1 = addiu(a0, -1);
                        sw(v1, s2, 0);
                        if (a0 != 0) {
                            // 0x004e7c80
                            charge(ctx, 1);
                            a1 = subu(0, s0);
                            for (;;) {
                                // 0x004e7c84
                                charge(ctx, 7);
                                v1 = addiu(sp, 0xF8);
                                lw(a3, sp, 0xE0);
                                lw(t0, v1, 0);
                                a2 = s3;
                                v1 = a1;
                                a0 = addiu(t0, -1);
                                if (t0 != 0) {
                                    for (;;) {
                                        // 0x004e7ca0
                                        charge(ctx, 3);
                                        t0 = a3 & 0x1;
                                        if (t0 != 0) {
                                            // 0x004e7ce0
                                            charge(ctx, 10);
                                            t0 = srl(a3, 1);
                                            t0 = addu(s6, t0);
                                            lbu(t0, t0, 0);
                                            t0 = sra(t0, 4);
                                            t0 = sll(t0, 1);
                                            t0 = addu(v0, t0);
                                            lhu(t1, t0, 0);
                                            t0 = t1 & 0x8000;
                                            if (t0 != 0) {
                                                // 0x004e7d08
                                                charge(ctx, 2);
                                                sh(t1, a2, 0);
                                            }
                                        } else {
                                            // 0x004e7cac
                                            charge(ctx, 10);
                                            t0 = srl(a3, 1);
                                            t0 = addu(s6, t0);
                                            lbu(t0, t0, 0);
                                            t0 = t0 & 0xF;
                                            t0 = sll(t0, 1);
                                            t0 = addu(v0, t0);
                                            lhu(t1, t0, 0);
                                            t0 = t1 & 0x8000;
                                            if (t0 != 0) {
                                                // 0x004e7cd4
                                                charge(ctx, 2);
                                                sh(t1, a2, 0);
                                            }
                                        }
                                        // 0x004e7d10
                                        charge(ctx, 3);
                                        v1 = addu(v1, s5);
                                        a2 = addiu(a2, 2);
                                        if (i64(v1) <= 0) {
                                            // 0x004e8518
                                            charge(ctx, 1);
                                            t0 = a0;
                                        } else {
                                            // 0x004e7d1c
                                            charge(ctx, 1);
                                            for (;;) {
                                                // 0x004e7d20
                                                charge(ctx, 7);
                                                v1 = subu(v1, s0);
                                                a3 = addiu(a3, 1);
                                                if (i64(v1) <= 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                            // 0x004e7d3c
                                            charge(ctx, 2);
                                            t0 = a0;
                                        }
                                        // 0x004e851c
                                        charge(ctx, 2);
                                        a0 = addiu(a0, -1);
                                        if (t0 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e8524
                                    charge(ctx, 1);
                                }
                                // 0x004e8528
                                charge(ctx, 5);
                                lw(v1, gp, -16896);  // 0x7CEAF0
                                s4 = addu(s4, s1);
                                lw(v1, v1, 24);
                                s3 = addu(s3, v1);
                                if (i64(s4) > 0) {
                                    // 0x004e853c
                                    charge(ctx, 1);
                                    lw(a0, s7, 24);
                                    for (;;) {
                                        // 0x004e8540
                                        charge(ctx, 7);
                                        lq(v1, sp, 0xB0);
                                        s6 = addu(s6, a0);
                                        s4 = subu(s4, v1);
                                        if (i64(s4) <= 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e855c
                                    charge(ctx, 1);
                                }
                                // 0x004e8560
                                charge(ctx, 4);
                                lw(a0, s2, 0);
                                v1 = addiu(a0, -1);
                                sw(v1, s2, 0);
                                if (a0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004e8570
                            charge(ctx, 2);
                            backedge(ctx);
                        }
                    }
                } else {
                    // 0x004e7a14
                    charge(ctx, 5);
                    lbu(v1, s7, 35);
                    v0 = 1;
                    v1 = v1 & 0xF;
                    if (v1 != v0) {
                        // 0x004e7ad0
                        charge(ctx, 5);
                        lw(v1, s2, 0);
                        lw(a3, s7, 8);
                        v0 = addiu(v1, -1);
                        sw(v0, s2, 0);
                        if (v1 != 0) {
                            // 0x004e7ae4
                            charge(ctx, 4);
                            t9 = subu(0, s0);
                            t7 = 128;
                            t8 = 0xFF0000;
                            a1 = 0xF80000;
                            for (;;) {
                                // 0x004e7af4
                                charge(ctx, 7);
                                v0 = addiu(sp, 0xF8);
                                t3 = s3;
                                lw(v0, v0, 0);
                                t2 = s6;
                                t0 = t9;
                                t1 = addiu(v0, -1);
                                if (v0 != 0) {
                                    for (;;) {
                                        // 0x004e7b10
                                        charge(ctx, 18);
                                        lbu(a2, t2, 0);
                                        at = 0x7F000000;
                                        at = at | 0x1;
                                        v0 = a2 & 0x10;
                                        a0 = a2 & 0xE7;
                                        v1 = sra(v0, 1);
                                        v0 = a2 & 0x8;
                                        v1 = a0 | v1;
                                        v0 = sll(v0, 1);
                                        v0 = v0 | v1;
                                        v0 = sll(v0, 2);
                                        v1 = addu(a3, v0);
                                        lw(a2, v1, 0);
                                        v0 = lui(0xFF00);
                                        v0 = a2 & v0;
                                        at = sltu(v0, at);
                                        if (at != 0) {
                                            // 0x004e7b88
                                            charge(ctx, 38);
                                            a0 = srl(v0, 24);
                                            lhu(v0, t3, 0);
                                            v1 = subu(t7, a0);
                                            t4 = v0 & 0x8000;
                                            t4 = sra(t4, 8);
                                            mult(t6, t4, v1);
                                            mult1(t4, a0, a0);
                                            t5 = addiu(t4, 8192);
                                            t4 = v0 & 0x7C00;
                                            t5 = addu(t6, t5);
                                            t5 = t5 & 0x4000;
                                            t4 = sra(t4, 7);
                                            t5 = sll(t5, 1);
                                            mult(t4, t4, v1);
                                            t6 = v0 & 0x3E0;
                                            t6 = sra(t6, 2);
                                            t4 = a2 & t8;
                                            t4 = srl(t4, 16);
                                            maddu(t4, a0, t4);
                                            t4 = t4 & 0x7C00;
                                            t4 = addu(t5, t4);
                                            mult1(t5, t6, v1);
                                            t5 = v0 & 0x1F;
                                            v0 = a2 & 0xFF00;
                                            t5 = sll(t5, 3);
                                            v0 = srl(v0, 8);
                                            maddu(v0, a0, v0);
                                            v0 = v0 & 0x7C00;
                                            v0 = srl(v0, 5);
                                            v0 = addu(v0, t4);
                                            mult(v1, t5, v1);
                                            v1 = a2 & 0xFF;
                                            maddu(v1, a0, v1);
                                            v1 = v1 & 0x7C00;
                                            v1 = srl(v1, 10);
                                            v0 = addu(v1, v0);
                                            sh(v0, t3, 0);
                                        } else {
                                            // 0x004e7b58
                                            charge(ctx, 12);
                                            lw(v0, v1, 0);
                                            a0 = v0 & a1;
                                            v1 = v0 & 0xF800;
                                            a0 = srl(a0, 9);
                                            v0 = v0 & 0xF8;
                                            v1 = srl(v1, 6);
                                            a0 = a0 | 0x8000;
                                            v1 = a0 | v1;
                                            v0 = srl(v0, 3);
                                            v0 = v0 | v1;
                                            sh(v0, t3, 0);
                                        }
                                        // 0x004e7c20
                                        charge(ctx, 3);
                                        t0 = addu(t0, s5);
                                        t3 = addiu(t3, 2);
                                        if (i64(t0) <= 0) {
                                            // 0x004e84b8
                                            charge(ctx, 1);
                                            v0 = t1;
                                        } else {
                                            // 0x004e7c2c
                                            charge(ctx, 1);
                                            for (;;) {
                                                // 0x004e7c30
                                                charge(ctx, 7);
                                                t0 = subu(t0, s0);
                                                t2 = addiu(t2, 1);
                                                if (i64(t0) <= 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                            // 0x004e7c4c
                                            charge(ctx, 2);
                                            v0 = t1;
                                        }
                                        // 0x004e84bc
                                        charge(ctx, 2);
                                        t1 = addiu(t1, -1);
                                        if (v0 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e84c4
                                    charge(ctx, 1);
                                }
                                // 0x004e84c8
                                charge(ctx, 5);
                                lw(v0, gp, -16896);  // 0x7CEAF0
                                s4 = addu(s4, s1);
                                lw(v0, v0, 24);
                                s3 = addu(s3, v0);
                                if (i64(s4) > 0) {
                                    // 0x004e84dc
                                    charge(ctx, 1);
                                    lw(v1, s7, 24);
                                    for (;;) {
                                        // 0x004e84e0
                                        charge(ctx, 7);
                                        lq(v0, sp, 0xB0);
                                        s6 = addu(s6, v1);
                                        s4 = subu(s4, v0);
                                        if (i64(s4) <= 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e84fc
                                    charge(ctx, 1);
                                }
                                // 0x004e8500
                                charge(ctx, 4);
                                lw(v1, s2, 0);
                                v0 = addiu(v1, -1);
                                sw(v0, s2, 0);
                                if (v1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004e8510
                            charge(ctx, 2);
                            backedge(ctx);
                        }
                    } else {
                        // 0x004e7a28
                        charge(ctx, 5);
                        lw(a0, s2, 0);
                        lw(v0, s7, 8);
                        v1 = addiu(a0, -1);
                        sw(v1, s2, 0);
                        if (a0 != 0) {
                            // 0x004e7a3c
                            charge(ctx, 1);
                            a1 = subu(0, s0);
                            for (;;) {
                                // 0x004e7a40
                                charge(ctx, 7);
                                v1 = addiu(sp, 0xF8);
                                a3 = s3;
                                lw(t0, v1, 0);
                                a2 = s6;
                                v1 = a1;
                                a0 = addiu(t0, -1);
                                if (t0 != 0) {
                                    // 0x004e7a5c
                                    charge(ctx, 1);
                                    for (;;) {
                                        // 0x004e7a60
                                        charge(ctx, 14);
                                        lbu(t3, a2, 0);
                                        t0 = t3 & 0x10;
                                        t2 = t3 & 0xE7;
                                        t1 = sra(t0, 1);
                                        t0 = t3 & 0x8;
                                        t1 = t2 | t1;
                                        t0 = sll(t0, 1);
                                        t0 = t0 | t1;
                                        t0 = sll(t0, 1);
                                        t0 = addu(v0, t0);
                                        lhu(t1, t0, 0);
                                        t0 = t1 & 0x8000;
                                        if (t0 != 0) {
                                            // 0x004e8450
                                            charge(ctx, 2);
                                            sh(t1, a3, 0);
                                            backedge(ctx);
                                        }
                                        // 0x004e7a98
                                        charge(ctx, 3);
                                        v1 = addu(v1, s5);
                                        a3 = addiu(a3, 2);
                                        if (i64(v1) > 0) {
                                            // 0x004e7aa4
                                            charge(ctx, 1);
                                            for (;;) {
                                                // 0x004e7aa8
                                                charge(ctx, 7);
                                                v1 = subu(v1, s0);
                                                a2 = addiu(a2, 1);
                                                if (i64(v1) <= 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                            // 0x004e7ac4
                                            charge(ctx, 2);
                                        }
                                        // 0x004e8458
                                        charge(ctx, 3);
                                        t0 = a0;
                                        a0 = addiu(a0, -1);
                                        if (t0 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e8464
                                    charge(ctx, 1);
                                }
                                // 0x004e8468
                                charge(ctx, 5);
                                lw(v1, gp, -16896);  // 0x7CEAF0
                                s4 = addu(s4, s1);
                                lw(v1, v1, 24);
                                s3 = addu(s3, v1);
                                if (i64(s4) > 0) {
                                    // 0x004e847c
                                    charge(ctx, 1);
                                    lw(a0, s7, 24);
                                    for (;;) {
                                        // 0x004e8480
                                        charge(ctx, 7);
                                        lq(v1, sp, 0xB0);
                                        s6 = addu(s6, a0);
                                        s4 = subu(s4, v1);
                                        if (i64(s4) <= 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e849c
                                    charge(ctx, 1);
                                }
                                // 0x004e84a0
                                charge(ctx, 4);
                                lw(a0, s2, 0);
                                v1 = addiu(a0, -1);
                                sw(v1, s2, 0);
                                if (a0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004e84b0
                            charge(ctx, 2);
                            backedge(ctx);
                        }
                    }
                }
                // 0x004e7fd0
                charge(ctx, 2);
                if (fp == 0) {
                    // 0x004e7fd8
                    charge(ctx, 4);
                    a0 = s7;
                    jal(ctx, 0x4E7FD8u, gen::fn_sub_4CDE00_004cde00);
                }
                goto L_004e7ffc;
            }
            // 0x004e7118
            charge(ctx, 3);
            v0 = 22;
            if (v1 == v0) {
                // 0x004e7978
                charge(ctx, 4);
                lw(v1, s2, 0);
                v0 = addiu(v1, -1);
                sw(v0, s2, 0);
                if (v1 != 0) {
                    // 0x004e7988
                    charge(ctx, 1);
                    a2 = subu(0, s0);
                    for (;;) {
                        // 0x004e798c
                        charge(ctx, 7);
                        v0 = addiu(sp, 0xF8);
                        t0 = s3;
                        lw(v0, v0, 0);
                        a3 = s6;
                        a0 = a2;
                        a1 = addiu(v0, -1);
                        if (v0 != 0) {
                            for (;;) {
                                // 0x004e79a8
                                charge(ctx, 4);
                                lhu(v1, a3, 0);
                                v0 = v1 & 0x8000;
                                if (v0 != 0) {
                                    // 0x004e83d0
                                    charge(ctx, 2);
                                    sh(v1, t0, 0);
                                    backedge(ctx);
                                }
                                // 0x004e79b8
                                charge(ctx, 3);
                                a0 = addu(a0, s5);
                                t0 = addiu(t0, 2);
                                if (i64(a0) > 0) {
                                    // 0x004e79c4
                                    charge(ctx, 1);
                                    for (;;) {
                                        // 0x004e79c8
                                        charge(ctx, 7);
                                        a0 = subu(a0, s0);
                                        a3 = addiu(a3, 2);
                                        if (i64(a0) <= 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e79e4
                                    charge(ctx, 2);
                                }
                                // 0x004e83d8
                                charge(ctx, 3);
                                v0 = a1;
                                a1 = addiu(a1, -1);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004e83e4
                            charge(ctx, 1);
                        }
                        // 0x004e83e8
                        charge(ctx, 5);
                        lw(v0, gp, -16896);  // 0x7CEAF0
                        s4 = addu(s4, s1);
                        lw(v0, v0, 24);
                        s3 = addu(s3, v0);
                        if (i64(s4) > 0) {
                            // 0x004e83fc
                            charge(ctx, 1);
                            lw(v1, s7, 24);
                            for (;;) {
                                // 0x004e8400
                                charge(ctx, 7);
                                lq(v0, sp, 0xB0);
                                s6 = addu(s6, v1);
                                s4 = subu(s4, v0);
                                if (i64(s4) <= 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004e841c
                            charge(ctx, 1);
                        }
                        // 0x004e8420
                        charge(ctx, 4);
                        lw(v1, s2, 0);
                        v0 = addiu(v1, -1);
                        sw(v0, s2, 0);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004e8430
                    charge(ctx, 2);
                    backedge(ctx);
                }
                goto L_004e7ffc;
            }
            // 0x004e7124
            charge(ctx, 3);
            v0 = 24;
            if (v1 == v0) {
                // 0x004e7820
                charge(ctx, 4);
                lw(v1, s2, 0);
                v0 = addiu(v1, -1);
                sw(v0, s2, 0);
                if (v1 != 0) {
                    // 0x004e7830
                    charge(ctx, 5);
                    t8 = subu(0, s0);
                    a0 = 128;
                    t5 = 0xFF0000;
                    a2 = 0xF80000;
                    t9 = lui(0xFF00);
                    for (;;) {
                        // 0x004e7844
                        charge(ctx, 7);
                        v0 = addiu(sp, 0xF8);
                        t3 = s3;
                        lw(v0, v0, 0);
                        t2 = s6;
                        t0 = t8;
                        t1 = addiu(v0, -1);
                        if (v0 != 0) {
                            for (;;) {
                                // 0x004e7860
                                charge(ctx, 7);
                                lw(a3, t2, 0);
                                at = 0x7F000000;
                                at = at | 0x1;
                                v0 = a3 & t9;
                                at = sltu(v0, at);
                                if (at != 0) {
                                    // 0x004e78a8
                                    charge(ctx, 38);
                                    a1 = srl(v0, 24);
                                    lhu(v0, t3, 0);
                                    v1 = subu(a0, a1);
                                    t4 = v0 & 0x8000;
                                    t4 = sra(t4, 8);
                                    mult(t7, t4, v1);
                                    mult1(t4, a1, a1);
                                    t6 = addiu(t4, 8192);
                                    t4 = a3 & t5;
                                    t6 = addu(t6, t7);
                                    t6 = t6 & 0x4000;
                                    t4 = srl(t4, 16);
                                    t6 = sll(t6, 1);
                                    mult(t4, t4, a1);
                                    t7 = a3 & 0xFF00;
                                    t7 = srl(t7, 8);
                                    t4 = v0 & 0x7C00;
                                    t4 = sra(t4, 7);
                                    maddu(t4, t4, v1);
                                    t4 = t4 & 0x7C00;
                                    t4 = addu(t6, t4);
                                    mult1(t6, t7, a1);
                                    t6 = v0 & 0x3E0;
                                    t6 = sra(t6, 2);
                                    v0 = v0 & 0x1F;
                                    maddu(t6, t6, v1);
                                    v0 = sll(v0, 3);
                                    t6 = t6 & 0x7C00;
                                    t6 = srl(t6, 5);
                                    t4 = addu(t6, t4);
                                    mult(v0, v0, v1);
                                    v0 = a3 & 0xFF;
                                    maddu(v0, v0, a1);
                                    v0 = v0 & 0x7C00;
                                    v0 = srl(v0, 10);
                                    v0 = addu(v0, t4);
                                    sh(v0, t3, 0);
                                } else {
                                    // 0x004e787c
                                    charge(ctx, 11);
                                    v1 = a3 & a2;
                                    v0 = a3 & 0xF800;
                                    a1 = srl(v1, 9);
                                    v1 = srl(v0, 6);
                                    a1 = a1 | 0x8000;
                                    v0 = a3 & 0xF8;
                                    v1 = a1 | v1;
                                    v0 = srl(v0, 3);
                                    v0 = v0 | v1;
                                    sh(v0, t3, 0);
                                }
                                // 0x004e7940
                                charge(ctx, 3);
                                t0 = addu(t0, s5);
                                t3 = addiu(t3, 2);
                                if (i64(t0) <= 0) {
                                    // 0x004e8370
                                    charge(ctx, 1);
                                    v0 = t1;
                                } else {
                                    // 0x004e794c
                                    charge(ctx, 1);
                                    for (;;) {
                                        // 0x004e7950
                                        charge(ctx, 7);
                                        t0 = subu(t0, s0);
                                        t2 = addiu(t2, 4);
                                        if (i64(t0) <= 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e796c
                                    charge(ctx, 2);
                                    v0 = t1;
                                }
                                // 0x004e8374
                                charge(ctx, 2);
                                t1 = addiu(t1, -1);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004e837c
                            charge(ctx, 1);
                        }
                        // 0x004e8380
                        charge(ctx, 5);
                        lw(v0, gp, -16896);  // 0x7CEAF0
                        s4 = addu(s4, s1);
                        lw(v0, v0, 24);
                        s3 = addu(s3, v0);
                        if (i64(s4) > 0) {
                            // 0x004e8394
                            charge(ctx, 1);
                            lw(v1, s7, 24);
                            for (;;) {
                                // 0x004e8398
                                charge(ctx, 7);
                                lq(v0, sp, 0xB0);
                                s6 = addu(s6, v1);
                                s4 = subu(s4, v0);
                                if (i64(s4) <= 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004e83b4
                            charge(ctx, 1);
                        }
                        // 0x004e83b8
                        charge(ctx, 4);
                        lw(v1, s2, 0);
                        v0 = addiu(v1, -1);
                        sw(v0, s2, 0);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004e83c8
                    charge(ctx, 2);
                    backedge(ctx);
                }
                goto L_004e7ffc;
            }
            // 0x004e7130
            charge(ctx, 3);
            v0 = 41;
            if (v1 == v0) {
                // 0x004e7308
                charge(ctx, 5);
                lbu(v0, s7, 34);
                v0 = v0 & 0x2;
                fp = sltu(0, v0);
                if (fp == 0) {
                    // 0x004e8110
                    charge(ctx, 6);
                    a0 = s7;
                    a1 = 0;
                    a2 = 2;
                    jal(ctx, 0x4E8118u, gen::fn_sub_4CE200_004ce200);
                    lw(v1, s7, 20);
                    backedge(ctx);
                } else {
                    // 0x004e731c
                    charge(ctx, 1);
                    lw(v1, s7, 20);
                }
                // 0x004e7320
                charge(ctx, 3);
                v0 = 8;
                if (v1 != v0) {
                    // 0x004e74a8
                    charge(ctx, 5);
                    lbu(v1, s7, 35);
                    v0 = 1;
                    v1 = v1 & 0xF;
                    if (v1 != v0) {
                        // 0x004e75e0
                        charge(ctx, 5);
                        lw(v1, s2, 0);
                        lw(a0, s7, 8);
                        v0 = addiu(v1, -1);
                        sw(v0, s2, 0);
                        if (v1 != 0) {
                            // 0x004e75f4
                            charge(ctx, 4);
                            t9 = subu(0, s0);
                            v1 = lui(0xFF00);
                            t8 = 128;
                            v0 = 0xFF0000;
                            for (;;) {
                                // 0x004e7604
                                charge(ctx, 7);
                                a2 = addiu(sp, 0xF8);
                                lw(a1, sp, 0xE0);
                                lw(t1, a2, 0);
                                t0 = s3;
                                a2 = t9;
                                a3 = addiu(t1, -1);
                                if (t1 != 0) {
                                    for (;;) {
                                        // 0x004e7620
                                        charge(ctx, 3);
                                        t1 = a1 & 0x1;
                                        if (t1 != 0) {
                                            // 0x004e7700
                                            charge(ctx, 12);
                                            t1 = srl(a1, 1);
                                            t1 = addu(s6, t1);
                                            at = 0x7F000000;
                                            lbu(t1, t1, 0);
                                            at = at | 0x1;
                                            t1 = sra(t1, 4);
                                            t1 = sll(t1, 2);
                                            t1 = addu(a0, t1);
                                            lw(t6, t1, 0);
                                            at = sltu(t6, at);
                                            if (at != 0) {
                                                // 0x004e7738
                                                charge(ctx, 38);
                                                lw(t3, t0, 0);
                                                t1 = t6 & v1;
                                                t5 = srl(t1, 24);
                                                t4 = subu(t8, t5);
                                                t1 = t3 & v0;
                                                t1 = srl(t1, 16);
                                                mult(t1, t1, t4);
                                                t1 = t6 & v0;
                                                t2 = srl(t1, 16);
                                                maddu(t2, t5, t2);
                                                t1 = t3 & v1;
                                                t1 = srl(t1, 24);
                                                t2 = t2 & 0x7F80;
                                                t2 = sll(t2, 9);
                                                mult1(t1, t1, t4);
                                                maddu(t1, t5, t5);
                                                t7 = t3 & 0xFF00;
                                                t7 = srl(t7, 8);
                                                t1 = t1 & 0x7F80;
                                                t1 = sll(t1, 17);
                                                t1 = addu(t1, t2);
                                                mult(t2, t7, t4);
                                                t2 = t3 & 0xFF;
                                                t3 = t6 & 0xFF00;
                                                t3 = srl(t3, 8);
                                                maddu(t3, t5, t3);
                                                t3 = t3 & 0x7F80;
                                                t3 = sll(t3, 1);
                                                t1 = addu(t3, t1);
                                                mult1(t2, t2, t4);
                                                t2 = t6 & 0xFF;
                                                maddu(t2, t5, t2);
                                                t2 = t2 & 0x7F80;
                                                t2 = srl(t2, 7);
                                                t1 = addu(t2, t1);
                                                sw(t1, t0, 0);
                                            } else {
                                                // 0x004e7730
                                                charge(ctx, 2);
                                                sw(t6, t0, 0);
                                            }
                                        } else {
                                            // 0x004e762c
                                            charge(ctx, 12);
                                            t1 = srl(a1, 1);
                                            at = 0x7F000000;
                                            t1 = addu(s6, t1);
                                            at = at | 0x1;
                                            lbu(t1, t1, 0);
                                            t1 = t1 & 0xF;
                                            t1 = sll(t1, 2);
                                            t1 = addu(a0, t1);
                                            lw(t6, t1, 0);
                                            at = sltu(t6, at);
                                            if (at != 0) {
                                                // 0x004e7668
                                                charge(ctx, 38);
                                                lw(t3, t0, 0);
                                                t1 = t6 & v1;
                                                t5 = srl(t1, 24);
                                                t4 = subu(t8, t5);
                                                t1 = t3 & v0;
                                                t1 = srl(t1, 16);
                                                mult(t1, t1, t4);
                                                t1 = t6 & v0;
                                                t2 = srl(t1, 16);
                                                maddu(t2, t5, t2);
                                                t1 = t3 & v1;
                                                t1 = srl(t1, 24);
                                                t2 = t2 & 0x7F80;
                                                t2 = sll(t2, 9);
                                                mult1(t1, t1, t4);
                                                maddu(t1, t5, t5);
                                                t7 = t3 & 0xFF00;
                                                t7 = srl(t7, 8);
                                                t1 = t1 & 0x7F80;
                                                t1 = sll(t1, 17);
                                                t1 = addu(t1, t2);
                                                mult(t2, t7, t4);
                                                t2 = t3 & 0xFF;
                                                t3 = t6 & 0xFF00;
                                                t3 = srl(t3, 8);
                                                maddu(t3, t5, t3);
                                                t3 = t3 & 0x7F80;
                                                t3 = sll(t3, 1);
                                                t1 = addu(t3, t1);
                                                mult1(t2, t2, t4);
                                                t2 = t6 & 0xFF;
                                                maddu(t2, t5, t2);
                                                t2 = t2 & 0x7F80;
                                                t2 = srl(t2, 7);
                                                t1 = addu(t2, t1);
                                                sw(t1, t0, 0);
                                            } else {
                                                // 0x004e765c
                                                charge(ctx, 2);
                                                sw(t6, t0, 0);
                                            }
                                        }
                                        // 0x004e77d0
                                        charge(ctx, 3);
                                        a2 = addu(a2, s5);
                                        t0 = addiu(t0, 4);
                                        if (i64(a2) <= 0) {
                                            // 0x004e8310
                                            charge(ctx, 1);
                                            t1 = a3;
                                        } else {
                                            // 0x004e77dc
                                            charge(ctx, 1);
                                            for (;;) {
                                                // 0x004e77e0
                                                charge(ctx, 7);
                                                a2 = subu(a2, s0);
                                                a1 = addiu(a1, 1);
                                                if (i64(a2) <= 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                            // 0x004e77fc
                                            charge(ctx, 2);
                                            t1 = a3;
                                        }
                                        // 0x004e8314
                                        charge(ctx, 2);
                                        a3 = addiu(a3, -1);
                                        if (t1 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e831c
                                    charge(ctx, 1);
                                }
                                // 0x004e8320
                                charge(ctx, 5);
                                lw(a1, gp, -16896);  // 0x7CEAF0
                                s4 = addu(s4, s1);
                                lw(a1, a1, 24);
                                s3 = addu(s3, a1);
                                if (i64(s4) > 0) {
                                    // 0x004e8334
                                    charge(ctx, 1);
                                    lw(a2, s7, 24);
                                    for (;;) {
                                        // 0x004e8338
                                        charge(ctx, 7);
                                        lq(a1, sp, 0xB0);
                                        s6 = addu(s6, a2);
                                        s4 = subu(s4, a1);
                                        if (i64(s4) <= 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e8354
                                    charge(ctx, 1);
                                }
                                // 0x004e8358
                                charge(ctx, 4);
                                lw(a2, s2, 0);
                                a1 = addiu(a2, -1);
                                sw(a1, s2, 0);
                                if (a2 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004e8368
                            charge(ctx, 2);
                            backedge(ctx);
                        }
                    } else {
                        // 0x004e74bc
                        charge(ctx, 5);
                        lw(v1, s2, 0);
                        lw(a0, s7, 8);
                        v0 = addiu(v1, -1);
                        sw(v0, s2, 0);
                        if (v1 != 0) {
                            // 0x004e74d0
                            charge(ctx, 2);
                            a3 = subu(0, s0);
                            v1 = lui(0x8000);
                            for (;;) {
                                // 0x004e74d8
                                charge(ctx, 7);
                                v0 = addiu(sp, 0xF8);
                                lw(t1, sp, 0xE0);
                                lw(v0, v0, 0);
                                t0 = s3;
                                a1 = a3;
                                a2 = addiu(v0, -1);
                                if (v0 != 0) {
                                    // 0x004e74f4
                                    charge(ctx, 1);
                                    for (;;) {
                                        // 0x004e74f8
                                        charge(ctx, 3);
                                        v0 = t1 & 0x1;
                                        if (v0 != 0) {
                                            // 0x004e7558
                                            charge(ctx, 10);
                                            v0 = srl(t1, 1);
                                            v0 = addu(s6, v0);
                                            lbu(v0, v0, 0);
                                            v0 = sra(v0, 4);
                                            v0 = sll(v0, 1);
                                            v0 = addu(a0, v0);
                                            lhu(v0, v0, 0);
                                            t2 = v0 & 0x8000;
                                            if (t2 != 0) {
                                                // 0x004e7580
                                                charge(ctx, 10);
                                                t3 = v0 & 0x7C00;
                                                t2 = v0 & 0x3E0;
                                                t3 = sll(t3, 9);
                                                v0 = v0 & 0x1F;
                                                t2 = sll(t2, 6);
                                                t3 = t3 | v1;
                                                t2 = t3 | t2;
                                                v0 = sll(v0, 3);
                                                v0 = v0 | t2;
                                                sw(v0, t0, 0);
                                            }
                                        } else {
                                            // 0x004e7504
                                            charge(ctx, 10);
                                            v0 = srl(t1, 1);
                                            v0 = addu(s6, v0);
                                            lbu(v0, v0, 0);
                                            v0 = v0 & 0xF;
                                            v0 = sll(v0, 1);
                                            v0 = addu(a0, v0);
                                            lhu(v0, v0, 0);
                                            t2 = v0 & 0x8000;
                                            if (t2 != 0) {
                                                // 0x004e752c
                                                charge(ctx, 11);
                                                t3 = v0 & 0x7C00;
                                                t2 = v0 & 0x3E0;
                                                t3 = sll(t3, 9);
                                                v0 = v0 & 0x1F;
                                                t2 = sll(t2, 6);
                                                t3 = t3 | v1;
                                                t2 = t3 | t2;
                                                v0 = sll(v0, 3);
                                                v0 = v0 | t2;
                                                sw(v0, t0, 0);
                                            }
                                        }
                                        // 0x004e75a8
                                        charge(ctx, 3);
                                        a1 = addu(a1, s5);
                                        t0 = addiu(t0, 4);
                                        if (i64(a1) <= 0) {
                                            // 0x004e82b0
                                            charge(ctx, 1);
                                            v0 = a2;
                                        } else {
                                            // 0x004e75b4
                                            charge(ctx, 1);
                                            for (;;) {
                                                // 0x004e75b8
                                                charge(ctx, 7);
                                                a1 = subu(a1, s0);
                                                t1 = addiu(t1, 1);
                                                if (i64(a1) <= 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                            // 0x004e75d4
                                            charge(ctx, 2);
                                            v0 = a2;
                                        }
                                        // 0x004e82b4
                                        charge(ctx, 2);
                                        a2 = addiu(a2, -1);
                                        if (v0 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e82bc
                                    charge(ctx, 1);
                                }
                                // 0x004e82c0
                                charge(ctx, 5);
                                lw(v0, gp, -16896);  // 0x7CEAF0
                                s4 = addu(s4, s1);
                                lw(v0, v0, 24);
                                s3 = addu(s3, v0);
                                if (i64(s4) > 0) {
                                    // 0x004e82d4
                                    charge(ctx, 1);
                                    lw(a1, s7, 24);
                                    for (;;) {
                                        // 0x004e82d8
                                        charge(ctx, 7);
                                        lq(v0, sp, 0xB0);
                                        s6 = addu(s6, a1);
                                        s4 = subu(s4, v0);
                                        if (i64(s4) <= 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e82f4
                                    charge(ctx, 1);
                                }
                                // 0x004e82f8
                                charge(ctx, 4);
                                lw(a1, s2, 0);
                                v0 = addiu(a1, -1);
                                sw(v0, s2, 0);
                                if (a1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004e8308
                            charge(ctx, 2);
                            backedge(ctx);
                        }
                    }
                } else {
                    // 0x004e732c
                    charge(ctx, 5);
                    lbu(v1, s7, 35);
                    v0 = 1;
                    v1 = v1 & 0xF;
                    if (v1 != v0) {
                        // 0x004e73e8
                        charge(ctx, 5);
                        lw(v1, s2, 0);
                        lw(t7, s7, 8);
                        v0 = addiu(v1, -1);
                        sw(v0, s2, 0);
                        if (v1 != 0) {
                            // 0x004e73fc
                            charge(ctx, 4);
                            t9 = subu(0, s0);
                            t0 = lui(0xFF00);
                            t8 = 128;
                            a0 = 0xFF0000;
                            for (;;) {
                                // 0x004e740c
                                charge(ctx, 7);
                                v0 = addiu(sp, 0xF8);
                                t5 = s3;
                                lw(v0, v0, 0);
                                t4 = s6;
                                t2 = t9;
                                t3 = addiu(v0, -1);
                                if (v0 != 0) {
                                    for (;;) {
                                        // 0x004e7428
                                        charge(ctx, 16);
                                        lbu(a2, t4, 0);
                                        at = 0x7F000000;
                                        at = at | 0x1;
                                        v0 = a2 & 0x10;
                                        a1 = a2 & 0xE7;
                                        v1 = sra(v0, 1);
                                        v0 = a2 & 0x8;
                                        v1 = a1 | v1;
                                        v0 = sll(v0, 1);
                                        v0 = v0 | v1;
                                        v0 = sll(v0, 2);
                                        v0 = addu(t7, v0);
                                        lw(t1, v0, 0);
                                        at = sltu(t1, at);
                                        if (at != 0) {
                                            // 0x004e81b8
                                            charge(ctx, 38);
                                            lw(a1, t5, 0);
                                            v0 = t1 & t0;
                                            a3 = srl(v0, 24);
                                            a2 = subu(t8, a3);
                                            v0 = a1 & a0;
                                            v0 = srl(v0, 16);
                                            mult(v0, v0, a2);
                                            v0 = t1 & a0;
                                            v1 = srl(v0, 16);
                                            maddu(v1, a3, v1);
                                            v0 = a1 & t0;
                                            v0 = srl(v0, 24);
                                            v1 = v1 & 0x7F80;
                                            v1 = sll(v1, 9);
                                            mult1(v0, v0, a2);
                                            maddu(v0, a3, a3);
                                            t6 = a1 & 0xFF00;
                                            t6 = srl(t6, 8);
                                            v0 = v0 & 0x7F80;
                                            v0 = sll(v0, 17);
                                            v0 = addu(v0, v1);
                                            mult(v1, t6, a2);
                                            v1 = a1 & 0xFF;
                                            a1 = t1 & 0xFF00;
                                            a1 = srl(a1, 8);
                                            maddu(a1, a3, a1);
                                            a1 = a1 & 0x7F80;
                                            a1 = sll(a1, 1);
                                            v0 = addu(a1, v0);
                                            mult1(v1, v1, a2);
                                            v1 = t1 & 0xFF;
                                            maddu(v1, a3, v1);
                                            v1 = v1 & 0x7F80;
                                            v1 = srl(v1, 7);
                                            v0 = addu(v1, v0);
                                            sw(v0, t5, 0);
                                            backedge(ctx);
                                        } else {
                                            // 0x004e7468
                                            charge(ctx, 2);
                                            sw(t1, t5, 0);
                                        }
                                        // 0x004e7470
                                        charge(ctx, 3);
                                        t2 = addu(t2, s5);
                                        t5 = addiu(t5, 4);
                                        if (i64(t2) > 0) {
                                            // 0x004e747c
                                            charge(ctx, 1);
                                            for (;;) {
                                                // 0x004e7480
                                                charge(ctx, 7);
                                                t2 = subu(t2, s0);
                                                t4 = addiu(t4, 1);
                                                if (i64(t2) <= 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                            // 0x004e749c
                                            charge(ctx, 2);
                                        }
                                        // 0x004e8250
                                        charge(ctx, 3);
                                        v0 = t3;
                                        t3 = addiu(t3, -1);
                                        if (v0 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e825c
                                    charge(ctx, 1);
                                }
                                // 0x004e8260
                                charge(ctx, 5);
                                lw(v0, gp, -16896);  // 0x7CEAF0
                                s4 = addu(s4, s1);
                                lw(v0, v0, 24);
                                s3 = addu(s3, v0);
                                if (i64(s4) > 0) {
                                    // 0x004e8274
                                    charge(ctx, 1);
                                    lw(v1, s7, 24);
                                    for (;;) {
                                        // 0x004e8278
                                        charge(ctx, 7);
                                        lq(v0, sp, 0xB0);
                                        s6 = addu(s6, v1);
                                        s4 = subu(s4, v0);
                                        if (i64(s4) <= 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e8294
                                    charge(ctx, 1);
                                }
                                // 0x004e8298
                                charge(ctx, 4);
                                lw(v1, s2, 0);
                                v0 = addiu(v1, -1);
                                sw(v0, s2, 0);
                                if (v1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004e82a8
                            charge(ctx, 2);
                            backedge(ctx);
                        }
                    } else {
                        // 0x004e7340
                        charge(ctx, 5);
                        lw(v1, s2, 0);
                        lw(a0, s7, 8);
                        v0 = addiu(v1, -1);
                        sw(v0, s2, 0);
                        if (v1 != 0) {
                            // 0x004e7354
                            charge(ctx, 2);
                            a3 = subu(0, s0);
                            v0 = lui(0x8000);
                            for (;;) {
                                // 0x004e735c
                                charge(ctx, 7);
                                v1 = addiu(sp, 0xF8);
                                t1 = s3;
                                lw(v1, v1, 0);
                                t0 = s6;
                                a1 = a3;
                                a2 = addiu(v1, -1);
                                if (v1 != 0) {
                                    for (;;) {
                                        // 0x004e7378
                                        charge(ctx, 14);
                                        lbu(t4, t0, 0);
                                        v1 = t4 & 0x10;
                                        t3 = t4 & 0xE7;
                                        t2 = sra(v1, 1);
                                        v1 = t4 & 0x8;
                                        t2 = t3 | t2;
                                        v1 = sll(v1, 1);
                                        v1 = v1 | t2;
                                        v1 = sll(v1, 1);
                                        v1 = addu(a0, v1);
                                        lhu(v1, v1, 0);
                                        t2 = v1 & 0x8000;
                                        if (t2 != 0) {
                                            // 0x004e8128
                                            charge(ctx, 11);
                                            t3 = v1 & 0x7C00;
                                            t2 = v1 & 0x3E0;
                                            t3 = sll(t3, 9);
                                            v1 = v1 & 0x1F;
                                            t2 = sll(t2, 6);
                                            t3 = t3 | v0;
                                            t2 = t3 | t2;
                                            v1 = sll(v1, 3);
                                            v1 = v1 | t2;
                                            sw(v1, t1, 0);
                                            backedge(ctx);
                                        }
                                        // 0x004e73b0
                                        charge(ctx, 3);
                                        a1 = addu(a1, s5);
                                        t1 = addiu(t1, 4);
                                        if (i64(a1) > 0) {
                                            // 0x004e73bc
                                            charge(ctx, 1);
                                            for (;;) {
                                                // 0x004e73c0
                                                charge(ctx, 7);
                                                a1 = subu(a1, s0);
                                                t0 = addiu(t0, 1);
                                                if (i64(a1) <= 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                            // 0x004e73dc
                                            charge(ctx, 2);
                                        }
                                        // 0x004e8158
                                        charge(ctx, 3);
                                        v1 = a2;
                                        a2 = addiu(a2, -1);
                                        if (v1 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e8164
                                    charge(ctx, 1);
                                }
                                // 0x004e8168
                                charge(ctx, 5);
                                lw(v1, gp, -16896);  // 0x7CEAF0
                                s4 = addu(s4, s1);
                                lw(v1, v1, 24);
                                s3 = addu(s3, v1);
                                if (i64(s4) > 0) {
                                    // 0x004e817c
                                    charge(ctx, 1);
                                    lw(a1, s7, 24);
                                    for (;;) {
                                        // 0x004e8180
                                        charge(ctx, 7);
                                        lq(v1, sp, 0xB0);
                                        s6 = addu(s6, a1);
                                        s4 = subu(s4, v1);
                                        if (i64(s4) <= 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e819c
                                    charge(ctx, 1);
                                }
                                // 0x004e81a0
                                charge(ctx, 4);
                                lw(a1, s2, 0);
                                v1 = addiu(a1, -1);
                                sw(v1, s2, 0);
                                if (a1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004e81b0
                            charge(ctx, 2);
                            backedge(ctx);
                        }
                    }
                }
                // 0x004e7808
                charge(ctx, 2);
                if (fp == 0) {
                    // 0x004e7810
                    charge(ctx, 4);
                    a0 = s7;
                    jal(ctx, 0x4E7810u, gen::fn_sub_4CDE00_004cde00);
                }
                goto L_004e7ffc;
            }
            // 0x004e713c
            charge(ctx, 3);
            v0 = 42;
            if (v1 == v0) {
                // 0x004e7288
                charge(ctx, 4);
                lw(v1, s2, 0);
                v0 = addiu(v1, -1);
                sw(v0, s2, 0);
                if (v1 != 0) {
                    // 0x004e7298
                    charge(ctx, 2);
                    a1 = subu(0, s0);
                    v0 = lui(0x8000);
                    for (;;) {
                        // 0x004e72a0
                        charge(ctx, 7);
                        v1 = addiu(sp, 0xF8);
                        a3 = s3;
                        lw(t0, v1, 0);
                        a2 = s6;
                        v1 = a1;
                        a0 = addiu(t0, -1);
                        if (t0 != 0) {
                            // 0x004e72bc
                            charge(ctx, 1);
                            for (;;) {
                                // 0x004e72c0
                                charge(ctx, 4);
                                lhu(t3, a2, 0);
                                t0 = t3 & 0x8000;
                                if (t0 != 0) {
                                    // 0x004e8080
                                    charge(ctx, 11);
                                    t1 = t3 & 0x7C00;
                                    t0 = t3 & 0x3E0;
                                    t2 = sll(t1, 9);
                                    t1 = sll(t0, 6);
                                    t2 = t2 | v0;
                                    t0 = t3 & 0x1F;
                                    t1 = t2 | t1;
                                    t0 = sll(t0, 3);
                                    t0 = t0 | t1;
                                    sw(t0, a3, 0);
                                    backedge(ctx);
                                }
                                // 0x004e72d0
                                charge(ctx, 3);
                                v1 = addu(v1, s5);
                                a3 = addiu(a3, 4);
                                if (i64(v1) > 0) {
                                    // 0x004e72dc
                                    charge(ctx, 1);
                                    for (;;) {
                                        // 0x004e72e0
                                        charge(ctx, 7);
                                        v1 = subu(v1, s0);
                                        a2 = addiu(a2, 2);
                                        if (i64(v1) <= 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e72fc
                                    charge(ctx, 2);
                                }
                                // 0x004e80b0
                                charge(ctx, 3);
                                t0 = a0;
                                a0 = addiu(a0, -1);
                                if (t0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004e80bc
                            charge(ctx, 1);
                        }
                        // 0x004e80c0
                        charge(ctx, 5);
                        lw(v1, gp, -16896);  // 0x7CEAF0
                        s4 = addu(s4, s1);
                        lw(v1, v1, 24);
                        s3 = addu(s3, v1);
                        if (i64(s4) > 0) {
                            // 0x004e80d4
                            charge(ctx, 1);
                            lw(a0, s7, 24);
                            for (;;) {
                                // 0x004e80d8
                                charge(ctx, 7);
                                lq(v1, sp, 0xB0);
                                s6 = addu(s6, a0);
                                s4 = subu(s4, v1);
                                if (i64(s4) <= 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004e80f4
                            charge(ctx, 1);
                        }
                        // 0x004e80f8
                        charge(ctx, 4);
                        lw(a0, s2, 0);
                        v1 = addiu(a0, -1);
                        sw(v1, s2, 0);
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004e8108
                    charge(ctx, 2);
                    backedge(ctx);
                }
                goto L_004e7ffc;
            }
            // 0x004e7148
            charge(ctx, 3);
            v0 = 44;
            if (v1 == v0) {
                // 0x004e715c
                charge(ctx, 4);
                lw(v1, s2, 0);
                v0 = addiu(v1, -1);
                sw(v0, s2, 0);
                if (v1 != 0) {
                    // 0x004e716c
                    charge(ctx, 4);
                    t8 = subu(0, s0);
                    t1 = lui(0xFF00);
                    a3 = 128;
                    a0 = 0xFF0000;
                    for (;;) {
                        // 0x004e717c
                        charge(ctx, 7);
                        v0 = addiu(sp, 0xF8);
                        t4 = s3;
                        lw(v0, v0, 0);
                        t3 = s6;
                        t5 = t8;
                        t6 = addiu(v0, -1);
                        if (v0 != 0) {
                            for (;;) {
                                // 0x004e7198
                                charge(ctx, 6);
                                lw(t2, t3, 0);
                                at = 0x7F000000;
                                at = at | 0x1;
                                at = sltu(t2, at);
                                if (at != 0) {
                                    // 0x004e71b8
                                    charge(ctx, 38);
                                    v0 = t2 & t1;
                                    t0 = srl(v0, 24);
                                    lw(a1, t4, 0);
                                    v0 = t2 & a0;
                                    a2 = subu(a3, t0);
                                    v0 = srl(v0, 16);
                                    mult(v0, v0, t0);
                                    v1 = a1 & a0;
                                    v1 = srl(v1, 16);
                                    v0 = a1 & t1;
                                    maddu(v1, v1, a2);
                                    v0 = srl(v0, 24);
                                    v1 = v1 & 0x7F80;
                                    v1 = sll(v1, 9);
                                    mult1(v0, v0, a2);
                                    maddu(v0, t0, t0);
                                    t7 = t2 & 0xFF00;
                                    t7 = srl(t7, 8);
                                    v0 = v0 & 0x7F80;
                                    v0 = sll(v0, 17);
                                    v0 = addu(v0, v1);
                                    mult(v1, t7, t0);
                                    v1 = t2 & 0xFF;
                                    t2 = a1 & 0xFF00;
                                    t2 = srl(t2, 8);
                                    maddu(t2, t2, a2);
                                    t2 = t2 & 0x7F80;
                                    t2 = sll(t2, 1);
                                    v0 = addu(t2, v0);
                                    mult1(v1, v1, t0);
                                    v1 = a1 & 0xFF;
                                    maddu(v1, v1, a2);
                                    v1 = v1 & 0x7F80;
                                    v1 = srl(v1, 7);
                                    v0 = addu(v1, v0);
                                    sw(v0, t4, 0);
                                } else {
                                    // 0x004e71b0
                                    charge(ctx, 2);
                                    sw(t2, t4, 0);
                                }
                                // 0x004e7250
                                charge(ctx, 3);
                                t5 = addu(t5, s5);
                                t4 = addiu(t4, 4);
                                if (i64(t5) <= 0) {
                                    // 0x004e8020
                                    charge(ctx, 1);
                                    v0 = t6;
                                } else {
                                    // 0x004e725c
                                    charge(ctx, 1);
                                    for (;;) {
                                        // 0x004e7260
                                        charge(ctx, 7);
                                        t5 = subu(t5, s0);
                                        t3 = addiu(t3, 4);
                                        if (i64(t5) <= 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e727c
                                    charge(ctx, 2);
                                    v0 = t6;
                                }
                                // 0x004e8024
                                charge(ctx, 2);
                                t6 = addiu(t6, -1);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004e802c
                            charge(ctx, 1);
                        }
                        // 0x004e8030
                        charge(ctx, 5);
                        lw(v0, gp, -16896);  // 0x7CEAF0
                        s4 = addu(s4, s1);
                        lw(v0, v0, 24);
                        s3 = addu(s3, v0);
                        if (i64(s4) > 0) {
                            // 0x004e8044
                            charge(ctx, 1);
                            lw(v1, s7, 24);
                            for (;;) {
                                // 0x004e8048
                                charge(ctx, 7);
                                lq(v0, sp, 0xB0);
                                s6 = addu(s6, v1);
                                s4 = subu(s4, v0);
                                if (i64(s4) <= 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004e8064
                            charge(ctx, 1);
                        }
                        // 0x004e8068
                        charge(ctx, 4);
                        lw(v1, s2, 0);
                        v0 = addiu(v1, -1);
                        sw(v0, s2, 0);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004e8078
                    charge(ctx, 2);
                    backedge(ctx);
                }
                goto L_004e7ffc;
            }
            // 0x004e7154
            charge(ctx, 2);
            v0 = 0;
            // 0x004e7fe8
            charge(ctx, 2);
            ld(ra, sp, 0xA0);
            // 0x004e85dc (the shared epilogue, written out on this path)
            charge(ctx, 11);
            lq(fp, sp, 0x90);
            lq(s7, sp, 0x80);
            lq(s6, sp, 0x70);
            lq(s5, sp, 0x60);
            lq(s4, sp, 0x50);
            lq(s3, sp, 0x40);
            lq(s2, sp, 0x30);
            lq(s1, sp, 0x20);
            lq(s0, sp, 0x10);
            sp = addiu(sp, 0x100);
            return;
        }
    L_004e8018:
        charge(ctx, 2);
        v0 = 0;
        goto L_004e85d8;
    }
    // 0x004e8008
    charge(ctx, 2);
    v0 = 1;
L_004e85d8:
    charge(ctx, 1);
    ld(ra, sp, 0xA0);
    // 0x004e85dc (the shared epilogue, written out on this path)
    charge(ctx, 11);
    lq(fp, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x100);
}

// sub_4E8610 [skyRasterRenderFast] -- the fast raster draw (standard function 19)
// ($a0 = the destination context, $a1 = the source raster, $a2 = a rectangle / point record; standard function 19 via
// 0x960104) The source raster is made resident in the GS texture cache (RpSkyTexCacheAccessRaster); a raster whose
// upload description is out of date is set up again (sub_4E4E90); the sprite is built in the DMA packet layer between
// DIntr and EIntr (sub_4E4180 / sub_4E4560 / sub_4E46C0, _rwDMAAddPURef keeps the raster's packets referenced while the
// DMA runs); a sub-raster draws through its parent (sub_4CDE00 / sub_4CE200). The driver's raster extension lives at
// raster + gp 0x7CEAA8; the PS2 driver globals at 0x7CEAE0 / 0x7CEAE8 / 0x7CEAF0 hold the current context, its
// frame-buffer description and the packet state.
// 0x004E8610 sub_4E8610 -- 4208 bytes; frame 0xD0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq)
void sub_4E8610(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004e8610
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    lw(v0, gp, -16968);  // 0x7CEAA8
    fp = addu(a0, v0);
    lbu(v0, fp, 0x36);
    v0 = v0 & 0x6;
    s4 = a0;
    if (v0 == 0) {
        // 0x004e865c
        charge(ctx, 30);
        s6 = addiu(sp, 0xB4);
        sw(zero, sp, 0xB0);
        sw(zero, s6, 0);
        v0 = addiu(sp, 0xB8);
        lw(v1, s4, 12);
        s7 = addiu(sp, 0xBC);
        lw(a2, gp, -16896);  // 0x7CEAF0
        s1 = addiu(sp, 0xC8);
        s2 = addiu(sp, 0xCC);
        a0 = addiu(sp, 0xB0);
        sw(v1, v0, 0);
        lw(v0, s4, 16);
        sw(v0, s7, 0);
        lh(v1, a2, 28);
        lw(v0, a1, 0);
        v0 = addu(v0, v1);
        sw(v0, sp, 0xC0);
        lw(v0, a1, 4);
        lh(v1, a2, 30);
        a1 = addiu(sp, 0xC0);
        v1 = addu(v0, v1);
        v0 = addiu(sp, 0xC4);
        sw(v1, v0, 0);
        lw(v0, s4, 12);
        sw(v0, s1, 0);
        lw(v0, s4, 16);
        link(ctx, 0x4E86C4u);  // $ra first: the delay slot below depends on it
        sw(v0, s2, 0);
        call(ctx, gen::fn_sub_4E4A90_004e4a90);
        if (v0 == 0) {
            // 0x004e93d4
            charge(ctx, 2);
            v0 = 1;
        } else {
            // 0x004e86d4
            charge(ctx, 5);
            lbu(v0, s4, 32);
            v0 = addiu(v0, -1);
            at = sltiu(v0, 2);
            if (at != 0) {
                // 0x004e93dc
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004e86e8
                charge(ctx, 5);
                lw(v0, gp, -16896);  // 0x7CEAF0
                v1 = 1;
                lbu(a0, v0, 32);
                if (a0 == v1) {
                    // 0x004e93e4
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x004e86fc
                    charge(ctx, 2);
                    if (a0 == v1) {
                        // 0x004e93bc
                        charge(ctx, 1);
                        v0 = 0;
                    L_004e93c0:
                        charge(ctx, 2);
                    } else {
                        // 0x004e8704
                        charge(ctx, 3);
                        v1 = 4;
                        if (a0 != v1) {
                            // 0x004e8710
                            charge(ctx, 2);
                            if (a0 == 0) {
                                goto L_004e888c;
                            }
                            // 0x004e8718
                            charge(ctx, 3);
                            v0 = 2;
                            if (a0 != v0) {
                                // 0x004e8724
                                charge(ctx, 2);
                                v0 = 0;
                                goto L_004e93c0;
                            }
                            // 0x004e872c
                            charge(ctx, 9);
                            v0 = addiu(sp, 0xC4);
                            lw(s3, s6, 0);
                            lw(s2, v0, 0);
                            lw(v0, s7, 0);
                            s5 = addu(s3, v0);
                            jal(ctx, 0x4E873Cu, gen::fn_sub_4E4180_004e4180);
                            v1 = subu(s5, s3);
                            if (v1 != 0) {
                                for (;;) {
                                    // 0x004e8750
                                    charge(ctx, 3);
                                    at = sltiu(v1, 65);
                                    s0 = v1;
                                    if (at == 0) {
                                        // 0x004e875c
                                        charge(ctx, 1);
                                        s0 = 64;
                                    }
                                    // 0x004e8760
                                    charge(ctx, 4);
                                    at = sltiu(v1, 65);
                                    sw(s3, s6, 0);
                                    sw(s0, s7, 0);
                                    if (at == 0) {
                                        // 0x004e8770
                                        charge(ctx, 2);
                                        s0 = addiu(s0, -1);
                                    }
                                    // 0x004e8778
                                    charge(ctx, 50);
                                    lw(v1, gp, -16912);  // 0x7CEAE0
                                    v0 = addiu(gp, -16904);  // &0x7CEAE8
                                    v1 = sll(v1, 2);
                                    v0 = addu(v0, v1);
                                    link(ctx, 0x4E8788u);  // $ra first: the delay slot below depends on it
                                    lw(a0, v0, 0);
                                    call(ctx, gen::fn_sub_4F1540_004f1540);
                                    lw(v1, gp, -16912);  // 0x7CEAE0
                                    v0 = addiu(gp, -16904);  // &0x7CEAE8
                                    a1 = s4;
                                    v1 = sll(v1, 2);
                                    v0 = addu(v0, v1);
                                    lw(a0, v0, 0);
                                    a2 = addiu(sp, 0xB0);
                                    jal(ctx, 0x4E87A8u, gen::fn_sub_4CE050_004ce050);
                                    lw(v1, gp, -16912);  // 0x7CEAE0
                                    v0 = addiu(gp, -16904);  // &0x7CEAE8
                                    v1 = sll(v1, 2);
                                    v0 = addu(v0, v1);
                                    link(ctx, 0x4E87C0u);  // $ra first: the delay slot below depends on it
                                    lw(a0, v0, 0);
                                    call(ctx, gen::fn_sub_4E4E90_004e4e90);
                                    lw(v1, gp, -16912);  // 0x7CEAE0
                                    v0 = addiu(gp, -16904);  // &0x7CEAE8
                                    v1 = sll(v1, 2);
                                    v0 = addu(v0, v1);
                                    lw(a0, v0, 0);
                                    a1 = 0;
                                    jal(ctx, 0x4E87DCu, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
                                    lw(a0, sp, 0xC0);
                                    t0 = 8;
                                    v0 = addiu(sp, 0xB8);
                                    a3 = addu(s2, s0);
                                    a1 = s2;
                                    t1 = t0;
                                    sd(zero, sp, 0x0);
                                    lw(v1, v0, 0);
                                    lw(a2, s1, 0);
                                    lw(v0, s7, 0);
                                    v1 = sll(v1, 4);
                                    a2 = addu(a0, a2);
                                    t2 = addiu(v1, -8);
                                    v0 = sll(v0, 4);
                                    t3 = addiu(v0, -8);
                                    jal(ctx, 0x4E881Cu, gen::fn_sub_4E4560_004e4560);
                                    lw(v0, gp, -16912);  // 0x7CEAE0
                                    s3 = addu(s3, s0);
                                    v1 = subu(s5, s3);
                                    s2 = addu(s2, s0);
                                    v0 = v0 ^ 0x1;
                                    sw(v0, gp, -16912);  // 0x7CEAE0
                                    if (v1 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                            }
                            // 0x004e8840
                            charge(ctx, 15);
                            jal(ctx, 0x4E8840u, gen::fn_sub_4E46C0_004e46c0);
                            jal(ctx, 0x4E8848u, gen::fn_DIntr_0050d3a0);
                            lw(v0, fp, 0x0);
                            v0 = addiu(v0, 1);
                            link(ctx, 0x4E8858u);  // $ra first: the delay slot below depends on it
                            sw(v0, fp, 0x0);
                            call(ctx, gen::fn_EIntr_0050d3f0);
                            lw(v1, fp, 0x4);
                            v0 = 1;
                            v1 = addiu(v1, 1);
                            sw(v1, fp, 0x4);
                            lw(v1, fp, 0x4);
                            if (v1 != v0) {
                            L_004e93c8:
                                charge(ctx, 1);
                                v0 = 1;
                            } else {
                                // 0x004e887c
                                charge(ctx, 4);
                                a0 = fp;
                                jal(ctx, 0x4E887Cu, gen::fn__rwDMAAddPURef_004d51c0);
                                v0 = 1;
                            }
                            // 0x004e93cc
                            charge(ctx, 2);
                            // 0x004e9650 (the shared epilogue, written out on this path)
                            charge(ctx, 12);
                            ld(ra, sp, 0xA0);
                            lq(fp, sp, 0x90);
                            lq(s7, sp, 0x80);
                            lq(s6, sp, 0x70);
                            lq(s5, sp, 0x60);
                            lq(s4, sp, 0x50);
                            lq(s3, sp, 0x40);
                            lq(s2, sp, 0x30);
                            lq(s1, sp, 0x20);
                            lq(s0, sp, 0x10);
                            sp = addiu(sp, 0xD0);
                            return;
                        }
                    L_004e888c:
                        charge(ctx, 3);
                        lw(v1, v0, 4);
                        a1 = addiu(v0, 4);
                        if (v1 != 0) {
                            // 0x004e8898
                            charge(ctx, 3);
                            lw(v1, s4, 4);
                            if (v1 == 0) {
                                goto L_004e93ec;
                            }
                            // 0x004e88a4
                            charge(ctx, 21);
                            v1 = addiu(sp, 0xC4);
                            lw(t2, gp, -16896);  // 0x7CEAF0
                            lw(t0, s4, 20);
                            a2 = 4;
                            lw(a0, v1, 0);
                            lw(a3, sp, 0xC0);
                            lw(t1, t2, 20);
                            v1 = addiu(t0, 7);
                            lh(t0, t2, 28);
                            fp = sra(v1, 3);
                            v1 = addiu(t2, 20);
                            t1 = addiu(t1, 7);
                            a3 = subu(a3, t0);
                            sw(a3, sp, 0xC0);
                            lh(a3, t2, 30);
                            a3 = subu(a0, a3);
                            a0 = addiu(sp, 0xC4);
                            sw(a3, a0, 0);
                            lw(a0, s4, 20);
                            s7 = sra(t1, 3);
                            if (a0 != a2) {
                                // 0x004e8930
                                charge(ctx, 5);
                                lw(a0, s4, 24);
                                lw(a2, s1, 0);
                                divu(a0, fp);
                                mflo(a3);
                                s3 = subu(a3, a2);
                            } else {
                                // 0x004e88f8
                                charge(ctx, 4);
                                lw(a2, s1, 0);
                                lw(a0, s4, 24);
                                a3 = sra(a2, 1);
                                if (i64(a2) < 0) {
                                    // 0x004e8908
                                    charge(ctx, 2);
                                    a3 = addiu(a2, 1);
                                    a3 = sra(a3, 1);
                                }
                                // 0x004e8910
                                charge(ctx, 6);
                                s3 = subu(a0, a3);
                                lw(a3, sp, 0xB0);
                                a3 = a3 & 0x1;
                                a3 = a3 & a2;
                                if (a3 != 0) {
                                    // 0x004e8928
                                    charge(ctx, 2);
                                    s3 = addiu(s3, -1);
                                }
                            }
                            // 0x004e8944
                            charge(ctx, 10);
                            lw(v0, v0, 24);
                            a3 = sll(s7, 2);
                            a3 = addu(a3, s7);
                            a3 = sll(a3, 1);
                            t0 = addu(fp, a3);
                            a3 = 21;
                            divu(v0, s7);
                            mflo(t1);
                            s5 = subu(t1, a2);
                            if (t0 == a3) {
                                // 0x004e8f24
                                charge(ctx, 5);
                                lbu(v0, s4, 34);
                                v0 = v0 & 0x2;
                                s0 = sltu(0, v0);
                                if (s0 == 0) {
                                    // 0x004e95a8
                                    charge(ctx, 6);
                                    a0 = s4;
                                    a1 = 0;
                                    a2 = 2;
                                    jal(ctx, 0x4E95B0u, gen::fn_sub_4CE200_004ce200);
                                    lw(a1, gp, -16896);  // 0x7CEAF0
                                    backedge(ctx);
                                } else {
                                    // 0x004e8f38
                                    charge(ctx, 1);
                                    lw(a1, gp, -16896);  // 0x7CEAF0
                                }
                                // 0x004e8f3c
                                charge(ctx, 13);
                                v0 = addiu(sp, 0xC4);
                                lw(v0, v0, 0);
                                lw(v1, a1, 24);
                                mult(a0, v1, v0);
                                lw(v1, a1, 4);
                                lw(v0, sp, 0xC0);
                                v1 = addu(v1, a0);
                                mult1(v0, s7, v0);
                                lw(a0, s4, 20);
                                v0 = addu(v1, v0);
                                v1 = 8;
                                if (a0 != v1) {
                                    // 0x004e9110
                                    charge(ctx, 12);
                                    lw(v1, s6, 0);
                                    lw(a0, s4, 24);
                                    mult(a3, a0, v1);
                                    lw(a2, s4, 4);
                                    lw(a1, sp, 0xB0);
                                    lbu(a0, s4, 35);
                                    v1 = 1;
                                    a2 = addu(a2, a3);
                                    a1 = sra(a1, 1);
                                    a0 = a0 & 0xF;
                                    t0 = addu(a2, a1);
                                    if (a0 != v1) {
                                        // 0x004e91c8
                                        charge(ctx, 5);
                                        lw(a0, s2, 0);
                                        lw(a3, s4, 8);
                                        v1 = addiu(a0, -1);
                                        sw(v1, s2, 0);
                                        if (a0 != 0) {
                                            // 0x004e91dc
                                            charge(ctx, 4);
                                            a2 = sll(s5, 1);
                                            a0 = 0x8000;
                                            v1 = 0xF80000;
                                            a1 = 0x40000000;
                                            for (;;) {
                                                // 0x004e91ec
                                                charge(ctx, 4);
                                                lw(t2, sp, 0xB0);
                                                t2 = t2 & 0x1;
                                                lw(t1, s1, 0);
                                                if (t2 != 0) {
                                                    // 0x004e91fc
                                                    charge(ctx, 8);
                                                    lbu(t2, t0, 0);
                                                    t2 = sra(t2, 4);
                                                    t2 = sll(t2, 2);
                                                    t2 = addu(a3, t2);
                                                    lw(t6, t2, 0);
                                                    t2 = sltu(t6, a1);
                                                    if (t2 != 0) {
                                                        // 0x004e9224
                                                        charge(ctx, 1);
                                                        t5 = 0;
                                                    } else {
                                                        // 0x004e921c
                                                        charge(ctx, 2);
                                                        t5 = a0;
                                                    }
                                                    // 0x004e9228
                                                    charge(ctx, 13);
                                                    t3 = t6 & v1;
                                                    t2 = t6 & 0xF800;
                                                    t4 = srl(t3, 9);
                                                    t0 = addiu(t0, 1);
                                                    t3 = srl(t2, 6);
                                                    t4 = t4 | t5;
                                                    t2 = t6 & 0xF8;
                                                    t3 = t3 | t4;
                                                    t2 = srl(t2, 3);
                                                    t1 = addiu(t1, -1);
                                                    t2 = t2 | t3;
                                                    sh(t2, v0, 0);
                                                    v0 = addiu(v0, 2);
                                                }
                                                // 0x004e925c
                                                charge(ctx, 3);
                                                at = sltiu(t1, 2);
                                                if (at == 0) {
                                                    for (;;) {
                                                        // 0x004e9268
                                                        charge(ctx, 8);
                                                        lbu(t2, t0, 0);
                                                        t2 = t2 & 0xF;
                                                        t2 = sll(t2, 2);
                                                        t2 = addu(a3, t2);
                                                        lw(t6, t2, 0);
                                                        t2 = sltu(t6, a1);
                                                        if (t2 != 0) {
                                                            // 0x004e9290
                                                            charge(ctx, 1);
                                                            t5 = 0;
                                                        } else {
                                                            // 0x004e9288
                                                            charge(ctx, 2);
                                                            t5 = a0;
                                                        }
                                                        // 0x004e9294
                                                        charge(ctx, 18);
                                                        t3 = t6 & v1;
                                                        t2 = t6 & 0xF800;
                                                        t4 = srl(t3, 9);
                                                        t3 = srl(t2, 6);
                                                        t4 = t4 | t5;
                                                        t2 = t6 & 0xF8;
                                                        t3 = t3 | t4;
                                                        t2 = srl(t2, 3);
                                                        t2 = t2 | t3;
                                                        sh(t2, v0, 0);
                                                        lbu(t2, t0, 0);
                                                        t2 = sra(t2, 4);
                                                        t2 = sll(t2, 2);
                                                        t2 = addu(a3, t2);
                                                        lw(t6, t2, 0);
                                                        t2 = sltu(t6, a1);
                                                        if (t2 != 0) {
                                                            // 0x004e92e4
                                                            charge(ctx, 1);
                                                            t5 = 0;
                                                        } else {
                                                            // 0x004e92dc
                                                            charge(ctx, 2);
                                                            t5 = a0;
                                                        }
                                                        // 0x004e92e8
                                                        charge(ctx, 15);
                                                        t3 = t6 & v1;
                                                        t1 = addiu(t1, -2);
                                                        t4 = srl(t3, 9);
                                                        t2 = t6 & 0xF800;
                                                        t3 = srl(t2, 6);
                                                        t4 = t4 | t5;
                                                        t2 = t6 & 0xF8;
                                                        t3 = t3 | t4;
                                                        t2 = srl(t2, 3);
                                                        at = sltiu(t1, 2);
                                                        t2 = t2 | t3;
                                                        t0 = addiu(t0, 1);
                                                        sh(t2, v0, 2);
                                                        v0 = addiu(v0, 4);
                                                        if (at != 0) {
                                                            break;
                                                        }
                                                        backedge(ctx);
                                                    }
                                                }
                                                // 0x004e9324
                                                charge(ctx, 2);
                                                if (t1 != 0) {
                                                    // 0x004e932c
                                                    charge(ctx, 8);
                                                    lbu(t1, t0, 0);
                                                    t1 = t1 & 0xF;
                                                    t1 = sll(t1, 2);
                                                    t1 = addu(a3, t1);
                                                    lw(t5, t1, 0);
                                                    t1 = sltu(t5, a1);
                                                    if (t1 != 0) {
                                                        // 0x004e9354
                                                        charge(ctx, 1);
                                                        t4 = 0;
                                                    } else {
                                                        // 0x004e934c
                                                        charge(ctx, 2);
                                                        t4 = a0;
                                                    }
                                                    // 0x004e9358
                                                    charge(ctx, 11);
                                                    t2 = t5 & v1;
                                                    t1 = t5 & 0xF800;
                                                    t3 = srl(t2, 9);
                                                    t2 = srl(t1, 6);
                                                    t3 = t3 | t4;
                                                    t1 = t5 & 0xF8;
                                                    t2 = t2 | t3;
                                                    t1 = srl(t1, 3);
                                                    t1 = t1 | t2;
                                                    sh(t1, v0, 0);
                                                    v0 = addiu(v0, 2);
                                                }
                                                // 0x004e9384
                                                charge(ctx, 6);
                                                lw(t2, s2, 0);
                                                t0 = addu(t0, s3);
                                                v0 = addu(v0, a2);
                                                t1 = addiu(t2, -1);
                                                sw(t1, s2, 0);
                                                if (t2 == 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                        }
                                    } else {
                                        // 0x004e9140
                                        charge(ctx, 5);
                                        lw(a1, s2, 0);
                                        lw(a0, s4, 8);
                                        v1 = addiu(a1, -1);
                                        sw(v1, s2, 0);
                                        if (a1 != 0) {
                                            // 0x004e9154
                                            charge(ctx, 1);
                                            v1 = sll(s5, 1);
                                            for (;;) {
                                                // 0x004e9158
                                                charge(ctx, 4);
                                                lw(a2, sp, 0xB0);
                                                a2 = a2 & 0x1;
                                                lw(a1, s1, 0);
                                                if (a2 != 0) {
                                                    // 0x004e95e0
                                                    charge(ctx, 10);
                                                    lbu(a2, t0, 0);
                                                    a1 = addiu(a1, -1);
                                                    a2 = sra(a2, 4);
                                                    t0 = addiu(t0, 1);
                                                    a2 = sll(a2, 1);
                                                    a2 = addu(a0, a2);
                                                    lhu(a2, a2, 0);
                                                    sh(a2, v0, 0);
                                                    v0 = addiu(v0, 2);
                                                    backedge(ctx);
                                                }
                                                // 0x004e9168
                                                charge(ctx, 3);
                                                at = sltiu(a1, 2);
                                                if (at == 0) {
                                                    // 0x004e9174
                                                    charge(ctx, 1);
                                                    for (;;) {
                                                        // 0x004e9178
                                                        charge(ctx, 17);
                                                        lbu(a2, t0, 0);
                                                        a1 = addiu(a1, -2);
                                                        at = sltiu(a1, 2);
                                                        a2 = a2 & 0xF;
                                                        a2 = sll(a2, 1);
                                                        a2 = addu(a0, a2);
                                                        lhu(a2, a2, 0);
                                                        sh(a2, v0, 0);
                                                        lbu(a2, t0, 0);
                                                        a2 = sra(a2, 4);
                                                        t0 = addiu(t0, 1);
                                                        a2 = sll(a2, 1);
                                                        a2 = addu(a0, a2);
                                                        lhu(a2, a2, 0);
                                                        sh(a2, v0, 2);
                                                        v0 = addiu(v0, 4);
                                                        if (at != 0) {
                                                            break;
                                                        }
                                                        backedge(ctx);
                                                    }
                                                    // 0x004e91bc
                                                    charge(ctx, 2);
                                                }
                                                // 0x004e9608
                                                charge(ctx, 2);
                                                if (a1 != 0) {
                                                    // 0x004e9630
                                                    charge(ctx, 8);
                                                    lbu(a1, t0, 0);
                                                    a1 = a1 & 0xF;
                                                    a1 = sll(a1, 1);
                                                    a1 = addu(a0, a1);
                                                    lhu(a1, a1, 0);
                                                    sh(a1, v0, 0);
                                                    v0 = addiu(v0, 2);
                                                    backedge(ctx);
                                                }
                                                // 0x004e9610
                                                charge(ctx, 6);
                                                lw(a2, s2, 0);
                                                t0 = addu(t0, s3);
                                                v0 = addu(v0, v1);
                                                a1 = addiu(a2, -1);
                                                sw(a1, s2, 0);
                                                if (a2 == 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                            // 0x004e9628
                                            charge(ctx, 2);
                                            backedge(ctx);
                                        }
                                    }
                                } else {
                                    // 0x004e8f70
                                    charge(ctx, 13);
                                    lw(v1, s6, 0);
                                    lw(a0, s4, 24);
                                    mult(a1, a0, v1);
                                    lw(a0, s4, 4);
                                    lw(v1, sp, 0xB0);
                                    a1 = addu(a0, a1);
                                    mult1(v1, fp, v1);
                                    lbu(a0, s4, 35);
                                    t3 = addu(a1, v1);
                                    v1 = 1;
                                    a0 = a0 & 0xF;
                                    if (a0 != v1) {
                                        // 0x004e9018
                                        charge(ctx, 5);
                                        lw(a0, s2, 0);
                                        lw(t1, s4, 8);
                                        v1 = addiu(a0, -1);
                                        sw(v1, s2, 0);
                                        if (a0 != 0) {
                                            // 0x004e902c
                                            charge(ctx, 4);
                                            t0 = sll(s5, 1);
                                            a1 = 0x8000;
                                            v1 = 0xF80000;
                                            a2 = 0x40000000;
                                            for (;;) {
                                                // 0x004e903c
                                                charge(ctx, 3);
                                                lw(a0, s1, 0);
                                                t2 = addiu(a0, -1);
                                                if (a0 != 0) {
                                                    for (;;) {
                                                        // 0x004e9048
                                                        charge(ctx, 14);
                                                        lbu(a3, t3, 0);
                                                        a0 = a3 & 0x10;
                                                        t5 = a3 & 0xE7;
                                                        t4 = sra(a0, 1);
                                                        a0 = a3 & 0x8;
                                                        t4 = t5 | t4;
                                                        a0 = sll(a0, 1);
                                                        a0 = a0 | t4;
                                                        a0 = sll(a0, 2);
                                                        a0 = addu(t1, a0);
                                                        lw(a0, a0, 0);
                                                        a0 = sltu(a0, a2);
                                                        if (a0 != 0) {
                                                            // 0x004e9088
                                                            charge(ctx, 1);
                                                            a0 = 0;
                                                        } else {
                                                            // 0x004e9080
                                                            charge(ctx, 2);
                                                            a0 = a1;
                                                        }
                                                        // 0x004e908c
                                                        charge(ctx, 25);
                                                        t4 = a3 & 0x10;
                                                        t5 = a3 & 0xE7;
                                                        t4 = sra(t4, 1);
                                                        a3 = a3 & 0x8;
                                                        t4 = t5 | t4;
                                                        a3 = sll(a3, 1);
                                                        a3 = a3 | t4;
                                                        t3 = addiu(t3, 1);
                                                        t4 = sll(a3, 2);
                                                        t4 = addu(t1, t4);
                                                        a3 = t2;
                                                        lw(t6, t4, 0);
                                                        t2 = addiu(t2, -1);
                                                        t5 = t6 & v1;
                                                        t4 = t6 & 0xF800;
                                                        t5 = srl(t5, 9);
                                                        t4 = srl(t4, 6);
                                                        t5 = t5 | a0;
                                                        a0 = t6 & 0xF8;
                                                        t4 = t4 | t5;
                                                        a0 = srl(a0, 3);
                                                        a0 = a0 | t4;
                                                        sh(a0, v0, 0);
                                                        v0 = addiu(v0, 2);
                                                        if (a3 == 0) {
                                                            break;
                                                        }
                                                        backedge(ctx);
                                                    }
                                                }
                                                // 0x004e90f0
                                                charge(ctx, 6);
                                                lw(a3, s2, 0);
                                                t3 = addu(t3, s3);
                                                v0 = addu(v0, t0);
                                                a0 = addiu(a3, -1);
                                                sw(a0, s2, 0);
                                                if (a3 == 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                            // 0x004e9108
                                            charge(ctx, 2);
                                        }
                                    } else {
                                        // 0x004e8fa4
                                        charge(ctx, 5);
                                        lw(a1, s2, 0);
                                        lw(a0, s4, 8);
                                        v1 = addiu(a1, -1);
                                        sw(v1, s2, 0);
                                        if (a1 != 0) {
                                            // 0x004e8fb8
                                            charge(ctx, 1);
                                            v1 = sll(s5, 1);
                                            for (;;) {
                                                // 0x004e8fbc
                                                charge(ctx, 3);
                                                lw(a1, s1, 0);
                                                t2 = addiu(a1, -1);
                                                if (a1 == 0) {
                                                    // 0x004e95c0
                                                    charge(ctx, 1);
                                                    lw(a2, s2, 0);
                                                } else {
                                                    for (;;) {
                                                        // 0x004e8fc8
                                                        charge(ctx, 17);
                                                        lbu(t1, t3, 0);
                                                        a1 = t2;
                                                        t2 = addiu(t2, -1);
                                                        a2 = t1 & 0x10;
                                                        t0 = t1 & 0xE7;
                                                        a3 = sra(a2, 1);
                                                        t3 = addiu(t3, 1);
                                                        a2 = t1 & 0x8;
                                                        a3 = t0 | a3;
                                                        a2 = sll(a2, 1);
                                                        a2 = a2 | a3;
                                                        a2 = sll(a2, 1);
                                                        a2 = addu(a0, a2);
                                                        lhu(a2, a2, 0);
                                                        sh(a2, v0, 0);
                                                        v0 = addiu(v0, 2);
                                                        if (a1 == 0) {
                                                            break;
                                                        }
                                                        backedge(ctx);
                                                    }
                                                    // 0x004e900c
                                                    charge(ctx, 2);
                                                    lw(a2, s2, 0);
                                                }
                                                // 0x004e95c4
                                                charge(ctx, 5);
                                                t3 = addu(t3, s3);
                                                v0 = addu(v0, v1);
                                                a1 = addiu(a2, -1);
                                                sw(a1, s2, 0);
                                                if (a2 == 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                            // 0x004e95d8
                                            charge(ctx, 2);
                                            backedge(ctx);
                                        }
                                    }
                                }
                                // 0x004e939c
                                charge(ctx, 2);
                                if (s0 == 0) {
                                    // 0x004e93a4
                                    charge(ctx, 4);
                                    a0 = s4;
                                    jal(ctx, 0x4E93A4u, gen::fn_sub_4CDE00_004cde00);
                                }
                                goto L_004e93c8;
                            }
                            // 0x004e896c
                            charge(ctx, 3);
                            a2 = 24;
                            if (t0 == a2) {
                                // 0x004e8e40
                                charge(ctx, 19);
                                v1 = addiu(sp, 0xC4);
                                lw(v1, v1, 0);
                                mult(a2, v0, v1);
                                lw(v1, a1, 0);
                                lw(v0, sp, 0xC0);
                                a1 = addu(v1, a2);
                                mult1(v1, s7, v0);
                                lw(v0, s6, 0);
                                a3 = addu(a1, v1);
                                mult(a0, a0, v0);
                                lw(v1, s4, 4);
                                lw(v0, sp, 0xB0);
                                a0 = addu(v1, a0);
                                mult1(v0, fp, v0);
                                lw(v1, s2, 0);
                                a2 = addu(a0, v0);
                                v0 = addiu(v1, -1);
                                sw(v0, s2, 0);
                                if (v1 != 0) {
                                    // 0x004e8e8c
                                    charge(ctx, 5);
                                    a0 = sll(s3, 2);
                                    v1 = sll(s5, 1);
                                    t5 = 0x8000;
                                    t3 = 0xF80000;
                                    v0 = 0x40000000;
                                    for (;;) {
                                        // 0x004e8ea0
                                        charge(ctx, 3);
                                        lw(t0, s1, 0);
                                        a1 = addiu(t0, -1);
                                        if (t0 != 0) {
                                            for (;;) {
                                                // 0x004e8eac
                                                charge(ctx, 4);
                                                lw(t6, a2, 0);
                                                t0 = sltu(t6, v0);
                                                if (t0 != 0) {
                                                    // 0x004e8ec4
                                                    charge(ctx, 1);
                                                    t4 = 0;
                                                } else {
                                                    // 0x004e8ebc
                                                    charge(ctx, 2);
                                                    t4 = t5;
                                                }
                                                // 0x004e8ec8
                                                charge(ctx, 15);
                                                t1 = t6 & t3;
                                                t0 = t6 & 0xF800;
                                                t2 = srl(t1, 9);
                                                a2 = addiu(a2, 4);
                                                t1 = srl(t0, 6);
                                                t2 = t2 | t4;
                                                t0 = t6 & 0xF8;
                                                t1 = t1 | t2;
                                                t0 = srl(t0, 3);
                                                t0 = t0 | t1;
                                                sh(t0, a3, 0);
                                                t0 = a1;
                                                a3 = addiu(a3, 2);
                                                a1 = addiu(a1, -1);
                                                if (t0 == 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                        }
                                        // 0x004e8f04
                                        charge(ctx, 6);
                                        lw(t0, s2, 0);
                                        a2 = addu(a2, a0);
                                        a3 = addu(a3, v1);
                                        a1 = addiu(t0, -1);
                                        sw(a1, s2, 0);
                                        if (t0 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e8f1c
                                    charge(ctx, 2);
                                }
                                goto L_004e93c8;
                            }
                            // 0x004e8978
                            charge(ctx, 3);
                            a2 = 41;
                            if (t0 != a2) {
                                // 0x004e8984
                                charge(ctx, 3);
                                a2 = 42;
                                if (t0 == a2) {
                                    // 0x004e8a48
                                    charge(ctx, 19);
                                    v1 = addiu(sp, 0xC4);
                                    lw(v1, v1, 0);
                                    mult(a2, v0, v1);
                                    lw(v1, a1, 0);
                                    lw(v0, sp, 0xC0);
                                    a1 = addu(v1, a2);
                                    mult1(v1, s7, v0);
                                    lw(v0, s6, 0);
                                    v1 = addu(a1, v1);
                                    mult(a1, a0, v0);
                                    lw(a0, s4, 4);
                                    lw(v0, sp, 0xB0);
                                    a0 = addu(a0, a1);
                                    mult1(v0, fp, v0);
                                    lw(a1, s2, 0);
                                    v0 = addu(a0, v0);
                                    a0 = addiu(a1, -1);
                                    sw(a0, s2, 0);
                                    if (a1 != 0) {
                                        // 0x004e8a94
                                        charge(ctx, 2);
                                        t2 = sll(s3, 1);
                                        t1 = sll(s5, 2);
                                        for (;;) {
                                            // 0x004e8a9c
                                            charge(ctx, 3);
                                            lw(a0, s1, 0);
                                            t3 = addiu(a0, -1);
                                            if (a0 == 0) {
                                                // 0x004e93f4
                                                charge(ctx, 1);
                                                lw(a1, s2, 0);
                                            } else {
                                                for (;;) {
                                                    // 0x004e8aa8
                                                    charge(ctx, 18);
                                                    lhu(t0, v0, 0);
                                                    a0 = t3;
                                                    t3 = addiu(t3, -1);
                                                    a2 = t0 & 0x8000;
                                                    a1 = t0 & 0x7C00;
                                                    a2 = sll(a2, 16);
                                                    a1 = sll(a1, 9);
                                                    a3 = a2 | a1;
                                                    v0 = addiu(v0, 2);
                                                    a1 = t0 & 0x3E0;
                                                    a2 = sll(a1, 6);
                                                    a1 = t0 & 0x1F;
                                                    a2 = a2 | a3;
                                                    a1 = sll(a1, 3);
                                                    a1 = a1 | a2;
                                                    sw(a1, v1, 0);
                                                    v1 = addiu(v1, 4);
                                                    if (a0 == 0) {
                                                        break;
                                                    }
                                                    backedge(ctx);
                                                }
                                                // 0x004e8af0
                                                charge(ctx, 2);
                                                lw(a1, s2, 0);
                                            }
                                            // 0x004e93f8
                                            charge(ctx, 5);
                                            v0 = addu(v0, t2);
                                            v1 = addu(v1, t1);
                                            a0 = addiu(a1, -1);
                                            sw(a0, s2, 0);
                                            if (a1 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x004e940c
                                        charge(ctx, 2);
                                        backedge(ctx);
                                    }
                                    goto L_004e93c8;
                                }
                                // 0x004e8990
                                charge(ctx, 3);
                                a2 = 44;
                                if (t0 != a2) {
                                    // 0x004e899c
                                    charge(ctx, 3);
                                    a2 = 22;
                                    if (t0 == a2) {
                                        goto L_004e89b0;
                                    }
                                    // 0x004e89a8
                                    charge(ctx, 2);
                                    v0 = 0;
                                    // 0x004e93b4
                                    charge(ctx, 2);
                                    // 0x004e9650 (the shared epilogue, written out on this path)
                                    charge(ctx, 12);
                                    ld(ra, sp, 0xA0);
                                    lq(fp, sp, 0x90);
                                    lq(s7, sp, 0x80);
                                    lq(s6, sp, 0x70);
                                    lq(s5, sp, 0x60);
                                    lq(s4, sp, 0x50);
                                    lq(s3, sp, 0x40);
                                    lq(s2, sp, 0x30);
                                    lq(s1, sp, 0x20);
                                    lq(s0, sp, 0x10);
                                    sp = addiu(sp, 0xD0);
                                    return;
                                }
                            L_004e89b0:
                                charge(ctx, 22);
                                lw(a2, v1, 0);
                                v1 = addiu(sp, 0xC4);
                                a2 = addiu(a2, 7);
                                lw(v1, v1, 0);
                                s5 = sra(a2, 3);
                                mult(a2, v0, v1);
                                lw(v1, a1, 0);
                                lw(v0, sp, 0xC0);
                                a1 = addu(v1, a2);
                                mult1(v1, s7, v0);
                                lw(v0, s6, 0);
                                s0 = addu(a1, v1);
                                mult(a0, a0, v0);
                                lw(v1, s4, 4);
                                lw(v0, sp, 0xB0);
                                a0 = addu(v1, a0);
                                mult1(v0, fp, v0);
                                lw(v1, s2, 0);
                                s3 = addu(a0, v0);
                                v0 = addiu(v1, -1);
                                sw(v0, s2, 0);
                                if (v1 != 0) {
                                    for (;;) {
                                        // 0x004e8a08
                                        charge(ctx, 14);
                                        lw(v0, s1, 0);
                                        mult(a2, v0, s5);
                                        a0 = s0;
                                        a1 = s3;
                                        jal(ctx, 0x4E8A14u, gen::fn_memcpy_00521250);
                                        lw(a0, s4, 24);
                                        lw(v0, gp, -16896);  // 0x7CEAF0
                                        lw(v1, s2, 0);
                                        s3 = addu(s3, a0);
                                        lw(a0, v0, 24);
                                        v0 = addiu(v1, -1);
                                        s0 = addu(s0, a0);
                                        sw(v0, s2, 0);
                                        if (v1 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004e8a40
                                    charge(ctx, 2);
                                }
                                goto L_004e93c8;
                            }
                            // 0x004e8af8
                            charge(ctx, 5);
                            lbu(v0, s4, 34);
                            v0 = v0 & 0x2;
                            s0 = sltu(0, v0);
                            if (s0 == 0) {
                                // 0x004e9414
                                charge(ctx, 6);
                                a0 = s4;
                                a1 = 0;
                                a2 = 2;
                                jal(ctx, 0x4E941Cu, gen::fn_sub_4CE200_004ce200);
                                lw(a1, gp, -16896);  // 0x7CEAF0
                                backedge(ctx);
                            } else {
                                // 0x004e8b0c
                                charge(ctx, 1);
                                lw(a1, gp, -16896);  // 0x7CEAF0
                            }
                            // 0x004e8b10
                            charge(ctx, 13);
                            v0 = addiu(sp, 0xC4);
                            lw(v0, v0, 0);
                            lw(v1, a1, 24);
                            mult(a0, v1, v0);
                            lw(v1, a1, 4);
                            lw(v0, sp, 0xC0);
                            a0 = addu(v1, a0);
                            mult1(v0, s7, v0);
                            lw(v1, s4, 20);
                            a2 = addu(a0, v0);
                            v0 = 8;
                            if (v1 != v0) {
                                // 0x004e8c90
                                charge(ctx, 12);
                                lw(v0, s6, 0);
                                lw(v1, s4, 24);
                                mult(a3, v1, v0);
                                lw(a1, s4, 4);
                                lw(a0, sp, 0xB0);
                                lbu(v1, s4, 35);
                                v0 = 1;
                                a1 = addu(a1, a3);
                                a0 = sra(a0, 1);
                                v1 = v1 & 0xF;
                                a0 = addu(a1, a0);
                                if (v1 != v0) {
                                    // 0x004e8da0
                                    charge(ctx, 5);
                                    lw(a1, s2, 0);
                                    lw(v1, s4, 8);
                                    v0 = addiu(a1, -1);
                                    sw(v0, s2, 0);
                                    if (a1 != 0) {
                                        // 0x004e8db4
                                        charge(ctx, 1);
                                        v0 = sll(s5, 2);
                                        for (;;) {
                                            // 0x004e8db8
                                            charge(ctx, 4);
                                            lw(a3, sp, 0xB0);
                                            a3 = a3 & 0x1;
                                            lw(a1, s1, 0);
                                            if (a3 != 0) {
                                                // 0x004e9538
                                                charge(ctx, 10);
                                                lbu(a3, a0, 0);
                                                a1 = addiu(a1, -1);
                                                a3 = sra(a3, 4);
                                                a0 = addiu(a0, 1);
                                                a3 = sll(a3, 2);
                                                a3 = addu(v1, a3);
                                                lw(a3, a3, 0);
                                                sw(a3, a2, 0);
                                                a2 = addiu(a2, 4);
                                                backedge(ctx);
                                            }
                                            // 0x004e8dc8
                                            charge(ctx, 3);
                                            at = sltiu(a1, 2);
                                            if (at == 0) {
                                                // 0x004e8dd4
                                                charge(ctx, 1);
                                                for (;;) {
                                                    // 0x004e8dd8
                                                    charge(ctx, 17);
                                                    lbu(a3, a0, 0);
                                                    a1 = addiu(a1, -2);
                                                    at = sltiu(a1, 2);
                                                    a3 = a3 & 0xF;
                                                    a3 = sll(a3, 2);
                                                    a3 = addu(v1, a3);
                                                    lw(a3, a3, 0);
                                                    sw(a3, a2, 0);
                                                    lbu(a3, a0, 0);
                                                    a3 = sra(a3, 4);
                                                    a0 = addiu(a0, 1);
                                                    a3 = sll(a3, 2);
                                                    a3 = addu(v1, a3);
                                                    lw(a3, a3, 0);
                                                    sw(a3, a2, 4);
                                                    a2 = addiu(a2, 8);
                                                    if (at != 0) {
                                                        break;
                                                    }
                                                    backedge(ctx);
                                                }
                                                // 0x004e8e1c
                                                charge(ctx, 2);
                                            }
                                            // 0x004e9560
                                            charge(ctx, 2);
                                            if (a1 != 0) {
                                                // 0x004e9588
                                                charge(ctx, 8);
                                                lbu(a1, a0, 0);
                                                a1 = a1 & 0xF;
                                                a1 = sll(a1, 2);
                                                a1 = addu(v1, a1);
                                                lw(a1, a1, 0);
                                                sw(a1, a2, 0);
                                                a2 = addiu(a2, 4);
                                                backedge(ctx);
                                            }
                                            // 0x004e9568
                                            charge(ctx, 6);
                                            lw(a3, s2, 0);
                                            a0 = addu(a0, s3);
                                            a2 = addu(a2, v0);
                                            a1 = addiu(a3, -1);
                                            sw(a1, s2, 0);
                                            if (a3 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x004e9580
                                        charge(ctx, 2);
                                        backedge(ctx);
                                    }
                                } else {
                                    // 0x004e8cc0
                                    charge(ctx, 5);
                                    lw(a1, s2, 0);
                                    lw(v1, s4, 8);
                                    v0 = addiu(a1, -1);
                                    sw(v0, s2, 0);
                                    if (a1 != 0) {
                                        // 0x004e8cd4
                                        charge(ctx, 1);
                                        v0 = sll(s5, 2);
                                        for (;;) {
                                            // 0x004e8cd8
                                            charge(ctx, 4);
                                            lw(a3, sp, 0xB0);
                                            a3 = a3 & 0x1;
                                            lw(a1, s1, 0);
                                            if (a3 != 0) {
                                                // 0x004e946c
                                                charge(ctx, 21);
                                                lbu(a3, a0, 0);
                                                a1 = addiu(a1, -1);
                                                a3 = sra(a3, 4);
                                                a0 = addiu(a0, 1);
                                                a3 = sll(a3, 1);
                                                a3 = addu(v1, a3);
                                                lhu(t2, a3, 0);
                                                t0 = t2 & 0x8000;
                                                a3 = t2 & 0x7C00;
                                                t0 = sll(t0, 16);
                                                a3 = sll(a3, 9);
                                                t1 = t0 | a3;
                                                a3 = t2 & 0x3E0;
                                                t0 = sll(a3, 6);
                                                a3 = t2 & 0x1F;
                                                t0 = t0 | t1;
                                                a3 = sll(a3, 3);
                                                a3 = a3 | t0;
                                                sw(a3, a2, 0);
                                                a2 = addiu(a2, 4);
                                                backedge(ctx);
                                            }
                                            // 0x004e8ce8
                                            charge(ctx, 3);
                                            at = sltiu(a1, 2);
                                            if (at == 0) {
                                                // 0x004e8cf4
                                                charge(ctx, 1);
                                                for (;;) {
                                                    // 0x004e8cf8
                                                    charge(ctx, 39);
                                                    lbu(a3, a0, 0);
                                                    a1 = addiu(a1, -2);
                                                    at = sltiu(a1, 2);
                                                    a3 = a3 & 0xF;
                                                    a3 = sll(a3, 1);
                                                    a3 = addu(v1, a3);
                                                    lhu(t2, a3, 0);
                                                    t0 = t2 & 0x8000;
                                                    a3 = t2 & 0x7C00;
                                                    t0 = sll(t0, 16);
                                                    a3 = sll(a3, 9);
                                                    t1 = t0 | a3;
                                                    a3 = t2 & 0x3E0;
                                                    t0 = sll(a3, 6);
                                                    a3 = t2 & 0x1F;
                                                    t0 = t0 | t1;
                                                    a3 = sll(a3, 3);
                                                    a3 = a3 | t0;
                                                    sw(a3, a2, 0);
                                                    lbu(a3, a0, 0);
                                                    a3 = sra(a3, 4);
                                                    a0 = addiu(a0, 1);
                                                    a3 = sll(a3, 1);
                                                    a3 = addu(v1, a3);
                                                    lhu(t2, a3, 0);
                                                    t0 = t2 & 0x8000;
                                                    a3 = t2 & 0x7C00;
                                                    t0 = sll(t0, 16);
                                                    a3 = sll(a3, 9);
                                                    t1 = t0 | a3;
                                                    a3 = t2 & 0x3E0;
                                                    t0 = sll(a3, 6);
                                                    a3 = t2 & 0x1F;
                                                    t0 = t0 | t1;
                                                    a3 = sll(a3, 3);
                                                    a3 = a3 | t0;
                                                    sw(a3, a2, 4);
                                                    a2 = addiu(a2, 8);
                                                    if (at != 0) {
                                                        break;
                                                    }
                                                    backedge(ctx);
                                                }
                                                // 0x004e8d94
                                                charge(ctx, 2);
                                            }
                                            // 0x004e94c0
                                            charge(ctx, 2);
                                            if (a1 != 0) {
                                                // 0x004e94e8
                                                charge(ctx, 19);
                                                lbu(a1, a0, 0);
                                                a1 = a1 & 0xF;
                                                a1 = sll(a1, 1);
                                                a1 = addu(v1, a1);
                                                lhu(t1, a1, 0);
                                                a3 = t1 & 0x8000;
                                                a1 = t1 & 0x7C00;
                                                a3 = sll(a3, 16);
                                                a1 = sll(a1, 9);
                                                t0 = a3 | a1;
                                                a1 = t1 & 0x3E0;
                                                a3 = sll(a1, 6);
                                                a1 = t1 & 0x1F;
                                                a3 = a3 | t0;
                                                a1 = sll(a1, 3);
                                                a1 = a1 | a3;
                                                sw(a1, a2, 0);
                                                a2 = addiu(a2, 4);
                                                backedge(ctx);
                                            }
                                            // 0x004e94c8
                                            charge(ctx, 6);
                                            lw(a3, s2, 0);
                                            a0 = addu(a0, s3);
                                            a2 = addu(a2, v0);
                                            a1 = addiu(a3, -1);
                                            sw(a1, s2, 0);
                                            if (a3 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x004e94e0
                                        charge(ctx, 2);
                                        backedge(ctx);
                                    }
                                }
                            } else {
                                // 0x004e8b44
                                charge(ctx, 13);
                                lw(v0, s6, 0);
                                lw(v1, s4, 24);
                                mult(a0, v1, v0);
                                lw(v1, s4, 4);
                                lw(v0, sp, 0xB0);
                                a0 = addu(v1, a0);
                                mult1(v0, fp, v0);
                                lbu(v1, s4, 35);
                                a1 = addu(a0, v0);
                                v0 = 1;
                                v1 = v1 & 0xF;
                                if (v1 != v0) {
                                    // 0x004e8c18
                                    charge(ctx, 5);
                                    lw(a0, s2, 0);
                                    lw(v1, s4, 8);
                                    v0 = addiu(a0, -1);
                                    sw(v0, s2, 0);
                                    if (a0 != 0) {
                                        // 0x004e8c2c
                                        charge(ctx, 1);
                                        v0 = sll(s5, 2);
                                        for (;;) {
                                            // 0x004e8c30
                                            charge(ctx, 3);
                                            lw(a0, s1, 0);
                                            t3 = addiu(a0, -1);
                                            if (a0 == 0) {
                                                // 0x004e944c
                                                charge(ctx, 1);
                                                lw(a3, s2, 0);
                                            } else {
                                                // 0x004e8c3c
                                                charge(ctx, 1);
                                                for (;;) {
                                                    // 0x004e8c40
                                                    charge(ctx, 17);
                                                    lbu(t2, a1, 0);
                                                    a0 = t3;
                                                    t3 = addiu(t3, -1);
                                                    a3 = t2 & 0x10;
                                                    t1 = t2 & 0xE7;
                                                    t0 = sra(a3, 1);
                                                    a1 = addiu(a1, 1);
                                                    a3 = t2 & 0x8;
                                                    t0 = t1 | t0;
                                                    a3 = sll(a3, 1);
                                                    a3 = a3 | t0;
                                                    a3 = sll(a3, 2);
                                                    a3 = addu(v1, a3);
                                                    lw(a3, a3, 0);
                                                    sw(a3, a2, 0);
                                                    a2 = addiu(a2, 4);
                                                    if (a0 == 0) {
                                                        break;
                                                    }
                                                    backedge(ctx);
                                                }
                                                // 0x004e8c84
                                                charge(ctx, 2);
                                                lw(a3, s2, 0);
                                            }
                                            // 0x004e9450
                                            charge(ctx, 5);
                                            a1 = addu(a1, s3);
                                            a2 = addu(a2, v0);
                                            a0 = addiu(a3, -1);
                                            sw(a0, s2, 0);
                                            if (a3 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x004e9464
                                        charge(ctx, 2);
                                        backedge(ctx);
                                    }
                                } else {
                                    // 0x004e8b78
                                    charge(ctx, 5);
                                    lw(a0, s2, 0);
                                    lw(v1, s4, 8);
                                    v0 = addiu(a0, -1);
                                    sw(v0, s2, 0);
                                    if (a0 != 0) {
                                        // 0x004e8b8c
                                        charge(ctx, 1);
                                        v0 = sll(s5, 2);
                                        for (;;) {
                                            // 0x004e8b90
                                            charge(ctx, 3);
                                            lw(a3, s1, 0);
                                            a0 = addiu(a3, -1);
                                            if (a3 == 0) {
                                                // 0x004e942c
                                                charge(ctx, 1);
                                                lw(a3, s2, 0);
                                            } else {
                                                // 0x004e8b9c
                                                charge(ctx, 1);
                                                for (;;) {
                                                    // 0x004e8ba0
                                                    charge(ctx, 28);
                                                    lbu(t3, a1, 0);
                                                    a3 = a0;
                                                    a0 = addiu(a0, -1);
                                                    t0 = t3 & 0x10;
                                                    t2 = t3 & 0xE7;
                                                    t1 = sra(t0, 1);
                                                    a1 = addiu(a1, 1);
                                                    t0 = t3 & 0x8;
                                                    t1 = t2 | t1;
                                                    t0 = sll(t0, 1);
                                                    t0 = t0 | t1;
                                                    t0 = sll(t0, 1);
                                                    t0 = addu(v1, t0);
                                                    lhu(t3, t0, 0);
                                                    t1 = t3 & 0x8000;
                                                    t0 = t3 & 0x7C00;
                                                    t1 = sll(t1, 16);
                                                    t0 = sll(t0, 9);
                                                    t2 = t1 | t0;
                                                    t0 = t3 & 0x3E0;
                                                    t1 = sll(t0, 6);
                                                    t0 = t3 & 0x1F;
                                                    t1 = t1 | t2;
                                                    t0 = sll(t0, 3);
                                                    t0 = t0 | t1;
                                                    sw(t0, a2, 0);
                                                    a2 = addiu(a2, 4);
                                                    if (a3 == 0) {
                                                        break;
                                                    }
                                                    backedge(ctx);
                                                }
                                                // 0x004e8c10
                                                charge(ctx, 2);
                                                lw(a3, s2, 0);
                                            }
                                            // 0x004e9430
                                            charge(ctx, 5);
                                            a1 = addu(a1, s3);
                                            a2 = addu(a2, v0);
                                            a0 = addiu(a3, -1);
                                            sw(a0, s2, 0);
                                            if (a3 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x004e9444
                                        charge(ctx, 2);
                                        backedge(ctx);
                                    }
                                }
                            }
                            // 0x004e8e28
                            charge(ctx, 2);
                            if (s0 == 0) {
                                // 0x004e8e30
                                charge(ctx, 4);
                                a0 = s4;
                                jal(ctx, 0x4E8E30u, gen::fn_sub_4CDE00_004cde00);
                            }
                            goto L_004e93c8;
                        }
                    L_004e93ec:
                        charge(ctx, 2);
                        v0 = 0;
                    }
                }
            }
        }
    } else {
        // 0x004e8654
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004e9650 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0xD0);
}

// sub_4E4E90 [skyRasterSetupForUpload] -- builds a raster's GS upload description (TEX0 fields, GS size)
// ($a0 = the raster; its driver extension at raster + gp 0x7CEAA8) Width / height rounded up to powers of two
// (sub_4D6B60 = log2), the cached upload packets (+56, +60..+84) freed, TEX0's TBW / TW / TH and the PSM
// and CLUT bits by the format (format byte & 0x6F: 1, 5, 6, 33, 37, 65, 69), the GS memory size in 2-KiB
// pages by depth (32 / 16 / 8 / 4 bits, with the CLUT for the palettised ones) and the byte size.
// 0x004E4E90 sub_4E4E90 -- 1360 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4E4E90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004e4e90
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, -16968);  // 0x7CEAA8
    s0 = a0;
    lw(v0, a0, 12);
    s5 = addu(s0, v1);
    a0 = addiu(v0, -1);
    jal(ctx, 0x4E4EC8u, gen::fn_sub_4D6B60_004d6b60);
    v1 = addiu(v0, 1);
    v0 = 1;
    s4 = sllv(v0, v1);
    lw(v0, s0, 16);
    a0 = addiu(v0, -1);
    jal(ctx, 0x4E4EE0u, gen::fn_sub_4D6B60_004d6b60);
    v1 = addiu(v0, 1);
    lw(a0, s5, 56);
    v0 = 1;
    s6 = sllv(v0, v1);
    lw(v0, s0, 20);
    v0 = addiu(v0, 7);
    s7 = sra(v0, 3);
    if (a0 != 0) {
        // 0x004e4f08
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x4E4F10u, v0.u());
        sw(zero, s5, 56);
    }
    // 0x004e4f1c
    charge(ctx, 4);
    s1 = 0x960000;
    s3 = 0;
    s2 = s5;
    s1 = addiu(s1, 380);  // &0x96017C (RwFree slot)
    for (;;) {
        // 0x004e4f2c
        charge(ctx, 3);
        lw(a0, s2, 60);
        if (a0 != 0) {
            // 0x004e4f38
            charge(ctx, 4);
            lw(v0, s1, 0);
            jalr(ctx, 0x4E4F3Cu, v0.u());
            sw(zero, s2, 60);
        }
        // 0x004e4f48
        charge(ctx, 4);
        s3 = addiu(s3, 1);
        v0 = sltiu(s3, 7);
        s2 = addiu(s2, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004e4f58
    charge(ctx, 3);
    s1 = srl(s4, 6);
    if (s1 == 0) {
        // 0x004e4f6c
        charge(ctx, 2);
        s1 = 1;
        a0 = s4;
    } else {
        // 0x004e4f64
        charge(ctx, 2);
        a0 = s4;
    }
    // 0x004e4f74
    charge(ctx, 25);
    jal(ctx, 0x4E4F74u, gen::fn_sub_4D6B60_004d6b60);
    v0 = v0 & 0xF;
    v1 = sll(s1, 14);
    v0 = sll(v0, 26);
    a0 = s6;
    s1 = v1 | v0;
    jal(ctx, 0x4E4F8Cu, gen::fn_sub_4D6B60_004d6b60);
    v0 = v0 & 0xF;
    a0 = s6;
    v0 = sll(v0, 30);
    v0 = s1 | v0;
    link(ctx, 0x4E4FA4u);  // $ra first: the delay slot below depends on it
    sw(v0, s5, 8);
    call(ctx, gen::fn_sub_4D6B60_004d6b60);
    a0 = v0 & 0xF;
    v1 = 5;
    a0 = sra(a0, 2);
    a0 = dsll32(a0, 0);
    a0 = dsra32(a0, 0);
    sw(a0, s5, 12);
    sh(zero, s5, 20);
    lbu(a0, s0, 35);
    a0 = a0 & 0x6F;
    if (a0 == v1) {
        // 0x004e513c
        charge(ctx, 3);
        lw(v1, s5, 12);
        v1 = v1 | 0x2C;
        sw(v1, s5, 12);
    L_004e5148:
        charge(ctx, 1);
        mult(v1, s6, s4);
    } else {
        // 0x004e4fd8
        charge(ctx, 3);
        v1 = 6;
        if (a0 == v1) {
            // 0x004e5128
            charge(ctx, 5);
            lw(a0, s5, 8);
            v1 = 0x100000;
            v1 = a0 | v1;
            sw(v1, s5, 8);
            goto L_004e5148;
        }
        // 0x004e4fe4
        charge(ctx, 3);
        v1 = 69;
        if (a0 == v1) {
            // 0x004e50f8
            charge(ctx, 12);
            lw(a1, s5, 8);
            a0 = 0x1400000;
            v1 = 0x20000000;
            a0 = a1 | a0;
            sw(a0, s5, 8);
            lw(a0, s5, 12);
            a0 = a0 | 0x2C;
            sw(a0, s5, 12);
            lw(a0, s5, 12);
            v1 = a0 | v1;
            sw(v1, s5, 12);
            goto L_004e5148;
        }
        // 0x004e4ff0
        charge(ctx, 3);
        v1 = 65;
        if (a0 == v1) {
            // 0x004e50b8
            charge(ctx, 16);
            lw(a2, s5, 8);
            a1 = 0x1400000;
            a0 = 0x500000;
            v1 = 0x20000000;
            a1 = a2 | a1;
            sw(a1, s5, 8);
            lw(a1, s5, 12);
            a1 = a1 | 0x2C;
            sw(a1, s5, 12);
            lw(a1, s5, 12);
            a0 = a1 | a0;
            sw(a0, s5, 12);
            lw(a0, s5, 12);
            v1 = a0 | v1;
            sw(v1, s5, 12);
            goto L_004e5148;
        }
        // 0x004e4ffc
        charge(ctx, 3);
        v1 = 37;
        if (a0 == v1) {
            // 0x004e5088
            charge(ctx, 12);
            lw(a1, s5, 8);
            a0 = 0x1300000;
            v1 = 0x20000000;
            a0 = a1 | a0;
            sw(a0, s5, 8);
            lw(a0, s5, 12);
            a0 = a0 | 0x2C;
            sw(a0, s5, 12);
            lw(a0, s5, 12);
            v1 = a0 | v1;
            sw(v1, s5, 12);
            goto L_004e5148;
        }
        // 0x004e5008
        charge(ctx, 3);
        v1 = 33;
        if (a0 == v1) {
            // 0x004e5048
            charge(ctx, 16);
            lw(a2, s5, 8);
            a1 = 0x1300000;
            a0 = 0x500000;
            v1 = 0x20000000;
            a1 = a2 | a1;
            sw(a1, s5, 8);
            lw(a1, s5, 12);
            a1 = a1 | 0x2C;
            sw(a1, s5, 12);
            lw(a1, s5, 12);
            a0 = a1 | a0;
            sw(a0, s5, 12);
            lw(a0, s5, 12);
            v1 = a0 | v1;
            sw(v1, s5, 12);
            goto L_004e5148;
        }
        // 0x004e5014
        charge(ctx, 3);
        v1 = 1;
        if (a0 == v1) {
            // 0x004e5028
            charge(ctx, 8);
            lw(a0, s5, 8);
            v1 = 0xA00000;
            v1 = a0 | v1;
            sw(v1, s5, 8);
            lw(v1, s5, 12);
            v1 = v1 | 0x2C;
            sw(v1, s5, 12);
            goto L_004e5148;
        }
        // 0x004e5020
        charge(ctx, 2);
        mult(v1, s6, s4);
    }
    // 0x004e514c
    charge(ctx, 6);
    mult(v1, s7, v1);
    sw(v1, s5, 40);
    lw(a0, s0, 20);
    at = slti(a0, 17);
    if (at == 0) {
        // 0x004e52e4
        charge(ctx, 4);
        lw(v1, s0, 12);
        v1 = addiu(v1, 63);
        a1 = sra(v1, 6);
        if (i64(v1) < 0) {
            // 0x004e52f4
            charge(ctx, 2);
            v1 = addiu(v1, 63);
            a1 = sra(v1, 6);
        }
        // 0x004e52fc
        charge(ctx, 4);
        lw(v1, s0, 16);
        a0 = addiu(v1, 31);
        v1 = sra(a0, 5);
        if (i64(a0) < 0) {
            // 0x004e530c
            charge(ctx, 2);
            v1 = addiu(a0, 31);
            v1 = sra(v1, 5);
        }
        // 0x004e5314
        charge(ctx, 7);
        mult(a0, a1, v1);
        v1 = si(-2048);
        a0 = sll(a0, 11);
        v1 = a0 & v1;
        sw(v1, s5, 48);
        sw(zero, s5, 44);
        backedge(ctx);
    } else {
        // 0x004e5164
        charge(ctx, 3);
        v1 = 16;
        if (a0 == v1) {
            // 0x004e5330
            charge(ctx, 4);
            lw(v1, s0, 12);
            a0 = addiu(v1, 63);
            v1 = sra(a0, 6);
            if (i64(a0) < 0) {
                // 0x004e5340
                charge(ctx, 2);
                v1 = addiu(a0, 63);
                v1 = sra(v1, 6);
            }
            // 0x004e5348
            charge(ctx, 6);
            a3 = dsll32(v1, 0);
            lw(v1, s0, 16);
            a3 = dsra32(a3, 0);
            a0 = addiu(v1, 63);
            v1 = sra(a0, 6);
            if (i64(a0) < 0) {
                // 0x004e5360
                charge(ctx, 2);
                v1 = addiu(a0, 63);
                v1 = sra(v1, 6);
            }
            // 0x004e5368
            charge(ctx, 19);
            a2 = dsll32(v1, 0);
            v1 = dsll32(a3, 0);
            a2 = dsrl32(a2, 0);
            v1 = dsra32(v1, 0);
            multu(a1, v1, a2);
            mfhi(a0);
            v1 = dsra32(a3, 0);
            pextlw(a1, a0, a1);
            mult1(a0, a2, v1);
            a0 = dsll32(a0, 0);
            v1 = si(-2048);
            a0 = a0 + a1;
            a0 = dsll32(a0, 0);
            a0 = dsra32(a0, 0);
            a0 = sll(a0, 11);
            v1 = a0 & v1;
            sw(v1, s5, 48);
            sw(zero, s5, 44);
            backedge(ctx);
        } else {
            // 0x004e5170
            charge(ctx, 3);
            v1 = 8;
            if (a0 != v1) {
                // 0x004e5220
                charge(ctx, 4);
                lw(v1, s0, 12);
                a0 = addiu(v1, 127);
                v1 = sra(a0, 7);
                if (i64(a0) < 0) {
                    // 0x004e5230
                    charge(ctx, 2);
                    v1 = addiu(a0, 127);
                    v1 = sra(v1, 7);
                }
                // 0x004e5238
                charge(ctx, 6);
                a2 = dsll32(v1, 0);
                lw(v1, s0, 16);
                a2 = dsra32(a2, 0);
                a0 = addiu(v1, 127);
                v1 = sra(a0, 7);
                if (i64(a0) < 0) {
                    // 0x004e5250
                    charge(ctx, 2);
                    v1 = addiu(a0, 127);
                    v1 = sra(v1, 7);
                }
                // 0x004e5258
                charge(ctx, 26);
                a3 = dsll32(v1, 0);
                v1 = dsll32(a2, 0);
                a3 = dsrl32(a3, 0);
                v1 = dsra32(v1, 0);
                multu(a1, v1, a3);
                mfhi(a0);
                v1 = dsra32(a2, 0);
                pextlw(a2, a0, a1);
                mult1(v1, a3, v1);
                a0 = si(-2048);
                a1 = dsll32(v1, 0);
                a1 = a1 + a2;
                v1 = 1;
                a1 = dsll32(a1, 0);
                a1 = dsra32(a1, 0);
                a1 = sll(a1, 11);
                a0 = a1 & a0;
                a0 = addiu(a0, 2048);
                sw(a0, s5, 48);
                lw(a0, s5, 48);
                a0 = srl(a0, 6);
                sw(a0, s5, 16);
                lw(a0, s5, 48);
                a0 = addiu(a0, 2048);
                sw(a0, s5, 48);
                sw(v1, s5, 44);
            } else {
                // 0x004e517c
                charge(ctx, 4);
                lw(v1, s0, 12);
                a0 = addiu(v1, 127);
                v1 = sra(a0, 7);
                if (i64(a0) < 0) {
                    // 0x004e518c
                    charge(ctx, 2);
                    v1 = addiu(a0, 127);
                    v1 = sra(v1, 7);
                }
                // 0x004e5194
                charge(ctx, 6);
                a2 = dsll32(v1, 0);
                lw(v1, s0, 16);
                a2 = dsra32(a2, 0);
                a0 = addiu(v1, 63);
                v1 = sra(a0, 6);
                if (i64(a0) < 0) {
                    // 0x004e51ac
                    charge(ctx, 2);
                    v1 = addiu(a0, 63);
                    v1 = sra(v1, 6);
                }
                // 0x004e51b4
                charge(ctx, 27);
                a3 = dsll32(v1, 0);
                v1 = dsll32(a2, 0);
                a3 = dsrl32(a3, 0);
                v1 = dsra32(v1, 0);
                multu(a1, v1, a3);
                mfhi(a0);
                v1 = dsra32(a2, 0);
                pextlw(a2, a0, a1);
                mult1(v1, a3, v1);
                a0 = si(-2048);
                a1 = dsll32(v1, 0);
                a1 = a1 + a2;
                v1 = 1;
                a1 = dsll32(a1, 0);
                a1 = dsra32(a1, 0);
                a1 = sll(a1, 11);
                a0 = a1 & a0;
                a0 = addiu(a0, 2048);
                sw(a0, s5, 48);
                lw(a0, s5, 48);
                a0 = srl(a0, 6);
                sw(a0, s5, 16);
                lw(a0, s5, 48);
                a0 = addiu(a0, 2048);
                sw(a0, s5, 48);
                sw(v1, s5, 44);
            }
        }
    }
    // 0x004e52c0
    charge(ctx, 9);
    a0 = 16384;
    v1 = 0x400000;
    v1 = v1 | 0x4;  // &0x400004
    sw(a0, s5, 24);
    sw(v1, s5, 28);
    sw(a0, s5, 32);
    sw(v1, s5, 36);
    sb(zero, s5, 22);
    // 0x004e53b4
    charge(ctx, 11);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// sub_4EFA00 [skyTexCacheMemRasterToGs] -- uploads a raster's memory image into its GS texture-cache slot
// The upload packets are built by format (the jump table 0x7BD010) into a GIF packet (_rwDMAOpenGIFPkt,
// sub_4D5FE0) for aligned / contiguous rectangles (skyFillInPktForUpLoadAlignedContiguousRectangle,
// sub_4EF540, sub_4EF770), with the 64-bit size arithmetic through __udivdi3, under DIntr / EIntr, the raster's
// packets referenced (_rwDMAAddPURef); a packet cache may be RwMalloc'd.
// 0x004EFA00 sub_4EFA00 -- 2268 bytes; frame 0x180: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4EFA00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004efa00
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x180);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    fp = a0;
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -16968);  // 0x7CEAA8
    s1 = addu(fp, v0);
    lbu(v0, s1, 54);
    v0 = v0 & 0x1;
    sw(a1, sp, 0x13C);
    if (v0 == 0) {
        // 0x004efa48
        charge(ctx, 21);
        lw(s0, fp, 0x4);
        sw(zero, gp, -16856);  // 0x7CEB18
        lw(v0, fp, 0x14);
        lw(v1, fp, 0xC);
        sw(v0, sp, 0x120);
        lw(v0, s1, 8);
        v0 = srl(v0, 20);
        v0 = v0 & 0x3F;
        sw(v0, sp, 0x110);
        lw(v0, sp, 0x120);
        mult(a0, v1, v0);
        lw(v0, fp, 0x18);
        a0 = sra(a0, 3);
        lbu(v1, s1, 22);
        v0 = v0 ^ a0;
        v0 = sltiu(v0, 1);
        sq(v0, sp, 0xC0);
        v0 = sra(v1, 2);
        at = sltiu(v0, 7);
        if (at != 0) {
            // 0x004efa9c
            charge(ctx, 7);
            v1 = 0x7C0000;
            v0 = sll(v0, 2);
            v1 = addiu(v1, -12272);  // &0x7BD010
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x4EFAB8u:  // table[4, 5, 6]
            L_004efab8:
                charge(ctx, 33);
                lwu(v0, s1, 36);
                lwu(v1, s1, 32);
                v0 = dsll32(v0, 0);
                a0 = v1 | v0;
                v0 = dsrl(a0, 20);
                v1 = a0 & 0x3FFF;
                v0 = v0 & 0x3FFF;
                v1 = dsll32(v1, 0);
                v0 = dsll32(v0, 0);
                v1 = dsra32(v1, 0);
                v0 = dsra32(v0, 0);
                sw(v1, sp, 0x170);
                sw(v0, sp, 0x174);
                v0 = dsrl32(a0, 8);
                v1 = v0 & 0x3FFF;
                v0 = dsrl(a0, 14);
                v1 = dsll32(v1, 0);
                v0 = v0 & 0x3F;
                v1 = dsra32(v1, 0);
                v0 = dsll32(v0, 0);
                sw(v1, sp, 0x178);
                v0 = dsra32(v0, 0);
                sw(v0, sp, 0x150);
                v0 = dsrl32(a0, 2);
                v1 = v0 & 0x3F;
                v0 = dsrl32(a0, 22);
                v1 = dsll32(v1, 0);
                v0 = v0 & 0x3F;
                v1 = dsra32(v1, 0);
                v0 = dsll32(v0, 0);
                sw(v1, sp, 0x154);
                v0 = dsra32(v0, 0);
                sw(v0, sp, 0x158);
            L_004efb3c:
                charge(ctx, 33);
                lwu(v0, s1, 28);
                lwu(v1, s1, 24);
                v0 = dsll32(v0, 0);
                a0 = v1 | v0;
                v0 = dsrl(a0, 20);
                v1 = a0 & 0x3FFF;
                v0 = v0 & 0x3FFF;
                v1 = dsll32(v1, 0);
                v0 = dsll32(v0, 0);
                v1 = dsra32(v1, 0);
                v0 = dsra32(v0, 0);
                sw(v1, sp, 0x164);
                sw(v0, sp, 0x168);
                v0 = dsrl32(a0, 8);
                v1 = v0 & 0x3FFF;
                v0 = dsrl(a0, 14);
                v1 = dsll32(v1, 0);
                v0 = v0 & 0x3F;
                v1 = dsra32(v1, 0);
                v0 = dsll32(v0, 0);
                sw(v1, sp, 0x16C);
                v0 = dsra32(v0, 0);
                sw(v0, sp, 0x144);
                v0 = dsrl32(a0, 2);
                v1 = v0 & 0x3F;
                v0 = dsrl32(a0, 22);
                v1 = dsll32(v1, 0);
                v0 = v0 & 0x3F;
                v1 = dsra32(v1, 0);
                v0 = dsll32(v0, 0);
                sw(v1, sp, 0x148);
                v0 = dsra32(v0, 0);
                sw(v0, sp, 0x14C);
                break;
            case 0x4EFB3Cu:  // table[1, 2, 3]
                goto L_004efb3c;
            case 0x4EFBC0u:  // table[0]
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            goto L_004efbc0;
        }
        goto L_004efab8;
    }
    // 0x004f0018
    charge(ctx, 10);
    lw(v0, fp, 0x24);
    lw(s0, v0, 0);
    s2 = addiu(v0, 16);
    v0 = sll(s0, 2);
    sw(a2, gp, -16856);  // 0x7CEB18
    a1 = addiu(v0, 4);
    lbu(v0, fp, 0x21);
    v0 = v0 & 0x40;
    if (v0 != 0) {
        // 0x004f0040
        charge(ctx, 3);
        lw(v0, s1, 44);
        v0 = srl(v0, 4);
        a1 = addu(a1, v0);
    }
    // 0x004f004c
    charge(ctx, 12);
    a0 = a2;
    jal(ctx, 0x4F004Cu, gen::fn_sub_4D6250_004d6250);
    lw(v1, sp, 0x13C);
    a0 = si(-64);
    lw(v0, gp, -17152);  // 0x7CE9F0
    at = sltu(0, s0);
    a3 = 0;
    v1 = v1 & a0;
    v1 = dsll32(v1, 0);
    v1 = dsrl32(v1, 0);
    a2 = dsll(v1, 26);
    if (at != 0) {
        for (;;) {
            // 0x004f007c
            charge(ctx, 16);
            lq(a0, s2, 0);
            a3 = addiu(a3, 1);
            v1 = sltu(a3, s0);
            sq(a0, v0, 0);
            lq(a0, s2, 16);
            sq(a0, v0, 16);
            ld(a1, s2, 32);
            ld(a0, s2, 40);
            a1 = a1 + a2;
            pcpyld(a0, a0, a1);
            sq(a0, v0, 32);
            lq(a0, s2, 48);
            sq(a0, v0, 48);
            s2 = addiu(s2, 64);
            v0 = addiu(v0, 64);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004f00bc
        charge(ctx, 1);
    }
    // 0x004f00c0
    charge(ctx, 4);
    lbu(v1, fp, 0x21);
    v1 = v1 & 0x40;
    if (v1 != 0) {
        // 0x004f0120
        charge(ctx, 17);
        lw(a1, s2, -12);
        lw(v1, s1, 44);
        lq(a0, a1, 0);
        t0 = addiu(v1, -80);
        v1 = sltiu(t0, 64);
        sq(a0, v0, 0);
        lq(a0, a1, 16);
        sq(a0, v0, 16);
        lq(a0, a1, 32);
        sq(a0, v0, 32);
        lq(a0, a1, 48);
        sq(a0, v0, 48);
        lq(a0, a1, 64);
        sq(a0, v0, 64);
        lw(a3, fp, 0x8);
        v0 = addiu(v0, 80);
        if (v1 != 0) {
            // 0x004f01a4
            charge(ctx, 6);
            lq(a0, a3, 16);
            lq(v1, a3, 0);
            sq(v1, v0, 0);
            sq(a0, v0, 16);
            v0 = addiu(v0, 32);
            backedge(ctx);
            goto L_004f00d0;
        }
        // 0x004f0164
        charge(ctx, 2);
        if (t0 == 0) {
            backedge(ctx);
            goto L_004f00d0;
        }
        for (;;) {
            // 0x004f016c
            charge(ctx, 12);
            lq(a2, a3, 0);
            t0 = addiu(t0, -64);
            lq(a1, a3, 16);
            lq(a0, a3, 32);
            lq(v1, a3, 48);
            sq(a2, v0, 0);
            a3 = addiu(a3, 64);
            sq(a1, v0, 16);
            sq(a0, v0, 32);
            sq(v1, v0, 48);
            v0 = addiu(v0, 64);
            if (t0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004f019c
        charge(ctx, 2);
        a0 = 0x50000000;
        backedge(ctx);
        goto L_004f00d4;
    }
L_004f00d0:
    charge(ctx, 1);
    a0 = 0x50000000;
L_004f00d4:
    charge(ctx, 19);
    v1 = 0x10000000;
    a1 = a0 | 0x2;
    a2 = dsll32(a1, 0);
    a0 = v1 | 0x2;
    a1 = dsll32(v1, 0);
    pcpyld(v1, a2, a0);
    a0 = 0x8001;
    sq(v1, v0, 0);
    a0 = a0 | a1;
    a2 = 14;
    pcpyld(a0, a2, a0);
    v1 = 127;
    a1 = 0;
    pcpyld(v1, v1, a1);
    sq(a0, v0, 16);
    sq(v1, v0, 32);
    v0 = addiu(v0, 48);
    sw(v0, gp, -17152);  // 0x7CE9F0
    backedge(ctx);
L_004effdc:
    charge(ctx, 13);
    jal(ctx, 0x4EFFDCu, gen::fn_DIntr_0050d3a0);
    lw(v0, s1, 0);
    v0 = addiu(v0, 1);
    link(ctx, 0x4EFFECu);  // $ra first: the delay slot below depends on it
    sw(v0, s1, 0);
    call(ctx, gen::fn_EIntr_0050d3f0);
    lw(a0, s1, 4);
    v1 = 1;
    a0 = addiu(a0, 1);
    sw(a0, s1, 4);
    lw(a0, s1, 4);
    if (a0 == v1) {
        // 0x004f02a0
        charge(ctx, 4);
        a0 = s1;
        jal(ctx, 0x4F02A0u, gen::fn__rwDMAAddPURef_004d51c0);
        backedge(ctx);
    }
    // 0x004f0010
    charge(ctx, 2);
    ld(ra, sp, 0x90);
    // 0x004f02b0
    charge(ctx, 11);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x180);
    return;
L_004efbc0:
    charge(ctx, 10);
    lw(v1, s1, 8);
    s7 = 0;
    lbu(v0, s1, 22);
    sw(zero, sp, 0x160);
    v1 = srl(v1, 14);
    v0 = sra(v0, 2);
    v1 = v1 & 0x3F;
    at = slt(v0, 0);
    sw(v1, sp, 0x140);
    if (at == 0) {
        // 0x004efbe8
        charge(ctx, 10);
        v0 = addiu(sp, 0x160);
        s3 = s1;
        sw(v0, sp, 0xD0);
        s2 = addiu(sp, 0x140);
        lw(v0, sp, 0x13C);
        v0 = srl(v0, 6);
        sq(v0, sp, 0xB0);
        v0 = 0x960000;
        v0 = addiu(v0, 376);  // &0x960178 (RwMalloc slot)
        sq(v0, sp, 0xA0);
        for (;;) {
            // 0x004efc10
            charge(ctx, 15);
            v0 = s0 & 0xF;
            lw(a3, fp, 0xC);
            v0 = sltu(0, v0);
            lw(a2, fp, 0x10);
            v1 = v0 ^ 0x1;
            lw(a1, fp, 0x18);
            lw(v0, sp, 0xD0);
            s5 = srav(a3, s7);
            s4 = srav(a2, s7);
            lw(a0, v0, 0);
            v0 = srav(a1, s7);
            sw(v0, sp, 0x100);
            lq(v0, sp, 0xB0);
            s6 = addu(v0, a0);
            if (v1 != 0) {
                // 0x004efc4c
                charge(ctx, 3);
                lq(v0, sp, 0xC0);
                if (v0 == 0) {
                    // 0x004efda8
                    charge(ctx, 4);
                    lbu(a0, s1, 54);
                    v0 = a0 & 0x2;
                    if (v0 != 0) {
                        // 0x004f0228
                        charge(ctx, 6);
                        lw(v1, s1, 8);
                        v0 = 19;
                        v1 = srl(v1, 20);
                        v1 = v1 & 0x3F;
                        if (v1 != v0) {
                            backedge(ctx);
                            goto L_004efdb8;
                        }
                        // 0x004f0240
                        charge(ctx, 12);
                        lw(v0, s2, 0);
                        a0 = srl(s5, 1);
                        lw(t3, sp, 0x100);
                        a3 = s6;
                        a1 = srl(s4, 1);
                        a2 = s0;
                        t1 = 32;
                        t2 = 0;
                        t0 = srl(v0, 1);
                        jal(ctx, 0x4F0260u, gen::fn_sub_4EF770_004ef770);
                        backedge(ctx);
                        goto L_004efe08;
                    }
                L_004efdb8:
                    charge(ctx, 3);
                    v0 = a0 & 0x4;
                    if (v0 != 0) {
                        // 0x004efdc4
                        charge(ctx, 6);
                        lw(v1, s1, 8);
                        v0 = 20;
                        v1 = srl(v1, 20);
                        v1 = v1 & 0x3F;
                        if (v1 != v0) {
                            goto L_004f0270;
                        }
                        // 0x004efddc
                        charge(ctx, 11);
                        lw(v0, s2, 0);
                        a0 = srl(s5, 1);
                        lw(t3, sp, 0x100);
                        a3 = s6;
                        a1 = srl(s4, 1);
                        a2 = s0;
                        t1 = 16;
                        t2 = 2;
                        t0 = srl(v0, 1);
                        jal(ctx, 0x4EFDFCu, gen::fn_sub_4EF770_004ef770);
                        goto L_004efe08;
                    }
                L_004f0270:
                    charge(ctx, 11);
                    lw(t0, s2, 0);
                    lw(t1, sp, 0x120);
                    a0 = s5;
                    lw(t2, sp, 0x110);
                    a3 = s6;
                    lw(t3, sp, 0x100);
                    a1 = s4;
                    a2 = s0;
                    jal(ctx, 0x4F028Cu, gen::fn_sub_4EF770_004ef770);
                    backedge(ctx);
                } else {
                    // 0x004efc58
                    charge(ctx, 3);
                    lw(v0, s3, 60);
                    if (v0 == 0) {
                        // 0x004efc64
                        charge(ctx, 12);
                        lbu(v0, s1, 52);
                        sb(v0, sp, 0xF0);
                        mult(v1, s5, s4);
                        lw(v0, sp, 0x120);
                        mult(v0, v0, v1);
                        v0 = srl(v0, 3);
                        v0 = dsll32(v0, 0);
                        v0 = dsrl32(v0, 0);
                        sd(v0, sp, 0xE0);
                        lbu(v0, sp, 0xF0);
                        if (v0 == 0) {
                            // 0x004efce0
                            charge(ctx, 16);
                            a0 = 10;
                            jal(ctx, 0x4EFCE0u, gen::fn__rwDMAOpenGIFPkt_004d54e0);
                            ld(v0, sp, 0xE0);
                            a1 = 32750;
                            v0 = daddiu(v0, 15);
                            a0 = dsrl(v0, 4);
                            jal(ctx, 0x4EFCF4u, gen::fn___udivdi3_0052fe98);
                            v1 = daddiu(v0, 1);
                            a1 = 0;
                            v0 = dsll(v1, 1);
                            v0 = v0 + v1;
                            v0 = dsll(v0, 4);
                            v0 = daddiu(v0, 176);
                            a0 = dsll32(v0, 0);
                            a0 = dsra32(a0, 0);
                            jal(ctx, 0x4EFD18u, gen::fn_sub_4D5FE0_004d5fe0);
                        } else {
                            // 0x004efc94
                            charge(ctx, 19);
                            ld(v0, sp, 0xE0);
                            a1 = 32750;
                            v0 = daddiu(v0, 15);
                            a0 = dsrl(v0, 4);
                            jal(ctx, 0x4EFCA0u, gen::fn___udivdi3_0052fe98);
                            v1 = daddiu(v0, 1);
                            v0 = 0x30000;
                            a1 = v0 | 0x411;
                            v0 = dsll(v1, 1);
                            v1 = v0 + v1;
                            lq(v0, sp, 0xA0);
                            v1 = dsll(v1, 4);
                            v1 = daddiu(v1, 176);
                            a0 = dsll32(v1, 0);
                            lw(v0, v0, 0);
                            a0 = dsra32(a0, 0);
                            jalr(ctx, 0x4EFCD0u, v0.u());
                        }
                        // 0x004efd20
                        charge(ctx, 6);
                        ld(a2, sp, 0xE0);
                        lbu(a3, sp, 0xF0);
                        a0 = v0;
                        a1 = s0;
                        jal(ctx, 0x4EFD2Cu, gen::fn_skyFillInPktForUpLoadAlignedContiguousRectangle_004ef020);
                        sw(v0, s3, 60);
                    }
                    // 0x004efd38
                    charge(ctx, 4);
                    lbu(a0, s1, 54);
                    v0 = a0 & 0x2;
                    if (v0 != 0) {
                        // 0x004f01bc
                        charge(ctx, 6);
                        lw(v1, s1, 8);
                        v0 = 19;
                        v1 = srl(v1, 20);
                        v1 = v1 & 0x3F;
                        if (v1 != v0) {
                            backedge(ctx);
                            goto L_004efd48;
                        }
                        // 0x004f01d4
                        charge(ctx, 11);
                        lw(v0, s2, 0);
                        a0 = srl(s5, 1);
                        lw(t1, s3, 60);
                        a2 = s6;
                        lbu(t2, s1, 52);
                        a1 = srl(s4, 1);
                        t0 = 0;
                        a3 = srl(v0, 1);
                        jal(ctx, 0x4F01F0u, gen::fn_sub_4EF540_004ef540);
                        backedge(ctx);
                        goto L_004efd90;
                    }
                L_004efd48:
                    charge(ctx, 3);
                    v0 = a0 & 0x4;
                    if (v0 != 0) {
                        // 0x004efd54
                        charge(ctx, 6);
                        lw(v1, s1, 8);
                        v0 = 20;
                        v1 = srl(v1, 20);
                        v1 = v1 & 0x3F;
                        if (v1 != v0) {
                            goto L_004f0200;
                        }
                        // 0x004efd6c
                        charge(ctx, 9);
                        lw(v0, s2, 0);
                        a0 = srl(s5, 1);
                        lw(t1, s3, 60);
                        a2 = s6;
                        lbu(t2, s1, 52);
                        a1 = srl(s4, 1);
                        t0 = 2;
                        a3 = srl(v0, 1);
                        jal(ctx, 0x4EFD88u, gen::fn_sub_4EF540_004ef540);
                        goto L_004efd90;
                    }
                L_004f0200:
                    charge(ctx, 10);
                    lw(a3, s2, 0);
                    lw(t0, sp, 0x110);
                    a0 = s5;
                    lw(t1, s3, 60);
                    a2 = s6;
                    lbu(t2, s1, 52);
                    a1 = s4;
                    jal(ctx, 0x4F0218u, gen::fn_sub_4EF540_004ef540);
                    backedge(ctx);
                L_004efd90:
                    charge(ctx, 3);
                    lbu(v0, s1, 52);
                    if (v0 == 0) {
                        // 0x004efd9c
                        charge(ctx, 2);
                        sw(zero, s3, 60);
                    }
                }
            }
        L_004efe08:
            charge(ctx, 6);
            lw(v0, sp, 0x100);
            mult(v0, v0, s4);
            s0 = addu(s0, v0);
            v0 = s0 & 0xF;
            if (v0 != 0) {
                // 0x004efe20
                charge(ctx, 4);
                v1 = addiu(s0, 15);
                v0 = si(-16);
                s0 = v1 & v0;
            }
            // 0x004efe30
            charge(ctx, 10);
            lw(v0, sp, 0xD0);
            s7 = addiu(s7, 1);
            s3 = addiu(s3, 4);
            v0 = addiu(v0, 4);
            sw(v0, sp, 0xD0);
            lbu(v0, s1, 22);
            v0 = sra(v0, 2);
            at = slt(v0, s7);
            s2 = addiu(s2, 4);
            if (at != 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004efe58
    charge(ctx, 3);
    lw(v0, s1, 44);
    if (v0 != 0) {
        // 0x004efe64
        charge(ctx, 4);
        lw(v1, fp, 0x14);
        at = slti(v1, 9);
        if (at != 0) {
            // 0x004efe74
            charge(ctx, 18);
            lw(v0, sp, 0x13C);
            v1 = sll(v1, 2);
            lw(a2, s1, 12);
            lw(a0, s1, 16);
            a1 = srl(v0, 6);
            v0 = 0x7C0000;
            v0 = addiu(v0, -12340);  // &0x7BCFCC
            v0 = addu(v0, v1);
            lw(s3, v0, 0);
            v0 = 0x7C0000;
            v0 = addiu(v0, -12308);  // &0x7BCFEC
            v1 = addu(v0, v1);
            lw(s2, v1, 0);
            v0 = 10;
            v1 = srl(a2, 19);
            s0 = v1 & 0xF;
            s7 = addu(a1, a0);
            if (s0 != v0) {
                // 0x004efebc
                charge(ctx, 3);
                v0 = 2;
                if (s0 == v0) {
                    goto L_004efee0;
                }
                // 0x004efec8
                charge(ctx, 2);
                if (s0 == 0) {
                    // 0x004efed8
                    charge(ctx, 2);
                    v1 = 32;
                } else {
                    // 0x004efed0
                    charge(ctx, 2);
                    v1 = 16;
                }
                goto L_004efee4;
            }
        L_004efee0:
            charge(ctx, 1);
            v1 = 16;
        L_004efee4:
            charge(ctx, 3);
            lw(v0, s1, 56);
            if (v0 == 0) {
                // 0x004efef0
                charge(ctx, 8);
                lw(s6, fp, 0x8);
                lbu(s5, s1, 52);
                mult(v0, s3, s2);
                mult(v0, v1, v0);
                v0 = srl(v0, 3);
                s4 = dsll32(v0, 0);
                s4 = dsrl32(s4, 0);
                if (s5 == 0) {
                    // 0x004eff58
                    charge(ctx, 16);
                    a0 = 10;
                    jal(ctx, 0x4EFF58u, gen::fn__rwDMAOpenGIFPkt_004d54e0);
                    v0 = daddiu(s4, 15);
                    a1 = 32750;
                    a0 = dsrl(v0, 4);
                    jal(ctx, 0x4EFF68u, gen::fn___udivdi3_0052fe98);
                    v1 = daddiu(v0, 1);
                    a1 = 0;
                    v0 = dsll(v1, 1);
                    v0 = v0 + v1;
                    v0 = dsll(v0, 4);
                    v0 = daddiu(v0, 176);
                    a0 = dsll32(v0, 0);
                    a0 = dsra32(a0, 0);
                    jal(ctx, 0x4EFF8Cu, gen::fn_sub_4D5FE0_004d5fe0);
                    a1 = s6;
                } else {
                    // 0x004eff10
                    charge(ctx, 18);
                    v0 = daddiu(s4, 15);
                    a1 = 32750;
                    a0 = dsrl(v0, 4);
                    jal(ctx, 0x4EFF18u, gen::fn___udivdi3_0052fe98);
                    v1 = daddiu(v0, 1);
                    v0 = 0x30000;
                    a1 = v0 | 0x411;
                    v0 = dsll(v1, 1);
                    v1 = v0 + v1;
                    v0 = 0x960000;
                    v1 = dsll(v1, 4);
                    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                    v1 = daddiu(v1, 176);
                    a0 = dsll32(v1, 0);
                    a0 = dsra32(a0, 0);
                    jalr(ctx, 0x4EFF48u, v0.u());
                    a1 = s6;
                }
                // 0x004eff98
                charge(ctx, 5);
                a2 = s4;
                a3 = s5;
                a0 = v0;
                jal(ctx, 0x4EFFA0u, gen::fn_skyFillInPktForUpLoadAlignedContiguousRectangle_004ef020);
                sw(v0, s1, 56);
            }
            // 0x004effac
            charge(ctx, 11);
            lw(t1, s1, 56);
            a0 = s3;
            lbu(t2, s1, 52);
            a1 = s2;
            a2 = s7;
            t0 = s0;
            a3 = 1;
            jal(ctx, 0x4EFFC4u, gen::fn_sub_4EF540_004ef540);
            lbu(v0, s1, 52);
            if (v0 == 0) {
                // 0x004effd8
                charge(ctx, 1);
                sw(zero, s1, 56);
            }
        }
    }
    goto L_004effdc;
}

// sub_4AB0E0 [rt2dObjectNodeDestroy] -- frees one Rt2d list node and returns its successor
// ($a0 = the node: +0 a buffer, +4 its owner tag, +20 the next node) A buffer is released (sub_4C20B0 when the
// tag is -1, else RwFree) and the word cleared; the node goes back to its free list (0x95ED84, slot
// 0x96018C). Returns the old +20.
// 0x004AB0E0 sub_4AB0E0 -- 136 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AB0E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ab0e0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 20);
    lw(a0, a0, 0);
    if (a0 != 0) {
        // 0x004ab104
        charge(ctx, 4);
        lw(v1, s1, 4);
        v0 = si(-1);
        if (v1 != v0) {
            // 0x004ab124
            charge(ctx, 4);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            jalr(ctx, 0x4AB12Cu, v0.u());
            goto L_004ab134;
        }
        // 0x004ab114
        charge(ctx, 4);
        jal(ctx, 0x4AB114u, gen::fn_sub_4C20B0_004c20b0);
        sw(zero, s1, 0);
        goto L_004ab138;
    }
L_004ab134:
    charge(ctx, 1);
    sw(zero, s1, 0);
L_004ab138:
    charge(ctx, 12);
    v1 = 0x960000;
    v0 = 0x960000;
    lw(a0, v1, -4732);  // 0x95ED84
    lw(v0, v0, 396);  // 0x96018C (free-list free slot)
    a1 = s1;
    jalr(ctx, 0x4AB148u, v0.u());
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4C1E70 [sListGetNewEntry] -- appends an entry to a growable array (grows by a quarter)
// ($a0 = {+0 data, +4 count, +8 capacity, +12 entry size}, $a1 = the memory hint) A full array grows to
// capacity + capacity / 4 (rounded toward 0, as the original's signed shift does) by RwRealloc; a failure is
// error 0x80000013 with the size -> 0. Returns data + count x size and counts the entry.
// 0x004C1E70 sub_4C1E70 -- 244 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C1E70(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004c1e70
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a2 = a1;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, slist::kCapacity);
    lw(v0, a0, slist::kCount);
    at = slt(v0, v1);
    s0 = a0;
    if (at == 0) {
        // 0x004c1eb4
        charge(ctx, 2);
        v0 = sra(v1, 2);
        if (i64(v1) < 0) {
            // 0x004c1ebc
            charge(ctx, 2);
            v0 = addiu(v1, 3);
            v0 = sra(v0, 2);
        }
        // 0x004c1ec4
        charge(ctx, 9);
        v1 = addu(v1, v0);
        lw(v0, s0, slist::kEntrySize);
        mult(a1, v0, v1);
        v0 = 0x960000;
        lw(v0, v0, 384);  // 0x960180 (RwRealloc slot)
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x4C1ED8u);  // $ra = the return address
        lw(a0, s0, slist::kData);
        call_ptr(ctx, jt);
        if (v0 != 0) {
            // 0x004c1ee8
            charge(ctx, 4);
            sw(v0, s0, slist::kData);
            lw(v0, s0, slist::kCapacity);
            v1 = sra(v0, 2);
            if (i64(v0) < 0) {
                // 0x004c1ef8
                charge(ctx, 2);
                v0 = addiu(v0, 3);
                v1 = sra(v0, 2);
            }
            // 0x004c1f00
            charge(ctx, 4);
            lw(v0, s0, slist::kCapacity);
            v0 = addu(v0, v1);
            sw(v0, s0, slist::kCapacity);
            backedge(ctx);
            goto L_004c1e94;
        }
        // 0x004c1f10
        charge(ctx, 5);
        v0 = 1;
        sw(v0, sp, 0x28);
        lw(v1, s0, slist::kCapacity);
        v0 = sra(v1, 2);
        if (i64(v1) < 0) {
            // 0x004c1f24
            charge(ctx, 2);
            v0 = addiu(v1, 3);
            v0 = sra(v0, 2);
        }
        // 0x004c1f2c
        charge(ctx, 10);
        v1 = addu(v1, v0);
        lw(v0, s0, slist::kEntrySize);
        mult(a1, v0, v1);
        v0 = lui(0x8000);
        a0 = v0 | 0x13;
        jal(ctx, 0x4C1F3Cu, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x2C);
        a0 = addiu(sp, 0x28);
        jal(ctx, 0x4C1F48u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
        // 0x004c1f54 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_004c1e94:
    charge(ctx, 8);
    lw(v1, s0, slist::kCount);
    lw(v0, s0, slist::kEntrySize);
    mult(a0, v1, v0);
    v0 = addiu(v1, 1);
    lw(v1, s0, slist::kData);
    sw(v0, s0, slist::kCount);
    v0 = addu(v1, a0);
    // 0x004c1f54 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4C47E0 [resEntryFree] -- frees one resEntry
// The entry's destroy notification (+20) if any, its owner's pointer (*+16) cleared, then an arena entry (+0 != 0) is
// unlinked, its size taken off the used bytes and its block returned to the resource heap (sub_4C6E60); an entry from
// outside the arena goes to RwFree. Returns 1.
// 0x004C47E0 sub_4C47E0 -- 168 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C47E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c47e0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 20);
    s0 = a0;
    if (v0 != 0) {
        // 0x004c47f8: the destroy notification
        charge(ctx, 2);
        jalr(ctx, 0x4C47F8u, v0.u());
    }
    // 0x004c4800
    charge(ctx, 3);
    lw(v0, s0, resentry::kOwnerRef);
    if (v0 != 0) {
        // 0x004c480c: clear the owner's pointer
        charge(ctx, 1);
        sw(zero, v0, 0);
    }
    // 0x004c4810
    charge(ctx, 3);
    lw(a1, s0, resentry::kNext);
    if (a1 == 0) {
        // 0x004c4860: outside the arena: RwFree
        charge(ctx, 6);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        a0 = s0;
        jalr(ctx, 0x4C4868u, v0.u());
        backedge(ctx);
    } else {
        // 0x004c481c: in the arena: unlink, used -= size, back to the resource heap
        charge(ctx, 15);
        lw(v1, s0, resentry::kPrev);
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        a0 = s0;
        sw(a1, v1, 0);
        lw(a1, s0, resentry::kPrev);
        lw(v1, s0, resentry::kNext);
        sw(a1, v1, 4);
        lw(v1, gp, -17408);  // 0x7CE8F0 (the resource module offset)
        lw(a1, s0, resentry::kSize);
        v1 = addu(v0, v1);
        lw(v0, v1, 4);
        v0 = subu(v0, a1);
        link(ctx, 0x4C4850u);  // $ra first: the delay slot below depends on it
        sw(v0, v1, 4);
        call(ctx, gen::fn_sub_4C6E60_004c6e60);
    }
    // 0x004c4858
    charge(ctx, 2);
    v0 = 1;
    // 0x004c4878
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4C4930 [resEntryAllocate] -- allocates a resEntry in the arena, evicting old entries until it fits
// ($a0 = the owner, $a1 = where the owner keeps the pointer, $a2 = the data size, $a3 = the destroy
// notification) Repeats: a block of size + 24 from the resource heap (sub_4C6F30); found -> the entry is
// linked at the head of this frame's list (+36), owner / size / owner pointer / destroy set, the used bytes
// grow, *$a1 = the entry, returned. Not found -> the tail of the older list (+32) is evicted, or, when that is
// empty, the tail of this frame's list (its size added to +8); eviction: the entry's destroy notification (+20) if any,
// its owner's pointer (*+16) cleared, then an arena entry (+0 != 0) is unlinked, its size taken off the used bytes and
// its block returned to the resource heap (sub_4C6E60); an entry from outside the arena goes to RwFree. Nothing left to
// evict:
// *$a1 = 0, error 12 (the size), 0.
// 0x004C4930 sub_4C4930 -- 708 bytes; frame 0xA0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C4930(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c4930
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    s7 = a3;
    sq(s5, sp, 0x50);
    s6 = a0;
    sq(s4, sp, 0x40);
    s5 = a2;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = 0x960000;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = 0;
    s0 = addiu(s5, 24);
    s3 = addiu(s3, 380);  // &0x96017C (RwFree slot)
    for (;;) {
        // 0x004c4978: a block from the resource heap
        charge(ctx, 11);
        lw(v1, gp, -17408);  // 0x7CE8F0 (the resource module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        lw(a0, v0, resentry::kOwner);
        a1 = s0;
        jal(ctx, 0x4C498Cu, gen::fn_sub_4C6F30_004c6f30);
        v1 = sltu(0, v0);
        v1 = v1 ^ 0x1;
        if (v1 == 0) {
            break;
        }
        // 0x004c4a28: no room: the older list's tail
        charge(ctx, 8);
        lw(v1, gp, -17408);  // 0x7CE8F0 (the resource module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        a0 = addu(v0, v1);
        lw(v0, a0, 32);
        lw(s4, v0, 4);
        if (s4 == v0) {
            // 0x004c4b10: the older list is empty: this frame's tail
            charge(ctx, 4);
            lw(v0, a0, 36);
            lw(s4, v0, 4);
            if (s4 == v0) {
                // 0x004c4bc0: nothing to evict
                charge(ctx, 2);
                s1 = 1;
                backedge(ctx);
            } else {
                // 0x004c4b20: count it as evicted this frame; evict
                charge(ctx, 7);
                lw(v1, a0, 8);
                lw(v0, s4, resentry::kSize);
                v0 = addu(v1, v0);
                sw(v0, a0, 8);
                lw(v0, s4, resentry::kDestroy);
                if (v0 != 0) {
                    // 0x004c4b3c
                    charge(ctx, 3);
                    a0 = s4;
                    jalr(ctx, 0x4C4B3Cu, v0.u());
                }
                // 0x004c4b48
                charge(ctx, 3);
                lw(v0, s4, resentry::kOwnerRef);
                if (v0 != 0) {
                    // 0x004c4b54
                    charge(ctx, 1);
                    sw(zero, v0, 0);
                }
                // 0x004c4b58
                charge(ctx, 3);
                lw(a1, s4, resentry::kNext);
                if (a1 == 0) {
                    // 0x004c4ba8
                    charge(ctx, 5);
                    lw(v0, s3, 0);
                    a0 = s4;
                    jalr(ctx, 0x4C4BACu, v0.u());
                    backedge(ctx);
                } else {
                    // 0x004c4b64
                    charge(ctx, 17);
                    lw(v1, s4, resentry::kPrev);
                    v0 = 0x960000;
                    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                    a0 = s4;
                    sw(a1, v1, 0);
                    lw(a1, s4, resentry::kPrev);
                    lw(v1, s4, resentry::kNext);
                    sw(a1, v1, 4);
                    lw(v1, gp, -17408);  // 0x7CE8F0 (the resource module offset)
                    lw(a1, s4, resentry::kSize);
                    v1 = addu(v0, v1);
                    lw(v0, v1, 4);
                    v0 = subu(v0, a1);
                    link(ctx, 0x4C4B98u);  // $ra first: the delay slot below depends on it
                    sw(v0, v1, 4);
                    call(ctx, gen::fn_sub_4C6E60_004c6e60);
                    backedge(ctx);
                }
            }
        } else {
            // 0x004c4a48: evict the older entry
            charge(ctx, 3);
            lw(v0, s4, resentry::kDestroy);
            if (v0 != 0) {
                // 0x004c4a54
                charge(ctx, 3);
                a0 = s4;
                jalr(ctx, 0x4C4A54u, v0.u());
            }
            // 0x004c4a60
            charge(ctx, 3);
            lw(v0, s4, resentry::kOwnerRef);
            if (v0 != 0) {
                // 0x004c4a6c
                charge(ctx, 1);
                sw(zero, v0, 0);
            }
            // 0x004c4a70
            charge(ctx, 3);
            lw(a1, s4, resentry::kNext);
            if (a1 == 0) {
                // 0x004c4afc
                charge(ctx, 5);
                lw(v0, s3, 0);
                a0 = s4;
                jalr(ctx, 0x4C4B00u, v0.u());
                backedge(ctx);
            } else {
                // 0x004c4a7c
                charge(ctx, 15);
                lw(v1, s4, resentry::kPrev);
                v0 = 0x960000;
                v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                a0 = s4;
                sw(a1, v1, 0);
                lw(a1, s4, resentry::kPrev);
                lw(v1, s4, resentry::kNext);
                sw(a1, v1, 4);
                lw(v1, gp, -17408);  // 0x7CE8F0 (the resource module offset)
                lw(a1, s4, resentry::kSize);
                v1 = addu(v0, v1);
                lw(v0, v1, 4);
                v0 = subu(v0, a1);
                link(ctx, 0x4C4AB0u);  // $ra first: the delay slot below depends on it
                sw(v0, v1, 4);
                call(ctx, gen::fn_sub_4C6E60_004c6e60);
            }
        }
        // 0x004c4ab8
        charge(ctx, 4);
        v0 = sltu(0, s1);
        v0 = v0 ^ 0x1;
        if (v0 == 0) {
            goto L_004c4ac8_12;
        }
        backedge(ctx);
    }
    // 0x004c49a4: found: link at the head of this frame's list, fill the entry
    charge(ctx, 30);
    lw(v1, gp, -17408);  // 0x7CE8F0 (the resource module offset)
    a0 = 0x960000;
    a0 = addiu(a0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = addu(a0, v1);
    lw(v1, v1, 36);
    lw(v1, v1, 0);
    sw(v1, v0, 0);
    lw(v1, gp, -17408);  // 0x7CE8F0 (the resource module offset)
    v1 = addu(a0, v1);
    lw(v1, v1, 36);
    sw(v1, v0, 4);
    lw(v1, gp, -17408);  // 0x7CE8F0 (the resource module offset)
    v1 = addu(a0, v1);
    lw(v1, v1, 36);
    lw(v1, v1, 0);
    sw(v0, v1, 4);
    lw(v1, gp, -17408);  // 0x7CE8F0 (the resource module offset)
    v1 = addu(a0, v1);
    lw(v1, v1, 36);
    sw(v0, v1, 0);
    sw(s6, v0, resentry::kOwner);
    sw(s5, v0, resentry::kSize);
    sw(s2, v0, resentry::kOwnerRef);
    sw(s7, v0, resentry::kDestroy);
    lw(v1, gp, -17408);  // 0x7CE8F0 (the resource module offset)
    a0 = addu(a0, v1);
    lw(v1, a0, 4);
    v1 = addu(v1, s5);
    sw(v1, a0, 4);
    if (s2 != 0) {
        // 0x004c4a1c
        charge(ctx, 3);
        sw(v0, s2, 0);
    }
    // 0x004c4bc8 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
    return;
L_004c4ac8_12:  // out of room: error 12
    charge(ctx, 2);
    if (s2 != 0) {
        // 0x004c4ad0
        charge(ctx, 1);
        sw(zero, s2, 0);
    }
    // 0x004c4ad4
    charge(ctx, 10);
    v0 = 1;
    a1 = s5;
    sw(v0, sp, 0x98);
    a0 = 12;
    jal(ctx, 0x4C4AE0u, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0x9C);
    a0 = addiu(sp, 0x98);
    jal(ctx, 0x4C4AECu, gen::fn_sub_4C1C50_004c1c50);
    v0 = 0;
    // 0x004c4bc8 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// sub_4CBF20 [imageAllocatePixels] -- allocates an image's pixels (and palette) and marks them owned
// Stride = ((depth + 7) / 8) x width rounded up to 4; depth 4 / 8 adds a palette of 4 << depth bytes after the
// pixels. RwMalloc(stride x height + palette, hint 0x30018) (the product through the second multiplier, mult1);
// none: error 0x80000013 -> 0. Pixels, palette (0 without), flags |= 1. Returns the image.
// 0x004CBF20 sub_4CBF20 -- 304 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CBF20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cbf20
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, rwimage::kDepth);
    v0 = v1 ^ 0x4;
    s1 = sltiu(v0, 1);
    s3 = a0;
    if (s1 == 0) {
        // 0x004cbf4c
        charge(ctx, 2);
        v0 = v1 ^ 0x8;
        s1 = sltiu(v0, 1);
    }
    // 0x004cbf54
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x004cbf6c
        charge(ctx, 1);
        a0 = 0;
    } else {
        // 0x004cbf5c
        charge(ctx, 4);
        v0 = 1;
        v0 = dsllv(v0, v1);
        a0 = dsll(v0, 2);
    }
    // 0x004cbf70
    charge(ctx, 28);
    v0 = addiu(v1, 7);
    v0 = sra(v0, 3);
    sw(v0, s3, rwimage::kStride);
    lw(v1, s3, rwimage::kStride);
    lw(v0, s3, rwimage::kWidth);
    mult(v1, v1, v0);
    sw(v1, s3, rwimage::kStride);
    v0 = si(-4);
    lw(v1, s3, rwimage::kStride);
    v1 = addiu(v1, 3);
    v0 = v1 & v0;
    sw(v0, s3, rwimage::kStride);
    lw(v1, s3, rwimage::kStride);
    lw(v0, s3, rwimage::kHeight);
    mult1(s0, v1, v0);
    v0 = dsll32(a0, 0);
    v0 = dsra32(v0, 0);
    s2 = addu(s0, v0);
    v0 = 0x30000;
    a1 = v0 | 0x18;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    a0 = s2;
    jalr(ctx, 0x4CBFC8u, v0.u());
    sw(v0, s3, rwimage::kPixels);
    lw(v0, s3, rwimage::kPixels);
    if (v0 == 0) {
        // 0x004cc00c
        charge(ctx, 10);
        v0 = 1;
        a1 = s2;
        sw(v0, sp, 0x58);
        v0 = lui(0x8000);
        a0 = v0 | 0x13;
        jal(ctx, 0x4CC01Cu, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x5C);
        a0 = addiu(sp, 0x58);
        jal(ctx, 0x4CC028u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x004cbfe0
        charge(ctx, 2);
        if (s1 == 0) {
            // 0x004cbff0
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x004cbfe8
            charge(ctx, 2);
            v0 = addu(v0, s0);
        }
        // 0x004cbff4
        charge(ctx, 6);
        sw(v0, s3, rwimage::kPalette);
        lw(v1, s3, rwimage::kFlags);
        v0 = s3;
        v1 = v1 | 0x1;
        sw(v1, s3, rwimage::kFlags);
    }
    // 0x004cc034 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4CC1D0 [imageApplyMask] -- copies a mask image's alpha into an image (converting it to 32 bits)
// ($a0 = the image, $a1 = the mask) Different sizes: error 0x8000000A; a depth other than 4 / 8 / 32: error
// 0x80000009. A palettised image is first expanded: a temporary image (the image free list, its plugins) gets
// the pixels (sub_4CBF20, sub_4CD620 copies), the image is re-allocated at depth 32 and copied back, the
// temporary freed. Then each row: the mask's alpha byte (32-bit) or its palette entry's alpha (4 / 8-bit)
// goes to byte 3 of each pixel. Returns the image or 0.
// 0x004CC1D0 sub_4CC1D0 -- 1000 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CC1D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004cc1d0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    lw(v0, a1, 4);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 4);
    s3 = a1;
    if (s1 == v0) {
        // 0x004cc204
        charge(ctx, 4);
        lw(s5, s4, 8);
        lw(v0, s3, 8);
        if (s5 != v0) {
            goto L_004cc42c;
        }
        // 0x004cc214
        charge(ctx, 4);
        lw(s0, s4, 12);
        v0 = 32;
        if (s0 == v0) {
            // 0x004cc304
            charge(ctx, 1);
            lw(v0, s4, 8);
        L_004cc308:
            charge(ctx, 6);
            lw(t1, s3, 20);
            lw(a2, s3, 24);
            lw(t0, s4, 20);
            at = slt(0, v0);
            t2 = 0;
            if (at != 0) {
                // 0x004cc320
                charge(ctx, 5);
                lw(t3, s3, 16);
                v0 = 4;
                lw(a1, s3, 12);
                v1 = 8;
                a0 = 32;
                for (;;) {
                    // 0x004cc334
                    charge(ctx, 2);
                    a3 = t0;
                    if (a1 == a0) {
                        // 0x004cc3a8
                        charge(ctx, 5);
                        lw(t4, s4, 4);
                        t6 = t1;
                        at = slt(0, t4);
                        t5 = 0;
                        if (at != 0) {
                            // 0x004cc3bc
                            charge(ctx, 1);
                            for (;;) {
                                // 0x004cc3c0
                                charge(ctx, 8);
                                lbu(t4, t6, 3);
                                t5 = addiu(t5, 1);
                                sb(t4, a3, 3);
                                t6 = addiu(t6, 4);
                                lw(t4, s4, 4);
                                t4 = slt(t5, t4);
                                a3 = addiu(a3, 4);
                                if (t4 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                        }
                    } else {
                        // 0x004cc33c
                        charge(ctx, 2);
                        if (a1 != v1) {
                            // 0x004cc344
                            charge(ctx, 2);
                            if (a1 == v0) {
                                goto L_004cc358;
                            }
                            // 0x004cc34c
                            charge(ctx, 2);
                            goto L_004cc3e0;
                        }
                    L_004cc358:
                        charge(ctx, 5);
                        lw(t4, s4, 4);
                        t5 = t1;
                        at = slt(0, t4);
                        t6 = 0;
                        if (at != 0) {
                            // 0x004cc36c
                            charge(ctx, 1);
                            for (;;) {
                                // 0x004cc370
                                charge(ctx, 11);
                                lbu(t4, t5, 0);
                                t6 = addiu(t6, 1);
                                t4 = sll(t4, 2);
                                t5 = addiu(t5, 1);
                                t4 = addu(a2, t4);
                                lbu(t4, t4, 3);
                                sb(t4, a3, 3);
                                lw(t4, s4, 4);
                                t4 = slt(t6, t4);
                                a3 = addiu(a3, 4);
                                if (t4 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004cc39c
                            charge(ctx, 2);
                        }
                    }
                L_004cc3e0:
                    charge(ctx, 7);
                    lw(a3, s4, 8);
                    lw(t4, s4, 16);
                    t2 = addiu(t2, 1);
                    t1 = addu(t1, t3);
                    a3 = slt(t2, a3);
                    t0 = addu(t0, t4);
                    if (a3 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004cc3fc
                charge(ctx, 1);
            }
            // 0x004cc400
            charge(ctx, 2);
            v0 = s4;
        } else {
            // 0x004cc224
            charge(ctx, 3);
            v0 = 8;
            if (s0 != v0) {
                // 0x004cc230
                charge(ctx, 3);
                v0 = 4;
                if (s0 == v0) {
                    goto L_004cc244;
                }
                // 0x004cc23c
                charge(ctx, 2);
                v1 = 1;
                // 0x004cc408
                charge(ctx, 9);
                v0 = lui(0x8000);
                sw(v1, sp, 0x70);
                a0 = v0 | 0x9;
                jal(ctx, 0x4CC410u, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x74);
                a0 = addiu(sp, 0x70);
                jal(ctx, 0x4CC41Cu, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
                // 0x004cc594 (the shared epilogue, written out on this path)
                charge(ctx, 9);
                ld(ra, sp, 0x60);
                lq(s5, sp, 0x50);
                lq(s4, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x80);
                return;
            }
        L_004cc244:
            charge(ctx, 13);
            lw(a2, gp, -17336);  // 0x7CE938
            a0 = 0x960000;
            v1 = 0x30000;
            v0 = 0x960000;
            a0 = addiu(a0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            a1 = v1 | 0x18;
            lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
            v1 = addu(a0, a2);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x4CC264u);  // $ra = the return address
            lw(a0, v1, 0);
            call_ptr(ctx, jt);
            s2 = v0;
            if (s2 == 0) {
                // 0x004cc454
                charge(ctx, 2);
                s2 = 0;
                backedge(ctx);
            } else {
                // 0x004cc278
                charge(ctx, 10);
                sw(s1, s2, 4);
                a0 = 0x780000;
                sw(s5, s2, 8);
                a0 = addiu(a0, -6512);  // &0x77E690 (the RwCamera plugin registry)
                sw(s0, s2, 12);
                a1 = s2;
                sw(zero, s2, 20);
                sw(zero, s2, 24);
                link(ctx, 0x4CC298u);  // $ra first: the delay slot below depends on it
                sw(zero, s2, 0);
                call(ctx, gen::fn_sub_4C64B0_004c64b0);
            }
            // 0x004cc2a0
            charge(ctx, 2);
            if (s2 == 0) {
                // 0x004cc45c
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004cc2a8
                charge(ctx, 4);
                a0 = s2;
                jal(ctx, 0x4CC2A8u, gen::fn_sub_4CBF20_004cbf20);
                if (v0 != 0) {
                    // 0x004cc490
                    charge(ctx, 7);
                    a0 = s2;
                    a1 = s4;
                    jal(ctx, 0x4CC494u, gen::fn_sub_4CD620_004cd620);
                    lw(v0, s4, 0);
                    v0 = v0 & 0x1;
                    if (v0 != 0) {
                        // 0x004cc540
                        charge(ctx, 11);
                        v0 = 0x960000;
                        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                        jt = v0.u();  // the target, read before the delay slot
                        link(ctx, 0x4CC548u);  // $ra = the return address
                        lw(a0, s4, 20);
                        call_ptr(ctx, jt);
                        sw(zero, s4, 20);
                        v0 = si(-2);
                        sw(zero, s4, 24);
                        lw(v1, s4, 0);
                        v0 = v1 & v0;
                        sw(v0, s4, 0);
                        backedge(ctx);
                    }
                    // 0x004cc4ac
                    charge(ctx, 22);
                    v0 = 32;
                    a0 = s4;
                    link(ctx, 0x4CC4B4u);  // $ra first: the delay slot below depends on it
                    sw(v0, s4, 12);
                    call(ctx, gen::fn_sub_4CBF20_004cbf20);
                    a0 = s4;
                    a1 = s2;
                    jal(ctx, 0x4CC4C0u, gen::fn_sub_4CD620_004cd620);
                    s0 = 0x960000;
                    s0 = addiu(s0, 380);  // &0x96017C (RwFree slot)
                    lw(v0, s0, 0);  // 0x96017C (RwFree slot)
                    jt = v0.u();  // the target, read before the delay slot
                    link(ctx, 0x4CC4D4u);  // $ra = the return address
                    lw(a0, s2, 20);
                    call_ptr(ctx, jt);
                    sw(zero, s2, 20);
                    v0 = si(-2);
                    sw(zero, s2, 24);
                    lw(v1, s2, 0);
                    v0 = v1 & v0;
                    sw(v0, s2, 0);
                    lw(v0, s2, 0);
                    v0 = v0 & 0x1;
                    if (v0 != 0) {
                        // 0x004cc56c
                        charge(ctx, 10);
                        lw(v0, s0, 0);
                        jt = v0.u();  // the target, read before the delay slot
                        link(ctx, 0x4CC570u);  // $ra = the return address
                        lw(a0, s2, 20);
                        call_ptr(ctx, jt);
                        sw(zero, s2, 20);
                        v0 = si(-2);
                        sw(zero, s2, 24);
                        lw(v1, s2, 0);
                        v0 = v1 & v0;
                        sw(v0, s2, 0);
                        backedge(ctx);
                    }
                    // 0x004cc504
                    charge(ctx, 15);
                    a0 = 0x780000;
                    a1 = s2;
                    a0 = addiu(a0, -6512);  // &0x77E690 (the RwCamera plugin registry)
                    jal(ctx, 0x4CC50Cu, gen::fn_sub_4C6560_004c6560);
                    lw(a0, gp, -17336);  // 0x7CE938
                    v1 = 0x960000;
                    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                    v0 = 0x960000;
                    lw(v0, v0, 396);  // 0x96018C (free-list free slot)
                    v1 = addu(v1, a0);
                    lw(a0, v1, 0);
                    a1 = s2;
                    jalr(ctx, 0x4CC530u, v0.u());
                    lw(v0, s4, 8);
                    backedge(ctx);
                    goto L_004cc308;
                }
                // 0x004cc2b8
                charge(ctx, 4);
                lw(v0, s2, 0);
                v0 = v0 & 0x1;
                if (v0 != 0) {
                    // 0x004cc464
                    charge(ctx, 11);
                    v0 = 0x960000;
                    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                    jt = v0.u();  // the target, read before the delay slot
                    link(ctx, 0x4CC46Cu);  // $ra = the return address
                    lw(a0, s2, 20);
                    call_ptr(ctx, jt);
                    sw(zero, s2, 20);
                    v0 = si(-2);
                    sw(zero, s2, 24);
                    lw(v1, s2, 0);
                    v0 = v1 & v0;
                    sw(v0, s2, 0);
                    backedge(ctx);
                }
                // 0x004cc2c8
                charge(ctx, 15);
                a0 = 0x780000;
                a1 = s2;
                a0 = addiu(a0, -6512);  // &0x77E690 (the RwCamera plugin registry)
                jal(ctx, 0x4CC2D0u, gen::fn_sub_4C6560_004c6560);
                lw(a0, gp, -17336);  // 0x7CE938
                v1 = 0x960000;
                v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                v0 = 0x960000;
                lw(v0, v0, 396);  // 0x96018C (free-list free slot)
                v1 = addu(v1, a0);
                lw(a0, v1, 0);
                a1 = s2;
                jalr(ctx, 0x4CC2F4u, v0.u());
                v0 = 0;
            }
        }
        // 0x004cc594 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(ra, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x80);
        return;
    }
L_004cc42c:
    charge(ctx, 10);
    v1 = 1;
    v0 = lui(0x8000);
    sw(v1, sp, 0x78);
    a0 = v0 | 0xA;
    jal(ctx, 0x4CC438u, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0x7C);
    a0 = addiu(sp, 0x78);
    jal(ctx, 0x4CC444u, gen::fn_sub_4C1C50_004c1c50);
    v0 = 0;
    // 0x004cc594 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// sub_4F61C0 [rxHeapFreeBlocksNewEntry] -- appends an entry to the RxHeap's free-block array (grows by 32)
// ($a0 = the heap: +12 the array of 8-byte entries, +16 capacity, +20 count) A full array grows by 32 entries
// (RwRealloc, hint 0x1030509); when it moved, each entry's block (+4) gets its back-pointer (+12) updated; a
// failure is error 0x80000013 and the capacity is put back. Returns the new entry or 0.
// 0x004F61C0 sub_4F61C0 -- 272 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F61C0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f61c0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 20);
    lw(v0, a0, 16);
    lw(s1, a0, 12);
    at = sltu(s0, v0);
    s2 = a0;
    if (at == 0) {
        // 0x004f6210
        charge(ctx, 12);
        v1 = addiu(v0, 32);
        v0 = 0x1030000;
        sw(v1, s2, 16);
        a2 = v0 | 0x409;  // &0x1030409
        lw(a0, s2, 12);
        v0 = 0x960000;
        lw(v0, v0, 384);  // 0x960180 (RwRealloc slot)
        a1 = sll(v1, 3);
        jalr(ctx, 0x4F622Cu, v0.u());
        s1 = v0;
        if (s1 == 0) {
            // 0x004f6280
            charge(ctx, 14);
            v1 = 1;
            v0 = lui(0x8000);
            sw(v1, sp, 0x48);
            a0 = v0 | 0x13;
            lw(v0, s2, 16);
            a1 = sll(v0, 3);
            jal(ctx, 0x4F6294u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x4C);
            a0 = addiu(sp, 0x48);
            jal(ctx, 0x4F62A0u, gen::fn_sub_4C1C50_004c1c50);
            lw(v0, s2, 16);
            v0 = addiu(v0, -32);
            sw(v0, s2, 16);
            backedge(ctx);
        } else {
            // 0x004f6240
            charge(ctx, 3);
            lw(v0, s2, 12);
            if (s1 != v0) {
                // 0x004f624c
                charge(ctx, 2);
                if (s0 != 0) {
                    // 0x004f6254
                    charge(ctx, 1);
                    v1 = s1;
                    for (;;) {
                        // 0x004f6258
                        charge(ctx, 7);
                        lw(v0, v1, 4);
                        s0 = addiu(s0, -1);
                        sw(v1, v0, 12);
                        v1 = addiu(v1, 8);
                        if (s0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004f6274
                    charge(ctx, 1);
                }
            }
            // 0x004f6278
            charge(ctx, 2);
            sw(s1, s2, 12);
            backedge(ctx);
        }
    }
    // 0x004f61ec
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x004f61f4
        charge(ctx, 5);
        lw(v0, s2, 20);
        v1 = addiu(v0, 1);
        v0 = sll(v0, 3);
        sw(v1, s2, 20);
        s1 = addu(s1, v0);
    }
    // 0x004f6208
    charge(ctx, 2);
    v0 = s1;
    // 0x004f62b8
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4933D0 [geometryUnlock] -- unlocks a geometry: rebuilds its mesh (tri-strips or tri-list) when it has none
// A geometry that has a mesh (+84) is returned. Else a build mesh for its triangles (sub_495B10); the
// triangles' distinct materials, textures and pipelines are counted in three scratch arrays (RwMalloc x3,
// linear searches), each triangle added (sub_495CF0 with its material from sub_495320), the arrays freed;
// then sub_499140 (bit 0 of +8: tri-strips) makes the mesh header (+84). Failure frees the build mesh
// (sub_495C20) -> 0. Returns the geometry.
// 0x004933D0 sub_4933D0 -- 828 bytes; frame 0xC0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq)
void sub_4933D0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004933d0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    s6 = 0;
    sq(s4, sp, 0x50);
    s5 = a0;
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    s3 = 0;
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    lw(v0, a0, 84);
    s2 = 0;
    if (v0 == 0) {
        // 0x0049341c
        charge(ctx, 4);
        link(ctx, 0x49341Cu);  // $ra first: the delay slot below depends on it
        lw(a0, s5, 16);
        call(ctx, gen::fn_sub_495B10_00495b10);
        sw(v0, sp, 0xB4);
        if (v0 == 0) {
            // 0x004936d8
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0049342c
            charge(ctx, 4);
            lw(v0, s5, 36);
            at = slt(0, v0);
            if (at != 0) {
                // 0x0049343c
                charge(ctx, 25);
                s0 = sll(v0, 2);
                s1 = 0x960000;
                v0 = 0x10000;
                s1 = addiu(s1, 376);  // &0x960178 (RwMalloc slot)
                a1 = v0 | 0x6;
                lw(v0, s1, 0);  // 0x960178 (RwMalloc slot)
                a0 = s0;
                jalr(ctx, 0x493454u, v0.u());
                s4 = v0;
                v1 = 0x10000;
                lw(v0, s1, 0);  // 0x960178 (RwMalloc slot)
                a0 = s0;
                a1 = v1 | 0x503;
                jalr(ctx, 0x49346Cu, v0.u());
                lw(v1, s1, 0);  // 0x960178 (RwMalloc slot)
                a0 = s0;
                sw(v0, sp, 0xBC);
                v0 = 0x10000;
                a1 = v0 | 0x503;
                jalr(ctx, 0x493484u, v1.u());
                sw(v0, sp, 0xB8);
                lw(v0, s5, 16);
                at = slt(0, v0);
                s7 = 0;
                if (at != 0) {
                    // 0x004934a0
                    charge(ctx, 1);
                    fp = 0;
                    for (;;) {
                        // 0x004934a4
                        charge(ctx, 12);
                        lw(v0, s5, 44);
                        a0 = addiu(s5, 32);
                        s1 = addu(v0, fp);
                        lhu(a1, s1, 6);
                        s0 = 0;
                        jal(ctx, 0x4934B4u, gen::fn_sub_495320_00495320);
                        lw(a0, v0, 0);
                        v1 = s3 & 0xFFFF;
                        at = slt(0, v1);
                        a1 = v0;
                        t2 = 0;
                        if (at != 0) {
                            // 0x004934d4
                            charge(ctx, 1);
                            for (;;) {
                                // 0x004934d8
                                charge(ctx, 6);
                                v0 = t2 & 0xFFFF;
                                v0 = sll(v0, 2);
                                v0 = addu(s4, v0);
                                lw(v0, v0, 0);
                                if (v0 == a0) {
                                    break;
                                }
                                // 0x004934f0
                                charge(ctx, 5);
                                v0 = addiu(t2, 1);
                                t2 = v0 & 0xFFFF;
                                v0 = slt(t2, v1);
                                if (v0 == 0) {
                                    goto L_00493504_10;
                                }
                                backedge(ctx);
                            }
                        }
                    L_00493508:
                        charge(ctx, 3);
                        v0 = t2 & 0xFFFF;
                        if (v0 == v1) {
                            // 0x00493670
                            charge(ctx, 6);
                            v1 = sll(v0, 2);
                            v0 = addiu(s3, 1);
                            v1 = addu(s4, v1);
                            s3 = v0 & 0xFFFF;
                            sw(a0, v1, 0);
                            backedge(ctx);
                        } else {
                            // 0x00493514
                            charge(ctx, 1);
                        }
                        // 0x00493518
                        charge(ctx, 2);
                        if (a0 != 0) {
                            // 0x00493520
                            charge(ctx, 2);
                            lw(s0, a0, 0);
                        }
                        // 0x00493528
                        charge(ctx, 4);
                        a0 = s2 & 0xFFFF;
                        at = slt(0, a0);
                        t3 = 0;
                        if (at != 0) {
                            for (;;) {
                                // 0x00493538
                                charge(ctx, 7);
                                v0 = t3 & 0xFFFF;
                                v1 = sll(v0, 2);
                                lw(v0, sp, 0xBC);
                                v0 = addu(v0, v1);
                                lw(v0, v0, 0);
                                if (v0 != s0) {
                                    // 0x00493554
                                    charge(ctx, 5);
                                    v0 = addiu(t3, 1);
                                    t3 = v0 & 0xFFFF;
                                    v0 = slt(t3, a0);
                                    if (v0 != 0) {
                                        backedge(ctx);
                                        continue;
                                    }
                                }
                                break;
                            }
                        }
                        // 0x00493568
                        charge(ctx, 3);
                        v0 = t3 & 0xFFFF;
                        if (v0 == a0) {
                            // 0x00493688
                            charge(ctx, 7);
                            v1 = sll(v0, 2);
                            lw(v0, sp, 0xBC);
                            v1 = addu(v0, v1);
                            v0 = addiu(s2, 1);
                            sw(s0, v1, 0);
                            s2 = v0 & 0xFFFF;
                            backedge(ctx);
                        } else {
                            // 0x00493574
                            charge(ctx, 1);
                        }
                        // 0x00493578
                        charge(ctx, 5);
                        lw(v0, a1, 8);
                        a3 = s6 & 0xFFFF;
                        at = slt(0, a3);
                        v1 = 0;
                        if (at != 0) {
                            // 0x0049358c
                            charge(ctx, 1);
                            for (;;) {
                                // 0x00493590
                                charge(ctx, 7);
                                a0 = v1 & 0xFFFF;
                                a2 = sll(a0, 2);
                                lw(a0, sp, 0xB8);
                                a0 = addu(a0, a2);
                                lw(a0, a0, 0);
                                if (a0 != v0) {
                                    // 0x004935ac
                                    charge(ctx, 5);
                                    v1 = addiu(v1, 1);
                                    v1 = v1 & 0xFFFF;
                                    a0 = slt(v1, a3);
                                    if (a0 != 0) {
                                        backedge(ctx);
                                        continue;
                                    }
                                }
                                break;
                            }
                        }
                        // 0x004935c0
                        charge(ctx, 3);
                        a0 = v1 & 0xFFFF;
                        if (a0 == a3) {
                            // 0x004936a8
                            charge(ctx, 7);
                            a2 = sll(a0, 2);
                            lw(a0, sp, 0xB8);
                            a2 = addu(a0, a2);
                            a0 = addiu(s6, 1);
                            sw(v0, a2, 0);
                            s6 = a0 & 0xFFFF;
                            backedge(ctx);
                        } else {
                            // 0x004935cc
                            charge(ctx, 1);
                        }
                        // 0x004935d0
                        charge(ctx, 12);
                        sd(v1, sp, 0x0);
                        lw(a0, sp, 0xB4);
                        lhu(a3, s1, 2);
                        lhu(t0, s1, 4);
                        lhu(t1, s1, 6);
                        link(ctx, 0x4935E4u);  // $ra first: the delay slot below depends on it
                        lhu(a2, s1, 0);
                        call(ctx, gen::fn_sub_495CF0_00495cf0);
                        lw(v0, s5, 16);
                        s7 = addiu(s7, 1);
                        v0 = slt(s7, v0);
                        fp = addiu(fp, 0x8);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x00493600
                charge(ctx, 11);
                s0 = 0x960000;
                s0 = addiu(s0, 380);  // &0x96017C (RwFree slot)
                lw(v0, s0, 0);  // 0x96017C (RwFree slot)
                a0 = s4;
                jalr(ctx, 0x49360Cu, v0.u());
                lw(v0, s0, 0);  // 0x96017C (RwFree slot)
                jt = v0.u();  // the target, read before the delay slot
                link(ctx, 0x493618u);  // $ra = the return address
                lw(a0, sp, 0xBC);
                call_ptr(ctx, jt);
                lw(v0, s0, 0);  // 0x96017C (RwFree slot)
                jt = v0.u();  // the target, read before the delay slot
                link(ctx, 0x493624u);  // $ra = the return address
                lw(a0, sp, 0xB8);
                call_ptr(ctx, jt);
            }
            // 0x0049362c
            charge(ctx, 4);
            lw(v0, s5, 8);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x00493650
                charge(ctx, 3);
                lw(a0, sp, 0xB4);
                a1 = 0;
                jal(ctx, 0x493654u, gen::fn_sub_499140_00499140);
            } else {
                // 0x0049363c
                charge(ctx, 5);
                lw(a0, sp, 0xB4);
                a1 = 1;
                jal(ctx, 0x493640u, gen::fn_sub_499140_00499140);
            }
            // 0x0049365c
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x004936c8
                charge(ctx, 4);
                link(ctx, 0x4936C8u);  // $ra first: the delay slot below depends on it
                lw(a0, sp, 0xB4);
                call(ctx, gen::fn_sub_495C20_00495c20);
                v0 = 0;
            } else {
                // 0x00493664
                charge(ctx, 3);
                sw(v0, s5, 84);
                v0 = s5;
            }
        }
    } else {
        // 0x00493414
        charge(ctx, 2);
        v0 = s5;
    }
    // 0x004936dc (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0xC0);
    return;
L_00493504_10:
    charge(ctx, 1);
    goto L_00493508;
}

// sub_495CF0 [buildMeshAddTriangle] -- appends a triangle to a build mesh (20-byte records, grows by one)
// ($a0 = the build mesh {+0 capacity, +4 count, +8 records}, $a1 = the material, $a2..$a3 / $t0..$t3 = the
// three vertex indices and the three extra u16s) A full array grows to count + 1 records (RwRealloc, or RwMalloc
// the first time; hint 0x1030502; failure: error 0x80000013 -> 0). The record: +0/+2/+4 the indices, +8 the
// material, +12..+18 the four u16s. Returns the build mesh.
// 0x00495CF0 sub_495CF0 -- 532 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_495CF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00495cf0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    fp = t3;
    sq(s6, sp, 0x60);
    s7 = t2;
    sq(s5, sp, 0x50);
    s6 = t1;
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    s2 = a3;
    sq(s0, sp, 0x0);
    lw(a1, a0, 4);
    lw(v0, a0, 0);
    v0 = sltu(a1, v0);
    s1 = t0;
    if (v0 == 0) {
        // 0x00495d4c
        charge(ctx, 5);
        v1 = addiu(a1, 1);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        s0 = sll(v0, 2);
        if (a1 == 0) {
            // 0x00495d84
            charge(ctx, 6);
            v0 = 0x1030000;
            a1 = v0 | 0x502;  // &0x1030502
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
            a0 = s0;
            jalr(ctx, 0x495D94u, v0.u());
        } else {
            // 0x00495d60
            charge(ctx, 9);
            v0 = 0x960000;
            v1 = 0x1030000;
            lw(a0, s5, 8);
            a1 = s0;
            lw(v0, v0, 384);  // 0x960180 (RwRealloc slot)
            a2 = v1 | 0x502;  // &0x1030502
            jalr(ctx, 0x495D74u, v0.u());
        }
        // 0x00495d9c
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x00495da4
            charge(ctx, 4);
            sw(v0, s5, 8);
            lw(v0, s5, 4);
            v0 = addiu(v0, 1);
            sw(v0, s5, 0);
            goto L_00495db4;
        }
        // 0x00495eac
        charge(ctx, 10);
        v0 = 2;
        a1 = s0;
        sw(v0, sp, 0xA8);
        v0 = lui(0x8000);
        a0 = v0 | 0x13;
        jal(ctx, 0x495EBCu, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0xAC);
        a0 = addiu(sp, 0xA8);
        jal(ctx, 0x495EC8u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
        // 0x00495ed4 (the shared epilogue, written out on this path)
        charge(ctx, 12);
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
        return;
    }
L_00495db4:
    charge(ctx, 62);
    lw(a0, s5, 4);
    v0 = s5;
    lw(a1, s5, 8);
    lhu(a2, sp, 0xB0);
    v1 = sll(a0, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a1);
    sw(s4, v1, 8);
    lw(a1, s5, 4);
    lw(v1, s5, 8);
    a0 = sll(a1, 2);
    a0 = addu(a0, a1);
    a0 = sll(a0, 2);
    v1 = addu(v1, a0);
    sh(s3, v1, 0);
    lw(a0, s5, 4);
    lw(a1, s5, 8);
    v1 = sll(a0, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a1);
    sh(s2, v1, 2);
    lw(a0, s5, 4);
    lw(a1, s5, 8);
    v1 = sll(a0, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a1);
    sh(s1, v1, 4);
    lw(a0, s5, 4);
    lw(a1, s5, 8);
    v1 = sll(a0, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a1);
    sh(s6, v1, 12);
    lw(a0, s5, 4);
    lw(a1, s5, 8);
    v1 = sll(a0, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a1);
    sh(s7, v1, 14);
    lw(a0, s5, 4);
    lw(a1, s5, 8);
    v1 = sll(a0, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a1);
    sh(fp, v1, 16);
    lw(a0, s5, 4);
    lw(a1, s5, 8);
    v1 = sll(a0, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a1);
    sh(a2, v1, 18);
    lw(v1, s5, 4);
    v1 = addiu(v1, 1);
    sw(v1, s5, 4);
    // 0x00495ed4 (the shared epilogue, written out on this path)
    charge(ctx, 12);
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

// sub_4967A0 [meshSortTriListPolygons] -- reorders a tri-list mesh's triangles so neighbours share no vertex
// ($a0 = the mesh {+0 the u16 indices, +4 their count}) A bitmap of (max index + 31) / 8 bytes and a copy of the
// indices (RwMalloc); repeated passes take, in order, the triangles none of whose vertices is marked in this
// pass (a 0xFFFF-filled triangle is skipped), writing them back and marking their vertices, until every
// triangle is placed. Frees both blocks.
// 0x004967A0 sub_4967A0 -- 804 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4967A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004967a0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    v1 = lui(0xAAAA);
    sd(ra, sp, 0x70);
    v1 = v1 | 0xAAAB;
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 4);
    lw(s3, a0, 0);
    multu(zero, v1, v0);
    mfhi(a0);
    at = sltu(0, v0);
    t3 = 0;
    v1 = 0;
    s0 = srl(a0, 1);
    if (at != 0) {
        // 0x004967f4
        charge(ctx, 3);
        at = sltiu(v0, 9);
        t4 = addiu(v0, -8);
        if (at == 0) {
            // 0x00496800
            charge(ctx, 1);
            t5 = s3;
            for (;;) {
                // 0x00496804
                charge(ctx, 20);
                lhu(a2, t5, 0);
                v1 = addiu(v1, 8);
                lhu(a1, t5, 2);
                a0 = sltu(v1, t4);
                lhu(t2, t5, 4);
                lhu(t1, t5, 6);
                lhu(t0, t5, 8);
                lhu(a3, t5, 10);
                t3 = t3 | a2;
                t3 = t3 | a1;
                lhu(a2, t5, 12);
                lhu(a1, t5, 14);
                t2 = t3 | t2;
                t1 = t2 | t1;
                t0 = t1 | t0;
                a3 = t0 | a3;
                a2 = a3 | a2;
                t3 = a2 | a1;
                t5 = addiu(t5, 16);
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00496854
            charge(ctx, 1);
        }
        // 0x00496858
        charge(ctx, 3);
        at = sltu(v1, v0);
        if (at != 0) {
            // 0x00496864
            charge(ctx, 2);
            a0 = sll(v1, 1);
            a2 = addu(s3, a0);
            for (;;) {
                // 0x0049686c
                charge(ctx, 7);
                lhu(a1, a2, 0);
                v1 = addiu(v1, 1);
                a0 = sltu(v1, v0);
                t3 = t3 | a1;
                a2 = addiu(a2, 2);
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x00496888
    charge(ctx, 12);
    v0 = addiu(t3, 31);
    s1 = srl(v0, 3);
    s2 = 0x960000;
    v0 = 0x10000;
    s2 = addiu(s2, 376);  // &0x960178 (RwMalloc slot)
    a1 = v0 | 0x502;
    lw(v0, s2, 0);  // 0x960178 (RwMalloc slot)
    a0 = s1;
    jalr(ctx, 0x4968A4u, v0.u());
    s4 = v0;
    if (s4 == 0) {
        // 0x00496a98
        charge(ctx, 1);
        v0 = s5;
    } else {
        // 0x004968b8
        charge(ctx, 10);
        v1 = 0x10000;
        lw(v0, s2, 0);
        a1 = v1 | 0x502;
        lw(v1, s5, 4);
        s6 = sll(v1, 1);
        a0 = s6;
        jalr(ctx, 0x4968CCu, v0.u());
        s2 = v0;
        if (s2 != 0) {
            // 0x004968e0
            charge(ctx, 7);
            a2 = s6;
            a0 = s2;
            a1 = s3;
            jal(ctx, 0x4968E8u, gen::fn_memcpy_00521250);
            at = sltu(0, s0);
            t4 = 0;
            if (at != 0) {
                // 0x004968fc
                charge(ctx, 3);
                a0 = 1;
                a2 = 0xFFFF;
                t1 = addiu(s1, -1);
                for (;;) {
                    // 0x00496908
                    charge(ctx, 3);
                    a1 = s4;
                    v1 = t1;
                    if (s1 != 0) {
                        // 0x00496914
                        charge(ctx, 1);
                        for (;;) {
                            // 0x00496918
                            charge(ctx, 7);
                            sb(zero, a1, 0);
                            v0 = v1;
                            a1 = addiu(a1, 1);
                            v1 = addiu(v1, -1);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x00496934
                        charge(ctx, 1);
                    }
                    // 0x00496938
                    charge(ctx, 3);
                    at = sltu(0, s0);
                    t3 = 0;
                    if (at != 0) {
                        // 0x00496944
                        charge(ctx, 1);
                        t2 = s2;
                        for (;;) {
                            // 0x00496948
                            charge(ctx, 7);
                            lhu(t0, t2, 2);
                            lhu(a1, t2, 0);
                            lhu(a3, t2, 4);
                            v0 = a1 & t0;
                            v0 = a3 & v0;
                            if (v0 != a2) {
                                // 0x00496964
                                charge(ctx, 9);
                                v1 = sra(a1, 5);
                                v0 = a1 & 0x1F;
                                a1 = sll(v1, 2);
                                v1 = sllv(a0, v0);
                                a1 = addu(s4, a1);
                                lw(v0, a1, 0);
                                t5 = v1 & v0;
                                if (t5 == 0) {
                                    // 0x00496988
                                    charge(ctx, 9);
                                    t5 = t0 & 0x1F;
                                    t0 = sra(t0, 5);
                                    t5 = sllv(a0, t5);
                                    t0 = sll(t0, 2);
                                    t0 = addu(s4, t0);
                                    lw(t0, t0, 0);
                                    t0 = t5 & t0;
                                    if (t0 == 0) {
                                        // 0x004969ac
                                        charge(ctx, 9);
                                        t0 = a3 & 0x1F;
                                        a3 = sra(a3, 5);
                                        t0 = sllv(a0, t0);
                                        a3 = sll(a3, 2);
                                        a3 = addu(s4, a3);
                                        lw(a3, a3, 0);
                                        a3 = t0 & a3;
                                        if (a3 == 0) {
                                            // 0x004969d0
                                            charge(ctx, 32);
                                            v0 = v0 | v1;
                                            t4 = addiu(t4, 1);
                                            sw(v0, a1, 0);
                                            lhu(v0, t2, 2);
                                            v1 = v0 & 0x1F;
                                            v0 = sra(v0, 5);
                                            a1 = sllv(a0, v1);
                                            v0 = sll(v0, 2);
                                            v1 = addu(s4, v0);
                                            lw(v0, v1, 0);
                                            v0 = v0 | a1;
                                            sw(v0, v1, 0);
                                            lhu(v0, t2, 4);
                                            v1 = v0 & 0x1F;
                                            v0 = sra(v0, 5);
                                            a1 = sllv(a0, v1);
                                            v0 = sll(v0, 2);
                                            v1 = addu(s4, v0);
                                            lw(v0, v1, 0);
                                            v0 = v0 | a1;
                                            sw(v0, v1, 0);
                                            lhu(v0, t2, 0);
                                            sh(v0, s3, 0);
                                            lhu(v0, t2, 2);
                                            sh(v0, s3, 2);
                                            lhu(v0, t2, 4);
                                            sh(v0, s3, 4);
                                            sh(a2, t2, 4);
                                            s3 = addiu(s3, 6);
                                            sh(a2, t2, 2);
                                            sh(a2, t2, 0);
                                        }
                                    }
                                }
                            }
                            // 0x00496a50
                            charge(ctx, 4);
                            t3 = addiu(t3, 1);
                            v0 = sltu(t3, s0);
                            t2 = addiu(t2, 6);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                    // 0x00496a60
                    charge(ctx, 3);
                    v0 = sltu(t4, s0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00496a6c
                charge(ctx, 1);
            }
            // 0x00496a70
            charge(ctx, 4);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            a0 = s2;
            jalr(ctx, 0x496A78u, v0.u());
        }
        // 0x00496a80
        charge(ctx, 6);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        a0 = s4;
        jalr(ctx, 0x496A88u, v0.u());
        v0 = s5;
    }
    // 0x00496a9c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// sub_4982B0 [triStripJoin] -- joins the strips of a tri-strip build into one index list (degenerate links)
// Part of the tri-strip mesh build (sub_498720): the strips found by sub_497600 are chained with repeated
// indices into the mesh's index array; scratch through RwMalloc / RwFree and the module's free list (gp
// 0x7CE850).
// 0x004982B0 sub_4982B0 -- 1136 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4982B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004982b0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a0;
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 0);
    s1 = a1;
    if (v0 != 0) {
        // 0x004982ec
        charge(ctx, 15);
        lw(a2, gp, -17568);  // 0x7CE850
        a0 = 0x960000;
        v1 = 0x30000;
        v0 = 0x960000;
        a0 = addiu(a0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        a1 = v1 | 0x502;
        lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
        v1 = addu(a0, a2);
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x49830Cu);  // $ra = the return address
        lw(a0, v1, 4);
        call_ptr(ctx, jt);
        sw(zero, v0, 4);
        sw(zero, v0, 8);
        lw(a0, s6, 0);
        s0 = v0;
        if (a0 != 0) {
            for (;;) {
                // 0x00498328
                charge(ctx, 8);
                lw(v1, a0, 4);
                lw(v0, s0, 8);
                v1 = addiu(v1, 6);
                v0 = addu(v0, v1);
                sw(v0, s0, 8);
                lw(a0, a0, 12);
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00498348
        charge(ctx, 13);
        lw(a0, s0, 8);
        v0 = 0x960000;
        v1 = 0x30000;
        lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
        a1 = v1 | 0x502;
        a0 = sll(a0, 2);
        jalr(ctx, 0x49835Cu, v0.u());
        sw(v0, s0, 0);
        lw(s2, s6, 0);
        lw(v0, s2, 4);
        at = sltu(0, v0);
        a2 = 0;
        if (at != 0) {
            // 0x0049837c
            charge(ctx, 1);
            a1 = 0;
            for (;;) {
                // 0x00498380
                charge(ctx, 16);
                lw(a0, s2, 0);
                a2 = addiu(a2, 1);
                lw(v1, s0, 4);
                lw(v0, s0, 0);
                a0 = addu(a0, a1);
                lhu(a0, a0, 0);
                v1 = sll(v1, 1);
                v0 = addu(v0, v1);
                sh(a0, v0, 0);
                lw(v0, s0, 4);
                v0 = addiu(v0, 1);
                sw(v0, s0, 4);
                lw(v0, s2, 4);
                v0 = sltu(a2, v0);
                a1 = addiu(a1, 2);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004983c0
        charge(ctx, 19);
        s4 = 0x960000;
        s4 = addiu(s4, 380);  // &0x96017C (RwFree slot)
        lw(v0, s4, 0);  // 0x96017C (RwFree slot)
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x4983CCu);  // $ra = the return address
        lw(a0, s2, 0);
        call_ptr(ctx, jt);
        sw(zero, s2, 0);
        v1 = 0x960000;
        lw(a0, gp, -17568);  // 0x7CE850
        s5 = 0x960000;
        v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        s5 = addiu(s5, 396);  // &0x96018C (free-list free slot)
        lw(v0, s5, 0);  // 0x96018C (free-list free slot)
        lw(s3, s2, 12);
        v1 = addu(v1, a0);
        lw(a0, v1, 4);
        a1 = s2;
        jalr(ctx, 0x4983FCu, v0.u());
        if (s3 != 0) {
            for (;;) {
                // 0x0049840c
                charge(ctx, 2);
                s2 = s3;
                if (s3 != 0) {
                    // 0x00498414
                    charge(ctx, 5);
                    lw(a2, s0, 4);
                    lw(v1, s0, 0);
                    v0 = sll(a2, 1);
                    a1 = addu(v1, v0);
                    lhu(a0, a1, -2);
                    for (;;) {
                        // 0x00498428
                        charge(ctx, 4);
                        lw(v0, s2, 0);
                        lhu(v1, v0, 0);
                        if (v1 == a0) {
                            goto L_00498438_11;
                        }
                        // 0x00498460
                        charge(ctx, 3);
                        lw(s2, s2, 12);
                        if (s2 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0049846c
                    charge(ctx, 1);
                }
            L_00498470:
                charge(ctx, 2);
                if (s2 == 0) {
                    // 0x004984e0
                    charge(ctx, 2);
                    s2 = s3;
                    if (s3 == 0) {
                        backedge(ctx);
                    } else {
                        // 0x004984e8
                        charge(ctx, 6);
                        lw(a2, s0, 4);
                        lw(v1, s0, 0);
                        v0 = sll(a2, 1);
                        a1 = addu(v1, v0);
                        lhu(a0, a1, -4);
                        for (;;) {
                            // 0x00498500
                            charge(ctx, 4);
                            lw(v0, s2, 0);
                            lhu(v1, v0, 0);
                            if (v1 == a0) {
                                goto L_00498510_25;
                            }
                            // 0x00498558
                            charge(ctx, 3);
                            lw(s2, s2, 12);
                            if (s2 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x00498564
                        charge(ctx, 2);
                        backedge(ctx);
                    }
                }
            L_00498478:
                charge(ctx, 2);
                if (s2 == 0) {
                    // 0x00498588
                    charge(ctx, 4);
                    lw(v1, s0, 4);
                    v0 = v1 & 0x1;
                    s2 = s3;
                    if (v0 != 0) {
                        // 0x00498598
                        charge(ctx, 2);
                        if (s1 == 0) {
                            goto L_00498600;
                        }
                        // 0x004985a0
                        charge(ctx, 23);
                        lw(v0, s0, 0);
                        v1 = sll(v1, 1);
                        v1 = addu(v0, v1);
                        lhu(v0, v1, -2);
                        sh(v0, v1, 0);
                        lw(a0, s3, 0);
                        lw(v1, s0, 4);
                        lw(v0, s0, 0);
                        lhu(a0, a0, 0);
                        v1 = sll(v1, 1);
                        v0 = addu(v0, v1);
                        sh(a0, v0, 2);
                        lw(a0, s3, 0);
                        lw(v1, s0, 4);
                        lw(v0, s0, 0);
                        lhu(a0, a0, 0);
                        v1 = sll(v1, 1);
                        v0 = addu(v0, v1);
                        sh(a0, v0, 4);
                        lw(v0, s0, 4);
                        v0 = addiu(v0, 3);
                        sw(v0, s0, 4);
                        backedge(ctx);
                        goto L_00498480;
                    }
                L_00498600:
                    charge(ctx, 16);
                    lw(v0, s0, 0);
                    v1 = sll(v1, 1);
                    v1 = addu(v0, v1);
                    lhu(v0, v1, -2);
                    sh(v0, v1, 0);
                    lw(a0, s3, 0);
                    lw(v1, s0, 4);
                    lw(v0, s0, 0);
                    lhu(a0, a0, 0);
                    v1 = sll(v1, 1);
                    v0 = addu(v0, v1);
                    sh(a0, v0, 2);
                    lw(v0, s0, 4);
                    v0 = addiu(v0, 2);
                    sw(v0, s0, 4);
                    backedge(ctx);
                }
            L_00498480:
                charge(ctx, 4);
                lw(v0, s2, 4);
                at = sltu(0, v0);
                a2 = 0;
                if (at != 0) {
                    // 0x00498490
                    charge(ctx, 2);
                    a1 = 0;
                    for (;;) {
                        // 0x00498498
                        charge(ctx, 16);
                        lw(a0, s2, 0);
                        lw(v1, s0, 4);
                        a2 = addiu(a2, 1);
                        lw(v0, s0, 0);
                        a0 = addu(a0, a1);
                        lhu(a0, a0, 0);
                        v1 = sll(v1, 1);
                        v0 = addu(v0, v1);
                        sh(a0, v0, 0);
                        lw(v0, s0, 4);
                        v0 = addiu(v0, 1);
                        sw(v0, s0, 4);
                        lw(v0, s2, 4);
                        v0 = sltu(a2, v0);
                        a1 = addiu(a1, 2);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004984d8
                    charge(ctx, 2);
                }
                // 0x00498640
                charge(ctx, 5);
                lw(v0, s4, 0);
                jt = v0.u();  // the target, read before the delay slot
                link(ctx, 0x498644u);  // $ra = the return address
                lw(a0, s2, 0);
                call_ptr(ctx, jt);
                sw(zero, s2, 0);
                if (s3 == s2) {
                    // 0x00498688
                    charge(ctx, 10);
                    lw(a0, gp, -17568);  // 0x7CE850
                    v1 = 0x960000;
                    lw(v0, s5, 0);
                    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                    lw(s3, s3, 12);
                    v1 = addu(v1, a0);
                    lw(a0, v1, 4);
                    a1 = s2;
                    jalr(ctx, 0x4986A4u, v0.u());
                } else {
                    // 0x00498654
                    charge(ctx, 3);
                    lw(v0, s3, 12);
                    a0 = s3;
                    if (v0 == s2) {
                        // 0x004986c8
                        charge(ctx, 1);
                        lw(v0, s2, 12);
                    } else {
                        for (;;) {
                            // 0x00498660
                            charge(ctx, 7);
                            lw(a0, a0, 12);
                            lw(v0, a0, 12);
                            if (v0 == s2) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x0049867c
                        charge(ctx, 2);
                        lw(v0, s2, 12);
                    }
                    // 0x004986cc
                    charge(ctx, 11);
                    v1 = 0x960000;
                    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                    sw(v0, a0, 12);
                    lw(a0, gp, -17568);  // 0x7CE850
                    lw(v0, s5, 0);
                    v1 = addu(v1, a0);
                    lw(a0, v1, 4);
                    a1 = s2;
                    jalr(ctx, 0x4986E8u, v0.u());
                    backedge(ctx);
                }
                // 0x004986b0
                charge(ctx, 2);
                if (s3 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004986b8
        charge(ctx, 4);
        sw(s0, s6, 0);
        sw(zero, s0, 12);
        v0 = 1;
    } else {
        // 0x004982e4
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004986f8 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_00498438_11:
    charge(ctx, 3);
    v0 = a2 & 0x1;
    if (v0 != 0) {
        // 0x00498444
        charge(ctx, 2);
        if (s1 != 0) {
            // 0x0049844c
            charge(ctx, 5);
            sh(v1, a1, 0);
            lw(v0, s0, 4);
            v0 = addiu(v0, 1);
            sw(v0, s0, 4);
        }
    }
    goto L_00498470;
L_00498510_25:
    charge(ctx, 3);
    v0 = a2 & 0x1;
    if (v0 == 0) {
        // 0x0049851c
        charge(ctx, 2);
        if (s1 == 0) {
            goto L_00498570;
        }
        // 0x00498524
        charge(ctx, 12);
        sh(v1, a1, 0);
        lw(a0, s2, 0);
        lw(v1, s0, 4);
        lw(v0, s0, 0);
        lhu(a0, a0, 0);
        v1 = sll(v1, 1);
        v0 = addu(v0, v1);
        sh(a0, v0, 2);
        lw(v0, s0, 4);
        v0 = addiu(v0, 2);
        sw(v0, s0, 4);
        backedge(ctx);
        goto L_00498478;
    }
L_00498570:
    charge(ctx, 5);
    sh(v1, a1, 0);
    lw(v0, s0, 4);
    v0 = addiu(v0, 1);
    sw(v0, s0, 4);
    backedge(ctx);
    goto L_00498478;
}

// sub_497600 [triStripStripTris] -- finds tri-strips over a mesh's triangles (the strip search)
// Part of the tri-strip mesh build (sub_498720): the triangle adjacency is built (sub_496CD0 / sub_496BE0),
// strips are grown from each untaken triangle (triStripTakeTriangle / triStripExtend) and the longest kept;
// scratch through RwMalloc / RwFree and the free list at gp 0x7CE850.
// 0x00497600 sub_497600 -- 3248 bytes; frame 0x150: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_497600(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t9{ctx, 25}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00497600
    enter(ctx, 34);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = 0;
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    a1 = addiu(sp, 0x140);
    sw(a0, sp, 0x12C);
    sw(a3, sp, 0x124);
    a0 = s2;
    sw(a2, sp, 0x128);
    lw(a3, sp, 0x12C);
    a2 = addiu(sp, 0x14C);
    sw(zero, sp, 0x14C);
    sw(zero, sp, 0x130);
    sw(zero, sp, 0x134);
    sw(zero, sp, 0x138);
    sw(zero, sp, 0x13C);
    sw(zero, sp, 0x140);
    sw(zero, sp, 0x144);
    sw(zero, sp, 0x100);
    link(ctx, 0x497670u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0xF0);
    call(ctx, gen::fn_sub_496CD0_00496cd0);
    at = sltu(0, s2);
    sw(v0, sp, 0x11C);
    a2 = 0;
    if (at != 0) {
        // 0x00497688
        charge(ctx, 1);
        a1 = v0;
        for (;;) {
            // 0x0049768c
            charge(ctx, 10);
            lw(v1, a1, 0);
            lbu(v0, v1, 32);
            v0 = sll(v0, 2);
            v0 = addu(v0, sp);
            lw(v0, v0, 304);
            sw(v0, v1, 16);
            lw(v1, a1, 0);
            lw(v0, v1, 16);
            if (v0 != 0) {
                // 0x004976b4
                charge(ctx, 1);
                sw(v1, v0, 20);
            }
            // 0x004976b8
            charge(ctx, 11);
            lw(a0, a1, 0);
            a2 = addiu(a2, 1);
            v0 = sltu(a2, s2);
            lbu(v1, a0, 32);
            v1 = sll(v1, 2);
            v1 = addu(v1, sp);
            sw(a0, v1, 304);
            lw(v1, a1, 0);
            sw(zero, v1, 20);
            a1 = addiu(a1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004976e4
        charge(ctx, 1);
    }
    // 0x004976e8
    charge(ctx, 49);
    lw(a2, gp, -17568);  // 0x7CE850
    a0 = 0x960000;
    v1 = 0x10000;
    s3 = 0x960000;
    a0 = addiu(a0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    a1 = v1 | 0x502;
    s3 = addiu(s3, 392);  // &0x960188 (free-list alloc slot)
    lw(v0, s3, 0);  // 0x960188 (free-list alloc slot)
    v1 = addu(a0, a2);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x49770Cu);  // $ra = the return address
    lw(a0, v1, 4);
    call_ptr(ctx, jt);
    v1 = sll(s2, 1);
    s1 = v0;
    s0 = addiu(v1, 2);
    v1 = 0x960000;
    sw(s0, v0, 8);
    v1 = addiu(v1, 376);  // &0x960178 (RwMalloc slot)
    sw(zero, v0, 4);
    sq(v1, sp, 0xA0);
    v1 = 0x10000;
    a1 = v1 | 0x502;
    lw(v1, v0, 8);
    lq(v0, sp, 0xA0);
    lw(v0, v0, 0);
    a0 = sll(v1, 2);
    jalr(ctx, 0x497748u, v0.u());
    sw(v0, s1, 0);
    v1 = 0x960000;
    lw(a0, gp, -17568);  // 0x7CE850
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = 0x10000;
    a1 = v0 | 0x502;
    lw(v0, s3, 0);  // 0x960188 (free-list alloc slot)
    v1 = addu(v1, a0);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x497770u);  // $ra = the return address
    lw(a0, v1, 4);
    call_ptr(ctx, jt);
    sw(s0, v0, 8);
    v1 = 0x10000;
    sw(zero, v0, 4);
    a1 = v1 | 0x502;
    lw(v1, v0, 8);
    s0 = v0;
    lq(v0, sp, 0xA0);
    lw(v0, v0, 0);
    a0 = sll(v1, 2);
    jalr(ctx, 0x497798u, v0.u());
    at = sltu(0, s2);
    sw(v0, s0, 0);
    if (at != 0) {
        for (;;) {
            // 0x004977ac
            charge(ctx, 3);
            lw(v0, sp, 0x124);
            sw(zero, sp, 0xEC);
            if (v0 == 0) {
                // 0x004977c0
                charge(ctx, 1);
                s5 = 3;
            } else {
                // 0x004977b8
                charge(ctx, 2);
                s5 = 0;
            }
            // 0x004977c4
            charge(ctx, 3);
            lw(v0, sp, 0x130);
            if (v0 == 0) {
                // 0x00497934
                charge(ctx, 6);
                a0 = addiu(sp, 0x134);
                lw(v0, a0, 0);
                v0 = sltu(0, v0);
                v0 = v0 ^ 0x1;
                v1 = 1;
                if (v0 != 0) {
                    for (;;) {
                        // 0x0049794c
                        charge(ctx, 7);
                        a0 = addiu(a0, 4);
                        v1 = addiu(v1, 1);
                        lw(v0, a0, 0);
                        v0 = sltu(0, v0);
                        v0 = v0 ^ 0x1;
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x00497968
                charge(ctx, 8);
                v0 = sll(v1, 2);
                v0 = addu(v0, sp);
                t9 = addiu(v0, 304);
                lw(v0, t9, 0);
                lw(a0, v0, 12);
                lw(a3, a0, 8);
                a1 = 0;
                if (a3 != 0) {
                    // 0x00497988
                    charge(ctx, 5);
                    lw(v1, a3, 24);
                    v1 = sltu(0, v1);
                    v1 = v1 ^ 0x1;
                    if (v1 != 0) {
                        // 0x0049799c
                        charge(ctx, 1);
                        a1 = 1;
                    }
                }
                // 0x004979a0
                charge(ctx, 3);
                lw(a2, a0, 4);
                a0 = 0;
                if (a2 != 0) {
                    // 0x004979ac
                    charge(ctx, 5);
                    lw(v1, a2, 24);
                    v1 = sltu(0, v1);
                    v1 = v1 ^ 0x1;
                    if (v1 != 0) {
                        // 0x004979c0
                        charge(ctx, 2);
                        a0 = 1;
                    }
                }
                // 0x0049806c
                charge(ctx, 4);
                v1 = addu(a0, a1);
                v1 = slti(v1, 2);
                if (v1 != 0) {
                    backedge(ctx);
                } else {
                    // 0x0049807c
                    charge(ctx, 2);
                    lw(a0, v0, 8);
                    backedge(ctx);
                    // 0x004979c8
                    charge(ctx, 3);
                    lw(v1, a0, 8);
                    a1 = 0;
                    if (v1 != 0) {
                        // 0x004979d4
                        charge(ctx, 5);
                        lw(v1, v1, 24);
                        v1 = sltu(0, v1);
                        v1 = v1 ^ 0x1;
                        if (v1 != 0) {
                            // 0x004979e8
                            charge(ctx, 1);
                            a1 = 1;
                        }
                    }
                    // 0x004979ec
                    charge(ctx, 3);
                    lw(v1, a0, 4);
                    a0 = 0;
                    if (v1 != 0) {
                        // 0x004979f8
                        charge(ctx, 5);
                        lw(v1, v1, 24);
                        v1 = sltu(0, v1);
                        v1 = v1 ^ 0x1;
                        if (v1 != 0) {
                            // 0x00497a0c
                            charge(ctx, 1);
                            a0 = 1;
                        }
                    }
                    // 0x00497a10
                    charge(ctx, 4);
                    v1 = addu(a0, a1);
                    v1 = slti(v1, 2);
                    if (v1 != 0) {
                        goto L_00497a28;
                    }
                    // 0x00497a20
                    charge(ctx, 2);
                    s7 = 1;
                    goto L_00497cc4;
                }
            L_00497a28:
                charge(ctx, 4);
                lw(a0, v0, 4);
                lw(a1, a0, 8);
                t1 = 0;
                if (a1 != 0) {
                    // 0x00497a38
                    charge(ctx, 5);
                    lw(v1, a1, 24);
                    v1 = sltu(0, v1);
                    v1 = v1 ^ 0x1;
                    if (v1 != 0) {
                        // 0x00497a4c
                        charge(ctx, 1);
                        t1 = 1;
                    }
                }
                // 0x00497a50
                charge(ctx, 3);
                lw(a0, a0, 4);
                t0 = 0;
                if (a0 != 0) {
                    // 0x00497a5c
                    charge(ctx, 5);
                    lw(v1, a0, 24);
                    v1 = sltu(0, v1);
                    v1 = v1 ^ 0x1;
                    if (v1 != 0) {
                        // 0x00497a70
                        charge(ctx, 2);
                        t0 = 1;
                    }
                }
                // 0x00498084
                charge(ctx, 4);
                v1 = addu(t0, t1);
                v1 = slti(v1, 2);
                if (v1 != 0) {
                    backedge(ctx);
                } else {
                    // 0x00498094
                    charge(ctx, 2);
                    t0 = sltu(0, a2);
                    backedge(ctx);
                    // 0x00497a78
                    charge(ctx, 2);
                    if (t0 != 0) {
                        // 0x00497a80
                        charge(ctx, 3);
                        lw(v1, a2, 24);
                        v1 = sltu(0, v1);
                        t0 = v1 ^ 0x1;
                    }
                    // 0x00497a8c
                    charge(ctx, 3);
                    v1 = sltu(0, a3);
                    if (v1 != 0) {
                        // 0x00497a98
                        charge(ctx, 3);
                        lw(v1, a3, 24);
                        v1 = sltu(0, v1);
                        v1 = v1 ^ 0x1;
                    }
                    // 0x00497aa4
                    charge(ctx, 4);
                    v1 = addu(t0, v1);
                    v1 = slti(v1, 2);
                    if (v1 != 0) {
                        goto L_00497abc;
                    }
                    // 0x00497ab4
                    charge(ctx, 2);
                    s7 = 2;
                    goto L_00497cc4;
                }
            L_00497abc:
                charge(ctx, 4);
                lw(t0, v0, 8);
                lw(v1, t0, 8);
                t2 = 0;
                if (v1 != 0) {
                    // 0x00497acc
                    charge(ctx, 5);
                    lw(v0, v1, 24);
                    v0 = sltu(0, v0);
                    v0 = v0 ^ 0x1;
                    if (v0 != 0) {
                        // 0x00497ae0
                        charge(ctx, 1);
                        t2 = 1;
                    }
                }
                // 0x00497ae4
                charge(ctx, 3);
                lw(v0, t0, 4);
                t1 = 0;
                if (v0 != 0) {
                    // 0x00497af0
                    charge(ctx, 5);
                    lw(t0, v0, 24);
                    t0 = sltu(0, t0);
                    t0 = t0 ^ 0x1;
                    if (t0 != 0) {
                        // 0x00497b04
                        charge(ctx, 2);
                        t1 = 1;
                    }
                }
                // 0x0049809c
                charge(ctx, 4);
                t0 = addu(t1, t2);
                t0 = slti(t0, 2);
                if (t0 != 0) {
                    backedge(ctx);
                } else {
                    // 0x004980ac
                    charge(ctx, 2);
                    t1 = sltu(0, a0);
                    backedge(ctx);
                    // 0x00497b0c
                    charge(ctx, 2);
                    if (t1 != 0) {
                        // 0x00497b14
                        charge(ctx, 3);
                        lw(t0, a0, 24);
                        t0 = sltu(0, t0);
                        t1 = t0 ^ 0x1;
                    }
                    // 0x00497b20
                    charge(ctx, 3);
                    t0 = sltu(0, a1);
                    if (t0 != 0) {
                        // 0x00497b2c
                        charge(ctx, 3);
                        lw(t0, a1, 24);
                        t0 = sltu(0, t0);
                        t0 = t0 ^ 0x1;
                    }
                    // 0x00497b38
                    charge(ctx, 4);
                    t0 = addu(t1, t0);
                    t0 = slti(t0, 2);
                    if (t0 != 0) {
                        goto L_00497b50;
                    }
                    // 0x00497b48
                    charge(ctx, 2);
                    s7 = 0;
                    goto L_00497cc4;
                }
            L_00497b50:
                charge(ctx, 3);
                t1 = sltu(0, a0);
                if (t1 != 0) {
                    // 0x00497b5c
                    charge(ctx, 3);
                    lw(t0, a0, 24);
                    t0 = sltu(0, t0);
                    t1 = t0 ^ 0x1;
                }
                // 0x00497b68
                charge(ctx, 3);
                t0 = sltu(0, a1);
                if (t0 != 0) {
                    // 0x00497b74
                    charge(ctx, 3);
                    lw(t0, a1, 24);
                    t0 = sltu(0, t0);
                    t0 = t0 ^ 0x1;
                }
                // 0x00497b80
                charge(ctx, 4);
                t2 = addu(t1, t0);
                t1 = sltu(0, v0);
                if (t1 != 0) {
                    // 0x00497b90
                    charge(ctx, 3);
                    lw(t0, v0, 24);
                    t0 = sltu(0, t0);
                    t1 = t0 ^ 0x1;
                }
                // 0x00497b9c
                charge(ctx, 3);
                t0 = sltu(0, v1);
                if (t0 != 0) {
                    // 0x00497ba8
                    charge(ctx, 3);
                    lw(t0, v1, 24);
                    t0 = sltu(0, t0);
                    t0 = t0 ^ 0x1;
                }
                // 0x00497bb4
                charge(ctx, 4);
                t0 = addu(t1, t0);
                at = slt(t0, t2);
                if (at == 0) {
                    // 0x00497c48
                    charge(ctx, 3);
                    a0 = sltu(0, v0);
                    if (a0 != 0) {
                        // 0x00497c54
                        charge(ctx, 3);
                        lw(v0, v0, 24);
                        v0 = sltu(0, v0);
                        a0 = v0 ^ 0x1;
                    }
                    // 0x00497c60
                    charge(ctx, 3);
                    v0 = sltu(0, v1);
                    if (v0 != 0) {
                        // 0x00497c6c
                        charge(ctx, 3);
                        lw(v0, v1, 24);
                        v0 = sltu(0, v0);
                        v0 = v0 ^ 0x1;
                    }
                    // 0x00497c78
                    charge(ctx, 3);
                    v1 = sltu(0, a2);
                    a0 = addu(a0, v0);
                    if (v1 != 0) {
                        // 0x00497c84
                        charge(ctx, 3);
                        lw(v0, a2, 24);
                        v0 = sltu(0, v0);
                        v1 = v0 ^ 0x1;
                    }
                    // 0x00497c90
                    charge(ctx, 3);
                    v0 = sltu(0, a3);
                    if (v0 != 0) {
                        // 0x00497c9c
                        charge(ctx, 3);
                        lw(v0, a3, 24);
                        v0 = sltu(0, v0);
                        v0 = v0 ^ 0x1;
                    }
                    // 0x00497ca8
                    charge(ctx, 4);
                    v0 = addu(v1, v0);
                    at = slt(v0, a0);
                    if (at == 0) {
                        // 0x00497cc0
                        charge(ctx, 1);
                        s7 = 1;
                    } else {
                        // 0x00497cb8
                        charge(ctx, 2);
                        s7 = 0;
                    }
                } else {
                    // 0x00497bc4
                    charge(ctx, 3);
                    v1 = sltu(0, a0);
                    if (v1 != 0) {
                        // 0x00497bd0
                        charge(ctx, 3);
                        lw(v0, a0, 24);
                        v0 = sltu(0, v0);
                        v1 = v0 ^ 0x1;
                    }
                    // 0x00497bdc
                    charge(ctx, 3);
                    v0 = sltu(0, a1);
                    if (v0 != 0) {
                        // 0x00497be8
                        charge(ctx, 3);
                        lw(v0, a1, 24);
                        v0 = sltu(0, v0);
                        v0 = v0 ^ 0x1;
                    }
                    // 0x00497bf4
                    charge(ctx, 4);
                    a0 = addu(v1, v0);
                    v1 = sltu(0, a2);
                    if (v1 != 0) {
                        // 0x00497c04
                        charge(ctx, 3);
                        lw(v0, a2, 24);
                        v0 = sltu(0, v0);
                        v1 = v0 ^ 0x1;
                    }
                    // 0x00497c10
                    charge(ctx, 3);
                    v0 = sltu(0, a3);
                    if (v0 != 0) {
                        // 0x00497c1c
                        charge(ctx, 3);
                        lw(v0, a3, 24);
                        v0 = sltu(0, v0);
                        v0 = v0 ^ 0x1;
                    }
                    // 0x00497c28
                    charge(ctx, 4);
                    v0 = addu(v1, v0);
                    at = slt(v0, a0);
                    if (at == 0) {
                        // 0x00497c40
                        charge(ctx, 2);
                        s7 = 1;
                    } else {
                        // 0x00497c38
                        charge(ctx, 2);
                        s7 = 2;
                    }
                }
            L_00497cc4:
                charge(ctx, 14);
                v1 = 3;
                sw(s6, sp, 0x120);
                fp = addiu(s2, -0x8);
                divu(s7, v1);
                mfhi(v0);
                sw(v0, sp, 0xD0);
                v0 = addiu(s7, 1);
                divu(v0, v1);
                mfhi(v0);
                sw(v0, sp, 0xC0);
                v0 = addiu(s7, 2);
                divu(v0, v1);
                mfhi(v0);
                sw(v0, sp, 0xB0);
                for (;;) {
                    // 0x00497cfc
                    charge(ctx, 3);
                    at = sltu(0, s2);
                    v1 = 0;
                    if (at != 0) {
                        // 0x00497d08
                        charge(ctx, 3);
                        at = sltiu(s2, 9);
                        if (at == 0) {
                            // 0x00497d14
                            charge(ctx, 1);
                            lw(v0, sp, 0x11C);
                            for (;;) {
                                // 0x00497d18
                                charge(ctx, 28);
                                lw(a2, v0, 0);
                                v1 = addiu(v1, 8);
                                a0 = sltu(v1, fp);
                                lw(a1, a2, 24);
                                sw(a1, a2, 28);
                                lw(a2, v0, 4);
                                lw(a1, a2, 24);
                                sw(a1, a2, 28);
                                lw(a2, v0, 8);
                                lw(a1, a2, 24);
                                sw(a1, a2, 28);
                                lw(a2, v0, 12);
                                lw(a1, a2, 24);
                                sw(a1, a2, 28);
                                lw(a2, v0, 16);
                                lw(a1, a2, 24);
                                sw(a1, a2, 28);
                                lw(a2, v0, 20);
                                lw(a1, a2, 24);
                                sw(a1, a2, 28);
                                lw(a2, v0, 24);
                                lw(a1, a2, 24);
                                sw(a1, a2, 28);
                                lw(a2, v0, 28);
                                lw(a1, a2, 24);
                                v0 = addiu(v0, 32);
                                sw(a1, a2, 28);
                                if (a0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                        }
                        // 0x00497d88
                        charge(ctx, 3);
                        at = sltu(v1, s2);
                        if (at == 0) {
                            goto L_004980b4;
                        }
                        // 0x00497d94
                        charge(ctx, 3);
                        lw(v0, sp, 0x11C);
                        a0 = sll(v1, 2);
                        a2 = addu(v0, a0);
                        for (;;) {
                            // 0x00497da0
                            charge(ctx, 7);
                            lw(a1, a2, 0);
                            v1 = addiu(v1, 1);
                            v0 = sltu(v1, s2);
                            lw(a0, a1, 24);
                            a2 = addiu(a2, 4);
                            sw(a0, a1, 28);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x00497dbc
                        charge(ctx, 2);
                        v1 = s5;
                        goto L_004980b8;
                    }
                L_004980b4:
                    charge(ctx, 1);
                    v1 = s5;
                L_004980b8:
                    charge(ctx, 3);
                    v0 = 2;
                    s5 = addiu(s5, 1);
                    if (v1 == v0) {
                        backedge(ctx);
                        // 0x00497dd4
                        charge(ctx, 2);
                        lw(s4, sp, 0xB0);
                    } else {
                        // 0x004980c4
                        charge(ctx, 3);
                        v0 = 1;
                        if (v1 == v0) {
                            backedge(ctx);
                            // 0x00497dcc
                            charge(ctx, 2);
                            lw(s4, sp, 0xC0);
                        } else {
                            // 0x004980d0
                            charge(ctx, 2);
                            if (v1 == 0) {
                                backedge(ctx);
                                // 0x00497dc4
                                charge(ctx, 2);
                                lw(s4, sp, 0xD0);
                            } else {
                                // 0x004980d8
                                charge(ctx, 2);
                                s4 = s7;
                                backedge(ctx);
                            }
                        }
                    }
                    // 0x00497ddc
                    charge(ctx, 3);
                    v0 = 2;
                    if (s4 == v0) {
                        // 0x00497e34
                        charge(ctx, 5);
                        lw(v1, t9, 0);
                        lw(v0, v1, 4);
                        sw(v0, sp, 0x100);
                        lw(v0, v1, 12);
                        sw(v0, sp, 0xF0);
                    L_00497e48:
                        charge(ctx, 1);
                        lw(v1, t9, 0);
                    } else {
                        // 0x00497de8
                        charge(ctx, 3);
                        v0 = 1;
                        if (s4 == v0) {
                            // 0x00497e1c
                            charge(ctx, 6);
                            lw(v1, t9, 0);
                            lw(v0, v1, 12);
                            sw(v0, sp, 0x100);
                            lw(v0, v1, 8);
                            sw(v0, sp, 0xF0);
                            goto L_00497e48;
                        }
                        // 0x00497df4
                        charge(ctx, 2);
                        if (s4 == 0) {
                            // 0x00497e04
                            charge(ctx, 6);
                            lw(v1, t9, 0);
                            lw(v0, v1, 8);
                            sw(v0, sp, 0x100);
                            lw(v0, v1, 4);
                            sw(v0, sp, 0xF0);
                            goto L_00497e48;
                        }
                        // 0x00497dfc
                        charge(ctx, 2);
                        lw(v1, t9, 0);
                    }
                    // 0x00497e4c
                    charge(ctx, 46);
                    v0 = 3;
                    lw(a0, v1, 0);
                    v1 = sll(a0, 2);
                    v1 = addu(v1, a0);
                    a0 = sll(v1, 2);
                    lw(v1, sp, 0x12C);
                    v1 = addu(v1, a0);
                    divu(s4, v0);
                    mfhi(a2);
                    lw(a1, s1, 0);
                    a0 = addiu(s4, 1);
                    a2 = sll(a2, 1);
                    a2 = addu(v1, a2);
                    lhu(a2, a2, 0);
                    sh(a2, a1, 0);
                    divu(a0, v0);
                    mfhi(a2);
                    lw(a1, s1, 0);
                    a0 = addiu(s4, 2);
                    a2 = sll(a2, 1);
                    a2 = addu(v1, a2);
                    lhu(a2, a2, 0);
                    sh(a2, a1, 2);
                    divu(a0, v0);
                    mfhi(a3);
                    lw(a0, s1, 0);
                    a1 = addiu(sp, 0x130);
                    a3 = sll(a3, 1);
                    v1 = addu(v1, a3);
                    lhu(v1, v1, 0);
                    sh(v1, a0, 4);
                    sw(v0, s1, 4);
                    lw(a0, t9, 0);
                    a2 = s5;
                    jal(ctx, 0x497ED0u, gen::fn_triStripTakeTriangle_00496f60);
                    lw(v0, sp, 0x120);
                    a0 = s1;
                    lw(a1, sp, 0x100);
                    a2 = addiu(sp, 0x130);
                    lw(a3, sp, 0x12C);
                    t0 = s5;
                    s6 = addiu(v0, 1);
                    jal(ctx, 0x497EF0u, gen::fn_triStripExtend_00497130);
                    at = slti(s5, 4);
                    s6 = addu(s6, v0);
                    if (at == 0) {
                        // 0x00497f60
                        charge(ctx, 4);
                        lw(v0, sp, 0xF0);
                        lw(v0, v0, 8);
                        a0 = 0;
                        if (v0 != 0) {
                            // 0x00497f70
                            charge(ctx, 5);
                            lw(v0, v0, 24);
                            v0 = sltu(0, v0);
                            v0 = v0 ^ 0x1;
                            if (v0 != 0) {
                                // 0x00497f84
                                charge(ctx, 1);
                                a0 = 1;
                            }
                        }
                        // 0x00497f88
                        charge(ctx, 4);
                        lw(v0, sp, 0xF0);
                        lw(v0, v0, 4);
                        v1 = 0;
                        if (v0 != 0) {
                            // 0x00497f98
                            charge(ctx, 5);
                            lw(v0, v0, 24);
                            v0 = sltu(0, v0);
                            v0 = v0 ^ 0x1;
                            if (v0 != 0) {
                                // 0x00497fac
                                charge(ctx, 1);
                                v1 = 1;
                            }
                        }
                        // 0x00497fb0
                        charge(ctx, 2);
                        v0 = addu(v1, a0);
                        v0 = slt(0, v0);
                    } else {
                        // 0x00497f04
                        charge(ctx, 4);
                        lw(v0, sp, 0xF0);
                        lw(v0, v0, 8);
                        a0 = 0;
                        if (v0 != 0) {
                            // 0x00497f14
                            charge(ctx, 5);
                            lw(v0, v0, 28);
                            v0 = sltu(0, v0);
                            v0 = v0 ^ 0x1;
                            if (v0 != 0) {
                                // 0x00497f28
                                charge(ctx, 1);
                                a0 = 1;
                            }
                        }
                        // 0x00497f2c
                        charge(ctx, 4);
                        lw(v0, sp, 0xF0);
                        lw(v0, v0, 4);
                        v1 = 0;
                        if (v0 != 0) {
                            // 0x00497f3c
                            charge(ctx, 5);
                            lw(v0, v0, 28);
                            v0 = sltu(0, v0);
                            v0 = v0 ^ 0x1;
                            if (v0 != 0) {
                                // 0x00497f50
                                charge(ctx, 1);
                                v1 = 1;
                            }
                        }
                        // 0x00497f54
                        charge(ctx, 3);
                        v0 = addu(v1, a0);
                        v0 = slt(0, v0);
                    }
                    // 0x00497fb8
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x00497fc0
                        charge(ctx, 4);
                        lw(v0, sp, 0xEC);
                        at = sltu(v0, s6);
                        if (at != 0) {
                            // 0x00497fd0
                            charge(ctx, 2);
                            s7 = s4;
                            sw(s6, sp, 0xEC);
                        }
                        // 0x00497fd8
                        charge(ctx, 3);
                        v0 = slti(s5, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        continue;
                    }
                    // 0x004980e0
                    charge(ctx, 21);
                    lw(t1, s1, 0);
                    v0 = 2;
                    lw(v1, s0, 0);
                    a0 = s0;
                    lw(a1, sp, 0xF0);
                    a2 = addiu(sp, 0x130);
                    lw(a3, sp, 0x12C);
                    t0 = s5;
                    lhu(t1, t1, 2);
                    sh(t1, v1, 0);
                    lw(t1, s1, 0);
                    lw(v1, s0, 0);
                    lhu(t1, t1, 0);
                    sh(t1, v1, 2);
                    link(ctx, 0x498118u);  // $ra first: the delay slot below depends on it
                    sw(v0, s0, 4);
                    call(ctx, gen::fn_triStripExtend_00497130);
                    lw(v1, s0, 4);
                    s6 = addu(s6, v0);
                    v0 = v1 & 0x1;
                    if (v0 != 0) {
                        // 0x00498230
                        charge(ctx, 9);
                        v0 = sll(v1, 1);
                        lw(v1, s0, 0);
                        v1 = addu(v0, v1);
                        lhu(v0, v1, -4);
                        sh(v0, v1, 0);
                        lw(v0, s0, 4);
                        v0 = addiu(v0, 1);
                        sw(v0, s0, 4);
                        backedge(ctx);
                    }
                    // 0x00498134
                    charge(ctx, 4);
                    lw(v0, sp, 0xEC);
                    at = sltu(v0, s6);
                    if (at != 0) {
                        // 0x00498144
                        charge(ctx, 2);
                        s7 = s4;
                        sw(s6, sp, 0xEC);
                    }
                    // 0x0049814c
                    charge(ctx, 3);
                    v0 = slti(s5, 4);
                    if (v0 == 0) {
                        goto L_00498158_143;
                    }
                    backedge(ctx);
                }
                // 0x00497fe4
                charge(ctx, 34);
                lw(a2, gp, -17568);  // 0x7CE850
                a0 = 0x960000;
                v1 = 0x30000;
                a0 = addiu(a0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                a1 = v1 | 0x502;
                lw(v0, s3, 0);
                v1 = addu(a0, a2);
                jt = v0.u();  // the target, read before the delay slot
                link(ctx, 0x498000u);  // $ra = the return address
                lw(a0, v1, 4);
                call_ptr(ctx, jt);
                lw(v1, sp, 0x128);
                s4 = v0;
                lw(a0, v1, 0);
                v1 = 0x30000;
                sw(a0, v0, 12);
                a1 = v1 | 0x502;
                lw(v1, sp, 0x128);
                sw(s4, v1, 0);
                lw(v1, s1, 4);
                sw(v1, v0, 8);
                lw(v1, s1, 4);
                sw(v1, v0, 4);
                lq(v0, sp, 0xA0);
                lw(v1, s1, 4);
                lw(v0, v0, 0);
                a0 = sll(v1, 2);
                jalr(ctx, 0x498044u, v0.u());
                sw(v0, s4, 0);
                lw(v0, s1, 4);
                lw(a0, s4, 0);
                lw(a1, s1, 0);
                a2 = sll(v0, 2);
                jal(ctx, 0x49805Cu, gen::fn_memcpy_00521250);
                v0 = sltu(s6, s2);
                backedge(ctx);
            } else {
                // 0x004977d0
                charge(ctx, 49);
                lw(s5, v0, 0);
                v1 = 0x960000;
                lw(a0, gp, -17568);  // 0x7CE850
                v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                v0 = 0x30000;
                a1 = v0 | 0x502;
                v1 = addu(v1, a0);
                lw(v0, s3, 0);
                jt = v0.u();  // the target, read before the delay slot
                link(ctx, 0x4977F0u);  // $ra = the return address
                lw(a0, v1, 4);
                call_ptr(ctx, jt);
                lw(v1, sp, 0x128);
                s4 = v0;
                a2 = 3;
                lw(a3, v1, 0);
                v1 = 0x30000;
                sw(a3, v0, 12);
                a1 = v1 | 0x502;
                lw(v1, sp, 0x128);
                sw(s4, v1, 0);
                sw(a2, v0, 8);
                sw(a2, v0, 4);
                lq(v0, sp, 0xA0);
                lw(v0, v0, 0);
                a0 = 12;
                jalr(ctx, 0x49782Cu, v0.u());
                sw(v0, s4, 0);
                v1 = 1;
                v0 = sll(s5, 2);
                lw(a0, s4, 0);
                v0 = addu(v0, s5);
                a1 = sll(v0, 2);
                lw(v0, sp, 0x12C);
                a1 = addu(v0, a1);
                lhu(v0, a1, 0);
                sh(v0, a0, 0);
                lhu(a0, a1, 2);
                lw(v0, s4, 0);
                sh(a0, v0, 2);
                lhu(a0, a1, 4);
                lw(v0, s4, 0);
                sh(a0, v0, 4);
                lw(v0, sp, 0x130);
                sw(v1, v0, 24);
                lw(v0, sp, 0x130);
                sw(v1, v0, 28);
                lw(v0, sp, 0x130);
                lw(v0, v0, 16);
                sw(v0, sp, 0x130);
                if (v0 != 0) {
                    // 0x00497894
                    charge(ctx, 1);
                    sw(zero, v0, 20);
                }
                // 0x00497898
                charge(ctx, 1);
                s6 = addiu(s6, 1);
            L_0049789c:
                charge(ctx, 1);
                v0 = sltu(s6, s2);
            }
            // 0x004978a0
            charge(ctx, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004978a8
    charge(ctx, 35);
    s3 = 0x960000;
    s3 = addiu(s3, 380);  // &0x96017C (RwFree slot)
    lw(v0, s3, 0);  // 0x96017C (RwFree slot)
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4978B4u);  // $ra = the return address
    lw(a0, s0, 0);
    call_ptr(ctx, jt);
    sw(zero, s0, 0);
    a1 = s0;
    lw(a0, gp, -17568);  // 0x7CE850
    v1 = 0x960000;
    s0 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    s0 = addiu(s0, 396);  // &0x96018C (free-list free slot)
    lw(v0, s0, 0);  // 0x96018C (free-list free slot)
    v1 = addu(v1, a0);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4978E0u);  // $ra = the return address
    lw(a0, v1, 4);
    call_ptr(ctx, jt);
    lw(v0, s3, 0);  // 0x96017C (RwFree slot)
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4978ECu);  // $ra = the return address
    lw(a0, s1, 0);
    call_ptr(ctx, jt);
    sw(zero, s1, 0);
    v1 = 0x960000;
    lw(a0, gp, -17568);  // 0x7CE850
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    lw(v0, s0, 0);  // 0x96018C (free-list free slot)
    v1 = addu(v1, a0);
    lw(a0, v1, 4);
    a1 = s1;
    jalr(ctx, 0x497910u, v0.u());
    lw(a3, sp, 0x11C);
    a0 = s2;
    lw(a2, sp, 0x14C);
    a1 = addiu(sp, 0x140);
    jal(ctx, 0x497924u, gen::fn_sub_496BE0_00496be0);
    v0 = 1;
    // 0x00498280
    charge(ctx, 12);
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
    sp = addiu(sp, 0x150);
    return;
L_00498158_143:
    charge(ctx, 33);
    lw(a2, gp, -17568);  // 0x7CE850
    a0 = 0x960000;
    v1 = 0x30000;
    a0 = addiu(a0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    a1 = v1 | 0x502;
    lw(v0, s3, 0);
    v1 = addu(a0, a2);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x498174u);  // $ra = the return address
    lw(a0, v1, 4);
    call_ptr(ctx, jt);
    lw(v1, sp, 0x128);
    s4 = v0;
    lw(a0, v1, 0);
    v1 = 0x30000;
    sw(a0, v0, 12);
    a1 = v1 | 0x502;
    lw(v1, sp, 0x128);
    sw(s4, v1, 0);
    lw(a0, s1, 4);
    lw(v1, s0, 4);
    v1 = addu(a0, v1);
    v1 = addiu(v1, -2);
    sw(v1, v0, 8);
    sw(zero, v0, 4);
    lw(v1, v0, 8);
    lq(v0, sp, 0xA0);
    lw(v0, v0, 0);
    a0 = sll(v1, 2);
    jalr(ctx, 0x4981C0u, v0.u());
    sw(v0, s4, 0);
    lw(v0, s0, 4);
    at = sltiu(v0, 3);
    if (at != 0) {
        // 0x00498254
        charge(ctx, 1);
        lw(a0, s4, 4);
    } else {
        for (;;) {
            // 0x004981dc
            charge(ctx, 19);
            lw(a1, s0, 0);
            a0 = sll(v0, 1);
            lw(v1, s4, 4);
            lw(v0, s4, 0);
            a0 = addu(a0, a1);
            lhu(a0, a0, -2);
            v1 = sll(v1, 1);
            v0 = addu(v0, v1);
            sh(a0, v0, 0);
            lw(v0, s4, 4);
            v0 = addiu(v0, 1);
            sw(v0, s4, 4);
            lw(v0, s0, 4);
            v0 = addiu(v0, -1);
            sw(v0, s0, 4);
            lw(v0, s0, 4);
            at = sltiu(v0, 3);
            if (at != 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00498228
        charge(ctx, 2);
        lw(a0, s4, 4);
    }
    // 0x00498258
    charge(ctx, 10);
    lw(v0, s1, 4);
    lw(v1, s4, 0);
    lw(a1, s1, 0);
    a0 = sll(a0, 1);
    a2 = sll(v0, 2);
    a0 = addu(v1, a0);
    jal(ctx, 0x49826Cu, gen::fn_memcpy_00521250);
    lw(v0, s4, 8);
    sw(v0, s4, 4);
    backedge(ctx);
    goto L_0049789c;
}

// sub_498720 [triStripMeshGenerate] -- builds a tri-strip mesh header from a build mesh
// The triangles sorted by material (qsort with meshSortCompare), a free list for the strip nodes
// (sub_4C3B50), per material the strips (sub_497600) joined (sub_4982B0), the header allocated (sub_4959C0) and
// the index lists copied; the scratch freed (sub_4C3C30, RwFree).
// 0x00498720 sub_498720 -- 1808 bytes; frame 0xF0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_498720(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00498720
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    v0 = 0x960000;
    sd(ra, sp, 0x90);
    v0 = addiu(v0, 376);  // &0x960178 (RwMalloc slot)
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(v0, sp, 0xA0);
    s6 = a1;
    v0 = 0x10000;
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    a1 = v0 | 0x502;
    sq(s3, sp, 0x30);
    s4 = 0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lq(v0, sp, 0xA0);
    s0 = a0;
    lw(v1, a0, 4);
    sw(a2, sp, 0xE8);
    lw(v0, v0, 0);
    a0 = sll(v1, 2);
    jalr(ctx, 0x49877Cu, v0.u());
    sw(v0, sp, 0xE4);
    if (v0 == 0) {
        // 0x004987d0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0049878c
        charge(ctx, 4);
        lw(a1, s0, 4);
        at = sltu(0, a1);
        a2 = 0;
        if (at == 0) {
            // 0x004987d8
            charge(ctx, 1);
            lw(a0, sp, 0xE4);
        } else {
            // 0x0049879c
            charge(ctx, 2);
            a0 = 0;
            v1 = v0;
            for (;;) {
                // 0x004987a4
                charge(ctx, 9);
                lw(v0, s0, 8);
                a2 = addiu(a2, 1);
                v0 = addu(v0, a0);
                sw(v0, v1, 0);
                a0 = addiu(a0, 20);
                lw(a1, s0, 4);
                v0 = sltu(a2, a1);
                v1 = addiu(v1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004987c8
            charge(ctx, 2);
            lw(a0, sp, 0xE4);
        }
        // 0x004987dc
        charge(ctx, 8);
        a3 = 0x490000;
        a2 = 4;
        a3 = addiu(a3, 26016);  // &meshSortCompare
        jal(ctx, 0x4987E4u, gen::fn_qsort_005225f8);
        lw(v1, s0, 4);
        v0 = sltiu(v1, 2);
        s1 = 1;
        if (v0 == 0) {
            // 0x004987fc
            charge(ctx, 6);
            lw(v0, sp, 0xE4);
            at = sltiu(v1, 2);
            lw(v0, v0, 0);
            lw(a2, v0, 8);
            a0 = s1;
            if (at == 0) {
                // 0x00498814
                charge(ctx, 2);
                lw(v0, sp, 0xE4);
                a1 = addiu(v0, 4);
                for (;;) {
                    // 0x0049881c
                    charge(ctx, 4);
                    lw(v0, a1, 0);
                    lw(v0, v0, 8);
                    if (v0 != a2) {
                        // 0x0049882c
                        charge(ctx, 3);
                        a2 = v0;
                        s1 = addiu(s1, 1);
                    }
                    // 0x00498838
                    charge(ctx, 4);
                    a0 = addiu(a0, 1);
                    v0 = sltu(a0, v1);
                    a1 = addiu(a1, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x00498848
        charge(ctx, 26);
        lq(v0, sp, 0xA0);
        v1 = 0x1010000;
        a0 = sll(s1, 2);
        lw(v0, v0, 0);
        a1 = v1 | 0x502;  // &0x1010502
        jalr(ctx, 0x498858u, v0.u());
        s3 = v0;
        v0 = sll(s1, 1);
        v1 = addu(v0, s1);
        v0 = 0x10000;
        a1 = v0 | 0x502;
        lq(v0, sp, 0xA0);
        lw(v0, v0, 0);
        a0 = sll(v1, 2);
        jalr(ctx, 0x49887Cu, v0.u());
        lw(v1, sp, 0xE4);
        sw(v0, sp, 0xCC);
        lw(v1, v1, 0);
        lw(v1, v1, 8);
        sw(v1, v0, 8);
        sw(zero, v0, 4);
        sw(zero, v0, 0);
        lw(a1, s0, 4);
        v0 = sltiu(a1, 2);
        fp = 0x1;
        if (v0 == 0) {
            // 0x004988b0
            charge(ctx, 4);
            v0 = addiu(a1, -1);
            at = sltu(0, v0);
            a0 = 0;
            if (at != 0) {
                // 0x004988c0
                charge(ctx, 3);
                lw(v0, sp, 0xCC);
                lw(a3, sp, 0xE4);
                a2 = addiu(v0, 12);
                for (;;) {
                    // 0x004988cc
                    charge(ctx, 6);
                    lw(v1, a3, 4);
                    lw(v0, a3, 0);
                    lw(v1, v1, 8);
                    lw(v0, v0, 8);
                    if (v0 != v1) {
                        // 0x004988e4
                        charge(ctx, 9);
                        sw(v1, a2, 8);
                        fp = addiu(fp, 0x1);
                        v1 = addiu(a0, 1);
                        sw(v1, a2, 4);
                        sw(zero, a2, 0);
                        lw(v0, a2, -8);
                        v0 = subu(v1, v0);
                        sw(v0, a2, -8);
                        a2 = addiu(a2, 12);
                    }
                    // 0x00498908
                    charge(ctx, 6);
                    lw(a1, s0, 4);
                    a0 = addiu(a0, 1);
                    v0 = addiu(a1, -1);
                    v0 = sltu(a0, v0);
                    a3 = addiu(a3, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x00498920
        charge(ctx, 31);
        v0 = sll(fp, 1);
        v1 = addu(v0, fp);
        v0 = lui(0xCCCC);
        a0 = sll(v1, 2);
        v1 = v0 | 0xCCCD;
        lw(v0, sp, 0xCC);
        a0 = addu(a0, v0);
        lw(v0, a0, -8);
        v0 = subu(a1, v0);
        sw(v0, a0, -8);
        lw(v0, s0, 4);
        multu(zero, v1, v0);
        mfhi(v1);
        v0 = 0x10000;
        a3 = v0 | 0x502;
        a0 = 16;
        a2 = 4;
        v0 = srl(v1, 3);
        a1 = addiu(v0, 5);
        jal(ctx, 0x498968u, gen::fn_sub_4C3B50_004c3b50);
        lw(v1, sp, 0xE4);
        a0 = 0x960000;
        lw(a1, gp, -17568);  // 0x7CE850
        a0 = addiu(a0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        at = sltu(0, fp);
        sw(zero, sp, 0xEC);
        sw(zero, sp, 0xB0);
        sw(v1, sp, 0xD0);
        v1 = addu(a0, a1);
        sw(v0, v1, 4);
        if (at != 0) {
            // 0x0049899c
            charge(ctx, 5);
            lw(s2, sp, 0xCC);
            s5 = 0x960000;
            s7 = 0x960000;
            s5 = addiu(s5, 380);  // &0x96017C (RwFree slot)
            s7 = addiu(s7, 396);  // &0x96018C (free-list free slot)
            for (;;) {
                // 0x004989b0
                charge(ctx, 14);
                v0 = 0x10000;
                lw(a0, s2, 4);
                a1 = v0 | 0x502;
                lq(v0, sp, 0xA0);
                v1 = sll(a0, 2);
                v1 = addu(v1, a0);
                lw(v0, v0, 0);
                a0 = sll(v1, 2);
                jalr(ctx, 0x4989CCu, v0.u());
                lw(a1, s2, 4);
                s0 = v0;
                at = sltu(0, a1);
                a2 = 0;
                if (at != 0) {
                    // 0x004989e8
                    charge(ctx, 2);
                    a0 = s0;
                    for (;;) {
                        // 0x004989f0
                        charge(ctx, 19);
                        lw(v0, sp, 0xD0);
                        a2 = addiu(a2, 1);
                        lw(v1, v0, 0);
                        lwc1(f3, v1, 0);
                        v0 = addiu(v0, 4);
                        lwc1(f2, v1, 4);
                        sw(v0, sp, 0xD0);
                        lwc1(f1, v1, 8);
                        lwc1(f0, v1, 12);
                        swc1(f3, a0, 0);
                        swc1(f2, a0, 4);
                        swc1(f1, a0, 8);
                        swc1(f0, a0, 12);
                        lwc1(f0, v1, 16);
                        swc1(f0, a0, 16);
                        lw(a1, s2, 4);
                        v0 = sltu(a2, a1);
                        a0 = addiu(a0, 20);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00498a3c
                    charge(ctx, 1);
                }
                // 0x00498a40
                charge(ctx, 10);
                a0 = s0;
                a2 = addiu(sp, 0xEC);
                a3 = s6;
                jal(ctx, 0x498A48u, gen::fn_sub_497600_00497600);
                lw(a1, sp, 0xE8);
                a0 = addiu(sp, 0xEC);
                jal(ctx, 0x498A54u, gen::fn_sub_4982B0_004982b0);
                lw(s1, sp, 0xEC);
                if (s1 != 0) {
                    for (;;) {
                        // 0x00498a68
                        charge(ctx, 18);
                        lq(v0, sp, 0xA0);
                        v1 = 0x10000;
                        lw(a0, s1, 4);
                        a1 = v1 | 0x502;
                        lw(v0, v0, 0);
                        v1 = sll(a0, 1);
                        a0 = addiu(v1, 12);
                        jalr(ctx, 0x498A80u, v0.u());
                        lw(a0, s2, 8);
                        v1 = addiu(v0, 12);
                        sw(a0, v0, 8);
                        lw(a0, s1, 4);
                        sw(a0, v0, 4);
                        sw(v1, v0, 0);
                        lw(v1, v0, 4);
                        at = sltu(0, v1);
                        a1 = 0;
                        if (at != 0) {
                            // 0x00498ab0
                            charge(ctx, 2);
                            a2 = 0;
                            for (;;) {
                                // 0x00498ab8
                                charge(ctx, 11);
                                lw(a0, s1, 0);
                                lw(v1, v0, 0);
                                a1 = addiu(a1, 1);
                                a0 = addu(a0, a2);
                                lhu(a0, a0, 0);
                                v1 = addu(v1, a2);
                                sh(a0, v1, 0);
                                lw(v1, v0, 4);
                                v1 = sltu(a1, v1);
                                a2 = addiu(a2, 2);
                                if (v1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x00498ae4
                            charge(ctx, 1);
                        }
                        // 0x00498ae8
                        charge(ctx, 8);
                        v1 = s4 & 0xFFFF;
                        a0 = sll(v1, 2);
                        a0 = addu(s3, a0);
                        v1 = addiu(s4, 1);
                        sw(v0, a0, 0);
                        lw(s1, s1, 12);
                        s4 = v1 & 0xFFFF;
                        if (s1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x00498b08
                charge(ctx, 3);
                lw(v0, sp, 0xEC);
                if (v0 != 0) {
                    // 0x00498b14
                    charge(ctx, 1);
                    for (;;) {
                        // 0x00498b18
                        charge(ctx, 18);
                        lw(s1, sp, 0xEC);
                        lw(v0, s5, 0);
                        lw(v1, s1, 12);
                        sw(v1, sp, 0xEC);
                        jt = v0.u();  // the target, read before the delay slot
                        link(ctx, 0x498B28u);  // $ra = the return address
                        lw(a0, s1, 0);
                        call_ptr(ctx, jt);
                        sw(zero, s1, 0);
                        v1 = 0x960000;
                        lw(a0, gp, -17568);  // 0x7CE850
                        v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                        lw(v0, s7, 0);
                        v1 = addu(v1, a0);
                        lw(a0, v1, 4);
                        a1 = s1;
                        jalr(ctx, 0x498B4Cu, v0.u());
                        lw(v0, sp, 0xEC);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x00498b60
                charge(ctx, 9);
                lw(v0, s5, 0);
                a0 = s0;
                jalr(ctx, 0x498B64u, v0.u());
                lw(v0, sp, 0xB0);
                v0 = addiu(v0, 1);
                sw(v0, sp, 0xB0);
                v0 = sltu(v0, fp);
                s2 = addiu(s2, 12);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00498b84
            charge(ctx, 1);
        }
        // 0x00498b88
        charge(ctx, 17);
        lw(v1, gp, -17568);  // 0x7CE850
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        link(ctx, 0x498B98u);  // $ra first: the delay slot below depends on it
        lw(a0, v0, 4);
        call(ctx, gen::fn_sub_4C3C30_004c3c30);
        lw(a1, gp, -17568);  // 0x7CE850
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        s0 = s4 & 0xFFFF;
        at = sltu(0, s0);
        a0 = 16;
        s2 = 0;
        v1 = 0;
        v0 = addu(v0, a1);
        sw(zero, v0, 4);
        if (at != 0) {
            // 0x00498bcc
            charge(ctx, 3);
            at = sltiu(s0, 9);
            v0 = addiu(s0, -8);
            if (at == 0) {
                // 0x00498bd8
                charge(ctx, 1);
                a1 = s3;
                for (;;) {
                    // 0x00498bdc
                    charge(ctx, 52);
                    lw(t4, a1, 0);
                    v1 = addiu(v1, 8);
                    lw(t2, a1, 8);
                    a2 = sltu(v1, v0);
                    lw(t1, a1, 12);
                    lw(t0, a1, 16);
                    lw(a3, a1, 20);
                    lw(t3, a1, 4);
                    lw(t6, t4, 4);
                    lw(t2, t2, 4);
                    lw(t1, t1, 4);
                    lw(t0, t0, 4);
                    lw(a3, a3, 4);
                    lw(t4, t3, 4);
                    t5 = sll(t6, 1);
                    t5 = addiu(t5, 12);
                    t5 = addu(a0, t5);
                    t3 = addu(s2, t6);
                    a0 = sll(t4, 1);
                    t3 = addu(t3, t4);
                    t4 = addiu(a0, 12);
                    a0 = addu(t3, t2);
                    a0 = addu(a0, t1);
                    t2 = sll(t2, 1);
                    t1 = sll(t1, 1);
                    t3 = addu(t5, t4);
                    t2 = addiu(t2, 12);
                    t1 = addiu(t1, 12);
                    t2 = addu(t3, t2);
                    a0 = addu(a0, t0);
                    t2 = addu(t2, t1);
                    t0 = sll(t0, 1);
                    t1 = addu(a0, a3);
                    t0 = addiu(t0, 12);
                    a0 = sll(a3, 1);
                    t0 = addu(t2, t0);
                    a0 = addiu(a0, 12);
                    lw(a3, a1, 24);
                    t2 = addu(t0, a0);
                    lw(a0, a1, 28);
                    lw(t0, a3, 4);
                    lw(a0, a0, 4);
                    a1 = addiu(a1, 32);
                    a3 = addu(t1, t0);
                    t0 = sll(t0, 1);
                    s2 = addu(a3, a0);
                    t0 = addiu(t0, 12);
                    a0 = sll(a0, 1);
                    a3 = addu(t2, t0);
                    a0 = addiu(a0, 12);
                    a0 = addu(a3, a0);
                    if (a2 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00498cac
                charge(ctx, 1);
            }
            // 0x00498cb0
            charge(ctx, 3);
            at = sltu(v1, s0);
            if (at != 0) {
                // 0x00498cbc
                charge(ctx, 2);
                v0 = sll(v1, 2);
                a3 = addu(s3, v0);
                for (;;) {
                    // 0x00498cc4
                    charge(ctx, 10);
                    lw(a1, a3, 0);
                    v1 = addiu(v1, 1);
                    v0 = sltu(v1, s0);
                    lw(a2, a1, 4);
                    a3 = addiu(a3, 4);
                    a1 = sll(a2, 1);
                    s2 = addu(s2, a2);
                    a1 = addiu(a1, 12);
                    a0 = addu(a0, a1);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00498cec
                charge(ctx, 1);
            }
        }
        // 0x00498cf0
        charge(ctx, 28);
        jal(ctx, 0x498CF0u, gen::fn_sub_4959C0_004959c0);
        v1 = 1;
        s7 = v0;
        sw(v1, v0, 0);
        a0 = s4 & 0xFFFF;
        sh(s4, v0, 4);
        v1 = sll(a0, 1);
        lw(a2, gp, -17568);  // 0x7CE850
        v1 = addu(v1, a0);
        a1 = 0x960000;
        s1 = addiu(s7, 16);
        v1 = sll(v1, 2);
        a1 = addiu(a1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        s4 = addu(s1, v1);
        at = sltu(0, s0);
        s5 = 0;
        v1 = addu(a1, a2);
        lh(v1, v1, 0);
        sh(v1, v0, 6);
        sw(zero, v0, 12);
        sw(s2, v0, 8);
        lw(v0, gp, -17568);  // 0x7CE850
        v1 = addu(a1, v0);
        lh(v0, v1, 0);
        v0 = addiu(v0, 1);
        sh(v0, v1, 0);
        if (at != 0) {
            // 0x00498d60
            charge(ctx, 3);
            s6 = 0x960000;
            s2 = s3;
            s6 = addiu(s6, 380);  // &0x96017C (RwFree slot)
            for (;;) {
                // 0x00498d6c
                charge(ctx, 25);
                sw(s4, s1, 0);
                a0 = s4;
                lw(v0, s2, 0);
                lw(v0, v0, 4);
                sw(v0, s1, 4);
                lw(v0, s2, 0);
                lw(v0, v0, 8);
                sw(v0, s1, 8);
                lw(v1, s2, 0);
                lw(v0, v1, 4);
                lw(a1, v1, 0);
                a2 = sll(v0, 1);
                jal(ctx, 0x498D98u, gen::fn_memcpy_00521250);
                lw(v1, s1, 4);
                lw(a0, s2, 0);
                lw(v0, s6, 0);
                v1 = sll(v1, 1);
                s1 = addiu(s1, 12);
                s4 = addu(s4, v1);
                jalr(ctx, 0x498DB4u, v0.u());
                s5 = addiu(s5, 1);
                sw(zero, s2, 0);
                v0 = sltu(s5, s0);
                s2 = addiu(s2, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00498dd0
        charge(ctx, 12);
        s0 = 0x960000;
        s0 = addiu(s0, 380);  // &0x96017C (RwFree slot)
        lw(v0, s0, 0);  // 0x96017C (RwFree slot)
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x498DDCu);  // $ra = the return address
        lw(a0, sp, 0xE4);
        call_ptr(ctx, jt);
        lw(v0, s0, 0);  // 0x96017C (RwFree slot)
        a0 = s3;
        jalr(ctx, 0x498DE8u, v0.u());
        lw(v0, s0, 0);  // 0x96017C (RwFree slot)
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x498DF4u);  // $ra = the return address
        lw(a0, sp, 0xCC);
        call_ptr(ctx, jt);
        v0 = s7;
    }
    // 0x00498e00 (the shared epilogue, written out on this path)
    charge(ctx, 12);
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
    sp = addiu(sp, 0xF0);
}

// sub_498E70 [triListMeshGenerate] -- builds a tri-list mesh header from a build mesh
// The triangles sorted by material (qsort with meshSortCompare), the header allocated (sub_4959C0), each
// material's indices written, then every mesh reordered by sub_4967A0 (meshHeaderForAllMeshes); errors through
// sub_4C1D10 / sub_4C1C50.
// 0x00498E70 sub_498E70 -- 716 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_498E70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00498e70
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v0 = 0x10000;
    sd(ra, sp, 0x50);
    a1 = v0 | 0x502;
    sq(s4, sp, 0x40);
    v0 = 0x960000;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(v1, a0, 4);
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    a0 = sll(v1, 2);
    jalr(ctx, 0x498EA4u, v0.u());
    s1 = v0;
    if (s1 == 0) {
        // 0x004990f0
        charge(ctx, 11);
        v1 = 2;
        v0 = lui(0x8000);
        sw(v1, sp, 0x60);
        a0 = v0 | 0x13;
        lw(v0, s2, 4);
        a1 = sll(v0, 2);
        jal(ctx, 0x499104u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x64);
        a0 = addiu(sp, 0x60);
        jal(ctx, 0x499110u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x00498eb8
        charge(ctx, 4);
        lw(a1, s2, 4);
        at = sltu(0, a1);
        a2 = 0;
        if (at != 0) {
            // 0x00498ec8
            charge(ctx, 2);
            a0 = 0;
            v1 = s1;
            for (;;) {
                // 0x00498ed0
                charge(ctx, 9);
                lw(v0, s2, 8);
                a2 = addiu(a2, 1);
                v0 = addu(v0, a0);
                sw(v0, v1, 0);
                a0 = addiu(a0, 20);
                lw(a1, s2, 4);
                v0 = sltu(a2, a1);
                v1 = addiu(v1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00498ef4
            charge(ctx, 1);
        }
        // 0x00498ef8
        charge(ctx, 9);
        a3 = 0x490000;
        a0 = s1;
        a2 = 4;
        a3 = addiu(a3, 26016);  // &meshSortCompare
        jal(ctx, 0x498F04u, gen::fn_qsort_005225f8);
        lw(a0, s2, 4);
        v0 = sltiu(a0, 2);
        a3 = 1;
        if (v0 == 0) {
            // 0x00498f1c
            charge(ctx, 5);
            lw(v0, s1, 0);
            at = sltiu(a0, 2);
            lw(a2, v0, 8);
            v1 = a3;
            if (at == 0) {
                // 0x00498f30
                charge(ctx, 1);
                a1 = addiu(s1, 4);
                for (;;) {
                    // 0x00498f34
                    charge(ctx, 4);
                    lw(v0, a1, 0);
                    lw(v0, v0, 8);
                    if (v0 != a2) {
                        // 0x00498f44
                        charge(ctx, 3);
                        a2 = v0;
                        a3 = addiu(a3, 1);
                    }
                    // 0x00498f50
                    charge(ctx, 4);
                    v1 = addiu(v1, 1);
                    v0 = sltu(v1, a0);
                    a1 = addiu(a1, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x00498f60
        charge(ctx, 13);
        v0 = sll(a3, 1);
        v1 = addu(v0, a3);
        v0 = sll(a0, 1);
        s3 = sll(v1, 2);
        v0 = addu(v0, a0);
        v1 = addiu(s3, 16);
        v0 = sll(v0, 1);
        s4 = addu(v1, v0);
        a0 = s4;
        jal(ctx, 0x498F80u, gen::fn_sub_4959C0_004959c0);
        s0 = v0;
        if (s0 == 0) {
            // 0x004990b4
            charge(ctx, 15);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            a0 = s1;
            jalr(ctx, 0x4990BCu, v0.u());
            v0 = 2;
            a1 = s4;
            sw(v0, sp, 0x68);
            v0 = lui(0x8000);
            a0 = v0 | 0x13;
            jal(ctx, 0x4990D4u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x6C);
            a0 = addiu(sp, 0x68);
            jal(ctx, 0x4990E0u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        } else {
            // 0x00498f94
            charge(ctx, 28);
            sw(zero, s0, 0);
            v0 = 1;
            sh(v0, s0, 4);
            t0 = 0x960000;
            lw(a2, gp, -17568);  // 0x7CE850
            t0 = addiu(t0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            a1 = addiu(s0, 16);
            v0 = 0;
            a0 = addu(a1, s3);
            v1 = s1;
            a2 = addu(t0, a2);
            lh(a2, a2, 0);
            sh(a2, s0, 6);
            sw(zero, s0, 12);
            lw(a3, s2, 4);
            a2 = sll(a3, 1);
            a2 = addu(a2, a3);
            sw(a2, s0, 8);
            lw(a2, gp, -17568);  // 0x7CE850
            a3 = addu(t0, a2);
            lh(a2, a3, 0);
            a2 = addiu(a2, 1);
            sh(a2, a3, 0);
            sw(zero, s0, 20);
            lw(a2, s1, 0);
            lw(a2, a2, 8);
            sw(a2, s0, 24);
            sw(a0, s0, 16);
            for (;;) {
                // 0x00499004
                charge(ctx, 5);
                lw(a3, v1, 0);
                lw(a2, a1, 8);
                lw(a3, a3, 8);
                if (a3 != a2) {
                    // 0x00499018
                    charge(ctx, 10);
                    a1 = addiu(a1, 12);
                    sw(zero, a1, 4);
                    lw(a2, v1, 0);
                    lw(a2, a2, 8);
                    sw(a2, a1, 8);
                    sw(a0, a1, 0);
                    lhu(a2, s0, 4);
                    a2 = addiu(a2, 1);
                    sh(a2, s0, 4);
                }
                // 0x00499040
                charge(ctx, 18);
                lw(a2, v1, 0);
                v0 = addiu(v0, 1);
                lhu(a2, a2, 0);
                sh(a2, a0, 0);
                lw(a2, v1, 0);
                lhu(a2, a2, 2);
                sh(a2, a0, 2);
                lw(a2, v1, 0);
                lhu(a2, a2, 4);
                v1 = addiu(v1, 4);
                sh(a2, a0, 4);
                lw(a2, a1, 4);
                a2 = addiu(a2, 3);
                sw(a2, a1, 4);
                lw(a2, s2, 4);
                a2 = sltu(v0, a2);
                a0 = addiu(a0, 6);
                if (a2 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00499088
            charge(ctx, 11);
            a1 = 0x490000;
            a0 = s0;
            a1 = addiu(a1, 26528);  // &sub_4967A0
            a2 = 0;
            jal(ctx, 0x499094u, gen::fn_meshHeaderForAllMeshes_00495f10);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            a0 = s1;
            jalr(ctx, 0x4990A4u, v0.u());
            v0 = s0;
        }
    }
    // 0x0049911c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// sub_49E5A0 [objectMeshCacheResize] -- re-allocates an object's mesh cache (the resEntries per mesh)
// ($a0 -> the cache pointer, $a1 = the mesh count) An old cache: from the last slot down, a resEntry still in
// the arena lists gets its owner pointer cleared, one outside is released (sub_49CC30, sub_4C47E0); the
// cache freed. Then a new one: RwMalloc(4 x (count - 1) + 8, hint 0x3050D), +0 = count, the slots zeroed.
// Returns $a0.
// 0x0049E5A0 sub_49E5A0 -- 284 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49E5A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049e5a0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 0);
    s4 = a1;
    if (s1 != 0) {
        // 0x0049e5d0
        charge(ctx, 3);
        lw(v0, s1, 0);
        s3 = addiu(v0, -1);
        if (v0 != 0) {
            // 0x0049e5dc
            charge(ctx, 2);
            v0 = sll(s3, 2);
            s2 = addu(s1, v0);
            for (;;) {
                // 0x0049e5e4
                charge(ctx, 3);
                lw(s0, s2, 4);
                if (s0 != 0) {
                    // 0x0049e5f0
                    charge(ctx, 3);
                    lw(v0, s0, 0);
                    if (v0 != 0) {
                        // 0x0049e5fc
                        charge(ctx, 1);
                        goto L_0049e600;
                    }
                    // 0x0049e608
                    charge(ctx, 3);
                    lw(v0, s0, 4);
                    if (v0 != 0) {
                        backedge(ctx);
                    L_0049e600:
                        charge(ctx, 2);
                        sw(zero, s0, 16);
                    } else {
                        // 0x0049e614
                        charge(ctx, 5);
                        a0 = s0;
                        jal(ctx, 0x49E614u, gen::fn_sub_49CC30_0049cc30);
                        a0 = s0;
                        jal(ctx, 0x49E61Cu, gen::fn_sub_4C47E0_004c47e0);
                    }
                }
                // 0x0049e628
                charge(ctx, 4);
                v0 = s3;
                s2 = addiu(s2, -4);
                s3 = addiu(s3, -1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0049e638
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        a0 = s1;
        jalr(ctx, 0x49E640u, v0.u());
        sw(zero, s5, 0);
    }
    // 0x0049e64c
    charge(ctx, 12);
    v0 = 0x30000;
    v1 = addiu(s4, -1);
    a1 = v0 | 0x50D;
    v1 = sll(v1, 2);
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    a0 = addiu(v1, 8);
    jalr(ctx, 0x49E664u, v0.u());
    sw(v0, s5, 0);
    lw(v0, s5, 0);
    if (v0 != 0) {
        // 0x0049e67c
        charge(ctx, 6);
        sw(s4, v0, 0);
        a2 = sll(s4, 2);
        lw(v0, s5, 0);
        a1 = 0;
        a0 = addiu(v0, 4);
        jal(ctx, 0x49E68Cu, gen::fn_memset_00521408);
    }
    // 0x0049e694 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v0 = s5;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// sub_4A08F0 [ps2AllAtomicResEntryAlloc] -- allocates an atomic's instance data (PS2All resEntry callback)
// ($a0 = the PS2All object, $a1 = where the pointer goes, $a2 = the size, $a3 = the destroy notification)
// An object with +36 uses the arena (sub_4C4930) for its atomic; else the geometry's flags bit 25 (native):
// RwMalloc(size + 24, hint 0x3050D) with a resEntry header outside the arena (not linked, owner = the
// geometry); otherwise the arena for the geometry. Returns the entry.
// 0x004A08F0 sub_4A08F0 -- 212 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4A08F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a08f0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    lw(v0, a0, 36);
    s1 = a3;
    if (v0 != 0) {
        // 0x004a099c
        charge(ctx, 4);
        link(ctx, 0x4A099Cu);  // $ra first: the delay slot below depends on it
        lw(a0, a0, 8);
        call(ctx, gen::fn_sub_4C4930_004c4930);
        sw(v0, s3, 0);
        backedge(ctx);
    } else {
        // 0x004a091c
        charge(ctx, 7);
        lw(v1, a0, 8);
        v0 = 0x2000000;
        lw(s0, v1, 24);
        lw(v1, s0, 8);
        v0 = v1 & v0;
        if (v0 == 0) {
            // 0x004a0988
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x4A0988u, gen::fn_sub_4C4930_004c4930);
            sw(v0, s3, 0);
        } else {
            // 0x004a0938
            charge(ctx, 20);
            v0 = 0x30000;
            a1 = v0 | 0x50D;
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
            a0 = addiu(s2, 24);
            jalr(ctx, 0x4A0948u, v0.u());
            sw(v0, s3, 0);
            lw(v1, s3, 0);
            sw(zero, v1, 0);
            lw(v1, s3, 0);
            sw(zero, v1, 4);
            lw(v1, s3, 0);
            sw(s0, v1, 12);
            lw(v1, s3, 0);
            sw(s2, v1, 8);
            lw(v1, s3, 0);
            sw(s3, v1, 16);
            lw(v1, s3, 0);
            sw(s1, v1, 20);
        }
    }
    // 0x004a0994
    charge(ctx, 2);
    ld(ra, sp, 0x40);
    // 0x004a09ac
    charge(ctx, 6);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4A0CE0 [ps2AllMeshResEntryAllocCB] -- the PS2All mesh resEntry callback: world sectors here, atomics through
//   sub_4A08F0
// An object whose type byte is 0xFF (a world sector): with the world's flags bit 25 (native) a header outside
// the arena (RwMalloc, as sub_4A08F0), else the arena (sub_4C4930). Other objects: sub_4A08F0. Returns *$a1.
// 0x004A0CE0 sub_4A0CE0 -- 224 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4A0CE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a0ce0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 255;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    lw(s0, a0, 8);
    lbu(v1, s0, 0);
    s1 = a3;
    if (v1 != v0) {
        // 0x004a0d94
        charge(ctx, 4);
        jal(ctx, 0x4A0D94u, gen::fn_sub_4A08F0_004a08f0);
        backedge(ctx);
    } else {
        // 0x004a0d14
        charge(ctx, 7);
        v0 = 0x960000;
        v1 = 0x2000000;
        lw(v0, v0, 116);  // 0x960074 (engine +4: the current world)
        lw(v0, v0, 8);
        v0 = v0 & v1;
        if (v0 == 0) {
            // 0x004a0d80
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x4A0D80u, gen::fn_sub_4C4930_004c4930);
            sw(v0, s3, 0);
        } else {
            // 0x004a0d30
            charge(ctx, 20);
            v0 = 0x30000;
            a1 = v0 | 0x50D;
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
            a0 = addiu(s2, 24);
            jalr(ctx, 0x4A0D40u, v0.u());
            sw(v0, s3, 0);
            lw(v0, s3, 0);
            sw(zero, v0, 0);
            lw(v0, s3, 0);
            sw(zero, v0, 4);
            lw(v0, s3, 0);
            sw(s0, v0, 12);
            lw(v0, s3, 0);
            sw(s2, v0, 8);
            lw(v0, s3, 0);
            sw(s3, v0, 16);
            lw(v0, s3, 0);
            sw(s1, v0, 20);
        }
    }
    // 0x004a0d8c
    charge(ctx, 2);
    lw(v0, s3, 0);
    // 0x004a0da4
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_47BB40 [ptankClonePipeAlloc] -- allocates a PTank clone pipeline's matrix array (RwMalloc, 16-aligned)
// ($a0 = the PTank data, $a1 = the particle count, $a2 = flags) count x 64 + 28 (+ 4 per particle with flag 2)
// + 16 bytes (hint 0x3012F); the 16-aligned header is cleared, the record's 72 bytes zeroed, the matrices
// start at header + 27 rounded to 16, stride 64; each matrix identity (flags 0x20003); with flag 2 a colour
// array of 0xFF bytes follows. Returns the block or 0.
// 0x0047BB40 sub_47BB40 -- 468 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_47BB40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0047bb40
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    v1 = 12;
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = sll(s3, 6);
    v0 = addiu(s1, 16);
    s0 = a2 & 0x2;
    v1 = addu(v1, v0);
    if (s0 != 0) {
        // 0x0047bb80
        charge(ctx, 2);
        v0 = sll(s3, 2);
        v1 = addu(v1, v0);
    }
    // 0x0047bb88
    charge(ctx, 9);
    v0 = 0x30000;
    a1 = v0 | 0x12F;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    a0 = addiu(v1, 16);
    jalr(ctx, 0x47BB98u, v0.u());
    s2 = v0;
    if (s2 == 0) {
        // 0x0047bc94
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0047bbac
        charge(ctx, 30);
        v1 = addiu(s2, 15);
        v0 = si(-16);
        s5 = v1 & v0;
        a0 = addiu(s4, 4);
        sw(zero, s5, 4);
        a1 = 0;
        sw(zero, s5, 8);
        a2 = 72;
        sw(zero, s5, 0);
        link(ctx, 0x47BBD0u);  // $ra first: the delay slot below depends on it
        sw(s5, s4, 76);
        call(ctx, gen::fn_memset_00521408);
        v1 = addiu(s5, 12);
        v0 = si(-16);
        v1 = addiu(v1, 15);
        a0 = 64;
        v0 = v1 & v0;
        at = slt(0, s3);
        sw(v0, s4, 12);
        v1 = 1;
        sw(a0, s4, 16);
        v0 = 8;
        sw(v1, s4, 80);
        t0 = 0;
        sw(zero, s4, 84);
        sw(v0, s4, 88);
        lwc1(f1, s4, 12);
        lwc1(f0, s4, 16);
        swc1(f1, sp, 0x78);
        swc1(f0, sp, 0x7C);
        if (at != 0) {
            // 0x0047bc24
            charge(ctx, 5);
            v0 = addiu(sp, 0x7C);
            a3 = 0x3F800000;
            lw(a0, v0, 0);
            v0 = 0x20000;
            a1 = v0 | 0x3;
            for (;;) {
                // 0x0047bc38
                charge(ctx, 21);
                lw(a2, sp, 0x78);
                t0 = addiu(t0, 1);
                v0 = slt(t0, s3);
                sw(a3, a2, 40);
                v1 = addu(a2, a0);
                sw(a3, a2, 20);
                sw(a3, a2, 0);
                sw(zero, a2, 16);
                sw(zero, a2, 8);
                sw(zero, a2, 4);
                sw(zero, a2, 36);
                sw(zero, a2, 32);
                sw(zero, a2, 24);
                sw(zero, a2, 56);
                sw(zero, a2, 52);
                sw(v1, sp, 0x78);
                sw(zero, a2, 48);
                lw(v1, a2, 12);
                v1 = v1 | a1;
                sw(v1, a2, 12);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0047bc8c
            charge(ctx, 2);
        }
        // 0x0047bc9c
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x0047bcac
            charge(ctx, 17);
            lw(v1, s4, 12);
            v0 = 4;
            a2 = sll(s3, 2);
            v1 = addu(v1, s1);
            sw(v1, s4, 36);
            sw(v0, s4, 40);
            lw(v0, s4, 80);
            v0 = addiu(v0, 1);
            sw(v0, s4, 80);
            lw(v0, s4, 88);
            v0 = v0 | 0x2;
            sw(v0, s4, 88);
            lw(a0, s4, 36);
            a1 = 255;
            jal(ctx, 0x47BCE0u, gen::fn_memset_00521408);
            backedge(ctx);
        }
        // 0x0047bca4
        charge(ctx, 2);
        v0 = s2;
    }
    // 0x0047bcf0 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// sub_47BE10 [ptankClonePipeRender] -- renders a PTank's clone pipeline (the render-state wrapped draw)
// With per-particle blending (+100) the vertex-alpha state on and the blend states saved / set (RenderStateGet /
// Set 0x960094 / 0x960090); with flag 2 sub_47B280 draws the colour path, else the frame's LTM (sub_4CB2F0)
// and sub_4733C0 / sub_47B750; the blend states restored. Returns 0.
// 0x0047BE10 sub_47BE10 -- 356 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_47BE10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0047be10
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, -17792);  // 0x7CE770
    lw(v0, a1, 100);
    v1 = addu(a0, v1);
    lw(v1, v1, 0);
    lw(s2, v1, 156);
    s3 = a2;
    if (v0 != 0) {
        // 0x0047bebc
        charge(ctx, 26);
        s1 = 0x960000;
        a0 = 12;
        s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        a1 = 1;
        jalr(ctx, 0x47BECCu, v0.u());
        s0 = 0x960000;
        a0 = 10;
        s0 = addiu(s0, 148);  // &pfn_RwRenderStateGet
        lw(v0, s0, 0);  // pfn_RwRenderStateGet
        a1 = addiu(sp, 0x6C);
        jalr(ctx, 0x47BEE4u, v0.u());
        lw(a1, s4, 92);
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        a0 = 10;
        jalr(ctx, 0x47BEF4u, v0.u());
        lw(v0, s0, 0);  // pfn_RwRenderStateGet
        a0 = 11;
        a1 = addiu(sp, 0x68);
        jalr(ctx, 0x47BF04u, v0.u());
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        lw(a1, s4, 96);
        a0 = 11;
        jalr(ctx, 0x47BF14u, v0.u());
        lw(v0, s4, 88);
        backedge(ctx);
    } else {
        // 0x0047be4c
        charge(ctx, 1);
        lw(v0, s4, 88);
    }
    // 0x0047be50
    charge(ctx, 3);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x0047be78
        charge(ctx, 13);
        lw(v0, s2, 8);
        link(ctx, 0x47BE7Cu);  // $ra first: the delay slot below depends on it
        lw(a0, v0, 4);
        call(ctx, gen::fn_sub_4CB2F0_004cb2f0);
        lw(a0, s2, 4);
        lw(a1, s2, 8);
        s0 = v0;
        jal(ctx, 0x47BE8Cu, gen::fn_sub_4733C0_004733c0);
        lw(a0, s2, 0);
        a2 = s3;
        lw(a1, s4, 12);
        a3 = addiu(s0, 32);
        jal(ctx, 0x47BEA0u, gen::fn_sub_47B750_0047b750);
        lw(v0, s4, 100);
    } else {
        // 0x0047be5c
        charge(ctx, 7);
        lw(a0, s2, 0);
        lw(a1, s4, 12);
        lw(a3, s4, 36);
        a2 = s3;
        jal(ctx, 0x47BE68u, gen::fn_sub_47B280_0047b280);
        lw(v0, s4, 100);
    }
    // 0x0047beac
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x0047bf24
        charge(ctx, 12);
        s0 = 0x960000;
        lw(a1, sp, 0x6C);
        s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        a0 = 10;
        jalr(ctx, 0x47BF34u, v0.u());
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        lw(a1, sp, 0x68);
        a0 = 11;
        jalr(ctx, 0x47BF44u, v0.u());
        backedge(ctx);
    }
    // 0x0047beb4
    charge(ctx, 2);
    v0 = 0;
    // 0x0047bf54
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// sub_4CA9B0 [frameModuleOpen] -- the frame module's open: the free list, the dirty-frame list
// ($a0 = the engine instance, $a1 = the module's offset) The offset goes to gp word 0x7CE930; the frame free
// list is created (sub_4C3B60: entry size = the frame registry's size, the block / preallocation counts of
// 0x7CDD6C / 0x7CDD70, alignment 16, the static record 0x964070, hint 0x4000E) into the module's word; with
// it the dirty-frame list 0x96012C is emptied (both links point at the head) and the open count goes up.
// Returns $a0, or 0 when the free list could not be made.
// 0x004CA9B0 sub_4CA9B0 -- 152 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4CA9B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ca9b0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x780000;
    sq(s0, sp, 0x0);
    a2 = 16;
    s0 = a0;
    sw(a1, gp, -17344);  // 0x7CE930 (the frame module offset)
    lw(a0, v0, -6544);  // 0x77E670 (the RwFrame plugin registry)
    t0 = addiu(t0, 16496);  // &0x964070 (the frame free list, static)
    lw(a1, gp, -20356);  // 0x7CDD6C (the frame free list: entries per block)
    lw(a3, gp, -20352);  // 0x7CDD70 (the frame free list: preallocated blocks)
    v0 = 0x40000;
    t1 = v0 | 0xE;
    jal(ctx, 0x4CA9E4u, gen::fn_sub_4C3B60_004c3b60);
    lw(a0, gp, -17344);  // 0x7CE930 (the frame module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = addu(v1, a0);
    sw(v0, v1, 0);
    lw(v0, v1, 0);
    if (v0 != 0) {
        // 0x004caa14: the free list exists: empty the dirty list, count the open
        charge(ctx, 9);
        a0 = 0x960000;
        v1 = 0x960000;
        a0 = addiu(a0, 300);  // &0x96012C (the dirty-frame list head)
        v0 = s0;
        sw(a0, v1, 304);  // 0x960130 (the dirty-frame list: prev)
        lw(v1, gp, -17340);  // 0x7CE934 (the frame module open count)
        sw(a0, a0, 0);  // 0x96012C (the dirty-frame list head)
        v1 = addiu(v1, 1);
        sw(v1, gp, -17340);  // 0x7CE934 (the frame module open count)
    } else {
        // 0x004caa0c: no free list: 0
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004caa38 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4CAA50 [frameModuleClose] -- the frame module's close: destroys the free list
// The module's free list (if any) goes to sub_4C3C30 and the word is cleared; the open count goes down; $v0 = $a0.
// 0x004CAA50 sub_4CAA50 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4CAA50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004caa50
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s0, sp, 0x0);
    lw(v1, gp, -17344);  // 0x7CE930 (the frame module offset)
    s0 = a0;
    v0 = addu(v0, v1);
    lw(a0, v0, 0);
    if (a0 != 0) {
        // 0x004caa7c: destroy the frame free list
        charge(ctx, 7);
        jal(ctx, 0x4CAA7Cu, gen::fn_sub_4C3C30_004c3c30);
        lw(v1, gp, -17344);  // 0x7CE930 (the frame module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        sw(zero, v0, 0);
    }
    // 0x004caa98 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(v1, gp, -17340);  // 0x7CE934 (the frame module open count)
    v0 = s0;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17340);  // 0x7CE934 (the frame module open count)
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4CAB70 [frameCloneRecurse] -- clones a frame and its subtree (one level of the clone)
// ($a0 = the source frame, $a1 = the clone hierarchy's root or 0) A frame from the free list (the slot 0x960188,
// hint 0x3000E) gets the source's four RwObject bytes, no parent, an empty object list, the source's modelling
// matrix (8 x 8 bytes), no children; its root is $a1 (0: the clone itself). The source's root word is pointed
// at its clone (the map the caller's link pass reads), then every child is cloned recursively and pushed at the
// head of the clone's child list (the order reverses); a child that fails destroys the partial clone
// (sub_4CB1B0) -> 0. Last the plugin constructors (sub_4C64B0) and the plugin copy from the source
// (sub_4C65D0). Returns the clone or 0.
// 0x004CAB70 sub_4CAB70 -- 368 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CAB70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004cab70
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v1 = 0x960000;
    sd(ra, sp, 0x40);
    v0 = 0x30000;
    sq(s3, sp, 0x30);
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(a0, gp, -17344);  // 0x7CE930 (the frame module offset)
    a1 = v0 | 0xE;
    v0 = 0x960000;
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    v1 = addu(v1, a0);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4CABB0u);  // $ra = the return address
    lw(a0, v1, 0);
    call_ptr(ctx, jt);
    s0 = v0;
    if (s0 == 0) {
        // 0x004cacb4: no frame: 0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004cabc4: the clone: the root it hangs on (itself when $a1 is 0)
        charge(ctx, 2);
        if (s1 == 0) {
            // 0x004cacbc
            charge(ctx, 2);
            s1 = s0;
            backedge(ctx);
        }
        // 0x004cabcc: copy the RwObject bytes, empty the object list
        charge(ctx, 16);
        lbu(v1, s2, 0);
        v0 = addiu(s0, 144);
        a2 = addiu(s2, 16);
        a1 = addiu(s0, 16);
        a0 = 8;
        sb(v1, s0, 0);
        lbu(v1, s2, 1);
        sb(v1, s0, 1);
        lbu(v1, s2, 2);
        sb(v1, s0, 2);
        lbu(v1, s2, rwobj::kPrivateFlags);
        sb(v1, s0, rwobj::kPrivateFlags);
        sw(zero, s0, rwobj::kParent);
        sw(v0, s0, rwframe::kObjects);
        sw(v0, s0, rwframe::kObjectsPrev);
        sw(zero, s0, rwobj::kParent);
        for (;;) {
            // 0x004cac0c: the modelling matrix, 8 bytes a step
            charge(ctx, 8);
            lw(v1, a2, 0);
            a0 = addiu(a0, -1);
            lw(v0, a2, 4);
            sw(v1, a1, 0);
            a2 = addiu(a2, 8);
            sw(v0, a1, 4);
            a1 = addiu(a1, 8);
            if (i64(a0) <= 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004cac2c: no children yet; the source's root word -> its clone
        charge(ctx, 7);
        sw(zero, s0, rwframe::kChild);
        sw(zero, s0, rwframe::kNext);
        sw(s1, s0, rwframe::kRoot);
        sw(s0, s2, rwframe::kRoot);
        lw(s3, s2, rwframe::kChild);
        if (s3 != 0) {
            for (;;) {
                // 0x004cac48: clone the next child
                charge(ctx, 5);
                a0 = s3;
                a1 = s1;
                jal(ctx, 0x4CAC4Cu, gen::fn_sub_4CAB70_004cab70);
                if (v0 == 0) {
                    goto L_004cac5c_6;
                }
                // 0x004cac6c: push it at the head of the clone's child list
                charge(ctx, 7);
                lw(v1, s0, rwframe::kChild);
                sw(v1, v0, rwframe::kNext);
                sw(v0, s0, rwframe::kChild);
                sw(s0, v0, rwobj::kParent);
                lw(s3, s3, rwframe::kNext);
                if (s3 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004cac88: the plugin data: construct, then copy
        charge(ctx, 11);
        a0 = 0x780000;
        a0 = addiu(a0, -6544);  // &0x77E670 (the RwFrame plugin registry)
        a1 = s0;
        jal(ctx, 0x4CAC90u, gen::fn_sub_4C64B0_004c64b0);
        a0 = 0x780000;
        a2 = s2;
        a0 = addiu(a0, -6544);  // &0x77E670 (the RwFrame plugin registry)
        a1 = s0;
        jal(ctx, 0x4CACA4u, gen::fn_sub_4C65D0_004c65d0);
        v0 = s0;
    }
    // 0x004cacc4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_004cac5c_6:  // a child failed: destroy the partial clone, 0
    charge(ctx, 4);
    a0 = s0;
    jal(ctx, 0x4CAC5Cu, gen::fn_sub_4CB1B0_004cb1b0);
    v0 = 0;
    // 0x004cacc4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4CACE0 [frameCloneHierarchy] -- clones a whole hierarchy and marks the clone dirty
// sub_4CAB70(frame, 0); a clone gets its private flags bits 0..1 cleared (it is in no dirty list yet) and goes
// to sub_4CB270 (the dirty list). Returns the clone or 0.
// 0x004CACE0 sub_4CACE0 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4CACE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cace0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 0;
    sd(ra, sp, 0x10);
    link(ctx, 0x4CACECu);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4CAB70_004cab70);
    s0 = v0;
    if (s0 != 0) {
        // 0x004cad00: the clone: not in the dirty list yet; mark it dirty
        charge(ctx, 6);
        lbu(v1, s0, rwobj::kPrivateFlags);
        v0 = si(-4);
        a0 = s0;
        v0 = v1 & v0;
        link(ctx, 0x4CAD10u);  // $ra first: the delay slot below depends on it
        sb(v0, s0, rwobj::kPrivateFlags);
        call(ctx, gen::fn_sub_4CB270_004cb270);
    }
    // 0x004cad18 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4CAD30 [frameSetHierarchyRoot] -- re-points every frame of a subtree at its hierarchy's root
// (The clump clone's second pass, after the clone map is no longer needed.) The root is the parent's root, or the
// frame itself without a parent; the frame, its children and their children get it here, deeper levels
// through sub_4CAAC0. Returns the frame.
// 0x004CAD30 sub_4CAD30 -- 256 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CAD30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cad30
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 4);
    s0 = a0;
    if (v0 == 0) {
        // 0x004cadbc: no parent: the frame is its own root
        charge(ctx, 4);
        sw(s0, s0, rwframe::kRoot);
        lw(s2, s0, rwframe::kChild);
        if (s2 == 0) {
            backedge(ctx);
        } else {
            for (;;) {
                // 0x004cadcc: a child: the root, then its children (sub_4CAAC0 walks the deeper levels)
                charge(ctx, 4);
                sw(s0, s2, rwframe::kRoot);
                lw(s1, s2, rwframe::kChild);
                if (s1 != 0) {
                    // 0x004caddc
                    charge(ctx, 1);
                    for (;;) {
                        // 0x004cade0
                        charge(ctx, 7);
                        a0 = s1;
                        a1 = s0;
                        jal(ctx, 0x4CADE4u, gen::fn_sub_4CAAC0_004caac0);
                        lw(s1, s1, rwframe::kNext);
                        if (s1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004cadfc
                    charge(ctx, 1);
                }
                // 0x004cae00
                charge(ctx, 3);
                lw(s2, s2, rwframe::kNext);
                if (s2 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004cae0c
            charge(ctx, 2);
            backedge(ctx);
        }
    } else {
        // 0x004cad54: a parent: its root
        charge(ctx, 5);
        lw(s2, v0, rwframe::kRoot);
        sw(s2, s0, rwframe::kRoot);
        lw(s3, s0, rwframe::kChild);
        if (s3 != 0) {
            for (;;) {
                // 0x004cad68: a child: the root, then its children (sub_4CAAC0 walks the deeper levels)
                charge(ctx, 4);
                sw(s2, s3, rwframe::kRoot);
                lw(s1, s3, rwframe::kChild);
                if (s1 == 0) {
                    // 0x004cada8
                    charge(ctx, 1);
                    lw(s3, s3, rwframe::kNext);
                } else {
                    for (;;) {
                        // 0x004cad78
                        charge(ctx, 7);
                        a0 = s1;
                        a1 = s2;
                        jal(ctx, 0x4CAD7Cu, gen::fn_sub_4CAAC0_004caac0);
                        lw(s1, s1, rwframe::kNext);
                        if (s1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004cad94
                    charge(ctx, 2);
                    lw(s3, s3, rwframe::kNext);
                }
                // 0x004cadac
                charge(ctx, 2);
                if (s3 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004cadb4
            charge(ctx, 2);
            backedge(ctx);
        }
    }
    // 0x004cada0
    charge(ctx, 2);
    v0 = s0;
    // 0x004cae14
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4CAE40 [frameInit] -- initialises a fresh frame and runs the frame plugins' constructors
// Zero RwObject bytes, no parent, an empty object list, the modelling and LTM matrices identity (flags 3, then
// |= 0x20003: orthogonal, normal, identity), no children, the root itself; then sub_4C64B0(frame registry,
// frame) as a tail call (its result is the function's).
// 0x004CAE40 sub_4CAE40 -- 204 bytes; leaf frame (no stack)
void sub_4CAE40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x004cae40
    enter(ctx, 51);  // entry check point + this block's cycles
    sb(zero, a0, 0);
    a1 = a0;
    sb(zero, a0, 1);
    v1 = addiu(a1, 144);
    sb(zero, a0, 2);
    a3 = 3;
    sb(zero, a0, rwobj::kPrivateFlags);
    a2 = 0x3F800000;
    sw(zero, a0, rwobj::kParent);
    v0 = 0x20000;
    sw(v1, a0, rwframe::kObjects);
    sw(v1, a0, rwframe::kObjectsPrev);
    sw(a3, a0, rwframe::kModellingFlags);
    v1 = v0 | 0x3;
    sw(a2, a0, 56);
    sw(a2, a0, 36);
    sw(a2, a0, rwframe::kModelling);
    sw(zero, a0, 32);
    sw(zero, a0, 24);
    sw(zero, a0, 20);
    sw(zero, a0, 52);
    sw(zero, a0, 48);
    sw(zero, a0, 40);
    sw(zero, a0, 72);
    sw(zero, a0, 68);
    sw(zero, a0, 64);
    lw(v0, a0, rwframe::kModellingFlags);
    v0 = v0 | v1;
    sw(v0, a0, rwframe::kModellingFlags);
    sw(a3, a0, rwframe::kLtmFlags);
    sw(a2, a0, 120);
    sw(a2, a0, 100);
    sw(a2, a0, rwframe::kLtm);
    sw(zero, a0, 96);
    sw(zero, a0, 88);
    sw(zero, a0, 84);
    sw(zero, a0, 116);
    sw(zero, a0, 112);
    sw(zero, a0, 104);
    sw(zero, a0, 136);
    sw(zero, a0, 132);
    sw(zero, a0, 128);
    lw(v0, a0, rwframe::kLtmFlags);
    v0 = v0 | v1;
    sw(v0, a0, rwframe::kLtmFlags);
    sw(zero, a0, rwframe::kChild);
    sw(zero, a0, rwframe::kNext);
    sw(a1, a0, rwframe::kRoot);
    a0 = 0x780000;
    a0 = addiu(a0, -6544);  // &0x77E670 (the RwFrame plugin registry)
    gen::fn_sub_4C64B0_004c64b0(ctx);  // tail call
}

// sub_4CAF10 [frameCreate] -- creates a frame (the free list, then sub_4CAE40)
// A frame from the module's free list through the slot 0x960188 (hint 0x3000E), initialised by sub_4CAE40.
// Returns the frame or 0.
// 0x004CAF10 sub_4CAF10 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4CAF10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004caf10
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x30000;
    sq(s0, sp, 0x0);
    a1 = v0 | 0xE;
    lw(a0, gp, -17344);  // 0x7CE930 (the frame module offset)
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = 0x960000;
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    v1 = addu(v1, a0);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4CAF3Cu);  // $ra = the return address
    lw(a0, v1, 0);
    call_ptr(ctx, jt);
    s0 = v0;
    if (s0 == 0) {
        // 0x004caf60: no memory: 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004caf50: initialise it
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x4CAF50u, gen::fn_sub_4CAE40_004cae40);
        v0 = s0;
    }
    // 0x004caf64 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4CAF80 [frameDestroy] -- destroys one frame: plugins, parent, dirty list, children orphaned, freed
// The frame plugins' destructors (sub_4C6560), the frame taken off its parent (sub_4CB590) if it has one, out of
// the dirty-frame list when its bits 0..1 say it is in it, each child's parent cleared (the children stay
// alive), the record back to the free list (slot 0x96018C). Returns 1.
// 0x004CAF80 sub_4CAF80 -- 208 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4CAF80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004caf80
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 0x780000;
    a1 = s0;
    a0 = addiu(a0, -6544);  // &0x77E670 (the RwFrame plugin registry)
    jal(ctx, 0x4CAF98u, gen::fn_sub_4C6560_004c6560);
    lw(v0, s0, rwobj::kParent);
    if (v0 != 0) {
        // 0x004cafec: detach from the parent
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x4CAFECu, gen::fn_sub_4CB590_004cb590);
        lbu(v0, s0, rwobj::kPrivateFlags);
        backedge(ctx);
    } else {
        // 0x004cafac
        charge(ctx, 1);
        lbu(v0, s0, rwobj::kPrivateFlags);
    }
    // 0x004cafb0
    charge(ctx, 3);
    v0 = v0 & 0x3;
    if (v0 != 0) {
        // 0x004caffc: in the dirty list: unlink
        charge(ctx, 7);
        lw(v1, s0, rwframe::kDirtyNext);
        lw(v0, s0, rwframe::kDirtyPrev);
        sw(v1, v0, 0);
        lw(v1, s0, rwframe::kDirtyPrev);
        lw(v0, s0, rwframe::kDirtyNext);
        sw(v1, v0, rwobj::kParent);
        backedge(ctx);
    }
    // 0x004cafbc
    charge(ctx, 3);
    lw(v0, s0, rwframe::kChild);
    if (v0 == 0) {
        // 0x004cb018
        charge(ctx, 1);
        lw(a0, gp, -17344);  // 0x7CE930 (the frame module offset)
    } else {
        for (;;) {
            // 0x004cafc8: orphan the next child
            charge(ctx, 7);
            sw(zero, v0, rwobj::kParent);
            lw(v0, v0, rwframe::kNext);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004cafe4
        charge(ctx, 2);
        lw(a0, gp, -17344);  // 0x7CE930 (the frame module offset)
    }
    // 0x004cb01c: back to the frame free list
    charge(ctx, 13);
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = 0x960000;
    lw(v0, v0, 396);  // 0x96018C (free-list free slot)
    v1 = addu(v1, a0);
    lw(a0, v1, 0);
    a1 = s0;
    jalr(ctx, 0x4CB034u, v0.u());
    ld(ra, sp, 0x10);
    v0 = 1;
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4CB050 [frameDestroySubtree] -- destroys a frame's subtree and the frame (recursive)
// For each child: its own children recursively, then the child itself (plugin destructors, dirty-list unlink,
// free); then the frame the same way. No parent is detached (the caller destroys whole hierarchies).
// 0x004CB050 sub_4CB050 -- 344 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CB050(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cb050
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (s3 != 0) {
        // 0x004cb074: the children
        charge(ctx, 3);
        lw(s2, s3, rwframe::kChild);
        if (s2 != 0) {
            // 0x004cb080
            charge(ctx, 2);
            s0 = 0x960000;
            s0 = addiu(s0, 396);  // &0x96018C (free-list free slot)
            for (;;) {
                // 0x004cb088: the next child (its sibling read first)
                charge(ctx, 2);
                lw(s1, s2, rwframe::kNext);
                if (s2 != 0) {
                    // 0x004cb090
                    charge(ctx, 3);
                    lw(a0, s2, rwframe::kChild);
                    if (a0 != 0) {
                        // 0x004cb09c
                        charge(ctx, 1);
                        for (;;) {
                            // 0x004cb0a0: the child's children, recursively
                            charge(ctx, 7);
                            link(ctx, 0x4CB0A0u);  // $ra first: the delay slot below depends on it
                            lw(s4, a0, rwframe::kNext);
                            call(ctx, gen::fn_sub_4CB050_004cb050);
                            a0 = s4;
                            if (s4 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004cb0bc
                        charge(ctx, 1);
                    }
                    // 0x004cb0c0: the child: plugin destructors
                    charge(ctx, 8);
                    a0 = 0x780000;
                    a0 = addiu(a0, -6544);  // &0x77E670 (the RwFrame plugin registry)
                    a1 = s2;
                    jal(ctx, 0x4CB0C8u, gen::fn_sub_4C6560_004c6560);
                    lbu(v0, s2, rwobj::kPrivateFlags);
                    v0 = v0 & 0x3;
                    if (v0 != 0) {
                        // 0x004cb16c: in the dirty list: unlink
                        charge(ctx, 7);
                        lw(v1, s2, rwframe::kDirtyNext);
                        lw(v0, s2, rwframe::kDirtyPrev);
                        sw(v1, v0, 0);
                        lw(v1, s2, rwframe::kDirtyPrev);
                        lw(v0, s2, rwframe::kDirtyNext);
                        sw(v1, v0, 4);
                        backedge(ctx);
                    }
                    // 0x004cb0e0: the child: back to the free list
                    charge(ctx, 8);
                    lw(a0, gp, -17344);  // 0x7CE930 (the frame module offset)
                    v1 = 0x960000;
                    lw(v0, s0, 0);
                    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                    v1 = addu(v1, a0);
                    lw(a0, v1, 0);
                    a1 = s2;
                    jalr(ctx, 0x4CB0F8u, v0.u());
                }
                // 0x004cb100
                charge(ctx, 2);
                s2 = s1;
                if (s1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004cb108: the frame itself: plugin destructors
        charge(ctx, 8);
        a0 = 0x780000;
        a0 = addiu(a0, -6544);  // &0x77E670 (the RwFrame plugin registry)
        a1 = s3;
        jal(ctx, 0x4CB110u, gen::fn_sub_4C6560_004c6560);
        lbu(v0, s3, rwobj::kPrivateFlags);
        v0 = v0 & 0x3;
        if (v0 != 0) {
            // 0x004cb128: in the dirty list: unlink
            charge(ctx, 6);
            lw(v1, s3, rwframe::kDirtyNext);
            lw(v0, s3, rwframe::kDirtyPrev);
            sw(v1, v0, 0);
            lw(v1, s3, rwframe::kDirtyPrev);
            lw(v0, s3, rwframe::kDirtyNext);
            sw(v1, v0, 4);
        }
        // 0x004cb140: back to the free list
        charge(ctx, 11);
        lw(a0, gp, -17344);  // 0x7CE930 (the frame module offset)
        v1 = 0x960000;
        v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = 0x960000;
        lw(v0, v0, 396);  // 0x96018C (free-list free slot)
        v1 = addu(v1, a0);
        lw(a0, v1, 0);
        a1 = s3;
        jalr(ctx, 0x4CB15Cu, v0.u());
    }
    // 0x004cb188 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4CB1B0 [frameDestroyHierarchy] -- destroys a frame and everything below it
// Each child's subtree through sub_4CB050, then the frame (plugin destructors, dirty-list unlink, free). A null
// frame does nothing. Returns 1.
// 0x004CB1B0 sub_4CB1B0 -- 188 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CB1B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cb1b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (s0 != 0) {
        // 0x004cb1cc
        charge(ctx, 3);
        lw(a0, s0, rwframe::kChild);
        if (a0 != 0) {
            for (;;) {
                // 0x004cb1d8: the next child's subtree
                charge(ctx, 7);
                link(ctx, 0x4CB1D8u);  // $ra first: the delay slot below depends on it
                lw(s1, a0, rwframe::kNext);
                call(ctx, gen::fn_sub_4CB050_004cb050);
                a0 = s1;
                if (s1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004cb1f4
            charge(ctx, 1);
        }
        // 0x004cb1f8: the frame: plugin destructors
        charge(ctx, 8);
        a0 = 0x780000;
        a0 = addiu(a0, -6544);  // &0x77E670 (the RwFrame plugin registry)
        a1 = s0;
        jal(ctx, 0x4CB200u, gen::fn_sub_4C6560_004c6560);
        lbu(v0, s0, rwobj::kPrivateFlags);
        v0 = v0 & 0x3;
        if (v0 != 0) {
            // 0x004cb218: in the dirty list: unlink
            charge(ctx, 6);
            lw(v1, s0, rwframe::kDirtyNext);
            lw(v0, s0, rwframe::kDirtyPrev);
            sw(v1, v0, 0);
            lw(v1, s0, rwframe::kDirtyPrev);
            lw(v0, s0, rwframe::kDirtyNext);
            sw(v1, v0, 4);
        }
        // 0x004cb230: back to the free list
        charge(ctx, 9);
        lw(a0, gp, -17344);  // 0x7CE930 (the frame module offset)
        v1 = 0x960000;
        v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = 0x960000;
        lw(v0, v0, 396);  // 0x96018C (free-list free slot)
        v1 = addu(v1, a0);
        lw(a0, v1, 0);
        a1 = s0;
        jalr(ctx, 0x4CB24Cu, v0.u());
    }
    // 0x004cb254 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    v0 = 1;
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4CB270 [frameUpdateObjects] -- marks a frame dirty (the hierarchy's root joins the dirty list)
// The frame's root joins the dirty-frame list 0x96012C unless it is in it (root private flags bits 0..1); root |= 3,
// the frame |= 0xC. Returns the frame.
// 0x004CB270 sub_4CB270 -- 116 bytes; leaf frame (no stack)
void sub_4CB270(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x004cb270
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, a0, rwframe::kRoot);
    lbu(a2, v1, rwobj::kPrivateFlags);
    v0 = a2 & 0x3;
    if (v0 == 0) {
        // 0x004cb2a4: link the root at the head of the dirty list
        charge(ctx, 14);
        a1 = 0x960000;
        a1 = addiu(a1, 300);  // &0x96012C (the dirty-frame list head)
        lw(v0, a1, 0);  // 0x96012C (the dirty-frame list head)
        sw(v0, v1, rwframe::kDirtyNext);
        lw(v0, a0, rwframe::kRoot);
        sw(a1, v0, 12);
        lw(v1, a0, rwframe::kRoot);
        lw(v0, a1, 0);  // 0x96012C (the dirty-frame list head)
        v1 = addiu(v1, 8);
        sw(v1, v0, 4);
        lw(v0, a0, rwframe::kRoot);
        v0 = addiu(v0, 8);
        sw(v0, a1, 0);  // 0x96012C (the dirty-frame list head)
        backedge(ctx);
    }
    // 0x004cb284: root |= 3, frame |= 0xC
    charge(ctx, 8);
    lw(v1, a0, rwframe::kRoot);
    a1 = a2 | 0x3;
    v0 = a0;
    sb(a1, v1, rwobj::kPrivateFlags);
    lbu(v1, a0, rwobj::kPrivateFlags);
    v1 = v1 | 0xC;
    sb(v1, a0, rwobj::kPrivateFlags);
    // 0x004cb2dc
    charge(ctx, 2);
}

// sub_4CB340 [frameGetRoot] -- returns the frame's hierarchy root
// 0x004CB340 sub_4CB340 -- 8 bytes; leaf frame (no stack)
void sub_4CB340(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004cb340
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, rwframe::kRoot);
}

// sub_4CB350 [frameAddChildNoUpdate] -- adds a child at the head of a frame's child list, without marking dirty
// ($a0 = the parent, $a1 = the child) A child with a parent is detached first (sub_4CB590); then it heads the
// parent's child list, its parent is set, and the parent's root goes to it and its whole subtree. Returns the
// parent.
// 0x004CB350 sub_4CB350 -- 200 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CB350(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cb350
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(v0, a1, 4);
    s0 = a0;
    if (v0 != 0) {
        // 0x004cb3d8
        charge(ctx, 4);
        a0 = s1;
        jal(ctx, 0x4CB3D8u, gen::fn_sub_4CB590_004cb590);
        lw(v0, s0, rwframe::kChild);
        backedge(ctx);
    } else {
        // 0x004cb378
        charge(ctx, 1);
        lw(v0, s0, rwframe::kChild);
    }
    // 0x004cb37c
    charge(ctx, 8);
    sw(v0, s1, rwframe::kNext);
    sw(s1, s0, rwframe::kChild);
    sw(s0, s1, rwobj::kParent);
    lw(s2, s0, rwframe::kRoot);
    sw(s2, s1, rwframe::kRoot);
    lw(s3, s1, rwframe::kChild);
    if (s3 != 0) {
        for (;;) {
            // 0x004cb39c
            charge(ctx, 4);
            sw(s2, s3, 160);
            lw(s1, s3, 152);
            if (s1 == 0) {
                // 0x004cb3e8
                charge(ctx, 1);
                lw(s3, s3, 156);
            } else {
                // 0x004cb3ac
                charge(ctx, 1);
                for (;;) {
                    // 0x004cb3b0
                    charge(ctx, 7);
                    a0 = s1;
                    a1 = s2;
                    jal(ctx, 0x4CB3B4u, gen::fn_sub_4CAAC0_004caac0);
                    lw(s1, s1, rwframe::kNext);
                    if (s1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004cb3cc
                charge(ctx, 2);
                lw(s3, s3, 156);
            }
            // 0x004cb3ec
            charge(ctx, 2);
            if (s3 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004cb3f4
        charge(ctx, 1);
    }
    // 0x004cb3f8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = s0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4CB420 [frameAddChild] -- adds a child to a frame and marks it dirty
// As sub_4CB350, then: the child, if it was a root in the dirty list, is unlinked and loses bits 0..1; then the frame's
// root joins the dirty-frame list 0x96012C unless it is in it (root private flags bits 0..1); root |= 3, the frame |=
// 0xC.
// Returns the parent.
// 0x004CB420 sub_4CB420 -- 368 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CB420(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cb420
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, a1, 4);
    s0 = a1;
    if (v0 != 0) {
        // 0x004cb4a8: the child has a parent: detach it
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x4CB4A8u, gen::fn_sub_4CB590_004cb590);
        lw(v0, s1, rwframe::kChild);
        backedge(ctx);
    } else {
        // 0x004cb44c
        charge(ctx, 1);
        lw(v0, s1, rwframe::kChild);
    }
    // 0x004cb450: head of the parent's child list
    charge(ctx, 8);
    sw(v0, s0, rwframe::kNext);
    sw(s0, s1, rwframe::kChild);
    sw(s1, s0, rwobj::kParent);
    lw(s3, s1, rwframe::kRoot);
    sw(s3, s0, rwframe::kRoot);
    lw(s4, s0, rwframe::kChild);
    if (s4 != 0) {
        for (;;) {
            // 0x004cb470: the root down the child's subtree
            charge(ctx, 4);
            sw(s3, s4, rwframe::kRoot);
            lw(s2, s4, rwframe::kChild);
            if (s2 == 0) {
                // 0x004cb4b8
                charge(ctx, 1);
                lw(s4, s4, rwframe::kNext);
            } else {
                for (;;) {
                    // 0x004cb480
                    charge(ctx, 7);
                    a0 = s2;
                    a1 = s3;
                    jal(ctx, 0x4CB484u, gen::fn_sub_4CAAC0_004caac0);
                    lw(s2, s2, rwframe::kNext);
                    if (s2 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004cb49c
                charge(ctx, 2);
                lw(s4, s4, rwframe::kNext);
            }
            // 0x004cb4bc
            charge(ctx, 2);
            if (s4 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004cb4c4
        charge(ctx, 1);
    }
    // 0x004cb4c8: the child was a root in the dirty list?
    charge(ctx, 4);
    lbu(v0, s0, rwobj::kPrivateFlags);
    v0 = v0 & 0x3;
    v1 = addiu(s0, 3);
    if (v0 != 0) {
        // 0x004cb50c: unlink it, clear bits 0..1
        charge(ctx, 11);
        lw(a1, s0, rwframe::kDirtyNext);
        v0 = si(-4);
        lw(a0, s0, rwframe::kDirtyPrev);
        sw(a1, a0, 0);
        lw(a1, s0, rwframe::kDirtyPrev);
        lw(a0, s0, rwframe::kDirtyNext);
        sw(a1, a0, 4);
        lbu(a0, v1, 0);
        v0 = a0 & v0;
        sb(v0, s0, rwobj::kPrivateFlags);
        backedge(ctx);
    }
    // 0x004cb4d8: mark dirty: the new root joins the dirty list
    charge(ctx, 5);
    lw(a0, s0, rwframe::kRoot);
    lbu(a2, a0, rwobj::kPrivateFlags);
    v0 = a2 & 0x3;
    if (v0 == 0) {
        // 0x004cb538: link the root at the head of the dirty list
        charge(ctx, 14);
        a1 = 0x960000;
        a1 = addiu(a1, 300);  // &0x96012C (the dirty-frame list head)
        lw(v0, a1, 0);  // 0x96012C (the dirty-frame list head)
        sw(v0, a0, rwframe::kDirtyNext);
        lw(v0, s0, rwframe::kRoot);
        sw(a1, v0, 12);
        lw(a0, s0, rwframe::kRoot);
        lw(v0, a1, 0);  // 0x96012C (the dirty-frame list head)
        a0 = addiu(a0, 8);
        sw(a0, v0, 4);
        lw(v0, s0, rwframe::kRoot);
        v0 = addiu(v0, 8);
        sw(v0, a1, 0);  // 0x96012C (the dirty-frame list head)
        backedge(ctx);
    }
    // 0x004cb4ec: root |= 3, child |= 0xC
    charge(ctx, 8);
    lw(a0, s0, rwframe::kRoot);
    a1 = a2 | 0x3;
    v0 = s1;
    sb(a1, a0, rwobj::kPrivateFlags);
    lbu(v1, v1, 0);
    v1 = v1 | 0xC;
    sb(v1, s0, rwobj::kPrivateFlags);
    // 0x004cb570
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4CB590 [frameRemoveChild] -- takes a frame off its parent: it becomes its own hierarchy, marked dirty
// Unlinked from the parent's child list (the head, or found by walking the siblings), no parent, no sibling, its
// own root, which goes down its subtree; then the frame's root joins the dirty-frame list 0x96012C unless it is in it
// (root private flags bits 0..1); root |= 3, the frame |= 0xC. Returns the frame.
// 0x004CB590 sub_4CB590 -- 332 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CB590(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cb590
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 4);
    s0 = a0;
    lw(a0, v0, rwframe::kChild);
    v1 = addiu(v0, 152);
    if (a0 == s0) {
        // 0x004cb5e8: the head of the parent's list
        charge(ctx, 2);
        lw(v0, s0, rwframe::kNext);
        sw(v0, v1, 0);
    } else {
        // 0x004cb5b8: find the sibling before it
        charge(ctx, 3);
        lw(v0, a0, rwframe::kNext);
        if (v0 != s0) {
            for (;;) {
                // 0x004cb5c4
                charge(ctx, 7);
                a0 = v0;
                lw(v0, v0, rwframe::kNext);
                if (v0 == s0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004cb5e0
            charge(ctx, 2);
        }
        // 0x004cb640: unlink after the sibling
        charge(ctx, 3);
        lw(v0, s0, rwframe::kNext);
        sw(v0, a0, rwframe::kNext);
        backedge(ctx);
    }
    // 0x004cb5f0: its own hierarchy now
    charge(ctx, 6);
    sw(zero, s0, rwobj::kParent);
    sw(zero, s0, rwframe::kNext);
    sw(s0, s0, rwframe::kRoot);
    lw(s2, s0, rwframe::kChild);
    if (s2 != 0) {
        for (;;) {
            // 0x004cb608: the root down the subtree
            charge(ctx, 4);
            sw(s0, s2, rwframe::kRoot);
            lw(s1, s2, rwframe::kChild);
            if (s1 == 0) {
                // 0x004cb64c
                charge(ctx, 1);
                lw(s2, s2, rwframe::kNext);
            } else {
                for (;;) {
                    // 0x004cb618
                    charge(ctx, 7);
                    a0 = s1;
                    a1 = s0;
                    jal(ctx, 0x4CB61Cu, gen::fn_sub_4CAAC0_004caac0);
                    lw(s1, s1, rwframe::kNext);
                    if (s1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004cb634
                charge(ctx, 2);
                lw(s2, s2, rwframe::kNext);
            }
            // 0x004cb650
            charge(ctx, 2);
            if (s2 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004cb658: mark dirty
    charge(ctx, 5);
    lw(v1, s0, rwframe::kRoot);
    lbu(a1, v1, rwobj::kPrivateFlags);
    v0 = a1 & 0x3;
    if (v0 == 0) {
        // 0x004cb68c: link the root at the head of the dirty list
        charge(ctx, 14);
        a0 = 0x960000;
        a0 = addiu(a0, 300);  // &0x96012C (the dirty-frame list head)
        lw(v0, a0, 0);  // 0x96012C (the dirty-frame list head)
        sw(v0, v1, rwframe::kDirtyNext);
        lw(v0, s0, rwframe::kRoot);
        sw(a0, v0, 12);
        lw(v1, s0, rwframe::kRoot);
        lw(v0, a0, 0);  // 0x96012C (the dirty-frame list head)
        v1 = addiu(v1, 8);
        sw(v1, v0, 4);
        lw(v0, s0, rwframe::kRoot);
        v0 = addiu(v0, 8);
        sw(v0, a0, 0);  // 0x96012C (the dirty-frame list head)
        backedge(ctx);
    }
    // 0x004cb66c
    charge(ctx, 8);
    lw(v1, s0, rwframe::kRoot);
    a0 = a1 | 0x3;
    v0 = s0;
    sb(a0, v1, rwobj::kPrivateFlags);
    lbu(v1, s0, rwobj::kPrivateFlags);
    v1 = v1 | 0xC;
    sb(v1, s0, rwobj::kPrivateFlags);
    // 0x004cb6c4
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4CB6E0 [frameForAllChildren] -- calls a callback on each child until it returns 0
// ($a0 = the frame, $a1 = the callback, $a2 = its data) The next sibling is read before each call (a callback may
// destroy its child). Returns the frame.
// 0x004CB6E0 sub_4CB6E0 -- 112 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CB6E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cb6e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    lw(a0, a0, rwframe::kChild);
    s1 = a2;
    if (a0 != 0) {
        for (;;) {
            // 0x004cb70c: callback(child, data)
            charge(ctx, 5);
            lw(s0, a0, rwframe::kNext);
            a1 = s1;
            jalr(ctx, 0x4CB710u, s2.u());
            if (v0 == 0) {
                goto L_004cb720_2;
            }
            // 0x004cb728
            charge(ctx, 2);
            a0 = s0;
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004cb730
    charge(ctx, 1);
    v0 = s3;
    // 0x004cb734 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_004cb720_2:  // the callback returned 0
    charge(ctx, 2);
    v0 = s3;
    // 0x004cb734 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4CB750 [frameOrthoNormalize] -- ortho-normalises the modelling matrix and marks the frame dirty
// sub_4C35D0(frame + 16), then the frame's root joins the dirty-frame list 0x96012C unless it is in it (root private
// flags bits 0..1); root |= 3, the frame |= 0xC. Returns the frame.
// 0x004CB750 sub_4CB750 -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4CB750(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cb750
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = addiu(s0, 16);
    jal(ctx, 0x4CB760u, gen::fn_sub_4C35D0_004c35d0);
    lw(v1, s0, rwframe::kRoot);
    lbu(a1, v1, rwobj::kPrivateFlags);
    v0 = a1 & 0x3;
    if (v0 == 0) {
        // 0x004cb79c: link the root at the head of the dirty list
        charge(ctx, 14);
        a0 = 0x960000;
        a0 = addiu(a0, 300);  // &0x96012C (the dirty-frame list head)
        lw(v0, a0, 0);  // 0x96012C (the dirty-frame list head)
        sw(v0, v1, rwframe::kDirtyNext);
        lw(v0, s0, rwframe::kRoot);
        sw(a0, v0, 12);
        lw(v1, s0, rwframe::kRoot);
        lw(v0, a0, 0);  // 0x96012C (the dirty-frame list head)
        v1 = addiu(v1, 8);
        sw(v1, v0, 4);
        lw(v0, s0, rwframe::kRoot);
        v0 = addiu(v0, 8);
        sw(v0, a0, 0);  // 0x96012C (the dirty-frame list head)
        backedge(ctx);
    }
    // 0x004cb77c: root |= 3, frame |= 0xC
    charge(ctx, 8);
    lw(v1, s0, rwframe::kRoot);
    a0 = a1 | 0x3;
    v0 = s0;
    sb(a0, v1, rwobj::kPrivateFlags);
    lbu(v1, s0, rwobj::kPrivateFlags);
    v1 = v1 | 0xC;
    sb(v1, s0, rwobj::kPrivateFlags);
    // 0x004cb7d4
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4CB890 [frameRotate] -- rotates the modelling matrix (axis, angle, combine) and marks the frame dirty
// ($a1 = the axis, $f12 = the angle in degrees, $a2 = the combine op, passed on) sub_4C31B0(frame + 16, ...),
// then the frame's root joins the dirty-frame list 0x96012C unless it is in it (root private flags bits 0..1); root |=
// 3, the frame |= 0xC. Returns the frame.
// 0x004CB890 sub_4CB890 -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4CB890(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cb890
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = addiu(s0, 16);
    jal(ctx, 0x4CB8A0u, gen::fn_sub_4C31B0_004c31b0);
    lw(v1, s0, rwframe::kRoot);
    lbu(a1, v1, rwobj::kPrivateFlags);
    v0 = a1 & 0x3;
    if (v0 == 0) {
        // 0x004cb8dc
        charge(ctx, 14);
        a0 = 0x960000;
        a0 = addiu(a0, 300);  // &0x96012C (the dirty-frame list head)
        lw(v0, a0, 0);  // 0x96012C (the dirty-frame list head)
        sw(v0, v1, rwframe::kDirtyNext);
        lw(v0, s0, rwframe::kRoot);
        sw(a0, v0, 12);
        lw(v1, s0, rwframe::kRoot);
        lw(v0, a0, 0);  // 0x96012C (the dirty-frame list head)
        v1 = addiu(v1, 8);
        sw(v1, v0, 4);
        lw(v0, s0, rwframe::kRoot);
        v0 = addiu(v0, 8);
        sw(v0, a0, 0);  // 0x96012C (the dirty-frame list head)
        backedge(ctx);
    }
    // 0x004cb8bc
    charge(ctx, 8);
    lw(v1, s0, rwframe::kRoot);
    a0 = a1 | 0x3;
    v0 = s0;
    sb(a0, v1, rwobj::kPrivateFlags);
    lbu(v1, s0, rwobj::kPrivateFlags);
    v1 = v1 | 0xC;
    sb(v1, s0, rwobj::kPrivateFlags);
    // 0x004cb914
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4CB930 [frameSetIdentity] -- sets the modelling matrix to identity and marks the frame dirty
// The modelling matrix = identity, its flags |= 0x20003; then the frame's root joins the dirty-frame list 0x96012C
// unless it is in it (root private flags bits 0..1); root |= 3, the frame |= 0xC. Returns the frame.
// 0x004CB930 sub_4CB930 -- 188 bytes; leaf frame (no stack)
void sub_4CB930(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x004cb930
    enter(ctx, 23);  // entry check point + this block's cycles
    v1 = 0x3F800000;
    v0 = 0x20000;
    sw(v1, a0, 56);
    v0 = v0 | 0x3;
    sw(v1, a0, 36);
    sw(v1, a0, rwframe::kModelling);
    sw(zero, a0, 32);
    sw(zero, a0, 24);
    sw(zero, a0, 20);
    sw(zero, a0, 52);
    sw(zero, a0, 48);
    sw(zero, a0, 40);
    sw(zero, a0, 72);
    sw(zero, a0, 68);
    sw(zero, a0, 64);
    lw(v1, a0, rwframe::kModellingFlags);
    v0 = v1 | v0;
    sw(v0, a0, rwframe::kModellingFlags);
    lw(v1, a0, rwframe::kRoot);
    lbu(a2, v1, rwobj::kPrivateFlags);
    v0 = a2 & 0x3;
    if (v0 == 0) {
        // 0x004cb9ac
        charge(ctx, 14);
        a1 = 0x960000;
        a1 = addiu(a1, 300);  // &0x96012C (the dirty-frame list head)
        lw(v0, a1, 0);  // 0x96012C (the dirty-frame list head)
        sw(v0, v1, rwframe::kDirtyNext);
        lw(v0, a0, rwframe::kRoot);
        sw(a1, v0, 12);
        lw(v1, a0, rwframe::kRoot);
        lw(v0, a1, 0);  // 0x96012C (the dirty-frame list head)
        v1 = addiu(v1, 8);
        sw(v1, v0, 4);
        lw(v0, a0, rwframe::kRoot);
        v0 = addiu(v0, 8);
        sw(v0, a1, 0);  // 0x96012C (the dirty-frame list head)
        backedge(ctx);
    }
    // 0x004cb98c
    charge(ctx, 8);
    lw(v1, a0, rwframe::kRoot);
    a1 = a2 | 0x3;
    v0 = a0;
    sb(a1, v1, rwobj::kPrivateFlags);
    lbu(v1, a0, rwobj::kPrivateFlags);
    v1 = v1 | 0xC;
    sb(v1, a0, rwobj::kPrivateFlags);
    // 0x004cb9e4
    charge(ctx, 2);
}

// sub_4CB9F0 [frameRegisterPlugin] -- registers a frame plugin (sub_4C61B0 on the frame registry)
// Tail call: sub_4C61B0(0x77E670, size, id, constructor, destructor, copy).
// 0x004CB9F0 sub_4CB9F0 -- 44 bytes; leaf frame (no stack)
void sub_4CB9F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x004cb9f0
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = a1;
    v1 = a2;
    a1 = a0;
    a2 = v0;
    v0 = a3;
    t1 = t0;
    a0 = 0x780000;
    a3 = v1;
    t0 = v0;
    a0 = addiu(a0, -6544);  // &0x77E670 (the RwFrame plugin registry)
    gen::fn_sub_4C61B0_004c61b0(ctx);  // tail call
}

// sub_4CEFB0 [frameSyncChildren] -- the hierarchy sync below a root: LTMs and object syncs (recursive)
// ($a0 = the first child, $a1 = the parent's 'LTM changed' bit) For each sibling: with bit 2 (its own or the
// parent's) its LTM = modelling x parent's LTM (sub_4C2F30); each object on the frame gets its sync callback
// (object +16, called with the object); bits 2..3 cleared; then its children with the combined bit.
// 0x004CEFB0 sub_4CEFB0 -- 236 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CEFB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cefb0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (s5 != 0) {
        for (;;) {
            // 0x004cefdc: the frame: own dirty bits | the parent's
            charge(ctx, 5);
            lbu(v0, s5, rwobj::kPrivateFlags);
            s3 = s4 | v0;
            v0 = s3 & 0x4;
            s1 = addiu(s5, 3);
            if (v0 != 0) {
                // 0x004cf058: LTM = modelling x parent LTM
                charge(ctx, 7);
                lw(v0, s5, rwobj::kParent);
                a0 = addiu(s5, 80);
                a1 = addiu(s5, 16);
                a2 = addiu(v0, 80);
                jal(ctx, 0x4CF064u, gen::fn_sub_4C2F30_004c2f30);
                backedge(ctx);
            }
            // 0x004ceff0
            charge(ctx, 4);
            lw(s2, s5, rwframe::kObjects);
            s0 = addiu(s5, 144);
            if (s2 != s0) {
                // 0x004cf000
                charge(ctx, 2);
                if (s2 != s0) {
                    for (;;) {
                        // 0x004cf008: the next object: its sync callback
                        charge(ctx, 7);
                        lw(v0, s2, 8);
                        a0 = addiu(s2, -8);
                        jalr(ctx, 0x4CF00Cu, v0.u());
                        lw(s2, s2, 0);
                        if (s2 == s0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004cf024
                    charge(ctx, 1);
                }
            }
            // 0x004cf028: clear bits 2..3; the children
            charge(ctx, 10);
            lbu(v1, s1, 0);
            v0 = si(-13);
            v0 = v1 & v0;
            sb(v0, s5, rwobj::kPrivateFlags);
            lw(a0, s5, rwframe::kChild);
            a1 = s3;
            jal(ctx, 0x4CF03Cu, gen::fn_sub_4CEFB0_004cefb0);
            lw(s5, s5, rwframe::kNext);
            if (s5 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004cf050
    charge(ctx, 2);
    // 0x004cf078
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// sub_4CF0A0 [frameSyncObjectsOnly] -- the object-only sync below a root (no LTM work; recursive)
// For each sibling: every object's sync callback, bit 3 cleared, the same for each child, the grandchildren
// recursively.
// 0x004CF0A0 sub_4CF0A0 -- 260 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CF0A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cf0a0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s1 = a0;
    sq(s0, sp, 0x0);
    if (s1 != 0) {
        for (;;) {
            // 0x004cf0c0
            charge(ctx, 4);
            lw(s2, s1, rwframe::kObjects);
            s0 = addiu(s1, 144);
            if (s2 != s0) {
                // 0x004cf0d0
                charge(ctx, 2);
                if (s2 != s0) {
                    for (;;) {
                        // 0x004cf0d8
                        charge(ctx, 7);
                        lw(v0, s2, 8);
                        a0 = addiu(s2, -8);
                        jalr(ctx, 0x4CF0DCu, v0.u());
                        lw(s2, s2, 0);
                        if (s2 == s0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004cf0f4
                    charge(ctx, 1);
                }
            }
            // 0x004cf0f8
            charge(ctx, 7);
            lbu(a0, s1, rwobj::kPrivateFlags);
            v1 = si(-9);
            v1 = a0 & v1;
            sb(v1, s1, rwobj::kPrivateFlags);
            lw(s0, s1, rwframe::kChild);
            if (s0 != 0) {
                // 0x004cf114
                charge(ctx, 1);
                for (;;) {
                    // 0x004cf118
                    charge(ctx, 4);
                    lw(s3, s0, 144);
                    s2 = addiu(s0, 144);
                    if (s3 != s2) {
                        // 0x004cf128
                        charge(ctx, 2);
                        if (s3 != s2) {
                            for (;;) {
                                // 0x004cf130
                                charge(ctx, 7);
                                lw(v0, s3, 8);
                                a0 = addiu(s3, -8);
                                jalr(ctx, 0x4CF134u, v0.u());
                                lw(s3, s3, 0);
                                if (s3 == s2) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004cf14c
                            charge(ctx, 1);
                        }
                    }
                    // 0x004cf150
                    charge(ctx, 9);
                    lbu(v1, s0, 3);
                    v0 = si(-9);
                    v0 = v1 & v0;
                    sb(v0, s0, 3);
                    link(ctx, 0x4CF160u);  // $ra first: the delay slot below depends on it
                    lw(a0, s0, 152);
                    call(ctx, gen::fn_sub_4CF0A0_004cf0a0);
                    lw(s0, s0, 156);
                    if (s0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004cf174
                charge(ctx, 1);
            }
            // 0x004cf178
            charge(ctx, 3);
            lw(s1, s1, rwframe::kNext);
            if (s1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004cf184
        charge(ctx, 1);
    }
    // 0x004cf188 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4CF1B0 [frameSyncHierarchy] -- syncs one dirty hierarchy from its root
// With root bit 0 (LTMs to update): a root with bit 2 copies its modelling matrix into its LTM; the root's
// objects are synced, then its children through sub_4CEFB0 with the root's bit 2. Without bit 0 only the
// objects are synced (the root, then each child through sub_4CF0A0, bit 3 cleared). The root keeps its high
// four private-flag bits.
// 0x004CF1B0 sub_4CF1B0 -- 396 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CF1B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cf1b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lbu(s0, a0, 3);
    v1 = s0 & 0x1;
    s2 = a0;
    if (v1 != 0) {
        // 0x004cf1dc: bit 0: the LTMs
        charge(ctx, 3);
        s1 = s0 & 0x4;
        if (s1 != 0) {
            // 0x004cf23c: bit 2: LTM = modelling (8 x 8 bytes)
            charge(ctx, 3);
            a2 = addiu(s2, 16);
            a1 = addiu(s2, 80);
            a0 = 8;
            for (;;) {
                // 0x004cf248
                charge(ctx, 8);
                lw(v1, a2, 0);
                a0 = addiu(a0, -1);
                lw(v0, a2, 4);
                sw(v1, a1, 0);
                a2 = addiu(a2, 8);
                sw(v0, a1, 4);
                a1 = addiu(a1, 8);
                if (i64(a0) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004cf268
            charge(ctx, 2);
            lw(s4, s2, rwframe::kObjects);
            backedge(ctx);
        } else {
            // 0x004cf1e8
            charge(ctx, 1);
            lw(s4, s2, rwframe::kObjects);
        }
        // 0x004cf1ec
        charge(ctx, 3);
        s3 = addiu(s2, 144);
        if (s4 != s3) {
            // 0x004cf1f8
            charge(ctx, 2);
            if (s4 != s3) {
                for (;;) {
                    // 0x004cf200: the root's objects
                    charge(ctx, 7);
                    lw(v0, s4, 8);
                    a0 = addiu(s4, -8);
                    jalr(ctx, 0x4CF204u, v0.u());
                    lw(s4, s4, 0);
                    if (s4 == s3) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004cf21c
                charge(ctx, 1);
            }
        }
        // 0x004cf220: the children: sub_4CEFB0
        charge(ctx, 3);
        lw(a0, s2, rwframe::kChild);
        a1 = s1;
        jal(ctx, 0x4CF224u, gen::fn_sub_4CEFB0_004cefb0);
        goto L_004cf22c;
    }
    // 0x004cf270: no bit 0: the objects only
    charge(ctx, 4);
    lw(s3, s2, rwframe::kObjects);
    s1 = addiu(s2, 144);
    if (s3 != s1) {
        // 0x004cf280
        charge(ctx, 2);
        if (s3 != s1) {
            for (;;) {
                // 0x004cf288
                charge(ctx, 7);
                lw(v0, s3, 8);
                a0 = addiu(s3, -8);
                jalr(ctx, 0x4CF28Cu, v0.u());
                lw(s3, s3, 0);
                if (s3 == s1) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004cf2a4
            charge(ctx, 1);
        }
    }
    // 0x004cf2a8
    charge(ctx, 3);
    lw(s1, s2, rwframe::kChild);
    if (s1 == 0) {
        backedge(ctx);
    L_004cf22c:
        charge(ctx, 1);
        v1 = si(-16);
    } else {
        for (;;) {
            // 0x004cf2b4: a child: its objects, bit 3 off, its children
            charge(ctx, 4);
            lw(s4, s1, rwframe::kObjects);
            s3 = addiu(s1, 144);
            if (s4 != s3) {
                // 0x004cf2c4
                charge(ctx, 2);
                if (s4 != s3) {
                    // 0x004cf2cc
                    charge(ctx, 1);
                    for (;;) {
                        // 0x004cf2d0
                        charge(ctx, 7);
                        lw(v0, s4, 8);
                        a0 = addiu(s4, -8);
                        jalr(ctx, 0x4CF2D4u, v0.u());
                        lw(s4, s4, 0);
                        if (s4 == s3) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004cf2ec
                    charge(ctx, 1);
                }
            }
            // 0x004cf2f0
            charge(ctx, 9);
            lbu(v1, s1, rwobj::kPrivateFlags);
            v0 = si(-9);
            v0 = v1 & v0;
            sb(v0, s1, rwobj::kPrivateFlags);
            link(ctx, 0x4CF300u);  // $ra first: the delay slot below depends on it
            lw(a0, s1, rwframe::kChild);
            call(ctx, gen::fn_sub_4CF0A0_004cf0a0);
            lw(s1, s1, rwframe::kNext);
            if (s1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004cf314
        charge(ctx, 2);
        v1 = si(-16);
        backedge(ctx);
    }
    // 0x004cf230: the root keeps its high four bits
    charge(ctx, 3);
    v1 = s0 & v1;
    sb(v1, s2, rwobj::kPrivateFlags);
    // 0x004cf31c
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4CF340 [frameSyncDirty] -- syncs every hierarchy in the dirty-frame list and empties it
// (Camera begin-update calls it once a frame.) For each entry of 0x96012C: sub_4CF1B0(entry - 8); then the list
// is empty again. Returns 1.
// 0x004CF340 sub_4CF340 -- 100 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CF340(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cf340
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0x960000;
    s0 = addiu(s0, 300);  // &0x96012C (the dirty-frame list head)
    lw(s1, s0, 0);  // 0x96012C (the dirty-frame list head)
    if (s1 != s0) {
        for (;;) {
            // 0x004cf364: the next dirty root
            charge(ctx, 7);
            a0 = addiu(s1, -8);
            jal(ctx, 0x4CF364u, gen::fn_sub_4CF1B0_004cf1b0);
            lw(s1, s1, 0);
            if (s1 == s0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004cf380 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v1 = 0x960000;
    sw(s0, s0, 0);
    v0 = 1;
    sw(s0, v1, 304);  // 0x960130 (the dirty-frame list: prev)
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4C7CF0 [frameSetStreamUpdate] -- stores the frame-list reader's 'mark roots dirty' switch (gp 0x7CDD60)
// sub_4C7D80 adds children with sub_4CB420 (dirty) instead of sub_4CB350 while it is set, and marks the roots.
// 0x004C7CF0 sub_4C7CF0 -- 8 bytes; leaf frame (no stack)
void sub_4C7CF0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, gp{ctx, 28};
    // 0x004c7cf0
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a0, gp, -20368);  // 0x7CDD60
}

// sub_4C7D00 [frameRegisterPluginStream] -- sets a frame plugin's stream callbacks (read, write, size)
// ($a0 = the plugin id, $a1..$a3 = read / write / get-size) The entry with that id in the frame registry
// (0x4C5960: the registries' shared chunk) gets the three callbacks; returns its offset, or -1 when the id is
// not registered.
// 0x004C7D00 sub_4C7D00 -- 116 bytes, 2 chunks; leaf frame (no stack)
void sub_4C7D00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x004c7d00
    enter(ctx, 9);  // entry check point + this block's cycles
    v1 = a1;
    v0 = a2;
    a1 = a0;
    t0 = a3;
    a0 = 0x780000;
    a2 = v1;
    a0 = addiu(a0, -6544);  // &0x77E670 (the RwFrame plugin registry)
    a3 = v0;
    backedge(ctx);
    // 0x004c5960
    charge(ctx, 3);
    lw(v1, a0, plugreg::kFirst);
    if (v1 != 0) {
        for (;;) {
            // 0x004c596c
            charge(ctx, 3);
            lw(v0, v1, plugentry::kPluginId);
            if (v0 == a1) {
                break;
            }
            // 0x004c5978
            charge(ctx, 3);
            lw(v1, v1, plugentry::kNext);
            if (v1 == 0) {
                goto L_004c5984_4;
            }
            backedge(ctx);
        }
    }
L_004c5988:
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x004c59a4
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x004c5990
        charge(ctx, 5);
        sw(a2, v1, plugentry::kReadCb);
        sw(a3, v1, plugentry::kWriteCb);
        sw(t0, v1, plugentry::kGetSizeCb);
        lw(v0, v1, plugentry::kOffset);
    }
    // 0x004c59a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004c5984_4:  // not found
    charge(ctx, 1);
    goto L_004c5988;
}

// sub_4C7D30 [frameListDeinit] -- frees a frame list's array
// ($a0 = a frame list {+0 the frames, +4 the count}) With frames the array is freed (RwFree slot); $v0 = $a0.
// 0x004C7D30 sub_4C7D30 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C7D30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004c7d30
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 4);
    s0 = a0;
    if (v0 != 0) {
        // 0x004c7d50
        charge(ctx, 6);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x4C7D58u);  // $ra = the return address
        lw(a0, s0, 0);
        call_ptr(ctx, jt);
        backedge(ctx);
    }
    // 0x004c7d48
    charge(ctx, 2);
    v0 = s0;
    // 0x004c7d68
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4C7D80 [frameListStreamRead] -- reads a frame list chunk: the frames, their hierarchy, their plugins
// ($a0 = the stream, $a1 = the frame list) The struct chunk (sub_4C1600 type 1; version 0x35000..0x37002, else
// an error 0x80000004), the count (4 bytes), an array of count pointers (RwMalloc, hint 0x3000E; none:
// error 0x80000013). Each frame: 56 bytes (right, up, at, pos and the parent index), a new frame
// (sub_4CAF10) with that modelling matrix; its flags: identity cleared when the matrix is orthonormal within
// 0.01 (sub_4C2B20 / sub_4C2AC0 / sub_4C2A70), else orthogonal / normal / identity all cleared; a parent
// index >= 0 adds it to that frame (sub_4CB420 or sub_4CB350 by the gp switch 0x7CDD60). Then each frame's
// plugin chunks (sub_4C5A50 on the frame registry); a root is marked dirty when the switch is 1. A failure
// destroys what was built and frees the array. Returns the list or 0.
// 0x004C7D80 sub_4C7D80 -- 1048 bytes; frame 0x100: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C7D80(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004c7d80
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    sd(ra, sp, 0x90);
    a2 = addiu(sp, 0xF8);
    sq(fp, sp, 0x80);
    a3 = addiu(sp, 0xF4);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    a1 = 1;
    sq(s1, sp, 0x10);
    link(ctx, 0x4C7DBCu);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1600_004c1600);
    if (v0 == 0) {
        // 0x004c7e1c
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004c7dcc
        charge(ctx, 6);
        lw(v1, sp, 0xF4);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x004c7de4
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_004c80a0;
            }
            // 0x004c7df8
            charge(ctx, 7);
            a0 = s5;
            a1 = addiu(sp, 0xFC);
            a2 = 4;
            jal(ctx, 0x4C7E00u, gen::fn_sub_4C5250_004c5250);
            v1 = 4;
            if (v0 == v1) {
                // 0x004c7e24
                charge(ctx, 13);
                lw(v1, sp, 0xFC);
                v0 = 0x30000;
                a1 = v0 | 0xE;
                v0 = 0x960000;
                sw(v1, s4, 4);
                lw(v1, sp, 0xFC);
                lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                a0 = sll(v1, 2);
                jalr(ctx, 0x4C7E40u, v0.u());
                sw(v0, s4, 0);
                lw(v0, s4, 0);
                if (v0 == 0) {
                    // 0x004c7e7c
                    charge(ctx, 12);
                    lw(v1, sp, 0xFC);
                    v0 = 1;
                    sw(v0, sp, 0xE8);
                    v0 = lui(0x8000);
                    a0 = v0 | 0x13;
                    a1 = sll(v1, 2);
                    jal(ctx, 0x4C7E90u, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0xEC);
                    a0 = addiu(sp, 0xE8);
                    jal(ctx, 0x4C7E9Cu, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                } else {
                    // 0x004c7e58
                    charge(ctx, 4);
                    lw(v1, sp, 0xFC);
                    v0 = slt(0, v1);
                    s3 = 0;
                    if (v0 != 0) {
                        // 0x004c7eac
                        charge(ctx, 4);
                        s0 = 0;
                        s6 = addiu(sp, 0xAC);
                        s7 = addiu(sp, 0xB8);
                        fp = addiu(sp, 0xC4);
                        for (;;) {
                            // 0x004c7ebc
                            charge(ctx, 7);
                            a0 = s5;
                            a1 = addiu(sp, 0xA0);
                            a2 = 56;
                            jal(ctx, 0x4C7EC4u, gen::fn_sub_4C5250_004c5250);
                            v1 = 56;
                            if (v0 != v1) {
                                break;
                            }
                            // 0x004c7ef0
                            charge(ctx, 5);
                            jal(ctx, 0x4C7EF0u, gen::fn_sub_4CAF10_004caf10);
                            s2 = v0;
                            if (s2 == 0) {
                                goto L_004c8024;
                            }
                            // 0x004c7f04
                            charge(ctx, 34);
                            lwc1(f2, sp, 0xA0);
                            s1 = addiu(s2, 16);
                            lwc1(f1, sp, 0xA4);
                            a0 = s1;
                            lwc1(f0, sp, 0xA8);
                            swc1(f2, s2, 16);
                            swc1(f1, s2, 20);
                            swc1(f0, s2, 24);
                            lwc1(f2, s6, 0);
                            lwc1(f1, s6, 4);
                            lwc1(f0, s6, 8);
                            swc1(f2, s2, 32);
                            swc1(f1, s2, 36);
                            swc1(f0, s2, 40);
                            lwc1(f2, s7, 0);
                            lwc1(f1, s7, 4);
                            lwc1(f0, s7, 8);
                            swc1(f2, s2, 48);
                            swc1(f1, s2, 52);
                            swc1(f0, s2, 56);
                            lwc1(f2, fp, 0x0);
                            lwc1(f1, fp, 0x4);
                            lwc1(f0, fp, 0x8);
                            swc1(f2, s2, 64);
                            swc1(f1, s2, 68);
                            link(ctx, 0x4C7F68u);  // $ra first: the delay slot below depends on it
                            swc1(f0, s2, 72);
                            call(ctx, gen::fn_sub_4C2B20_004c2b20);
                            v0 = 0x3C230000;
                            v0 = v0 | 0xD70A;
                            mtc1(v0, f1);
                            c_lt_s(f1, f0);
                            if (cond(ctx)) {
                                // 0x004c7f8c
                                charge(ctx, 1);
                                goto L_004c7f90;
                            }
                            // 0x004c803c
                            charge(ctx, 9);
                            a0 = s1;
                            jal(ctx, 0x4C803Cu, gen::fn_sub_4C2AC0_004c2ac0);
                            v0 = 0x3C230000;
                            v0 = v0 | 0xD70A;
                            mtc1(v0, f1);
                            c_lt_s(f1, f0);
                            if (cond(ctx)) {
                                backedge(ctx);
                            L_004c7f90:
                                charge(ctx, 6);
                                lw(v1, s1, 12);
                                v0 = lui(0xFFFD);
                                v0 = v0 | 0xFFFC;
                                v0 = v1 & v0;
                                sw(v0, s1, 12);
                            } else {
                                // 0x004c8060
                                charge(ctx, 9);
                                a0 = s1;
                                jal(ctx, 0x4C8060u, gen::fn_sub_4C2A70_004c2a70);
                                v0 = 0x3F7D0000;
                                v0 = v0 | 0x70A4;
                                mtc1(v0, f1);
                                c_le_s(f1, f0);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004c7f90;
                                }
                                // 0x004c8084
                                charge(ctx, 6);
                                lw(v1, s1, 12);
                                v0 = lui(0xFFFD);
                                v0 = v0 | 0xFFFF;
                                v0 = v1 & v0;
                                sw(v0, s1, 12);
                                backedge(ctx);
                            }
                            // 0x004c7fa8
                            charge(ctx, 7);
                            lw(v0, s4, 0);
                            v0 = addu(v0, s0);
                            sw(s2, v0, 0);
                            v0 = addiu(sp, 0xD0);
                            lw(v1, v0, 0);
                            if (i64(v1) >= 0) {
                                // 0x004c7fc4
                                charge(ctx, 3);
                                lw(v0, gp, -20368);  // 0x7CDD60
                                if (v0 == 0) {
                                    // 0x004c7ff0
                                    charge(ctx, 6);
                                    lw(v0, s4, 0);
                                    v1 = sll(v1, 2);
                                    v0 = addu(v0, v1);
                                    lw(a0, v0, 0);
                                    a1 = s2;
                                    jal(ctx, 0x4C8000u, gen::fn_sub_4CB350_004cb350);
                                } else {
                                    // 0x004c7fd0
                                    charge(ctx, 8);
                                    lw(v0, s4, 0);
                                    v1 = sll(v1, 2);
                                    v0 = addu(v0, v1);
                                    lw(a0, v0, 0);
                                    a1 = s2;
                                    jal(ctx, 0x4C7FE0u, gen::fn_sub_4CB420_004cb420);
                                }
                            }
                            // 0x004c8008
                            charge(ctx, 5);
                            lw(v1, sp, 0xFC);
                            s3 = addiu(s3, 1);
                            v0 = slt(s3, v1);
                            s0 = addiu(s0, 4);
                            if (v0 == 0) {
                                goto L_004c801c_24;
                            }
                            backedge(ctx);
                        }
                        // 0x004c7ed8
                        charge(ctx, 6);
                        v0 = 0x960000;
                        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                        jt = v0.u();  // the target, read before the delay slot
                        link(ctx, 0x4C7EE0u);  // $ra = the return address
                        lw(a0, s4, 0);
                        call_ptr(ctx, jt);
                        v0 = 0;
                    } else {
                        // 0x004c7e68
                        charge(ctx, 1);
                        v0 = slt(0, v1);
                    L_004c7e6c:
                        charge(ctx, 2);
                        s1 = 0;
                        if (v0 != 0) {
                            // 0x004c80c8
                            charge(ctx, 1);
                            s2 = 0;
                            for (;;) {
                                // 0x004c80cc
                                charge(ctx, 10);
                                lw(v0, s4, 0);
                                a0 = 0x780000;
                                a0 = addiu(a0, -6544);  // &0x77E670 (the RwFrame plugin registry)
                                a1 = s5;
                                v0 = addu(v0, s2);
                                lw(s0, v0, 0);
                                a2 = s0;
                                jal(ctx, 0x4C80E4u, gen::fn_sub_4C5A50_004c5a50);
                                if (v0 == 0) {
                                    break;
                                }
                                // 0x004c8118
                                charge(ctx, 4);
                                a0 = s0;
                                jal(ctx, 0x4C8118u, gen::fn_sub_4CB340_004cb340);
                                if (s0 == v0) {
                                    // 0x004c8144
                                    charge(ctx, 4);
                                    lw(v1, gp, -20368);  // 0x7CDD60
                                    v0 = 1;
                                    if (v1 != v0) {
                                        backedge(ctx);
                                    } else {
                                        // 0x004c8154
                                        charge(ctx, 4);
                                        a0 = s0;
                                        jal(ctx, 0x4C8154u, gen::fn_sub_4CB270_004cb270);
                                        backedge(ctx);
                                    }
                                }
                                // 0x004c8128
                                charge(ctx, 5);
                                lw(v0, sp, 0xFC);
                                s1 = addiu(s1, 1);
                                v0 = slt(s1, v0);
                                s2 = addiu(s2, 4);
                                if (v0 == 0) {
                                    goto L_004c813c_35;
                                }
                                backedge(ctx);
                            }
                            // 0x004c80f4
                            charge(ctx, 9);
                            lw(v0, s4, 0);
                            link(ctx, 0x4C80F8u);  // $ra first: the delay slot below depends on it
                            lw(a0, v0, 0);
                            call(ctx, gen::fn_sub_4CB1B0_004cb1b0);
                            v0 = 0x960000;
                            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                            jt = v0.u();  // the target, read before the delay slot
                            link(ctx, 0x4C8108u);  // $ra = the return address
                            lw(a0, s4, 0);
                            call_ptr(ctx, jt);
                            v0 = 0;
                            // 0x004c8168 (the shared epilogue, written out on this path)
                            charge(ctx, 12);
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
                            sp = addiu(sp, 0x100);
                            return;
                        }
                    L_004c7e74:
                        charge(ctx, 2);
                        v0 = s4;
                    }
                }
            } else {
                // 0x004c7e14
                charge(ctx, 2);
                v0 = 0;
            }
            // 0x004c8168 (the shared epilogue, written out on this path)
            charge(ctx, 12);
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
            sp = addiu(sp, 0x100);
            return;
        }
    L_004c80a0:
        charge(ctx, 10);
        v0 = 1;
        sw(v0, sp, 0xE0);
        v0 = lui(0x8000);
        a0 = v0 | 0x4;
        jal(ctx, 0x4C80ACu, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0xE4);
        a0 = addiu(sp, 0xE0);
        jal(ctx, 0x4C80B8u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x004c8168 (the shared epilogue, written out on this path)
    charge(ctx, 12);
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
    sp = addiu(sp, 0x100);
    return;
L_004c801c_24:
    charge(ctx, 2);
    v0 = slt(0, v1);
    backedge(ctx);
    goto L_004c7e6c;
L_004c8024:
    charge(ctx, 6);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4C802Cu);  // $ra = the return address
    lw(a0, s4, 0);
    call_ptr(ctx, jt);
    v0 = 0;
    // 0x004c8168 (the shared epilogue, written out on this path)
    charge(ctx, 12);
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
    sp = addiu(sp, 0x100);
    return;
L_004c813c_35:
    charge(ctx, 2);
    backedge(ctx);
    goto L_004c7e74;
}

// sub_4C2200 [matrixMultiplyDefault] -- dst = a x b for 3x4 matrices (the module's default multiply)
// ($a0 = dst, $a1 = a, $a2 = b) Each row of a (right, up, at) times b's 3x3 part, and pos = a.pos x b + b.pos;
// the R5900 FPU's accumulator ops (mula / madda / madd) do the dot products, so every product is rounded the
// way the original rounds it. The flags word is not written (the caller sets it).
// 0x004C2200 sub_4C2200 -- 304 bytes; leaf frame (no stack)
void sub_4C2200(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f18{ctx, 18};
    // 0x004c2200
    enter(ctx, 76);  // entry check point + this block's cycles
    lwc1(f4, a1, 4);
    lwc1(f16, a2, 16);
    lwc1(f5, a1, 0);
    lwc1(f17, a2, 0);
    lwc1(f6, a1, 8);
    lwc1(f18, a2, 32);
    lwc1(f13, a2, 20);
    mula_s(f4, f16);
    lwc1(f14, a2, 4);
    madda_s(f5, f17);
    lwc1(f15, a2, 36);
    madd_s(f0, f6, f18);
    mula_s(f4, f13);
    lwc1(f10, a2, 24);
    lwc1(f11, a2, 8);
    lwc1(f12, a2, 40);
    lwc1(f1, a1, 20);
    swc1(f0, a0, 0);
    madda_s(f5, f14);
    madd_s(f0, f6, f15);
    mula_s(f4, f10);
    madda_s(f5, f11);
    swc1(f0, a0, 4);
    madd_s(f0, f6, f12);
    lwc1(f2, a1, 16);
    mula_s(f1, f16);
    lwc1(f3, a1, 24);
    swc1(f0, a0, 8);
    lwc1(f7, a1, 36);
    lwc1(f8, a1, 32);
    madda_s(f2, f17);
    lwc1(f9, a1, 40);
    madd_s(f0, f3, f18);
    mula_s(f1, f13);
    swc1(f0, a0, 16);
    madda_s(f2, f14);
    madd_s(f0, f3, f15);
    mula_s(f1, f10);
    madda_s(f2, f11);
    swc1(f0, a0, 20);
    madd_s(f0, f3, f12);
    mula_s(f7, f16);
    madda_s(f8, f17);
    madd_s(f3, f9, f18);
    swc1(f0, a0, 24);
    mula_s(f7, f13);
    lwc1(f4, a1, 52);
    lwc1(f5, a1, 48);
    swc1(f3, a0, 32);
    madda_s(f8, f14);
    madd_s(f3, f9, f15);
    mula_s(f7, f10);
    lwc1(f6, a1, 56);
    lwc1(f2, a2, 48);
    swc1(f3, a0, 36);
    madda_s(f8, f11);
    madd_s(f3, f9, f12);
    mula_s(f4, f16);
    swc1(f3, a0, 40);
    madda_s(f5, f17);
    madd_s(f3, f6, f18);
    add_s(f2, f2, f3);
    mula_s(f4, f13);
    lwc1(f1, a2, 52);
    swc1(f2, a0, 48);
    madda_s(f5, f14);
    madd_s(f2, f6, f15);
    mula_s(f4, f10);
    lwc1(f0, a2, 56);
    add_s(f2, f1, f2);
    madda_s(f5, f11);
    madd_s(f1, f6, f12);
    add_s(f0, f0, f1);
    swc1(f2, a0, 52);
    swc1(f0, a0, 56);
}

// sub_4C2A30 [matrixSetMultiplyFn] -- sets the matrix module's multiply function (0: the default sub_4C2200)
// Stores the function in the matrix module's data (0x960070 + gp 0x7CE8D8: +0 the free list, +4 0x20000, +8 the
// multiply function, +12 / +16 / +20 the normal / orthogonal / identity tolerances) at +8. Returns 1.
// 0x004C2A30 sub_4C2A30 -- 56 bytes; leaf frame (no stack)
void sub_4C2A30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x004c2a30
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 == 0) {
        // 0x004c2a54
        charge(ctx, 3);
        a0 = 0x4C0000;
        a0 = addiu(a0, 8704);  // &sub_4C2200
        backedge(ctx);
    }
    // 0x004c2a38
    charge(ctx, 7);
    lw(a1, gp, -17432);  // 0x7CE8D8 (the matrix module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = 1;
    v1 = addu(v1, a1);
    sw(a0, v1, matmod::kMultiply);
    // 0x004c2a60
    charge(ctx, 2);
}

// sub_4C2A70 [matrixDeterminant] -- the determinant of the 3x3 part, in $f0
// right . (up x at), the cross product's terms through the accumulator ops (mula / msub, mula / madda / madd).
// 0x004C2A70 sub_4C2A70 -- 76 bytes; leaf frame (no stack)
void sub_4C2A70(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9};
    // 0x004c2a70
    enter(ctx, 19);  // entry check point + this block's cycles
    lwc1(f8, a0, 16);
    lwc1(f3, a0, 36);
    lwc1(f7, a0, 32);
    lwc1(f1, a0, 20);
    lwc1(f9, a0, 40);
    lwc1(f6, a0, 24);
    lwc1(f0, a0, 4);
    mula_s(f8, f3);
    lwc1(f2, a0, 0);
    msub_s(f5, f1, f7);
    mula_s(f1, f9);
    msub_s(f3, f6, f3);
    mula_s(f6, f7);
    msub_s(f1, f8, f9);
    mula_s(f1, f0);
    lwc1(f4, a0, 8);
    madda_s(f3, f2);
    madd_s(f0, f5, f4);
}

// sub_4C2AC0 [matrixOrthogonalError] -- the sum of the squared dot products of the three axes, in $f0
// (right.up)^2 + (up.at)^2 + (at.right)^2: 0 for an orthogonal matrix.
// 0x004C2AC0 sub_4C2AC0 -- 88 bytes; leaf frame (no stack)
void sub_4C2AC0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9};
    // 0x004c2ac0
    enter(ctx, 22);  // entry check point + this block's cycles
    lwc1(f9, a0, 36);
    lwc1(f8, a0, 20);
    lwc1(f7, a0, 32);
    lwc1(f6, a0, 16);
    lwc1(f1, a0, 40);
    lwc1(f5, a0, 24);
    lwc1(f3, a0, 4);
    mula_s(f8, f9);
    lwc1(f2, a0, 0);
    madda_s(f6, f7);
    lwc1(f0, a0, 8);
    madd_s(f4, f5, f1);
    mula_s(f9, f3);
    madda_s(f7, f2);
    madd_s(f1, f1, f0);
    mula_s(f3, f8);
    madda_s(f2, f6);
    madd_s(f0, f0, f5);
    mula_s(f1, f1);
    madda_s(f4, f4);
    madd_s(f0, f0, f0);
}

// sub_4C2B20 [matrixNormalError] -- the sum of the squared (length^2 - 1) of the three axes, in $f0
// (|right|^2 - 1)^2 + (|up|^2 - 1)^2 + (|at|^2 - 1)^2: 0 when every axis has length 1.
// 0x004C2B20 sub_4C2B20 -- 108 bytes; leaf frame (no stack)
void sub_4C2B20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6};
    // 0x004c2b20
    enter(ctx, 27);  // entry check point + this block's cycles
    lwc1(f6, a0, 4);
    v0 = 0x3F800000;
    lwc1(f4, a0, 0);
    lwc1(f3, a0, 8);
    lwc1(f2, a0, 20);
    lwc1(f1, a0, 16);
    lwc1(f0, a0, 24);
    mula_s(f6, f6);
    madda_s(f4, f4);
    madd_s(f3, f3, f3);
    mtc1(v0, f5);
    mula_s(f2, f2);
    madda_s(f1, f1);
    sub_s(f4, f3, f5);
    madd_s(f0, f0, f0);
    sub_s(f3, f0, f5);
    lwc1(f2, a0, 36);
    lwc1(f1, a0, 32);
    lwc1(f0, a0, 40);
    mula_s(f2, f2);
    madda_s(f1, f1);
    madd_s(f0, f0, f0);
    mula_s(f3, f3);
    sub_s(f0, f0, f5);
    madda_s(f4, f4);
    madd_s(f0, f0, f0);
}

// sub_4C2B90 [matrixModuleClose] -- the matrix module's close: destroys its free list
// The free list of the matrix module's data (0x960070 + gp 0x7CE8D8: +0 the free list, +4 0x20000, +8 the multiply
// function, +12 / +16 / +20 the normal / orthogonal / identity tolerances) goes to sub_4C3C30 and its word is cleared;
// the open count (0x7CE8DC) goes
// down; $v0 = $a0.
// 0x004C2B90 sub_4C2B90 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C2B90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c2b90
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s0, sp, 0x0);
    lw(v1, gp, -17432);  // 0x7CE8D8 (the matrix module offset)
    s0 = a0;
    v0 = addu(v0, v1);
    lw(a0, v0, 0);
    if (a0 != 0) {
        // 0x004c2bbc
        charge(ctx, 7);
        jal(ctx, 0x4C2BBCu, gen::fn_sub_4C3C30_004c3c30);
        lw(v1, gp, -17432);  // 0x7CE8D8 (the matrix module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        sw(zero, v0, 0);
    }
    // 0x004c2bd8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(v1, gp, -17428);  // 0x7CE8DC (the matrix module open count)
    v0 = s0;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17428);  // 0x7CE8DC (the matrix module open count)
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4C2C00 [matrixModuleOpen] -- the matrix module's open: the free list, the multiply function, the tolerances
// ($a0 = the engine instance, $a1 = the module's offset, stored at 0x7CE8D8) The matrix free list (64-byte
// entries, the counts of 0x7CDD30 / 0x7CDD34, alignment 16, the static record 0x95FF50, hint 0x4000D); with
// it +4 = 0x20000, +8 = sub_4C2200, and the default tolerances (the 12 bytes at 0x77E5B0, copied through a
// stack temporary to sub_4C2CF0); the open count goes up. Returns $a0, or 0 without a free list.
// 0x004C2C00 sub_4C2C00 -- 184 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C2C00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x004c2c00
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    t0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x40000;
    sq(s0, sp, 0x0);
    a2 = 16;
    sw(a1, gp, -17432);  // 0x7CE8D8 (the matrix module offset)
    s0 = a0;
    lw(a1, gp, -20416);  // 0x7CDD30 (the matrix free list: entries per block)
    a0 = 64;
    lw(a3, gp, -20412);  // 0x7CDD34 (the matrix free list: preallocated blocks)
    t0 = addiu(t0, -176);  // &0x95FF50 (the matrix free list, static)
    t1 = v0 | 0xD;
    jal(ctx, 0x4C2C30u, gen::fn_sub_4C3B60_004c3b60);
    lw(a0, gp, -17432);  // 0x7CE8D8 (the matrix module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    a1 = addu(v1, a0);
    sw(v0, a1, 0);
    lw(v0, a1, 0);
    if (v0 != 0) {
        // 0x004c2c64: the free list exists: flags, multiply function, tolerances
        charge(ctx, 17);
        v1 = 0x20000;
        v0 = 0x4C0000;
        v0 = addiu(v0, 8704);  // &sub_4C2200
        sw(v1, a1, matmod::kFlags);
        sw(v0, a1, matmod::kMultiply);
        a0 = addiu(sp, 0x20);
        v0 = 0x780000;
        ld(v1, v0, -6736);  // 0x77E5B0 (the default matrix tolerances)
        v0 = 0x780000;
        sd(v1, sp, 0x20);
        lwc1(f0, v0, -6728);  // 0x77E5B8
        link(ctx, 0x4C2C90u);  // $ra first: the delay slot below depends on it
        swc1(f0, sp, 0x28);
        call(ctx, gen::fn_sub_4C2CF0_004c2cf0);
        lw(v0, gp, -17428);  // 0x7CE8DC (the matrix module open count)
        v0 = addiu(v0, 1);
        sw(v0, gp, -17428);  // 0x7CE8DC (the matrix module open count)
        backedge(ctx);
    } else {
        // 0x004c2c58: no free list: 0
        charge(ctx, 1);
        s0 = 0;
    }
    // 0x004c2c5c
    charge(ctx, 2);
    v0 = s0;
    // 0x004c2ca8
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4C2CC0 [matrixGetTolerances] -- copies the three matrix tolerances out ($a0 = 3 floats); returns 1
// 0x004C2CC0 sub_4C2CC0 -- 48 bytes; leaf frame (no stack)
void sub_4C2CC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x004c2cc0
    enter(ctx, 12);  // entry check point + this block's cycles
    lw(a1, gp, -17432);  // 0x7CE8D8 (the matrix module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = 1;
    v1 = addu(v1, a1);
    lwc1(f2, v1, 12);
    lwc1(f1, v1, 16);
    lwc1(f0, v1, 20);
    swc1(f2, a0, 0);
    swc1(f1, a0, 4);
    swc1(f0, a0, 8);
}

// sub_4C2CF0 [matrixSetTolerances] -- sets the three matrix tolerances from $a0 (3 floats); returns 1
// 0x004C2CF0 sub_4C2CF0 -- 48 bytes; leaf frame (no stack)
void sub_4C2CF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x004c2cf0
    enter(ctx, 12);  // entry check point + this block's cycles
    lw(a1, gp, -17432);  // 0x7CE8D8 (the matrix module offset)
    v1 = 0x960000;
    lwc1(f2, a0, 0);
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    lwc1(f1, a0, 4);
    v0 = 1;
    lwc1(f0, a0, 8);
    v1 = addu(v1, a1);
    swc1(f2, v1, 12);
    swc1(f1, v1, 16);
    swc1(f0, v1, 20);
}

// sub_4C2D20 [matrixOptimize] -- sets a matrix's normal / orthogonal / identity flags from its values
// ($a0 = the matrix, $a1 = the tolerances or 0 for the module's) Normal when the normal error (as
// sub_4C2B20) is not above tolerance 0, orthogonal when the orthogonal error (as sub_4C2AC0) is not above
// tolerance 1; only then identity when |right - x|^2 + |up - y|^2 + |at - z|^2 + |pos|^2 is not above tolerance
// 2. Each flag is set or cleared in the flags word. Returns the matrix.
// 0x004C2D20 sub_4C2D20 -- 484 bytes; leaf frame (no stack)
void sub_4C2D20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12};
    // 0x004c2d20
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a1 == 0) {
        // 0x004c2ee4: no tolerances given: the module's (+12)
        charge(ctx, 6);
        lw(v1, gp, -17432);  // 0x7CE8D8 (the matrix module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        a1 = addiu(v0, 12);
        backedge(ctx);
    }
    // 0x004c2d28: the normal error against tolerance 0
    charge(ctx, 30);
    lwc1(f0, a0, 4);
    v0 = 0x3F800000;
    lwc1(f3, a0, rwmatrix::kRight);
    lwc1(f2, a0, 8);
    lwc1(f11, a0, 20);
    lwc1(f1, a0, rwmatrix::kUp);
    mtc1(v0, f8);
    mula_s(f0, f0);
    madda_s(f3, f3);
    madd_s(f2, f2, f2);
    lwc1(f0, a0, 24);
    sub_s(f7, f2, f8);
    mula_s(f11, f11);
    madda_s(f1, f1);
    madd_s(f2, f0, f0);
    sub_s(f6, f2, f8);
    lwc1(f3, a0, 36);
    lwc1(f2, a0, rwmatrix::kAt);
    lwc1(f10, a0, 40);
    lwc1(f4, a1, 0);
    mula_s(f3, f3);
    madda_s(f2, f2);
    madd_s(f5, f10, f10);
    mula_s(f6, f6);
    sub_s(f5, f5, f8);
    madda_s(f7, f7);
    madd_s(f5, f5, f5);
    c_lt_s(f4, f5);
    a3 = 1;
    if (cond(ctx)) {
        // 0x004c2da0
        charge(ctx, 1);
        a3 = 0;
    }
    // 0x004c2da4: the orthogonal error against tolerance 1
    charge(ctx, 19);
    lwc1(f8, a0, 4);
    lwc1(f7, a0, rwmatrix::kRight);
    lwc1(f5, a0, 8);
    mula_s(f11, f3);
    madda_s(f1, f2);
    madd_s(f9, f0, f10);
    mula_s(f3, f8);
    madda_s(f2, f7);
    madd_s(f6, f10, f5);
    mula_s(f8, f11);
    madda_s(f7, f1);
    madd_s(f5, f5, f0);
    mula_s(f6, f6);
    madda_s(f9, f9);
    lwc1(f4, a1, 4);
    madd_s(f5, f5, f5);
    c_lt_s(f4, f5);
    a2 = 1;
    if (cond(ctx)) {
        // 0x004c2df0
        charge(ctx, 1);
        a2 = 0;
    }
    // 0x004c2df4
    charge(ctx, 3);
    v0 = sltu(0, a3);
    t0 = 0;
    if (v0 != 0) {
        // 0x004c2e00
        charge(ctx, 1);
        v0 = sltu(0, a2);
    }
    // 0x004c2e04
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x004c2e0c: both: the identity error against tolerance 2
        charge(ctx, 30);
        v0 = 0x3F800000;
        mtc1(v0, f5);
        lwc1(f6, a0, rwmatrix::kRight);
        sub_s(f9, f11, f5);
        sub_s(f8, f10, f5);
        sub_s(f12, f6, f5);
        lwc1(f11, a0, 4);
        lwc1(f10, a0, 8);
        lwc1(f7, a0, 52);
        lwc1(f6, a0, rwmatrix::kPos);
        lwc1(f5, a0, 56);
        lwc1(f4, a1, 8);
        mula_s(f11, f11);
        madda_s(f12, f12);
        madd_s(f10, f10, f10);
        mula_s(f9, f9);
        madda_s(f1, f1);
        madd_s(f0, f0, f0);
        mula_s(f3, f3);
        madda_s(f2, f2);
        madd_s(f2, f8, f8);
        add_s(f0, f10, f0);
        mula_s(f7, f7);
        madda_s(f6, f6);
        add_s(f0, f2, f0);
        madd_s(f1, f5, f5);
        add_s(f0, f1, f0);
        c_lt_s(f4, f0);
        if (!cond(ctx)) {
            // 0x004c2e84
            charge(ctx, 1);
            t0 = 1;
        }
    }
    // 0x004c2e88: the flags: normal (bit 0)
    charge(ctx, 2);
    lw(v1, a0, rwmatrix::kFlags);
    if (a3 == 0) {
        // 0x004c2e98
        charge(ctx, 2);
        v0 = si(-2);
        v1 = v1 & v0;
    } else {
        // 0x004c2e90
        charge(ctx, 2);
        v1 = v1 | 0x1;
    }
    // 0x004c2ea0: orthogonal (bit 1)
    charge(ctx, 2);
    if (a2 == 0) {
        // 0x004c2eb0
        charge(ctx, 2);
        v0 = si(-3);
        v1 = v1 & v0;
    } else {
        // 0x004c2ea8
        charge(ctx, 2);
        v1 = v1 | 0x2;
    }
    // 0x004c2eb8: identity (bit 17)
    charge(ctx, 2);
    if (t0 == 0) {
        // 0x004c2ecc
        charge(ctx, 3);
        v0 = lui(0xFFFD);
        v0 = v0 | 0xFFFF;
        v1 = v1 & v0;
    } else {
        // 0x004c2ec0
        charge(ctx, 3);
        v0 = 0x20000;
        v1 = v1 | v0;
    }
    // 0x004c2ed8
    charge(ctx, 3);
    sw(v1, a0, rwmatrix::kFlags);
    v0 = a0;
    // 0x004c2efc
    charge(ctx, 2);
}

// sub_4C2F10 [matrixUpdate] -- clears a matrix's normal / orthogonal / identity flags (after an edit); returns it
// 0x004C2F10 sub_4C2F10 -- 28 bytes; leaf frame (no stack)
void sub_4C2F10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004c2f10
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(a1, a0, rwmatrix::kFlags);
    v1 = lui(0xFFFD);
    v1 = v1 | 0xFFFC;
    v0 = a0;
    v1 = a1 & v1;
    sw(v1, a0, rwmatrix::kFlags);
}

// sub_4C2FC0 [matrixRotateOneMinusCosineSine] -- rotates a matrix about a unit axis, from (1 - cos) and sin
// ($a0 = the matrix, $a1 = the unit axis, $f12 = 1 - cos, $f13 = sin, $a2 = the combine op) The rotation is
// built on the stack (+0x60: the Rodrigues terms through the accumulator ops; flags 3, pos 0); combine 0
// replaces the matrix, 1 pre-concatenates (rotation x matrix, sub_4C2F30), 2 post-concatenates (matrix x
// rotation); anything else is error 0x80000003 "Invalid combination type" and returns 0. Else returns the
// matrix.
// 0x004C2FC0 sub_4C2FC0 -- 484 bytes; frame 0xB0: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C2FC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f12{ctx, 12}, f13{ctx, 13};
    // 0x004c2fc0
    enter(ctx, 53);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    v0 = 0x3F800000;
    lwc1(f7, a1, 0);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    mtc1(v0, f4);
    mtc1(zero, f3);
    s0 = a0;
    v0 = 3;
    sw(zero, sp, 0x90);
    adda_s(f3, f4);
    sw(v0, sp, 0x6C);
    lwc1(f2, a1, 4);
    v0 = 2;
    msub_s(f0, f7, f7);
    sw(zero, sp, 0x94);
    mul_s(f0, f0, f12);
    sw(zero, sp, 0x98);
    sub_s(f0, f4, f0);
    swc1(f0, sp, 0x60);
    adda_s(f3, f4);
    msub_s(f0, f2, f2);
    mul_s(f0, f0, f12);
    sub_s(f0, f4, f0);
    adda_s(f3, f4);
    lwc1(f1, a1, 8);
    swc1(f0, sp, 0x74);
    mul_s(f3, f7, f13);
    msub_s(f0, f1, f1);
    mul_s(f0, f0, f12);
    sub_s(f0, f4, f0);
    swc1(f0, sp, 0x88);
    mul_s(f0, f2, f1);
    mul_s(f6, f0, f12);
    mul_s(f0, f1, f7);
    mul_s(f5, f0, f12);
    mul_s(f0, f1, f13);
    mul_s(f1, f7, f2);
    mul_s(f4, f1, f12);
    add_s(f1, f4, f0);
    sub_s(f0, f4, f0);
    mul_s(f2, f2, f13);
    swc1(f1, sp, 0x64);
    swc1(f0, sp, 0x70);
    sub_s(f1, f5, f2);
    add_s(f0, f5, f2);
    swc1(f1, sp, 0x68);
    swc1(f0, sp, 0x80);
    add_s(f1, f6, f3);
    sub_s(f0, f6, f3);
    swc1(f1, sp, 0x78);
    swc1(f0, sp, 0x84);
    if (a2 == v0) {
        // 0x004c3128: combine 2: matrix x rotation, copied back
        charge(ctx, 7);
        a0 = addiu(sp, 0x20);
        a1 = s0;
        a2 = addiu(sp, 0x60);
        jal(ctx, 0x4C3130u, gen::fn_sub_4C2F30_004c2f30);
        a2 = addiu(sp, 0x20);
        a0 = 8;
        a1 = s0;
        for (;;) {
            // 0x004c3144
            charge(ctx, 8);
            lw(v1, a2, 0);
            a0 = addiu(a0, -1);
            lw(v0, a2, 4);
            sw(v1, a1, 0);
            a2 = addiu(a2, 8);
            sw(v0, a1, 4);
            a1 = addiu(a1, 8);
            if (i64(a0) <= 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004c3164
        charge(ctx, 2);
    L_004c3190:
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x004c3094
        charge(ctx, 3);
        v0 = 1;
        if (a2 == v0) {
            // 0x004c30e4: combine 1: rotation x matrix, copied back
            charge(ctx, 7);
            a0 = addiu(sp, 0x20);
            a1 = addiu(sp, 0x60);
            a2 = s0;
            jal(ctx, 0x4C30ECu, gen::fn_sub_4C2F30_004c2f30);
            a2 = addiu(sp, 0x20);
            a0 = 8;
            a1 = s0;
            for (;;) {
                // 0x004c3100
                charge(ctx, 8);
                lw(v1, a2, 0);
                a0 = addiu(a0, -1);
                lw(v0, a2, 4);
                sw(v1, a1, 0);
                a2 = addiu(a2, 8);
                sw(v0, a1, 4);
                a1 = addiu(a1, 8);
                if (i64(a0) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004c3120
            charge(ctx, 2);
            goto L_004c3190;
        }
        // 0x004c30a0
        charge(ctx, 2);
        if (a2 != 0) {
            // 0x004c30a8: another op: the error
            charge(ctx, 2);
            sw(v0, sp, 0xA8);
            // 0x004c316c
            charge(ctx, 9);
            a1 = 0x780000;
            v0 = lui(0x8000);
            a1 = addiu(a1, -6720);  // "Invalid combination type"
            a0 = v0 | 0x3;
            jal(ctx, 0x4C3178u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0xAC);
            a0 = addiu(sp, 0xA8);
            jal(ctx, 0x4C3184u, gen::fn_sub_4C1C50_004c1c50);
            s0 = 0;
            goto L_004c3190;
        }
        // 0x004c30b0: combine 0: the rotation replaces the matrix
        charge(ctx, 3);
        a2 = addiu(sp, 0x60);
        a0 = 8;
        a1 = s0;
        for (;;) {
            // 0x004c30bc
            charge(ctx, 8);
            lw(v1, a2, 0);
            a0 = addiu(a0, -1);
            lw(v0, a2, 4);
            sw(v1, a1, 0);
            a2 = addiu(a2, 8);
            sw(v0, a1, 4);
            a1 = addiu(a1, 8);
            if (i64(a0) <= 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004c30dc
        charge(ctx, 2);
        v0 = s0;
    }
    // 0x004c3194 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// sub_4C31B0 [matrixRotate] -- rotates a matrix about an axis by an angle in degrees
// ($a0 = the matrix, $a1 = the axis, $f12 = degrees, $a2 = the combine op) The axis is normalised (1 / length
// when the length is above 0), the angle times pi / 180 (0x3C8EFA35) goes to sinf and cosf, and
// sub_4C2FC0 does the rest with 1 - cos and sin. Returns the matrix.
// 0x004C31B0 sub_4C31B0 -- 240 bytes; frame 0x50: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
void sub_4C31B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20};
    // 0x004c31b0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x3C8E0000;
    lwc1(f0, a1, 4);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    v0 = v0 | 0xFA35;
    sq(s0, sp, 0x10);
    lwc1(f2, a1, 0);
    mtc1(v0, f1);
    s1 = a0;
    swc1(f20, sp, 0x0);
    s0 = a2;
    mul_s(f20, f1, f12);
    mula_s(f0, f0);
    lwc1(f0, a1, 8);
    madda_s(f2, f2);
    mtc1(zero, f1);
    madd_s(f0, f0, f0);
    sqrt_s(f3, f0);
    c_le_s(f3, f1);
    if (!cond(ctx)) {
        // 0x004c3214: 1 / the axis length
        charge(ctx, 7);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        div_s(f3, f0, f3);
    }
    // 0x004c3230: the unit axis on the stack; sin, cos; the rotation
    charge(ctx, 28);
    mul_s(f0, f2, f3);
    swc1(f0, sp, 0x40);
    lwc1(f1, a1, 4);
    lwc1(f0, a1, 8);
    mov_s(f12, f20);
    mul_s(f1, f1, f3);
    mul_s(f0, f0, f3);
    swc1(f1, sp, 0x44);
    link(ctx, 0x4C3250u);  // $ra first: the delay slot below depends on it
    swc1(f0, sp, 0x48);
    call(ctx, gen::fn_sinf_0052e878);
    mov_s(f12, f20);
    mov_s(f20, f0);
    jal(ctx, 0x4C325Cu, gen::fn_cosf_0052e6d8);
    v0 = 0x3F800000;
    a2 = s0;
    mtc1(v0, f1);
    a0 = s1;
    mov_s(f13, f20);
    a1 = addiu(sp, 0x40);
    sub_s(f12, f1, f0);
    jal(ctx, 0x4C327Cu, gen::fn_sub_4C2FC0_004c2fc0);
    v0 = s1;
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lwc1(f20, sp, 0x0);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x50);
}

// sub_4C3880 [matrixDestroy] -- returns a matrix to the matrix free list (slot 0x96018C); returns 1
// 0x004C3880 sub_4C3880 -- 60 bytes; frame 0x10: ra sp+0x0
void sub_4C3880(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004c3880
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x960000;
    sd(ra, sp, 0x0);
    a1 = a0;
    lw(a0, gp, -17432);  // 0x7CE8D8 (the matrix module offset)
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = 0x960000;
    lw(v0, v0, 396);  // 0x96018C (free-list free slot)
    v1 = addu(v1, a0);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4C38A4u);  // $ra = the return address
    lw(a0, v1, 0);
    call_ptr(ctx, jt);
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}

// sub_4C38C0 [matrixCreate] -- a new identity matrix from the matrix free list
// The free list through the slot 0x960188 (hint 0x3000D); a matrix is set to identity with flags 3 | 0x20003.
// Returns the matrix or 0.
// 0x004C38C0 sub_4C38C0 -- 148 bytes; frame 0x10: ra sp+0x0
void sub_4C38C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004c38c0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x960000;
    sd(ra, sp, 0x0);
    v0 = 0x30000;
    lw(a0, gp, -17432);  // 0x7CE8D8 (the matrix module offset)
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    a1 = v0 | 0xD;
    v0 = 0x960000;
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    v1 = addu(v1, a0);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4C38E8u);  // $ra = the return address
    lw(a0, v1, 0);
    call_ptr(ctx, jt);
    if (v0 != 0) {
        // 0x004c38f8
        charge(ctx, 20);
        v1 = 3;
        a0 = 0x3F800000;
        sw(v1, v0, rwmatrix::kFlags);
        sw(a0, v0, 40);
        v1 = 0x20000;
        sw(a0, v0, 20);
        v1 = v1 | 0x3;
        sw(a0, v0, rwmatrix::kRight);
        sw(zero, v0, rwmatrix::kUp);
        sw(zero, v0, 8);
        sw(zero, v0, 4);
        sw(zero, v0, 36);
        sw(zero, v0, rwmatrix::kAt);
        sw(zero, v0, 24);
        sw(zero, v0, 56);
        sw(zero, v0, 52);
        sw(zero, v0, rwmatrix::kPos);
        lw(a0, v0, rwmatrix::kFlags);
        v1 = a0 | v1;
        sw(v1, v0, rwmatrix::kFlags);
    }
    // 0x004c3948 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// sub_4B91B0 [matrixStreamGetSize] -- the size of a matrix chunk's payload: 64
// 0x004B91B0 sub_4B91B0 -- 8 bytes; leaf frame (no stack)
void sub_4B91B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x004b91b0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 64;
}

// sub_4C19F0 [matrixStreamRead] -- reads a matrix from a stream (a struct chunk of 52 bytes)
// ($a0 = the stream, $a1 = the matrix or 0 for a new one) The struct chunk (sub_4C1600 type 1; no chunk:
// error 0x8000001A; version outside 0x35000..0x37002: error 0x80000004), its payload read into a zeroed
// 52-byte stack record (right, up, at, pos, flags; a short read: error 0x8000001A), a new matrix when $a1 is
// 0 (sub_4C38C0); the 12 floats copied, flags = the record's flags & 3, and an orthonormal one (3) goes through
// sub_4C2FB0. Returns the matrix or 0.
// 0x004C19F0 sub_4C19F0 -- 460 bytes; frame 0x90: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C19F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x004c19f0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x20);
    a2 = addiu(sp, 0x8C);
    sq(s1, sp, 0x10);
    a3 = addiu(sp, 0x88);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a1 = 1;
    jal(ctx, 0x4C1A10u, gen::fn_sub_4C1600_004c1600);
    if (v0 != 0) {
        // 0x004c1a20: the chunk's version
        charge(ctx, 6);
        lw(v1, sp, 0x88);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x004c1a38
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_004c1b58;
            }
            // 0x004c1a4c: the payload into the stack record
            charge(ctx, 13);
            a0 = addiu(sp, 0x30);
            a1 = 0;
            a2 = 52;
            jal(ctx, 0x4C1A54u, gen::fn_memset_00521408);
            lw(a2, sp, 0x8C);
            a0 = s1;
            a1 = addiu(sp, 0x30);
            jal(ctx, 0x4C1A64u, gen::fn_sub_4C5250_004c5250);
            lw(v1, sp, 0x8C);
            v0 = v1 ^ v0;
            v0 = sltiu(v0, 1);
            if (v0 != 0) {
                // 0x004c1a80
                charge(ctx, 2);
                if (s0 == 0) {
                    // 0x004c1b20: no matrix given: a new one
                    charge(ctx, 4);
                    jal(ctx, 0x4C1B20u, gen::fn_sub_4C38C0_004c38c0);
                    s0 = v0;
                    backedge(ctx);
                }
                // 0x004c1a88
                charge(ctx, 2);
                if (s0 != 0) {
                    // 0x004c1a90: copy the axes and the position; the flags & 3
                    charge(ctx, 31);
                    lw(v1, sp, 0x60);
                    v0 = 3;
                    sw(zero, s0, rwmatrix::kFlags);
                    a0 = v1 & 0x3;
                    lwc1(f2, sp, 0x30);
                    v1 = a0 & 0x3;
                    lwc1(f1, sp, 0x34);
                    lwc1(f0, sp, 0x38);
                    swc1(f2, s0, rwmatrix::kRight);
                    swc1(f1, s0, 4);
                    swc1(f0, s0, 8);
                    lwc1(f2, sp, 0x3C);
                    lwc1(f1, sp, 0x40);
                    lwc1(f0, sp, 0x44);
                    swc1(f2, s0, rwmatrix::kUp);
                    swc1(f1, s0, 20);
                    swc1(f0, s0, 24);
                    lwc1(f2, sp, 0x48);
                    lwc1(f1, sp, 0x4C);
                    lwc1(f0, sp, 0x50);
                    swc1(f2, s0, rwmatrix::kAt);
                    swc1(f1, s0, 36);
                    swc1(f0, s0, 40);
                    lwc1(f2, sp, 0x54);
                    lwc1(f1, sp, 0x58);
                    lwc1(f0, sp, 0x5C);
                    swc1(f2, s0, rwmatrix::kPos);
                    swc1(f1, s0, 52);
                    swc1(f0, s0, 56);
                    sw(a0, s0, rwmatrix::kFlags);
                    if (v1 == v0) {
                        // 0x004c1b0c: orthonormal: sub_4C2FB0
                        charge(ctx, 3);
                        a0 = s0;
                        a1 = s0;
                        jal(ctx, 0x4C1B10u, gen::fn_sub_4C2FB0_004c2fb0);
                    }
                }
                goto L_004c1b18;
            }
            // 0x004c1b30: short read: error 0x8000001A
            charge(ctx, 10);
            v1 = 1;
            v0 = lui(0x8000);
            sw(v1, sp, 0x80);
            a0 = v0 | 0x1A;
            jal(ctx, 0x4C1B3Cu, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x84);
            a0 = addiu(sp, 0x80);
            jal(ctx, 0x4C1B48u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
            // 0x004c1ba8 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x90);
            return;
        }
    L_004c1b58:  // a version outside 0x35000..0x37002: error 0x80000004
        charge(ctx, 10);
        v1 = 1;
        v0 = lui(0x8000);
        sw(v1, sp, 0x78);
        a0 = v0 | 0x4;
        jal(ctx, 0x4C1B64u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x7C);
        a0 = addiu(sp, 0x78);
        jal(ctx, 0x4C1B70u, gen::fn_sub_4C1C50_004c1c50);
        s0 = 0;
        backedge(ctx);
        goto L_004c1b18;
    }
    // 0x004c1b80: no struct chunk: error 0x8000001A
    charge(ctx, 10);
    v1 = 1;
    v0 = lui(0x8000);
    sw(v1, sp, 0x70);
    a0 = v0 | 0x1A;
    jal(ctx, 0x4C1B8Cu, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0x74);
    a0 = addiu(sp, 0x70);
    jal(ctx, 0x4C1B98u, gen::fn_sub_4C1C50_004c1c50);
    s0 = 0;
    backedge(ctx);
L_004c1b18:
    charge(ctx, 2);
    v0 = s0;
    // 0x004c1ba8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// sub_4C3960 [freeListSetPrealloc] -- sets the free lists' preallocation switch (gp 0x7CDD38)
// While it is 0, sub_4C3970 creates every free list without preallocated blocks.
// 0x004C3960 sub_4C3960 -- 8 bytes; leaf frame (no stack)
void sub_4C3960(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, gp{ctx, 28};
    // 0x004c3960
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a0, gp, -20408);  // 0x7CDD38 (free lists: preallocation enabled)
}

// sub_4C3970 [freeListCreate] -- creates (or initialises) a free list and preallocates blocks
// ($a0 = the entry size, $a1 = entries per block, $a2 = the alignment (0: 16), $a3 = blocks to preallocate,
// $t0 = a static record or 0, $t1 = the memory hint) A static record gets flags 3; otherwise a 36-byte record
// comes from the free list of free lists (0x7CE8E4, through the slot 0x960188) or, before that exists, from
// RwMalloc, with flags 2 (only the hint's byte 0xFF0000 is passed). The entry size is rounded up to the
// alignment, the bitmap is (entries + 7) / 8 bytes, the block list empty. With preallocation on (0x7CDD38),
// each preallocated block is RwMalloc(alignment + bitmap + 7 + entries x size) linked at the head with a zero
// bitmap (memset); a failed one destroys the free list (sub_4C3B70) -> 0. Last the record joins the list of
// all free lists (0x7CE8E8). Returns the free list.
// 0x004C3970 sub_4C3970 -- 468 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C3970(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c3970
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a1;
    sq(s3, sp, 0x30);
    s4 = a3;
    sq(s2, sp, 0x20);
    s3 = t0;
    sq(s1, sp, 0x10);
    s2 = t1;
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, -20408);  // 0x7CDD38 (free lists: preallocation enabled)
    s0 = a2;
    if (v0 == 0) {
        // 0x004c39b0: preallocation off: no blocks
        charge(ctx, 1);
        s4 = 0;
    }
    // 0x004c39b4
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x004c39bc: alignment 0 -> 16
        charge(ctx, 1);
        s0 = 16;
    }
    // 0x004c39c0
    charge(ctx, 2);
    if (s3 != 0) {
        // 0x004c39c8: a static record: flags 3
        charge(ctx, 2);
        v0 = 3;
        sw(v0, s3, freelist::kFlags);
        goto L_004c39d0;
    }
    // 0x004c3a38
    charge(ctx, 3);
    lw(a0, gp, -17420);  // 0x7CE8E4 (the free list that holds free lists)
    if (a0 == 0) {
        // 0x004c3a70: no free list of free lists yet: RwMalloc(36)
        charge(ctx, 8);
        v0 = 0xFF0000;
        a1 = s2 & v0;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
        a0 = 36;
        jalr(ctx, 0x4C3A80u, v0.u());
        s3 = v0;
        backedge(ctx);
    } else {
        // 0x004c3a44: a record from the free list of free lists
        charge(ctx, 6);
        v0 = 0x960000;
        v1 = 0xFF0000;
        lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
        a1 = s2 & v1;
        jalr(ctx, 0x4C3A50u, v0.u());
        s3 = v0;
    }
    // 0x004c3a5c
    charge(ctx, 2);
    if (s3 == 0) {
        // 0x004c3a90: no record: 0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004c3a64: allocated: flags 2
        charge(ctx, 3);
        v0 = 2;
        sw(v0, s3, freelist::kFlags);
        backedge(ctx);
    L_004c39d0:  // the record: entry size rounded to the alignment, the bitmap size, an empty block list
        charge(ctx, 16);
        a0 = addiu(s0, -1);
        v1 = addiu(s5, 7);
        v0 = addu(s1, a0);
        a0 = nor(a0, 0);
        a0 = a0 & v0;
        v0 = si(-8);
        sw(a0, s3, freelist::kEntrySize);
        v0 = v1 & v0;
        sw(s5, s3, freelist::kEntriesPerBlock);
        s1 = srl(v0, 3);
        sw(s0, s3, freelist::kAlignment);
        v0 = addiu(s3, 16);
        sw(s1, s3, freelist::kHeapSize);
        sw(v0, s3, freelist::kBlocks);
        sw(v0, s3, freelist::kBlocksPrev);
        if (s4 == 0) {
            // 0x004c3a10
            charge(ctx, 1);
            lw(a1, gp, -17416);  // 0x7CE8E8 (the list of all free lists)
            goto L_004c3a14;
        }
        // 0x004c3a98: the preallocated blocks: their size
        charge(ctx, 6);
        v1 = addiu(s1, 7);
        mult(v0, s5, a0);
        s5 = 0x960000;
        v0 = addu(v1, v0);
        s5 = addiu(s5, 376);  // &0x960178 (RwMalloc slot)
        s0 = addu(s0, v0);
        for (;;) {
            // 0x004c3ab0: RwMalloc a block
            charge(ctx, 6);
            lw(v0, s5, 0);
            a0 = s0;
            a1 = s2;
            jalr(ctx, 0x4C3AB8u, v0.u());
            if (v0 == 0) {
                goto L_004c3ac8_17;
            }
            // 0x004c3ad8: link it at the head, clear its bitmap
            charge(ctx, 16);
            sw(zero, v0, 4);
            v1 = addiu(s3, 16);
            sw(zero, v0, 0);
            a0 = addiu(v0, 8);
            lw(a3, s3, freelist::kBlocks);
            a1 = 0;
            a2 = s1;
            sw(a3, v0, 0);
            sw(v1, v0, 4);
            lw(v1, s3, freelist::kBlocks);
            sw(v0, v1, 4);
            link(ctx, 0x4C3B04u);  // $ra first: the delay slot below depends on it
            sw(v0, s3, freelist::kBlocks);
            call(ctx, gen::fn_memset_00521408);
            s4 = addiu(s4, -1);
            if (s4 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004c3b18: join the list of all free lists
        charge(ctx, 2);
        lw(a1, gp, -17416);  // 0x7CE8E8 (the list of all free lists)
        backedge(ctx);
    L_004c3a14:  // the list of all free lists 0x7CE8E8: at its head
        charge(ctx, 9);
        v1 = addiu(gp, -17416);  // &0x7CE8E8 (the list of all free lists)
        a0 = addiu(s3, 28);
        v0 = s3;
        sw(a1, s3, freelist::kLink);
        sw(v1, s3, freelist::kLinkPrev);
        lw(v1, gp, -17416);  // 0x7CE8E8 (the list of all free lists)
        sw(a0, v1, 4);
        sw(a0, gp, -17416);  // 0x7CE8E8 (the list of all free lists)
    }
    // 0x004c3b20 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004c3ac8_17:  // a block could not be allocated: destroy the free list, 0
    charge(ctx, 4);
    a0 = s3;
    jal(ctx, 0x4C3AC8u, gen::fn_sub_4C3B70_004c3b70);
    v0 = 0;
    // 0x004c3b20 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// sub_4C3B50 [freeListCreateOneBlock] -- sub_4C3970 with one preallocated block and no static record
// ($a0 = entry size, $a1 = entries per block, $a2 = alignment, $a3 = hint) Tail call.
// 0x004C3B50 sub_4C3B50 -- 16 bytes; leaf frame (no stack)
void sub_4C3B50(EEContext& ctx) {
    using namespace hg;
    Gpr a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x004c3b50
    enter(ctx, 4);  // entry check point + this block's cycles
    t1 = a3;
    t0 = 0;
    a3 = 1;
    gen::fn_sub_4C3970_004c3970(ctx);  // tail call
}

// sub_4C3B60 [freeListCreateFull] -- sub_4C3970 with all six arguments (tail call; the entry the modules use)
// 0x004C3B60 sub_4C3B60 -- 8 bytes; leaf frame (no stack)
void sub_4C3B60(EEContext& ctx) {
    using namespace hg;
    // 0x004c3b60
    enter(ctx, 2);  // entry check point + this block's cycles
    gen::fn_sub_4C3970_004c3970(ctx);  // tail call
}

// sub_4C3B70 [freeListFree] -- frees a free list's blocks and (unless static) its record
// Every block is unlinked and goes to RwFree; a record without flag bit 0 goes back to the free list of free
// lists (0x7CE8E4) unless it is that free list or there is none (then RwFree). The record stays in the list of
// all free lists (sub_4C3C30 is the full destroy). $v0: what the last free returned.
// 0x004C3B70 sub_4C3B70 -- 192 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C3B70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c3b70
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    s1 = a0;
    sq(s0, sp, 0x0);
    lw(a0, a0, 16);
    v1 = addiu(s1, 16);
    if (a0 != v1) {
        // 0x004c3b94
        charge(ctx, 2);
        s0 = 0x960000;
        s0 = addiu(s0, 380);  // &0x96017C (RwFree slot)
        for (;;) {
            // 0x004c3b9c: the next block: unlink, RwFree
            charge(ctx, 13);
            lw(v1, a0, 0);
            lw(v0, a0, 4);
            sw(v1, v0, 0);
            lw(v1, a0, 4);
            lw(v0, a0, 0);
            sw(v1, v0, 4);
            lw(v0, s0, 0);
            jalr(ctx, 0x4C3BB8u, v0.u());
            lw(a0, s1, freelist::kBlocks);
            v1 = addiu(s1, 16);
            if (a0 == v1) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004c3bd0: not static: the record too
    charge(ctx, 4);
    lw(v1, s1, freelist::kFlags);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x004c3be0
        charge(ctx, 3);
        lw(a0, gp, -17420);  // 0x7CE8E4 (the free list that holds free lists)
        if (a0 != s1) {
            // 0x004c3bec
            charge(ctx, 2);
            if (a0 == 0) {
                goto L_004c3c0c;
            }
            // 0x004c3bf4: back to the free list of free lists
            charge(ctx, 6);
            v0 = 0x960000;
            lw(v0, v0, 396);  // 0x96018C (free-list free slot)
            a1 = s1;
            jalr(ctx, 0x4C3BFCu, v0.u());
            ld(ra, sp, 0x20);
            // 0x004c3c20 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
    L_004c3c0c:  // that free list itself, or none yet: RwFree
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        a0 = s1;
        jalr(ctx, 0x4C3C14u, v0.u());
    }
    // 0x004c3c1c
    charge(ctx, 1);
    ld(ra, sp, 0x20);
    // 0x004c3c20 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4C3C30 [freeListDestroy] -- destroys a free list: out of the global list, blocks freed, record freed
// The record leaves the list of all free lists, every block goes to RwFree, and a record without flag bit 0
// goes back to the free list of free lists (or RwFree, as sub_4C3B70). Returns 1.
// 0x004C3C30 sub_4C3C30 -- 220 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C3C30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c3c30
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a1, a0, 28);
    v0 = addiu(s1, 16);
    lw(v1, a0, 32);
    sw(a1, v1, 0);
    lw(a1, a0, 32);
    lw(v1, a0, 28);
    sw(a1, v1, 4);
    lw(a0, a0, 16);
    if (a0 != v0) {
        // 0x004c3c6c
        charge(ctx, 2);
        s0 = 0x960000;
        s0 = addiu(s0, 380);  // &0x96017C (RwFree slot)
        for (;;) {
            // 0x004c3c74: the next block: unlink, RwFree
            charge(ctx, 13);
            lw(v1, a0, 0);
            lw(v0, a0, 4);
            sw(v1, v0, 0);
            lw(v1, a0, 4);
            lw(v0, a0, 0);
            sw(v1, v0, 4);
            lw(v0, s0, 0);
            jalr(ctx, 0x4C3C90u, v0.u());
            lw(a0, s1, freelist::kBlocks);
            v0 = addiu(s1, 16);
            if (a0 == v0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004c3ca8: not static: the record too
    charge(ctx, 4);
    lw(v0, s1, freelist::kFlags);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x004c3cb8
        charge(ctx, 3);
        lw(a0, gp, -17420);  // 0x7CE8E4 (the free list that holds free lists)
        if (a0 != s1) {
            // 0x004c3cc4
            charge(ctx, 2);
            if (a0 == 0) {
                goto L_004c3ce4;
            }
            // 0x004c3ccc: back to the free list of free lists
            charge(ctx, 6);
            v0 = 0x960000;
            lw(v0, v0, 396);  // 0x96018C (free-list free slot)
            a1 = s1;
            jalr(ctx, 0x4C3CD4u, v0.u());
            ld(ra, sp, 0x20);
            // 0x004c3cf8 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            v0 = 1;
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
    L_004c3ce4:  // that free list itself, or none yet: RwFree
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        a0 = s1;
        jalr(ctx, 0x4C3CECu, v0.u());
    }
    // 0x004c3cf4
    charge(ctx, 1);
    ld(ra, sp, 0x20);
    // 0x004c3cf8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 1;
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4C4080 [freeListPurge] -- frees a free list's empty blocks; returns the bytes released
// Each block is unlinked, its bitmap summed (8 bytes a step, then the rest): a block with no entry in use goes
// to RwFree, the others are linked back at the head (so the order reverses). Returns blocks freed x the entry
// size (the product the original computes, LO of mult).
// 0x004C4080 sub_4C4080 -- 372 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C4080(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c4080
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = addiu(s5, 16);
    lw(s2, a0, 8);
    lw(a0, a0, 16);
    s3 = 0;
    if (a0 != s1) {
        // 0x004c40b8
        charge(ctx, 2);
        s0 = 0x960000;
        s0 = addiu(s0, 380);  // &0x96017C (RwFree slot)
        for (;;) {
            // 0x004c40c0: the next block: unlink, sum its bitmap
            charge(ctx, 12);
            lw(a3, a0, 0);
            at = sltu(0, s2);
            lw(v0, a0, 4);
            v1 = addiu(a0, 8);
            a1 = 0;
            sw(a3, v0, 0);
            lw(a3, a0, 4);
            lw(v0, a0, 0);
            sw(a3, v0, 4);
            lw(s4, a0, 0);
            a2 = 0;
            if (at != 0) {
                // 0x004c40f0
                charge(ctx, 3);
                at = sltiu(s2, 9);
                v0 = addiu(s2, -8);
                if (at == 0) {
                    // 0x004c40fc
                    charge(ctx, 1);
                    for (;;) {
                        // 0x004c4100: 8 bitmap bytes a step
                        charge(ctx, 20);
                        t6 = addu(v1, a2);
                        lbu(t0, t6, 0);
                        a2 = addiu(a2, 8);
                        lbu(t5, t6, 1);
                        a3 = sltu(a2, v0);
                        lbu(t4, t6, 2);
                        lbu(t3, t6, 3);
                        lbu(t2, t6, 4);
                        lbu(t1, t6, 5);
                        a1 = addu(a1, t0);
                        t5 = addu(a1, t5);
                        lbu(t0, t6, 6);
                        lbu(a1, t6, 7);
                        t4 = addu(t5, t4);
                        t3 = addu(t4, t3);
                        t2 = addu(t3, t2);
                        t1 = addu(t2, t1);
                        t0 = addu(t1, t0);
                        a1 = addu(t0, a1);
                        if (a3 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x004c4150
                charge(ctx, 3);
                at = sltu(a2, s2);
                if (at != 0) {
                    // 0x004c415c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x004c4160: the remaining bytes
                        charge(ctx, 7);
                        v0 = addu(v1, a2);
                        lbu(a3, v0, 0);
                        a2 = addiu(a2, 1);
                        v0 = sltu(a2, s2);
                        a1 = addu(a1, a3);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004c417c
                    charge(ctx, 1);
                }
            }
            // 0x004c4180
            charge(ctx, 2);
            if (a1 == 0) {
                // 0x004c41bc: no entry in use: RwFree
                charge(ctx, 5);
                lw(v0, s0, 0);
                jalr(ctx, 0x4C41C0u, v0.u());
                s3 = addiu(s3, 1);
                backedge(ctx);
            } else {
                // 0x004c4188: in use: back at the head
                charge(ctx, 8);
                lw(v1, s5, freelist::kBlocks);
                v0 = addiu(s5, 16);
                sw(v1, a0, 0);
                sw(v0, a0, 4);
                lw(v0, s5, freelist::kBlocks);
                sw(a0, v0, 4);
                sw(a0, s5, freelist::kBlocks);
            }
            // 0x004c41a8
            charge(ctx, 2);
            a0 = s4;
            if (s4 == s1) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004c41b0: blocks freed x entry size
    charge(ctx, 3);
    lw(v0, s5, freelist::kEntrySize);
    mult(v0, s3, v0);
    // 0x004c41d0
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// sub_4C4200 [freeListForAllUsed] -- calls a callback on every entry in use, from a snapshot of each bitmap
// ($a0 = the free list, $a1 = the callback, $a2 = its data) For each block the bitmap is copied first
// (RwMalloc of the bitmap size, hint 0x10000; memcpy) so the callback may free entries; each set bit (MSB
// first) gives the entry ((block + bitmap + alignment + 7) & -alignment) + size x index, called as
// callback(entry, data); the copy is freed. No memory for a copy: 0. Returns the free list.
// 0x004C4200 sub_4C4200 -- 432 bytes; frame 0xF0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C4200(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004c4200
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    s7 = a2;
    sq(s5, sp, 0x50);
    s6 = a1;
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    v0 = addiu(s5, 16);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 16);
    lw(s4, a0, 8);
    sq(v0, sp, 0xD0);
    if (s0 != v0) {
        // 0x004c424c
        charge(ctx, 6);
        v0 = 0x960000;
        v0 = addiu(v0, 376);  // &0x960178 (RwMalloc slot)
        sq(v0, sp, 0xC0);
        v0 = 0x960000;
        v0 = addiu(v0, 380);  // &0x96017C (RwFree slot)
        sq(v0, sp, 0xB0);
        for (;;) {
            // 0x004c4264: a copy of this block's bitmap
            charge(ctx, 9);
            lq(v0, sp, 0xC0);
            a0 = s4;
            a1 = 0x10000;
            lw(v0, v0, 0);
            s1 = addiu(s0, 8);
            jalr(ctx, 0x4C4274u, v0.u());
            fp = v0;
            if (fp == 0) {
                break;
            }
            // 0x004c4290: memcpy the bitmap; the next block read first
            charge(ctx, 9);
            a1 = s1;
            a0 = fp;
            a2 = s4;
            jal(ctx, 0x4C4298u, gen::fn_memcpy_00521250);
            lw(v0, s0, 0);
            at = sltu(0, s4);
            s3 = 0;
            sw(v0, sp, 0xE0);
            if (at != 0) {
                // 0x004c42b4
                charge(ctx, 3);
                s0 = addu(s0, s4);
                s1 = 0;
                for (;;) {
                    // 0x004c42c0: the next bitmap byte
                    charge(ctx, 4);
                    v0 = addu(fp, s3);
                    lbu(v0, v0, 0);
                    sq(v0, sp, 0xA0);
                    if (v0 != 0) {
                        // 0x004c42d0
                        charge(ctx, 2);
                        s2 = 0;
                        for (;;) {
                            // 0x004c42d8: bit 7 - k
                            charge(ctx, 7);
                            v0 = 128;
                            v0 = srav(v0, s2);
                            v1 = v0 & 0xFF;
                            lq(v0, sp, 0xA0);
                            v0 = v0 & v1;
                            if (v0 != 0) {
                                // 0x004c4348: in use: callback(entry, data)
                                charge(ctx, 14);
                                lw(a0, s5, freelist::kAlignment);
                                v1 = addu(s1, s2);
                                lw(v0, s5, freelist::kEntrySize);
                                a1 = addu(s0, a0);
                                a0 = addiu(a0, -1);
                                a1 = addiu(a1, 7);
                                a0 = nor(a0, 0);
                                a0 = a1 & a0;
                                mult(v0, v0, v1);
                                a1 = s7;
                                a0 = addu(a0, v0);
                                jalr(ctx, 0x4C4370u, s6.u());
                                backedge(ctx);
                            } else {
                                // 0x004c42f4
                                charge(ctx, 1);
                            }
                            // 0x004c42f8
                            charge(ctx, 4);
                            s2 = addiu(s2, 1);
                            v0 = sltiu(s2, 8);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                    // 0x004c4308
                    charge(ctx, 4);
                    s3 = addiu(s3, 1);
                    v0 = sltu(s3, s4);
                    s1 = addiu(s1, 8);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004c4318: free the copy; the next block
            charge(ctx, 9);
            lq(v0, sp, 0xB0);
            lw(v0, v0, 0);
            a0 = fp;
            jalr(ctx, 0x4C4320u, v0.u());
            lw(s0, sp, 0xE0);
            lq(v0, sp, 0xD0);
            v1 = s0;
            if (v1 == v0) {
                goto L_004c433c_13;
            }
            backedge(ctx);
        }
        // 0x004c4288: no memory for the copy: 0
        charge(ctx, 2);
        v0 = 0;
        // 0x004c4380 (the shared epilogue, written out on this path)
        charge(ctx, 12);
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
        sp = addiu(sp, 0xF0);
        return;
    }
L_004c4340:
    charge(ctx, 2);
    v0 = s5;
    // 0x004c4380 (the shared epilogue, written out on this path)
    charge(ctx, 12);
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
    sp = addiu(sp, 0xF0);
    return;
L_004c433c_13:  // back at the list head: done
    charge(ctx, 1);
    goto L_004c4340;
}

// sub_4C43B0 [freeListPurgeAll] -- purges every free list (sub_4C4080); returns the total bytes released
// Over the list of all free lists 0x7CE8E8 (each link is the record + 28); only positive results are added.
// 0x004C43B0 sub_4C43B0 -- 108 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C43B0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c43b0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, gp, -17416);  // 0x7CE8E8 (the list of all free lists)
    s0 = addiu(gp, -17416);  // &0x7CE8E8 (the list of all free lists)
    s2 = 0;
    if (s1 != s0) {
        for (;;) {
            // 0x004c43d4: purge the next free list
            charge(ctx, 5);
            a0 = addiu(s1, -28);
            jal(ctx, 0x4C43D4u, gen::fn_sub_4C4080_004c4080);
            at = slt(0, v0);
            if (at != 0) {
                // 0x004c43e8
                charge(ctx, 2);
                s2 = addu(s2, v0);
            }
            // 0x004c43f0
            charge(ctx, 3);
            lw(s1, s1, 0);
            if (s1 == s0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004c43fc
        charge(ctx, 1);
    }
    // 0x004c4400 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4C45F0 [resArenaInit] -- initialises the resource arena (its heap block and its two lists)
// ($a0 = the arena data, $a1 = the size) A size gets a heap block (RwMalloc, hint 0x4040B; none: error
// 0x80000013) set up by sub_4C6DF0 (too small: freed, error 12); size 0: no heap. Then both lists are empty,
// +36 -> list A (this frame), +32 -> list B (older), size, used 0, evicted 0. Returns the arena or 0.
// 0x004C45F0 sub_4C45F0 -- 256 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C45F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004c45f0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    s1 = a0;
    if (s0 == 0) {
        // 0x004c460c: size 0: no heap
        charge(ctx, 1);
        sw(zero, s1, resarena::kHeap);
        goto L_004c4610;
    }
    // 0x004c4644
    charge(ctx, 10);
    v0 = 0x40000;
    a1 = v0 | 0x40B;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    a0 = s0;
    jalr(ctx, 0x4C4654u, v0.u());
    sw(v0, s1, resarena::kHeap);
    lw(a0, s1, resarena::kHeap);
    if (a0 == 0) {
        // 0x004c46b4: no memory: error 0x80000013
        charge(ctx, 10);
        v0 = 1;
        a1 = s0;
        sw(v0, sp, 0x38);
        v0 = lui(0x8000);
        a0 = v0 | 0x13;
        jal(ctx, 0x4C46C4u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x3C);
        a0 = addiu(sp, 0x38);
        jal(ctx, 0x4C46D0u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x004c466c: set the heap up
        charge(ctx, 4);
        a1 = s0;
        jal(ctx, 0x4C466Cu, gen::fn_sub_4C6DF0_004c6df0);
        if (v0 != 0) {
            backedge(ctx);
        L_004c4610:  // empty lists, the size, nothing used
            charge(ctx, 13);
            a0 = addiu(s1, 16);
            v1 = addiu(s1, 24);
            sw(a0, s1, resarena::kListA);
            v0 = s1;
            sw(a0, s1, resarena::kListAPrev);
            sw(v1, s1, resarena::kListB);
            sw(v1, s1, resarena::kListBPrev);
            sw(a0, s1, resarena::kCurrent);
            sw(v1, s1, resarena::kOlder);
            sw(s0, s1, resarena::kSize);
            sw(zero, s1, resarena::kUsed);
            sw(zero, s1, resarena::kEvicted);
        } else {
            // 0x004c467c: the heap could not be set up: free it, error 12
            charge(ctx, 14);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x4C4684u);  // $ra = the return address
            lw(a0, s1, resarena::kHeap);
            call_ptr(ctx, jt);
            v0 = 1;
            a0 = 12;
            sw(v0, sp, 0x30);
            a1 = 0;
            jal(ctx, 0x4C4698u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x34);
            a0 = addiu(sp, 0x30);
            jal(ctx, 0x4C46A4u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        }
    }
    // 0x004c46dc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4C46F0 [resModuleOpen] -- the resource module's open: the arena at its offset
// ($a1 = the offset, stored at 0x7CE8F0) sub_4C45F0(0x960070 + offset, the size 0x960198); the open count goes
// up. Returns $a0, or 0.
// 0x004C46F0 sub_4C46F0 -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C46F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c46f0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s0, sp, 0x0);
    s0 = a0;
    sw(a1, gp, -17408);  // 0x7CE8F0 (the resource module offset)
    a0 = addu(v0, a1);
    v0 = 0x960000;
    link(ctx, 0x4C4714u);  // $ra first: the delay slot below depends on it
    lw(a1, v0, 408);
    call(ctx, gen::fn_sub_4C45F0_004c45f0);
    if (v0 != 0) {
        // 0x004c472c
        charge(ctx, 4);
        lw(v1, gp, -17404);  // 0x7CE8F4 (the resource module open count)
        v0 = s0;
        v1 = addiu(v1, 1);
        sw(v1, gp, -17404);  // 0x7CE8F4 (the resource module open count)
    } else {
        // 0x004c4724
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004c473c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4C4750 [resModuleClose] -- the resource module's close: empties the arena, frees its heap
// sub_4C4D70, then a heap block goes through sub_4C6E50 and RwFree and is cleared; the count goes down.
// 0x004C4750 sub_4C4750 -- 140 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C4750(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004c4750
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x4C475Cu, gen::fn_sub_4C4D70_004c4d70);
    lw(v1, gp, -17408);  // 0x7CE8F0 (the resource module offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = addu(v0, v1);
    lw(a0, v0, 12);
    if (a0 != 0) {
        // 0x004c4780
        charge(ctx, 15);
        jal(ctx, 0x4C4780u, gen::fn_sub_4C6E50_004c6e50);
        lw(a0, gp, -17408);  // 0x7CE8F0 (the resource module offset)
        v1 = 0x960000;
        v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        v1 = addu(v1, a0);
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x4C47A0u);  // $ra = the return address
        lw(a0, v1, 12);
        call_ptr(ctx, jt);
        lw(v1, gp, -17408);  // 0x7CE8F0 (the resource module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        sw(zero, v0, 12);
    }
    // 0x004c47bc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(v1, gp, -17404);  // 0x7CE8F4 (the resource module open count)
    v0 = s0;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17404);  // 0x7CE8F4 (the resource module open count)
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4C4890 [resArenaNewFrame] -- the arena's frame flip: this frame's entries become the older ones
// (RwRasterShowRaster calls it.) The older list's entries are appended to this frame's list (or moved, when it
// is empty), the older head is emptied, then the two pointers swap (+36 -> the empty head, +32 -> the full
// one) and the evicted count is reset.
// 0x004C4890 sub_4C4890 -- 148 bytes; leaf frame (no stack)
void sub_4C4890(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x004c4890
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(a0, gp, -17408);  // 0x7CE8F0 (the resource module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = addu(v1, a0);
    lw(a1, v1, 32);
    lw(a0, a1, 0);
    lw(a2, v1, 36);
    if (a0 != a1) {
        // 0x004c48b0: the older list has entries
        charge(ctx, 3);
        lw(v1, a2, 0);
        if (v1 == a2) {
            // 0x004c48e0: this frame's list is empty: move them
            charge(ctx, 9);
            sw(a0, a2, 0);
            lw(v1, a2, 0);
            sw(a2, v1, 4);
            lw(v1, a1, 4);
            sw(v1, a2, 4);
            lw(v1, a2, 4);
            sw(a2, v1, 0);
            sw(a1, a1, 0);
            sw(a1, a1, 4);
        } else {
            // 0x004c48bc: append them at its tail
            charge(ctx, 9);
            lw(v1, a2, 4);
            sw(a0, v1, 0);
            sw(v1, a0, 4);
            lw(v1, a1, 4);
            sw(a2, v1, 0);
            sw(v1, a2, 4);
            sw(a1, a1, 0);
            sw(a1, a1, 4);
        }
    }
    // 0x004c4904 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(a0, gp, -17408);  // 0x7CE8F0 (the resource module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = addu(v1, a0);
    sw(a1, v1, 36);
    sw(a2, v1, 32);
    sw(zero, v1, 8);
}

// RwResourcesSetArenaSize -- sets the resource arena's size (before the open: just the size word)
// Before the module is open the size goes to 0x960198. Open: the size is stored, the arena emptied
// (sub_4C4D70), the old heap released (sub_4C6E50, RwFree), a new block of the size allocated (RwMalloc, hint
// 0x3040B; none: size 0, error 0x80000013 -> 0) and set up (sub_4C6DF0; too small: freed, error 12 -> 0).
// Returns 1 or 0.
// 0x004C4C00 RwResourcesSetArenaSize -- 284 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void RwResourcesSetArenaSize(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004c4c00
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17404);  // 0x7CE8F4 (the resource module open count)
    s2 = a0;
    if (v0 != 0) {
        // 0x004c4c30: open: empty the arena, free the old heap, a new block
        charge(ctx, 23);
        lw(v1, gp, -17408);  // 0x7CE8F0 (the resource module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        s1 = addu(v0, v1);
        link(ctx, 0x4C4C40u);  // $ra first: the delay slot below depends on it
        sw(s2, s1, resarena::kSize);
        call(ctx, gen::fn_sub_4C4D70_004c4d70);
        link(ctx, 0x4C4C48u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, resarena::kHeap);
        call(ctx, gen::fn_sub_4C6E50_004c6e50);
        s0 = 0x960000;
        s0 = addiu(s0, 380);  // &0x96017C (RwFree slot)
        lw(v0, s0, 0);  // 0x96017C (RwFree slot)
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x4C4C5Cu);  // $ra = the return address
        lw(a0, s1, resarena::kHeap);
        call_ptr(ctx, jt);
        v0 = 0x30000;
        a1 = v0 | 0x40B;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
        a0 = s2;
        jalr(ctx, 0x4C4C74u, v0.u());
        sw(v0, s1, resarena::kHeap);
        lw(a0, s1, resarena::kHeap);
        if (a0 == 0) {
            // 0x004c4ca4: no memory: error 0x80000013
            charge(ctx, 12);
            v1 = 1;
            v0 = lui(0x8000);
            a1 = s2;
            sw(v1, sp, 0x48);
            a0 = v0 | 0x13;
            link(ctx, 0x4C4CB8u);  // $ra first: the delay slot below depends on it
            sw(zero, s1, resarena::kSize);
            call(ctx, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x4C);
            a0 = addiu(sp, 0x48);
            jal(ctx, 0x4C4CC4u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        } else {
            // 0x004c4c8c: set the heap up
            charge(ctx, 4);
            a1 = s2;
            jal(ctx, 0x4C4C8Cu, gen::fn_sub_4C6DF0_004c6df0);
            if (v0 == 0) {
                // 0x004c4cd4: too small: free it, error 12
                charge(ctx, 12);
                lw(v0, s0, 0);
                jt = v0.u();  // the target, read before the delay slot
                link(ctx, 0x4C4CD8u);  // $ra = the return address
                lw(a0, s1, resarena::kHeap);
                call_ptr(ctx, jt);
                v0 = 1;
                a0 = 12;
                sw(v0, sp, 0x40);
                a1 = 0;
                jal(ctx, 0x4C4CECu, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x44);
                a0 = addiu(sp, 0x40);
                jal(ctx, 0x4C4CF8u, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
            } else {
                // 0x004c4c9c
                charge(ctx, 2);
                v0 = 1;
            }
        }
    } else {
        // 0x004c4c20: not open: remember the size
        charge(ctx, 4);
        v1 = 0x960000;
        v0 = 1;
        sw(s2, v1, 408);  // 0x960198 (the resource arena size before the module opens)
    }
    // 0x004c4d04 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4C4D20 [resArenaGetUsage] -- this frame's resource use: the evicted bytes + the entries in this frame's list
// 0x004C4D20 sub_4C4D20 -- 72 bytes; leaf frame (no stack)
void sub_4C4D20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x004c4d20
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v1, gp, -17408);  // 0x7CE8F0 (the resource module offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = addu(v0, v1);
    lw(a0, v1, 36);
    lw(a1, a0, 0);
    lw(v0, v1, 8);
    if (a1 != a0) {
        for (;;) {
            // 0x004c4d40
            charge(ctx, 7);
            lw(v1, a1, 8);
            lw(a1, a1, 0);
            v0 = addu(v0, v1);
            if (a1 == a0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004c4d5c
        charge(ctx, 1);
    }
    // 0x004c4d60 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// sub_4C4D70 [resArenaEmpty] -- frees every entry of the arena
// List B is chained after list A's tail and every entry from A's head up to B's head is freed (the entry's destroy
// notification (+20) if any, its owner's pointer (*+16) cleared, then an arena entry (+0 != 0) is unlinked, its size
// taken off the used bytes and its block returned to the resource heap (sub_4C6E60); an entry from outside the arena
// goes to RwFree);
// then both heads are empty and the evicted count 0. Returns 1.
// 0x004C4D70 sub_4C4D70 -- 308 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C4D70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c4d70
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    a0 = 0x960000;
    sd(ra, sp, 0x40);
    a0 = addiu(a0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17408);  // 0x7CE8F0 (the resource module offset)
    v0 = addu(a0, v0);
    lw(v1, v0, 24);
    lw(v0, v0, 20);
    sw(v1, v0, 0);
    lw(v0, gp, -17408);  // 0x7CE8F0 (the resource module offset)
    v0 = addu(a0, v0);
    lw(s3, v0, 16);
    s1 = addiu(v0, 24);
    if (s3 != s1) {
        // 0x004c4dbc
        charge(ctx, 2);
        s0 = 0x960000;
        s0 = addiu(s0, 380);  // &0x96017C (RwFree slot)
        for (;;) {
            // 0x004c4dc4: the next entry (its successor read first)
            charge(ctx, 4);
            s2 = s3;
            lw(v0, s2, resentry::kDestroy);
            lw(s3, s3, 0);
            if (v0 != 0) {
                // 0x004c4dd4: the destroy notification
                charge(ctx, 3);
                a0 = s2;
                jalr(ctx, 0x4C4DD4u, v0.u());
            }
            // 0x004c4de0
            charge(ctx, 3);
            lw(v0, s2, resentry::kOwnerRef);
            if (v0 != 0) {
                // 0x004c4dec: clear the owner's pointer
                charge(ctx, 1);
                sw(zero, v0, 0);
            }
            // 0x004c4df0
            charge(ctx, 3);
            lw(a1, s2, resentry::kNext);
            if (a1 == 0) {
                // 0x004c4e74: outside the arena: RwFree
                charge(ctx, 5);
                lw(v0, s0, 0);
                a0 = s2;
                jalr(ctx, 0x4C4E78u, v0.u());
                backedge(ctx);
            } else {
                // 0x004c4dfc: unlink, used -= size, back to the resource heap
                charge(ctx, 15);
                lw(v1, s2, resentry::kPrev);
                v0 = 0x960000;
                v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                a0 = s2;
                sw(a1, v1, 0);
                lw(a1, s2, resentry::kPrev);
                lw(v1, s2, resentry::kNext);
                sw(a1, v1, 4);
                lw(v1, gp, -17408);  // 0x7CE8F0 (the resource module offset)
                lw(a1, s2, resentry::kSize);
                v1 = addu(v0, v1);
                lw(v0, v1, 4);
                v0 = subu(v0, a1);
                link(ctx, 0x4C4E30u);  // $ra first: the delay slot below depends on it
                sw(v0, v1, 4);
                call(ctx, gen::fn_sub_4C6E60_004c6e60);
            }
            // 0x004c4e38
            charge(ctx, 2);
            if (s3 == s1) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004c4e40: both lists empty
    charge(ctx, 13);
    lw(a0, gp, -17408);  // 0x7CE8F0 (the resource module offset)
    v1 = 0x960000;
    v0 = 1;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    a1 = addu(v1, a0);
    a0 = addiu(a1, 16);
    v1 = addiu(a1, 24);
    sw(a0, a1, 16);
    sw(a0, a1, 20);
    sw(v1, a1, 24);
    sw(v1, a1, 28);
    sw(zero, a1, 8);
    // 0x004c4e88
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4C6DF0 [resHeapInit] -- sets up the resource heap in a block: one free span
// ($a0 = the block, $a1 = its size) The first span starts at (block + 39) & -32 and ends at (block + size) &
// -32, minus a 32-byte header; under 32 bytes: 0. The span's header: {+0 the block, +4 0, +8 0, +12 its size,
// +16 0}; the block's first two words point at it. Returns 1.
// 0x004C6DF0 sub_4C6DF0 -- 88 bytes; leaf frame (no stack)
void sub_4C6DF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004c6df0
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = addu(a0, a1);
    v1 = si(-32);
    a1 = addiu(a0, 39);
    v0 = v0 & v1;
    a1 = a1 & v1;
    v0 = subu(v0, a1);
    v1 = addiu(v0, -32);
    at = slti(v1, 32);
    if (at == 0) {
        // 0x004c6e20
        charge(ctx, 8);
        sw(a0, a1, 0);
        v0 = 1;
        sw(zero, a1, 4);
        sw(zero, a1, 8);
        sw(zero, a1, 16);
        sw(v1, a1, 12);
        sw(a1, a0, 0);
        sw(a1, a0, 4);
    } else {
        // 0x004c6e18
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004c6e40 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// sub_4C6E50 [resHeapClose] -- the resource heap's close (nothing to do); returns 1
// 0x004C6E50 sub_4C6E50 -- 8 bytes; leaf frame (no stack)
void sub_4C6E50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x004c6e50
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 1;
}

// sub_4C12D0 [chunkIsComplex] -- 1 when a chunk type holds sub-chunks (types 5..11, 14..16, 18, 20, 26), else 0
// ($a0 -> a chunk-header info, +0 = the type) A chain of compares: 26, 20, 18, 16, 15, 14, 11..6 and 5 answer 1;
// 19 and 13 and every other type 0.
// 0x004C12D0 sub_4C12D0 -- 376 bytes; leaf frame (no stack)
void sub_4C12D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x004c12d0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 0);
    v0 = 26;
    if (v1 == v0) {
        // 0x004c143c
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x004c12e0
        charge(ctx, 3);
        v0 = 20;
        if (v1 == v0) {
            // 0x004c1434
            charge(ctx, 2);
            v0 = 1;
        } else {
            // 0x004c12ec
            charge(ctx, 3);
            v0 = 19;
            if (v1 == v0) {
                // 0x004c142c
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004c12f8
                charge(ctx, 3);
                v0 = 18;
                if (v1 == v0) {
                    // 0x004c1424
                    charge(ctx, 2);
                    v0 = 1;
                } else {
                    // 0x004c1304
                    charge(ctx, 3);
                    v0 = 16;
                    if (v1 == v0) {
                        // 0x004c141c
                        charge(ctx, 2);
                        v0 = 1;
                    } else {
                        // 0x004c1310
                        charge(ctx, 3);
                        v0 = 15;
                        if (v1 == v0) {
                            // 0x004c1414
                            charge(ctx, 2);
                            v0 = 1;
                        } else {
                            // 0x004c131c
                            charge(ctx, 3);
                            v0 = 14;
                            if (v1 == v0) {
                                // 0x004c140c
                                charge(ctx, 2);
                                v0 = 1;
                            } else {
                                // 0x004c1328
                                charge(ctx, 3);
                                v0 = 13;
                                if (v1 == v0) {
                                    // 0x004c1404
                                    charge(ctx, 2);
                                    v0 = 0;
                                } else {
                                    // 0x004c1334
                                    charge(ctx, 3);
                                    v0 = 11;
                                    if (v1 == v0) {
                                        // 0x004c13fc
                                        charge(ctx, 2);
                                        v0 = 1;
                                    } else {
                                        // 0x004c1340
                                        charge(ctx, 3);
                                        v0 = 10;
                                        if (v1 == v0) {
                                            // 0x004c13f4
                                            charge(ctx, 2);
                                            v0 = 1;
                                        } else {
                                            // 0x004c134c
                                            charge(ctx, 3);
                                            v0 = 9;
                                            if (v1 == v0) {
                                                // 0x004c13ec
                                                charge(ctx, 2);
                                                v0 = 1;
                                            } else {
                                                // 0x004c1358
                                                charge(ctx, 3);
                                                v0 = 8;
                                                if (v1 == v0) {
                                                    // 0x004c13e4
                                                    charge(ctx, 2);
                                                    v0 = 1;
                                                } else {
                                                    // 0x004c1364
                                                    charge(ctx, 3);
                                                    v0 = 7;
                                                    if (v1 == v0) {
                                                        // 0x004c13dc
                                                        charge(ctx, 2);
                                                        v0 = 1;
                                                    } else {
                                                        // 0x004c1370
                                                        charge(ctx, 3);
                                                        v0 = 6;
                                                        if (v1 == v0) {
                                                            // 0x004c13d4
                                                            charge(ctx, 2);
                                                            v0 = 1;
                                                        } else {
                                                            // 0x004c137c
                                                            charge(ctx, 3);
                                                            v0 = 5;
                                                            if (v1 == v0) {
                                                                // 0x004c13cc
                                                                charge(ctx, 2);
                                                                v0 = 1;
                                                            } else {
                                                                // 0x004c1388
                                                                charge(ctx, 3);
                                                                v0 = 3;
                                                                if (v1 == v0) {
                                                                    // 0x004c13c4
                                                                    charge(ctx, 2);
                                                                    v0 = 0;
                                                                } else {
                                                                    // 0x004c1394
                                                                    charge(ctx, 3);
                                                                    v0 = 2;
                                                                    if (v1 == v0) {
                                                                        // 0x004c13bc
                                                                        charge(ctx, 2);
                                                                        v0 = 0;
                                                                    } else {
                                                                        // 0x004c13a0
                                                                        charge(ctx, 3);
                                                                        v0 = 1;
                                                                        if (v1 == v0) {
                                                                            // 0x004c13b4
                                                                            charge(ctx, 2);
                                                                            v0 = 0;
                                                                        } else {
                                                                            // 0x004c13ac
                                                                            charge(ctx, 2);
                                                                            v0 = 0;
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x004c1440 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// sub_4C1450 [streamReadChunkHeader] -- reads a 12-byte chunk header; returns type / length / version / build
// ($a0 = the stream, $a1 / $a2 / $a3 / $t0 = where to put the type, length, version, build, each optional)
// 12 bytes into the frame (a short read: error 0x8000001A -> 0); the library id word: a high half -> version = ((id >>
// 14) & 0x3FF00) + 0x30000 | ((id >> 16) & 0x3F), build = id & 0xFFFF; a pre-3.1 id (high half 0) -> version = id << 8,
// build 0; sub_4C12D0 classifies it.
// Returns 1.
// 0x004C1450 sub_4C1450 -- 328 bytes; frame 0x80: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C1450(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c1450
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    s1 = a3;
    s0 = t0;
    a1 = addiu(sp, 0x70);
    a2 = 12;
    jal(ctx, 0x4C147Cu, gen::fn_sub_4C5250_004c5250);
    v0 = v0 ^ 0xC;
    v0 = sltiu(v0, 1);
    if (v0 == 0) {
        // 0x004c1558: short read: error 0x8000001A
        charge(ctx, 9);
        v1 = 1;
        v0 = lui(0x8000);
        sw(v1, sp, 0x68);
        a0 = v0 | 0x1A;
        jal(ctx, 0x4C1564u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x6C);
        a0 = addiu(sp, 0x68);
        jal(ctx, 0x4C1570u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x004c1494: the header: type, length, the library id
        charge(ctx, 10);
        v0 = addiu(sp, 0x78);
        lw(a2, sp, 0x70);
        lw(a0, v0, 0);
        a1 = addiu(sp, 0x54);
        lw(v1, sp, 0x74);
        sw(a2, sp, 0x50);
        v0 = lui(0xFFFF);
        v0 = a0 & v0;
        sw(v1, a1, 0);
        if (v0 != 0) {
            // 0x004c14d4: a 3.1+ id: version and build from the packed word
            charge(ctx, 13);
            v0 = srl(a0, 16);
            t0 = srl(a0, 14);
            v1 = v0 & 0x3F;
            a3 = 0x30000;
            v0 = a0 & 0xFFFF;
            t1 = addiu(sp, 0x5C);
            a0 = a3 | 0xFF00;
            sw(v0, t1, 0);
            a0 = t0 & a0;
            a2 = addiu(sp, 0x58);
            v0 = addu(a0, a3);
            v0 = v0 | v1;
            sw(v0, a2, 0);
        } else {
            // 0x004c14bc: an old id: version = id << 8
            charge(ctx, 6);
            t1 = addiu(sp, 0x5C);
            v0 = sll(a0, 8);
            a2 = addiu(sp, 0x58);
            sw(zero, t1, 0);
            sw(v0, a2, 0);
        }
        // 0x004c1508: complex or not (sub_4C12D0)
        charge(ctx, 4);
        a0 = addiu(sp, 0x50);
        jal(ctx, 0x4C1508u, gen::fn_sub_4C12D0_004c12d0);
        sw(v0, sp, 0x60);
        if (s3 != 0) {
            // 0x004c1518: the type out
            charge(ctx, 2);
            lw(v0, sp, 0x50);
            sw(v0, s3, 0);
        }
        // 0x004c1520
        charge(ctx, 2);
        if (s2 != 0) {
            // 0x004c1528: the length out
            charge(ctx, 2);
            lw(v0, a1, 0);
            sw(v0, s2, 0);
        }
        // 0x004c1530
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x004c1538: the build out
            charge(ctx, 2);
            lw(v0, t1, 0);
            sw(v0, s0, 0);
        }
        // 0x004c1540
        charge(ctx, 2);
        if (s1 != 0) {
            // 0x004c1548: the version out
            charge(ctx, 2);
            lw(v0, a2, 0);
            sw(v0, s1, 0);
        }
        // 0x004c1550
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x004c157c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// sub_4C15A0 [streamWriteVersionedChunkHeader] -- writes a chunk header (type, length, version, build)
// ($a0 = the stream, $a1 = type, $a2 = length, $a3 = version, $t0 = build) The library id = build |
// ((version - 0x30000) & 0x3FF00) << 14 | (version & 0x3F) << 16; the 12 bytes go to sub_4C53F0 (its
// result is returned).
// 0x004C15A0 sub_4C15A0 -- 88 bytes; frame 0x20: ra sp+0x0
void sub_4C15A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c15a0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = t0 & 0xFFFF;
    sd(ra, sp, 0x0);
    v1 = lui(0xFFFD);
    t0 = addu(a3, v1);
    sw(a2, sp, 0x14);
    v1 = a3 & 0x3F;
    a2 = 0x30000;
    a3 = a2 | 0xFF00;
    sw(a1, sp, 0x10);
    a3 = t0 & a3;
    v1 = sll(v1, 16);
    a3 = sll(a3, 14);
    a1 = addiu(sp, 0x10);
    v1 = a3 | v1;
    a2 = 12;
    v0 = v0 | v1;
    link(ctx, 0x4C15E4u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x18);
    call(ctx, gen::fn_sub_4C53F0_004c53f0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4C1600 [streamFindChunk] -- skips chunks until one of the wanted type; returns its length / version
// ($a0 = the stream, $a1 = the type, $a2 / $a3 = where to put the length / the version) Headers are read
// (sub_4C1450) and other chunks skipped (sub_4C5620) until the type matches; a version outside
// 0x35000..0x37002 is error 0x80000004 -> 0. Returns 1, or 0 when the stream ends (or a skip fails).
// 0x004C1600 sub_4C1600 -- 336 bytes; frame 0x70: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C1600(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c1600
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    t0 = 0;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = a2;
    s0 = a3;
    a1 = addiu(sp, 0x6C);
    a2 = addiu(sp, 0x68);
    a3 = addiu(sp, 0x64);
    jal(ctx, 0x4C1634u, gen::fn_sub_4C1450_004c1450);
    if (v0 != 0) {
        for (;;) {
            // 0x004c1644: this chunk's type?
            charge(ctx, 3);
            lw(v0, sp, 0x6C);
            if (v0 == s2) {
                goto L_004c1650_2;
            }
            // 0x004c16a4: another type: skip its payload
            charge(ctx, 5);
            lw(a1, sp, 0x68);
            a0 = s3;
            jal(ctx, 0x4C16A8u, gen::fn_sub_4C5620_004c5620);
            if (v0 == 0) {
                goto L_004c1730;
            }
            // 0x004c16b8: the next header
            charge(ctx, 8);
            a0 = s3;
            a1 = addiu(sp, 0x6C);
            a2 = addiu(sp, 0x68);
            a3 = addiu(sp, 0x64);
            t0 = 0;
            jal(ctx, 0x4C16C8u, gen::fn_sub_4C1450_004c1450);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004c16d8
    charge(ctx, 2);
    v0 = 0;
    // 0x004c1734 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004c1650_2:  // the wanted type: check its version
    charge(ctx, 6);
    lw(v1, sp, 0x64);
    v0 = 0x30000;
    v0 = v0 | 0x5000;
    v0 = sltu(v1, v0);
    if (v0 != 0) {
        // 0x004c16e0: too new: error 0x80000004
        charge(ctx, 10);
        v1 = 1;
        v0 = lui(0x8000);
        sw(v1, sp, 0x58);
        a0 = v0 | 0x4;
        jal(ctx, 0x4C16ECu, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x5C);
        a0 = addiu(sp, 0x58);
        jal(ctx, 0x4C16F8u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x004c1668
        charge(ctx, 5);
        at = 0x30000;
        at = at | 0x7003;
        at = sltu(v1, at);
        if (at == 0) {
            // 0x004c1708: too old: error 0x80000004
            charge(ctx, 10);
            v1 = 1;
            v0 = lui(0x8000);
            sw(v1, sp, 0x50);
            a0 = v0 | 0x4;
            jal(ctx, 0x4C1714u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x54);
            a0 = addiu(sp, 0x50);
            jal(ctx, 0x4C1720u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        } else {
            // 0x004c167c: found: the length out
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x004c1684
                charge(ctx, 2);
                lw(v0, sp, 0x68);
                sw(v0, s1, 0);
            }
            // 0x004c168c
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x004c1694: the version out
                charge(ctx, 2);
                lw(v0, sp, 0x64);
                sw(v0, s0, 0);
            }
            // 0x004c169c
            charge(ctx, 2);
            v0 = 1;
        }
    }
    // 0x004c1734 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004c1730:  // a skip failed: 0
    charge(ctx, 1);
    v0 = 0;
    // 0x004c1734 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// sub_4C1750 [streamWriteReal] -- writes floats to a stream, through a 256-byte stack buffer
// ($a0 = the stream, $a1 = the data, $a2 = bytes) Up to 256 bytes a pass: memcpy into the frame (the
// byte-order conversion of a big-endian target compiles to nothing here), sub_4C53F0. Returns the stream, or
// 0 when a write fails.
// 0x004C1750 sub_4C1750 -- 160 bytes; frame 0x150: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C1750(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c1750
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    s1 = a2;
    sq(s0, sp, 0x0);
    if (s1 != 0) {
        for (;;) {
            // 0x004c1778: this pass: min(bytes, 256)
            charge(ctx, 3);
            at = sltiu(s1, 256);
            if (at == 0) {
                // 0x004c17c8
                charge(ctx, 2);
                s0 = 256;
                backedge(ctx);
            } else {
                // 0x004c1784
                charge(ctx, 1);
                s0 = s1;
            }
            // 0x004c1788: copy, write
            charge(ctx, 10);
            a0 = addiu(sp, 0x50);
            a1 = s2;
            a2 = s0;
            jal(ctx, 0x4C1790u, gen::fn_memcpy_00521250);
            a0 = s3;
            a1 = addiu(sp, 0x50);
            a2 = s0;
            jal(ctx, 0x4C17A0u, gen::fn_sub_4C53F0_004c53f0);
            if (v0 == 0) {
                break;
            }
            // 0x004c17b0: the rest
            charge(ctx, 3);
            s1 = subu(s1, s0);
            s2 = addu(s2, s0);
            if (s1 == 0) {
                goto L_004c17bc_5;
            }
            backedge(ctx);
        }
        // 0x004c17d0
        charge(ctx, 1);
        v0 = 0;
        // 0x004c17d4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x150);
        return;
    }
L_004c17c0:
    charge(ctx, 2);
    v0 = s3;
    // 0x004c17d4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x150);
    return;
L_004c17bc_5:  // all written
    charge(ctx, 1);
    goto L_004c17c0;
}

// sub_4C17F0 [streamWriteInt32] -- writes 32-bit integers (sub_4C53F0); returns the stream
// The result of the write is ignored (no conversion on a little-endian target).
// 0x004C17F0 sub_4C17F0 -- 40 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C17F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c17f0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x4C17FCu, gen::fn_sub_4C53F0_004c53f0);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4C1820 [streamWriteInt32b] -- writes 32-bit integers: a second copy of sub_4C17F0 (identical body); returns the
//   stream
// 0x004C1820 sub_4C1820 -- 40 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C1820(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c1820
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x4C182Cu, gen::fn_sub_4C53F0_004c53f0);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4C1850 [streamReadInt32] -- reads 32-bit integers (sub_4C5250); 0 and error 0x8000001A when nothing is read
// 0x004C1850 sub_4C1850 -- 88 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C1850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c1850
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x4C185Cu, gen::fn_sub_4C5250_004c5250);
    if (v0 == 0) {
        // 0x004c1874: nothing read: error 0x8000001A
        charge(ctx, 9);
        v1 = 1;
        v0 = lui(0x8000);
        sw(v1, sp, 0x28);
        a0 = v0 | 0x1A;
        jal(ctx, 0x4C1880u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x2C);
        a0 = addiu(sp, 0x28);
        jal(ctx, 0x4C188Cu, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x004c186c: read: the stream
        charge(ctx, 2);
        v0 = s0;
    }
    // 0x004c1898 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4C18B0 [streamReadReal] -- reads floats (sub_4C5250); 0 and error 0x8000001A when nothing is read
// 0x004C18B0 sub_4C18B0 -- 88 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C18B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c18b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x4C18BCu, gen::fn_sub_4C5250_004c5250);
    if (v0 == 0) {
        // 0x004c18d4
        charge(ctx, 9);
        v1 = 1;
        v0 = lui(0x8000);
        sw(v1, sp, 0x28);
        a0 = v0 | 0x1A;
        jal(ctx, 0x4C18E0u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x2C);
        a0 = addiu(sp, 0x28);
        jal(ctx, 0x4C18ECu, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x004c18cc
        charge(ctx, 2);
        v0 = s0;
    }
    // 0x004c18f8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4C1910 [streamReadInt32b] -- reads 32-bit integers: a second copy of sub_4C1850 (identical body); 0 and error
//   0x8000001A on failure
// 0x004C1910 sub_4C1910 -- 88 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C1910(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c1910
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x4C191Cu, gen::fn_sub_4C5250_004c5250);
    if (v0 == 0) {
        // 0x004c1934
        charge(ctx, 9);
        v1 = 1;
        v0 = lui(0x8000);
        sw(v1, sp, 0x28);
        a0 = v0 | 0x1A;
        jal(ctx, 0x4C1940u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x2C);
        a0 = addiu(sp, 0x28);
        jal(ctx, 0x4C194Cu, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x004c192c
        charge(ctx, 2);
        v0 = s0;
    }
    // 0x004c1958 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4C1970 [streamReadChunkHeaderInfo] -- reads a chunk header into a 20-byte info record
// ($a0 = the stream, $a1 = the info: +0 type, +4 length, +8 version, +12 build, +16 complex) sub_4C1450 into
// the frame, copied, sub_4C12D0 for +16. Returns the stream or 0.
// 0x004C1970 sub_4C1970 -- 128 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C1970(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c1970
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    a2 = addiu(sp, 0x38);
    sq(s1, sp, 0x10);
    a3 = addiu(sp, 0x34);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    t0 = addiu(sp, 0x30);
    a1 = addiu(sp, 0x3C);
    jal(ctx, 0x4C1994u, gen::fn_sub_4C1450_004c1450);
    if (v0 != 0) {
        // 0x004c19ac
        charge(ctx, 12);
        lw(v0, sp, 0x3C);
        a0 = s0;
        sw(v0, s0, 0);
        lw(v0, sp, 0x38);
        sw(v0, s0, 4);
        lw(v0, sp, 0x34);
        sw(v0, s0, 8);
        lw(v0, sp, 0x30);
        link(ctx, 0x4C19CCu);  // $ra first: the delay slot below depends on it
        sw(v0, s0, 12);
        call(ctx, gen::fn_sub_4C12D0_004c12d0);
        sw(v0, s0, 16);
        v0 = s1;
    } else {
        // 0x004c19a4
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004c19dc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4C4EB0 [streamModuleOpen] -- the stream module's open: the stream free list
// ($a1 = the offset, stored at 0x7CE8F8) A free list of 36-byte streams (the counts of 0x7CDD3C / 0x7CDD40,
// alignment 4, the static record 0x95FFB0, hint 0x40404); the open count goes up. Returns $a0 or 0.
// 0x004C4EB0 sub_4C4EB0 -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C4EB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c4eb0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x40000;
    sq(s0, sp, 0x0);
    a2 = 4;
    sw(a1, gp, -17400);  // 0x7CE8F8 (the stream module offset)
    s0 = a0;
    lw(a1, gp, -20404);  // 0x7CDD3C (the stream free list: entries per block)
    a0 = 36;
    lw(a3, gp, -20400);  // 0x7CDD40 (the stream free list: preallocated blocks)
    t0 = addiu(t0, -80);  // &0x95FFB0 (the stream free list, static)
    t1 = v0 | 0x404;
    jal(ctx, 0x4C4EE0u, gen::fn_sub_4C3B60_004c3b60);
    lw(a0, gp, -17400);  // 0x7CE8F8 (the stream module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = addu(v1, a0);
    sw(v0, v1, 0);
    lw(v0, v1, 0);
    if (v0 != 0) {
        // 0x004c4f10
        charge(ctx, 4);
        lw(v1, gp, -17396);  // 0x7CE8FC (the stream module open count)
        v0 = s0;
        v1 = addiu(v1, 1);
        sw(v1, gp, -17396);  // 0x7CE8FC (the stream module open count)
    } else {
        // 0x004c4f08
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004c4f20 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4C4F30 [streamModuleClose] -- the stream module's close: destroys the free list; count down
// 0x004C4F30 sub_4C4F30 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C4F30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c4f30
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s0, sp, 0x0);
    lw(v1, gp, -17400);  // 0x7CE8F8 (the stream module offset)
    s0 = a0;
    v0 = addu(v0, v1);
    lw(a0, v0, 0);
    if (a0 != 0) {
        // 0x004c4f5c
        charge(ctx, 2);
        jal(ctx, 0x4C4F5Cu, gen::fn_sub_4C3C30_004c3c30);
    }
    // 0x004c4f64 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(v1, gp, -17396);  // 0x7CE8FC (the stream module open count)
    v0 = s0;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17396);  // 0x7CE8FC (the stream module open count)
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4C4F90 [streamOpenFileName] -- opens a file-name stream: the file opened in the access mode
// ($a0 = the stream, $a1 = the access 1 / 2 / 3, $a2 = the name) sub_4C0240(name, the mode string at
// 0x7CDD44 / 0x7CDD48 / 0x7CDD4C); another access is error 13. No file: error 0x80000002 -> 0. Else the
// handle goes to +12 and the stream is returned.
// 0x004C4F90 sub_4C4F90 -- 256 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C4F90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c4f90
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 3;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = 0;
    sq(s0, sp, 0x0);
    s1 = 0;
    s0 = a2;
    if (a1 == v0) {
        // 0x004c5008: append
        charge(ctx, 5);
        a0 = s0;
        a1 = addiu(gp, -20388);  // "ab"
        jal(ctx, 0x4C500Cu, gen::fn_sub_4C0240_004c0240);
        s1 = v0;
    } else {
        // 0x004c4fc0
        charge(ctx, 3);
        v0 = 2;
        if (a1 == v0) {
            // 0x004c4ff4: write
            charge(ctx, 5);
            a0 = s0;
            a1 = addiu(gp, -20392);  // "wb"
            jal(ctx, 0x4C4FF8u, gen::fn_sub_4C0240_004c0240);
            s1 = v0;
        } else {
            // 0x004c4fcc
            charge(ctx, 3);
            v0 = 1;
            if (a1 == v0) {
                // 0x004c4fe0: read
                charge(ctx, 5);
                a0 = s0;
                a1 = addiu(gp, -20396);  // "rb"
                jal(ctx, 0x4C4FE4u, gen::fn_sub_4C0240_004c0240);
                s1 = v0;
            } else {
                // 0x004c4fd8
                charge(ctx, 2);
                sw(v0, sp, 0x58);
                // 0x004c501c: a bad access: error 13
                charge(ctx, 5);
                a0 = 13;
                jal(ctx, 0x4C501Cu, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x5C);
                a0 = addiu(sp, 0x58);
                jal(ctx, 0x4C5028u, gen::fn_sub_4C1C50_004c1c50);
            }
        }
    }
    // 0x004c5030
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x004c5048: no file: error 0x80000002
        charge(ctx, 11);
        v0 = 1;
        a1 = s0;
        sw(v0, sp, 0x50);
        v0 = lui(0x8000);
        a0 = v0 | 0x2;
        jal(ctx, 0x4C5058u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x54);
        a0 = addiu(sp, 0x50);
        jal(ctx, 0x4C5064u, gen::fn_sub_4C1C50_004c1c50);
        backedge(ctx);
    } else {
        // 0x004c5038: the handle
        charge(ctx, 2);
        sw(s1, s3, stream::kFile);
        s2 = s3;
    }
    // 0x004c5040
    charge(ctx, 2);
    v0 = s2;
    // 0x004c5074
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4C5090 [streamOpenMemory] -- opens a memory stream over {start, size}
// ($a0 = the stream, $a1 = the access, $a2 -> {start, size}) Append: position = size; write: position, size
// and start 0 (the buffer grows on write); read: position 0 over the given block. Another access: error 13 -> 0.
// 0x004C5090 sub_4C5090 -- 172 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C5090(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c5090
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 3;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    if (a1 == v0) {
        // 0x004c50f8: append: at the end
        charge(ctx, 7);
        lw(v1, a2, 4);
        s0 = a0;
        lw(v0, a2, 0);
        sw(v1, a0, stream::kFile);
        sw(v1, a0, stream::kMemSize);
        sw(v0, a0, stream::kMemStart);
    } else {
        // 0x004c50a8
        charge(ctx, 3);
        v0 = 2;
        if (a1 == v0) {
            // 0x004c50e4: write: an empty buffer
            charge(ctx, 5);
            sw(zero, a0, stream::kFile);
            s0 = a0;
            sw(zero, a0, stream::kMemSize);
            sw(zero, a0, stream::kMemStart);
        } else {
            // 0x004c50b4
            charge(ctx, 3);
            v0 = 1;
            if (a1 == v0) {
                // 0x004c50c8: read: from the start
                charge(ctx, 7);
                lw(v1, a2, 4);
                s0 = a0;
                lw(v0, a2, 0);
                sw(zero, a0, stream::kFile);
                sw(v1, a0, stream::kMemSize);
                sw(v0, a0, stream::kMemStart);
            } else {
                // 0x004c50c0
                charge(ctx, 2);
                sw(v0, sp, 0x28);
                // 0x004c5114: a bad access: error 13
                charge(ctx, 5);
                a0 = 13;
                jal(ctx, 0x4C5114u, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x2C);
                a0 = addiu(sp, 0x28);
                jal(ctx, 0x4C5120u, gen::fn_sub_4C1C50_004c1c50);
            }
        }
    }
    // 0x004c5128 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4C5140 [streamInitialize] -- fills a stream record by type (file, file name, memory, custom)
// ($a0 = the stream, $a1 = owned by the free list, $a2 = the type, $a3 = the access, $t0 = the data) Type 4
// copies 20 bytes of callbacks and data (+12..+31); 3 -> sub_4C5090, 2 -> sub_4C4F90; 1 takes the handle when
// sub_4C0820 does not answer -1; another type: error 14. Returns the stream or 0.
// 0x004C5140 sub_4C5140 -- 268 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C5140(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c5140
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = t0;
    s0 = 0;
    if (s2 == 0) {
        // 0x004c5220: no record: 0
        charge(ctx, 2);
        v0 = 0;
        // 0x004c5234
        charge(ctx, 1);
        ld(ra, sp, 0x30);
    } else {
        // 0x004c5164: type, access, owner
        charge(ctx, 5);
        sw(a2, s2, stream::kType);
        v0 = 4;
        sw(a3, s2, stream::kAccess);
        sw(a1, s2, stream::kRwOwned);
        if (a2 == v0) {
            // 0x004c51e8: custom: the five words
            charge(ctx, 6);
            a1 = s1;
            a0 = addiu(s2, 12);
            a2 = 20;
            jal(ctx, 0x4C51F0u, gen::fn_memcpy_00521250);
            s0 = s2;
        L_004c5214:  // the result
            charge(ctx, 1);
            v0 = s0;
        } else {
            // 0x004c5178
            charge(ctx, 3);
            v0 = 3;
            if (a2 == v0) {
                // 0x004c51d4: memory
                charge(ctx, 5);
                a1 = a3;
                a2 = s1;
                jal(ctx, 0x4C51D8u, gen::fn_sub_4C5090_004c5090);
                s0 = v0;
                goto L_004c5214;
            }
            // 0x004c5184
            charge(ctx, 3);
            v0 = 2;
            if (a2 == v0) {
                // 0x004c51c0: file name
                charge(ctx, 5);
                a1 = a3;
                a2 = s1;
                jal(ctx, 0x4C51C4u, gen::fn_sub_4C4F90_004c4f90);
                s0 = v0;
                goto L_004c5214;
            }
            // 0x004c5190
            charge(ctx, 3);
            v0 = 1;
            if (a2 != v0) {
                // 0x004c519c: a bad type: error 14
                charge(ctx, 2);
                sw(v0, sp, 0x48);
                // 0x004c5200
                charge(ctx, 5);
                a0 = 14;
                jal(ctx, 0x4C5200u, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x4C);
                a0 = addiu(sp, 0x48);
                jal(ctx, 0x4C520Cu, gen::fn_sub_4C1C50_004c1c50);
                goto L_004c5214;
            }
            // 0x004c51a4: file: a valid handle?
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x4C51A4u, gen::fn_sub_4C0820_004c0820);
            v1 = si(-1);
            if (v0 != v1) {
                // 0x004c5228: the handle
                charge(ctx, 3);
                sw(s1, s2, stream::kFile);
                s0 = s2;
                backedge(ctx);
            }
            // 0x004c51b8
            charge(ctx, 2);
            v0 = s0;
        }
        // 0x004c5218
        charge(ctx, 2);
        ld(ra, sp, 0x30);
    }
    // 0x004c5238 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4C5250 [streamRead] -- reads bytes from a stream; returns the count read
// ($a0 = the stream, $a1 = the buffer, $a2 = bytes) Custom: its read callback (+16) with its data. Memory:
// at most size - position bytes (fewer: error 5, the end of the stream), memcpy from start + position, the
// position moves. File / file name: sub_4C03D0 (fread); a short read is error 5 at the end of the file
// (sub_4C06B0) or 0x8000001A. Another type: error 14 -> 0.
// 0x004C5250 sub_4C5250 -- 404 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C5250(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004c5250
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    a3 = a0;
    sd(ra, sp, 0x30);
    v0 = 4;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    lw(a0, a0, 0);
    s1 = a2;
    if (a0 == v0) {
        // 0x004c5318: custom: read(data, buffer, bytes)
        charge(ctx, 5);
        lw(v0, a3, stream::kMemSize);
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x4C531Cu);  // $ra = the return address
        lw(a0, a3, stream::kCustomData);
        call_ptr(ctx, jt);
        ld(ra, sp, 0x30);
    } else {
        // 0x004c527c
        charge(ctx, 3);
        v0 = 3;
        if (a0 == v0) {
            // 0x004c52d4: memory: what is left
            charge(ctx, 6);
            lw(v1, a3, stream::kMemSize);
            lw(v0, a3, stream::kFile);
            v0 = subu(v1, v0);
            at = sltu(v0, s1);
            s0 = addiu(a3, 12);
            if (at != 0) {
                // 0x004c53a4: not enough: error 5
                charge(ctx, 10);
                s1 = v0;
                a0 = 5;
                v0 = 1;
                link(ctx, 0x4C53B0u);  // $ra first: the delay slot below depends on it
                sw(v0, sp, 0x48);
                call(ctx, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x4C);
                a0 = addiu(sp, 0x48);
                jal(ctx, 0x4C53BCu, gen::fn_sub_4C1C50_004c1c50);
                lw(v1, s0, 8);
                backedge(ctx);
            } else {
                // 0x004c52ec
                charge(ctx, 1);
                lw(v1, s0, 8);
            }
            // 0x004c52f0: copy, move the position
            charge(ctx, 10);
            a0 = s2;
            lw(v0, s0, stream::kType);
            a2 = s1;
            a1 = addu(v1, v0);
            jal(ctx, 0x4C52FCu, gen::fn_memcpy_00521250);
            lw(v1, s0, stream::kType);
            v0 = s1;
            v1 = addu(v1, s1);
            sw(v1, s0, stream::kType);
        } else {
            // 0x004c5288
            charge(ctx, 3);
            v1 = 1;
            if (a0 != v1) {
                // 0x004c5294
                charge(ctx, 3);
                v0 = 2;
                if (a0 == v0) {
                    goto L_004c52a8;
                }
                // 0x004c52a0
                charge(ctx, 2);
                sw(v1, sp, 0x40);
                // 0x004c532c: a bad type: error 14
                charge(ctx, 7);
                a0 = 14;
                jal(ctx, 0x4C532Cu, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x44);
                a0 = addiu(sp, 0x40);
                jal(ctx, 0x4C5338u, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
                goto L_004c53cc;
            }
        L_004c52a8:  // file / file name: fread
            charge(ctx, 9);
            lw(s0, a3, stream::kFile);
            a0 = s2;
            a1 = 1;
            a2 = s1;
            a3 = s0;
            jal(ctx, 0x4C52B8u, gen::fn_sub_4C03D0_004c03d0);
            s2 = v0;
            if (s2 != s1) {
                // 0x004c5348: short: at the end of the file?
                charge(ctx, 4);
                a0 = s0;
                jal(ctx, 0x4C5348u, gen::fn_sub_4C06B0_004c06b0);
                if (v0 == 0) {
                    // 0x004c537c: no: error 0x8000001A
                    charge(ctx, 10);
                    v1 = 1;
                    v0 = lui(0x8000);
                    sw(v1, sp, 0x50);
                    a0 = v0 | 0x1A;
                    jal(ctx, 0x4C5388u, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0x54);
                    a0 = addiu(sp, 0x50);
                    jal(ctx, 0x4C5394u, gen::fn_sub_4C1C50_004c1c50);
                    backedge(ctx);
                } else {
                    // 0x004c5358: yes: error 5
                    charge(ctx, 9);
                    v0 = 1;
                    a0 = 5;
                    link(ctx, 0x4C5360u);  // $ra first: the delay slot below depends on it
                    sw(v0, sp, 0x58);
                    call(ctx, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0x5C);
                    a0 = addiu(sp, 0x58);
                    jal(ctx, 0x4C536Cu, gen::fn_sub_4C1C50_004c1c50);
                    backedge(ctx);
                }
            }
            // 0x004c52cc
            charge(ctx, 2);
            v0 = s2;
        }
    L_004c53cc:
        charge(ctx, 1);
        ld(ra, sp, 0x30);
    }
    // 0x004c53d0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4C53F0 [streamWrite] -- writes bytes to a stream; returns the stream or 0
// Custom: its write callback (+20; 0 -> 0). Memory: a buffer of 512 bytes on the first write (RwMalloc, hint
// 0x30404; none: error 0x80000013), grown by RwRealloc to size + max(bytes, 512) when the data does not fit
// (failure: error 0x80000013 with the missing size), memcpy at the position, which moves. File: sub_4C0420
// (fwrite); short: error 0x8000001C. Another type: error 14.
// 0x004C53F0 sub_4C53F0 -- 548 bytes; frame 0x80: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C53F0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004c53f0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    v0 = 4;
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, a0, 0);
    s2 = a2;
    if (a0 == v0) {
        // 0x004c5508: custom: write(data, buffer, bytes)
        charge(ctx, 6);
        lw(v0, s4, stream::kMemStart);
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x4C550Cu);  // $ra = the return address
        lw(a0, s4, stream::kCustomData);
        call_ptr(ctx, jt);
        if (v0 == 0) s4 = 0;
        v0 = s4;
    } else {
        // 0x004c5424
        charge(ctx, 3);
        v0 = 3;
        if (a0 == v0) {
            // 0x004c5474: memory: a buffer yet?
            charge(ctx, 3);
            lw(v0, s4, stream::kMemStart);
            s1 = addiu(s4, 12);
            if (v0 == 0) {
                // 0x004c5568: the first 512 bytes
                charge(ctx, 10);
                v0 = 0x30000;
                a1 = v0 | 0x404;
                v0 = 0x960000;
                lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                a0 = 512;
                jalr(ctx, 0x4C5578u, v0.u());
                sw(v0, s1, 8);
                lw(v0, s1, 8);
                if (v0 != 0) {
                    // 0x004c5590: its size
                    charge(ctx, 3);
                    v0 = 512;
                    sw(v0, s1, 4);
                    backedge(ctx);
                    goto L_004c5480;
                }
                // 0x004c559c: no memory: error 0x80000013
                charge(ctx, 11);
                v1 = 1;
                v0 = lui(0x8000);
                sw(v1, sp, 0x70);
                a0 = v0 | 0x13;
                a1 = 512;
                jal(ctx, 0x4C55ACu, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x74);
                a0 = addiu(sp, 0x70);
                jal(ctx, 0x4C55B8u, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
                // 0x004c55f4 (the shared epilogue, written out on this path)
                charge(ctx, 8);
                ld(ra, sp, 0x50);
                lq(s4, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x80);
                return;
            }
        L_004c5480:  // does it fit?
            charge(ctx, 6);
            lw(v1, s1, 4);
            lw(v0, s1, 0);
            v0 = subu(v1, v0);
            at = sltu(v0, s2);
            if (at != 0) {
                // 0x004c5498: does not fit: grow by max(bytes, 512)
                charge(ctx, 3);
                at = sltiu(s2, 512);
                if (at == 0) {
                    // 0x004c54ac
                    charge(ctx, 1);
                    s0 = addu(s2, v1);
                } else {
                    // 0x004c54a4
                    charge(ctx, 2);
                    s0 = addiu(v1, 512);
                }
                // 0x004c54b0: RwRealloc
                charge(ctx, 9);
                v0 = 0x960000;
                v1 = 0x1030000;
                lw(a0, s1, 8);
                a1 = s0;
                lw(v0, v0, 384);  // 0x960180 (RwRealloc slot)
                a2 = v1 | 0x404;  // &0x1030404
                jalr(ctx, 0x4C54C4u, v0.u());
                if (v0 != 0) {
                    // 0x004c54d4: the new block and size
                    charge(ctx, 2);
                    sw(v0, s1, 8);
                    sw(s0, s1, 4);
                    goto L_004c54dc;
                }
                // 0x004c55c8: no memory: error 0x80000013
                charge(ctx, 11);
                v1 = 1;
                v0 = lui(0x8000);
                sw(v1, sp, 0x68);
                a0 = v0 | 0x13;
                lw(v0, s1, 4);
                a1 = subu(s0, v0);
                jal(ctx, 0x4C55DCu, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x6C);
                a0 = addiu(sp, 0x68);
                jal(ctx, 0x4C55E8u, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
                // 0x004c55f4 (the shared epilogue, written out on this path)
                charge(ctx, 8);
                ld(ra, sp, 0x50);
                lq(s4, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x80);
                return;
            }
        L_004c54dc:  // copy at the position
            charge(ctx, 11);
            lw(v1, s1, 8);
            a1 = s3;
            lw(v0, s1, 0);
            a2 = s2;
            a0 = addu(v1, v0);
            jal(ctx, 0x4C54ECu, gen::fn_memcpy_00521250);
            lw(v1, s1, 0);
            v0 = s4;
            v1 = addu(v1, s2);
            sw(v1, s1, 0);
        } else {
            // 0x004c5430
            charge(ctx, 3);
            v1 = 1;
            if (a0 != v1) {
                // 0x004c543c
                charge(ctx, 3);
                v0 = 2;
                if (a0 == v0) {
                    goto L_004c5450;
                }
                // 0x004c5448
                charge(ctx, 2);
                sw(v1, sp, 0x60);
                // 0x004c5524: a bad type: error 14
                charge(ctx, 7);
                a0 = 14;
                jal(ctx, 0x4C5524u, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x64);
                a0 = addiu(sp, 0x60);
                jal(ctx, 0x4C5530u, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
                // 0x004c55f4 (the shared epilogue, written out on this path)
                charge(ctx, 8);
                ld(ra, sp, 0x50);
                lq(s4, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x80);
                return;
            }
        L_004c5450:  // file / file name: fwrite
            charge(ctx, 7);
            lw(a3, s4, stream::kFile);
            a0 = s3;
            a1 = 1;
            a2 = s2;
            jal(ctx, 0x4C545Cu, gen::fn_sub_4C0420_004c0420);
            if (v0 != s2) {
                // 0x004c5540: short write: error 0x8000001C
                charge(ctx, 10);
                v1 = 1;
                v0 = lui(0x8000);
                sw(v1, sp, 0x78);
                a0 = v0 | 0x1C;
                jal(ctx, 0x4C554Cu, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x7C);
                a0 = addiu(sp, 0x78);
                jal(ctx, 0x4C5558u, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
            } else {
                // 0x004c546c
                charge(ctx, 2);
                v0 = s4;
            }
        }
    }
    // 0x004c55f4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// sub_4C5620 [streamSkip] -- skips bytes in a stream; returns the stream or 0
// 0 bytes: the stream. Custom: its skip callback (+24). Memory: past the end -> the position is clamped to the
// size, error 5, 0; else it moves. File: sub_4C0470 (fseek, current); a failure at the end of the file (sub_4C06B0)
// is error 5. Another type: error 14.
// 0x004C5620 sub_4C5620 -- 348 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C5620(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004c5620
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (a1 == 0) {
        // 0x004c5700: nothing to skip
        charge(ctx, 2);
        v0 = s0;
    } else {
        // 0x004c5638
        charge(ctx, 4);
        lw(a0, s0, stream::kType);
        v0 = 4;
        if (a0 == v0) {
            // 0x004c56c8: custom: skip(data, bytes)
            charge(ctx, 6);
            lw(v0, s0, stream::kCustomSkip);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x4C56CCu);  // $ra = the return address
            lw(a0, s0, stream::kCustomData);
            call_ptr(ctx, jt);
            if (v0 == 0) s0 = 0;
            v0 = s0;
        } else {
            // 0x004c5648
            charge(ctx, 3);
            v0 = 3;
            if (a0 == v0) {
                // 0x004c569c: memory: within the size?
                charge(ctx, 6);
                lw(v0, s0, stream::kFile);
                lw(v1, s0, stream::kMemSize);
                v0 = addu(v0, a1);
                at = sltu(v1, v0);
                a0 = addiu(s0, 12);
                if (at != 0) {
                    // 0x004c5744: past the end: clamp, error 5
                    charge(ctx, 9);
                    sw(v1, a0, 0);
                    v0 = 1;
                    sw(v0, sp, 0x40);
                    a0 = 5;
                    jal(ctx, 0x4C5750u, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0x44);
                    a0 = addiu(sp, 0x40);
                    jal(ctx, 0x4C575Cu, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                } else {
                    // 0x004c56b4: move the position
                    charge(ctx, 5);
                    lw(v1, a0, 0);
                    v0 = s0;
                    v1 = addu(v1, a1);
                    sw(v1, a0, 0);
                }
            } else {
                // 0x004c5654
                charge(ctx, 3);
                v1 = 1;
                if (a0 != v1) {
                    // 0x004c5660
                    charge(ctx, 3);
                    v0 = 2;
                    if (a0 == v0) {
                        goto L_004c5674;
                    }
                    // 0x004c566c
                    charge(ctx, 2);
                    sw(v1, sp, 0x38);
                    // 0x004c56e4: a bad type: error 14
                    charge(ctx, 7);
                    a0 = 14;
                    jal(ctx, 0x4C56E4u, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0x3C);
                    a0 = addiu(sp, 0x38);
                    jal(ctx, 0x4C56F0u, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                    // 0x004c5768 (the shared epilogue, written out on this path)
                    charge(ctx, 5);
                    ld(ra, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x50);
                    return;
                }
            L_004c5674:  // file / file name: fseek
                charge(ctx, 8);
                lw(s1, s0, stream::kFile);
                a1 = dsll32(a1, 0);
                a1 = dsrl32(a1, 0);
                a2 = 1;
                a0 = s1;
                jal(ctx, 0x4C5684u, gen::fn_sub_4C0470_004c0470);
                if (v0 != 0) {
                    // 0x004c5708: seek failed: at the end?
                    charge(ctx, 4);
                    a0 = s1;
                    jal(ctx, 0x4C5708u, gen::fn_sub_4C06B0_004c06b0);
                    if (v0 != 0) {
                        // 0x004c5720: error 5
                        charge(ctx, 9);
                        v0 = 1;
                        a0 = 5;
                        link(ctx, 0x4C5728u);  // $ra first: the delay slot below depends on it
                        sw(v0, sp, 0x48);
                        call(ctx, gen::fn_sub_4C1D10_004c1d10);
                        sw(v0, sp, 0x4C);
                        a0 = addiu(sp, 0x48);
                        jal(ctx, 0x4C5734u, gen::fn_sub_4C1C50_004c1c50);
                        backedge(ctx);
                    }
                    // 0x004c5718
                    charge(ctx, 2);
                    s0 = 0;
                    backedge(ctx);
                }
                // 0x004c5694
                charge(ctx, 2);
                v0 = s0;
            }
        }
    }
    // 0x004c5768 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4C5780 [streamClose] -- closes a stream (and frees its record when the free list owns it)
// ($a0 = the stream, $a1 -> {start, size} or 0) Custom: its close callback (+12) if any. Memory: unless it was
// opened for reading, the buffer and its position go to *$a1. File name: sub_4C0370 (fclose; its result
// decides). File: nothing. Another type: error 14 -> 0. An owned record goes back to the stream free list.
// Returns 1 or the fclose verdict.
// 0x004C5780 sub_4C5780 -- 284 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C5780(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004c5780
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 4;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 0);
    s1 = a0;
    if (v1 == v0) {
        // 0x004c5810: custom: close(data)
        charge(ctx, 3);
        lw(v0, s1, stream::kFile);
        if (v0 != 0) {
            // 0x004c581c
            charge(ctx, 2);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x4C581Cu);  // $ra = the return address
            lw(a0, s1, stream::kCustomData);
            call_ptr(ctx, jt);
        }
        // 0x004c5824
        charge(ctx, 1);
        s0 = 1;
    L_004c5828:  // owned by the free list?
        charge(ctx, 3);
        lw(v0, s1, stream::kRwOwned);
        if (v0 != 0) {
            // 0x004c585c: owned: back to the free list
            charge(ctx, 11);
            lw(a0, gp, -17400);  // 0x7CE8F8 (the stream module offset)
            v1 = 0x960000;
            v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            v0 = 0x960000;
            lw(v0, v0, 396);  // 0x96018C (free-list free slot)
            v1 = addu(v1, a0);
            lw(a0, v1, 0);
            a1 = s1;
            jalr(ctx, 0x4C5878u, v0.u());
            backedge(ctx);
        }
        // 0x004c5834
        charge(ctx, 2);
        v0 = s0;
    } else {
        // 0x004c57a0
        charge(ctx, 3);
        v0 = 3;
        if (v1 == v0) {
            // 0x004c57e0: memory: written?
            charge(ctx, 4);
            lw(v1, s1, stream::kAccess);
            v0 = 1;
            if (v1 != v0) {
                // 0x004c57f0
                charge(ctx, 2);
                if (a1 != 0) {
                    // 0x004c57f8: the buffer and its size out
                    charge(ctx, 4);
                    lw(v0, s1, stream::kMemStart);
                    sw(v0, a1, 0);
                    lw(v0, s1, stream::kFile);
                    sw(v0, a1, 4);
                }
            }
            // 0x004c5808
            charge(ctx, 2);
            s0 = 1;
            goto L_004c5828;
        }
        // 0x004c57ac
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x004c57cc: file name: fclose
            charge(ctx, 5);
            link(ctx, 0x4C57CCu);  // $ra first: the delay slot below depends on it
            lw(a0, s1, stream::kFile);
            call(ctx, gen::fn_sub_4C0370_004c0370);
            s0 = v0;
            s0 = sltiu(s0, 1);
            goto L_004c5828;
        }
        // 0x004c57b8
        charge(ctx, 3);
        s0 = 1;
        if (v1 == s0) {
            goto L_004c5828;
        }
        // 0x004c57c4
        charge(ctx, 2);
        a0 = 14;
        // 0x004c5840
        charge(ctx, 7);
        link(ctx, 0x4C5840u);  // $ra first: the delay slot below depends on it
        sw(s0, sp, 0x38);
        call(ctx, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x3C);
        a0 = addiu(sp, 0x38);
        jal(ctx, 0x4C584Cu, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x004c5888 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4C58A0 [streamOpen] -- opens a stream: a record from the stream free list, filled by sub_4C5140
// ($a0 = the type, $a1 = the access, $a2 = the data) The record comes from the free list (slot 0x960188, hint
// 0x30404); sub_4C5140(record, 1, type, access, data); a failure returns the record -> 0.
// 0x004C58A0 sub_4C58A0 -- 184 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C58A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004c58a0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v1 = 0x30000;
    sd(ra, sp, 0x30);
    v0 = 0x960000;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    a0 = 0x960000;
    lw(a2, gp, -17400);  // 0x7CE8F8 (the stream module offset)
    a0 = addiu(a0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    a1 = v1 | 0x404;
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    v1 = addu(a0, a2);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4C58E0u);  // $ra = the return address
    lw(a0, v1, 0);
    call_ptr(ctx, jt);
    t0 = s0;
    a2 = s2;
    s0 = v0;
    a3 = s1;
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x4C58FCu, gen::fn_sub_4C5140_004c5140);
    if (v0 == 0) {
        // 0x004c5914: failed: free the record
        charge(ctx, 11);
        lw(a0, gp, -17400);  // 0x7CE8F8 (the stream module offset)
        v1 = 0x960000;
        v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = 0x960000;
        lw(v0, v0, 396);  // 0x96018C (free-list free slot)
        v1 = addu(v1, a0);
        lw(a0, v1, 0);
        a1 = s0;
        jalr(ctx, 0x4C5930u, v0.u());
        s0 = 0;
        backedge(ctx);
    }
    // 0x004c590c
    charge(ctx, 2);
    v0 = s0;
    // 0x004c5940
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4C5A50 [pluginRegistryReadDataChunks] -- reads an object's extension chunk: each plugin's data, then the always
//   callbacks
// ($a0 = the registry, $a1 = the stream, $a2 = the object) The extension chunk (sub_4C1600 type 3; version
// 0x35000..0x37002, else error 0x80000004). Its payload is a sequence of sub-chunks: each header (sub_4C1450),
// the entry with that plugin id, its read callback (stream, length, object, offset, size) or a skip
// (sub_4C5620) when the id has no entry or no reader; the length left drops by length + 12. Then every
// entry's always callback (object, offset, size); one that returns 0 -> 0. Returns the registry or 0.
// 0x004C5A50 sub_4C5A50 -- 468 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C5A50(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c5a50
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    a3 = addiu(sp, 0x58);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    a0 = s1;
    a1 = 3;
    a2 = addiu(sp, 0x5C);
    jal(ctx, 0x4C5A7Cu, gen::fn_sub_4C1600_004c1600);
    if (v0 == 0) {
        // 0x004c5afc: no extension chunk: 0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004c5a8c
        charge(ctx, 6);
        lw(v1, sp, 0x58);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x004c5aa4: the chunk's version
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_004c5be8;
            }
            // 0x004c5ab8
            charge(ctx, 3);
            lw(v0, sp, 0x5C);
            if (v0 != 0) {
                for (;;) {
                    // 0x004c5b04: the next sub-chunk's header
                    charge(ctx, 8);
                    a0 = s1;
                    a1 = addiu(sp, 0x54);
                    a2 = addiu(sp, 0x50);
                    a3 = 0;
                    t0 = 0;
                    jal(ctx, 0x4C5B14u, gen::fn_sub_4C1450_004c1450);
                    if (v0 == 0) {
                        goto L_004c5b24_11;
                    }
                    // 0x004c5b2c: the entry with its id
                    charge(ctx, 3);
                    lw(t0, s2, plugreg::kFirst);
                    if (t0 != 0) {
                        // 0x004c5b38
                        charge(ctx, 2);
                        lw(v1, sp, 0x54);
                        for (;;) {
                            // 0x004c5b40
                            charge(ctx, 3);
                            lw(v0, t0, plugentry::kPluginId);
                            if (v0 != v1) {
                                // 0x004c5b4c
                                charge(ctx, 3);
                                lw(t0, t0, plugentry::kNext);
                                if (t0 != 0) {
                                    backedge(ctx);
                                    continue;
                                }
                            }
                            break;
                        }
                    }
                    // 0x004c5b58
                    charge(ctx, 2);
                    if (t0 != 0) {
                        // 0x004c5b60: a reader?
                        charge(ctx, 3);
                        lw(v0, t0, plugentry::kReadCb);
                        if (v0 == 0) {
                            goto L_004c5bb4;
                        }
                        // 0x004c5b6c: read(stream, length, object, offset, size)
                        charge(ctx, 8);
                        lw(a3, t0, plugentry::kOffset);
                        a0 = s1;
                        lw(a1, sp, 0x50);
                        lw(t0, t0, plugentry::kSize);
                        a2 = s0;
                        jalr(ctx, 0x4C5B7Cu, v0.u());
                        if (v0 == 0) {
                            goto L_004c5b8c_19;
                        }
                    L_004c5b94:  // the length left
                        charge(ctx, 6);
                        lw(v0, sp, 0x50);
                        lw(v1, sp, 0x5C);
                        v0 = addiu(v0, 12);
                        v0 = subu(v1, v0);
                        sw(v0, sp, 0x5C);
                        if (v0 == 0) {
                            goto L_004c5bac_21;
                        }
                        backedge(ctx);
                        continue;
                    }
                L_004c5bb4:  // no reader: skip the payload
                    charge(ctx, 5);
                    lw(a1, sp, 0x50);
                    a0 = s1;
                    jal(ctx, 0x4C5BB8u, gen::fn_sub_4C5620_004c5620);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    goto L_004c5b94;
                }
                // 0x004c5bc8
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004c5ac4: the always callbacks
                charge(ctx, 1);
                lw(s1, s2, plugreg::kFirst);
            L_004c5ac8:  // each entry
                charge(ctx, 2);
                if (s1 != 0) {
                    for (;;) {
                        // 0x004c5ad0: always(object, offset, size)
                        charge(ctx, 3);
                        lw(v0, s1, plugentry::kAlwaysCb);
                        if (v0 != 0) {
                            // 0x004c5adc
                            charge(ctx, 6);
                            lw(a1, s1, plugentry::kOffset);
                            lw(a2, s1, plugentry::kSize);
                            a0 = s0;
                            jalr(ctx, 0x4C5AE4u, v0.u());
                            if (v0 != 0) {
                                goto L_004c5bd0;
                            }
                            goto L_004c5af4_8;
                        }
                    L_004c5bd0:  // the next entry
                        charge(ctx, 3);
                        lw(s1, s1, plugentry::kNext);
                        if (s1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004c5bdc
                    charge(ctx, 1);
                }
                // 0x004c5be0
                charge(ctx, 2);
                v0 = s2;
            }
            // 0x004c5c0c (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_004c5be8:  // a bad version: error 0x80000004
        charge(ctx, 9);
        v1 = 1;
        v0 = lui(0x8000);
        sw(v1, sp, 0x48);
        a0 = v0 | 0x4;
        jal(ctx, 0x4C5BF4u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x4C);
        a0 = addiu(sp, 0x48);
        jal(ctx, 0x4C5C00u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x004c5c0c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004c5af4_8:  // an always callback failed
    charge(ctx, 2);
    v0 = 0;
    // 0x004c5c0c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004c5b24_11:
    charge(ctx, 2);
    v0 = 0;
    // 0x004c5c0c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004c5b8c_19:
    charge(ctx, 2);
    v0 = 0;
    // 0x004c5c0c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004c5bac_21:  // the payload is used up: the always callbacks
    charge(ctx, 2);
    lw(s1, s2, plugreg::kFirst);
    backedge(ctx);
    goto L_004c5ac8;
}

// sub_4C5C30 [pluginRegistryInvokeRights] -- calls the rights callback of the plugin with a given id
// ($a0 = the registry, $a1 = the id, $a2 = the object) rights(object, offset, size); returns the registry when it
// succeeds, 0 when it fails or the id has no entry / no rights callback.
// 0x004C5C30 sub_4C5C30 -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C5C30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004c5c30
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    lw(v1, a0, plugreg::kFirst);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (v1 != 0) {
        for (;;) {
            // 0x004c5c48
            charge(ctx, 3);
            lw(v0, v1, plugentry::kPluginId);
            if (v0 != a1) {
                // 0x004c5c54
                charge(ctx, 3);
                lw(v1, v1, plugentry::kNext);
                if (v1 != 0) {
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x004c5c60
    charge(ctx, 2);
    if (v1 != 0) {
        // 0x004c5c68
        charge(ctx, 3);
        lw(v0, v1, plugentry::kRightsCb);
        if (v0 == 0) {
            goto L_004c5c90;
        }
        // 0x004c5c74
        charge(ctx, 7);
        a0 = a2;
        lw(a2, v1, plugentry::kSize);
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x4C5C7Cu);  // $ra = the return address
        lw(a1, v1, plugentry::kOffset);
        call_ptr(ctx, jt);
        if (v0 == 0) s0 = 0;
        v0 = s0;
        // 0x004c5c94 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_004c5c90:  // no entry or no callback: 0
    charge(ctx, 1);
    v0 = 0;
    // 0x004c5c94 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4C5CB0 [pluginRegistryGetSize] -- the bytes an object's extension chunk payload takes
// ($a0 = the registry, $a1 = the object) Sum over the entries with a size callback of size + 12 (a header) for
// each size above 0.
// 0x004C5CB0 sub_4C5CB0 -- 124 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C5CB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c5cb0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    lw(s0, a0, plugreg::kFirst);
    s1 = 0;
    if (s0 != 0) {
        for (;;) {
            // 0x004c5cd4
            charge(ctx, 3);
            lw(v0, s0, plugentry::kGetSizeCb);
            if (v0 != 0) {
                // 0x004c5ce0
                charge(ctx, 6);
                lw(a1, s0, plugentry::kOffset);
                lw(a2, s0, plugentry::kSize);
                a0 = s2;
                jalr(ctx, 0x4C5CE8u, v0.u());
                if (i64(v0) > 0) {
                    // 0x004c5cf8
                    charge(ctx, 2);
                    v0 = addiu(v0, 12);
                    s1 = addu(s1, v0);
                }
            }
            // 0x004c5d00
            charge(ctx, 3);
            lw(s0, s0, plugentry::kNext);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004c5d0c
        charge(ctx, 1);
    }
    // 0x004c5d10 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4C5D30 [pluginRegistryWriteDataChunks] -- writes an object's extension chunk (the plugins with data)
// ($a0 = the registry, $a1 = the stream, $a2 = the object) The payload size as sub_4C5CB0, the extension
// chunk's header (type 3, version 0x37002, build 0x37), then for each entry with a size and a writer and a
// size above 0: its header (its id, version 0x37002, build 0x37) and write(stream, length, object, offset,
// size). A failed header write -> 0, a failed plugin write ends the loop with 0. Returns the registry.
// 0x004C5D30 sub_4C5D30 -- 356 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C5D30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c5d30
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    lw(s0, a0, plugreg::kFirst);
    s1 = 0;
    if (s0 != 0) {
        for (;;) {
            // 0x004c5d64: size the payload
            charge(ctx, 3);
            lw(v0, s0, plugentry::kGetSizeCb);
            if (v0 != 0) {
                // 0x004c5d70
                charge(ctx, 6);
                lw(a1, s0, plugentry::kOffset);
                lw(a2, s0, plugentry::kSize);
                a0 = s2;
                jalr(ctx, 0x4C5D78u, v0.u());
                if (i64(v0) > 0) {
                    // 0x004c5d88
                    charge(ctx, 2);
                    v0 = addiu(v0, 12);
                    s1 = addu(s1, v0);
                }
            }
            // 0x004c5d90
            charge(ctx, 3);
            lw(s0, s0, plugentry::kNext);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004c5d9c
        charge(ctx, 1);
    }
    // 0x004c5da0: the extension chunk's header
    charge(ctx, 9);
    v0 = 0x30000;
    a2 = s1;
    a0 = s3;
    a1 = 3;
    t0 = 55;
    a3 = v0 | 0x7002;
    jal(ctx, 0x4C5DB4u, gen::fn_sub_4C15A0_004c15a0);
    if (v0 == 0) {
        // 0x004c5e54
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004c5dc4: each entry
        charge(ctx, 3);
        lw(s0, s4, plugreg::kFirst);
        if (s0 != 0) {
            for (;;) {
                // 0x004c5dd0
                charge(ctx, 3);
                lw(v1, s0, plugentry::kGetSizeCb);
                if (v1 != 0) {
                    // 0x004c5ddc: a writer?
                    charge(ctx, 3);
                    lw(v0, s0, plugentry::kWriteCb);
                    if (v0 == 0) {
                        goto L_004c5e64;
                    }
                    // 0x004c5de8
                    charge(ctx, 7);
                    lw(a1, s0, plugentry::kOffset);
                    lw(a2, s0, plugentry::kSize);
                    a0 = s2;
                    jalr(ctx, 0x4C5DF0u, v1.u());
                    s1 = v0;
                    if (i64(s1) <= 0) {
                        goto L_004c5e64;
                    }
                    // 0x004c5e04: its sub-chunk header
                    charge(ctx, 9);
                    lw(a1, s0, plugentry::kPluginId);
                    v0 = 0x30000;
                    a0 = s3;
                    a2 = s1;
                    a3 = v0 | 0x7002;
                    t0 = 55;
                    jal(ctx, 0x4C5E18u, gen::fn_sub_4C15A0_004c15a0);
                    if (v0 == 0) {
                        goto L_004c5e5c;
                    }
                    // 0x004c5e28: write(stream, length, object, offset, size)
                    charge(ctx, 9);
                    lw(a3, s0, plugentry::kOffset);
                    a1 = s1;
                    lw(t0, s0, plugentry::kSize);
                    a0 = s3;
                    lw(v0, s0, plugentry::kWriteCb);
                    a2 = s2;
                    jalr(ctx, 0x4C5E3Cu, v0.u());
                    if (v0 != 0) {
                        goto L_004c5e64;
                    }
                    goto L_004c5e4c_13;
                }
            L_004c5e64:  // the next entry
                charge(ctx, 3);
                lw(s0, s0, plugentry::kNext);
                if (s0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004c5e70
        charge(ctx, 1);
        v0 = s4;
    }
    // 0x004c5e74 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004c5e4c_13:  // a plugin write failed: 0
    charge(ctx, 2);
    v0 = 0;
    // 0x004c5e74 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004c5e5c:  // a header write failed: 0
    charge(ctx, 2);
    v0 = 0;
    // 0x004c5e74 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4C5EA0 [pluginRegistrySkipDataChunks] -- skips an extension chunk and all its sub-chunks
// ($a0 = a registry (returned), $a1 = the stream) The type-3 chunk, then each sub-chunk header and payload
// until the length is used up. Returns $a0, or 0 on a read / skip failure.
// 0x004C5EA0 sub_4C5EA0 -- 196 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C5EA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c5ea0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a3 = 0;
    sd(ra, sp, 0x20);
    a2 = addiu(sp, 0x3C);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = s0;
    a1 = 3;
    jal(ctx, 0x4C5EC4u, gen::fn_sub_4C1600_004c1600);
    if (v0 == 0) {
        // 0x004c5ee8
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004c5ed4
        charge(ctx, 3);
        lw(v0, sp, 0x3C);
        if (v0 != 0) {
            for (;;) {
                // 0x004c5ef0: the next sub-chunk
                charge(ctx, 8);
                a0 = s0;
                a1 = 0;
                a2 = addiu(sp, 0x38);
                a3 = 0;
                t0 = 0;
                jal(ctx, 0x4C5F00u, gen::fn_sub_4C1450_004c1450);
                if (v0 == 0) {
                    goto L_004c5f10_5;
                }
                // 0x004c5f18: skip its payload
                charge(ctx, 5);
                lw(a1, sp, 0x38);
                a0 = s0;
                jal(ctx, 0x4C5F1Cu, gen::fn_sub_4C5620_004c5620);
                if (v0 == 0) {
                    goto L_004c5f4c;
                }
                // 0x004c5f2c
                charge(ctx, 6);
                lw(v0, sp, 0x38);
                lw(v1, sp, 0x3C);
                v0 = addiu(v0, 12);
                v0 = subu(v1, v0);
                sw(v0, sp, 0x3C);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004c5f44
            charge(ctx, 2);
            backedge(ctx);
        }
        // 0x004c5ee0
        charge(ctx, 2);
        v0 = s1;
    }
    // 0x004c5f50 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_004c5f10_5:  // a header could not be read: 0
    charge(ctx, 2);
    v0 = 0;
    // 0x004c5f50 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_004c5f4c:  // a skip failed: 0
    charge(ctx, 1);
    v0 = 0;
    // 0x004c5f50 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4C5F70 [pluginModuleOpen] -- the plugin module's open: the free list of 60-byte plugin entries
// sub_4C3B60(60, the counts of 0x7CDD50 / 0x7CDD54, alignment 4, the static record 0x95FFE0, hint 0x40000) to
// gp 0x7CE908; the count of registries with entries 0x7CE904 = 0. Returns 1, or 0 without a free list.
// 0x004C5F70 sub_4C5F70 -- 76 bytes; frame 0x10: ra sp+0x0
void sub_4C5F70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c5f70
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = 0x960000;
    sd(ra, sp, 0x0);
    a0 = 60;
    lw(a1, gp, -20384);  // 0x7CDD50 (the plugin-entry free list: entries per block)
    a2 = 4;
    lw(a3, gp, -20380);  // 0x7CDD54 (the plugin-entry free list: preallocated blocks)
    t0 = addiu(t0, -32);  // &0x95FFE0 (the plugin-entry free list, static)
    t1 = 0x40000;
    jal(ctx, 0x4C5F90u, gen::fn_sub_4C3B60_004c3b60);
    sw(v0, gp, -17384);  // 0x7CE908 (the free list of plugin entries)
    if (v0 == 0) {
        // 0x004c5fac
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004c5fa0
        charge(ctx, 3);
        sw(zero, gp, -17388);  // 0x7CE904 (the registries with entries, count)
        v0 = 1;
    }
    // 0x004c5fb0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// sub_4C6000 [pluginModuleClose] -- the plugin module's close: every registry reset, the entries freed
// First sub_4C4200(entries, sub_4C5FC0, entries). When the free-list alloc slot is not the engine's own
// (0x4C3D10), every registry in the array 0x7CE900 has its entries freed one by one (slot 0x96018C) and,
// when it had entries, its size reset to the original and its first / last cleared; the array is freed
// (RwFree). Then the entry free list is destroyed (sub_4C3C30) and cleared. Returns 1.
// 0x004C6000 sub_4C6000 -- 320 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C6000(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c6000
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, gp, -17384);  // 0x7CE908 (the free list of plugin entries)
    if (a0 != 0) {
        // 0x004c6028: for all used entries: sub_4C5FC0
        charge(ctx, 10);
        a1 = 0x4C0000;
        a2 = a0;
        a1 = addiu(a1, 24512);  // &sub_4C5FC0
        jal(ctx, 0x4C6030u, gen::fn_sub_4C4200_004c4200);
        v0 = 0x960000;
        v1 = 0x4C0000;
        lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
        v1 = addiu(v1, 15632);  // &sub_4C3D10
        if (v0 != v1) {
            // 0x004c6050: a custom allocator: free the entries of each registry
            charge(ctx, 4);
            lw(v0, gp, -17388);  // 0x7CE904 (the registries with entries, count)
            at = sltu(0, v0);
            s4 = 0;
            if (at != 0) {
                // 0x004c6060
                charge(ctx, 3);
                s1 = 0x960000;
                s2 = 0;
                s1 = addiu(s1, 396);  // &0x96018C (free-list free slot)
                for (;;) {
                    // 0x004c606c: the next registry
                    charge(ctx, 6);
                    lw(v0, gp, -17392);  // 0x7CE900 (the registries with entries, array)
                    v0 = addu(v0, s2);
                    lw(v0, v0, 0);
                    lw(a1, v0, 16);
                    s3 = 0;
                    if (a1 != 0) {
                        // 0x004c6084
                        charge(ctx, 1);
                        lw(s3, a1, plugentry::kParent);
                    }
                    // 0x004c6088
                    charge(ctx, 2);
                    if (a1 != 0) {
                        for (;;) {
                            // 0x004c6090: free the next entry
                            charge(ctx, 7);
                            lw(s0, a1, plugentry::kNext);
                            lw(v0, s1, 0);
                            a0 = 0;
                            jalr(ctx, 0x4C6098u, v0.u());
                            a1 = s0;
                            if (s0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004c60ac
                        charge(ctx, 1);
                    }
                    // 0x004c60b0
                    charge(ctx, 2);
                    if (s3 != 0) {
                        // 0x004c60b8: it had entries:
                        charge(ctx, 3);
                        lw(v0, s3, plugreg::kFirst);
                        if (v0 != 0) {
                            // 0x004c60c4: the original size, no entries
                            charge(ctx, 5);
                            lw(v0, s3, plugreg::kOrigSize);
                            sw(v0, s3, plugreg::kSizeOfStruct);
                            sw(zero, s3, plugreg::kFirst);
                            sw(zero, s3, plugreg::kLast);
                        }
                    }
                    // 0x004c60d8
                    charge(ctx, 5);
                    lw(v0, gp, -17388);  // 0x7CE904 (the registries with entries, count)
                    s4 = addiu(s4, 1);
                    v0 = sltu(s4, v0);
                    s2 = addiu(s2, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004c60ec
                charge(ctx, 1);
            }
            // 0x004c60f0
            charge(ctx, 3);
            lw(a0, gp, -17392);  // 0x7CE900 (the registries with entries, array)
            if (a0 != 0) {
                // 0x004c60fc: free the registry array
                charge(ctx, 5);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                jalr(ctx, 0x4C6104u, v0.u());
                sw(zero, gp, -17392);  // 0x7CE900 (the registries with entries, array)
            }
        }
        // 0x004c6110: destroy the entry free list
        charge(ctx, 3);
        link(ctx, 0x4C6110u);  // $ra first: the delay slot below depends on it
        lw(a0, gp, -17384);  // 0x7CE908 (the free list of plugin entries)
        call(ctx, gen::fn_sub_4C3C30_004c3c30);
        sw(zero, gp, -17384);  // 0x7CE908 (the free list of plugin entries)
    }
    // 0x004c611c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    v0 = 1;
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4C6140 [pluginDefaultConstructor] -- the default plugin constructor: returns the object
// 0x004C6140 sub_4C6140 -- 8 bytes; leaf frame (no stack)
void sub_4C6140(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004c6140
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}

// sub_4C6150 [pluginDefaultDestructor] -- the default plugin destructor: returns the object
// 0x004C6150 sub_4C6150 -- 8 bytes; leaf frame (no stack)
void sub_4C6150(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004c6150
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}

// sub_4C6160 [pluginDefaultCopy] -- the default plugin copy: returns the destination
// 0x004C6160 sub_4C6160 -- 8 bytes; leaf frame (no stack)
void sub_4C6160(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004c6160
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}

// sub_4C61B0 [pluginRegistryAddPlugin] -- registers a plugin: its data offset in the object, its callbacks
// ($a0 = the registry, $a1 = the size, $a2 = the id, $a3 / $t0 / $t1 = constructor / destructor / copy, 0 for
// the defaults) -1 before the plugin module is open. After the engine has started (sub_4CA500): error
// 0x80000017 -> -1. With a custom free-list allocator the registry joins the array 0x7CE900 (grown by one:
// RwMalloc, copy, RwFree of the old array). An id already registered: error 0x80000017 and that entry's
// offset. A registry with a maximum that the new size (current + size rounded to 4) exceeds: -1. Else a
// 60-byte entry from the free list: offset = the old object size (which grows), size, id, no stream callbacks,
// the three callbacks, linked at the tail. Returns the plugin's offset (or -1).
// 0x004C61B0 sub_4C61B0 -- 768 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C61B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004c61b0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    s7 = t1;
    sq(s5, sp, 0x50);
    s6 = t0;
    sq(s4, sp, 0x40);
    s5 = a3;
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17384);  // 0x7CE908 (the free list of plugin entries)
    s2 = a2;
    if (v0 == 0) {
        // 0x004c62d0: no plugin module: -1
        charge(ctx, 2);
        v0 = si(-1);
    } else {
        // 0x004c61fc
        charge(ctx, 4);
        jal(ctx, 0x4C61FCu, gen::fn_sub_4CA500_004ca500);
        if (v0 != 0) {
            // 0x004c62d8: the engine has started: error 0x80000017
            charge(ctx, 10);
            v1 = 1;
            v0 = lui(0x8000);
            sw(v1, sp, 0xA8);
            a0 = v0 | 0x17;
            jal(ctx, 0x4C62E4u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0xAC);
            a0 = addiu(sp, 0xA8);
            jal(ctx, 0x4C62F0u, gen::fn_sub_4C1C50_004c1c50);
            v0 = si(-1);
        } else {
            // 0x004c620c: a custom free-list allocator?
            charge(ctx, 7);
            fp = 0x960000;
            v0 = 0x4C0000;
            fp = addiu(fp, 0x188);
            v0 = addiu(v0, 15632);  // &sub_4C3D10
            lw(v1, fp, 0x0);
            if (v1 != v0) {
                // 0x004c6228
                charge(ctx, 4);
                lw(v1, gp, -17388);  // 0x7CE904 (the registries with entries, count)
                at = sltu(0, v1);
                a1 = 0;
                if (at != 0) {
                    // 0x004c6238
                    charge(ctx, 1);
                    lw(a0, gp, -17392);  // 0x7CE900 (the registries with entries, array)
                    for (;;) {
                        // 0x004c623c: is the registry in the array?
                        charge(ctx, 3);
                        lw(v0, a0, 0);
                        if (s4 != v0) {
                            // 0x004c6248
                            charge(ctx, 4);
                            a1 = addiu(a1, 1);
                            v0 = sltu(a1, v1);
                            a0 = addiu(a0, 4);
                            if (v0 != 0) {
                                backedge(ctx);
                                continue;
                            }
                        }
                        break;
                    }
                }
                // 0x004c6258
                charge(ctx, 2);
                if (v1 == a1) {
                    // 0x004c6260: no: a longer array
                    charge(ctx, 10);
                    v0 = addiu(v1, 1);
                    a0 = sll(v0, 2);
                    v0 = 0x960000;
                    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                    a1 = 0x40000;
                    jalr(ctx, 0x4C6270u, v0.u());
                    s1 = v0;
                    lw(v0, gp, -17392);  // 0x7CE900 (the registries with entries, array)
                    s0 = 0;
                    if (v0 != 0) {
                        // 0x004c6288
                        charge(ctx, 4);
                        lw(v0, gp, -17388);  // 0x7CE904 (the registries with entries, count)
                        at = sltu(0, v0);
                        if (at != 0) {
                            // 0x004c6298
                            charge(ctx, 2);
                            a0 = 0;
                            v1 = s1;
                            for (;;) {
                                // 0x004c62a0: copy the old entries
                                charge(ctx, 10);
                                lw(v0, gp, -17392);  // 0x7CE900 (the registries with entries, array)
                                s0 = addiu(s0, 1);
                                v0 = addu(v0, a0);
                                lw(v0, v0, 0);
                                a0 = addiu(a0, 4);
                                sw(v0, v1, 0);
                                lw(v0, gp, -17388);  // 0x7CE904 (the registries with entries, count)
                                v0 = sltu(s0, v0);
                                v1 = addiu(v1, 4);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004c62c8
                            charge(ctx, 2);
                        }
                        // 0x004c6300: free the old array
                        charge(ctx, 4);
                        v0 = 0x960000;
                        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                        jt = v0.u();  // the target, read before the delay slot
                        link(ctx, 0x4C6308u);  // $ra = the return address
                        lw(a0, gp, -17392);  // 0x7CE900 (the registries with entries, array)
                        call_ptr(ctx, jt);
                    }
                    // 0x004c6310: append the registry
                    charge(ctx, 7);
                    v0 = sll(s0, 2);
                    v0 = addu(s1, v0);
                    sw(s4, v0, 0);
                    lw(v0, gp, -17388);  // 0x7CE904 (the registries with entries, count)
                    sw(s1, gp, -17392);  // 0x7CE900 (the registries with entries, array)
                    v0 = addiu(v0, 1);
                    sw(v0, gp, -17388);  // 0x7CE904 (the registries with entries, count)
                }
            }
            // 0x004c632c
            charge(ctx, 3);
            lw(s0, s4, plugreg::kFirst);
            if (s0 != 0) {
                for (;;) {
                    // 0x004c6338: an entry with this id?
                    charge(ctx, 3);
                    lw(v0, s0, plugentry::kPluginId);
                    if (v0 == s2) {
                        goto L_004c6344_19;
                    }
                    // 0x004c636c
                    charge(ctx, 3);
                    lw(s0, s0, plugentry::kNext);
                    if (s0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004c6378: the new object size
            charge(ctx, 7);
            a0 = addiu(s3, 3);
            v0 = si(-4);
            lw(v1, s4, plugreg::kSizeOfStruct);
            a0 = a0 & v0;
            lw(v0, s4, plugreg::kMaxSize);
            s0 = addu(v1, a0);
            if (v0 != 0) {
                // 0x004c6394
                charge(ctx, 3);
                at = slt(v0, s0);
                if (at == 0) {
                    goto L_004c63a8;
                }
                // 0x004c63a0
                charge(ctx, 2);
                v0 = si(-1);
                // 0x004c6480 (the shared epilogue, written out on this path)
                charge(ctx, 12);
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
                return;
            }
        L_004c63a8:  // fits: an entry from the free list
            charge(ctx, 6);
            lw(v0, fp, 0x0);
            lw(a0, gp, -17384);  // 0x7CE908 (the free list of plugin entries)
            a1 = 0x40000;
            jalr(ctx, 0x4C63B0u, v0.u());
            if (v0 == 0) {
                // 0x004c647c
                charge(ctx, 1);
                v0 = si(-1);
            } else {
                // 0x004c63c0: the entry: offset, size, id, no stream callbacks
                charge(ctx, 11);
                lw(v1, s4, plugreg::kSizeOfStruct);
                sw(v1, v0, 0);
                sw(s0, s4, plugreg::kSizeOfStruct);
                sw(s3, v0, plugentry::kSize);
                sw(s2, v0, plugentry::kPluginId);
                sw(zero, v0, plugentry::kReadCb);
                sw(zero, v0, plugentry::kWriteCb);
                sw(zero, v0, plugentry::kGetSizeCb);
                sw(zero, v0, plugentry::kAlwaysCb);
                sw(zero, v0, plugentry::kRightsCb);
                if (s5 == 0) {
                    // 0x004c63f4
                    charge(ctx, 3);
                    s5 = 0x4C0000;
                    s5 = addiu(s5, 24896);  // &sub_4C6140
                    sw(s5, v0, plugentry::kConstructCb);
                } else {
                    // 0x004c63ec: the constructor (or the default)
                    charge(ctx, 2);
                    sw(s5, v0, plugentry::kConstructCb);
                }
                // 0x004c6400
                charge(ctx, 2);
                if (s6 == 0) {
                    // 0x004c6410
                    charge(ctx, 3);
                    s6 = 0x4C0000;
                    s6 = addiu(s6, 24912);  // &sub_4C6150
                    sw(s6, v0, plugentry::kDestructCb);
                } else {
                    // 0x004c6408: the destructor (or the default)
                    charge(ctx, 2);
                    sw(s6, v0, plugentry::kDestructCb);
                }
                // 0x004c641c
                charge(ctx, 2);
                if (s7 == 0) {
                    // 0x004c642c
                    charge(ctx, 3);
                    s7 = 0x4C0000;
                    s7 = addiu(s7, 24928);  // &sub_4C6160
                    sw(s7, v0, plugentry::kCopyCb);
                } else {
                    // 0x004c6424: the copy (or the default)
                    charge(ctx, 2);
                    sw(s7, v0, plugentry::kCopyCb);
                }
                // 0x004c6438
                charge(ctx, 7);
                sw(zero, v0, plugentry::kErrStrCb);
                sw(zero, v0, plugentry::kNext);
                sw(zero, v0, plugentry::kPrev);
                sw(s4, v0, plugentry::kParent);
                lw(v1, s4, plugreg::kFirst);
                if (v1 == 0) {
                    // 0x004c6470: the first entry
                    charge(ctx, 3);
                    sw(v0, s4, plugreg::kFirst);
                    sw(v0, s4, plugreg::kLast);
                    backedge(ctx);
                } else {
                    // 0x004c6454: linked at the tail
                    charge(ctx, 5);
                    lw(v1, s4, plugreg::kLast);
                    sw(v0, v1, 48);
                    lw(v1, s4, plugreg::kLast);
                    sw(v1, v0, plugentry::kPrev);
                    sw(v0, s4, plugreg::kLast);
                }
                // 0x004c6468
                charge(ctx, 2);
                lw(v0, v0, 0);
            }
        }
    }
    // 0x004c6480 (the shared epilogue, written out on this path)
    charge(ctx, 12);
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
    return;
L_004c6344_19:  // already registered: error 0x80000017, its offset
    charge(ctx, 10);
    v1 = 1;
    v0 = lui(0x8000);
    sw(v1, sp, 0xA0);
    a0 = v0 | 0x17;
    jal(ctx, 0x4C6350u, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0xA4);
    a0 = addiu(sp, 0xA0);
    jal(ctx, 0x4C635Cu, gen::fn_sub_4C1C50_004c1c50);
    lw(v0, s0, plugentry::kOffset);
    // 0x004c6480 (the shared epilogue, written out on this path)
    charge(ctx, 12);
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

// sub_4C64B0 [pluginRegistryInitObject] -- runs every plugin constructor on an object (unwinds on failure)
// ($a0 = the registry, $a1 = the object) constructor(object, offset, size) in order; one that returns 0 makes
// the entries before it run their destructors backwards, and the result is 0. Returns the registry.
// 0x004C64B0 sub_4C64B0 -- 164 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C64B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c64b0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(s0, a0, plugreg::kFirst);
    s1 = a1;
    if (s0 != 0) {
        for (;;) {
            // 0x004c64d4: construct
            charge(ctx, 7);
            lw(a1, s0, plugentry::kOffset);
            lw(a2, s0, plugentry::kSize);
            lw(v0, s0, plugentry::kConstructCb);
            a0 = s1;
            jalr(ctx, 0x4C64E0u, v0.u());
            if (v0 == 0) {
                goto L_004c64f0_2;
            }
            // 0x004c6524
            charge(ctx, 3);
            lw(s0, s0, plugentry::kNext);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004c6530
    charge(ctx, 2);
    v0 = s2;
    // 0x004c653c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_004c64f0_2:  // a constructor failed: unwind
    charge(ctx, 3);
    lw(s0, s0, plugentry::kPrev);
    if (s0 == 0) {
        // 0x004c6538
        charge(ctx, 1);
        v0 = 0;
    } else {
        for (;;) {
            // 0x004c64fc: destruct the earlier ones, backwards
            charge(ctx, 8);
            lw(a1, s0, plugentry::kOffset);
            lw(a2, s0, plugentry::kSize);
            lw(v0, s0, plugentry::kDestructCb);
            a0 = s1;
            jalr(ctx, 0x4C6508u, v0.u());
            lw(s0, s0, plugentry::kPrev);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004c651c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004c653c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4C6560 [pluginRegistryDeInitObject] -- runs every plugin destructor on an object, last first; returns the
//   registry
// 0x004C6560 sub_4C6560 -- 100 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C6560(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c6560
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(s0, a0, plugreg::kLast);
    s1 = a1;
    if (s0 != 0) {
        for (;;) {
            // 0x004c6584: destruct(object, offset, size)
            charge(ctx, 8);
            lw(a1, s0, plugentry::kOffset);
            lw(a2, s0, plugentry::kSize);
            lw(v0, s0, plugentry::kDestructCb);
            a0 = s1;
            jalr(ctx, 0x4C6590u, v0.u());
            lw(s0, s0, plugentry::kPrev);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004c65a4
        charge(ctx, 1);
    }
    // 0x004c65a8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4C65D0 [pluginRegistryCopyObject] -- runs every plugin copy (dst, src); returns the registry
// 0x004C65D0 sub_4C65D0 -- 112 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C65D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c65d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    lw(s0, a0, plugreg::kFirst);
    s1 = a2;
    if (s0 != 0) {
        for (;;) {
            // 0x004c65fc: copy(dst, src, offset, size)
            charge(ctx, 9);
            lw(a2, s0, plugentry::kOffset);
            a0 = s2;
            lw(a3, s0, plugentry::kSize);
            lw(v0, s0, plugentry::kCopyCb);
            a1 = s1;
            jalr(ctx, 0x4C660Cu, v0.u());
            lw(s0, s0, plugentry::kNext);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004c6620 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = s3;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4D0C30 [texDictCreate] -- creates an empty texture dictionary (linked into the module's list)
// A record from the dictionary free list (slot 0x960188, hint 0x30016): RwObject type 6, no parent, linked at
// the head of the module's dictionary list (+16 / +20), an empty texture list (+8 / +12), then the dictionary
// plugins' constructors. Returns the dictionary or 0.
// 0x004D0C30 sub_4D0C30 -- 212 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4D0C30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004d0c30
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x30000;
    sq(s0, sp, 0x0);
    a1 = v0 | 0x16;
    lw(a0, gp, -17312);  // 0x7CE950 (the texture module offset)
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = 0x960000;
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    v1 = addu(v1, a0);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4D0C5Cu);  // $ra = the return address
    lw(a0, v1, 12);
    call_ptr(ctx, jt);
    s0 = v0;
    if (s0 == 0) {
        // 0x004d0cf0: no memory: 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004d0c70: type 6, linked into the module's list, empty
        charge(ctx, 32);
        v0 = 6;
        a3 = 0x960000;
        sb(v0, s0, 0);
        a0 = 0x780000;
        sb(zero, s0, 1);
        a3 = addiu(a3, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        sb(zero, s0, 2);
        a2 = addiu(s0, 16);
        sb(zero, s0, 3);
        v0 = addiu(s0, 8);
        sw(zero, s0, rwobj::kParent);
        a0 = addiu(a0, -6416);  // &0x77E6F0 (the RwTexDictionary plugin registry)
        lw(v1, gp, -17312);  // 0x7CE950 (the texture module offset)
        a1 = s0;
        v1 = addu(a3, v1);
        lw(v1, v1, 0);
        sw(v1, s0, rwtexdict::kLink);
        lw(v1, gp, -17312);  // 0x7CE950 (the texture module offset)
        v1 = addu(a3, v1);
        sw(v1, s0, rwtexdict::kLinkPrev);
        lw(v1, gp, -17312);  // 0x7CE950 (the texture module offset)
        v1 = addu(a3, v1);
        lw(v1, v1, 0);
        sw(a2, v1, 4);
        lw(v1, gp, -17312);  // 0x7CE950 (the texture module offset)
        v1 = addu(a3, v1);
        sw(a2, v1, 0);
        sw(v0, s0, rwtexdict::kTextures);
        link(ctx, 0x4D0CE0u);  // $ra first: the delay slot below depends on it
        sw(v0, s0, rwtexdict::kTexturesPrev);
        call(ctx, gen::fn_sub_4C64B0_004c64b0);
        v0 = s0;
    }
    // 0x004d0cf4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4D0D10 [texDictDestroy] -- destroys a texture dictionary and every texture in it
// Not current any more if it was; each texture destroyed (sub_4D0DC0 with sub_4D0F00), the plugins'
// destructors, out of the module's list, back to the free list. Returns 1.
// 0x004D0D10 sub_4D0D10 -- 176 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4D0D10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d0d10
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s0, sp, 0x0);
    lw(v1, gp, -17312);  // 0x7CE950 (the texture module offset)
    s0 = a0;
    v0 = addu(v0, v1);
    v1 = addiu(v0, 16);
    lw(v0, v0, 16);
    if (v0 == s0) {
        // 0x004d0da8: it was the current dictionary
        charge(ctx, 2);
        sw(zero, v1, 0);
        backedge(ctx);
    }
    // 0x004d0d40: destroy its textures, its plugins, unlink, free
    charge(ctx, 26);
    a1 = 0x4D0000;
    a0 = s0;
    a1 = addiu(a1, 3840);  // &sub_4D0F00
    a2 = 0;
    jal(ctx, 0x4D0D4Cu, gen::fn_sub_4D0DC0_004d0dc0);
    a0 = 0x780000;
    a1 = s0;
    a0 = addiu(a0, -6416);  // &0x77E6F0 (the RwTexDictionary plugin registry)
    jal(ctx, 0x4D0D5Cu, gen::fn_sub_4C6560_004c6560);
    lw(a2, s0, rwtexdict::kLink);
    v1 = 0x960000;
    lw(a0, s0, rwtexdict::kLinkPrev);
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = 0x960000;
    sw(a2, a0, 0);
    lw(a2, s0, rwtexdict::kLinkPrev);
    lw(a0, s0, rwtexdict::kLink);
    sw(a2, a0, 4);
    lw(a0, gp, -17312);  // 0x7CE950 (the texture module offset)
    lw(v0, v0, 396);  // 0x96018C (free-list free slot)
    v1 = addu(v1, a0);
    lw(a0, v1, 12);
    a1 = s0;
    jalr(ctx, 0x4D0D98u, v0.u());
    v0 = 1;
    // 0x004d0db0
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4D0DC0 [texDictForAllTextures] -- calls a callback on each texture of a dictionary until it returns 0
// ($a0 = the dictionary, $a1 = callback(texture, data), $a2 = data) The next link is read before each call (the
// callback may destroy its texture); the texture is the link - 8. Returns the dictionary.
// 0x004D0DC0 sub_4D0DC0 -- 124 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4D0DC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d0dc0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    lw(v0, a0, rwtexdict::kTextures);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s2 = a2;
    s1 = addiu(s4, 8);
    sq(s0, sp, 0x0);
    if (v0 != s1) {
        for (;;) {
            // 0x004d0df4: callback(texture, data)
            charge(ctx, 6);
            lw(s0, v0, 0);
            a0 = addiu(v0, -8);
            a1 = s2;
            jalr(ctx, 0x4D0DFCu, s3.u());
            if (v0 == 0) {
                break;
            }
            // 0x004d0e0c
            charge(ctx, 2);
            v0 = s0;
            if (s0 == s1) {
                goto L_004d0e14_3;
            }
            backedge(ctx);
        }
    }
    // 0x004d0e18 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = s4;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004d0e14_3:  // the end of the list
    charge(ctx, 1);
    // 0x004d0e18 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = s4;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4D0E40 [textureCreate] -- creates a texture over a raster
// ($a0 = the raster) A record from the texture free list (hint 0x30006): no dictionary, empty name and mask, one
// reference, filter 1 with wrap addressing in u and v (0x1101), then the texture plugins' constructors.
// Returns the texture or 0.
// 0x004D0E40 sub_4D0E40 -- 184 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4D0E40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004d0e40
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 0x30000;
    sd(ra, sp, 0x20);
    a1 = v1 | 0x6;
    sq(s1, sp, 0x10);
    v0 = 0x960000;
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a2, gp, -17312);  // 0x7CE950 (the texture module offset)
    a0 = 0x960000;
    a0 = addiu(a0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    v1 = addu(a0, a2);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4D0E74u);  // $ra = the return address
    lw(a0, v1, 8);
    call_ptr(ctx, jt);
    s0 = v0;
    if (s0 != 0) {
        // 0x004d0e88: the fields, then the plugins
        charge(ctx, 22);
        sw(zero, s0, rwtex::kDict);
        v0 = lui(0xFFFF);
        sb(zero, s0, rwtex::kName);
        v1 = v0 | 0xFF;
        sb(zero, s0, rwtex::kMask);
        a0 = 1;
        sw(s1, s0, rwtex::kRaster);
        v0 = si(-256);
        sw(a0, s0, rwtex::kRefCount);
        a1 = s0;
        sw(zero, s0, rwtex::kFilterAddressing);
        a0 = 0x780000;
        lw(a2, s0, rwtex::kFilterAddressing);
        a0 = addiu(a0, -6448);  // &0x77E6D0 (the RwTexture plugin registry)
        v1 = a2 & v1;
        v1 = v1 | 0x1100;
        sw(v1, s0, rwtex::kFilterAddressing);
        lw(v1, s0, rwtex::kFilterAddressing);
        v0 = v1 & v0;
        v0 = v0 | 0x1;
        link(ctx, 0x4D0ED8u);  // $ra first: the delay slot below depends on it
        sw(v0, s0, rwtex::kFilterAddressing);
        call(ctx, gen::fn_sub_4C64B0_004c64b0);
    }
    // 0x004d0ee0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4D0F00 [textureDestroy] -- drops a texture reference; the last one destroys it
// The count goes down; at 0 or below: the texture plugins' destructors, out of its dictionary, its raster destroyed
// (sub_4CDE90), back to the free list (the count is raised for the destructors and lowered
// again). Returns 1.
// 0x004D0F00 sub_4D0F00 -- 204 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4D0F00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d0f00
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 1;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, rwtex::kRefCount);
    v1 = addiu(v1, -1);
    sw(v1, a0, rwtex::kRefCount);
    lw(v1, a0, rwtex::kRefCount);
    s0 = a0;
    if (i64(v1) <= 0) {
        // 0x004d0f30: the last reference
        charge(ctx, 9);
        v0 = addiu(v1, 1);
        a0 = 0x780000;
        a0 = addiu(a0, -6448);  // &0x77E6D0 (the RwTexture plugin registry)
        sw(v0, s0, rwtex::kRefCount);
        a1 = s0;
        jal(ctx, 0x4D0F40u, gen::fn_sub_4C6560_004c6560);
        lw(v0, s0, rwtex::kDict);
        if (v0 != 0) {
            // 0x004d0fa4: in a dictionary: unlink
            charge(ctx, 7);
            lw(v1, s0, rwtex::kDictNext);
            lw(v0, s0, rwtex::kDictPrev);
            sw(v1, v0, 0);
            lw(v1, s0, rwtex::kDictPrev);
            lw(v0, s0, rwtex::kDictNext);
            sw(v1, v0, 4);
            backedge(ctx);
        }
        // 0x004d0f54
        charge(ctx, 3);
        lw(a0, s0, rwtex::kRaster);
        if (a0 != 0) {
            // 0x004d0f60: destroy the raster
            charge(ctx, 3);
            jal(ctx, 0x4D0F60u, gen::fn_sub_4CDE90_004cde90);
            sw(zero, s0, rwtex::kRaster);
        }
        // 0x004d0f6c: back to the texture free list
        charge(ctx, 14);
        lw(a0, s0, rwtex::kRefCount);
        v1 = 0x960000;
        v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = 0x960000;
        a0 = addiu(a0, -1);
        sw(a0, s0, rwtex::kRefCount);
        lw(a0, gp, -17312);  // 0x7CE950 (the texture module offset)
        lw(v0, v0, 396);  // 0x96018C (free-list free slot)
        v1 = addu(v1, a0);
        lw(a0, v1, 8);
        a1 = s0;
        jalr(ctx, 0x4D0F94u, v0.u());
        v0 = 1;
        backedge(ctx);
    }
    // 0x004d0f28
    charge(ctx, 2);
    ld(ra, sp, 0x10);
    // 0x004d0fc0
    charge(ctx, 3);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4D1070 [textureSetMaskName] -- copies a texture's mask name (32 bytes, NUL forced on overflow)
// strncpy (the string slot 0x960140) into +48; a name of 32 or more characters (strlen slot 0x960164) is error
// 0x8000001E and the last byte is cleared. Returns the texture.
// 0x004D1070 sub_4D1070 -- 156 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4D1070(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d1070
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x960000;
    sd(ra, sp, 0x20);
    a2 = 32;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, v0, 320);  // 0x960140 (the string function strncpy)
    s0 = a1;
    a0 = addiu(s1, 48);
    jalr(ctx, 0x4D1094u, v0.u());
    v0 = 0x960000;
    lw(v0, v0, 356);  // 0x960164 (the string function strlen)
    a0 = s0;
    jalr(ctx, 0x4D10A4u, v0.u());
    at = sltiu(v0, 32);
    if (at == 0) {
        // 0x004d10c0: too long: error, terminate
        charge(ctx, 14);
        lb(t0, s0, 31);
        v0 = 1;
        sw(v0, sp, 0x38);
        a1 = s0;
        v0 = lui(0x8000);
        a2 = 32;
        a0 = v0 | 0x1E;
        a3 = 31;
        jal(ctx, 0x4D10DCu, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x3C);
        a0 = addiu(sp, 0x38);
        jal(ctx, 0x4D10E8u, gen::fn_sub_4C1C50_004c1c50);
        sb(zero, s1, rwtex::kMaskLast);
        backedge(ctx);
    }
    // 0x004d10b8
    charge(ctx, 2);
    v0 = s1;
    // 0x004d10f8
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4D1110 [texDictAddTexture] -- moves a texture into a dictionary (at the head of its list)
// ($a0 = the dictionary, $a1 = the texture) Unlinked from its old dictionary first. Returns the texture.
// 0x004D1110 sub_4D1110 -- 92 bytes; leaf frame (no stack)
void sub_4D1110(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x004d1110
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a1, rwtex::kDict);
    if (v0 != 0) {
        // 0x004d1148: unlink from the old dictionary
        charge(ctx, 7);
        lw(v1, a1, rwtex::kDictNext);
        lw(v0, a1, rwtex::kDictPrev);
        sw(v1, v0, 0);
        lw(v1, a1, rwtex::kDictPrev);
        lw(v0, a1, rwtex::kDictNext);
        sw(v1, v0, 4);
        backedge(ctx);
    }
    // 0x004d111c: link at the head
    charge(ctx, 11);
    sw(a0, a1, rwtex::kDict);
    v1 = addiu(a0, 8);
    lw(a3, a0, rwtexdict::kTextures);
    a2 = addiu(a1, 8);
    v0 = a1;
    sw(a3, a1, rwtex::kDictNext);
    sw(v1, a1, rwtex::kDictPrev);
    lw(v1, a0, rwtexdict::kTextures);
    sw(a2, v1, 4);
    sw(a2, a0, rwtexdict::kTextures);
    // 0x004d1164
    charge(ctx, 2);
}

// sub_4D1170 [texDictFindNamedTexture] -- finds a texture in a dictionary by name (sub_4D09D0 compares)
// ($a0 = the dictionary, $a1 = the name) Returns the texture or 0.
// 0x004D1170 sub_4D1170 -- 96 bytes; frame 0x10: ra sp+0x0
void sub_4D1170(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d1170
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = addiu(a0, 8);
    sd(ra, sp, 0x0);
    lw(t1, a0, 8);
    t3 = a1;
    if (t1 != t0) {
        for (;;) {
            // 0x004d1188
            charge(ctx, 4);
            t2 = addiu(t1, -8);
            a0 = addiu(t2, 16);
            if (a0 != 0) {
                // 0x004d11b0
                charge(ctx, 4);
                a1 = t3;
                jal(ctx, 0x4D11B0u, gen::fn_sub_4D09D0_004d09d0);
                if (v0 != 0) {
                    break;
                }
                backedge(ctx);
                goto L_004d1198;
            }
        L_004d1198:
            charge(ctx, 4);
            lw(t1, t1, 0);
            if (t1 == t0) {
                goto L_004d11a8;
            }
            backedge(ctx);
        }
        // 0x004d11c0
        charge(ctx, 1);
        v0 = t2;
        // 0x004d11c4 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_004d11a8:  // not found: 0
    charge(ctx, 2);
    v0 = 0;
    // 0x004d11c4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// sub_4D11F0 [texDictGetCurrent] -- returns the module's current texture dictionary
// 0x004D11F0 sub_4D11F0 -- 24 bytes; leaf frame (no stack)
void sub_4D11F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, gp{ctx, 28};
    // 0x004d11f0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, gp, -17312);  // 0x7CE950 (the texture module offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = addu(v0, v1);
    lw(v0, v0, 16);
}

// sub_4D1210 [textureGenerateMipName] -- calls the module's callback +48 if set (else 0)
// 0x004D1210 sub_4D1210 -- 68 bytes; frame 0x10: ra sp+0x0
void sub_4D1210(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d1210
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x960000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    lw(v1, gp, -17312);  // 0x7CE950 (the texture module offset)
    v0 = addu(v0, v1);
    lw(v0, v0, texmod::kCb48);
    if (v0 == 0) {
        // 0x004d1244
        charge(ctx, 2);
        v0 = 0;
        ld(ra, sp, 0x0);
    } else {
        // 0x004d1234
        charge(ctx, 4);
        jalr(ctx, 0x4D1234u, v0.u());
        ld(ra, sp, 0x0);
    }
    // 0x004d124c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// sub_4D13B0 [textureRegisterPlugin] -- registers a texture plugin (sub_4C61B0 on the texture registry)
// 0x004D13B0 sub_4D13B0 -- 44 bytes; leaf frame (no stack)
void sub_4D13B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x004d13b0
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = a1;
    v1 = a2;
    a1 = a0;
    a2 = v0;
    v0 = a3;
    t1 = t0;
    a0 = 0x780000;
    a3 = v1;
    t0 = v0;
    a0 = addiu(a0, -6448);  // &0x77E6D0 (the RwTexture plugin registry)
    gen::fn_sub_4C61B0_004c61b0(ctx);  // tail call
}

// sub_4D1420 [textureModuleClose] -- the texture module's close: scratch block, own dictionary, free lists
// The scratch block is freed; with both free lists, the module's own dictionary (0x7CE948), when it is still
// in the list, is destroyed as sub_4D0D10 does; then both free lists are destroyed; the count goes down.
// 0x004D1420 sub_4D1420 -- 448 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4D1420(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d1420
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x960000;
    sd(ra, sp, 0x20);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v1, gp, -17312);  // 0x7CE950 (the texture module offset)
    v0 = addu(v0, v1);
    lw(a0, v0, texmod::kScratch);
    if (a0 != 0) {
        // 0x004d1450: free the scratch block
        charge(ctx, 10);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x4D1458u, v0.u());
        lw(v1, gp, -17312);  // 0x7CE950 (the texture module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        sw(zero, v0, texmod::kScratch);
        sh(zero, v0, texmod::kScratchSize);
    }
    // 0x004d1478
    charge(ctx, 7);
    lw(v1, gp, -17312);  // 0x7CE950 (the texture module offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    a1 = addu(v0, v1);
    lw(v0, a1, texmod::kTexFreeList);
    if (v0 != 0) {
        // 0x004d1494
        charge(ctx, 3);
        lw(v0, a1, texmod::kDictFreeList);
        if (v0 != 0) {
            // 0x004d14a0
            charge(ctx, 3);
            lw(v0, a1, texmod::kDicts);
            if (v0 != a1) {
                // 0x004d14ac: is the module's own dictionary still listed?
                charge(ctx, 1);
                lw(a0, gp, -17320);  // 0x7CE948 (the default texture dictionary)
                for (;;) {
                    // 0x004d14b0
                    charge(ctx, 4);
                    lw(v1, v0, texmod::kDicts);
                    v0 = addiu(v0, -16);
                    if (v0 == a0) {
                        goto L_004d14c0_7;
                    }
                    // 0x004d1548
                    charge(ctx, 2);
                    v0 = v1;
                    if (v1 != a1) {
                        backedge(ctx);
                        continue;
                    }
                    break;
                }
            }
        }
    }
L_004d1550:  // the free lists
    charge(ctx, 3);
    lw(a0, a1, texmod::kTexFreeList);
    if (a0 != 0) {
        // 0x004d155c: destroy the texture free list
        charge(ctx, 7);
        jal(ctx, 0x4D155Cu, gen::fn_sub_4C3C30_004c3c30);
        lw(v1, gp, -17312);  // 0x7CE950 (the texture module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        sw(zero, v0, texmod::kTexFreeList);
    }
    // 0x004d1578
    charge(ctx, 7);
    lw(v1, gp, -17312);  // 0x7CE950 (the texture module offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = addu(v0, v1);
    lw(a0, v0, texmod::kDictFreeList);
    if (a0 != 0) {
        // 0x004d1594: destroy the dictionary free list
        charge(ctx, 7);
        jal(ctx, 0x4D1594u, gen::fn_sub_4C3C30_004c3c30);
        lw(v1, gp, -17312);  // 0x7CE950 (the texture module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        sw(zero, v0, texmod::kDictFreeList);
    }
    // 0x004d15b0
    charge(ctx, 5);
    lw(v1, gp, -17308);  // 0x7CE954 (the texture module open count)
    v0 = s1;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17308);  // 0x7CE954 (the texture module open count)
    // 0x004d15cc
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
L_004d14c0_7:  // found: destroy it (as sub_4D0D10)
    charge(ctx, 4);
    lw(s0, gp, -17320);  // 0x7CE948 (the default texture dictionary)
    lw(v0, a1, texmod::kCurrentDict);
    v1 = addiu(a1, 16);
    if (v0 == s0) {
        // 0x004d15c4
        charge(ctx, 2);
        sw(zero, v1, 0);
        backedge(ctx);
    }
    // 0x004d14d0
    charge(ctx, 30);
    a1 = 0x4D0000;
    a0 = s0;
    a1 = addiu(a1, 3840);  // &sub_4D0F00
    a2 = 0;
    jal(ctx, 0x4D14DCu, gen::fn_sub_4D0DC0_004d0dc0);
    a0 = 0x780000;
    a1 = s0;
    a0 = addiu(a0, -6416);  // &0x77E6F0 (the RwTexDictionary plugin registry)
    jal(ctx, 0x4D14ECu, gen::fn_sub_4C6560_004c6560);
    lw(a2, s0, rwtexdict::kLink);
    v1 = 0x960000;
    lw(a0, s0, rwtexdict::kLinkPrev);
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = 0x960000;
    sw(a2, a0, 0);
    lw(a2, s0, rwtexdict::kLinkPrev);
    lw(a0, s0, rwtexdict::kLink);
    sw(a2, a0, 4);
    lw(a0, gp, -17312);  // 0x7CE950 (the texture module offset)
    lw(v0, v0, 396);  // 0x96018C (free-list free slot)
    v1 = addu(v1, a0);
    lw(a0, v1, 12);
    a1 = s0;
    jalr(ctx, 0x4D1528u, v0.u());
    lw(v1, gp, -17312);  // 0x7CE950 (the texture module offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sw(zero, gp, -17320);  // 0x7CE948 (the default texture dictionary)
    a1 = addu(v0, v1);
    goto L_004d1550;
}

// sub_4D15E0 [textureModuleOpen] -- the texture module's open: free lists, its own dictionary, the callbacks
// ($a1 = the offset, at 0x7CE950) The texture free list (entry size = the texture registry's, static record
// 0x964160, hint 0x40006), the dictionary free list (static 0x964130, hint 0x40108), an empty dictionary list,
// the open counted, a dictionary created inline (as sub_4D0C30) which becomes current and the module's own
// (0x7CE948), and the default callbacks (+20 sub_4D05F0, +24 sub_4D0AC0, +44 sub_4D0640, +48 sub_4CF5C0).
// A failure destroys what was made. Returns $a0 or 0.
// 0x004D15E0 sub_4D15E0 -- 596 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4D15E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004d15e0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    t0 = 0x960000;
    sd(ra, sp, 0x20);
    v0 = 0x780000;
    sq(s1, sp, 0x10);
    a2 = 4;
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, v0, -6448);  // 0x77E6D0 (the RwTexture plugin registry)
    t0 = addiu(t0, 16736);  // &0x964160 (the texture free list, static)
    sw(a1, gp, -17312);  // 0x7CE950 (the texture module offset)
    lw(a1, gp, -20312);  // 0x7CDD98 (the texture free list: entries per block)
    lw(a3, gp, -20308);  // 0x7CDD9C (the texture free list: preallocated blocks)
    v0 = 0x40000;
    t1 = v0 | 0x6;
    jal(ctx, 0x4D1618u, gen::fn_sub_4C3B60_004c3b60);
    lw(a0, gp, -17312);  // 0x7CE950 (the texture module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = addu(v1, a0);
    sw(v0, v1, 8);
    lw(v0, v1, 8);
    if (v0 != 0) {
        // 0x004d1648: the dictionary free list
        charge(ctx, 18);
        v0 = 0x780000;
        t0 = 0x960000;
        lw(a0, v0, -6416);  // 0x77E6F0 (the RwTexDictionary plugin registry)
        a2 = 4;
        lw(a1, gp, -20304);  // 0x7CDDA0 (the texture-dictionary free list: entries per block)
        t0 = addiu(t0, 16688);  // &0x964130 (the texture-dictionary free list, static)
        lw(a3, gp, -20300);  // 0x7CDDA4 (the texture-dictionary free list: preallocated blocks)
        v0 = 0x40000;
        t1 = v0 | 0x408;
        jal(ctx, 0x4D1668u, gen::fn_sub_4C3B60_004c3b60);
        lw(v1, gp, -17312);  // 0x7CE950 (the texture module offset)
        a2 = 0x960000;
        a2 = addiu(a2, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v1 = addu(a2, v1);
        sw(v0, v1, 12);
        lw(v0, v1, 12);
        if (v0 == 0) {
            // 0x004d17b8: none: destroy the texture free list
            charge(ctx, 9);
            link(ctx, 0x4D17B8u);  // $ra first: the delay slot below depends on it
            lw(a0, v1, 8);
            call(ctx, gen::fn_sub_4C3C30_004c3c30);
            lw(a0, gp, -17312);  // 0x7CE950 (the texture module offset)
            v1 = 0x960000;
            v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            v0 = 0;
            v1 = addu(v1, a0);
            sw(zero, v1, 8);
        } else {
            // 0x004d1690: an empty dictionary list; a dictionary
            charge(ctx, 16);
            lw(a0, gp, -17312);  // 0x7CE950 (the texture module offset)
            v0 = 0x30000;
            sw(v1, v1, 0);
            a1 = v0 | 0x16;
            lw(v1, gp, -17308);  // 0x7CE954 (the texture module open count)
            v0 = 0x960000;
            a0 = addu(a2, a0);
            sw(a0, a0, 4);
            lw(a0, a0, 12);
            v1 = addiu(v1, 1);
            lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x4D16BCu);  // $ra = the return address
            sw(v1, gp, -17308);  // 0x7CE954 (the texture module open count)
            call_ptr(ctx, jt);
            s0 = v0;
            if (s0 == 0) {
                // 0x004d17dc
                charge(ctx, 2);
                s0 = 0;
                backedge(ctx);
            } else {
                // 0x004d16d0: type 6, linked, empty (as sub_4D0C30)
                charge(ctx, 30);
                v0 = 6;
                a3 = 0x960000;
                sb(v0, s0, 0);
                a0 = 0x780000;
                sb(zero, s0, 1);
                a3 = addiu(a3, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                sb(zero, s0, 2);
                a2 = addiu(s0, 16);
                sb(zero, s0, 3);
                v0 = addiu(s0, 8);
                sw(zero, s0, rwobj::kParent);
                a0 = addiu(a0, -6416);  // &0x77E6F0 (the RwTexDictionary plugin registry)
                lw(v1, gp, -17312);  // 0x7CE950 (the texture module offset)
                a1 = s0;
                v1 = addu(a3, v1);
                lw(v1, v1, 0);
                sw(v1, s0, rwtexdict::kLink);
                lw(v1, gp, -17312);  // 0x7CE950 (the texture module offset)
                v1 = addu(a3, v1);
                sw(v1, s0, rwtexdict::kLinkPrev);
                lw(v1, gp, -17312);  // 0x7CE950 (the texture module offset)
                v1 = addu(a3, v1);
                lw(v1, v1, 0);
                sw(a2, v1, 4);
                lw(v1, gp, -17312);  // 0x7CE950 (the texture module offset)
                v1 = addu(a3, v1);
                sw(a2, v1, 0);
                sw(v0, s0, rwtexdict::kTextures);
                link(ctx, 0x4D1740u);  // $ra first: the delay slot below depends on it
                sw(v0, s0, rwtexdict::kTexturesPrev);
                call(ctx, gen::fn_sub_4C64B0_004c64b0);
            }
            // 0x004d1748: current and the module's own
            charge(ctx, 8);
            lw(v0, gp, -17312);  // 0x7CE950 (the texture module offset)
            t0 = 0x960000;
            t0 = addiu(t0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            v1 = addu(t0, v0);
            sw(s0, v1, 16);
            lw(v0, v1, 16);
            sw(s0, gp, -17320);  // 0x7CE948 (the default texture dictionary)
            if (v0 == 0) {
                // 0x004d17e4: no dictionary: destroy both free lists
                charge(ctx, 15);
                link(ctx, 0x4D17E4u);  // $ra first: the delay slot below depends on it
                lw(a0, v1, 12);
                call(ctx, gen::fn_sub_4C3C30_004c3c30);
                lw(v1, gp, -17312);  // 0x7CE950 (the texture module offset)
                v0 = 0x960000;
                v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                v0 = addu(v0, v1);
                sw(zero, v0, 12);
                link(ctx, 0x4D1800u);  // $ra first: the delay slot below depends on it
                lw(a0, v0, 8);
                call(ctx, gen::fn_sub_4C3C30_004c3c30);
                lw(a0, gp, -17312);  // 0x7CE950 (the texture module offset)
                v1 = 0x960000;
                v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                v0 = 0;
                v1 = addu(v1, a0);
                sw(zero, v1, 8);
            } else {
                // 0x004d1768: the default callbacks
                charge(ctx, 20);
                lw(a3, gp, -17312);  // 0x7CE950 (the texture module offset)
                a2 = 0x4D0000;
                sw(zero, v1, 28);
                a1 = 0x4D0000;
                a0 = 0x4D0000;
                v1 = 0x4D0000;
                a2 = addiu(a2, 2752);  // &sub_4D0AC0
                a1 = addiu(a1, 1520);  // &sub_4D05F0
                a0 = addiu(a0, 1600);  // &sub_4D0640
                v1 = addiu(v1, -2624);  // &sub_4CF5C0
                v0 = s1;
                a3 = addu(t0, a3);
                sw(zero, a3, 32);
                sw(a2, a3, 24);
                sw(a1, a3, 20);
                sw(a0, a3, 44);
                sw(v1, a3, 48);
                sw(zero, a3, 36);
                sh(zero, a3, 40);
            }
        }
    } else {
        // 0x004d1640
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004d1820 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4C81A0 [textureRegisterPluginStream] -- sets a texture plugin's stream callbacks (the registries' shared chunk)
// As sub_4C7D00 for the texture registry: returns the plugin's offset or -1.
// 0x004C81A0 sub_4C81A0 -- 116 bytes, 2 chunks; leaf frame (no stack)
void sub_4C81A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x004c81a0
    enter(ctx, 9);  // entry check point + this block's cycles
    v1 = a1;
    v0 = a2;
    a1 = a0;
    t0 = a3;
    a0 = 0x780000;
    a2 = v1;
    a0 = addiu(a0, -6448);  // &0x77E6D0 (the RwTexture plugin registry)
    a3 = v0;
    backedge(ctx);
    // 0x004c5960
    charge(ctx, 3);
    lw(v1, a0, 16);
    if (v1 != 0) {
        for (;;) {
            // 0x004c596c
            charge(ctx, 3);
            lw(v0, v1, 8);
            if (v0 == a1) {
                break;
            }
            // 0x004c5978
            charge(ctx, 3);
            lw(v1, v1, 48);
            if (v1 == 0) {
                goto L_004c5984_4;
            }
            backedge(ctx);
        }
    }
L_004c5988:
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x004c59a4
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x004c5990
        charge(ctx, 5);
        sw(a2, v1, 12);
        sw(a3, v1, 16);
        sw(t0, v1, 20);
        lw(v0, v1, 0);
    }
    // 0x004c59a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004c5984_4:
    charge(ctx, 1);
    goto L_004c5988;
}

// sub_4C81D0 [textureStreamGetSize] -- the bytes a texture chunk takes
// The name's and the mask's string chunks (sub_4C7410) + 28 + 12, the extension (sub_4C5CB0) + 12.
// 0x004C81D0 sub_4C81D0 -- 100 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C81D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c81d0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    s1 = a0;
    sq(s0, sp, 0x0);
    a0 = addiu(s1, 16);
    s0 = 16;
    jal(ctx, 0x4C81E8u, gen::fn_sub_4C7410_004c7410);
    v0 = addiu(v0, 12);
    a0 = addiu(s1, 48);
    s0 = addu(s0, v0);
    jal(ctx, 0x4C81F8u, gen::fn_sub_4C7410_004c7410);
    v0 = addiu(v0, 12);
    a0 = 0x780000;
    a1 = s1;
    s0 = addu(s0, v0);
    a0 = addiu(a0, -6448);  // &0x77E6D0 (the RwTexture plugin registry)
    jal(ctx, 0x4C8210u, gen::fn_sub_4C5CB0_004c5cb0);
    v0 = addiu(v0, 12);
    ld(ra, sp, 0x20);
    v0 = addu(s0, v0);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4C8240 [textureStreamWrite] -- writes a texture chunk: struct, name, mask, extension
// The texture chunk header (type 6, the size as sub_4C81D0, version 0x37002, build 0x37), a 4-byte struct
// chunk: the filter / addressing (u16 +80) | bit 16 when the raster has mip levels that are not generated
// (format byte bit 4 clear), the two strings (sub_4C7460), the extension (sub_4C5D30). Returns the texture or 0.
// 0x004C8240 sub_4C8240 -- 372 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C8240(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c8240
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = 16;
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = addiu(s1, 16);
    jal(ctx, 0x4C8260u, gen::fn_sub_4C7410_004c7410);
    v0 = addiu(v0, 12);
    a0 = addiu(s1, 48);
    s2 = addu(s2, v0);
    jal(ctx, 0x4C8270u, gen::fn_sub_4C7410_004c7410);
    v0 = addiu(v0, 12);
    a0 = 0x780000;
    a0 = addiu(a0, -6448);  // &0x77E6D0 (the RwTexture plugin registry)
    s2 = addu(s2, v0);
    a1 = s1;
    jal(ctx, 0x4C8288u, gen::fn_sub_4C5CB0_004c5cb0);
    v0 = addiu(v0, 12);
    a0 = s0;
    a2 = addu(s2, v0);
    a1 = 6;
    v0 = 0x30000;
    t0 = 55;
    a3 = v0 | 0x7002;
    jal(ctx, 0x4C82A8u, gen::fn_sub_4C15A0_004c15a0);
    if (v0 != 0) {
        // 0x004c82c0: the struct chunk
        charge(ctx, 9);
        v0 = 0x30000;
        a0 = s0;
        a1 = 1;
        a2 = 4;
        a3 = v0 | 0x7002;
        t0 = 55;
        jal(ctx, 0x4C82D4u, gen::fn_sub_4C15A0_004c15a0);
        if (v0 == 0) {
            // 0x004c8338
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004c82e4: a raster: its format's auto-mipmap bit
            charge(ctx, 3);
            lw(v0, s1, rwtex::kRaster);
            if (v0 != 0) {
                // 0x004c82f0
                charge(ctx, 4);
                lbu(v0, v0, 35);
                v0 = v0 & 0x10;
                if (v0 != 0) {
                    goto L_004c8340;
                }
                // 0x004c8300
                charge(ctx, 1);
                v0 = 1;
                goto L_004c8304;
            }
        L_004c8340:
            charge(ctx, 2);
            v0 = 0;
            backedge(ctx);
        L_004c8304:  // the filter / addressing word
            charge(ctx, 11);
            lhu(v1, s1, rwtex::kFilterAddressing);
            v0 = v0 & 0xFF;
            v0 = sll(v0, 16);
            a0 = s0;
            a1 = addiu(sp, 0x4C);
            a2 = 4;
            v0 = v1 | v0;
            link(ctx, 0x4C8320u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x4C);
            call(ctx, gen::fn_sub_4C53F0_004c53f0);
            if (v0 != 0) {
                // 0x004c8348: the name
                charge(ctx, 5);
                a0 = addiu(s1, 16);
                a1 = s0;
                jal(ctx, 0x4C834Cu, gen::fn_sub_4C7460_004c7460);
                if (v0 != 0) {
                    // 0x004c8364: the mask
                    charge(ctx, 5);
                    a0 = addiu(s1, 48);
                    a1 = s0;
                    jal(ctx, 0x4C8368u, gen::fn_sub_4C7460_004c7460);
                    if (v0 != 0) {
                        // 0x004c8380: the extension
                        charge(ctx, 7);
                        a0 = 0x780000;
                        a1 = s0;
                        a0 = addiu(a0, -6448);  // &0x77E6D0 (the RwTexture plugin registry)
                        a2 = s1;
                        jal(ctx, 0x4C838Cu, gen::fn_sub_4C5D30_004c5d30);
                        if (v0 == 0) s1 = 0;
                        v0 = s1;
                    } else {
                        // 0x004c8378
                        charge(ctx, 2);
                        v0 = 0;
                    }
                } else {
                    // 0x004c835c
                    charge(ctx, 2);
                    v0 = 0;
                }
            } else {
                // 0x004c8330
                charge(ctx, 2);
                v0 = 0;
            }
        }
    } else {
        // 0x004c82b8
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004c839c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4C83C0 [textureStreamRead] -- reads a texture chunk: the texture comes from the read-by-name path
// The struct chunk (version 0x35000..0x37002, else error 0x80000004): a 4-byte word read into a zeroed frame
// slot; v addressing 0 takes the u addressing. The mipmapping states (sub_4D0B80 / sub_4D0BC0) are saved and
// set: on for the filters 3..6, auto-mipmapping only when bit 16 is clear. The name and the mask (string
// chunks, sub_4C78A0), the texture by name (sub_4D1260); the states restored. A new texture (one reference)
// takes the filter word and reads its extension (sub_4C5A50); an existing one skips it (sub_4C5EA0). Returns
// the texture or 0.
// 0x004C83C0 sub_4C83C0 -- 652 bytes; frame 0x180: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C83C0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c83c0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x180);
    a1 = 1;
    sd(ra, sp, 0x50);
    a2 = addiu(sp, 0x17C);
    sq(s4, sp, 0x40);
    a3 = addiu(sp, 0x178);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    link(ctx, 0x4C83E8u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1600_004c1600);
    if (v0 == 0) {
        // 0x004c8560: no struct chunk: 0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004c83f8
        charge(ctx, 6);
        lw(v1, sp, 0x178);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x004c8410
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_004c8608;
            }
            // 0x004c8424: the filter / addressing word
            charge(ctx, 11);
            a0 = addiu(sp, 0x174);
            a1 = 0;
            a2 = 4;
            jal(ctx, 0x4C842Cu, gen::fn_memset_00521408);
            lw(s0, sp, 0x17C);
            a0 = s3;
            a1 = addiu(sp, 0x174);
            a2 = s0;
            jal(ctx, 0x4C8440u, gen::fn_sub_4C5250_004c5250);
            if (s0 != v0) {
                // 0x004c8568
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004c8450
                charge(ctx, 7);
                lw(a0, sp, 0x174);
                v0 = srl(a0, 8);
                v1 = v0 & 0xF;
                v0 = srl(a0, 12);
                v0 = v0 & 0xF;
                s0 = a0 & 0xFF;
                if (v0 == 0) {
                    // 0x004c8570
                    charge(ctx, 5);
                    v0 = v1 & 0xF;
                    v0 = sll(v0, 12);
                    v0 = a0 | v0;
                    sw(v0, sp, 0x174);
                    backedge(ctx);
                }
                // 0x004c846c: save the mipmap states
                charge(ctx, 11);
                lw(v0, sp, 0x174);
                v0 = srl(v0, 16);
                s4 = v0 & 0xFF;
                jal(ctx, 0x4C8474u, gen::fn_sub_4D0B80_004d0b80);
                s2 = v0;
                jal(ctx, 0x4C847Cu, gen::fn_sub_4D0BC0_004d0bc0);
                s1 = v0;
                v0 = addiu(s0, -3);
                at = sltiu(v0, 4);
                if (at == 0) {
                    // 0x004c84cc: not a mipmap filter: both off
                    charge(ctx, 4);
                    a0 = 0;
                    jal(ctx, 0x4C84CCu, gen::fn_sub_4D0B60_004d0b60);
                    a0 = 0;
                    jal(ctx, 0x4C84D4u, gen::fn_sub_4D0BA0_004d0ba0);
                L_004c84dc:  // the strings
                    charge(ctx, 1);
                    a0 = addiu(sp, 0xE0);
                } else {
                    // 0x004c8498: a mipmap filter: mipmapping on
                    charge(ctx, 5);
                    a0 = 1;
                    jal(ctx, 0x4C8498u, gen::fn_sub_4D0B60_004d0b60);
                    v0 = s4 & 0x1;
                    if (v0 == 0) {
                        // 0x004c84bc: bit 16 clear: auto-mipmapping on
                        charge(ctx, 4);
                        a0 = 1;
                        jal(ctx, 0x4C84BCu, gen::fn_sub_4D0BA0_004d0ba0);
                        goto L_004c84dc;
                    }
                    // 0x004c84ac: bit 16 set: auto-mipmapping off
                    charge(ctx, 4);
                    a0 = 0;
                    jal(ctx, 0x4C84ACu, gen::fn_sub_4D0BA0_004d0ba0);
                    a0 = addiu(sp, 0xE0);
                }
                // 0x004c84e0: the name
                charge(ctx, 4);
                a1 = s3;
                jal(ctx, 0x4C84E0u, gen::fn_sub_4C78A0_004c78a0);
                if (v0 == 0) {
                    // 0x004c8584
                    charge(ctx, 6);
                    a0 = s2;
                    jal(ctx, 0x4C8584u, gen::fn_sub_4D0B60_004d0b60);
                    a0 = s1;
                    jal(ctx, 0x4C858Cu, gen::fn_sub_4D0BA0_004d0ba0);
                    v0 = 0;
                } else {
                    // 0x004c84f0: the mask
                    charge(ctx, 5);
                    a0 = addiu(sp, 0x60);
                    a1 = s3;
                    jal(ctx, 0x4C84F4u, gen::fn_sub_4C78A0_004c78a0);
                    if (v0 == 0) {
                        // 0x004c859c
                        charge(ctx, 6);
                        a0 = s2;
                        jal(ctx, 0x4C859Cu, gen::fn_sub_4D0B60_004d0b60);
                        a0 = s1;
                        jal(ctx, 0x4C85A4u, gen::fn_sub_4D0BA0_004d0ba0);
                        v0 = 0;
                    } else {
                        // 0x004c8504: the texture by name
                        charge(ctx, 5);
                        a0 = addiu(sp, 0xE0);
                        a1 = addiu(sp, 0x60);
                        jal(ctx, 0x4C8508u, gen::fn_sub_4D1260_004d1260);
                        s0 = v0;
                        if (v0 == 0) {
                            // 0x004c85b4: none: skip the extension, restore
                            charge(ctx, 10);
                            a0 = 0x780000;
                            a1 = s3;
                            a0 = addiu(a0, -6448);  // &0x77E6D0 (the RwTexture plugin registry)
                            jal(ctx, 0x4C85BCu, gen::fn_sub_4C5EA0_004c5ea0);
                            a0 = s2;
                            jal(ctx, 0x4C85C4u, gen::fn_sub_4D0B60_004d0b60);
                            a0 = s1;
                            jal(ctx, 0x4C85CCu, gen::fn_sub_4D0BA0_004d0ba0);
                            v0 = 0;
                        } else {
                            // 0x004c8518: restore the states; new?
                            charge(ctx, 8);
                            a0 = s2;
                            jal(ctx, 0x4C8518u, gen::fn_sub_4D0B60_004d0b60);
                            a0 = s1;
                            jal(ctx, 0x4C8520u, gen::fn_sub_4D0BA0_004d0ba0);
                            lw(v1, s0, rwtex::kRefCount);
                            v0 = 1;
                            if (v1 == v0) {
                                // 0x004c85dc: new: the filter word, the extension
                                charge(ctx, 9);
                                lhu(v0, sp, 0x174);
                                a0 = 0x780000;
                                a1 = s3;
                                a0 = addiu(a0, -6448);  // &0x77E6D0 (the RwTexture plugin registry)
                                a2 = s0;
                                link(ctx, 0x4C85F0u);  // $ra first: the delay slot below depends on it
                                sw(v0, s0, rwtex::kFilterAddressing);
                                call(ctx, gen::fn_sub_4C5A50_004c5a50);
                                if (v0 != 0) {
                                    backedge(ctx);
                                L_004c8558:
                                    charge(ctx, 2);
                                    v0 = s0;
                                } else {
                                    // 0x004c8600
                                    charge(ctx, 2);
                                    v0 = 0;
                                }
                            } else {
                                // 0x004c8538: existing: skip the extension
                                charge(ctx, 6);
                                a0 = 0x780000;
                                a1 = s3;
                                a0 = addiu(a0, -6448);  // &0x77E6D0 (the RwTexture plugin registry)
                                jal(ctx, 0x4C8540u, gen::fn_sub_4C5EA0_004c5ea0);
                                if (v0 != 0) {
                                    goto L_004c8558;
                                }
                                // 0x004c8550
                                charge(ctx, 2);
                                v0 = 0;
                            }
                        }
                    }
                }
            }
            // 0x004c862c (the shared epilogue, written out on this path)
            charge(ctx, 8);
            ld(ra, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x180);
            return;
        }
    L_004c8608:  // a bad version: error 0x80000004
        charge(ctx, 9);
        v1 = 1;
        v0 = lui(0x8000);
        sw(v1, sp, 0x168);
        a0 = v0 | 0x4;
        jal(ctx, 0x4C8614u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x16C);
        a0 = addiu(sp, 0x168);
        jal(ctx, 0x4C8620u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x004c862c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x180);
}

// sub_4C8650 [texDictDestroyTextureCB] -- the dictionary walk's callback: sub_4D0F00(texture), returns the texture
// 0x004C8650 sub_4C8650 -- 40 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C8650(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c8650
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x4C865Cu, gen::fn_sub_4D0F00_004d0f00);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4C8680 [texDictStreamRead] -- reads a texture dictionary chunk: native textures, their extensions
// The struct chunk (version check as above): {u16 count, u16 device id}; the device id from
// _rwDeviceSystemRequest(0x960080, 22) must match when both are set (else 0). A new dictionary (sub_4D0C30);
// for each texture: a native-texture chunk (type 21, version checked), the device's native read (standard
// function 26, 0x960120), the texture's extension (sub_4C5A50), added (sub_4D1110). Then the dictionary's
// extension. Any failure destroys the textures read so far (sub_4C8650) and the dictionary. Returns the
// dictionary or 0.
// 0x004C8680 sub_4C8680 -- 796 bytes; frame 0x70: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C8680(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c8680
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    a1 = 1;
    sd(ra, sp, 0x30);
    a2 = addiu(sp, 0x68);
    sq(s2, sp, 0x20);
    a3 = addiu(sp, 0x64);
    sq(s1, sp, 0x10);
    s2 = a0;
    link(ctx, 0x4C86A0u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1600_004c1600);
    if (v0 == 0) {
        // 0x004c8718: no struct chunk: 0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004c86b0
        charge(ctx, 6);
        lw(v1, sp, 0x64);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x004c86c8
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_004c8960;
            }
            // 0x004c86dc: count and device id
            charge(ctx, 13);
            s1 = 0x960000;
            a0 = addiu(sp, 0x60);
            a1 = 0;
            a2 = 4;
            s1 = addiu(s1, 128);  // &0x960080 (engine +16: the device)
            jal(ctx, 0x4C86ECu, gen::fn_memset_00521408);
            lw(s0, sp, 0x68);
            a0 = s2;
            a1 = addiu(sp, 0x60);
            a2 = s0;
            jal(ctx, 0x4C8700u, gen::fn_sub_4C5250_004c5250);
            if (s0 == v0) {
                // 0x004c8720: the device's id
                charge(ctx, 12);
                a0 = s1;
                a1 = 22;
                a2 = addiu(sp, 0x6E);
                a3 = 0;
                t0 = 0;
                link(ctx, 0x4C8734u);  // $ra first: the delay slot below depends on it
                sh(zero, sp, 0x6E);
                call(ctx, gen::fn__rwDeviceSystemRequest_004ca3e0);
                lbu(v0, sp, 0x6E);
                sh(v0, sp, 0x6E);
                lhu(v1, sp, 0x6E);
                if (v1 != 0) {
                    // 0x004c8750
                    charge(ctx, 3);
                    lhu(v0, sp, 0x62);
                    if (v0 == 0) {
                        goto L_004c876c;
                    }
                    // 0x004c875c
                    charge(ctx, 2);
                    if (v1 == v0) {
                        goto L_004c876c;
                    }
                    // 0x004c8764
                    charge(ctx, 2);
                    v0 = 0;
                    // 0x004c8984 (the shared epilogue, written out on this path)
                    charge(ctx, 6);
                    ld(ra, sp, 0x30);
                    lq(s2, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x70);
                    return;
                }
            L_004c876c:  // a new dictionary
                charge(ctx, 5);
                jal(ctx, 0x4C876Cu, gen::fn_sub_4D0C30_004d0c30);
                s1 = v0;
                if (s1 == 0) {
                    // 0x004c8884
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x004c8780: count textures
                    charge(ctx, 4);
                    lhu(v1, sp, 0x60);
                    v0 = addiu(v1, -1);
                    sh(v0, sp, 0x60);
                    if (v1 != 0) {
                        // 0x004c8790
                        charge(ctx, 2);
                        s0 = 0x960000;
                        s0 = addiu(s0, 288);  // &0x960120 (standard function 26: native texture read)
                        for (;;) {
                            // 0x004c8798: the next native-texture chunk
                            charge(ctx, 7);
                            a0 = s2;
                            a1 = 21;
                            a2 = addiu(sp, 0x68);
                            a3 = addiu(sp, 0x64);
                            jal(ctx, 0x4C87A4u, gen::fn_sub_4C1600_004c1600);
                            if (v0 == 0) {
                                goto L_004c87b4_14;
                            }
                            // 0x004c87d8
                            charge(ctx, 6);
                            lw(v1, sp, 0x64);
                            v0 = 0x30000;
                            v0 = v0 | 0x5000;
                            v0 = sltu(v1, v0);
                            if (v0 != 0) {
                                goto L_004c888c;
                            }
                            // 0x004c87f0
                            charge(ctx, 5);
                            at = 0x30000;
                            at = at | 0x7003;
                            at = sltu(v1, at);
                            if (at == 0) {
                                goto L_004c888c;
                            }
                            // 0x004c8804: the device reads it
                            charge(ctx, 7);
                            lw(a2, sp, 0x68);
                            a0 = s2;
                            lw(v0, s0, 0);
                            a1 = addiu(sp, 0x5C);
                            jalr(ctx, 0x4C8810u, v0.u());
                            if (v0 == 0) {
                                goto L_004c88d0;
                            }
                            // 0x004c8820
                            charge(ctx, 3);
                            lw(a2, sp, 0x5C);
                            if (a2 == 0) {
                                goto L_004c88f4;
                            }
                            // 0x004c882c: its extension
                            charge(ctx, 6);
                            a0 = 0x780000;
                            a1 = s2;
                            a0 = addiu(a0, -6448);  // &0x77E6D0 (the RwTexture plugin registry)
                            jal(ctx, 0x4C8834u, gen::fn_sub_4C5A50_004c5a50);
                            if (v0 == 0) {
                                goto L_004c8918;
                            }
                            // 0x004c8844: into the dictionary
                            charge(ctx, 7);
                            lw(a1, sp, 0x5C);
                            a0 = s1;
                            jal(ctx, 0x4C8848u, gen::fn_sub_4D1110_004d1110);
                            lhu(v1, sp, 0x60);
                            v0 = addiu(v1, -1);
                            sh(v0, sp, 0x60);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                    // 0x004c8860: the dictionary's extension
                    charge(ctx, 7);
                    a0 = 0x780000;
                    a1 = s2;
                    a0 = addiu(a0, -6416);  // &0x77E6F0 (the RwTexDictionary plugin registry)
                    a2 = s1;
                    jal(ctx, 0x4C886Cu, gen::fn_sub_4C5A50_004c5a50);
                    if (v0 == 0) {
                        // 0x004c893c: failed: destroy everything
                        charge(ctx, 9);
                        a1 = 0x4D0000;
                        a0 = s1;
                        a1 = addiu(a1, -31152);  // &sub_4C8650
                        a2 = 0;
                        jal(ctx, 0x4C8948u, gen::fn_sub_4D0DC0_004d0dc0);
                        a0 = s1;
                        jal(ctx, 0x4C8950u, gen::fn_sub_4D0D10_004d0d10);
                        v0 = 0;
                    } else {
                        // 0x004c887c
                        charge(ctx, 2);
                        v0 = s1;
                    }
                }
            } else {
                // 0x004c8710
                charge(ctx, 2);
                v0 = 0;
            }
            // 0x004c8984 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x70);
            return;
        }
    L_004c8960:  // a bad version: error 0x80000004
        charge(ctx, 9);
        v1 = 1;
        v0 = lui(0x8000);
        sw(v1, sp, 0x48);
        a0 = v0 | 0x4;
        jal(ctx, 0x4C896Cu, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x4C);
        a0 = addiu(sp, 0x48);
        jal(ctx, 0x4C8978u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x004c8984 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004c87b4_14:  // no chunk: destroy everything
    charge(ctx, 9);
    a1 = 0x4D0000;
    a0 = s1;
    a1 = addiu(a1, -31152);  // &sub_4C8650
    a2 = 0;
    jal(ctx, 0x4C87C0u, gen::fn_sub_4D0DC0_004d0dc0);
    a0 = s1;
    jal(ctx, 0x4C87C8u, gen::fn_sub_4D0D10_004d0d10);
    v0 = 0;
    // 0x004c8984 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004c888c:  // a bad version: destroy everything, error
    charge(ctx, 17);
    a1 = 0x4D0000;
    a0 = s1;
    a1 = addiu(a1, -31152);  // &sub_4C8650
    a2 = 0;
    jal(ctx, 0x4C8898u, gen::fn_sub_4D0DC0_004d0dc0);
    a0 = s1;
    jal(ctx, 0x4C88A0u, gen::fn_sub_4D0D10_004d0d10);
    v1 = 1;
    v0 = lui(0x8000);
    sw(v1, sp, 0x50);
    a0 = v0 | 0x4;
    jal(ctx, 0x4C88B4u, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0x54);
    a0 = addiu(sp, 0x50);
    jal(ctx, 0x4C88C0u, gen::fn_sub_4C1C50_004c1c50);
    v0 = 0;
    // 0x004c8984 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004c88d0:  // the device read failed
    charge(ctx, 9);
    a1 = 0x4D0000;
    a0 = s1;
    a1 = addiu(a1, -31152);  // &sub_4C8650
    a2 = 0;
    jal(ctx, 0x4C88DCu, gen::fn_sub_4D0DC0_004d0dc0);
    a0 = s1;
    jal(ctx, 0x4C88E4u, gen::fn_sub_4D0D10_004d0d10);
    v0 = 0;
    // 0x004c8984 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004c88f4:  // no texture
    charge(ctx, 9);
    a1 = 0x4D0000;
    a0 = s1;
    a1 = addiu(a1, -31152);  // &sub_4C8650
    a2 = 0;
    jal(ctx, 0x4C8900u, gen::fn_sub_4D0DC0_004d0dc0);
    a0 = s1;
    jal(ctx, 0x4C8908u, gen::fn_sub_4D0D10_004d0d10);
    v0 = 0;
    // 0x004c8984 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004c8918:  // the extension failed
    charge(ctx, 9);
    a1 = 0x4D0000;
    a0 = s1;
    a1 = addiu(a1, -31152);  // &sub_4C8650
    a2 = 0;
    jal(ctx, 0x4C8924u, gen::fn_sub_4D0DC0_004d0dc0);
    a0 = s1;
    jal(ctx, 0x4C892Cu, gen::fn_sub_4D0D10_004d0d10);
    v0 = 0;
    // 0x004c8984 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// sub_4CDE40 [rasterUnlockPalette] -- unlocks a raster's palette (standard function 24), clears its lock bits 3..4
// 0x004CDE40 sub_4CDE40 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4CDE40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cde40
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    a2 = 0;
    sq(s0, sp, 0x0);
    lw(v0, v0, 280);  // 0x960118 (standard function 24: palette unlock)
    s0 = a0;
    a0 = 0;
    a1 = s0;
    jalr(ctx, 0x4CDE60u, v0.u());
    lbu(a0, s0, 34);
    v1 = si(-25);
    v0 = s0;
    v1 = a0 & v1;
    sb(v1, s0, 34);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4CDE90 [rasterDestroy] -- destroys a raster: plugins, the device's destroy, back to the free list
// sub_4C6560 (raster registry), standard function 5 (0x9600CC), the raster free list (module +96). Returns 1.
// 0x004CDE90 sub_4CDE90 -- 112 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4CDE90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cde90
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 0x780000;
    a1 = s0;
    a0 = addiu(a0, -6480);  // &0x77E6B0 (the RwRaster plugin registry)
    jal(ctx, 0x4CDEA8u, gen::fn_sub_4C6560_004c6560);
    v0 = 0x960000;
    a0 = 0;
    lw(v0, v0, 204);  // 0x9600CC (standard function 5: raster destroy)
    a1 = s0;
    a2 = 0;
    jalr(ctx, 0x4CDEC0u, v0.u());
    lw(a0, gp, -17328);  // 0x7CE940 (the raster module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = 0x960000;
    lw(v0, v0, 396);  // 0x96018C (free-list free slot)
    v1 = addu(v1, a0);
    lw(a0, v1, 96);
    a1 = s0;
    jalr(ctx, 0x4CDEE4u, v0.u());
    ld(ra, sp, 0x10);
    v0 = 1;
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4CDF00 [rasterRegisterPlugin] -- registers a raster plugin (sub_4C61B0 on the raster registry)
// 0x004CDF00 sub_4CDF00 -- 44 bytes; leaf frame (no stack)
void sub_4CDF00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x004cdf00
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = a1;
    v1 = a2;
    a1 = a0;
    a2 = v0;
    v0 = a3;
    t1 = t0;
    a0 = 0x780000;
    a3 = v1;
    t0 = v0;
    a0 = addiu(a0, -6480);  // &0x77E6B0 (the RwRaster plugin registry)
    gen::fn_sub_4C61B0_004c61b0(ctx);  // tail call
}

// sub_4CDF30 [rasterLockPalette] -- locks a raster's palette (standard function 23); returns the palette or 0
// 0x004CDF30 sub_4CDF30 -- 68 bytes; frame 0x20: ra sp+0x0
void sub_4CDF30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cdf30
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = a0;
    a2 = a1;
    sd(ra, sp, 0x0);
    a1 = v0;
    v0 = 0x960000;
    lw(v0, v0, 276);  // 0x960114 (standard function 23: palette lock)
    a0 = addiu(sp, 0x1C);
    jalr(ctx, 0x4CDF4Cu, v0.u());
    if (v0 == 0) {
        // 0x004cdf64: failed: 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004cdf5c: the palette
        charge(ctx, 2);
        lw(v0, sp, 0x1C);
    }
    // 0x004cdf68 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4CDF80 [rasterGetNumLevels] -- a raster's mip level count (1 without the mipmap format bit; -1 on failure)
// 0x004CDF80 sub_4CDF80 -- 88 bytes; frame 0x20: ra sp+0x0
void sub_4CDF80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cdf80
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    lbu(v0, a0, rwraster::kFormat);
    v0 = sll(v0, 8);
    v0 = v0 & 0x8000;
    a1 = a0;
    if (v0 != 0) {
        // 0x004cdfa4: mipmapped: ask the device (standard function 28)
        charge(ctx, 7);
        v0 = 0x960000;
        a0 = addiu(sp, 0x1C);
        lw(v0, v0, 296);  // 0x960128 (standard function 28: raster mip levels)
        a2 = 0;
        jalr(ctx, 0x4CDFB0u, v0.u());
        if (v0 == 0) {
            // 0x004cdfc8
            charge(ctx, 1);
            v0 = si(-1);
        } else {
            // 0x004cdfc0
            charge(ctx, 2);
            lw(v0, sp, 0x1C);
        }
    } else {
        // 0x004cdf9c: no mip levels: 1
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x004cdfcc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4CE0F0 [rasterCreate] -- creates a raster through the device (standard function 4)
// ($a0 = width, $a1 = height, $a2 = depth, $a3 = flags) A record from the raster free list (module +96, hint
// 0x30807): no lock / private flags, size and depth, offsets 0, its own parent, no pixels or palette; the
// device's create (0x9600C8) with the flags; success runs the raster plugins' constructors, failure returns the
// record. Returns the raster or 0.
// 0x004CE0F0 sub_4CE0F0 -- 272 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CE0F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004ce0f0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v1 = 0x960000;
    sd(ra, sp, 0x50);
    v0 = 0x30000;
    sq(s4, sp, 0x40);
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    a1 = v0 | 0x407;
    sq(s0, sp, 0x0);
    v0 = 0x960000;
    lw(a0, gp, -17328);  // 0x7CE940 (the raster module offset)
    s2 = a2;
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    v1 = addu(v1, a0);
    lw(a0, v1, 96);
    s1 = a3;
    jalr(ctx, 0x4CE13Cu, v0.u());
    s0 = v0;
    if (s0 == 0) {
        // 0x004ce1dc: no memory: 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004ce150: the fields; the device creates it
        charge(ctx, 18);
        v0 = 0x960000;
        a2 = s1;
        lw(v0, v0, 200);  // 0x9600C8 (standard function 4: raster create)
        a0 = 0;
        a1 = s0;
        sb(zero, s0, rwraster::kLockFlags);
        sb(zero, s0, rwraster::kPrivateFlags);
        sw(s4, s0, rwraster::kWidth);
        sw(s3, s0, rwraster::kHeight);
        sh(zero, s0, rwraster::kOffsetX);
        sh(zero, s0, rwraster::kOffsetY);
        sw(s2, s0, rwraster::kDepth);
        sw(s0, s0, rwraster::kParent);
        sw(zero, s0, rwraster::kPixels);
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x4CE188u);  // $ra = the return address
        sw(zero, s0, rwraster::kPalette);
        call_ptr(ctx, jt);
        if (v0 != 0) {
            // 0x004ce1c4: the plugins
            charge(ctx, 6);
            a0 = 0x780000;
            a1 = s0;
            a0 = addiu(a0, -6480);  // &0x77E6B0 (the RwRaster plugin registry)
            jal(ctx, 0x4CE1CCu, gen::fn_sub_4C64B0_004c64b0);
            v0 = s0;
        } else {
            // 0x004ce198: the device failed: back to the free list
            charge(ctx, 11);
            lw(a0, gp, -17328);  // 0x7CE940 (the raster module offset)
            v1 = 0x960000;
            v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            v0 = 0x960000;
            lw(v0, v0, 396);  // 0x96018C (free-list free slot)
            v1 = addu(v1, a0);
            lw(a0, v1, 96);
            a1 = s0;
            jalr(ctx, 0x4CE1B4u, v0.u());
            v0 = 0;
        }
    }
    // 0x004ce1e0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4CE250 [rasterModuleClose] -- the raster module's close: destroys the raster free list; count down
// 0x004CE250 sub_4CE250 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4CE250(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ce250
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s0, sp, 0x0);
    lw(v1, gp, -17328);  // 0x7CE940 (the raster module offset)
    s0 = a0;
    v0 = addu(v0, v1);
    lw(a0, v0, 96);
    if (a0 != 0) {
        // 0x004ce27c
        charge(ctx, 7);
        jal(ctx, 0x4CE27Cu, gen::fn_sub_4C3C30_004c3c30);
        lw(v1, gp, -17328);  // 0x7CE940 (the raster module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        sw(zero, v0, 96);
    }
    // 0x004ce298 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(v1, gp, -17324);  // 0x7CE944 (the raster module open count)
    v0 = s0;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17324);  // 0x7CE944 (the raster module open count)
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4CE2C0 [rasterModuleOpen] -- the raster module's open: the context stack, the raster free list
// ($a1 = the offset, at 0x7CE940) The 52-byte context area at +44 is cleared (+77 = 0x80) and +0 points at it;
// the raster free list (entry size = the raster registry's, static 0x964100, hint 0x40407) goes to +96; the
// open counted. Returns $a0 or 0.
// 0x004CE2C0 sub_4CE2C0 -- 220 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4CE2C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ce2c0
    enter(ctx, 45);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s0, sp, 0x0);
    v0 = addu(v0, a1);
    sw(a1, gp, -17328);  // 0x7CE940 (the raster module offset)
    s0 = a0;
    a2 = 52;
    a0 = addiu(v0, 44);
    a1 = 0;
    jal(ctx, 0x4CE2E8u, gen::fn_memset_00521408);
    lw(t3, gp, -17328);  // 0x7CE940 (the raster module offset)
    t2 = 0x960000;
    t2 = addiu(t2, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = 0x780000;
    lw(a0, v0, -6480);  // 0x77E6B0 (the RwRaster plugin registry)
    t0 = 0x960000;
    v1 = 128;
    lw(a1, gp, -20336);  // 0x7CDD80 (the raster free list: entries per block)
    lw(a3, gp, -20332);  // 0x7CDD84 (the raster free list: preallocated blocks)
    a2 = 4;
    t0 = addiu(t0, 16640);  // &0x964100 (the raster free list, static)
    t2 = addu(t2, t3);
    sw(zero, t2, 56);
    sw(zero, t2, 60);
    v0 = 0x40000;
    sw(zero, t2, 64);
    t1 = v0 | 0x407;
    sb(v1, t2, 77);
    v0 = addiu(t2, 44);
    sw(zero, t2, 48);
    sw(zero, t2, 52);
    sb(zero, t2, 76);
    sw(zero, t2, 40);
    link(ctx, 0x4CE34Cu);  // $ra first: the delay slot below depends on it
    sw(v0, t2, 0);
    call(ctx, gen::fn_sub_4C3B60_004c3b60);
    lw(a0, gp, -17328);  // 0x7CE940 (the raster module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = addu(v1, a0);
    sw(v0, v1, 96);
    lw(v0, v1, 96);
    if (v0 != 0) {
        // 0x004ce37c
        charge(ctx, 4);
        lw(v1, gp, -17324);  // 0x7CE944 (the raster module open count)
        v0 = s0;
        v1 = addiu(v1, 1);
        sw(v1, gp, -17324);  // 0x7CE944 (the raster module open count)
    } else {
        // 0x004ce374
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004ce38c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
