// Phase 5 slice render_sky: the RenderWare sky driver's core and the 2D bridges (docs/ANALYSIS/22_rendering.md
// sections 2.4, 3.2, 5.3, 5.4; queue_rendering.txt "Full queue: RenderWare sky driver / PS2All / plugins"; the rows
// render_rw2 left for a dedicated pass, docs/INTEGRATION_LOG.md "render_rw2" -> "Not taken").
//
// What is here (functions.json names; [role] in the comments):
//   * The render-state funnel _rwSkySetRenderState 0x4D6B90 (RW's device render-state entry, ~665 call sites through
//     RwRenderStateSet's device pointer): RW state -> the GS register shadows ($gp-relative, below) and, where the
//     GS must see the change at once, a one-register A+D packet through _rwDMAOpenVIFPkt.
//   * The camera: SkyCameraBeginUpdate 0x4D84C0 (the draw environment packet FRAME/ZBUF/XYOFFSET/SCISSOR/TEST/
//     DTHE/COLCLAMP, the per-camera VU1 constants sub_4EEC20, the camera's frustum corners and planes; the first
//     call of a frame throttles in _rwDMAWaitQueue), the camera clear sub_4D8F40 [SkyCameraClear: a sprite strip per
//     32 pixels over the raster, colour and/or Z], and the deferred raster upload sub_4F1B30 [the pending
//     texture-cache raster's TEX0/TEX1 packet, run by SkyCameraBeginUpdate when $gp-16988 is set].
//   * Rasters / texture cache: the mip-map chain builder sub_4E3640 [GS sprite copies level n -> n+1, MIPTBP1/2],
//     the texture-cache upload sub_4F0C70 [PATH3 upload of a resident raster through sub_4D6250, then the CLUT /
//     TEX0 refresh when it is the cache's current raster], the cache placement sub_4F1780 [find / evict a slot,
//     TBP/CBP patched into the raster's TEX0 words].
//   * The PDS 2D bridges sub_46FDD0, RpPDS_G3_2DFont_PS2AllBridgeCallBack 0x4709E0, sub_471470 (one body compiled
//     three times; Rt2d fill / font / stroke pipes) and sub_4A2790 [the same skeleton for the Im3D pipes]: the
//     material bridge without the texture part (the raster comes from _rwSkySetRenderState state 1).
//
// Register discipline (wave-7 rule, docs/PHASE5_AGENT_BRIEF.md): a check point may preempt the thread and the kernel
// then saves the WHOLE register file in guest memory; every callee spills what it receives; game code reads
// registers a callee left behind. So these bodies are register-faithful at every check point, call and return: they
// run on a Cpu view of the guest registers (sky::Cpu below: one variable per GPR, the FPU / MMI / COP0 operations
// through the runtime's own instruction semantics), write the original prologue spills and keep the original's
// register allocation; the data flow is named in the comments and constants. Virtual time follows the recompiled
// bodies block by block (ADR-0013).
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"
#include "p3fes_recomp_rt.h"

