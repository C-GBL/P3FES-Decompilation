// The "IOP" on the far side of the SIF: an HLE of the sifcmd/sifrpc kernel services and of the RPC
// servers SLUS_216.21 binds (docs/ANALYSIS/12_irx_rpc_threads.md §2, RUNTIME_CONTRACT §4). No IOP
// code runs for the servers below except the sound path: with IopConfig::sk_mode == Modules the six
// SK/libsd IRX modules are loaded from the disc and interpreted in place (ADR-0014, runtime/hle/sif/README.md
// §9), answering SDRDRV's RPC and driving the SPU2 voice model. Requests arrive as SIF command packets
// over SIF1 (EE -> IOP, sceSifSetDma) and every
// answer leaves as IOP -> EE SIF0 DMA: data written into EE RAM plus, for packets, a write into the
// EE's sifcmd receive buffer followed by HwBus::dma_complete(5), so the game's own
// sceSifCmdIntrHdlr / _request_end / end callbacks run (runtime/hle/sif/README.md).
//
// This header is the inspection and host-input surface; the IOP is created and driven by SifHle
// (sif.h). Not thread-safe (ADR-0013 §1).
#pragma once

#include <array>
#include <cstddef>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "p3fes/ee_types.h"

namespace p3fes::hle {
class CdvdHle;
class DiscSource;
}  // namespace p3fes::hle

namespace p3fes::audio {
class AudioSink;
class StreamTap;
}  // namespace p3fes::audio

namespace p3fes::hle::memcard {
struct IopSlotConfig;
}  // namespace p3fes::hle::memcard

