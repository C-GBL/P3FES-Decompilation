// The IPU itself: registers, the input FIFO + bit-stream buffer, the output FIFO and the command engine (BCLR,
// IDEC, BDEC, VDEC, FDEC, SETIQ, SETVQ, CSC, PACK, SETTH), independent of the bus. Time is passed in as the
// virtual EE cycle of each access (HwBus::time().cycles); runtime/ipu/README.md documents the model.
//
// Data flow is synchronous and eager: whenever input arrives (CPU FIFO write, DMAC ch4), output space frees up
// (CPU FIFO read, DMAC ch3) or a command is written, the engine decodes as far as the buffered bits and the output
// FIFO allow, one atomic syntax element (<= 32 bits) at a time, so a stall never loses or half-consumes an element
// and the 10-qword input side can never deadlock a command. BUSY, however, follows virtual time: a command
// completes at max(issue + cost, the cycle its data flow finished) — see IpuCosts — and only then raises INTC 8.
#pragma once

#include "p3fes/ipu/ipu_regs.h"
#include "p3fes/ipu/mpeg2.h"

#include <cstddef>
#include <functional>
#include <string>

namespace p3fes {
class StateIo;  // p3fes/state_io.h (machine states)
}

namespace p3fes::ipu {

inline constexpr u64 kNever = ~u64{0};

// Minimum virtual cost in EE cycles from a command's issue to its completion, indexed by command code (inf: no
// hardware measurement; first estimates like the kernel's DMA 64 + 2/qword). A command whose data flow (input
// consumed, last output qword in the output FIFO) ends later completes at that later cycle. Codes 0xA-0xF are
// reserved (trapped, never started).
struct IpuCosts {
    u64 cycles[16] = {
        8,   // BCLR
        64,  // IDEC
        64,  // BDEC
        16,  // VDEC
        16,  // FDEC
        32,  // SETIQ
        16,  // SETVQ
        64,  // CSC
        64,  // PACK
        8,   // SETTH
        0, 0, 0, 0, 0, 0,
    };
};

struct IpuTrap {
    enum class Kind : u8 {
        ReservedCommand,   // IPU_CMD code 0xA-0xF
        CommandWhileBusy,  // IPU_CMD written while a command is in progress (ignored)
        InFifoOverflow,    // CPU write to the input FIFO with 10 qwords buffered (dropped)
        OutFifoUnderflow,  // CPU read of an empty output FIFO (reads 0)
        ReservedRegister,  // an access the register map does not define (width / offset / direction)
        Unsupported,       // a defined feature whose semantics are not modelled (IDEC SGN = 1)
    };
    Kind kind = Kind::ReservedRegister;
    u32 pa = 0;
    u64 value = 0;
    std::string message;
};

struct IpuStats {
    u64 commands[16] = {};
    u64 in_qwords = 0, out_qwords = 0;
    u64 input_stalls = 0, output_stalls = 0;
    u64 errors = 0;       // ECD events
    u64 macroblocks = 0;  // BDEC/IDEC macroblocks decoded, CSC/PACK macroblocks converted
    u64 interrupts = 0;
};

class IpuCore {
public:
    explicit IpuCore(IpuCosts costs = {});
    IpuCore(const IpuCore&) = delete;
    IpuCore& operator=(const IpuCore&) = delete;

    // Power-on state: FIFOs empty, BP 0, CTRL 0, idle, intra matrix = the MPEG default, non-intra all 16, VQ CLUT
    // and thresholds 0, DC predictors 128 (inf).
    void power_on();

    // ---- register interface (`now` = virtual EE cycle of the access) ----
    void write_cmd(u32 v, u64 now);
    void write_ctrl(u32 v, u64 now);
    u64 read_cmd(u64 now);   // DATA (last VDEC/FDEC result) | BUSY << 63
    u32 read_ctrl(u64 now);
    u32 read_bp(u64 now);
    u64 read_top(u64 now);   // the next 32 bit-stream bits | BUSY << 63 (still decoding, or < 32 bits buffered)
    // CPU FIFO access (sq to 0x10007010 / lq from 0x10007000); false on overflow / underflow (trapped).
    bool write_in_fifo(const u128& q, u64 now);
    bool read_out_fifo(u128& q, u64 now);

    // ---- DMA data paths ----
    // toIPU: accepts up to n qwords (fewer when the 10-qword input side stays full after decoding).
    std::size_t push_input(const u128* q, std::size_t n, u64 now);
    // fromIPU: produces up to n qwords (fewer when the output FIFO runs dry).
    std::size_t pop_output(u128* q, std::size_t n, u64 now);

    // Completes a command whose completion cycle has been reached (BUSY clears, INTC 8 via the completion
    // handler); returns the pending completion cycle, or kNever. Every entry point above calls it first.
    u64 update(u64 now);

    void set_completion_handler(std::function<void()> f) { on_complete_ = std::move(f); }
    void set_trap_handler(std::function<void(const IpuTrap&)> f) { on_trap_ = std::move(f); }

