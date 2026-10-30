// Phase 5 slice render_rw2: RenderWare sky-driver builders that reach the DMA packet layer (docs/ANALYSIS/22_rendering.md
// sections 2.4, 3.2, 5 and 7; queue_rendering.txt "Full queue: RenderWare sky driver / PS2All / plugins", class a/a0 rows
// with the callsB flag). Every function here writes VIF/GIF packet data into the scratchpad through the recompiled DMA
// packet layer (_rwDMAOpenVIFPkt 0x4D59D0, _rwDMAAddPkt 0x4D5000, _rwDMAForceBufferSwap 0x4D4DF0, _rwDMAHandler
// 0x4D4350, sub_4D5FE0, sub_4D5E90: DMAC registers, kept recompiled behind direct calls) or calls a function that does.
//
// Groups (each function's comment has its role):
//   * PS2All / PDS material bridges: the seven 60-byte skin wrappers (matrix-palette upload sub_46B8E0 when a skin
//     palette is pending, then the material bridge) and the three 12-byte pair-unpacking tail calls of the PDS 2D
//     bridges; the resEntry header builder at 0x4A26D0.
//   * DMA queue: the resource-reference flush sub_4D4280, _rwDMAWaitQueue, _rwDMAReqFlip (flip request packet).
//   * Camera / raster: SkyRasterShowRaster, the camera end update sub_4D8E80 (TEXFLUSH), the GS-register packets of
//     the raster functions (sub_4E4180 draw environment, sub_4E4420 sprite fill, sub_4E4560 textured sprite copy,
//     sub_4E46C0 environment restore), the raster clear sub_4E4800 and its whole-raster form sub_4E4E40.
//   * Render state: RpSkyRenderStateSet 0x4D7F60 (game-facing ALPHA / TEST / DIMX states).
//   * Texture upload / VU1 blocks: the image-upload header sub_4EF540, the VU1 record upload sub_46C330.
//   * PTank (particles): the render-callback setters sub_478440 / sub_479840, the 2D lock sub_477470, the constant
//     attribute fills sub_478100 / sub_477810 / sub_477C90 / sub_485EF0 / sub_485FF0, the texture state sub_4748C0,
//     the camera block sub_4733C0.
//
// Names: functions.json names now (`sub_*` mostly; one row of the RW band carries a stray C++ runtime symbol,
// `HandleUnexpected__...` at 0x4A26D0, kept as the IDA name). Proposed roles are in brackets in the comments.
// The recompiled program's entry points (`fn_<name>_<addr8>`) are defined in src/render/rw_builders.cpp.
//
// Register discipline (wave-7 rule, docs/PHASE5_AGENT_BRIEF.md): a check point may preempt the thread and the kernel
// then saves the WHOLE register file in guest memory; callees spill what they receive. So every function here leaves
// every register -- GPRs in 128 bits, HI/LO, FPRs -- as the original does at each check point, each call and the
// return, and writes the original prologue spills (rwb::Frame). The packet logic is written once, readably; the
// scratch values the original leaves in registers are set where it leaves them.
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"

#include <cstddef>