namespace p3fes::hle::sif {

namespace detail {
class IopCore;
}

// Host controller state for one pad port (the lead feeds it from the keyboard/XInput later).
// `buttons` is a pressed mask in libpad's convention (ps2sdk ee/rpc/pad/include/libpad.h @ 329e2bb:
// the game reads ~(data[2] | data[3] << 8)); sticks are 0x00..0xFF, 0x80 centred.
struct PadInput {
    bool connected = true;
    u16 buttons = 0;
    u8 rx = 0x80, ry = 0x80, lx = 0x80, ly = 0x80;
};
namespace pad_button {
inline constexpr u16 kSelect = 0x0001, kL3 = 0x0002, kR3 = 0x0004, kStart = 0x0008;
inline constexpr u16 kUp = 0x0010, kRight = 0x0020, kDown = 0x0040, kLeft = 0x0080;
inline constexpr u16 kL2 = 0x0100, kR2 = 0x0200, kL1 = 0x0400, kR1 = 0x0800;
inline constexpr u16 kTriangle = 0x1000, kCircle = 0x2000, kCross = 0x4000, kSquare = 0x8000;
}  // namespace pad_button

struct SoundRequest;

// One sceCdRead the game made through cdvdfsv (sid 0x80000595 fn 1), as its data is delivered (or refused).
// IopConfig::cd_read_sink; the host's --read-log (docs/MODERNIZE_PLAN.md §3, stage 0). Observation only.
struct CdReadEvent {
    u32 lsn = 0, sectors = 0;  // sceCdRead's arguments
    u32 dst = 0;               // the guest destination (sceCdRead's buf)
    int error = 0;             // libcdvd error code at completion (0 = data delivered; SCECdErREAD for a refused read)
    std::span<const std::byte> data;  // the sectors*2048 bytes delivered (the staging copy for an unaligned
                                      // destination, guest RAM otherwise); empty when error != 0
    u64 cycle = 0, vblank = 0;  // Timebase at completion
};

// Who answers SDRDRV's RPC 0x80000701 (runtime/hle/sif/README.md §9, ADR-0014): the constant replies of
// srv_sdr.cpp §3 (increment 1 and before; silent) or the game's own SDRDRV/SK/MOD IRX modules interpreted
// in place over the SPU2 voice model (increment 2, the default). Kept as a switch for A/B runs.
enum class SkMode : u8 { Constants, Modules };
// Where IOP memory is handed out (iop_core.h): Legacy = the map every snapshot before increment 2 was taken
// with (heap from 0x80000); Pcsx2 = the SK module images at the addresses PCSX2 loaded them to and the game's
// heap allocations from 0xBD400, which is where PCSX2's first game allocation lands (docs/ANALYSIS/19 §1.4
// "IOP identity": the IOP addresses the EE stores then equal PCSX2's). Pcsx2 needs Modules for the images.
enum class IopLayout : u8 { Legacy, Pcsx2 };

struct IopConfig {
    // Virtual time from an N-command (sceCdRead / sceCdSeek) arriving to its RPC end being queued:
    // max(1, fixed + per sector). 0/0 (default) = completes at the first service() once virtual time
    // has moved past the issuing syscall, which `11` §5.3 shows is safe (every consumer polls;
    // sceCdRead sets sceCd_c_cb_sem before calling sceSifCallRpc, obs 0x510CC4).
    u64 cd_fixed_latency_cycles = 0;
    u64 cd_cycles_per_sector = 0;
    // Virtual time from the reset packet (sceSifResetIop) to SMFLAG SIFINIT|CMDINIT|BOOTEND being
    // set again. Must exceed the few instructions between the reset DMA and the EE's own SMFLAG
    // clears (obs 0x50C93C -> 0x50C958). inf: 1 ms.
    u64 reboot_cycles = 294'912;
    // Contents of rom0:ROMVER served by fileio (checkModelVersion 0x4F90B8 reads it byte by byte up
    // to a NUL and compares the last 8 digits with 20010608). Default: the 16 bytes of the BIOS the
    // PCSX2 oracle runs (v02.30 USA, `15` §0; ROMDIR size 16), i.e. a "new" model, so the game asks
    // the kernel for _GetGsDxDyOffset (syscall 0x80), which owns the offsets (`15` H-23).
    std::array<char, 16> romver = {'0', '2', '3', '0', 'A', 'C', '2', '0', '0', '8', '0', '2', '2', '0', '\n', '\0'};
    // First module id handed out by loadfile after each IOP (re)boot (ids are sequential).
    int first_module_id = 1;
    // Log sink for loud events (unknown ids, first occurrences, reboots). nullptr = stderr.
    std::function<void(std::string_view)> log;
    // Per-call trace (every bind/call/command); off by default.
    bool trace = false;
    // CRI_ADXI's server thread runs once per IOP vblank-end (WaitVblankEnd, IRX 0x17C): RNA discard,
    // then every DTX exchange. The HLE runs that tick this long after it first sees a new
    // VBLANK_START. inf: ~22 H-lines of NTSC vertical blanking (22 x 18,743 EE cycles).
    u64 adxi_tick_delay_cycles = 412'352;
    // Memory card in MEMORY CARD slot 1 behind the DBCMAN + MC2_S1 model (iop/srv_dbcman.cpp,
    // docs/ANALYSIS/17_memory_card.md; p3fes/hle/memcard/iop_slot.h). nullptr: no card inserted.
    std::shared_ptr<const memcard::IopSlotConfig> memcard;
    // Every sound-side request (SDRDRV libsd codes, SK 0x90F0 blocks, CRI DTX) as it is answered, in order,
    // the full stream (the inspection ring keeps only the newest 256). Host `--sound-log FILE` writes one
    // line per call (docs/ANALYSIS/19 §4 phase 0). Called on the host thread, from inside the RPC. Voice
    // key-on/key-off events of the SPU2 model and RNA start/stop of the ADX model arrive here too (sid 0 /
    // fno 1 KON, 2 KOFF; sid 0x90000200 fno 0x8000/0x8001), not counted as requests.
    std::function<void(const SoundRequest&)> sound_sink;
    // Every sceCdRead as it completes (or is refused), in order (CdReadEvent). Called on the host thread from the
    // IOP's tick, after the data is in place and before the EE sees the RPC end; it must not write anywhere the
    // guest can see. nullptr = off (the default).
    std::function<void(const CdReadEvent&)> cd_read_sink;
    // ADR-0014: the SK sound path (see SkMode / IopLayout above).
    SkMode sk_mode = SkMode::Modules;
    IopLayout iop_layout = IopLayout::Pcsx2;
    // Where the six module files come from when `sk_mode == Modules`: by default the disc the IOP was built
    // with (cdrom0:\LIB31\<name>;1 through its DiscSource; the extracted-volumes source reads
    // extracted/disc/LIB31/<name>). Tests override with a reader of their own; a reader returning nullopt
    // (or no disc) leaves the constant replies in place, logged once.
    std::function<std::optional<std::vector<u8>>(std::string_view file_name)> module_source;
    // SPU2 voice model: the hardware's 4-tap gaussian interpolation (default) or the linear form of
    // increment 2 (p3fes/audio/spu2_voice.h Interpolation); host --spu2-interp.
    bool spu2_gaussian = true;
};

// ADR-0014 counters (IopHle::sk_stats): the interpreted SK stack and the voice model.
struct SkStats {
    bool modules = false;          // the six modules are loaded and SDRDRV answers 0x80000701
    u32 modules_loaded = 0;        // IRX images loaded (7 with the game's duplicate SKHSYNTH)
    u64 rpc_routed = 0;            // requests answered by SDRDRV's handler
    u64 rpc_pending = 0;           // handlers that blocked and finished later (expected 0)
    u64 tick_runs = 0;             // SKSOUND hard-timer handler runs
    u64 instructions = 0;          // R3000 instructions interpreted
    u64 key_ons = 0, key_offs = 0; // SPU2 voice model
    u64 key_offs_sounding = 0;     // key-offs that released a voice still sounding (the rest found it idle)
    u32 voices_active = 0;         // at the instant of the query (0 between sounds: no stuck voice)
    u32 voices_active_max = 0;     // most voices active at one rendered instant
    u64 voice_longest_frames = 0;  // longest key-on .. off span of a finished voice (render granularity)
    u64 volume_sweeps = 0;         // voice volume writes in sweep mode (bit 15), not modelled
    u32 sd_inits = 0;              // sceSdInit calls the modules made
    u64 voice_frames = 0;          // frames in which a voice produced output
    u64 first_voice_frame = ~0ull; // timeline frame of the first voice output (~0 = none)
    u64 mix_passes = 0;            // mixer passes pushed to the host sink
    u64 mix_passes_skipped = 0;    // silent passes left as gaps
    u64 mix_stream_late = 0;       // PSM frames that arrived for an already emitted pass (dropped; expected 0)
    std::string fault;             // the kernel's first fatal problem, empty = none
};

struct LoadedModule {
    int id = 0;
    std::string path;  // as sent, e.g. "cdrom0:\LIB31\SIO2MAN.IRX;1"
    std::string args;  // NUL-separated arguments with NULs shown as '\0' bytes (arglen bytes)
};

// One sound-side request (SDRDRV 0x80000701 incl. the SK 0x90F0 blocks, CRI DTX 0x90000200).
struct SoundRequest {
    u32 sid = 0;
    u32 fno = 0;              // libsd function code / DTX command
    u32 sk_module = 0;        // SK block word0 (0 SOUND, 0x1000000 HSYNTH, 0x4000000 SESQ) when fno == 0x90F0
    u32 sk_function = 0;      // SK block word1
    std::array<u32, 8> args{};  // first words after the selector(s)
    s32 result = 0;
    u64 cycle = 0;
    u64 vblank = 0;           // Timebase::vblanks when answered
};

// The verb a request stands for, as a short stable key for logs and the capture.json census
// (docs/ANALYSIS/19 §1.1 names): "SetParam", "SOUND_Control 0x80", "SOUND_Send", "HSYNTH_Bind 3",
// "SESQ_Control play", "DTX urpc", ... Unknown codes become "libsd 0x8090" / "SK m/f".
std::string sound_verb(const SoundRequest& r);

// A server id, command id or function the HLE does not model. Answered (zeros / success) and
// logged once; `count` keeps growing.
struct UnknownEvent {
    enum class Kind : u8 { Server, Function, Command, Dma } kind = Kind::Command;
    u32 id = 0;   // sid / cid / IOP address
    u32 fno = 0;  // function number for Kind::Function
    u64 count = 0;
};

// CRI_ADXI model counters (runtime/hle/sif/iop/srv_adxi.cpp; docs/ANALYSIS/16_iop_audio_modules.md).
struct AdxiStats {
    u64 ticks = 0;               // IOP server passes (vblank-end ticks that had work)
    u64 dtx_blocks_in = 0;       // EE blocks accepted (EE counter > IOP counter)
    u64 dtx_blocks_out = 0;      // IOP blocks DMA'd back (counter written to the EE buffer)
    u64 urpc_calls = 0;
    u64 sjx_chunks_in = 0;       // data chunks the EE handed over (SJX, DTX id 0)
    u64 sjx_chunks_out = 0;      // consumed chunks returned to the EE
    u64 rna_commands = 0;        // RNA parameter commands (DTX id 1)
    u64 psm_passes = 0;          // 512-frame mixer passes rendered
    u64 pcm_bytes_consumed = 0;  // input PCM read out of IOP RAM by the mixer
    u64 underrun_samples = 0;    // a playing channel had no data
    u64 sj_errors = 0;           // chain-pool overflow / bad handle
    u32 dtx_open = 0;            // DTX objects in use
    u32 rna_playing = 0;         // RNAs currently started
};

struct IopStats {
    u64 sif1_transfers = 0;    // SifDmaTransfer_t entries consumed
    u64 commands = 0;          // packets parsed from the IOP command buffer
    u64 sync_packets = 0;      // cid 0x80000004 appended by libsifcmd's sceSifSetDma
    u64 binds = 0;
    u64 calls = 0;
    u64 sif0_packets = 0;      // packets written to the EE receive buffer (= dma_complete(5) calls)
    u64 sif0_data_writes = 0;  // IOP -> EE data writes (reply data, fp, cd sectors, pad frames ...)
    u64 ee_write_failures = 0; // EE address not backed (logged)
    u64 reboots = 0;
    u64 cd_reads = 0;
    u64 cd_sectors = 0;
    u64 pad_frames = 0;
};

// --native sound, steps 2-3: the SK stack on native code (runtime/native/sound/sk) as SDRDRV's server would see it
// (the host's adapter over sk::NativeSk; IopHle::set_native_sk).
class SkNativeBackend {
public:
    virtual ~SkNativeBackend() = default;
    // loadfile's request for one of the six SK modules at virtual `now`: the module id; its start result in `start`.
    virtual s32 load_module(u64 now, std::string_view path, std::string_view args, s32* start) = 0;
    // SDRDRV's registered RPC server (its SifRpcServerData_t and receive buffer), false before SDRDRV started.
    virtual bool server(u32& sd, u32& buf) const = 0;
    // SDRDRV's function `fno` with `send` (already in its receive buffer): the reply bytes, nullopt after a fault.
    virtual std::optional<std::vector<u8>> rpc(u64 now, u32 fno, std::span<const u8> send, u32 recv_size) = 0;
    virtual void advance(u64 now) = 0;  // the SK tick up to `now`
    virtual u64 tick_runs() const = 0;
    virtual std::string fault() const = 0;
};

class IopHle {
public:
    ~IopHle();
    IopHle(const IopHle&) = delete;
    IopHle& operator=(const IopHle&) = delete;

