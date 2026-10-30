// CRI_ADXI.IRX ("CRI ADX Driver Ver.9.44", DTX 1.10, SJX 1.09, SJRMT 1.03, IOPRNA 1.32, PSM 1.10,
// RCV 1.12; Feb 28 2005) modelled at the protocol the EE observes. Evidence: the IRX's instructions
// (IDA, module offsets) and the EE clients in SLUS_216.21 (VAs); docs/ANALYSIS/16_iop_audio_modules.md.
//
// What runs here, all on virtual time (ADR-0013):
//   * the DTX RPC server 0x90000200: fn 2 create (IRX 0x9D0), fn 3 destroy (0xAE8), fn 1024+u =
//     urpc u (0x720 -> table 0xE090/0xDF90); every reply is the request buffer modified in place;
//   * the per-vblank-end server pass (IRX 0x88 loop: WaitVblankEnd -> 0x1234): RNA discard (0x1140),
//     then every DTX exchange (0xE14 -> 0xB24): an EE block is accepted when the counter word at
//     wklen-4 of the IOP buffer exceeds the IOP's count; the receive callback runs, then the send
//     callback, the IOP count becomes EE count + 1, is stored at wklen-4 and the whole wklen-byte
//     buffer goes back to the EE buffer by sceSifSetDma (0xC68) -- here a SIF0 data write;
//   * SJX (DTX id 0): EE data chunks (IOP addresses) enter the IOP SJUNI's data line (0x8F60);
//     consumed chunks go back to the EE (0x900C);
//   * IOPRNA (DTX id 1): parameter commands (0xEA0) -> the PSM model; the reply carries 0 entries
//     (0x10F8);
//   * the PSM mixer: 512-frame passes at 48 kHz while an output is started (PSMOUT 0x5864/0x5A68,
//     4 KiB AutoDMA buffer), each playing RNA consuming sfreq/48000 input samples per frame per channel
//     from its SJUNI data line in IOP RAM, mixed with the PSM volume law (0x27E4, tables 0xD310/0xD38C)
//     into the host AudioSink; consumed bytes go to the SJUNI free line.
#pragma once

#include <array>
#include <deque>
#include <vector>

#include "iop_core.h"

namespace p3fes::hle::sif::detail {

struct SjChunk {
    u32 ptr = 0;
    u32 len = 0;
};

// CRI SJUNI (the same library as the EE copy: sjuni_PutChunk 0x5636D0, sjuni_GetChunk 0x563530,
// sjuni_GetNumData 0x563418; IOP object layout matches, PCSX2 title state): four lines of chunk
// descriptors over a chain pool of pool_size/16 nodes. Mode 1 merges a put that continues the tail
// and splits a get larger than `max`; other modes return nothing for an oversized get.
class SjUni {
public:
    void create(u32 mode, u32 pool, u32 pool_size);
    void destroy() { *this = SjUni{}; }
    bool used() const { return used_; }
    bool put(u32 line, SjChunk c);  // false: no free chain node (CRI error -3)
    SjChunk get(u32 line, u32 max);
    bool unget(u32 line, SjChunk c);
    u32 num_data(u32 line) const;
    void reset();
    const std::deque<SjChunk>& line(u32 l) const { return lines_[l & 3]; }
    u32 nodes_in_use() const;
    u32 node_capacity() const { return nodes_; }
    void state(StateIo& io);

private:
    bool used_ = false;
    u32 mode_ = 0;
    u32 pool_ = 0;
    u32 nodes_ = 0;
    std::array<std::deque<SjChunk>, 4> lines_{};
};

class AdxiServer final : public RpcServer {
public:
    static constexpr u32 kDtxMax = 16, kRnaMax = 16, kSjxMax = 32, kSjMax = 64;
    static constexpr u32 kPassFrames = 512;  // half of PSMOUT's 4 KiB L/R AutoDMA buffer (IRX 0x5918)

    AdxiServer();
    std::string_view name() const override { return "cri_adxi"; }
    bool call(IopCore& core, const RpcRequest& req, RpcReply& reply, u32 ticket) override;
    void tick(IopCore& core, u64 now, const Timebase& tb) override;
    u64 next_deadline() const override { return tick_due_; }
    void reboot() override;
    void state(StateIo& io, IopCore& core) override;

