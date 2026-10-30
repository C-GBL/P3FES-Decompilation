// Phase 5 slice render_im2d: RenderWare's Im2D submission path on the PS2 driver ("sky") -- the 18
// functions between the game's RwIm2DRender* calls and the DMA packet layer (docs/ANALYSIS/22_rendering.md
// sections 6 and 8.1). Every sprite, glyph, window, fade and HUD quad of the game passes through here.
//
// Data flow (one Im2D call):
//
//   game code --jalr device slot--> SkyIm2DRenderPrimitive(prim, verts, n)        SkyIm2DRenderPrimitive   (0x9600A0)
//                                   SkyIm2DRenderIndexedPrimitive(prim, ...)      SkyIm2DRenderIndexedPrimitive   (0x9600A4)
//                                   SkyIm2DRenderLine / SkyIm2DRenderTriangle      SkyIm2DRenderLine / SkyIm2DRenderTriangle
//      |  descriptor = bit 0 of the Im2D flag byte ? 0x7BCF80 : 0x7BCF70
//      v
//   builder (prim table 0x77F1B0 / 0x77F1D0, or addCopyVU1Line / addCopyVU1Triangle)
//      per packet of at most `limit` primitives ($gp-16872 lines, $gp-16868 triangles):
//        descriptor->open (open2DVU1Pkt, open2DVU1Pkt): _rwDMAOpenVIFPkt (recompiled, touches the DMAC),
//            the packet head (STCYCL/FLUSH, an UNPACK of 3 qw, the GIF tag with PRIM patched in, BASE/OFFSET),
//            and a DMA `call` of the VU1 program when it is not the resident one
//        per batch of at most 16 primitives: cnt tag + ITOP/STCYCL, STMASK + UNPACK V4-32 header,
//            the primitives' RwIm2DVertex records copied verbatim (4 qw each), the batch trailer (MSCALF first,
//            MSCNT after)
//        closeAndDispatchVU1Packet: the 64-byte packet tail
//
// The packet is written to the scratchpad at the write pointer $gp-17148; the DMA packet layer copies it to
// the DMA buffer by fromSPR when a half fills. A host fast path for UI quads would intercept the builders'
// (primitive class, vertex list) here and skip the VIF/VU1 work.
//
// Names: functions.json gives every one of the 18 as sub_*; the bracketed names are verified in
// symbols/deltas/rendering.sym (22_rendering.md section 6). The recompiled program's entry points
// (`fn_sub_<ADDR>_<addr8>`) are defined in src/render/render_im2d.cpp.
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"

#include <array>
#include <cstddef>
#include <cstring>
#include <initializer_list>