    // Host input for pad port 0/1 (slot 0). Applied to the next frame PADMAN writes (one per vblank).
    void set_pad_input(unsigned port, const PadInput& in);
    // Host audio: the CRI_ADXI mixer model pushes its 48 kHz stereo output to `mix` and every RNA
    // play session's consumed PCM to `tap` (both optional, borrowed; nullptr detaches). The output
    // is a function of virtual time only (runtime/audio/README.md).
    void set_audio_output(audio::AudioSink* mix, audio::StreamTap* tap = nullptr);
    // Where an ADX stream's 48 kHz passes enter the output: the SPU2 mixer's stream input in Modules mode (the
    // voices are added there), else `mix` itself. `--native sound` pushes its ADX mix here (runtime/native/sound).
    audio::AudioSink* adx_input();
    AdxiStats adxi_stats() const;
    // End of run: pushes the mixer's last passes (the voice/PSM sum is emitted two passes behind the clock).
    void flush_audio();
    SkStats sk_stats() const;

    // ---- --native sound, steps 2-3 (runtime/native/sound/sk, docs/MODERNIZE_PLAN.md section 3) ----------------------
    // What the native SK stack (the six SK modules as native code, no interpreter, no SIF) uses of this model: the RAM
    // the game uploads its sound banks to (sceSifAllocSysMemory + SIF DMA from H_Sndcom), the heap's placement calls,
    // libsd over the SPU2 voice model the mixer plays (iop/libsd_hle.h libsd_call: the same LibsdHle the interpreted
    // modules drive, created on first use and attached to the mixer), and the --sound-log request line. Supported
    // with sk_mode == Modules and iop_layout == Pcsx2 (the native code sits at the Pcsx2 image bases).
    bool native_sk_supported() const;
    u8* native_sk_ram();  // 2 MiB
    u32 native_sk_alloc(u32 size, u32 mode, u32 addr);
    u32 native_sk_alloc_in(u32 lo, u32 hi, u32 size);
    bool native_sk_free(u32 addr);
    u32 native_sk_libsd(u32 ordinal, const u32 (&args)[5]);
    void native_sk_at_time(u64 ee_cycles);  // the voices render up to here
    // One SDRDRV request answered natively, logged and counted as the faithful server records it (sid 0x80000701).
    void native_sk_record(u32 fno, std::span<const u8> send, s32 result, u64 cycles);
    // A LIB31 module file as the faithful loader reads it (IopConfig::module_source, else the disc).
    std::optional<std::vector<u8>> read_sk_module(std::string_view file_name);
    void log(std::string_view line) const;
    // The native SK stack behind SDRDRV's RPC: loadfile's requests for the six SK modules start it instead of loading
    // the IRX into the interpreter, and every SDRDRV request is answered by it at the same virtual instant the
    // interpreted modules would answer (the game's sceSdRemote / sceSifCallRpc traffic is unchanged). nullptr = off.
    void set_native_sk(SkNativeBackend* backend);

    // Inspection.
    const IopStats& stats() const;
    std::vector<LoadedModule> modules() const;  // since the last IOP reboot, in load order
    std::vector<SoundRequest> sound_log() const;  // newest 256, oldest first
    u64 sound_requests() const;
    std::map<std::string, u64> sound_census() const;  // sound_verb() -> count, since start
    std::vector<UnknownEvent> unknown_events() const;
    u64 unknown_total() const;
    bool rebooting() const;
    u32 ee_receive_buffer() const;  // EE address the IOP sends packets to (0 = not told yet)
    std::span<const u8> ram() const;  // 2 MiB IOP RAM image
    u32 heap_free_total() const;
    CdvdHle* cdvd();  // nullptr when constructed without a disc

private:
    friend class SifHle;
    explicit IopHle(std::unique_ptr<detail::IopCore> core);
    std::unique_ptr<detail::IopCore> core_;
};

}  // namespace p3fes::hle::sif