namespace p3fes::game {

namespace rwb {

// --- RenderWare sky-driver globals ($gp-relative; gp = 0x7D2CF0 in retail; 22_rendering.md section 5.1) -----------
inline constexpr s32 kGpPuRefSlots = -20292;       // u16: number of slots of the resource-reference ring
inline constexpr s32 kGpAlphaTestRef = -20256;     // RpSkyRenderStateSet state 5: the 1..7 value kept
inline constexpr s32 kGpPuRefWrite = -17268;       // u16 write index of the resource-reference ring (_rwDMAAddPURef)
inline constexpr s32 kGpPuRefRead = -17264;        // u16 read index
inline constexpr s32 kGpPuRefRing = -17260;        // ring of resource-entry pointers
inline constexpr s32 kGpQueuePending = -17252;     // u8: a flip / swap is pending
inline constexpr s32 kGpFlipCount = -17248;        // u8: flips requested
inline constexpr s32 kGpFieldParity = -17244;      // u8
inline constexpr s32 kGpInterlace = -17240;        // u8: 1 = interlaced (the field-parity wait in the raster packets)
inline constexpr s32 kGpQueueTail = -17236;        // end of the queue the handler drains
inline constexpr s32 kGpQueueHead = -17232;        // the handler's read pointer (entries {type, addr}, 8 bytes)
inline constexpr s32 kGpDmaBusyA = -17220;         // u8: a DMA chain is in flight
inline constexpr s32 kGpDmaBusyB = -17216;         // u8: the other DMA path is in flight
inline constexpr s32 kGpQueueWrite = -17192;       // queue write pointer
inline constexpr s32 kGpHalfIndex = -17168;        // u8: which half-buffer is being built
inline constexpr s32 kGpHalfStart = -17160;        // u32[2]: the two half-buffer starts
inline constexpr s32 kGpSprWritePtr = -17148;      // scratchpad packet write pointer
inline constexpr s32 kGpShowRasterPending = -17104;  // u64: SkyRasterShowRaster resets it
inline constexpr s32 kGpTexFlushPending = -17096;  // a TEXFLUSH is owed (camera end update / show raster clear it)
inline constexpr s32 kGpZbuf1 = -17088;            // u64 shadow of GS ZBUF_1
inline constexpr s32 kGpFrame1 = -17080;           // u64 shadow of GS FRAME_1 (this field's draw environment)
inline constexpr s32 kGpTest1 = -17072;            // u64 shadow of GS TEST_1
inline constexpr s32 kGpXyoffset = -17064;         // u64 shadow of GS XYOFFSET (bit 35 = the odd field's half line)
inline constexpr s32 kGpPrimShadow = -17040;       // u64 render flags shadow; the raster packets force bits 5..8
inline constexpr s32 kGpAlpha1 = -17032;           // u64 shadow of GS ALPHA_1
inline constexpr s32 kGpFrameCount = -17016;       // frame counter (SkyRasterShowRaster increments it)
inline constexpr s32 kGpNeedVsync = -16988;        // set when a deferred raster operation is queued
inline constexpr s32 kGpDimxMode = -16960;         // RpSkyRenderStateSet state 1: 0 / 0x55555555 / 1
inline constexpr s32 kGpCurrentTexture = -16948;   // last raster the bridges made resident (-1 / 0 = none)
inline constexpr s32 kGpDimxEnabled = -16936;      // DIMX state allowed
inline constexpr s32 kGpPrimShadowSaved = -16920;  // u64 copy of kGpPrimShadow taken by sub_4E4180
inline constexpr s32 kGpFrameRaster = -16896;      // the camera's frame-buffer raster
inline constexpr s32 kGpRenderStateF = -16864;     // RpSkyRenderStateSet state 4: the float value
inline constexpr s32 kGpRenderStateFSet = -16860;  // ... and its companion word (cleared)
inline constexpr s32 kGpPtankDataOffset = -17792;  // RpPTank: plugin data offset inside the atomic

// Absolute RW globals.
inline constexpr u32 kSkinPalettePending = 0x95DE38u;  // RpSkin: the matrix palette record of the current atomic (0 = none)
inline constexpr u32 kFlipPacketData = 0x964990u;      // _rwDMAReqFlip argument of SkyRasterShowRaster
inline constexpr u32 kDeferredOps = 0x964D50u;         // four words: deferred raster operations pending

// GIF tag of a one-register A+D packet (NLOOP 1, EOP, NREG 1) and the A+D descriptor (REGS = 0xE).
inline constexpr u64 kGifAdTag1 = 0x1000000000008001ull;
inline constexpr u64 kGifAd = 14;
// GS registers (A+D addresses).
inline constexpr u64 kGsXyoffset1 = 0x18, kGsTexflush = 0x3F, kGsAlpha1 = 0x42, kGsDimx = 0x44, kGsDthe = 0x45,
                     kGsTest1 = 0x47, kGsFrame1 = 0x4C, kGsZbuf1 = 0x4E;

inline u32 gpv(const EEContext& ctx, s32 off) noexcept { return ee::core::gpr32(ctx, GPR_GP) + static_cast<u32>(off); }
inline u32 lw(const EEContext& ctx, u32 va) noexcept { return guest::load<u32>(ctx, va); }
inline u64 ld(const EEContext& ctx, u32 va) noexcept { return guest::load<u64>(ctx, va); }
inline void sw(EEContext& ctx, u32 va, u32 v) noexcept { guest::store<u32>(ctx, va, v); }
inline void sd(EEContext& ctx, u32 va, u64 v) noexcept { guest::store<u64>(ctx, va, v); }

inline u128 make_q(u64 lo, u64 hi) noexcept {
    u128 q;
    q.u64[0] = lo;
    q.u64[1] = hi;
    return q;
}
// SQ: the address is forced to a quadword boundary.
inline void sq(EEContext& ctx, u32 va, const u128& q) noexcept { guest::store<u128>(ctx, va & ~15u, q); }
inline void sq(EEContext& ctx, u32 va, u64 lo, u64 hi) noexcept { sq(ctx, va, make_q(lo, hi)); }

// Register writes as the original performs them: d() a 64-bit result (bits 64..127 kept, as every non-MMI
// instruction), w() a 32-bit result sign-extended, q() a 128-bit one (LQ, PCPYLD).
struct Regs {
    EEContext& c;
    u64 get(unsigned r) const noexcept { return ee::core::gpr64(c, r); }
    u32 get32(unsigned r) const noexcept { return ee::core::gpr32(c, r); }
    void d(unsigned r, u64 v) noexcept { ee::core::set_gpr64(c, r, v); }
    void w(unsigned r, u32 v) noexcept { ee::core::set_gpr64(c, r, ee::core::sext32(v)); }
    void q(unsigned r, u64 lo, u64 hi) noexcept { ee::core::set_gpr128(c, r, make_q(lo, hi)); }
    void q(unsigned r, const u128& v) noexcept { ee::core::set_gpr128(c, r, v); }
    u128 get_q(unsigned r) const noexcept { return c.gpr[r]; }
};

// The original's stack frame: `addiu sp, sp, -size` on construction, the prologue spills through sd()/sq()/swc1()
// (written to the guest stack), and on destruction the epilogue's reloads (ld / lq / lwc1) and `addiu sp, sp, size`.
class Frame {
public:
    Frame(EEContext& ctx, u32 size) noexcept : ctx_(ctx), size_(size) {
        ee::core::set_gpr64(ctx_, GPR_SP, ee::core::sext32(ee::core::gpr32(ctx_, GPR_SP) - size));
    }
    ~Frame() {
        for (unsigned i = 0; i < n_; ++i) {
            const Slot& s = slot_[i];
            switch (s.kind) {
            case Kind::D: ee::core::set_gpr64(ctx_, s.r, guest::load<u64>(ctx_, at(s.off))); break;
            case Kind::Q: ee::core::set_gpr128(ctx_, s.r, guest::load<u128>(ctx_, at(s.off) & ~15u)); break;
            case Kind::F: ctx_.fpr[s.r] = guest::load<u32>(ctx_, at(s.off)); break;
            }
        }
        ee::core::set_gpr64(ctx_, GPR_SP, ee::core::sext32(ee::core::gpr32(ctx_, GPR_SP) + size_));
    }
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;