namespace p3fes::game {

namespace im2d {

// --- guest addresses (obs: instructions and ELF data) ------------------------------------------------
inline constexpr u32 kGp = 0x007D2CF0u;
inline constexpr u32 kDescriptorNoFog = 0x7BCF70u;  // {open2DVU1Pkt, program 038 (lines), program 039 (triangles), 0}
inline constexpr u32 kDescriptorFog = 0x7BCF80u;    // {open2DVU1Pkt, program 036, program 037, 0}
inline constexpr u32 kPrimTable = 0x77F1B0u;        // [rwPRIMTYPE 1..5] -> addCopyVU1Prim{LineList,PolyLine,TriList,TriStrip,TriFan}
inline constexpr u32 kIndexedPrimTable = 0x77F1D0u; // [1..5] -> addCopyVU1IndPrim*

// RW sky driver globals ($gp-relative).
inline constexpr u32 kSprWritePtr = kGp - 17148u;      // scratchpad packet write pointer (_rwDMAOpenVIFPkt moves it)
inline constexpr u32 kIm2DFlags = kGp - 16892u;        // byte; bit 0 selects the fog descriptor 0x7BCF80
inline constexpr u32 kResidentProgram = kGp - 16888u;  // VU1 program the packet stream last `call`ed
inline constexpr u32 kMaxLinesPerPacket = kGp - 16872u;
inline constexpr u32 kMaxTrisPerPacket = kGp - 16868u;
inline constexpr u32 kRenderFlags = kGp - 20272u;      // 64-bit; low 11 bits OR'ed into the GIF PRIM, bit 4 (TME) picks a head qw

// Packet templates (quadwords the VU1 dispatch init sub_4EC510 fills; contents as seen in the dorm and
// battle snapshots, obs).
inline constexpr u32 kTplNextBatchEnd = 0x965850u;   // FLUSHE, MSCNT: trailer of the 2nd.. batch of a packet
inline constexpr u32 kTplCnt1B = 0x965870u;          // DMA cnt tag, 1 qw
inline constexpr u32 kTplCnt1A = 0x965880u;          // DMA cnt tag, 1 qw
inline constexpr u32 kTplGifTag = 0x9658A0u;         // GIF tag of the VU1 kick; open2DVU1Pkt patches PRIM (word +4, bits 15..25)
inline constexpr u32 kTplFirstBatchEnd = 0x9658E0u;  // FLUSH, MSCALF 0: trailer of the 1st batch of a packet
inline constexpr u32 kTplFlush = 0x9658F0u;          // FLUSH
inline constexpr u32 kTplBaseOffset = 0x9659B0u;     // BASE 0, OFFSET 0x1E1
inline constexpr u32 kTplHeadNoTex = 0x9659E0u;      // head qw when render flag bit 4 is clear
inline constexpr u32 kTplHeadTex = 0x9659F0u;        // ... when it is set
inline constexpr u32 kTplUnpack3 = 0x965A00u;        // DMA cnt 3 + UNPACK V4-32 3 qw to VU1 0x3F9
inline constexpr u32 kTplUnpack3Data = 0x965A20u;    // first qw of that UNPACK (two floats)

// One Im2D vertex: 64 bytes, copied verbatim (4 quadwords) into the VU1 packet; the builders never look
// inside. Field meaning from the game's writers (H_Cursor_UpdateDrawTask 0x100230 stores x/y at +0/+4,
// z at +8, 1/camera->+0x80 at +24 and the colour bytes as floats at +32..+44: obs; the rest inf).
struct RwIm2DVertex {
    float x, y, z;     // +0   screen position
    float cam_z;       // +12
    float u, v;        // +16  texture coordinates
    float recip_z;     // +24  1 / camera z
    float pad0;        // +28
    float r, g, b, a;  // +32  colour, 0..255 as floats
    float extra[4];    // +48  not used by the 2D programs (inf)
};
static_assert(sizeof(RwIm2DVertex) == 64, "an Im2D vertex is four quadwords");

// The guest layout of a dispatch descriptor (0x7BCF70 / 0x7BCF80).
struct Im2DDescriptor {
    u32 open;          // open2DVU1Pkt 0x4EC100 in both
    u32 line_program;  // VU1 program image (038 / 036)
    u32 tri_program;   // (039 / 037)
    u32 zero;
};

// --- local helpers ---------------------------------------------------------------------------------
// Register fidelity: the kernel saves the whole register file in guest memory whenever a check point
// preempts the thread or the thread makes a switching syscall (KernelOptions::context_frames: GPRs 1..25,
// HI/LO, gp/sp/fp/ra at $sp - 0x280), and the prologues of callees and interrupt handlers spill registers
// into the stack below. So every register these functions write holds the original's value at each check
// point, at each call and at the return, and their prologues write the original's spills.

// One prologue spill: `sq reg, off(sp)` (quad) or `sd reg, off(sp)`; the epilogue reloads it (lq / ld).
struct Spill {
    unsigned reg;
    u32 off;
    bool quad;
};

// The original's stack frame: lowers $sp, writes the prologue spills; the destructor reloads them from the
// guest stack and restores $sp, as the epilogue does. link() sets $ra to a call's link value (`jal` /
// `jalr`); the reload of the $ra spill puts back the caller's (bits 64..127 of $ra are never written).
class Frame {
public:
    Frame(EEContext& ctx, u32 size, std::initializer_list<Spill> spills) noexcept : Frame(ctx, size, spills.begin(), spills.size()) {}
    Frame(EEContext& ctx, u32 size, const Spill* spills, std::size_t n) noexcept : ctx_(ctx), sf_(ctx, size) {
        for (std::size_t i = 0; i < n && i < spills_.size(); ++i) {
            const Spill& s = spills[i];
            spills_[count_++] = s;
            if (s.quad) {
                guest::store<u128>(ctx_, sf_.at(s.off), ctx_.gpr[s.reg]);
            } else {
                guest::store<u64>(ctx_, sf_.at(s.off), ee::core::gpr64(ctx_, s.reg));
            }
        }
    }
    ~Frame() {
        for (std::size_t i = 0; i < count_; ++i) {
            const Spill& s = spills_[i];
            if (s.quad) {
                ee::core::set_gpr128(ctx_, s.reg, guest::load<u128>(ctx_, sf_.at(s.off)));
            } else {
                ee::core::set_gpr64(ctx_, s.reg, guest::load<u64>(ctx_, sf_.at(s.off)));
            }
        }
    }
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;
    void link(u32 call_pc) noexcept { ee::core::set_gpr64(ctx_, GPR_RA, ee::core::link_value(call_pc)); }

private:
    EEContext& ctx_;
    guest::StackFrame sf_;
    std::array<Spill, 10> spills_{};
    std::size_t count_ = 0;
};

inline u128 make_q(u64 lo, u64 hi) noexcept {
    u128 q;
    q.u64[0] = lo;
    q.u64[1] = hi;
    return q;
}
// LQ / SQ: the address is forced to a quadword boundary.
inline u128 load_q(const EEContext& ctx, u32 va) noexcept { return guest::load<u128>(ctx, va & ~15u); }
inline void store_q(EEContext& ctx, u32 va, const u128& q) noexcept { guest::store<u128>(ctx, va & ~15u, q); }

inline RwIm2DVertex read_vertex(const EEContext& ctx, u32 va) noexcept {
    RwIm2DVertex v;
    for (u32 k = 0; k < 4; ++k) {
        const u128 q = load_q(ctx, va + 16u * k);
        std::memcpy(reinterpret_cast<u8*>(&v) + 16u * k, &q, 16);
    }
    return v;
}

// The scratchpad packet cursor: the write pointer $gp-17148 read once, advanced per quadword, written back
// by flush() (the compiled code re-reads and re-writes the global around every store; nothing else runs
// in between, so only the final value is observable).
class SprCursor {
public:
    explicit SprCursor(EEContext& ctx) noexcept : ctx_(ctx), p_(guest::load<u32>(ctx, kSprWritePtr)) {}
    void put(const u128& q) noexcept {
        store_q(ctx_, p_, q);
        p_ += 16u;
    }
    void put(const RwIm2DVertex& v) noexcept {
        for (u32 k = 0; k < 4; ++k) {
            u128 q;
            std::memcpy(&q, reinterpret_cast<const u8*>(&v) + 16u * k, 16);
            put(q);
        }
    }
    void flush() noexcept { guest::store<u32>(ctx_, kSprWritePtr, p_); }
    u32 at() const noexcept { return p_; }

private:
    EEContext& ctx_;
    u32 p_;
};

// The descriptor SkyIm2DRender* pick: bit 0 of the Im2D flag byte.
inline bool fog_selected(const EEContext& ctx) noexcept { return (guest::load<u8>(ctx, kIm2DFlags) & 1u) != 0; }

}  // namespace im2d

// --- the 18 functions (leaf first) -------------------------------------------------------------------

// [closeAndDispatchVU1Packet] Appends the 64-byte packet tail (cnt 1 + FLUSH, cnt 1 + FLUSH from the
// templates at 0x965880 / 0x965870 / 0x9658F0) at the scratchpad write pointer.
void closeAndDispatchVU1Packet(EEContext& ctx);

// [open2DVU1Pkt] The descriptors' open callback: reserves batch_qw * ceil(prim_count / 16) + 22 +
// prim_qw * prim_count quadwords (one fewer when `program` is resident) through _rwDMAOpenVIFPkt, writes
// the packet head (8 qw) with the GS PRIM (render flags | gs_prim) patched into the GIF tag template, and a
// DMA `call` of `program` when it is not resident (then it becomes resident). Returns 1.
u32 open2DVU1Pkt(EEContext& ctx, u32 batch_qw, u32 prim_qw, u32 prim_count, u32 gs_prim, u64 program);

// [addCopyVU1Line] / [addCopyVU1Triangle]: one primitive, one batch (none when the packet limit is 0).
// `open_arg` is handed to the open callback as its sixth argument ($t1; open2DVU1Pkt ignores it).
void addCopyVU1Line(EEContext& ctx, u32 desc, u64 open_arg, u32 va, u32 vb);
void addCopyVU1Triangle(EEContext& ctx, u32 desc, u64 open_arg, u32 va, u32 vb, u32 vc);

// The prim-array builders: (descriptor, open_arg, vertex array, vertex count).
void addCopyVU1PrimLineList(EEContext& ctx);  // [register ABI] [addCopyVU1PrimLineList]  n/2 lines
void addCopyVU1PrimPolyLine(EEContext& ctx);  // [register ABI] [addCopyVU1PrimPolyLine]  n-1 lines
void addCopyVU1PrimTriList(EEContext& ctx);  // [register ABI] [addCopyVU1PrimTriList]   n/3 triangles
void addCopyVU1PrimTriStrip(EEContext& ctx);  // [register ABI] [addCopyVU1PrimTriStrip]  n-2, alternating winding
void addCopyVU1PrimTriFan(EEContext& ctx);  // [register ABI] [addCopyVU1PrimTriFan]    n-2 around vertex 0

// The indexed builders: (descriptor, open_arg, vertex array, u16 index array, index count).
void addCopyVU1IndPrimLineList(EEContext& ctx);  // [register ABI] [addCopyVU1IndPrimLineList]
void addCopyVU1IndPrimPolyLine(EEContext& ctx);  // [register ABI] [addCopyVU1IndPrimPolyLine]
void addCopyVU1IndPrimTriList(EEContext& ctx);  // [register ABI] [addCopyVU1IndPrimTriList]
void addCopyVU1IndPrimTriStrip(EEContext& ctx);  // [register ABI] [addCopyVU1IndPrimTriStrip]
void addCopyVU1IndPrimTriFan(EEContext& ctx);  // [register ABI] [addCopyVU1IndPrimTriFan]

// The device slots (written by _rwSkyOverloadPipelines): each returns 1.
u32 SkyIm2DRenderLine(EEContext& ctx, u32 verts, u32 num_verts, u32 i0, u32 i1);           // [SkyIm2DRenderLine]
u32 SkyIm2DRenderTriangle(EEContext& ctx, u32 verts, u32 num_verts, u32 i0, u32 i1, u32 i2);   // [SkyIm2DRenderTriangle]
u32 SkyIm2DRenderPrimitive(EEContext& ctx, u64 prim, u64 verts, u64 num_verts);                 // [SkyIm2DRenderPrimitive]
u32 SkyIm2DRenderIndexedPrimitive(EEContext& ctx, u64 prim, u64 verts, u64 num_verts);                 // [SkyIm2DRenderIndexedPrimitive]
                                                                                     //   (indices in $a3, count in $t0, passed through)

}  // namespace p3fes::game