    // ---- inspection (tests, tools) ----
    bool busy() const noexcept { return busy_; }
    u32 command() const noexcept { return cmd_; }
    u64 completion_cycle() const noexcept { return work_done_ ? complete_at_ : kNever; }
    unsigned in_qwords() const noexcept { return in_count_; }
    unsigned out_qwords() const noexcept { return out_count_; }
    unsigned staged_output_qwords() const noexcept { return pend_qw_ - pend_pos_; }
    unsigned bit_pointer() const noexcept { return bp_; }
    unsigned buffered_bits() const noexcept;
    const u8* intra_matrix() const noexcept { return iq_intra_; }      // raster order
    const u8* nonintra_matrix() const noexcept { return iq_nonintra_; }
    const u16* vqclut() const noexcept { return vqclut_; }
    unsigned th0() const noexcept { return th0_; }
    unsigned th1() const noexcept { return th1_; }
    int dc_predictor(unsigned c) const noexcept { return dc_[c]; }
    const IpuStats& stats() const noexcept { return stats_; }

    // Machine state (p3fes/state_io.h): FIFOs, decoder position, tables, command timing, stats.
    void state(StateIo& io);

private:
    enum class St : u8 { Progress, Finished, NeedInput, NeedOutput, Error };
    enum class Phase : u8 {
        Idle,
        SkipFb,
        Fdec,
        Vdec,
        LoadBytes,   // SETIQ / SETVQ / CSC / PACK input
        Convert,     // CSC / PACK: convert the loaded macroblock and stage its output
        BdecCbp,
        IdecHeader,  // macroblock_type [+ dct_type] [+ quantiser_scale_code]
        Block,       // next coded block, or the end of the macroblock's blocks
        BlockDc,
        BlockFirst,
        BlockAc,
        MbOut,       // stage the finished macroblock (BDEC RAW16 / IDEC CSC output)
        IdecNext,    // start code or macroblock_address_increment
        IdecScan,    // byte-aligned search for 0x000001
    };

    // bit access at the step cursor
    u8 in_byte(unsigned b) const noexcept;
    unsigned avail() const noexcept;
    u32 window() const noexcept;
    bool take(unsigned n, u32& v) noexcept;
    void commit() noexcept;
    void push_in(const u128& q) noexcept;

    // output staging
    bool stage_free() const noexcept { return pend_pos_ == pend_qw_; }
    void stage(const u8* bytes, unsigned qwords) noexcept;
    void drain_stage() noexcept;

    void start(u32 v, u64 now);
    void run(u64 now);
    St step();
    St step_vdec();
    St step_load();
    St step_convert();
    St step_header();
    St step_block();
    St step_dc();
    St step_first();
    St step_ac();
    St step_mbout();
    St step_idec_next();
    St step_idec_scan();
    void end_block();
    void reset_fifos() noexcept;
    void trap(IpuTrap::Kind k, u32 pa, u64 value, std::string msg);

    unsigned code() const noexcept { return cmd_ >> 28; }
    bool mpeg1() const noexcept { return (lmode_ & kCtrlMp1) != 0; }

    IpuCosts costs_;
    std::function<void()> on_complete_;
    std::function<void(const IpuTrap&)> on_trap_;

    // input: ring of 16 qword slots holding up to kInCapacityQw qwords; bp_ = bits consumed of the head qword
    u8 in_[16][16] = {};
    unsigned in_head_ = 0, in_count_ = 0, bp_ = 0;
    unsigned cur_ = 0;  // step cursor: bit offset from the head qword's first bit
    // output FIFO and the staging buffer of the macroblock being emitted
    u8 out_[kOutFifoQw][16] = {};
    unsigned out_head_ = 0, out_count_ = 0;
    u8 pend_[mpeg2::kRgb32Bytes] = {};
    unsigned pend_qw_ = 0, pend_pos_ = 0;

    // registers
    u32 mode_ = 0;   // CTRL IDP/AS/IVF/QST/MP1/PCT
    u32 lmode_ = 0;  // mode latched at command issue
    bool ecd_ = false, scd_ = false;
    u32 cbp_ = 0;
    u32 data_ = 0;
    u8 iq_intra_[64] = {}, iq_nonintra_[64] = {};
    u16 vqclut_[16] = {};
    unsigned th0_ = 0, th1_ = 0;
    int dc_[3] = {128, 128, 128};

    // command
    u32 cmd_ = 0;
    bool busy_ = false, finished_ = false, work_done_ = false;
    u64 issue_at_ = 0, complete_at_ = kNever;
    Phase phase_ = Phase::Idle, after_fb_ = Phase::Idle;

    // decoder state
    unsigned load_total_ = 0, load_n_ = 0;
    u8 load_[mpeg2::kRgb32Bytes] = {};
    unsigned mb_left_ = 0;  // CSC/PACK macroblocks still to convert
    bool intra_ = false, field_dct_ = false;
    unsigned qsc_ = 0, cbp_mb_ = 0, blk_ = 0, k_ = 0;
    s32 qf_[64] = {};
    s16 blocks_[6][64] = {};

    IpuStats stats_;
};

} // namespace p3fes::ipu