namespace p3fes::game {

namespace sky {

// --- the sky driver's $gp-relative words (gp = 0x7D2CF0 in retail; the instructions name them gp-N) -------------
inline constexpr s32 kGpRenderFlags = -20272;    // u64: GIF PRIM bits (0x08 IIP gouraud, 0x10 TME, 0x20 FGE, 0x40 ABE,
                                                 // 0x100 FST) of every packet the bridges build
inline constexpr s32 kGpSrcBlend = -20264;       // state 10: 0..5 (row of the ALPHA table 0x77EF80)
inline constexpr s32 kGpDestBlend = -20260;      // state 11: 0..5 (column)
inline constexpr s32 kGpFogEnabled = -20232;     // the bridges' second clip-vector pair
inline constexpr s32 kGpTexCacheSlots = -20228;  // number of texture-cache slots
inline constexpr s32 kGpCamera = -19504;         // the kwln root camera (tests)
inline constexpr s32 kGpQueuePending = -17252;   // u8
inline constexpr s32 kGpFlipCount = -17248;      // u8: flips requested
inline constexpr s32 kGpFieldParity = -17244;    // u8
inline constexpr s32 kGpInterlace = -17240;      // u8: 1 = interlaced (field-parity XYOFFSET)
inline constexpr s32 kGpDmaBusyA = -17220;       // u8
inline constexpr s32 kGpGifTail = -17152;        // the GIF (PATH3) chain write pointer
inline constexpr s32 kGpSprWrite = -17148;       // scratchpad packet write pointer (_rwDMAOpenVIFPkt moves it)
inline constexpr s32 kGpMaxRaster = -17120;      // {max width, max height} of a camera raster
inline constexpr s32 kGpCamBegun = -17096;       // the first BeginUpdate of a frame has waited for the queue
inline constexpr s32 kGpZbuf1 = -17088;          // u64 shadow of GS ZBUF_1 (bit 32 ZMSK)
inline constexpr s32 kGpFrame1 = -17080;         // u64 shadow of GS FRAME_1
inline constexpr s32 kGpTest1 = -17072;          // u64 shadow of GS TEST_1 (ATE / ATST / AREF / ZTE / ZTST)
inline constexpr s32 kGpXyoffset = -17064;       // u64 shadow of GS XYOFFSET_1
inline constexpr s32 kGpFogCol = -17056;         // u64 shadow of GS FOGCOL
inline constexpr s32 kGpClamp1 = -17048;         // u64 shadow of GS CLAMP_1 (bits 0..3 WMS / WMT)
inline constexpr s32 kGpTex1 = -17040;           // u64 shadow of GS TEX1_1 (MMAG / MMIN bits 5..8)
inline constexpr s32 kGpAlpha1 = -17032;         // u64 shadow of GS ALPHA_1
inline constexpr s32 kGpFrameCount = -17016;     // frame counter (bit 0: which FRAME_1 value)
inline constexpr s32 kGpXyBaseX = -17008;        // u64: XYOFFSET of a non-frame raster (x, y)
inline constexpr s32 kGpXyBaseY = -17000;
inline constexpr s32 kGpBeginCount = -16984;     // camera BeginUpdates
inline constexpr s32 kGpRasterUpload = -16988;   // a texture-cache raster upload is owed (sub_4F1B30 at BeginUpdate)
inline constexpr s32 kGpRasterExt = -16968;      // plugin offset of the sky raster extension
inline constexpr s32 kGpCamFrustum = -16972;     // plugin offset of the camera's frustum block
inline constexpr s32 kGpCamProjection = -16964;  // state 20 (cull mode) value
inline constexpr s32 kGpVertexAlpha = -16956;    // state 12: vertex alpha enabled
inline constexpr s32 kGpRasterAlpha = -16952;    // the current raster has alpha
inline constexpr s32 kGpRaster = -16948;         // state 1: the current texture raster
inline constexpr s32 kGpFogTable = -16924;       // state 16 (fog type 1): the fog table address
inline constexpr s32 kGpCamFlags = -16892;       // u8: bit 0 fog, bit 5 cull
inline constexpr s32 kGpResidentProgram = -16888;
inline constexpr s32 kGpClipHi = -16884;
inline constexpr s32 kGpClipLo = -16880;
inline constexpr s32 kGpCullMode = -16876;

// Absolute driver globals.
inline constexpr u32 kTexCacheActive = 0x0077F200u;   // texture cache: non-zero when the cache is on
inline constexpr u32 kTexCacheHand = 0x0077F204u;     // eviction hand (-1 = none)
inline constexpr u32 kTexCacheHandEnd = 0x0077F208u;
inline constexpr u32 kTexCacheNext = 0x0077F210u;     // next free slot index
inline constexpr u32 kTexCacheSlots = 0x0077F214u;    // the slot array (12-byte slots {raster, gs address, size})
inline constexpr u32 kTexCacheBase = 0x0077F218u;     // GS base address of the cache
inline constexpr u32 kTexCacheSize = 0x0077F21Cu;
inline constexpr u32 kTexCacheCurrent = 0x0077F224u;  // the raster of the last cache access
inline constexpr u32 kTexCacheMode = 0x0077F228u;     // the mode of that access (0 / 1: which remembered slot)
inline constexpr u32 kTexCacheHit0 = 0x0077F22Cu;
inline constexpr u32 kTexCacheHit1 = 0x0077F230u;
inline constexpr u32 kAlphaTable = 0x0077EF80u;       // ALPHA_1 words [6 src][6 dest] (24-byte rows)
inline constexpr u32 kFrame1A = 0x009649F0u;       // FRAME_1 of the two frame buffers (by frame parity)
inline constexpr u32 kFrame1B = 0x00964B60u;
inline constexpr u32 kFogTable = 0x00965610u;         // state 16 fog type 1
inline constexpr u32 kCamConstants = 0x00965330u;     // SkyCameraBeginUpdate: 8 doublewords copied from camera +32
inline constexpr u32 kTplGifTag = 0x009658A0u;        // the bridges' GIF tag template
inline constexpr u32 kTplClipCull = 0x00965930u;
inline constexpr u32 kTplClipFog = 0x00965910u;
inline constexpr u32 kPdsCamera = 0x0095EF84u;        // the camera the PDS 2D pipes draw with (+20 projection: 1 perspective)

// --- R5900 integer results ------------------------------------------------------------------------------------
namespace core = ee::core;
constexpr u64 sx(u32 v) { return core::sext32(v); }
constexpr u64 si(s32 v) { return static_cast<u64>(static_cast<s64>(v)); }  // a negative immediate
constexpr u64 addu(u64 a, u64 b) { return core::add32(a, b); }
constexpr u64 addiu(u64 a, s32 i) { return core::add32i(a, i); }
constexpr u64 subu(u64 a, u64 b) { return core::sub32(a, b); }
constexpr u64 lui(u32 i) { return core::lui(i); }
constexpr u64 sll(u64 a, unsigned n) { return core::sll(a, n); }
constexpr u64 srl(u64 a, unsigned n) { return core::srl(a, n); }
constexpr u64 sra(u64 a, unsigned n) { return core::sra(a, n); }
constexpr u64 dsll(u64 a, unsigned n) { return core::dsll(a, n); }
constexpr u64 dsrl(u64 a, unsigned n) { return core::dsrl(a, n); }
constexpr u64 dsll32(u64 a, unsigned n) { return core::dsll32(a, n); }
constexpr u64 dsrl32(u64 a, unsigned n) { return core::dsrl32(a, n); }
constexpr u64 dsra32(u64 a, unsigned n) { return core::dsra32(a, n); }
constexpr u64 slt(u64 a, u64 b) { return core::slt(a, b); }
constexpr u64 sltu(u64 a, u64 b) { return core::sltu(a, b); }
constexpr u64 sltiu(u64 a, s32 i) { return core::sltiu(a, i); }
constexpr bool ltz(u64 a) { return static_cast<s64>(a) < 0; }
constexpr bool lez(u64 a) { return static_cast<s64>(a) <= 0; }
constexpr u32 w(u64 v) { return static_cast<u32>(v); }

// One GPR of the guest context (64-bit writes keep bits 64..127, as every non-MMI EE instruction).
struct Gpr {
    EEContext& c;
    const unsigned r;
    operator u64() const noexcept { return c.gpr[r].u64[0]; }
    u32 u() const noexcept { return c.gpr[r].u32[0]; }
    Gpr& operator=(u64 v) noexcept {
        core::set_gpr64(c, r, v);
        return *this;
    }
    Gpr& operator=(const Gpr& o) noexcept { return *this = static_cast<u64>(o); }
};

enum : unsigned { F0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22 };

// The guest machine as the bodies see it.
class Cpu {
public:
    explicit Cpu(EEContext& ctx) noexcept : c(ctx) {}

