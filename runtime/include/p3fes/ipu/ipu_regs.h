// IPU (Image Processing Unit) register map, field layout and command codes.
//
// Sources (tags as in runtime/ipu/README.md): register addresses and widths from ps2sdk
// `common/include/ee_regs.h` (IPU_CMD/IPU_TOP 64-bit, IPU_CTRL/IPU_BP 32-bit, FIFOs at 0x10007000/10) [obs];
// field positions from the game's own libmpeg/libipu (SDK 3.1, recompiled), read in recomp/generated/
// (`sceIpuInit 0x502B08`, `_sceMpegWaitIpuIdle 0x4FD370`, `_decMB0 0x4FCCA0`, `_pictureCodingExtension
// 0x4FF5C0`, `sceIpuStopDMA 0x5027F0`/`sceIpuRestartDMA 0x5028D8`) and cross-checked against ps2sdk's AFL
// `ee/mpeg/src/libmpeg_core.c` (an independent IPU client) [obs]. INTC cause 8 = IPU: ps2sdk
// `ee/kernel/include/kernel.h` `INTC_IPU` [obs].
#pragma once

#include "p3fes/ee_types.h"

namespace p3fes::ipu {

// ---- physical addresses ------------------------------------------------------------------------------
inline constexpr u32 kRegBase = 0x10002000u;   // IPU_CMD .. IPU_TOP (4 x 16 bytes)
inline constexpr u32 kRegEnd = 0x10002040u;
inline constexpr u32 kIpuCmd = 0x10002000u;    // write: command; read (64): DATA[31:0] | BUSY bit 63
inline constexpr u32 kIpuCtrl = 0x10002010u;   // 32-bit
inline constexpr u32 kIpuBp = 0x10002020u;     // 32-bit, read-only
inline constexpr u32 kIpuTop = 0x10002030u;    // read (64): BSTOP[31:0] | BUSY bit 63
inline constexpr u32 kFifoBase = 0x10007000u;
inline constexpr u32 kFifoEnd = 0x10007020u;
inline constexpr u32 kOutFifo = 0x10007000u;   // 128-bit read (fromIPU side)
inline constexpr u32 kInFifo = 0x10007010u;    // 128-bit write (toIPU side)

inline constexpr unsigned kIntcIpu = 8;        // INTC cause (ps2sdk INTC_IPU)
inline constexpr unsigned kDmaFromIpu = 3;     // DMAC channel 3: IPU -> RAM (normal mode only)
inline constexpr unsigned kDmaToIpu = 4;       // DMAC channel 4: RAM -> IPU (normal / source chain)

// FIFO depths in quadwords. The input side is the 8-qword FIFO plus the 2-qword bit-stream decoder
// buffer that IPU_BP.FP counts (IFC 0-8, FP 0-2); the output FIFO is 8 qwords (IPU_CTRL.OFC).
inline constexpr unsigned kInFifoQw = 8;
inline constexpr unsigned kFpQw = 2;
inline constexpr unsigned kInCapacityQw = kInFifoQw + kFpQw;
inline constexpr unsigned kOutFifoQw = 8;

// ---- IPU_CTRL ------------------------------------------------------------------------------------------
inline constexpr u32 kCtrlIfcMask = 0x0000000Fu;  // [3:0]  input FIFO counter (qwords, excludes FP)
inline constexpr u32 kCtrlOfcShift = 4;           // [7:4]  output FIFO counter
inline constexpr u32 kCtrlCbpShift = 8;           // [13:8] coded block pattern of the last BDEC/IDEC MB
inline constexpr u32 kCtrlEcd = 1u << 14;         // error code detected
inline constexpr u32 kCtrlScd = 1u << 15;         // start code detected
inline constexpr u32 kCtrlIdpShift = 16;          // [17:16] intra DC precision
inline constexpr u32 kCtrlAs = 1u << 20;          // alternate scan
inline constexpr u32 kCtrlIvf = 1u << 21;         // intra VLC format (table B.15)
inline constexpr u32 kCtrlQst = 1u << 22;         // q_scale_type (non-linear)
inline constexpr u32 kCtrlMp1 = 1u << 23;         // MPEG-1 bit stream
inline constexpr u32 kCtrlPctShift = 24;          // [26:24] picture coding type (1 I, 2 P, 3 B, 4 D)
inline constexpr u32 kCtrlRst = 1u << 30;         // write 1: reset
inline constexpr u32 kCtrlBusy = 1u << 31;        // read: command in progress
// Bits a CTRL write stores (IDP, AS, IVF, QST, MP1, PCT). The game writes CTRL read-modify-write, so the
// status bits it reads back (IFC/OFC/CBP/ECD/SCD/BUSY) must be ignored on write.
inline constexpr u32 kCtrlModeMask = 0x00030000u | kCtrlAs | kCtrlIvf | kCtrlQst | kCtrlMp1 | 0x07000000u;

// ---- IPU_BP -----------------------------------------------------------------------------------------------
inline constexpr u32 kBpMask = 0x7Fu;             // [6:0]  bit pointer inside the first buffered qword
inline constexpr u32 kBpIfcShift = 8;             // [11:8] IFC
inline constexpr u32 kBpFpShift = 16;             // [17:16] FP

// ---- commands (IPU_CMD bits 31:28) -------------------------------------------------------------------------
enum class Cmd : u8 {
    Bclr = 0,   // [6:0] BP
    Idec = 1,   // [5:0] FB, [20:16] QSC, 24 DTD, 25 SGN, 26 DTE, 27 OFM
    Bdec = 2,   // [5:0] FB, [20:16] QSC, 25 DT, 26 DCR, 27 MBI
    Vdec = 3,   // [5:0] FB, [27:26] TBL (0 MBAI, 1 MB type, 2 motion code, 3 DMV)
    Fdec = 4,   // [5:0] FB
    Setiq = 5,  // [5:0] FB, 27 IQM (0 intra, 1 non-intra)
    Setvq = 6,
    Csc = 7,    // [10:0] MBC, 26 DTE, 27 OFM (0 RGB32, 1 RGB16)
    Pack = 8,   // [10:0] MBC, 26 DTE, 27 OFM (0 INDX4, 1 RGB16)
    Setth = 9,  // [8:0] TH0, [24:16] TH1
};
inline constexpr const char* kCmdName[16] = {"BCLR", "IDEC", "BDEC", "VDEC", "FDEC", "SETIQ", "SETVQ", "CSC",
                                             "PACK", "SETTH", "CMD_A", "CMD_B", "CMD_C", "CMD_D", "CMD_E", "CMD_F"};

constexpr unsigned cmd_code(u32 v) { return v >> 28; }
constexpr unsigned cmd_fb(u32 v) { return v & 0x3Fu; }
constexpr unsigned cmd_qsc(u32 v) { return (v >> 16) & 0x1Fu; }
constexpr unsigned cmd_mbc(u32 v) { return v & 0x7FFu; }
constexpr bool cmd_bit(u32 v, unsigned b) { return ((v >> b) & 1u) != 0; }

// Command words the game's libmpeg/libipu issue (recomp/generated, see runtime/ipu/README.md "Game usage").
inline constexpr u32 kCmdVdecMbai = 0x30000000u;
inline constexpr u32 kCmdVdecMbType = 0x34000000u;
inline constexpr u32 kCmdVdecMotion = 0x38000000u;
inline constexpr u32 kCmdVdecDmv = 0x3C000000u;
inline constexpr u32 kCmdFdec = 0x40000000u;
inline constexpr u32 kCmdSetiqIntra = 0x50000000u;
inline constexpr u32 kCmdSetiqNonIntra = 0x58000000u;
inline constexpr u32 kCmdSetvq = 0x60000000u;
inline constexpr u32 kCmdCsc = 0x70000000u;
inline constexpr u32 kCmdSetth = 0x90000000u;

} // namespace p3fes::ipu