    void sd(unsigned r, u32 off) noexcept { guest::store<u64>(ctx_, at(off), ee::core::gpr64(ctx_, r)); add(r, off, Kind::D); }
    void sq(unsigned r, u32 off) noexcept { guest::store<u128>(ctx_, at(off) & ~15u, ctx_.gpr[r]); add(r, off, Kind::Q); }
    void swc1(unsigned f, u32 off) noexcept { guest::store<u32>(ctx_, at(off), ctx_.fpr[f]); add(f, off, Kind::F); }
    u32 sp() const noexcept { return ee::core::gpr32(ctx_, GPR_SP); }
    u32 at(u32 off) const noexcept { return sp() + off; }

private:
    enum class Kind : u8 { D, Q, F };
    void add(unsigned r, u32 off, Kind k) noexcept { slot_[n_++] = {r, off, k}; }
    struct Slot {
        unsigned r;
        u32 off;
        Kind kind;
    };
    EEContext& ctx_;
    u32 size_;
    Slot slot_[12] = {};
    unsigned n_ = 0;
};

// `jal fn` at `pc` ($ra = pc + 8; the delay slot is the caller's last register write before this call).
inline void jal(EEContext& ctx, u32 pc, void (*fn)(EEContext&)) {
    ee::core::set_gpr64(ctx, GPR_RA, ee::core::link_value(pc));
    fn(ctx);
}

}  // namespace rwb

// --- the replaced functions (functions.json name; [proposed role]) --------------------------------------------------
// Arguments the originals only use as load/store bases are 32-bit values; those copied whole into s-registers or
// compared as whole registers are the 64-bit register values. Functions taking only EEContext& read their arguments
// from the registers as the originals do.

// PS2All / PDS bridges.
void sub_46FB70(EEContext& ctx);  // [register ABI] [PDS 2D bridge entry]: sub_46F400(pair[0], pair[1]) as a tail call
void sub_470780(EEContext& ctx);  // [register ABI] [PDS 2D bridge entry]: sub_470200(pair[0], pair[1]) as a tail call
void sub_471210(EEContext& ctx);  // [register ABI] [PDS 2D bridge entry]: sub_470E10(pair[0], pair[1]) as a tail call
// [PDS skin bridges] when a skin matrix palette is pending (kSkinPalettePending): its upload sub_46B8E0(pipe), then
// the material bridge(pipe). The seven differ only in the bridge.
void sub_472130(EEContext& ctx);  // [register ABI] -> RpMeshPS2AllBridgeCallBack 0x4A0E00
void sub_472170(EEContext& ctx);  // [register ABI] -> matfxBridgeBumpMap
void sub_4721B0(EEContext& ctx);  // [register ABI] -> matfxBridgeEnvMap
void sub_4721F0(EEContext& ctx);  // [register ABI] -> matfxBridgeBumpEnvMap
void sub_472230(EEContext& ctx);  // [register ABI] -> matfxBridgeDual
void sub_473340(EEContext& ctx);  // [register ABI] -> matfxBridgeUvTransform
void sub_473380(EEContext& ctx);  // [register ABI] -> matfxBridgeDualUvTransform
// [PS2All resEntry header] opens a 128-qw VIF packet, allocates the entry's DMA block (sub_4D5FE0(size + 24, 0)) into
// *out and fills its header {0, 0, size, owner->+8, 0, tag}; returns the entry.
u32 HandleUnexpected__FP12ThrowContextP13ExceptionInfoP16ex_specificationPc(EEContext& ctx, u64 owner, u64 out, u64 size,
                                                                           u64 tag);

// DMA queue.
void sub_4D4280(EEContext& ctx);       // [_rwDMAFlushPURefs] the resource-reference ring -> type-0x42 queue fences
void _rwDMAWaitQueue(EEContext& ctx);  // swap halves once the DMA side is idle (kicks the handler when it is not)
void _rwDMAReqFlip(EEContext& ctx, u64 flip_data, u64 flags);  // flip request: 24-qw packet, fence 64/65, handler kick

// Camera / raster.
u32 SkyRasterShowRaster(EEContext& ctx);  // [SkyRasterShowRaster] pending clear, flip request, deferred-op flag; 1
void sub_4D8E80(EEContext& ctx);  // [register ABI] [SkyCameraEndUpdate] TEXFLUSH packet for camera textures; 1
void sub_4E4E40(EEContext& ctx);             // [clear the whole frame raster] sub_4E4800(0, {0, 0, w, h})
void sub_4E4180(EEContext& ctx, u64 mode);   // [raster draw environment] FRAME/ZBUF/TEST/DTHE/ALPHA/XYOFFSET
void sub_4E4420(EEContext& ctx);  // [raster fill rectangle] PRIM sprite / XYZ2 / RGBAQ from $a0..$t3 + 2 stack words
void sub_4E4560(EEContext& ctx);  // [raster copy sprite] textured sprite UV / XYZ2 pairs from $a0..$t3 + a stack word
void sub_4E46C0(EEContext& ctx);  // [restore draw environment] FRAME/ZBUF/ALPHA/XYOFFSET from the shadows
u32 sub_4E4800(EEContext& ctx, u32 rect, u64 colour);  // [raster clear] GS sprite fill or CPU fill of a locked raster

// Render state.
void RpSkyRenderStateSet(EEContext& ctx);  // [register ABI] 0x4D7F60: states 1 DIMX, 2 ALPHA, 3 TEST, 4, 5

// PTank (particles).
void sub_478440(EEContext& ctx);  // [register ABI] [PTank 2D render callbacks] install, run sub_4861B0
void sub_479840(EEContext& ctx);  // [register ABI] [PTank 3D render callbacks] install, run sub_4861B0
void sub_485EF0(EEContext& ctx);  // [register ABI] [PTank constant UV (2 pairs)] per particle
void sub_485FF0(EEContext& ctx);  // [register ABI] [PTank constant UV (4 pairs)] per particle
void sub_4748C0(EEContext& ctx);  // [register ABI] [PTank texture] raster resident + TEX0/TEX1, ATE
void sub_4733C0(EEContext& ctx);  // [register ABI] [PTank camera block] 4-qw UNPACK: two vectors + LTM row
void sub_477470(EEContext& ctx);  // [register ABI] [PTank 2D lock] component pointers / strides
void sub_478100(EEContext& ctx);  // [register ABI] [PTank constant size] the pair at tank+112
void sub_477810(EEContext& ctx);  // [register ABI] [PTank constant colour] the bytes at tank+124
void sub_477C90(EEContext& ctx);  // [register ABI] [PTank constant UV rectangle] tank+144..159

// Texture upload / VU1 blocks.
void sub_4EF540(EEContext& ctx);               // [image upload header] BITBLTBUF / TRXREG GIF packet from $a0..$t2
void sub_46C330(EEContext& ctx);  // [register ABI] [VU1 record upload] n 80-byte records to VU1 0x2FF; returns src

}  // namespace p3fes::game
