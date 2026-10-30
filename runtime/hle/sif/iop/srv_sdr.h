// SDRDRV.IRX ("sdr_driver", RPC 0x80000701) and the Standard Kit sound modules it dispatches to
// (SKSOUND "StandardKit/Sound/Foundation", SKHSYNTH "HardwareSynthesizer", SKSESQ "SE_Seq_Player",
// MODSESQ, MODHSYN). Two ways to answer (IopConfig::sk_mode, ADR-0014; README.md §9):
//
//   * Modules (default): the six IRX files are loaded from the disc when the game's loadfile requests
//     them (IopCore::load_sk_module from srv_system.cpp), relocated into IOP RAM at the addresses PCSX2
//     loads them to (IopLayout::Pcsx2) and run on the kernel HLE (iop_kernel_hle.h). Once SDRDRV's RPC
//     thread has registered 0x80000701 the binding is re-pointed at its SifRpcServerData_t / receive
//     buffer, so the EE's send data lands in the module's own buffer and every request -- the libsd
//     codes 0x8000..0x8080, 0xE620, 0x8F10 and the 0x90F0 SK blocks -- is handed to the handler at
//     +0x588 on that thread (IopKernel::rpc_dispatch); the reply is the 16 bytes at the pointer it
//     returns. Before each request and at every SIF check point the kernel is advanced to virtual
//     `now` so SKSOUND's 240 Hz tick (MODSESQ sequencing, MODHSYN voice keying through libsd) runs on
//     time; libsd drives the SPU2 voice model (p3fes/audio/spu2_voice.h), which the IopCore's mixer
//     sums with the CRI PSM stream into the host AudioSink. Nothing here adds a check point
//     (next_deadline stays "never"): the modules consume no EE time.
//   * Constants: the increment-1 model below -- the values the IRXs return, with no voices played and
//     SOUND_Send's bank bytes kept in a 2 MiB SPU2-RAM shadow. Evidence: docs/ANALYSIS/16 §9 (IRX
//     offsets per module) and the EE clients (sceSdRemote 0x5129C0, sceSkSs* 0x51DB00..0x51E0DC,
//     H_Sndcom_* 0x10CAC0..0x10DB60):
//       - every call: result word cleared (SDRDRV 0x5A4), the 16-byte reply is {result, 0, 0, 0};
//       - libsd codes (0x588 switch): SetParam/SetSwitch/SetAddr/SetCoreAttr store into a register
//         shadow, the Get* forms read it back (inf: the SPU2 itself is not modelled);
//       - 0xE620 starts SDRDRV's callback thread (0xC8C) -> 0; the thread binds the EE's 0x80000704
//         (0xFF0/0x1014) but never calls it in this game -- the bind is not sent (16 §9.5);
//       - 0x9000..0x90F0 user commands: slot (code & 0xF0) >> 4; only 0x90F0 is registered (SKSOUND
//         0xDD4); its block word0 >> 24 selects SOUND 0 / HSYNTH 1 / SESQ 4 (SKSOUND 0xD30), an
//         unregistered module answers -310.
//     The constants stay the fallback when no module file can be read (no disc, a test rig).
#pragma once

#include <array>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "iop_core.h"

namespace p3fes::hle {
class DiscSource;
}

namespace p3fes::hle::sif::iop {
class IopKernel;
class LibsdHle;
}  // namespace p3fes::hle::sif::iop

namespace p3fes::audio {
class Spu2Mixer;
class Spu2Voices;
}  // namespace p3fes::audio

namespace p3fes::hle::sif::detail {

// PCSX2's placement of the six module images (extracted/_pcsx2/dorm/iopMemory.bin, the ModuleInfo
// chain: SDRDRV id 32 ... SKSESQ id 39; each image 0x30 bytes after its 256-byte-aligned block).
struct SkModulePlacement {
    const char* file;
    u32 base;
};
inline constexpr SkModulePlacement kSkModulesPcsx2[] = {
    {"SDRDRV.IRX", 0x00083230u},  {"MODHSYN.IRX", 0x00084F30u}, {"MODSESQ.IRX", 0x00095A30u},
    {"SKSOUND.IRX", 0x00098630u}, {"SKHSYNTH.IRX", 0x0009A030u}, {"SKSESQ.IRX", 0x000B0730u},
};
// Kernel-owned memory (stacks, argv, the modules' work areas) per layout: between/after the images in
// Pcsx2 (below the game's heap at 0xBD400, then the top of RAM), the top of the legacy heap otherwise.
inline constexpr u32 kIopHeapBeginPcsx2 = 0x000BD400u;
inline constexpr u32 kIopHeapEndPcsx2 = 0x001F0000u;
inline constexpr std::pair<u32, u32> kKernelRangesPcsx2[] = {{0x0009B900u, 0x000B0700u}, {0x000B2200u, 0x000BD400u}, {0x001F0000u, 0x001FF000u}};
inline constexpr std::pair<u32, u32> kKernelRangesLegacy[] = {{0x001A0000u, 0x001F0000u}};

class SdrdrvServer final : public RpcServer {
public:
    static constexpr s32 kErrUnknown = -310;  // 0xFFFFFECA (SKSOUND 0xD5C, SKHSYNTH 0x1340, ...)
    static constexpr s32 kErrNoSlot = -101;   // 0xFFFFFF9B
    static constexpr s32 kErrNotBound = -201; // 0xFFFFFF37
    static constexpr u32 kHsynthEntries = 8;  // SKHSYNTH maxentry default (IRX 0xD0, no argument given)
    static constexpr u32 kPorts = 16;         // SKSOUND port count (inf: sksound export 8 not traced)
    static constexpr u32 kSesqEntries = 16;   // SKSESQ "maxentry=16" (kwlnInitPS2Systems arg 0x67872C)
    static constexpr u32 kSesqTracks = 16;    // SKSESQ "maxtrack=16" (0x678720); MODSESQ's own mask has 32 (19 §5)
    static constexpr u32 kSid = 0x80000701u;

