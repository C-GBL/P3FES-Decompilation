// The producer side of the threaded graphics pipeline (gs_pipeline.h): what VIF1, the GIF and the GS privileged
// registers hand over instead of executing it themselves while the pipeline is on.
//
// The EE thread keeps everything the guest can observe (VIF1 codes, registers, stalls and interrupts; the DMAC; GIF
// arbitration and PATH2/PATH3 tag walking; the GS privileged registers) and turns the rest into an ordered command
// stream: UNPACK / MPG writes into VU1 memory, VU1 runs (MSCAL/MSCALF/MSCNT), the GsCore calls of PATH2/PATH3, and
// the PATH1 queue flushes. Worker threads execute the stream in order on the same objects (VU1Interpreter, GsCore,
// a PATH1-only Gif), so every result is the synchronous model's; the EE waits only where it could observe one
// (docs/ANALYSIS/23 §7, gs_pipeline.h "Sync rules").
#pragma once

#include "p3fes/ee_types.h"

#include <cstddef>
#include <span>

namespace p3fes::gs {

// One UNPACK as VIF1 executes it: the VIFcode and the VIF registers it reads (ROW is the value *before* the unpack;
// mode 2 updates ROW, which the EE side keeps itself).
struct UnpackArgs {
    u32 code = 0, cycle = 0, mode = 0, mask = 0, tops = 0;
    u32 row[4] = {}, col[4] = {};
};

// Executes an UNPACK of `words` (n words) into VU1 data memory `mem` (16 KiB; null = registers only) and updates
// `row` (mode 2). Returns the number of vectors written (VifStats::unpack_qwords). vif1.cpp.
u32 vif_unpack(const UnpackArgs& a, const u32* words, std::size_t n, u8* mem, u32 row[4]);

// Why the EE waited (GsPipeline::Stats::waits / syncs, one counter each).
enum class SyncWhy : u8 {
    CsrRead,       // GS CSR read (SIGNAL / FINISH bits; the vblank handlers read it every vblank for FIELD)
    SiglblidRead,  // GS SIGLBLID read
    PrivWrite,     // CSR / IMR / SIGLBLID write
    CsrReset,      // CSR.RESET write (drain)
    GifEvent,      // a PATH2/PATH3 SIGNAL / FINISH / LABEL write (pending PATH1 events go first)
    ImrUnmasked,   // a VU1 run while IMR lets SIGNAL or FINISH interrupt: synchronous, run by run
    GifP1q,        // GIF_STAT with PATH1 packets possibly queued
    GifTagRead,    // GIF TAG0-3 / CNT read (drain)
    LocalRead,     // local -> host data (VIF1 FIFO / channel 1 read; drain)
    Host,          // the host: snapshot, machine state, compose, op hand-off outside a vblank, stop (drain)
    Count
};
const char* to_string(SyncWhy w) noexcept;

class GsPipe {
public:
    virtual ~GsPipe() = default;

    // ---- VIF1 -------------------------------------------------------------------------------------------------
    virtual void unpack(const UnpackArgs& a, const u32* words, std::size_t n) = 0;
    // MPG of `n` words at byte offset `byte_off` of micro memory; `src` = host pointer of the first payload word
    // (profiling attribution only).
    virtual void mpg(u32 byte_off, const u32* words, std::size_t n, const void* src) = 0;
    // Zero-copy forms: the command is queued with room for `nwords` payload words and the caller writes them there
    // (VIF1 memcpys payload runs straight from DMA data). The caller must write all of them before its next call to
    // the pipe, then call reserve_done() (which may hand the batch over); a payload that arrives across DMA
    // transfers, with other pipe calls in between, goes through unpack() / mpg() instead.
    virtual u32* unpack_reserve(const UnpackArgs& a, u32 nwords) = 0;
    virtual u32* mpg_reserve(u32 byte_off, u32 nwords, const void* src) = 0;
    virtual void reserve_done() = 0;
    // MSCAL (0x14) / MSCALF (0x15) / MSCNT (0x17) with the TOP/ITOP VIF1 just latched.
    virtual void vu_run(u32 op, u32 imm, u32 top, u32 itop, u32 code, u64 step_limit) = 0;
    virtual void vu_reset() = 0;  // CTC2 vi28 FBRST.RS1

    // ---- GIF (PATH2 / PATH3 GsCore calls, in the order Gif::feed makes them) ----------------------------------
    virtual void gs_tag(u32 path) = 0;
    virtual void gs_reg(u32 path, u32 reg, u64 value) = 0;
    virtual void gs_packed(u32 path, u32 desc, const u128& q) = 0;
    virtual void gs_image(u32 path, std::span<const u128> q) = 0;
    // The GIF reached a point where its PATH1 queue runs (owner idle after a PATH2/PATH3 packet).
    virtual void p1_flush() = 0;
    virtual void p1_clear() = 0;  // GIF_CTRL reset
    // A command counter (increases with every command; Gif uses it to order its last tag against PATH1's).
    virtual u64 seq() const noexcept = 0;

    // ---- sync points -----------------------------------------------------------------------------------------
    // The VU1 stage has executed every command issued so far; the SIGNAL / FINISH / LABEL writes its PATH1 packets
    // made visible are applied to the privileged registers, and VU1 traps are reported.
    virtual void sync_vu(SyncWhy why) = 0;
    // Every stage has executed every command issued so far and is idle: the caller may touch GsCore / VU1 itself.
    virtual void drain(SyncWhy why) = 0;
    // sync_vu(), then the number of PATH1 packets kicked while the GIF was busy and not yet flushed (GIF_STAT.P1Q).
    virtual std::size_t p1_queued() = 0;
    // drain(), then: true + the tag words when the last GIF tag read on any path was a PATH1 tag read after the
    // command numbered `after_seq` (GIF TAG0-3 / CNT registers).
    virtual bool p1_last_tag(u64 after_seq, u32 tag[4]) = 0;
};

} // namespace p3fes::gs