    EEContext& c;
    Gpr zero{c, 0}, at{c, 1}, v0{c, 2}, v1{c, 3}, a0{c, 4}, a1{c, 5}, a2{c, 6}, a3{c, 7};
    Gpr t0{c, 8}, t1{c, 9}, t2{c, 10}, t3{c, 11}, t4{c, 12}, t5{c, 13}, t6{c, 14}, t7{c, 15};
    Gpr s0{c, 16}, s1{c, 17}, s2{c, 18}, s3{c, 19}, s4{c, 20}, s5{c, 21}, s6{c, 22}, s7{c, 23};
    Gpr t8{c, 24}, t9{c, 25}, gp{c, 28}, sp{c, 29}, s8{c, 30}, ra{c, 31};

    // virtual time
    void enter(u64 n) { guest::enter(c, n); }  // not noexcept: a check point may raise a fatal event
    void charge(u64 n) noexcept { guest::charge(c, n); }
    void backedge() { guest::backedge(c); }

    // loads / stores (32-bit addresses; LQ / SQ force a quadword boundary)
    u64 lw(u64 a) const noexcept { return sx(guest::load<u32>(c, w(a))); }
    u64 lwu(u64 a) const noexcept { return guest::load<u32>(c, w(a)); }
    u64 lh(u64 a) const noexcept { return core::sext16(guest::load<u16>(c, w(a))); }
    u64 lhu(u64 a) const noexcept { return guest::load<u16>(c, w(a)); }
    u64 lbu(u64 a) const noexcept { return guest::load<u8>(c, w(a)); }
    u64 ld(u64 a) const noexcept { return guest::load<u64>(c, w(a)); }
    void lq(Gpr& d, u64 a) noexcept { core::set_gpr128(c, d.r, guest::load<u128>(c, w(a) & ~15u)); }
    void sw(u64 a, u64 v) noexcept { guest::store<u32>(c, w(a), w(v)); }
    void sb(u64 a, u64 v) noexcept { guest::store<u8>(c, w(a), static_cast<u8>(v)); }
    void sd(u64 a, u64 v) noexcept { guest::store<u64>(c, w(a), v); }
    void sq(u64 a, const Gpr& v) noexcept { guest::store<u128>(c, w(a) & ~15u, c.gpr[v.r]); }

