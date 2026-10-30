// SDRDRV + Standard Kit sound modules (srv_sdr.h; docs/ANALYSIS/16_iop_audio_modules.md §9, ADR-0014).
// sceSdRemote 0x5129C0 (EE, obs): rpc number = libsd function code; default: send the 64-byte args
// block at 0x96E000 (word0 = its own address, words 1..6 = args), receive 16 into it; result = word0.
// Codes 0x9000..0x90F0 send `arg2` bytes from `arg1` instead (0x512C64): the SK wrappers
// 0x51DB00..0x51E0DC send a 64-byte block {module << 24, function, args...} with code 0x90F0.
#include "srv_sdr.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <fstream>

#include "iop_kernel_hle.h"
#include "libsd_hle.h"
#include "p3fes/audio/spu2_voice.h"
#include "p3fes/hle/disc_source.h"

namespace p3fes::hle::sif::detail {
namespace {

constexpr u32 kSkCommand = 0x90F0u;
constexpr u32 kModSound = 0, kModHsynth = 1, kModSesq = 4;
constexpr const char* kSkModuleFiles[] = {"SDRDRV.IRX", "MODHSYN.IRX", "MODSESQ.IRX", "SKSOUND.IRX", "SKHSYNTH.IRX", "SKSESQ.IRX"};

template <std::size_t N>
s32 first_free(const std::array<bool, N>& a) {
    for (std::size_t i = 0; i < N; ++i)
        if (!a[i]) return static_cast<s32>(i);
    return -1;
}
template <std::size_t N>
s32 first_zero(const std::array<u8, N>& a) {
    for (std::size_t i = 0; i < N; ++i)
        if (a[i] == 0) return static_cast<s32>(i);
    return -1;
}
// Port state bits as SKSOUND keeps them (sksound export 9/10): bit 1 = HSYNTH bound (SKHSYNTH 0xC38
// ORs 2), bit 0 = SESQ bound (SKSESQ 0xAF4 ORs 1).
constexpr u8 kPortHsynth = 2, kPortSesq = 1;

// "cdrom0:\LIB31\SDRDRV.IRX;1" -> "SDRDRV.IRX"
std::string file_name_of(std::string_view path) {
    std::string n(path);
    if (const auto slash = n.find_last_of("\\/"); slash != std::string::npos) n = n.substr(slash + 1);
    if (const auto semi = n.find(';'); semi != std::string::npos) n = n.substr(0, semi);
    for (char& ch : n) ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
    return n;
}
bool is_sk_module(const std::string& name) {
    for (const char* f : kSkModuleFiles)
        if (name == f) return true;
    return false;
}

}  // namespace

std::unique_ptr<SdrdrvServer> make_sdrdrv_server(DiscSource* disc) { return std::make_unique<SdrdrvServer>(disc); }

SdrdrvServer::SdrdrvServer(DiscSource* disc) : disc_(disc) {}
SdrdrvServer::~SdrdrvServer() = default;

void SdrdrvServer::reboot() {
    params_.clear();
    spu2_.clear();
    spu2_sent_ = 0;
    hs_entry_.fill(false);
    port_.fill(0);
    sq_entry_.fill(false);
    track_.fill(false);
    track_next_ = 0;
    // The IOP heap was reset by the core: the module images, threads and timers are gone with it. The voice
    // model goes too (a reboot silences the SPU2 as sceSdInit would); the mixer keeps its timeline.
    if (mixer_) mixer_->set_voices(nullptr);
    kernel_.reset();
    sd_.reset();
    routed_ = false;
    module_failed_ = false;
    modules_loaded_ = 0;
    pending_ = Pending{};
}

std::span<const u8> SdrdrvServer::spu2_ram() const {
    if (sd_) return sd_->spu_ram();
    return spu2_;
}

audio::Spu2Voices* SdrdrvServer::voices() { return sd_ ? &sd_->voices() : nullptr; }

// ---- the interpreted modules ---------------------------------------------------------------------------

void SdrdrvServer::ensure_kernel(IopCore& core) {
    if (kernel_) return;
    core_ = &core;
    sd_ = std::make_unique<iop::LibsdHle>();
    kernel_ = std::make_unique<iop::IopKernel>(core.ram(), *sd_, [&core](std::string_view s) { core.log(s); });
    std::vector<std::pair<u32, u32>> ranges;
    if (core.config().iop_layout == IopLayout::Pcsx2) {
        for (const auto& r : kKernelRangesPcsx2) ranges.push_back(r);
        for (const SkModulePlacement& p : kSkModulesPcsx2) kernel_->set_fixed_base(p.file, p.base);
    } else {
        for (const auto& r : kKernelRangesLegacy) ranges.push_back(r);
    }
    kernel_->set_alloc_ranges(std::move(ranges));
    kernel_->set_time_hook([this](u64 ee) {
        if (mixer_) mixer_->advance_voices(audio::frames_at_cycles(ee));
    });
    sd_->on_key_on = [this](const audio::Spu2KeyOn& k) {
        SoundRequest ev;
        ev.sid = 0;
        ev.fno = 1;
        ev.args = {k.core, k.voice, k.ssa, k.lsax, k.pitch, k.adsr1, k.adsr2, (static_cast<u32>(k.voll) << 16) | k.volr};
        ev.cycle = kernel_->now();
        ev.result = static_cast<s32>(audio::frames_at_cycles(kernel_->now()));
        core_->record_event(ev);
    };
    sd_->on_key_off = [this](u32 c, u32 v) {
        SoundRequest ev;
        ev.sid = 0;
        ev.fno = 2;
        ev.args = {c, v, 0, 0, 0, 0, 0, 0};
        ev.cycle = kernel_->now();
        ev.result = static_cast<s32>(audio::frames_at_cycles(kernel_->now()));
        core_->record_event(ev);
    };
    // Core-level register writes that change a value (the volume law, MMIX, effect attributes, sceSdInit):
    // sid 0 / fno 3 "CORE" lines of --sound-log: core, kind, code, value, old (libsd_hle.h on_core_write).
    sd_->on_core_write = [this](u32 c, u32 kind, u32 code, u32 value, u32 old) {
        SoundRequest ev;
        ev.sid = 0;
        ev.fno = 3;
        ev.args = {c, kind, code, value, old, 0, 0, 0};
        ev.cycle = kernel_->now();
        ev.result = static_cast<s32>(audio::frames_at_cycles(kernel_->now()));
        core_->record_event(ev);
    };
    sd_->voices().set_interpolation(core.config().spu2_gaussian ? audio::Interpolation::Gaussian : audio::Interpolation::Linear);
    if (mixer_) mixer_->set_voices(&sd_->voices());
}

std::optional<std::vector<u8>> SdrdrvServer::read_module(IopCore& core, std::string_view file_name) {
    if (core.config().module_source) return core.config().module_source(file_name);
    if (!disc_) return std::nullopt;
    const std::string path = "\\LIB31\\" + std::string(file_name) + ";1";
    if (auto found = disc_->find_file(path); found && found.value()) {
        const DiscFile& f = *found.value();
        std::vector<u8> bytes(static_cast<std::size_t>(f.sectors()) * kSectorSize);
        const auto rd = disc_->read_sectors(f.lsn, f.sectors(), std::as_writable_bytes(std::span(bytes)));
        if (rd) {
            bytes.resize(f.size);
            return bytes;
        }
    }
    // The extracted-volumes source does not cover LIB31 (disc_source.h): read the extracted file itself.
    if (disc_->identity().kind == DiscSourceKind::ExtractedVolumes) {
        const std::filesystem::path p = disc_->identity().origin / "LIB31" / std::string(file_name);
        std::ifstream in(p, std::ios::binary);
        if (in) {
            std::vector<u8> bytes((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
            if (!bytes.empty()) return bytes;
        }
    }
    return std::nullopt;
}

std::optional<s32> SdrdrvServer::on_module_load(IopCore& core, std::string_view path, std::string_view args) {
    if (core.config().sk_mode != SkMode::Modules || module_failed_) return std::nullopt;
    const std::string name = file_name_of(path);
    if (!is_sk_module(name)) return std::nullopt;
    ensure_kernel(core);
    kernel_->advance_to(core.now());  // the module starts at virtual `now` (its timers and GetSystemTime)
    const auto bytes = read_module(core, name);
    if (!bytes) {
        core.log("[iop] SK modules: " + name + " not readable from the disc; SDRDRV keeps the constant replies");
        module_failed_ = true;
        return std::nullopt;
    }
    std::string err;
    const auto r = kernel_->load_module(*bytes, path, args, err);
    if (!r) {
        core.log("[iop] SK modules: loading " + name + " failed (" + err + "); SDRDRV keeps the constant replies");
        module_failed_ = true;
        routed_ = false;
        return std::nullopt;
    }
    ++modules_loaded_;
    core.log("[iop] SK modules: " + name + " at " + hex32(r->info.base) + ", start returned " + std::to_string(r->start_result) + " after " +
             std::to_string(r->start_instructions) + " instructions" + (r->resident ? "" : " (not resident, freed)"));
    if (!routed_ && kernel_->has_rpc_server(kSid)) {
        const iop::RpcServerRecord* rec = kernel_->rpc_server(kSid);
        core.rebind_server(kSid, rec->sd, rec->buf, 0x100u);
        routed_ = true;
        core.log("[iop] SDRDRV answers 0x80000701 from the module: handler " + hex32(rec->func) + ", sd " + hex32(rec->sd) + ", buffer " + hex32(rec->buf));
    }
    return r->start_result;
}

void SdrdrvServer::advance(IopCore& core, u64 now) {
    if (!kernel_) return;
    kernel_->advance_to(now);
    if (!kernel_->fault().empty() && routed_) {
        core.log("[iop] SK modules: kernel fault (" + kernel_->fault() + "); SDRDRV falls back to the constant replies");
        routed_ = false;
        module_failed_ = true;
    }
}

RpcReply SdrdrvServer::reply_from(u32 result_ptr, u32 recv_size) const {
    RpcReply reply;
    const u32 n = std::max<u32>(recv_size, 16u);
    reply.rdata.assign(n, 0);
    if (core_ && result_ptr) {
        if (const u8* p = core_->ram().at(result_ptr, n)) std::memcpy(reply.rdata.data(), p, n);
    }
    return reply;
}

void SdrdrvServer::finish_pending(IopCore& core, u32 result_ptr) {
    RpcReply reply = reply_from(result_ptr, pending_.recv_size);
    SoundRequest r = pending_.log;
    r.result = static_cast<s32>(load32(reply.rdata, 0));
    core.record_sound(r);
    const u32 ticket = pending_.ticket;
    pending_ = Pending{};
    ++rpc_routed_;
    core.complete(ticket, std::move(reply));
}

void SdrdrvServer::tick(IopCore& core, u64 now, const Timebase& /*tb*/) {
    if (!kernel_) return;
    advance(core, now);
    if (pending_.active)
        if (const auto res = kernel_->rpc_poll()) finish_pending(core, *res);
}

void SdrdrvServer::fill_log(const RpcRequest& req, SoundRequest& r) const {
    r.sid = req.sid;
    r.fno = req.fno;
    const u32 code = req.fno & 0xFFF0u;
    if (code == kSkCommand) {
        r.sk_module = req_word(req, 0);
        r.sk_function = req_word(req, 4);
        for (std::size_t i = 0; i < r.args.size(); ++i) r.args[i] = req_word(req, 8 + 4 * i);
    } else {
        for (std::size_t i = 0; i < r.args.size(); ++i) r.args[i] = req_word(req, 4 + 4 * i);
    }
}

SkStats SdrdrvServer::sk_stats() const {
    SkStats s;
    s.modules = routed_;
    s.modules_loaded = modules_loaded_;
    s.rpc_routed = rpc_routed_;
    s.rpc_pending = rpc_pending_;
    if (kernel_) {
        s.tick_runs = kernel_->timer_handler_runs();
        s.instructions = kernel_->instructions();
        s.fault = kernel_->fault();
    }
    if (sd_) {
        s.key_ons = sd_->key_ons();
        s.key_offs = sd_->key_offs();
        s.key_offs_sounding = sd_->voices().key_offs_sounding();
        s.voices_active = sd_->voices().active_voices();
        s.voices_active_max = sd_->voices().active_voices_max();
        s.voice_longest_frames = sd_->voices().longest_voice_frames();
        s.volume_sweeps = sd_->voices().volume_sweeps();
        s.sd_inits = sd_->init_calls();
    }
    if (mixer_) {
        s.voice_frames = mixer_->voice_frames();
        s.first_voice_frame = mixer_->first_voice_frame();
        s.mix_passes = mixer_->passes_pushed();
        s.mix_passes_skipped = mixer_->passes_skipped();
        s.mix_stream_late = mixer_->stream_frames_late();
    }
    return s;
}

// ---- RPC ---------------------------------------------------------------------------------------------------

bool SdrdrvServer::call(IopCore& core, const RpcRequest& req, RpcReply& reply, u32 ticket) {
    SoundRequest r;
    fill_log(req, r);
    r.cycle = core.now();
    if (routed_ && kernel_) {
        advance(core, core.now());  // ticks due before this request run first
        if (routed_ && !pending_.active) {
            std::string err;
            const auto res = kernel_->rpc_dispatch(kSid, req.fno, req.data_iop, static_cast<u32>(req.data.size()), err);
            if (res) {
                reply = reply_from(*res, req.recv_size);
                r.result = static_cast<s32>(load32(reply.rdata, 0));
                ++rpc_routed_;
                core.record_sound(r);
                return true;
            }
            if (kernel_->rpc_pending()) {
                // The handler blocked (nothing on the SK path is expected to): the reply follows from tick().
                ++rpc_pending_;
                if (rpc_pending_ == 1) core.log("[iop] SDRDRV handler blocked for fno " + hex32(req.fno) + "; the reply is deferred to the next check point");
                pending_.active = true;
                pending_.ticket = ticket;
                pending_.recv_size = req.recv_size;
                pending_.log = r;
                return false;
            }
            core.log("[iop] SK modules: RPC dispatch failed (" + err + "); SDRDRV falls back to the constant replies");
            routed_ = false;
            module_failed_ = true;
        } else if (pending_.active) {
            core.log("[iop] SDRDRV: a request arrived while a handler is pending; answered with the constant model");
        }
    }

    // ---- the constant model -------------------------------------------------------------------------
    s32 result = 0;  // dword_14E0 = 0 on entry (SDRDRV 0x5A4)
    const u32 code = req.fno & 0xFFF0u;
    if (code >= 0x9000u && code <= 0x90F0u) {
        result = code == kSkCommand ? sk(core, req, r) : 0;  // unregistered user slots leave 0 (0xC5C)
        if (code != kSkCommand)
            core.note_unknown(UnknownEvent::Kind::Function, req.sid, req.fno, "SDRDRV user command slot not registered (answered 0)");
    } else {
        result = libsd(core, req, r);
    }
    r.result = result;
    core.record_sound(r);
    reply.rdata.assign(16, 0);  // &dword_14E0 (0xDAC): result, then three words of SDRDRV bss (inf 0)
    put_word(reply.rdata, 0, static_cast<u32>(result));
    return true;
}

s32 SdrdrvServer::libsd(IopCore& core, const RpcRequest& req, SoundRequest& r) {
    const u32 code = req.fno & 0xFFF0u;
    const u32 a1 = r.args[0], a2 = r.args[1];
    switch (code) {
    case 0x8000u:  // sceSdInit(arg1) (0x85C): libsd returns 0 on success (inf)
        params_.clear();
        return 0;
    case 0x8010u:  // sceSdSetParam(u16, u16) (0x878): void -> 0
        params_[0x10000u | (a1 & 0xFFFFu)] = a2 & 0xFFFFu;
        return 0;
    case 0x8020u:  // sceSdGetParam -> & 0xFFFF (0x8D8)
        return static_cast<s32>(param(0x10000u | (a1 & 0xFFFFu)) & 0xFFFFu);
    case 0x8030u:  // sceSdSetSwitch (0x890)
        params_[0x20000u | (a1 & 0xFFFFu)] = a2;
        return 0;
    case 0x8040u:  // sceSdGetSwitch (0x8EC)
        return static_cast<s32>(param(0x20000u | (a1 & 0xFFFFu)));
    case 0x8050u:  // sceSdSetAddr (0x8A8)
        params_[0x30000u | (a1 & 0xFFFFu)] = a2;
        return 0;
    case 0x8060u:  // sceSdGetAddr (0x908)
        return static_cast<s32>(param(0x30000u | (a1 & 0xFFFFu)));
    case 0x8070u:  // sceSdSetCoreAttr (0x8C0)
        params_[0x40000u | (a1 & 0xFFFFu)] = a2 & 0xFFFFu;
        return 0;
    case 0x8080u:  // sceSdGetCoreAttr -> & 0xFFFF (0x924)
        return static_cast<s32>(param(0x40000u | (a1 & 0xFFFFu)) & 0xFFFFu);
    case 0x8F10u:  // thread priorities (0xC24 -> export 4): 0 when both are valid (inf)
    case 0xE620u:  // callback thread create (0xC8C)
    case 0xE630u:  // callback thread delete (0xCEC)
        return 0;
    default:
        core.note_unknown(UnknownEvent::Kind::Function, req.sid, req.fno, "libsd function not modelled (answered 0)");
        return 0;
    }
}

s32 SdrdrvServer::sk(IopCore& core, const RpcRequest& /*req*/, SoundRequest& r) {
    const u32 module = (r.sk_module >> 24) & 0x7Fu;  // SKSOUND 0xD38: lbu 3(block) & 0x7F
    s32 result = kErrUnknown;
    switch (module) {
    case kModSound: result = sk_sound(core, r); break;
    case kModHsynth: result = sk_hsynth(r); break;
    case kModSesq: result = sk_sesq(r); break;
    default: break;  // dword_1750[module] == 0 -> -310 (0xD58)
    }
    if (result == kErrUnknown)
        core.note_unknown(UnknownEvent::Kind::Function, r.sid, (r.sk_module >> 16) | r.sk_function,
                          "SK module/function the IRX answers with -310");
    return result;
}

s32 SdrdrvServer::sk_sound(IopCore& core, const SoundRequest& r) {
    // SKSOUND 0xE20: function 0/1 -> 0, 2 Control (0xA64), 3 status (0xD08), 10 Send (export 18).
    switch (r.sk_function) {
    case 0:
    case 1:
        return 0;
    case 2:  // SOUND_Control(arg0, command, ...)
        switch (r.args[1]) {
        case 0x80u: params_[0x10000u | 0x981u] = (r.args[2] * 129u) & 0x7FFFu;  // master volume L/R (0xB24)
                    params_[0x10000u | 0xA81u] = (r.args[3] * 129u) & 0x7FFFu;
                    return 0;
        case 0x81u:  // core attribute 6/7 (0xB00)
        case 0x82u:  // core attributes 2/3 (0xB68)
        case 0x84u:  // effect depth (0xBF8: SetParam 0xB80/0xC80/0xB81/0xC81)
        case 0x8Fu:  // core attribute 0xA (0xCA0)
            return 0;
        case 0x83u:  // effect attributes, both cores (0xB94): sceSdSetEffectAttr result (inf 0)
            return 0;
        default:
            return kErrUnknown;  // includes 1/2 (0xCC0/0xCD8: not traced, no game caller)
        }
    case 3:  // 0xD08: arg1 != 0 -> -310, else a status word (inf 0)
        return r.args[1] != 0 ? kErrUnknown : 0;
    case 10: {  // SOUND_Send(ch, iop, spu, size) -> sceSdVoiceTrans(ch, 0, iop, spu, size) (0xA00)
        const u32 iop = r.args[1], spu = r.args[2], size = r.args[3];
        if (spu2_.empty()) spu2_.assign(2u * 1024u * 1024u, 0);
        const u8* src = core.ram().at(iop, size);
        if (src && static_cast<u64>(spu & 0x1FFFFFu) + size <= spu2_.size()) {
            std::memcpy(spu2_.data() + (spu & 0x1FFFFFu), src, size);
            spu2_sent_ += size;
        }
        return static_cast<s32>(size);  // inf: libsd returns the transfer size (ps2sdk voice.c agrees)
    }
    default:
        return kErrUnknown;
    }
}

s32 SdrdrvServer::sk_hsynth(const SoundRequest& r) {
    // SKHSYNTH 0x1310: 0 Bind (export 7, 0x820), 1 Unbind (export 8), 2 export 9, 3 0x119C.
    const s32 id = static_cast<s32>(r.args[1]);
    switch (r.sk_function) {
    case 0:
        if (r.args[0] >= 1 && r.args[0] <= 3) {  // bank entry: first free (0x8C8) or the given id
            const s32 e = id == -1 ? first_free(hs_entry_) : id;
            if (e < 0 || e >= static_cast<s32>(kHsynthEntries)) return kErrNoSlot;
            hs_entry_[static_cast<std::size_t>(e)] = true;
            return e;
        }
        if (r.args[0] == 5) {  // port <- entry (0xACC): first port with no binding (& 3 == 0)
            const s32 p = id == -1 ? first_zero(port_) : id;
            if (p < 0 || p >= static_cast<s32>(kPorts)) return kErrNoSlot;
            const u32 entry = r.args[2];
            if (entry >= kHsynthEntries) return kErrNoSlot;
            if (!hs_entry_[entry]) return kErrNotBound;  // entry flags & 3 must be 3 (0xB98)
            port_[static_cast<std::size_t>(p)] |= kPortHsynth;
            return p;
        }
        return kErrUnknown;
    case 1:  // Unbind(type, id) (inf: frees and returns 0)
        if (r.args[0] >= 1 && r.args[0] <= 3 && static_cast<u32>(id) < kHsynthEntries) hs_entry_[static_cast<u32>(id)] = false;
        if (r.args[0] == 5 && static_cast<u32>(id) < kPorts) port_[static_cast<u32>(id)] &= static_cast<u8>(~kPortHsynth);
        return 0;
    case 2:
    case 3:
        return 0;  // inf: not traced, no game caller
    default:
        return kErrUnknown;
    }
}

s32 SdrdrvServer::sk_sesq(const SoundRequest& r) {
    // SKSESQ: 0 Bind (export 5, 0x770), 1 Unbind (export 6), 2 Control (export 7, 0xCFC), 3 Status.
    const s32 id = static_cast<s32>(r.args[1]);
    switch (r.sk_function) {
    case 0:
        if (r.args[0] == 0 || r.args[0] == 10) {  // sequence entry: first free (0x818) or the given id
            const s32 e = id == -1 ? first_free(sq_entry_) : id;
            if (e < 0 || e >= static_cast<s32>(kSesqEntries)) return kErrNoSlot;
            sq_entry_[static_cast<std::size_t>(e)] = true;
            return e;
        }
        if (r.args[0] == 5) {  // port <- entry: returns the port (0xA88: s2 = s3)
            const s32 p = id == -1 ? first_zero(port_) : id;
            if (p < 0 || p >= static_cast<s32>(kPorts)) return kErrNoSlot;
            if (port_[static_cast<std::size_t>(p)] & kPortSesq) return -202;  // 0x8F8: already bound
            const u32 entry = r.args[2];
            if (entry >= kSesqEntries) return kErrNoSlot;
            if (!sq_entry_[entry]) return kErrNotBound;  // 0x94C
            port_[static_cast<std::size_t>(p)] |= kPortSesq;
            return p;
        }
        return kErrUnknown;
    case 1:  // Unbind(type, id)
        if ((r.args[0] == 0 || r.args[0] == 10) && static_cast<u32>(id) < kSesqEntries) sq_entry_[static_cast<u32>(id)] = false;
        if (r.args[0] == 5 && static_cast<u32>(id) < kPorts) port_[static_cast<u32>(id)] &= static_cast<u8>(~kPortSesq);
        return 0;
    case 2: {  // Control(port, command, type 10, ...): 0/7 play -> track (modsesq), 2 stop -> 0
        const u32 port = r.args[0], cmd = r.args[1];
        if (port >= kPorts) return kErrNoSlot;
        if (r.args[2] != 10) return 0;  // 0xE18 / 0xF1C: type other than 10 returns 0
        if (cmd == 0 || cmd == 7) {
            // The constant model's allocator: first free, round-robin when full. MODSESQ's real one (round-robin
            // from the last track + 1 over a 32-bit mask, 19 §1.4) answers in Modules mode.
            s32 t = first_free(track_);
            if (t < 0) {
                t = static_cast<s32>(track_next_ % kSesqTracks);
                ++track_next_;
            }
            track_[static_cast<std::size_t>(t)] = true;
            return t;
        }
        if (cmd == 2) {
            const u32 h = r.args[3];
            if (h < kSesqTracks) track_[h] = false;
            return 0;
        }
        return kErrUnknown;
    }
    case 3:
        return 0;  // Status (export 8): inf 0, result ignored by the game (0x10DB20)
    default:
        return kErrUnknown;
    }
}

}  // namespace p3fes::hle::sif::detail
