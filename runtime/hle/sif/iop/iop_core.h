// Private: the IOP model behind IopHle (iop.h) -- IOP RAM, the sifcmd/sifrpc services, the SIF
// register file both CPUs see, the IOP -> EE (SIF0) queue and the RPC server registry. The servers
// themselves live in srv_*.cpp and talk to the core only through RpcServer / IopCore below.
#pragma once

#include <array>
#include <cstddef>
#include <deque>
#include <map>
#include <memory>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "p3fes/ee_memory.h"
#include "p3fes/hle/hw_bus.h"
#include "p3fes/hle/sif/iop.h"
#include "p3fes/hle/sif/protocol.h"

namespace p3fes::audio {
class Spu2Mixer;
}
namespace p3fes {
class StateIo;  // p3fes/state_io.h (machine states, iop_state.cpp)
}

namespace p3fes::hle::sif::detail {

inline constexpr u64 kNever = ~0ull;

// ---- IOP memory map (inf: chosen, plausible for a 2 MiB IOP after IOPRP310 + 15 modules) --------
inline constexpr u32 kIopRamSize = 2u * 1024u * 1024u;
inline constexpr u32 kIopCmdBuffer = 0x0001E000u;   // sifcmd receive buffer (what SMCOM reports)
inline constexpr u32 kIopCmdBufferSize = 0x100u;
inline constexpr u32 kIopServerArena = 0x00020000u; // server data + receive buffers (bump allocated)
inline constexpr u32 kIopServerArenaEnd = 0x00080000u;
inline constexpr u32 kIopHeapBegin = 0x00080000u;   // sysmem/heaplib allocations
inline constexpr u32 kIopHeapEnd = 0x001F0000u;
inline constexpr u32 kIopHeapAlign = 256u;           // inf: sysmem block granularity

class IopRam {
public:
    IopRam();
    // nullptr if [addr, addr+len) leaves IOP RAM (addresses are masked to the 2 MiB physical window
    // first: kseg0/kseg1 mirrors fold).
    u8* at(u32 addr, u32 len);
    const u8* at(u32 addr, u32 len) const;
    std::span<const u8> image() const { return {ram_.data(), ram_.size()}; }

    // Heap (heaplib AllocSysMemory / AllocIopHeap). mode 0 = first fit from the bottom, 1 = from the
    // top, 2 = at `addr` exactly (anywhere in RAM above the server arena, 16-byte granular). 0 = failed.
    u32 alloc(u32 size, u32 mode, u32 addr);
    // First fit inside [lo, hi) (the interpreted modules' kernel-owned memory, iop_kernel_hle.h).
    u32 alloc_in(u32 lo, u32 hi, u32 size);
    bool free(u32 addr);
    u32 free_total() const;
    u32 free_max() const;
    u32 block_size(u32 addr) const;   // 0 if not an allocated block start
    void reset_heap();
    // The range mode 0/1 allocations come from (IopConfig::iop_layout); default kIopHeapBegin..End.
    void set_heap(u32 begin, u32 end) { heap_begin_ = begin; heap_end_ = end; }
    u32 heap_begin() const { return heap_begin_; }
    u32 heap_end() const { return heap_end_; }
    const std::map<u32, u32>& blocks() const { return blocks_; }