    // FPU (the runtime's instruction semantics: EE singles, ACC, FCR31 flags)
    void lwc1(unsigned f, u64 a) noexcept { c.fpr[f] = guest::load<u32>(c, w(a)); }
    void swc1(unsigned f, u64 a) noexcept { guest::store<u32>(c, w(a), c.fpr[f]); }
    void mtc1(const Gpr& g, unsigned f) noexcept { rt::mtc1(c, g.r, f); }
    void mfc1(Gpr& g, unsigned f) noexcept { rt::mfc1(c, g.r, f); }
    void cvt_s_w(unsigned d, unsigned s) noexcept { rt::cvt_s_w(c, d, s); }
    void cvt_w_s(unsigned d, unsigned s) noexcept { rt::cvt_w_s(c, d, s); }
    void add_s(unsigned d, unsigned s, unsigned t) noexcept { rt::add_s(c, d, s, t); }
    void sub_s(unsigned d, unsigned s, unsigned t) noexcept { rt::sub_s(c, d, s, t); }
    void mul_s(unsigned d, unsigned s, unsigned t) noexcept { rt::mul_s(c, d, s, t); }
    void div_s(unsigned d, unsigned s, unsigned t) noexcept { rt::div_s(c, d, s, t); }
    void madd_s(unsigned d, unsigned s, unsigned t) noexcept { rt::madd_s(c, d, s, t); }
    void msub_s(unsigned d, unsigned s, unsigned t) noexcept { rt::msub_s(c, d, s, t); }
    void mula_s(unsigned s, unsigned t) noexcept { rt::mula_s(c, s, t); }
    void madda_s(unsigned s, unsigned t) noexcept { rt::madda_s(c, s, t); }