    void set_output(audio::AudioSink* mix, audio::StreamTap* tap) {
        mix_ = mix;
        tap_ = tap;
    }
    AdxiStats stats() const;

private:
    enum class Cb : u8 { None, Sjx, Rna };
    struct Dtx {
        bool used = false;
        u8 stat = 0;  // 1 = waiting for the EE's block (IRX obj+1)
        u8 enable = 0;
        u32 cnt = 0;
        u32 ee_buf = 0, iop_buf = 0, wklen = 0;
        Cb rcv = Cb::None, snd = Cb::None;
    };
    struct Sjx {
        bool used = false;
        u16 id = 0;
        u32 sj = 0;      // IOP SJUNI handle
        u32 ee_sj = 0;   // the EE's local SJUNI (echoed only)
        u32 line = 0;    // line returned to the EE (0 = free when created with mode 1)
        u32 ee_sjx = 0;  // the EE's SJX object (written into every returned entry)
    };
    struct Resampler {
        u32 phase = 0;   // in 1/48000 input-sample units
        s16 prev = 0, cur = 0;
    };
    struct Rna {
        bool used = false;
        s8 discard = 0;            // IRX rna+1 (command 8)
        u8 b2 = 0, b3 = 0;         // rna+2 (command 10), rna+3 (command 12)
        u32 maxnch = 0, nch = 0;
        std::array<u32, 2> sj{};
        u32 vol_all = 0;           // rna+0x18 (command 5)
        // PSM (IRX 0x2350 object)
        bool playing = false;
        u32 psm_nch = 0;           // psm+3
        u32 sfreq = 48000;         // psm+0x34
        std::array<s32, 2> vol{255, 255};  // psm+0x38
        std::array<s32, 2> pan{0, 0};      // psm+0x40
        s32 mpan = 0;                      // psm+0x48
        u32 core = 0;                      // psm+0x4C
        std::array<Resampler, 2> rs{};
        u32 stream = 0;            // StreamTap session id (0 = none)
    };

    // module image (IOP addresses of the objects; fixed once allocated in the server arena)
    u32 base_ = 0;
    std::array<Dtx, kDtxMax> dtx_{};
    std::array<Rna, kRnaMax> rna_{};
    std::array<Sjx, kSjxMax> sjx_{};
    std::array<SjUni, kSjMax> sj_{};

    // PSM globals
    u32 core_no_ = 0;          // IRX 0xD410 ("spucore=" never parses for this game, 16 §1.2)
    u32 sfreq_default_ = 48000;  // 0xD7F4 (urpc 12)
    u32 psm_voices_ = 0;       // 0xD800 (urpc 10)
    u32 init_count_ = 0;       // 0xD40C
    bool paused_ = false;      // 0xD418 (command 11)
    std::array<bool, 2> out_running_{};
    u64 next_frame_ = 0;       // timeline position of the next pass

    u64 seen_vblank_ = ~0ull;
    u64 tick_due_ = kNever;
    u64 now_ = 0;               // virtual time of the current call / pass (events)
    IopCore* core_ = nullptr;   // for record_event (set on every call / tick)
    u32 stream_seq_ = 0;
    AdxiStats st_{};
    audio::AudioSink* mix_ = nullptr;
    audio::StreamTap* tap_ = nullptr;
    std::vector<s16> mixbuf_;

    void ensure_image(IopCore& core);
    u32 dtx_handle(u32 i) const { return base_ + 0x0000u + 68u * i; }
    u32 rna_handle(u32 i) const { return base_ + 0x0480u + 0x1Cu * i; }
    u32 sjx_handle(u32 i) const { return base_ + 0x0680u + 20u * i; }
    u32 sj_handle(u32 i) const { return base_ + 0x0980u + 0x30u * i; }
    int rna_index(u32 handle) const;
    int sjx_index(u32 handle) const;
    int sj_index(u32 handle) const;
    SjUni* sj_at(u32 handle);

    bool active() const;
    void server_pass(IopCore& core, u64 now);
    void dtx_exec(IopCore& core, Dtx& d);
    void sjx_receive(IopCore& core, std::span<u8> buf);
    void sjx_send(IopCore& core, std::span<u8> buf);
    void rna_receive(IopCore& core, std::span<u8> buf);
    void urpc(IopCore& core, u32 n, std::vector<u8>& b);
    void bind_module_defaults();

    // PSM
    void psm_init(IopCore& core);
    void psm_finish();
    void out_start(IopCore& core, u32 core_no);
    void out_stop(u32 core_no);
    void render_until(IopCore& core, u64 now);
    void render_pass(IopCore& core);
    void psm_start(Rna& r, u32 index);
    void psm_stop(Rna& r);
    u32 read_samples(IopCore& core, Rna& r, u32 ch, std::span<s16> out);
};

std::unique_ptr<AdxiServer> make_adxi_server();

// The PSM volume law (IRX 0x27E4): side gain 0..255 for a channel volume 0..255, pan -15..15 and
// output pan -15..15; `right` selects the mirrored table entries.
u32 psm_side_gain(s32 vol, s32 pan, s32 mpan, bool right);

}  // namespace p3fes::hle::sif::detail