    // Server arena (fixed for the life of the IOP; reset on reboot).
    u32 arena_alloc(u32 size);
    void reset_arena() { arena_next_ = kIopServerArena; }
    void state(StateIo& io);

private:
    std::vector<u8> ram_;
    std::map<u32, u32> blocks_;  // start -> size (rounded)
    u32 arena_next_ = kIopServerArena;
    u32 heap_begin_ = kIopHeapBegin, heap_end_ = kIopHeapEnd;
    bool overlaps(u32 start, u32 size) const;
};

// The SIF mailbox registers + the kernel's software registers (sceSifSetReg/GetReg).
struct SifRegisterFile {
    u32 mscom = 0;
    u32 smcom = kIopCmdBuffer;
    u32 msflg = 0;
    u32 smflg = flag::kAllBooted;  // the IOP is up when the game starts (booted by EELOAD)
    u32 ctrl = 0;
    u32 bd6 = 0;
    std::array<u32, reg::kSystemCount> sys{};
};

// One IOP -> EE data write (part of a SIF0 transfer).
struct EeWrite {
    u32 addr = 0;
    std::vector<u8> bytes;
};

// One SIF0 transfer list: data writes, optionally followed by a command packet for the EE's receive
// buffer (which raises DMAC ch5).
struct Sif0Item {
    std::vector<EeWrite> writes;
    bool has_packet = false;
    std::array<u8, kCmdPacketMax> packet{};
    u32 packet_size = 0;
    u64 not_before = 0;
};

struct RpcRequest {
    u32 sid = 0;
    u32 fno = 0;
    std::span<const u8> data;  // send data, in IOP RAM at the server's buffer
    u32 data_iop = 0;          // IOP address of `data` (the binding's receive buffer)
    u32 recv_size = 0;
    u32 recv_ee = 0;           // EE receive buffer
    u32 client_ee = 0;         // EE SifRpcClientData_t*
    u32 rmode = 0;
};

struct RpcReply {
    std::vector<u8> rdata;       // reply data for the receive buffer (padded/truncated to recv_size)
    std::vector<EeWrite> writes; // other IOP -> EE writes that precede the reply
};

// Machine-state serialisers of the shared structs (iop_state.cpp).
void state_io(StateIo& io, EeWrite& w);
void state_io(StateIo& io, Sif0Item& s);
void state_io(StateIo& io, RpcReply& r);

class IopCore;
class CdvdfsvServer;
class PadmanServer;
class AdxiServer;
class SdrdrvServer;

class RpcServer {
public:
    virtual ~RpcServer() = default;
    virtual std::string_view name() const = 0;
    // Answer a call. Return true when `reply` is final; false to defer: the server keeps `ticket` and
    // later calls core.complete(ticket, reply).
    virtual bool call(IopCore& core, const RpcRequest& req, RpcReply& reply, u32 ticket) = 0;
    // Timed work (latency, per-vblank output). `now` = Timebase::cycles.
    virtual void tick(IopCore& /*core*/, u64 /*now*/, const Timebase& /*tb*/) {}
    virtual u64 next_deadline() const { return kNever; }
    // The IOP rebooted: forget per-boot state.
    virtual void reboot() {}
    // Machine state (iop_state.cpp / each server's file): every dynamic field. Loading runs after the server was
    // built and wired like the saver's; `core` is the owner (for servers that build parts lazily).
    virtual void state(StateIo& io, IopCore& core) = 0;
};

struct Binding {
    u32 sid = 0;
    RpcServer* server = nullptr;  // nullptr = unknown server (answers zeros)
    u32 sd = 0;                   // IOP address of its SifRpcServerData_t (what bind reports)
    u32 buf = 0;                  // receive buffer (what bind reports as cd->buf)
    u32 buf_size = 0;
};

class IopCore {
public:
    IopCore(EEMemory& mem, HwBus& bus, IopConfig config, DiscSource* disc);
    ~IopCore();

    // ---- driven by SifHle ---------------------------------------------------------------------
    // One SIF1 transfer (EE -> IOP), already copied out of EE RAM.
    void sif1_receive(u32 iop_dest, std::span<const u8> bytes, u32 attr);
    void tick();
    // Delivers due SIF0 items while `sif0_started`; clears it for every packet delivered.
    void flush_sif0(bool& sif0_started);
    u64 next_event_cycles(bool sif0_started) const;

    SifRegisterFile& regs() { return regs_; }