    // MMI, HI/LO, COP0
    void pcpyld(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::pcpyld(c, d.r, s.r, t.r); }
    void mult(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::mult(c, d.r, s.r, t.r); }
    void mfhi(Gpr& d) noexcept { rt::mfhi(c, d.r); }
    void di() noexcept { rt::di(c); }
    void ei() noexcept { rt::ei(c); }
    void sync_p() noexcept { rt::sync(c, 0x10); }
    void mfc0_status(Gpr& d) noexcept { rt::mfc0(c, d.r, 12); }

    // `jal fn` at pc ($ra = pc + 8; the delay slot, written before the call here, never touches $ra)
    void jal(u32 pc, rt::Fn fn) {
        rt::jal(c, pc);
        fn(c);
    }

    u32 gpw(s32 off) const noexcept { return gp.u() + static_cast<u32>(off); }

    // `DI` until Status.EIE reads clear (the a0-class interrupt mask around the driver's shared words): one block
    // of `cost` cycles per try, a check point on every retry. `mask` holds 0x10000, `scratch` receives Status.
    void di_wait(Gpr& scratch, const Gpr& mask, u64 cost) {
        for (;;) {
            charge(cost);
            di();
            sync_p();
            mfc0_status(scratch);
            scratch = scratch & mask;
            if (scratch == 0) return;
            backedge();
        }
    }

    // --- the bodies (sky.cpp) ---
    void set_render_state();     // _rwSkySetRenderState
    void raster_upload();        // sub_4F1B30

private:
    // _rwSkySetRenderState pieces
    void rs_epilogue();                              // reload $ra, then rs_tail
    void rs_tail();                                  // $s1 / $s0 and the frame
    void rs_ok();                                    // v0 = 1
    void rs_fail();                                  // v0 = 0
    void rs_ad_packet(u32 pc, s32 shadow, u32 reg);  // _rwDMAOpenVIFPkt(0x80000000, 2) + rs_ad_tail
    void rs_ad_tail(s32 shadow, u32 reg);            // one-register A+D packet {tag, (shadow, reg)}
    void rs_raster();                                // state 1
    void rs_dispatch(u64 state);                     // the handlers of states 2..30
};

}  // namespace sky

// --- the replaced functions (functions.json name; [proposed role]) ---------------------------------------------
// Each takes its arguments as the original receives them ($a0..$a2); the result is what it leaves in $v0.
u32 _rwSkySetRenderState(EEContext& ctx, u64 state, u64 value);  // RW render state -> GS shadows / A+D packet; 1 ok
void SkyCameraBeginUpdate(EEContext& ctx);  // [register ABI] the draw environment of `camera`; 1 ok
void sub_4D8F40(EEContext& ctx);  // [register ABI] [SkyCameraClear] flags 1 colour, 2 Z; 1 ok
void sub_4E3640(EEContext& ctx);  // [register ABI] [raster mip-map chain on the GS]
void sub_4F0C70(EEContext& ctx);  // [register ABI] [texture-cache PATH3 upload]; 1 queued
void sub_4F1B30(EEContext& ctx);                                    // [deferred cache-raster TEX0 / TEX1 packet]
void sub_4F1780(EEContext& ctx);  // [register ABI] [texture-cache placement]; 1 resident
void sub_46FDD0(EEContext& ctx);  // [register ABI] [PDS 2D bridge]
void RpPDS_G3_2DFont_PS2AllBridgeCallBack(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
void sub_471470(EEContext& ctx);  // [register ABI] [PDS 2D bridge]
void sub_4A2790(EEContext& ctx);  // [register ABI] [PS2All Im3D bridge]

}  // namespace p3fes::game