    explicit SdrdrvServer(DiscSource* disc);
    ~SdrdrvServer() override;

    std::string_view name() const override { return "sdrdrv"; }
    bool call(IopCore& core, const RpcRequest& req, RpcReply& reply, u32 ticket) override;
    void tick(IopCore& core, u64 now, const Timebase& tb) override;
    void reboot() override;
    void state(StateIo& io, IopCore& core) override;

    // ---- modules (IopCore) -----------------------------------------------------------------------------
    // loadfile asked for `path`: when it names one of the six SK modules and sk_mode is Modules, the file is
    // read (IopConfig::module_source, else the disc) and loaded; returns the module's start result.
    std::optional<s32> on_module_load(IopCore& core, std::string_view path, std::string_view args);
    void set_mixer(audio::Spu2Mixer* m) { mixer_ = m; }
    bool modules_active() const { return routed_; }
    audio::Spu2Voices* voices();
    SkStats sk_stats() const;

    // ---- inspection (tests) ------------------------------------------------------------------------
    std::span<const u8> spu2_ram() const;
    u64 spu2_bytes_sent() const { return spu2_sent_; }
    u32 param(u32 reg) const {
        auto it = params_.find(reg);
        return it == params_.end() ? 0u : it->second;
    }
    const iop::IopKernel* kernel() const { return kernel_.get(); }

private:
    // ---- constants model ------------------------------------------------------------------------------
    std::map<u32, u32> params_;      // libsd register shadow (code | reg -> value)
    std::vector<u8> spu2_;           // SPU2 RAM shadow, allocated on the first SOUND_Send
    u64 spu2_sent_ = 0;
    std::array<bool, kHsynthEntries> hs_entry_{};
    std::array<u8, kPorts> port_{};  // bit 1 HSYNTH, bit 0 SESQ
    std::array<bool, kSesqEntries> sq_entry_{};
    std::array<bool, kSesqTracks> track_{};
    u32 track_next_ = 0;             // round-robin when every track is busy (inf)

    s32 libsd(IopCore& core, const RpcRequest& req, SoundRequest& r);
    s32 sk(IopCore& core, const RpcRequest& req, SoundRequest& r);
    s32 sk_sound(IopCore& core, const SoundRequest& r);
    s32 sk_hsynth(const SoundRequest& r);
    s32 sk_sesq(const SoundRequest& r);

    // ---- interpreted modules ----------------------------------------------------------------------------
    DiscSource* disc_ = nullptr;
    IopCore* core_ = nullptr;
    std::unique_ptr<iop::LibsdHle> sd_;
    std::unique_ptr<iop::IopKernel> kernel_;
    audio::Spu2Mixer* mixer_ = nullptr;
    bool routed_ = false;            // SDRDRV registered 0x80000701: requests go to the handler
    bool module_failed_ = false;     // a load/run problem: constants from here on (logged once)
    u32 modules_loaded_ = 0;
    u64 rpc_routed_ = 0, rpc_pending_ = 0;
    struct Pending {
        bool active = false;
        u32 ticket = 0;
        u32 recv_size = 0;
        SoundRequest log;
    } pending_;

    void ensure_kernel(IopCore& core);
    std::optional<std::vector<u8>> read_module(IopCore& core, std::string_view file_name);
    void advance(IopCore& core, u64 now);
    RpcReply reply_from(u32 result_ptr, u32 recv_size) const;
    void finish_pending(IopCore& core, u32 result_ptr);
    void fill_log(const RpcRequest& req, SoundRequest& r) const;
};

std::unique_ptr<SdrdrvServer> make_sdrdrv_server(DiscSource* disc);

}  // namespace p3fes::hle::sif::detail