    // ---- used by servers ----------------------------------------------------------------------
    EEMemory& ee() { return mem_; }
    IopRam& ram() { return ram_; }
    const IopRam& ram() const { return ram_; }
    const IopConfig& config() const { return config_; }
    IopStats& stats() { return stats_; }
    const IopStats& stats() const { return stats_; }
    u64 now() const { return bus_.time().cycles; }
    const Timebase& time() const { return bus_.time(); }
    void complete(u32 ticket, RpcReply reply);
    // Queues an IOP -> EE command packet (header filled from `cid`, payload after the header) with
    // optional data writes ahead of it.
    void send_command(u32 cid, std::span<const u8> payload, std::vector<EeWrite> writes = {}, u32 opt = 0);
    // Immediate IOP -> EE write that raises no interrupt (PADMAN frames). false: not EE memory.
    bool ee_store(u32 addr, std::span<const u8> bytes);
    // IOP-initiated sceSifSetDma without a command (CRI DTX write-back, IRX 0xC68): queued on SIF0
    // behind earlier items and delivered by the next service() (ADR-0013 check points).
    void queue_ee_write(u32 addr, std::vector<u8> bytes);
    bool ee_load(u32 addr, std::span<u8> out) const;
    void note_unknown(UnknownEvent::Kind kind, u32 id, u32 fno, std::string_view what);
    void log(std::string_view line) const;
    void record_sound(const SoundRequest& r);
    // A sound-side event that is not a request (voice key-on/off, RNA start/stop): to the sink and the
    // census, not counted in sound_requests().
    void record_event(const SoundRequest& r);
    void record_module(LoadedModule m) { modules_.push_back(std::move(m)); }
    int next_module_id() { return next_module_id_++; }
    // Points an existing binding at a server's own SifRpcServerData_t / receive buffer (the interpreted
    // SDRDRV registering 0x80000701): later binds report them and later calls' send data lands there.
    void rebind_server(u32 sid, u32 sd, u32 buf, u32 buf_size);
    // loadfile asked for `path`: the SK module path is interpreted when sk_mode says so (srv_sdr.h);
    // returns its start result, nullopt when nothing was loaded.
    std::optional<s32> load_sk_module(std::string_view path, std::string_view args);

    // ---- inspection -----------------------------------------------------------------------------
    const std::vector<LoadedModule>& modules() const { return modules_; }
    std::vector<SoundRequest> sound_log() const;
    u64 sound_requests() const { return sound_total_; }
    const std::map<std::string, u64>& sound_census() const { return sound_census_; }
    std::vector<UnknownEvent> unknown_events() const;
    u64 unknown_total() const { return unknown_total_; }
    bool rebooting() const { return rebooting_; }
    u32 ee_receive_buffer() const { return ee_recv_buf_; }
    CdvdHle* cdvd();
    void set_pad_input(unsigned port, const PadInput& in);
    void set_audio_output(audio::AudioSink* mix, audio::StreamTap* tap);
    audio::AudioSink* adx_input() { return adx_input_; }
    AdxiStats adxi_stats() const;
    void flush_audio();
    SkStats sk_stats() const;
    SdrdrvServer* sdrdrv() { return sdr_; }

    // Machine state of the IOP side (iop_state.cpp): RAM + heap, SIF registers, queued SIF0 packets, bindings,
    // pending calls, every server, the SPU2 mixer and the memory card image.
    void state(StateIo& io);

private:
    struct PendingCall {
        RpcCall call;
        u32 sid = 0;
    };

    EEMemory& mem_;
    HwBus& bus_;
    IopConfig config_;
    IopRam ram_;
    SifRegisterFile regs_;
    IopStats stats_{};

    std::deque<Sif0Item> sif0_;
    u32 ee_recv_buf_ = 0;
    std::array<u32, 32> iop_sregs_{};

    bool rebooting_ = false;
    u64 reboot_deadline_ = kNever;

    std::vector<std::unique_ptr<RpcServer>> servers_;
    std::map<u32, Binding> by_sid_;
    std::map<u32, u32> sid_by_sd_;
    std::map<u32, PendingCall> pending_;
    u32 next_ticket_ = 1;

