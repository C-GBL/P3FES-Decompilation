// Slice render_rw8: RenderWare, eighth pass -- the RxPipeline core (create, lock, add fragment / path, find node, the
// unlock with its topological sort and cluster passes, the RxHeap), the pipe constructors that need it (the PDS
// registry's, PTank's, Im3D's, the PS2AllMat node's initialisation), Rt2d's object layer and animation, the image file
// readers / writers, RtQuat, the mipmap K / L pass and the palette quantiser (the group overview, the pipeline rules and
// the record layouts are in game/include/p3fes/game/render_rw8.h). Every body started as p3fes_handgen's output and
// keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points statement for
// statement (game/include/p3fes/game/hg_cpu.h); what was added is the role of each function, the role of its main
// blocks, the names of the record offsets (rw4:: .. rw8::) and the labels of the RW globals. sub_* keep their
// symbols/functions.json names; proposed names are in brackets (symbols/deltas/render_rw8.sym).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/render_rw8.h"

namespace p3fes::recomp_gen {
void fn_PDSRegistryAddPipe_0046aa80(p3fes::EEContext&);
void fn_PS2AllMatPipelineNodeInit_004a3540(p3fes::EEContext&);
void fn_RpPDSGetPipe_0046a890(p3fes::EEContext&);
void fn_RpPDSRegisterPipe_0046a830(p3fes::EEContext&);
void fn_RpPDSSkyMatPipeCreate_0046ad80(p3fes::EEContext&);
void fn_RxPipelineExecute_004f2e70(p3fes::EEContext&);
void fn_RxPipelineNodePS2AllMatSetVU1CodeArray_004a3db0(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_dpcmp_005316d0(p3fes::EEContext&);
void fn_fabsf_0052e788(p3fes::EEContext&);
void fn_j__rwSListGetEntry_004b2c70(p3fes::EEContext&);
void fn_logf_0052ea30(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_ps2AllMatClusterLayout_0049cc70(p3fes::EEContext&);
void fn_rpSpr2dGenCreatePS2AllMatPipe_00478a70(p3fes::EEContext&);
void fn_rpSpr3dGenCreatePS2AllMatPipe_00479e50(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_0049ff00(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_0_004a3f10(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_sub_45EC20_0045ec20(p3fes::EEContext&);
void fn_sub_45EE00_0045ee00(p3fes::EEContext&);
void fn_sub_45F580_0045f580(p3fes::EEContext&);
void fn_sub_45F7D0_0045f7d0(p3fes::EEContext&);
void fn_sub_46A600_0046a600(p3fes::EEContext&);
void fn_sub_46A8D0_0046a8d0(p3fes::EEContext&);
void fn_sub_46A970_0046a970(p3fes::EEContext&);
void fn_sub_46AC30_0046ac30(p3fes::EEContext&);
void fn_sub_46AFA0_0046afa0(p3fes::EEContext&);
void fn_sub_474BB0_00474bb0(p3fes::EEContext&);
void fn_sub_474C60_00474c60(p3fes::EEContext&);
void fn_sub_479030_00479030(p3fes::EEContext&);
void fn_sub_47A3D0_0047a3d0(p3fes::EEContext&);
void fn_sub_47AB70_0047ab70(p3fes::EEContext&);
void fn_sub_47B1A0_0047b1a0(p3fes::EEContext&);
void fn_sub_48F030_0048f030(p3fes::EEContext&);
void fn_sub_48F580_0048f580(p3fes::EEContext&);
void fn_sub_48FBD0_0048fbd0(p3fes::EEContext&);
void fn_sub_492C30_00492c30(p3fes::EEContext&);
void fn_sub_493C50_00493c50(p3fes::EEContext&);
void fn_sub_493C80_00493c80(p3fes::EEContext&);
void fn_sub_494520_00494520(p3fes::EEContext&);
void fn_sub_494550_00494550(p3fes::EEContext&);
void fn_sub_494DB0_00494db0(p3fes::EEContext&);
void fn_sub_494DE0_00494de0(p3fes::EEContext&);
void fn_sub_499250_00499250(p3fes::EEContext&);
void fn_sub_499280_00499280(p3fes::EEContext&);
void fn_sub_499720_00499720(p3fes::EEContext&);
void fn_sub_499850_00499850(p3fes::EEContext&);
void fn_sub_499A80_00499a80(p3fes::EEContext&);
void fn_sub_499AF0_00499af0(p3fes::EEContext&);
void fn_sub_49C680_0049c680(p3fes::EEContext&);
void fn_sub_49C6C0_0049c6c0(p3fes::EEContext&);
void fn_sub_49C810_0049c810(p3fes::EEContext&);
void fn_sub_49C8C0_0049c8c0(p3fes::EEContext&);
void fn_sub_49C9B0_0049c9b0(p3fes::EEContext&);
void fn_sub_49FE40_0049fe40(p3fes::EEContext&);
void fn_sub_49FEC0_0049fec0(p3fes::EEContext&);
void fn_sub_4A30D0_004a30d0(p3fes::EEContext&);
void fn_sub_4A35C0_004a35c0(p3fes::EEContext&);
void fn_sub_4A38F0_004a38f0(p3fes::EEContext&);
void fn_sub_4A3A80_004a3a80(p3fes::EEContext&);
void fn_sub_4A3C10_004a3c10(p3fes::EEContext&);
void fn_sub_4A3D70_004a3d70(p3fes::EEContext&);
void fn_sub_4A3E30_004a3e30(p3fes::EEContext&);
void fn_sub_4A5200_004a5200(p3fes::EEContext&);
void fn_sub_4A5210_004a5210(p3fes::EEContext&);
void fn_sub_4A5290_004a5290(p3fes::EEContext&);
void fn_sub_4A52A0_004a52a0(p3fes::EEContext&);
void fn_sub_4A5320_004a5320(p3fes::EEContext&);
void fn_sub_4A5330_004a5330(p3fes::EEContext&);
void fn_sub_4A5470_004a5470(p3fes::EEContext&);
void fn_sub_4A5540_004a5540(p3fes::EEContext&);
void fn_sub_4A6530_004a6530(p3fes::EEContext&);
void fn_sub_4A9A80_004a9a80(p3fes::EEContext&);
void fn_sub_4A9BD0_004a9bd0(p3fes::EEContext&);
void fn_sub_4AB0E0_004ab0e0(p3fes::EEContext&);
void fn_sub_4AC240_004ac240(p3fes::EEContext&);
void fn_sub_4AC390_004ac390(p3fes::EEContext&);
void fn_sub_4AC410_004ac410(p3fes::EEContext&);
void fn_sub_4AC710_004ac710(p3fes::EEContext&);
void fn_sub_4AD480_004ad480(p3fes::EEContext&);
void fn_sub_4AD5B0_004ad5b0(p3fes::EEContext&);
void fn_sub_4AD700_004ad700(p3fes::EEContext&);
void fn_sub_4AD940_004ad940(p3fes::EEContext&);
void fn_sub_4ADC90_004adc90(p3fes::EEContext&);
void fn_sub_4ADCC0_004adcc0(p3fes::EEContext&);
void fn_sub_4ADFD0_004adfd0(p3fes::EEContext&);
void fn_sub_4AE150_004ae150(p3fes::EEContext&);
void fn_sub_4AE1F0_004ae1f0(p3fes::EEContext&);
void fn_sub_4AE8F0_004ae8f0(p3fes::EEContext&);
void fn_sub_4AE900_004ae900(p3fes::EEContext&);
void fn_sub_4B0360_004b0360(p3fes::EEContext&);
void fn_sub_4B0430_004b0430(p3fes::EEContext&);
void fn_sub_4B0560_004b0560(p3fes::EEContext&);
void fn_sub_4B08C0_004b08c0(p3fes::EEContext&);
void fn_sub_4B0B10_004b0b10(p3fes::EEContext&);
void fn_sub_4B0DF0_004b0df0(p3fes::EEContext&);
void fn_sub_4B0FA0_004b0fa0(p3fes::EEContext&);
void fn_sub_4B1420_004b1420(p3fes::EEContext&);
void fn_sub_4B14C0_004b14c0(p3fes::EEContext&);
void fn_sub_4B1500_004b1500(p3fes::EEContext&);
void fn_sub_4B1700_004b1700(p3fes::EEContext&);
void fn_sub_4B1870_004b1870(p3fes::EEContext&);
void fn_sub_4B1A30_004b1a30(p3fes::EEContext&);
void fn_sub_4B1A80_004b1a80(p3fes::EEContext&);
void fn_sub_4B1B00_004b1b00(p3fes::EEContext&);
void fn_sub_4B1D00_004b1d00(p3fes::EEContext&);
void fn_sub_4B22B0_004b22b0(p3fes::EEContext&);
void fn_sub_4B2300_004b2300(p3fes::EEContext&);
void fn_sub_4B2BA0_004b2ba0(p3fes::EEContext&);
void fn_sub_4B2BF0_004b2bf0(p3fes::EEContext&);
void fn_sub_4B2C80_004b2c80(p3fes::EEContext&);
void fn_sub_4B3030_004b3030(p3fes::EEContext&);
void fn_sub_4B34D0_004b34d0(p3fes::EEContext&);
void fn_sub_4B3610_004b3610(p3fes::EEContext&);
void fn_sub_4B39F0_004b39f0(p3fes::EEContext&);
void fn_sub_4B4450_004b4450(p3fes::EEContext&);
void fn_sub_4B4A60_004b4a60(p3fes::EEContext&);
void fn_sub_4B5270_004b5270(p3fes::EEContext&);
void fn_sub_4B5380_004b5380(p3fes::EEContext&);
void fn_sub_4B56D0_004b56d0(p3fes::EEContext&);
void fn_sub_4B59B0_004b59b0(p3fes::EEContext&);
void fn_sub_4B5B50_004b5b50(p3fes::EEContext&);
void fn_sub_4B6000_004b6000(p3fes::EEContext&);
void fn_sub_4B9840_004b9840(p3fes::EEContext&);
void fn_sub_4B9870_004b9870(p3fes::EEContext&);
void fn_sub_4B99A0_004b99a0(p3fes::EEContext&);
void fn_sub_4B9BA0_004b9ba0(p3fes::EEContext&);
void fn_sub_4B9D40_004b9d40(p3fes::EEContext&);
void fn_sub_4B9E00_004b9e00(p3fes::EEContext&);
void fn_sub_4BA2A0_004ba2a0(p3fes::EEContext&);
void fn_sub_4BAD50_004bad50(p3fes::EEContext&);
void fn_sub_4BC830_004bc830(p3fes::EEContext&);
void fn_sub_4BCA00_004bca00(p3fes::EEContext&);
void fn_sub_4BCAE0_004bcae0(p3fes::EEContext&);
void fn_sub_4BCB20_004bcb20(p3fes::EEContext&);
void fn_sub_4BCB30_004bcb30(p3fes::EEContext&);
void fn_sub_4BCBF0_004bcbf0(p3fes::EEContext&);
void fn_sub_4BDB30_004bdb30(p3fes::EEContext&);
void fn_sub_4BDBB0_004bdbb0(p3fes::EEContext&);
void fn_sub_4BDC30_004bdc30(p3fes::EEContext&);
void fn_sub_4BDCB0_004bdcb0(p3fes::EEContext&);
void fn_sub_4BDDE0_004bdde0(p3fes::EEContext&);
void fn_sub_4BE1E0_004be1e0(p3fes::EEContext&);
void fn_sub_4BE310_004be310(p3fes::EEContext&);
void fn_sub_4BE930_004be930(p3fes::EEContext&);
void fn_sub_4C1600_004c1600(p3fes::EEContext&);
void fn_sub_4C17F0_004c17f0(p3fes::EEContext&);
void fn_sub_4C1820_004c1820(p3fes::EEContext&);
void fn_sub_4C1850_004c1850(p3fes::EEContext&);
void fn_sub_4C18B0_004c18b0(p3fes::EEContext&);
void fn_sub_4C1910_004c1910(p3fes::EEContext&);
void fn_sub_4C19F0_004c19f0(p3fes::EEContext&);
void fn_sub_4C1C50_004c1c50(p3fes::EEContext&);
void fn_sub_4C1D10_004c1d10(p3fes::EEContext&);
void fn_sub_4C1F70_004c1f70(p3fes::EEContext&);
void fn_sub_4C2090_004c2090(p3fes::EEContext&);
void fn_sub_4C20B0_004c20b0(p3fes::EEContext&);
void fn_sub_4C2120_004c2120(p3fes::EEContext&);
void fn_sub_4C2130_004c2130(p3fes::EEContext&);
void fn_sub_4C21B0_004c21b0(p3fes::EEContext&);
void fn_sub_4C3B50_004c3b50(p3fes::EEContext&);
void fn_sub_4C3B60_004c3b60(p3fes::EEContext&);
void fn_sub_4C3C30_004c3c30(p3fes::EEContext&);
void fn_sub_4C5250_004c5250(p3fes::EEContext&);
void fn_sub_4C53F0_004c53f0(p3fes::EEContext&);
void fn_sub_4C5620_004c5620(p3fes::EEContext&);
void fn_sub_4C5780_004c5780(p3fes::EEContext&);
void fn_sub_4C58A0_004c58a0(p3fes::EEContext&);
void fn_sub_4C5A50_004c5a50(p3fes::EEContext&);
void fn_sub_4C5C30_004c5c30(p3fes::EEContext&);
void fn_sub_4C64B0_004c64b0(p3fes::EEContext&);
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
void fn_sub_4C6B20_004c6b20(p3fes::EEContext&);
void fn_sub_4C7B60_004c7b60(p3fes::EEContext&);
void fn_sub_4C7D00_004c7d00(p3fes::EEContext&);
void fn_sub_4C81A0_004c81a0(p3fes::EEContext&);
void fn_sub_4CA000_004ca000(p3fes::EEContext&);
void fn_sub_4CA510_004ca510(p3fes::EEContext&);
void fn_sub_4CA520_004ca520(p3fes::EEContext&);
void fn_sub_4CA560_004ca560(p3fes::EEContext&);
void fn_sub_4CA5B0_004ca5b0(p3fes::EEContext&);
void fn_sub_4CB9F0_004cb9f0(p3fes::EEContext&);
void fn_sub_4CBE00_004cbe00(p3fes::EEContext&);
void fn_sub_4CBEB0_004cbeb0(p3fes::EEContext&);
void fn_sub_4CBF20_004cbf20(p3fes::EEContext&);
void fn_sub_4CC5C0_004cc5c0(p3fes::EEContext&);
void fn_sub_4CC6B0_004cc6b0(p3fes::EEContext&);
void fn_sub_4D0DC0_004d0dc0(p3fes::EEContext&);
void fn_sub_4D11F0_004d11f0(p3fes::EEContext&);
void fn_sub_4D13B0_004d13b0(p3fes::EEContext&);
void fn_sub_4D1900_004d1900(p3fes::EEContext&);
void fn_sub_4D1A50_004d1a50(p3fes::EEContext&);
void fn_sub_4D1C30_004d1c30(p3fes::EEContext&);
void fn_sub_4D1DF0_004d1df0(p3fes::EEContext&);
void fn_sub_4D1F10_004d1f10(p3fes::EEContext&);
void fn_sub_4D2030_004d2030(p3fes::EEContext&);
void fn_sub_4D2130_004d2130(p3fes::EEContext&);
void fn_sub_4D22F0_004d22f0(p3fes::EEContext&);
void fn_sub_4D2730_004d2730(p3fes::EEContext&);
void fn_sub_4D2900_004d2900(p3fes::EEContext&);
void fn_sub_4D2B50_004d2b50(p3fes::EEContext&);
void fn_sub_4D2D60_004d2d60(p3fes::EEContext&);
void fn_sub_4D2ED0_004d2ed0(p3fes::EEContext&);
void fn_sub_4D3040_004d3040(p3fes::EEContext&);
void fn_sub_4D3120_004d3120(p3fes::EEContext&);
void fn_sub_4D3220_004d3220(p3fes::EEContext&);
void fn_sub_4D3300_004d3300(p3fes::EEContext&);
void fn_sub_4D3800_004d3800(p3fes::EEContext&);
void fn_sub_4D3FC0_004d3fc0(p3fes::EEContext&);
void fn_sub_4D40E0_004d40e0(p3fes::EEContext&);
void fn_sub_4D41E0_004d41e0(p3fes::EEContext&);
void fn_sub_4D8320_004d8320(p3fes::EEContext&);
void fn_sub_4F22B0_004f22b0(p3fes::EEContext&);
void fn_sub_4F23C0_004f23c0(p3fes::EEContext&);
void fn_sub_4F2430_004f2430(p3fes::EEContext&);
void fn_sub_4F2730_004f2730(p3fes::EEContext&);
void fn_sub_4F2790_004f2790(p3fes::EEContext&);
void fn_sub_4F2870_004f2870(p3fes::EEContext&);
void fn_sub_4F28A0_004f28a0(p3fes::EEContext&);
void fn_sub_4F28D0_004f28d0(p3fes::EEContext&);
void fn_sub_4F28F0_004f28f0(p3fes::EEContext&);
void fn_sub_4F2990_004f2990(p3fes::EEContext&);
void fn_sub_4F2A00_004f2a00(p3fes::EEContext&);
void fn_sub_4F2AD0_004f2ad0(p3fes::EEContext&);
void fn_sub_4F2E60_004f2e60(p3fes::EEContext&);
void fn_sub_4F2F70_004f2f70(p3fes::EEContext&);
void fn_sub_4F3010_004f3010(p3fes::EEContext&);
void fn_sub_4F30E0_004f30e0(p3fes::EEContext&);
void fn_sub_4F3150_004f3150(p3fes::EEContext&);
void fn_sub_4F31C0_004f31c0(p3fes::EEContext&);
void fn_sub_4F3260_004f3260(p3fes::EEContext&);
void fn_sub_4F3410_004f3410(p3fes::EEContext&);
void fn_sub_4F3680_004f3680(p3fes::EEContext&);
void fn_sub_4F3880_004f3880(p3fes::EEContext&);
void fn_sub_4F3970_004f3970(p3fes::EEContext&);
void fn_sub_4F3D60_004f3d60(p3fes::EEContext&);
void fn_sub_4F3F70_004f3f70(p3fes::EEContext&);
void fn_sub_4F3F80_004f3f80(p3fes::EEContext&);
void fn_sub_4F4640_004f4640(p3fes::EEContext&);
void fn_sub_4F4830_004f4830(p3fes::EEContext&);
void fn_sub_4F4950_004f4950(p3fes::EEContext&);
void fn_sub_4F4C30_004f4c30(p3fes::EEContext&);
void fn_sub_4F4CF0_004f4cf0(p3fes::EEContext&);
void fn_sub_4F4DB0_004f4db0(p3fes::EEContext&);
void fn_sub_4F4FE0_004f4fe0(p3fes::EEContext&);
void fn_sub_4F50A0_004f50a0(p3fes::EEContext&);
void fn_sub_4F5520_004f5520(p3fes::EEContext&);
void fn_sub_4F57F0_004f57f0(p3fes::EEContext&);
void fn_sub_4F5A90_004f5a90(p3fes::EEContext&);
void fn_sub_4F5B80_004f5b80(p3fes::EEContext&);
void fn_sub_4F5C50_004f5c50(p3fes::EEContext&);
void fn_sub_4F5D90_004f5d90(p3fes::EEContext&);
void fn_sub_4F6140_004f6140(p3fes::EEContext&);
void fn_sub_4F61C0_004f61c0(p3fes::EEContext&);
void fn_sub_4F62D0_004f62d0(p3fes::EEContext&);
void fn_sub_4F63D0_004f63d0(p3fes::EEContext&);
void fn_sub_4F64F0_004f64f0(p3fes::EEContext&);
void fn_sub_4F65B0_004f65b0(p3fes::EEContext&);
void fn_sub_4F67B0_004f67b0(p3fes::EEContext&);
void fn_sub_4F6890_004f6890(p3fes::EEContext&);
void fn_sub_4F6970_004f6970(p3fes::EEContext&);
void fn_sub_4F6A10_004f6a10(p3fes::EEContext&);
void fn_sub_4F6B50_004f6b50(p3fes::EEContext&);
void fn_sub_4F6CE0_004f6ce0(p3fes::EEContext&);
void fn_sub_4F6F20_004f6f20(p3fes::EEContext&);
void fn_sub_4F7080_004f7080(p3fes::EEContext&);
void fn_sub_4F72C0_004f72c0(p3fes::EEContext&);
void fn_sub_4F72D0_004f72d0(p3fes::EEContext&);
void fn_sub_4F72E0_004f72e0(p3fes::EEContext&);
void fn_sub_4F72F0_004f72f0(p3fes::EEContext&);
void fn_worldForAllSectors_0049a870(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace rw4;
using namespace rw5;
using namespace rw6;
using namespace rw7;
using namespace rw8;

namespace gen = ::p3fes::recomp_gen;

// sub_45EC20 -- a float compare: 1 when the libgcc compare (dpcmp) of its operands is positive, else 0
// 0x0045EC20 sub_45EC20 -- 32 bytes; frame 0x10: ra sp+0x0
void sub_45EC20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0045ec20
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x45EC28u, gen::fn_dpcmp_005316d0);
    ld(ra, sp, 0x0);
    v0 = slt(0, v0);
    sp = addiu(sp, 0x10);
}


// sub_45F580 [plg11DStreamWrite] -- plugin 0x11D's stream write: when the object's extension word is set, a 4-byte header (sub_4CA510) and the extension's body (sub_45EE00)
// ($a0 = the stream, $a2 = the object, $a3 = the extension offset) The stream, or 0 on a write error.
// 0x0045F580 sub_45F580 -- 128 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_45F580(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0045f580
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = addu(a2, a3);
    lw(v0, s0, 0);
    s1 = a0;
    if (v0 != 0) {
        // 0x0045f5a8
        charge(ctx, 9);
        jal(ctx, 0x45F5A8u, gen::fn_sub_4CA510_004ca510);
        sw(v0, sp, 0x3C);
        a0 = s1;
        a1 = addiu(sp, 0x3C);
        a2 = 4;
        jal(ctx, 0x45F5BCu, gen::fn_sub_4C17F0_004c17f0);
        if (v0 != 0) {
            // 0x0045f5d4
            charge(ctx, 5);
            lw(a0, s0, 0);
            a1 = s1;
            jal(ctx, 0x45F5D8u, gen::fn_sub_45EE00_0045ee00);
            if (v0 != 0) {
                backedge(ctx);
                goto L_0045f5a0;
            }
            // 0x0045f5e8
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0045f5cc
            charge(ctx, 2);
            v0 = 0;
        }
        // 0x0045f5ec (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_0045f5a0:
    charge(ctx, 2);
    v0 = s1;
    // 0x0045f5ec (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_45F7D0 [plg11DPluginAttach] -- registers plugin 0x11D: the engine extension, the clump extension, the world-sector and atomic extensions with their stream callbacks
// The offsets go to gp 0x7CE720.. (engine, clump, sector, atomic); 1 when every registration succeeded, else 0.
// 0x0045F7D0 sub_45F7D0 -- 340 bytes; frame 0x10: ra sp+0x0
void sub_45F7D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0045f7d0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = 0x460000;
    a3 = 0x460000;
    sd(ra, sp, 0x0);
    a0 = 4;
    a1 = 285;
    a2 = addiu(a2, -2928);  // &sub_45F490
    a3 = addiu(a3, -2880);  // &sub_45F4C0
    jal(ctx, 0x45F7ECu, gen::fn_sub_4CA520_004ca520);
    sw(v0, gp, -17872);  // 0x7CE720 (plugin 0x11D's engine extension offset)
    v0 = slt(0, v0);
    if (v0 != 0) {
        // 0x0045f80c
        charge(ctx, 11);
        a2 = 0x460000;
        a0 = 4;
        a1 = 285;
        a2 = addiu(a2, -2128);  // &sub_45F7B0
        a3 = 0;
        t0 = 0;
        jal(ctx, 0x45F820u, gen::fn_sub_492C30_00492c30);
        sw(v0, gp, -17868);  // 0x7CE724 (plugin 0x11D's clump extension offset)
        v0 = slt(0, v0);
        if (v0 != 0) {
            // 0x0045f84c
            charge(ctx, 13);
            a2 = 0x460000;
            a3 = 0x460000;
            a0 = 4;
            a1 = 285;
            a2 = addiu(a2, -2768);  // &sub_45F530
            a3 = addiu(a3, -2848);  // &sub_45F4E0
            t0 = 0;
            jal(ctx, 0x45F864u, gen::fn_sub_499250_00499250);
            sw(v0, gp, -17860);  // 0x7CE72C (plugin 0x11D's atomic extension offset)
            v0 = slt(v0, 0);
            v0 = v0 ^ 0x1;
            if (v0 != 0) {
                // 0x0045f888
                charge(ctx, 11);
                a1 = 0x460000;
                a2 = 0x460000;
                a3 = 0x460000;
                a0 = 285;
                a1 = addiu(a1, -2560);  // &sub_45F600
                a2 = addiu(a2, -2688);  // &sub_45F580
                a3 = addiu(a3, -2752);  // &sub_45F540
                jal(ctx, 0x45F8A0u, gen::fn_sub_499280_00499280);
                v0 = slt(v0, 0);
                v0 = v0 ^ 0x1;
                backedge(ctx);
            }
            // 0x0045f880
            charge(ctx, 2);
            v0 = sltu(0, v0);
            backedge(ctx);
        }
        // 0x0045f838
        charge(ctx, 3);
        v0 = sltu(0, v0);
        if (v0 != 0) {
            // 0x0045f8b4
            charge(ctx, 13);
            a2 = 0x460000;
            a3 = 0x460000;
            a0 = 4;
            a1 = 285;
            a2 = addiu(a2, -2768);  // &sub_45F530
            a3 = addiu(a3, -2848);  // &sub_45F4E0
            t0 = 0;
            jal(ctx, 0x45F8CCu, gen::fn_sub_493C50_00493c50);
            sw(v0, gp, -17864);  // 0x7CE728 (plugin 0x11D's world-sector extension offset)
            v0 = slt(v0, 0);
            v0 = v0 ^ 0x1;
            if (v0 != 0) {
                // 0x0045f8f0
                charge(ctx, 11);
                a1 = 0x460000;
                a2 = 0x460000;
                a3 = 0x460000;
                a0 = 285;
                a1 = addiu(a1, -2560);  // &sub_45F600
                a2 = addiu(a2, -2688);  // &sub_45F580
                a3 = addiu(a3, -2752);  // &sub_45F540
                jal(ctx, 0x45F908u, gen::fn_sub_493C80_00493c80);
                v0 = slt(v0, 0);
                v0 = v0 ^ 0x1;
                backedge(ctx);
            }
            // 0x0045f8e8
            charge(ctx, 2);
            v0 = sltu(0, v0);
            backedge(ctx);
        }
        // 0x0045f844
        charge(ctx, 2);
        backedge(ctx);
    }
    // 0x0045f804
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    // 0x0045f91c
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}


// sub_46A600 [pdsEngineOpen] -- the PDS plugin's engine open: on the first open every registered pipe is built (sub_46AC30 on the registry 0x95C44C); the open count up; $a0
// 0x0046A600 sub_46A600 -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_46A600(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046a600
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, v0, -15288);  // 0x95C448 (the PDS plugin's open count)
    s0 = a0;
    if (v0 == 0) {
        // 0x0046a638
        charge(ctx, 5);
        a0 = 0x960000;
        a0 = addiu(a0, -15284);  // &0x95C44C (the PDS pipe registry {entries, count, capacity, built})
        jal(ctx, 0x46A63Cu, gen::fn_sub_46AC30_0046ac30);
        backedge(ctx);
    }
    // 0x0046a61c
    charge(ctx, 7);
    v1 = 0x960000;
    v0 = s0;
    lw(a0, v1, -15288);  // 0x95C448 (the PDS plugin's open count)
    v1 = 0x960000;
    a0 = addiu(a0, 1);
    sw(a0, v1, -15288);  // 0x95C448 (the PDS plugin's open count)
    // 0x0046a64c
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// RpPDSRegisterPipe -- registers a PDS pipe definition: the registry set up with its requested size when it has none (sub_46A970), then PDSRegistryAddPipe; $a0
// 0x0046A830 RpPDSRegisterPipe -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void RpPDSRegisterPipe(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046a830
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 0x960000;
    a0 = addiu(a0, -15284);  // &0x95C44C (the PDS pipe registry {entries, count, capacity, built})
    lw(v0, a0, 0);  // 0x95C44C (the PDS pipe registry {entries, count, capacity, built})
    if (v0 == 0) {
        // 0x0046a864
        charge(ctx, 5);
        v0 = 0x960000;
        link(ctx, 0x46A868u);  // $ra first: the delay slot below depends on it
        lw(a1, v0, -15268);  // 0x95C45C (the PDS registry's requested size)
        call(ctx, gen::fn_sub_46A970_0046a970);
        a0 = v0;
        backedge(ctx);
    }
    // 0x0046a854
    charge(ctx, 4);
    a1 = s0;
    jal(ctx, 0x46A854u, gen::fn_PDSRegistryAddPipe_0046aa80);
    v0 = s0;
    // 0x0046a878
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_46A8D0 [pdsObjPipeCreate] -- builds a type-2 (object) registry entry's pipe: its definition's material pipe set from the entry naming the aux id (0 for none), then sub_46AFA0; the pipe's plugin data = the entry's id
// ($a0 = the entry, $a1 = the registry) Entries of another type are left alone.
// 0x0046A8D0 sub_46A8D0 -- 160 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_46A8D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046a8d0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 2;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 12);
    if (a0 != v1) {
        // 0x0046a960
        charge(ctx, 1);
        ld(ra, sp, 0x10);
    } else {
        // 0x0046a8f0
        charge(ctx, 3);
        lw(a2, s0, pdsentry::kAuxId);
        lw(a0, s0, pdsentry::kDef);
        if (a2 == 0) {
            // 0x0046a958
            charge(ctx, 2);
            sw(zero, a0, 16);
            backedge(ctx);
        } else {
            // 0x0046a8fc
            charge(ctx, 4);
            lw(v1, a1, 4);
            at = sltu(0, v1);
            a3 = 0;
            if (at != 0) {
                // 0x0046a90c
                charge(ctx, 1);
                lw(a1, a1, 0);
                for (;;) {
                    // 0x0046a910
                    charge(ctx, 3);
                    lw(v0, a1, 8);
                    if (a2 == v0) {
                        goto L_0046a91c_5;
                    }
                    // 0x0046a928
                    charge(ctx, 4);
                    a3 = addiu(a3, 1);
                    v0 = sltu(a3, v1);
                    a1 = addiu(a1, 20);
                    if (v0 != 0) {
                        backedge(ctx);
                        continue;
                    }
                    break;
                }
            }
        }
    L_0046a938:
        charge(ctx, 8);
        jal(ctx, 0x46A938u, gen::fn_sub_46AFA0_0046afa0);
        sw(v0, s0, pdsentry::kPipe);
        lw(a0, s0, pdsentry::kId);
        lw(v1, s0, pdsentry::kPipe);
        sw(a0, v1, 48);
        ld(ra, sp, 0x10);
    }
    // 0x0046a964 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    return;
L_0046a91c_5:
    charge(ctx, 3);
    lw(v0, a1, 16);
    sw(v0, a0, 16);
    goto L_0046a938;
}


// PDSRegistryAddPipe -- adds a definition to the PDS registry: refused (error 0x131 / 2) when its id is there; the entries doubled (RwRealloc) when full; in a built registry the pipe is made at once
// ($a0 = the registry, $a1 = the 16-byte record {definition, aux id, id, type}) Type 1 through RpPDSSkyMatPipeCreate
// (the pipe's plugin data = the id), type 2 through sub_46A8D0, any other type error 0x131 / 1. The registry, or 0.
// 0x0046AA80 PDSRegistryAddPipe -- 420 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void PDSRegistryAddPipe(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046aa80
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    a2 = 0;
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(a0, a0, 4);
    at = sltu(0, a0);
    s1 = a1;
    if (at != 0) {
        // 0x0046aaac
        charge(ctx, 2);
        lw(a1, s2, pdsreg::kEntries);
        lw(v1, s1, pdsentry::kId);
        for (;;) {
            // 0x0046aab4
            charge(ctx, 3);
            lw(v0, a1, 8);
            if (v1 != v0) {
                // 0x0046aac0
                charge(ctx, 4);
                a2 = addiu(a2, 1);
                v0 = sltu(a2, a0);
                a1 = addiu(a1, 20);
                if (v0 != 0) {
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
    }
    // 0x0046aad0
    charge(ctx, 3);
    v0 = sltu(a2, a0);
    if (v0 != 0) {
        // 0x0046abb4
        charge(ctx, 9);
        v0 = 305;
        a0 = 2;
        link(ctx, 0x46ABBCu);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x48);
        call(ctx, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x4C);
        a0 = addiu(sp, 0x48);
        jal(ctx, 0x46ABC8u, gen::fn_sub_4C1C50_004c1c50);
        s2 = 0;
        backedge(ctx);
    L_0046aba8:
        charge(ctx, 1);
        v0 = s2;
    } else {
        // 0x0046aadc
        charge(ctx, 3);
        lw(v0, s2, pdsreg::kCapacity);
        if (a0 == v0) {
            // 0x0046abd8
            charge(ctx, 14);
            v1 = sll(v0, 1);
            sw(v1, s2, pdsreg::kCapacity);
            v0 = 0x1040000;
            lw(a1, s2, pdsreg::kCapacity);
            a2 = v0 | 0x131;  // &0x1040131
            v0 = 0x960000;
            lw(a0, s2, pdsreg::kEntries);
            lw(v0, v0, 384);  // 0x960180 (RwRealloc slot)
            v1 = sll(a1, 2);
            v1 = addu(v1, a1);
            a1 = sll(v1, 2);
            jalr(ctx, 0x46AC00u, v0.u());
            sw(v0, s2, pdsreg::kEntries);
            backedge(ctx);
        }
        // 0x0046aae8
        charge(ctx, 20);
        lw(a0, s2, pdsreg::kCount);
        v1 = addiu(a0, 1);
        v0 = sll(a0, 2);
        v0 = addu(v0, a0);
        sw(v1, s2, pdsreg::kCount);
        a0 = sll(v0, 2);
        lw(v1, s2, pdsreg::kEntries);
        lw(v0, s1, pdsentry::kId);
        s0 = addu(v1, a0);
        sw(v0, s0, pdsentry::kId);
        lw(v0, s1, pdsentry::kType);
        sw(v0, s0, pdsentry::kType);
        lw(v0, s1, pdsentry::kDef);
        sw(v0, s0, pdsentry::kDef);
        lw(v0, s1, pdsentry::kAuxId);
        sw(v0, s0, pdsentry::kAuxId);
        sw(zero, s0, pdsentry::kPipe);
        lw(v0, s2, pdsreg::kWord12);
        if (v0 == 0) {
            goto L_0046aba8;
        }
        // 0x0046ab38
        charge(ctx, 4);
        lw(v1, s0, pdsentry::kType);
        v0 = 2;
        if (v1 != v0) {
            // 0x0046ab48
            charge(ctx, 3);
            a0 = 1;
            if (v1 == a0) {
                // 0x0046ab5c
                charge(ctx, 2);
                if (v1 == a0) {
                    // 0x0046ab64
                    charge(ctx, 7);
                    link(ctx, 0x46AB64u);  // $ra first: the delay slot below depends on it
                    lw(a0, s0, pdsentry::kDef);
                    call(ctx, gen::fn_RpPDSSkyMatPipeCreate_0046ad80);
                    sw(v0, s0, pdsentry::kPipe);
                    lw(v1, s0, pdsentry::kId);
                    lw(v0, s0, pdsentry::kPipe);
                    sw(v1, v0, 48);
                }
            } else {
                // 0x0046ab54
                charge(ctx, 2);
                v0 = 305;
                // 0x0046ab94
                charge(ctx, 5);
                link(ctx, 0x46AB94u);  // $ra first: the delay slot below depends on it
                sw(v0, sp, 0x40);
                call(ctx, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x44);
                a0 = addiu(sp, 0x40);
                jal(ctx, 0x46ABA0u, gen::fn_sub_4C1C50_004c1c50);
            }
            goto L_0046aba8;
        }
        // 0x0046ab80
        charge(ctx, 5);
        a0 = s0;
        a1 = s2;
        jal(ctx, 0x46AB84u, gen::fn_sub_46A8D0_0046a8d0);
        v0 = s2;
    }
    // 0x0046abac
    charge(ctx, 2);
    ld(ra, sp, 0x30);
    // 0x0046ac10
    charge(ctx, 5);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_46AC30 [pdsRegistryBuildPipes] -- builds every registry entry's pipe: first the type-1 (material) pipes through RpPDSSkyMatPipeCreate (plugin data = the id), then every entry through sub_46A8D0; marks the registry built (+12 = 1)
// 0x0046AC30 sub_46AC30 -- 228 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_46AC30(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046ac30
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 4);
    at = sltu(0, v1);
    s2 = 0;
    if (at != 0) {
        // 0x0046ac5c
        charge(ctx, 1);
        s1 = 0;
        for (;;) {
            // 0x0046ac60
            charge(ctx, 6);
            lw(v1, s3, pdsreg::kEntries);
            v0 = 1;
            s0 = addu(v1, s1);
            lw(v1, s0, 12);
            if (v1 == v0) {
                // 0x0046acac
                charge(ctx, 7);
                link(ctx, 0x46ACACu);  // $ra first: the delay slot below depends on it
                lw(a0, s0, 0);
                call(ctx, gen::fn_RpPDSSkyMatPipeCreate_0046ad80);
                sw(v0, s0, 16);
                lw(v1, s0, 8);
                lw(v0, s0, 16);
                sw(v1, v0, 48);
                backedge(ctx);
            }
            // 0x0046ac78
            charge(ctx, 5);
            lw(v1, s3, pdsreg::kCount);
            s2 = addiu(s2, 1);
            v0 = sltu(s2, v1);
            s1 = addiu(s1, 20);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0046ac8c
        charge(ctx, 1);
    }
    // 0x0046ac90
    charge(ctx, 3);
    v0 = sltu(0, v1);
    s0 = 0;
    if (v0 != 0) {
        // 0x0046acc8
        charge(ctx, 1);
        s1 = 0;
        for (;;) {
            // 0x0046accc
            charge(ctx, 9);
            lw(v0, s3, pdsreg::kEntries);
            a1 = s3;
            a0 = addu(v0, s1);
            jal(ctx, 0x46ACD4u, gen::fn_sub_46A8D0_0046a8d0);
            lw(v0, s3, pdsreg::kCount);
            s0 = addiu(s0, 1);
            v0 = sltu(s0, v0);
            s1 = addiu(s1, 20);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0046acf0
        charge(ctx, 2);
        v1 = 1;
        backedge(ctx);
    } else {
        // 0x0046ac9c
        charge(ctx, 1);
        v1 = 1;
    }
    // 0x0046aca0
    charge(ctx, 3);
    v0 = s3;
    sw(v1, s3, pdsreg::kWord12);
    // 0x0046acf8
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// RpPDSSkyMatPipeCreate -- builds a PS2AllMat material pipeline from a 132-byte PDS definition: create, lock, the PS2AllMat node, its clusters, the batch set-up of the primitive type, unlock, then the VIF offset, VU1 code array and five callbacks
// ($a0 = the definition) The plugin id / data from +0 / +4; up to ten clusters (+8, {cluster, type}) through
// sub_4A35C0; primitive type +88: 1 / 2 lines (sub_4A3A80), 3..5 triangles (sub_4A38F0), 6 points (sub_4A3C10), any
// other error 0x131 / 0; after the unlock the node is found again by name (the unlock moved it) and configured. The
// pipeline.
// 0x0046AD80 RpPDSSkyMatPipeCreate -- 540 bytes; frame 0x90: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void RpPDSSkyMatPipeCreate(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046ad80
    enter(ctx, 35);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    link(ctx, 0x46ADA4u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4F2F70_004f2f70);
    lw(v1, s4, pdsmatdef::kPluginId);
    s5 = v0;
    a0 = s5;
    sw(v1, v0, 44);
    lw(v1, s4, pdsmatdef::kPluginData);
    link(ctx, 0x46ADC0u);  // $ra first: the delay slot below depends on it
    sw(v1, v0, 48);
    call(ctx, gen::fn_sub_4F4640_004f4640);
    s0 = v0;
    jal(ctx, 0x46ADC8u, gen::fn_sceLibgcc32GetErxEntries_0_004a3f10);
    s3 = v0;
    a0 = s0;
    a1 = 0;
    a2 = s3;
    a3 = 0;
    jal(ctx, 0x46ADE0u, gen::fn_sub_4F4950_004f4950);
    lw(a1, s3, 0);
    s6 = v0;
    a0 = s6;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x46ADF8u, gen::fn_sub_4F4830_004f4830);
    s2 = v0;
    s1 = 0;
    s0 = s4;
    for (;;) {
        // 0x0046ae0c
        charge(ctx, 3);
        at = sltiu(s1, 10);
        if (at != 0) {
            // 0x0046ae18
            charge(ctx, 3);
            lw(a1, s0, 8);
            if (a1 != 0) {
                // 0x0046ae24
                charge(ctx, 6);
                lw(a2, s0, 12);
                a0 = s2;
                jal(ctx, 0x46AE28u, gen::fn_sub_4A35C0_004a35c0);
                s0 = addiu(s0, 8);
                s1 = addiu(s1, 1);
                backedge(ctx);
                continue;
            }
        }
        break;
    }
    // 0x0046af48
    charge(ctx, 4);
    lw(v1, s4, pdsmatdef::kPrimType);
    at = sltiu(v1, 7);
    if (at == 0) {
        backedge(ctx);
    } else {
        // 0x0046af58
        charge(ctx, 7);
        a0 = 0x7C0000;
        v1 = sll(v1, 2);
        a0 = addiu(a0, -14112);  // &0x7BC8E0
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x46AE40u:  // table[1, 2]
            backedge(ctx);
            // 0x0046ae40
            charge(ctx, 7);
            lw(a1, s4, pdsmatdef::kBatch0);
            lw(a2, s4, pdsmatdef::kBatch1);
            lw(a3, s4, pdsmatdef::kBatch2);
            a0 = s2;
            jal(ctx, 0x46AE4Cu, gen::fn_sub_4A3A80_004a3a80);
            a0 = s6;
            break;
        case 0x46AE5Cu:  // table[3, 4, 5]
            backedge(ctx);
            // 0x0046ae5c
            charge(ctx, 7);
            lw(a1, s4, pdsmatdef::kBatch0);
            lw(a2, s4, pdsmatdef::kBatch1);
            lw(a3, s4, pdsmatdef::kBatch2);
            a0 = s2;
            jal(ctx, 0x46AE68u, gen::fn_sub_4A38F0_004a38f0);
        L_0046aeac:
            charge(ctx, 1);
            a0 = s6;
            break;
        case 0x46AE78u:  // table[6]
            backedge(ctx);
            // 0x0046ae78
            charge(ctx, 6);
            lw(a1, s4, pdsmatdef::kBatch0);
            lw(a2, s4, pdsmatdef::kBatch1);
            a0 = s2;
            jal(ctx, 0x46AE80u, gen::fn_sub_4A3C10_004a3c10);
            goto L_0046aeac;
        case 0x46AE90u:  // table[0]
            backedge(ctx);
        L_0046ae90:
            charge(ctx, 7);
            v0 = 305;
            a0 = 0;
            link(ctx, 0x46AE98u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x88);
            call(ctx, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x8C);
            a0 = addiu(sp, 0x88);
            jal(ctx, 0x46AEA4u, gen::fn_sub_4C1C50_004c1c50);
            goto L_0046aeac;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
        goto L_0046aeb0;
    }
    goto L_0046ae90;
L_0046aeb0:
    charge(ctx, 38);
    jal(ctx, 0x46AEB0u, gen::fn_sub_4F3F80_004f3f80);
    lw(a1, s3, 0);
    a0 = v0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x46AEC4u, gen::fn_sub_4F4830_004f4830);
    lw(a1, s4, pdsmatdef::kVifOffset);
    a0 = v0;
    jal(ctx, 0x46AED0u, gen::fn_sub_4A3D70_004a3d70);
    s0 = v0;
    lw(v0, s4, pdsmatdef::kVU1Code);
    lw(a1, v0, 0);
    lw(a2, v0, 4);
    a0 = s0;
    jal(ctx, 0x46AEE8u, gen::fn_RxPipelineNodePS2AllMatSetVU1CodeArray_004a3db0);
    lw(a2, s4, pdsmatdef::kCallBack1);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x46AEF8u, gen::fn_sub_4A3E30_004a3e30);
    lw(a2, s4, pdsmatdef::kCallBack2);
    a0 = v0;
    a1 = 2;
    jal(ctx, 0x46AF08u, gen::fn_sub_4A3E30_004a3e30);
    lw(a2, s4, pdsmatdef::kCallBack3);
    a0 = v0;
    a1 = 3;
    jal(ctx, 0x46AF18u, gen::fn_sub_4A3E30_004a3e30);
    lw(a2, s4, pdsmatdef::kCallBack4);
    a0 = v0;
    a1 = 4;
    jal(ctx, 0x46AF28u, gen::fn_sub_4A3E30_004a3e30);
    lw(a2, s4, pdsmatdef::kCallBack5);
    a0 = v0;
    a1 = 5;
    jal(ctx, 0x46AF38u, gen::fn_sub_4A3E30_004a3e30);
    v0 = s5;
    // 0x0046af74
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}


// sub_46AFA0 [pdsObjPipeCreateFromDef] -- builds a PS2All object pipeline from a 20-byte PDS definition: create, lock, the PS2All node, unlock, then its two callbacks and its material pipeline
// ($a0 = the definition) The plugin id / data from +0 / +4; the callbacks +8 / +12 (sub_49FE40 types 1 / 2) and the
// material pipeline +16 (sub_49FEC0). The pipeline.
// 0x0046AFA0 sub_46AFA0 -- 188 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_46AFA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046afa0
    enter(ctx, 47);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    link(ctx, 0x46AFB4u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4F2F70_004f2f70);
    lw(v1, s2, pdsobjdef::kPluginId);
    s1 = v0;
    a0 = s1;
    sw(v1, v0, 44);
    lw(v1, s2, pdsobjdef::kPluginData);
    link(ctx, 0x46AFD0u);  // $ra first: the delay slot below depends on it
    sw(v1, v0, 48);
    call(ctx, gen::fn_sub_4F4640_004f4640);
    s0 = v0;
    jal(ctx, 0x46AFD8u, gen::fn_sceLibgcc32GetErxEntries_0049ff00);
    a0 = s0;
    a1 = 0;
    s0 = v0;
    a3 = 0;
    a2 = s0;
    jal(ctx, 0x46AFF0u, gen::fn_sub_4F4950_004f4950);
    a0 = v0;
    jal(ctx, 0x46AFF8u, gen::fn_sub_4F3F80_004f3f80);
    lw(a1, s0, 0);
    a0 = v0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x46B00Cu, gen::fn_sub_4F4830_004f4830);
    lw(a2, s2, pdsobjdef::kCallBack1);
    a0 = v0;
    a1 = 1;
    jal(ctx, 0x46B01Cu, gen::fn_sub_49FE40_0049fe40);
    lw(a2, s2, pdsobjdef::kCallBack2);
    a0 = v0;
    a1 = 2;
    jal(ctx, 0x46B02Cu, gen::fn_sub_49FE40_0049fe40);
    lw(a1, s2, pdsobjdef::kMatPipe);
    a0 = v0;
    jal(ctx, 0x46B038u, gen::fn_sub_49FEC0_0049fec0);
    v0 = s1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_474BB0 [ptankEngineOpen] -- PTank's engine open: a 24-byte record of six pipelines (RwMalloc) at engine + gp 0x7CE774, filled by the 3D and 2D sprite pipe builders, the tank pipe (+0) and the instancing pipe (+20); $a0, or 0
// 0x00474BB0 sub_474BB0 -- 164 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_474BB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00474bb0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x40000;
    sd(ra, sp, 0x20);
    a1 = v0 | 0x12F;
    sq(s1, sp, 0x10);
    v0 = 0x960000;
    sq(s0, sp, 0x0);
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    s0 = a0;
    a0 = 24;
    jalr(ctx, 0x474BD4u, v0.u());
    s1 = v0;
    if (s1 == 0) {
        // 0x00474c3c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00474be8
        charge(ctx, 21);
        lw(v1, gp, -17788);  // 0x7CE774 (the PTank engine offset (its six pipelines))
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        a0 = s1;
        v0 = addu(v0, v1);
        sw(s1, v0, 0);
        sw(zero, s1, ptankpipes::kSpr2dMat);
        sw(zero, s1, ptankpipes::kSpr2dObj);
        sw(zero, s1, ptankpipes::kSpr3dMat);
        sw(zero, s1, ptankpipes::kSpr3dObj);
        link(ctx, 0x474C10u);  // $ra first: the delay slot below depends on it
        sw(zero, s1, ptankpipes::kInstance);
        call(ctx, gen::fn_sub_47A3D0_0047a3d0);
        a0 = s1;
        jal(ctx, 0x474C18u, gen::fn_sub_479030_00479030);
        jal(ctx, 0x474C20u, gen::fn_sub_47AB70_0047ab70);
        link(ctx, 0x474C28u);  // $ra first: the delay slot below depends on it
        sw(v0, s1, ptankpipes::kTank);
        call(ctx, gen::fn_sub_47B1A0_0047b1a0);
        sw(v0, s1, ptankpipes::kInstance);
        v0 = s0;
    }
    // 0x00474c40 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_474C60 [ptankEngineClose] -- PTank's engine close: each of the six pipelines destroyed (RxPipelineDestroy) and the record freed; $a0
// 0x00474C60 sub_474C60 -- 204 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_474C60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00474c60
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x960000;
    sd(ra, sp, 0x20);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, -17788);  // 0x7CE774 (the PTank engine offset (its six pipelines))
    v0 = addu(v0, v1);
    lw(s1, v0, 0);
    s0 = a0;
    if (s1 != 0) {
        // 0x00474c8c
        charge(ctx, 3);
        lw(a0, s1, ptankpipes::kSpr2dObj);
        if (a0 != 0) {
            // 0x00474c98
            charge(ctx, 2);
            jal(ctx, 0x474C98u, gen::fn_sub_4F3010_004f3010);
        }
        // 0x00474ca0
        charge(ctx, 3);
        lw(a0, s1, ptankpipes::kSpr2dMat);
        if (a0 != 0) {
            // 0x00474cac
            charge(ctx, 2);
            jal(ctx, 0x474CACu, gen::fn_sub_4F3010_004f3010);
        }
        // 0x00474cb4
        charge(ctx, 3);
        lw(a0, s1, ptankpipes::kSpr3dObj);
        if (a0 != 0) {
            // 0x00474cc0
            charge(ctx, 2);
            jal(ctx, 0x474CC0u, gen::fn_sub_4F3010_004f3010);
        }
        // 0x00474cc8
        charge(ctx, 3);
        lw(a0, s1, ptankpipes::kSpr3dMat);
        if (a0 != 0) {
            // 0x00474cd4
            charge(ctx, 2);
            jal(ctx, 0x474CD4u, gen::fn_sub_4F3010_004f3010);
        }
        // 0x00474cdc
        charge(ctx, 3);
        lw(a0, s1, ptankpipes::kInstance);
        if (a0 != 0) {
            // 0x00474ce8
            charge(ctx, 2);
            jal(ctx, 0x474CE8u, gen::fn_sub_4F3010_004f3010);
        }
        // 0x00474cf0
        charge(ctx, 3);
        lw(a0, s1, ptankpipes::kTank);
        if (a0 != 0) {
            // 0x00474cfc
            charge(ctx, 2);
            jal(ctx, 0x474CFCu, gen::fn_sub_4F3010_004f3010);
        }
        // 0x00474d04
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        a0 = s1;
        jalr(ctx, 0x474D0Cu, v0.u());
    }
    // 0x00474d14 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// rpSpr2dGenCreatePS2AllMatPipe -- builds the 2D sprite PS2AllMat pipeline: the PS2AllMat node with four sprite clusters (their definitions refreshed from the static templates), point batches, the sprite VU1 code and callbacks
// The cluster definitions 0x95D3A0..0x95D3D0 get their names / attributes from 0x77E2C0..0x77E2F0 each time; the
// batch set-up sub_4A3C10(4, 53); after the unlock: VIF offset 212, the VU1 code 0x77B1E0 x 4, callbacks 2 / 3 / 4
// (sub_4A0CE0, sub_478440, sub_478520). The pipeline, or 0.
// 0x00478A70 rpSpr2dGenCreatePS2AllMatPipe -- 588 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void rpSpr2dGenCreatePS2AllMatPipe(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00478a70
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    link(ctx, 0x478A80u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4F2F70_004f2f70);
    s1 = v0;
    if (s1 != 0) {
        // 0x00478a94
        charge(ctx, 7);
        a0 = s1;
        jal(ctx, 0x478A94u, gen::fn_sub_4F4640_004f4640);
        s0 = v0;
        jal(ctx, 0x478A9Cu, gen::fn_sceLibgcc32GetErxEntries_0_004a3f10);
        s2 = v0;
        if (s2 != 0) {
            // 0x00478ab0
            charge(ctx, 122);
            a0 = s0;
            a1 = 0;
            a2 = s2;
            a3 = 0;
            jal(ctx, 0x478ABCu, gen::fn_sub_4F4950_004f4950);
            lw(a1, s2, 0);
            a0 = s0;
            a2 = 0;
            a3 = 0;
            jal(ctx, 0x478AD0u, gen::fn_sub_4F4830_004f4830);
            a0 = 0x960000;
            a1 = 0x780000;
            s1 = v0;
            a0 = addiu(a0, -11312);  // &0x95D3D0
            a1 = addiu(a1, -7456);  // &0x77E2E0
            a2 = 16;
            jal(ctx, 0x478AECu, gen::fn_memcpy_00521250);
            v1 = 0x6C000000;
            v0 = 0x960000;
            sw(v1, v0, -11352);  // 0x95D3A8
            a0 = 0x960000;
            v0 = 0x960000;
            a1 = 0x780000;
            lw(v1, v0, -11304);  // 0x95D3D8
            a0 = addiu(a0, -11328);  // &0x95D3C0
            a1 = addiu(a1, -7488);  // &0x77E2C0
            a2 = 16;
            v1 = v1 | 0x4;
            v0 = 0x960000;
            v1 = v1 | 0x1;
            v1 = v1 | 0x8;
            link(ctx, 0x478B2Cu);  // $ra first: the delay slot below depends on it
            sw(v1, v0, -11304);
            call(ctx, gen::fn_memcpy_00521250);
            v0 = 0x960000;
            a0 = 0x960000;
            lw(a3, v0, -11320);  // 0x95D3C8
            v1 = si(-8193);
            a1 = 0x780000;
            a0 = addiu(a0, -11344);  // &0x95D3B0
            a1 = addiu(a1, -7456);  // &0x77E2E0
            a2 = 16;
            v1 = a3 & v1;
            v0 = 0x960000;
            v1 = v1 | 0x4;
            v1 = v1 | 0x1;
            v1 = v1 | 0x8;
            link(ctx, 0x478B68u);  // $ra first: the delay slot below depends on it
            sw(v1, v0, -11320);
            call(ctx, gen::fn_memcpy_00521250);
            v1 = 0x64000000;
            a0 = 0x960000;
            v1 = v1 | 0x4;
            a1 = 0x780000;
            v1 = v1 | 0x1;
            v0 = 0x960000;
            v1 = v1 | 0x8;
            a0 = addiu(a0, -11360);  // &0x95D3A0
            a1 = addiu(a1, -7440);  // &0x77E2F0
            a2 = 16;
            link(ctx, 0x478B98u);  // $ra first: the delay slot below depends on it
            sw(v1, v0, -11336);
            call(ctx, gen::fn_memcpy_00521250);
            v1 = 0x6C000000;
            a1 = 0x960000;
            v1 = v1 | 0x4;
            v0 = 0x960000;
            v1 = v1 | 0x1;
            a0 = s1;
            v1 = v1 | 0x8;
            a1 = addiu(a1, -11312);  // &0x95D3D0
            a2 = 8;
            link(ctx, 0x478BC4u);  // $ra first: the delay slot below depends on it
            sw(v1, v0, -11352);
            call(ctx, gen::fn_sub_4A35C0_004a35c0);
            a1 = 0x960000;
            a0 = s1;
            a1 = addiu(a1, -11328);  // &0x95D3C0
            a2 = 4;
            jal(ctx, 0x478BD8u, gen::fn_sub_4A35C0_004a35c0);
            a1 = 0x960000;
            a0 = s1;
            a1 = addiu(a1, -11344);  // &0x95D3B0
            a2 = 6;
            jal(ctx, 0x478BECu, gen::fn_sub_4A35C0_004a35c0);
            a1 = 0x960000;
            a0 = s1;
            a1 = addiu(a1, -11360);  // &0x95D3A0
            a2 = 7;
            jal(ctx, 0x478C00u, gen::fn_sub_4A35C0_004a35c0);
            a0 = s1;
            a1 = 4;
            a2 = 53;
            jal(ctx, 0x478C10u, gen::fn_sub_4A3C10_004a3c10);
            a0 = s0;
            jal(ctx, 0x478C18u, gen::fn_sub_4F3F80_004f3f80);
            lw(a1, s2, 0);
            s1 = v0;
            a0 = s1;
            a2 = 0;
            a3 = 0;
            jal(ctx, 0x478C30u, gen::fn_sub_4F4830_004f4830);
            s0 = v0;
            a1 = 212;
            a0 = s0;
            jal(ctx, 0x478C40u, gen::fn_sub_4A3D70_004a3d70);
            a1 = 0x780000;
            a0 = s0;
            a1 = addiu(a1, -20000);  // &0x77B1E0
            a2 = 4;
            jal(ctx, 0x478C54u, gen::fn_RxPipelineNodePS2AllMatSetVU1CodeArray_004a3db0);
            a2 = 0x4A0000;
            a0 = s0;
            a1 = 2;
            a2 = addiu(a2, 3296);  // &sub_4A0CE0
            jal(ctx, 0x478C68u, gen::fn_sub_4A3E30_004a3e30);
            a2 = 0x480000;
            a0 = s0;
            a1 = 3;
            a2 = addiu(a2, -31680);  // &sub_478440
            jal(ctx, 0x478C7Cu, gen::fn_sub_4A3E30_004a3e30);
            a2 = 0x480000;
            a0 = s0;
            a1 = 4;
            a2 = addiu(a2, -31456);  // &sub_478520
            jal(ctx, 0x478C90u, gen::fn_sub_4A3E30_004a3e30);
            goto L_00478c98;
        }
        // 0x00478ca0
        charge(ctx, 1);
        v0 = 0;
        // 0x00478ca4 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_00478c98:
    charge(ctx, 2);
    v0 = s1;
    // 0x00478ca4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_479030 [ptankSpr2dPipesCreate] -- builds PTank's 2D sprite pipes: the PS2AllMat pipe (+4) and its PS2All object pipe (+8: callback 1 sub_478CC0, the material pipe); 1 when the object pipe was made
// 0x00479030 sub_479030 -- 308 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_479030(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00479030
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = 0;
    jal(ctx, 0x479054u, gen::fn_rpSpr2dGenCreatePS2AllMatPipe_00478a70);
    sw(v0, s2, ptankpipes::kSpr2dMat);
    lw(s3, s2, ptankpipes::kSpr2dMat);
    if (s3 != 0) {
        // 0x0047906c
        charge(ctx, 5);
        jal(ctx, 0x47906Cu, gen::fn_sub_4F2F70_004f2f70);
        s0 = v0;
        if (s0 != 0) {
            // 0x00479080
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x479080u, gen::fn_sub_4F4640_004f4640);
            s4 = v0;
            if (s4 != 0) {
                // 0x00479094
                charge(ctx, 18);
                jal(ctx, 0x479094u, gen::fn_sceLibgcc32GetErxEntries_0049ff00);
                s5 = v0;
                a0 = s4;
                a1 = 0;
                a2 = s5;
                a3 = 0;
                jal(ctx, 0x4790ACu, gen::fn_sub_4F4950_004f4950);
                lw(a1, s5, 0);
                s4 = v0;
                a0 = s4;
                a2 = 0;
                a3 = 0;
                jal(ctx, 0x4790C4u, gen::fn_sub_4F4830_004f4830);
                a0 = s4;
                jal(ctx, 0x4790CCu, gen::fn_sub_4F3F80_004f3f80);
                if (v0 == 0) {
                    goto L_00479130;
                }
                // 0x004790dc
                charge(ctx, 14);
                lw(a1, s5, 0);
                a0 = v0;
                a2 = 0;
                a3 = 0;
                jal(ctx, 0x4790E8u, gen::fn_sub_4F4830_004f4830);
                s4 = v0;
                a2 = 0x480000;
                a1 = 1;
                a0 = s4;
                a2 = addiu(a2, -29504);  // &sub_478CC0
                jal(ctx, 0x479100u, gen::fn_sub_49FE40_0049fe40);
                a0 = s4;
                a1 = s3;
                jal(ctx, 0x47910Cu, gen::fn_sub_49FEC0_0049fec0);
                goto L_00479114;
            }
        L_00479130:
            charge(ctx, 2);
            a0 = s0;
            jal(ctx, 0x479130u, gen::fn_sub_4F3010_004f3010);
        }
        // 0x00479138
        charge(ctx, 2);
        s0 = 0;
        backedge(ctx);
    L_00479114:
        charge(ctx, 4);
        sw(s0, s2, ptankpipes::kSpr2dObj);
        lw(v0, s2, ptankpipes::kSpr2dObj);
        if (v0 != 0) {
            // 0x00479124
            charge(ctx, 1);
            s1 = 1;
        }
    }
    // 0x00479128
    charge(ctx, 2);
    v0 = s1;
    // 0x00479140
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


// rpSpr3dGenCreatePS2AllMatPipe -- builds the 3D sprite PS2AllMat pipeline: as the 2D one with the 3D sprite clusters (0x95D3E0..0x95D400) and VU1 code
// The pipeline, or 0.
// 0x00479E50 rpSpr3dGenCreatePS2AllMatPipe -- 504 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void rpSpr3dGenCreatePS2AllMatPipe(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00479e50
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    link(ctx, 0x479E60u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4F2F70_004f2f70);
    s1 = v0;
    if (s1 != 0) {
        // 0x00479e74
        charge(ctx, 7);
        a0 = s1;
        jal(ctx, 0x479E74u, gen::fn_sub_4F4640_004f4640);
        s0 = v0;
        jal(ctx, 0x479E7Cu, gen::fn_sceLibgcc32GetErxEntries_0_004a3f10);
        s2 = v0;
        if (s2 != 0) {
            // 0x00479e90
            charge(ctx, 101);
            a0 = s0;
            a1 = 0;
            a2 = s2;
            a3 = 0;
            jal(ctx, 0x479E9Cu, gen::fn_sub_4F4950_004f4950);
            lw(a1, s2, 0);
            a0 = s0;
            a2 = 0;
            a3 = 0;
            jal(ctx, 0x479EB0u, gen::fn_sub_4F4830_004f4830);
            a0 = 0x960000;
            a1 = 0x780000;
            s1 = v0;
            a0 = addiu(a0, -11264);  // &0x95D400
            a1 = addiu(a1, -7536);  // &0x77E290
            a2 = 16;
            jal(ctx, 0x479ECCu, gen::fn_memcpy_00521250);
            v1 = 0x6C000000;
            a0 = 0x960000;
            v1 = v1 | 0x4;
            a1 = 0x780000;
            v1 = v1 | 0x1;
            v0 = 0x960000;
            v1 = v1 | 0x8;
            a0 = addiu(a0, -11280);  // &0x95D3F0
            a1 = addiu(a1, -7488);  // &0x77E2C0
            a2 = 16;
            link(ctx, 0x479EFCu);  // $ra first: the delay slot below depends on it
            sw(v1, v0, -11256);
            call(ctx, gen::fn_memcpy_00521250);
            v0 = 0x960000;
            a0 = 0x960000;
            lw(a3, v0, -11272);  // 0x95D3F8
            v1 = si(-8193);
            a1 = 0x780000;
            a0 = addiu(a0, -11296);  // &0x95D3E0
            a1 = addiu(a1, -7440);  // &0x77E2F0
            a2 = 16;
            v1 = a3 & v1;
            v0 = 0x960000;
            v1 = v1 | 0x4;
            v1 = v1 | 0x1;
            v1 = v1 | 0x8;
            link(ctx, 0x479F38u);  // $ra first: the delay slot below depends on it
            sw(v1, v0, -11272);
            call(ctx, gen::fn_memcpy_00521250);
            v1 = 0x64000000;
            a1 = 0x960000;
            v1 = v1 | 0x4;
            v0 = 0x960000;
            v1 = v1 | 0x1;
            a0 = s1;
            v1 = v1 | 0x8;
            a1 = addiu(a1, -11280);  // &0x95D3F0
            a2 = 4;
            link(ctx, 0x479F64u);  // $ra first: the delay slot below depends on it
            sw(v1, v0, -11288);
            call(ctx, gen::fn_sub_4A35C0_004a35c0);
            a1 = 0x960000;
            a0 = s1;
            a1 = addiu(a1, -11264);  // &0x95D400
            a2 = 6;
            jal(ctx, 0x479F78u, gen::fn_sub_4A35C0_004a35c0);
            a1 = 0x960000;
            a0 = s1;
            a1 = addiu(a1, -11296);  // &0x95D3E0
            a2 = 7;
            jal(ctx, 0x479F8Cu, gen::fn_sub_4A35C0_004a35c0);
            a0 = s1;
            a1 = 3;
            a2 = 80;
            jal(ctx, 0x479F9Cu, gen::fn_sub_4A3C10_004a3c10);
            a0 = s0;
            jal(ctx, 0x479FA4u, gen::fn_sub_4F3F80_004f3f80);
            lw(a1, s2, 0);
            s1 = v0;
            a0 = s1;
            a2 = 0;
            a3 = 0;
            jal(ctx, 0x479FBCu, gen::fn_sub_4F4830_004f4830);
            s0 = v0;
            a1 = 240;
            a0 = s0;
            jal(ctx, 0x479FCCu, gen::fn_sub_4A3D70_004a3d70);
            a1 = 0x780000;
            a0 = s0;
            a1 = addiu(a1, -19984);  // &0x77B1F0
            a2 = 4;
            jal(ctx, 0x479FE0u, gen::fn_RxPipelineNodePS2AllMatSetVU1CodeArray_004a3db0);
            a2 = 0x4A0000;
            a0 = s0;
            a1 = 2;
            a2 = addiu(a2, 3296);  // &sub_4A0CE0
            jal(ctx, 0x479FF4u, gen::fn_sub_4A3E30_004a3e30);
            a2 = 0x480000;
            a0 = s0;
            a1 = 3;
            a2 = addiu(a2, -26560);  // &sub_479840
            jal(ctx, 0x47A008u, gen::fn_sub_4A3E30_004a3e30);
            a2 = 0x480000;
            a0 = s0;
            a1 = 4;
            a2 = addiu(a2, -26368);  // &sub_479900
            jal(ctx, 0x47A01Cu, gen::fn_sub_4A3E30_004a3e30);
            goto L_0047a024;
        }
        // 0x0047a02c
        charge(ctx, 1);
        v0 = 0;
        // 0x0047a030 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_0047a024:
    charge(ctx, 2);
    v0 = s1;
    // 0x0047a030 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_47A3D0 [ptankSpr3dPipesCreate] -- builds PTank's 3D sprite pipes: the PS2AllMat pipe (+12) and its PS2All object pipe (+16: callback 1 sub_47A050, the material pipe); 1 when the object pipe was made
// 0x0047A3D0 sub_47A3D0 -- 308 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_47A3D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0047a3d0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = 0;
    jal(ctx, 0x47A3F4u, gen::fn_rpSpr3dGenCreatePS2AllMatPipe_00479e50);
    sw(v0, s2, ptankpipes::kSpr3dMat);
    lw(s3, s2, ptankpipes::kSpr3dMat);
    if (s3 != 0) {
        // 0x0047a40c
        charge(ctx, 5);
        jal(ctx, 0x47A40Cu, gen::fn_sub_4F2F70_004f2f70);
        s0 = v0;
        if (s0 != 0) {
            // 0x0047a420
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x47A420u, gen::fn_sub_4F4640_004f4640);
            s4 = v0;
            if (s4 != 0) {
                // 0x0047a434
                charge(ctx, 18);
                jal(ctx, 0x47A434u, gen::fn_sceLibgcc32GetErxEntries_0049ff00);
                s5 = v0;
                a0 = s4;
                a1 = 0;
                a2 = s5;
                a3 = 0;
                jal(ctx, 0x47A44Cu, gen::fn_sub_4F4950_004f4950);
                lw(a1, s5, 0);
                s4 = v0;
                a0 = s4;
                a2 = 0;
                a3 = 0;
                jal(ctx, 0x47A464u, gen::fn_sub_4F4830_004f4830);
                a0 = s4;
                jal(ctx, 0x47A46Cu, gen::fn_sub_4F3F80_004f3f80);
                if (v0 == 0) {
                    goto L_0047a4d0;
                }
                // 0x0047a47c
                charge(ctx, 14);
                lw(a1, s5, 0);
                a0 = v0;
                a2 = 0;
                a3 = 0;
                jal(ctx, 0x47A488u, gen::fn_sub_4F4830_004f4830);
                s4 = v0;
                a2 = 0x480000;
                a1 = 1;
                a0 = s4;
                a2 = addiu(a2, -24496);  // &sub_47A050
                jal(ctx, 0x47A4A0u, gen::fn_sub_49FE40_0049fe40);
                a0 = s4;
                a1 = s3;
                jal(ctx, 0x47A4ACu, gen::fn_sub_49FEC0_0049fec0);
                goto L_0047a4b4;
            }
        L_0047a4d0:
            charge(ctx, 2);
            a0 = s0;
            jal(ctx, 0x47A4D0u, gen::fn_sub_4F3010_004f3010);
        }
        // 0x0047a4d8
        charge(ctx, 2);
        s0 = 0;
        backedge(ctx);
    L_0047a4b4:
        charge(ctx, 4);
        sw(s0, s2, ptankpipes::kSpr3dObj);
        lw(v0, s2, ptankpipes::kSpr3dObj);
        if (v0 != 0) {
            // 0x0047a4c4
            charge(ctx, 1);
            s1 = 1;
        }
    }
    // 0x0047a4c8
    charge(ctx, 2);
    v0 = s1;
    // 0x0047a4e0
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


// sub_47AB70 [ptankTankPipeCreate] -- builds the tank pipeline: create, lock, the PS2PTank node fragment, unlock; the pipeline (stored at +0)
// 0x0047AB70 sub_47AB70 -- 120 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_47AB70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0047ab70
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    link(ctx, 0x47AB78u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4F2F70_004f2f70);
    s0 = v0;
    if (s0 != 0) {
        // 0x0047ab8c
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x47AB8Cu, gen::fn_sub_4F4640_004f4640);
        if (v0 != 0) {
            // 0x0047ab9c
            charge(ctx, 10);
            a2 = 0x780000;
            a0 = v0;
            a1 = 0;
            a2 = addiu(a2, -19952);  // &0x77B210
            a3 = 0;
            jal(ctx, 0x47ABACu, gen::fn_sub_4F4950_004f4950);
            a0 = v0;
            jal(ctx, 0x47ABB4u, gen::fn_sub_4F3F80_004f3f80);
            if (v0 == 0) {
                goto L_0047abcc;
            }
            // 0x0047abc4
            charge(ctx, 2);
            v0 = s0;
            // 0x0047abd8 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x20);
            return;
        }
    L_0047abcc:
        charge(ctx, 2);
        a0 = s0;
        jal(ctx, 0x47ABCCu, gen::fn_sub_4F3010_004f3010);
    }
    // 0x0047abd4
    charge(ctx, 1);
    v0 = 0;
    // 0x0047abd8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_47B1A0 [ptankInstancePipeCreate] -- builds PTank's instancing pipeline: a PS2All object pipe with callback 1 sub_47ABF0; the pipeline (stored at +20), or 0
// 0x0047B1A0 sub_47B1A0 -- 212 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_47B1A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0047b1a0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    link(ctx, 0x47B1B0u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4F2F70_004f2f70);
    s2 = v0;
    if (s2 != 0) {
        // 0x0047b1c4
        charge(ctx, 5);
        a0 = s2;
        jal(ctx, 0x47B1C4u, gen::fn_sub_4F4640_004f4640);
        s0 = v0;
        if (s0 != 0) {
            // 0x0047b1d8
            charge(ctx, 18);
            jal(ctx, 0x47B1D8u, gen::fn_sceLibgcc32GetErxEntries_0049ff00);
            s1 = v0;
            a0 = s0;
            a1 = 0;
            a2 = s1;
            a3 = 0;
            jal(ctx, 0x47B1F0u, gen::fn_sub_4F4950_004f4950);
            lw(a1, s1, 0);
            s0 = v0;
            a0 = s0;
            a2 = 0;
            a3 = 0;
            jal(ctx, 0x47B208u, gen::fn_sub_4F4830_004f4830);
            a0 = s0;
            jal(ctx, 0x47B210u, gen::fn_sub_4F3F80_004f3f80);
            if (v0 == 0) {
                goto L_0047b250;
            }
            // 0x0047b220
            charge(ctx, 12);
            lw(a1, s1, 0);
            a0 = v0;
            a2 = 0;
            a3 = 0;
            jal(ctx, 0x47B22Cu, gen::fn_sub_4F4830_004f4830);
            a2 = 0x480000;
            a0 = v0;
            a1 = 1;
            a2 = addiu(a2, -21520);  // &sub_47ABF0
            jal(ctx, 0x47B240u, gen::fn_sub_49FE40_0049fe40);
            v0 = s2;
            // 0x0047b25c (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_0047b250:
        charge(ctx, 2);
        a0 = s2;
        jal(ctx, 0x47B250u, gen::fn_sub_4F3010_004f3010);
    }
    // 0x0047b258
    charge(ctx, 1);
    v0 = 0;
    // 0x0047b25c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_48F030 [rpUserDataPluginAttach] -- registers RpUserData (plugin 0x11F): the engine open / close and the 8-byte user-data list with its stream callbacks on nine object types
// Frames, clumps, atomics, world sectors, cameras, lights, geometries, materials, textures (each a 4-byte
// extension and its read / write / size callbacks); the offsets go to gp 0x7CE7B8..; 1, or 0 at the first failure.
// 0x0048F030 sub_48F030 -- 776 bytes; frame 0x10: ra sp+0x0
void sub_48F030(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0048f030
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = 0x490000;
    a3 = 0x490000;
    sd(ra, sp, 0x0);
    a0 = 0;
    a1 = 287;
    a2 = addiu(a2, -8912);  // &sub_48DD30
    a3 = addiu(a3, -8880);  // &sub_48DD50
    jal(ctx, 0x48F04Cu, gen::fn_sub_4CA520_004ca520);
    if (i64(v0) >= 0) {
        // 0x0048f064
        charge(ctx, 11);
        a2 = 0x490000;
        a3 = 0x490000;
        t0 = 0x490000;
        a0 = 8;
        a1 = 287;
        a2 = addiu(a2, -5488);  // &sub_48EA90
        a3 = addiu(a3, -5456);  // &sub_48EAB0
        t0 = addiu(t0, -5296);  // &sub_48EB50
        jal(ctx, 0x48F080u, gen::fn_sub_493C50_00493c50);
        sw(v0, gp, -17720);  // 0x7CE7B8
        if (i64(v0) >= 0) {
            // 0x0048f098
            charge(ctx, 10);
            a1 = 0x490000;
            a2 = 0x490000;
            a3 = 0x490000;
            a0 = 287;
            a1 = addiu(a1, -5088);  // &sub_48EC20
            a2 = addiu(a2, -4880);  // &sub_48ECF0
            a3 = addiu(a3, -4832);  // &sub_48ED20
            jal(ctx, 0x48F0B0u, gen::fn_sub_493C80_00493c80);
            sw(v0, gp, -17716);  // 0x7CE7BC
            if (i64(v0) >= 0) {
                // 0x0048f0c8
                charge(ctx, 13);
                a2 = 0x490000;
                a3 = 0x490000;
                t0 = 0x490000;
                a0 = 8;
                a1 = 287;
                a2 = addiu(a2, -5488);  // &sub_48EA90
                a3 = addiu(a3, -5456);  // &sub_48EAB0
                t0 = addiu(t0, -5296);  // &sub_48EB50
                jal(ctx, 0x48F0E4u, gen::fn_sub_499250_00499250);
                sw(v0, gp, -17712);  // 0x7CE7C0
                lw(v0, gp, -17720);  // 0x7CE7B8
                if (i64(v0) >= 0) {
                    // 0x0048f104
                    charge(ctx, 12);
                    a1 = 0x490000;
                    a2 = 0x490000;
                    a3 = 0x490000;
                    a0 = 287;
                    a1 = addiu(a1, -5088);  // &sub_48EC20
                    a2 = addiu(a2, -4880);  // &sub_48ECF0
                    a3 = addiu(a3, -4832);  // &sub_48ED20
                    jal(ctx, 0x48F11Cu, gen::fn_sub_499280_00499280);
                    sw(v0, gp, -17708);  // 0x7CE7C4
                    lw(v0, gp, -17716);  // 0x7CE7BC
                    if (i64(v0) >= 0) {
                        // 0x0048f13c
                        charge(ctx, 11);
                        a2 = 0x490000;
                        a3 = 0x490000;
                        t0 = 0x490000;
                        a0 = 8;
                        a1 = 287;
                        a2 = addiu(a2, -5488);  // &sub_48EA90
                        a3 = addiu(a3, -5456);  // &sub_48EAB0
                        t0 = addiu(t0, -5296);  // &sub_48EB50
                        jal(ctx, 0x48F158u, gen::fn_sub_4CB9F0_004cb9f0);
                        sw(v0, gp, -17704);  // 0x7CE7C8
                        if (i64(v0) >= 0) {
                            // 0x0048f170
                            charge(ctx, 10);
                            a1 = 0x490000;
                            a2 = 0x490000;
                            a3 = 0x490000;
                            a0 = 287;
                            a1 = addiu(a1, -5088);  // &sub_48EC20
                            a2 = addiu(a2, -4880);  // &sub_48ECF0
                            a3 = addiu(a3, -4832);  // &sub_48ED20
                            jal(ctx, 0x48F188u, gen::fn_sub_4C7D00_004c7d00);
                            sw(v0, gp, -17700);  // 0x7CE7CC
                            if (i64(v0) >= 0) {
                                // 0x0048f1a0
                                charge(ctx, 11);
                                a2 = 0x490000;
                                a3 = 0x490000;
                                t0 = 0x490000;
                                a0 = 8;
                                a1 = 287;
                                a2 = addiu(a2, -5488);  // &sub_48EA90
                                a3 = addiu(a3, -5456);  // &sub_48EAB0
                                t0 = addiu(t0, -5296);  // &sub_48EB50
                                jal(ctx, 0x48F1BCu, gen::fn_sub_4CA000_004ca000);
                                sw(v0, gp, -17696);  // 0x7CE7D0
                                if (i64(v0) >= 0) {
                                    // 0x0048f1d4
                                    charge(ctx, 10);
                                    a1 = 0x490000;
                                    a2 = 0x490000;
                                    a3 = 0x490000;
                                    a0 = 287;
                                    a1 = addiu(a1, -5088);  // &sub_48EC20
                                    a2 = addiu(a2, -4880);  // &sub_48ECF0
                                    a3 = addiu(a3, -4832);  // &sub_48ED20
                                    jal(ctx, 0x48F1ECu, gen::fn_sub_4C7B60_004c7b60);
                                    sw(v0, gp, -17692);  // 0x7CE7D4
                                    if (i64(v0) >= 0) {
                                        // 0x0048f204
                                        charge(ctx, 11);
                                        a2 = 0x490000;
                                        a3 = 0x490000;
                                        t0 = 0x490000;
                                        a0 = 8;
                                        a1 = 287;
                                        a2 = addiu(a2, -5488);  // &sub_48EA90
                                        a3 = addiu(a3, -5456);  // &sub_48EAB0
                                        t0 = addiu(t0, -5296);  // &sub_48EB50
                                        jal(ctx, 0x48F220u, gen::fn_sub_494520_00494520);
                                        sw(v0, gp, -17688);  // 0x7CE7D8
                                        if (i64(v0) >= 0) {
                                            // 0x0048f238
                                            charge(ctx, 10);
                                            a1 = 0x490000;
                                            a2 = 0x490000;
                                            a3 = 0x490000;
                                            a0 = 287;
                                            a1 = addiu(a1, -5088);  // &sub_48EC20
                                            a2 = addiu(a2, -4880);  // &sub_48ECF0
                                            a3 = addiu(a3, -4832);  // &sub_48ED20
                                            jal(ctx, 0x48F250u, gen::fn_sub_494550_00494550);
                                            sw(v0, gp, -17684);  // 0x7CE7DC
                                            if (i64(v0) >= 0) {
                                                // 0x0048f268
                                                charge(ctx, 11);
                                                a2 = 0x490000;
                                                a3 = 0x490000;
                                                t0 = 0x490000;
                                                a0 = 8;
                                                a1 = 287;
                                                a2 = addiu(a2, -5488);  // &sub_48EA90
                                                a3 = addiu(a3, -5456);  // &sub_48EAB0
                                                t0 = addiu(t0, -5296);  // &sub_48EB50
                                                jal(ctx, 0x48F284u, gen::fn_sub_494DB0_00494db0);
                                                sw(v0, gp, -17680);  // 0x7CE7E0
                                                if (i64(v0) >= 0) {
                                                    // 0x0048f29c
                                                    charge(ctx, 10);
                                                    a1 = 0x490000;
                                                    a2 = 0x490000;
                                                    a3 = 0x490000;
                                                    a0 = 287;
                                                    a1 = addiu(a1, -5088);  // &sub_48EC20
                                                    a2 = addiu(a2, -4880);  // &sub_48ECF0
                                                    a3 = addiu(a3, -4832);  // &sub_48ED20
                                                    jal(ctx, 0x48F2B4u, gen::fn_sub_494DE0_00494de0);
                                                    sw(v0, gp, -17676);  // 0x7CE7E4
                                                    if (i64(v0) >= 0) {
                                                        // 0x0048f2cc
                                                        charge(ctx, 11);
                                                        a2 = 0x490000;
                                                        a3 = 0x490000;
                                                        t0 = 0x490000;
                                                        a0 = 8;
                                                        a1 = 287;
                                                        a2 = addiu(a2, -5488);  // &sub_48EA90
                                                        a3 = addiu(a3, -5456);  // &sub_48EAB0
                                                        t0 = addiu(t0, -5296);  // &sub_48EB50
                                                        jal(ctx, 0x48F2E8u, gen::fn_sub_4D13B0_004d13b0);
                                                        sw(v0, gp, -17672);  // 0x7CE7E8
                                                        if (i64(v0) >= 0) {
                                                            // 0x0048f300
                                                            charge(ctx, 11);
                                                            a1 = 0x490000;
                                                            a2 = 0x490000;
                                                            a3 = 0x490000;
                                                            a0 = 287;
                                                            a1 = addiu(a1, -5088);  // &sub_48EC20
                                                            a2 = addiu(a2, -4880);  // &sub_48ECF0
                                                            a3 = addiu(a3, -4832);  // &sub_48ED20
                                                            jal(ctx, 0x48F318u, gen::fn_sub_4C81A0_004c81a0);
                                                            sw(v0, gp, -17668);  // 0x7CE7EC
                                                            v0 = slt(v0, 0);
                                                            v0 = v0 ^ 0x1;
                                                        } else {
                                                            // 0x0048f2f8
                                                            charge(ctx, 2);
                                                            v0 = 0;
                                                        }
                                                    } else {
                                                        // 0x0048f2c4
                                                        charge(ctx, 2);
                                                        v0 = 0;
                                                    }
                                                } else {
                                                    // 0x0048f294
                                                    charge(ctx, 2);
                                                    v0 = 0;
                                                }
                                            } else {
                                                // 0x0048f260
                                                charge(ctx, 2);
                                                v0 = 0;
                                            }
                                        } else {
                                            // 0x0048f230
                                            charge(ctx, 2);
                                            v0 = 0;
                                        }
                                    } else {
                                        // 0x0048f1fc
                                        charge(ctx, 2);
                                        v0 = 0;
                                    }
                                } else {
                                    // 0x0048f1cc
                                    charge(ctx, 2);
                                    v0 = 0;
                                }
                            } else {
                                // 0x0048f198
                                charge(ctx, 2);
                                v0 = 0;
                            }
                        } else {
                            // 0x0048f168
                            charge(ctx, 2);
                            v0 = 0;
                        }
                    } else {
                        // 0x0048f134
                        charge(ctx, 2);
                        v0 = 0;
                    }
                } else {
                    // 0x0048f0fc
                    charge(ctx, 2);
                    v0 = 0;
                }
            } else {
                // 0x0048f0c0
                charge(ctx, 2);
                v0 = 0;
            }
        } else {
            // 0x0048f090
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x0048f05c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0048f32c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_48F580 [worldSectorStreamRead] -- reads an atomic world sector (chunk 9, versions 0x35000..0x37002): the 44-byte header, the sector's bounding box and counts, its vertices / normals / UVs / triangles, the collision and plugin data
// ($a0 = the stream, $a1 = the address cursor, $a2 = the world, $a3 = the world's flags) Takes the record from the
// cursor (advanced by the sector size of 0x77DDB0) and fills it; on a failure the partial sector is torn down
// (sub_499720 / sub_499850) and 0 is returned.
// 0x0048F580 sub_48F580 -- 1616 bytes; frame 0x120: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48F580(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0048f580
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    s7 = a2;
    sq(s5, sp, 0x50);
    s6 = a0;
    sq(s4, sp, 0x40);
    a2 = 0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a3;
    s1 = 1;
    a3 = addiu(sp, 0x11C);
    a1 = s1;
    link(ctx, 0x48F5C8u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1600_004c1600);
    if (v0 != 0) {
        // 0x0048f5d8
        charge(ctx, 6);
        lw(v1, sp, 0x11C);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x0048f5f0
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_0048f604;
            }
            // 0x0048f634
            charge(ctx, 7);
            a0 = s6;
            a1 = addiu(sp, 0xA0);
            a2 = 44;
            jal(ctx, 0x48F63Cu, gen::fn_sub_4C5250_004c5250);
            v1 = 44;
            if (v0 != v1) {
                // 0x0048f85c
                charge(ctx, 2);
                v0 = 0;
                goto L_0048fba0;
            }
            // 0x0048f650
            charge(ctx, 6);
            v0 = 0x780000;
            lw(s3, s4, 0);
            lw(v0, v0, -8784);  // 0x77DDB0 (the world-sector plugin registry (its extension size))
            v0 = addu(s3, v0);
            sw(v0, s4, 0);
            if (s3 == 0) {
                // 0x0048f864
                charge(ctx, 12);
                v0 = lui(0x8000);
                v1 = 2;
                a0 = v0 | 0x13;
                v0 = 0x780000;
                lw(a1, v0, -8784);  // 0x77DDB0 (the world-sector plugin registry (its extension size))
                link(ctx, 0x48F878u);  // $ra first: the delay slot below depends on it
                sw(v1, sp, 0x108);
                call(ctx, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x10C);
                a0 = addiu(sp, 0x108);
                jal(ctx, 0x48F884u, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
                goto L_0048fba0;
            }
            // 0x0048f668
            charge(ctx, 44);
            v0 = si(-1);
            fp = addiu(sp, 0xA4);
            sw(v0, s3, 0);
            s5 = addiu(sp, 0xA8);
            lwc1(f2, sp, 0xAC);
            a0 = addiu(s3, 16);
            lwc1(f1, sp, 0xB0);
            a1 = 0;
            lwc1(f0, sp, 0xB4);
            a2 = 32;
            swc1(f2, s3, 108);
            swc1(f1, s3, 112);
            swc1(f0, s3, 116);
            lwc1(f2, sp, 0xB8);
            lwc1(f1, sp, 0xBC);
            lwc1(f0, sp, 0xC0);
            swc1(f2, s3, 96);
            swc1(f1, s3, 100);
            swc1(f0, s3, 104);
            lw(v0, sp, 0xA0);
            sh(v0, s3, 128);
            lw(v0, fp, 0x0);
            sh(v0, s3, 132);
            lw(v0, s5, 0);
            sh(v0, s3, 130);
            sw(zero, s3, 4);
            sw(zero, s3, 8);
            sw(zero, s3, 48);
            link(ctx, 0x48F6D8u);  // $ra first: the delay slot below depends on it
            sw(zero, s3, 12);
            call(ctx, gen::fn_memset_00521408);
            sw(zero, s3, 124);
            a0 = addiu(s3, 56);
            sw(zero, s3, 52);
            v1 = addiu(s3, 64);
            sw(zero, s3, 120);
            v0 = 0x1000000;
            sw(a0, s3, 56);
            sw(a0, s3, 60);
            sw(v1, s3, 64);
            sw(v1, s3, 68);
            lw(v1, s7, 8);
            v0 = v1 & v0;
            if (v0 == 0) {
                // 0x0048f718
                charge(ctx, 3);
                lw(a0, s5, 0);
                if (a0 != 0) {
                    // 0x0048f894
                    charge(ctx, 10);
                    lw(v1, s4, 0);
                    v0 = sll(a0, 1);
                    v0 = addu(v0, a0);
                    s0 = sll(v0, 2);
                    v0 = addu(v1, s0);
                    sw(v0, s4, 0);
                    sw(v1, s3, 8);
                    lw(v0, s3, 8);
                    if (v0 == 0) {
                        // 0x0048f9e4
                        charge(ctx, 11);
                        v1 = 2;
                        v0 = lui(0x8000);
                        sw(v1, sp, 0x100);
                        a0 = v0 | 0x13;
                        a1 = s0;
                        jal(ctx, 0x48F9F4u, gen::fn_sub_4C1D10_004c1d10);
                        sw(v0, sp, 0x104);
                        a0 = addiu(sp, 0x100);
                        jal(ctx, 0x48FA00u, gen::fn_sub_4C1C50_004c1c50);
                        s1 = 0;
                        backedge(ctx);
                    }
                    // 0x0048f8bc
                    charge(ctx, 2);
                    if (s1 != 0) {
                        // 0x0048fa10
                        charge(ctx, 6);
                        lw(a1, s3, 8);
                        a2 = s0;
                        a0 = s6;
                        jal(ctx, 0x48FA18u, gen::fn_sub_4C18B0_004c18b0);
                        if (v0 != 0) {
                            backedge(ctx);
                        } else {
                            // 0x0048fa28
                            charge(ctx, 2);
                            s1 = 0;
                            backedge(ctx);
                        }
                    }
                    // 0x0048f8c4
                    charge(ctx, 2);
                    if (s1 != 0) {
                        // 0x0048f8cc
                        charge(ctx, 3);
                        v0 = s2 & 0x10;
                        if (v0 != 0) {
                            // 0x0048f8d8
                            charge(ctx, 9);
                            lw(v0, s5, 0);
                            lw(v1, s4, 0);
                            s0 = sll(v0, 2);
                            v0 = addu(v1, s0);
                            sw(v0, s4, 0);
                            sw(v1, s3, 12);
                            lw(v0, s3, 12);
                            if (v0 == 0) {
                                // 0x0048fa30
                                charge(ctx, 11);
                                v1 = 2;
                                v0 = lui(0x8000);
                                sw(v1, sp, 0xF8);
                                a0 = v0 | 0x13;
                                a1 = s0;
                                jal(ctx, 0x48FA40u, gen::fn_sub_4C1D10_004c1d10);
                                sw(v0, sp, 0xFC);
                                a0 = addiu(sp, 0xF8);
                                jal(ctx, 0x48FA4Cu, gen::fn_sub_4C1C50_004c1c50);
                                s1 = 0;
                                backedge(ctx);
                            }
                            // 0x0048f8fc
                            charge(ctx, 2);
                            if (s1 != 0) {
                                // 0x0048f904
                                charge(ctx, 6);
                                lw(a1, s3, 12);
                                a0 = s6;
                                a2 = s0;
                                jal(ctx, 0x48F90Cu, gen::fn_sub_4C5250_004c5250);
                                if (s0 != v0) {
                                    // 0x0048f91c
                                    charge(ctx, 1);
                                    s1 = 0;
                                }
                            }
                        }
                    }
                    // 0x0048f920
                    charge(ctx, 2);
                    if (s1 != 0) {
                        // 0x0048f928
                        charge(ctx, 3);
                        v0 = s2 & 0x8;
                        if (v0 != 0) {
                            // 0x0048f934
                            charge(ctx, 9);
                            lw(v0, s5, 0);
                            lw(v1, s4, 0);
                            s0 = sll(v0, 2);
                            v0 = addu(v1, s0);
                            sw(v0, s4, 0);
                            sw(v1, s3, 48);
                            lw(v0, s3, 48);
                            if (v0 == 0) {
                                // 0x0048fa5c
                                charge(ctx, 11);
                                v1 = 2;
                                v0 = lui(0x8000);
                                sw(v1, sp, 0xF0);
                                a0 = v0 | 0x13;
                                a1 = s0;
                                jal(ctx, 0x48FA6Cu, gen::fn_sub_4C1D10_004c1d10);
                                sw(v0, sp, 0xF4);
                                a0 = addiu(sp, 0xF0);
                                jal(ctx, 0x48FA78u, gen::fn_sub_4C1C50_004c1c50);
                                s1 = 0;
                                backedge(ctx);
                            }
                            // 0x0048f958
                            charge(ctx, 2);
                            if (s1 != 0) {
                                // 0x0048f960
                                charge(ctx, 6);
                                lw(a1, s3, 48);
                                a2 = s0;
                                a0 = s6;
                                jal(ctx, 0x48F968u, gen::fn_sub_4C5250_004c5250);
                                if (v0 == 0) {
                                    // 0x0048f978
                                    charge(ctx, 1);
                                    s1 = 0;
                                }
                            }
                        }
                    }
                    // 0x0048f97c
                    charge(ctx, 2);
                    if (s1 == 0) {
                        backedge(ctx);
                    } else {
                        // 0x0048f984
                        charge(ctx, 3);
                        lw(v1, s7, 32);
                        if (i64(v1) <= 0) {
                            backedge(ctx);
                        } else {
                            // 0x0048f990
                            charge(ctx, 5);
                            lhu(v0, s3, 130);
                            at = slt(0, v1);
                            s2 = 0;
                            s5 = sll(v0, 3);
                            if (at == 0) {
                                backedge(ctx);
                            } else {
                                // 0x0048f9a4
                                charge(ctx, 1);
                                s0 = s3;
                                for (;;) {
                                    // 0x0048f9a8
                                    charge(ctx, 5);
                                    lw(v1, s4, 0);
                                    v0 = addu(v1, s5);
                                    sw(v0, s4, 0);
                                    sw(v1, s0, 16);
                                    if (s1 == 0) {
                                        // 0x0048f9bc
                                        charge(ctx, 1);
                                        goto L_0048f9c0;
                                    }
                                    // 0x0048fa88
                                    charge(ctx, 3);
                                    lw(v0, s0, 16);
                                    if (v0 == 0) {
                                        goto L_0048fa94_56;
                                    }
                                    backedge(ctx);
                                L_0048f9c0:
                                    charge(ctx, 2);
                                    if (s1 != 0) {
                                        // 0x0048fac0
                                        charge(ctx, 6);
                                        lw(a1, s0, 16);
                                        a0 = s6;
                                        a2 = s5;
                                        jal(ctx, 0x48FAC8u, gen::fn_sub_4C18B0_004c18b0);
                                        if (v0 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                        goto L_0048f9c8;
                                    }
                                L_0048f9c8:
                                    charge(ctx, 5);
                                    lw(v0, s7, 32);
                                    s2 = addiu(s2, 1);
                                    v0 = slt(s2, v0);
                                    s0 = addiu(s0, 4);
                                    if (v0 == 0) {
                                        goto L_0048f9dc_49;
                                    }
                                    backedge(ctx);
                                }
                                // 0x0048fad8
                                charge(ctx, 2);
                                s1 = 0;
                                backedge(ctx);
                            }
                        }
                    }
                }
            L_0048f724:
                charge(ctx, 2);
                if (s1 != 0) {
                    // 0x0048f72c
                    charge(ctx, 3);
                    lw(v0, fp, 0x0);
                    if (v0 != 0) {
                        // 0x0048f738
                        charge(ctx, 8);
                        lw(v1, s4, 0);
                        s0 = sll(v0, 3);
                        v0 = addu(v1, s0);
                        sw(v0, s4, 0);
                        sw(v1, s3, 4);
                        lw(v0, s3, 4);
                        if (v0 == 0) {
                            // 0x0048fae0
                            charge(ctx, 11);
                            v1 = 2;
                            v0 = lui(0x8000);
                            sw(v1, sp, 0xE0);
                            a0 = v0 | 0x13;
                            a1 = s0;
                            jal(ctx, 0x48FAF0u, gen::fn_sub_4C1D10_004c1d10);
                            sw(v0, sp, 0xE4);
                            a0 = addiu(sp, 0xE0);
                            jal(ctx, 0x48FAFCu, gen::fn_sub_4C1C50_004c1c50);
                            s1 = 0;
                            backedge(ctx);
                        }
                        // 0x0048f758
                        charge(ctx, 2);
                        if (s1 != 0) {
                            // 0x0048fb0c
                            charge(ctx, 6);
                            lw(a1, s3, 4);
                            a2 = s0;
                            a0 = s6;
                            jal(ctx, 0x48FB14u, gen::fn_sub_4C1850_004c1850);
                            if (v0 != 0) {
                                backedge(ctx);
                            } else {
                                // 0x0048fb24
                                charge(ctx, 2);
                                s1 = 0;
                                backedge(ctx);
                            }
                        }
                        // 0x0048f760
                        charge(ctx, 2);
                        if (s1 != 0) {
                            // 0x0048f768
                            charge(ctx, 6);
                            lw(v0, sp, 0x11C);
                            at = 0x30000;
                            at = at | 0x6002;
                            at = sltu(v0, at);
                            if (at != 0) {
                                // 0x0048f780
                                charge(ctx, 4);
                                lw(v0, fp, 0x0);
                                at = slt(0, v0);
                                a1 = 0;
                                if (at != 0) {
                                    // 0x0048f790
                                    charge(ctx, 4);
                                    a2 = 0;
                                    a0 = addiu(sp, 0xDA);
                                    v1 = addiu(sp, 0xDC);
                                    v0 = addiu(sp, 0xDE);
                                    for (;;) {
                                        // 0x0048f7a0
                                        charge(ctx, 29);
                                        lw(a3, s3, 4);
                                        a1 = addiu(a1, 1);
                                        t3 = addu(a3, a2);
                                        lh(t1, t3, 2);
                                        lh(a3, t3, 6);
                                        lh(t2, t3, 0);
                                        lh(t0, t3, 4);
                                        sh(t1, sp, 0xDA);
                                        sh(a3, sp, 0xDE);
                                        lhu(a3, a0, 0);
                                        sh(t2, sp, 0xD8);
                                        sh(t0, sp, 0xDC);
                                        lhu(t2, v1, 0);
                                        lhu(t1, v0, 0);
                                        lhu(t0, sp, 0xD8);
                                        sh(a3, t3, 0);
                                        lw(a3, s3, 4);
                                        a3 = addu(a3, a2);
                                        sh(t2, a3, 2);
                                        lw(a3, s3, 4);
                                        a3 = addu(a3, a2);
                                        sh(t1, a3, 4);
                                        lw(a3, s3, 4);
                                        a3 = addu(a3, a2);
                                        sh(t0, a3, 6);
                                        lw(a3, fp, 0x0);
                                        a3 = slt(a1, a3);
                                        a2 = addiu(a2, 8);
                                        if (a3 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x0048f814
                                    charge(ctx, 1);
                                }
                            }
                        }
                    }
                }
            }
            // 0x0048f818
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x0048fb2c
                charge(ctx, 7);
                a0 = 0x780000;
                a1 = s3;
                a0 = addiu(a0, -8784);  // &0x77DDB0 (the world-sector plugin registry (its extension size))
                jal(ctx, 0x48FB34u, gen::fn_sub_4C64B0_004c64b0);
                sw(zero, gp, -17652);  // 0x7CE7FC
                sw(zero, gp, -17656);  // 0x7CE7F8
                if (s1 != 0) {
                    // 0x0048fb78
                    charge(ctx, 7);
                    a0 = 0x780000;
                    a1 = s6;
                    a0 = addiu(a0, -8784);  // &0x77DDB0 (the world-sector plugin registry (its extension size))
                    a2 = s3;
                    jal(ctx, 0x48FB84u, gen::fn_sub_4C5A50_004c5a50);
                    if (v0 != 0) {
                        backedge(ctx);
                    } else {
                        // 0x0048fb94
                        charge(ctx, 2);
                        s1 = 0;
                        backedge(ctx);
                    }
                }
                // 0x0048fb48
                charge(ctx, 2);
                if (s1 == 0) {
                    backedge(ctx);
                } else {
                    // 0x0048fb50
                    charge(ctx, 3);
                    lw(a1, gp, -17652);  // 0x7CE7FC
                    if (a1 == 0) {
                        backedge(ctx);
                    } else {
                        // 0x0048fb5c
                        charge(ctx, 7);
                        lw(a3, gp, -17656);  // 0x7CE7F8
                        a0 = 0x780000;
                        a0 = addiu(a0, -8784);  // &0x77DDB0 (the world-sector plugin registry (its extension size))
                        a2 = s3;
                        jal(ctx, 0x48FB68u, gen::fn_sub_4C5C30_004c5c30);
                        backedge(ctx);
                    }
                }
            }
            // 0x0048f820
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x0048fb9c
                charge(ctx, 1);
                v0 = s3;
                goto L_0048fba0;
            }
            // 0x0048f828
            charge(ctx, 4);
            lbu(v0, s7, 3);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x0048f848
                charge(ctx, 3);
                a0 = s3;
                jal(ctx, 0x48F848u, gen::fn_sub_499850_00499850);
                v0 = 0;
            } else {
                // 0x0048f838
                charge(ctx, 4);
                a0 = s3;
                jal(ctx, 0x48F838u, gen::fn_sub_499720_00499720);
                v0 = 0;
            }
            // 0x0048f854
            charge(ctx, 2);
            ld(ra, sp, 0x90);
            // 0x0048fba4 (the shared epilogue, written out on this path)
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
            sp = addiu(sp, 0x120);
            return;
        }
    L_0048f604:
        charge(ctx, 10);
        v1 = 2;
        v0 = lui(0x8000);
        sw(v1, sp, 0x110);
        a0 = v0 | 0x4;
        jal(ctx, 0x48F610u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x114);
        a0 = addiu(sp, 0x110);
        jal(ctx, 0x48F61Cu, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
        goto L_0048fba0;
    }
    // 0x0048f62c
    charge(ctx, 2);
    v0 = 0;
L_0048fba0:
    charge(ctx, 1);
    ld(ra, sp, 0x90);
    // 0x0048fba4 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x120);
    return;
L_0048f9dc_49:
    charge(ctx, 2);
    backedge(ctx);
    goto L_0048f724;
L_0048fa94_56:
    charge(ctx, 11);
    v0 = 2;
    a1 = s5;
    sw(v0, sp, 0xE8);
    v0 = lui(0x8000);
    a0 = v0 | 0x13;
    jal(ctx, 0x48FAA4u, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0xEC);
    a0 = addiu(sp, 0xE8);
    jal(ctx, 0x48FAB0u, gen::fn_sub_4C1C50_004c1c50);
    s1 = 0;
    backedge(ctx);
    goto L_0048f724;
}


// sub_48FBD0 [worldPlaneStreamRead] -- reads a plane sector (chunk 10) and its two children, recursively: plane sectors through itself, atomic sectors through sub_48F580
// ($a0 = the stream, $a1 = the address cursor, $a2 = the world, $a3 = the world's flags) The 24-byte plane
// record (type, value, the two child flags, the left / right extents -- 0x40000000 in the flags keeps the streamed
// extents); 0 and the partial tree torn down on a failure.
// 0x0048FBD0 sub_48FBD0 -- 1140 bytes; frame 0xC0: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_48FBD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x0048fbd0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    s2 = a3;
    sq(s0, sp, 0x0);
    a2 = addiu(sp, 0xBC);
    s0 = 1;
    a3 = addiu(sp, 0xB8);
    a1 = s0;
    jal(ctx, 0x48FC0Cu, gen::fn_sub_4C1600_004c1600);
    if (v0 == 0) {
        // 0x0048fc70
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0048fc1c
        charge(ctx, 6);
        lw(v1, sp, 0xB8);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x0048fc34
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_0048fc48;
            }
            // 0x0048fc78
            charge(ctx, 11);
            a0 = addiu(sp, 0x70);
            a1 = 0;
            a2 = 24;
            jal(ctx, 0x48FC80u, gen::fn_memset_00521408);
            lw(s1, sp, 0xBC);
            a0 = s5;
            a1 = addiu(sp, 0x70);
            a2 = s1;
            jal(ctx, 0x48FC94u, gen::fn_sub_4C5250_004c5250);
            if (s1 != v0) {
                // 0x0048ffe8
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x0048fca4
                charge(ctx, 4);
                lw(s1, s4, 0);
                v0 = addiu(s1, 24);
                sw(v0, s4, 0);
                if (s1 == 0) {
                    // 0x0048fff0
                    charge(ctx, 11);
                    v1 = 2;
                    v0 = lui(0x8000);
                    sw(v1, sp, 0xA8);
                    a0 = v0 | 0x13;
                    a1 = 24;
                    jal(ctx, 0x490000u, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0xAC);
                    a0 = addiu(sp, 0xA8);
                    jal(ctx, 0x49000Cu, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                } else {
                    // 0x0048fcb4
                    charge(ctx, 8);
                    lw(a0, sp, 0x70);
                    v0 = 0x40000000;
                    v1 = addiu(sp, 0x74);
                    v0 = s2 & v0;
                    sw(a0, s1, 0);
                    lwc1(f0, v1, 0);
                    swc1(f0, s1, 4);
                    if (v0 == 0) {
                        // 0x0048fce8
                        charge(ctx, 4);
                        lwc1(f0, v1, 0);
                        swc1(f0, s1, 16);
                        lwc1(f0, v1, 0);
                        swc1(f0, s1, 20);
                    } else {
                        // 0x0048fcd4
                        charge(ctx, 5);
                        lwc1(f0, sp, 0x80);
                        swc1(f0, s1, 16);
                        lwc1(f0, sp, 0x84);
                        swc1(f0, s1, 20);
                    }
                    // 0x0048fcf8
                    charge(ctx, 3);
                    lw(v0, sp, 0x78);
                    if (v0 == 0) {
                        // 0x0048fda8
                        charge(ctx, 7);
                        a0 = s5;
                        a1 = 10;
                        a2 = 0;
                        a3 = addiu(sp, 0xB8);
                        jal(ctx, 0x48FDB4u, gen::fn_sub_4C1600_004c1600);
                        if (v0 == 0) {
                            // 0x0048fdc4
                            charge(ctx, 1);
                            s0 = 0;
                        }
                        // 0x0048fdc8
                        charge(ctx, 2);
                        if (s0 != 0) {
                            // 0x0048fdd0
                            charge(ctx, 6);
                            lw(v1, sp, 0xB8);
                            v0 = 0x30000;
                            v0 = v0 | 0x5000;
                            v0 = sltu(v1, v0);
                            if (v0 == 0) {
                                // 0x0048fde8
                                charge(ctx, 5);
                                at = 0x30000;
                                at = at | 0x7003;
                                at = sltu(v1, at);
                                if (at == 0) {
                                    goto L_0048fdfc;
                                }
                                goto L_0048fe20;
                            }
                        L_0048fdfc:
                            charge(ctx, 9);
                            v1 = 2;
                            v0 = lui(0x8000);
                            sw(v1, sp, 0x98);
                            a0 = v0 | 0x4;
                            jal(ctx, 0x48FE08u, gen::fn_sub_4C1D10_004c1d10);
                            sw(v0, sp, 0x9C);
                            a0 = addiu(sp, 0x98);
                            jal(ctx, 0x48FE14u, gen::fn_sub_4C1C50_004c1c50);
                            s0 = 0;
                        }
                    L_0048fe20:
                        charge(ctx, 2);
                        if (s0 != 0) {
                            // 0x0048fe28
                            charge(ctx, 7);
                            a0 = s5;
                            a1 = s4;
                            a2 = s3;
                            a3 = s2;
                            jal(ctx, 0x48FE34u, gen::fn_sub_48FBD0_0048fbd0);
                            sw(v0, s1, 8);
                            if (v0 == 0) {
                                // 0x0048fe44
                                charge(ctx, 1);
                                s0 = 0;
                            }
                        }
                    } else {
                        // 0x0048fd04
                        charge(ctx, 7);
                        a0 = s5;
                        a1 = 9;
                        a2 = 0;
                        a3 = addiu(sp, 0xB8);
                        jal(ctx, 0x48FD10u, gen::fn_sub_4C1600_004c1600);
                        if (v0 == 0) {
                            // 0x0048fd20
                            charge(ctx, 1);
                            s0 = 0;
                        }
                        // 0x0048fd24
                        charge(ctx, 2);
                        if (s0 != 0) {
                            // 0x0048fd2c
                            charge(ctx, 6);
                            lw(v1, sp, 0xB8);
                            v0 = 0x30000;
                            v0 = v0 | 0x5000;
                            v0 = sltu(v1, v0);
                            if (v0 == 0) {
                                // 0x0048fd44
                                charge(ctx, 5);
                                at = 0x30000;
                                at = at | 0x7003;
                                at = sltu(v1, at);
                                if (at == 0) {
                                    goto L_0048fd58;
                                }
                                goto L_0048fd7c;
                            }
                        L_0048fd58:
                            charge(ctx, 9);
                            v1 = 2;
                            v0 = lui(0x8000);
                            sw(v1, sp, 0xA0);
                            a0 = v0 | 0x4;
                            jal(ctx, 0x48FD64u, gen::fn_sub_4C1D10_004c1d10);
                            sw(v0, sp, 0xA4);
                            a0 = addiu(sp, 0xA0);
                            jal(ctx, 0x48FD70u, gen::fn_sub_4C1C50_004c1c50);
                            s0 = 0;
                        }
                    L_0048fd7c:
                        charge(ctx, 2);
                        if (s0 != 0) {
                            // 0x0048fd84
                            charge(ctx, 7);
                            a0 = s5;
                            a1 = s4;
                            a2 = s3;
                            a3 = s2;
                            jal(ctx, 0x48FD90u, gen::fn_sub_48F580_0048f580);
                            sw(v0, s1, 8);
                            if (v0 == 0) {
                                // 0x0048fda0
                                charge(ctx, 2);
                                s0 = 0;
                            }
                        }
                    }
                    // 0x0048fe48
                    charge(ctx, 2);
                    if (s0 != 0) {
                        // 0x0048fe50
                        charge(ctx, 3);
                        lw(v0, sp, 0x7C);
                        if (v0 == 0) {
                            // 0x0048ff00
                            charge(ctx, 7);
                            a0 = s5;
                            a1 = 10;
                            a2 = 0;
                            a3 = addiu(sp, 0xB8);
                            jal(ctx, 0x48FF0Cu, gen::fn_sub_4C1600_004c1600);
                            if (v0 == 0) {
                                // 0x0048ff1c
                                charge(ctx, 1);
                                s0 = 0;
                            }
                            // 0x0048ff20
                            charge(ctx, 2);
                            if (s0 != 0) {
                                // 0x0048ff28
                                charge(ctx, 6);
                                lw(v1, sp, 0xB8);
                                v0 = 0x30000;
                                v0 = v0 | 0x5000;
                                v0 = sltu(v1, v0);
                                if (v0 == 0) {
                                    // 0x0048ff40
                                    charge(ctx, 5);
                                    at = 0x30000;
                                    at = at | 0x7003;
                                    at = sltu(v1, at);
                                    if (at == 0) {
                                        goto L_0048ff54;
                                    }
                                    goto L_0048ff78;
                                }
                            L_0048ff54:
                                charge(ctx, 9);
                                v1 = 2;
                                v0 = lui(0x8000);
                                sw(v1, sp, 0x88);
                                a0 = v0 | 0x4;
                                jal(ctx, 0x48FF60u, gen::fn_sub_4C1D10_004c1d10);
                                sw(v0, sp, 0x8C);
                                a0 = addiu(sp, 0x88);
                                jal(ctx, 0x48FF6Cu, gen::fn_sub_4C1C50_004c1c50);
                                s0 = 0;
                            }
                        L_0048ff78:
                            charge(ctx, 2);
                            if (s0 != 0) {
                                // 0x0048ff80
                                charge(ctx, 7);
                                a0 = s5;
                                a1 = s4;
                                a3 = s2;
                                a2 = s3;
                                jal(ctx, 0x48FF8Cu, gen::fn_sub_48FBD0_0048fbd0);
                                sw(v0, s1, 12);
                                if (v0 == 0) {
                                    // 0x0048ff9c
                                    charge(ctx, 1);
                                    s0 = 0;
                                }
                            }
                        } else {
                            // 0x0048fe5c
                            charge(ctx, 7);
                            a0 = s5;
                            a1 = 9;
                            a2 = 0;
                            a3 = addiu(sp, 0xB8);
                            jal(ctx, 0x48FE68u, gen::fn_sub_4C1600_004c1600);
                            if (v0 == 0) {
                                // 0x0048fe78
                                charge(ctx, 1);
                                s0 = 0;
                            }
                            // 0x0048fe7c
                            charge(ctx, 2);
                            if (s0 != 0) {
                                // 0x0048fe84
                                charge(ctx, 6);
                                lw(v1, sp, 0xB8);
                                v0 = 0x30000;
                                v0 = v0 | 0x5000;
                                v0 = sltu(v1, v0);
                                if (v0 == 0) {
                                    // 0x0048fe9c
                                    charge(ctx, 5);
                                    at = 0x30000;
                                    at = at | 0x7003;
                                    at = sltu(v1, at);
                                    if (at == 0) {
                                        goto L_0048feb0;
                                    }
                                    goto L_0048fed4;
                                }
                            L_0048feb0:
                                charge(ctx, 9);
                                v1 = 2;
                                v0 = lui(0x8000);
                                sw(v1, sp, 0x90);
                                a0 = v0 | 0x4;
                                jal(ctx, 0x48FEBCu, gen::fn_sub_4C1D10_004c1d10);
                                sw(v0, sp, 0x94);
                                a0 = addiu(sp, 0x90);
                                jal(ctx, 0x48FEC8u, gen::fn_sub_4C1C50_004c1c50);
                                s0 = 0;
                            }
                        L_0048fed4:
                            charge(ctx, 2);
                            if (s0 != 0) {
                                // 0x0048fedc
                                charge(ctx, 7);
                                a0 = s5;
                                a1 = s4;
                                a3 = s2;
                                a2 = s3;
                                jal(ctx, 0x48FEE8u, gen::fn_sub_48F580_0048f580);
                                sw(v0, s1, 12);
                                if (v0 == 0) {
                                    // 0x0048fef8
                                    charge(ctx, 2);
                                    s0 = 0;
                                }
                            }
                        }
                    }
                    // 0x0048ffa0
                    charge(ctx, 2);
                    if (s0 != 0) {
                        // 0x0049001c
                        charge(ctx, 1);
                        v0 = s1;
                    } else {
                        // 0x0048ffa8
                        charge(ctx, 3);
                        lw(a0, s1, 8);
                        if (a0 != 0) {
                            // 0x0048ffb4
                            charge(ctx, 4);
                            lbu(v0, s3, 3);
                            v0 = v0 & 0x1;
                            if (v0 == 0) {
                                // 0x0048ffd4
                                charge(ctx, 3);
                                jal(ctx, 0x48FFD4u, gen::fn_sub_499850_00499850);
                                sw(zero, s1, 8);
                            } else {
                                // 0x0048ffc4
                                charge(ctx, 4);
                                jal(ctx, 0x48FFC4u, gen::fn_sub_499720_00499720);
                                sw(zero, s1, 8);
                            }
                        }
                        // 0x0048ffe0
                        charge(ctx, 2);
                        v0 = 0;
                    }
                }
            }
            // 0x00490020 (the shared epilogue, written out on this path)
            charge(ctx, 9);
            ld(ra, sp, 0x60);
            lq(s5, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0xC0);
            return;
        }
    L_0048fc48:
        charge(ctx, 10);
        v1 = 2;
        v0 = lui(0x8000);
        sw(v1, sp, 0xB0);
        a0 = v0 | 0x4;
        jal(ctx, 0x48FC54u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0xB4);
        a0 = addiu(sp, 0xB0);
        jal(ctx, 0x48FC60u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x00490020 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xC0);
}


// sub_499A80 [worldEngineClose] -- the world module's engine close: its 16-byte free list destroyed, the default pipelines released (sub_49C680), the open count down; $a0
// 0x00499A80 sub_499A80 -- 112 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_499A80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00499a80
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s0, sp, 0x0);
    lw(v1, gp, -17552);  // 0x7CE860 (the world module's engine offset (a 16-byte free list))
    s0 = a0;
    v0 = addu(v0, v1);
    lw(a0, v0, 0);
    if (a0 != 0) {
        // 0x00499aac
        charge(ctx, 7);
        jal(ctx, 0x499AACu, gen::fn_sub_4C3C30_004c3c30);
        lw(v1, gp, -17552);  // 0x7CE860 (the world module's engine offset (a 16-byte free list))
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        sw(zero, v0, 0);
    }
    // 0x00499ac8
    charge(ctx, 10);
    jal(ctx, 0x499AC8u, gen::fn_sub_49C680_0049c680);
    lw(v1, gp, -17548);  // 0x7CE864 (the world module's open count)
    v0 = s0;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17548);  // 0x7CE864 (the world module's open count)
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_499AF0 [worldEngineOpen] -- the world module's engine open: the default pipelines (sub_49C6C0), then a 16-byte free list (8 per block) whose record links to itself; $a0, or 0
// $a1 = the module's engine offset (stored at gp 0x7CE860).
// 0x00499AF0 sub_499AF0 -- 160 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_499AF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00499af0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    sw(a1, gp, -17552);  // 0x7CE860 (the world module's engine offset (a 16-byte free list))
    s0 = a0;
    jal(ctx, 0x499B00u, gen::fn_sub_49C6C0_0049c6c0);
    if (v0 != 0) {
        // 0x00499b18
        charge(ctx, 17);
        t0 = 0x960000;
        v0 = 0x40000;
        a0 = 16;
        a1 = 8;
        a2 = 4;
        a3 = 1;
        t0 = addiu(t0, -8400);  // &0x95DF30 (the world module's free-list static block)
        t1 = v0 | 0xB;
        jal(ctx, 0x499B34u, gen::fn_sub_4C3B60_004c3b60);
        lw(a0, gp, -17552);  // 0x7CE860 (the world module's engine offset (a 16-byte free list))
        v1 = 0x960000;
        v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        a0 = addu(v1, a0);
        sw(v0, a0, 0);
        lw(v0, a0, 0);
        if (v0 != 0) {
            // 0x00499b64
            charge(ctx, 7);
            v1 = addiu(a0, 4);
            v0 = s0;
            sw(v1, a0, 4);
            sw(v1, a0, 8);
            lw(v1, gp, -17548);  // 0x7CE864 (the world module's open count)
            v1 = addiu(v1, 1);
            sw(v1, gp, -17548);  // 0x7CE864 (the world module's open count)
        } else {
            // 0x00499b5c
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x00499b10
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00499b80 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_49C680 [worldDefaultPipesDestroy] -- releases the default pipelines: the Im3D ones (sub_49C9B0) and the default material / world-sector / atomic pipes (sub_4A5290, sub_4A5320, sub_4A5200)
// 0x0049C680 sub_49C680 -- 52 bytes; frame 0x10: ra sp+0x0
void sub_49C680(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0049c680
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x49C688u, gen::fn_sub_49C9B0_0049c9b0);
    jal(ctx, 0x49C690u, gen::fn_sub_4A5290_004a5290);
    jal(ctx, 0x49C698u, gen::fn_sub_4A5320_004a5320);
    jal(ctx, 0x49C6A0u, gen::fn_sub_4A5200_004a5200);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_49C6C0 [worldDefaultPipesCreate] -- creates the default pipelines: the pipeline module's defaults cleared (+60..+92), then the atomic, world-sector, material and Im3D pipes; on a failure all released; 1 / 0
// 0x0049C6C0 sub_49C6C0 -- 200 bytes; frame 0x10: ra sp+0x0
void sub_49C6C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049c6c0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x960000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    lw(v1, gp, -16840);  // 0x7CEB28 (the pipeline module offset)
    v0 = addu(v0, v1);
    sw(zero, v0, 60);
    sw(zero, v0, 64);
    sw(zero, v0, 68);
    sw(zero, v0, 72);
    sw(zero, v0, 76);
    sw(zero, v0, 80);
    sw(zero, v0, 84);
    sw(zero, v0, 88);
    link(ctx, 0x49C6F8u);  // $ra first: the delay slot below depends on it
    sw(zero, v0, 92);
    call(ctx, gen::fn_sub_4A5210_004a5210);
    if (v0 != 0) {
        // 0x0049c728
        charge(ctx, 4);
        jal(ctx, 0x49C728u, gen::fn_sub_4A5330_004a5330);
        backedge(ctx);
    }
    // 0x0049c708
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x0049c738
        charge(ctx, 4);
        jal(ctx, 0x49C738u, gen::fn_sub_4A52A0_004a52a0);
        backedge(ctx);
    }
    // 0x0049c710
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x0049c748
        charge(ctx, 4);
        jal(ctx, 0x49C748u, gen::fn_sub_49C8C0_0049c8c0);
        backedge(ctx);
    }
    // 0x0049c718
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x0049c758
        charge(ctx, 9);
        jal(ctx, 0x49C758u, gen::fn_sub_49C9B0_0049c9b0);
        jal(ctx, 0x49C760u, gen::fn_sub_4A5290_004a5290);
        jal(ctx, 0x49C768u, gen::fn_sub_4A5320_004a5320);
        jal(ctx, 0x49C770u, gen::fn_sub_4A5200_004a5200);
        v0 = 0;
    } else {
        // 0x0049c720
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x0049c77c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_49C810 [im3dTransformPipeCreate] -- builds the Im3D transform pipeline ('FastIm3DTransform'): create (plugin id 1), lock, the node fragment 0x77DE10, unlock; on a failure destroyed and error 0x80000006
// The pipeline, or 0.
// 0x0049C810 sub_49C810 -- 176 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
void sub_49C810(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049c810
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    link(ctx, 0x49C818u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4F2F70_004f2f70);
    s0 = v0;
    if (s0 != 0) {
        // 0x0049c82c
        charge(ctx, 6);
        v0 = 1;
        a0 = s0;
        link(ctx, 0x49C834u);  // $ra first: the delay slot below depends on it
        sw(v0, s0, 44);
        call(ctx, gen::fn_sub_4F4640_004f4640);
        if (v0 != 0) {
            // 0x0049c844
            charge(ctx, 8);
            a2 = 0x780000;
            a0 = v0;
            a1 = 0;
            a2 = addiu(a2, -8688);  // &0x77DE10
            a3 = 0;
            jal(ctx, 0x49C854u, gen::fn_sub_4F4950_004f4950);
            if (v0 == 0) {
                goto L_0049c87c;
            }
            // 0x0049c864
            charge(ctx, 4);
            a0 = v0;
            jal(ctx, 0x49C864u, gen::fn_sub_4F3F80_004f3f80);
            if (v0 == 0) {
                goto L_0049c87c;
            }
            // 0x0049c874
            charge(ctx, 2);
            v0 = s0;
            // 0x0049c8b0 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
    L_0049c87c:
        charge(ctx, 2);
        a0 = s0;
        jal(ctx, 0x49C87Cu, gen::fn_sub_4F3010_004f3010);
    }
    // 0x0049c884
    charge(ctx, 11);
    v1 = 2;
    v0 = lui(0x8000);
    a1 = 0x780000;
    sw(v1, sp, 0x28);
    a0 = v0 | 0x6;
    a1 = addiu(a1, -8624);  // "FastIm3DTransform"
    jal(ctx, 0x49C898u, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0x2C);
    a0 = addiu(sp, 0x28);
    jal(ctx, 0x49C8A4u, gen::fn_sub_4C1C50_004c1c50);
    v0 = 0;
    // 0x0049c8b0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_49C8C0 [im3dPipesCreate] -- sets the Im3D module's pipelines: the transform pipe (sub_49C810) and the render pipes the PDS registry holds for ids 4..7, each made the current pipe of its primitive types; 1
// Module +28 transform, +32..+40 the triangle pipe (id 6) for three primitive types, +44 / +48 the line pipe (id 7),
// +56 id 4, +60 id 5; sub_4F23C0 / sub_4F2430 make them current (the triangle pipe for types 3 / 5 / 4, the line
// pipe for 1 / 2).
// 0x0049C8C0 sub_49C8C0 -- 236 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49C8C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049c8c0
    enter(ctx, 59);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    link(ctx, 0x49C8D8u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_49C810_0049c810);
    s4 = v0;
    a0 = 4;
    jal(ctx, 0x49C8E4u, gen::fn_RpPDSGetPipe_0046a890);
    s1 = v0;
    a0 = 6;
    jal(ctx, 0x49C8F0u, gen::fn_RpPDSGetPipe_0046a890);
    s3 = v0;
    a0 = 5;
    jal(ctx, 0x49C8FCu, gen::fn_RpPDSGetPipe_0046a890);
    s0 = v0;
    a0 = 7;
    jal(ctx, 0x49C908u, gen::fn_RpPDSGetPipe_0046a890);
    lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
    s2 = v0;
    v0 = 0x960000;
    a0 = s4;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = addu(v0, v1);
    sw(s4, v0, 28);
    sw(s3, v0, 32);
    sw(s3, v0, 36);
    sw(s3, v0, 40);
    sw(s2, v0, 44);
    sw(s2, v0, 48);
    sw(s1, v0, 56);
    link(ctx, 0x49C944u);  // $ra first: the delay slot below depends on it
    sw(s0, v0, 60);
    call(ctx, gen::fn_sub_4F23C0_004f23c0);
    a0 = s3;
    a1 = 3;
    jal(ctx, 0x49C950u, gen::fn_sub_4F2430_004f2430);
    a0 = s3;
    a1 = 5;
    jal(ctx, 0x49C95Cu, gen::fn_sub_4F2430_004f2430);
    a0 = s3;
    a1 = 4;
    jal(ctx, 0x49C968u, gen::fn_sub_4F2430_004f2430);
    a0 = s2;
    a1 = 1;
    jal(ctx, 0x49C974u, gen::fn_sub_4F2430_004f2430);
    a0 = s2;
    a1 = 2;
    jal(ctx, 0x49C980u, gen::fn_sub_4F2430_004f2430);
    ld(ra, sp, 0x50);
    v0 = 1;
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_49C9B0 [im3dPipesDestroy] -- clears the Im3D module's pipelines: the current pipes of every primitive type reset, the module's pointers cleared, the transform pipe destroyed
// 0x0049C9B0 sub_49C9B0 -- 160 bytes; frame 0x10: ra sp+0x0
void sub_49C9B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049c9b0
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0;
    sd(ra, sp, 0x0);
    a1 = 2;
    jal(ctx, 0x49C9BCu, gen::fn_sub_4F2430_004f2430);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x49C9C8u, gen::fn_sub_4F2430_004f2430);
    a0 = 0;
    a1 = 4;
    jal(ctx, 0x49C9D4u, gen::fn_sub_4F2430_004f2430);
    a0 = 0;
    a1 = 5;
    jal(ctx, 0x49C9E0u, gen::fn_sub_4F2430_004f2430);
    a0 = 0;
    a1 = 3;
    jal(ctx, 0x49C9ECu, gen::fn_sub_4F2430_004f2430);
    a0 = 0;
    jal(ctx, 0x49C9F4u, gen::fn_sub_4F23C0_004f23c0);
    lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = addu(v0, v1);
    sw(zero, v0, 60);
    sw(zero, v0, 56);
    sw(zero, v0, 48);
    sw(zero, v0, 44);
    sw(zero, v0, 36);
    sw(zero, v0, 40);
    sw(zero, v0, 32);
    link(ctx, 0x49CA28u);  // $ra first: the delay slot below depends on it
    lw(a0, v0, 28);
    call(ctx, gen::fn_sub_4F3010_004f3010);
    lw(a0, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = addu(v1, a0);
    sw(zero, v1, 28);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_4A30D0 [ps2AllMatNodeClusterLayout] -- lays out a PS2AllMat node's clusters from its initialisation data: per cluster its attributes and VIF unpack width; refuses illegal attribute combinations with a message
// ($a0 = the node) The private data +182 = the batch count (init +56), +188 / +500 the batch sizes (+48 / +52), +176
// the primitive flags (3 when 0); each of the ten clusters' attributes (+32 + 8i) and unpack width (+36 + 8i:
// 0x6C.. 4, 0x68.. 3, 0x64.. / 0x6D.. 2, 0x60.. / 0x65.. / 0x6E.. 1); errors through the engine's sprintf slot
// name the cluster (XYZW, UV, RGBA, Normal, User1..4). Then the cluster layout (ps2AllMatClusterLayout); 1 / 0.
// 0x004A30D0 sub_4A30D0 -- 1128 bytes; frame 0x580: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4A30D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, t8{ctx, 24}, t9{ctx, 25}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a30d0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x580);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 20);
    s0 = 0;
    jal(ctx, 0x4A30F0u, gen::fn_sub_4F3F70_004f3f70);
    if (v0 != 0) {
        // 0x004a3100
        charge(ctx, 5);
        lw(v1, v0, 56);
        sb(v1, s1, 182);
        lbu(v1, s1, 182);
        if (v1 == 0) {
            // 0x004a3248
            charge(ctx, 2);
            v0 = 0;
            goto L_004a3518;
        }
        // 0x004a3114
        charge(ctx, 9);
        lw(v1, v0, 48);
        sw(v1, s1, 188);
        lw(v1, v0, 52);
        sw(v1, s1, 500);
        lw(v1, v0, 60);
        sw(v1, s1, 176);
        lw(v1, s1, 176);
        if (v1 == 0) {
            // 0x004a3250
            charge(ctx, 3);
            v1 = 3;
            sw(v1, s1, 176);
            backedge(ctx);
        }
        // 0x004a3138
        charge(ctx, 16);
        sb(zero, s1, 181);
        s2 = 0;
        t9 = v0;
        t8 = s1;
        t4 = 0x68000000;
        t3 = 0x6D000000;
        t2 = 0x64000000;
        t1 = 0x65000000;
        t0 = 0x6E000000;
        a3 = 0x60000000;
        t6 = lui(0xFF00);
        t5 = 0x6C000000;
        v1 = 4;
        a0 = 3;
        a1 = 2;
        a2 = 1;
        for (;;) {
            // 0x004a3178
            charge(ctx, 3);
            lw(t7, t9, 0);
            if (t7 == 0) {
                // 0x004a34e4
                charge(ctx, 2);
                sw(zero, t8, 32);
                backedge(ctx);
            L_004a3210:
                charge(ctx, 5);
                s2 = addiu(s2, 1);
                t7 = sltiu(s2, 10);
                t9 = addiu(t9, 4);
                t8 = addiu(t8, 8);
                if (t7 == 0) {
                    break;
                }
                backedge(ctx);
                continue;
            }
            // 0x004a3184
            charge(ctx, 4);
            lw(s4, t7, 8);
            s3 = s4 & 0x1;
            s0 = addiu(s0, 1);
            if (s3 == 0) {
                // 0x004a3194
                charge(ctx, 3);
                t7 = s4 & 0x10;
                if (t7 == 0) {
                    goto L_004a33c0;
                }
                // 0x004a31a0
                charge(ctx, 5);
                sw(s4, t8, 32);
                lw(t7, t8, 32);
                t7 = t7 & t6;
                if (t7 != t5) {
                    // 0x004a31b4
                    charge(ctx, 2);
                    if (t7 == t4) {
                        // 0x004a3200
                        charge(ctx, 2);
                        sw(a0, t8, 36);
                    } else {
                        // 0x004a31bc
                        charge(ctx, 2);
                        if (t7 != t3) {
                            // 0x004a31c4
                            charge(ctx, 2);
                            if (t7 == t2) {
                                goto L_004a31f8;
                            }
                            // 0x004a31cc
                            charge(ctx, 2);
                            if (t7 != t1) {
                                // 0x004a31d4
                                charge(ctx, 2);
                                if (t7 == t0) {
                                    goto L_004a31f0;
                                }
                                // 0x004a31dc
                                charge(ctx, 2);
                                if (t7 == a3) {
                                    goto L_004a31f0;
                                }
                                // 0x004a31e4
                                charge(ctx, 2);
                                goto L_004a3208;
                            }
                        L_004a31f0:
                            charge(ctx, 2);
                            sw(a2, t8, 36);
                            goto L_004a3210;
                        }
                    L_004a31f8:
                        charge(ctx, 2);
                        sw(a1, t8, 36);
                    }
                    goto L_004a3210;
                }
            L_004a3208:
                charge(ctx, 2);
                sw(v1, t8, 36);
                goto L_004a3210;
            }
            // 0x004a325c
            charge(ctx, 5);
            sw(s4, t8, 32);
            lw(s3, t7, 8);
            s3 = s3 & 0x10;
            if (s3 != 0) {
                goto L_004a3318;
            }
            // 0x004a3270
            charge(ctx, 4);
            lw(s3, t8, 32);
            s3 = s3 & t6;
            if (s3 != t5) {
                // 0x004a3280
                charge(ctx, 2);
                if (s3 == t4) {
                    // 0x004a32c8
                    charge(ctx, 2);
                    sw(a0, t8, 36);
                } else {
                    // 0x004a3288
                    charge(ctx, 2);
                    if (s3 != t3) {
                        // 0x004a3290
                        charge(ctx, 2);
                        if (s3 == t2) {
                            goto L_004a32c0;
                        }
                        // 0x004a3298
                        charge(ctx, 2);
                        if (s3 != t1) {
                            // 0x004a32a0
                            charge(ctx, 2);
                            if (s3 == t0) {
                                goto L_004a32b8;
                            }
                            // 0x004a32a8
                            charge(ctx, 2);
                            if (s3 == a3) {
                                goto L_004a32b8;
                            }
                            // 0x004a32b0
                            charge(ctx, 2);
                            goto L_004a32d0;
                        }
                    L_004a32b8:
                        charge(ctx, 2);
                        sw(a2, t8, 36);
                        goto L_004a32d8;
                    }
                L_004a32c0:
                    charge(ctx, 2);
                    sw(a1, t8, 36);
                }
                goto L_004a32d8;
            }
        L_004a32d0:
            charge(ctx, 2);
            sw(v1, t8, 36);
        L_004a32d8:
            charge(ctx, 4);
            lw(s4, t7, 8);
            s3 = s4 & 0x6;
            if (s3 == 0) {
                // 0x004a3360
                charge(ctx, 3);
                at = sltiu(s2, 6);
                if (at == 0) {
                    goto L_004a339c;
                }
                // 0x004a336c
                charge(ctx, 3);
                s3 = s4 & 0x8;
                if (s3 != 0) {
                    goto L_004a3378_46;
                }
                backedge(ctx);
                goto L_004a3210;
            }
            // 0x004a32e8
            charge(ctx, 3);
            s3 = s4 & 0x2000;
            if (s3 != 0) {
                goto L_004a333c;
            }
            // 0x004a32f4
            charge(ctx, 8);
            lbu(t7, s1, 181);
            t7 = sll(t7, 2);
            t7 = addu(s1, t7);
            sw(zero, t7, 128);
            lbu(t7, s1, 181);
            t7 = addiu(t7, 1);
            sb(t7, s1, 181);
            backedge(ctx);
            goto L_004a3210;
        }
        // 0x004a3224
        charge(ctx, 1);
        goto L_004a3228;
    }
    // 0x004a34f0
    charge(ctx, 9);
    v1 = 4;
    sb(v1, s1, 182);
    v1 = 256;
    sw(v1, s1, 188);
    v1 = 64;
    sw(v1, s1, 500);
    v1 = 3;
    sw(v1, s1, 176);
    backedge(ctx);
L_004a3228:
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x004a3230
        charge(ctx, 2);
        if (s0 == 0) {
            goto L_004a3514;
        }
        // 0x004a3238
        charge(ctx, 4);
        a0 = s1;
        jal(ctx, 0x4A3238u, gen::fn_ps2AllMatClusterLayout_0049cc70);
        ld(ra, sp, 0x50);
        // 0x004a351c (the shared epilogue, written out on this path)
        charge(ctx, 7);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x580);
        return;
    }
L_004a3514:
    charge(ctx, 1);
    v0 = 0;
L_004a3518:
    charge(ctx, 1);
    ld(ra, sp, 0x50);
    // 0x004a351c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x580);
    return;
L_004a3318:
    charge(ctx, 9);
    v0 = 0x960000;
    lw(a2, t7, 0);
    a1 = 0x780000;
    lw(v0, v0, 308);  // 0x960134 (the engine's sprintf slot)
    a0 = addiu(sp, 0x480);
    a1 = addiu(a1, -8448);  // &0x77DF00
    jalr(ctx, 0x4A332Cu, v0.u());
    v0 = 0;
    goto L_004a3518;
L_004a333c:
    charge(ctx, 9);
    v0 = 0x960000;
    a1 = 0x780000;
    lw(a2, t7, 0);
    a0 = addiu(sp, 0x380);
    lw(v0, v0, 308);  // 0x960134 (the engine's sprintf slot)
    a1 = addiu(a1, -8320);  // &0x77DF80
    jalr(ctx, 0x4A3350u, v0.u());
    v0 = 0;
    goto L_004a3518;
L_004a3378_46:
    charge(ctx, 9);
    v0 = 0x960000;
    a1 = 0x780000;
    lw(a2, t7, 0);
    a0 = addiu(sp, 0x180);
    lw(v0, v0, 308);  // 0x960134 (the engine's sprintf slot)
    a1 = addiu(a1, -8176);  // &0x77E010
    jalr(ctx, 0x4A338Cu, v0.u());
    v0 = 0;
    goto L_004a3518;
L_004a339c:
    charge(ctx, 9);
    v0 = 0x960000;
    a1 = 0x780000;
    lw(a2, t7, 0);
    a0 = addiu(sp, 0x280);
    lw(v0, v0, 308);  // 0x960134 (the engine's sprintf slot)
    a1 = addiu(a1, -7968);  // &0x77E0E0
    jalr(ctx, 0x4A33B0u, v0.u());
    v0 = 0;
    goto L_004a3518;
L_004a33c0:
    charge(ctx, 3);
    at = sltiu(s2, 10);
    if (at == 0) {
        // 0x004a34b0
        charge(ctx, 4);
        a1 = 0x780000;
        a0 = addiu(sp, 0x60);
        a1 = addiu(a1, -7824);  // "!UNKNOWN!"
        jal(ctx, 0x4A34B8u, gen::fn_strcpy_00524270);
    } else {
        // 0x004a33cc
        charge(ctx, 7);
        v1 = 0x7C0000;
        v0 = sll(s2, 2);
        v1 = addiu(v1, -13568);  // &0x7BCB00
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x4A33E8u:  // table[0]
            // 0x004a33e8
            charge(ctx, 5);
            a0 = addiu(sp, 0x60);
            a1 = addiu(gp, -20696);  // "XYZ"
            jal(ctx, 0x4A33ECu, gen::fn_strcpy_00524270);
            break;
        case 0x4A33FCu:  // table[1]
            // 0x004a33fc
            charge(ctx, 5);
            a0 = addiu(sp, 0x60);
            a1 = addiu(gp, -20688);  // "XYZW"
            jal(ctx, 0x4A3400u, gen::fn_strcpy_00524270);
            break;
        case 0x4A3410u:  // table[2]
            // 0x004a3410
            charge(ctx, 5);
            a0 = addiu(sp, 0x60);
            a1 = addiu(gp, -20680);  // "UV"
            jal(ctx, 0x4A3414u, gen::fn_strcpy_00524270);
            break;
        case 0x4A3424u:  // table[3]
            // 0x004a3424
            charge(ctx, 5);
            a0 = addiu(sp, 0x60);
            a1 = addiu(gp, -20676);  // "UV2"
            jal(ctx, 0x4A3428u, gen::fn_strcpy_00524270);
            break;
        case 0x4A3438u:  // table[4]
            // 0x004a3438
            charge(ctx, 5);
            a0 = addiu(sp, 0x60);
            a1 = addiu(gp, -20672);  // "RGBA"
            jal(ctx, 0x4A343Cu, gen::fn_strcpy_00524270);
            break;
        case 0x4A344Cu:  // table[5]
            // 0x004a344c
            charge(ctx, 5);
            a0 = addiu(sp, 0x60);
            a1 = addiu(gp, -20664);  // "Normal"
            jal(ctx, 0x4A3450u, gen::fn_strcpy_00524270);
            break;
        case 0x4A3460u:  // table[6]
            // 0x004a3460
            charge(ctx, 5);
            a0 = addiu(sp, 0x60);
            a1 = addiu(gp, -20656);  // "User1"
            jal(ctx, 0x4A3464u, gen::fn_strcpy_00524270);
            break;
        case 0x4A3474u:  // table[7]
            // 0x004a3474
            charge(ctx, 5);
            a0 = addiu(sp, 0x60);
            a1 = addiu(gp, -20648);  // "User2"
            jal(ctx, 0x4A3478u, gen::fn_strcpy_00524270);
            break;
        case 0x4A3488u:  // table[8]
            // 0x004a3488
            charge(ctx, 5);
            a0 = addiu(sp, 0x60);
            a1 = addiu(gp, -20640);  // "User3"
            jal(ctx, 0x4A348Cu, gen::fn_strcpy_00524270);
            break;
        case 0x4A349Cu:  // table[9]
            // 0x004a349c
            charge(ctx, 5);
            a0 = addiu(sp, 0x60);
            a1 = addiu(gp, -20632);  // "User4"
            jal(ctx, 0x4A34A0u, gen::fn_strcpy_00524270);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    }
    // 0x004a34c0
    charge(ctx, 9);
    v0 = 0x960000;
    a1 = 0x780000;
    lw(v0, v0, 308);  // 0x960134 (the engine's sprintf slot)
    a0 = addiu(sp, 0x80);
    a1 = addiu(a1, -7808);  // "PS2AllMatProcessInitData; %s cluster has unrecognised attributes"
    a2 = addiu(sp, 0x60);
    jalr(ctx, 0x4A34D4u, v0.u());
    v0 = 0;
    goto L_004a3518;
}


// PS2AllMatPipelineNodeInit -- the PS2AllMat node's pipeline-node init: no callbacks, VIF offset 0x114 (276), the default VU1 code array (0x77F130, 32 entries), then the cluster layout (sub_4A30D0)
// 0x004A3540 PS2AllMatPipelineNodeInit -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void PS2AllMatPipelineNodeInit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a3540
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    link(ctx, 0x4A354Cu);  // $ra first: the delay slot below depends on it
    lw(s0, a0, 20);
    call(ctx, gen::fn_sub_4A30D0_004a30d0);
    if (v0 != 0) {
        // 0x004a3564
        charge(ctx, 15);
        a0 = 0x780000;
        v1 = 32;
        a0 = addiu(a0, -3792);  // &0x77F130
        sw(a0, s0, allmatpriv::kVU1Code);
        sw(v1, s0, allmatpriv::kVU1CodeCount);
        a0 = 276;
        sw(a0, s0, allmatpriv::kVifOffset);
        v1 = 13561;
        sw(zero, s0, allmatpriv::kCallBack1);
        sw(zero, s0, allmatpriv::kCallBack2);
        sw(zero, s0, allmatpriv::kCallBack3);
        sw(zero, s0, allmatpriv::kCallBack4);
        sw(zero, s0, allmatpriv::kCallBack5);
        sw(v1, s0, 808);
        ld(ra, sp, 0x10);
    } else {
        // 0x004a355c
        charge(ctx, 2);
        ld(ra, sp, 0x10);
    }
    // 0x004a35a0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4A9A80 [rt2dFontFindOrRead] -- finds a font in the font dictionary by name (strcmp slot), else reads it through the font read callback and adds it (a 12-byte dictionary entry); the font, or 0
// 0x004A9A80 sub_4A9A80 -- 332 bytes; frame 0xC0: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4A9A80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a9a80
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    v0 = 0x960000;
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, v0, -4744);  // 0x95ED78 (Rt2d fonts: the font dictionary)
    s2 = a0;
    if (s0 != 0) {
        // 0x004a9aa4
        charge(ctx, 2);
        s1 = 0x960000;
        s1 = addiu(s1, 344);  // &0x960158 (the engine's strcmp slot)
        for (;;) {
            // 0x004a9aac
            charge(ctx, 6);
            lw(a1, s0, 0);
            lw(v0, s1, 0);
            a0 = s2;
            jalr(ctx, 0x4A9AB4u, v0.u());
            if (v0 == 0) {
                goto L_004a9ac4_3;
            }
            // 0x004a9acc
            charge(ctx, 3);
            lw(s0, s0, 8);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004a9ad8
    charge(ctx, 1);
    s0 = 0;
L_004a9adc:
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x004a9aec
        charge(ctx, 14);
        s1 = 0x960000;
        s1 = addiu(s1, 316);  // &0x96013C (the engine's strcpy slot)
        jal(ctx, 0x4A9AF0u, gen::fn_sub_4CC6B0_004cc6b0);
        a1 = v0;
        lw(v0, s1, 0);  // 0x96013C (the engine's strcpy slot)
        a0 = addiu(sp, 0x40);
        jalr(ctx, 0x4A9B00u, v0.u());
        v0 = 0x960000;
        lw(v0, v0, -2952);  // 0x95F478 (Rt2d fonts: the font read callback)
        a0 = s2;
        jalr(ctx, 0x4A9B10u, v0.u());
        s0 = v0;
        if (s0 == 0) {
            // 0x004a9bac
            charge(ctx, 2);
            s0 = 0;
            backedge(ctx);
        } else {
            // 0x004a9b24
            charge(ctx, 30);
            v0 = 0x960000;
            v1 = 0x30000;
            lw(a0, v0, -4748);  // 0x95ED74
            v0 = 0x960000;
            lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
            a1 = v1 | 0x190;
            jalr(ctx, 0x4A9B38u, v0.u());
            sw(s0, v0, 4);
            s0 = v0;
            v0 = 0x960000;
            lw(v0, v0, 356);  // 0x960164 (the engine's strlen slot)
            a0 = s2;
            jalr(ctx, 0x4A9B50u, v0.u());
            a0 = addiu(v0, 1);
            v0 = 0x30000;
            a1 = v0 | 0x190;
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
            jalr(ctx, 0x4A9B6Cu, v0.u());
            sw(v0, s0, 0);
            lw(v0, s1, 0);
            lw(a0, s0, 0);
            a1 = s2;
            jalr(ctx, 0x4A9B80u, v0.u());
            v1 = 0x960000;
            v0 = 0x960000;
            lw(v1, v1, -4744);  // 0x95ED78 (Rt2d fonts: the font dictionary)
            sw(v1, s0, 8);
            sw(s0, v0, -4744);  // 0x95ED78 (Rt2d fonts: the font dictionary)
        }
        // 0x004a9b9c
        charge(ctx, 4);
        a0 = addiu(sp, 0x40);
        jal(ctx, 0x4A9B9Cu, gen::fn_sub_4CC5C0_004cc5c0);
        backedge(ctx);
    }
    // 0x004a9ae4
    charge(ctx, 2);
    v0 = s0;
    // 0x004a9bb4
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xC0);
    return;
L_004a9ac4_3:
    charge(ctx, 2);
    goto L_004a9adc;
}


// sub_4AC240 [rt2dObjectListCompact] -- walks an object list (the next pointer at +20), recursing every fourth level, and replaces each single-entry sList (count 1) by its entry (sub_4AB0E0); the list
// 0x004AC240 sub_4AC240 -- 332 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AC240(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ac240
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s1 = a0;
    sq(s0, sp, 0x0);
    if (s1 != 0) {
        // 0x004ac260
        charge(ctx, 3);
        lw(s0, s1, 20);
        if (s0 != 0) {
            // 0x004ac26c
            charge(ctx, 3);
            lw(s3, s0, 20);
            if (s3 != 0) {
                // 0x004ac278
                charge(ctx, 3);
                lw(s2, s3, 20);
                if (s2 != 0) {
                    // 0x004ac284
                    charge(ctx, 8);
                    link(ctx, 0x4AC284u);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, 20);
                    call(ctx, gen::fn_sub_4AC240_004ac240);
                    sw(v0, s2, 20);
                    link(ctx, 0x4AC290u);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, 0);
                    call(ctx, gen::fn_sub_4C2120_004c2120);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x004ac2a4
                        charge(ctx, 3);
                        a0 = s2;
                        jal(ctx, 0x4AC2A4u, gen::fn_sub_4AB0E0_004ab0e0);
                        s2 = v0;
                    }
                }
                // 0x004ac2b0
                charge(ctx, 6);
                sw(s2, s3, 20);
                link(ctx, 0x4AC2B4u);  // $ra first: the delay slot below depends on it
                lw(a0, s3, 0);
                call(ctx, gen::fn_sub_4C2120_004c2120);
                v1 = 1;
                if (v0 == v1) {
                    // 0x004ac2c8
                    charge(ctx, 3);
                    a0 = s3;
                    jal(ctx, 0x4AC2C8u, gen::fn_sub_4AB0E0_004ab0e0);
                    s3 = v0;
                }
            }
            // 0x004ac2d4
            charge(ctx, 6);
            sw(s3, s0, 20);
            link(ctx, 0x4AC2D8u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn_sub_4C2120_004c2120);
            v1 = 1;
            if (v0 == v1) {
                // 0x004ac2ec
                charge(ctx, 3);
                a0 = s0;
                jal(ctx, 0x4AC2ECu, gen::fn_sub_4AB0E0_004ab0e0);
                s0 = v0;
            }
        }
        // 0x004ac2f8
        charge(ctx, 6);
        sw(s0, s1, 20);
        link(ctx, 0x4AC2FCu);  // $ra first: the delay slot below depends on it
        lw(a0, s1, 0);
        call(ctx, gen::fn_sub_4C2120_004c2120);
        v1 = 1;
        if (v0 == v1) {
            // 0x004ac310
            charge(ctx, 3);
            lw(a0, s1, 0);
            lw(s0, s1, 20);
            if (a0 != 0) {
                // 0x004ac31c
                charge(ctx, 4);
                lw(v1, s1, 4);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x004ac33c
                    charge(ctx, 4);
                    v0 = 0x960000;
                    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                    jalr(ctx, 0x4AC344u, v0.u());
                    goto L_004ac34c;
                }
                // 0x004ac32c
                charge(ctx, 4);
                jal(ctx, 0x4AC32Cu, gen::fn_sub_4C20B0_004c20b0);
                sw(zero, s1, 0);
                goto L_004ac350;
            }
        L_004ac34c:
            charge(ctx, 1);
            sw(zero, s1, 0);
        L_004ac350:
            charge(ctx, 7);
            v1 = 0x960000;
            v0 = 0x960000;
            lw(a0, v1, -4732);  // 0x95ED84
            lw(v0, v0, 396);  // 0x96018C (free-list free slot)
            a1 = s1;
            jalr(ctx, 0x4AC360u, v0.u());
            s1 = s0;
        }
    }
    // 0x004ac36c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = s1;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_4AC410 [rt2dObjectListClear] -- clears an object list's string slots: an sList-backed slot (+4 == -1) destroyed, an allocated one freed, both zeroed; recursing down the list (+20)
// 0x004AC410 sub_4AC410 -- 340 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AC410(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ac410
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = si(-1);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 4);
    if (a0 == v1) {
        // 0x004ac530
        charge(ctx, 4);
        link(ctx, 0x4AC530u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);
        call(ctx, gen::fn_sub_4C20B0_004c20b0);
        sw(zero, s0, 0);
        backedge(ctx);
    } else {
        // 0x004ac434
        charge(ctx, 3);
        lw(a0, s0, 0);
        if (a0 != 0) {
            // 0x004ac440
            charge(ctx, 4);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            jalr(ctx, 0x4AC448u, v0.u());
        }
        // 0x004ac450
        charge(ctx, 1);
        sw(zero, s0, 0);
    }
    // 0x004ac454
    charge(ctx, 4);
    sw(zero, s0, 4);
    lw(s1, s0, 20);
    if (s1 == 0) {
        // 0x004ac550
        charge(ctx, 1);
        ld(ra, sp, 0x20);
    } else {
        // 0x004ac464
        charge(ctx, 4);
        lw(a0, s1, 4);
        v1 = si(-1);
        if (a0 == v1) {
            // 0x004ac540
            charge(ctx, 4);
            link(ctx, 0x4AC540u);  // $ra first: the delay slot below depends on it
            lw(a0, s1, 0);
            call(ctx, gen::fn_sub_4C20B0_004c20b0);
            sw(zero, s1, 0);
            backedge(ctx);
        } else {
            // 0x004ac474
            charge(ctx, 3);
            lw(a0, s1, 0);
            if (a0 != 0) {
                // 0x004ac480
                charge(ctx, 4);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                jalr(ctx, 0x4AC488u, v0.u());
            }
            // 0x004ac490
            charge(ctx, 1);
            sw(zero, s1, 0);
        }
        // 0x004ac494
        charge(ctx, 4);
        sw(zero, s1, 4);
        lw(a0, s1, 20);
        if (a0 != 0) {
            // 0x004ac4a4
            charge(ctx, 5);
            jal(ctx, 0x4AC4A4u, gen::fn_sub_4AC410_004ac410);
            lw(a0, s1, 20);
            if (a0 != 0) {
                // 0x004ac4b8
                charge(ctx, 5);
                jal(ctx, 0x4AC4B8u, gen::fn_sub_4AB0E0_004ab0e0);
                a0 = v0;
                if (a0 != 0) {
                    // 0x004ac4cc
                    charge(ctx, 4);
                    jal(ctx, 0x4AC4CCu, gen::fn_sub_4AB0E0_004ab0e0);
                    a0 = v0;
                    jal(ctx, 0x4AC4D4u, gen::fn_sub_4AC390_004ac390);
                }
            }
            // 0x004ac4dc
            charge(ctx, 1);
            sw(zero, s1, 20);
        }
        // 0x004ac4e0
        charge(ctx, 3);
        lw(a0, s0, 20);
        if (a0 != 0) {
            // 0x004ac4ec
            charge(ctx, 5);
            jal(ctx, 0x4AC4ECu, gen::fn_sub_4AB0E0_004ab0e0);
            a0 = v0;
            if (a0 != 0) {
                // 0x004ac500
                charge(ctx, 5);
                jal(ctx, 0x4AC500u, gen::fn_sub_4AB0E0_004ab0e0);
                a0 = v0;
                if (a0 != 0) {
                    // 0x004ac514
                    charge(ctx, 4);
                    jal(ctx, 0x4AC514u, gen::fn_sub_4AB0E0_004ab0e0);
                    a0 = v0;
                    jal(ctx, 0x4AC51Cu, gen::fn_sub_4AC390_004ac390);
                }
            }
        }
        // 0x004ac524
        charge(ctx, 3);
        sw(zero, s0, 20);
        ld(ra, sp, 0x20);
    }
    // 0x004ac554 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4AC710 [rt2dObjectListFlatten] -- turns an object list's sList-backed slots (+4 == -1) into plain arrays (sub_4C2130) with their counts, down the list (+20, recursing every fourth record) while the slots are sList-backed
// 0x004AC710 sub_4AC710 -- 224 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AC710(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ac710
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (s0 != 0) {
        // 0x004ac730
        charge(ctx, 4);
        lw(v1, s0, 4);
        v0 = si(-1);
        if (v1 == v0) {
            // 0x004ac740
            charge(ctx, 10);
            link(ctx, 0x4AC740u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn_sub_4C2120_004c2120);
            lw(a0, s0, 0);
            s1 = v0;
            jal(ctx, 0x4AC74Cu, gen::fn_sub_4C2130_004c2130);
            sw(v0, s0, 0);
            sw(s1, s0, 4);
            lw(s2, s0, 20);
            if (s2 != 0) {
                // 0x004ac768
                charge(ctx, 4);
                lw(v1, s2, 4);
                v0 = si(-1);
                if (v1 == v0) {
                    // 0x004ac778
                    charge(ctx, 10);
                    link(ctx, 0x4AC778u);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, 0);
                    call(ctx, gen::fn_sub_4C2120_004c2120);
                    lw(a0, s2, 0);
                    s1 = v0;
                    jal(ctx, 0x4AC784u, gen::fn_sub_4C2130_004c2130);
                    sw(v0, s2, 0);
                    sw(s1, s2, 4);
                    lw(s2, s2, 20);
                    if (s2 != 0) {
                        // 0x004ac7a0
                        charge(ctx, 4);
                        lw(v1, s2, 4);
                        v0 = si(-1);
                        if (v1 == v0) {
                            // 0x004ac7b0
                            charge(ctx, 9);
                            link(ctx, 0x4AC7B0u);  // $ra first: the delay slot below depends on it
                            lw(a0, s2, 0);
                            call(ctx, gen::fn_sub_4C2120_004c2120);
                            lw(a0, s2, 0);
                            s1 = v0;
                            jal(ctx, 0x4AC7BCu, gen::fn_sub_4C2130_004c2130);
                            sw(v0, s2, 0);
                            sw(s1, s2, 4);
                            link(ctx, 0x4AC7CCu);  // $ra first: the delay slot below depends on it
                            lw(a0, s2, 20);
                            call(ctx, gen::fn_sub_4AC710_004ac710);
                        }
                    }
                }
            }
        }
    }
    // 0x004ac7d4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4AD480 [rt2dTextSetString] -- copies a text object's string: two-byte codes up to a 0 pair for a unicode font, else strlen + 1 bytes, into a new block (RwMalloc); its byte length at +8; 1 / 0
// 0x004AD480 sub_4AD480 -- 296 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AD480(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ad480
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 16);
    lw(a0, v0, 4);
    s2 = a1;
    jal(ctx, 0x4AD4A4u, gen::fn_sub_4A9BD0_004a9bd0);
    if (v0 == 0) {
        // 0x004ad534
        charge(ctx, 15);
        v0 = 0x960000;
        lw(v0, v0, 356);  // 0x960164 (the engine's strlen slot)
        a0 = s2;
        jalr(ctx, 0x4AD53Cu, v0.u());
        s1 = v0;
        v0 = 0x30000;
        a1 = v0 | 0x1A7;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
        a0 = addiu(s1, 1);
        jalr(ctx, 0x4AD558u, v0.u());
        sw(v0, s3, 0);
        lw(a0, s3, 0);
        if (a0 == 0) {
            // 0x004ad588
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x004ad570
            charge(ctx, 6);
            v0 = 0x960000;
            lw(v0, v0, 316);  // 0x96013C (the engine's strcpy slot)
            a1 = s2;
            jalr(ctx, 0x4AD578u, v0.u());
            sw(s1, s3, 8);
            backedge(ctx);
        L_004ad524:
            charge(ctx, 2);
            v0 = s3;
        }
    } else {
        // 0x004ad4b4
        charge(ctx, 2);
        v1 = s2;
        s1 = 0;
        for (;;) {
            // 0x004ad4bc
            charge(ctx, 3);
            lb(v0, v1, 0);
            if (v0 == 0) {
                goto L_004ad4d8;
            }
        L_004ad4c8:
            charge(ctx, 3);
            s1 = addiu(s1, 2);
            v1 = addiu(v1, 2);
            backedge(ctx);
        }
    L_004ad4e8_5:
        charge(ctx, 11);
        v0 = 0x30000;
        s0 = addiu(s1, 2);
        a1 = v0 | 0x1A7;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
        a0 = s0;
        jalr(ctx, 0x4AD4FCu, v0.u());
        sw(v0, s3, 0);
        lw(a0, s3, 0);
        if (a0 != 0) {
            // 0x004ad514
            charge(ctx, 4);
            a1 = s2;
            a2 = s0;
            jal(ctx, 0x4AD518u, gen::fn_memcpy_00521250);
            sw(s1, s3, 8);
            goto L_004ad524;
        }
        // 0x004ad52c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004ad58c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_004ad4d8:
    charge(ctx, 4);
    lb(v0, v1, 1);
    if (v0 == 0) {
        goto L_004ad4e8_5;
    }
    backedge(ctx);
    goto L_004ad4c8;
}


// sub_4AD5B0 [rt2dTextObjectInit] -- initialises a text object: height 1.0, a fresh brush (Rt2dBrushCreate), the font by name (sub_4AD700; a missing font sets error 400 and flag 0x1000000), the string
// ($a0 = the object, $a1 = the string, $a2 = the font name) The object, or 0 (the brush destroyed) when the string
// cannot be copied.
// 0x004AD5B0 sub_4AD5B0 -- 240 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AD5B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ad5b0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v1 = 0x3F800000;
    sd(ra, sp, 0x30);
    v0 = si(-2);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    sw(v1, a0, 188);
    s0 = a2;
    lw(v1, a0, 8);
    v0 = v1 & v0;
    link(ctx, 0x4AD5E4u);  // $ra first: the delay slot below depends on it
    sw(v0, a0, 8);
    call(ctx, gen::fn_sub_4A5470_004a5470);
    sw(v0, s2, 180);
    lw(v0, s2, 180);
    if (v0 != 0) {
        // 0x004ad604
        charge(ctx, 5);
        a1 = s0;
        a0 = s2;
        jal(ctx, 0x4AD608u, gen::fn_sub_4AD700_004ad700);
        if (v0 == 0) {
            // 0x004ad64c
            charge(ctx, 12);
            v0 = 400;
            a0 = 0;
            link(ctx, 0x4AD654u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x48);
            call(ctx, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x4C);
            a0 = addiu(sp, 0x48);
            jal(ctx, 0x4AD660u, gen::fn_sub_4C1C50_004c1c50);
            lw(v1, s2, 8);
            v0 = 0x1000000;
            v0 = v1 | v0;
            sw(v0, s2, 8);
            backedge(ctx);
        }
        // 0x004ad618
        charge(ctx, 2);
        if (s1 == 0) {
            // 0x004ad67c
            charge(ctx, 3);
            sw(zero, s2, 176);
            sw(zero, s2, 184);
            backedge(ctx);
        L_004ad644:
            charge(ctx, 2);
            v0 = s2;
        } else {
            // 0x004ad620
            charge(ctx, 5);
            a1 = s1;
            a0 = addiu(s2, 176);
            jal(ctx, 0x4AD624u, gen::fn_sub_4AD480_004ad480);
            if (v0 != 0) {
                goto L_004ad644;
            }
            // 0x004ad634
            charge(ctx, 4);
            link(ctx, 0x4AD634u);  // $ra first: the delay slot below depends on it
            lw(a0, s2, 180);
            call(ctx, gen::fn_sub_4A5540_004a5540);
            v0 = 0;
        }
    } else {
        // 0x004ad5fc
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004ad688 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_4AD700 [rt2dTextSetFont] -- sets a text object's font (+192) to the font of that name (sub_4A9A80); the object, or 0 when none
// 0x004AD700 sub_4AD700 -- 80 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AD700(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ad700
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    s1 = a0;
    sq(s0, sp, 0x0);
    a0 = a1;
    s0 = s1;
    jal(ctx, 0x4AD718u, gen::fn_sub_4A9A80_004a9a80);
    if (v0 == 0) {
        // 0x004ad734
        charge(ctx, 2);
        s0 = 0;
        backedge(ctx);
    }
    // 0x004ad728
    charge(ctx, 3);
    sw(v0, s1, 192);
    v0 = s0;
    // 0x004ad73c
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4AD940 [rt2dTextObjectStreamRead] -- reads a text object: the font name and string lengths and bytes, the height, then the object set up (sub_4AD5B0) and its brush read (Rt2dBrushStreamRead)
// 0x004AD940 sub_4AD940 -- 524 bytes; frame 0x90: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AD940(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x004ad940
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    a2 = 4;
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    a0 = s4;
    sq(s1, sp, 0x10);
    a1 = addiu(sp, 0x84);
    sq(s0, sp, 0x0);
    s2 = 0;
    jal(ctx, 0x4AD974u, gen::fn_sub_4C5250_004c5250);
    a2 = 4;
    if (v0 == a2) {
        // 0x004ad990
        charge(ctx, 6);
        a0 = s4;
        a1 = addiu(sp, 0x7C);
        jal(ctx, 0x4AD994u, gen::fn_sub_4C5250_004c5250);
        v1 = 4;
        if (v0 != v1) {
            backedge(ctx);
            goto L_004ad988;
        }
        // 0x004ad9a8
        charge(ctx, 11);
        s0 = 0x960000;
        lw(a0, sp, 0x84);
        s0 = addiu(s0, 376);  // &0x960178 (RwMalloc slot)
        v1 = 0x10000;
        lw(v0, s0, 0);  // 0x960178 (RwMalloc slot)
        a1 = v1 | 0x1A7;
        a0 = addiu(a0, 3);
        jalr(ctx, 0x4AD9C0u, v0.u());
        s3 = v0;
        if (s3 != 0) {
            // 0x004ad9d4
            charge(ctx, 8);
            lw(v0, sp, 0x84);
            a0 = s4;
            a1 = s3;
            s1 = addiu(v0, 1);
            a2 = s1;
            jal(ctx, 0x4AD9E4u, gen::fn_sub_4C5250_004c5250);
            if (s1 != v0) {
                goto L_004adac8;
            }
            // 0x004ad9f4
            charge(ctx, 7);
            a0 = s4;
            a1 = addiu(sp, 0x80);
            a2 = 4;
            jal(ctx, 0x4AD9FCu, gen::fn_sub_4C5250_004c5250);
            v1 = 4;
            if (v0 != v1) {
                goto L_004adac8;
            }
            // 0x004ada10
            charge(ctx, 9);
            lw(v0, sp, 0x84);
            v0 = addu(v0, s3);
            sb(zero, v0, 1);
            lw(v0, sp, 0x84);
            v0 = addu(v0, s3);
            sb(zero, v0, 2);
            lw(v0, sp, 0x80);
            s1 = 0;
            if (v0 != 0) {
                // 0x004adae0
                charge(ctx, 8);
                a0 = addiu(v0, 1);
                v1 = 0x10000;
                lw(v0, s0, 0);
                a1 = v1 | 0x1A7;
                jalr(ctx, 0x4ADAECu, v0.u());
                s2 = v0;
                if (s2 == 0) {
                    backedge(ctx);
                } else {
                    // 0x004adb00
                    charge(ctx, 8);
                    lw(v0, sp, 0x80);
                    a0 = s4;
                    a1 = s2;
                    s0 = addiu(v0, 1);
                    a2 = s0;
                    jal(ctx, 0x4ADB10u, gen::fn_sub_4C5250_004c5250);
                    if (s0 != v0) {
                        backedge(ctx);
                    } else {
                        // 0x004adb20
                        charge(ctx, 2);
                        s1 = 1;
                        backedge(ctx);
                    }
                }
            } else {
                // 0x004ada34
                charge(ctx, 1);
                s1 = 1;
            }
            // 0x004ada38
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x004ada40
                charge(ctx, 6);
                a0 = s5;
                a1 = s3;
                a2 = s2;
                jal(ctx, 0x4ADA48u, gen::fn_sub_4AD5B0_004ad5b0);
                if (v0 == 0) {
                    goto L_004adab8;
                }
                // 0x004ada58
                charge(ctx, 7);
                a0 = s4;
                a1 = 418;
                a2 = addiu(sp, 0x8C);
                a3 = addiu(sp, 0x88);
                jal(ctx, 0x4ADA64u, gen::fn_sub_4C1600_004c1600);
                if (v0 == 0) {
                    goto L_004adab8;
                }
                // 0x004ada74
                charge(ctx, 5);
                lw(a0, s5, 180);
                a1 = s4;
                jal(ctx, 0x4ADA78u, gen::fn_sub_4A6530_004a6530);
                if (v0 == 0) {
                    goto L_004adab8;
                }
                // 0x004ada88
                charge(ctx, 12);
                lwc1(f0, sp, 0x7C);
                s0 = 0x960000;
                s0 = addiu(s0, 380);  // &0x96017C (RwFree slot)
                swc1(f0, s5, 188);
                lw(v0, s0, 0);  // 0x96017C (RwFree slot)
                a0 = s2;
                jalr(ctx, 0x4ADA9Cu, v0.u());
                lw(v0, s0, 0);  // 0x96017C (RwFree slot)
                a0 = s3;
                jalr(ctx, 0x4ADAA8u, v0.u());
                v0 = s5;
                // 0x004adb28 (the shared epilogue, written out on this path)
                charge(ctx, 9);
                ld(ra, sp, 0x60);
                lq(s5, sp, 0x50);
                lq(s4, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x90);
                return;
            }
        L_004adab8:
            charge(ctx, 4);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            a0 = s2;
            jalr(ctx, 0x4ADAC0u, v0.u());
            goto L_004adac8;
        }
    L_004adac8:
        charge(ctx, 6);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        a0 = s3;
        jalr(ctx, 0x4ADAD0u, v0.u());
        backedge(ctx);
        goto L_004ad988;
    }
L_004ad988:
    charge(ctx, 2);
    v0 = 0;
    // 0x004adb28 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}


// sub_4ADC90 [rt2dObjectCopyHeader] -- copies a 272-byte Rt2d object (memcpy, a tail call)
// 0x004ADC90 sub_4ADC90 -- 8 bytes; leaf frame (no stack)
void sub_4ADC90(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6};
    // 0x004adc90
    enter(ctx, 2);  // entry check point + this block's cycles
    a2 = 272;
    gen::fn_memcpy_00521250(ctx);  // tail call
}


// sub_4ADCC0 [rt2dObjectInit] -- initialises an Rt2d object record: the type, the id 666, two identity matrices, flags |= 0x20003, cleared colour and depth
// 0x004ADCC0 sub_4ADCC0 -- 236 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4ADCC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004adcc0
    enter(ctx, 59);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 666;
    sd(ra, sp, 0x10);
    t0 = 0x3F800000;
    sq(s0, sp, 0x0);
    a2 = 96;
    sw(a1, a0, 0);
    s0 = a0;
    sw(v0, a0, 4);
    a1 = 0;
    sw(t0, a0, 56);
    v0 = 0x20000;
    sw(t0, a0, 36);
    a3 = v0 | 0x3;
    sw(t0, a0, 16);
    v0 = 6;
    sw(zero, a0, 32);
    sw(zero, a0, 24);
    sw(zero, a0, 20);
    sw(zero, a0, 52);
    sw(zero, a0, 48);
    sw(zero, a0, 40);
    sw(zero, a0, 72);
    sw(zero, a0, 68);
    sw(zero, a0, 64);
    lw(v1, a0, 28);
    v1 = v1 | a3;
    sw(v1, a0, 28);
    sw(t0, a0, 120);
    sw(t0, a0, 100);
    sw(t0, a0, 80);
    sw(zero, a0, 96);
    sw(zero, a0, 88);
    sw(zero, a0, 84);
    sw(zero, a0, 116);
    sw(zero, a0, 112);
    sw(zero, a0, 104);
    sw(zero, a0, 136);
    sw(zero, a0, 132);
    sw(zero, a0, 128);
    lw(v1, a0, 92);
    v1 = v1 | a3;
    sw(v1, a0, 92);
    sw(t0, a0, 144);
    sw(t0, a0, 148);
    sw(t0, a0, 152);
    sw(t0, a0, 156);
    sw(zero, a0, 160);
    sw(zero, a0, 164);
    sw(zero, a0, 168);
    sw(zero, a0, 172);
    sw(v0, a0, 8);
    a0 = addiu(s0, 176);
    jal(ctx, 0x4ADD90u, gen::fn_memset_00521408);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4AE150 [rt2dObjectSetColorMult] -- sets an object's colour multiplier: the four floats x 255 at +160, flag bit 3 (changed); the object
// 0x004AE150 sub_4AE150 -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4AE150(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x004ae150
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 16;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = addiu(s0, 160);
    jal(ctx, 0x4AE164u, gen::fn_memcpy_00521250);
    lwc1(f0, s0, 160);
    v1 = 0x437F0000;
    mtc1(v1, f1);
    v0 = s0;
    mul_s(f0, f0, f1);
    swc1(f0, s0, 160);
    lwc1(f0, s0, 164);
    mul_s(f0, f0, f1);
    swc1(f0, s0, 164);
    lwc1(f0, s0, 168);
    mul_s(f0, f0, f1);
    swc1(f0, s0, 168);
    lwc1(f0, s0, 172);
    mul_s(f0, f0, f1);
    swc1(f0, s0, 172);
    lw(v1, s0, 8);
    v1 = v1 | 0x8;
    sw(v1, s0, 8);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4B0B10 [rt2dTriangulateRun] -- triangulates a closed outline by ear clipping: a three-vertex outline is one triangle; else each ear found (sub_4B0430) is cut off, its three indices appended, recursing on the rest
// 0x004B0B10 sub_4B0B10 -- 732 bytes; frame 0xB0: ra sp+0x90, s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
void sub_4B0B10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f20{ctx, 20};
    // 0x004b0b10
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    v0 = 3;
    sd(ra, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    lw(v1, a0, 12);
    s5 = a0;
    if (v1 != v0) {
        // 0x004b0bf0
        charge(ctx, 4);
        lw(s2, s5, 4);
        s4 = 0;
        lw(s1, s2, 0);
        lw(s0, s1, 0);
        for (;;) {
            // 0x004b0c00
            charge(ctx, 8);
            a0 = s5;
            a1 = s0;
            a2 = s2;
            a3 = s1;
            jal(ctx, 0x4B0C0Cu, gen::fn_sub_4B0430_004b0430);
            v1 = 1;
            if (v0 == v1) {
                goto L_004b0c20_5;
            }
            // 0x004b0c2c
            charge(ctx, 5);
            s2 = s1;
            lw(v0, s5, 4);
            s1 = s0;
            lw(s0, s0, 0);
            if (s2 != v0) {
                backedge(ctx);
                continue;
            }
            break;
        }
    L_004b0c40:
        charge(ctx, 2);
        if (s4 == 0) {
            backedge(ctx);
        } else {
            // 0x004b0c48
            charge(ctx, 7);
            lw(s2, s5, 4);
            mtc1(zero, f20);
            lw(s6, s2, 0);
            lw(s1, s6, 0);
            lw(s3, s1, 0);
            s0 = 0;
            if (s3 != s2) {
                // 0x004b0c64
                charge(ctx, 1);
                s7 = addiu(sp, 0xAC);
                for (;;) {
                    // 0x004b0c68
                    charge(ctx, 9);
                    a0 = s5;
                    a1 = s3;
                    a2 = s2;
                    a3 = s6;
                    t0 = s1;
                    jal(ctx, 0x4B0C78u, gen::fn_sub_4B0560_004b0560);
                    v1 = 8;
                    if (v0 == v1) {
                        // 0x004b0ce0
                        charge(ctx, 45);
                        lw(v1, s2, 4);
                        a0 = addiu(sp, 0xA8);
                        lw(v0, s1, 4);
                        a1 = a0;
                        lw(a2, s5, 16);
                        v1 = sll(v1, 3);
                        v0 = sll(v0, 3);
                        v1 = addu(a2, v1);
                        v0 = addu(a2, v0);
                        lwc1(f1, v1, 4);
                        lwc1(f0, v0, 4);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0xA8);
                        lw(v1, s1, 4);
                        lw(v0, s2, 4);
                        lw(a2, s5, 16);
                        v1 = sll(v1, 3);
                        v0 = sll(v0, 3);
                        v1 = addu(a2, v1);
                        v0 = addu(a2, v0);
                        lwc1(f1, v1, 0);
                        lwc1(f0, v0, 0);
                        sub_s(f0, f1, f0);
                        link(ctx, 0x4B0D3Cu);  // $ra first: the delay slot below depends on it
                        swc1(f0, s7, 0);
                        call(ctx, gen::fn_sub_4C6B20_004c6b20);
                        lw(v1, s3, 4);
                        lwc1(f0, s7, 0);
                        lw(v0, s1, 4);
                        lwc1(f3, sp, 0xA8);
                        lw(a0, s5, 16);
                        v1 = sll(v1, 3);
                        v0 = sll(v0, 3);
                        v1 = addu(a0, v1);
                        v0 = addu(a0, v0);
                        lwc1(f2, v0, 4);
                        lwc1(f1, v1, 4);
                        lwc1(f5, v0, 0);
                        lwc1(f4, v1, 0);
                        sub_s(f1, f2, f1);
                        sub_s(f4, f5, f4);
                        mula_s(f1, f0);
                        madd_s(f0, f4, f3);
                        c_le_s(f0, f20);
                        if (cond(ctx)) {
                            backedge(ctx);
                        } else {
                            // 0x004b0d94
                            charge(ctx, 3);
                            mov_s(f20, f0);
                            s0 = s3;
                            backedge(ctx);
                        }
                    } else {
                        // 0x004b0c8c
                        charge(ctx, 1);
                    }
                    // 0x004b0c90
                    charge(ctx, 3);
                    lw(s3, s3, 0);
                    if (s3 == s2) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004b0c9c
                charge(ctx, 1);
            }
            // 0x004b0ca0
            charge(ctx, 2);
            if (s0 == 0) {
                // 0x004b0da0
                charge(ctx, 7);
                lw(a1, s5, 4);
                lw(v0, a1, 0);
                lw(a2, v0, 0);
                a0 = s5;
                jal(ctx, 0x4B0DACu, gen::fn_sub_4B08C0_004b08c0);
                s0 = v0;
                backedge(ctx);
            } else {
                // 0x004b0ca8
                charge(ctx, 5);
                a1 = s4;
                a2 = s0;
                a0 = s5;
                jal(ctx, 0x4B0CB0u, gen::fn_sub_4B08C0_004b08c0);
                s0 = v0;
            }
            // 0x004b0cbc
            charge(ctx, 9);
            a0 = s0;
            jal(ctx, 0x4B0CBCu, gen::fn_sub_4B0B10_004b0b10);
            a0 = s5;
            jal(ctx, 0x4B0CC4u, gen::fn_sub_4B0B10_004b0b10);
            a0 = s0;
            link(ctx, 0x4B0CD0u);  // $ra first: the delay slot below depends on it
            sw(zero, s0, 16);
            call(ctx, gen::fn_sub_4B0360_004b0360);
            backedge(ctx);
        }
    } else {
        // 0x004b0b4c
        charge(ctx, 39);
        lw(v0, s5, 4);
        lw(a1, s5, 8);
        lw(a0, v0, 4);
        lw(v1, a1, 0);
        lw(v0, a1, 4);
        v1 = sll(v1, 2);
        v0 = addu(v0, v1);
        sw(a0, v0, 0);
        lw(v1, s5, 8);
        lw(v0, v1, 0);
        v0 = addiu(v0, 1);
        sw(v0, v1, 0);
        lw(v0, s5, 4);
        lw(a1, s5, 8);
        lw(a0, v0, 0);
        lw(v1, a1, 0);
        lw(v0, a1, 4);
        lw(a0, a0, 4);
        v1 = sll(v1, 2);
        v0 = addu(v0, v1);
        sw(a0, v0, 0);
        lw(v1, s5, 8);
        lw(v0, v1, 0);
        v0 = addiu(v0, 1);
        sw(v0, v1, 0);
        lw(v0, s5, 4);
        lw(a1, s5, 8);
        lw(a0, v0, 0);
        lw(v1, a1, 0);
        lw(v0, a1, 4);
        lw(a0, a0, 0);
        v1 = sll(v1, 2);
        v0 = addu(v0, v1);
        lw(v1, a0, 4);
        sw(v1, v0, 0);
        lw(v1, s5, 8);
        lw(v0, v1, 0);
        v0 = addiu(v0, 1);
        sw(v0, v1, 0);
    }
    // 0x004b0be8
    charge(ctx, 2);
    v0 = s5;
    // 0x004b0dbc
    charge(ctx, 12);
    ld(ra, sp, 0x90);
    lwc1(f20, sp, 0x0);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0xB0);
    return;
L_004b0c20_5:
    charge(ctx, 3);
    sw(s2, s5, 4);
    s4 = s1;
    goto L_004b0c40;
}


// sub_4B0FA0 [rt2dPathTriangulate] -- triangulates a path's outline (sub_4B0DF0 builds it) into the index buffer $a2: the triangle count to *$a1; the outline freed; $a0
// 0x004B0FA0 sub_4B0FA0 -- 164 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B0FA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b0fa0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a2;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    s1 = a1;
    link(ctx, 0x4B0FC4u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4B0DF0_004b0df0);
    s0 = v0;
    if (s0 != 0) {
        // 0x004b0fd8
        charge(ctx, 18);
        s3 = 0x960000;
        a0 = s0;
        s3 = addiu(s3, -4708);  // &0x95ED9C (the path fill's triangulation: index count)
        sw(s4, s3, 4);  // 0x95EDA0 (the path fill's triangulation: the index buffer)
        sw(zero, s3, 0);  // 0x95ED9C (the path fill's triangulation: index count)
        link(ctx, 0x4B0FECu);  // $ra first: the delay slot below depends on it
        sw(s3, s0, 8);
        call(ctx, gen::fn_sub_4B0B10_004b0b10);
        lw(v1, s3, 0);  // 0x95ED9C (the path fill's triangulation: index count)
        v0 = 0x55550000;
        v0 = v0 | 0x5556;
        mult(zero, v0, v1);
        v1 = srl(v1, 31);
        mfhi(v0);
        a0 = s0;
        v0 = addu(v0, v1);
        link(ctx, 0x4B1018u);  // $ra first: the delay slot below depends on it
        sw(v0, s1, 0);
        call(ctx, gen::fn_sub_4B0360_004b0360);
    }
    // 0x004b1020 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = s2;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_4B1420 [rt2dKeyFrameListReset] -- rewinds a keyframe list: time 0, the first and last entries of its sList, the first entry's changes applied to the props ($a1); $a0
// 0x004B1420 sub_4B1420 -- 152 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B1420(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b1420
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(a0, a0, 0);
    s1 = a1;
    jal(ctx, 0x4B143Cu, gen::fn_sub_4C2120_004c2120);
    s0 = v0;
    sw(zero, s2, 8);
    if (i64(s0) > 0) {
        // 0x004b1464
        charge(ctx, 15);
        sw(zero, s2, 16);
        lw(a0, s2, 0);
        a1 = 0;
        jal(ctx, 0x4B146Cu, gen::fn_sub_4C21B0_004c21b0);
        sw(v0, s2, 20);
        lw(a0, s2, 0);
        a1 = addiu(s0, -1);
        jal(ctx, 0x4B147Cu, gen::fn_sub_4C21B0_004c21b0);
        sw(v0, s2, 24);
        lw(v0, s2, 20);
        lw(a0, v0, 4);
        a1 = s1;
        jal(ctx, 0x4B1490u, gen::fn_sub_4B2300_004b2300);
        backedge(ctx);
    } else {
        // 0x004b1450
        charge(ctx, 3);
        sw(zero, s2, 16);
        sw(zero, s2, 20);
        sw(zero, s2, 24);
    }
    // 0x004b145c
    charge(ctx, 2);
    v0 = s2;
    // 0x004b14a0
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4B14C0 [rt2dAnimAddDeltaTime] -- advances an animation by $f12 x its speed (+4, + its offset +8): the new time through sub_4B1700; $a0
// 0x004B14C0 sub_4B14C0 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B14C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x004b14c0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    mtc1(zero, f0);
    sq(s0, sp, 0x0);
    lwc1(f1, a0, 8);
    s0 = a0;
    lwc1(f2, a0, 4);
    adda_s(f0, f1);
    madd_s(f12, f12, f2);
    jal(ctx, 0x4B14E0u, gen::fn_sub_4B1700_004b1700);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4B1500 [rt2dKeyFrameListStep] -- steps a keyframe list $a2 entries forwards (positive) or backwards (negative), applying each entry's changes to the props; the list's current / next entry pointers updated; $a0
// 0x004B1500 sub_4B1500 -- 288 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B1500(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x004b1500
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    lw(a0, a0, 0);
    s1 = a2;
    jal(ctx, 0x4B1524u, gen::fn_sub_4C2090_004c2090);
    s0 = v0;
    for (;;) {
        // 0x004b1530
        charge(ctx, 2);
        if (i64(s1) > 0) {
            // 0x004b1538
            charge(ctx, 3);
            lw(v0, s3, 20);
            if (v0 != 0) {
                // 0x004b1544
                charge(ctx, 13);
                lwc1(f0, v0, 0);
                swc1(f0, s3, 8);
                lw(v0, s3, 20);
                lw(a0, v0, 4);
                a1 = s2;
                jal(ctx, 0x4B1554u, gen::fn_sub_4B2300_004b2300);
                lw(v0, s3, 20);
                sw(v0, s3, 16);
                lw(v1, s3, 20);
                lw(v0, s3, 24);
                at = sltu(v1, v0);
                if (at == 0) {
                    // 0x004b1588
                    charge(ctx, 2);
                    sw(zero, s3, 20);
                } else {
                    // 0x004b1578
                    charge(ctx, 4);
                    lw(v0, s3, 20);
                    v0 = addiu(v0, 8);
                    sw(v0, s3, 20);
                }
                // 0x004b1590
                charge(ctx, 2);
                s1 = addiu(s1, -1);
                backedge(ctx);
                continue;
            }
        }
        break;
    }
    for (;;) {
        // 0x004b1598
        charge(ctx, 2);
        if (i64(s1) < 0) {
            // 0x004b15a0
            charge(ctx, 3);
            lw(v0, s3, 16);
            if (v0 != 0) {
                // 0x004b15ac
                charge(ctx, 12);
                lwc1(f0, v0, 0);
                swc1(f0, s3, 8);
                lw(v0, s3, 16);
                lw(a0, v0, 4);
                a1 = s2;
                jal(ctx, 0x4B15BCu, gen::fn_sub_4B2300_004b2300);
                lw(v0, s3, 16);
                sw(v0, s3, 20);
                lw(v0, s3, 16);
                at = sltu(s0, v0);
                if (at == 0) {
                    // 0x004b15f0
                    charge(ctx, 2);
                    sw(zero, s3, 16);
                } else {
                    // 0x004b15dc
                    charge(ctx, 4);
                    lw(v0, s3, 16);
                    v0 = addiu(v0, -8);
                    sw(v0, s3, 16);
                }
                // 0x004b15f8
                charge(ctx, 2);
                s1 = addiu(s1, -1);
                backedge(ctx);
                continue;
            }
        }
        break;
    }
    // 0x004b1600 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = s3;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_4B1700 [rt2dAnimSetTime] -- moves an animation to time $f12: steps through the keyframes in the direction of the change, wrapping at the ends when looping (the 1.0 / 0.0 bounds), each crossed keyframe applied; $a0
// 0x004B1700 sub_4B1700 -- 360 bytes; frame 0x60: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
void sub_4B1700(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    // 0x004b1700
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    s3 = a0;
    sq(s1, sp, 0x20);
    s2 = a1;
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lwc1(f0, a0, 8);
    mov_s(f21, f12);
    mtc1(zero, f20);
    c_le_s(f21, f0);
    s1 = 0;
    if (!cond(ctx)) {
        // 0x004b17e8
        charge(ctx, 2);
        s0 = 1;
        backedge(ctx);
    L_004b1754:
        charge(ctx, 5);
        mtc1(zero, f1);
        c_lt_s(f21, f1);
        if (!cond(ctx)) {
            // 0x004b1784
            charge(ctx, 5);
            lw(v0, s3, 24);
            lwc1(f0, v0, 0);
            c_le_s(f21, f0);
            if (!cond(ctx)) {
                // 0x004b1798
                charge(ctx, 5);
                sub_s(f1, f21, f0);
                s1 = 1;
                mov_s(f21, f0);
                lwc1(f0, s3, 4);
                div_s(f20, f1, f0);
            }
        } else {
            // 0x004b1768
            charge(ctx, 7);
            lwc1(f0, s3, 4);
            s1 = 1;
            div_s(f20, f21, f0);
            mov_s(f21, f1);
        }
        // 0x004b17ac
        charge(ctx, 1);
        lw(v1, s3, 20);
        for (;;) {
            // 0x004b17b0
            charge(ctx, 4);
            v0 = sltu(0, v1);
            v0 = v0 ^ 0x1;
            if (v0 == 0) {
                // 0x004b17c0
                charge(ctx, 4);
                lwc1(f0, v1, 0);
                c_le_s(f0, f21);
                if (cond(ctx)) {
                L_004b17d0:
                    charge(ctx, 6);
                    a0 = s3;
                    a1 = s2;
                    a2 = s0;
                    jal(ctx, 0x4B17D8u, gen::fn_sub_4B1500_004b1500);
                    lw(v1, s3, 20);
                    backedge(ctx);
                    continue;
                }
            }
            // 0x004b17f8
            charge(ctx, 3);
            lw(v0, s3, 16);
            if (v0 == 0) {
                goto L_004b1818;
            }
            // 0x004b1804
            charge(ctx, 4);
            lwc1(f0, v0, 0);
            c_le_s(f0, f21);
            if (cond(ctx)) {
                break;
            }
            backedge(ctx);
            goto L_004b17d0;
        }
        // 0x004b1814
        charge(ctx, 1);
    L_004b1818:
        charge(ctx, 3);
        v0 = 1;
        swc1(f21, s3, 8);
        if (s1 == v0) {
            // 0x004b1824
            charge(ctx, 3);
            lw(v0, gp, -17492);  // 0x7CE89C
            if (v0 != 0) {
                // 0x004b1830
                charge(ctx, 4);
                a1 = s2;
                a0 = s3;
                mov_s(f12, f20);
                jalr(ctx, 0x4B1838u, v0.u());
            }
        }
        // 0x004b1840
        charge(ctx, 1);
        v0 = s3;
    } else {
        // 0x004b1744
        charge(ctx, 3);
        c_lt_s(f21, f0);
        if (cond(ctx)) {
            // 0x004b1750
            charge(ctx, 1);
            s0 = si(-1);
            goto L_004b1754;
        }
        // 0x004b17f0
        charge(ctx, 2);
        v0 = s3;
    }
    // 0x004b1844 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lwc1(f21, sp, 0x4);
    lq(s3, sp, 0x40);
    lwc1(f20, sp, 0x0);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x60);
}


// sub_4B1870 [rt2dKeyFrameListGotoIndex] -- moves a keyframe list to entry $a2: rewinds when the target lies before the current one, then steps forwards to it; $a0
// 0x004B1870 sub_4B1870 -- 276 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B1870(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b1870
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    lw(a0, a0, 0);
    s1 = a2;
    jal(ctx, 0x4B1898u, gen::fn_sub_4C2090_004c2090);
    lw(v1, s3, 16);
    a0 = sll(s1, 3);
    s0 = addu(v0, a0);
    v0 = sltu(s0, v1);
    if (v0 != 0) {
        // 0x004b18f0
        charge(ctx, 5);
        link(ctx, 0x4B18F0u);  // $ra first: the delay slot below depends on it
        lw(a0, s3, 0);
        call(ctx, gen::fn_sub_4C2120_004c2120);
        s4 = v0;
        sw(zero, s3, 8);
        if (i64(s4) > 0) {
            // 0x004b1928
            charge(ctx, 15);
            sw(zero, s3, 16);
            lw(a0, s3, 0);
            a1 = 0;
            jal(ctx, 0x4B1930u, gen::fn_sub_4C21B0_004c21b0);
            sw(v0, s3, 20);
            lw(a0, s3, 0);
            a1 = addiu(s4, -1);
            jal(ctx, 0x4B1940u, gen::fn_sub_4C21B0_004c21b0);
            sw(v0, s3, 24);
            lw(v0, s3, 20);
            lw(a0, v0, 4);
            a1 = s2;
            jal(ctx, 0x4B1954u, gen::fn_sub_4B2300_004b2300);
            a0 = s3;
            backedge(ctx);
        } else {
            // 0x004b1904
            charge(ctx, 4);
            sw(zero, s3, 16);
            sw(zero, s3, 20);
            sw(zero, s3, 24);
            a0 = s3;
        }
        // 0x004b1914
        charge(ctx, 5);
        a1 = s2;
        a2 = 1;
        jal(ctx, 0x4B1918u, gen::fn_sub_4B1500_004b1500);
        lw(v0, s3, 16);
        backedge(ctx);
    } else {
        // 0x004b18b8
        charge(ctx, 1);
        lw(v0, s3, 16);
    }
    // 0x004b18bc
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x004b18c4
        charge(ctx, 3);
        v0 = subu(s0, v0);
        s1 = sra(v0, 3);
        if (i64(v0) < 0) {
            // 0x004b18d0
            charge(ctx, 2);
            v0 = addiu(v0, 7);
            s1 = sra(v0, 3);
        }
    }
    // 0x004b18d8
    charge(ctx, 6);
    a0 = s3;
    a1 = s2;
    a2 = s1;
    jal(ctx, 0x4B18E0u, gen::fn_sub_4B1500_004b1500);
    ld(ra, sp, 0x50);
    // 0x004b1968
    charge(ctx, 7);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_4B1D00 [rt2dAnimStreamReadBody] -- reads an animation's keyframes: the header (count, duration), per keyframe its time and changed props (matrix, colour, colour offset, the object, a string), into 160-byte records; 1 / 0
// 0x004B1D00 sub_4B1D00 -- 1452 bytes; frame 0x100: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B1D00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x004b1d00
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    a2 = 12;
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s1 = a1;
    sq(s0, sp, 0x0);
    a1 = addiu(sp, 0xF0);
    s0 = 0;
    jal(ctx, 0x4B1D3Cu, gen::fn_sub_4C5250_004c5250);
    v1 = 12;
    if (v0 != v1) {
        // 0x004b1fb8
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004b1d50
        charge(ctx, 6);
        lwc1(f0, sp, 0xF4);
        s6 = addiu(sp, 0xF8);
        swc1(f0, s1, 0);
        lw(a0, s6, 0);
        s4 = 0;
        if (a0 != 0) {
            // 0x004b1d68
            charge(ctx, 11);
            v0 = 0x10000;
            v1 = sll(a0, 2);
            a1 = v0 | 0x1A9;
            v1 = addu(v1, a0);
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
            a0 = sll(v1, 5);
            jalr(ctx, 0x4B1D80u, v0.u());
            s0 = v0;
            if (s0 == 0) {
                // 0x004b1fc0
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004b1d94
                charge(ctx, 4);
                lw(v0, s6, 0);
                at = slt(0, v0);
                s3 = 0;
                if (at == 0) {
                    goto L_004b1eb4;
                }
                // 0x004b1da4
                charge(ctx, 3);
                s2 = s0;
                fp = addiu(sp, 0xEC);
                s7 = addiu(sp, 0xD4);
                for (;;) {
                    // 0x004b1db0
                    charge(ctx, 7);
                    a0 = s5;
                    a1 = addiu(sp, 0xE8);
                    a2 = 8;
                    jal(ctx, 0x4B1DB8u, gen::fn_sub_4C5250_004c5250);
                    v1 = 8;
                    if (v0 == v1) {
                        // 0x004b1fc8
                        charge(ctx, 6);
                        lw(v1, sp, 0xE8);
                        a0 = addiu(sp, 0xD0);
                        lw(v0, fp, 0x0);
                        sw(v1, sp, 0xD0);
                        sw(v0, s7, 0);
                        backedge(ctx);
                    } else {
                        // 0x004b1dcc
                        charge(ctx, 1);
                        a0 = 0;
                    }
                    // 0x004b1dd0
                    charge(ctx, 2);
                    if (a0 == 0) {
                        goto L_004b1fe0;
                    }
                    // 0x004b1dd8
                    charge(ctx, 13);
                    lw(a0, s7, 0);
                    v1 = 1;
                    lw(v0, sp, 0xD0);
                    s4 = addiu(s4, 16);
                    sw(a0, s2, 4);
                    sw(v1, s2, 0);
                    v0 = v0 & 0x1;
                    sw(zero, s2, 8);
                    sw(zero, s2, 80);
                    sw(zero, s2, 100);
                    sw(zero, s2, 120);
                    sw(zero, s2, 140);
                    if (v0 != 0) {
                        // 0x004b1ff8
                        charge(ctx, 7);
                        a0 = s5;
                        a1 = 13;
                        a2 = 0;
                        a3 = 0;
                        jal(ctx, 0x4B2004u, gen::fn_sub_4C1600_004c1600);
                        if (v0 != 0) {
                            // 0x004b2030
                            charge(ctx, 5);
                            a0 = s5;
                            a1 = addiu(s2, 16);
                            jal(ctx, 0x4B2034u, gen::fn_sub_4C19F0_004c19f0);
                            if (v0 == 0) {
                                // 0x004b204c
                                charge(ctx, 2);
                                v0 = 0;
                                backedge(ctx);
                            } else {
                                // 0x004b2044
                                charge(ctx, 2);
                                v0 = addiu(s2, 16);
                                backedge(ctx);
                            }
                        } else {
                            // 0x004b2014
                            charge(ctx, 1);
                            v0 = 0;
                        }
                        // 0x004b2018
                        charge(ctx, 2);
                        if (v0 == 0) {
                            goto L_004b2054;
                        }
                        // 0x004b2020
                        charge(ctx, 4);
                        v0 = 1;
                        s4 = addiu(s4, 64);
                        sw(v0, s2, 8);
                        backedge(ctx);
                        goto L_004b1e0c;
                    }
                L_004b1e0c:
                    charge(ctx, 4);
                    lw(v0, sp, 0xD0);
                    v0 = v0 & 0x2;
                    if (v0 != 0) {
                        // 0x004b206c
                        charge(ctx, 7);
                        a0 = s5;
                        a1 = addiu(sp, 0xC0);
                        a2 = 16;
                        jal(ctx, 0x4B2074u, gen::fn_sub_4C5250_004c5250);
                        v1 = 16;
                        if (v0 == v1) {
                            // 0x004b20a4
                            charge(ctx, 13);
                            lwc1(f0, sp, 0xC0);
                            v0 = addiu(sp, 0xC4);
                            v1 = addiu(s2, 84);
                            swc1(f0, s2, 84);
                            lwc1(f0, v0, 0);
                            swc1(f0, s2, 88);
                            v0 = addiu(sp, 0xC8);
                            lwc1(f0, v0, 0);
                            swc1(f0, s2, 92);
                            v0 = addiu(sp, 0xCC);
                            lwc1(f0, v0, 0);
                            swc1(f0, s2, 96);
                            backedge(ctx);
                        } else {
                            // 0x004b2088
                            charge(ctx, 1);
                            v1 = 0;
                        }
                        // 0x004b208c
                        charge(ctx, 2);
                        if (v1 == 0) {
                            goto L_004b20d8;
                        }
                        // 0x004b2094
                        charge(ctx, 4);
                        v0 = 1;
                        s4 = addiu(s4, 16);
                        sw(v0, s2, 80);
                        backedge(ctx);
                        goto L_004b1e1c;
                    }
                L_004b1e1c:
                    charge(ctx, 4);
                    lw(v0, sp, 0xD0);
                    v0 = v0 & 0x4;
                    if (v0 != 0) {
                        // 0x004b20f0
                        charge(ctx, 7);
                        a0 = s5;
                        a1 = addiu(sp, 0xB0);
                        a2 = 16;
                        jal(ctx, 0x4B20F8u, gen::fn_sub_4C5250_004c5250);
                        v1 = 16;
                        if (v0 == v1) {
                            // 0x004b2128
                            charge(ctx, 13);
                            lwc1(f0, sp, 0xB0);
                            v0 = addiu(sp, 0xB4);
                            v1 = addiu(s2, 104);
                            swc1(f0, s2, 104);
                            lwc1(f0, v0, 0);
                            swc1(f0, s2, 108);
                            v0 = addiu(sp, 0xB8);
                            lwc1(f0, v0, 0);
                            swc1(f0, s2, 112);
                            v0 = addiu(sp, 0xBC);
                            lwc1(f0, v0, 0);
                            swc1(f0, s2, 116);
                            backedge(ctx);
                        } else {
                            // 0x004b210c
                            charge(ctx, 1);
                            v1 = 0;
                        }
                        // 0x004b2110
                        charge(ctx, 2);
                        if (v1 == 0) {
                            goto L_004b215c;
                        }
                        // 0x004b2118
                        charge(ctx, 4);
                        v0 = 1;
                        s4 = addiu(s4, 16);
                        sw(v0, s2, 100);
                        backedge(ctx);
                        goto L_004b1e2c;
                    }
                L_004b1e2c:
                    charge(ctx, 4);
                    lw(v0, sp, 0xD0);
                    v0 = v0 & 0x8;
                    if (v0 != 0) {
                        // 0x004b1e3c
                        charge(ctx, 7);
                        a0 = s5;
                        a1 = addiu(sp, 0xE0);
                        a2 = 8;
                        jal(ctx, 0x4B1E44u, gen::fn_sub_4C5250_004c5250);
                        v1 = 8;
                        if (v0 == v1) {
                            // 0x004b1e60
                            charge(ctx, 7);
                            lw(v0, sp, 0xE0);
                            v1 = addiu(s2, 124);
                            v0 = sltu(0, v0);
                            sw(v0, s2, 124);
                            v0 = addiu(sp, 0xE4);
                            lw(v0, v0, 0);
                            sw(v0, s2, 128);
                        } else {
                            // 0x004b1e58
                            charge(ctx, 2);
                            v1 = 0;
                        }
                        // 0x004b1e7c
                        charge(ctx, 2);
                        if (v1 == 0) {
                            goto L_004b2174;
                        }
                        // 0x004b1e84
                        charge(ctx, 3);
                        v0 = 1;
                        s4 = addiu(s4, 16);
                        sw(v0, s2, 120);
                        goto L_004b1e90;
                    }
                L_004b1e90:
                    charge(ctx, 4);
                    lw(v0, sp, 0xD0);
                    v0 = v0 & 0x10;
                    if (v0 != 0) {
                        // 0x004b218c
                        charge(ctx, 7);
                        a0 = s5;
                        a1 = addiu(sp, 0xA0);
                        a2 = 16;
                        jal(ctx, 0x4B2194u, gen::fn_sub_4C5250_004c5250);
                        v1 = 16;
                        if (v0 == v1) {
                            // 0x004b21c4
                            charge(ctx, 10);
                            lwc1(f3, sp, 0xA0);
                            v0 = addiu(s2, 144);
                            lwc1(f2, sp, 0xA4);
                            lwc1(f1, sp, 0xA8);
                            lwc1(f0, sp, 0xAC);
                            swc1(f3, s2, 144);
                            swc1(f2, s2, 148);
                            swc1(f1, s2, 152);
                            swc1(f0, s2, 156);
                            backedge(ctx);
                        } else {
                            // 0x004b21a8
                            charge(ctx, 1);
                            v0 = 0;
                        }
                        // 0x004b21ac
                        charge(ctx, 2);
                        if (v0 == 0) {
                            break;
                        }
                        // 0x004b21b4
                        charge(ctx, 4);
                        v0 = 1;
                        s4 = addiu(s4, 16);
                        sw(v0, s2, 140);
                        backedge(ctx);
                        goto L_004b1ea0;
                    }
                L_004b1ea0:
                    charge(ctx, 5);
                    lw(v0, s6, 0);
                    s3 = addiu(s3, 1);
                    v0 = slt(s3, v0);
                    s2 = addiu(s2, 160);
                    if (v0 == 0) {
                        goto L_004b1eb4;
                    }
                    backedge(ctx);
                }
                // 0x004b21ec
                charge(ctx, 6);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                a0 = s0;
                jalr(ctx, 0x4B21F4u, v0.u());
                v0 = 0;
            }
            // 0x004b227c (the shared epilogue, written out on this path)
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
    L_004b1eb4:
        charge(ctx, 12);
        v0 = 0x30000;
        a1 = v0 | 0x1A9;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
        a0 = addiu(s4, 16);
        jalr(ctx, 0x4B1EC4u, v0.u());
        s4 = v0;
        s2 = 0;
        lw(v0, s6, 0);
        at = slt(0, v0);
        s5 = s4;
        if (at != 0) {
            // 0x004b1ee4
            charge(ctx, 1);
            s3 = s0;
            for (;;) {
                // 0x004b1ee8
                charge(ctx, 24);
                lw(v0, s3, 8);
                t1 = 2;
                lw(t2, s3, 80);
                a3 = 4;
                lw(t0, s3, 100);
                a1 = 8;
                lw(a2, s3, 120);
                v1 = 16;
                lw(a0, s3, 140);
                v0 = sltu(0, v0);
                if (t2 == 0) t1 = 0;
                v0 = v0 | t1;
                if (t0 == 0) a3 = 0;
                v0 = a3 | v0;
                if (a2 == 0) a1 = 0;
                v0 = a1 | v0;
                if (a0 == 0) v1 = 0;
                v0 = v1 | v0;
                sw(v0, s5, 0);
                lw(v0, s3, 4);
                sw(v0, s5, 4);
                lw(v0, s3, 8);
                s5 = addiu(s5, 16);
                if (v0 != 0) {
                    // 0x004b2204
                    charge(ctx, 6);
                    a0 = s5;
                    a1 = addiu(s3, 16);
                    a2 = 64;
                    jal(ctx, 0x4B220Cu, gen::fn_memcpy_00521250);
                    s5 = addiu(s5, 64);
                    backedge(ctx);
                }
                // 0x004b1f48
                charge(ctx, 3);
                lw(v0, s3, 80);
                if (v0 != 0) {
                    // 0x004b221c
                    charge(ctx, 6);
                    a0 = s5;
                    a1 = addiu(s3, 84);
                    a2 = 16;
                    jal(ctx, 0x4B2224u, gen::fn_memcpy_00521250);
                    s5 = addiu(s5, 16);
                    backedge(ctx);
                }
                // 0x004b1f54
                charge(ctx, 3);
                lw(v0, s3, 100);
                if (v0 != 0) {
                    // 0x004b2234
                    charge(ctx, 6);
                    a0 = s5;
                    a1 = addiu(s3, 104);
                    a2 = 16;
                    jal(ctx, 0x4B223Cu, gen::fn_memcpy_00521250);
                    s5 = addiu(s5, 16);
                    backedge(ctx);
                }
                // 0x004b1f60
                charge(ctx, 3);
                lw(v0, s3, 120);
                if (v0 != 0) {
                    // 0x004b224c
                    charge(ctx, 6);
                    a0 = s5;
                    a1 = addiu(s3, 124);
                    a2 = 16;
                    jal(ctx, 0x4B2254u, gen::fn_memcpy_00521250);
                    s5 = addiu(s5, 16);
                    backedge(ctx);
                }
                // 0x004b1f6c
                charge(ctx, 3);
                lw(v0, s3, 140);
                if (v0 != 0) {
                    // 0x004b2264
                    charge(ctx, 6);
                    a0 = s5;
                    a1 = addiu(s3, 144);
                    a2 = 16;
                    jal(ctx, 0x4B226Cu, gen::fn_memcpy_00521250);
                    s5 = addiu(s5, 16);
                    backedge(ctx);
                }
                // 0x004b1f78
                charge(ctx, 5);
                lw(v0, s6, 0);
                s2 = addiu(s2, 1);
                v0 = slt(s2, v0);
                s3 = addiu(s3, 160);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004b1f8c
        charge(ctx, 5);
        v0 = 32;
        sw(v0, s5, 0);
        sw(zero, s1, 4);
        sw(s4, s1, 8);
        if (s0 != 0) {
            // 0x004b1fa0
            charge(ctx, 4);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            a0 = s0;
            jalr(ctx, 0x4B1FA8u, v0.u());
        }
        // 0x004b1fb0
        charge(ctx, 2);
        v0 = s1;
    }
    // 0x004b227c (the shared epilogue, written out on this path)
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
L_004b1fe0:
    charge(ctx, 6);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    a0 = s0;
    jalr(ctx, 0x4B1FE8u, v0.u());
    v0 = 0;
    // 0x004b227c (the shared epilogue, written out on this path)
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
L_004b2054:
    charge(ctx, 6);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    a0 = s0;
    jalr(ctx, 0x4B205Cu, v0.u());
    v0 = 0;
    // 0x004b227c (the shared epilogue, written out on this path)
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
L_004b20d8:
    charge(ctx, 6);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    a0 = s0;
    jalr(ctx, 0x4B20E0u, v0.u());
    v0 = 0;
    // 0x004b227c (the shared epilogue, written out on this path)
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
L_004b215c:
    charge(ctx, 6);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    a0 = s0;
    jalr(ctx, 0x4B2164u, v0.u());
    v0 = 0;
    // 0x004b227c (the shared epilogue, written out on this path)
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
L_004b2174:
    charge(ctx, 6);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    a0 = s0;
    jalr(ctx, 0x4B217Cu, v0.u());
    v0 = 0;
    // 0x004b227c (the shared epilogue, written out on this path)
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
}


// sub_4B22B0 [rt2dAnimStreamRead] -- reads an animation: a record from the animation free list (0x95FB4C), filled by sub_4B1D00
// 0x004B22B0 sub_4B22B0 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B22B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b22b0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x30000;
    sd(ra, sp, 0x10);
    a1 = v0 | 0x1B0;
    sq(s0, sp, 0x0);
    v0 = 0x960000;
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    s0 = a0;
    a0 = 0x960000;
    a0 = addiu(a0, -1204);  // &0x95FB4C (Rt2dAnim: the animation free list)
    jalr(ctx, 0x4B22D4u, v0.u());
    a0 = s0;
    a1 = v0;
    jal(ctx, 0x4B22E0u, gen::fn_sub_4B1D00_004b1d00);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4B2300 [rt2dKeyFrameApply] -- applies one keyframe's changes to the props: for each change record (until flag 0x20) the object's matrix (64 bytes, flag 1), colour (flag 2), colour offset (flag 4), visibility / string (flags 8 / 16), each marked changed
// 0x004B2300 sub_4B2300 -- 448 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B2300(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b2300
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s2, a0, 8);
    lw(v0, s2, 0);
    v0 = v0 & 0x20;
    s1 = s2;
    if (v0 == 0) {
        for (;;) {
            // 0x004b2340
            charge(ctx, 8);
            lw(a0, s3, 12);
            link(ctx, 0x4B2344u);  // $ra first: the delay slot below depends on it
            lw(a1, s1, 4);
            call(ctx, gen::fn_sub_4C21B0_004c21b0);
            s0 = v0;
            lw(v0, s1, 0);
            v0 = v0 & 0x1;
            s2 = addiu(s2, 16);
            if (v0 != 0) {
                // 0x004b23b8
                charge(ctx, 9);
                a0 = addiu(s0, 16);
                a1 = s2;
                a2 = 64;
                jal(ctx, 0x4B23C0u, gen::fn_memcpy_00521250);
                v0 = 1;
                s2 = addiu(s2, 64);
                sw(v0, s0, 8);
                sw(v0, s0, 0);
                backedge(ctx);
            }
            // 0x004b2360
            charge(ctx, 4);
            lw(v0, s1, 0);
            v0 = v0 & 0x2;
            if (v0 != 0) {
                // 0x004b23e0
                charge(ctx, 9);
                a0 = addiu(s0, 84);
                a1 = s2;
                a2 = 16;
                jal(ctx, 0x4B23E8u, gen::fn_memcpy_00521250);
                v0 = 1;
                s2 = addiu(s2, 16);
                sw(v0, s0, 80);
                sw(v0, s0, 0);
                backedge(ctx);
            }
            // 0x004b2370
            charge(ctx, 4);
            lw(v0, s1, 0);
            v0 = v0 & 0x4;
            if (v0 != 0) {
                // 0x004b2408
                charge(ctx, 9);
                a0 = addiu(s0, 104);
                a1 = s2;
                a2 = 16;
                jal(ctx, 0x4B2410u, gen::fn_memcpy_00521250);
                v0 = 1;
                s2 = addiu(s2, 16);
                sw(v0, s0, 100);
                sw(v0, s0, 0);
                backedge(ctx);
            }
            // 0x004b2380
            charge(ctx, 4);
            lw(v0, s1, 0);
            v0 = v0 & 0x8;
            if (v0 != 0) {
                // 0x004b2430
                charge(ctx, 9);
                a0 = addiu(s0, 124);
                a1 = s2;
                a2 = 16;
                jal(ctx, 0x4B2438u, gen::fn_memcpy_00521250);
                v0 = 1;
                s2 = addiu(s2, 16);
                sw(v0, s0, 120);
                sw(v0, s0, 0);
                backedge(ctx);
            }
            // 0x004b2390
            charge(ctx, 4);
            lw(v0, s1, 0);
            v0 = v0 & 0x10;
            if (v0 != 0) {
                // 0x004b2458
                charge(ctx, 17);
                a0 = addiu(s0, 144);
                a1 = s2;
                a2 = 16;
                jal(ctx, 0x4B2460u, gen::fn_memcpy_00521250);
                v0 = 1;
                sw(v0, s0, 140);
                sw(v0, s0, 0);
                lw(a1, s0, 144);
                a0 = s3;
                jal(ctx, 0x4B2478u, gen::fn_sub_4B2BA0_004b2ba0);
                sw(v0, s0, 144);
                lw(a1, s0, 148);
                a0 = s3;
                jal(ctx, 0x4B2488u, gen::fn_sub_4B2BA0_004b2ba0);
                sw(v0, s0, 148);
                s2 = addiu(s2, 16);
                backedge(ctx);
            }
            // 0x004b23a0
            charge(ctx, 4);
            lw(v0, s2, 0);
            v0 = v0 & 0x20;
            s1 = s2;
            if (v0 != 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004b23b0
        charge(ctx, 2);
        backedge(ctx);
    }
    // 0x004b2338
    charge(ctx, 2);
    v0 = s4;
    // 0x004b24a0
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_4B2BF0 [rt2dSListAddCopy] -- appends an entry to an sList (sub_4C1F70) and copies $a2 bytes into it when $a1 is given; the entry's index, or -1
// 0x004B2BF0 sub_4B2BF0 -- 128 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B2BF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b2bf0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = a2;
    s0 = a0;
    jal(ctx, 0x4B2C0Cu, gen::fn_sub_4C2120_004c2120);
    a0 = s0;
    a1 = s1;
    s0 = v0;
    v0 = 0x30000;
    a2 = v0 | 0x1A9;
    jal(ctx, 0x4B2C24u, gen::fn_sub_4C1F70_004c1f70);
    if (v0 == 0) {
        // 0x004b2c54
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x004b2c34
        charge(ctx, 2);
        if (s2 != 0) {
            // 0x004b2c3c
            charge(ctx, 4);
            a0 = v0;
            a1 = s2;
            a2 = s1;
            jal(ctx, 0x4B2C44u, gen::fn_memcpy_00521250);
        }
        // 0x004b2c4c
        charge(ctx, 2);
        v0 = s0;
    }
    // 0x004b2c58 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4B2C80 [rt2dAnimPropsStreamRead] -- reads an animation's props: a 16-byte props record (from the free list when $a1 is 0), the label count and each label string into the scene's string sList; the props, or 0
// 0x004B2C80 sub_4B2C80 -- 408 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B2C80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b2c80
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    if (s1 == 0) {
        // 0x004b2d10
        charge(ctx, 9);
        v0 = 0x30000;
        a0 = 0x960000;
        a1 = v0 | 0x1A9;
        v0 = 0x960000;
        lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
        a0 = addiu(a0, -1348);  // &0x95FABC (Rt2dAnim: the props free list)
        jalr(ctx, 0x4B2D24u, v0.u());
        if (v0 == 0) {
            // 0x004b2d5c
            charge(ctx, 2);
            v0 = 0;
            backedge(ctx);
        } else {
            // 0x004b2d34
            charge(ctx, 6);
            sw(zero, v0, 0);
            v1 = si(-1);
            sw(v1, v0, 4);
            sw(zero, v0, 8);
            sw(zero, v0, 12);
            if (v0 == 0) {
                // 0x004b2d64
                charge(ctx, 12);
                sw(zero, v0, 0);
                a0 = 0x960000;
                sw(v1, v0, 4);
                a1 = v0;
                sw(zero, v0, 8);
                v1 = 0x960000;
                sw(zero, v0, 12);
                lw(v0, v1, 396);  // 0x96018C (free-list free slot)
                a0 = addiu(a0, -1348);  // &0x95FABC (Rt2dAnim: the props free list)
                jalr(ctx, 0x4B2D84u, v0.u());
                v0 = 0;
                backedge(ctx);
            }
        }
        // 0x004b2d4c
        charge(ctx, 2);
        s1 = v0;
        if (v0 != 0) {
            backedge(ctx);
            goto L_004b2ca8;
        }
        // 0x004b2d54
        charge(ctx, 2);
        v0 = 0;
        // 0x004b2dfc (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x60);
        return;
    }
L_004b2ca8:
    charge(ctx, 6);
    a0 = s0;
    a1 = addiu(sp, 0x5C);
    a2 = 4;
    jal(ctx, 0x4B2CB0u, gen::fn_sub_4C1910_004c1910);
    if (v0 == 0) {
        // 0x004b2d94
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004b2cc0
        charge(ctx, 3);
        lw(a2, sp, 0x5C);
        if (i64(a2) <= 0) {
            // 0x004b2ccc
            charge(ctx, 2);
            v0 = si(-1);
            sw(v0, s1, 4);
            goto L_004b2cd4;
        }
        // 0x004b2d9c
        charge(ctx, 7);
        lw(a0, s2, 28);
        a1 = 0;
        jal(ctx, 0x4B2DA0u, gen::fn_sub_4B2BF0_004b2bf0);
        s3 = v0;
        v0 = si(-1);
        if (s3 != v0) {
            // 0x004b2dc0
            charge(ctx, 10);
            lw(a0, s2, 28);
            lw(s2, sp, 0x5C);
            a1 = s3;
            jal(ctx, 0x4B2DC8u, gen::fn_j__rwSListGetEntry_004b2c70);
            lw(a2, sp, 0x5C);
            a0 = s0;
            a1 = v0;
            jal(ctx, 0x4B2DD8u, gen::fn_sub_4C5250_004c5250);
            if (s2 != v0) {
                // 0x004b2df0
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004b2de8
                charge(ctx, 2);
                sw(s3, s1, 4);
                backedge(ctx);
            L_004b2cd4:
                charge(ctx, 6);
                a0 = s0;
                a1 = s1;
                a2 = 4;
                jal(ctx, 0x4B2CDCu, gen::fn_sub_4C1910_004c1910);
                if (v0 == 0) {
                    // 0x004b2df8
                    charge(ctx, 1);
                    v0 = 0;
                } else {
                    // 0x004b2cec
                    charge(ctx, 6);
                    a0 = s0;
                    a1 = addiu(s1, 8);
                    a2 = 4;
                    jal(ctx, 0x4B2CF4u, gen::fn_sub_4C1910_004c1910);
                    if (v0 == 0) {
                        // 0x004b2d04
                        charge(ctx, 1);
                        s1 = 0;
                    }
                    // 0x004b2d08
                    charge(ctx, 2);
                    v0 = s1;
                }
            }
        } else {
            // 0x004b2db8
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x004b2dfc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_4B4450 [rt2dMaestroAnimReset] -- resets a maestro animation: its scene object (when the animation names one), each of its keyframe lists rewound and stepped once
// 0x004B4450 sub_4B4450 -- 340 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B4450(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b4450
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    v1 = si(-1);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a1;
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a1, a1, 52);
    s7 = a0;
    if (a1 == v1) {
        // 0x004b448c
        charge(ctx, 3);
        lw(v0, s6, 56);
        if (v0 != v1) {
            goto L_004b454c;
        }
        // 0x004b4498
        charge(ctx, 1);
        lw(s5, s7, 36);
        goto L_004b449c;
    }
L_004b454c:
    charge(ctx, 11);
    a0 = s7;
    jal(ctx, 0x4B454Cu, gen::fn_sub_4B5270_004b5270);
    lw(a1, s6, 56);
    a0 = v0;
    jal(ctx, 0x4B4558u, gen::fn_sub_4AE900_004ae900);
    s5 = v0;
    a1 = 0;
    a0 = s5;
    jal(ctx, 0x4B4568u, gen::fn_sub_4ADFD0_004adfd0);
    backedge(ctx);
L_004b449c:
    charge(ctx, 6);
    a0 = addiu(s6, 4);
    jal(ctx, 0x4B449Cu, gen::fn_sub_4B1A30_004b1a30);
    s1 = v0;
    at = slt(0, s1);
    s4 = 0;
    if (at != 0) {
        for (;;) {
            // 0x004b44b4
            charge(ctx, 6);
            lw(a0, s6, 48);
            a1 = s4;
            jal(ctx, 0x4B44B8u, gen::fn_sub_4B6000_004b6000);
            s0 = v0;
            if (s0 != 0) {
                // 0x004b44cc
                charge(ctx, 9);
                link(ctx, 0x4B44CCu);  // $ra first: the delay slot below depends on it
                lw(a0, s0, 8);
                call(ctx, gen::fn_sub_4C2120_004c2120);
                lw(a0, s0, 8);
                s0 = v0;
                jal(ctx, 0x4B44D8u, gen::fn_sub_4C2090_004c2090);
                at = slt(0, s0);
                s2 = v0;
                s3 = 0;
                if (at != 0) {
                    for (;;) {
                        // 0x004b44f0
                        charge(ctx, 10);
                        lw(a1, s2, 0);
                        a0 = s7;
                        jal(ctx, 0x4B44F4u, gen::fn_sub_4B34D0_004b34d0);
                        a0 = v0;
                        a1 = s5;
                        jal(ctx, 0x4B4500u, gen::fn_sub_4B3610_004b3610);
                        s3 = addiu(s3, 1);
                        v0 = slt(s3, s0);
                        s2 = addiu(s2, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
            // 0x004b4518
            charge(ctx, 4);
            s4 = addiu(s4, 1);
            v0 = slt(s4, s1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004b4528
    charge(ctx, 9);
    a0 = addiu(s6, 4);
    a1 = addiu(s6, 32);
    jal(ctx, 0x4B452Cu, gen::fn_sub_4B1420_004b1420);
    a0 = addiu(s6, 4);
    a1 = addiu(s6, 32);
    a2 = 1;
    jal(ctx, 0x4B453Cu, gen::fn_sub_4B1500_004b1500);
    v0 = s7;
    // 0x004b4578
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


// sub_4B5270 [rt2dMaestroGetSceneObject] -- the maestro's scene object of animation $a1: the parent chain followed recursively through the animations' parent (+52) and child index (+56); the root's +36 for none
// 0x004B5270 sub_4B5270 -- 184 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B5270(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b5270
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (i64(a1) > 0) {
        // 0x004b5298
        charge(ctx, 5);
        link(ctx, 0x4B5298u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 8);
        call(ctx, gen::fn_sub_4C21B0_004c21b0);
        lw(a1, v0, 52);
        s1 = v0;
        if (i64(a1) > 0) {
            // 0x004b52c0
            charge(ctx, 5);
            link(ctx, 0x4B52C0u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 8);
            call(ctx, gen::fn_sub_4C21B0_004c21b0);
            lw(a1, v0, 52);
            s2 = v0;
            if (i64(a1) > 0) {
                // 0x004b52e8
                charge(ctx, 11);
                link(ctx, 0x4B52E8u);  // $ra first: the delay slot below depends on it
                lw(a0, s0, 8);
                call(ctx, gen::fn_sub_4C21B0_004c21b0);
                lw(a1, v0, 52);
                a0 = s0;
                s0 = v0;
                jal(ctx, 0x4B52F8u, gen::fn_sub_4B5270_004b5270);
                lw(a1, s0, 56);
                a0 = v0;
                jal(ctx, 0x4B5304u, gen::fn_sub_4AE900_004ae900);
                a0 = v0;
                backedge(ctx);
            } else {
                // 0x004b52d4
                charge(ctx, 1);
                lw(a0, s0, 36);
            }
            // 0x004b52d8
            charge(ctx, 4);
            link(ctx, 0x4B52D8u);  // $ra first: the delay slot below depends on it
            lw(a1, s2, 56);
            call(ctx, gen::fn_sub_4AE900_004ae900);
            a0 = v0;
            backedge(ctx);
        } else {
            // 0x004b52ac
            charge(ctx, 1);
            lw(a0, s0, 36);
        }
        // 0x004b52b0
        charge(ctx, 4);
        link(ctx, 0x4B52B0u);  // $ra first: the delay slot below depends on it
        lw(a1, s1, 56);
        call(ctx, gen::fn_sub_4AE900_004ae900);
        backedge(ctx);
    } else {
        // 0x004b528c
        charge(ctx, 1);
        lw(v0, s0, 36);
    }
    // 0x004b5290
    charge(ctx, 2);
    ld(ra, sp, 0x30);
    // 0x004b5314
    charge(ctx, 5);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4B5380 [rt2dMaestroUpdate] -- updates every animation of a maestro: per animation its scene object, its time stepped and each crossed keyframe applied; button transitions queued
// 0x004B5380 sub_4B5380 -- 836 bytes; frame 0x110: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B5380(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004b5380
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x110);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, a0, 8);
    s4 = a1;
    jal(ctx, 0x4B53B4u, gen::fn_sub_4C2120_004c2120);
    lw(a0, s5, 8);
    link(ctx, 0x4B53C0u);  // $ra first: the delay slot below depends on it
    sq(v0, sp, 0xD0);
    call(ctx, gen::fn_sub_4C2090_004c2090);
    lw(v1, s5, 68);
    fp = v0;
    sq(v1, sp, 0xC0);
    lq(v1, sp, 0xD0);
    at = slt(0, v1);
    s6 = 0;
    if (at != 0) {
        for (;;) {
            // 0x004b53e4
            charge(ctx, 10);
            a0 = s5;
            a1 = s6;
            link(ctx, 0x4B53ECu);  // $ra first: the delay slot below depends on it
            sw(s6, s5, 68);
            call(ctx, gen::fn_sub_4B5270_004b5270);
            sw(v0, sp, 0xEC);
            a0 = addiu(fp, 0x4);
            jal(ctx, 0x4B53F8u, gen::fn_sub_4B1A80_004b1a80);
            a1 = v0;
            if (i64(a1) >= 0) {
                // 0x004b540c
                charge(ctx, 13);
                link(ctx, 0x4B540Cu);  // $ra first: the delay slot below depends on it
                lw(a0, fp, 0x30);
                call(ctx, gen::fn_sub_4B6000_004b6000);
                lw(a0, v0, 8);
                s0 = v0;
                jal(ctx, 0x4B5418u, gen::fn_sub_4C2120_004c2120);
                lw(a0, s0, 8);
                link(ctx, 0x4B5424u);  // $ra first: the delay slot below depends on it
                sq(v0, sp, 0xB0);
                call(ctx, gen::fn_sub_4C2090_004c2090);
                lq(v1, sp, 0xB0);
                sw(v0, sp, 0xF0);
                at = slt(0, v1);
                sw(zero, sp, 0x100);
                if (at != 0) {
                    for (;;) {
                        // 0x004b5440
                        charge(ctx, 8);
                        lw(v0, sp, 0xF0);
                        lw(a1, v0, 0);
                        a0 = s5;
                        jal(ctx, 0x4B5448u, gen::fn_sub_4B34D0_004b34d0);
                        lw(v1, v0, 8);
                        v1 = v1 & 0x1;
                        s2 = v0;
                        if (v1 != 0) {
                            // 0x004b5460
                            charge(ctx, 15);
                            lw(a1, s2, 4);
                            link(ctx, 0x4B5464u);  // $ra first: the delay slot below depends on it
                            lw(a0, sp, 0xEC);
                            call(ctx, gen::fn_sub_4AE900_004ae900);
                            s7 = v0;
                            a1 = 0;
                            a0 = s7;
                            jal(ctx, 0x4B5474u, gen::fn_sub_4AE900_004ae900);
                            s1 = v0;
                            s0 = 0;
                            a0 = s1;
                            s3 = 0;
                            jal(ctx, 0x4B5488u, gen::fn_sub_4AE8F0_004ae8f0);
                            v1 = slt(0, v0);
                            if (v1 != 0) {
                                for (;;) {
                                    // 0x004b55dc
                                    charge(ctx, 6);
                                    a0 = s1;
                                    a1 = s3;
                                    jal(ctx, 0x4B55E0u, gen::fn_sub_4AE900_004ae900);
                                    s0 = sltu(0, s0);
                                    if (s0 == 0) {
                                        // 0x004b55f4
                                        charge(ctx, 4);
                                        a0 = v0;
                                        a1 = s4;
                                        jal(ctx, 0x4B55F8u, gen::fn_sub_4AE1F0_004ae1f0);
                                        s0 = sltu(0, v0);
                                    }
                                    // 0x004b5604
                                    charge(ctx, 6);
                                    a0 = s1;
                                    s3 = addiu(s3, 1);
                                    jal(ctx, 0x4B5608u, gen::fn_sub_4AE8F0_004ae8f0);
                                    v1 = slt(s3, v0);
                                    if (v1 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004b561c
                                charge(ctx, 2);
                                lw(a0, s2, 12);
                                backedge(ctx);
                            } else {
                                // 0x004b549c
                                charge(ctx, 1);
                                lw(a0, s2, 12);
                            }
                            // 0x004b54a0
                            charge(ctx, 18);
                            a2 = sll(s0, 5);
                            lw(a1, s5, 52);
                            s1 = 1;
                            lw(v1, s2, 8);
                            a0 = a0 & 0x1;
                            a0 = sltu(0, a0);
                            a3 = sll(a1, 6);
                            a0 = sll(a0, 7);
                            a1 = sll(a1, 4);
                            t0 = addu(s5, a0);
                            a0 = v1 & 0x2;
                            v1 = addu(t0, a3);
                            v1 = addu(v1, a2);
                            v1 = addu(v1, a1);
                            s3 = addiu(v1, 88);
                            lw(v1, v1, 88);
                            sq(v1, sp, 0xA0);
                            if (a0 != 0) {
                                // 0x004b5624
                                charge(ctx, 8);
                                a0 = s7;
                                a1 = s1;
                                jal(ctx, 0x4B5628u, gen::fn_sub_4AE900_004ae900);
                                lw(a1, s3, 4);
                                a0 = v0;
                                jal(ctx, 0x4B5634u, gen::fn_sub_4ADFD0_004adfd0);
                                s1 = addiu(s1, 1);
                                backedge(ctx);
                            }
                            // 0x004b54e8
                            charge(ctx, 4);
                            lw(v1, s2, 8);
                            v1 = v1 & 0x4;
                            if (v1 != 0) {
                                // 0x004b5644
                                charge(ctx, 8);
                                a0 = s7;
                                a1 = s1;
                                jal(ctx, 0x4B5648u, gen::fn_sub_4AE900_004ae900);
                                lw(a1, s3, 8);
                                a0 = v0;
                                jal(ctx, 0x4B5654u, gen::fn_sub_4ADFD0_004adfd0);
                                s1 = addiu(s1, 1);
                                backedge(ctx);
                            }
                            // 0x004b54f8
                            charge(ctx, 4);
                            lw(v1, s2, 8);
                            v1 = v1 & 0x8;
                            if (v1 != 0) {
                                // 0x004b5664
                                charge(ctx, 8);
                                a0 = s7;
                                a1 = s1;
                                jal(ctx, 0x4B5668u, gen::fn_sub_4AE900_004ae900);
                                lw(a1, s3, 12);
                                a0 = v0;
                                jal(ctx, 0x4B5674u, gen::fn_sub_4ADFD0_004adfd0);
                                lw(a0, s2, 8);
                                backedge(ctx);
                            } else {
                                // 0x004b5508
                                charge(ctx, 1);
                                lw(a0, s2, 8);
                            }
                            // 0x004b550c
                            charge(ctx, 4);
                            lq(v1, sp, 0xA0);
                            v1 = a0 & v1;
                            if (v1 != 0) {
                                // 0x004b551c
                                charge(ctx, 5);
                                lq(v1, sp, 0xA0);
                                a2 = srl(a0, 4);
                                a1 = sra(v1, 4);
                                a0 = si(-1);
                                if (a1 != 0) {
                                    for (;;) {
                                        // 0x004b5530
                                        charge(ctx, 3);
                                        v1 = a2 & 0x1;
                                        if (v1 != 0) {
                                            // 0x004b553c
                                            charge(ctx, 1);
                                            a0 = addiu(a0, 1);
                                        }
                                        // 0x004b5540
                                        charge(ctx, 4);
                                        a1 = sra(a1, 1);
                                        a2 = sra(a2, 1);
                                        if (a1 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                }
                                // 0x004b5550
                                charge(ctx, 5);
                                v1 = sll(a0, 2);
                                v1 = addu(s2, v1);
                                lw(a1, v1, 16);
                                if (i64(a1) >= 0) {
                                    // 0x004b5564
                                    charge(ctx, 4);
                                    a0 = s5;
                                    jal(ctx, 0x4B5564u, gen::fn_sub_4B39F0_004b39f0);
                                }
                            }
                            // 0x004b5684
                            charge(ctx, 2);
                            if (s0 == 0) {
                                backedge(ctx);
                                // 0x004b5580
                                charge(ctx, 4);
                                lw(a0, s2, 12);
                                v1 = si(-2);
                                v1 = a0 & v1;
                                sw(v1, s2, 12);
                            } else {
                                // 0x004b568c
                                charge(ctx, 2);
                                lw(v1, s2, 12);
                                backedge(ctx);
                                // 0x004b5574
                                charge(ctx, 3);
                                v1 = v1 | 0x1;
                                sw(v1, s2, 12);
                            }
                        }
                        // 0x004b5590
                        charge(ctx, 11);
                        lw(v1, sp, 0xF0);
                        v1 = addiu(v1, 4);
                        sw(v1, sp, 0xF0);
                        lw(v1, sp, 0x100);
                        v1 = addiu(v1, 1);
                        sw(v1, sp, 0x100);
                        a0 = v1;
                        lq(v1, sp, 0xB0);
                        v1 = slt(a0, v1);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
            // 0x004b55bc
            charge(ctx, 5);
            lq(v1, sp, 0xD0);
            s6 = addiu(s6, 1);
            v1 = slt(s6, v1);
            fp = addiu(fp, 0x3C);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004b55d0
    charge(ctx, 3);
    lq(v1, sp, 0xC0);
    sw(v1, s5, 68);
    // 0x004b5694
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
    sp = addiu(sp, 0x110);
}


// sub_4B56D0 [rt2dMaestroUpdateButtons] -- updates a maestro's buttons against the pointer message $a1: each button's state from its hot region and the message, transitions queued
// 0x004B56D0 sub_4B56D0 -- 732 bytes; frame 0x130: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B56D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004b56d0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x130);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 52);
    lw(s7, a1, 8);
    lw(a0, a0, 8);
    link(ctx, 0x4B570Cu);  // $ra first: the delay slot below depends on it
    sw(a1, sp, 0x12C);
    call(ctx, gen::fn_sub_4C2120_004c2120);
    lw(a0, s5, 8);
    link(ctx, 0x4B5718u);  // $ra first: the delay slot below depends on it
    sq(v0, sp, 0xE0);
    call(ctx, gen::fn_sub_4C2090_004c2090);
    s2 = v0;
    lw(v0, s5, 68);
    sq(v0, sp, 0xD0);
    lq(v0, sp, 0xE0);
    at = slt(0, v0);
    s4 = 0;
    if (at != 0) {
        // 0x004b573c
        charge(ctx, 4);
        v0 = sll(s0, 6);
        sq(v0, sp, 0xC0);
        v0 = sll(s7, 4);
        sq(v0, sp, 0xB0);
        for (;;) {
            // 0x004b574c
            charge(ctx, 21);
            a0 = s5;
            a1 = s4;
            link(ctx, 0x4B5754u);  // $ra first: the delay slot below depends on it
            sw(s4, s5, 68);
            call(ctx, gen::fn_sub_4B5270_004b5270);
            sw(v0, sp, 0xFC);
            a0 = addiu(s2, 4);
            jal(ctx, 0x4B5760u, gen::fn_sub_4B1A80_004b1a80);
            lw(a0, s2, 48);
            a1 = v0;
            jal(ctx, 0x4B576Cu, gen::fn_sub_4B6000_004b6000);
            lw(a0, v0, 8);
            s0 = v0;
            jal(ctx, 0x4B5778u, gen::fn_sub_4C2120_004c2120);
            lw(a0, s0, 8);
            link(ctx, 0x4B5784u);  // $ra first: the delay slot below depends on it
            sq(v0, sp, 0xA0);
            call(ctx, gen::fn_sub_4C2090_004c2090);
            sw(v0, sp, 0x100);
            lq(v0, sp, 0xA0);
            at = slt(0, v0);
            sw(zero, sp, 0x110);
            if (at != 0) {
                for (;;) {
                    // 0x004b57a0
                    charge(ctx, 9);
                    lw(v0, sp, 0x100);
                    lw(a1, v0, 0);
                    a0 = s5;
                    jal(ctx, 0x4B57A8u, gen::fn_sub_4B34D0_004b34d0);
                    s1 = v0;
                    lw(v0, v0, 8);
                    v0 = v0 & 0x1;
                    if (v0 != 0) {
                        // 0x004b57c4
                        charge(ctx, 21);
                        lw(a1, s1, 4);
                        link(ctx, 0x4B57C8u);  // $ra first: the delay slot below depends on it
                        lw(a0, sp, 0xFC);
                        call(ctx, gen::fn_sub_4AE900_004ae900);
                        lw(v1, s1, 12);
                        s6 = v0;
                        lw(v0, s1, 8);
                        s3 = 1;
                        v1 = v1 & 0x1;
                        a0 = sltu(0, v1);
                        v1 = v0 & 0x2;
                        v0 = sll(a0, 7);
                        a1 = addu(s5, v0);
                        a0 = sll(a0, 5);
                        lq(v0, sp, 0xC0);
                        v0 = addu(a1, v0);
                        a0 = addu(v0, a0);
                        lq(v0, sp, 0xB0);
                        v0 = addu(a0, v0);
                        lw(s0, v0, 88);
                        fp = addiu(v0, 0x58);
                        if (v1 != 0) {
                            // 0x004b590c
                            charge(ctx, 8);
                            a0 = s6;
                            a1 = s3;
                            jal(ctx, 0x4B5910u, gen::fn_sub_4AE900_004ae900);
                            lw(a1, fp, 0x4);
                            a0 = v0;
                            jal(ctx, 0x4B591Cu, gen::fn_sub_4ADFD0_004adfd0);
                            s3 = addiu(s3, 1);
                            backedge(ctx);
                        }
                        // 0x004b5818
                        charge(ctx, 4);
                        lw(v0, s1, 8);
                        v0 = v0 & 0x4;
                        if (v0 != 0) {
                            // 0x004b592c
                            charge(ctx, 8);
                            a0 = s6;
                            a1 = s3;
                            jal(ctx, 0x4B5930u, gen::fn_sub_4AE900_004ae900);
                            lw(a1, fp, 0x8);
                            a0 = v0;
                            jal(ctx, 0x4B593Cu, gen::fn_sub_4ADFD0_004adfd0);
                            s3 = addiu(s3, 1);
                            backedge(ctx);
                        }
                        // 0x004b5828
                        charge(ctx, 4);
                        lw(v0, s1, 8);
                        v0 = v0 & 0x8;
                        if (v0 != 0) {
                            // 0x004b594c
                            charge(ctx, 8);
                            a0 = s6;
                            a1 = s3;
                            jal(ctx, 0x4B5950u, gen::fn_sub_4AE900_004ae900);
                            lw(a1, fp, 0xC);
                            a0 = v0;
                            jal(ctx, 0x4B595Cu, gen::fn_sub_4ADFD0_004adfd0);
                            lw(v1, s1, 8);
                            backedge(ctx);
                        } else {
                            // 0x004b5838
                            charge(ctx, 1);
                            lw(v1, s1, 8);
                        }
                        // 0x004b583c
                        charge(ctx, 3);
                        v0 = v1 & s0;
                        if (v0 != 0) {
                            // 0x004b5848
                            charge(ctx, 3);
                            a0 = srl(v1, 4);
                            v1 = si(-1);
                            if (s0 != 0) {
                                for (;;) {
                                    // 0x004b5854
                                    charge(ctx, 3);
                                    v0 = a0 & 0x1;
                                    if (v0 != 0) {
                                        // 0x004b5860
                                        charge(ctx, 2);
                                        v1 = addiu(v1, 1);
                                    }
                                    // 0x004b5868
                                    charge(ctx, 4);
                                    s0 = sra(s0, 1);
                                    a0 = sra(a0, 1);
                                    if (s0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                            }
                            // 0x004b5878
                            charge(ctx, 5);
                            v0 = sll(v1, 2);
                            v0 = addu(s1, v0);
                            lw(a1, v0, 16);
                            if (i64(a1) >= 0) {
                                // 0x004b588c
                                charge(ctx, 4);
                                a0 = s5;
                                jal(ctx, 0x4B588Cu, gen::fn_sub_4B39F0_004b39f0);
                            }
                        }
                        // 0x004b596c
                        charge(ctx, 2);
                        if (s7 == 0) {
                            backedge(ctx);
                            // 0x004b58a8
                            charge(ctx, 4);
                            lw(v1, s1, 12);
                            v0 = si(-3);
                            v0 = v1 & v0;
                            sw(v0, s1, 12);
                        } else {
                            // 0x004b5974
                            charge(ctx, 2);
                            lw(v0, s1, 12);
                            backedge(ctx);
                            // 0x004b589c
                            charge(ctx, 3);
                            v0 = v0 | 0x2;
                            sw(v0, s1, 12);
                        }
                    }
                    // 0x004b58b8
                    charge(ctx, 11);
                    lw(v0, sp, 0x100);
                    v0 = addiu(v0, 4);
                    sw(v0, sp, 0x100);
                    lw(v0, sp, 0x110);
                    v0 = addiu(v0, 1);
                    sw(v0, sp, 0x110);
                    v1 = v0;
                    lq(v0, sp, 0xA0);
                    v0 = slt(v1, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004b58e4
            charge(ctx, 5);
            lq(v0, sp, 0xE0);
            s4 = addiu(s4, 1);
            v0 = slt(s4, v0);
            s2 = addiu(s2, 60);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004b58f8
    charge(ctx, 5);
    lq(v0, sp, 0xD0);
    sw(v0, s5, 68);
    lw(v0, sp, 0x12C);
    sw(s7, s5, 52);
    // 0x004b597c
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
    sp = addiu(sp, 0x130);
}


// sub_4B5B50 [rt2dMaestroMessageHandler] -- the maestro's default message handler: play / stop (flag bit 0), goto frame / label (keyframe list moved), buttons, by the message type (a jump table)
// 0x004B5B50 sub_4B5B50 -- 552 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B5B50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4};
    // 0x004b5b50
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, a1, 0);
    at = sltiu(v0, 14);
    s0 = a1;
    if (at != 0) {
        // 0x004b5b78
        charge(ctx, 7);
        v1 = 0x7C0000;
        v0 = sll(v0, 2);
        v1 = addiu(v1, -13424);  // &0x7BCB90
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x4B5B94u:  // table[1]
            // 0x004b5b94
            charge(ctx, 7);
            link(ctx, 0x4B5B94u);  // $ra first: the delay slot below depends on it
            lw(a1, s0, 4);
            call(ctx, gen::fn_sub_4B4A60_004b4a60);
            lw(a0, v0, 0);
            v1 = si(-2);
            v1 = a0 & v1;
            sw(v1, v0, 0);
        L_004b5d1c:
            charge(ctx, 1);
            v0 = s0;
            break;
        case 0x4B5BB0u:  // table[2]
            // 0x004b5bb0
            charge(ctx, 6);
            link(ctx, 0x4B5BB0u);  // $ra first: the delay slot below depends on it
            lw(a1, s0, 4);
            call(ctx, gen::fn_sub_4B4A60_004b4a60);
            lw(v1, v0, 0);
            v1 = v1 | 0x1;
            sw(v1, v0, 0);
            goto L_004b5d1c;
        case 0x4B5BC8u:  // table[3]
            // 0x004b5bc8
            charge(ctx, 11);
            link(ctx, 0x4B5BC8u);  // $ra first: the delay slot below depends on it
            lw(a1, s0, 4);
            call(ctx, gen::fn_sub_4B4A60_004b4a60);
            s1 = v0;
            a0 = addiu(s1, 4);
            jal(ctx, 0x4B5BD4u, gen::fn_sub_4B1B00_004b1b00);
            s2 = v0;
            a0 = addiu(s1, 4);
            jal(ctx, 0x4B5BE0u, gen::fn_sub_4B1A30_004b1a30);
            v0 = slt(s2, v0);
            if (v0 != 0) {
                // 0x004b5d28
                charge(ctx, 8);
                a2 = s2;
                a0 = addiu(s1, 4);
                a1 = addiu(s1, 32);
                jal(ctx, 0x4B5D30u, gen::fn_sub_4B1870_004b1870);
                lw(v0, s1, 0);
                v0 = v0 | 0x2;
                sw(v0, s1, 0);
                backedge(ctx);
            }
            // 0x004b5bf4
            charge(ctx, 2);
            v0 = s0;
            break;
        case 0x4B5BFCu:  // table[4]
            // 0x004b5bfc
            charge(ctx, 8);
            link(ctx, 0x4B5BFCu);  // $ra first: the delay slot below depends on it
            lw(a1, s0, 4);
            call(ctx, gen::fn_sub_4B4A60_004b4a60);
            s1 = v0;
            a0 = addiu(s1, 4);
            jal(ctx, 0x4B5C08u, gen::fn_sub_4B1A80_004b1a80);
            a2 = addiu(v0, -1);
            if (i64(a2) >= 0) {
                // 0x004b5d48
                charge(ctx, 7);
                a0 = addiu(s1, 4);
                a1 = addiu(s1, 32);
                jal(ctx, 0x4B5D4Cu, gen::fn_sub_4B1870_004b1870);
                lw(v0, s1, 0);
                v0 = v0 | 0x2;
                sw(v0, s1, 0);
                backedge(ctx);
            }
            // 0x004b5c1c
            charge(ctx, 2);
            goto L_004b5d1c;
        case 0x4B5C24u:  // table[5]
            // 0x004b5c24
            charge(ctx, 11);
            link(ctx, 0x4B5C24u);  // $ra first: the delay slot below depends on it
            lw(a1, s0, 4);
            call(ctx, gen::fn_sub_4B4A60_004b4a60);
            lw(a2, s0, 8);
            s1 = v0;
            a0 = addiu(s1, 4);
            a1 = addiu(s1, 32);
            jal(ctx, 0x4B5C38u, gen::fn_sub_4B1870_004b1870);
            lw(v0, s1, 0);
            v0 = v0 | 0x2;
            sw(v0, s1, 0);
            goto L_004b5d1c;
        case 0x4B5C50u:  // table[6]
            // 0x004b5c50
            charge(ctx, 14);
            link(ctx, 0x4B5C50u);  // $ra first: the delay slot below depends on it
            lw(a1, s0, 4);
            call(ctx, gen::fn_sub_4B4A60_004b4a60);
            lw(a1, s0, 8);
            a0 = s1;
            s1 = v0;
            jal(ctx, 0x4B5C60u, gen::fn_sub_4B3030_004b3030);
            lw(a2, v0, 8);
            a0 = addiu(s1, 4);
            a1 = addiu(s1, 32);
            jal(ctx, 0x4B5C70u, gen::fn_sub_4B1870_004b1870);
            lw(v0, s1, 0);
            v0 = v0 | 0x2;
            sw(v0, s1, 0);
            goto L_004b5d1c;
        case 0x4B5C88u:  // table[7]
            // 0x004b5c88
            charge(ctx, 2);
            goto L_004b5d1c;
        case 0x4B5C90u:  // table[8]
            // 0x004b5c90
            charge(ctx, 4);
            link(ctx, 0x4B5C90u);  // $ra first: the delay slot below depends on it
            lw(a1, s0, 8);
            call(ctx, gen::fn_sub_4B39F0_004b39f0);
            goto L_004b5d1c;
        case 0x4B5CA0u:  // table[9]
            // 0x004b5ca0
            charge(ctx, 2);
            goto L_004b5d1c;
        case 0x4B5CA8u:  // table[10]
            // 0x004b5ca8
            charge(ctx, 20);
            lwc1(f4, s0, 8);
            v0 = 0x3F800000;
            mtc1(v0, f1);
            a1 = addiu(s1, 44);
            mtc1(zero, f0);
            lwc1(f3, s1, 60);
            adda_s(f0, f1);
            lwc1(f2, s1, 64);
            cvt_s_w(f0, f4);
            mul_s(f0, f0, f3);
            mul_s(f0, f2, f0);
            swc1(f0, s1, 44);
            lwc1(f1, s0, 12);
            lwc1(f0, s1, 56);
            cvt_s_w(f1, f1);
            msub_s(f0, f1, f0);
            link(ctx, 0x4B5CE8u);  // $ra first: the delay slot below depends on it
            swc1(f0, s1, 48);
            call(ctx, gen::fn_sub_4B5380_004b5380);
            goto L_004b5d1c;
        case 0x4B5CF8u:  // table[11]
            // 0x004b5cf8
            charge(ctx, 4);
            jal(ctx, 0x4B5CF8u, gen::fn_sub_4B56D0_004b56d0);
            s0 = v0;
            goto L_004b5d1c;
        case 0x4B5D08u:  // table[13]
            // 0x004b5d08
            charge(ctx, 4);
            jal(ctx, 0x4B5D08u, gen::fn_sub_4B59B0_004b59b0);
            s0 = v0;
            goto L_004b5d1c;
        case 0x4B5D18u:  // table[0, 12]
        L_004b5d18:
            charge(ctx, 1);
            s0 = 0;
            goto L_004b5d1c;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        goto L_004b5d20;
    }
    goto L_004b5d18;
L_004b5d20:
    charge(ctx, 2);
    ld(ra, sp, 0x30);
    // 0x004b5d64
    charge(ctx, 5);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4B9840 [bmpPaletteSize] -- the palette size of a BMP of $a0 bits per pixel: 4 x 2^bpp below 9, else 0
// 0x004B9840 sub_4B9840 -- 40 bytes; leaf frame (no stack)
void sub_4B9840(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4};
    // 0x004b9840
    enter(ctx, 3);  // entry check point + this block's cycles
    at = sltiu(a0, 9);
    if (at == 0) {
        // 0x004b985c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004b984c
        charge(ctx, 4);
        v0 = 1;
        v0 = sllv(v0, a0);
        v0 = sll(v0, 2);
    }
    // 0x004b9860 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_4B9870 [bmpWriteFileHeader] -- writes a BMP file header: 'BM', the file size (54 + palette + rows padded to 32 bits), two reserved words, the bits' offset
// 0x004B9870 sub_4B9870 -- 292 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B9870(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b9870
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 66;
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    a1 = addiu(sp, 0x4F);
    sb(v0, sp, 0x4F);
    a2 = 1;
    jal(ctx, 0x4B989Cu, gen::fn_sub_4C53F0_004c53f0);
    v0 = 77;
    a0 = s2;
    sb(v0, sp, 0x4E);
    a1 = addiu(sp, 0x4E);
    a2 = 1;
    jal(ctx, 0x4B98B4u, gen::fn_sub_4C53F0_004c53f0);
    lw(v0, s0, 4);
    mult(a0, v0, s1);
    v1 = si(-32);
    lw(v0, s0, 8);
    a0 = addiu(a0, 31);
    v1 = a0 & v1;
    v1 = srl(v1, 3);
    mult(v1, v0, v1);
    at = sltiu(s1, 9);
    if (at == 0) {
        // 0x004b98f8
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004b98e8
        charge(ctx, 4);
        v0 = 1;
        v0 = sllv(v0, s1);
        v0 = sll(v0, 2);
    }
    // 0x004b98fc
    charge(ctx, 20);
    v0 = addiu(v0, 54);
    a0 = s2;
    v0 = addu(v0, v1);
    a1 = addiu(sp, 0x44);
    sw(v0, sp, 0x44);
    a2 = 4;
    jal(ctx, 0x4B9910u, gen::fn_sub_4C17F0_004c17f0);
    a0 = s2;
    a1 = addiu(sp, 0x4C);
    a2 = 2;
    link(ctx, 0x4B9924u);  // $ra first: the delay slot below depends on it
    sh(zero, sp, 0x4C);
    call(ctx, gen::fn_sub_4C1820_004c1820);
    a0 = s2;
    a1 = addiu(sp, 0x4A);
    a2 = 2;
    link(ctx, 0x4B9938u);  // $ra first: the delay slot below depends on it
    sh(zero, sp, 0x4A);
    call(ctx, gen::fn_sub_4C1820_004c1820);
    at = sltiu(s1, 9);
    if (at == 0) {
        // 0x004b995c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004b994c
        charge(ctx, 4);
        v0 = 1;
        v0 = sllv(v0, s1);
        v0 = sll(v0, 2);
    }
    // 0x004b9960
    charge(ctx, 13);
    v0 = addiu(v0, 54);
    a0 = s2;
    sw(v0, sp, 0x40);
    a1 = addiu(sp, 0x40);
    a2 = 4;
    jal(ctx, 0x4B9970u, gen::fn_sub_4C17F0_004c17f0);
    ld(ra, sp, 0x30);
    v0 = 14;
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_4B99A0 [bmpWriteInfoHeader] -- writes a BMP info header (40 bytes: width, height, 1 plane, the bit count, no compression) and the image's palette
// 0x004B99A0 sub_4B99A0 -- 500 bytes; frame 0xD0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq), s4 sp+0xC8
void sub_4B99A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b99a0
    enter(ctx, 64);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = 40;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    a1 = addiu(sp, 0xC8);
    a2 = 4;
    link(ctx, 0x4B99E0u);  // $ra first: the delay slot below depends on it
    sw(s4, sp, 0xC8);
    call(ctx, gen::fn_sub_4C17F0_004c17f0);
    lw(v0, s0, 4);
    a0 = s5;
    a1 = addiu(sp, 0xC4);
    a2 = 4;
    link(ctx, 0x4B99F8u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0xC4);
    call(ctx, gen::fn_sub_4C17F0_004c17f0);
    lw(v0, s0, 8);
    a0 = s5;
    a1 = addiu(sp, 0xC0);
    a2 = 4;
    link(ctx, 0x4B9A10u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0xC0);
    call(ctx, gen::fn_sub_4C17F0_004c17f0);
    v0 = 1;
    a0 = s5;
    sh(v0, sp, 0xCE);
    a1 = addiu(sp, 0xCE);
    a2 = 2;
    jal(ctx, 0x4B9A28u, gen::fn_sub_4C1820_004c1820);
    a0 = s5;
    a1 = addiu(sp, 0xCC);
    a2 = 2;
    link(ctx, 0x4B9A3Cu);  // $ra first: the delay slot below depends on it
    sh(s1, sp, 0xCC);
    call(ctx, gen::fn_sub_4C1820_004c1820);
    a0 = s5;
    a1 = addiu(sp, 0xBC);
    a2 = 4;
    link(ctx, 0x4B9A50u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0xBC);
    call(ctx, gen::fn_sub_4C17F0_004c17f0);
    a0 = s5;
    a1 = addiu(sp, 0xB8);
    a2 = 4;
    link(ctx, 0x4B9A64u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0xB8);
    call(ctx, gen::fn_sub_4C17F0_004c17f0);
    a0 = s5;
    a1 = addiu(sp, 0xB4);
    a2 = 4;
    link(ctx, 0x4B9A78u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0xB4);
    call(ctx, gen::fn_sub_4C17F0_004c17f0);
    a0 = s5;
    a1 = addiu(sp, 0xB0);
    a2 = 4;
    link(ctx, 0x4B9A8Cu);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0xB0);
    call(ctx, gen::fn_sub_4C17F0_004c17f0);
    at = sltiu(s1, 9);
    if (at == 0) {
        // 0x004b9b38
        charge(ctx, 12);
        a0 = s5;
        a1 = addiu(sp, 0xA0);
        a2 = 4;
        link(ctx, 0x4B9B44u);  // $ra first: the delay slot below depends on it
        sw(zero, sp, 0xA0);
        call(ctx, gen::fn_sub_4C17F0_004c17f0);
        a0 = s5;
        a1 = addiu(sp, 0x9C);
        a2 = 4;
        link(ctx, 0x4B9B58u);  // $ra first: the delay slot below depends on it
        sw(zero, sp, 0x9C);
        call(ctx, gen::fn_sub_4C17F0_004c17f0);
        backedge(ctx);
    } else {
        // 0x004b9aa0
        charge(ctx, 16);
        lw(s2, s0, 24);
        v0 = 1;
        s1 = sllv(v0, s1);
        a0 = s5;
        a1 = addiu(sp, 0xA8);
        a2 = 4;
        link(ctx, 0x4B9AB8u);  // $ra first: the delay slot below depends on it
        sw(s1, sp, 0xA8);
        call(ctx, gen::fn_sub_4C17F0_004c17f0);
        a0 = s5;
        a1 = addiu(sp, 0xA4);
        a2 = 4;
        link(ctx, 0x4B9ACCu);  // $ra first: the delay slot below depends on it
        sw(s1, sp, 0xA4);
        call(ctx, gen::fn_sub_4C17F0_004c17f0);
        at = slt(0, s1);
        s3 = 0;
        if (at != 0) {
            // 0x004b9ae0
            charge(ctx, 3);
            s0 = addiu(sp, 0xAD);
            s6 = addiu(sp, 0xAE);
            s7 = addiu(sp, 0xAF);
            for (;;) {
                // 0x004b9aec
                charge(ctx, 17);
                lbu(v1, s2, 2);
                v0 = 255;
                a0 = s5;
                a1 = addiu(sp, 0xAC);
                a2 = 4;
                sb(v1, sp, 0xAC);
                lbu(v1, s2, 1);
                sb(v1, s0, 0);
                lbu(v1, s2, 0);
                sb(v1, s6, 0);
                link(ctx, 0x4B9B14u);  // $ra first: the delay slot below depends on it
                sb(v0, s7, 0);
                call(ctx, gen::fn_sub_4C53F0_004c53f0);
                s3 = addiu(s3, 1);
                s4 = addiu(s4, 4);
                v0 = slt(s3, s1);
                s2 = addiu(s2, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x004b9b30
    charge(ctx, 2);
    v0 = s4;
    // 0x004b9b68
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
}


// sub_4B9BA0 [bmpWriteRow] -- writes one image row bottom-up into a BMP row: 4-bit pixels packed in pairs, 8-bit copied, 32-bit as BGR, padded to 32 bits; the bytes written
// 0x004B9BA0 sub_4B9BA0 -- 412 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B9BA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b9ba0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 4;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = t0;
    s0 = 0;
    if (a3 == v0) {
        // 0x004b9c38
        charge(ctx, 8);
        lw(v0, s2, 16);
        mult(v1, a2, v0);
        lw(a0, s2, 4);
        a3 = 0;
        lw(v0, s2, 20);
        at = slt(0, a0);
        a1 = addu(v0, v1);
        if (at != 0) {
            // 0x004b9c58
            charge(ctx, 1);
            a2 = 0;
            for (;;) {
                // 0x004b9c5c
                charge(ctx, 12);
                v1 = addu(a1, a3);
                v0 = addu(s1, a2);
                lbu(a0, v1, 0);
                a3 = addiu(a3, 2);
                lbu(v1, v1, 1);
                a0 = sll(a0, 4);
                v1 = a0 | v1;
                sb(v1, v0, 0);
                lw(a0, s2, 4);
                v0 = slt(a3, a0);
                a2 = addiu(a2, 1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004b9c8c
            charge(ctx, 1);
        }
        // 0x004b9c90
        charge(ctx, 2);
        v0 = sra(a0, 1);
        s0 = addu(s0, v0);
    } else {
        // 0x004b9bd0
        charge(ctx, 3);
        v0 = 8;
        if (a3 == v0) {
            // 0x004b9cbc
            charge(ctx, 10);
            lw(v0, s2, 16);
            mult(v1, a2, v0);
            a0 = s1;
            lw(v0, s2, 20);
            lw(a2, s2, 4);
            a1 = addu(v0, v1);
            jal(ctx, 0x4B9CD0u, gen::fn_memcpy_00521250);
            lw(v0, s2, 4);
            s0 = addu(s0, v0);
            backedge(ctx);
        } else {
            // 0x004b9bdc
            charge(ctx, 8);
            lw(v0, s2, 16);
            mult(v1, a2, v0);
            lw(a1, s2, 4);
            a0 = 0;
            lw(v0, s2, 20);
            at = slt(0, a1);
            a2 = addu(v0, v1);
            if (at == 0) {
                // 0x004b9ce4
                charge(ctx, 1);
                v0 = sll(a1, 1);
            } else {
                // 0x004b9bfc
                charge(ctx, 1);
                v1 = s1;
                for (;;) {
                    // 0x004b9c00
                    charge(ctx, 12);
                    lbu(v0, a2, 0);
                    a0 = addiu(a0, 1);
                    sb(v0, v1, 2);
                    lbu(v0, a2, 1);
                    sb(v0, v1, 1);
                    lbu(v0, a2, 2);
                    sb(v0, v1, 0);
                    a2 = addiu(a2, 4);
                    lw(a1, s2, 4);
                    v0 = slt(a0, a1);
                    v1 = addiu(v1, 3);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004b9c30
                charge(ctx, 2);
                v0 = sll(a1, 1);
            }
            // 0x004b9ce8
            charge(ctx, 3);
            v0 = addu(v0, a1);
            s0 = addu(s0, v0);
            backedge(ctx);
        }
    }
    // 0x004b9c98
    charge(ctx, 7);
    a1 = s1;
    a0 = s3;
    a2 = s0;
    jal(ctx, 0x4B9CA0u, gen::fn_sub_4C53F0_004c53f0);
    v0 = s0 & 0x3;
    if (v0 != 0) {
        for (;;) {
            // 0x004b9cf4
            charge(ctx, 9);
            a0 = s3;
            a1 = addiu(sp, 0x5F);
            a2 = 1;
            link(ctx, 0x4B9D00u);  // $ra first: the delay slot below depends on it
            sb(zero, sp, 0x5F);
            call(ctx, gen::fn_sub_4C53F0_004c53f0);
            s0 = addiu(s0, 1);
            v0 = s0 & 0x3;
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004b9d18
        charge(ctx, 2);
        backedge(ctx);
    }
    // 0x004b9cb4
    charge(ctx, 2);
    v0 = s0;
    // 0x004b9d20
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_4B9D40 [bmpWritePixels] -- writes an image's rows to a BMP from the last to the first (sub_4B9BA0) through a row buffer; the total bytes
// 0x004B9D40 sub_4B9D40 -- 192 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B9D40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b9d40
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v0 = 0x960000;
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = a2;
    lw(a0, a2, 4);
    a1 = 0x10000;
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    s0 = 0;
    v1 = sll(a0, 1);
    a0 = addu(v1, a0);
    jalr(ctx, 0x4B9D84u, v0.u());
    s4 = v0;
    lw(v0, s1, 8);
    s5 = addiu(v0, -1);
    if (i64(s5) >= 0) {
        for (;;) {
            // 0x004b9da0
            charge(ctx, 9);
            a0 = s3;
            a1 = s1;
            a2 = s5;
            a3 = s2;
            t0 = s4;
            jal(ctx, 0x4B9DB0u, gen::fn_sub_4B9BA0_004b9ba0);
            s5 = addiu(s5, -1);
            s0 = addu(s0, v0);
            if (i64(s5) < 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004b9dc4
        charge(ctx, 1);
    }
    // 0x004b9dc8
    charge(ctx, 14);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    a0 = s4;
    jalr(ctx, 0x4B9DD0u, v0.u());
    v0 = s0;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}


// sub_4B9E00 [bmpReadRow] -- converts one BMP row into an image row by (image depth, BMP bit count): 32-bit RGBA from 24 / 32-bit BGR(A), palette indices from 1 / 4 / 8-bit; unknown pairs error
// 0x004B9E00 sub_4B9E00 -- 1172 bytes; frame 0x20: ra sp+0x0
void sub_4B9E00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b9e00
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    lw(t4, a0, 4);
    lw(t1, a0, 16);
    lw(v0, a0, 24);
    v1 = t4;
    mult(t3, t1, a1);
    lw(t2, a0, 20);
    t1 = sll(a3, 8);
    a1 = 8224;
    lw(a3, a0, 12);
    a3 = t1 | a3;
    a0 = addu(t2, t3);
    if (a3 != a1) {
        // 0x004b9e38
        charge(ctx, 3);
        a1 = 6176;
        if (a3 == a1) {
            // 0x004ba14c
            charge(ctx, 2);
            if (t0 == 0) {
                // 0x004ba198
                charge(ctx, 2);
                v1 = addiu(t4, -1);
                if (t4 != 0) {
                    // 0x004ba1a0
                    charge(ctx, 1);
                    a1 = 255;
                    for (;;) {
                        // 0x004ba1a4
                        charge(ctx, 12);
                        lbu(a3, a2, 0);
                        v0 = v1;
                        v1 = addiu(v1, -1);
                        sb(a3, a0, 2);
                        lbu(a3, a2, 1);
                        sb(a3, a0, 1);
                        lbu(a3, a2, 2);
                        sb(a3, a0, 0);
                        a2 = addiu(a2, 3);
                        sb(a1, a0, 3);
                        a0 = addiu(a0, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004ba1d4
                    charge(ctx, 2);
                }
            } else {
                // 0x004ba154
                charge(ctx, 2);
                v1 = addiu(t4, -1);
                if (t4 != 0) {
                    // 0x004ba15c
                    charge(ctx, 1);
                    a1 = 255;
                    for (;;) {
                        // 0x004ba160
                        charge(ctx, 12);
                        lbu(a3, a2, 0);
                        v0 = v1;
                        v1 = addiu(v1, -1);
                        sb(a3, a0, 0);
                        lbu(a3, a2, 1);
                        sb(a3, a0, 1);
                        lbu(a3, a2, 2);
                        sb(a3, a0, 2);
                        a2 = addiu(a2, 3);
                        sb(a1, a0, 3);
                        a0 = addiu(a0, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004ba190
                    charge(ctx, 2);
                }
            }
            goto L_004ba218;
        }
        // 0x004b9e44
        charge(ctx, 3);
        a1 = 4128;
        if (a3 == a1) {
            // 0x004ba0f8
            charge(ctx, 2);
            v1 = addiu(t4, -1);
            if (t4 != 0) {
                // 0x004ba100
                charge(ctx, 1);
                a1 = 255;
                for (;;) {
                    // 0x004ba104
                    charge(ctx, 16);
                    lhu(t2, a2, 0);
                    v0 = v1;
                    v1 = addiu(v1, -1);
                    t0 = sra(t2, 8);
                    a3 = sra(t2, 3);
                    t1 = t0 & 0xF8;
                    a2 = addiu(a2, 2);
                    t0 = a3 & 0xFC;
                    sb(t1, a0, 0);
                    a3 = sll(t2, 3);
                    sb(t0, a0, 1);
                    a3 = a3 & 0xF8;
                    sb(a3, a0, 2);
                    sb(a1, a0, 3);
                    a0 = addiu(a0, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004ba144
                charge(ctx, 2);
            }
            goto L_004ba218;
        }
        // 0x004b9e50
        charge(ctx, 3);
        a1 = 3872;
        if (a3 == a1) {
            // 0x004ba0a4
            charge(ctx, 2);
            v1 = addiu(t4, -1);
            if (t4 != 0) {
                // 0x004ba0ac
                charge(ctx, 1);
                a1 = 255;
                for (;;) {
                    // 0x004ba0b0
                    charge(ctx, 16);
                    lhu(t2, a2, 0);
                    v0 = v1;
                    v1 = addiu(v1, -1);
                    t0 = sra(t2, 7);
                    a3 = sra(t2, 2);
                    t1 = t0 & 0xF8;
                    a2 = addiu(a2, 2);
                    t0 = a3 & 0xF8;
                    sb(t1, a0, 0);
                    a3 = sll(t2, 3);
                    sb(t0, a0, 1);
                    a3 = a3 & 0xF8;
                    sb(a3, a0, 2);
                    sb(a1, a0, 3);
                    a0 = addiu(a0, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004ba0f0
                charge(ctx, 2);
            }
            goto L_004ba218;
        }
        // 0x004b9e5c
        charge(ctx, 3);
        a1 = 2080;
        if (a3 == a1) {
            // 0x004ba054
            charge(ctx, 2);
            v1 = addiu(t4, -1);
            if (t4 != 0) {
                for (;;) {
                    // 0x004ba05c
                    charge(ctx, 16);
                    lbu(a3, a2, 0);
                    a1 = v1;
                    v1 = addiu(v1, -1);
                    a3 = sll(a3, 2);
                    a2 = addiu(a2, 1);
                    a3 = addu(v0, a3);
                    lbu(t2, a3, 0);
                    lbu(t1, a3, 1);
                    lbu(t0, a3, 2);
                    lbu(a3, a3, 3);
                    sb(t2, a0, 0);
                    sb(t1, a0, 1);
                    sb(t0, a0, 2);
                    sb(a3, a0, 3);
                    a0 = addiu(a0, 4);
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004ba09c
                charge(ctx, 2);
            }
            goto L_004ba218;
        }
        // 0x004b9e68
        charge(ctx, 3);
        a1 = 1056;
        if (a3 == a1) {
            // 0x004b9fe4
            charge(ctx, 5);
            lbu(t3, a2, 0);
            t5 = 4;
            v1 = addiu(t4, -1);
            a2 = addiu(a2, 1);
            if (t4 != 0) {
                // 0x004b9ff8
                charge(ctx, 1);
                a1 = t5;
                for (;;) {
                    // 0x004b9ffc
                    charge(ctx, 16);
                    a3 = t3 & 0xFF;
                    a3 = srav(a3, t5);
                    a3 = a3 & 0xF;
                    t5 = addiu(t5, -4);
                    a3 = sll(a3, 2);
                    a3 = addu(v0, a3);
                    lbu(t2, a3, 0);
                    lbu(t1, a3, 1);
                    lbu(t0, a3, 2);
                    lbu(a3, a3, 3);
                    sb(t2, a0, 0);
                    sb(t1, a0, 1);
                    sb(t0, a0, 2);
                    sb(a3, a0, 3);
                    a0 = addiu(a0, 4);
                    if (i64(t5) < 0) {
                        // 0x004ba278
                        charge(ctx, 4);
                        lbu(t3, a2, 0);
                        t5 = a1;
                        a2 = addiu(a2, 1);
                        backedge(ctx);
                    } else {
                        // 0x004ba03c
                        charge(ctx, 1);
                    }
                    // 0x004ba040
                    charge(ctx, 3);
                    a3 = v1;
                    v1 = addiu(v1, -1);
                    if (a3 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004ba04c
                charge(ctx, 2);
            }
            goto L_004ba218;
        }
        // 0x004b9e74
        charge(ctx, 3);
        a1 = 288;
        if (a3 == a1) {
            // 0x004b9f78
            charge(ctx, 5);
            lbu(t3, a2, 0);
            t5 = 7;
            v1 = addiu(t4, -1);
            a2 = addiu(a2, 1);
            if (t4 != 0) {
                // 0x004b9f8c
                charge(ctx, 1);
                a1 = t5;
                for (;;) {
                    // 0x004b9f90
                    charge(ctx, 16);
                    a3 = t3 & 0xFF;
                    a3 = srav(a3, t5);
                    a3 = a3 & 0x1;
                    t5 = addiu(t5, -1);
                    a3 = sll(a3, 2);
                    a3 = addu(v0, a3);
                    lbu(t2, a3, 0);
                    lbu(t1, a3, 1);
                    lbu(t0, a3, 2);
                    lbu(a3, a3, 3);
                    sb(t2, a0, 0);
                    sb(t1, a0, 1);
                    sb(t0, a0, 2);
                    sb(a3, a0, 3);
                    a0 = addiu(a0, 4);
                    if (i64(t5) < 0) {
                        // 0x004ba268
                        charge(ctx, 4);
                        lbu(t3, a2, 0);
                        t5 = a1;
                        a2 = addiu(a2, 1);
                        backedge(ctx);
                    }
                    // 0x004b9fd0
                    charge(ctx, 3);
                    a3 = v1;
                    v1 = addiu(v1, -1);
                    if (a3 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004b9fdc
                charge(ctx, 2);
            }
            goto L_004ba218;
        }
        // 0x004b9e80
        charge(ctx, 3);
        v0 = 2056;
        if (a3 == v0) {
            // 0x004b9f64
            charge(ctx, 5);
            a1 = a2;
            a2 = t4;
            jal(ctx, 0x4B9F68u, gen::fn_memcpy_00521250);
            goto L_004ba218;
        }
        // 0x004b9e8c
        charge(ctx, 3);
        v0 = 1032;
        if (a3 != v0) {
            // 0x004b9e98
            charge(ctx, 3);
            v0 = 1028;
            if (a3 == v0) {
                goto L_004b9f14;
            }
            // 0x004b9ea4
            charge(ctx, 3);
            v0 = 264;
            if (a3 != v0) {
                // 0x004b9eb0
                charge(ctx, 3);
                v0 = 260;
                if (a3 == v0) {
                    goto L_004b9ec4;
                }
                // 0x004b9ebc
                charge(ctx, 2);
                v1 = 413;
                // 0x004ba220
                charge(ctx, 9);
                v0 = lui(0x8000);
                sw(v1, sp, 0x18);
                a0 = v0 | 0x8;
                jal(ctx, 0x4BA228u, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x1C);
                a0 = addiu(sp, 0x18);
                jal(ctx, 0x4BA234u, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
                // 0x004ba288 (the shared epilogue, written out on this path)
                charge(ctx, 3);
                ld(ra, sp, 0x0);
                sp = addiu(sp, 0x20);
                return;
            }
        L_004b9ec4:
            charge(ctx, 6);
            lbu(t0, a2, 0);
            v0 = v1;
            a3 = 7;
            v1 = addiu(v1, -1);
            a2 = addiu(a2, 1);
            if (v0 != 0) {
                // 0x004b9edc
                charge(ctx, 1);
                v0 = a3;
                for (;;) {
                    // 0x004b9ee0
                    charge(ctx, 7);
                    a1 = t0 & 0xFF;
                    a1 = srav(a1, a3);
                    a1 = a1 & 0x1;
                    a3 = addiu(a3, -1);
                    sb(a1, a0, 0);
                    a0 = addiu(a0, 1);
                    if (i64(a3) < 0) {
                        // 0x004ba244
                        charge(ctx, 4);
                        lbu(t0, a2, 0);
                        a3 = v0;
                        a2 = addiu(a2, 1);
                        backedge(ctx);
                    } else {
                        // 0x004b9efc
                        charge(ctx, 1);
                    }
                    // 0x004b9f00
                    charge(ctx, 3);
                    a1 = v1;
                    v1 = addiu(v1, -1);
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004b9f0c
                charge(ctx, 2);
            }
            goto L_004ba218;
        }
    L_004b9f14:
        charge(ctx, 6);
        lbu(a3, a2, 0);
        v0 = v1;
        t0 = 4;
        v1 = addiu(v1, -1);
        a2 = addiu(a2, 1);
        if (v0 != 0) {
            // 0x004b9f2c
            charge(ctx, 1);
            v0 = t0;
            for (;;) {
                // 0x004b9f30
                charge(ctx, 7);
                a1 = a3 & 0xFF;
                a1 = srav(a1, t0);
                a1 = a1 & 0xF;
                t0 = addiu(t0, -4);
                sb(a1, a0, 0);
                a0 = addiu(a0, 1);
                if (i64(t0) < 0) {
                    // 0x004ba258
                    charge(ctx, 4);
                    lbu(a3, a2, 0);
                    t0 = v0;
                    a2 = addiu(a2, 1);
                    backedge(ctx);
                } else {
                    // 0x004b9f4c
                    charge(ctx, 1);
                }
                // 0x004b9f50
                charge(ctx, 3);
                a1 = v1;
                v1 = addiu(v1, -1);
                if (a1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004b9f5c
            charge(ctx, 2);
        }
        goto L_004ba218;
    }
    // 0x004ba1dc
    charge(ctx, 2);
    v1 = addiu(t4, -1);
    if (t4 != 0) {
        // 0x004ba1e4
        charge(ctx, 1);
        a1 = 255;
        for (;;) {
            // 0x004ba1e8
            charge(ctx, 12);
            lbu(a3, a2, 0);
            v0 = v1;
            v1 = addiu(v1, -1);
            sb(a3, a0, 0);
            lbu(a3, a2, 1);
            sb(a3, a0, 1);
            lbu(a3, a2, 2);
            sb(a3, a0, 2);
            a2 = addiu(a2, 4);
            sb(a1, a0, 3);
            a0 = addiu(a0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
L_004ba218:
    charge(ctx, 2);
    v0 = 1;
    // 0x004ba288 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4BA2A0 [bmpImageRead] -- reads a BMP file into a new image: the file stream opened, the 'BM' header and info header checked, the palette, the rows (sub_4B9E00) bottom-up; the image, or 0
// 0x004BA2A0 sub_4BA2A0 -- 2732 bytes; frame 0x510: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4BA2A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004ba2a0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x510);
    a2 = a0;
    sd(ra, sp, 0x90);
    a0 = 2;
    sq(fp, sp, 0x80);
    a1 = 1;
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    link(ctx, 0x4BA2D4u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C58A0_004c58a0);
    s5 = v0;
    if (s5 == 0) {
        // 0x004bad18
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004ba2e8
        charge(ctx, 7);
        a0 = s5;
        a1 = addiu(sp, 0x50C);
        a2 = 4;
        jal(ctx, 0x4BA2F0u, gen::fn_sub_4C5250_004c5250);
        v1 = 4;
        if (v0 != v1) {
            // 0x004ba680
            charge(ctx, 5);
            a0 = s5;
            a1 = 0;
            jal(ctx, 0x4BA684u, gen::fn_sub_4C5780_004c5780);
            v0 = 0;
        } else {
            // 0x004ba304
            charge(ctx, 4);
            lhu(v1, sp, 0x50C);
            v0 = 19778;
            if (v1 != v0) {
                // 0x004ba694
                charge(ctx, 5);
                a0 = s5;
                a1 = 0;
                jal(ctx, 0x4BA698u, gen::fn_sub_4C5780_004c5780);
                v0 = 0;
            } else {
                // 0x004ba314
                charge(ctx, 7);
                a0 = s5;
                a1 = addiu(sp, 0xE2);
                a2 = 14;
                jal(ctx, 0x4BA31Cu, gen::fn_sub_4C5250_004c5250);
                v1 = 14;
                if (v0 != v1) {
                    // 0x004ba6a8
                    charge(ctx, 5);
                    a0 = s5;
                    a1 = 0;
                    jal(ctx, 0x4BA6ACu, gen::fn_sub_4C5780_004c5780);
                    v0 = 0;
                } else {
                    // 0x004ba330
                    charge(ctx, 11);
                    s0 = addiu(sp, 0xEC);
                    lw(s4, sp, 0xE8);
                    lw(s7, s0, 0);
                    a0 = s5;
                    a1 = addiu(sp, 0xE0);
                    s2 = 18;
                    s1 = addiu(s7, -4);
                    a2 = s1;
                    jal(ctx, 0x4BA34Cu, gen::fn_sub_4C5250_004c5250);
                    if (s1 != v0) {
                        // 0x004ba6bc
                        charge(ctx, 5);
                        a0 = s5;
                        a1 = 0;
                        jal(ctx, 0x4BA6C0u, gen::fn_sub_4C5780_004c5780);
                        v0 = 0;
                    } else {
                        // 0x004ba35c
                        charge(ctx, 3);
                        v0 = 12;
                        s3 = addu(s2, s1);
                        if (s7 == v0) {
                            // 0x004ba368
                            charge(ctx, 8);
                            lh(v0, sp, 0xE0);
                            s0 = 0;
                            lh(s2, sp, 0xE2);
                            sw(zero, sp, 0xD0);
                            sw(v0, sp, 0xB0);
                            lh(v0, sp, 0xE6);
                            sh(v0, sp, 0xC0);
                            goto L_004ba3e8;
                        }
                        // 0x004ba388
                        charge(ctx, 11);
                        lw(v0, s0, 0);
                        v1 = 2;
                        sw(v0, sp, 0xD0);
                        lw(v0, sp, 0xE0);
                        lw(s0, sp, 0xFC);
                        sw(v0, sp, 0xB0);
                        lh(v0, sp, 0xEA);
                        sh(v0, sp, 0xC0);
                        lw(v0, sp, 0xD0);
                        lw(s2, sp, 0xE4);
                        if (v0 != v1) {
                        L_004ba3e8:
                            charge(ctx, 2);
                            if (i64(s0) > 0) {
                                // 0x004ba3f0
                                charge(ctx, 7);
                                lh(v0, sp, 0xC0);
                                s1 = v0;
                                v0 = 1;
                                v0 = sllv(v0, s1);
                                at = slt(v0, s0);
                                if (at != 0) {
                                    goto L_004ba6d0;
                                }
                                goto L_004ba40c;
                            }
                        L_004ba6d0:
                            charge(ctx, 5);
                            lh(v0, sp, 0xC0);
                            s1 = v0;
                            v0 = 1;
                            s0 = sllv(v0, s1);
                            backedge(ctx);
                        L_004ba40c:
                            charge(ctx, 3);
                            v0 = 32;
                            if (s1 != v0) {
                                // 0x004ba418
                                charge(ctx, 3);
                                v0 = 24;
                                if (s1 == v0) {
                                    goto L_004ba470;
                                }
                                // 0x004ba424
                                charge(ctx, 3);
                                v0 = 16;
                                if (s1 == v0) {
                                    goto L_004ba470;
                                }
                                // 0x004ba430
                                charge(ctx, 3);
                                v0 = 15;
                                if (s1 == v0) {
                                    goto L_004ba470;
                                }
                                // 0x004ba43c
                                charge(ctx, 3);
                                a2 = 8;
                                if (s1 != a2) {
                                    // 0x004ba448
                                    charge(ctx, 3);
                                    v0 = 4;
                                    if (s1 != v0) {
                                        // 0x004ba454
                                        charge(ctx, 3);
                                        v0 = 1;
                                        if (s1 == v0) {
                                            goto L_004ba468;
                                        }
                                        // 0x004ba460
                                        charge(ctx, 2);
                                        a2 = 32;
                                        goto L_004ba474;
                                    }
                                L_004ba468:
                                    charge(ctx, 2);
                                    a2 = 4;
                                }
                                goto L_004ba474;
                            }
                        L_004ba470:
                            charge(ctx, 1);
                            a2 = 32;
                        L_004ba474:
                            charge(ctx, 6);
                            lw(a0, sp, 0xB0);
                            a1 = s2;
                            jal(ctx, 0x4BA478u, gen::fn_sub_4CBE00_004cbe00);
                            fp = v0;
                            if (fp == 0) {
                                // 0x004ba6e4
                                charge(ctx, 5);
                                a0 = s5;
                                a1 = 0;
                                jal(ctx, 0x4BA6E8u, gen::fn_sub_4C5780_004c5780);
                                v0 = 0;
                            } else {
                                // 0x004ba48c
                                charge(ctx, 4);
                                a0 = fp;
                                jal(ctx, 0x4BA48Cu, gen::fn_sub_4CBF20_004cbf20);
                                if (v0 == 0) {
                                    // 0x004ba6f8
                                    charge(ctx, 7);
                                    a0 = fp;
                                    jal(ctx, 0x4BA6F8u, gen::fn_sub_4CBEB0_004cbeb0);
                                    a0 = s5;
                                    a1 = 0;
                                    jal(ctx, 0x4BA704u, gen::fn_sub_4C5780_004c5780);
                                    v0 = 0;
                                } else {
                                    // 0x004ba49c
                                    charge(ctx, 3);
                                    at = slti(s1, 9);
                                    if (at != 0) {
                                        // 0x004ba4a8
                                        charge(ctx, 3);
                                        v0 = 12;
                                        lw(s6, fp, 0x18);
                                        if (s7 == v0) {
                                            // 0x004ba714
                                            charge(ctx, 8);
                                            v0 = sll(s0, 1);
                                            a0 = s5;
                                            s7 = addu(v0, s0);
                                            a1 = addiu(sp, 0xE0);
                                            a2 = s7;
                                            jal(ctx, 0x4BA724u, gen::fn_sub_4C5250_004c5250);
                                            if (s7 == v0) {
                                                // 0x004ba734
                                                charge(ctx, 4);
                                                at = slt(0, s0);
                                                s3 = addu(s3, s7);
                                                a2 = 0;
                                                if (at != 0) {
                                                    // 0x004ba744
                                                    charge(ctx, 3);
                                                    at = slti(s0, 9);
                                                    v1 = addiu(s0, -8);
                                                    if (at == 0) {
                                                        // 0x004ba750
                                                        charge(ctx, 3);
                                                        at = slt(s0, 0);
                                                        v0 = 0;
                                                        if (at == 0) {
                                                            // 0x004ba75c
                                                            charge(ctx, 5);
                                                            at = 0x7FFF0000;
                                                            at = at | 0xFFFF;
                                                            at = slt(s0, at);
                                                            if (at != 0) {
                                                                // 0x004ba770
                                                                charge(ctx, 1);
                                                                v0 = 1;
                                                            }
                                                        }
                                                        // 0x004ba774
                                                        charge(ctx, 2);
                                                        if (v0 != 0) {
                                                            // 0x004ba77c
                                                            charge(ctx, 3);
                                                            a1 = addiu(sp, 0xE0);
                                                            a0 = s6;
                                                            v0 = 255;
                                                            for (;;) {
                                                                // 0x004ba788
                                                                charge(ctx, 61);
                                                                lbu(t0, a1, 2);
                                                                a2 = addiu(a2, 8);
                                                                a3 = slt(a2, v1);
                                                                sb(t0, a0, 0);
                                                                lbu(t0, a1, 1);
                                                                sb(t0, a0, 1);
                                                                lbu(t0, a1, 0);
                                                                sb(t0, a0, 2);
                                                                sb(v0, a0, 3);
                                                                lbu(t0, a1, 5);
                                                                sb(t0, a0, 4);
                                                                lbu(t0, a1, 4);
                                                                sb(t0, a0, 5);
                                                                lbu(t0, a1, 3);
                                                                sb(t0, a0, 6);
                                                                sb(v0, a0, 7);
                                                                lbu(t0, a1, 8);
                                                                sb(t0, a0, 8);
                                                                lbu(t0, a1, 7);
                                                                sb(t0, a0, 9);
                                                                lbu(t0, a1, 6);
                                                                sb(t0, a0, 10);
                                                                sb(v0, a0, 11);
                                                                lbu(t0, a1, 11);
                                                                sb(t0, a0, 12);
                                                                lbu(t0, a1, 10);
                                                                sb(t0, a0, 13);
                                                                lbu(t0, a1, 9);
                                                                sb(t0, a0, 14);
                                                                sb(v0, a0, 15);
                                                                lbu(t0, a1, 14);
                                                                sb(t0, a0, 16);
                                                                lbu(t0, a1, 13);
                                                                sb(t0, a0, 17);
                                                                lbu(t0, a1, 12);
                                                                sb(t0, a0, 18);
                                                                sb(v0, a0, 19);
                                                                lbu(t0, a1, 17);
                                                                sb(t0, a0, 20);
                                                                lbu(t0, a1, 16);
                                                                sb(t0, a0, 21);
                                                                lbu(t0, a1, 15);
                                                                sb(t0, a0, 22);
                                                                sb(v0, a0, 23);
                                                                lbu(t0, a1, 20);
                                                                sb(t0, a0, 24);
                                                                lbu(t0, a1, 19);
                                                                sb(t0, a0, 25);
                                                                lbu(t0, a1, 18);
                                                                sb(t0, a0, 26);
                                                                sb(v0, a0, 27);
                                                                lbu(t0, a1, 23);
                                                                sb(t0, a0, 28);
                                                                lbu(t0, a1, 22);
                                                                sb(t0, a0, 29);
                                                                lbu(t0, a1, 21);
                                                                sb(t0, a0, 30);
                                                                a1 = addiu(a1, 24);
                                                                sb(v0, a0, 31);
                                                                a0 = addiu(a0, 32);
                                                                if (a3 == 0) {
                                                                    break;
                                                                }
                                                                backedge(ctx);
                                                            }
                                                            // 0x004ba87c
                                                            charge(ctx, 1);
                                                        }
                                                    }
                                                    // 0x004ba880
                                                    charge(ctx, 3);
                                                    at = slt(a2, s0);
                                                    if (at != 0) {
                                                        // 0x004ba88c
                                                        charge(ctx, 7);
                                                        v0 = sll(a2, 2);
                                                        v1 = sll(a2, 1);
                                                        a1 = addu(s6, v0);
                                                        v0 = addu(v1, a2);
                                                        v0 = addu(v0, sp);
                                                        v1 = 255;
                                                        a3 = addiu(v0, 224);
                                                        for (;;) {
                                                            // 0x004ba8a8
                                                            charge(ctx, 12);
                                                            lbu(a0, a3, 2);
                                                            a2 = addiu(a2, 1);
                                                            v0 = slt(a2, s0);
                                                            sb(a0, a1, 0);
                                                            lbu(a0, a3, 1);
                                                            sb(a0, a1, 1);
                                                            lbu(a0, a3, 0);
                                                            sb(a0, a1, 2);
                                                            a3 = addiu(a3, 3);
                                                            sb(v1, a1, 3);
                                                            a1 = addiu(a1, 4);
                                                            if (v0 == 0) {
                                                                break;
                                                            }
                                                            backedge(ctx);
                                                        }
                                                    }
                                                }
                                                goto L_004ba8d8;
                                            }
                                            // 0x004bab24
                                            charge(ctx, 5);
                                            a0 = s5;
                                            a1 = 0;
                                            jal(ctx, 0x4BAB28u, gen::fn_sub_4C5780_004c5780);
                                            v0 = 0;
                                        } else {
                                            // 0x004ba4b4
                                            charge(ctx, 3);
                                            v0 = 40;
                                            if (s7 != v0) {
                                                // 0x004bab4c
                                                charge(ctx, 13);
                                                v1 = 413;
                                                v0 = lui(0x8000);
                                                sw(v1, sp, 0x4F8);
                                                a0 = v0 | 0x9;
                                                jal(ctx, 0x4BAB58u, gen::fn_sub_4C1D10_004c1d10);
                                                sw(v0, sp, 0x4FC);
                                                a0 = addiu(sp, 0x4F8);
                                                jal(ctx, 0x4BAB64u, gen::fn_sub_4C1C50_004c1c50);
                                                a0 = s5;
                                                a1 = 0;
                                                jal(ctx, 0x4BAB70u, gen::fn_sub_4C5780_004c5780);
                                                v0 = 0;
                                            } else {
                                                // 0x004ba4c0
                                                charge(ctx, 7);
                                                s7 = sll(s0, 2);
                                                a0 = s5;
                                                a1 = addiu(sp, 0xE0);
                                                a2 = s7;
                                                jal(ctx, 0x4BA4CCu, gen::fn_sub_4C5250_004c5250);
                                                if (s7 == v0) {
                                                    // 0x004ba4dc
                                                    charge(ctx, 4);
                                                    at = slt(0, s0);
                                                    s3 = addu(s3, s7);
                                                    a0 = 0;
                                                    if (at != 0) {
                                                        // 0x004ba4ec
                                                        charge(ctx, 3);
                                                        at = slti(s0, 9);
                                                        v1 = addiu(s0, -8);
                                                        if (at == 0) {
                                                            // 0x004ba4f8
                                                            charge(ctx, 3);
                                                            at = slt(s0, 0);
                                                            v0 = 0;
                                                            if (at == 0) {
                                                                // 0x004ba504
                                                                charge(ctx, 5);
                                                                at = 0x7FFF0000;
                                                                at = at | 0xFFFF;
                                                                at = slt(s0, at);
                                                                if (at != 0) {
                                                                    // 0x004ba518
                                                                    charge(ctx, 1);
                                                                    v0 = 1;
                                                                }
                                                            }
                                                            // 0x004ba51c
                                                            charge(ctx, 2);
                                                            if (v0 != 0) {
                                                                // 0x004ba524
                                                                charge(ctx, 3);
                                                                a2 = addiu(sp, 0xE0);
                                                                a1 = s6;
                                                                v0 = 255;
                                                                for (;;) {
                                                                    // 0x004ba530
                                                                    charge(ctx, 61);
                                                                    lbu(t0, a2, 2);
                                                                    a0 = addiu(a0, 8);
                                                                    a3 = slt(a0, v1);
                                                                    sb(t0, a1, 0);
                                                                    lbu(t0, a2, 1);
                                                                    sb(t0, a1, 1);
                                                                    lbu(t0, a2, 0);
                                                                    sb(t0, a1, 2);
                                                                    sb(v0, a1, 3);
                                                                    lbu(t0, a2, 6);
                                                                    sb(t0, a1, 4);
                                                                    lbu(t0, a2, 5);
                                                                    sb(t0, a1, 5);
                                                                    lbu(t0, a2, 4);
                                                                    sb(t0, a1, 6);
                                                                    sb(v0, a1, 7);
                                                                    lbu(t0, a2, 10);
                                                                    sb(t0, a1, 8);
                                                                    lbu(t0, a2, 9);
                                                                    sb(t0, a1, 9);
                                                                    lbu(t0, a2, 8);
                                                                    sb(t0, a1, 10);
                                                                    sb(v0, a1, 11);
                                                                    lbu(t0, a2, 14);
                                                                    sb(t0, a1, 12);
                                                                    lbu(t0, a2, 13);
                                                                    sb(t0, a1, 13);
                                                                    lbu(t0, a2, 12);
                                                                    sb(t0, a1, 14);
                                                                    sb(v0, a1, 15);
                                                                    lbu(t0, a2, 18);
                                                                    sb(t0, a1, 16);
                                                                    lbu(t0, a2, 17);
                                                                    sb(t0, a1, 17);
                                                                    lbu(t0, a2, 16);
                                                                    sb(t0, a1, 18);
                                                                    sb(v0, a1, 19);
                                                                    lbu(t0, a2, 22);
                                                                    sb(t0, a1, 20);
                                                                    lbu(t0, a2, 21);
                                                                    sb(t0, a1, 21);
                                                                    lbu(t0, a2, 20);
                                                                    sb(t0, a1, 22);
                                                                    sb(v0, a1, 23);
                                                                    lbu(t0, a2, 26);
                                                                    sb(t0, a1, 24);
                                                                    lbu(t0, a2, 25);
                                                                    sb(t0, a1, 25);
                                                                    lbu(t0, a2, 24);
                                                                    sb(t0, a1, 26);
                                                                    sb(v0, a1, 27);
                                                                    lbu(t0, a2, 30);
                                                                    sb(t0, a1, 28);
                                                                    lbu(t0, a2, 29);
                                                                    sb(t0, a1, 29);
                                                                    lbu(t0, a2, 28);
                                                                    sb(t0, a1, 30);
                                                                    a2 = addiu(a2, 32);
                                                                    sb(v0, a1, 31);
                                                                    a1 = addiu(a1, 32);
                                                                    if (a3 == 0) {
                                                                        break;
                                                                    }
                                                                    backedge(ctx);
                                                                }
                                                                // 0x004ba624
                                                                charge(ctx, 1);
                                                            }
                                                        }
                                                        // 0x004ba628
                                                        charge(ctx, 3);
                                                        at = slt(a0, s0);
                                                        if (at != 0) {
                                                            // 0x004ba634
                                                            charge(ctx, 5);
                                                            v0 = sll(a0, 2);
                                                            v1 = 255;
                                                            a2 = addu(s6, v0);
                                                            v0 = addu(v0, sp);
                                                            a3 = addiu(v0, 224);
                                                            for (;;) {
                                                                // 0x004ba648
                                                                charge(ctx, 12);
                                                                lbu(a1, a3, 2);
                                                                a0 = addiu(a0, 1);
                                                                v0 = slt(a0, s0);
                                                                sb(a1, a2, 0);
                                                                lbu(a1, a3, 1);
                                                                sb(a1, a2, 1);
                                                                lbu(a1, a3, 0);
                                                                sb(a1, a2, 2);
                                                                a3 = addiu(a3, 4);
                                                                sb(v1, a2, 3);
                                                                a2 = addiu(a2, 4);
                                                                if (v0 == 0) {
                                                                    break;
                                                                }
                                                                backedge(ctx);
                                                            }
                                                            // 0x004ba678
                                                            charge(ctx, 2);
                                                        }
                                                    }
                                                    goto L_004ba8d8;
                                                }
                                                // 0x004bab38
                                                charge(ctx, 5);
                                                a0 = s5;
                                                a1 = 0;
                                                jal(ctx, 0x4BAB3Cu, gen::fn_sub_4C5780_004c5780);
                                                v0 = 0;
                                            }
                                        }
                                        // 0x004bad1c (the shared epilogue, written out on this path)
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
                                        sp = addiu(sp, 0x510);
                                        return;
                                    }
                                L_004ba8d8:
                                    charge(ctx, 5);
                                    a1 = subu(s4, s3);
                                    a0 = s5;
                                    jal(ctx, 0x4BA8DCu, gen::fn_sub_4C5620_004c5620);
                                    if (v0 == 0) {
                                        // 0x004bab80
                                        charge(ctx, 7);
                                        a0 = fp;
                                        jal(ctx, 0x4BAB80u, gen::fn_sub_4CBEB0_004cbeb0);
                                        a0 = s5;
                                        a1 = 0;
                                        jal(ctx, 0x4BAB8Cu, gen::fn_sub_4C5780_004c5780);
                                        v0 = 0;
                                    } else {
                                        // 0x004ba8ec
                                        charge(ctx, 5);
                                        lw(v0, sp, 0xB0);
                                        mult(v0, v0, s1);
                                        v1 = addiu(v0, 7);
                                        v0 = sra(v1, 3);
                                        if (i64(v1) < 0) {
                                            // 0x004ba900
                                            charge(ctx, 2);
                                            v0 = addiu(v1, 7);
                                            v0 = sra(v0, 3);
                                        }
                                        // 0x004ba908
                                        charge(ctx, 10);
                                        a1 = addiu(v0, 3);
                                        a0 = si(-4);
                                        lw(v0, sp, 0xB0);
                                        s0 = a1 & a0;
                                        v1 = addiu(v0, 7);
                                        v0 = si(-8);
                                        a0 = v1 & v0;
                                        v1 = addiu(s1, 7);
                                        v0 = sra(v1, 3);
                                        if (i64(v1) < 0) {
                                            // 0x004ba930
                                            charge(ctx, 2);
                                            v0 = addiu(v1, 7);
                                            v0 = sra(v0, 3);
                                        }
                                        // 0x004ba938
                                        charge(ctx, 9);
                                        mult(s3, a0, v0);
                                        a1 = 0x10000;
                                        v0 = 0x960000;
                                        lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
                                        a0 = s3;
                                        jalr(ctx, 0x4BA948u, v0.u());
                                        s4 = v0;
                                        if (s4 != 0) {
                                            // 0x004ba95c
                                            charge(ctx, 3);
                                            lw(v0, sp, 0xD0);
                                            if (v0 != 0) {
                                                // 0x004ba968
                                                charge(ctx, 3);
                                                v0 = 24;
                                                if (s1 == v0) {
                                                    goto L_004ba9b8;
                                                }
                                                // 0x004ba974
                                                charge(ctx, 3);
                                                v0 = 32;
                                                if (s1 == v0) {
                                                    goto L_004ba9b8;
                                                }
                                                // 0x004ba980
                                                charge(ctx, 4);
                                                lw(v0, sp, 0xD0);
                                                v1 = 1;
                                                if (v0 != v1) {
                                                    // 0x004baccc
                                                    charge(ctx, 19);
                                                    v1 = 413;
                                                    v0 = lui(0x8000);
                                                    sw(v1, sp, 0x4E8);
                                                    a0 = v0 | 0x9;
                                                    jal(ctx, 0x4BACD8u, gen::fn_sub_4C1D10_004c1d10);
                                                    sw(v0, sp, 0x4EC);
                                                    a0 = addiu(sp, 0x4E8);
                                                    jal(ctx, 0x4BACE4u, gen::fn_sub_4C1C50_004c1c50);
                                                    v0 = 0x960000;
                                                    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                                                    a0 = s4;
                                                    jalr(ctx, 0x4BACF4u, v0.u());
                                                    a0 = fp;
                                                    jal(ctx, 0x4BACFCu, gen::fn_sub_4CBEB0_004cbeb0);
                                                    a0 = s5;
                                                    a1 = 0;
                                                    jal(ctx, 0x4BAD08u, gen::fn_sub_4C5780_004c5780);
                                                    v0 = 0;
                                                } else {
                                                    // 0x004ba990
                                                    charge(ctx, 3);
                                                    at = slt(0, s2);
                                                    s7 = 0;
                                                    if (at == 0) {
                                                    L_004bab00:
                                                        charge(ctx, 9);
                                                        v0 = 0x960000;
                                                        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                                                        a0 = s4;
                                                        jalr(ctx, 0x4BAB08u, v0.u());
                                                        a0 = s5;
                                                        a1 = 0;
                                                        jal(ctx, 0x4BAB14u, gen::fn_sub_4C5780_004c5780);
                                                        v0 = fp;
                                                    } else {
                                                        // 0x004ba99c
                                                        charge(ctx, 4);
                                                        lh(v0, sp, 0xC0);
                                                        s6 = addiu(sp, 0x509);
                                                        // daddu v0: a 64-bit move to itself (no effect)
                                                        sw(v0, sp, 0xA0);
                                                        for (;;) {
                                                        L_004ba9ac:
                                                            charge(ctx, 3);
                                                            s1 = 0;
                                                            s3 = 0;
                                                            for (;;) {
                                                                // 0x004baa44
                                                                charge(ctx, 7);
                                                                a0 = s5;
                                                                a1 = addiu(sp, 0x508);
                                                                a2 = 2;
                                                                jal(ctx, 0x4BAA4Cu, gen::fn_sub_4C5250_004c5250);
                                                                v1 = 2;
                                                                if (v0 != v1) {
                                                                    goto L_004baa60_80;
                                                                }
                                                                // 0x004baa8c
                                                                charge(ctx, 3);
                                                                lbu(a2, sp, 0x508);
                                                                if (a2 != 0) {
                                                                    // 0x004babdc
                                                                    charge(ctx, 6);
                                                                    lbu(a1, s6, 0);
                                                                    a0 = addu(s4, s1);
                                                                    jal(ctx, 0x4BABE0u, gen::fn_memset_00521408);
                                                                    lbu(v0, sp, 0x508);
                                                                    s1 = addu(s1, v0);
                                                                    backedge(ctx);
                                                                L_004baac0:
                                                                    charge(ctx, 4);
                                                                    v0 = sltu(0, s3);
                                                                    v0 = v0 ^ 0x1;
                                                                    if (v0 == 0) {
                                                                        goto L_004baad0_87;
                                                                    }
                                                                    backedge(ctx);
                                                                    continue;
                                                                }
                                                                // 0x004baa98
                                                                charge(ctx, 4);
                                                                lbu(s0, s6, 0);
                                                                at = slti(s0, 3);
                                                                if (at != 0) {
                                                                    // 0x004baaa8
                                                                    charge(ctx, 2);
                                                                    if (s0 == 0) {
                                                                        // 0x004bac98
                                                                        charge(ctx, 2);
                                                                        s3 = 1;
                                                                        backedge(ctx);
                                                                        goto L_004baac0;
                                                                    }
                                                                    // 0x004baab0
                                                                    charge(ctx, 3);
                                                                    s3 = 1;
                                                                    if (s0 != s3) {
                                                                        break;
                                                                    }
                                                                    // 0x004baabc
                                                                    charge(ctx, 1);
                                                                    s7 = addiu(s2, -1);
                                                                    goto L_004baac0;
                                                                }
                                                                // 0x004babf8
                                                                charge(ctx, 6);
                                                                a1 = addu(s4, s1);
                                                                a0 = s5;
                                                                a2 = s0;
                                                                jal(ctx, 0x4BAC00u, gen::fn_sub_4C5250_004c5250);
                                                                if (s0 != v0) {
                                                                    goto L_004bac6c;
                                                                }
                                                                // 0x004bac10
                                                                charge(ctx, 5);
                                                                lbu(v0, s6, 0);
                                                                s1 = addu(s1, v0);
                                                                v0 = v0 & 0x1;
                                                                if (v0 == 0) {
                                                                    backedge(ctx);
                                                                    goto L_004baac0;
                                                                }
                                                                // 0x004bac24
                                                                charge(ctx, 7);
                                                                a0 = s5;
                                                                a1 = addiu(sp, 0x508);
                                                                a2 = 1;
                                                                jal(ctx, 0x4BAC2Cu, gen::fn_sub_4C5250_004c5250);
                                                                v1 = 1;
                                                                if (v0 != v1) {
                                                                    goto L_004bac40_99;
                                                                }
                                                                backedge(ctx);
                                                                goto L_004baac0;
                                                            }
                                                            break;
                                                        }
                                                        // 0x004baca0
                                                        charge(ctx, 11);
                                                        v0 = 0x960000;
                                                        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                                                        a0 = s4;
                                                        jalr(ctx, 0x4BACA8u, v0.u());
                                                        a0 = fp;
                                                        jal(ctx, 0x4BACB0u, gen::fn_sub_4CBEB0_004cbeb0);
                                                        a0 = s5;
                                                        a1 = 0;
                                                        jal(ctx, 0x4BACBCu, gen::fn_sub_4C5780_004c5780);
                                                        v0 = 0;
                                                    }
                                                }
                                                // 0x004bad1c (the shared epilogue, written out on this path)
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
                                                sp = addiu(sp, 0x510);
                                                return;
                                            }
                                        L_004ba9b8:
                                            charge(ctx, 3);
                                            at = slt(0, s2);
                                            s1 = 0;
                                            if (at == 0) {
                                                goto L_004bab00;
                                            }
                                            // 0x004ba9c4
                                            charge(ctx, 2);
                                            lh(v0, sp, 0xC0);
                                            s3 = v0;
                                            for (;;) {
                                                // 0x004ba9cc
                                                charge(ctx, 6);
                                                a0 = s5;
                                                a1 = s4;
                                                a2 = s0;
                                                jal(ctx, 0x4BA9D4u, gen::fn_sub_4C5250_004c5250);
                                                if (s0 != v0) {
                                                    goto L_004ba9e4_76;
                                                }
                                                // 0x004baa10
                                                charge(ctx, 11);
                                                v0 = addiu(s2, -1);
                                                a0 = fp;
                                                a1 = subu(v0, s1);
                                                a2 = s4;
                                                a3 = s3;
                                                t0 = 0;
                                                jal(ctx, 0x4BAA24u, gen::fn_sub_4B9E00_004b9e00);
                                                s1 = addiu(s1, 1);
                                                v0 = slt(s1, s2);
                                                if (v0 == 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                            // 0x004baa3c
                                            charge(ctx, 2);
                                            goto L_004bab00;
                                        }
                                        // 0x004bab9c
                                        charge(ctx, 16);
                                        v0 = 413;
                                        a1 = s3;
                                        sw(v0, sp, 0x4F0);
                                        v0 = lui(0x8000);
                                        a0 = v0 | 0x13;
                                        jal(ctx, 0x4BABACu, gen::fn_sub_4C1D10_004c1d10);
                                        sw(v0, sp, 0x4F4);
                                        a0 = addiu(sp, 0x4F0);
                                        jal(ctx, 0x4BABB8u, gen::fn_sub_4C1C50_004c1c50);
                                        a0 = fp;
                                        jal(ctx, 0x4BABC0u, gen::fn_sub_4CBEB0_004cbeb0);
                                        a0 = s5;
                                        a1 = 0;
                                        jal(ctx, 0x4BABCCu, gen::fn_sub_4C5780_004c5780);
                                        v0 = 0;
                                    }
                                }
                            }
                        } else {
                            // 0x004ba3b4
                            charge(ctx, 13);
                            v1 = 413;
                            v0 = lui(0x8000);
                            sw(v1, sp, 0x500);
                            a0 = v0 | 0x9;
                            jal(ctx, 0x4BA3C0u, gen::fn_sub_4C1D10_004c1d10);
                            sw(v0, sp, 0x504);
                            a0 = addiu(sp, 0x500);
                            jal(ctx, 0x4BA3CCu, gen::fn_sub_4C1C50_004c1c50);
                            a0 = s5;
                            a1 = 0;
                            jal(ctx, 0x4BA3D8u, gen::fn_sub_4C5780_004c5780);
                            v0 = 0;
                        }
                    }
                }
            }
        }
    }
    // 0x004bad1c (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x510);
    return;
L_004ba9e4_76:
    charge(ctx, 11);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    a0 = s4;
    jalr(ctx, 0x4BA9ECu, v0.u());
    a0 = fp;
    jal(ctx, 0x4BA9F4u, gen::fn_sub_4CBEB0_004cbeb0);
    a0 = s5;
    a1 = 0;
    jal(ctx, 0x4BAA00u, gen::fn_sub_4C5780_004c5780);
    v0 = 0;
    // 0x004bad1c (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x510);
    return;
L_004baa60_80:
    charge(ctx, 11);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    a0 = s4;
    jalr(ctx, 0x4BAA68u, v0.u());
    a0 = fp;
    jal(ctx, 0x4BAA70u, gen::fn_sub_4CBEB0_004cbeb0);
    a0 = s5;
    a1 = 0;
    jal(ctx, 0x4BAA7Cu, gen::fn_sub_4C5780_004c5780);
    v0 = 0;
    // 0x004bad1c (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x510);
    return;
L_004baad0_87:
    charge(ctx, 11);
    lw(a3, sp, 0xA0);
    v0 = addiu(s2, -1);
    a0 = fp;
    a1 = subu(v0, s7);
    a2 = s4;
    t0 = 1;
    jal(ctx, 0x4BAAE4u, gen::fn_sub_4B9E00_004b9e00);
    s7 = addiu(s7, 1);
    v0 = slt(s7, s2);
    if (v0 == 0) {
        goto L_004baafc_88;
    }
    backedge(ctx);
    goto L_004ba9ac;
L_004baafc_88:
    charge(ctx, 1);
    goto L_004bab00;
L_004bac40_99:
    charge(ctx, 11);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    a0 = s4;
    jalr(ctx, 0x4BAC48u, v0.u());
    a0 = fp;
    jal(ctx, 0x4BAC50u, gen::fn_sub_4CBEB0_004cbeb0);
    a0 = s5;
    a1 = 0;
    jal(ctx, 0x4BAC5Cu, gen::fn_sub_4C5780_004c5780);
    v0 = 0;
    // 0x004bad1c (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x510);
    return;
L_004bac6c:
    charge(ctx, 11);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    a0 = s4;
    jalr(ctx, 0x4BAC74u, v0.u());
    a0 = fp;
    jal(ctx, 0x4BAC7Cu, gen::fn_sub_4CBEB0_004cbeb0);
    a0 = s5;
    a1 = 0;
    jal(ctx, 0x4BAC88u, gen::fn_sub_4C5780_004c5780);
    v0 = 0;
    // 0x004bad1c (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x510);
}


// sub_4BAD50 [bmpImageWrite] -- writes an image as a BMP file: the file stream opened (sub_4C58A0), the headers and pixels, closed; the image, or 0
// 0x004BAD50 sub_4BAD50 -- 172 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4BAD50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004bad50
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a2 = a1;
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    s2 = a0;
    sq(s1, sp, 0x10);
    a0 = 2;
    sq(s0, sp, 0x0);
    a1 = a0;
    jal(ctx, 0x4BAD70u, gen::fn_sub_4C58A0_004c58a0);
    s1 = v0;
    if (s1 == 0) {
        // 0x004bade0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004bad84
        charge(ctx, 3);
        lw(v0, s2, 24);
        s0 = 24;
        if (v0 != 0) {
            // 0x004bad90
            charge(ctx, 1);
            lw(s0, s2, 12);
        }
        // 0x004bad94
        charge(ctx, 19);
        a0 = s1;
        a1 = s0;
        a2 = s2;
        jal(ctx, 0x4BAD9Cu, gen::fn_sub_4B9870_004b9870);
        a0 = s1;
        a1 = s0;
        a2 = s2;
        jal(ctx, 0x4BADACu, gen::fn_sub_4B99A0_004b99a0);
        a0 = s1;
        a1 = s0;
        a2 = s2;
        jal(ctx, 0x4BADBCu, gen::fn_sub_4B9D40_004b9d40);
        a0 = s0;
        jal(ctx, 0x4BADC4u, gen::fn_sub_4B9840_004b9840);
        a0 = s1;
        a1 = 0;
        jal(ctx, 0x4BADD0u, gen::fn_sub_4C5780_004c5780);
        v0 = s2;
    }
    // 0x004bade4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4BC830 [mipKLTriangleArea] -- accumulates a triangle's texel density: its screen area (cross product) against its texture's texel count, summed into the pass record
// 0x004BC830 sub_4BC830 -- 464 bytes; frame 0x90: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
void sub_4BC830(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f12{ctx, 12}, f20{ctx, 20};
    // 0x004bc830
    enter(ctx, 90);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    s5 = a1;
    sq(s3, sp, 0x40);
    s4 = a2;
    sq(s2, sp, 0x30);
    v0 = sll(s4, 3);
    sq(s1, sp, 0x20);
    s3 = a3;
    a2 = addu(v0, a0);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    v0 = sll(s3, 3);
    a1 = addu(a0, v0);
    s2 = t0;
    v0 = sll(s2, 3);
    lw(a3, t1, 8);
    v1 = addu(v0, a0);
    s1 = t1;
    lwc1(f3, a2, 0);
    v0 = 0x3F000000;
    lwc1(f4, a1, 4);
    lwc1(f6, a2, 4);
    lwc1(f5, a1, 0);
    lwc1(f2, v1, 4);
    lw(s0, a3, 0);
    lwc1(f1, v1, 0);
    mtc1(v0, f0);
    mula_s(f3, f4);
    msuba_s(f5, f6);
    madda_s(f5, f2);
    msuba_s(f1, f4);
    madda_s(f1, f6);
    msub_s(f1, f3, f2);
    mul_s(f12, f0, f1);
    jal(ctx, 0x4BC8C0u, gen::fn_fabsf_0052e788);
    lw(v1, s0, 12);
    lw(v0, s0, 16);
    mult(a0, v1, v0);
    mtc1(a0, f1);
    v0 = sll(s4, 1);
    v1 = addu(v0, s4);
    cvt_s_w(f1, f1);
    v0 = sll(s3, 1);
    v0 = addu(v0, s3);
    v1 = sll(v1, 2);
    a1 = addu(s5, v1);
    v0 = sll(v0, 2);
    v1 = addu(s5, v0);
    a0 = addiu(sp, 0x80);
    v0 = sll(s2, 1);
    v0 = addu(v0, s2);
    mul_s(f20, f0, f1);
    v0 = sll(v0, 2);
    v0 = addu(s5, v0);
    lwc1(f4, a1, 0);
    lwc1(f3, v1, 0);
    lwc1(f0, v0, 0);
    lwc1(f5, a1, 8);
    lwc1(f1, v1, 8);
    lwc1(f7, a1, 4);
    lwc1(f2, v1, 4);
    sub_s(f8, f3, f4);
    sub_s(f3, f0, f4);
    sub_s(f4, f1, f5);
    lwc1(f1, v0, 4);
    sub_s(f6, f2, f7);
    lwc1(f0, v0, 8);
    sub_s(f2, f1, f7);
    sub_s(f1, f0, f5);
    mula_s(f6, f1);
    msub_s(f0, f4, f2);
    swc1(f0, sp, 0x80);
    mula_s(f4, f3);
    msub_s(f0, f8, f1);
    mula_s(f8, f2);
    swc1(f0, sp, 0x84);
    msub_s(f0, f6, f3);
    link(ctx, 0x4BC970u);  // $ra first: the delay slot below depends on it
    swc1(f0, sp, 0x88);
    call(ctx, gen::fn_sub_4C6AC0_004c6ac0);
    v1 = 0x3F000000;
    mtc1(v1, f2);
    mtc1(zero, f1);
    mul_s(f2, f2, f0);
    c_le_s(f2, f1);
    if (!cond(ctx)) {
        // 0x004bc998
        charge(ctx, 6);
        v1 = 0x3F800000;
        mtc1(v1, f0);
        c_le_s(f20, f0);
        if (!cond(ctx)) {
            // 0x004bc9b0
            charge(ctx, 10);
            lwc1(f1, s1, 20);
            lwc1(f0, s1, 12);
            mul_s(f1, f2, f1);
            div_s(f1, f1, f20);
            sqrt_s(f1, f1);
            add_s(f0, f0, f1);
            swc1(f0, s1, 12);
            lw(v1, s1, 16);
            v1 = addiu(v1, 1);
            sw(v1, s1, 16);
        }
    }
    // 0x004bc9d8 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lwc1(f20, sp, 0x0);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x90);
}


// sub_4BCA00 [mipKLSectorTriangles] -- visits a world sector's triangles: those whose material passes the pass's filter add their density (sub_4BC830); the sector
// 0x004BCA00 sub_4BCA00 -- 216 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4BCA00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004bca00
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    lhu(v0, a0, 132);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s2 = 0;
    v0 = sltu(0, v0);
    sq(s0, sp, 0x0);
    if (v0 != 0) {
        // 0x004bca3c
        charge(ctx, 1);
        s1 = 0;
        for (;;) {
            // 0x004bca40
            charge(ctx, 13);
            lw(a0, s4, 4);
            lw(v1, s3, 4);
            lw(v0, s3, 24);
            s0 = addu(a0, s1);
            lhu(a0, s0, 6);
            lw(v1, v1, 16);
            a0 = sll(a0, 2);
            v1 = addu(v1, a0);
            lw(a0, v1, 0);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x4BCA64u);  // $ra = the return address
            lw(a1, s3, 8);
            call_ptr(ctx, jt);
            if (v0 != 0) {
                // 0x004bca94
                charge(ctx, 9);
                lhu(a2, s0, 0);
                lhu(a3, s0, 2);
                lhu(t0, s0, 4);
                lw(a0, s4, 16);
                lw(a1, s4, 8);
                t1 = s3;
                jal(ctx, 0x4BCAA8u, gen::fn_sub_4BC830_004bc830);
                backedge(ctx);
            } else {
                // 0x004bca74
                charge(ctx, 1);
            }
            // 0x004bca78
            charge(ctx, 5);
            lhu(v0, s4, 132);
            s2 = addiu(s2, 1);
            v0 = sltu(s2, v0);
            s1 = addiu(s1, 8);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004bca8c
        charge(ctx, 2);
        backedge(ctx);
    }
    // 0x004bca34
    charge(ctx, 2);
    v0 = s4;
    // 0x004bcab8
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_4BCAE0 [mipKLSectorCallBack] -- the sector callback of the K / L pass: the material filter set (sub_4BCB20), the sector's triangles visited
// 0x004BCAE0 sub_4BCAE0 -- 52 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4BCAE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004bcae0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x4C0000;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, -13536);  // &sub_4BCB20
    sq(s0, sp, 0x0);
    s0 = a0;
    link(ctx, 0x4BCAF8u);  // $ra first: the delay slot below depends on it
    sw(v0, a1, 24);
    call(ctx, gen::fn_sub_4BCA00_004bca00);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4BCB20 [mipKLMatchTexture] -- 1 when the material's texture is the one the pass looks at
// 0x004BCB20 sub_4BCB20 -- 16 bytes; leaf frame (no stack)
void sub_4BCB20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004bcb20
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 0);
    v0 = v0 ^ a1;
    v0 = sltiu(v0, 1);
}


// sub_4BCB30 [mipKLTextureCallBack] -- the texture callback of the K / L pass: every world sector visited for the texture; with any density the texture's K value set from its logarithm (sub_4D8320)
// 0x004BCB30 sub_4BCB30 -- 188 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
void sub_4BCB30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x004bcb30
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    s1 = a0;
    swc1(f20, sp, 0x0);
    s0 = a1;
    sw(s1, a1, 8);
    a2 = s0;
    sw(zero, a1, 12);
    sw(zero, a1, 16);
    lw(a0, a1, 4);
    a1 = 0x4C0000;
    a1 = addiu(a1, -13600);  // &sub_4BCAE0
    jal(ctx, 0x4BCB64u, gen::fn_worldForAllSectors_0049a870);
    lw(v0, s0, 16);
    if (i64(v0) > 0) {
        // 0x004bcb80
        charge(ctx, 21);
        mtc1(v0, f1);
        lwc1(f0, s0, 12);
        cvt_s_w(f1, f1);
        div_s(f12, f0, f1);
        jal(ctx, 0x4BCB98u, gen::fn_logf_0052ea30);
        v0 = 0x40000000;
        mtc1(v0, f12);
        mov_s(f20, f0);
        jal(ctx, 0x4BCBA8u, gen::fn_logf_0052ea30);
        div_s(f0, f20, f0);
        a0 = s1;
        neg_s(f12, f0);
        jal(ctx, 0x4BCBC4u, gen::fn_sub_4D8320_004d8320);
        backedge(ctx);
    }
    // 0x004bcb78
    charge(ctx, 2);
    v0 = s1;
    // 0x004bcbd4
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lwc1(f20, sp, 0x0);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x40);
}


// sub_4BCBF0 [RpMipmapKLWorldCalculate] -- computes the mipmap K / L values of a world's textures: for mipmapped rasters (flags 0x84) every texture of the current dictionary visited (sub_4BCB30)
// 0x004BCBF0 sub_4BCBF0 -- 212 bytes; frame 0x70: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4BCBF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x004bcbf0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(a1, a0, 8);
    a0 = 0x1000000;
    v1 = a1 & a0;
    if (v1 != a0) {
        // 0x004bcc1c
        charge(ctx, 3);
        v1 = a1 & 0x84;
        if (v1 != 0) {
            // 0x004bcc28
            charge(ctx, 27);
            jal(ctx, 0x4BCC28u, gen::fn_sub_4CA5B0_004ca5b0);
            a1 = v0;
            a0 = addiu(sp, 0x30);
            jal(ctx, 0x4BCC34u, gen::fn_sub_4CA560_004ca560);
            lwc1(f1, s0, 104);
            v0 = 0x40000000;
            lwc1(f0, s0, 108);
            lw(v1, sp, 0x30);
            mtc1(v0, f2);
            lw(v0, sp, 0x34);
            mul_s(f1, f2, f1);
            mul_s(f0, f2, f0);
            mul_s(f1, f1, f0);
            mult(v0, v1, v0);
            sw(s1, sp, 0x54);
            sw(zero, sp, 0x50);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            div_s(f0, f0, f1);
            link(ctx, 0x4BCC84u);  // $ra first: the delay slot below depends on it
            swc1(f0, sp, 0x64);
            call(ctx, gen::fn_sub_4D11F0_004d11f0);
            if (v0 != 0) {
                // 0x004bcc94
                charge(ctx, 7);
                jal(ctx, 0x4BCC94u, gen::fn_sub_4D11F0_004d11f0);
                a1 = 0x4C0000;
                a0 = v0;
                a1 = addiu(a1, -13520);  // &sub_4BCB30
                a2 = addiu(sp, 0x50);
                jal(ctx, 0x4BCCA8u, gen::fn_sub_4D0DC0_004d0dc0);
            }
        }
    }
    // 0x004bccb0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}


// sub_4BDB30 [quatFromMatrixX] -- the matrix-to-quaternion case of a dominant x diagonal: x = sqrt(1 + xx - yy - zz) / 2, the other components from the off-diagonals
// 0x004BDB30 sub_4BDB30 -- 124 bytes; leaf frame (no stack)
void sub_4BDB30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8};
    // 0x004bdb30
    enter(ctx, 31);  // entry check point + this block's cycles
    lwc1(f8, a1, 20);
    v0 = 0x3F800000;
    lwc1(f7, a1, 40);
    mtc1(v0, f5);
    lwc1(f6, a1, 0);
    v0 = 0x3F000000;
    mtc1(v0, f4);
    lwc1(f3, a1, 24);
    add_s(f7, f8, f7);
    v0 = a0;
    lwc1(f2, a1, 36);
    sub_s(f6, f6, f7);
    add_s(f5, f5, f6);
    sub_s(f2, f3, f2);
    sqrt_s(f3, f5);
    lwc1(f1, a1, 4);
    lwc1(f0, a1, 16);
    add_s(f0, f1, f0);
    mul_s(f1, f4, f3);
    div_s(f3, f4, f3);
    swc1(f1, a0, 0);
    mul_s(f1, f3, f2);
    swc1(f1, a0, 12);
    mul_s(f0, f3, f0);
    swc1(f0, a0, 4);
    lwc1(f1, a1, 8);
    lwc1(f0, a1, 32);
    add_s(f0, f1, f0);
    mul_s(f0, f3, f0);
    swc1(f0, a0, 8);
}


// sub_4BDBB0 [quatFromMatrixY] -- the matrix-to-quaternion case of a dominant y diagonal
// 0x004BDBB0 sub_4BDBB0 -- 124 bytes; leaf frame (no stack)
void sub_4BDBB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8};
    // 0x004bdbb0
    enter(ctx, 31);  // entry check point + this block's cycles
    lwc1(f8, a1, 40);
    v0 = 0x3F800000;
    lwc1(f7, a1, 0);
    mtc1(v0, f5);
    lwc1(f6, a1, 20);
    v0 = 0x3F000000;
    mtc1(v0, f4);
    lwc1(f3, a1, 32);
    add_s(f7, f8, f7);
    v0 = a0;
    lwc1(f2, a1, 8);
    sub_s(f6, f6, f7);
    add_s(f5, f5, f6);
    sub_s(f2, f3, f2);
    sqrt_s(f3, f5);
    lwc1(f1, a1, 24);
    lwc1(f0, a1, 36);
    add_s(f0, f1, f0);
    mul_s(f1, f4, f3);
    div_s(f3, f4, f3);
    swc1(f1, a0, 4);
    mul_s(f1, f3, f2);
    swc1(f1, a0, 12);
    mul_s(f0, f3, f0);
    swc1(f0, a0, 8);
    lwc1(f1, a1, 16);
    lwc1(f0, a1, 4);
    add_s(f0, f1, f0);
    mul_s(f0, f3, f0);
    swc1(f0, a0, 0);
}


// sub_4BDC30 [quatFromMatrixZ] -- the matrix-to-quaternion case of a dominant z diagonal
// 0x004BDC30 sub_4BDC30 -- 124 bytes; leaf frame (no stack)
void sub_4BDC30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8};
    // 0x004bdc30
    enter(ctx, 31);  // entry check point + this block's cycles
    lwc1(f8, a1, 0);
    v0 = 0x3F800000;
    lwc1(f7, a1, 20);
    mtc1(v0, f5);
    lwc1(f6, a1, 40);
    v0 = 0x3F000000;
    mtc1(v0, f4);
    lwc1(f3, a1, 4);
    add_s(f7, f8, f7);
    v0 = a0;
    lwc1(f2, a1, 16);
    sub_s(f6, f6, f7);
    add_s(f5, f5, f6);
    sub_s(f2, f3, f2);
    sqrt_s(f3, f5);
    lwc1(f1, a1, 32);
    lwc1(f0, a1, 8);
    add_s(f0, f1, f0);
    mul_s(f1, f4, f3);
    div_s(f3, f4, f3);
    swc1(f1, a0, 8);
    mul_s(f1, f3, f2);
    swc1(f1, a0, 12);
    mul_s(f0, f3, f0);
    swc1(f0, a0, 0);
    lwc1(f1, a1, 36);
    lwc1(f0, a1, 24);
    add_s(f0, f1, f0);
    mul_s(f0, f3, f0);
    swc1(f0, a0, 4);
}


// sub_4BDCB0 [RtQuatConvertFromMatrix] -- converts a rotation matrix to a quaternion: a positive trace directly (w = sqrt(trace + 1) / 2), else the case of the largest diagonal element (sub_4BDB30 / sub_4BDBB0 / sub_4BDC30)
// ($a0 = the quaternion, $a1 = the matrix) Returns 1, or 0 for a null argument.
// 0x004BDCB0 sub_4BDCB0 -- 292 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4BDCB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6};
    // 0x004bdcb0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = sltu(0, a0);
    if (s0 != 0) {
        // 0x004bdcc8
        charge(ctx, 1);
        s0 = sltu(0, a1);
    }
    // 0x004bdccc
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x004bdcd4
        charge(ctx, 9);
        lwc1(f5, a1, 20);
        lwc1(f4, a1, 0);
        lwc1(f3, a1, 40);
        mtc1(zero, f0);
        add_s(f1, f4, f5);
        add_s(f2, f3, f1);
        c_le_s(f2, f0);
        if (!cond(ctx)) {
            // 0x004bdd5c
            charge(ctx, 26);
            v1 = 0x3F800000;
            v0 = 0x3F000000;
            mtc1(v1, f0);
            mtc1(v0, f1);
            add_s(f0, f0, f2);
            sqrt_s(f2, f0);
            div_s(f6, f1, f2);
            mul_s(f0, f1, f2);
            swc1(f0, a0, 12);
            lwc1(f5, a1, 24);
            lwc1(f4, a1, 36);
            lwc1(f1, a1, 4);
            lwc1(f0, a1, 16);
            lwc1(f3, a1, 32);
            lwc1(f2, a1, 8);
            sub_s(f4, f5, f4);
            sub_s(f0, f1, f0);
            mul_s(f1, f6, f4);
            sub_s(f2, f3, f2);
            swc1(f1, a0, 0);
            mul_s(f1, f6, f2);
            mul_s(f0, f6, f0);
            swc1(f1, a0, 4);
            swc1(f0, a0, 8);
            backedge(ctx);
        } else {
            // 0x004bdcf8
            charge(ctx, 3);
            c_le_s(f4, f5);
            if (cond(ctx)) {
                // 0x004bdd2c
                charge(ctx, 3);
                c_le_s(f5, f3);
                if (cond(ctx)) {
                    // 0x004bdd44
                    charge(ctx, 2);
                    v0 = 0x4C0000;
                    v0 = addiu(v0, -9168);  // &sub_4BDC30
                } else {
                    // 0x004bdd38
                    charge(ctx, 3);
                    v0 = 0x4C0000;
                    v0 = addiu(v0, -9296);  // &sub_4BDBB0
                }
            } else {
                // 0x004bdd04
                charge(ctx, 3);
                c_le_s(f4, f3);
                if (cond(ctx)) {
                    // 0x004bdd1c
                    charge(ctx, 2);
                    v0 = 0x4C0000;
                    v0 = addiu(v0, -9168);  // &sub_4BDC30
                } else {
                    // 0x004bdd10
                    charge(ctx, 3);
                    v0 = 0x4C0000;
                    v0 = addiu(v0, -9424);  // &sub_4BDB30
                }
                // 0x004bdd24
                charge(ctx, 2);
            }
            // 0x004bdd4c
            charge(ctx, 2);
            jalr(ctx, 0x4BDD4Cu, v0.u());
        }
    }
    // 0x004bdd54
    charge(ctx, 2);
    v0 = s0;
    // 0x004bddc4
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4BDDE0 [RtQuatRotate] -- rotates a quaternion by $f12 degrees about an axis: the axis quaternion (sin / cos of the half angle, the axis normalised) replaces, pre- or post-multiplies it by the combine type
// ($a0 = the quaternion, $a1 = the axis, $a2 = 0 replace / 1 pre-concat / 2 post-concat) Other types: 'Invalid
// combination type' (error); returns the quaternion, or 0.
// 0x004BDDE0 sub_4BDDE0 -- 1024 bytes; frame 0xA0: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
void sub_4BDDE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f12{ctx, 12}, f20{ctx, 20};
    // 0x004bdde0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    s1 = a0;
    swc1(f20, sp, 0x0);
    s0 = a1;
    if (s1 != 0) {
        // 0x004bde04
        charge(ctx, 2);
        if (s0 == 0) {
            goto L_004be19c;
        }
        // 0x004bde0c
        charge(ctx, 3);
        v0 = 2;
        if (a2 == v0) {
            // 0x004be000
            charge(ctx, 91);
            v0 = 0x3C0E0000;
            v0 = v0 | 0xFA35;
            mtc1(v0, f0);
            lwc1(f1, s1, 4);
            mul_s(f20, f0, f12);
            swc1(f1, sp, 0x54);
            lwc1(f2, s1, 0);
            lwc1(f1, s1, 8);
            lwc1(f0, s1, 12);
            mov_s(f12, f20);
            swc1(f2, sp, 0x50);
            swc1(f1, sp, 0x58);
            link(ctx, 0x4BE030u);  // $ra first: the delay slot below depends on it
            swc1(f0, sp, 0x5C);
            call(ctx, gen::fn_sinf_0052e878);
            mov_s(f12, f20);
            s2 = addiu(sp, 0x6C);
            mov_s(f20, f0);
            jal(ctx, 0x4BE040u, gen::fn_cosf_0052e6d8);
            swc1(f0, s2, 0);
            a1 = s0;
            a0 = addiu(sp, 0x60);
            jal(ctx, 0x4BE050u, gen::fn_sub_4C69F0_004c69f0);
            v1 = addiu(sp, 0x64);
            v0 = addiu(sp, 0x68);
            lwc1(f7, v1, 0);
            lwc1(f8, sp, 0x60);
            lwc1(f2, v0, 0);
            lwc1(f0, sp, 0x5C);
            lwc1(f1, s2, 0);
            lwc1(f6, sp, 0x54);
            mul_s(f7, f7, f20);
            mul_s(f8, f8, f20);
            mul_s(f2, f2, f20);
            lwc1(f4, sp, 0x50);
            mula_s(f7, f6);
            lwc1(f5, sp, 0x58);
            mul_s(f1, f1, f0);
            madda_s(f8, f4);
            swc1(f2, v0, 0);
            madd_s(f2, f2, f5);
            sub_s(f1, f1, f2);
            swc1(f8, sp, 0x60);
            swc1(f7, v1, 0);
            swc1(f1, s1, 12);
            lwc1(f1, v1, 0);
            lwc1(f2, v0, 0);
            mtc1(zero, f3);
            mula_s(f1, f5);
            msub_s(f1, f2, f6);
            swc1(f1, s1, 0);
            lwc1(f1, v0, 0);
            lwc1(f2, sp, 0x60);
            mula_s(f1, f4);
            msub_s(f1, f2, f5);
            swc1(f1, s1, 4);
            lwc1(f1, sp, 0x60);
            lwc1(f2, v1, 0);
            mula_s(f1, f6);
            msub_s(f1, f2, f4);
            swc1(f1, s1, 8);
            lwc1(f1, s1, 0);
            lwc1(f2, s2, 0);
            adda_s(f3, f1);
            madd_s(f1, f4, f2);
            swc1(f1, s1, 0);
            lwc1(f1, s1, 4);
            lwc1(f2, s2, 0);
            adda_s(f3, f1);
            madd_s(f1, f6, f2);
            swc1(f1, s1, 4);
            lwc1(f1, s1, 8);
            lwc1(f2, s2, 0);
            adda_s(f3, f1);
            madd_s(f1, f5, f2);
            swc1(f1, s1, 8);
            lwc1(f1, s1, 0);
            lwc1(f2, sp, 0x60);
            adda_s(f3, f1);
            madd_s(f1, f2, f0);
            swc1(f1, s1, 0);
            lwc1(f1, s1, 4);
            lwc1(f2, v1, 0);
            adda_s(f3, f1);
            madd_s(f1, f2, f0);
            swc1(f1, s1, 4);
            lwc1(f1, s1, 8);
            lwc1(f2, v0, 0);
            adda_s(f3, f1);
            madd_s(f0, f2, f0);
            swc1(f0, s1, 8);
        } else {
            // 0x004bde18
            charge(ctx, 3);
            v0 = 1;
            if (a2 == v0) {
                // 0x004bde94
                charge(ctx, 91);
                v0 = 0x3C0E0000;
                v0 = v0 | 0xFA35;
                mtc1(v0, f0);
                lwc1(f1, s1, 4);
                mul_s(f20, f0, f12);
                swc1(f1, sp, 0x74);
                lwc1(f2, s1, 0);
                lwc1(f1, s1, 8);
                lwc1(f0, s1, 12);
                mov_s(f12, f20);
                swc1(f2, sp, 0x70);
                swc1(f1, sp, 0x78);
                link(ctx, 0x4BDEC4u);  // $ra first: the delay slot below depends on it
                swc1(f0, sp, 0x7C);
                call(ctx, gen::fn_sinf_0052e878);
                mov_s(f12, f20);
                s2 = addiu(sp, 0x8C);
                mov_s(f20, f0);
                jal(ctx, 0x4BDED4u, gen::fn_cosf_0052e6d8);
                swc1(f0, s2, 0);
                a1 = s0;
                a0 = addiu(sp, 0x80);
                jal(ctx, 0x4BDEE4u, gen::fn_sub_4C69F0_004c69f0);
                v1 = addiu(sp, 0x84);
                v0 = addiu(sp, 0x88);
                lwc1(f7, v1, 0);
                lwc1(f8, sp, 0x80);
                lwc1(f2, v0, 0);
                lwc1(f5, sp, 0x7C);
                lwc1(f1, s2, 0);
                lwc1(f6, sp, 0x74);
                mul_s(f7, f7, f20);
                mul_s(f8, f8, f20);
                mul_s(f2, f2, f20);
                lwc1(f4, sp, 0x70);
                mula_s(f6, f7);
                lwc1(f0, sp, 0x78);
                mul_s(f1, f5, f1);
                madda_s(f4, f8);
                swc1(f2, v0, 0);
                madd_s(f2, f0, f2);
                sub_s(f1, f1, f2);
                swc1(f8, sp, 0x80);
                swc1(f7, v1, 0);
                swc1(f1, s1, 12);
                lwc1(f1, v0, 0);
                lwc1(f2, v1, 0);
                mtc1(zero, f3);
                mula_s(f6, f1);
                msub_s(f1, f0, f2);
                swc1(f1, s1, 0);
                lwc1(f1, sp, 0x80);
                lwc1(f2, v0, 0);
                mula_s(f0, f1);
                msub_s(f1, f4, f2);
                swc1(f1, s1, 4);
                lwc1(f1, v1, 0);
                lwc1(f2, sp, 0x80);
                mula_s(f4, f1);
                msub_s(f1, f6, f2);
                swc1(f1, s1, 8);
                lwc1(f1, s1, 0);
                lwc1(f2, sp, 0x80);
                adda_s(f3, f1);
                madd_s(f1, f2, f5);
                swc1(f1, s1, 0);
                lwc1(f1, s1, 4);
                lwc1(f2, v1, 0);
                adda_s(f3, f1);
                madd_s(f1, f2, f5);
                swc1(f1, s1, 4);
                lwc1(f1, s1, 8);
                lwc1(f2, v0, 0);
                adda_s(f3, f1);
                madd_s(f1, f2, f5);
                swc1(f1, s1, 8);
                lwc1(f1, s1, 0);
                lwc1(f2, s2, 0);
                adda_s(f3, f1);
                madd_s(f1, f4, f2);
                swc1(f1, s1, 0);
                lwc1(f1, s1, 4);
                lwc1(f2, s2, 0);
                adda_s(f3, f1);
                madd_s(f1, f6, f2);
                swc1(f1, s1, 4);
                lwc1(f1, s1, 8);
                lwc1(f2, s2, 0);
                adda_s(f3, f1);
                madd_s(f0, f0, f2);
                swc1(f0, s1, 8);
            } else {
                // 0x004bde24
                charge(ctx, 2);
                if (a2 == 0) {
                    // 0x004bde34
                    charge(ctx, 24);
                    v0 = 0x3C0E0000;
                    v0 = v0 | 0xFA35;
                    mtc1(v0, f0);
                    mul_s(f20, f0, f12);
                    mov_s(f12, f20);
                    jal(ctx, 0x4BDE48u, gen::fn_sinf_0052e878);
                    mov_s(f12, f20);
                    mov_s(f20, f0);
                    jal(ctx, 0x4BDE54u, gen::fn_cosf_0052e6d8);
                    swc1(f0, s1, 12);
                    a1 = s0;
                    a0 = s1;
                    jal(ctx, 0x4BDE64u, gen::fn_sub_4C69F0_004c69f0);
                    lwc1(f0, s1, 0);
                    mul_s(f0, f0, f20);
                    swc1(f0, s1, 0);
                    lwc1(f0, s1, 4);
                    mul_s(f0, f0, f20);
                    swc1(f0, s1, 4);
                    lwc1(f0, s1, 8);
                    mul_s(f0, f0, f20);
                    swc1(f0, s1, 8);
                } else {
                    // 0x004bde2c
                    charge(ctx, 2);
                    v1 = 405;
                    // 0x004be16c
                    charge(ctx, 10);
                    v0 = lui(0x8000);
                    a1 = 0x780000;
                    sw(v1, sp, 0x98);
                    a0 = v0 | 0x3;
                    a1 = addiu(a1, -6768);  // "Invalid combination type"
                    jal(ctx, 0x4BE17Cu, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0x9C);
                    a0 = addiu(sp, 0x98);
                    jal(ctx, 0x4BE188u, gen::fn_sub_4C1C50_004c1c50);
                    s1 = 0;
                }
            }
        }
        goto L_004be194;
    }
L_004be19c:
    charge(ctx, 10);
    v1 = 405;
    v0 = lui(0x8000);
    sw(v1, sp, 0x90);
    a0 = v0 | 0x16;
    jal(ctx, 0x4BE1A8u, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0x94);
    a0 = addiu(sp, 0x90);
    jal(ctx, 0x4BE1B4u, gen::fn_sub_4C1C50_004c1c50);
    s1 = 0;
    backedge(ctx);
L_004be194:
    charge(ctx, 2);
    v0 = s1;
    // 0x004be1c4
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lwc1(f20, sp, 0x0);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0xA0);
}


// sub_4BE1E0 [RtQuatTransformVectors] -- rotates $a2 vectors by a unit quaternion: v' = v (w^2 - |q|^2) + 2 (q.v) q + 2 w (q x v), from $a1 into $a0
// 0x004BE1E0 sub_4BE1E0 -- 300 bytes; frame 0x10
void sub_4BE1E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16};
    // 0x004be1e0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    at = slt(0, a2);
    lwc1(f4, a3, 12);
    t1 = a0;
    lwc1(f13, a3, 4);
    t0 = 0;
    lwc1(f12, a3, 0);
    lwc1(f11, a3, 8);
    mul_s(f0, f4, f4);
    mula_s(f13, f13);
    madda_s(f12, f12);
    madd_s(f1, f11, f11);
    sub_s(f3, f0, f1);
    add_s(f0, f12, f12);
    add_s(f1, f13, f13);
    add_s(f2, f11, f11);
    mul_s(f14, f0, f4);
    mul_s(f15, f1, f4);
    mul_s(f16, f2, f4);
    if (at != 0) {
        // 0x004be230
        charge(ctx, 3);
        mtc1(zero, f7);
        a3 = addiu(sp, 0x4);
        v1 = addiu(sp, 0x8);
        for (;;) {
            // 0x004be23c
            charge(ctx, 49);
            lwc1(f10, a1, 4);
            t0 = addiu(t0, 1);
            lwc1(f8, a1, 0);
            v0 = slt(t0, a2);
            lwc1(f9, a1, 8);
            mula_s(f1, f10);
            madda_s(f0, f8);
            madd_s(f6, f2, f9);
            a1 = addiu(a1, 12);
            mula_s(f15, f9);
            msub_s(f4, f16, f10);
            swc1(f4, sp, 0x0);
            swc1(f4, t1, 0);
            mula_s(f16, f8);
            msub_s(f4, f14, f9);
            swc1(f4, a3, 0);
            mula_s(f14, f10);
            msub_s(f4, f15, f8);
            lwc1(f5, sp, 0x4);
            swc1(f4, v1, 0);
            lwc1(f4, sp, 0x8);
            swc1(f5, t1, 4);
            swc1(f4, t1, 8);
            lwc1(f4, t1, 0);
            adda_s(f7, f4);
            madd_s(f4, f12, f6);
            swc1(f4, t1, 0);
            lwc1(f4, t1, 4);
            adda_s(f7, f4);
            madd_s(f4, f13, f6);
            swc1(f4, t1, 4);
            lwc1(f4, t1, 8);
            adda_s(f7, f4);
            madd_s(f4, f11, f6);
            swc1(f4, t1, 8);
            lwc1(f4, t1, 0);
            adda_s(f7, f4);
            madd_s(f4, f8, f3);
            swc1(f4, t1, 0);
            lwc1(f4, t1, 4);
            adda_s(f7, f4);
            madd_s(f4, f10, f3);
            swc1(f4, t1, 4);
            lwc1(f4, t1, 8);
            adda_s(f7, f4);
            madd_s(f4, f9, f3);
            swc1(f4, t1, 8);
            t1 = addiu(t1, 12);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004be300 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = a0;
    sp = addiu(sp, 0x10);
}


// sub_4BE310 [RtQuatSetupSlerpCache] -- sets up a slerp cache: the start quaternion (+0), the end one (+16, negated when the dot product is negative), the angle (+32, acos of |dot| by polynomial), the 'nearly equal' flag (+36)
// When |dot| < 0.99999 both quaternions are divided by sin(angle) (a polynomial sine) for the interpolation.
// 0x004BE310 sub_4BE310 -- 1568 bytes; frame 0x10
void sub_4BE310(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17};
    // 0x004be310
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    lwc1(f4, a0, 0);
    lwc1(f3, a0, 4);
    lwc1(f2, a0, 8);
    lwc1(f1, a0, 12);
    mtc1(zero, f0);
    swc1(f4, a2, 0);
    swc1(f3, a2, 4);
    swc1(f2, a2, 8);
    swc1(f1, a2, 12);
    lwc1(f2, a0, 4);
    lwc1(f1, a1, 4);
    lwc1(f4, a0, 0);
    lwc1(f3, a1, 0);
    lwc1(f6, a0, 8);
    lwc1(f5, a1, 8);
    lwc1(f8, a1, 12);
    mula_s(f2, f1);
    lwc1(f7, a0, 12);
    madda_s(f4, f3);
    madda_s(f6, f5);
    madd_s(f1, f7, f8);
    c_lt_s(f1, f0);
    if (!cond(ctx)) {
        // 0x004be3d0
        charge(ctx, 6);
        v1 = 0x3F800000;
        mtc1(v1, f0);
        c_le_s(f1, f0);
        if (cond(ctx)) {
            // 0x004be3f0
            charge(ctx, 2);
            mov_s(f0, f1);
            lwc1(f4, a1, 0);
        } else {
            // 0x004be3e8
            charge(ctx, 2);
            lwc1(f4, a1, 0);
        }
        // 0x004be3f8
        charge(ctx, 7);
        lwc1(f3, a1, 4);
        lwc1(f2, a1, 8);
        lwc1(f1, a1, 12);
        swc1(f4, a2, 16);
        swc1(f3, a2, 20);
        swc1(f2, a2, 24);
        swc1(f1, a2, 28);
    } else {
        // 0x004be374
        charge(ctx, 6);
        v1 = lui(0xBF80);
        mtc1(v1, f0);
        c_lt_s(f1, f0);
        if (!cond(ctx)) {
            // 0x004be39c
            charge(ctx, 2);
            neg_s(f0, f1);
            neg_s(f1, f8);
        } else {
            // 0x004be38c
            charge(ctx, 4);
            v1 = 0x3F800000;
            mtc1(v1, f0);
            neg_s(f1, f8);
        }
        // 0x004be3a4
        charge(ctx, 11);
        swc1(f1, a2, 28);
        lwc1(f1, a1, 0);
        neg_s(f1, f1);
        swc1(f1, a2, 16);
        lwc1(f1, a1, 4);
        neg_s(f1, f1);
        swc1(f1, a2, 20);
        lwc1(f1, a1, 8);
        neg_s(f1, f1);
        swc1(f1, a2, 24);
    }
    // 0x004be414
    charge(ctx, 8);
    swc1(f0, sp, 0xC);
    at = 0x3F800000;
    lw(a0, sp, 0xC);
    v1 = dsll32(a0, 1);
    v1 = dsrl32(v1, 1);
    at = slt(v1, at);
    if (at == 0) {
        // 0x004be5a8
        charge(ctx, 2);
        if (i64(a0) <= 0) {
            // 0x004be5b8
            charge(ctx, 4);
            v1 = 0x40490000;
            v1 = v1 | 0xFDB;
            sw(v1, a2, 32);
            backedge(ctx);
        } else {
            // 0x004be5b0
            charge(ctx, 2);
            sw(zero, a2, 32);
            backedge(ctx);
        }
    } else {
        // 0x004be434
        charge(ctx, 4);
        at = 0x3F000000;
        at = slt(v1, at);
        if (at == 0) {
            // 0x004be5c8
            charge(ctx, 2);
            if (i64(a0) < 0) {
                // 0x004be708
                charge(ctx, 73);
                v1 = 0x3F000000;
                a0 = 0x3F800000;
                mtc1(v1, f15);
                mtc1(a0, f16);
                v1 = 0x38110000;
                v1 = v1 | 0xEF08;
                mtc1(v1, f14);
                add_s(f12, f16, f0);
                v1 = 0x3A4F0000;
                a0 = v1 | 0x7F04;
                v1 = lui(0xBD24);
                v1 = v1 | 0x1146;
                mtc1(v1, f11);
                mtc1(a0, f13);
                v1 = 0x3E4E0000;
                a0 = v1 | 0xAA8;
                v1 = lui(0xBEA6);
                v1 = v1 | 0xB090;
                mtc1(v1, f9);
                mtc1(a0, f10);
                mul_s(f15, f15, f12);
                v1 = 0x3E2A0000;
                a0 = v1 | 0xAAAB;
                v1 = 0x3D9D0000;
                v1 = v1 | 0xC62E;
                mtc1(v1, f7);
                mtc1(zero, f12);
                mtc1(a0, f8);
                v1 = lui(0xBF30);
                adda_s(f12, f13);
                a0 = v1 | 0x3361;
                v1 = 0x40010000;
                madd_s(f13, f14, f15);
                v1 = v1 | 0x572D;
                adda_s(f12, f11);
                mtc1(v1, f5);
                madd_s(f11, f15, f13);
                adda_s(f12, f10);
                v1 = lui(0xC019);
                mtc1(a0, f6);
                madd_s(f10, f15, f11);
                a0 = v1 | 0xD139;
                adda_s(f12, f9);
                v1 = 0x33A20000;
                madd_s(f9, f15, f10);
                v1 = v1 | 0x2168;
                adda_s(f12, f8);
                madd_s(f8, f15, f9);
                mtc1(v1, f3);
                adda_s(f12, f6);
                v1 = 0x40000000;
                madd_s(f6, f7, f15);
                mtc1(v1, f2);
                adda_s(f12, f5);
                v1 = 0x40490000;
                v1 = v1 | 0xFDA;
                mtc1(a0, f4);
                madd_s(f5, f15, f6);
                adda_s(f12, f4);
                madd_s(f4, f15, f5);
                adda_s(f12, f16);
                mul_s(f8, f15, f8);
                mtc1(v1, f1);
                madd_s(f4, f15, f4);
                adda_s(f12, f1);
                sqrt_s(f17, f15);
                div_s(f1, f8, f4);
                mul_s(f1, f1, f17);
                sub_s(f1, f1, f3);
                add_s(f1, f17, f1);
                msub_s(f1, f2, f1);
                swc1(f1, a2, 32);
                backedge(ctx);
            } else {
                // 0x004be5d0
                charge(ctx, 78);
                a0 = 0x3F800000;
                v1 = 0x3F000000;
                mtc1(a0, f14);
                mtc1(v1, f13);
                a0 = 0x38110000;
                a1 = a0 | 0xEF08;
                v1 = si(-4096);
                a0 = 0x3A4F0000;
                a0 = a0 | 0x7F04;
                mtc1(a0, f11);
                sub_s(f10, f14, f0);
                a0 = lui(0xBD24);
                mul_s(f13, f13, f10);
                mtc1(a1, f12);
                mtc1(zero, f10);
                a1 = a0 | 0x1146;
                a0 = 0x3E4E0000;
                a0 = a0 | 0xAA8;
                mtc1(a0, f8);
                adda_s(f10, f11);
                sqrt_s(f15, f13);
                a0 = lui(0xBEA6);
                mtc1(a1, f9);
                madd_s(f11, f12, f13);
                a1 = a0 | 0xB090;
                a0 = 0x3E2A0000;
                a0 = a0 | 0xAAAB;
                mtc1(a0, f7);
                adda_s(f10, f9);
                madd_s(f9, f13, f11);
                a0 = 0x3D9D0000;
                mtc1(a1, f4);
                adda_s(f10, f8);
                a1 = a0 | 0xC62E;
                a0 = lui(0xBF30);
                a0 = a0 | 0x3361;
                madd_s(f8, f13, f9);
                mtc1(a0, f5);
                adda_s(f10, f4);
                madd_s(f8, f13, f8);
                a0 = 0x40010000;
                mtc1(a1, f6);
                adda_s(f10, f7);
                a1 = a0 | 0x572D;
                madd_s(f7, f13, f8);
                a0 = lui(0xC019);
                adda_s(f10, f5);
                a0 = a0 | 0xD139;
                mtc1(a0, f2);
                mtc1(a1, f3);
                madd_s(f5, f6, f13);
                a0 = 0x40000000;
                adda_s(f10, f3);
                madd_s(f3, f13, f5);
                adda_s(f10, f2);
                madd_s(f2, f13, f3);
                adda_s(f10, f14);
                madd_s(f2, f13, f2);
                mul_s(f7, f13, f7);
                div_s(f5, f7, f2);
                mtc1(a0, f1);
                swc1(f15, sp, 0x8);
                lw(a0, sp, 0x8);
                adda_s(f10, f13);
                v1 = a0 & v1;
                sw(v1, sp, 0x4);
                lwc1(f4, sp, 0x4);
                add_s(f2, f15, f4);
                msub_s(f3, f4, f4);
                div_s(f2, f3, f2);
                adda_s(f10, f2);
                madd_s(f2, f5, f15);
                add_s(f2, f4, f2);
                mul_s(f1, f1, f2);
                swc1(f1, a2, 32);
                backedge(ctx);
            }
        } else {
            // 0x004be444
            charge(ctx, 5);
            at = 0x23000000;
            at = at | 0x1;
            at = slt(v1, at);
            if (at == 0) {
                // 0x004be468
                charge(ctx, 66);
                v1 = 0x38110000;
                a0 = v1 | 0xEF08;
                v1 = 0x3A4F0000;
                t0 = v1 | 0x7F04;
                v1 = lui(0xBD24);
                a1 = v1 | 0x1146;
                v1 = 0x3E4E0000;
                a3 = v1 | 0xAA8;
                mtc1(a0, f14);
                v1 = lui(0xBEA6);
                mul_s(f15, f0, f0);
                a0 = v1 | 0xB090;
                v1 = 0x3E2A0000;
                mtc1(a1, f11);
                mtc1(t0, f13);
                a1 = v1 | 0xAAAB;
                mtc1(zero, f12);
                v1 = 0x3D9D0000;
                mtc1(a0, f9);
                adda_s(f12, f13);
                a0 = v1 | 0xC62E;
                v1 = lui(0xBF30);
                madd_s(f13, f14, f15);
                v1 = v1 | 0x3361;
                adda_s(f12, f11);
                mtc1(v1, f6);
                mtc1(a3, f10);
                madd_s(f11, f15, f13);
                v1 = 0x40010000;
                mtc1(a0, f7);
                adda_s(f12, f10);
                a0 = v1 | 0x572D;
                madd_s(f10, f15, f11);
                v1 = lui(0xC019);
                adda_s(f12, f9);
                v1 = v1 | 0xD139;
                mtc1(v1, f4);
                mtc1(a1, f8);
                madd_s(f9, f15, f10);
                v1 = 0x3F800000;
                adda_s(f12, f8);
                madd_s(f8, f15, f9);
                adda_s(f12, f6);
                mtc1(v1, f3);
                mtc1(a0, f5);
                madd_s(f6, f7, f15);
                v1 = 0x33A20000;
                a0 = v1 | 0x2168;
                adda_s(f12, f5);
                v1 = 0x3FC90000;
                madd_s(f5, f15, f6);
                v1 = v1 | 0xFDA;
                adda_s(f12, f4);
                madd_s(f4, f15, f5);
                adda_s(f12, f3);
                mul_s(f8, f15, f8);
                mtc1(a0, f2);
                madd_s(f3, f15, f4);
                adda_s(f12, f2);
                div_s(f2, f8, f3);
                msub_s(f2, f0, f2);
                sub_s(f2, f0, f2);
                mtc1(v1, f1);
                sub_s(f1, f1, f2);
                swc1(f1, a2, 32);
            } else {
                // 0x004be458
                charge(ctx, 4);
                v1 = 0x3FC90000;
                v1 = v1 | 0xFDB;
                sw(v1, a2, 32);
            }
        }
    }
    // 0x004be570
    charge(ctx, 7);
    v1 = 0x3F7F0000;
    v1 = v1 | 0xFF58;
    mtc1(v1, f1);
    c_lt_s(f0, f1);
    a0 = 1;
    if (cond(ctx)) {
        // 0x004be58c
        charge(ctx, 1);
        a0 = 0;
    }
    // 0x004be590
    charge(ctx, 4);
    sw(a0, a2, 36);
    lw(v1, a2, 36);
    if (v1 == 0) {
        // 0x004be82c
        charge(ctx, 63);
        lwc1(f10, a2, 32);
        v1 = 0x2F2E0000;
        a0 = v1 | 0xC9D3;
        v1 = lui(0xB2D7);
        v1 = v1 | 0x2F34;
        mtc1(v1, f7);
        mtc1(a0, f8);
        v1 = 0x36380000;
        a0 = v1 | 0xEF1B;
        mul_s(f9, f10, f10);
        v1 = lui(0xB950);
        v1 = v1 | 0xD01;
        mtc1(zero, f6);
        mtc1(v1, f4);
        adda_s(f6, f7);
        mtc1(a0, f5);
        v1 = 0x3C080000;
        madd_s(f7, f8, f9);
        a0 = v1 | 0x8889;
        adda_s(f6, f5);
        v1 = lui(0xBE2A);
        madd_s(f5, f9, f7);
        v1 = v1 | 0xAAAB;
        adda_s(f6, f4);
        mtc1(v1, f2);
        mtc1(a0, f3);
        madd_s(f4, f9, f5);
        v1 = 0x3F800000;
        adda_s(f6, f3);
        madd_s(f3, f9, f4);
        adda_s(f6, f2);
        madd_s(f2, f9, f3);
        mul_s(f1, f9, f10);
        adda_s(f6, f10);
        mtc1(v1, f0);
        madd_s(f1, f1, f2);
        div_s(f1, f0, f1);
        lwc1(f0, a2, 12);
        mul_s(f0, f0, f1);
        swc1(f0, a2, 12);
        lwc1(f0, a2, 0);
        mul_s(f0, f0, f1);
        swc1(f0, a2, 0);
        lwc1(f0, a2, 4);
        mul_s(f0, f0, f1);
        swc1(f0, a2, 4);
        lwc1(f0, a2, 8);
        mul_s(f0, f0, f1);
        swc1(f0, a2, 8);
        lwc1(f0, a2, 28);
        mul_s(f0, f0, f1);
        swc1(f0, a2, 28);
        lwc1(f0, a2, 16);
        mul_s(f0, f0, f1);
        swc1(f0, a2, 16);
        lwc1(f0, a2, 20);
        mul_s(f0, f0, f1);
        swc1(f0, a2, 20);
        lwc1(f0, a2, 24);
        mul_s(f0, f0, f1);
        swc1(f0, a2, 24);
        backedge(ctx);
    }
    // 0x004be5a0
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
    // 0x004be928
    charge(ctx, 2);
}


// sub_4BE930 [rasImageWriteOpen] -- opens a Sun raster image file for writing: the 32-byte big-endian header (magic 0x59A66A95, width, height, 24 bits), the record's sizes and a cleared band buffer
// ($a0 = the writer record, $a1 = width, $a2 = height, $a3.. = the band height / file name) Returns the record.
// 0x004BE930 sub_4BE930 -- 740 bytes; frame 0x90: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4BE930(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004be930
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    v1 = 24;
    sd(ra, sp, 0x50);
    v0 = addiu(sp, 0x6C);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a3;
    sw(v1, v0, 0);
    s0 = t0;
    v0 = addiu(sp, 0x64);
    sw(zero, sp, 0x7C);
    sw(a1, v0, 0);
    v0 = 1;
    sw(a2, sp, 0x68);
    sw(v0, sp, 0x74);
    sw(v0, sp, 0x78);
    mult(v0, a1, v1);
    v1 = addiu(v0, 7);
    v0 = sra(v1, 3);
    if (i64(v1) < 0) {
        // 0x004be990
        charge(ctx, 2);
        v0 = addiu(v1, 7);
        v0 = sra(v0, 3);
    }
    // 0x004be998
    charge(ctx, 127);
    v1 = addiu(v0, 1);
    v0 = si(-2);
    v0 = v1 & v0;
    mult(t3, v0, a2);
    a3 = addiu(sp, 0x60);
    lw(t2, a3, 0);
    t0 = lui(0x956A);
    a0 = addiu(sp, 0x8F);
    v1 = addiu(sp, 0x8D);
    lw(s3, a3, 4);
    t0 = t0 | 0xA659;
    sw(t3, sp, 0x70);
    v0 = addiu(sp, 0x8E);
    lw(t7, a3, 8);
    div1(a1, s1);
    lw(t6, a3, 12);
    sw(t2, sp, 0x8C);
    lbu(s4, sp, 0x8C);
    lbu(t9, a0, 0);
    lbu(t8, v1, 0);
    lbu(t2, v0, 0);
    lw(t5, a3, 16);
    lw(t4, a3, 20);
    lw(t3, a3, 24);
    sb(t9, sp, 0x8C);
    sb(s4, a0, 0);
    sb(t2, v1, 0);
    sb(t8, v0, 0);
    lw(t8, sp, 0x8C);
    lw(t2, a3, 28);
    sw(s3, sp, 0x8C);
    sw(t8, a3, 0);
    sw(t0, sp, 0x60);
    lbu(s3, sp, 0x8C);
    lbu(t9, a0, 0);
    lbu(t8, v1, 0);
    lbu(t0, v0, 0);
    sb(t9, sp, 0x8C);
    sb(s3, a0, 0);
    sb(t0, v1, 0);
    sb(t8, v0, 0);
    lw(t0, sp, 0x8C);
    sw(t7, sp, 0x8C);
    sw(t0, a3, 4);
    lbu(t9, sp, 0x8C);
    lbu(t8, a0, 0);
    lbu(t7, v1, 0);
    lbu(t0, v0, 0);
    sb(t8, sp, 0x8C);
    sb(t9, a0, 0);
    sb(t0, v1, 0);
    sb(t7, v0, 0);
    lw(t0, sp, 0x8C);
    sw(t6, sp, 0x8C);
    sw(t0, a3, 8);
    lbu(t8, sp, 0x8C);
    lbu(t7, a0, 0);
    lbu(t6, v1, 0);
    lbu(t0, v0, 0);
    sb(t7, sp, 0x8C);
    sb(t8, a0, 0);
    sb(t0, v1, 0);
    sb(t6, v0, 0);
    lw(t0, sp, 0x8C);
    sw(t5, sp, 0x8C);
    sw(t0, a3, 12);
    lbu(t7, sp, 0x8C);
    lbu(t6, a0, 0);
    lbu(t5, v1, 0);
    lbu(t0, v0, 0);
    sb(t6, sp, 0x8C);
    sb(t7, a0, 0);
    sb(t0, v1, 0);
    sb(t5, v0, 0);
    lw(t0, sp, 0x8C);
    sw(t4, sp, 0x8C);
    sw(t0, a3, 16);
    lbu(t6, sp, 0x8C);
    lbu(t5, a0, 0);
    lbu(t4, v1, 0);
    lbu(t0, v0, 0);
    sb(t5, sp, 0x8C);
    sb(t6, a0, 0);
    sb(t0, v1, 0);
    sb(t4, v0, 0);
    lw(t0, sp, 0x8C);
    sw(t3, sp, 0x8C);
    sw(t0, a3, 20);
    lbu(t5, sp, 0x8C);
    lbu(t4, a0, 0);
    lbu(t3, v1, 0);
    lbu(t0, v0, 0);
    sb(t4, sp, 0x8C);
    sb(t5, a0, 0);
    sb(t0, v1, 0);
    sb(t3, v0, 0);
    lw(t0, sp, 0x8C);
    sw(t2, sp, 0x8C);
    sw(t0, a3, 24);
    lbu(t4, sp, 0x8C);
    lbu(t3, a0, 0);
    lbu(t2, v1, 0);
    lbu(t0, v0, 0);
    sb(t4, a0, 0);
    sb(t3, sp, 0x8C);
    a0 = 2;
    sb(t0, v1, 0);
    sb(t2, v0, 0);
    lw(v0, sp, 0x8C);
    sw(v0, a3, 28);
    sw(a1, s2, 12);
    mflo1(v0);
    sw(a2, s2, 16);
    div(a2, s0);
    sw(s1, s2, 20);
    sw(s0, s2, 24);
    sw(v0, s2, 28);
    mflo(v0);
    sw(v0, s2, 32);
    sw(t1, s2, 4);
    lw(a2, s2, 4);
    a1 = a0;
    jal(ctx, 0x4BEB7Cu, gen::fn_sub_4C58A0_004c58a0);
    sw(v0, s2, 8);
    lw(a0, s2, 8);
    if (a0 == 0) {
        // 0x004bebec
        charge(ctx, 2);
        sw(zero, s2, 48);
        backedge(ctx);
    } else {
        // 0x004beb94
        charge(ctx, 20);
        a1 = addiu(sp, 0x60);
        a2 = 32;
        jal(ctx, 0x4BEB98u, gen::fn_sub_4C53F0_004c53f0);
        lw(v0, s2, 28);
        mult(v0, v0, s1);
        mult(a0, s0, v0);
        v0 = 0x30000;
        v1 = sll(a0, 1);
        a1 = v0 | 0x191;
        v1 = addu(v1, a0);
        sw(v1, s2, 36);
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x4BEBC8u);  // $ra = the return address
        lw(a0, s2, 36);
        call_ptr(ctx, jt);
        sw(v0, s2, 48);
        lw(a2, s2, 36);
        lw(a0, s2, 48);
        a1 = 0;
        jal(ctx, 0x4BEBDCu, gen::fn_memset_00521408);
    }
    // 0x004bebe4
    charge(ctx, 2);
    v0 = s2;
    // 0x004bebf4
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}


// sub_4D1900 [imageAlphaClass] -- classifies a palettised image's alpha through its palette: 1 opaque (every alpha >= 0xF0), 2 only transparent / opaque alphas, 3 translucent (an alpha in 0x10..0xEF); 2 for other depths
// 0x004D1900 sub_4D1900 -- 328 bytes; leaf frame (no stack)
void sub_4D1900(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12};
    // 0x004d1900
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(a1, a0, 12);
    v0 = 32;
    lw(t0, a0, 4);
    lw(a3, a0, 8);
    lw(a2, a0, 16);
    v1 = 0;
    if (a1 != v0) {
        // 0x004d191c
        charge(ctx, 3);
        v0 = 8;
        if (a1 != v0) {
            // 0x004d1928
            charge(ctx, 3);
            v0 = 4;
            if (a1 == v0) {
                goto L_004d193c;
            }
            // 0x004d1934
            charge(ctx, 2);
            v0 = 2;
            goto L_004d19e4;
        }
    L_004d193c:
        charge(ctx, 5);
        lw(t2, a0, 20);
        at = slt(0, a3);
        lw(a1, a0, 24);
        t3 = 0;
        if (at == 0) {
            goto L_004d19e0;
        }
        // 0x004d1950
        charge(ctx, 1);
        a0 = 1;
        for (;;) {
            // 0x004d1954
            charge(ctx, 4);
            at = slt(0, t0);
            t1 = t2;
            t4 = 0;
            if (at != 0) {
                // 0x004d1964
                charge(ctx, 1);
                for (;;) {
                    // 0x004d1968
                    charge(ctx, 7);
                    lbu(v0, t1, 0);
                    v0 = sll(v0, 2);
                    v0 = addu(a1, v0);
                    lbu(v0, v0, 3);
                    at = slti(v0, 240);
                    if (at != 0) {
                        // 0x004d1984
                        charge(ctx, 3);
                        at = slti(v0, 16);
                        v1 = a0;
                        if (at != 0) {
                            goto L_004d19f0;
                        }
                        goto L_004d1990_10;
                    }
                L_004d19f0:
                    charge(ctx, 4);
                    t4 = addiu(t4, 1);
                    v0 = slt(t4, t0);
                    t1 = addiu(t1, 1);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004d1a00
            charge(ctx, 4);
            t3 = addiu(t3, 1);
            v0 = slt(t3, a3);
            t2 = addu(t2, a2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004d1a10
        charge(ctx, 2);
        backedge(ctx);
        goto L_004d19e0;
    }
    // 0x004d1998
    charge(ctx, 4);
    lw(t4, a0, 20);
    at = slt(0, a3);
    t2 = 0;
    if (at != 0) {
        // 0x004d19a8
        charge(ctx, 2);
        a0 = 1;
        a1 = 255;
        for (;;) {
            // 0x004d19b0
            charge(ctx, 4);
            at = slt(0, t0);
            t3 = t4;
            t1 = 0;
            if (at != 0) {
                for (;;) {
                    // 0x004d19c0
                    charge(ctx, 3);
                    lbu(v0, t3, 3);
                    if (v0 != a1) {
                        // 0x004d19cc
                        charge(ctx, 3);
                        at = slti(v0, 16);
                        v1 = a0;
                        if (at != 0) {
                            goto L_004d1a18;
                        }
                        goto L_004d19d8_16;
                    }
                L_004d1a18:
                    charge(ctx, 4);
                    t1 = addiu(t1, 1);
                    v0 = slt(t1, t0);
                    t3 = addiu(t3, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004d1a28
            charge(ctx, 4);
            t2 = addiu(t2, 1);
            v0 = slt(t2, a3);
            t4 = addu(t4, a2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004d1a38
        charge(ctx, 2);
        backedge(ctx);
        goto L_004d19e0;
    }
L_004d19e0:
    charge(ctx, 1);
    v0 = 2;
L_004d19e4:
    charge(ctx, 3);
    a0 = 1;
    if (v1 == 0) v0 = a0;
    // 0x004d1a40 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004d1990_10:
    charge(ctx, 2);
    v0 = 3;
    // 0x004d1a40 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004d19d8_16:
    charge(ctx, 2);
    v0 = 3;
    // 0x004d1a40 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_4D1A50 [quantAddPixel] -- adds one RGBA pixel (its low bits dropped by the quantiser's depth) to a node's statistics: the count, the weighted channel sums (luminance weights 0.509 / 0.194 ..) and the squared sum
// 0x004D1A50 sub_4D1A50 -- 472 bytes; leaf frame (no stack)
void sub_4D1A50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f12{ctx, 12};
    // 0x004d1a50
    enter(ctx, 12);  // entry check point + this block's cycles
    lw(a3, gp, -20296);  // 0x7CDDA8
    t0 = 8;
    lbu(a2, a1, 0);
    v1 = 1;
    a3 = subu(t0, a3);
    v1 = sllv(v1, a3);
    v1 = addiu(v1, -1);
    v1 = v1 & 0xFF;
    a2 = a2 & v1;
    a2 = a2 & 0xFF;
    if (i64(a2) < 0) {
        // 0x004d1a8c
        charge(ctx, 7);
        a3 = srl(a2, 1);
        a2 = a2 & 0x1;
        a3 = a3 | a2;
        mtc1(a3, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x004d1a80
        charge(ctx, 3);
        mtc1(a2, f0);
        cvt_s_w(f1, f0);
    }
    // 0x004d1aa8
    charge(ctx, 8);
    a3 = 0x3B800000;
    lbu(a2, a1, 1);
    a3 = a3 | 0x8081;
    mtc1(a3, f0);
    a2 = a2 & v1;
    a2 = a2 & 0xFF;
    mul_s(f3, f0, f1);
    if (i64(a2) < 0) {
        // 0x004d1ad4
        charge(ctx, 7);
        a3 = srl(a2, 1);
        a2 = a2 & 0x1;
        a3 = a3 | a2;
        mtc1(a3, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x004d1ac8
        charge(ctx, 3);
        mtc1(a2, f0);
        cvt_s_w(f1, f0);
    }
    // 0x004d1af0
    charge(ctx, 8);
    a3 = 0x3B800000;
    lbu(a2, a1, 2);
    a3 = a3 | 0x8081;
    mtc1(a3, f0);
    a2 = a2 & v1;
    a2 = a2 & 0xFF;
    mul_s(f4, f0, f1);
    if (i64(a2) < 0) {
        // 0x004d1b1c
        charge(ctx, 7);
        a3 = srl(a2, 1);
        a2 = a2 & 0x1;
        a3 = a3 | a2;
        mtc1(a3, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x004d1b10
        charge(ctx, 3);
        mtc1(a2, f0);
        cvt_s_w(f1, f0);
    }
    // 0x004d1b38
    charge(ctx, 8);
    lbu(a1, a1, 3);
    a2 = 0x3B800000;
    a2 = a2 | 0x8081;
    mtc1(a2, f0);
    v1 = a1 & v1;
    v1 = v1 & 0xFF;
    mul_s(f5, f0, f1);
    if (i64(v1) < 0) {
        // 0x004d1b64
        charge(ctx, 7);
        a1 = srl(v1, 1);
        v1 = v1 & 0x1;
        a1 = a1 | v1;
        mtc1(a1, f0);
        cvt_s_w(f2, f0);
        add_s(f2, f2, f2);
    } else {
        // 0x004d1b58
        charge(ctx, 3);
        mtc1(v1, f0);
        cvt_s_w(f2, f0);
    }
    // 0x004d1b80
    charge(ctx, 42);
    v1 = 0x3B800000;
    a1 = v1 | 0x8081;
    mtc1(a1, f1);
    v1 = 0x3F020000;
    v1 = v1 | 0x660D;
    mul_s(f7, f1, f2);
    mtc1(v1, f0);
    mula_s(f4, f4);
    mul_s(f1, f3, f0);
    v1 = 0x3E460000;
    v1 = v1 | 0xDE6B;
    mtc1(v1, f0);
    mul_s(f3, f4, f12);
    mul_s(f0, f5, f0);
    madda_s(f1, f1);
    madda_s(f0, f0);
    mul_s(f2, f0, f12);
    lwc1(f0, a0, 0);
    mul_s(f4, f1, f12);
    add_s(f0, f0, f12);
    swc1(f0, a0, 0);
    lwc1(f0, a0, 20);
    mtc1(zero, f6);
    madd_s(f5, f7, f7);
    mul_s(f1, f7, f12);
    adda_s(f6, f0);
    madd_s(f0, f12, f5);
    swc1(f0, a0, 20);
    lwc1(f0, a0, 4);
    add_s(f0, f0, f4);
    swc1(f0, a0, 4);
    lwc1(f0, a0, 8);
    add_s(f0, f0, f3);
    swc1(f0, a0, 8);
    lwc1(f0, a0, 12);
    add_s(f0, f0, f2);
    swc1(f0, a0, 12);
    lwc1(f0, a0, 16);
    add_s(f0, f0, f1);
    swc1(f0, a0, 16);
}


// sub_4D1C30 [quantNodeFinish] -- finishes a leaf's statistics: its variance term from the sums
// 0x004D1C30 sub_4D1C30 -- 448 bytes; leaf frame (no stack)
void sub_4D1C30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6};
    // 0x004d1c30
    enter(ctx, 16);  // entry check point + this block's cycles
    lwc1(f5, a0, 8);
    lwc1(f4, a0, 4);
    lwc1(f2, a0, 12);
    lwc1(f0, a0, 16);
    lwc1(f1, a0, 0);
    mtc1(zero, f3);
    mula_s(f5, f5);
    madda_s(f4, f4);
    madda_s(f2, f2);
    madd_s(f2, f0, f0);
    div_s(f1, f2, f1);
    lwc1(f0, a0, 20);
    sub_s(f0, f0, f1);
    c_lt_s(f0, f3);
    swc1(f0, a0, 20);
    if (cond(ctx)) {
        // 0x004d1de0
        charge(ctx, 2);
        swc1(f3, a0, 20);
        backedge(ctx);
    }
    // 0x004d1c70
    charge(ctx, 3);
    lbu(v1, a1, 0);
    if (i64(v1) < 0) {
        // 0x004d1c88
        charge(ctx, 7);
        a2 = srl(v1, 1);
        v1 = v1 & 0x1;
        a2 = a2 | v1;
        mtc1(a2, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x004d1c7c
        charge(ctx, 3);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
    }
    // 0x004d1ca4
    charge(ctx, 6);
    a2 = 0x3B800000;
    lbu(v1, a1, 1);
    a2 = a2 | 0x8081;
    mtc1(a2, f0);
    mul_s(f3, f0, f1);
    if (i64(v1) < 0) {
        // 0x004d1cc8
        charge(ctx, 7);
        a2 = srl(v1, 1);
        v1 = v1 & 0x1;
        a2 = a2 | v1;
        mtc1(a2, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x004d1cbc
        charge(ctx, 3);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
    }
    // 0x004d1ce4
    charge(ctx, 6);
    a2 = 0x3B800000;
    lbu(v1, a1, 2);
    a2 = a2 | 0x8081;
    mtc1(a2, f0);
    mul_s(f6, f0, f1);
    if (i64(v1) < 0) {
        // 0x004d1d08
        charge(ctx, 7);
        a2 = srl(v1, 1);
        v1 = v1 & 0x1;
        a2 = a2 | v1;
        mtc1(a2, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x004d1cfc
        charge(ctx, 3);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
    }
    // 0x004d1d24
    charge(ctx, 6);
    lbu(v1, a1, 3);
    a1 = 0x3B800000;
    a1 = a1 | 0x8081;
    mtc1(a1, f0);
    mul_s(f4, f0, f1);
    if (i64(v1) < 0) {
        // 0x004d1d48
        charge(ctx, 7);
        a1 = srl(v1, 1);
        v1 = v1 & 0x1;
        a1 = a1 | v1;
        mtc1(a1, f0);
        cvt_s_w(f2, f0);
        add_s(f2, f2, f2);
    } else {
        // 0x004d1d3c
        charge(ctx, 3);
        mtc1(v1, f0);
        cvt_s_w(f2, f0);
    }
    // 0x004d1d64
    charge(ctx, 31);
    a1 = 0x3B800000;
    v1 = 0x3F020000;
    a2 = a1 | 0x8081;
    mtc1(a2, f1);
    a1 = v1 | 0x660D;
    v1 = 0x3E460000;
    mul_s(f5, f1, f2);
    v1 = v1 | 0xDE6B;
    mtc1(a1, f0);
    mtc1(v1, f1);
    mul_s(f2, f3, f0);
    lwc1(f0, a0, 0);
    mul_s(f1, f4, f1);
    mul_s(f4, f2, f0);
    mul_s(f2, f1, f0);
    mul_s(f3, f6, f0);
    mul_s(f1, f5, f0);
    lwc1(f0, a0, 4);
    add_s(f0, f0, f4);
    swc1(f0, a0, 4);
    lwc1(f0, a0, 8);
    add_s(f0, f0, f3);
    swc1(f0, a0, 8);
    lwc1(f0, a0, 12);
    add_s(f0, f0, f2);
    swc1(f0, a0, 12);
    lwc1(f0, a0, 16);
    add_s(f0, f0, f1);
    swc1(f0, a0, 16);
    // 0x004d1de8
    charge(ctx, 2);
}


// sub_4D1DF0 [quantNodeAdd] -- adds two nodes' statistics into $a0: counts, channel sums and the variance terms combined
// 0x004D1DF0 sub_4D1DF0 -- 280 bytes; leaf frame (no stack)
void sub_4D1DF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9};
    // 0x004d1df0
    enter(ctx, 9);  // entry check point + this block's cycles
    lwc1(f1, a1, 20);
    lwc1(f0, a2, 20);
    mtc1(zero, f9);
    add_s(f0, f1, f0);
    swc1(f0, a0, 20);
    lwc1(f3, a1, 0);
    c_le_s(f3, f9);
    if (!cond(ctx)) {
        // 0x004d1e14
        charge(ctx, 4);
        lwc1(f2, a2, 0);
        c_le_s(f2, f9);
        if (!cond(ctx)) {
            // 0x004d1e24
            charge(ctx, 36);
            v1 = 0x3F800000;
            mtc1(v1, f1);
            lwc1(f0, a1, 4);
            div_s(f8, f1, f3);
            div_s(f7, f1, f2);
            lwc1(f5, a1, 8);
            mul_s(f0, f0, f8);
            lwc1(f4, a1, 12);
            lwc1(f3, a1, 16);
            adda_s(f9, f0);
            lwc1(f2, a2, 4);
            mul_s(f6, f5, f8);
            msub_s(f5, f2, f7);
            lwc1(f1, a2, 8);
            adda_s(f9, f6);
            lwc1(f0, a2, 12);
            mul_s(f4, f4, f8);
            msub_s(f1, f1, f7);
            adda_s(f9, f4);
            msub_s(f4, f0, f7);
            mul_s(f3, f3, f8);
            adda_s(f9, f3);
            lwc1(f3, a2, 16);
            mul_s(f2, f1, f1);
            msub_s(f3, f3, f7);
            adda_s(f9, f2);
            madd_s(f2, f5, f5);
            adda_s(f9, f2);
            madd_s(f2, f4, f4);
            adda_s(f9, f2);
            add_s(f1, f8, f7);
            madd_s(f2, f3, f3);
            div_s(f1, f2, f1);
            lwc1(f0, a0, 20);
            add_s(f0, f0, f1);
            swc1(f0, a0, 20);
        }
    }
    // 0x004d1eb4 (the shared epilogue, written out on this path)
    charge(ctx, 21);
    lwc1(f1, a1, 4);
    lwc1(f0, a2, 4);
    add_s(f0, f1, f0);
    swc1(f0, a0, 4);
    lwc1(f1, a1, 8);
    lwc1(f0, a2, 8);
    add_s(f0, f1, f0);
    swc1(f0, a0, 8);
    lwc1(f1, a1, 12);
    lwc1(f0, a2, 12);
    add_s(f0, f1, f0);
    swc1(f0, a0, 12);
    lwc1(f1, a1, 16);
    lwc1(f0, a2, 16);
    add_s(f0, f1, f0);
    swc1(f0, a0, 16);
    lwc1(f1, a1, 0);
    lwc1(f0, a2, 0);
    add_s(f0, f1, f0);
    swc1(f0, a0, 0);
}


// sub_4D1F10 [quantNodeSubtract] -- subtracts one node's sums from another's (the remainder's mean recomputed)
// 0x004D1F10 sub_4D1F10 -- 284 bytes; leaf frame (no stack)
void sub_4D1F10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9};
    // 0x004d1f10
    enter(ctx, 29);  // entry check point + this block's cycles
    lwc1(f1, a1, 0);
    lwc1(f0, a2, 0);
    mtc1(zero, f9);
    sub_s(f0, f1, f0);
    swc1(f0, a0, 0);
    lwc1(f1, a1, 4);
    lwc1(f0, a2, 4);
    sub_s(f0, f1, f0);
    swc1(f0, a0, 4);
    lwc1(f1, a1, 8);
    lwc1(f0, a2, 8);
    sub_s(f0, f1, f0);
    swc1(f0, a0, 8);
    lwc1(f1, a1, 12);
    lwc1(f0, a2, 12);
    sub_s(f0, f1, f0);
    swc1(f0, a0, 12);
    lwc1(f1, a1, 16);
    lwc1(f0, a2, 16);
    sub_s(f0, f1, f0);
    swc1(f0, a0, 16);
    lwc1(f1, a1, 20);
    lwc1(f0, a2, 20);
    sub_s(f0, f1, f0);
    swc1(f0, a0, 20);
    lwc1(f3, a0, 0);
    c_le_s(f3, f9);
    if (!cond(ctx)) {
        // 0x004d1f84
        charge(ctx, 4);
        lwc1(f2, a2, 0);
        c_le_s(f2, f9);
        if (!cond(ctx)) {
            // 0x004d1f94
            charge(ctx, 36);
            v1 = 0x3F800000;
            mtc1(v1, f1);
            lwc1(f0, a2, 4);
            div_s(f8, f1, f2);
            div_s(f7, f1, f3);
            lwc1(f5, a2, 8);
            mul_s(f0, f0, f8);
            lwc1(f4, a2, 12);
            lwc1(f3, a2, 16);
            adda_s(f9, f0);
            lwc1(f2, a0, 4);
            mul_s(f6, f5, f8);
            msub_s(f5, f2, f7);
            lwc1(f1, a0, 8);
            adda_s(f9, f6);
            lwc1(f0, a0, 12);
            mul_s(f4, f4, f8);
            msub_s(f1, f1, f7);
            adda_s(f9, f4);
            msub_s(f4, f0, f7);
            mul_s(f3, f3, f8);
            adda_s(f9, f3);
            lwc1(f3, a0, 16);
            mul_s(f2, f1, f1);
            msub_s(f3, f3, f7);
            adda_s(f9, f2);
            madd_s(f2, f5, f5);
            adda_s(f9, f2);
            madd_s(f2, f4, f4);
            adda_s(f9, f2);
            add_s(f1, f8, f7);
            madd_s(f2, f3, f3);
            div_s(f1, f2, f1);
            lwc1(f0, a0, 20);
            sub_s(f0, f0, f1);
            swc1(f0, a0, 20);
        }
    }
    // 0x004d2024 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_4D2030 [quantNodeToColor] -- converts a node's mean back to an RGBA palette colour (each channel x 255.99, the luminance weights undone)
// 0x004D2030 sub_4D2030 -- 256 bytes; leaf frame (no stack)
void sub_4D2030(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8};
    // 0x004d2030
    enter(ctx, 40);  // entry check point + this block's cycles
    lwc1(f7, a1, 0);
    v1 = 0x3F800000;
    mtc1(v1, f8);
    lwc1(f5, a1, 4);
    v1 = 0x3F020000;
    a2 = v1 | 0x660D;
    v1 = 0x3E460000;
    div_s(f7, f8, f7);
    v1 = v1 | 0xDE6B;
    mul_s(f5, f5, f7);
    mtc1(a2, f4);
    mtc1(v1, f2);
    div_s(f5, f5, f4);
    v1 = 0x437F0000;
    a2 = v1 | 0xFD71;
    v1 = 255;
    lwc1(f6, a1, 12);
    lwc1(f1, a1, 8);
    lwc1(f0, a1, 16);
    mtc1(a2, f3);
    mul_s(f4, f6, f7);
    sb(v1, a0, 0);
    div_s(f4, f4, f2);
    mul_s(f1, f1, f7);
    mul_s(f1, f3, f1);
    cvt_w_s(f1, f1);
    mul_s(f0, f0, f7);
    mul_s(f2, f3, f5);
    mfc1(t0, f1);
    mul_s(f0, f3, f0);
    mul_s(f1, f3, f4);
    cvt_w_s(f2, f2);
    cvt_w_s(f1, f1);
    cvt_w_s(f0, f0);
    mfc1(a1, f2);
    mfc1(a3, f1);
    v1 = slti(a1, 255);
    mfc1(a2, f0);
    if (v1 != 0) {
        // 0x004d2108
        charge(ctx, 2);
        sb(a1, a0, 0);
        backedge(ctx);
    }
    // 0x004d20d0
    charge(ctx, 4);
    a1 = 255;
    v1 = slti(t0, 255);
    sb(a1, a0, 1);
    if (v1 != 0) {
        // 0x004d2110
        charge(ctx, 2);
        sb(t0, a0, 1);
        backedge(ctx);
    }
    // 0x004d20e0
    charge(ctx, 4);
    a1 = 255;
    v1 = slti(a3, 255);
    sb(a1, a0, 2);
    if (v1 != 0) {
        // 0x004d2118
        charge(ctx, 2);
        sb(a3, a0, 2);
        backedge(ctx);
    }
    // 0x004d20f0
    charge(ctx, 4);
    a1 = 255;
    v1 = slti(a2, 255);
    sb(a1, a0, 3);
    if (v1 != 0) {
        // 0x004d2120
        charge(ctx, 2);
        sb(a2, a0, 3);
        backedge(ctx);
    }
    // 0x004d2100
    charge(ctx, 2);
    // 0x004d2128
    charge(ctx, 2);
}


// sub_4D2130 [quantTreeInsert] -- inserts a pixel into the 16-way colour tree (one bit of each of the four channels per level): the child by the pixel's bits, allocated from the 92-byte node free list, recursively
// 0x004D2130 sub_4D2130 -- 448 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4D2130(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004d2130
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a2;
    s1 = a3;
    sq(s0, sp, 0x0);
    if (s1 == 0) {
        // 0x004d224c
        charge(ctx, 2);
        v0 = a1;
    L_004d22d4:
        charge(ctx, 1);
        ld(ra, sp, 0x40);
    } else {
        // 0x004d2158
        charge(ctx, 9);
        v0 = s2 & 0xF;
        v0 = dsll32(v0, 0);
        v0 = dsra32(v0, 0);
        v0 = sll(v0, 2);
        v0 = addu(v0, a1);
        s0 = addiu(v0, 28);
        lw(v0, v0, 28);
        if (v0 == 0) {
            // 0x004d2254
            charge(ctx, 9);
            v0 = 0x30000;
            a1 = v0 | 0x411;
            v0 = 0x960000;
            lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x4D2264u);  // $ra = the return address
            lw(a0, s3, 16388);
            call_ptr(ctx, jt);
            sw(v0, s0, 0);
            a1 = 0;
            a0 = v0;
            for (;;) {
                // 0x004d2278
                charge(ctx, 12);
                sw(zero, a0, 28);
                a1 = addiu(a1, 8);
                sw(zero, a0, 32);
                v1 = slti(a1, 16);
                sw(zero, a0, 36);
                sw(zero, a0, 40);
                sw(zero, a0, 44);
                sw(zero, a0, 48);
                sw(zero, a0, 52);
                sw(zero, a0, 56);
                a0 = addiu(a0, 32);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004d22a8
            charge(ctx, 3);
            v1 = 1;
            if (s1 != v1) {
                backedge(ctx);
            } else {
                // 0x004d22b4
                charge(ctx, 8);
                sb(zero, v0, 24);
                sw(zero, v0, 0);
                sw(zero, v0, 4);
                sw(zero, v0, 8);
                sw(zero, v0, 12);
                sw(zero, v0, 16);
                sw(zero, v0, 20);
                backedge(ctx);
            }
        }
        // 0x004d217c
        charge(ctx, 3);
        v1 = addiu(s1, -1);
        lw(v0, s0, 0);
        if (v1 == 0) {
            goto L_004d22d4;
        }
        // 0x004d2188
        charge(ctx, 10);
        v1 = dsrl(s2, 4);
        v1 = v1 & 0xF;
        v1 = dsll32(v1, 0);
        v1 = dsra32(v1, 0);
        v1 = sll(v1, 2);
        v0 = addu(v1, v0);
        s0 = addiu(v0, 28);
        lw(v0, v0, 28);
        if (v0 == 0) {
            // 0x004d21b0
            charge(ctx, 9);
            v0 = 0x30000;
            a1 = v0 | 0x411;
            v0 = 0x960000;
            lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x4D21C0u);  // $ra = the return address
            lw(a0, s3, 16388);
            call_ptr(ctx, jt);
            sw(v0, s0, 0);
            a0 = addiu(v0, 28);
            a1 = 0;
            for (;;) {
                // 0x004d21d4
                charge(ctx, 12);
                sw(zero, a0, 0);
                a1 = addiu(a1, 8);
                sw(zero, a0, 4);
                v1 = slti(a1, 16);
                sw(zero, a0, 8);
                sw(zero, a0, 12);
                sw(zero, a0, 16);
                sw(zero, a0, 20);
                sw(zero, a0, 24);
                sw(zero, a0, 28);
                a0 = addiu(a0, 32);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004d2204
            charge(ctx, 4);
            a0 = addiu(s1, -1);
            v1 = 1;
            if (a0 == v1) {
                // 0x004d2214
                charge(ctx, 7);
                sb(zero, v0, 24);
                sw(zero, v0, 0);
                sw(zero, v0, 4);
                sw(zero, v0, 8);
                sw(zero, v0, 12);
                sw(zero, v0, 16);
                sw(zero, v0, 20);
            }
        }
        // 0x004d2230
        charge(ctx, 7);
        lw(a1, s0, 0);
        a2 = dsrl(s2, 8);
        a3 = addiu(s1, -2);
        a0 = s3;
        jal(ctx, 0x4D223Cu, gen::fn_sub_4D2130_004d2130);
        ld(ra, sp, 0x40);
    }
    // 0x004d22d8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_4D22F0 [quantAddImage] -- adds an image's pixels to the colour tree (sub_4D2130 with the pixel statistics sub_4D1A50), 32-bit pixels directly, palettised ones through their palette
// 0x004D22F0 sub_4D22F0 -- 1084 bytes; frame 0x100: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
void sub_4D22F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004d22f0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    s4 = a0;
    sq(s2, sp, 0x30);
    a0 = 32;
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    sw(a1, sp, 0xFC);
    lw(v1, a1, 24);
    mov_s(f20, f12);
    lw(fp, a1, 16);
    lw(s2, a1, 20);
    sq(v1, sp, 0xD0);
    lw(v1, a1, 8);
    lw(a1, a1, 12);
    s3 = v1;
    if (a1 == a0) {
        // 0x004d24b8
        charge(ctx, 2);
        s3 = addiu(v1, -1);
        if (v1 != 0) {
            // 0x004d24c0
            charge(ctx, 3);
            v1 = 0x960000;
            v1 = addiu(v1, 392);  // &0x960188 (free-list alloc slot)
            sq(v1, sp, 0xB0);
            for (;;) {
                // 0x004d24cc
                charge(ctx, 5);
                lw(v1, sp, 0xFC);
                s1 = s2;
                lw(v1, v1, 4);
                s0 = addiu(v1, -1);
                if (v1 != 0) {
                    for (;;) {
                        // 0x004d24e0
                        charge(ctx, 33);
                        lw(s6, gp, -20296);  // 0x7CDDA8
                        lbu(a1, s1, 0);
                        a3 = 8;
                        lbu(v1, s1, 1);
                        a2 = 0x960000;
                        lbu(t1, s1, 2);
                        a2 = addiu(a2, 16784);  // &0x964190 (the quantiser's palette scratch)
                        lbu(t0, s1, 3);
                        lw(a0, s4, 16384);
                        a3 = subu(a3, s6);
                        a1 = srav(a1, a3);
                        v1 = srav(v1, a3);
                        a1 = sll(a1, 3);
                        t1 = srav(t1, a3);
                        v1 = sll(v1, 3);
                        a3 = srav(t0, a3);
                        a1 = addu(a2, a1);
                        v1 = addu(a2, v1);
                        t0 = sll(t1, 3);
                        ld(a1, a1, 0);
                        t0 = addu(a2, t0);
                        ld(v1, v1, 0);
                        a3 = sll(a3, 3);
                        a2 = addu(a2, a3);
                        ld(a3, t0, 0);
                        ld(a2, a2, 0);
                        a1 = dsll(a1, 3);
                        v1 = dsll(v1, 2);
                        a1 = a1 | v1;
                        v1 = dsll(a3, 1);
                        v1 = v1 | a1;
                        s7 = a2 | v1;
                        if (s6 != 0) {
                            // 0x004d2570
                            charge(ctx, 9);
                            v0 = s7 & 0xF;
                            v0 = dsll32(v0, 0);
                            v0 = dsra32(v0, 0);
                            v0 = sll(v0, 2);
                            v0 = addu(a0, v0);
                            s5 = addiu(v0, 28);
                            lw(v0, v0, 28);
                            if (v0 == 0) {
                                // 0x004d2670
                                charge(ctx, 10);
                                lq(v0, sp, 0xB0);
                                v1 = 0x30000;
                                lw(a0, s4, 16388);
                                lw(v0, v0, 0);
                                a1 = v1 | 0x411;
                                jalr(ctx, 0x4D2680u, v0.u());
                                sw(v0, s5, 0);
                                a0 = addiu(v0, 28);
                                a1 = 0;
                                for (;;) {
                                    // 0x004d2698
                                    charge(ctx, 12);
                                    sw(zero, a0, 0);
                                    sw(zero, a0, 4);
                                    a1 = addiu(a1, 8);
                                    sw(zero, a0, 8);
                                    v1 = slti(a1, 16);
                                    sw(zero, a0, 12);
                                    sw(zero, a0, 16);
                                    sw(zero, a0, 20);
                                    sw(zero, a0, 24);
                                    sw(zero, a0, 28);
                                    a0 = addiu(a0, 32);
                                    if (v1 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004d26c8
                                charge(ctx, 3);
                                v1 = 1;
                                if (s6 != v1) {
                                    backedge(ctx);
                                } else {
                                    // 0x004d26d4
                                    charge(ctx, 8);
                                    sb(zero, v0, 24);
                                    sw(zero, v0, 0);
                                    sw(zero, v0, 4);
                                    sw(zero, v0, 8);
                                    sw(zero, v0, 12);
                                    sw(zero, v0, 16);
                                    sw(zero, v0, 20);
                                    backedge(ctx);
                                }
                            } else {
                                // 0x004d2594
                                charge(ctx, 1);
                            }
                            // 0x004d2598
                            charge(ctx, 6);
                            lw(a1, s5, 0);
                            a2 = dsrl(s7, 4);
                            a3 = addiu(s6, -1);
                            a0 = s4;
                            jal(ctx, 0x4D25A4u, gen::fn_sub_4D2130_004d2130);
                            a0 = v0;
                        } else {
                            // 0x004d2564
                            charge(ctx, 2);
                        }
                        // 0x004d25b0
                        charge(ctx, 7);
                        a1 = s1;
                        mov_s(f12, f20);
                        jal(ctx, 0x4D25B4u, gen::fn_sub_4D1A50_004d1a50);
                        v1 = s0;
                        s1 = addiu(s1, 4);
                        s0 = addiu(s0, -1);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004d25cc
                    charge(ctx, 1);
                }
                // 0x004d25d0
                charge(ctx, 4);
                v1 = s3;
                s2 = addu(s2, fp);
                s3 = addiu(s3, -1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    } else {
        // 0x004d2350
        charge(ctx, 3);
        v1 = 8;
        if (a1 != v1) {
            // 0x004d235c
            charge(ctx, 3);
            v1 = 4;
            if (a1 == v1) {
                goto L_004d2370;
            }
            // 0x004d2368
            charge(ctx, 2);
            goto L_004d25e0;
        }
    L_004d2370:
        charge(ctx, 3);
        v1 = s3;
        s3 = addiu(s3, -1);
        if (v1 != 0) {
            // 0x004d237c
            charge(ctx, 3);
            v1 = 0x960000;
            v1 = addiu(v1, 392);  // &0x960188 (free-list alloc slot)
            sq(v1, sp, 0xC0);
            for (;;) {
                // 0x004d2388
                charge(ctx, 5);
                lw(v1, sp, 0xFC);
                s7 = s2;
                lw(v1, v1, 4);
                s1 = addiu(v1, -1);
                if (v1 != 0) {
                    // 0x004d239c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x004d23a0
                        charge(ctx, 38);
                        lbu(v1, s7, 0);
                        a2 = 0x960000;
                        lw(s5, gp, -20296);  // 0x7CDDA8
                        a1 = 8;
                        a2 = addiu(a2, 16784);  // &0x964190 (the quantiser's palette scratch)
                        lw(a0, s4, 16384);
                        a3 = sll(v1, 2);
                        lq(v1, sp, 0xD0);
                        v1 = addu(v1, a3);
                        a3 = subu(a1, s5);
                        lbu(t1, v1, 2);
                        lbu(t2, v1, 0);
                        lbu(a1, v1, 1);
                        lbu(t0, v1, 3);
                        sw(v1, sp, 0xE0);
                        t1 = srav(t1, a3);
                        v1 = srav(t2, a3);
                        t2 = sll(v1, 3);
                        v1 = srav(a1, a3);
                        a3 = srav(t0, a3);
                        v1 = sll(v1, 3);
                        a1 = addu(a2, t2);
                        v1 = addu(a2, v1);
                        t0 = sll(t1, 3);
                        ld(a1, a1, 0);
                        ld(v1, v1, 0);
                        t0 = addu(a2, t0);
                        a3 = sll(a3, 3);
                        a2 = addu(a2, a3);
                        ld(a3, t0, 0);
                        ld(a2, a2, 0);
                        a1 = dsll(a1, 3);
                        v1 = dsll(v1, 2);
                        a1 = a1 | v1;
                        v1 = dsll(a3, 1);
                        v1 = v1 | a1;
                        s6 = a2 | v1;
                        if (s5 != 0) {
                            // 0x004d2440
                            charge(ctx, 9);
                            v0 = s6 & 0xF;
                            v0 = dsll32(v0, 0);
                            v0 = dsra32(v0, 0);
                            v0 = sll(v0, 2);
                            v0 = addu(a0, v0);
                            s0 = addiu(v0, 28);
                            lw(v0, v0, 28);
                            if (v0 == 0) {
                                // 0x004d25e8
                                charge(ctx, 10);
                                v0 = 0x30000;
                                a1 = v0 | 0x411;
                                lq(v0, sp, 0xC0);
                                lw(v0, v0, 0);
                                jt = v0.u();  // the target, read before the delay slot
                                link(ctx, 0x4D25F8u);  // $ra = the return address
                                lw(a0, s4, 16388);
                                call_ptr(ctx, jt);
                                sw(v0, s0, 0);
                                a0 = addiu(v0, 28);
                                a1 = 0;
                                for (;;) {
                                    // 0x004d2610
                                    charge(ctx, 12);
                                    sw(zero, a0, 0);
                                    sw(zero, a0, 4);
                                    a1 = addiu(a1, 8);
                                    sw(zero, a0, 8);
                                    v1 = slti(a1, 16);
                                    sw(zero, a0, 12);
                                    sw(zero, a0, 16);
                                    sw(zero, a0, 20);
                                    sw(zero, a0, 24);
                                    sw(zero, a0, 28);
                                    a0 = addiu(a0, 32);
                                    if (v1 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004d2640
                                charge(ctx, 3);
                                v1 = 1;
                                if (s5 != v1) {
                                    backedge(ctx);
                                } else {
                                    // 0x004d264c
                                    charge(ctx, 8);
                                    sb(zero, v0, 24);
                                    sw(zero, v0, 0);
                                    sw(zero, v0, 4);
                                    sw(zero, v0, 8);
                                    sw(zero, v0, 12);
                                    sw(zero, v0, 16);
                                    sw(zero, v0, 20);
                                    backedge(ctx);
                                }
                            } else {
                                // 0x004d2464
                                charge(ctx, 1);
                            }
                            // 0x004d2468
                            charge(ctx, 6);
                            lw(a1, s0, 0);
                            a2 = dsrl(s6, 4);
                            a3 = addiu(s5, -1);
                            a0 = s4;
                            jal(ctx, 0x4D2474u, gen::fn_sub_4D2130_004d2130);
                            a0 = v0;
                        } else {
                            // 0x004d2438
                            charge(ctx, 2);
                        }
                        // 0x004d2480
                        charge(ctx, 7);
                        lw(a1, sp, 0xE0);
                        mov_s(f12, f20);
                        jal(ctx, 0x4D2484u, gen::fn_sub_4D1A50_004d1a50);
                        v1 = s1;
                        s7 = addiu(s7, 1);
                        s1 = addiu(s1, -1);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004d249c
                    charge(ctx, 1);
                }
                // 0x004d24a0
                charge(ctx, 4);
                v1 = s3;
                s2 = addu(s2, fp);
                s3 = addiu(s3, -1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004d24b0
            charge(ctx, 2);
        }
    }
L_004d25e0:
    charge(ctx, 2);
    // 0x004d26f8
    charge(ctx, 13);
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lwc1(f20, sp, 0x0);
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


// sub_4D2730 [quantBoxAssign] -- gives the tree's nodes inside a colour box the box's palette index, recursively
// 0x004D2730 sub_4D2730 -- 460 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4D2730(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004d2730
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    s1 = a3;
    s0 = t0;
    if (a0 != 0) {
        // 0x004d2770
        charge(ctx, 19);
        v1 = 1;
        lw(a3, s3, 0);
        t1 = sllv(v1, s2);
        lw(a2, s3, 4);
        lw(a1, s3, 8);
        lw(v1, s3, 12);
        lw(t6, s1, 0);
        lw(t4, s1, 4);
        lw(t2, s1, 8);
        t7 = addu(a3, t1);
        t5 = addu(a2, t1);
        lw(t0, s1, 12);
        t3 = addu(a1, t1);
        t1 = addu(v1, t1);
        t6 = subu(t7, t6);
        t4 = subu(t5, t4);
        t2 = subu(t3, t2);
        t0 = subu(t1, t0);
        if (i64(t6) <= 0) {
            goto L_004d28cc;
        }
        // 0x004d27bc
        charge(ctx, 2);
        if (i64(t4) <= 0) {
            goto L_004d28cc;
        }
        // 0x004d27c4
        charge(ctx, 2);
        if (i64(t2) <= 0) {
            goto L_004d28cc;
        }
        // 0x004d27cc
        charge(ctx, 2);
        if (i64(t0) <= 0) {
            goto L_004d28cc;
        }
        // 0x004d27d4
        charge(ctx, 9);
        lw(t3, s1, 16);
        lw(t2, s1, 20);
        lw(t1, s1, 24);
        lw(t0, s1, 28);
        a3 = subu(a3, t3);
        a2 = subu(a2, t2);
        a1 = subu(a1, t1);
        v1 = subu(v1, t0);
        if (i64(a3) < 0) {
            // 0x004d2800
            charge(ctx, 2);
            if (i64(a2) < 0) {
                // 0x004d2808
                charge(ctx, 2);
                if (i64(a1) < 0) {
                    // 0x004d2810
                    charge(ctx, 2);
                    if (i64(v1) < 0) {
                        // 0x004d2818
                        charge(ctx, 2);
                        if (s2 != 0) {
                            // 0x004d282c
                            charge(ctx, 5);
                            s5 = a0;
                            s6 = 0;
                            s4 = addiu(sp, 0xA4);
                            s7 = addiu(sp, 0xA8);
                            fp = addiu(sp, 0xAC);
                            for (;;) {
                                // 0x004d2840
                                charge(ctx, 33);
                                v0 = sra(s6, 3);
                                a2 = addiu(s2, -1);
                                v0 = v0 & 0x1;
                                lw(a3, s3, 0);
                                t0 = sllv(v0, a2);
                                a1 = addiu(sp, 0xA0);
                                v0 = sra(s6, 2);
                                v1 = v0 & 0x1;
                                v0 = sra(s6, 1);
                                t1 = sllv(v1, a2);
                                v0 = v0 & 0x1;
                                a0 = sllv(v0, a2);
                                v0 = s6 & 0x1;
                                v1 = sllv(v0, a2);
                                v0 = addu(a3, t0);
                                sw(v0, sp, 0xA0);
                                a3 = s1;
                                lw(v0, s3, 4);
                                v0 = addu(v0, t1);
                                sw(v0, s4, 0);
                                lw(v0, s3, 8);
                                v0 = addu(v0, a0);
                                sw(v0, s7, 0);
                                lw(v0, s3, 12);
                                v0 = addu(v0, v1);
                                sw(v0, fp, 0x0);
                                lw(a0, s5, 28);
                                t0 = s0;
                                jal(ctx, 0x4D28ACu, gen::fn_sub_4D2730_004d2730);
                                s6 = addiu(s6, 1);
                                v1 = slti(s6, 16);
                                s5 = addiu(s5, 4);
                                if (v1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004d28c4
                            charge(ctx, 2);
                            backedge(ctx);
                        } else {
                            // 0x004d2820
                            charge(ctx, 1);
                            sb(s0, a0, 24);
                        }
                        // 0x004d2824
                        charge(ctx, 2);
                    }
                }
            }
            goto L_004d28cc;
        }
        // 0x004d27f8
        charge(ctx, 2);
        ld(ra, sp, 0x90);
        // 0x004d28d0 (the shared epilogue, written out on this path)
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
        sp = addiu(sp, 0xB0);
        return;
    }
L_004d28cc:
    charge(ctx, 1);
    ld(ra, sp, 0x90);
    // 0x004d28d0 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xB0);
}


// sub_4D2900 [quantBoxSum] -- sums the statistics of the tree's nodes inside a colour box, recursively (sub_4D1DF0)
// 0x004D2900 sub_4D2900 -- 584 bytes; frame 0xD0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4D2900(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004d2900
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    s1 = a3;
    s0 = t0;
    if (s4 != 0) {
        // 0x004d2944
        charge(ctx, 19);
        lw(s7, s3, 0);
        v1 = 1;
        lw(s6, s3, 4);
        v1 = sllv(v1, s2);
        lw(s5, s3, 8);
        lw(t7, s3, 12);
        lw(t2, s1, 0);
        lw(t1, s1, 4);
        t6 = addu(s7, v1);
        lw(t0, s1, 8);
        t5 = addu(s6, v1);
        lw(a3, s1, 12);
        t4 = addu(s5, v1);
        t3 = addu(t7, v1);
        a2 = subu(t6, t2);
        a1 = subu(t5, t1);
        a0 = subu(t4, t0);
        v1 = subu(t3, a3);
        if (i64(a2) <= 0) {
            goto L_004d2b18;
        }
        // 0x004d2990
        charge(ctx, 2);
        if (i64(a1) <= 0) {
            goto L_004d2b18;
        }
        // 0x004d2998
        charge(ctx, 2);
        if (i64(a0) <= 0) {
            goto L_004d2b18;
        }
        // 0x004d29a0
        charge(ctx, 2);
        if (i64(v1) <= 0) {
            goto L_004d2b18;
        }
        // 0x004d29a8
        charge(ctx, 11);
        lw(a0, s1, 24);
        lw(a2, s1, 16);
        lw(v1, s1, 28);
        lw(a1, s1, 20);
        t8 = subu(s5, a0);
        sq(t8, sp, 0xA0);
        t9 = subu(s7, a2);
        t8 = subu(t7, v1);
        fp = subu(s6, a1);
        sq(t8, sp, 0xB0);
        if (i64(t9) < 0) {
            // 0x004d29dc
            charge(ctx, 2);
            if (i64(fp) < 0) {
                // 0x004d29e4
                charge(ctx, 3);
                lq(t8, sp, 0xA0);
                if (i64(t8) < 0) {
                    // 0x004d29f0
                    charge(ctx, 3);
                    lq(t8, sp, 0xB0);
                    if (i64(t8) < 0) {
                        // 0x004d29fc
                        charge(ctx, 5);
                        t2 = subu(s7, t2);
                        t1 = subu(s6, t1);
                        t0 = subu(s5, t0);
                        a3 = subu(t7, a3);
                        if (i64(t2) >= 0) {
                            // 0x004d2a10
                            charge(ctx, 2);
                            if (i64(t1) < 0) {
                                goto L_004d2a6c;
                            }
                            // 0x004d2a18
                            charge(ctx, 2);
                            if (i64(t0) < 0) {
                                goto L_004d2a6c;
                            }
                            // 0x004d2a20
                            charge(ctx, 2);
                            if (i64(a3) < 0) {
                                goto L_004d2a6c;
                            }
                            // 0x004d2a28
                            charge(ctx, 5);
                            a2 = subu(a2, t6);
                            a1 = subu(a1, t5);
                            a0 = subu(a0, t4);
                            v1 = subu(v1, t3);
                            if (i64(a2) < 0) {
                                goto L_004d2a6c;
                            }
                            // 0x004d2a3c
                            charge(ctx, 2);
                            if (i64(a1) < 0) {
                                goto L_004d2a6c;
                            }
                            // 0x004d2a44
                            charge(ctx, 2);
                            if (i64(a0) < 0) {
                                goto L_004d2a6c;
                            }
                            // 0x004d2a4c
                            charge(ctx, 2);
                            if (i64(v1) < 0) {
                                goto L_004d2a6c;
                            }
                            // 0x004d2a54
                            charge(ctx, 6);
                            a2 = s4;
                            a0 = s0;
                            a1 = s0;
                            jal(ctx, 0x4D2A5Cu, gen::fn_sub_4D1DF0_004d1df0);
                            goto L_004d2b18;
                        }
                    L_004d2a6c:
                        charge(ctx, 2);
                        if (i64(s2) > 0) {
                            // 0x004d2a7c
                            charge(ctx, 4);
                            s6 = 0;
                            s5 = addiu(sp, 0xC4);
                            s7 = addiu(sp, 0xC8);
                            fp = addiu(sp, 0xCC);
                            for (;;) {
                                // 0x004d2a8c
                                charge(ctx, 33);
                                v0 = sra(s6, 3);
                                a2 = addiu(s2, -1);
                                v0 = v0 & 0x1;
                                lw(a3, s3, 0);
                                t0 = sllv(v0, a2);
                                a1 = addiu(sp, 0xC0);
                                v0 = sra(s6, 2);
                                v1 = v0 & 0x1;
                                v0 = sra(s6, 1);
                                t1 = sllv(v1, a2);
                                v0 = v0 & 0x1;
                                a0 = sllv(v0, a2);
                                v0 = s6 & 0x1;
                                v1 = sllv(v0, a2);
                                v0 = addu(a3, t0);
                                sw(v0, sp, 0xC0);
                                a3 = s1;
                                lw(v0, s3, 4);
                                v0 = addu(v0, t1);
                                sw(v0, s5, 0);
                                lw(v0, s3, 8);
                                v0 = addu(v0, a0);
                                sw(v0, s7, 0);
                                lw(v0, s3, 12);
                                v0 = addu(v0, v1);
                                sw(v0, fp, 0x0);
                                lw(a0, s4, 28);
                                t0 = s0;
                                jal(ctx, 0x4D2AF8u, gen::fn_sub_4D2900_004d2900);
                                s6 = addiu(s6, 1);
                                v1 = slti(s6, 16);
                                s4 = addiu(s4, 4);
                                if (v1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004d2b10
                            charge(ctx, 2);
                            backedge(ctx);
                        }
                        // 0x004d2a74
                        charge(ctx, 2);
                    }
                }
            }
            goto L_004d2b18;
        }
        // 0x004d29d4
        charge(ctx, 2);
        ld(ra, sp, 0x90);
        // 0x004d2b1c (the shared epilogue, written out on this path)
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
        sp = addiu(sp, 0xD0);
        return;
    }
L_004d2b18:
    charge(ctx, 1);
    ld(ra, sp, 0x90);
    // 0x004d2b1c (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xD0);
}


// sub_4D2B50 [quantSplitError] -- the error of splitting a box at a plane: both halves' sums (sub_4D2900 / sub_4D1F10) and their weighted variance
// 0x004D2B50 sub_4D2B50 -- 524 bytes; frame 0x120: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
void sub_4D2B50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x004d2b50
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    v1 = sll(a2, 2);
    sd(ra, sp, 0xA0);
    v0 = addu(a1, v1);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    s5 = a0;
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    lwc1(f20, t0, 20);
    lwc1(f3, a1, 0);
    lwc1(f2, a1, 4);
    lwc1(f1, a1, 8);
    lwc1(f0, a1, 12);
    swc1(f3, sp, 0x100);
    swc1(f2, sp, 0x104);
    swc1(f1, sp, 0x108);
    swc1(f0, sp, 0x10C);
    lwc1(f3, a1, 16);
    lwc1(f2, a1, 20);
    lwc1(f1, a1, 24);
    lwc1(f0, a1, 28);
    swc1(f3, sp, 0x110);
    swc1(f2, sp, 0x114);
    swc1(f1, sp, 0x118);
    swc1(f0, sp, 0x11C);
    lw(s3, v0, 0);
    lw(s2, v0, 16);
    a0 = subu(s2, s3);
    at = slti(a0, 2);
    s6 = t0;
    if (at == 0) {
        // 0x004d2bf0
        charge(ctx, 5);
        v0 = addu(v1, sp);
        s7 = addu(a3, v1);
        s1 = addiu(v0, 272);
        s0 = addiu(sp, 0xF4);
        fp = addiu(sp, 0xD4);
        for (;;) {
            // 0x004d2c04
            charge(ctx, 38);
            v0 = sra(a0, 1);
            lw(a2, gp, -20296);  // 0x7CDDA8
            s4 = addu(s3, v0);
            a0 = s5;
            v0 = addiu(sp, 0xB4);
            a1 = addiu(sp, 0xB0);
            sw(zero, v0, 0);
            a3 = addiu(sp, 0x100);
            v0 = addiu(sp, 0xB8);
            t0 = addiu(sp, 0xE0);
            sw(zero, v0, 0);
            v0 = addiu(sp, 0xBC);
            sw(zero, sp, 0xB0);
            sw(zero, v0, 0);
            v0 = addiu(sp, 0xF8);
            sw(s4, s1, 0);
            sb(zero, v0, 0);
            v0 = addiu(sp, 0xE4);
            sw(zero, sp, 0xE0);
            sw(zero, v0, 0);
            v0 = addiu(sp, 0xE8);
            sw(zero, s0, 0);
            sw(zero, v0, 0);
            v0 = addiu(sp, 0xEC);
            sw(zero, v0, 0);
            v0 = addiu(sp, 0xF0);
            link(ctx, 0x4D2C6Cu);  // $ra first: the delay slot below depends on it
            sw(zero, v0, 0);
            call(ctx, gen::fn_sub_4D2900_004d2900);
            a0 = addiu(sp, 0xC0);
            a1 = s6;
            a2 = addiu(sp, 0xE0);
            jal(ctx, 0x4D2C7Cu, gen::fn_sub_4D1F10_004d1f10);
            lwc1(f0, sp, 0xE0);
            mtc1(zero, f1);
            c_eq_s(f1, f0);
            if (cond(ctx)) {
                // 0x004d2d08
                charge(ctx, 2);
                s3 = s4;
                backedge(ctx);
            } else {
                // 0x004d2c9c
                charge(ctx, 4);
                lwc1(f0, sp, 0xC0);
                c_eq_s(f1, f0);
                if (cond(ctx)) {
                    // 0x004d2d10
                    charge(ctx, 2);
                    s2 = s4;
                    backedge(ctx);
                } else {
                    // 0x004d2cac
                    charge(ctx, 6);
                    lwc1(f1, s0, 0);
                    lwc1(f0, fp, 0x0);
                    add_s(f0, f1, f0);
                    c_lt_s(f0, f20);
                    if (cond(ctx)) {
                        // 0x004d2d18
                        charge(ctx, 4);
                        lw(v0, s1, 0);
                        mov_s(f20, f0);
                        sw(v0, s7, 0);
                        backedge(ctx);
                    } else {
                        // 0x004d2cc4
                        charge(ctx, 1);
                    }
                    // 0x004d2cc8
                    charge(ctx, 5);
                    lwc1(f1, s0, 0);
                    lwc1(f0, fp, 0x0);
                    c_lt_s(f1, f0);
                    if (!cond(ctx)) {
                        // 0x004d2ce8
                        charge(ctx, 2);
                        s2 = s4;
                    } else {
                        // 0x004d2cdc
                        charge(ctx, 2);
                        s3 = s4;
                    }
                }
            }
            // 0x004d2cf0
            charge(ctx, 4);
            a0 = subu(s2, s3);
            at = slti(a0, 2);
            if (at != 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004d2d00
        charge(ctx, 2);
        backedge(ctx);
    }
    // 0x004d2be8
    charge(ctx, 2);
    mov_s(f0, f20);
    // 0x004d2d28
    charge(ctx, 13);
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lwc1(f20, sp, 0x0);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x120);
}


// sub_4D2D60 [quantBestSplit] -- finds a box's best split over the four axes (sub_4D2B50), the axis and position stored
// 0x004D2D60 sub_4D2D60 -- 360 bytes; frame 0x70: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4D2D60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x004d2d60
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = a2;
    s0 = a3;
    a1 = s1;
    a2 = 0;
    a3 = addiu(sp, 0x50);
    t0 = s2;
    jal(ctx, 0x4D2D94u, gen::fn_sub_4D2B50_004d2b50);
    swc1(f0, sp, 0x60);
    a0 = s3;
    a1 = s1;
    a2 = 1;
    a3 = addiu(sp, 0x50);
    t0 = s2;
    jal(ctx, 0x4D2DB0u, gen::fn_sub_4D2B50_004d2b50);
    swc1(f0, sp, 0x64);
    a0 = s3;
    a1 = s1;
    a2 = 2;
    a3 = addiu(sp, 0x50);
    t0 = s2;
    jal(ctx, 0x4D2DCCu, gen::fn_sub_4D2B50_004d2b50);
    a0 = s3;
    a1 = s1;
    swc1(f0, sp, 0x68);
    a2 = 3;
    a3 = addiu(sp, 0x50);
    t0 = s2;
    jal(ctx, 0x4D2DE8u, gen::fn_sub_4D2B50_004d2b50);
    swc1(f0, sp, 0x6C);
    a0 = 0;
    a1 = 0;
    v1 = addiu(sp, 0x60);
    for (;;) {
        // 0x004d2e00
        charge(ctx, 7);
        v0 = sll(a0, 2);
        v0 = addu(v0, sp);
        lwc1(f1, v0, 96);
        lwc1(f0, v1, 0);
        c_lt_s(f0, f1);
        if (cond(ctx)) {
            // 0x004d2e1c
            charge(ctx, 1);
            a0 = a1;
        }
        // 0x004d2e20
        charge(ctx, 4);
        a1 = addiu(a1, 1);
        v0 = slti(a1, 4);
        v1 = addiu(v1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004d2e30
    charge(ctx, 7);
    v0 = sll(a0, 2);
    a1 = addu(v0, sp);
    lwc1(f0, s2, 20);
    lwc1(f1, a1, 96);
    c_lt_s(f1, f0);
    if (cond(ctx)) {
        // 0x004d2e54
        charge(ctx, 22);
        lwc1(f3, s1, 0);
        a0 = addu(s0, v0);
        lwc1(f2, s1, 4);
        v1 = addu(v0, s1);
        lwc1(f1, s1, 8);
        v0 = 1;
        lwc1(f0, s1, 12);
        swc1(f3, s0, 0);
        swc1(f2, s0, 4);
        swc1(f1, s0, 8);
        swc1(f0, s0, 12);
        lwc1(f3, s1, 16);
        lwc1(f2, s1, 20);
        lwc1(f1, s1, 24);
        lwc1(f0, s1, 28);
        swc1(f3, s0, 16);
        swc1(f2, s0, 20);
        swc1(f1, s0, 24);
        swc1(f0, s0, 28);
        lbu(a1, a1, 80);
        sw(a1, a0, 0);
        sw(a1, v1, 16);
    } else {
        // 0x004d2e4c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004d2eac (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}


// sub_4D2ED0 [quantTreeSum] -- rebuilds a node's statistics from its 16 children to a depth, recursively (leaves finished by sub_4D1C30)
// 0x004D2ED0 sub_4D2ED0 -- 356 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4D2ED0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004d2ed0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    sw(zero, sp, 0xA8);
    if (s4 != 0) {
        // 0x004d2f10
        charge(ctx, 2);
        sw(s4, sp, 0xA8);
        if (i64(s2) <= 0) {
            // 0x004d2ff8
            charge(ctx, 2);
            jal(ctx, 0x4D2FF8u, gen::fn_sub_4D1C30_004d1c30);
            goto L_004d3000;
        }
        // 0x004d2f18
        charge(ctx, 13);
        sb(zero, s4, 24);
        s1 = 0;
        sw(zero, s4, 0);
        s0 = s4;
        sw(zero, s4, 4);
        s5 = addiu(s2, -1);
        sw(zero, s4, 8);
        s6 = addiu(sp, 0xAD);
        sw(zero, s4, 12);
        s7 = addiu(sp, 0xAE);
        sw(zero, s4, 16);
        fp = addiu(sp, 0xAF);
        sw(zero, s4, 20);
        for (;;) {
            // 0x004d2f4c
            charge(ctx, 33);
            lw(t1, gp, -20296);  // 0x7CDDA8
            t2 = 8;
            v0 = sra(s1, 3);
            lbu(a3, s3, 0);
            t0 = v0 & 0x1;
            a2 = addiu(s2, -1);
            v0 = sra(s1, 2);
            a0 = v0 & 0x1;
            v0 = sra(s1, 1);
            t1 = subu(t2, t1);
            v1 = v0 & 0x1;
            t1 = addu(s5, t1);
            v0 = s1 & 0x1;
            t0 = sllv(t0, t1);
            a0 = sllv(a0, t1);
            a3 = addu(a3, t0);
            v1 = sllv(v1, t1);
            sb(a3, sp, 0xAC);
            v0 = sllv(v0, t1);
            lbu(a3, s3, 1);
            a0 = addu(a3, a0);
            sb(a0, s6, 0);
            lbu(a0, s3, 2);
            v1 = addu(a0, v1);
            sb(v1, s7, 0);
            lbu(v1, s3, 3);
            v0 = addu(v1, v0);
            sb(v0, fp, 0x0);
            lw(a0, s0, 28);
            a1 = addiu(sp, 0xAC);
            jal(ctx, 0x4D2FC0u, gen::fn_sub_4D2ED0_004d2ed0);
            if (v0 != 0) {
                // 0x004d2fd0
                charge(ctx, 4);
                a2 = v0;
                a0 = s4;
                a1 = s4;
                jal(ctx, 0x4D2FD8u, gen::fn_sub_4D1DF0_004d1df0);
            }
            // 0x004d2fe0
            charge(ctx, 4);
            s1 = addiu(s1, 1);
            v0 = slti(s1, 16);
            s0 = addiu(s0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004d2ff0
        charge(ctx, 2);
        lw(v0, sp, 0xA8);
        // 0x004d3004 (the shared epilogue, written out on this path)
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
L_004d3000:
    charge(ctx, 1);
    lw(v0, sp, 0xA8);
    // 0x004d3004 (the shared epilogue, written out on this path)
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


// sub_4D3040 [quantTreeCount] -- counts the nodes present at a depth below a node, recursively
// 0x004D3040 sub_4D3040 -- 212 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4D3040(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d3040
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a1;
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = 0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (a0 != 0) {
        // 0x004d3070
        charge(ctx, 2);
        if (i64(s6) <= 0) {
            // 0x004d30e4
            charge(ctx, 1);
            s4 = 1;
            goto L_004d30e8;
        }
        // 0x004d3078
        charge(ctx, 2);
        s1 = a0;
        s5 = 0;
        for (;;) {
            // 0x004d3080
            charge(ctx, 3);
            lw(s0, s1, 28);
            s2 = 0;
            if (s0 != 0) {
                // 0x004d308c
                charge(ctx, 3);
                v0 = addiu(s6, -1);
                if (i64(v0) > 0) {
                    // 0x004d30a0
                    charge(ctx, 2);
                    s3 = 0;
                    for (;;) {
                        // 0x004d30a8
                        charge(ctx, 8);
                        lw(a0, s0, 28);
                        a1 = addiu(s6, -2);
                        jal(ctx, 0x4D30ACu, gen::fn_sub_4D3040_004d3040);
                        s2 = addu(s2, v0);
                        s3 = addiu(s3, 1);
                        v0 = slti(s3, 16);
                        s0 = addiu(s0, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                } else {
                    // 0x004d3098
                    charge(ctx, 2);
                    s2 = 1;
                }
            }
            // 0x004d30c8
            charge(ctx, 5);
            s5 = addiu(s5, 1);
            v0 = slti(s5, 16);
            s4 = addu(s4, s2);
            s1 = addiu(s1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004d30dc
        charge(ctx, 2);
        v0 = s4;
        // 0x004d30ec (the shared epilogue, written out on this path)
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
    }
L_004d30e8:
    charge(ctx, 1);
    v0 = s4;
    // 0x004d30ec (the shared epilogue, written out on this path)
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


// sub_4D3120 [quantTreeColors] -- writes palette colours for the tree's nodes at a depth (sub_4D2030), each node's index stored, recursively
// 0x004D3120 sub_4D3120 -- 252 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4D3120(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d3120
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v0 = a2;
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    s3 = a3;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (s5 != 0) {
        // 0x004d3154
        charge(ctx, 2);
        if (i64(s3) <= 0) {
            // 0x004d31e0
            charge(ctx, 6);
            v1 = sll(v0, 2);
            a1 = s5;
            a0 = addu(s4, v1);
            jal(ctx, 0x4D31E8u, gen::fn_sub_4D2030_004d2030);
            sb(v0, s5, 24);
            v0 = addiu(v0, 1);
            goto L_004d31f8;
        }
        // 0x004d315c
        charge(ctx, 1);
        s2 = 0;
        for (;;) {
            // 0x004d3160
            charge(ctx, 3);
            lw(s0, s5, 28);
            if (s0 != 0) {
                // 0x004d316c
                charge(ctx, 3);
                v1 = addiu(s3, -1);
                if (i64(v1) <= 0) {
                    // 0x004d31b0
                    charge(ctx, 6);
                    v1 = sll(v0, 2);
                    a0 = addu(s4, v1);
                    a1 = s0;
                    jal(ctx, 0x4D31B8u, gen::fn_sub_4D2030_004d2030);
                    sb(v0, s0, 24);
                    v0 = addiu(v0, 1);
                } else {
                    // 0x004d3178
                    charge(ctx, 2);
                    s1 = 0;
                    for (;;) {
                        // 0x004d3180
                        charge(ctx, 9);
                        lw(a0, s0, 28);
                        a3 = addiu(s3, -2);
                        a1 = s4;
                        a2 = v0;
                        jal(ctx, 0x4D318Cu, gen::fn_sub_4D3120_004d3120);
                        s1 = addiu(s1, 1);
                        v1 = slti(s1, 16);
                        s0 = addiu(s0, 4);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004d31a4
                    charge(ctx, 2);
                }
            }
            // 0x004d31c8
            charge(ctx, 4);
            s2 = addiu(s2, 1);
            v1 = slti(s2, 16);
            s5 = addiu(s5, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004d31d8
        charge(ctx, 2);
        ld(ra, sp, 0x60);
        // 0x004d31fc (the shared epilogue, written out on this path)
        charge(ctx, 8);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x70);
        return;
    }
L_004d31f8:
    charge(ctx, 1);
    ld(ra, sp, 0x60);
    // 0x004d31fc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}


// sub_4D3220 [quantTreeLookup] -- the palette index of a pixel: down the tree by the pixel's bits ($a1, four per level) to the depth; the node's index
// 0x004D3220 sub_4D3220 -- 216 bytes; frame 0x10: ra sp+0x0
void sub_4D3220(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d3220
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a2 == 0) {
        // 0x004d32d8
        charge(ctx, 2);
        lbu(v0, a0, 24);
        backedge(ctx);
    } else {
        // 0x004d322c
        charge(ctx, 8);
        v1 = a1 & 0xF;
        v0 = addiu(a2, -1);
        v1 = dsll32(v1, 0);
        v1 = dsra32(v1, 0);
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        lw(a0, v1, 28);
        if (v0 == 0) {
            // 0x004d32e0
            charge(ctx, 2);
            lbu(v0, a0, 24);
            backedge(ctx);
        } else {
            // 0x004d324c
            charge(ctx, 9);
            v1 = dsrl(a1, 4);
            v0 = addiu(a2, -2);
            v1 = v1 & 0xF;
            v1 = dsll32(v1, 0);
            v1 = dsra32(v1, 0);
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            lw(a0, v1, 28);
            if (v0 == 0) {
                // 0x004d32e8
                charge(ctx, 2);
                lbu(v0, a0, 24);
                backedge(ctx);
            } else {
                // 0x004d3270
                charge(ctx, 9);
                v1 = dsrl(a1, 8);
                v0 = addiu(a2, -3);
                v1 = v1 & 0xF;
                v1 = dsll32(v1, 0);
                v1 = dsra32(v1, 0);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 28);
                if (v0 != 0) {
                    // 0x004d329c
                    charge(ctx, 10);
                    v0 = dsrl(a1, 12);
                    a2 = addiu(a2, -4);
                    v0 = v0 & 0xF;
                    v0 = dsll32(v0, 0);
                    v0 = dsra32(v0, 0);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    lw(a0, v0, 28);
                    a1 = dsrl(a1, 16);
                    jal(ctx, 0x4D32BCu, gen::fn_sub_4D3220_004d3220);
                } else {
                    // 0x004d3294
                    charge(ctx, 2);
                    lbu(v0, v1, 24);
                }
                // 0x004d32c4
                charge(ctx, 1);
                v0 = v0 & 0xFF;
            }
            // 0x004d32c8
            charge(ctx, 1);
            v0 = v0 & 0xFF;
        }
        // 0x004d32cc
        charge(ctx, 1);
        v0 = v0 & 0xFF;
    }
    // 0x004d32d0
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    // 0x004d32f0
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}


// sub_4D3300 [quantMakePalette] -- builds the palette: the tree's statistics summed (sub_4D2ED0); with few enough nodes each gets an entry (sub_4D3120), else colour boxes are split at their best plane (sub_4D2D60) until the palette is full and assigned (sub_4D2730)
// 0x004D3300 sub_4D3300 -- 1280 bytes; frame 0xF0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4D3300(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x004d3300
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    v0 = 4;
    sd(ra, sp, 0x90);
    v1 = addiu(sp, 0xEC);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (v1 != 0) {
        for (;;) {
            // 0x004d3344
            charge(ctx, 7);
            sb(zero, v1, 0);
            v0 = addiu(v0, -1);
            v1 = addiu(v1, 1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004d3360
    charge(ctx, 7);
    lw(a2, gp, -20296);  // 0x7CDDA8
    lw(a0, s3, 16384);
    a1 = addiu(sp, 0xEC);
    jal(ctx, 0x4D3368u, gen::fn_sub_4D2ED0_004d2ed0);
    at = slt(0, s4);
    a1 = 0;
    if (at != 0) {
        // 0x004d337c
        charge(ctx, 3);
        at = slti(s4, 9);
        v1 = addiu(s4, -8);
        if (at == 0) {
            // 0x004d3388
            charge(ctx, 3);
            at = slt(s4, 0);
            v0 = 0;
            if (at == 0) {
                // 0x004d3394
                charge(ctx, 5);
                at = 0x7FFF0000;
                at = at | 0xFFFF;
                at = slt(s4, at);
                if (at != 0) {
                    // 0x004d33a8
                    charge(ctx, 1);
                    v0 = 1;
                }
            }
            // 0x004d33ac
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x004d33b4
                charge(ctx, 1);
                a0 = s5;
                for (;;) {
                    // 0x004d33b8
                    charge(ctx, 36);
                    sb(zero, a0, 0);
                    a1 = addiu(a1, 8);
                    sb(zero, a0, 1);
                    v0 = slt(a1, v1);
                    sb(zero, a0, 2);
                    sb(zero, a0, 3);
                    sb(zero, a0, 4);
                    sb(zero, a0, 5);
                    sb(zero, a0, 6);
                    sb(zero, a0, 7);
                    sb(zero, a0, 8);
                    sb(zero, a0, 9);
                    sb(zero, a0, 10);
                    sb(zero, a0, 11);
                    sb(zero, a0, 12);
                    sb(zero, a0, 13);
                    sb(zero, a0, 14);
                    sb(zero, a0, 15);
                    sb(zero, a0, 16);
                    sb(zero, a0, 17);
                    sb(zero, a0, 18);
                    sb(zero, a0, 19);
                    sb(zero, a0, 20);
                    sb(zero, a0, 21);
                    sb(zero, a0, 22);
                    sb(zero, a0, 23);
                    sb(zero, a0, 24);
                    sb(zero, a0, 25);
                    sb(zero, a0, 26);
                    sb(zero, a0, 27);
                    sb(zero, a0, 28);
                    sb(zero, a0, 29);
                    sb(zero, a0, 30);
                    sb(zero, a0, 31);
                    a0 = addiu(a0, 32);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x004d3448
        charge(ctx, 3);
        at = slt(a1, s4);
        if (at != 0) {
            // 0x004d3454
            charge(ctx, 2);
            v0 = sll(a1, 2);
            v1 = addu(s5, v0);
            for (;;) {
                // 0x004d345c
                charge(ctx, 8);
                sb(zero, v1, 0);
                a1 = addiu(a1, 1);
                sb(zero, v1, 1);
                v0 = slt(a1, s4);
                sb(zero, v1, 2);
                sb(zero, v1, 3);
                v1 = addiu(v1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004d347c
            charge(ctx, 1);
        }
    }
    // 0x004d3480
    charge(ctx, 4);
    lw(s0, s3, 16384);
    lw(s6, gp, -20296);  // 0x7CDDA8
    s1 = 0;
    if (s0 != 0) {
        // 0x004d3490
        charge(ctx, 2);
        if (i64(s6) > 0) {
            // 0x004d34a0
            charge(ctx, 1);
            s2 = 0;
            for (;;) {
                // 0x004d34a4
                charge(ctx, 8);
                lw(a0, s0, 28);
                a1 = addiu(s6, -1);
                jal(ctx, 0x4D34A8u, gen::fn_sub_4D3040_004d3040);
                s1 = addu(s1, v0);
                s2 = addiu(s2, 1);
                v0 = slti(s2, 16);
                s0 = addiu(s0, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004d34c4
            charge(ctx, 1);
        } else {
            // 0x004d3498
            charge(ctx, 2);
            s1 = 1;
        }
    }
    // 0x004d34c8
    charge(ctx, 3);
    at = slt(s4, s1);
    if (at != 0) {
        // 0x004d3534
        charge(ctx, 39);
        sw(zero, s3, 0);
        v1 = 1;
        sw(zero, s3, 4);
        a1 = addiu(sp, 0xD0);
        sw(zero, s3, 8);
        a3 = s3;
        sw(zero, s3, 12);
        lw(v0, gp, -20296);  // 0x7CDDA8
        v0 = sllv(v1, v0);
        sw(v0, s3, 16);
        lw(v0, gp, -20296);  // 0x7CDDA8
        v0 = sllv(v1, v0);
        sw(v0, s3, 20);
        lw(v0, gp, -20296);  // 0x7CDDA8
        v0 = sllv(v1, v0);
        sw(v0, s3, 24);
        lw(v0, gp, -20296);  // 0x7CDDA8
        v0 = sllv(v1, v0);
        sw(v0, s3, 28);
        lw(a0, s3, 16384);
        sw(zero, sp, 0xD0);
        sw(zero, sp, 0xD4);
        sw(zero, sp, 0xD8);
        sw(zero, sp, 0xDC);
        sb(zero, s3, 9240);
        sw(zero, s3, 9216);
        sw(zero, s3, 9220);
        sw(zero, s3, 9224);
        sw(zero, s3, 9228);
        sw(zero, s3, 9232);
        sw(zero, s3, 9236);
        lw(a2, gp, -20296);  // 0x7CDDA8
        t0 = addiu(s3, 9216);
        jal(ctx, 0x4D35B4u, gen::fn_sub_4D2900_004d2900);
        lwc1(f0, s3, 9236);
        at = slti(s4, 2);
        s1 = 1;
        swc1(f0, s3, 8192);
        if (at == 0) {
            for (;;) {
                // 0x004d35d0
                charge(ctx, 5);
                mtc1(zero, f1);
                at = slt(0, s1);
                s2 = si(-1);
                a0 = 0;
                if (at != 0) {
                    // 0x004d35e4
                    charge(ctx, 1);
                    v1 = s3;
                    for (;;) {
                        // 0x004d35e8
                        charge(ctx, 4);
                        lwc1(f0, v1, 8192);
                        c_le_s(f0, f1);
                        if (!cond(ctx)) {
                            // 0x004d35f8
                            charge(ctx, 2);
                            mov_s(f1, f0);
                            s2 = a0;
                        }
                        // 0x004d3600
                        charge(ctx, 4);
                        a0 = addiu(a0, 1);
                        v0 = slt(a0, s1);
                        v1 = addiu(v1, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x004d3610
                charge(ctx, 3);
                v0 = si(-1);
                if (s2 != v0) {
                    // 0x004d361c
                    charge(ctx, 16);
                    v0 = sll(s2, 5);
                    v1 = sll(s1, 5);
                    s7 = addu(s3, v0);
                    fp = addu(s3, v1);
                    v0 = sll(s2, 3);
                    lw(a0, s3, 16384);
                    v0 = subu(v0, s2);
                    a2 = s7;
                    v0 = sll(v0, 2);
                    a3 = fp;
                    s0 = addu(s3, v0);
                    s6 = addiu(s0, 9216);
                    a1 = s6;
                    jal(ctx, 0x4D364Cu, gen::fn_sub_4D2D60_004d2d60);
                    if (v0 != 0) {
                        // 0x004d36f4
                        charge(ctx, 55);
                        lw(a0, s3, 16384);
                        v0 = addiu(sp, 0xC4);
                        t0 = s6;
                        a3 = s7;
                        a1 = addiu(sp, 0xC0);
                        sw(zero, v0, 0);
                        v0 = addiu(sp, 0xC8);
                        sw(zero, sp, 0xC0);
                        sw(zero, v0, 0);
                        v0 = addiu(sp, 0xCC);
                        sw(zero, v0, 0);
                        sb(zero, s0, 9240);
                        sw(zero, s0, 9216);
                        sw(zero, s0, 9220);
                        sw(zero, s0, 9224);
                        sw(zero, s0, 9228);
                        sw(zero, s0, 9232);
                        sw(zero, s0, 9236);
                        lw(a2, gp, -20296);  // 0x7CDDA8
                        s6 = addiu(s0, 9236);
                        jal(ctx, 0x4D3740u, gen::fn_sub_4D2900_004d2900);
                        lw(a0, s3, 16384);
                        v0 = sll(s1, 3);
                        v0 = subu(v0, s1);
                        a3 = fp;
                        v0 = sll(v0, 2);
                        a1 = addiu(sp, 0xB0);
                        v1 = addu(s3, v0);
                        v0 = addiu(sp, 0xB4);
                        s0 = addiu(v1, 9236);
                        sw(zero, v0, 0);
                        v0 = addiu(sp, 0xB8);
                        sw(zero, sp, 0xB0);
                        sw(zero, v0, 0);
                        v0 = addiu(sp, 0xBC);
                        sw(zero, v0, 0);
                        sb(zero, v1, 9240);
                        sw(zero, v1, 9216);
                        sw(zero, v1, 9220);
                        sw(zero, v1, 9224);
                        sw(zero, v1, 9228);
                        sw(zero, v1, 9232);
                        sw(zero, v1, 9236);
                        lw(a2, gp, -20296);  // 0x7CDDA8
                        t0 = addiu(v1, 9216);
                        jal(ctx, 0x4D37A4u, gen::fn_sub_4D2900_004d2900);
                        lwc1(f0, s6, 0);
                        v0 = sll(s2, 2);
                        v1 = addu(s3, v0);
                        v0 = sll(s1, 2);
                        v0 = addu(s3, v0);
                        swc1(f0, v1, 8192);
                        lwc1(f0, s0, 0);
                        swc1(f0, v0, 8192);
                        backedge(ctx);
                    } else {
                        // 0x004d365c
                        charge(ctx, 5);
                        v0 = sll(s2, 2);
                        s1 = addiu(s1, -1);
                        v0 = addu(s3, v0);
                        sw(zero, v0, 8192);
                    }
                    // 0x004d3670
                    charge(ctx, 4);
                    s1 = addiu(s1, 1);
                    v0 = slt(s1, s4);
                    if (v0 != 0) {
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
        }
        // 0x004d3680
        charge(ctx, 3);
        at = slt(0, s4);
        s0 = 0;
        if (at == 0) {
            backedge(ctx);
        } else {
            // 0x004d368c
            charge(ctx, 5);
            s1 = s3;
            s2 = s3;
            s6 = addiu(sp, 0xA4);
            s7 = addiu(sp, 0xA8);
            fp = addiu(sp, 0xAC);
            for (;;) {
                // 0x004d36a0
                charge(ctx, 19);
                lw(a0, s3, 16384);
                a1 = addiu(sp, 0xA0);
                lw(a2, gp, -20296);  // 0x7CDDA8
                a3 = s1;
                t0 = s0;
                sw(zero, sp, 0xA0);
                sw(zero, s6, 0);
                sw(zero, s7, 0);
                link(ctx, 0x4D36C0u);  // $ra first: the delay slot below depends on it
                sw(zero, fp, 0x0);
                call(ctx, gen::fn_sub_4D2730_004d2730);
                a0 = s5;
                a1 = addiu(s2, 9216);
                jal(ctx, 0x4D36CCu, gen::fn_sub_4D2030_004d2030);
                s0 = addiu(s0, 1);
                s1 = addiu(s1, 32);
                v0 = slt(s0, s4);
                s2 = addiu(s2, 28);
                s5 = addiu(s5, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004d36ec
            charge(ctx, 2);
            backedge(ctx);
        }
    } else {
        // 0x004d34d4
        charge(ctx, 5);
        s4 = s1;
        lw(s0, gp, -20296);  // 0x7CDDA8
        lw(s1, s3, 16384);
        a2 = 0;
        if (s1 != 0) {
            // 0x004d34e8
            charge(ctx, 2);
            if (i64(s0) <= 0) {
                // 0x004d3520
                charge(ctx, 5);
                a0 = s5;
                a1 = s1;
                jal(ctx, 0x4D3524u, gen::fn_sub_4D2030_004d2030);
                sb(zero, s1, 24);
                backedge(ctx);
            } else {
                // 0x004d34f0
                charge(ctx, 1);
                s2 = 0;
                for (;;) {
                    // 0x004d34f4
                    charge(ctx, 9);
                    lw(a0, s1, 28);
                    a3 = addiu(s0, -1);
                    a1 = s5;
                    jal(ctx, 0x4D34FCu, gen::fn_sub_4D3120_004d3120);
                    a2 = v0;
                    s2 = addiu(s2, 1);
                    v0 = slti(s2, 16);
                    s1 = addiu(s1, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
    }
    // 0x004d3518
    charge(ctx, 2);
    v0 = s4;
    // 0x004d37d0
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


// sub_4D3800 [quantMatchImage] -- converts an image to palette indices: each pixel's index looked up (sub_4D3220), packed for 4 or 8-bit rasters
// 0x004D3800 sub_4D3800 -- 1972 bytes; frame 0x120: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4D3800(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004d3800
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = t0;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    a1 = 4;
    lw(s6, t1, 16);
    lw(s0, t1, 20);
    s1 = t1;
    if (a2 == a1) {
        // 0x004d384c
        charge(ctx, 3);
        v1 = 1;
        if (a3 != v1) {
            goto L_004d3c30;
        }
        // 0x004d3858
        charge(ctx, 4);
        lw(a0, s1, 12);
        v1 = 32;
        if (a0 != v1) {
            // 0x004d3868
            charge(ctx, 3);
            v1 = 8;
            if (a0 != v1) {
                // 0x004d3874
                charge(ctx, 2);
                if (a0 == a1) {
                    goto L_004d3884;
                }
                // 0x004d387c
                charge(ctx, 2);
                goto L_004d3f3c;
            }
        L_004d3884:
            charge(ctx, 5);
            lw(v1, s1, 24);
            sq(v1, sp, 0xD0);
            lw(v1, s1, 8);
            fp = addiu(v1, -0x1);
            if (v1 == 0) {
                goto L_004d3f84;
            }
            for (;;) {
                // 0x004d3898
                charge(ctx, 7);
                lw(v1, s1, 4);
                s4 = s3;
                sw(s0, sp, 0x110);
                s7 = 0;
                at = sltu(0, v1);
                sq(v1, sp, 0xC0);
                if (at != 0) {
                    for (;;) {
                        // 0x004d38b4
                        charge(ctx, 41);
                        lw(v1, sp, 0x110);
                        a2 = 0x960000;
                        lw(t0, gp, -20296);  // 0x7CDDA8
                        a1 = 8;
                        a2 = addiu(a2, 16784);  // &0x964190 (the quantiser's palette scratch)
                        lbu(a0, v1, 0);
                        a3 = sll(a0, 2);
                        lw(v1, s5, 16384);
                        lw(a0, sp, 0x110);
                        a0 = addiu(a0, 1);
                        sw(a0, sp, 0x110);
                        lq(a0, sp, 0xD0);
                        t1 = addu(a0, a3);
                        a3 = subu(a1, t0);
                        lbu(a0, t1, 1);
                        lbu(a1, t1, 0);
                        lbu(t2, t1, 2);
                        a0 = srav(a0, a3);
                        a1 = srav(a1, a3);
                        a0 = sll(a0, 3);
                        lbu(t1, t1, 3);
                        t2 = srav(t2, a3);
                        a1 = sll(a1, 3);
                        a0 = addu(a2, a0);
                        a1 = addu(a2, a1);
                        ld(a0, a0, 0);
                        ld(a1, a1, 0);
                        a3 = srav(t1, a3);
                        t1 = sll(t2, 3);
                        a3 = sll(a3, 3);
                        t1 = addu(a2, t1);
                        a0 = dsll(a0, 2);
                        a2 = addu(a2, a3);
                        a1 = dsll(a1, 3);
                        ld(a3, t1, 0);
                        a1 = a1 | a0;
                        ld(a2, a2, 0);
                        a0 = dsll(a3, 1);
                        a0 = a0 | a1;
                        a0 = a2 | a0;
                        if (t0 == 0) {
                            // 0x004d3f44
                            charge(ctx, 2);
                            lbu(a0, v1, 24);
                            backedge(ctx);
                        } else {
                            // 0x004d3958
                            charge(ctx, 8);
                            a2 = a0 & 0xF;
                            a1 = addiu(t0, -1);
                            a2 = dsll32(a2, 0);
                            a2 = dsra32(a2, 0);
                            a2 = sll(a2, 2);
                            v1 = addu(v1, a2);
                            lw(a2, v1, 28);
                            if (a1 == 0) {
                                // 0x004d3f4c
                                charge(ctx, 2);
                                lbu(v1, a2, 24);
                                backedge(ctx);
                            } else {
                                // 0x004d3978
                                charge(ctx, 9);
                                a1 = dsrl(a0, 4);
                                v1 = addiu(t0, -2);
                                a1 = a1 & 0xF;
                                a1 = dsll32(a1, 0);
                                a1 = dsra32(a1, 0);
                                a1 = sll(a1, 2);
                                a1 = addu(a2, a1);
                                lw(a3, a1, 28);
                                if (v1 != 0) {
                                    // 0x004d39a4
                                    charge(ctx, 11);
                                    v0 = dsrl(a0, 8);
                                    a1 = dsrl(a0, 12);
                                    v0 = v0 & 0xF;
                                    v0 = dsll32(v0, 0);
                                    v0 = dsra32(v0, 0);
                                    v0 = sll(v0, 2);
                                    v0 = addu(a3, v0);
                                    lw(a0, v0, 28);
                                    a2 = addiu(t0, -3);
                                    jal(ctx, 0x4D39C4u, gen::fn_sub_4D3220_004d3220);
                                    v1 = v0;
                                } else {
                                    // 0x004d399c
                                    charge(ctx, 2);
                                    lbu(v1, a3, 24);
                                }
                                // 0x004d39d0
                                charge(ctx, 1);
                                v1 = v1 & 0xFF;
                            }
                            // 0x004d39d4
                            charge(ctx, 1);
                            a0 = v1 & 0xFF;
                        }
                        // 0x004d39d8
                        charge(ctx, 3);
                        v1 = s7 & 0x1;
                        if (v1 == 0) {
                            // 0x004d3a14
                            charge(ctx, 8);
                            lbu(a1, s4, 0);
                            v1 = a0 & 0xFF;
                            a0 = v1 & 0xF;
                            v1 = a1 & 0xF0;
                            sb(v1, s4, 0);
                            lbu(v1, s4, 0);
                            v1 = v1 | a0;
                            sb(v1, s4, 0);
                        } else {
                            // 0x004d39e4
                            charge(ctx, 12);
                            lbu(a1, s4, 0);
                            v1 = a0 & 0xFF;
                            v1 = v1 & 0xF;
                            v1 = sll(v1, 4);
                            a0 = v1 & 0xFF;
                            v1 = a1 & 0xF;
                            sb(v1, s4, 0);
                            lbu(v1, s4, 0);
                            v1 = v1 | a0;
                            sb(v1, s4, 0);
                            s4 = addiu(s4, 1);
                        }
                        // 0x004d3a34
                        charge(ctx, 5);
                        lq(v1, sp, 0xC0);
                        s7 = addiu(s7, 1);
                        v1 = sltu(s7, v1);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x004d3a48
                charge(ctx, 5);
                v1 = fp;
                s0 = addu(s0, s6);
                s3 = addu(s3, s2);
                fp = addiu(fp, -0x1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004d3a5c
            charge(ctx, 2);
            goto L_004d3f3c;
        }
        // 0x004d3a64
        charge(ctx, 4);
        lw(a0, s1, 8);
        v1 = addiu(a0, -1);
        sw(v1, sp, 0x100);
        if (a0 == 0) {
        L_004d3f84:
            charge(ctx, 1);
            ld(ra, sp, 0x90);
        } else {
            for (;;) {
                // 0x004d3a74
                charge(ctx, 7);
                lw(v1, s1, 4);
                fp = s0;
                s4 = s3;
                s7 = 0;
                at = sltu(0, v1);
                sq(v1, sp, 0xB0);
                if (at != 0) {
                    for (;;) {
                        // 0x004d3a90
                        charge(ctx, 35);
                        t0 = fp;
                        lw(a3, gp, -20296);  // 0x7CDDA8
                        lbu(a0, t0, 0);
                        a2 = 8;
                        lbu(v1, t0, 1);
                        a1 = 0x960000;
                        lbu(t2, t0, 2);
                        a1 = addiu(a1, 16784);  // &0x964190 (the quantiser's palette scratch)
                        lbu(t1, t0, 3);
                        fp = addiu(fp, 0x4);
                        a2 = subu(a2, a3);
                        a0 = srav(a0, a2);
                        v1 = srav(v1, a2);
                        a0 = sll(a0, 3);
                        t2 = srav(t2, a2);
                        v1 = sll(v1, 3);
                        a2 = srav(t1, a2);
                        a0 = addu(a1, a0);
                        v1 = addu(a1, v1);
                        t1 = sll(t2, 3);
                        ld(a0, a0, 0);
                        t1 = addu(a1, t1);
                        ld(v1, v1, 0);
                        a2 = sll(a2, 3);
                        a1 = addu(a1, a2);
                        lw(t0, s5, 16384);
                        ld(a2, t1, 0);
                        ld(a1, a1, 0);
                        a0 = dsll(a0, 3);
                        v1 = dsll(v1, 2);
                        a0 = a0 | v1;
                        v1 = dsll(a2, 1);
                        v1 = v1 | a0;
                        v1 = a1 | v1;
                        if (a3 == 0) {
                            // 0x004d3f54
                            charge(ctx, 2);
                            lbu(a0, t0, 24);
                            backedge(ctx);
                        } else {
                            // 0x004d3b1c
                            charge(ctx, 8);
                            a1 = v1 & 0xF;
                            a0 = addiu(a3, -1);
                            a1 = dsll32(a1, 0);
                            a1 = dsra32(a1, 0);
                            a1 = sll(a1, 2);
                            a1 = addu(t0, a1);
                            lw(a2, a1, 28);
                            if (a0 == 0) {
                                // 0x004d3f5c
                                charge(ctx, 2);
                                lbu(v1, a2, 24);
                                backedge(ctx);
                            } else {
                                // 0x004d3b3c
                                charge(ctx, 9);
                                a1 = dsrl(v1, 4);
                                a0 = addiu(a3, -2);
                                a1 = a1 & 0xF;
                                a1 = dsll32(a1, 0);
                                a1 = dsra32(a1, 0);
                                a1 = sll(a1, 2);
                                a1 = addu(a2, a1);
                                lw(t0, a1, 28);
                                if (a0 != 0) {
                                    // 0x004d3b68
                                    charge(ctx, 11);
                                    v0 = dsrl(v1, 8);
                                    a2 = addiu(a3, -3);
                                    v0 = v0 & 0xF;
                                    v0 = dsll32(v0, 0);
                                    v0 = dsra32(v0, 0);
                                    v0 = sll(v0, 2);
                                    v0 = addu(t0, v0);
                                    lw(a0, v0, 28);
                                    a1 = dsrl(v1, 12);
                                    jal(ctx, 0x4D3B88u, gen::fn_sub_4D3220_004d3220);
                                    v1 = v0;
                                } else {
                                    // 0x004d3b60
                                    charge(ctx, 2);
                                    lbu(v1, t0, 24);
                                }
                                // 0x004d3b94
                                charge(ctx, 1);
                                v1 = v1 & 0xFF;
                            }
                            // 0x004d3b98
                            charge(ctx, 1);
                            a0 = v1 & 0xFF;
                        }
                        // 0x004d3b9c
                        charge(ctx, 3);
                        v1 = s7 & 0x1;
                        if (v1 == 0) {
                            // 0x004d3bd8
                            charge(ctx, 8);
                            lbu(a1, s4, 0);
                            v1 = a0 & 0xFF;
                            a0 = v1 & 0xF;
                            v1 = a1 & 0xF0;
                            sb(v1, s4, 0);
                            lbu(v1, s4, 0);
                            v1 = v1 | a0;
                            sb(v1, s4, 0);
                        } else {
                            // 0x004d3ba8
                            charge(ctx, 12);
                            lbu(a1, s4, 0);
                            v1 = a0 & 0xFF;
                            v1 = v1 & 0xF;
                            v1 = sll(v1, 4);
                            a0 = v1 & 0xFF;
                            v1 = a1 & 0xF;
                            sb(v1, s4, 0);
                            lbu(v1, s4, 0);
                            v1 = v1 | a0;
                            sb(v1, s4, 0);
                            s4 = addiu(s4, 1);
                        }
                        // 0x004d3bf8
                        charge(ctx, 5);
                        lq(v1, sp, 0xB0);
                        s7 = addiu(s7, 1);
                        v1 = sltu(s7, v1);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x004d3c0c
                charge(ctx, 7);
                lw(a0, sp, 0x100);
                s0 = addu(s0, s6);
                s3 = addu(s3, s2);
                v1 = a0;
                v1 = addiu(v1, -1);
                sw(v1, sp, 0x100);
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004d3c28
            charge(ctx, 2);
        L_004d3f3c:
            charge(ctx, 2);
            ld(ra, sp, 0x90);
        }
        // 0x004d3f88 (the shared epilogue, written out on this path)
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
        sp = addiu(sp, 0x120);
        return;
    }
L_004d3c30:
    charge(ctx, 4);
    lw(a0, s1, 12);
    v1 = 32;
    if (a0 == v1) {
        // 0x004d3ddc
        charge(ctx, 3);
        lw(v1, s1, 8);
        s7 = addiu(v1, -1);
        if (v1 == 0) {
            goto L_004d3f84;
        }
        for (;;) {
            // 0x004d3de8
            charge(ctx, 6);
            lw(a0, s1, 4);
            s4 = s0;
            fp = s3;
            v1 = addiu(a0, -1);
            sw(v1, sp, 0xF0);
            if (a0 != 0) {
                for (;;) {
                    // 0x004d3e00
                    charge(ctx, 35);
                    t0 = s4;
                    lw(a3, gp, -20296);  // 0x7CDDA8
                    lbu(a0, t0, 0);
                    a2 = 8;
                    lbu(v1, t0, 1);
                    a1 = 0x960000;
                    lbu(t2, t0, 2);
                    a1 = addiu(a1, 16784);  // &0x964190 (the quantiser's palette scratch)
                    lbu(t1, t0, 3);
                    s4 = addiu(s4, 4);
                    a2 = subu(a2, a3);
                    a0 = srav(a0, a2);
                    v1 = srav(v1, a2);
                    a0 = sll(a0, 3);
                    t2 = srav(t2, a2);
                    v1 = sll(v1, 3);
                    a2 = srav(t1, a2);
                    a0 = addu(a1, a0);
                    v1 = addu(a1, v1);
                    t1 = sll(t2, 3);
                    ld(a0, a0, 0);
                    t1 = addu(a1, t1);
                    ld(v1, v1, 0);
                    a2 = sll(a2, 3);
                    a1 = addu(a1, a2);
                    lw(t0, s5, 16384);
                    ld(a2, t1, 0);
                    ld(a1, a1, 0);
                    a0 = dsll(a0, 3);
                    v1 = dsll(v1, 2);
                    a0 = a0 | v1;
                    v1 = dsll(a2, 1);
                    v1 = v1 | a0;
                    v1 = a1 | v1;
                    if (a3 == 0) {
                        // 0x004d3f74
                        charge(ctx, 2);
                        lbu(v1, t0, 24);
                        backedge(ctx);
                    } else {
                        // 0x004d3e8c
                        charge(ctx, 8);
                        a1 = v1 & 0xF;
                        a0 = addiu(a3, -1);
                        a1 = dsll32(a1, 0);
                        a1 = dsra32(a1, 0);
                        a1 = sll(a1, 2);
                        a1 = addu(t0, a1);
                        lw(a2, a1, 28);
                        if (a0 == 0) {
                            // 0x004d3f7c
                            charge(ctx, 2);
                            lbu(v1, a2, 24);
                            backedge(ctx);
                        } else {
                            // 0x004d3eac
                            charge(ctx, 9);
                            a1 = dsrl(v1, 4);
                            a0 = addiu(a3, -2);
                            a1 = a1 & 0xF;
                            a1 = dsll32(a1, 0);
                            a1 = dsra32(a1, 0);
                            a1 = sll(a1, 2);
                            a1 = addu(a2, a1);
                            lw(t0, a1, 28);
                            if (a0 != 0) {
                                // 0x004d3ed8
                                charge(ctx, 11);
                                v0 = dsrl(v1, 8);
                                a2 = addiu(a3, -3);
                                v0 = v0 & 0xF;
                                v0 = dsll32(v0, 0);
                                v0 = dsra32(v0, 0);
                                v0 = sll(v0, 2);
                                v0 = addu(t0, v0);
                                lw(a0, v0, 28);
                                a1 = dsrl(v1, 12);
                                jal(ctx, 0x4D3EF8u, gen::fn_sub_4D3220_004d3220);
                                v1 = v0;
                            } else {
                                // 0x004d3ed0
                                charge(ctx, 2);
                                lbu(v1, t0, 24);
                            }
                            // 0x004d3f04
                            charge(ctx, 1);
                            v1 = v1 & 0xFF;
                        }
                        // 0x004d3f08
                        charge(ctx, 1);
                        v1 = v1 & 0xFF;
                    }
                    // 0x004d3f0c
                    charge(ctx, 7);
                    lw(a0, sp, 0xF0);
                    sb(v1, fp, 0x0);
                    fp = addiu(fp, 0x1);
                    v1 = a0;
                    v1 = addiu(v1, -1);
                    sw(v1, sp, 0xF0);
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004d3f28
            charge(ctx, 5);
            v1 = s7;
            s0 = addu(s0, s6);
            s3 = addu(s3, s2);
            s7 = addiu(s7, -1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        goto L_004d3f3c;
    }
    // 0x004d3c40
    charge(ctx, 3);
    v1 = 8;
    if (a0 != v1) {
        // 0x004d3c4c
        charge(ctx, 3);
        v1 = 4;
        if (a0 == v1) {
            goto L_004d3c60;
        }
        // 0x004d3c58
        charge(ctx, 2);
        goto L_004d3f3c;
    }
L_004d3c60:
    charge(ctx, 5);
    lw(v1, s1, 24);
    sq(v1, sp, 0xA0);
    lw(v1, s1, 8);
    s7 = addiu(v1, -1);
    if (v1 == 0) {
        goto L_004d3f84;
    }
    for (;;) {
        // 0x004d3c74
        charge(ctx, 6);
        lw(a0, s1, 4);
        s4 = s0;
        fp = s3;
        v1 = addiu(a0, -1);
        sw(v1, sp, 0xE0);
        if (a0 != 0) {
            for (;;) {
                // 0x004d3c8c
                charge(ctx, 38);
                lbu(v1, s4, 0);
                a1 = 0x960000;
                lw(a3, gp, -20296);  // 0x7CDDA8
                a0 = 8;
                a1 = addiu(a1, 16784);  // &0x964190 (the quantiser's palette scratch)
                lw(t0, s5, 16384);
                a2 = sll(v1, 2);
                s4 = addiu(s4, 1);
                lq(v1, sp, 0xA0);
                t1 = addu(v1, a2);
                a2 = subu(a0, a3);
                lbu(v1, t1, 1);
                lbu(a0, t1, 0);
                lbu(t2, t1, 2);
                v1 = srav(v1, a2);
                a0 = srav(a0, a2);
                v1 = sll(v1, 3);
                lbu(t1, t1, 3);
                t2 = srav(t2, a2);
                a0 = sll(a0, 3);
                v1 = addu(a1, v1);
                a0 = addu(a1, a0);
                ld(v1, v1, 0);
                ld(a0, a0, 0);
                a2 = srav(t1, a2);
                t1 = sll(t2, 3);
                a2 = sll(a2, 3);
                t1 = addu(a1, t1);
                v1 = dsll(v1, 2);
                a1 = addu(a1, a2);
                a0 = dsll(a0, 3);
                ld(a2, t1, 0);
                a0 = a0 | v1;
                ld(a1, a1, 0);
                v1 = dsll(a2, 1);
                v1 = v1 | a0;
                v1 = a1 | v1;
                if (a3 == 0) {
                    // 0x004d3f64
                    charge(ctx, 2);
                    lbu(v1, t0, 24);
                    backedge(ctx);
                } else {
                    // 0x004d3d24
                    charge(ctx, 8);
                    a1 = v1 & 0xF;
                    a0 = addiu(a3, -1);
                    a1 = dsll32(a1, 0);
                    a1 = dsra32(a1, 0);
                    a1 = sll(a1, 2);
                    a1 = addu(t0, a1);
                    lw(a2, a1, 28);
                    if (a0 == 0) {
                        // 0x004d3f6c
                        charge(ctx, 2);
                        lbu(v1, a2, 24);
                        backedge(ctx);
                    } else {
                        // 0x004d3d44
                        charge(ctx, 9);
                        a1 = dsrl(v1, 4);
                        a0 = addiu(a3, -2);
                        a1 = a1 & 0xF;
                        a1 = dsll32(a1, 0);
                        a1 = dsra32(a1, 0);
                        a1 = sll(a1, 2);
                        a1 = addu(a2, a1);
                        lw(t0, a1, 28);
                        if (a0 != 0) {
                            // 0x004d3d70
                            charge(ctx, 11);
                            v0 = dsrl(v1, 8);
                            a2 = addiu(a3, -3);
                            v0 = v0 & 0xF;
                            v0 = dsll32(v0, 0);
                            v0 = dsra32(v0, 0);
                            v0 = sll(v0, 2);
                            v0 = addu(t0, v0);
                            lw(a0, v0, 28);
                            a1 = dsrl(v1, 12);
                            jal(ctx, 0x4D3D90u, gen::fn_sub_4D3220_004d3220);
                            v1 = v0;
                        } else {
                            // 0x004d3d68
                            charge(ctx, 2);
                            lbu(v1, t0, 24);
                        }
                        // 0x004d3d9c
                        charge(ctx, 1);
                        v1 = v1 & 0xFF;
                    }
                    // 0x004d3da0
                    charge(ctx, 1);
                    v1 = v1 & 0xFF;
                }
                // 0x004d3da4
                charge(ctx, 7);
                lw(a0, sp, 0xE0);
                sb(v1, fp, 0x0);
                fp = addiu(fp, 0x1);
                v1 = a0;
                v1 = addiu(v1, -1);
                sw(v1, sp, 0xE0);
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004d3dc0
        charge(ctx, 5);
        v1 = s7;
        s0 = addu(s0, s6);
        s3 = addu(s3, s2);
        s7 = addiu(s7, -1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004d3dd4
    charge(ctx, 2);
    goto L_004d3f3c;
}


// sub_4D3FC0 [quantInit] -- initialises the quantiser: the bit-spreading table (2^depth 64-bit masks at 0x964190), the 92-byte node free list, the root with 16 empty children
// 0x004D3FC0 sub_4D3FC0 -- 288 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4D3FC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004d3fc0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 1;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a2, gp, -20296);  // 0x7CDDA8
    s0 = a0;
    a0 = sllv(a1, a2);
    at = sltu(0, a0);
    t2 = 0;
    if (at != 0) {
        // 0x004d3fe8
        charge(ctx, 3);
        a3 = 0x960000;
        v1 = addiu(a2, -1);
        a3 = addiu(a3, 16784);  // &0x964190 (the quantiser's palette scratch)
        for (;;) {
            // 0x004d3ff4
            charge(ctx, 4);
            at = sltu(0, a2);
            t0 = 0;
            t1 = 0;
            if (at != 0) {
                for (;;) {
                    // 0x004d4004
                    charge(ctx, 4);
                    v0 = sllv(a1, t1);
                    v0 = t2 & v0;
                    if (v0 == 0) {
                        // 0x004d4024
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x004d4014
                        charge(ctx, 4);
                        v0 = subu(v1, t1);
                        v0 = sll(v0, 2);
                        v0 = sllv(a1, v0);
                    }
                    // 0x004d4028
                    charge(ctx, 7);
                    v0 = dsll32(v0, 0);
                    t1 = addiu(t1, 1);
                    v0 = dsra32(v0, 0);
                    t0 = t0 | v0;
                    v0 = sltu(t1, a2);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004d4044
            charge(ctx, 5);
            t2 = addiu(t2, 1);
            sd(t0, a3, 0);
            v0 = sltu(t2, a0);
            a3 = addiu(a3, 8);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004d4058
    charge(ctx, 17);
    v0 = 0x30000;
    a0 = 92;
    a1 = 1024;
    a2 = 4;
    a3 = v0 | 0x411;
    jal(ctx, 0x4D4068u, gen::fn_sub_4C3B50_004c3b50);
    sw(v0, s0, 16388);
    v0 = 0x30000;
    a1 = v0 | 0x411;
    v0 = 0x960000;
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4D4084u);  // $ra = the return address
    lw(a0, s0, 16388);
    call_ptr(ctx, jt);
    sw(v0, s0, 16384);
    a0 = 0;
    lw(v0, s0, 16384);
    v1 = addiu(v0, 28);
    for (;;) {
        // 0x004d409c
        charge(ctx, 12);
        sw(zero, v1, 0);
        a0 = addiu(a0, 8);
        sw(zero, v1, 4);
        v0 = slti(a0, 16);
        sw(zero, v1, 8);
        sw(zero, v1, 12);
        sw(zero, v1, 16);
        sw(zero, v1, 20);
        sw(zero, v1, 24);
        sw(zero, v1, 28);
        v1 = addiu(v1, 32);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004d40cc
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    v0 = 1;
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4D40E0 [quantTreeFree] -- returns a node's children to the node free list, recursively
// 0x004D40E0 sub_4D40E0 -- 252 bytes; frame 0xA0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4D40E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004d40e0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    fp = a1;
    sq(s6, sp, 0x60);
    s7 = a2;
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (fp != 0) {
        // 0x004d411c
        charge(ctx, 2);
        if (i64(s7) > 0) {
            // 0x004d4124
            charge(ctx, 4);
            s0 = 0x960000;
            s4 = 0;
            s6 = fp;
            s0 = addiu(s0, 396);  // &0x96018C (free-list free slot)
            for (;;) {
                // 0x004d4134
                charge(ctx, 3);
                lw(s3, s6, 28);
                if (s3 != 0) {
                    // 0x004d4140
                    charge(ctx, 3);
                    v0 = addiu(s7, -1);
                    if (i64(v0) > 0) {
                        // 0x004d414c
                        charge(ctx, 3);
                        s2 = 0;
                        s1 = s3;
                        for (;;) {
                            // 0x004d4158
                            charge(ctx, 8);
                            lw(a1, s1, 28);
                            a2 = addiu(s7, -2);
                            a0 = s5;
                            jal(ctx, 0x4D4160u, gen::fn_sub_4D40E0_004d40e0);
                            s2 = addiu(s2, 1);
                            v0 = slti(s2, 16);
                            s1 = addiu(s1, 4);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                    // 0x004d4178
                    charge(ctx, 4);
                    lw(a0, s5, 16388);
                    lw(v0, s0, 0);
                    a1 = s3;
                    jalr(ctx, 0x4D4180u, v0.u());
                }
                // 0x004d4188
                charge(ctx, 4);
                s4 = addiu(s4, 1);
                v0 = slti(s4, 16);
                s6 = addiu(s6, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004d4198
        charge(ctx, 5);
        v0 = 0x960000;
        lw(a0, s5, 16388);
        lw(v0, v0, 396);  // 0x96018C (free-list free slot)
        a1 = fp;
        jalr(ctx, 0x4D41A4u, v0.u());
    }
    // 0x004d41ac (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xA0);
}


// sub_4D41E0 [quantTerm] -- releases the quantiser: the tree's nodes freed (sub_4D40E0), the node free list destroyed
// 0x004D41E0 sub_4D41E0 -- 160 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4D41E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d41e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 16384);
    lw(s2, gp, -20296);  // 0x7CDDA8
    s1 = a0;
    if (s0 != 0) {
        // 0x004d420c
        charge(ctx, 2);
        if (i64(s2) > 0) {
            // 0x004d4214
            charge(ctx, 2);
            s4 = 0;
            s3 = s0;
            for (;;) {
                // 0x004d421c
                charge(ctx, 8);
                lw(a1, s3, 28);
                a2 = addiu(s2, -1);
                a0 = s1;
                jal(ctx, 0x4D4224u, gen::fn_sub_4D40E0_004d40e0);
                s4 = addiu(s4, 1);
                v0 = slti(s4, 16);
                s3 = addiu(s3, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004d423c
            charge(ctx, 1);
        }
        // 0x004d4240
        charge(ctx, 5);
        v0 = 0x960000;
        lw(a0, s1, 16388);
        lw(v0, v0, 396);  // 0x96018C (free-list free slot)
        a1 = s0;
        jalr(ctx, 0x4D424Cu, v0.u());
    }
    // 0x004d4254
    charge(ctx, 11);
    sw(zero, s1, 16384);
    link(ctx, 0x4D4258u);  // $ra first: the delay slot below depends on it
    lw(a0, s1, 16388);
    call(ctx, gen::fn_sub_4C3C30_004c3c30);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_4D8320 [RpSkyTextureSetMipmapK] -- sets a texture's mipmap K: $f12 x 16 clamped to -2048..2047, stored in its raster's extension; the texture, or 0
// 0x004D8320 sub_4D8320 -- 156 bytes; leaf frame (no stack)
void sub_4D8320(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x004d8320
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x004d8328
        charge(ctx, 3);
        lw(a2, a0, 0);
        if (a2 == 0) {
            goto L_004d83b0;
        }
        // 0x004d8334
        charge(ctx, 10);
        v0 = 0x41800000;
        mtc1(v0, f0);
        mul_s(f0, f0, f12);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = slti(v1, -2048);
        if (v0 != 0) {
            // 0x004d83a8
            charge(ctx, 2);
            v1 = si(-2048);
            backedge(ctx);
        } else {
            // 0x004d835c
            charge(ctx, 3);
            at = slti(v1, 2048);
            if (at == 0) {
                // 0x004d8368
                charge(ctx, 1);
                v1 = 2047;
            }
        }
        // 0x004d836c
        charge(ctx, 15);
        v0 = v1 & 0xFFFF;
        lw(v1, gp, -16968);  // 0x7CEAA8
        a1 = v0 & 0xFFF;
        v0 = a0;
        a2 = addu(a2, v1);
        lhu(v1, a2, 20);
        v1 = v1 & 0xF000;
        sh(v1, a2, 20);
        lw(a0, a0, 0);
        lw(v1, gp, -16968);  // 0x7CEAA8
        a0 = addu(a0, v1);
        lhu(v1, a0, 20);
        v1 = v1 | a1;
        sh(v1, a0, 20);
        // 0x004d83b4 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_004d83b0:
    charge(ctx, 1);
    v0 = 0;
    // 0x004d83b4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_4F22B0 [RwIm3DRenderLine] -- renders one line of the transformed Im3D vertices: two u16 indices from the global RxHeap, the Im3D line pipe executed; 1, or 0 (error 35 when nothing is transformed)
// ($a0 / $a1 = the two vertex indices) The module's render record (+76): primitive 1 (lines), the index buffer at
// +116 with room for two; the indices freed again after the execute.
// 0x004F22B0 sub_4F22B0 -- 264 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F22B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f22b0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    link(ctx, 0x4F22CCu);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4F2E60_004f2e60);
    lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
    s1 = v0;
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    a2 = addu(v0, v1);
    lw(v0, a2, 68);
    if (v0 == 0) {
        // 0x004f2378
        charge(ctx, 9);
        v0 = 1;
        a0 = 35;
        link(ctx, 0x4F2380u);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x58);
        call(ctx, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x5C);
        a0 = addiu(sp, 0x58);
        jal(ctx, 0x4F238Cu, gen::fn_sub_4C1C50_004c1c50);
        backedge(ctx);
    L_004f2370:
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004f22f4
        charge(ctx, 23);
        lw(a1, a2, 16);
        v1 = 1;
        v0 = 2;
        s0 = addiu(a2, 76);
        a0 = s1;
        sw(a1, a2, 108);
        sw(v1, a2, 112);
        sw(zero, a2, 116);
        sw(v0, a2, 120);
        lw(v0, a2, 120);
        a1 = sll(v0, 1);
        jal(ctx, 0x4F231Cu, gen::fn_sub_4F67B0_004f67b0);
        sw(v0, s0, 40);
        a1 = s0;
        lw(v0, s0, 40);
        sh(s3, v0, 0);
        lw(v0, s0, 40);
        sh(s2, v0, 2);
        lw(a0, s0, 32);
        a2 = 0;
        jal(ctx, 0x4F2340u, gen::fn_RxPipelineExecute_004f2e70);
        if (v0 == 0) {
            // 0x004f2364
            charge(ctx, 3);
            lw(a1, s0, 40);
            a0 = s1;
            jal(ctx, 0x4F2368u, gen::fn_sub_4F65B0_004f65b0);
            goto L_004f2370;
        }
        // 0x004f2350
        charge(ctx, 5);
        lw(a1, s0, 40);
        a0 = s1;
        jal(ctx, 0x4F2354u, gen::fn_sub_4F65B0_004f65b0);
        v0 = 1;
    }
    // 0x004f239c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_4F2730 [im3dEngineClose] -- the Im3D module's engine close: two empty hooks, the open count down; $a0
// 0x004F2730 sub_4F2730 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4F2730(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f2730
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s0, sp, 0x0);
    lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
    s0 = a0;
    v0 = addu(v0, v1);
    a0 = addiu(v0, 32);
    jal(ctx, 0x4F2750u, gen::fn_sub_4F72E0_004f72e0);
    lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = addu(v0, v1);
    a0 = addiu(v0, 28);
    jal(ctx, 0x4F2768u, gen::fn_sub_4F72C0_004f72c0);
    lw(v1, gp, -16844);  // 0x7CEB24 (the Im3D module's open count)
    v0 = s0;
    v1 = addiu(v1, -1);
    sw(v1, gp, -16844);  // 0x7CEB24 (the Im3D module's open count)
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4F2790 [im3dEngineOpen] -- the Im3D module's engine open: the module offset / address stored, the module cleared, two hooks that always succeed; $a0
// 0x004F2790 sub_4F2790 -- 220 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4F2790(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f2790
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sq(s0, sp, 0x0);
    a2 = 124;
    s0 = a0;
    sw(a1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
    a0 = addu(v0, a1);
    lw(v0, gp, -16844);  // 0x7CEB24 (the Im3D module's open count)
    a1 = 0;
    sw(a0, gp, -16852);  // 0x7CEB1C (the Im3D module's address)
    v0 = addiu(v0, 1);
    link(ctx, 0x4F27C4u);  // $ra first: the delay slot below depends on it
    sw(v0, gp, -16844);  // 0x7CEB24 (the Im3D module's open count)
    call(ctx, gen::fn_memset_00521408);
    lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = addu(v0, v1);
    a0 = addiu(v0, 28);
    jal(ctx, 0x4F27DCu, gen::fn_sub_4F72D0_004f72d0);
    if (v0 != 0) {
        // 0x004f27fc
        charge(ctx, 8);
        lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        a0 = addiu(v0, 32);
        jal(ctx, 0x4F280Cu, gen::fn_sub_4F72F0_004f72f0);
        backedge(ctx);
    }
    // 0x004f27ec
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x004f281c
        charge(ctx, 16);
        lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        a0 = addiu(v0, 32);
        jal(ctx, 0x4F282Cu, gen::fn_sub_4F72E0_004f72e0);
        lw(v1, gp, -16848);  // 0x7CEB20 (the Im3D module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        a0 = addiu(v0, 28);
        jal(ctx, 0x4F2844u, gen::fn_sub_4F72C0_004f72c0);
        lw(v1, gp, -16844);  // 0x7CEB24 (the Im3D module's open count)
        v0 = 0;
        v1 = addiu(v1, -1);
        sw(v1, gp, -16844);  // 0x7CEB24 (the Im3D module's open count)
    } else {
        // 0x004f27f4
        charge(ctx, 2);
        v0 = s0;
    }
    // 0x004f285c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4F2870 [rxPipelineModuleOpen] -- the pipeline module's engine open: its offset (gp 0x7CEB28) stored, the module set up (sub_4F2A00); $a0, or 0
// 0x004F2870 sub_4F2870 -- 48 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4F2870(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f2870
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    sw(a1, gp, -16840);  // 0x7CEB28 (the pipeline module offset)
    s0 = a0;
    jal(ctx, 0x4F2880u, gen::fn_sub_4F2A00_004f2a00);
    if (v0 == 0) s0 = 0;
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4F28A0 [rxPipelineModuleClose] -- the pipeline module's engine close: the module torn down (sub_4F2990); $a0
// 0x004F28A0 sub_4F28A0 -- 40 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4F28A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f28a0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x4F28ACu, gen::fn_sub_4F2990_004f2990);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4F28D0 -- a hook that always succeeds (1)
// 0x004F28D0 sub_4F28D0 -- 8 bytes; leaf frame (no stack)
void sub_4F28D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x004f28d0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 1;
}


// sub_4F28F0 [rxPacketReleaseClusters] -- releases a packet's clusters: each slot (28 bytes) with data and no 'external' flag frees it from the global RxHeap; the slots cleared, the packet's count 0
// Marks the pipeline's embedded packet free (+16 = 1) first.
// 0x004F28F0 sub_4F28F0 -- 160 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F28F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f28f0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a1 = 1;
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(v1, a0, 4);
    s0 = addiu(s2, 20);
    sw(a1, v1, 16);
    lhu(s1, a0, 2);
    for (;;) {
        // 0x004f291c
        charge(ctx, 3);
        lw(v1, s0, 20);
        if (v1 != 0) {
            // 0x004f2928
            charge(ctx, 3);
            lw(a1, s0, 4);
            if (a1 != 0) {
                // 0x004f2934
                charge(ctx, 4);
                lhu(v1, s0, 0);
                v1 = v1 & 0x2;
                if (v1 == 0) {
                    // 0x004f2944
                    charge(ctx, 3);
                    link(ctx, 0x4F2944u);  // $ra first: the delay slot below depends on it
                    lw(a0, gp, -16832);  // 0x7CEB30 (the global RxHeap)
                    call(ctx, gen::fn_sub_4F65B0_004f65b0);
                }
            }
            // 0x004f2950
            charge(ctx, 6);
            sw(zero, s0, 0);
            sw(zero, s0, 4);
            sw(zero, s0, 12);
            sw(zero, s0, 16);
            sw(zero, s0, 20);
        }
        // 0x004f2968
        charge(ctx, 3);
        s1 = addiu(s1, -1);
        s0 = addiu(s0, 28);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004f2974
    charge(ctx, 7);
    sh(zero, s2, 0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4F2990 [rxPipelineModuleTerm] -- tears the pipeline module down when it is open: the 52-byte pipeline free list destroyed, the global RxHeap destroyed, the flag cleared; 1
// 0x004F2990 sub_4F2990 -- 104 bytes; frame 0x10: ra sp+0x0
void sub_4F2990(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f2990
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -16836);  // 0x7CEB2C (the pipeline module's 'open' flag)
    if (v0 != 0) {
        // 0x004f29ac
        charge(ctx, 16);
        lw(v1, gp, -16840);  // 0x7CEB28 (the pipeline module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        v0 = addu(v0, v1);
        link(ctx, 0x4F29BCu);  // $ra first: the delay slot below depends on it
        lw(a0, v0, 0);
        call(ctx, gen::fn_sub_4C3C30_004c3c30);
        lw(v1, gp, -16840);  // 0x7CEB28 (the pipeline module offset)
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        lw(a0, gp, -16832);  // 0x7CEB30 (the global RxHeap)
        v0 = addu(v0, v1);
        link(ctx, 0x4F29D8u);  // $ra first: the delay slot below depends on it
        sw(zero, v0, 0);
        call(ctx, gen::fn_sub_4F6970_004f6970);
        sw(zero, gp, -16832);  // 0x7CEB30 (the global RxHeap)
        sw(zero, gp, -16836);  // 0x7CEB2C (the pipeline module's 'open' flag)
        backedge(ctx);
    }
    // 0x004f29a4
    charge(ctx, 2);
    v0 = 1;
    // 0x004f29ec
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_4F2A00 [rxPipelineModuleInit] -- sets the pipeline module up: the global RxHeap (its initial size 0x7CDDF0), the 52-byte pipeline free list, the node limit (64), the default render-state vector (sub_4F6B50)
// Refused when already open; 1, or 0 with the heap destroyed again.
// 0x004F2A00 sub_4F2A00 -- 208 bytes; frame 0x10: ra sp+0x0
void sub_4F2A00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f2a00
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -16836);  // 0x7CEB2C (the pipeline module's 'open' flag)
    if (v0 == 0) {
        // 0x004f2a1c
        charge(ctx, 4);
        link(ctx, 0x4F2A1Cu);  // $ra first: the delay slot below depends on it
        lw(a0, gp, -20224);  // 0x7CDDF0 (the global RxHeap's initial size)
        call(ctx, gen::fn_sub_4F6A10_004f6a10);
        sw(v0, gp, -16832);  // 0x7CEB30 (the global RxHeap)
        if (v0 == 0) {
            // 0x004f2aac
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004f2a2c
            charge(ctx, 17);
            lw(a1, gp, -20216);  // 0x7CDDF8 (the pipeline free list's entries per block)
            t0 = 0x960000;
            lw(a3, gp, -20212);  // 0x7CDDFC (the pipeline free list's alignment)
            v0 = 0x40000;
            a0 = 52;
            a2 = 4;
            t0 = addiu(t0, 23200);  // &0x965AA0 (the pipeline free list's static block)
            t1 = v0 | 0x409;
            jal(ctx, 0x4F2A48u, gen::fn_sub_4C3B60_004c3b60);
            lw(v1, gp, -16840);  // 0x7CEB28 (the pipeline module offset)
            a1 = 0x960000;
            a1 = addiu(a1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            a0 = addu(a1, v1);
            sw(v0, a0, 0);
            lw(v0, a0, 0);
            if (v0 == 0) {
                // 0x004f2ab4
                charge(ctx, 4);
                link(ctx, 0x4F2AB4u);  // $ra first: the delay slot below depends on it
                lw(a0, gp, -16832);  // 0x7CEB30 (the global RxHeap)
                call(ctx, gen::fn_sub_4F6970_004f6970);
                sw(zero, gp, -16832);  // 0x7CEB30 (the global RxHeap)
                v0 = 0;
            } else {
                // 0x004f2a70
                charge(ctx, 15);
                lw(v1, gp, -20220);  // 0x7CDDF4 (the pipeline node limit (64))
                lw(v0, gp, -16840);  // 0x7CEB28 (the pipeline module offset)
                sw(v1, a0, 56);
                v0 = addu(a1, v0);
                a0 = addiu(v0, 4);
                jal(ctx, 0x4F2A80u, gen::fn_sub_4F6B50_004f6b50);
                lw(a0, gp, -16840);  // 0x7CEB28 (the pipeline module offset)
                v1 = 0x960000;
                v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                v0 = 1;
                sw(v0, gp, -16836);  // 0x7CEB2C (the pipeline module's 'open' flag)
                v1 = addu(v1, a0);
                sw(zero, v1, 52);
                sw(zero, v1, 48);
            }
        }
    } else {
        // 0x004f2a14
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004f2ac4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_4F2F70 [RxPipelineCreate] -- creates a pipeline: a cleared 52-byte record from the pipeline free list; the pipeline, or error 0x80000013 (out of memory) and 0
// 0x004F2F70 sub_4F2F70 -- 148 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4F2F70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004f2f70
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x30000;
    sq(s0, sp, 0x0);
    a1 = v0 | 0x409;
    lw(a0, gp, -16840);  // 0x7CEB28 (the pipeline module offset)
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = 0x960000;
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    v1 = addu(v1, a0);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4F2F9Cu);  // $ra = the return address
    lw(a0, v1, 0);
    call_ptr(ctx, jt);
    s0 = v0;
    if (s0 == 0) {
        // 0x004f2fcc
        charge(ctx, 10);
        v1 = 1;
        v0 = lui(0x8000);
        sw(v1, sp, 0x28);
        a0 = v0 | 0x13;
        a1 = 52;
        jal(ctx, 0x4F2FDCu, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x2C);
        a0 = addiu(sp, 0x28);
        jal(ctx, 0x4F2FE8u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x004f2fb0
        charge(ctx, 7);
        a0 = s0;
        a1 = 0;
        a2 = 52;
        jal(ctx, 0x4F2FB8u, gen::fn_memset_00521408);
        sw(zero, s0, rxpipeline::kLocked);
        v0 = s0;
    }
    // 0x004f2ff4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4F30E0 [rxUnlockScratchAlloc] -- takes $a0 bytes (rounded to 4) from the top of the unlock's scratch area, which grows downwards; the block, or error 0x80000013 (out of memory) and 0 when it would pass the bottom
// 0x004F30E0 sub_4F30E0 -- 108 bytes; frame 0x20: ra sp+0x0
void sub_4F30E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f30e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a0 = addiu(a0, 3);
    sd(ra, sp, 0x0);
    v1 = si(-4);
    a1 = a0 & v1;
    lw(v0, gp, -16824);  // 0x7CEB38 (the unlock's scratch top (allocated downwards))
    lw(v1, gp, -16820);  // 0x7CEB3C (the unlock's scratch bottom)
    v0 = subu(v0, a1);
    v1 = sltu(v0, v1);
    sw(v0, gp, -16824);  // 0x7CEB38 (the unlock's scratch top (allocated downwards))
    if (v1 != 0) {
        // 0x004f3114
        charge(ctx, 12);
        v0 = addu(v0, a1);
        v1 = 1;
        sw(v0, gp, -16824);  // 0x7CEB38 (the unlock's scratch top (allocated downwards))
        v0 = lui(0x8000);
        sw(v1, sp, 0x18);
        a0 = v0 | 0x13;
        jal(ctx, 0x4F3128u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x1C);
        a0 = addiu(sp, 0x18);
        jal(ctx, 0x4F3134u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
        ld(ra, sp, 0x0);
    } else {
        // 0x004f310c
        charge(ctx, 2);
        ld(ra, sp, 0x0);
    }
    // 0x004f3144 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x20);
}


// sub_4F31C0 [rxPipelineCountClusters] -- counts the distinct cluster definitions among a pipeline's nodes' clusters of interest (repeatedly the next larger address); the count
// 0x004F31C0 sub_4F31C0 -- 152 bytes; leaf frame (no stack)
void sub_4F31C0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13};
    // 0x004f31c0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(a3, a0, rxpipeline::kNumNodes);
    v0 = 0;
    t4 = 0;
    a2 = si(-1);
    for (;;) {
        // 0x004f31d0
        charge(ctx, 5);
        t5 = t4;
        at = sltu(0, a3);
        t3 = 0;
        t4 = a2;
        if (at != 0) {
            // 0x004f31e4
            charge(ctx, 1);
            lw(t1, a0, rxpipeline::kNodes);
            for (;;) {
                // 0x004f31e8
                charge(ctx, 5);
                lw(v1, t1, 0);
                lw(a1, v1, 32);
                at = sltu(0, a1);
                t2 = 0;
                if (at != 0) {
                    // 0x004f31fc
                    charge(ctx, 1);
                    lw(t0, v1, 36);
                    for (;;) {
                        // 0x004f3200
                        charge(ctx, 4);
                        lw(v1, t0, 0);
                        at = sltu(t5, v1);
                        if (at != 0) {
                            // 0x004f3210
                            charge(ctx, 3);
                            at = sltu(v1, t4);
                            if (at != 0) {
                                // 0x004f321c
                                charge(ctx, 1);
                                t4 = v1;
                            }
                        }
                        // 0x004f3220
                        charge(ctx, 4);
                        t2 = addiu(t2, 1);
                        v1 = sltu(t2, a1);
                        t0 = addiu(t0, 12);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x004f3230
                charge(ctx, 4);
                t3 = addiu(t3, 1);
                v1 = sltu(t3, a3);
                t1 = addiu(t1, 40);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004f3240
        charge(ctx, 2);
        if (t4 == a2) {
            break;
        }
        // 0x004f3248
        charge(ctx, 2);
        v0 = addiu(v0, 1);
        backedge(ctx);
    }
    // 0x004f3250
    charge(ctx, 2);
}


// sub_4F3260 [rxPipelineResizeSuperBlock] -- resizes a pipeline's super block (RwRealloc) to $a1 bytes and relocates every pointer into it: the nodes, the packet, the input requirements and each node's five pointer fields
// 1, or error 0x80000013 (out of memory) and 0.
// 0x004F3260 sub_4F3260 -- 424 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F3260(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f3260
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v1 = 0x1040000;
    sd(ra, sp, 0x30);
    v0 = 0x960000;
    sq(s2, sp, 0x20);
    a2 = v1 | 0x409;  // &0x1040409
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s2, a0, 32);
    s0 = a1;
    lw(v0, v0, 384);  // 0x960180 (RwRealloc slot)
    a0 = s2;
    jalr(ctx, 0x4F3290u, v0.u());
    if (v0 == 0) {
        // 0x004f33c8
        charge(ctx, 10);
        v0 = 1;
        a1 = s0;
        sw(v0, sp, 0x48);
        v0 = lui(0x8000);
        a0 = v0 | 0x13;
        jal(ctx, 0x4F33D8u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x4C);
        a0 = addiu(sp, 0x48);
        jal(ctx, 0x4F33E4u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x004f32a0
        charge(ctx, 9);
        lw(a0, s1, rxpipeline::kNumNodes);
        v1 = subu(v0, s2);
        sw(v0, s1, rxpipeline::kSuperBlock);
        sw(s0, s1, rxpipeline::kSuperBlockSize);
        lw(v0, s1, rxpipeline::kSuperBlock);
        sw(v0, s1, rxpipeline::kNodes);
        lw(v0, s1, rxpipeline::kPacket);
        if (v0 != 0) {
            // 0x004f32c4
            charge(ctx, 2);
            v0 = addu(v0, v1);
            sw(v0, s1, rxpipeline::kPacket);
        }
        // 0x004f32cc
        charge(ctx, 3);
        lw(v0, s1, rxpipeline::kInputReqs);
        if (v0 != 0) {
            // 0x004f32d8
            charge(ctx, 2);
            v0 = addu(v0, v1);
            sw(v0, s1, rxpipeline::kInputReqs);
        }
        // 0x004f32e0
        charge(ctx, 3);
        at = sltu(0, a0);
        a1 = 0;
        if (at != 0) {
            // 0x004f32ec
            charge(ctx, 1);
            v0 = 0;
            for (;;) {
                // 0x004f32f0
                charge(ctx, 6);
                lw(a2, s1, rxpipeline::kNodes);
                a2 = addu(a2, v0);
                a3 = addiu(a2, 8);
                lw(a2, a2, 8);
                if (a2 != 0) {
                    // 0x004f3308
                    charge(ctx, 2);
                    a2 = addu(a2, v1);
                    sw(a2, a3, 0);
                }
                // 0x004f3310
                charge(ctx, 6);
                lw(a2, s1, rxpipeline::kNodes);
                a2 = addu(a2, v0);
                a3 = addiu(a2, 12);
                lw(a2, a2, 12);
                if (a2 != 0) {
                    // 0x004f3328
                    charge(ctx, 2);
                    a2 = addu(a2, v1);
                    sw(a2, a3, 0);
                }
                // 0x004f3330
                charge(ctx, 6);
                lw(a2, s1, rxpipeline::kNodes);
                a2 = addu(a2, v0);
                a3 = addiu(a2, 16);
                lw(a2, a2, 16);
                if (a2 != 0) {
                    // 0x004f3348
                    charge(ctx, 2);
                    a2 = addu(a2, v1);
                    sw(a2, a3, 0);
                }
                // 0x004f3350
                charge(ctx, 6);
                lw(a2, s1, rxpipeline::kNodes);
                a2 = addu(a2, v0);
                a3 = addiu(a2, 20);
                lw(a2, a2, 20);
                if (a2 != 0) {
                    // 0x004f3368
                    charge(ctx, 2);
                    a2 = addu(a2, v1);
                    sw(a2, a3, 0);
                }
                // 0x004f3370
                charge(ctx, 6);
                lw(a2, s1, rxpipeline::kNodes);
                a2 = addu(a2, v0);
                a3 = addiu(a2, 24);
                lw(a2, a2, 24);
                if (a2 != 0) {
                    // 0x004f3388
                    charge(ctx, 2);
                    a2 = addu(a2, v1);
                    sw(a2, a3, 0);
                }
                // 0x004f3390
                charge(ctx, 6);
                lw(a2, s1, rxpipeline::kNodes);
                a2 = addu(a2, v0);
                a3 = addiu(a2, 28);
                lw(a2, a2, 28);
                if (a2 != 0) {
                    // 0x004f33a8
                    charge(ctx, 2);
                    a2 = addu(a2, v1);
                    sw(a2, a3, 0);
                }
                // 0x004f33b0
                charge(ctx, 4);
                a1 = addiu(a1, 1);
                a2 = sltu(a1, a0);
                v0 = addiu(v0, 40);
                if (a2 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004f33c0
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x004f33f0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_4F3410 [rxPipelineCopyNodes] -- copies pipeline $a1's nodes into pipeline $a0's super-block layout (nodes from the top, each node's outputs in its 128-byte slot), initialisation data duplicated; for $a0 == $a1 only the outputs are re-laid out
// 1, or error 0x80000013 (out of memory) and 0 (an initialisation-data copy failed).
// 0x004F3410 sub_4F3410 -- 624 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F3410(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f3410
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (s4 != s3) {
        // 0x004f343c
        charge(ctx, 4);
        lw(v0, s3, rxpipeline::kNumNodes);
        s2 = addiu(v0, -1);
        if (i64(s2) < 0) {
            // 0x004f344c
            charge(ctx, 1);
            lw(v0, s3, rxpipeline::kNumNodes);
        L_004f3450:
            charge(ctx, 1);
            sw(v0, s4, rxpipeline::kNumNodes);
            goto L_004f3454;
        }
        // 0x004f3548
        charge(ctx, 5);
        v0 = sll(s2, 2);
        s0 = 0x960000;
        v0 = addu(v0, s2);
        s0 = addiu(s0, 376);  // &0x960178 (RwMalloc slot)
        s1 = sll(v0, 3);
        for (;;) {
            // 0x004f355c
            charge(ctx, 23);
            lw(v1, s4, rxpipeline::kNodes);
            a2 = 40;
            lw(v0, s3, rxpipeline::kNodes);
            a0 = addu(v1, s1);
            a1 = addu(v0, s1);
            jal(ctx, 0x4F356Cu, gen::fn_memcpy_00521250);
            lw(v0, s4, rxpipeline::kNodes);
            v0 = addu(v0, s1);
            sw(zero, v0, 12);
            lw(v0, s4, rxpipeline::kNodes);
            v0 = addu(v0, s1);
            sw(zero, v0, 16);
            lw(v0, s4, rxpipeline::kNodes);
            v0 = addu(v0, s1);
            sw(zero, v0, 20);
            lw(v0, s4, rxpipeline::kNodes);
            v0 = addu(v0, s1);
            sw(zero, v0, 24);
            lw(v0, s4, rxpipeline::kNodes);
            v0 = addu(v0, s1);
            lw(a0, v0, 36);
            if (a0 != 0) {
                // 0x004f35cc
                charge(ctx, 12);
                lw(v0, s0, 0);
                v1 = 0x30000;
                a1 = v1 | 0x409;
                jalr(ctx, 0x4F35D4u, v0.u());
                lw(v1, s4, rxpipeline::kNodes);
                v1 = addu(v1, s1);
                sw(v0, v1, 32);
                lw(v0, s4, rxpipeline::kNodes);
                v0 = addu(v0, s1);
                lw(a0, v0, 32);
                if (a0 == 0) {
                    break;
                }
                // 0x004f35fc
                charge(ctx, 7);
                lw(a2, v0, 36);
                lw(v0, s3, rxpipeline::kNodes);
                v0 = addu(v0, s1);
                link(ctx, 0x4F3608u);  // $ra first: the delay slot below depends on it
                lw(a1, v0, 32);
                call(ctx, gen::fn_memcpy_00521250);
                backedge(ctx);
                goto L_004f35b8;
            }
        L_004f35b8:
            charge(ctx, 3);
            s2 = addiu(s2, -1);
            s1 = addiu(s1, -40);
            if (i64(s2) < 0) {
                goto L_004f35c4_16;
            }
            backedge(ctx);
        }
        // 0x004f3618
        charge(ctx, 16);
        v0 = 1;
        sw(v0, sp, 0x78);
        lw(a1, s4, rxpipeline::kNodes);
        v0 = sll(s2, 2);
        v0 = addu(v0, s2);
        v1 = sll(v0, 3);
        v0 = lui(0x8000);
        a0 = v0 | 0x13;
        v0 = addu(v1, a1);
        link(ctx, 0x4F363Cu);  // $ra first: the delay slot below depends on it
        lw(a1, v0, 36);
        call(ctx, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x7C);
        a0 = addiu(sp, 0x78);
        jal(ctx, 0x4F3648u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
        // 0x004f365c (the shared epilogue, written out on this path)
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
L_004f3454:
    charge(ctx, 13);
    lw(a1, gp, -16840);  // 0x7CEB28 (the pipeline module offset)
    a0 = 0x960000;
    a0 = addiu(a0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    lw(v0, s3, rxpipeline::kNumNodes);
    lw(v1, s4, rxpipeline::kNodes);
    a0 = addu(a0, a1);
    lw(a0, a0, 56);
    s0 = addiu(v0, -1);
    v0 = sll(a0, 2);
    v0 = addu(v0, a0);
    v0 = sll(v0, 3);
    s5 = addu(v1, v0);
    if (i64(s0) >= 0) {
        // 0x004f3488
        charge(ctx, 5);
        v0 = sll(s0, 2);
        v1 = sll(s0, 7);
        v0 = addu(v0, s0);
        s2 = addu(s5, v1);
        s1 = sll(v0, 3);
        for (;;) {
            // 0x004f349c
            charge(ctx, 8);
            lw(v0, s4, rxpipeline::kNodes);
            v0 = addu(v0, s1);
            sw(s2, v0, 8);
            lw(v0, s3, rxpipeline::kNodes);
            v0 = addu(v0, s1);
            lw(a1, v0, 8);
            if (a1 != 0) {
                // 0x004f34bc
                charge(ctx, 5);
                lw(v0, s4, rxpipeline::kNodes);
                v0 = addu(v0, s1);
                lw(a0, v0, 8);
                a2 = 128;
                jal(ctx, 0x4F34C8u, gen::fn_memcpy_00521250);
            }
            // 0x004f34d0
            charge(ctx, 4);
            s0 = addiu(s0, -1);
            s2 = addiu(s2, -128);
            s1 = addiu(s1, -40);
            if (i64(s0) < 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004f34e0
    charge(ctx, 11);
    lw(a0, gp, -16840);  // 0x7CEB28 (the pipeline module offset)
    v1 = 0x960000;
    lw(v0, s3, rxpipeline::kNumNodes);
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    a1 = 0;
    v1 = addu(v1, a0);
    lw(v1, v1, 56);
    at = sltu(0, v0);
    v1 = sll(v1, 7);
    a0 = addu(s5, v1);
    if (at == 0) {
        // 0x004f3658
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x004f350c
        charge(ctx, 1);
        v1 = 0;
        for (;;) {
            // 0x004f3510
            charge(ctx, 12);
            sw(zero, a0, 0);
            a1 = addiu(a1, 1);
            sw(zero, a0, 4);
            sw(zero, a0, 8);
            lw(v0, s4, rxpipeline::kNodes);
            v0 = addu(v0, v1);
            sw(a0, v0, 28);
            v1 = addiu(v1, 40);
            lw(v0, s3, rxpipeline::kNumNodes);
            v0 = sltu(a1, v0);
            a0 = addiu(a0, 12);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004f3540
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x004f365c (the shared epilogue, written out on this path)
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
L_004f35c4_16:
    charge(ctx, 2);
    lw(v0, s3, rxpipeline::kNumNodes);
    backedge(ctx);
    goto L_004f3450;
}


// sub_4F3680 [rxPipelineNodeSetup] -- sets up a locked pipeline's next node record from a definition: refuses more than 32 outputs (41) or clusters (40) or a full pipeline (42); outputs all unconnected, a cleared sort record; the count up
// ($a0 = the pipeline, $a1 = the node, $a2 = the definition) 1 / 0.
// 0x004F3680 sub_4F3680 -- 500 bytes; frame 0x80: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F3680(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f3680
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    a0 = s3;
    lw(s0, a2, 44);
    a1 = 0;
    s1 = 1;
    a2 = 40;
    jal(ctx, 0x4F36B8u, gen::fn_memset_00521408);
    at = sltiu(s0, 33);
    if (at == 0) {
        // 0x004f3778
        charge(ctx, 9);
        v0 = s1;
        a0 = 41;
        link(ctx, 0x4F3780u);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x78);
        call(ctx, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x7C);
        a0 = addiu(sp, 0x78);
        jal(ctx, 0x4F378Cu, gen::fn_sub_4C1C50_004c1c50);
        s1 = 0;
        backedge(ctx);
    }
    // 0x004f36cc
    charge(ctx, 4);
    lw(v0, s2, rxdef::kNumClusters);
    at = sltiu(v0, 33);
    if (at == 0) {
        // 0x004f379c
        charge(ctx, 9);
        v0 = 1;
        a0 = 40;
        link(ctx, 0x4F37A4u);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x70);
        call(ctx, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x74);
        a0 = addiu(sp, 0x70);
        jal(ctx, 0x4F37B0u, gen::fn_sub_4C1C50_004c1c50);
        s1 = 0;
        backedge(ctx);
    }
    // 0x004f36dc
    charge(ctx, 8);
    lw(v1, gp, -16840);  // 0x7CEB28 (the pipeline module offset)
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = addu(v0, v1);
    lw(v0, v0, 56);
    at = sltu(s0, v0);
    if (at == 0) {
        // 0x004f37c0
        charge(ctx, 9);
        v0 = 1;
        a0 = 42;
        link(ctx, 0x4F37C8u);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x68);
        call(ctx, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x6C);
        a0 = addiu(sp, 0x68);
        jal(ctx, 0x4F37D4u, gen::fn_sub_4C1C50_004c1c50);
        s1 = 0;
        backedge(ctx);
    }
    // 0x004f36fc
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x004f3704
        charge(ctx, 19);
        lw(a1, gp, -16840);  // 0x7CEB28 (the pipeline module offset)
        a0 = 0x960000;
        a0 = addiu(a0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        lw(v0, s4, rxpipeline::kNumNodes);
        lw(v1, s4, rxpipeline::kNodes);
        a0 = addu(a0, a1);
        lw(a1, a0, 56);
        v0 = sll(v0, 7);
        a0 = sll(a1, 2);
        a0 = addu(a0, a1);
        a0 = sll(a0, 3);
        v1 = addu(v1, a0);
        a0 = addu(v1, v0);
        sw(a0, s3, rxpnode::kOutputs);
        sw(s0, s3, rxpnode::kNumOutputs);
        lw(v0, s3, rxpnode::kNumOutputs);
        at = sltu(0, v0);
        a2 = 0;
        if (at == 0) {
            // 0x004f37e4
            charge(ctx, 1);
            lw(a1, gp, -16840);  // 0x7CEB28 (the pipeline module offset)
        } else {
            // 0x004f3750
            charge(ctx, 1);
            v1 = si(-1);
            for (;;) {
                // 0x004f3754
                charge(ctx, 7);
                sw(v1, a0, 0);
                a2 = addiu(a2, 1);
                lw(v0, s3, rxpnode::kNumOutputs);
                a0 = addiu(a0, 4);
                v0 = sltu(a2, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004f3770
            charge(ctx, 2);
            lw(a1, gp, -16840);  // 0x7CEB28 (the pipeline module offset)
        }
        // 0x004f37e8
        charge(ctx, 26);
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        lw(v1, s4, rxpipeline::kNumNodes);
        lw(a0, s4, rxpipeline::kNodes);
        v0 = addu(v0, a1);
        lw(a2, v0, 56);
        a1 = sll(a2, 2);
        v0 = sll(v1, 1);
        a1 = addu(a1, a2);
        v0 = addu(v0, v1);
        a1 = sll(a1, 3);
        v1 = sll(a2, 7);
        a0 = addu(a0, a1);
        v0 = sll(v0, 2);
        v1 = addu(a0, v1);
        v0 = addu(v1, v0);
        sw(zero, v0, 0);
        sw(zero, v0, 4);
        sw(zero, v0, 8);
        sw(v0, s3, rxpnode::kTopSortData);
        sw(zero, s3, rxpnode::kInitData);
        sw(zero, s3, rxpnode::kInitDataSize);
        sw(s2, s3, rxpnode::kNodeDef);
        lw(v0, s4, rxpipeline::kNumNodes);
        v0 = addiu(v0, 1);
        sw(v0, s4, rxpipeline::kNumNodes);
    }
    // 0x004f3850 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = s1;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}


// sub_4F3880 [rxTopSortCountInputs] -- the topological sort's start: each node's sort record cleared, then each connected output adds one to its target's in-degree
// 0x004F3880 sub_4F3880 -- 240 bytes; leaf frame (no stack)
void sub_4F3880(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x004f3880
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(a1, a0, 4);
    lw(a3, a0, 8);
    at = sltu(0, a1);
    a2 = 0;
    if (at != 0) {
        for (;;) {
            // 0x004f3894
            charge(ctx, 3);
            lw(v1, a3, 0);
            if (v1 != 0) {
                // 0x004f38a0
                charge(ctx, 4);
                lw(v1, a3, 28);
                sw(zero, v1, 4);
                lw(v1, a3, 28);
                sw(zero, v1, 0);
            }
            // 0x004f38b0
            charge(ctx, 5);
            lw(a1, a0, 4);
            a2 = addiu(a2, 1);
            v1 = sltu(a2, a1);
            a3 = addiu(a3, 40);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004f38c4
        charge(ctx, 1);
    }
    // 0x004f38c8
    charge(ctx, 4);
    lw(t1, a0, 8);
    at = sltu(0, a1);
    t0 = 0;
    if (at != 0) {
        // 0x004f38d8
        charge(ctx, 1);
        a2 = si(-1);
        for (;;) {
            // 0x004f38dc
            charge(ctx, 3);
            lw(v1, t1, 0);
            if (v1 != 0) {
                // 0x004f38e8
                charge(ctx, 3);
                lw(t3, t1, 4);
                if (t3 != 0) {
                    // 0x004f38f4
                    charge(ctx, 1);
                    lw(t2, t1, 8);
                    for (;;) {
                        // 0x004f38f8
                        charge(ctx, 3);
                        lw(a3, t2, 0);
                        if (a3 != a2) {
                            // 0x004f3940
                            charge(ctx, 10);
                            lw(v1, a0, 8);
                            a1 = sll(a3, 2);
                            a1 = addu(a1, a3);
                            a1 = sll(a1, 3);
                            v1 = addu(v1, a1);
                            lw(a1, v1, 28);
                            lw(v1, a1, 0);
                            v1 = addiu(v1, 1);
                            sw(v1, a1, 0);
                            backedge(ctx);
                        } else {
                            // 0x004f3904
                            charge(ctx, 1);
                        }
                        // 0x004f3908
                        charge(ctx, 5);
                        t3 = addiu(t3, -1);
                        t2 = addiu(t2, 4);
                        if (t3 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004f391c
                    charge(ctx, 1);
                }
            }
            // 0x004f3920
            charge(ctx, 5);
            lw(v1, a0, 4);
            t0 = addiu(t0, 1);
            v1 = sltu(t0, v1);
            t1 = addiu(t1, 40);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004f3934
        charge(ctx, 1);
    }
    // 0x004f3938
    charge(ctx, 2);
    // 0x004f3968
    charge(ctx, 2);
}


// sub_4F3970 [rxTopSortPlace] -- places a node at the next sorted position: swaps it there (node record, outputs, sort record, every output index renumbered), then each target whose inputs are now all placed follows, recursively
// 0x004F3970 sub_4F3970 -- 996 bytes; frame 0x90: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F3970(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13};
    // 0x004f3970
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(t0, a0, 4);
    s0 = a0;
    if (t0 != a1) {
        // 0x004f3994
        charge(ctx, 16);
        lw(a2, s0, 0);
        v1 = sll(t0, 2);
        a0 = addu(v1, t0);
        t3 = 0;
        v1 = sll(a1, 2);
        a3 = sll(a0, 3);
        v1 = addu(v1, a1);
        a0 = sll(v1, 3);
        lw(v1, a2, 8);
        v1 = addiu(v1, 8);
        a2 = addu(v1, a3);
        v1 = addu(v1, a0);
        lw(a2, a2, 0);
        lw(v1, v1, 0);
        t2 = a2;
        t1 = v1;
        for (;;) {
            // 0x004f39d4
            charge(ctx, 37);
            lw(t6, t2, 0);
            t3 = addiu(t3, 8);
            lw(t5, t1, 0);
            t4 = sltiu(t3, 32);
            sw(t5, t2, 0);
            sw(t6, t1, 0);
            lw(t6, t2, 4);
            lw(t5, t1, 4);
            sw(t5, t2, 4);
            sw(t6, t1, 4);
            lw(t6, t2, 8);
            lw(t5, t1, 8);
            sw(t5, t2, 8);
            sw(t6, t1, 8);
            lw(t6, t2, 12);
            lw(t5, t1, 12);
            sw(t5, t2, 12);
            sw(t6, t1, 12);
            lw(t6, t2, 16);
            lw(t5, t1, 16);
            sw(t5, t2, 16);
            sw(t6, t1, 16);
            lw(t6, t2, 20);
            lw(t5, t1, 20);
            sw(t5, t2, 20);
            sw(t6, t1, 20);
            lw(t6, t2, 24);
            lw(t5, t1, 24);
            sw(t5, t2, 24);
            sw(t6, t1, 24);
            lw(t6, t2, 28);
            lw(t5, t1, 28);
            sw(t5, t2, 28);
            sw(t6, t1, 28);
            t2 = addiu(t2, 32);
            t1 = addiu(t1, 32);
            if (t4 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004f3a68
        charge(ctx, 100);
        lw(t2, s0, 0);
        t1 = 0;
        lw(t2, t2, 8);
        t2 = addu(a3, t2);
        sw(v1, t2, 8);
        lw(v1, s0, 0);
        lw(v1, v1, 8);
        v1 = addu(a0, v1);
        sw(a2, v1, 8);
        lw(v1, s0, 0);
        lw(v1, v1, 8);
        v1 = addiu(v1, 28);
        a2 = addu(v1, a3);
        lw(t2, a2, 0);
        v1 = addu(v1, a0);
        lw(a2, v1, 0);
        lwc1(f5, t2, 0);
        lwc1(f4, t2, 4);
        lwc1(f3, t2, 8);
        lwc1(f2, a2, 0);
        lwc1(f1, a2, 4);
        lwc1(f0, a2, 8);
        swc1(f5, sp, 0x80);
        swc1(f4, sp, 0x84);
        swc1(f3, sp, 0x88);
        swc1(f2, t2, 0);
        swc1(f1, t2, 4);
        swc1(f0, t2, 8);
        swc1(f5, a2, 0);
        swc1(f4, a2, 4);
        swc1(f3, a2, 8);
        lw(v1, s0, 0);
        lw(v1, v1, 8);
        v1 = addu(a3, v1);
        sw(a2, v1, 28);
        lw(v1, s0, 0);
        lw(v1, v1, 8);
        v1 = addu(a0, v1);
        sw(t2, v1, 28);
        lw(v1, s0, 0);
        lw(v1, v1, 8);
        a2 = addu(v1, a3);
        v1 = addu(v1, a0);
        lwc1(f13, a2, 0);
        lwc1(f12, a2, 4);
        lwc1(f11, a2, 8);
        lwc1(f10, a2, 12);
        lwc1(f9, a2, 16);
        lwc1(f8, a2, 20);
        lwc1(f7, a2, 24);
        lwc1(f6, a2, 28);
        lwc1(f5, a2, 32);
        lwc1(f4, a2, 36);
        lwc1(f3, v1, 0);
        lwc1(f2, v1, 4);
        lwc1(f1, v1, 8);
        lwc1(f0, v1, 12);
        swc1(f13, sp, 0x50);
        swc1(f12, sp, 0x54);
        swc1(f11, sp, 0x58);
        swc1(f10, sp, 0x5C);
        swc1(f9, sp, 0x60);
        swc1(f3, a2, 0);
        swc1(f2, a2, 4);
        swc1(f1, a2, 8);
        swc1(f0, a2, 12);
        lwc1(f3, v1, 16);
        lwc1(f2, v1, 20);
        lwc1(f1, v1, 24);
        lwc1(f0, v1, 28);
        swc1(f8, sp, 0x64);
        swc1(f7, sp, 0x68);
        swc1(f6, sp, 0x6C);
        swc1(f5, sp, 0x70);
        swc1(f3, a2, 16);
        swc1(f2, a2, 20);
        swc1(f1, a2, 24);
        swc1(f0, a2, 28);
        lwc1(f1, v1, 32);
        lwc1(f0, v1, 36);
        swc1(f1, a2, 32);
        swc1(f0, a2, 36);
        lw(v1, s0, 0);
        lw(v1, v1, 8);
        v1 = addu(v1, a0);
        swc1(f13, v1, 0);
        swc1(f12, v1, 4);
        swc1(f11, v1, 8);
        swc1(f10, v1, 12);
        swc1(f9, v1, 16);
        swc1(f8, v1, 20);
        swc1(f7, v1, 24);
        swc1(f6, v1, 28);
        swc1(f5, v1, 32);
        swc1(f4, v1, 36);
        lw(a0, s0, 0);
        lw(v1, a0, 4);
        at = sltu(0, v1);
        swc1(f4, sp, 0x74);
        if (at != 0) {
            // 0x004f3bf8
            charge(ctx, 1);
            t2 = 0;
            for (;;) {
                // 0x004f3bfc
                charge(ctx, 6);
                lw(v1, a0, 8);
                a2 = addu(v1, t2);
                lw(v1, a2, 4);
                at = sltu(0, v1);
                t3 = 0;
                if (at != 0) {
                    // 0x004f3c14
                    charge(ctx, 1);
                    a3 = 0;
                    for (;;) {
                        // 0x004f3c18
                        charge(ctx, 5);
                        lw(v1, a2, 8);
                        a0 = addu(v1, a3);
                        lw(v1, a0, 0);
                        if (t0 == v1) {
                            // 0x004f3ce0
                            charge(ctx, 2);
                            sw(a1, a0, 0);
                            backedge(ctx);
                        } else {
                            // 0x004f3c2c
                            charge(ctx, 2);
                            if (a1 == v1) {
                                // 0x004f3c34
                                charge(ctx, 1);
                                sw(t0, a0, 0);
                            }
                        }
                        // 0x004f3c38
                        charge(ctx, 5);
                        lw(v1, a2, 4);
                        t3 = addiu(t3, 1);
                        v1 = sltu(t3, v1);
                        a3 = addiu(a3, 4);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004f3c4c
                    charge(ctx, 1);
                }
                // 0x004f3c50
                charge(ctx, 6);
                lw(a0, s0, 0);
                t1 = addiu(t1, 1);
                lw(v1, a0, 4);
                v1 = sltu(t1, v1);
                t2 = addiu(t2, 40);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x004f3c68
    charge(ctx, 12);
    lw(v1, s0, 0);
    lw(a2, s0, 4);
    lw(a0, v1, 8);
    a1 = sll(a2, 2);
    a1 = addu(a1, a2);
    a1 = sll(a1, 3);
    v1 = addiu(a2, 1);
    s1 = addu(a0, a1);
    sw(v1, s0, 4);
    lw(v1, s1, 4);
    if (v1 != 0) {
        // 0x004f3c98
        charge(ctx, 3);
        at = sltu(0, v1);
        s2 = 0;
        if (at != 0) {
            // 0x004f3ca4
            charge(ctx, 1);
            s3 = 0;
            for (;;) {
                // 0x004f3ca8
                charge(ctx, 6);
                lw(a0, s1, 8);
                v1 = si(-1);
                a0 = addu(a0, s3);
                lw(a1, a0, 0);
                if (a1 != v1) {
                    // 0x004f3ce8
                    charge(ctx, 15);
                    lw(a2, s0, 0);
                    v1 = sll(a1, 2);
                    v1 = addu(v1, a1);
                    a0 = sll(v1, 3);
                    lw(v1, a2, 8);
                    a2 = addu(v1, a0);
                    lw(a0, a2, 28);
                    lw(v1, a0, 4);
                    v1 = addiu(v1, 1);
                    sw(v1, a0, 4);
                    lw(v1, a2, 28);
                    lw(a0, v1, 0);
                    lw(v1, v1, 4);
                    if (a0 != v1) {
                        backedge(ctx);
                    } else {
                        // 0x004f3d24
                        charge(ctx, 4);
                        a0 = s0;
                        jal(ctx, 0x4F3D24u, gen::fn_sub_4F3970_004f3970);
                        backedge(ctx);
                    }
                }
                // 0x004f3cc0
                charge(ctx, 5);
                lw(v1, s1, 4);
                s2 = addiu(s2, 1);
                v1 = sltu(s2, v1);
                s3 = addiu(s3, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004f3cd4
            charge(ctx, 1);
        }
    }
    // 0x004f3cd8
    charge(ctx, 2);
    // 0x004f3d38
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}


// sub_4F3D60 [rxPipelineTopSort] -- sorts a pipeline's nodes topologically from its entry point: in-degrees (sub_4F3880), the entry must have none (error 36), then the placement (sub_4F3970); the pipeline, or 0 when a node is unreachable (a cycle)
// 0x004F3D60 sub_4F3D60 -- 340 bytes; frame 0x40: ra sp+0x10, s0 sp+0x0 (sq), s0 sp+0x38
void sub_4F3D60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f3d60
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    sw(zero, sp, 0x3C);
    link(ctx, 0x4F3D74u);  // $ra first: the delay slot below depends on it
    sw(s0, sp, 0x38);
    call(ctx, gen::fn_sub_4F3880_004f3880);
    lw(a1, s0, rxpipeline::kEntryPoint);
    lw(a0, s0, rxpipeline::kNodes);
    v0 = sll(a1, 2);
    v0 = addu(v0, a1);
    v0 = sll(v0, 3);
    v0 = addu(v0, a0);
    lw(v0, v0, 28);
    lw(v0, v0, 0);
    if (v0 != 0) {
        // 0x004f3e4c
        charge(ctx, 9);
        v0 = 1;
        a0 = 36;
        link(ctx, 0x4F3E54u);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x30);
        call(ctx, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x34);
        a0 = addiu(sp, 0x30);
        jal(ctx, 0x4F3E60u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x004f3da4
        charge(ctx, 4);
        lw(v1, s0, rxpipeline::kNumNodes);
        at = sltu(0, v1);
        a3 = 0;
        if (at != 0) {
            // 0x004f3db4
            charge(ctx, 1);
            a2 = 0;
            for (;;) {
                // 0x004f3db8
                charge(ctx, 2);
                if (a3 != a1) {
                    // 0x004f3e70
                    charge(ctx, 5);
                    v0 = addu(a0, a2);
                    lw(v0, v0, 28);
                    lw(v0, v0, 0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    goto L_004f3dc0;
                }
            L_004f3dc0:
                charge(ctx, 6);
                a3 = addiu(a3, 1);
                v0 = sltu(a3, v1);
                a2 = addiu(a2, 40);
                if (v0 == 0) {
                    goto L_004f3dd8;
                }
                backedge(ctx);
            }
            // 0x004f3e84
            charge(ctx, 8);
            v0 = 1;
            a0 = 34;
            link(ctx, 0x4F3E8Cu);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x28);
            call(ctx, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x2C);
            a0 = addiu(sp, 0x28);
            jal(ctx, 0x4F3E98u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
            // 0x004f3ea4 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_004f3dd8:
        charge(ctx, 6);
        a0 = addiu(sp, 0x38);
        jal(ctx, 0x4F3DD8u, gen::fn_sub_4F3970_004f3970);
        lw(a0, s0, rxpipeline::kNumNodes);
        at = sltu(0, a0);
        a1 = 0;
        if (at != 0) {
            // 0x004f3df0
            charge(ctx, 1);
            lw(a2, s0, rxpipeline::kNodes);
            for (;;) {
                // 0x004f3df4
                charge(ctx, 5);
                lw(v0, a2, 28);
                lw(v1, v0, 0);
                lw(v0, v0, 4);
                if (v1 != v0) {
                    goto L_004f3e08_8;
                }
                // 0x004f3e2c
                charge(ctx, 4);
                a1 = addiu(a1, 1);
                v0 = sltu(a1, a0);
                a2 = addiu(a2, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004f3e3c
            charge(ctx, 1);
        }
        // 0x004f3e40
        charge(ctx, 3);
        sw(zero, s0, rxpipeline::kEntryPoint);
        v0 = s0;
    }
    // 0x004f3ea4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_004f3e08_8:
    charge(ctx, 9);
    v0 = 1;
    a0 = 28;
    link(ctx, 0x4F3E10u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x20);
    call(ctx, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0x24);
    a0 = addiu(sp, 0x20);
    jal(ctx, 0x4F3E1Cu, gen::fn_sub_4C1C50_004c1c50);
    v0 = 0;
    // 0x004f3ea4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4F3F80 [RxLockedPipeUnlock] -- unlocks a locked pipeline: sizes the super block, sorts the nodes (sub_4F3D60), lays out outputs and sort records, runs the cluster passes (sub_4F6140), shrinks the block, then each node's init / pipeline-node init / config
// Refused for a null (error 0x80000016) or unlocked (52) pipeline, or an entry point without a node (36). The
// definitions' use counts go up (nodeInit on the first); a failing init undoes the nodes initialised so far
// (pipelineNodeTerm, nodeTerm) and leaves the pipeline locked. The pipeline (+0 = 0), or 0.
// 0x004F3F80 sub_4F3F80 -- 1728 bytes; frame 0xC0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F3F80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004f3f80
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (s4 != 0) {
        // 0x004f3fb4
        charge(ctx, 3);
        lw(v0, s4, rxpipeline::kLocked);
        if (v0 == 0) {
            goto L_004f45bc;
        }
        // 0x004f3fc0
        charge(ctx, 3);
        lw(v0, s4, rxpipeline::kNumNodes);
        if (v0 != 0) {
            // 0x004f3fcc
            charge(ctx, 6);
            lw(a1, s4, rxpipeline::kEntryPoint);
            s6 = 0;
            s7 = 0;
            at = sltu(a1, v0);
            fp = 0;
            if (at != 0) {
                // 0x004f3fe4
                charge(ctx, 8);
                lw(v0, s4, rxpipeline::kNodes);
                v1 = sll(a1, 2);
                v1 = addu(v1, a1);
                v1 = sll(v1, 3);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                if (v0 == 0) {
                    goto L_004f41d0;
                }
                // 0x004f4004: the super block's size: the distinct clusters, nodes, outputs, sort records, slots, private data
                charge(ctx, 21);
                jal(ctx, 0x4F4004u, gen::fn_sub_4F31C0_004f31c0);
                lw(a2, gp, -16840);  // 0x7CEB28 (the pipeline module offset)
                v1 = 0x960000;
                v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                lw(a0, s4, rxpipeline::kNumNodes);
                a1 = 0;
                v1 = addu(v1, a2);
                lw(t0, v1, 56);
                at = sltu(0, a0);
                v1 = sll(a0, 2);
                a3 = sll(t0, 7);
                v1 = addu(v1, a0);
                a2 = sll(v1, 3);
                v1 = sll(t0, 1);
                v1 = addu(v1, t0);
                v1 = sll(v1, 2);
                t0 = addu(v1, t0);
                t0 = sll(t0, 2);
                s1 = addu(t0, a3);
                if (at != 0) {
                    // 0x004f4058
                    charge(ctx, 3);
                    at = sltiu(a0, 9);
                    t1 = addiu(a0, -8);
                    if (at == 0) {
                        // 0x004f4064
                        charge(ctx, 3);
                        lw(a3, s4, rxpipeline::kNodes);
                        lw(a3, a3, 4);
                        t0 = sll(a3, 2);
                        for (;;) {
                            // 0x004f4070
                            charge(ctx, 11);
                            a2 = addu(a2, t0);
                            a1 = addiu(a1, 8);
                            a2 = addu(a2, t0);
                            a3 = sltu(a1, t1);
                            a2 = addu(a2, t0);
                            a2 = addu(a2, t0);
                            a2 = addu(a2, t0);
                            a2 = addu(a2, t0);
                            a2 = addu(a2, t0);
                            a2 = addu(a2, t0);
                            if (a3 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004f409c
                        charge(ctx, 1);
                    }
                    // 0x004f40a0
                    charge(ctx, 3);
                    at = sltu(a1, a0);
                    if (at != 0) {
                        // 0x004f40ac
                        charge(ctx, 3);
                        lw(a3, s4, rxpipeline::kNodes);
                        lw(a3, a3, 4);
                        t0 = sll(a3, 2);
                        for (;;) {
                            // 0x004f40b8
                            charge(ctx, 7);
                            a1 = addiu(a1, 1);
                            a2 = addu(a2, t0);
                            a3 = sltu(a1, a0);
                            if (a3 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004f40d4
                        charge(ctx, 1);
                    }
                }
                // 0x004f40d8
                charge(ctx, 25);
                t0 = addu(v1, a2);
                mult(a2, a0, v0);
                a3 = sll(v0, 3);
                v1 = addu(a3, v0);
                v1 = sll(v1, 2);
                v1 = addiu(v1, 20);
                mult1(a1, a0, v1);
                v1 = sll(a2, 4);
                v1 = addu(a1, v1);
                a2 = sll(a2, 2);
                v1 = addu(t0, v1);
                a1 = 0;
                t0 = addu(a1, a3);
                a1 = sll(v0, 1);
                a3 = addu(a1, v0);
                a3 = sll(a3, 2);
                a1 = addiu(v0, 1);
                a3 = addu(t0, a3);
                a2 = addu(a3, a2);
                mult(a1, a0, a1);
                at = sltu(0, a0);
                t1 = 0;
                a1 = sll(a1, 2);
                a1 = addu(a2, a1);
                if (at != 0) {
                    // 0x004f413c
                    charge(ctx, 1);
                    lw(t0, s4, rxpipeline::kNodes);
                    for (;;) {
                        // 0x004f4140
                        charge(ctx, 4);
                        lw(a3, t0, 0);
                        lw(a2, a3, 52);
                        if (a2 != 0) {
                            // 0x004f4150
                            charge(ctx, 2);
                            a1 = addu(a1, a2);
                        }
                        // 0x004f4158
                        charge(ctx, 7);
                        lw(a3, a3, 32);
                        t1 = addiu(t1, 1);
                        t0 = addiu(t0, 40);
                        a2 = sltu(t1, a0);
                        a3 = sll(a3, 2);
                        a1 = addu(a1, a3);
                        if (a2 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004f4174
                    charge(ctx, 1);
                }
                // 0x004f4178
                charge(ctx, 10);
                a0 = addiu(v0, -1);
                v0 = sll(a0, 3);
                v0 = subu(v0, a0);
                v0 = sll(v0, 2);
                v0 = addiu(v0, 48);
                v0 = addu(a1, v0);
                v0 = addu(v1, v0);
                at = sltu(s1, v0);
                if (at != 0) {
                    // 0x004f41a0
                    charge(ctx, 1);
                    s1 = v0;
                }
                // 0x004f41a4: grown (sub_4F3260) when it is smaller
                charge(ctx, 4);
                lw(v0, s4, rxpipeline::kSuperBlockSize);
                at = sltu(v0, s1);
                if (at != 0) {
                    // 0x004f41b4
                    charge(ctx, 5);
                    a0 = s4;
                    a1 = s1;
                    jal(ctx, 0x4F41B8u, gen::fn_sub_4F3260_004f3260);
                    if (v0 != 0) {
                        goto L_004f41f4;
                    }
                    // 0x004f41c8
                    charge(ctx, 2);
                    v0 = 0;
                    // 0x004f4610 (the shared epilogue, written out on this path)
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
                    sp = addiu(sp, 0xC0);
                    return;
                }
            L_004f41f4:
                charge(ctx, 9);
                lw(v0, s4, rxpipeline::kSuperBlock);
                a0 = s4;
                v0 = addu(v0, s1);
                sw(zero, gp, -16820);  // 0x7CEB3C (the unlock's scratch bottom)
                link(ctx, 0x4F4204u);  // $ra first: the delay slot below depends on it
                sw(v0, gp, -16824);  // 0x7CEB38 (the unlock's scratch top (allocated downwards))
                call(ctx, gen::fn_sub_4F3D60_004f3d60);
                s4 = v0;
                if (s4 == 0) {
                    // 0x004f4308
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x004f4218
                    charge(ctx, 22);
                    lw(a2, gp, -16840);  // 0x7CEB28 (the pipeline module offset)
                    a1 = 0x960000;
                    a1 = addiu(a1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
                    lw(v1, s4, rxpipeline::kNumNodes);
                    lw(v0, s4, rxpipeline::kSuperBlock);
                    lw(a0, s4, rxpipeline::kNodes);
                    a1 = addu(a1, a2);
                    lw(a2, a1, 56);
                    s0 = addiu(v1, -1);
                    v0 = addu(v0, s1);
                    v1 = sll(s0, 1);
                    v1 = addu(v1, s0);
                    s3 = addiu(v0, -12);
                    v0 = sll(v1, 2);
                    a1 = sll(a2, 2);
                    v1 = sll(a2, 7);
                    a1 = addu(a1, a2);
                    a1 = sll(a1, 3);
                    s1 = addu(a0, a1);
                    v1 = addu(s1, v1);
                    s2 = addu(v1, v0);
                    if (i64(s0) >= 0) {
                        // 0x004f4310: the nodes' sort records copied to the top of the super block
                        charge(ctx, 3);
                        v0 = sll(s0, 2);
                        v0 = addu(v0, s0);
                        s5 = sll(v0, 3);
                        for (;;) {
                            // 0x004f431c
                            charge(ctx, 12);
                            a0 = s3;
                            a1 = s2;
                            a2 = 12;
                            jal(ctx, 0x4F4324u, gen::fn_memcpy_00521250);
                            lw(v0, s4, rxpipeline::kNodes);
                            s0 = addiu(s0, -1);
                            s2 = addiu(s2, -12);
                            v0 = addu(v0, s5);
                            sw(s3, v0, 28);
                            s5 = addiu(s5, -40);
                            s3 = addiu(s3, -12);
                            if (i64(s0) < 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004f434c
                        charge(ctx, 2);
                        lw(v1, s4, rxpipeline::kNumNodes);
                        backedge(ctx);
                    } else {
                        // 0x004f4270
                        charge(ctx, 1);
                        lw(v1, s4, rxpipeline::kNumNodes);
                    }
                    // 0x004f4274
                    charge(ctx, 8);
                    s5 = 0;
                    lw(a1, s4, rxpipeline::kNodes);
                    v0 = sll(v1, 2);
                    at = sltu(0, v1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 3);
                    s3 = addu(a1, v0);
                    if (at != 0) {
                        // 0x004f4294: each node's outputs copied after the nodes
                        charge(ctx, 1);
                        s0 = 0;
                        for (;;) {
                            // 0x004f4298
                            charge(ctx, 4);
                            v1 = addu(a1, s0);
                            lw(v0, v1, 4);
                            if (v0 != 0) {
                                // 0x004f4354
                                charge(ctx, 8);
                                a2 = sll(v0, 2);
                                a0 = s3;
                                a1 = s1;
                                jal(ctx, 0x4F435Cu, gen::fn_memcpy_00521250);
                                lw(v0, s4, rxpipeline::kNodes);
                                v0 = addu(v0, s0);
                                sw(s3, v0, 8);
                                backedge(ctx);
                            } else {
                                // 0x004f42a8
                                charge(ctx, 2);
                                sw(zero, v1, 8);
                            }
                            // 0x004f42b0
                            charge(ctx, 12);
                            lw(a1, s4, rxpipeline::kNodes);
                            lw(v0, s4, rxpipeline::kNumNodes);
                            s5 = addiu(s5, 1);
                            s1 = addiu(s1, 128);
                            v1 = addu(a1, s0);
                            lw(a0, v1, 4);
                            v0 = sltu(s5, v0);
                            s0 = addiu(s0, 40);
                            v1 = sll(a0, 2);
                            s6 = addu(s6, a0);
                            s3 = addu(s3, v1);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                    // 0x004f42e0: the scratch area set, then the cluster passes (sub_4F6140)
                    charge(ctx, 8);
                    v0 = sll(s6, 2);
                    v0 = addu(s1, v0);
                    a0 = s4;
                    sw(v0, gp, -16820);  // 0x7CEB3C (the unlock's scratch bottom)
                    link(ctx, 0x4F42F0u);  // $ra first: the delay slot below depends on it
                    sw(s2, gp, -16824);  // 0x7CEB38 (the unlock's scratch top (allocated downwards))
                    call(ctx, gen::fn_sub_4F6140_004f6140);
                    if (v0 == 0) {
                        // 0x004f4378: the super block shrunk to what was used
                        charge(ctx, 7);
                        lw(v1, s4, rxpipeline::kSuperBlock);
                        lw(v0, gp, -16820);  // 0x7CEB3C (the unlock's scratch bottom)
                        a0 = s4;
                        a1 = subu(v0, v1);
                        jal(ctx, 0x4F4384u, gen::fn_sub_4F3260_004f3260);
                        if (v0 != 0) {
                            // 0x004f4394
                            charge(ctx, 4);
                            lw(a0, s4, rxpipeline::kNumNodes);
                            at = sltu(0, a0);
                            v1 = 0;
                            if (at != 0) {
                                // 0x004f43a4
                                charge(ctx, 1);
                                a1 = 0;
                                for (;;) {
                                    // 0x004f43a8
                                    charge(ctx, 8);
                                    lw(v0, s4, rxpipeline::kNodes);
                                    v1 = addiu(v1, 1);
                                    v0 = addu(v0, a1);
                                    sw(zero, v0, 28);
                                    lw(a0, s4, rxpipeline::kNumNodes);
                                    v0 = sltu(v1, a0);
                                    a1 = addiu(a1, 40);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                            }
                            // 0x004f43c8: each node, the last first: its definition's use count up (node init on the first use), the pipeline-node init
                            charge(ctx, 3);
                            s0 = addiu(a0, -1);
                            if (i64(s0) >= 0) {
                                // 0x004f43d4
                                charge(ctx, 3);
                                v0 = sll(s0, 2);
                                v0 = addu(v0, s0);
                                s2 = sll(v0, 3);
                                for (;;) {
                                    // 0x004f43e0
                                    charge(ctx, 7);
                                    lw(v0, s4, rxpipeline::kNodes);
                                    s1 = addu(v0, s2);
                                    lw(s3, s1, 0);
                                    lw(v1, s3, 60);
                                    v0 = addiu(v1, 1);
                                    sw(v0, s3, 60);
                                    if (v1 == 0) {
                                        // 0x004f43fc
                                        charge(ctx, 3);
                                        lw(v0, s3, 8);
                                        if (v0 == 0) {
                                            goto L_004f442c;
                                        }
                                        // 0x004f4408
                                        charge(ctx, 4);
                                        a0 = s3;
                                        jalr(ctx, 0x4F4408u, v0.u());
                                        if (v0 != 0) {
                                            goto L_004f442c;
                                        }
                                        goto L_004f4418_50;
                                    }
                                L_004f442c:
                                    charge(ctx, 3);
                                    lw(v0, s3, 16);
                                    if (v0 != 0) {
                                        // 0x004f4438
                                        charge(ctx, 4);
                                        a0 = s1;
                                        jalr(ctx, 0x4F4438u, v0.u());
                                        if (v0 != 0) {
                                            goto L_004f4488;
                                        }
                                        goto L_004f4448_53;
                                    }
                                L_004f4488:
                                    charge(ctx, 3);
                                    s0 = addiu(s0, -1);
                                    s2 = addiu(s2, -40);
                                    if (i64(s0) < 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004f4494
                                charge(ctx, 2);
                            }
                        L_004f458c:
                            charge(ctx, 2);
                            if (s7 != 0) {
                                backedge(ctx);
                            } else {
                                // 0x004f4594
                                charge(ctx, 2);
                                lw(v0, s4, rxpipeline::kNumNodes);
                                backedge(ctx);
                                // 0x004f449c: each node's config callback
                                charge(ctx, 3);
                                s0 = addiu(v0, -1);
                                if (i64(s0) >= 0) {
                                    // 0x004f44a8
                                    charge(ctx, 3);
                                    v0 = sll(s0, 2);
                                    v0 = addu(v0, s0);
                                    s1 = sll(v0, 3);
                                    for (;;) {
                                        // 0x004f44b4
                                        charge(ctx, 6);
                                        lw(v0, s4, rxpipeline::kNodes);
                                        a0 = addu(v0, s1);
                                        lw(v0, a0, 0);
                                        lw(v0, v0, 24);
                                        if (v0 != 0) {
                                            // 0x004f44cc
                                            charge(ctx, 4);
                                            a1 = s4;
                                            jalr(ctx, 0x4F44CCu, v0.u());
                                            if (v0 != 0) {
                                                goto L_004f459c;
                                            }
                                            goto L_004f44dc_63;
                                        }
                                    L_004f459c:
                                        charge(ctx, 3);
                                        s0 = addiu(s0, -1);
                                        s1 = addiu(s1, -40);
                                        if (i64(s0) < 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004f45a8
                                    charge(ctx, 2);
                                    backedge(ctx);
                                }
                            }
                        L_004f44e4:
                            charge(ctx, 2);
                            if (s7 == 0) {
                                goto L_004f45b0;
                            }
                            // 0x004f44ec: a failure: the nodes initialised so far terminated again (pipeline-node term, node term at the last use)
                            charge(ctx, 5);
                            lw(v0, s4, rxpipeline::kNumNodes);
                            s0 = subu(v0, fp);
                            at = sltu(s0, v0);
                            if (at != 0) {
                                // 0x004f4500
                                charge(ctx, 3);
                                v0 = sll(s0, 2);
                                v0 = addu(v0, s0);
                                s1 = sll(v0, 3);
                                for (;;) {
                                    // 0x004f450c
                                    charge(ctx, 6);
                                    lw(v0, s4, rxpipeline::kNodes);
                                    a0 = addu(v0, s1);
                                    lw(s2, a0, 0);
                                    lw(v0, s2, 20);
                                    if (v0 != 0) {
                                        // 0x004f4524
                                        charge(ctx, 3);
                                        jalr(ctx, 0x4F4524u, v0.u());
                                    }
                                    // 0x004f4530
                                    charge(ctx, 6);
                                    lw(v0, s2, 60);
                                    v0 = addiu(v0, -1);
                                    sw(v0, s2, 60);
                                    lw(v0, s2, 60);
                                    if (v0 == 0) {
                                        // 0x004f4548
                                        charge(ctx, 3);
                                        lw(v0, s2, 12);
                                        if (v0 != 0) {
                                            // 0x004f4554
                                            charge(ctx, 3);
                                            a0 = s2;
                                            jalr(ctx, 0x4F4554u, v0.u());
                                        }
                                    }
                                    // 0x004f4560
                                    charge(ctx, 5);
                                    lw(v0, s4, rxpipeline::kNumNodes);
                                    s0 = addiu(s0, 1);
                                    v0 = sltu(s0, v0);
                                    s1 = addiu(s1, 40);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004f4574
                                charge(ctx, 1);
                            }
                            goto L_004f4578;
                        }
                    L_004f4578:
                        charge(ctx, 5);
                        a0 = s4;
                        a1 = s4;
                        jal(ctx, 0x4F457Cu, gen::fn_sub_4F3410_004f3410);
                        v0 = 0;
                    } else {
                        // 0x004f4300
                        charge(ctx, 2);
                        v0 = 0;
                    }
                }
                // 0x004f4610 (the shared epilogue, written out on this path)
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
                sp = addiu(sp, 0xC0);
                return;
            }
        L_004f41d0:
            charge(ctx, 9);
            v0 = 1;
            a0 = 36;
            link(ctx, 0x4F41D8u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0xB8);
            call(ctx, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0xBC);
            a0 = addiu(sp, 0xB8);
            jal(ctx, 0x4F41E4u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
            // 0x004f4610 (the shared epilogue, written out on this path)
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
            sp = addiu(sp, 0xC0);
            return;
        }
    L_004f45b0:
        charge(ctx, 3);
        sw(zero, s4, rxpipeline::kLocked);
        v0 = s4;
        // 0x004f4610 (the shared epilogue, written out on this path)
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
        sp = addiu(sp, 0xC0);
        return;
    }
L_004f45bc:
    charge(ctx, 2);
    if (s4 == 0) {
        // 0x004f45e8: a null pipeline: error 0x80000016
        charge(ctx, 10);
        v1 = 1;
        v0 = lui(0x8000);
        sw(v1, sp, 0xB0);
        a0 = v0 | 0x16;
        jal(ctx, 0x4F45F4u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0xB4);
        a0 = addiu(sp, 0xB0);
        jal(ctx, 0x4F4600u, gen::fn_sub_4C1C50_004c1c50);
        backedge(ctx);
    } else {
        // 0x004f45c4: not locked: error 52
        charge(ctx, 7);
        v0 = 1;
        a0 = 52;
        link(ctx, 0x4F45CCu);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0xA8);
        call(ctx, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0xAC);
        a0 = addiu(sp, 0xA8);
        jal(ctx, 0x4F45D8u, gen::fn_sub_4C1C50_004c1c50);
    }
    // 0x004f45e0
    charge(ctx, 2);
    v0 = 0;
    // 0x004f4610 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xC0);
    return;
L_004f4418_50:
    charge(ctx, 5);
    lw(v0, s4, rxpipeline::kNumNodes);
    s7 = 1;
    v0 = addiu(v0, -1);
    fp = subu(v0, s0);
    goto L_004f458c;
L_004f4448_53:
    charge(ctx, 6);
    lw(v0, s3, 60);
    v0 = addiu(v0, -1);
    sw(v0, s3, 60);
    lw(v0, s3, 60);
    if (v0 == 0) {
        // 0x004f4460
        charge(ctx, 3);
        lw(v0, s3, 12);
        if (v0 != 0) {
            // 0x004f446c
            charge(ctx, 2);
            a0 = s3;
            jalr(ctx, 0x4F446Cu, v0.u());
        }
    }
    // 0x004f4474
    charge(ctx, 5);
    lw(v0, s4, rxpipeline::kNumNodes);
    s7 = 1;
    v0 = addiu(v0, -1);
    fp = subu(v0, s0);
    goto L_004f458c;
L_004f44dc_63:
    charge(ctx, 2);
    lw(fp, s4, rxpipeline::kNumNodes);
    s7 = 1;
    goto L_004f44e4;
}


// sub_4F4640 [RxPipelineLock] -- locks a pipeline for editing: a super block of 180 x the node limit (RwMalloc, or grown), the nodes copied into its layout, each node's pipeline-node term and (at its last use) node term run
// Already locked: returned as it is. Each node's slot-cluster word (+12) cleared. The pipeline (+0 = 1), or 0.
// 0x004F4640 sub_4F4640 -- 484 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F4640(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004f4640
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 0);
    s3 = a0;
    if (v0 == 0) {
        // 0x004f4664
        charge(ctx, 14);
        lw(a1, gp, -16840);  // 0x7CEB28 (the pipeline module offset)
        v1 = 0x960000;
        v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
        lw(v0, s3, rxpipeline::kNodes);
        v1 = addu(v1, a1);
        lw(a2, v1, 56);
        a1 = sll(a2, 1);
        v1 = sll(a2, 7);
        a1 = addu(a1, a2);
        a1 = sll(a1, 2);
        a1 = addu(a1, a2);
        a1 = sll(a1, 2);
        s0 = addu(a1, v1);
        if (v0 == 0) {
            // 0x004f4780
            charge(ctx, 10);
            v0 = 0x1030000;
            a1 = v0 | 0x409;  // &0x1030409
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
            a0 = s0;
            jalr(ctx, 0x4F4790u, v0.u());
            sw(v0, s3, rxpipeline::kSuperBlock);
            lw(v0, s3, rxpipeline::kSuperBlock);
            if (v0 != 0) {
                // 0x004f47a8
                charge(ctx, 4);
                sw(s0, s3, rxpipeline::kSuperBlockSize);
                lw(v0, s3, rxpipeline::kSuperBlock);
                sw(v0, s3, rxpipeline::kNodes);
                backedge(ctx);
            L_004f46e0:
                charge(ctx, 5);
                v0 = 1;
                sw(v0, s3, rxpipeline::kLocked);
                lw(v0, s3, rxpipeline::kNodes);
                if (v0 != 0) {
                    // 0x004f46f4
                    charge(ctx, 4);
                    lw(v0, s3, rxpipeline::kNumNodes);
                    at = sltu(0, v0);
                    s2 = 0;
                    if (at != 0) {
                        // 0x004f4704
                        charge(ctx, 1);
                        s0 = 0;
                        for (;;) {
                            // 0x004f4708
                            charge(ctx, 7);
                            lw(v0, s3, rxpipeline::kNodes);
                            a0 = addu(v0, s0);
                            lw(v0, a0, 0);
                            s1 = addiu(v0, 4);
                            lw(v0, v0, 20);
                            if (v0 == 0) {
                                // 0x004f47e4
                                charge(ctx, 1);
                                lw(v0, s3, rxpipeline::kNodes);
                            } else {
                                // 0x004f4724
                                charge(ctx, 4);
                                jalr(ctx, 0x4F4724u, v0.u());
                                lw(v0, s3, rxpipeline::kNodes);
                            }
                            // 0x004f47e8
                            charge(ctx, 6);
                            v0 = addu(v0, s0);
                            lw(v1, v0, 0);
                            lw(v0, v1, 60);
                            v0 = addiu(v0, -1);
                            sw(v0, v1, 60);
                            if (v0 != 0) {
                                backedge(ctx);
                            } else {
                                // 0x004f4800
                                charge(ctx, 2);
                                backedge(ctx);
                                // 0x004f4738
                                charge(ctx, 3);
                                lw(v1, s1, 8);
                                if (v1 != 0) {
                                    // 0x004f4744
                                    charge(ctx, 5);
                                    lw(v0, s3, rxpipeline::kNodes);
                                    v0 = addu(v0, s0);
                                    jt = v1.u();  // the target, read before the delay slot
                                    link(ctx, 0x4F474Cu);  // $ra = the return address
                                    lw(a0, v0, 0);
                                    call_ptr(ctx, jt);
                                }
                            }
                            // 0x004f4758
                            charge(ctx, 8);
                            lw(v0, s3, rxpipeline::kNodes);
                            s2 = addiu(s2, 1);
                            v0 = addu(v0, s0);
                            sw(zero, v0, 12);
                            lw(v0, s3, rxpipeline::kNumNodes);
                            v0 = sltu(s2, v0);
                            s0 = addiu(s0, 40);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                }
                goto L_004f4778;
            }
            // 0x004f47b8
            charge(ctx, 11);
            v0 = 1;
            a1 = s0;
            sw(v0, sp, 0x58);
            v0 = lui(0x8000);
            a0 = v0 | 0x13;
            jal(ctx, 0x4F47C8u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x5C);
            a0 = addiu(sp, 0x58);
            jal(ctx, 0x4F47D4u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        } else {
            // 0x004f469c
            charge(ctx, 4);
            lw(v0, s3, rxpipeline::kSuperBlockSize);
            at = sltu(v0, s0);
            if (at != 0) {
                // 0x004f46ac
                charge(ctx, 4);
                a1 = s0;
                jal(ctx, 0x4F46ACu, gen::fn_sub_4F3260_004f3260);
                if (v0 != 0) {
                    goto L_004f46c4;
                }
                // 0x004f46bc
                charge(ctx, 2);
                v0 = 0;
                // 0x004f4808 (the shared epilogue, written out on this path)
                charge(ctx, 7);
                ld(ra, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x60);
                return;
            }
        L_004f46c4:
            charge(ctx, 5);
            a0 = s3;
            a1 = s3;
            jal(ctx, 0x4F46C8u, gen::fn_sub_4F3410_004f3410);
            if (v0 != 0) {
                goto L_004f46e0;
            }
            // 0x004f46d8
            charge(ctx, 2);
            v0 = 0;
        }
        // 0x004f4808 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x60);
        return;
    }
L_004f4778:
    charge(ctx, 2);
    v0 = s3;
    // 0x004f4808 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_4F4830 [RxPipelineFindNodeByName] -- finds a pipeline's node by its definition's name (strcmp slot), from the node after $a2 (the first when 0); its index to *$a3
// The node, or 0 with *$a3 = -1 (a null pipeline / name, no nodes, no match).
// 0x004F4830 sub_4F4830 -- 280 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F4830(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f4830
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    v0 = sltu(0, s5);
    sq(s2, sp, 0x20);
    s4 = a1;
    sq(s1, sp, 0x10);
    s3 = a3;
    sq(s0, sp, 0x0);
    if (v0 != 0) {
        // 0x004f4864
        charge(ctx, 1);
        v0 = sltu(0, s4);
    }
    // 0x004f4868
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x004f4870
        charge(ctx, 2);
        lw(v0, s5, rxpipeline::kNumNodes);
        v0 = sltu(0, v0);
    }
    // 0x004f4878
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x004f4880
        charge(ctx, 3);
        lw(s1, s5, rxpipeline::kNumNodes);
        lw(s2, s5, rxpipeline::kNodes);
        if (a2 != 0) {
            for (;;) {
                // 0x004f488c
                charge(ctx, 2);
                if (s2 != a2) {
                    // 0x004f4894
                    charge(ctx, 2);
                    if (i64(s1) > 0) {
                        // 0x004f489c
                        charge(ctx, 3);
                        s2 = addiu(s2, 40);
                        s1 = addiu(s1, -1);
                        backedge(ctx);
                        continue;
                    }
                }
                break;
            }
            // 0x004f48a8
            charge(ctx, 2);
            s2 = addiu(s2, 40);
            s1 = addiu(s1, -1);
        }
        // 0x004f48b0
        charge(ctx, 2);
        if (i64(s1) <= 0) {
            goto L_004f4910;
        }
        // 0x004f48b8
        charge(ctx, 2);
        s0 = 0x960000;
        s0 = addiu(s0, 344);  // &0x960158 (the engine's strcmp slot)
        for (;;) {
            // 0x004f48c0
            charge(ctx, 3);
            lw(v0, s2, 0);
            if (v0 != 0) {
                // 0x004f48cc
                charge(ctx, 6);
                lw(a0, v0, 0);
                lw(v0, s0, 0);
                a1 = s4;
                jalr(ctx, 0x4F48D4u, v0.u());
                if (v0 != 0) {
                    goto L_004f4900;
                }
                goto L_004f48e4_14;
            }
        L_004f4900:
            charge(ctx, 3);
            s1 = addiu(s1, -1);
            s2 = addiu(s2, 40);
            if (i64(s1) <= 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004f490c
        charge(ctx, 1);
        goto L_004f4910;
    }
L_004f4910:
    charge(ctx, 2);
    if (s3 != 0) {
        // 0x004f4918
        charge(ctx, 2);
        v0 = si(-1);
        sw(v0, s3, 0);
    }
    // 0x004f4920
    charge(ctx, 1);
    v0 = 0;
    // 0x004f4924 (the shared epilogue, written out on this path)
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
L_004f48e4_14:
    charge(ctx, 2);
    if (s3 != 0) {
        // 0x004f48ec
        charge(ctx, 3);
        lw(v0, s5, rxpipeline::kNumNodes);
        v0 = subu(v0, s1);
        sw(v0, s3, 0);
    }
    // 0x004f48f8
    charge(ctx, 2);
    v0 = s2;
    // 0x004f4924 (the shared epilogue, written out on this path)
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


// sub_4F4950 [RxLockedPipeAddFragment] -- adds a chain of nodes to a locked pipeline: the definitions from $a2 on (a NULL-terminated list), each node set up (sub_4F3680) and connected from the previous node's output 0 (sub_4F4C30)
// *$a1 = the first new node's index. Refused for a null / unlocked pipeline, an empty list, more nodes than the
// limit (42); a failure destroys the nodes added (sub_4F2AD0). The pipeline, or 0.
// 0x004F4950 sub_4F4950 -- 732 bytes; frame 0x110: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F4950(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f4950
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x110);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    s7 = a1;
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    sd(a3, sp, 0xE8);
    sd(t0, sp, 0xF0);
    sd(t1, sp, 0xF8);
    sd(t2, sp, 0x100);
    sd(t3, sp, 0x108);
    if (s1 != 0) {
        // 0x004f4998
        charge(ctx, 3);
        lw(v0, s1, rxpipeline::kLocked);
        if (v0 == 0) {
            goto L_004f4bac;
        }
        // 0x004f49a4
        charge(ctx, 4);
        v1 = 3;
        v0 = slti(v1, 8);
        s0 = 0;
        if (v0 != 0) {
            // 0x004f49bc
            charge(ctx, 3);
            v0 = 8;
            v0 = subu(v0, v1);
            a0 = sll(v0, 3);
        } else {
            // 0x004f49b4
            charge(ctx, 2);
            a0 = 0;
        }
        // 0x004f49c8
        charge(ctx, 5);
        v0 = dsll32(a2, 0);
        v1 = addiu(sp, 0x110);
        v0 = dsra32(v0, 0);
        v1 = subu(v1, a0);
        if (v0 != 0) {
            for (;;) {
                // 0x004f49dc
                charge(ctx, 7);
                v1 = addiu(v1, 8);
                s0 = addiu(s0, 1);
                lw(v0, v1, -8);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004f49f8
        charge(ctx, 2);
        if (s0 == 0) {
        L_004f4afc:
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004f4a00
            charge(ctx, 10);
            lw(v1, gp, -16840);  // 0x7CEB28 (the pipeline module offset)
            v0 = 0x960000;
            v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            lw(s6, s1, rxpipeline::kNumNodes);
            v0 = addu(v0, v1);
            lw(v0, v0, 56);
            a0 = addu(s6, s0);
            at = sltu(v0, a0);
            s4 = 0;
            if (at != 0) {
                // 0x004f4b04
                charge(ctx, 9);
                v0 = 1;
                a0 = 42;
                link(ctx, 0x4F4B0Cu);  // $ra first: the delay slot below depends on it
                sw(v0, sp, 0xA8);
                call(ctx, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0xAC);
                a0 = addiu(sp, 0xA8);
                jal(ctx, 0x4F4B18u, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
            } else {
                // 0x004f4a28
                charge(ctx, 4);
                v1 = 3;
                v0 = slti(v1, 8);
                s5 = 0;
                if (v0 != 0) {
                    // 0x004f4a40
                    charge(ctx, 3);
                    v0 = 8;
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 3);
                } else {
                    // 0x004f4a38
                    charge(ctx, 2);
                    v1 = 0;
                }
                // 0x004f4a4c
                charge(ctx, 5);
                a2 = dsll32(a2, 0);
                v0 = addiu(sp, 0x110);
                a2 = dsra32(a2, 0);
                s2 = subu(v0, v1);
                if (a2 != 0) {
                    for (;;) {
                        // 0x004f4a60
                        charge(ctx, 11);
                        lw(v0, s1, rxpipeline::kNodes);
                        a1 = addu(s6, s5);
                        v1 = sll(a1, 2);
                        a0 = s1;
                        v1 = addu(v1, a1);
                        v1 = sll(v1, 3);
                        s3 = addu(v0, v1);
                        a1 = s3;
                        jal(ctx, 0x4F4A7Cu, gen::fn_sub_4F3680_004f3680);
                        if (v0 == 0) {
                            break;
                        }
                        // 0x004f4a8c
                        charge(ctx, 2);
                        if (s4 != 0) {
                            // 0x004f4a94
                            charge(ctx, 2);
                            if (s4 != 0) {
                                // 0x004f4a9c
                                charge(ctx, 3);
                                lw(v0, s4, 0);
                                if (v0 == 0) {
                                    goto L_004f4b28;
                                }
                                // 0x004f4aa8
                                charge(ctx, 4);
                                lw(v0, s4, 4);
                                at = sltu(0, v0);
                                if (at == 0) {
                                    goto L_004f4b28;
                                }
                                // 0x004f4ab8
                                charge(ctx, 2);
                                lw(a1, s4, 8);
                                goto L_004f4ac0;
                            }
                        L_004f4b28:
                            charge(ctx, 2);
                            a1 = 0;
                            backedge(ctx);
                        L_004f4ac0:
                            charge(ctx, 2);
                            if (s3 != 0) {
                                // 0x004f4ac8
                                charge(ctx, 3);
                                lw(v0, s3, 0);
                                if (v0 == 0) {
                                    goto L_004f4b30;
                                }
                                // 0x004f4ad4
                                charge(ctx, 1);
                                a2 = s3;
                                goto L_004f4ad8;
                            }
                        L_004f4b30:
                            charge(ctx, 2);
                            a2 = 0;
                            backedge(ctx);
                        L_004f4ad8:
                            charge(ctx, 4);
                            a0 = s1;
                            jal(ctx, 0x4F4AD8u, gen::fn_sub_4F4C30_004f4c30);
                            if (v0 != 0) {
                                goto L_004f4b38;
                            }
                            goto L_004f4ae8_23;
                        }
                    L_004f4b38:
                        charge(ctx, 5);
                        s2 = addiu(s2, 8);
                        lw(a2, s2, -8);
                        s4 = s3;
                        s5 = addiu(s5, 1);
                        if (a2 == 0) {
                            goto L_004f4b4c_29;
                        }
                        backedge(ctx);
                    }
                }
            L_004f4b50:
                charge(ctx, 2);
                if (s5 != s0) {
                    // 0x004f4b58
                    charge(ctx, 3);
                    v0 = s5;
                    s5 = addiu(s5, -1);
                    if (v0 == 0) {
                        backedge(ctx);
                    } else {
                        for (;;) {
                            // 0x004f4b64
                            charge(ctx, 11);
                            lw(v0, s1, rxpipeline::kNodes);
                            a0 = addu(s5, s6);
                            v1 = sll(a0, 2);
                            a1 = s1;
                            v1 = addu(v1, a0);
                            v1 = sll(v1, 3);
                            a0 = addu(v0, v1);
                            jal(ctx, 0x4F4B7Cu, gen::fn_sub_4F2AD0_004f2ad0);
                            v0 = s5;
                            s5 = addiu(s5, -1);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004f4b90
                        charge(ctx, 2);
                        backedge(ctx);
                    }
                    goto L_004f4afc;
                }
                // 0x004f4b98
                charge(ctx, 2);
                if (s7 != 0) {
                    // 0x004f4ba0
                    charge(ctx, 1);
                    sw(s6, s7, 0);
                }
                // 0x004f4ba4
                charge(ctx, 2);
                v0 = s1;
            }
        }
        // 0x004f4c00 (the shared epilogue, written out on this path)
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
        sp = addiu(sp, 0x110);
        return;
    }
L_004f4bac:
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x004f4bd8
        charge(ctx, 10);
        v1 = 1;
        v0 = lui(0x8000);
        sw(v1, sp, 0xA0);
        a0 = v0 | 0x16;
        jal(ctx, 0x4F4BE4u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0xA4);
        a0 = addiu(sp, 0xA0);
        jal(ctx, 0x4F4BF0u, gen::fn_sub_4C1C50_004c1c50);
        backedge(ctx);
    } else {
        // 0x004f4bb4
        charge(ctx, 9);
        v0 = 1;
        a0 = 52;
        link(ctx, 0x4F4BBCu);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x98);
        call(ctx, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x9C);
        a0 = addiu(sp, 0x98);
        jal(ctx, 0x4F4BC8u, gen::fn_sub_4C1C50_004c1c50);
        backedge(ctx);
    }
    goto L_004f4afc;
L_004f4ae8_23:
    charge(ctx, 5);
    a0 = s3;
    a1 = s1;
    jal(ctx, 0x4F4AECu, gen::fn_sub_4F2AD0_004f2ad0);
    goto L_004f4b50;
L_004f4b4c_29:
    charge(ctx, 1);
    goto L_004f4b50;
}


// sub_4F4C30 [RxLockedPipeAddPath] -- connects an output slot (*$a1, which must be -1) of a locked pipeline to node $a2: the node's index stored; the pipeline, or 0 when unlocked, connected or not a node of it
// 0x004F4C30 sub_4F4C30 -- 192 bytes; leaf frame (no stack)
void sub_4F4C30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x004f4c30
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x004f4c38
        charge(ctx, 3);
        lw(v0, a0, rxpipeline::kLocked);
        if (v0 == 0) {
            goto L_004f4ce4;
        }
        // 0x004f4c44
        charge(ctx, 2);
        if (a1 == 0) {
            goto L_004f4ce4;
        }
        // 0x004f4c4c
        charge(ctx, 4);
        lw(v1, a1, 0);
        v0 = si(-1);
        if (v1 != v0) {
            goto L_004f4ce4;
        }
        // 0x004f4c5c
        charge(ctx, 2);
        if (a2 == 0) {
            goto L_004f4ce4;
        }
        // 0x004f4c64
        charge(ctx, 3);
        lw(v0, a2, rxpnode::kNodeDef);
        if (v0 == 0) {
            goto L_004f4ce4;
        }
        // 0x004f4c70
        charge(ctx, 16);
        lw(a3, a0, rxpipeline::kNodes);
        v0 = 0x66660000;
        v0 = v0 | 0x6667;
        v1 = subu(a2, a3);
        mult(zero, v0, v1);
        v1 = srl(v1, 31);
        mfhi(v0);
        v0 = sra(v0, 4);
        v1 = addu(v0, v1);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 3);
        v0 = addu(a3, v0);
        if (v0 == a2) {
            // 0x004f4ccc
            charge(ctx, 4);
            lw(v0, a0, rxpipeline::kNumNodes);
            at = sltu(v1, v0);
            if (at == 0) {
                backedge(ctx);
                goto L_004f4cb0;
            }
            // 0x004f4cdc
            charge(ctx, 2);
            v0 = si(-1);
            backedge(ctx);
            goto L_004f4cb8;
        }
    L_004f4cb0:
        charge(ctx, 2);
        v1 = si(-1);
        v0 = si(-1);
    L_004f4cb8:
        charge(ctx, 2);
        if (v1 == v0) {
            goto L_004f4ce4;
        }
        // 0x004f4cc0
        charge(ctx, 3);
        sw(v1, a1, 0);
        v0 = a0;
        // 0x004f4ce8 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_004f4ce4:
    charge(ctx, 1);
    v0 = 0;
    // 0x004f4ce8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_4F4CF0 [rxReqListAdd] -- adds a cluster to a node's requirement list (36-byte entries): an existing entry made required when $a2 is 1; else appended with its flags, creator and slot -1; the entry
// 0x004F4CF0 sub_4F4CF0 -- 188 bytes; leaf frame (no stack)
void sub_4F4CF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    // 0x004f4cf0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(t1, a0, 0);
    if (t1 != 0) {
        // 0x004f4cfc
        charge(ctx, 4);
        lw(v0, a0, 12);
        at = sltu(0, t1);
        t2 = 0;
        if (at == 0) {
            goto L_004f4d30;
        }
        for (;;) {
            // 0x004f4d0c
            charge(ctx, 3);
            lw(v1, v0, 0);
            if (v1 == a1) {
                goto L_004f4d18_3;
            }
            // 0x004f4d20
            charge(ctx, 4);
            t2 = addiu(t2, 1);
            v1 = sltu(t2, t1);
            v0 = addiu(v0, 36);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        goto L_004f4d30;
    }
L_004f4d30:
    charge(ctx, 1);
    v0 = 0;
L_004f4d34:
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x004f4d5c
        charge(ctx, 18);
        v1 = sll(t1, 3);
        lw(v0, a0, 12);
        v1 = addu(v1, t1);
        lw(t1, a0, 0);
        t2 = sll(v1, 2);
        v1 = si(-1);
        v0 = addu(v0, t2);
        t1 = addiu(t1, 1);
        sw(t1, a0, 0);
        sw(a1, v0, 0);
        sw(a2, v0, 4);
        sw(a3, v0, 8);
        sw(zero, v0, 16);
        sw(a0, v0, 20);
        sw(zero, v0, 12);
        sw(zero, v0, 24);
        sw(v1, v0, 28);
        sw(t0, v0, 32);
    } else {
        // 0x004f4d3c
        charge(ctx, 3);
        v1 = 1;
        if (a2 == v1) {
            // 0x004f4d50
            charge(ctx, 3);
            sw(v1, v0, 4);
            sw(t0, v0, 32);
            backedge(ctx);
        }
        // 0x004f4d48
        charge(ctx, 2);
    }
    // 0x004f4da4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004f4d18_3:
    charge(ctx, 2);
    goto L_004f4d34;
}


// sub_4F4DB0 [rxReqListRemove] -- drops a cluster from a node's requirement list (its reference count down; at 0 the last entry moved into its place) and, for each output that does not keep the cluster, from the target node, recursively
// 0x004F4DB0 sub_4F4DB0 -- 560 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F4DB0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x004f4db0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a1, 28);
    lw(a0, a1, 0);
    lw(v1, v1, 8);
    lw(a1, v1, 0);
    s6 = addiu(a0, 32);
    if (a1 != 0) {
        // 0x004f4df8
        charge(ctx, 4);
        lw(v1, v1, 12);
        at = sltu(0, a1);
        a2 = 0;
        if (at == 0) {
            goto L_004f4e30;
        }
        for (;;) {
            // 0x004f4e08
            charge(ctx, 3);
            lw(a0, v1, 0);
            if (a0 == s3) {
                goto L_004f4e14_3;
            }
            // 0x004f4e1c
            charge(ctx, 4);
            a2 = addiu(a2, 1);
            a0 = sltu(a2, a1);
            v1 = addiu(v1, 36);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004f4e2c
        charge(ctx, 1);
        goto L_004f4e30;
    }
L_004f4e30:
    charge(ctx, 1);
    v1 = 0;
L_004f4e34:
    charge(ctx, 2);
    if (v1 != 0) {
        // 0x004f4e3c
        charge(ctx, 4);
        lw(a0, v1, 8);
        a0 = addiu(a0, -1);
        sw(a0, v1, 8);
        if (a0 == 0) {
            // 0x004f4e4c
            charge(ctx, 11);
            lw(a0, s4, 28);
            lw(t0, a0, 8);
            lw(a3, t0, 0);
            lw(a2, t0, 12);
            a1 = addiu(a3, -1);
            a0 = sll(a1, 3);
            a0 = addu(a0, a1);
            a0 = sll(a0, 2);
            a0 = addu(a2, a0);
            if (v1 != a0) {
                // 0x004f4e78
                charge(ctx, 22);
                a0 = sll(a3, 3);
                a0 = addu(a0, a3);
                a0 = sll(a0, 2);
                a0 = addu(a0, a2);
                lwc1(f3, a0, -36);
                lwc1(f2, a0, -32);
                lwc1(f1, a0, -28);
                lwc1(f0, a0, -24);
                swc1(f3, v1, 0);
                swc1(f2, v1, 4);
                swc1(f1, v1, 8);
                swc1(f0, v1, 12);
                lwc1(f3, a0, -20);
                lwc1(f2, a0, -16);
                lwc1(f1, a0, -12);
                lwc1(f0, a0, -8);
                swc1(f3, v1, 16);
                swc1(f2, v1, 20);
                swc1(f1, v1, 24);
                swc1(f0, v1, 28);
                lwc1(f0, a0, -4);
                swc1(f0, v1, 32);
            }
            // 0x004f4ed0
            charge(ctx, 7);
            lw(v1, t0, 0);
            v1 = addiu(v1, -1);
            sw(v1, t0, 0);
            lw(v1, s4, 4);
            at = sltu(0, v1);
            s2 = 0;
            if (at != 0) {
                // 0x004f4eec
                charge(ctx, 2);
                s1 = 0;
                s0 = 0;
                for (;;) {
                    // 0x004f4ef4
                    charge(ctx, 6);
                    lw(a0, s4, 8);
                    v1 = si(-1);
                    a0 = addu(a0, s1);
                    lw(a2, a0, 0);
                    if (a2 != v1) {
                        // 0x004f4f0c
                        charge(ctx, 7);
                        lw(v1, s4, 0);
                        t0 = 0;
                        lw(a0, s6, 0);
                        lw(v1, v1, 48);
                        at = sltu(0, a0);
                        a1 = addu(v1, s0);
                        if (at != 0) {
                            // 0x004f4f28
                            charge(ctx, 1);
                            lw(a3, s6, 4);
                            for (;;) {
                                // 0x004f4f2c
                                charge(ctx, 3);
                                lw(v1, a3, 0);
                                if (v1 == s3) {
                                    goto L_004f4f38_17;
                                }
                                // 0x004f4f40
                                charge(ctx, 4);
                                t0 = addiu(t0, 1);
                                v1 = sltu(t0, a0);
                                a3 = addiu(a3, 12);
                                if (v1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                        }
                        // 0x004f4f50
                        charge(ctx, 2);
                        t0 = si(-1);
                        v1 = si(-1);
                    L_004f4f58:
                        charge(ctx, 2);
                        if (t0 != v1) {
                            // 0x004f4f68
                            charge(ctx, 4);
                            lw(v1, a1, 4);
                            a0 = sll(t0, 2);
                            v1 = addu(v1, a0);
                            lw(v1, v1, 0);
                        } else {
                            // 0x004f4f60
                            charge(ctx, 2);
                            lw(v1, a1, 8);
                        }
                        // 0x004f4f78
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x004f4f80
                            charge(ctx, 8);
                            lw(v0, s5, 8);
                            v1 = sll(a2, 2);
                            v1 = addu(v1, a2);
                            a0 = s5;
                            v1 = sll(v1, 3);
                            a2 = s3;
                            a1 = addu(v0, v1);
                            jal(ctx, 0x4F4F98u, gen::fn_sub_4F4DB0_004f4db0);
                        }
                    }
                    // 0x004f4fa0
                    charge(ctx, 6);
                    lw(v1, s4, 4);
                    s2 = addiu(s2, 1);
                    s1 = addiu(s1, 4);
                    v1 = sltu(s2, v1);
                    s0 = addiu(s0, 12);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
    }
    // 0x004f4fb8 (the shared epilogue, written out on this path)
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
L_004f4e14_3:
    charge(ctx, 2);
    goto L_004f4e34;
L_004f4f38_17:
    charge(ctx, 2);
    v1 = si(-1);
    goto L_004f4f58;
}


// sub_4F4FE0 [rxSlotMerge] -- merges two cluster-slot chains: both followed to their roots; when different, the second is appended to the first and taken out of the free chain $a0
// 0x004F4FE0 sub_4F4FE0 -- 192 bytes; leaf frame (no stack)
void sub_4F4FE0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x004f4fe0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a1, 12);
    if (v1 != 0) {
        for (;;) {
            // 0x004f4fec
            charge(ctx, 7);
            lw(a1, a1, 12);
            lw(v1, a1, 12);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004f5008
    charge(ctx, 3);
    lw(v1, a2, 12);
    if (v1 != 0) {
        for (;;) {
            // 0x004f5014
            charge(ctx, 7);
            lw(a2, a2, 12);
            lw(v1, a2, 12);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004f5030
    charge(ctx, 2);
    if (a1 != a2) {
        // 0x004f5038
        charge(ctx, 3);
        lw(v1, a1, 4);
        a3 = a1;
        if (v1 != 0) {
            for (;;) {
                // 0x004f5044
                charge(ctx, 7);
                lw(a3, a3, 4);
                lw(v1, a3, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004f5060
        charge(ctx, 5);
        sw(a2, a3, 4);
        sw(a1, a2, 12);
        lw(v1, a0, 0);
        if (v1 != a2) {
            for (;;) {
                // 0x004f5074
                charge(ctx, 7);
                a0 = addiu(v1, 8);
                lw(v1, v1, 8);
                if (v1 == a2) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004f5090
        charge(ctx, 2);
        lw(v1, v1, 8);
        sw(v1, a0, 0);
    }
    // 0x004f5098 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_4F50A0 [rxPipelineBuildRequirements] -- the requirement pass, last node first: per node a requirement list (cluster count from sub_4F31C0, scratch-allocated), filled from its outputs' targets and its own clusters of interest
// Errors: a cluster listed twice (30), a null cluster (31), out of memory (32), a required cluster an output
// invalidates (29). 0, or the error.
// 0x004F50A0 sub_4F50A0 -- 1152 bytes; frame 0xF0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F50A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004f50a0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s4, a0, 4);
    lw(v0, a0, 8);
    a0 = addiu(s4, -1);
    v1 = sll(a0, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 3);
    s3 = addu(v0, v1);
    for (;;) {
        // 0x004f50ec
        charge(ctx, 6);
        lw(v0, s3, 0);
        a2 = 0;
        lw(a3, v0, 32);
        at = sltu(0, a3);
        s0 = addiu(v0, 32);
        if (at != 0) {
            // 0x004f5104
            charge(ctx, 2);
            lw(a1, v0, 36);
            t1 = a1;
            for (;;) {
                // 0x004f510c
                charge(ctx, 3);
                lw(a0, t1, 0);
                if (a0 == 0) {
                    goto L_004f5118_4;
                }
                // 0x004f5144
                charge(ctx, 4);
                t2 = addiu(a2, 1);
                at = sltu(t2, a3);
                if (at != 0) {
                    // 0x004f5154
                    charge(ctx, 5);
                    v0 = sll(t2, 1);
                    v0 = addu(v0, t2);
                    v0 = sll(v0, 2);
                    t0 = addu(a1, v0);
                    for (;;) {
                        // 0x004f5168
                        charge(ctx, 3);
                        lw(v1, t0, 0);
                        if (a0 == v1) {
                            goto L_004f5174_8;
                        }
                        // 0x004f51a4
                        charge(ctx, 4);
                        t2 = addiu(t2, 1);
                        v0 = sltu(t2, a3);
                        t0 = addiu(t0, 12);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004f51b4
                    charge(ctx, 1);
                }
                // 0x004f51b8
                charge(ctx, 4);
                a2 = addiu(a2, 1);
                v0 = sltu(a2, a3);
                t1 = addiu(t1, 12);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004f51c8
        charge(ctx, 8);
        a0 = s5;
        jal(ctx, 0x4F51C8u, gen::fn_sub_4F31C0_004f31c0);
        s1 = v0;
        a0 = 20;
        jal(ctx, 0x4F51D4u, gen::fn_sub_4F30E0_004f30e0);
        s2 = v0;
        if (s2 != 0) {
            // 0x004f51e8
            charge(ctx, 8);
            v0 = sll(s1, 3);
            v0 = addu(v0, s1);
            a0 = sll(v0, 2);
            jal(ctx, 0x4F51F0u, gen::fn_sub_4F30E0_004f30e0);
            sw(v0, s2, 12);
            lw(v0, s2, 12);
            if (v0 == 0) {
                goto L_004f5434;
            }
            // 0x004f5208
            charge(ctx, 4);
            sw(s1, s2, 4);
            sw(zero, s2, 0);
            sw(s3, s2, 16);
            sw(zero, s2, 8);
            goto L_004f5218;
        }
    L_004f5434:
        charge(ctx, 2);
        s2 = 0;
        backedge(ctx);
    L_004f5218:
        charge(ctx, 3);
        lw(v0, s3, 28);
        sw(s2, v0, 8);
        if (s2 == 0) {
            goto L_004f543c;
        }
        // 0x004f5224
        charge(ctx, 4);
        lw(v0, s3, 4);
        at = sltu(0, v0);
        s2 = 0;
        if (at != 0) {
            // 0x004f5234
            charge(ctx, 2);
            fp = 0;
            sw(zero, sp, 0xB0);
            for (;;) {
                // 0x004f523c
                charge(ctx, 6);
                lw(v1, s3, 8);
                v0 = si(-1);
                v1 = addu(v1, fp);
                lw(a0, v1, 0);
                if (a0 != v0) {
                    // 0x004f5254
                    charge(ctx, 15);
                    v0 = sll(a0, 2);
                    lw(v1, s5, 8);
                    a0 = addu(v0, a0);
                    lw(v0, s3, 0);
                    a0 = sll(a0, 3);
                    s6 = addu(v1, a0);
                    lw(v1, s6, 28);
                    lw(a0, v0, 48);
                    lw(v0, sp, 0xB0);
                    s7 = addu(a0, v0);
                    lw(a0, v1, 8);
                    lw(v1, a0, 0);
                    at = sltu(0, v1);
                    s1 = 0;
                    if (at == 0) {
                        goto L_004f53bc;
                    }
                    // 0x004f5290
                    charge(ctx, 1);
                    sw(zero, sp, 0xA0);
                    for (;;) {
                        // 0x004f5294
                        charge(ctx, 3);
                        at = sltu(s1, v1);
                        if (at == 0) {
                            // 0x004f52b0
                            charge(ctx, 1);
                            v0 = 0;
                        } else {
                            // 0x004f52a0
                            charge(ctx, 4);
                            lw(v1, a0, 12);
                            lw(v0, sp, 0xA0);
                            v0 = addu(v1, v0);
                        }
                        // 0x004f52b4
                        charge(ctx, 5);
                        lw(a0, s0, 0);
                        lw(a2, v0, 0);
                        at = sltu(0, a0);
                        a3 = 0;
                        if (at != 0) {
                            // 0x004f52c8
                            charge(ctx, 1);
                            lw(a1, s0, 4);
                            for (;;) {
                                // 0x004f52cc
                                charge(ctx, 3);
                                lw(v1, a1, 0);
                                if (v1 == a2) {
                                    goto L_004f52d8_27;
                                }
                                // 0x004f52e0
                                charge(ctx, 4);
                                a3 = addiu(a3, 1);
                                v1 = sltu(a3, a0);
                                a1 = addiu(a1, 12);
                                if (v1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                        }
                        // 0x004f52f0
                        charge(ctx, 2);
                        a3 = si(-1);
                        v1 = si(-1);
                    L_004f52f8:
                        charge(ctx, 2);
                        if (a3 != v1) {
                            // 0x004f5308
                            charge(ctx, 4);
                            lw(v1, s7, 4);
                            a0 = sll(a3, 2);
                            v1 = addu(v1, a0);
                            lw(a1, v1, 0);
                        } else {
                            // 0x004f5300
                            charge(ctx, 2);
                            lw(a1, s7, 8);
                        }
                        // 0x004f5318
                        charge(ctx, 2);
                        if (a1 != 0) {
                            // 0x004f5320
                            charge(ctx, 4);
                            lw(a0, v0, 4);
                            v1 = 1;
                            if (a0 == v1) {
                                // 0x004f5330
                                charge(ctx, 2);
                                if (a1 == v1) {
                                    goto L_004f5394;
                                }
                                goto L_004f5338_36;
                            }
                            // 0x004f537c
                            charge(ctx, 3);
                            v0 = 2;
                            if (a1 == v0) {
                                // 0x004f5388
                                charge(ctx, 3);
                                a0 = s5;
                                a1 = s6;
                                jal(ctx, 0x4F538Cu, gen::fn_sub_4F4DB0_004f4db0);
                            }
                            goto L_004f5394;
                        }
                        // 0x004f5460
                        charge(ctx, 9);
                        lw(v1, s3, 28);
                        a1 = a2;
                        lw(t0, v0, 32);
                        lw(a0, v1, 8);
                        lw(a3, v1, 0);
                        link(ctx, 0x4F5474u);  // $ra first: the delay slot below depends on it
                        lw(a2, v0, 4);
                        call(ctx, gen::fn_sub_4F4CF0_004f4cf0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    L_004f5394:
                        charge(ctx, 10);
                        lw(v0, sp, 0xA0);
                        s1 = addiu(s1, 1);
                        v0 = addiu(v0, 36);
                        sw(v0, sp, 0xA0);
                        lw(v0, s6, 28);
                        lw(a0, v0, 8);
                        lw(v1, a0, 0);
                        v0 = sltu(s1, v1);
                        if (v0 == 0) {
                            goto L_004f53bc;
                        }
                        backedge(ctx);
                    }
                    break;
                }
            L_004f53bc:
                charge(ctx, 8);
                lw(v0, sp, 0xB0);
                s2 = addiu(s2, 1);
                v0 = addiu(v0, 12);
                sw(v0, sp, 0xB0);
                lw(v0, s3, 4);
                v0 = sltu(s2, v0);
                fp = addiu(fp, 0x4);
                if (v0 == 0) {
                    goto L_004f53dc;
                }
                backedge(ctx);
            }
            goto L_004f5484_50;
        }
    L_004f53dc:
        charge(ctx, 4);
        lw(v0, s0, 0);
        at = sltu(0, v0);
        t3 = 0;
        if (at != 0) {
            // 0x004f53ec
            charge(ctx, 2);
            t5 = 0;
            t4 = 0;
            for (;;) {
                // 0x004f53f4
                charge(ctx, 5);
                lw(v0, s0, 8);
                v0 = addu(v0, t5);
                lw(a2, v0, 0);
                if (a2 != 0) {
                    // 0x004f54a8
                    charge(ctx, 10);
                    lw(v0, s0, 4);
                    lw(v1, s3, 28);
                    v0 = addu(v0, t4);
                    lw(a0, v1, 8);
                    lw(a3, v1, 0);
                    lw(a1, v0, 0);
                    t0 = s3;
                    jal(ctx, 0x4F54C0u, gen::fn_sub_4F4CF0_004f4cf0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    goto L_004f5408;
                }
            L_004f5408:
                charge(ctx, 6);
                lw(v0, s0, 0);
                t3 = addiu(t3, 1);
                t5 = addiu(t5, 4);
                v0 = sltu(t3, v0);
                t4 = addiu(t4, 12);
                if (v0 == 0) {
                    goto L_004f5420;
                }
                backedge(ctx);
            }
            break;
        }
    L_004f5420:
        charge(ctx, 3);
        s4 = addiu(s4, -1);
        s3 = addiu(s3, -40);
        if (s4 == 0) {
            goto L_004f542c_46;
        }
        backedge(ctx);
    }
    // 0x004f54d0
    charge(ctx, 8);
    v0 = 1;
    a0 = 32;
    link(ctx, 0x4F54D8u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0xC0);
    call(ctx, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0xC4);
    a0 = addiu(sp, 0xC0);
    jal(ctx, 0x4F54E4u, gen::fn_sub_4C1C50_004c1c50);
    v0 = 32;
    // 0x004f54f0 (the shared epilogue, written out on this path)
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
L_004f5118_4:
    charge(ctx, 11);
    v0 = 1;
    sw(v0, sp, 0xE8);
    lw(v0, s3, 0);
    lw(a1, v0, 0);
    a0 = 31;
    jal(ctx, 0x4F5128u, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0xEC);
    a0 = addiu(sp, 0xE8);
    jal(ctx, 0x4F5134u, gen::fn_sub_4C1C50_004c1c50);
    v0 = 31;
    // 0x004f54f0 (the shared epilogue, written out on this path)
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
L_004f5174_8:
    charge(ctx, 12);
    v0 = 1;
    sw(v0, sp, 0xE0);
    lw(v0, s3, 0);
    lw(a2, v1, 0);
    lw(a1, v0, 0);
    a0 = 30;
    jal(ctx, 0x4F5188u, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0xE4);
    a0 = addiu(sp, 0xE0);
    jal(ctx, 0x4F5194u, gen::fn_sub_4C1C50_004c1c50);
    v0 = 30;
    // 0x004f54f0 (the shared epilogue, written out on this path)
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
L_004f52d8_27:
    charge(ctx, 2);
    v1 = si(-1);
    goto L_004f52f8;
L_004f5338_36:
    charge(ctx, 17);
    sw(v1, sp, 0xC8);
    t0 = s2;
    lw(a1, v0, 0);
    lw(v1, s3, 0);
    lw(t1, s7, 0);
    lw(v0, v0, 32);
    lw(a3, v1, 0);
    lw(a1, a1, 0);
    lw(v0, v0, 0);
    lw(a2, v0, 0);
    a0 = 29;
    jal(ctx, 0x4F5360u, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0xCC);
    a0 = addiu(sp, 0xC8);
    jal(ctx, 0x4F536Cu, gen::fn_sub_4C1C50_004c1c50);
    v0 = 29;
    // 0x004f54f0 (the shared epilogue, written out on this path)
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
L_004f542c_46:
    charge(ctx, 2);
    v0 = 0;
    // 0x004f54f0 (the shared epilogue, written out on this path)
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
L_004f543c:
    charge(ctx, 9);
    v0 = 1;
    a0 = 32;
    link(ctx, 0x4F5444u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0xD8);
    call(ctx, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0xDC);
    a0 = addiu(sp, 0xD8);
    jal(ctx, 0x4F5450u, gen::fn_sub_4C1C50_004c1c50);
    v0 = 32;
    // 0x004f54f0 (the shared epilogue, written out on this path)
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
L_004f5484_50:
    charge(ctx, 9);
    v0 = 1;
    a0 = 32;
    link(ctx, 0x4F548Cu);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0xD0);
    call(ctx, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0xD4);
    a0 = addiu(sp, 0xD0);
    jal(ctx, 0x4F5498u, gen::fn_sub_4C1C50_004c1c50);
    v0 = 32;
    // 0x004f54f0 (the shared epilogue, written out on this path)
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


// sub_4F5520 [rxPipelinePropagateRequirements] -- the propagation pass, first node first: each node's clusters and each output's surviving clusters marked in the targets' lists (bit per output); 0, or 32
// 0x004F5520 sub_4F5520 -- 708 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F5520(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f5520
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s2, a0, 4);
    lw(t0, a0, 8);
    for (;;) {
        // 0x004f5544
        charge(ctx, 6);
        lw(v0, t0, 0);
        t6 = addiu(v0, 32);
        lw(v0, v0, 32);
        at = sltu(0, v0);
        t4 = 0;
        if (at != 0) {
            // 0x004f555c
            charge(ctx, 1);
            t3 = 0;
            for (;;) {
                // 0x004f5560
                charge(ctx, 5);
                lw(v0, t6, 4);
                v1 = addu(v0, t3);
                lw(v0, v1, 4);
                if (v0 == 0) {
                    // 0x004f5574
                    charge(ctx, 1);
                    goto L_004f5578;
                }
                // 0x004f5748
                charge(ctx, 8);
                lw(v0, t0, 28);
                a2 = 0;
                lw(a1, v1, 0);
                lw(a0, v0, 8);
                a3 = 1;
                jal(ctx, 0x4F5758u, gen::fn_sub_4F4CF0_004f4cf0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            L_004f5578:
                charge(ctx, 5);
                lw(v0, t6, 0);
                t4 = addiu(t4, 1);
                v0 = sltu(t4, v0);
                t3 = addiu(t3, 12);
                if (v0 == 0) {
                    goto L_004f558c_6;
                }
                backedge(ctx);
            }
            goto L_004f5768_41;
        }
    L_004f5590:
        charge(ctx, 4);
        lw(v0, t0, 4);
        at = sltu(0, v0);
        t7 = 0;
        if (at != 0) {
            // 0x004f55a0
            charge(ctx, 2);
            s0 = 0;
            t9 = 0;
            for (;;) {
                // 0x004f55a8
                charge(ctx, 6);
                lw(v1, t0, 8);
                v0 = si(-1);
                v1 = addu(v1, s0);
                lw(a0, v1, 0);
                if (a0 != v0) {
                    // 0x004f55c0
                    charge(ctx, 14);
                    v0 = sll(a0, 2);
                    lw(v1, s3, 8);
                    a0 = addu(v0, a0);
                    lw(v0, t0, 0);
                    a0 = sll(a0, 3);
                    t5 = addu(v1, a0);
                    lw(v1, v0, 48);
                    lw(v0, t5, 28);
                    t4 = addu(v1, t9);
                    lw(a0, v0, 8);
                    lw(v1, a0, 0);
                    at = sltu(0, v1);
                    s1 = 0;
                    if (at == 0) {
                        goto L_004f571c;
                    }
                    // 0x004f55f8
                    charge(ctx, 3);
                    v0 = 1;
                    t8 = 0;
                    t3 = sllv(v0, t7);
                    for (;;) {
                        // 0x004f5604
                        charge(ctx, 3);
                        at = sltu(s1, v1);
                        if (at == 0) {
                            // 0x004f561c
                            charge(ctx, 1);
                            v0 = 0;
                        } else {
                            // 0x004f5610
                            charge(ctx, 3);
                            lw(v0, a0, 12);
                            v0 = addu(v0, t8);
                        }
                        // 0x004f5620
                        charge(ctx, 5);
                        lw(v1, t6, 0);
                        lw(a1, v0, 0);
                        at = sltu(0, v1);
                        a2 = 0;
                        if (at != 0) {
                            // 0x004f5634
                            charge(ctx, 1);
                            lw(a0, t6, 4);
                            for (;;) {
                                // 0x004f5638
                                charge(ctx, 3);
                                lw(v0, a0, 0);
                                if (v0 == a1) {
                                    goto L_004f5644_18;
                                }
                                // 0x004f564c
                                charge(ctx, 4);
                                a2 = addiu(a2, 1);
                                v0 = sltu(a2, v1);
                                a0 = addiu(a0, 12);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004f565c
                            charge(ctx, 1);
                        }
                        // 0x004f5660
                        charge(ctx, 2);
                        a2 = si(-1);
                        v0 = si(-1);
                    L_004f5668:
                        charge(ctx, 2);
                        if (a2 != v0) {
                            // 0x004f5678
                            charge(ctx, 4);
                            lw(v0, t4, 4);
                            v1 = sll(a2, 2);
                            v0 = addu(v0, v1);
                            lw(v1, v0, 0);
                        } else {
                            // 0x004f5670
                            charge(ctx, 2);
                            lw(v1, t4, 8);
                        }
                        // 0x004f5688
                        charge(ctx, 3);
                        v0 = 2;
                        if (v1 != v0) {
                            // 0x004f5694
                            charge(ctx, 2);
                            if (v1 != 0) {
                                // 0x004f578c
                                charge(ctx, 7);
                                lw(v0, t0, 28);
                                a2 = 0;
                                lw(a0, v0, 8);
                                a3 = 1;
                                jal(ctx, 0x4F5798u, gen::fn_sub_4F4CF0_004f4cf0);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            L_004f56ec:
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x004f56f4
                                    charge(ctx, 3);
                                    lw(v1, v0, 24);
                                    v1 = v1 | t3;
                                    sw(v1, v0, 24);
                                }
                                goto L_004f5700;
                            }
                            // 0x004f569c
                            charge(ctx, 5);
                            lw(v0, t0, 28);
                            lw(v0, v0, 8);
                            lw(a0, v0, 0);
                            if (a0 != 0) {
                                // 0x004f56b0
                                charge(ctx, 4);
                                lw(v0, v0, 12);
                                at = sltu(0, a0);
                                a2 = 0;
                                if (at == 0) {
                                    goto L_004f56e8;
                                }
                                for (;;) {
                                    // 0x004f56c0
                                    charge(ctx, 3);
                                    lw(v1, v0, 0);
                                    if (v1 == a1) {
                                        goto L_004f56cc_30;
                                    }
                                    // 0x004f56d4
                                    charge(ctx, 4);
                                    a2 = addiu(a2, 1);
                                    v1 = sltu(a2, a0);
                                    v0 = addiu(v0, 36);
                                    if (v1 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004f56e4
                                charge(ctx, 1);
                                goto L_004f56e8;
                            }
                        L_004f56e8:
                            charge(ctx, 1);
                            v0 = 0;
                            goto L_004f56ec;
                        }
                    L_004f5700:
                        charge(ctx, 7);
                        lw(v0, t5, 28);
                        s1 = addiu(s1, 1);
                        lw(a0, v0, 8);
                        lw(v1, a0, 0);
                        v0 = sltu(s1, v1);
                        t8 = addiu(t8, 36);
                        if (v0 == 0) {
                            goto L_004f571c;
                        }
                        backedge(ctx);
                    }
                    break;
                }
            L_004f571c:
                charge(ctx, 6);
                lw(v0, t0, 4);
                t7 = addiu(t7, 1);
                s0 = addiu(s0, 4);
                v0 = sltu(t7, v0);
                t9 = addiu(t9, 12);
                if (v0 == 0) {
                    goto L_004f5734;
                }
                backedge(ctx);
            }
            break;
        }
    L_004f5734:
        charge(ctx, 3);
        s2 = addiu(s2, -1);
        t0 = addiu(t0, 40);
        if (s2 == 0) {
            goto L_004f5740_39;
        }
        backedge(ctx);
    }
    // 0x004f57a8
    charge(ctx, 8);
    v0 = a3;
    a0 = 32;
    link(ctx, 0x4F57B0u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x50);
    call(ctx, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0x54);
    a0 = addiu(sp, 0x50);
    jal(ctx, 0x4F57BCu, gen::fn_sub_4C1C50_004c1c50);
    v0 = 32;
    // 0x004f57c8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004f558c_6:
    charge(ctx, 1);
    goto L_004f5590;
L_004f5644_18:
    charge(ctx, 2);
    v0 = si(-1);
    goto L_004f5668;
L_004f56cc_30:
    charge(ctx, 2);
    goto L_004f56ec;
L_004f5740_39:
    charge(ctx, 2);
    v0 = 0;
    // 0x004f57c8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004f5768_41:
    charge(ctx, 9);
    v0 = a3;
    a0 = 32;
    link(ctx, 0x4F5770u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x58);
    call(ctx, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0x5C);
    a0 = addiu(sp, 0x58);
    jal(ctx, 0x4F577Cu, gen::fn_sub_4C1C50_004c1c50);
    v0 = 32;
    // 0x004f57c8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_4F57F0 [rxPipelineAllocSlots] -- the slot pass: each requirement entry gets a slot record (16 bytes, scratch-allocated) unless it already has one; entries carried along an output share their source's slot (merged when both have one)
// 0x004F57F0 sub_4F57F0 -- 672 bytes; frame 0x90: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F57F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f57f0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a0;
    sq(s4, sp, 0x40);
    s5 = a1;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s4, a0, 4);
    lw(s2, a0, 8);
    for (;;) {
        // 0x004f5824
        charge(ctx, 6);
        lw(v0, s2, 28);
        lw(a0, v0, 8);
        lw(v1, a0, 0);
        at = sltu(0, v1);
        s3 = 0;
        if (at != 0) {
            // 0x004f583c
            charge(ctx, 1);
            s1 = 0;
            for (;;) {
                // 0x004f5840
                charge(ctx, 3);
                at = sltu(s3, v1);
                if (at == 0) {
                    // 0x004f5858
                    charge(ctx, 1);
                    s0 = 0;
                } else {
                    // 0x004f584c
                    charge(ctx, 3);
                    lw(v0, a0, 12);
                    s0 = addu(v0, s1);
                }
                // 0x004f585c
                charge(ctx, 3);
                lw(v0, s0, 12);
                if (v0 == 0) {
                    // 0x004f59bc
                    charge(ctx, 4);
                    a0 = 16;
                    jal(ctx, 0x4F59BCu, gen::fn_sub_4F30E0_004f30e0);
                    if (v0 == 0) {
                        // 0x004f5a00
                        charge(ctx, 2);
                        v0 = 0;
                        backedge(ctx);
                    } else {
                        // 0x004f59cc
                        charge(ctx, 6);
                        sw(zero, v0, 4);
                        sw(zero, v0, 0);
                        sw(zero, v0, 12);
                        lw(v1, s5, 0);
                        sw(v1, v0, 8);
                        sw(v0, s5, 0);
                    }
                    // 0x004f59e4
                    charge(ctx, 2);
                    sw(v0, s0, 12);
                    if (v0 == 0) {
                        break;
                    }
                    // 0x004f59ec
                    charge(ctx, 5);
                    lw(v1, s0, 12);
                    lw(v0, v1, 0);
                    sw(v0, s0, 16);
                    sw(s0, v1, 0);
                    backedge(ctx);
                    goto L_004f5868;
                }
            L_004f5868:
                charge(ctx, 7);
                lw(v0, s2, 28);
                s3 = addiu(s3, 1);
                lw(a0, v0, 8);
                lw(v1, a0, 0);
                v0 = sltu(s3, v1);
                s1 = addiu(s1, 36);
                if (v0 == 0) {
                    goto L_004f5884;
                }
                backedge(ctx);
            }
            goto L_004f5a08;
        }
    L_004f5884:
        charge(ctx, 4);
        lw(v0, s2, 4);
        at = sltu(0, v0);
        t5 = 0;
        if (at != 0) {
            // 0x004f5894
            charge(ctx, 1);
            t4 = 0;
            for (;;) {
                // 0x004f5898
                charge(ctx, 6);
                lw(v1, s2, 8);
                v0 = si(-1);
                v1 = addu(v1, t4);
                lw(a0, v1, 0);
                if (a0 != v0) {
                    // 0x004f58b0
                    charge(ctx, 11);
                    lw(v0, s6, 8);
                    v1 = sll(a0, 2);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 3);
                    t1 = addu(v0, v1);
                    lw(v0, t1, 28);
                    lw(a0, v0, 8);
                    lw(v1, a0, 0);
                    at = sltu(0, v1);
                    t2 = 0;
                    if (at == 0) {
                        goto L_004f5994;
                    }
                    // 0x004f58dc
                    charge(ctx, 3);
                    v0 = 1;
                    t3 = 0;
                    t0 = sllv(v0, t5);
                    for (;;) {
                        // 0x004f58e8
                        charge(ctx, 3);
                        at = sltu(t2, v1);
                        if (at == 0) {
                            // 0x004f5900
                            charge(ctx, 1);
                            v0 = 0;
                        } else {
                            // 0x004f58f4
                            charge(ctx, 3);
                            lw(v0, a0, 12);
                            v0 = addu(v0, t3);
                        }
                        // 0x004f5904
                        charge(ctx, 3);
                        lw(v1, v0, 4);
                        if (v1 != 0) {
                            // 0x004f5910
                            charge(ctx, 5);
                            lw(v1, s2, 28);
                            lw(v1, v1, 8);
                            lw(a0, v1, 0);
                            lw(a1, v0, 0);
                            if (a0 != 0) {
                                // 0x004f5924
                                charge(ctx, 4);
                                lw(a3, v1, 12);
                                at = sltu(0, a0);
                                a2 = 0;
                                if (at == 0) {
                                    goto L_004f5958;
                                }
                                for (;;) {
                                    // 0x004f5934
                                    charge(ctx, 3);
                                    lw(v1, a3, 0);
                                    if (v1 == a1) {
                                        goto L_004f5940_20;
                                    }
                                    // 0x004f5948
                                    charge(ctx, 4);
                                    a2 = addiu(a2, 1);
                                    v1 = sltu(a2, a0);
                                    a3 = addiu(a3, 36);
                                    if (v1 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                goto L_004f5958;
                            }
                        L_004f5958:
                            charge(ctx, 1);
                            a3 = 0;
                        L_004f595c:
                            charge(ctx, 2);
                            if (a3 == 0) {
                                goto L_004f5a44;
                            }
                            // 0x004f5964
                            charge(ctx, 4);
                            lw(v1, a3, 24);
                            v1 = v1 & t0;
                            if (v1 == 0) {
                                goto L_004f5a44;
                            }
                            // 0x004f5974
                            charge(ctx, 3);
                            lw(a1, v0, 12);
                            if (a1 == 0) {
                                // 0x004f5a2c
                                charge(ctx, 6);
                                lw(a0, a3, 12);
                                lw(v1, a0, 0);
                                sw(v1, v0, 16);
                                sw(v0, a0, 0);
                                lw(v1, a3, 12);
                                sw(v1, v0, 12);
                                goto L_004f5a44;
                            }
                            // 0x004f5980
                            charge(ctx, 5);
                            lw(a2, a3, 12);
                            a0 = s5;
                            jal(ctx, 0x4F5984u, gen::fn_sub_4F4FE0_004f4fe0);
                            lw(v0, t1, 28);
                            goto L_004f5a48;
                        }
                    L_004f5a44:
                        charge(ctx, 1);
                        lw(v0, t1, 28);
                    L_004f5a48:
                        charge(ctx, 6);
                        t2 = addiu(t2, 1);
                        lw(a0, v0, 8);
                        lw(v1, a0, 0);
                        v0 = sltu(t2, v1);
                        t3 = addiu(t3, 36);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004f5a60
                    charge(ctx, 2);
                    lw(v0, s2, 4);
                    backedge(ctx);
                    goto L_004f5998;
                }
            L_004f5994:
                charge(ctx, 1);
                lw(v0, s2, 4);
            L_004f5998:
                charge(ctx, 4);
                t5 = addiu(t5, 1);
                v0 = sltu(t5, v0);
                t4 = addiu(t4, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004f59a8
        charge(ctx, 3);
        s4 = addiu(s4, -1);
        s2 = addiu(s2, 40);
        if (s4 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004f59b4
    charge(ctx, 2);
    v0 = 0;
    // 0x004f5a68 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
    return;
L_004f5940_20:
    charge(ctx, 2);
    goto L_004f595c;
L_004f5a08:
    charge(ctx, 9);
    v0 = 1;
    a0 = 32;
    link(ctx, 0x4F5A10u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x88);
    call(ctx, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0x8C);
    a0 = addiu(sp, 0x88);
    jal(ctx, 0x4F5A1Cu, gen::fn_sub_4C1C50_004c1c50);
    v0 = 32;
    // 0x004f5a68 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}


// sub_4F5A90 [rxPipelineCountSlots] -- numbers the slot chains: the bits used along each chain, the first free bit index as its slot; the highest + 1 is the pipeline's slot count
// 0x004F5A90 sub_4F5A90 -- 236 bytes; leaf frame (no stack)
void sub_4F5A90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x004f5a90
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(t2, a1, 0);
    t3 = 0;
    if (t2 != 0) {
        // 0x004f5a9c
        charge(ctx, 1);
        a1 = 1;
        for (;;) {
            // 0x004f5aa0
            charge(ctx, 2);
            a2 = 0;
            a3 = t2;
            for (;;) {
                // 0x004f5aa8
                charge(ctx, 3);
                lw(v1, a3, 0);
                if (v1 != 0) {
                    // 0x004f5ab4
                    charge(ctx, 1);
                    for (;;) {
                        // 0x004f5ab8
                        charge(ctx, 7);
                        lw(v0, v1, 20);
                        lw(v0, v0, 8);
                        lw(v1, v1, 16);
                        a2 = a2 | v0;
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004f5ad4
                    charge(ctx, 1);
                }
                // 0x004f5ad8
                charge(ctx, 3);
                lw(a3, a3, 4);
                if (a3 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004f5ae4
            charge(ctx, 3);
            v0 = a2 & 0x1;
            t1 = 0;
            if (v0 != 0) {
                for (;;) {
                    // 0x004f5af0
                    charge(ctx, 7);
                    a2 = srl(a2, 1);
                    v0 = a2 & 0x1;
                    t1 = addiu(t1, 1);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004f5b0c
                charge(ctx, 1);
            }
            // 0x004f5b10
            charge(ctx, 3);
            v0 = sltu(t1, t3);
            if (v0 == 0) {
                // 0x004f5b1c
                charge(ctx, 1);
                t3 = addiu(t1, 1);
            }
            // 0x004f5b20
            charge(ctx, 2);
            a2 = t2;
            a3 = sllv(a1, t1);
            for (;;) {
                // 0x004f5b28
                charge(ctx, 3);
                lw(t0, a2, 0);
                if (t0 != 0) {
                    // 0x004f5b34
                    charge(ctx, 1);
                    for (;;) {
                        // 0x004f5b38
                        charge(ctx, 8);
                        sw(t1, t0, 28);
                        lw(v1, t0, 20);
                        lw(v0, v1, 8);
                        v0 = v0 | a3;
                        sw(v0, v1, 8);
                        lw(t0, t0, 16);
                        if (t0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x004f5b58
                charge(ctx, 3);
                lw(a2, a2, 4);
                if (a2 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004f5b64
            charge(ctx, 3);
            lw(t2, t2, 8);
            if (t2 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004f5b70 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    sw(t3, a0, 12);
    v0 = 0;
}


// sub_4F5B80 [rxSlotSortKeys] -- fills the slot sort records: per slot its key (the first node using it) and the chain
// 0x004F5B80 sub_4F5B80 -- 208 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F5B80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f5b80
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
    s1 = 0;
    s0 = s4;
    if (s4 != 0) {
        for (;;) {
            // 0x004f5bb4
            charge(ctx, 2);
            a0 = s4;
            if (s4 != s0) {
                // 0x004f5bbc
                charge(ctx, 3);
                lw(v0, s0, 0);
                lw(v1, v0, 0);
                for (;;) {
                    // 0x004f5bc8
                    charge(ctx, 4);
                    lw(v0, a0, 0);
                    lw(v0, v0, 0);
                    if (v0 == v1) {
                        break;
                    }
                    // 0x004f5bd8
                    charge(ctx, 3);
                    lw(a0, a0, 8);
                    if (a0 == s0) {
                        goto L_004f5be4_5;
                    }
                    backedge(ctx);
                }
            }
        L_004f5be8:
            charge(ctx, 2);
            if (a0 == s0) {
                // 0x004f5c08
                charge(ctx, 2);
                if (s3 != 0) {
                    // 0x004f5c10
                    charge(ctx, 6);
                    lw(v0, s0, 0);
                    a1 = s1;
                    lw(a0, v0, 0);
                    a2 = s2;
                    jalr(ctx, 0x4F5C1Cu, s3.u());
                }
                // 0x004f5c28
                charge(ctx, 2);
                s1 = addiu(s1, 1);
                backedge(ctx);
            }
            // 0x004f5bf0
            charge(ctx, 3);
            lw(s0, s0, 8);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004f5bfc
        charge(ctx, 1);
    }
    // 0x004f5c00
    charge(ctx, 2);
    v0 = s1;
    // 0x004f5c30
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004f5be4_5:
    charge(ctx, 1);
    goto L_004f5be8;
}


// sub_4F5C50 [rxSlotSort] -- sorts the slot records by key (sub_4F7080) and renumbers them in that order
// 0x004F5C50 sub_4F5C50 -- 220 bytes; frame 0x10: ra sp+0x0
void sub_4F5C50(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f5c50
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t2 = a0;
    sd(ra, sp, 0x0);
    t0 = 0;
    lw(a1, a0, 8);
    lw(v0, a1, 28);
    lw(a0, v0, 8);
    lw(v1, a0, 0);
    at = sltu(0, v1);
    t1 = 0;
    if (at != 0) {
        // 0x004f5c7c
        charge(ctx, 2);
        a3 = 0;
        a2 = 0;
        for (;;) {
            // 0x004f5c84
            charge(ctx, 3);
            at = sltu(t1, v1);
            if (at == 0) {
                // 0x004f5c9c
                charge(ctx, 1);
                a0 = 0;
            } else {
                // 0x004f5c90
                charge(ctx, 3);
                lw(v0, a0, 12);
                a0 = addu(v0, a3);
            }
            // 0x004f5ca0
            charge(ctx, 5);
            lw(v0, a0, 4);
            v0 = addiu(v0, -1);
            at = sltiu(v0, 2);
            if (at != 0) {
                // 0x004f5cf8
                charge(ctx, 11);
                lw(v1, t2, 28);
                t0 = addiu(t0, 1);
                lw(v0, a0, 0);
                v1 = addu(v1, a2);
                sw(v0, v1, 0);
                a2 = addiu(a2, 12);
                lw(v0, a0, 4);
                sw(v0, v1, 4);
                lw(v0, a0, 28);
                sw(v0, v1, 8);
                backedge(ctx);
            }
            // 0x004f5cb4
            charge(ctx, 7);
            lw(v0, a1, 28);
            t1 = addiu(t1, 1);
            lw(a0, v0, 8);
            lw(v1, a0, 0);
            v0 = sltu(t1, v1);
            a3 = addiu(a3, 36);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004f5cd0
    charge(ctx, 10);
    sw(t0, t2, 24);
    a2 = 12;
    lw(a0, t2, 28);
    a3 = 0;
    lw(a1, t2, 24);
    t0 = 0;
    t1 = si(-1);
    jal(ctx, 0x4F5CE8u, gen::fn_sub_4F7080_004f7080);
    ld(ra, sp, 0x0);
    // 0x004f5d24
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}


// sub_4F5D90 [rxPipelineAssignSlots] -- the assignment pass: slots sorted (sub_4F5B80, sub_4F5C50), then each node's input-to-slot map and slot cluster refs written into the super block
// 0x004F5D90 sub_4F5D90 -- 944 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F5D90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f5d90
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    a2 = 0;
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = 0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 8);
    lw(v0, v0, 28);
    lw(a0, v0, 8);
    lw(v1, a0, 0);
    at = sltu(0, v1);
    s1 = a1;
    if (at != 0) {
        // 0x004f5dd8
        charge(ctx, 1);
        a1 = 0;
        for (;;) {
            // 0x004f5ddc
            charge(ctx, 3);
            at = sltu(a2, v1);
            if (at == 0) {
                // 0x004f5df4
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x004f5de8
                charge(ctx, 3);
                lw(v0, a0, 12);
                v0 = addu(v0, a1);
            }
            // 0x004f5df8
            charge(ctx, 5);
            lw(v0, v0, 4);
            v0 = addiu(v0, -1);
            at = sltiu(v0, 2);
            if (at != 0) {
                // 0x004f5e0c
                charge(ctx, 1);
                s3 = addiu(s3, 1);
            }
            // 0x004f5e10
            charge(ctx, 4);
            a2 = addiu(a2, 1);
            v0 = sltu(a2, v1);
            a1 = addiu(a1, 36);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004f5e20
    charge(ctx, 38);
    a0 = s1;
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x4F5E28u, gen::fn_sub_4F5B80_004f5b80);
    s0 = v0;
    a0 = 0;
    jal(ctx, 0x4F5E34u, gen::fn_sub_4F30E0_004f30e0);
    s2 = v0;
    a0 = 0;
    jal(ctx, 0x4F5E40u, gen::fn_sub_4F3150_004f3150);
    a2 = subu(s2, v0);
    a0 = v0;
    a1 = 0;
    jal(ctx, 0x4F5E50u, gen::fn_memset_00521408);
    lw(v0, s5, 12);
    v1 = addiu(v0, -1);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v0 = sll(v0, 2);
    a0 = addiu(v0, 48);
    jal(ctx, 0x4F5E6Cu, gen::fn_sub_4F3150_004f3150);
    sw(v0, s5, 20);
    a1 = 0x4F0000;
    lw(v1, s5, 12);
    a0 = s1;
    lw(v0, s5, 20);
    a1 = addiu(a1, 23856);  // &sub_4F5D30
    a2 = addiu(sp, 0x7C);
    sh(v1, v0, 2);
    lw(v0, s5, 20);
    sw(s5, v0, 4);
    sw(zero, s5, 16);
    link(ctx, 0x4F5EA0u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x7C);
    call(ctx, gen::fn_sub_4F5B80_004f5b80);
    lw(v0, s5, 4);
    at = sltu(0, v0);
    s1 = 0;
    if (at != 0) {
        // 0x004f5eb8
        charge(ctx, 1);
        s2 = 0;
        for (;;) {
            // 0x004f5ebc
            charge(ctx, 4);
            lw(v1, s5, 8);
            lw(v0, s5, 12);
            s4 = addu(v1, s2);
            if (v0 != 0) {
                // 0x004f6078
                charge(ctx, 4);
                a0 = sll(v0, 2);
                jal(ctx, 0x4F6078u, gen::fn_sub_4F3150_004f3150);
                sw(v0, s4, 12);
                backedge(ctx);
            }
            // 0x004f5ecc
            charge(ctx, 9);
            lw(v0, s5, 12);
            v0 = addiu(v0, 1);
            a0 = sll(v0, 2);
            jal(ctx, 0x4F5ED4u, gen::fn_sub_4F3150_004f3150);
            sw(v0, s4, 16);
            lw(v0, s4, 0);
            lw(v0, v0, 32);
            if (v0 != 0) {
                // 0x004f6088
                charge(ctx, 4);
                a0 = sll(v0, 2);
                jal(ctx, 0x4F6088u, gen::fn_sub_4F3150_004f3150);
                sw(v0, s4, 24);
                backedge(ctx);
            }
            // 0x004f5ef0
            charge(ctx, 4);
            lw(v0, s4, 0);
            lw(v0, v0, 52);
            if (v0 != 0) {
                // 0x004f6098
                charge(ctx, 6);
                v1 = addiu(v0, 3);
                v0 = si(-4);
                a0 = v1 & v0;
                jal(ctx, 0x4F60A0u, gen::fn_sub_4F3150_004f3150);
                sw(v0, s4, 20);
                backedge(ctx);
            }
            // 0x004f5f00
            charge(ctx, 7);
            lw(v0, s4, 28);
            a1 = si(-1);
            lw(a3, v0, 8);
            lw(a2, a3, 0);
            at = sltu(0, a2);
            v1 = 0;
            if (at != 0) {
                // 0x004f5f1c
                charge(ctx, 1);
                a0 = 0;
                for (;;) {
                    // 0x004f5f20
                    charge(ctx, 3);
                    at = sltu(v1, a2);
                    t2 = 0;
                    if (at == 0) {
                        // 0x004f5f38
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x004f5f2c
                        charge(ctx, 3);
                        lw(v0, a3, 12);
                        v0 = addu(v0, a0);
                    }
                    // 0x004f5f3c
                    charge(ctx, 3);
                    at = sltu(0, s0);
                    t3 = 0;
                    if (at != 0) {
                        // 0x004f5f48
                        charge(ctx, 3);
                        lw(t0, sp, 0x7C);
                        lw(a3, v0, 0);
                        t1 = t0;
                        for (;;) {
                            // 0x004f5f54
                            charge(ctx, 3);
                            lw(a2, t1, 0);
                            if (a2 == a3) {
                                goto L_004f5f60_21;
                            }
                            // 0x004f5f6c
                            charge(ctx, 4);
                            t3 = addiu(t3, 1);
                            a2 = sltu(t3, s0);
                            t1 = addiu(t1, 8);
                            if (a2 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004f5f7c
                        charge(ctx, 1);
                    }
                L_004f5f80:
                    charge(ctx, 20);
                    lw(a3, v0, 28);
                    lw(a2, s4, 12);
                    v1 = addiu(v1, 1);
                    a3 = sll(a3, 2);
                    a2 = addu(a2, a3);
                    sw(t2, a2, 0);
                    lw(a3, v0, 28);
                    lw(a2, s4, 16);
                    lw(t0, v0, 24);
                    a3 = sll(a3, 2);
                    a2 = addu(a2, a3);
                    sw(t0, a2, 4);
                    lw(a2, v0, 24);
                    lw(v0, s4, 28);
                    a1 = a1 & a2;
                    lw(a3, v0, 8);
                    lw(a2, a3, 0);
                    v0 = sltu(v1, a2);
                    a0 = addiu(a0, 36);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004f5fd0
            charge(ctx, 7);
            lw(v0, s4, 16);
            sw(a1, v0, 0);
            lw(v0, s4, 0);
            lw(v0, v0, 32);
            at = sltu(0, v0);
            a2 = 0;
            if (at != 0) {
                // 0x004f5fec
                charge(ctx, 3);
                t2 = 0;
                t1 = 0;
                a0 = si(-1);
                for (;;) {
                    // 0x004f5ff8
                    charge(ctx, 7);
                    lw(v0, s4, 24);
                    v0 = addu(v0, t2);
                    sw(a0, v0, 0);
                    lw(v1, s5, 12);
                    at = sltu(0, v1);
                    a1 = 0;
                    if (at != 0) {
                        // 0x004f6014
                        charge(ctx, 3);
                        lw(v0, s4, 12);
                        a3 = 0;
                        t0 = v0;
                        for (;;) {
                            // 0x004f6020
                            charge(ctx, 3);
                            lw(t3, t0, 0);
                            if (t3 != 0) {
                                // 0x004f602c
                                charge(ctx, 9);
                                lw(t3, s4, 0);
                                t4 = addu(v0, a3);
                                lw(t4, t4, 0);
                                lw(t3, t3, 36);
                                lw(t4, t4, 0);
                                t3 = addu(t3, t1);
                                lw(t3, t3, 0);
                                if (t4 != t3) {
                                    goto L_004f60b0;
                                }
                                goto L_004f6050_31;
                            }
                        L_004f60b0:
                            charge(ctx, 5);
                            a1 = addiu(a1, 1);
                            t0 = addiu(t0, 4);
                            t3 = sltu(a1, v1);
                            a3 = addiu(a3, 4);
                            if (t3 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004f60c4
                        charge(ctx, 1);
                    }
                L_004f60c8:
                    charge(ctx, 7);
                    lw(v0, s4, 0);
                    a2 = addiu(a2, 1);
                    t2 = addiu(t2, 4);
                    lw(v0, v0, 32);
                    v0 = sltu(a2, v0);
                    t1 = addiu(t1, 12);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004f60e4
                charge(ctx, 1);
            }
            // 0x004f60e8
            charge(ctx, 5);
            lw(v0, s5, 4);
            s1 = addiu(s1, 1);
            v0 = sltu(s1, v0);
            s2 = addiu(s2, 40);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004f60fc
        charge(ctx, 2);
        backedge(ctx);
    }
    // 0x004f6060
    charge(ctx, 2);
    if (s3 != 0) {
        // 0x004f6104
        charge(ctx, 6);
        v0 = sll(s3, 1);
        v0 = addu(v0, s3);
        a0 = sll(v0, 2);
        jal(ctx, 0x4F610Cu, gen::fn_sub_4F3150_004f3150);
        sw(v0, s5, 28);
        backedge(ctx);
    }
    // 0x004f6068
    charge(ctx, 4);
    a0 = s5;
    jal(ctx, 0x4F6068u, gen::fn_sub_4F5C50_004f5c50);
    v0 = 0;
    // 0x004f611c
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
L_004f5f60_21:
    charge(ctx, 3);
    a2 = sll(t3, 3);
    t2 = addu(t0, a2);
    goto L_004f5f80;
L_004f6050_31:
    charge(ctx, 4);
    lw(v0, s4, 24);
    v0 = addu(v0, t2);
    sw(a1, v0, 0);
    goto L_004f60c8;
}


// sub_4F6140 [rxPipelineClusterPasses] -- runs the unlock's cluster passes in order: requirements, propagation, slot allocation, slot count, assignment; the first error, or 0
// 0x004F6140 sub_4F6140 -- 128 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4F6140(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f6140
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    link(ctx, 0x4F6150u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x2C);
    call(ctx, gen::fn_sub_4F50A0_004f50a0);
    if (v0 == 0) {
        // 0x004f6168
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x4F6168u, gen::fn_sub_4F5520_004f5520);
        if (v0 == 0) {
            // 0x004f6178
            charge(ctx, 5);
            a0 = s0;
            a1 = addiu(sp, 0x2C);
            jal(ctx, 0x4F617Cu, gen::fn_sub_4F57F0_004f57f0);
            if (v0 != 0) {
                goto L_004f61b0;
            }
            // 0x004f618c
            charge(ctx, 5);
            a0 = s0;
            a1 = addiu(sp, 0x2C);
            jal(ctx, 0x4F6190u, gen::fn_sub_4F5A90_004f5a90);
            if (v0 != 0) {
                goto L_004f61b0;
            }
            // 0x004f61a0
            charge(ctx, 4);
            link(ctx, 0x4F61A0u);  // $ra first: the delay slot below depends on it
            lw(a1, sp, 0x2C);
            call(ctx, gen::fn_sub_4F5D90_004f5d90);
            backedge(ctx);
            goto L_004f6160;
        }
    L_004f61b0:
        charge(ctx, 1);
        ld(ra, sp, 0x10);
        // 0x004f61b4 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_004f6160:
    charge(ctx, 2);
    ld(ra, sp, 0x10);
    // 0x004f61b4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4F63D0 [rxHeapGrow] -- grows an RxHeap by a super block of max(size + 96, the heap's block size) (RwMalloc, 128-aligned start), its first free block made; 'Heap resized from %d to %d bytes'; the block's free header, or 0
// 0x004F63D0 sub_4F63D0 -- 284 bytes; frame 0x140: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F63D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f63d0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = addiu(a1, 96);
    lw(v0, a0, 0);
    at = sltu(s1, v0);
    s2 = a0;
    if (at != 0) {
        // 0x004f63f8
        charge(ctx, 1);
        s1 = v0;
    }
    // 0x004f63fc
    charge(ctx, 9);
    v0 = 0x1040000;
    a1 = v0 | 0x409;  // &0x1040409
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    a0 = addiu(s1, 139);
    jalr(ctx, 0x4F640Cu, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x004f6420
        charge(ctx, 7);
        v1 = addiu(s0, 12);
        v0 = si(-128);
        v1 = addiu(v1, 127);
        v0 = v1 & v0;
        sw(v0, s0, 0);
        sw(s1, s0, 4);
        sw(zero, s0, 8);
    }
    // 0x004f643c
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x004f6444
        charge(ctx, 6);
        lw(a1, s2, 4);
        a0 = s0;
        a2 = s2;
        jal(ctx, 0x4F644Cu, gen::fn_sub_4F62D0_004f62d0);
        if (v0 == 0) {
            // 0x004f645c
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x004f6464
                charge(ctx, 4);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                a0 = s0;
                jalr(ctx, 0x4F646Cu, v0.u());
            }
            goto L_004f6474;
        }
        // 0x004f647c
        charge(ctx, 6);
        lw(v0, s2, 4);
        sw(v0, s0, 8);
        sw(s0, s2, 4);
        lw(v1, s2, 4);
        a3 = 0;
        if (v1 != 0) {
            for (;;) {
                // 0x004f6494
                charge(ctx, 7);
                lw(v0, v1, 4);
                lw(v1, v1, 8);
                a3 = addu(a3, v0);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004f64b0
        charge(ctx, 9);
        v0 = 0x960000;
        lw(v0, v0, 308);  // 0x960134 (the engine's sprintf slot)
        a1 = 0x780000;
        a2 = subu(a3, s1);
        a0 = addiu(sp, 0x40);
        a1 = addiu(a1, -3520);  // "Heap resized from %d to %d bytes"
        jalr(ctx, 0x4F64C4u, v0.u());
        lw(v0, s0, 0);
        v0 = addiu(v0, 32);
        // 0x004f64d4 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x140);
        return;
    }
L_004f6474:
    charge(ctx, 2);
    v0 = 0;
    // 0x004f64d4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x140);
}


// sub_4F64F0 [rxHeapSplit] -- allocates $a2 bytes from a free block: split when 256 or more bytes remain (the rest stays free in the same entry), else the whole block taken and its free entry removed; the user pointer (header + 32)
// 0x004F64F0 sub_4F64F0 -- 192 bytes; leaf frame (no stack)
void sub_4F64F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x004f64f0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a1, 0);
    v0 = subu(v0, a2);
    at = sltiu(v0, 256);
    if (at == 0) {
        // 0x004f6558
        charge(ctx, 14);
        lw(a3, a1, 4);
        v0 = addiu(v0, -32);
        a0 = addu(a2, a3);
        sw(v0, a0, 40);
        v1 = addiu(a0, 32);
        sw(a3, a0, 32);
        lw(v0, a3, 4);
        sw(v0, a0, 36);
        sw(a1, a0, 44);
        sw(a2, a3, 8);
        sw(v1, a3, 4);
        lw(v0, a0, 36);
        if (v0 != 0) {
            // 0x004f6590
            charge(ctx, 1);
            sw(v1, v0, 0);
        }
        // 0x004f6594
        charge(ctx, 5);
        sw(v1, a1, 4);
        v0 = addiu(a3, 32);
        lw(v1, v1, 8);
        sw(v1, a1, 0);
        sw(zero, a3, 12);
    } else {
        // 0x004f6504
        charge(ctx, 7);
        lw(a2, a0, 20);
        lw(v1, a0, 12);
        v0 = addiu(a2, -1);
        v0 = sll(v0, 3);
        v0 = addu(v1, v0);
        lw(a3, a1, 4);
        if (v0 != a1) {
            // 0x004f6520
            charge(ctx, 8);
            v0 = sll(a2, 3);
            v0 = addu(v0, v1);
            lwc1(f1, v0, -8);
            lwc1(f0, v0, -4);
            swc1(f1, a1, 0);
            swc1(f0, a1, 4);
            lw(v0, a1, 4);
            sw(a1, v0, 12);
        }
        // 0x004f6540
        charge(ctx, 6);
        lw(v1, a0, 20);
        v0 = addiu(a3, 32);
        v1 = addiu(v1, -1);
        sw(v1, a0, 20);
        sw(zero, a3, 12);
    }
    // 0x004f65a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_4F65B0 [RxHeapFree] -- frees an RxHeap block: merged with a free previous and / or next block (their entries removed or reused), else given a new free entry
// 0x004F65B0 sub_4F65B0 -- 500 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4F65B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x004f65b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t0 = 0;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a2, a1, -32);
    s0 = addiu(a1, -32);
    if (a2 != 0) {
        // 0x004f65cc
        charge(ctx, 3);
        lw(v1, a2, 12);
        if (v1 != 0) {
            // 0x004f65d8
            charge(ctx, 1);
            t0 = 1;
        }
    }
    // 0x004f65dc
    charge(ctx, 3);
    lw(a1, s0, heapblock::kNext);
    a3 = 0;
    if (a1 != 0) {
        // 0x004f65e8
        charge(ctx, 3);
        lw(v1, a1, 12);
        if (v1 != 0) {
            // 0x004f65f4
            charge(ctx, 2);
            a3 = 1;
        }
    }
    // 0x004f6718
    charge(ctx, 2);
    if (t0 != 0) {
        // 0x004f6720
        charge(ctx, 2);
        backedge(ctx);
        // 0x004f65fc
        charge(ctx, 2);
        if (a3 == 0) {
            // 0x004f6728
            charge(ctx, 15);
            lw(a0, s0, heapblock::kSize);
            lw(v1, a2, 8);
            a0 = addiu(a0, 32);
            v1 = addu(v1, a0);
            sw(v1, a2, 8);
            lw(v1, s0, heapblock::kPrev);
            lw(a0, v1, 8);
            lw(v1, v1, 12);
            sw(a0, v1, 0);
            lw(a0, s0, heapblock::kNext);
            lw(v1, s0, heapblock::kPrev);
            sw(a0, v1, 4);
            lw(a0, s0, heapblock::kNext);
            if (a0 == 0) {
                goto L_004f6794;
            }
            // 0x004f6764
            charge(ctx, 3);
            lw(v1, s0, heapblock::kPrev);
            sw(v1, a0, 0);
            backedge(ctx);
            goto L_004f6710;
        }
        // 0x004f6604
        charge(ctx, 8);
        lw(a3, a1, 12);
        lw(a2, a0, 20);
        lw(a1, a0, 12);
        v1 = addiu(a2, -1);
        v1 = sll(v1, 3);
        v1 = addu(a1, v1);
        if (v1 != a3) {
            // 0x004f6624
            charge(ctx, 8);
            v1 = sll(a2, 3);
            v1 = addu(v1, a1);
            lwc1(f1, v1, -8);
            lwc1(f0, v1, -4);
            swc1(f1, a3, 0);
            swc1(f0, a3, 4);
            lw(v1, a3, 4);
            sw(a3, v1, 12);
        }
        // 0x004f6644
        charge(ctx, 24);
        lw(v1, a0, 20);
        v1 = addiu(v1, -1);
        sw(v1, a0, 20);
        lw(v1, s0, heapblock::kNext);
        lw(a0, s0, heapblock::kPrev);
        lw(a2, s0, heapblock::kSize);
        lw(a1, v1, 8);
        lw(v1, a0, 8);
        a1 = addu(a2, a1);
        a1 = addiu(a1, 64);
        v1 = addu(v1, a1);
        sw(v1, a0, 8);
        lw(v1, s0, heapblock::kPrev);
        lw(a0, v1, 8);
        lw(v1, v1, 12);
        sw(a0, v1, 0);
        lw(a0, s0, heapblock::kNext);
        lw(v1, s0, heapblock::kPrev);
        lw(a0, a0, 4);
        sw(a0, v1, 4);
        lw(v1, s0, heapblock::kNext);
        lw(a0, v1, 4);
        if (a0 == 0) {
            goto L_004f6794;
        }
        // 0x004f66a4
        charge(ctx, 3);
        lw(v1, s0, heapblock::kPrev);
        sw(v1, a0, 0);
        goto L_004f6710;
    }
    backedge(ctx);
    // 0x004f66b0
    charge(ctx, 2);
    if (a3 != 0) {
        // 0x004f66b8
        charge(ctx, 21);
        lw(a0, a1, 8);
        lw(v1, s0, heapblock::kSize);
        a0 = addiu(a0, 32);
        v1 = addu(v1, a0);
        sw(v1, s0, heapblock::kSize);
        lw(v1, s0, heapblock::kNext);
        lw(v1, v1, 12);
        sw(v1, s0, heapblock::kFreeEntry);
        lw(v1, s0, heapblock::kNext);
        lw(v1, v1, 12);
        sw(s0, v1, 4);
        lw(v1, s0, heapblock::kNext);
        lw(a0, s0, heapblock::kSize);
        lw(v1, v1, 12);
        sw(a0, v1, 0);
        lw(v1, s0, heapblock::kNext);
        lw(v1, v1, 4);
        sw(v1, s0, heapblock::kNext);
        lw(v1, s0, heapblock::kNext);
        if (v1 == 0) {
            goto L_004f6794;
        }
        // 0x004f670c
        charge(ctx, 1);
        sw(s0, v1, 0);
        goto L_004f6710;
    }
    // 0x004f6770
    charge(ctx, 4);
    jal(ctx, 0x4F6770u, gen::fn_sub_4F61C0_004f61c0);
    if (v0 == 0) {
    L_004f6794:
        charge(ctx, 1);
        ld(ra, sp, 0x10);
    } else {
        // 0x004f6780
        charge(ctx, 5);
        sw(s0, v0, 4);
        lw(v1, s0, heapblock::kSize);
        sw(v1, v0, 0);
        sw(v0, s0, heapblock::kFreeEntry);
        backedge(ctx);
    L_004f6710:
        charge(ctx, 2);
        ld(ra, sp, 0x10);
    }
    // 0x004f6798 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4F67B0 [RxHeapAlloc] -- allocates from an RxHeap: the size rounded to 32, the free entries searched from the last, the heap grown when none fits (sub_4F63D0); the heap marked dirty; the block, or error 0x80000013 (out of memory) and 0
// 0x004F67B0 sub_4F67B0 -- 224 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F67B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f67b0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = si(-32);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(a2, a0, 20);
    v1 = addiu(s0, 31);
    s0 = v1 & v0;
    lw(v0, a0, 12);
    v1 = addiu(a2, -1);
    v1 = sll(v1, 3);
    a1 = addu(v0, v1);
    for (;;) {
        // 0x004f67e8
        charge(ctx, 4);
        lw(v0, a1, 0);
        v0 = sltu(v0, s0);
        if (v0 == 0) {
            goto L_004f67f8_2;
        }
        // 0x004f6814
        charge(ctx, 3);
        a2 = addiu(a2, -1);
        a1 = addiu(a1, -8);
        if (a2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004f6820
    charge(ctx, 5);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x4F6824u, gen::fn_sub_4F63D0_004f63d0);
    if (v0 == 0) {
        // 0x004f6854
        charge(ctx, 10);
        v0 = 1;
        a1 = s0;
        sw(v0, sp, 0x38);
        v0 = lui(0x8000);
        a0 = v0 | 0x13;
        jal(ctx, 0x4F6864u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x3C);
        a0 = addiu(sp, 0x38);
        jal(ctx, 0x4F6870u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x004f6834
        charge(ctx, 8);
        v1 = 1;
        a2 = s0;
        sw(v1, s1, rxheap::kDirty);
        lw(a1, v0, 12);
        a0 = s1;
        jal(ctx, 0x4F6844u, gen::fn_sub_4F64F0_004f64f0);
    }
    // 0x004f687c
    charge(ctx, 1);
    ld(ra, sp, 0x20);
    // 0x004f6880 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_004f67f8_2:
    charge(ctx, 7);
    v0 = 1;
    a2 = s0;
    sw(v0, s1, rxheap::kDirty);
    a0 = s1;
    jal(ctx, 0x4F6804u, gen::fn_sub_4F64F0_004f64f0);
    ld(ra, sp, 0x20);
    // 0x004f6880 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4F6970 [RxHeapDestroy] -- destroys an RxHeap: the free-entry array, every super block, the record (RwFree)
// 0x004F6970 sub_4F6970 -- 152 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F6970(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f6970
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    if (s2 != 0) {
        // 0x004f698c
        charge(ctx, 3);
        lw(a0, s2, rxheap::kFreeEntries);
        if (a0 != 0) {
            // 0x004f6998
            charge(ctx, 5);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            jalr(ctx, 0x4F69A0u, v0.u());
            sw(zero, s2, rxheap::kFreeEntries);
        }
        // 0x004f69ac
        charge(ctx, 3);
        lw(a0, s2, rxheap::kSuperBlocks);
        if (a0 != 0) {
            // 0x004f69b8
            charge(ctx, 2);
            s0 = 0x960000;
            s0 = addiu(s0, 380);  // &0x96017C (RwFree slot)
            for (;;) {
                // 0x004f69c0
                charge(ctx, 2);
                lw(s1, a0, 8);
                if (a0 != 0) {
                    // 0x004f69c8
                    charge(ctx, 4);
                    lw(v0, s0, 0);
                    jalr(ctx, 0x4F69CCu, v0.u());
                }
                // 0x004f69d8
                charge(ctx, 2);
                a0 = s1;
                if (s1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004f69e0
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        a0 = s2;
        jalr(ctx, 0x4F69E8u, v0.u());
    }
    // 0x004f69f0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4F6A10 [RxHeapCreate] -- creates an RxHeap of at least 1,024 bytes: the 28-byte record and its first super block (size rounded to 32, a 128-aligned start), the free entries set up (sub_4F6890); the heap, or 0
// 0x004F6A10 sub_4F6A10 -- 312 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F6A10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f6a10
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    s2 = a0;
    sq(s1, sp, 0x10);
    at = sltiu(s2, 1024);
    sq(s0, sp, 0x0);
    if (at != 0) {
        // 0x004f6a30
        charge(ctx, 1);
        s2 = 1024;
    }
    // 0x004f6a34
    charge(ctx, 10);
    s0 = 0x960000;
    v1 = 0x40000;
    s0 = addiu(s0, 376);  // &0x960178 (RwMalloc slot)
    a0 = 28;
    lw(v0, s0, 0);  // 0x960178 (RwMalloc slot)
    a1 = v1 | 0x409;
    jalr(ctx, 0x4F6A48u, v0.u());
    s1 = v0;
    if (s1 != 0) {
        // 0x004f6a5c
        charge(ctx, 6);
        v1 = addiu(s2, 31);
        v0 = si(-32);
        s2 = v1 & v0;
        at = sltiu(s2, 128);
        if (at != 0) {
            // 0x004f6a74
            charge(ctx, 1);
            s2 = 128;
        }
        // 0x004f6a78
        charge(ctx, 8);
        lw(v0, s0, 0);
        v1 = 0x1040000;
        a0 = addiu(s2, 139);
        a1 = v1 | 0x409;  // &0x1040409
        jalr(ctx, 0x4F6A84u, v0.u());
        s0 = v0;
        if (s0 != 0) {
            // 0x004f6a98
            charge(ctx, 7);
            v1 = addiu(s0, 12);
            v0 = si(-128);
            v1 = addiu(v1, 127);
            v0 = v1 & v0;
            sw(v0, s0, 0);
            sw(s2, s0, 4);
            sw(zero, s0, 8);
        }
        // 0x004f6ab4
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x004f6abc
            charge(ctx, 10);
            sw(s2, s1, rxheap::kBlockSize);
            v0 = 1;
            sw(s0, s1, rxheap::kSuperBlocks);
            sw(zero, s1, rxheap::kFreeEntries);
            sw(zero, s1, rxheap::kEntriesCapacity);
            sw(zero, s1, rxheap::kNumFree);
            sw(v0, s1, rxheap::kDirty);
            lw(v1, s1, rxheap::kDirty);
            if (v1 != 0) {
                // 0x004f6aec
                charge(ctx, 2);
                a0 = s1;
                jal(ctx, 0x4F6AECu, gen::fn_sub_4F6890_004f6890);
            } else {
                // 0x004f6ae4
                charge(ctx, 2);
            }
            // 0x004f6af4
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x004f6afc
                charge(ctx, 2);
                if (s0 != 0) {
                    // 0x004f6b04
                    charge(ctx, 4);
                    v0 = 0x960000;
                    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
                    a0 = s0;
                    jalr(ctx, 0x4F6B0Cu, v0.u());
                }
                goto L_004f6b14;
            }
            // 0x004f6b2c
            charge(ctx, 1);
            v0 = s1;
            // 0x004f6b30 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_004f6b14:
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        a0 = s1;
        jalr(ctx, 0x4F6B1Cu, v0.u());
    }
    // 0x004f6b24
    charge(ctx, 2);
    v0 = 0;
    // 0x004f6b30 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4F6B50 [RxRenderStateVectorSetDefaultRenderStateVector] -- fills a render-state vector with the defaults: flags 7, gouraud shading, blend src 5 / dest 6, no raster, wrap addressing, linear filter, the border / fog colours
// Only the module's own vector (else error 0x80000018); a device that keeps its own (id 3) copies the module's.
// 0x004F6B50 sub_4F6B50 -- 400 bytes; frame 0x30: ra sp+0x0
void sub_4F6B50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x004f6b50
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x004f6cb0
        charge(ctx, 9);
        v1 = 1;
        v0 = lui(0x8000);
        sw(v1, sp, 0x18);
        a0 = v0 | 0x16;
        jal(ctx, 0x4F6CBCu, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x1C);
        a0 = addiu(sp, 0x18);
        jal(ctx, 0x4F6CC8u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x004f6b5c
        charge(ctx, 5);
        v0 = 0x960000;
        v1 = 3;
        lw(v0, v0, 404);  // 0x960194 (the engine's device id)
        if (v0 == v1) {
            // 0x004f6bb4
            charge(ctx, 26);
            lw(v1, gp, -16840);  // 0x7CEB28 (the pipeline module offset)
            v0 = 0x960000;
            v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            v0 = addu(v0, v1);
            lwc1(f3, v0, 4);
            lwc1(f2, v0, 8);
            lwc1(f1, v0, 12);
            lwc1(f0, v0, 16);
            swc1(f3, a0, 0);
            swc1(f2, a0, 4);
            swc1(f1, a0, 8);
            swc1(f0, a0, 12);
            lwc1(f3, v0, 20);
            lwc1(f2, v0, 24);
            lwc1(f1, v0, 28);
            lwc1(f0, v0, 32);
            swc1(f3, a0, 16);
            swc1(f2, a0, 20);
            swc1(f1, a0, 24);
            swc1(f0, a0, 28);
            lwc1(f2, v0, 36);
            lwc1(f1, v0, 40);
            lwc1(f0, v0, 44);
            swc1(f2, a0, 32);
            swc1(f1, a0, 36);
            swc1(f0, a0, 40);
        L_004f6c1c:
            charge(ctx, 2);
            v0 = a0;
        } else {
            // 0x004f6b70
            charge(ctx, 7);
            lw(v1, gp, -16840);  // 0x7CEB28 (the pipeline module offset)
            v0 = 0x960000;
            v0 = addiu(v0, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
            v0 = addu(v0, v1);
            v0 = addiu(v0, 4);
            if (a0 == v0) {
                // 0x004f6c24
                charge(ctx, 35);
                lbu(t3, gp, -20208);  // 0x7CDE00 (the default render state's border / fog colour)
                a3 = 7;
                lbu(t2, gp, -20207);  // 0x7CDE01
                a2 = 2;
                lbu(t1, gp, -20206);  // 0x7CDE02
                a1 = 5;
                lbu(t0, gp, -20205);  // 0x7CDE03
                v1 = 6;
                v0 = 1;
                sb(t3, sp, 0x2C);
                sb(t2, sp, 0x2D);
                sb(t1, sp, 0x2E);
                sw(a3, a0, 0);
                sw(a2, a0, 4);
                sw(a1, a0, 8);
                sw(v1, a0, 12);
                sw(zero, a0, 16);
                sw(v0, a0, 20);
                sw(v0, a0, 24);
                sw(a2, a0, 28);
                lbu(a2, sp, 0x2C);
                sb(t0, sp, 0x2F);
                lbu(a1, sp, 0x2D);
                lbu(v1, sp, 0x2E);
                lbu(v0, sp, 0x2F);
                sb(a2, a0, 32);
                sb(a1, a0, 33);
                sb(v1, a0, 34);
                sb(v0, a0, 35);
                sw(zero, a0, 36);
                sb(a2, a0, 40);
                sb(a1, a0, 41);
                sb(v1, a0, 42);
                sb(v0, a0, 43);
                backedge(ctx);
                goto L_004f6c1c;
            }
            // 0x004f6b8c
            charge(ctx, 10);
            v1 = 1;
            v0 = lui(0x8000);
            sw(v1, sp, 0x20);
            a0 = v0 | 0x18;
            jal(ctx, 0x4F6B98u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x24);
            a0 = addiu(sp, 0x20);
            jal(ctx, 0x4F6BA4u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        }
    }
    // 0x004f6cd4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4F6CE0 [rxRadixSortPass] -- the radix pass of the slot sort: an explicit-stack partition of the records by the key's bits, highest bit first, down to runs of five
// 0x004F6CE0 sub_4F6CE0 -- 576 bytes; frame 0x1A0: s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F6CE0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x004f6ce0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1A0);
    v1 = sll(a2, 2);
    sq(s1, sp, 0x10);
    t1 = addiu(sp, 0x20);
    sq(s0, sp, 0x0);
    t9 = addiu(t1, 12);
    sw(a0, sp, 0x20);
    t3 = srl(a2, 2);
    sw(a1, sp, 0x24);
    t2 = addu(v1, a2);
    sw(t0, sp, 0x28);
    v1 = sltiu(a2, 4);
    for (;;) {
        // 0x004f6d10
        charge(ctx, 4);
        t9 = addiu(t9, -12);
        lw(a0, t9, 0);
        lw(a1, t9, 4);
        lw(t0, t9, 8);
        for (;;) {
            // 0x004f6d20
            charge(ctx, 3);
            t8 = a0;
            t7 = a1;
            for (;;) {
                // 0x004f6d40
                charge(ctx, 5);
                t4 = addu(a0, a3);
                lw(t4, t4, 0);
                t4 = t0 & t4;
                if (t4 == 0) {
                    backedge(ctx);
                    // 0x004f6d30
                    charge(ctx, 4);
                    a0 = addu(a0, a2);
                    at = sltu(a1, a0);
                    if (at == 0) {
                        continue;
                    }
                } else {
                    // 0x004f6d54
                    charge(ctx, 5);
                    t4 = addu(a1, a3);
                    lw(t4, t4, 0);
                    t4 = t0 & t4;
                    if (t4 == 0) {
                        // 0x004f6ee0
                        charge(ctx, 1);
                        t6 = a0;
                    L_004f6ee4:
                        charge(ctx, 3);
                        t5 = a1;
                        t4 = a2;
                        if (v1 != 0) {
                            backedge(ctx);
                        } else {
                            // 0x004f6ef0
                            charge(ctx, 2);
                            backedge(ctx);
                            // 0x004f6d98
                            charge(ctx, 3);
                            at = sltiu(t3, 9);
                            if (at == 0) {
                                // 0x004f6da4
                                charge(ctx, 2);
                                if (v1 == 0) {
                                    // 0x004f6dac
                                    charge(ctx, 1);
                                    for (;;) {
                                        // 0x004f6db0
                                        charge(ctx, 37);
                                        lw(s1, t5, 0);
                                        lw(s0, t6, 0);
                                        t4 = addiu(t4, -32);
                                        at = sltiu(t4, 36);
                                        sw(s0, t5, 0);
                                        sw(s1, t6, 0);
                                        lw(s1, t5, 4);
                                        lw(s0, t6, 4);
                                        sw(s0, t5, 4);
                                        sw(s1, t6, 4);
                                        lw(s1, t5, 8);
                                        lw(s0, t6, 8);
                                        sw(s0, t5, 8);
                                        sw(s1, t6, 8);
                                        lw(s1, t5, 12);
                                        lw(s0, t6, 12);
                                        sw(s0, t5, 12);
                                        sw(s1, t6, 12);
                                        lw(s1, t5, 16);
                                        lw(s0, t6, 16);
                                        sw(s0, t5, 16);
                                        sw(s1, t6, 16);
                                        lw(s1, t5, 20);
                                        lw(s0, t6, 20);
                                        sw(s0, t5, 20);
                                        sw(s1, t6, 20);
                                        lw(s1, t5, 24);
                                        lw(s0, t6, 24);
                                        sw(s0, t5, 24);
                                        sw(s1, t6, 24);
                                        lw(s1, t5, 28);
                                        lw(s0, t6, 28);
                                        sw(s0, t5, 28);
                                        sw(s1, t6, 28);
                                        t5 = addiu(t5, 32);
                                        t6 = addiu(t6, 32);
                                        if (at != 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004f6e44
                                    charge(ctx, 1);
                                }
                            }
                            // 0x004f6e48
                            charge(ctx, 3);
                            s0 = sltiu(t4, 4);
                            if (s0 == 0) {
                                // 0x004f6e54
                                charge(ctx, 1);
                                for (;;) {
                                    // 0x004f6e58
                                    charge(ctx, 9);
                                    lw(s1, t5, 0);
                                    lw(s0, t6, 0);
                                    t4 = addiu(t4, -4);
                                    at = sltiu(t4, 4);
                                    sw(s0, t5, 0);
                                    sw(s1, t6, 0);
                                    t5 = addiu(t5, 4);
                                    t6 = addiu(t6, 4);
                                    if (at != 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004f6e7c
                                charge(ctx, 1);
                            }
                        }
                        // 0x004f6e80
                        charge(ctx, 5);
                        a0 = addu(a0, a2);
                        a1 = subu(a1, a2);
                        at = sltu(a1, a0);
                        if (at != 0) {
                            goto L_004f6e94_19;
                        }
                        backedge(ctx);
                        continue;
                    }
                    for (;;) {
                        // 0x004f6d68
                        charge(ctx, 4);
                        a1 = subu(a1, a2);
                        at = sltu(a1, a0);
                        if (at != 0) {
                            break;
                        }
                        // 0x004f6d78
                        charge(ctx, 5);
                        t4 = addu(a1, a3);
                        lw(t4, t4, 0);
                        t4 = t0 & t4;
                        if (t4 == 0) {
                            goto L_004f6d8c_8;
                        }
                        backedge(ctx);
                    }
                }
                break;
            }
        L_004f6e98:
            charge(ctx, 3);
            t0 = srl(t0, 1);
            if (t0 == 0) {
                goto L_004f6ed0;
            }
            // 0x004f6ea4
            charge(ctx, 5);
            t4 = addu(a1, a2);
            a1 = addu(t4, t2);
            at = sltu(t7, a1);
            if (at == 0) {
                // 0x004f6ef8
                charge(ctx, 5);
                sw(t4, t9, 0);
                sw(t7, t9, 4);
                sw(t0, t9, 8);
                t9 = addiu(t9, 12);
                backedge(ctx);
            }
            // 0x004f6eb8
            charge(ctx, 5);
            a1 = subu(a0, a2);
            t4 = addu(t8, t2);
            at = sltu(a1, t4);
            a0 = t8;
            if (at != 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004f6ecc
        charge(ctx, 1);
    L_004f6ed0:
        charge(ctx, 2);
        if (t9 == t1) {
            break;
        }
        backedge(ctx);
    }
    // 0x004f6ed8
    charge(ctx, 2);
    // 0x004f6f10
    charge(ctx, 4);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x1A0);
    return;
L_004f6d8c_8:
    charge(ctx, 2);
    t6 = a0;
    goto L_004f6ee4;
L_004f6e94_19:
    charge(ctx, 1);
    goto L_004f6e98;
}


// sub_4F6F20 [rxInsertionSortPass] -- the insertion pass of the slot sort: records of stride $a2 ordered by the int key at $a3
// 0x004F6F20 sub_4F6F20 -- 352 bytes; leaf frame (no stack)
void sub_4F6F20(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    // 0x004f6f20
    enter(ctx, 3);  // entry check point + this block's cycles
    a1 = addiu(a1, -1);
    a0 = addu(a0, a2);
    if (a1 != 0) {
        // 0x004f6f2c
        charge(ctx, 2);
        t1 = srl(a2, 2);
        v1 = sltiu(a2, 4);
        for (;;) {
            // 0x004f6f34
            charge(ctx, 8);
            t5 = subu(a0, a2);
            t0 = addu(a0, a3);
            t2 = addu(t5, a3);
            lw(t0, t0, 0);
            lw(t2, t2, 0);
            at = sltu(t0, t2);
            if (at != 0) {
                // 0x004f6f54
                charge(ctx, 1);
                for (;;) {
                    // 0x004f6f58
                    charge(ctx, 4);
                    t4 = t5;
                    t3 = addu(t5, a2);
                    t2 = a2;
                    if (v1 == 0) {
                        // 0x004f6f68
                        charge(ctx, 3);
                        at = sltiu(t1, 9);
                        if (at == 0) {
                            // 0x004f6f74
                            charge(ctx, 2);
                            if (v1 == 0) {
                                // 0x004f6f7c
                                charge(ctx, 1);
                                for (;;) {
                                    // 0x004f6f80
                                    charge(ctx, 37);
                                    lw(t7, t3, 0);
                                    lw(t6, t4, 0);
                                    t2 = addiu(t2, -32);
                                    at = sltiu(t2, 36);
                                    sw(t6, t3, 0);
                                    sw(t7, t4, 0);
                                    lw(t7, t3, 4);
                                    lw(t6, t4, 4);
                                    sw(t6, t3, 4);
                                    sw(t7, t4, 4);
                                    lw(t7, t3, 8);
                                    lw(t6, t4, 8);
                                    sw(t6, t3, 8);
                                    sw(t7, t4, 8);
                                    lw(t7, t3, 12);
                                    lw(t6, t4, 12);
                                    sw(t6, t3, 12);
                                    sw(t7, t4, 12);
                                    lw(t7, t3, 16);
                                    lw(t6, t4, 16);
                                    sw(t6, t3, 16);
                                    sw(t7, t4, 16);
                                    lw(t7, t3, 20);
                                    lw(t6, t4, 20);
                                    sw(t6, t3, 20);
                                    sw(t7, t4, 20);
                                    lw(t7, t3, 24);
                                    lw(t6, t4, 24);
                                    sw(t6, t3, 24);
                                    sw(t7, t4, 24);
                                    lw(t7, t3, 28);
                                    lw(t6, t4, 28);
                                    sw(t6, t3, 28);
                                    sw(t7, t4, 28);
                                    t3 = addiu(t3, 32);
                                    t4 = addiu(t4, 32);
                                    if (at != 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004f7014
                                charge(ctx, 1);
                            }
                        }
                        // 0x004f7018
                        charge(ctx, 3);
                        t6 = sltiu(t2, 4);
                        if (t6 == 0) {
                            // 0x004f7024
                            charge(ctx, 1);
                            for (;;) {
                                // 0x004f7028
                                charge(ctx, 9);
                                lw(t7, t3, 0);
                                lw(t6, t4, 0);
                                t2 = addiu(t2, -4);
                                at = sltiu(t2, 4);
                                sw(t6, t3, 0);
                                sw(t7, t4, 0);
                                t3 = addiu(t3, 4);
                                t4 = addiu(t4, 4);
                                if (at != 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004f704c
                            charge(ctx, 1);
                        }
                    }
                    // 0x004f7050
                    charge(ctx, 6);
                    t5 = subu(t5, a2);
                    t2 = addu(t5, a3);
                    lw(t2, t2, 0);
                    at = sltu(t0, t2);
                    if (at == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004f7068
            charge(ctx, 3);
            a1 = addiu(a1, -1);
            a0 = addu(a0, a2);
            if (a1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004f7074
        charge(ctx, 1);
    }
    // 0x004f7078 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_4F7080 [rxSortRecords] -- sorts $a1 records of stride $a2 by the int key at offset $a3 (keys in [$t0, $t1)): the radix pass for six or more, the smallest of the first five moved first, then the insertion pass
// 0x004F7080 sub_4F7080 -- 568 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F7080(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f7080
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    if (s1 != 0) {
        // 0x004f709c
        charge(ctx, 4);
        v1 = addiu(a3, 4);
        at = sltu(a2, v1);
        if (at != 0) {
            goto L_004f72a4;
        }
        // 0x004f70ac
        charge(ctx, 3);
        at = sltu(t0, t1);
        if (at == 0) {
            goto L_004f72a4;
        }
        // 0x004f70b8
        charge(ctx, 3);
        at = sltiu(s0, 6);
        if (at == 0) {
            // 0x004f70c4
            charge(ctx, 2);
            if (t1 == 0) {
                // 0x004f70fc
                charge(ctx, 1);
                a0 = si(-1);
            L_004f7100:
                charge(ctx, 1);
                v1 = addiu(s0, -1);
            } else {
                // 0x004f70cc
                charge(ctx, 3);
                v1 = srl(t1, 1);
                a0 = 0;
                if (v1 == 0) {
                    goto L_004f7100;
                }
                for (;;) {
                    // 0x004f70d8
                    charge(ctx, 7);
                    v1 = srl(v1, 1);
                    a0 = addiu(a0, 1);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004f70f4
                charge(ctx, 2);
                // 0x004f729c
                charge(ctx, 2);
                v1 = addiu(s0, -1);
                backedge(ctx);
            }
            // 0x004f7104
            charge(ctx, 6);
            mult(a1, v1, a2);
            v1 = 1;
            a1 = addu(s1, a1);
            t0 = sllv(v1, a0);
            a0 = s1;
            jal(ctx, 0x4F7114u, gen::fn_sub_4F6CE0_004f6ce0);
        }
        // 0x004f711c
        charge(ctx, 3);
        at = sltiu(s0, 2);
        if (at != 0) {
            goto L_004f72a4;
        }
        // 0x004f7128
        charge(ctx, 4);
        v1 = addiu(s0, -1);
        at = sltiu(v1, 4);
        t1 = 4;
        if (at != 0) {
            // 0x004f7138
            charge(ctx, 1);
            t1 = v1;
        }
        // 0x004f713c
        charge(ctx, 7);
        mult(v1, t1, a2);
        t0 = t1;
        v1 = addu(s1, v1);
        t1 = addiu(t1, -1);
        v1 = addu(v1, a3);
        lw(a1, v1, 0);
        mult1(a0, t1, a2);
        for (;;) {
            // 0x004f7158
            charge(ctx, 6);
            v1 = addu(s1, a0);
            v1 = addu(v1, a3);
            lw(v1, v1, 0);
            at = sltu(v1, a1);
            if (at != 0) {
                // 0x004f7170
                charge(ctx, 2);
                a1 = v1;
                t0 = t1;
            }
            // 0x004f7178
            charge(ctx, 4);
            v1 = t1;
            a0 = subu(a0, a2);
            t1 = addiu(t1, -1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004f7188
        charge(ctx, 2);
        if (t0 != 0) {
            // 0x004f7190
            charge(ctx, 6);
            a1 = s1;
            mult(a0, t0, a2);
            t1 = sltiu(a2, 4);
            v1 = a2;
            a0 = addu(s1, a0);
            if (t1 == 0) {
                // 0x004f71a8
                charge(ctx, 4);
                t0 = srl(a2, 2);
                at = sltiu(t0, 9);
                if (at == 0) {
                    // 0x004f71b8
                    charge(ctx, 2);
                    if (t1 == 0) {
                        for (;;) {
                            // 0x004f71c0
                            charge(ctx, 37);
                            lw(t1, a0, 0);
                            v1 = addiu(v1, -32);
                            lw(t0, a1, 0);
                            at = sltiu(v1, 36);
                            sw(t0, a0, 0);
                            sw(t1, a1, 0);
                            lw(t1, a0, 4);
                            lw(t0, a1, 4);
                            sw(t0, a0, 4);
                            sw(t1, a1, 4);
                            lw(t1, a0, 8);
                            lw(t0, a1, 8);
                            sw(t0, a0, 8);
                            sw(t1, a1, 8);
                            lw(t1, a0, 12);
                            lw(t0, a1, 12);
                            sw(t0, a0, 12);
                            sw(t1, a1, 12);
                            lw(t1, a0, 16);
                            lw(t0, a1, 16);
                            sw(t0, a0, 16);
                            sw(t1, a1, 16);
                            lw(t1, a0, 20);
                            lw(t0, a1, 20);
                            sw(t0, a0, 20);
                            sw(t1, a1, 20);
                            lw(t1, a0, 24);
                            lw(t0, a1, 24);
                            sw(t0, a0, 24);
                            sw(t1, a1, 24);
                            lw(t1, a0, 28);
                            lw(t0, a1, 28);
                            sw(t0, a0, 28);
                            sw(t1, a1, 28);
                            a0 = addiu(a0, 32);
                            a1 = addiu(a1, 32);
                            if (at != 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004f7254
                        charge(ctx, 1);
                    }
                }
                // 0x004f7258
                charge(ctx, 3);
                t0 = sltiu(v1, 4);
                if (t0 == 0) {
                    for (;;) {
                        // 0x004f7264
                        charge(ctx, 9);
                        lw(t1, a0, 0);
                        v1 = addiu(v1, -4);
                        lw(t0, a1, 0);
                        at = sltiu(v1, 4);
                        sw(t0, a0, 0);
                        sw(t1, a1, 0);
                        a0 = addiu(a0, 4);
                        a1 = addiu(a1, 4);
                        if (at != 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
        }
        // 0x004f7288
        charge(ctx, 5);
        a0 = s1;
        a1 = s0;
        jal(ctx, 0x4F728Cu, gen::fn_sub_4F6F20_004f6f20);
        ld(ra, sp, 0x20);
        // 0x004f72a8 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_004f72a4:
    charge(ctx, 1);
    ld(ra, sp, 0x20);
    // 0x004f72a8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4F72C0 -- an empty hook
// 0x004F72C0 sub_4F72C0 -- 8 bytes; leaf frame (no stack)
void sub_4F72C0(EEContext& ctx) {
    using namespace hg;
    // 0x004f72c0
    enter(ctx, 2);  // entry check point + this block's cycles
}


// sub_4F72D0 -- a hook that always succeeds (1)
// 0x004F72D0 sub_4F72D0 -- 8 bytes; leaf frame (no stack)
void sub_4F72D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x004f72d0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 1;
}


// sub_4F72E0 -- an empty hook
// 0x004F72E0 sub_4F72E0 -- 8 bytes; leaf frame (no stack)
void sub_4F72E0(EEContext& ctx) {
    using namespace hg;
    // 0x004f72e0
    enter(ctx, 2);  // entry check point + this block's cycles
}


// sub_4F72F0 -- a hook that always succeeds (1)
// 0x004F72F0 sub_4F72F0 -- 8 bytes; leaf frame (no stack)
void sub_4F72F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x004f72f0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 1;
}


}  // namespace p3fes::game