    std::vector<LoadedModule> modules_;
    int next_module_id_ = 1;

    std::array<SoundRequest, 256> sound_ring_{};
    u64 sound_total_ = 0;
    std::map<std::string, u64> sound_census_;  // sound_verb() -> count

    std::map<std::pair<int, u64>, UnknownEvent> unknown_;
    u64 unknown_total_ = 0;

    CdvdfsvServer* cdvd_ = nullptr;
    PadmanServer* pad_ = nullptr;
    AdxiServer* adxi_ = nullptr;
    SdrdrvServer* sdr_ = nullptr;
    audio::AudioSink* adx_input_ = nullptr;  // set_audio_output: the mixer's stream input, else the mix sink
    std::unique_ptr<audio::Spu2Mixer> mixer_;  // Modules mode: voices + PSM -> the host sink

    void register_servers(DiscSource* disc);
    Binding& bind_server(u32 sid, RpcServer* server, u32 buf_size);
    Binding& binding_for(u32 sid);
    void on_command(std::span<const u8> pkt);
    void on_bind(std::span<const u8> pkt);
    void on_call(std::span<const u8> pkt);
    void on_rdata(std::span<const u8> pkt);
    void begin_reboot(std::span<const u8> pkt);
    void finish_reboot();
    void finish_call(const RpcCall& call, const Binding& b, RpcReply reply);
    void push(Sif0Item item);
};

// Server factories (srv_*.cpp).
std::unique_ptr<RpcServer> make_loadfile_server();
std::unique_ptr<RpcServer> make_heap_server();
std::unique_ptr<RpcServer> make_fileio_server();
std::unique_ptr<RpcServer> make_dbcman_server();
std::unique_ptr<SdrdrvServer> make_sdrdrv_server(DiscSource* disc);  // srv_sdr.cpp (SDRDRV + SK modules)
std::unique_ptr<AdxiServer> make_adxi_server();   // srv_adxi.cpp (CRI_ADXI: DTX, SJX, SJRMT, IOPRNA/PSM)


// Little helpers shared by the servers.
inline u32 req_word(const RpcRequest& r, std::size_t off) { return load32(r.data, off); }
inline void put_word(std::vector<u8>& v, std::size_t off, u32 value) {
    if (v.size() < off + 4) v.resize(off + 4, 0);
    store32(v, off, value);
}
inline std::string c_string(std::span<const u8> b, std::size_t off, std::size_t max) {
    std::string s;
    for (std::size_t i = off; i < b.size() && i < off + max && b[i] != 0; ++i) s.push_back(static_cast<char>(b[i]));
    return s;
}
std::string hex32(u32 v);

// How the IOP splits a DMA into an EE buffer that is not 64-byte aligned (cdvdfsv readee, ps2sdk
// cdvdfsv.c @ 329e2bb; the same head/tail block shape is unpacked by _sceCd_cd_read_intr 0x50F8A8 and
// _sceFs_Rcv_Intr 0x507C38): `head` bytes up to the next 64-byte line and the `tail` after the last
// line boundary travel in a side block the EE copies into place; `body` is DMA'd directly.
struct UnalignedSplit {
    u32 head = 0, body = 0, tail = 0;
    u32 tail_addr = 0;  // (addr + len) & ~63
};
inline UnalignedSplit split_unaligned(u32 addr, u32 len) {
    UnalignedSplit s;
    const u32 end = addr + len;
    s.tail_addr = end & ~63u;
    if (len == 0) return s;
    if ((addr & ~63u) == ((end - 1u) & ~63u) && (addr & 63u) != 0) {  // inside one line (fileio 1-byte reads)
        s.head = len;
        s.tail_addr = end;
        return s;
    }
    s.head = (addr & 63u) ? 64u - (addr & 63u) : 0u;
    s.tail = end - s.tail_addr;
    s.body = len - s.head - s.tail;
    return s;
}

}  // namespace p3fes::hle::sif::detail
