#include "game_host.h"

#include <windows.h>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <map>
#include <system_error>
#include <utility>

#include "elf_image.h"
#include "host_backtrace.h"
#include "host_watch.h"
#include "input.h"
#include "p3fes/gs/gs_output.h"
#include "pc_text.h"
#include "p3fes/hle/memcard/iop_slot.h"
#include "p3fes/hle/memcard/source.h"
#include "p3fes/pinned.h"
#include "p3fes/rt/rt_adapter.h"
#include "p3fes_recomp_rt.h"

namespace p3fes::app {

namespace {

// Guest globals read for stop conditions and capture.json (symbols/p3fes.sym; tools/ours/pcsx2/capture.py).
constexpr std::uint32_t kSkyFrameCount = 0x7CEA78u;     // g_skyFrameCount
constexpr std::uint32_t kRwFlipPending = 0x7CE9ACu;     // g_rwDMAFlipPending (u8)
constexpr std::uint32_t kRwFlipBuf = 0x7CE9A8u;         // g_rwDMAFlipBuf (u8)
constexpr std::uint32_t kAdxVsyncCnt = 0x787568u;       // adxt_vsync_cnt
constexpr std::uint32_t kKwlnFrame = 0x7CE10Cu;         // kwln frame counter (capture.py "kwln_frame")
constexpr std::uint32_t kKwlnFirstFrame = 0x7CC134u;    // g_kwlnFirstFrame
constexpr std::uint32_t kEntry = 0x00100008u;           // start (INVENTORY.md, contract §1.1)
// Movie markers (MarkerEdge): game flag 5127 in the flag array at 0x83A21C (setter sub_16F1F0), and the movie
// task's Sofdec player pointer at 0x7CDF10 (gp - 0x4DE0).
constexpr std::uint32_t kMovieFlagWord = 0x83A21Cu + (5127u >> 5) * 4u;
constexpr std::uint32_t kMovieFlagBit = 5127u & 31u;
constexpr std::uint32_t kMovieObject = 0x7CDF10u;

const char* status_name(std::uint32_t s) {
    switch (s) {
    case 0x01: return "RUN";
    case 0x02: return "READY";
    case 0x04: return "WAIT";
    case 0x08: return "SUSPEND";
    case 0x0C: return "WAITSUSPEND";
    case 0x10: return "DORMANT";
    default: return "?";
    }
}

std::string hexs(std::uint64_t v, int w = 8) {
    char b[32];
    std::snprintf(b, sizeof b, "0x%0*llX", w, static_cast<unsigned long long>(v));
    return b;
}

std::uint64_t qpc() {
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);
    return static_cast<std::uint64_t>(t.QuadPart);
}

} // namespace

// ---- tracing wrapper (only installed with --trace-syscalls / --trace-hw) -------------------------------
//
// Forwards everything to the kernel's RtHooks and logs the first N occurrences per kind. Costs one more
// indirect call per check point, so it is not installed otherwise.
class TracingHooks final : public RtHooks, public hle::HwBus {
public:
    TracingHooks(RtHooks& inner, const GuestSymbols& syms, unsigned n_sys, unsigned n_hw,
                 std::function<void(std::string_view)> out)
        : in_(inner), bus_(inner.bus()), syms_(syms), n_sys_(n_sys), n_hw_(n_hw), out_(std::move(out)) {}

    void syscall(EEContext& ctx, u32 pc) override {
        const s32 num = static_cast<s32>(ctx.gpr[GPR_V1].u32[0]);
        const bool log_it = n_sys_ && ++sys_count_[num] <= n_sys_;
        char pre[384] = {};
        if (log_it) {
            const u32 slot = static_cast<u32>(num < 0 ? -num : num);
            std::snprintf(pre, sizeof pre, "syscall %s0x%02X %-22s @%s a0=%08X a1=%08X a2=%08X a3=%08X", num < 0 ? "-" : " ",
                          slot, hle::syscall_name(slot), syms_.describe(pc).c_str(), ctx.gpr[GPR_A0].u32[0],
                          ctx.gpr[GPR_A1].u32[0], ctx.gpr[GPR_A2].u32[0], ctx.gpr[GPR_A3].u32[0]);
        }
        const u64 c0 = ctx.cycles;
        in_.syscall(ctx, pc);
        if (log_it) {
            char line[512];
            std::snprintf(line, sizeof line, "[%12llu] %s -> v0=%08X", static_cast<unsigned long long>(c0), pre,
                          ctx.gpr[GPR_V0].u32[0]);
            out_(line);
        }
    }
    void check_events(EEContext& ctx) override { in_.check_events(ctx); }
    const u64* deadline_ptr() const override { return in_.deadline_ptr(); }
    hle::HwBus& bus() override { return n_hw_ ? static_cast<hle::HwBus&>(*this) : bus_; }
    void trap(EEContext& ctx, u32 pc, u32 kind, u32 code) override { in_.trap(ctx, pc, kind, code); }
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* what) override { in_.fatal(ctx, pc, what); }
    void vu_control_write(EEContext& ctx, u32 reg, u32 value) override {
        if (n_hw_) hw_log(0xC0000000u | reg, 32, true, value);
        in_.vu_control_write(ctx, reg, value);
    }

    // HwBus: guest accesses only (devices keep the kernel's bus).
    void map(u32 b, u32 e, hle::HwDevice* d) override { bus_.map(b, e, d); }
    void set_dma_handler(unsigned ch, hle::DmaChannelHandler* h) override { bus_.set_dma_handler(ch, h); }
    void raise_intc(unsigned cause) override { bus_.raise_intc(cause); }
    void dma_complete(unsigned ch) override { bus_.dma_complete(ch); }
    const hle::Timebase& time() const override { return bus_.time(); }
    u32 read32(u32 pa) override { const u32 v = bus_.read32(pa); hw_log(pa, 32, false, v); return v; }
    void write32(u32 pa, u32 v) override { hw_log(pa, 32, true, v); bus_.write32(pa, v); }
    u64 read64(u32 pa) override { const u64 v = bus_.read64(pa); hw_log(pa, 64, false, v); return v; }
    void write64(u32 pa, u64 v) override { hw_log(pa, 64, true, v); bus_.write64(pa, v); }
    u128 read128(u32 pa) override { const u128 v = bus_.read128(pa); hw_log(pa, 128, false, v.lo()); return v; }
    void write128(u32 pa, const u128& v) override { hw_log(pa, 128, true, v.lo()); bus_.write128(pa, v); }
    u8 read8(u32 pa) override { const u8 v = bus_.read8(pa); hw_log(pa, 8, false, v); return v; }
    u16 read16(u32 pa) override { const u16 v = bus_.read16(pa); hw_log(pa, 16, false, v); return v; }
    void write8(u32 pa, u8 v) override { hw_log(pa, 8, true, v); bus_.write8(pa, v); }
    void write16(u32 pa, u16 v) override { hw_log(pa, 16, true, v); bus_.write16(pa, v); }

private:
    void hw_log(u32 pa, u32 width, bool write, u64 v) {
        const u64 key = (static_cast<u64>(pa) << 1) | (write ? 1u : 0u);
        if (++hw_count_[key] > n_hw_) return;
        std::string where;
        const auto bt = guest_backtrace(2);
        for (const GuestFrame& f : bt) where += (where.empty() ? "" : " <- ") + syms_.describe(f.va);
        char line[512];
        std::snprintf(line, sizeof line, "[%12llu] hw %s%-3u %s %s %s  in %s", static_cast<unsigned long long>(bus_.time().cycles),
                      write ? "W" : "R", width, (pa >> 30) == 3 ? ("vi" + std::to_string(pa & 31)).c_str() : hexs(pa).c_str(),
                      write ? "<-" : "->", hexs(v, width >= 64 ? 16 : 8).c_str(), where.empty() ? "?" : where.c_str());
        out_(line);
    }

    RtHooks& in_;
    hle::HwBus& bus_;
    const GuestSymbols& syms_;
    unsigned n_sys_, n_hw_;
    std::function<void(std::string_view)> out_;
    std::map<s32, unsigned> sys_count_;
    std::map<u64, unsigned> hw_count_;
};

const char* to_string(StopReason r) {
    switch (r) {
    case StopReason::None: return "none";
    case StopReason::Flip: return "flip";
    case StopReason::Vblank: return "vblank";
    case StopReason::Cycles: return "cycles";
    case StopReason::Sky: return "sky";
    case StopReason::EveryVblank: return "every-vblank";
    case StopReason::MainExited: return "main-exited";
    case StopReason::Fatal: return "fatal";
    }
    return "?";
}

void GameHost::CtxDelete::operator()(EEContext* c) const noexcept {
    if (pinned::owns(c)) c->~EEContext();
    else delete c;
}

GameHost::GameHost() = default;

GameHost::~GameHost() {
    disarm_write_watch();
    if (gs_ && (gs_probe_ || gpu_rec_)) gs_->core().set_draw_observer(nullptr);
    if (gs_ && native_) {
        gs_->vif1().set_run_hook(nullptr);
        gs_->vu1().set_sink(gs_.get());
    }
    native_.reset();
    gpu_rec_.reset();
    gs_probe_.reset();
    set_hooks(nullptr);
    rt::bind_context(nullptr);
    tracing_.reset();
    sif_.reset();
    if (sound_log_) std::fclose(sound_log_);
    sound_log_ = nullptr;
    audio_.reset();  // after the IOP that pushes into it
    disc_.reset();
    ipu_.reset();
    gs_.reset();
    kernel_.reset();  // on the host fiber (L4)
}

void GameHost::log(std::string_view s) const {
    std::fwrite(s.data(), 1, s.size(), stderr);
    std::fputc('\n', stderr);
}

double GameHost::wall_seconds() const {
    LARGE_INTEGER f;
    QueryPerformanceFrequency(&f);
    return static_cast<double>(wall_ticks_) / static_cast<double>(f.QuadPart);
}

bool GameHost::load_elf(std::string& error) {
    recomp::ElfImage elf;
    const std::string path = cfg_.elf.string();
    const recomp::ElfImage::LoadResult r = elf.load(path.c_str());
    if (r.error) {
        error = "ELF " + path + ": " + r.error + " (sha256 " + r.sha256_hex + ")";
        return false;
    }
    elf_sha256_ = r.sha256_hex;
    if (elf.entry() != kEntry) {
        error = "ELF entry " + hexs(elf.entry()) + " is not start 0x00100008";
        return false;
    }
    u8* ram = mem_->main_ram();
    for (const recomp::ElfSegment& s : elf.segments()) {
        if (s.memsz == 0) continue;
        const std::uint32_t pa = EEMemory::to_physical(s.vaddr);
        if (pa >= EEMemory::kMainRamSize || s.memsz > EEMemory::kMainRamSize - pa) {
            error = "ELF segment " + hexs(s.vaddr) + "+" + hexs(s.memsz) + " is outside main RAM";
            return false;
        }
        const std::uint8_t* src = s.filesz ? elf.bytes_at(s.vaddr, s.filesz) : nullptr;
        if (s.filesz && !src) {
            error = "ELF segment " + hexs(s.vaddr) + " has no file bytes";
            return false;
        }
        if (s.filesz) std::memcpy(ram + pa, src, s.filesz);
        std::memset(ram + pa + s.filesz, 0, s.memsz - s.filesz);  // .bss beyond the file (none in this ELF)
        if (s.filesz && elf_image_bytes_ == 0) {  // the program segment (code + data, the ROFS tables in it)
            elf_image_va_ = s.vaddr;
            elf_image_bytes_ = s.filesz;
        }
    }
    return true;
}

void GameHost::apply_pc_text() {
    if (!cfg_.pc_text || elf_image_bytes_ == 0) return;
    u8* ram = mem_->main_ram() + EEMemory::to_physical(elf_image_va_);
    const pc_text::Result r = pc_text::apply(std::span<std::uint8_t>(ram, elf_image_bytes_), elf_image_va_);
    if (r.status == pc_text::Status::Mismatch)
        log("pc-text: " + std::string(pc_text::to_string(r.status)) + ": " + r.detail + "; the messages keep the disc's wording");
    else if (!cfg_.quiet)
        log("pc-text: memory-card messages in PC wording (" + std::to_string(r.entries) + " entries " + pc_text::to_string(r.status) + ")");
}

bool GameHost::patch_mods_tables(std::string& error) {
    u8* ram = mem_->main_ram() + EEMemory::to_physical(elf_image_va_);
    auto r = mods_->patch_rofs_tables(std::span<std::byte>(reinterpret_cast<std::byte*>(ram), elf_image_bytes_), elf_image_va_);
    if (!r) {
        error = "mods: " + std::string(formats::error_name(r.code())) + " " + r.detail();
        return false;
    }
    return true;
}

bool GameHost::reload_mods(std::string& error) {
    if (!mods_) {
        error = "mods: no --mods folder was given";
        return false;
    }
    auto r = mods_->reload();
    if (!r) {
        error = "mods: reload failed: " + std::string(formats::error_name(r.code())) + " " + r.detail();
        return false;
    }
    return patch_mods_tables(error);
}

bool GameHost::set_mods_enabled(bool on, std::string& error) {
    if (!mods_) {
        error = "mods: the overlay is off (start with --mods or HostConfig::mods_overlay)";
        return false;
    }
    const bool was = mods_->enabled();
    mods_->set_enabled(on);
    if (reload_mods(error)) return true;
    mods_->set_enabled(was);
    return false;
}

bool GameHost::set_mod_folders(std::vector<std::filesystem::path> folders, std::string& error) {
    if (!mods_) {
        error = "mods: the overlay is off (start with --mods or HostConfig::mods_overlay)";
        return false;
    }
    std::vector<std::filesystem::path> old = mods_->dirs();
    mods_->set_dirs(std::move(folders));
    if (reload_mods(error)) return true;
    mods_->set_dirs(std::move(old));
    return false;
}

const std::vector<hle::ModOverride>& GameHost::mod_overrides() const {
    static const std::vector<hle::ModOverride> none;
    return mods_ ? mods_->scan().overrides : none;
}

std::vector<std::string> GameHost::mod_files_read_since_reload() const {
    return mods_ ? mods_->files_read() : std::vector<std::string>{};
}

void GameHost::set_mod_read_callback(std::function<void(const std::string&)> f) {
    if (mods_) mods_->set_read_observer(std::move(f));
}

std::vector<std::string> GameHost::mods_stale_after_reload() const {
    return mods_ ? mods_->stale_after_reload() : std::vector<std::string>{};
}

bool GameHost::init(const HostConfig& cfg, std::string& error) {
    cfg_ = cfg;
    if (!cfg_.symbols.empty()) syms_.load(cfg_.symbols);

    // Machine states (runtime/STATE.md; dev-only builds, -DP3FES_MACHINE_STATES=ON): guest RAM, the EEContext and the
    // kernel object at fixed addresses, in this order, in every process (the frames on the guest fibers point into
    // them). Other builds use the normal allocator.
#if defined(P3FES_MACHINE_STATES)
    pinned::enable();
#endif
    mem_ = std::make_unique<EEMemory>();
    {
        void* p = pinned::alloc(sizeof(EEContext), alignof(EEContext));
        ctx_.reset(p ? new (p) EEContext() : new EEContext());
    }
    ctx_->memory = mem_.get();
    if (!load_elf(error)) return false;
    apply_pc_text();

    hle::KernelOptions ko;
    ko.fatal_sink = [this](const hle::FatalInfo& info) { on_fatal(info); };
    ko.log_sink = [this](std::string_view s) {
        if (!cfg_.quiet) log(std::string("[kernel] ").append(s));
    };
    kernel_ = std::make_unique<hle::Kernel>(*mem_, *ctx_, std::move(ko));

    gs_ = std::make_unique<gs::GsSystem>();
    gs_->attach(kernel_->bus());
    // PATH3 unmasked with channel 2 stalled on the mask (RW's texture sync packet: `MSKPATH3 off`, ~96 NOPs,
    // `MSKPATH3 on`, `FLUSHA`, then the TEX0 + draw): the upload must go through *now*, inside that window, as the
    // GIF would let it on hardware. Without this the DMAC's periodic retry ran it after the whole VIF1 chain, so
    // every draw of the frame preceded its texture (the title-screen bug, docs/INTEGRATION_LOG.md "Title fix").
    gs_->set_path3_ready_callback([this] { kernel_->retry_dma_now(2); });
    gs_->set_trap_handler([this](const gs::VifTrap& t) {
        char msg[256];
        std::snprintf(msg, sizeof msg, "GS/VIF1 trap: %s (VIFcode 0x%08X)", gs::to_string(t.kind), t.code);
        kernel_->hooks().fatal(*ctx_, ctx_->pc, msg);
    });
    gs_->core().set_reg_observer([this](u32 reg, u64 v) { observe_gs_reg(reg, v); });
    gs_->priv().set_flip_callback([this](const gs::FlipEvent& e) {
        flips_.push_back({e.count, e.vblank, ctx_->cycles, e.circuit, e.fbp, guest_u32(kSkyFrameCount), host_seconds()});
        if (gs_probe_) gs_probe_->on_flip(e);
        if (plan_.until_flip && e.count >= plan_.until_flip && reason_ == StopReason::None) {
            reason_ = StopReason::Flip;
            kernel_->request_stop();
        }
    });
    if (cfg_.gs_probe.enabled()) {
        gs_probe_ = std::make_unique<GsProbe>(cfg_.gs_probe, *gs_, kernel_->bus().time());
        if (!cfg_.gs_probe.census.empty()) gs_->core().set_draw_observer(gs_probe_.get());
    }
    kernel_->set_vu_control_handler([this](u32 reg, u32 value) {
        if (reg == 28 && (value & 0x200u)) gs_->vu1_reset();  // FBRST RS1 (B-42/B-43); in order with queued VU1 work
    });

    // IPU (runtime/ipu/README.md "Integration"): registers + FIFOs, DMAC ch3/ch4, INTC 8; traps fail closed.
    ipu_ = std::make_unique<ipu::IpuSystem>();
    ipu_->attach(kernel_->bus());
    ipu_->set_trap_handler([this](const ipu::IpuTrap& t) {
        const std::string msg = "IPU trap: " + t.message;
        kernel_->hooks().fatal(*ctx_, ctx_->pc, msg.c_str());
    });
    kernel_->add_device_service([this] { return ipu_->service(); });

    auto disc = hle::open_user_disc(cfg_.disc);
    if (!disc) {
        error = "disc " + cfg_.disc.string() + ": " + std::string(formats::error_name(disc.code())) + " " + disc.detail();
        return false;
    }
    disc_ = std::move(disc.value());
    if (!cfg_.mods.empty() || cfg_.mods_overlay) {  // ADR-0016: only when asked for; otherwise disc_ is the plain source
        hle::ModsOptions mo;
        mo.dirs = cfg_.mods;
        mo.enabled = cfg_.mods_enabled;
        mo.log = [this](std::string_view s) { log(s); };  // always printed: the applied overrides are the point
        auto ov = hle::ModsOverlay::open(std::move(disc_), std::move(mo));
        if (!ov) {
            error = "mods: " + std::string(formats::error_name(ov.code())) + " " + ov.detail();
            return false;
        }
        mods_ = ov.value().get();
        disc_ = std::move(ov).value();
        if (!patch_mods_tables(error)) return false;
    }

    hle::sif::IopConfig ic;
    ic.trace = cfg_.trace_sif;
    if (cfg_.sk_mode == "constants") ic.sk_mode = hle::sif::SkMode::Constants;
    else if (cfg_.sk_mode == "modules") ic.sk_mode = hle::sif::SkMode::Modules;
    else {
        error = "bad sk mode '" + cfg_.sk_mode + "' (constants | modules)";
        return false;
    }
    if (cfg_.iop_layout == "legacy") ic.iop_layout = hle::sif::IopLayout::Legacy;
    else if (cfg_.iop_layout == "pcsx2") ic.iop_layout = hle::sif::IopLayout::Pcsx2;
    else {
        error = "bad IOP layout '" + cfg_.iop_layout + "' (legacy | pcsx2)";
        return false;
    }
    if (cfg_.spu2_interp == "gaussian") ic.spu2_gaussian = true;
    else if (cfg_.spu2_interp == "linear") ic.spu2_gaussian = false;
    else {
        error = "bad SPU2 interpolation '" + cfg_.spu2_interp + "' (gaussian | linear)";
        return false;
    }
    ic.log = [this](std::string_view s) {
        if (!cfg_.quiet || cfg_.trace_sif) log(std::string("[iop] ").append(s));
    };
    if (!open_memcard(ic, error)) return false;
    if (!cfg_.sound_log.empty()) {
        sound_log_ = std::fopen(cfg_.sound_log.string().c_str(), "wb");
        if (!sound_log_) {
            error = "cannot write --sound-log " + cfg_.sound_log.string();
            return false;
        }
        std::fprintf(sound_log_, "# p3fes sound log: vblank cycles sid fno verb | [sk=module/function] args(8 words, hex) -> result\n");
        ic.sound_sink = [this](const hle::sif::SoundRequest& r) {
            std::fprintf(sound_log_, "%llu %llu %08X %04X %s |", static_cast<unsigned long long>(r.vblank),
                         static_cast<unsigned long long>(r.cycle), r.sid, r.fno, hle::sif::sound_verb(r).c_str());
            if ((r.fno & 0xFFF0u) == 0x90F0u) std::fprintf(sound_log_, " sk=%08X/%u", r.sk_module, r.sk_function);
            for (u32 a : r.args) std::fprintf(sound_log_, " %X", a);
            std::fprintf(sound_log_, " -> %d\n", r.result);
        };
    }
    sif_ = std::make_unique<hle::sif::SifHle>(*mem_, kernel_->bus(), ic, disc_.get());
    sif_->attach();
    // Host audio right after the SifHle exists (runtime/audio/README.md "Host wiring"): the CRI_ADXI mixer model
    // pushes its 48 kHz mix and every RNA session's PCM; positions come from virtual time only.
    audio_ = std::make_unique<audio::HostAudio>(cfg_.audio);
    sif_->iop().set_audio_output(audio_->mix_sink(), audio_->stream_tap());
    if (hle::sif::install_sif_syscalls(*kernel_, *sif_) != static_cast<int>(hle::sif::kSifSyscalls.size())) {
        error = "kernel refused a SIF syscall slot";
        return false;
    }
    kernel_->add_device_service([this] {
        sif_->service();
        return sif_->next_event_cycles();
    });
    kernel_->add_device_service([this] { return host_service(); });

    if (cfg_.trace_syscalls || cfg_.trace_hw) {
        tracing_ = std::make_unique<TracingHooks>(kernel_->hooks(), syms_, cfg_.trace_syscalls, cfg_.trace_hw,
                                                  [this](std::string_view s) { log(std::string("[trace] ").append(s)); });
        set_hooks(tracing_.get());
    } else {
        set_hooks(&kernel_->hooks());
    }
    rt::bind_context(ctx_.get());
    if (cfg_.zones_every)
        zones_ = std::make_unique<ZoneRecorder>(cfg_.zones_every, mem_->main_ram(), EEMemory::kMainRamSize);
    if (cfg_.watch_len &&
        !arm_write_watch(mem_->main_ram(), cfg_.watch_va & 0x01FFFFFFu, cfg_.watch_len, cfg_.watch_hits, syms_, &ctx_->cycles,
                         [this](const std::string& s) { log(s); })) {
        error = "cannot arm the write watch";
        return false;
    }
    return true;
}

// --memcard (p3fes/hle/memcard/source.h, docs/ANALYSIS/17 §6). The default "" is PCSX2's slot-1 card (the Phase 4
// oracle's card, copy-on-write); when PCSX2.ini names none (no ini, slot disabled, file missing or not a plain
// file) -- the case on a player's machine -- the port's own card %APPDATA%\P3FES\saves\Mcd001.ps2 is used,
// created formatted on first use (GOAL.md Phase 3; "appdata" selects it explicitly). Without %APPDATA% the run
// continues with no card and says so. An explicit spec that cannot be opened, or a PCSX2 card that exists but
// cannot be used, fails the init.
std::filesystem::path GameHost::appdata_card_path() {
    char* appdata = nullptr;
    std::size_t len = 0;
    if (_dupenv_s(&appdata, &len, "APPDATA") != 0 || !appdata || !*appdata) {
        std::free(appdata);
        return {};
    }
    std::filesystem::path p = std::filesystem::path(appdata) / "P3FES" / "saves" / "Mcd001.ps2";
    std::free(appdata);
    return p;
}

bool GameHost::open_memcard(hle::sif::IopConfig& ic, std::string& error) {
    const hle::memcard::SourceOptions opt;
    std::string spec = cfg_.memcard;
    bool use_appdata = spec == "appdata";
    if (spec.empty()) {
        std::string why;
        if (!hle::memcard::pcsx2_slot1_card(opt.pcsx2_ini, &why)) {
            log("[host] memory card: PCSX2's slot-1 card is not available (" + why + "); using the port's own card");
            use_appdata = true;
        }
    }
    hle::memcard::OpenResult mr;
    if (use_appdata) {
        const std::filesystem::path card = appdata_card_path();
        if (card.empty()) {
            log("[host] memory card: %APPDATA% is not set; running with no card (--memcard none|new|blank|PATH chooses one)");
            mr = hle::memcard::open_memcard("none", opt);
        } else {
            mr = hle::memcard::open_or_create(card, opt.format_time);
        }
    } else {
        mr = hle::memcard::open_memcard(spec, opt);
    }
    if (!mr.ok) {
        error = "--memcard " + (cfg_.memcard.empty() ? std::string("(default: PCSX2's slot-1 card)") : cfg_.memcard) + ": " +
                mr.error;
        return false;
    }
    memcard_desc_ = mr.description;
    log("[host] memory card: " + mr.description);
    if (mr.card) {
        auto slot = std::make_shared<hle::memcard::IopSlotConfig>();
        slot->slot1 = std::move(mr.card);
        ic.memcard = std::move(slot);
    }
    return true;
}

void GameHost::flush_audio() {
    if (sif_) sif_->iop().flush_audio();  // the mixer's last passes, before the sinks close
    if (audio_) audio_->flush();
}

void GameHost::finish_diagnostics() {
    if (gs_probe_) gs_probe_->finish();
}

bool GameHost::enable_gpu_recording(bool split_overlaps, bool prim_records) {
    if (gpu_rec_) return true;
    if (!cfg_.gs_probe.census.empty()) return false;  // one draw observer at a time
    gpu_rec_ = std::make_unique<gs::GsOpRecorder>(gs_->core(), split_overlaps, prim_records);
    gpu_rec_->sync_hook = [this](gs::GpuSyncReason why) { gpu_sync_point(why); };
    gs_->core().set_draw_observer(gpu_rec_.get());
    gs_->core().set_software_raster(false);
    gpu_handed_back_ = false;
    return true;
}

bool GameHost::enable_native_renderer(std::uint32_t mask, int mode) {
    if (!gpu_rec_ || gpu_handed_back_) return false;
    if (!native_) native_ = std::make_unique<native::NativeG3>(gs_->core(), *gpu_rec_, *gs_);
    native_->set_mask(mask);
    native_->set_diff(mode == 1, stdout);
    if (mode == 2) native_->set_verify(16, stdout);
    if (mode != 0) gs_->vu1().set_sink(native_.get());  // the tee forwards every kick to GsSystem (PATH1)
    gs_->vif1().set_run_hook(native_.get());
    return true;
}

void GameHost::disable_gpu_recording() {
    if (!gpu_rec_) return;
    gs_quiesce();
    if (native_) {
        gs_->vif1().set_run_hook(nullptr);
        gs_->vu1().set_sink(gs_.get());
        native_.reset();
    }
    gs_->core().set_draw_observer(nullptr);
    gs_->core().set_software_raster(true);
    gpu_rec_.reset();
    frame_source_ = nullptr;
    gpu_memory_source_ = nullptr;
}

void GameHost::take_gpu_ops(gs::OpList& out) {
    gs_quiesce();
    if (gpu_rec_ && !gpu_handed_back_) gpu_rec_->take(out);
    else out.clear();
}

bool GameHost::start_gs_pipeline(const gs::GsPipelineOptions& o) {
    // The native renderer's diff / verify modes tee the VU1 kicks on the EE side (diagnostics): synchronous only.
    if (native_ && (native_->diff() || native_->verify())) return false;
    gs_->start_pipeline(o);
    // The native renderer's hook runs on the VU1 stage (Vif1::run_hook, consulted by the pipeline); its GS-side work
    // (PRIM write, recorder call) travels as a GS-stage command at that point of the stream.
    if (native_) {
        gs::GsPipeline* p = gs_->pipeline();
        native_->set_emitter([p](std::function<void()> f) { p->emit_gs(std::move(f)); });
    }
    gs_->pipeline()->set_fail_handler([this](const char* what) { kernel_->hooks().fatal(*ctx_, ctx_->pc, what); });
    return true;
}

void GameHost::stop_gs_pipeline() {
    if (gs_) gs_->stop_pipeline();
    if (native_) native_->set_emitter(nullptr);
}

void GameHost::gs_quiesce() const {
    if (gs_) gs_->quiesce();
}

void GameHost::submit_ops(const gs::DisplayRegs& display, const GpuSubmit& submit) {
    if (!gpu_rec_ || gpu_handed_back_ || !submit) return;
    gs::OpList ops;
    if (gpu_recycle_) gpu_recycle_(ops);  // take() leaves the recorder this storage
    gpu_rec_->take(ops);
    submit(std::move(ops), display);
}

void GameHost::end_vblank_slice(GpuSubmit submit) {
    if (!gpu_rec_ || gpu_handed_back_ || !submit) return;
    const gs::DisplayRegs d = gs_->priv().display();
    if (gs::GsPipeline* p = gs_->pipeline()) {
        p->call_on_gs([this, d, f = std::move(submit)] { submit_ops(d, f); });
        return;
    }
    submit_ops(d, submit);
}

bool GameHost::set_native_side_table(bool on) {
    if (!gpu_rec_) return false;
    gpu_rec_->set_native_side_table(on);
    return true;
}

bool GameHost::sync_gpu_memory(std::string& error) {
    if (!gpu_rec_ || gpu_handed_back_ || !gpu_memory_source_) return true;  // the CPU copy is already complete
    gs::OpList ops;
    gpu_rec_->take(ops);  // closes pending transfer words first: their values come from the CPU copy as it is now
    std::vector<std::uint8_t> vram;
    std::array<std::uint16_t, 512> clut{};
    if (!gpu_memory_source_(std::move(ops), vram, clut) || vram.size() != gs::kVramBytes) {
        error = "the d3d11 GS renderer did not return GS memory (timeout or lost device)";
        gpu_sync_failed_ = true;
        return false;
    }
    // GPU memory = uploads + draws; the CPU copy held the uploads only. Afterwards both agree everywhere.
    std::memcpy(gs_->core().mem().data(), vram.data(), gs::kVramBytes);
    gs_->core().set_clut(clut);
    ++gpu_syncs_;
    return true;
}

// The recorder's sync points (gs_ops.h GpuSyncReason), on the EE fiber inside run().
void GameHost::gpu_sync_point(gs::GpuSyncReason why) {
    if (why == gs::GpuSyncReason::Unsupported && !gpu_fallback_on_unsupported_) return;  // windowed: skipped
    std::string err;
    if (!sync_gpu_memory(err)) {
        log("p3fes: gs-backend: " + err + " at a " +
            (why == gs::GpuSyncReason::LocalRead ? std::string("local->host transfer") : std::string("primitive the GPU path cannot draw")) +
            ": the run is no longer exact");
        return;
    }
    if (why == gs::GpuSyncReason::Unsupported) {
        // Software from here on: the core draws this primitive itself (GsCore::draw_queue) and every later one. The
        // recorder object stays alive until the owner calls disable_gpu_recording() between run slices.
        gs_->core().set_draw_observer(nullptr);
        gs_->core().set_software_raster(true);
        gpu_handed_back_ = true;
        log("p3fes: gs-backend: a point/line primitive at vblank " + std::to_string(kernel_->bus().time().vblanks) +
            ": GS memory synced from the GPU, the software GS draws from here on");
    }
}

// The host's own device service: stop conditions on virtual cycles and at VBLANK_START.
std::uint64_t GameHost::host_service() {
    const hle::Timebase& t = kernel_->bus().time();
    auto stop = [this](StopReason r) {
        if (reason_ != StopReason::None) return;
        reason_ = r;
        kernel_->request_stop();
    };
    if (plan_.until_cycles && t.cycles >= plan_.until_cycles) stop(StopReason::Cycles);
    if (t.vblanks != last_vblank_seen_) {
        last_vblank_seen_ = t.vblanks;
        feed_pad_input(t.vblanks, sif_->iop());  // input.h: the state for PADMAN's next frame
        sample_markers(t.vblanks);
        if (plan_.until_vblank && t.vblanks >= plan_.until_vblank) stop(StopReason::Vblank);
        if (plan_.until_sky && guest_u32(kSkyFrameCount) >= plan_.until_sky) stop(StopReason::Sky);
        if (plan_.every_vblank) stop(StopReason::EveryVblank);
        if (zones_) {
            zones_->vblank(t.vblanks, gs_->flip_count());
            if (zones_->due(t.vblanks)) zones_->row(t.vblanks, t.cycles, zone_work());
        }
    }
    return (plan_.until_cycles && t.cycles < plan_.until_cycles) ? plan_.until_cycles : ~0ull;
}

ZoneWork GameHost::zone_work() const {
    ZoneWork w;
    const gs::GsCoreStats& c = gs_->core().stats();
    const gs::GifStats& g = gs_->gif().stats();
    const gs::VifStats& v = gs_->vif1().stats();
    const vu1::VU1Stats& u = gs_->vu1().stats();
    w.flips = gs_->flip_count();
    w.gs_prims = c.primitives;
    w.gs_pixels = c.pixels_written;
    w.gs_image_qw_in = c.image_qwords_in;
    w.gs_image_qw_out = c.image_qwords_out;
    w.gs_local_copies = c.local_copies;
    w.gs_clut_loads = c.clut_loads;
    w.gs_reg_writes = c.reg_writes;
    for (unsigned p = 0; p < 4; ++p) w.gif_qw[p] = g.qwords[p];
    w.vif_vu_runs = v.vu_runs;
    w.vif_vu_pairs = v.vu_pairs;
    w.vif_mpg_pairs = v.mpg_pairs;
    w.vu1_kicks = u.kicks;
    w.vu1_kick_qw = u.kick_qwords;
    if (zone_render_counters_) zone_render_counters_(w);
    // What is on screen, for the segment classifier of tools/ours/perf/bench.py: the names of the running kwln tasks
    // (game/include/p3fes/game/task.h: list head 0x7CE07C, next at +0x40, name at +0x00) and whether a Sofdec movie
    // is playing (the movie task's player pointer; flag 5127 is no use here: battles and menus set it too). Read
    // straight from guest RAM, never written.
    const std::uint8_t* ram = mem_->main_ram();
    const std::uint32_t size = EEMemory::kMainRamSize;
    auto rd = [ram, size](std::uint32_t va) -> std::uint32_t {
        va &= 0x1FFFFFFFu;
        if (va > size - 4u) return 0;
        std::uint32_t v;
        std::memcpy(&v, ram + va, 4);
        return v;
    };
    w.movie = rd(kMovieObject) != 0;
    std::uint32_t task = rd(0x7CE07Cu);
    for (unsigned n = 0; task && n < 512; ++n) {
        const std::uint32_t at = task & 0x1FFFFFFFu;
        if (at > size - 0x68u) break;
        if (!w.tasks.empty()) w.tasks += '|';
        for (unsigned i = 0; i < 23; ++i) {
            const char ch = static_cast<char>(ram[at + i]);
            if (!ch) break;
            w.tasks += (ch > ' ' && ch < 0x7F && ch != '|') ? ch : '_';
        }
        task = rd(at + 0x40u);
    }
    return w;
}

bool GameHost::write_zones(const std::string& path) {
    if (!zones_) return false;
    const hle::Timebase& t = kernel_->bus().time();
    const bool ok = zones_->write(path, t.vblanks, t.cycles, zone_work(), [this](std::uint32_t va) {
        return va ? syms_.describe(va) : std::string("(unattributed)");
    });
    zones_.reset();
    return ok;
}

double GameHost::host_seconds() const {
    LARGE_INTEGER f;
    QueryPerformanceFrequency(&f);
    return static_cast<double>(wall_ticks_ + (qpc() - run_t0_)) / static_cast<double>(f.QuadPart);
}

void GameHost::sample_markers(std::uint64_t vblank) {
    const std::uint32_t flag = (guest_u32(kMovieFlagWord) >> kMovieFlagBit) & 1u;
    const std::uint32_t obj = guest_u32(kMovieObject);
    if (flag == movie_flag_ && obj == movie_obj_) return;
    const double wall = host_seconds();
    const std::uint64_t cyc = kernel_->bus().time().cycles;
    const std::uint32_t sky = guest_u32(kSkyFrameCount);
    if (flag != movie_flag_) markers_.push_back({"movie flag 5127", movie_flag_, flag, vblank, cyc, sky, wall});
    if (obj != movie_obj_) markers_.push_back({"movie object 0x7CDF10", movie_obj_, obj, vblank, cyc, sky, wall});
    movie_flag_ = flag;
    movie_obj_ = obj;
}

StopReason GameHost::run(const StopPlan& plan) {
    if (dead_) return reason_;
    plan_ = plan;
    reason_ = StopReason::None;
    const std::uint64_t t0 = qpc();
    run_t0_ = t0;
    hle::RunResult r;
    if (!started_) {
        started_ = true;
        kernel_->start(rt::lookup_func(kEntry));
    }
    r = kernel_->run_until(nullptr);
    wall_ticks_ += qpc() - t0;
    switch (r.status) {
    case hle::RunStatus::Stopped: break;
    case hle::RunStatus::MainExited:
        reason_ = StopReason::MainExited;
        dead_ = true;
        break;
    case hle::RunStatus::Fatal:
        reason_ = StopReason::Fatal;
        dead_ = true;
        if (fatal_message_.empty()) fatal_message_ = r.message;
        break;
    }
    return reason_;
}

void GameHost::on_fatal(const hle::FatalInfo& info) {
    // Runs on the guest fiber before the kernel switches to the host: the host stack is the guest call chain.
    std::string m = "FATAL: " + info.message + "\n";
    m += "  thread " + std::to_string(info.thread) + ", cycles " + std::to_string(ctx_->cycles) + ", vblanks " +
         std::to_string(kernel_->bus().time().vblanks) + ", flips " + std::to_string(gs_ ? gs_->flip_count() : 0) + "\n";
    m += "  pc " + syms_.describe(info.pc) + ", ra " + syms_.describe(ctx_->gpr[GPR_RA].u32[0]) + ", sp " +
         hexs(ctx_->gpr[GPR_SP].u32[0]) + ", v1 " + hexs(info.v1) + "\n";
    const auto bt = guest_backtrace(24);
    if (bt.empty()) {
        m += "  (no recompiled frames resolved on the host stack; PDB missing?)\n";
    } else {
        m += "  guest call chain (innermost first):\n";
        for (const GuestFrame& f : bt) m += "    " + syms_.describe(f.va) + "\n";
    }
    fatal_message_ = m;
    log(m);
}

bool GameHost::snapshot(const std::filesystem::path& dir, const std::string& label, std::string& error) {
    gs_quiesce();
    std::error_code ec;
    std::filesystem::create_directories(dir, ec);
    if (ec) {
        error = "cannot create " + dir.string() + ": " + ec.message();
        return false;
    }
    if (!kernel_->snapshot_eemem((dir / "eeMemory.bin").string())) {
        error = "cannot write " + (dir / "eeMemory.bin").string();
        return false;
    }
    // D3D11 back end: GS memory from the GPU into the CPU copy first, so gsMemory.bin holds the rendered pixels and,
    // headless (no frame source), frame.png is the software CRTC (gs::compose) over them.
    if (!sync_gpu_memory(error)) return false;
    const gs::Frame frame = shown_frame();  // windowed D3D11: the GPU's picture (its CRTC pass)
    const bool png_ok = !frame.empty() && gs::write_png((dir / "frame.png").string(), frame);
    {
        // GS local memory (4 MiB, the GS core's linear byte order), for comparisons with PCSX2's GS.bin.
        std::FILE* g = std::fopen((dir / "gsMemory.bin").string().c_str(), "wb");
        const bool g_ok = g && std::fwrite(gs_->core().mem().data(), 1, gs::kVramBytes, g) == gs::kVramBytes;
        if (g) std::fclose(g);
        if (!g_ok) {
            error = "cannot write " + (dir / "gsMemory.bin").string();
            return false;
        }
    }

    std::FILE* f = std::fopen((dir / "capture.json").string().c_str(), "wb");
    if (!f) {
        error = "cannot write capture.json";
        return false;
    }
    const hle::Timebase& t = kernel_->bus().time();
    std::fprintf(f, "{\n  \"tool\": \"p3fes\",\n  \"point\": \"%s\",\n", label.c_str());
    std::fprintf(f, "  \"stop_reason\": \"%s\",\n", to_string(reason_));
    std::fprintf(f, "  \"flip_count\": %llu,\n", static_cast<unsigned long long>(gs_->flip_count()));
    std::fprintf(f, "  \"cycles\": %llu,\n  \"hlines\": %llu,\n  \"vblanks\": %llu,\n  \"field\": %u,\n",
                 static_cast<unsigned long long>(t.cycles), static_cast<unsigned long long>(t.hlines),
                 static_cast<unsigned long long>(t.vblanks), t.field);
    // "sp" is the live context's stack pointer: meaningful for "current_thread" when a thread is running at
    // the snapshot (tracediff --dead-stack); at the idle thread (0) every thread's bound is its saved frame.
    std::fprintf(f, "  \"pc\": \"0x%08X\",\n  \"sp\": \"0x%08X\",\n  \"current_thread\": %d,\n", ctx_->pc,
                 ctx_->gpr[GPR_SP].u32[0], kernel_->current_thread());
    std::fprintf(f, "  \"threads\": [");
    bool first = true;
    for (int tid = 1; tid < 256; ++tid) {
        const hle::ThreadView v = kernel_->thread(tid);
        if (v.status == 0) continue;
        std::fprintf(f, "%s\n    {\"tid\": %d, \"status\": \"%s\", \"priority\": %d, \"init_priority\": %d, \"wait_type\": %u, \"wait_id\": %u, \"wakeup_count\": %u, \"entry\": \"0x%08X\", \"stack\": \"0x%08X\", \"stack_size\": \"0x%X\", \"frame\": \"0x%08X\"}",
                     first ? "" : ",", tid, status_name(v.status), v.priority, v.init_priority, v.wait_type, v.wait_id,
                     v.wakeup_count, v.entry, v.stack, v.stack_size, v.frame);
        first = false;
    }
    std::fprintf(f, "\n  ],\n");
    std::fprintf(f, "  \"state_globals\": {\"g_skyFrameCount\": %u, \"g_rwDMAFlipPending\": %u, \"g_rwDMAFlipBuf\": %u, "
                    "\"adxt_vsync_cnt\": %u, \"kwln_frame\": %u, \"g_kwlnFirstFrame\": %u},\n",
                 guest_u32(kSkyFrameCount), guest_u8(kRwFlipPending), guest_u8(kRwFlipBuf), guest_u32(kAdxVsyncCnt),
                 guest_u32(kKwlnFrame), guest_u32(kKwlnFirstFrame));
    std::fprintf(f, "  \"flips\": [");
    for (std::size_t i = 0; i < flips_.size(); ++i) {
        const FlipRecord& fl = flips_[i];
        std::fprintf(f, "%s\n    {\"count\": %llu, \"vblank\": %llu, \"cycles\": %llu, \"circuit\": %u, \"fbp\": %u, \"sky\": %u}",
                     i ? "," : "", static_cast<unsigned long long>(fl.count), static_cast<unsigned long long>(fl.vblank),
                     static_cast<unsigned long long>(fl.cycles), fl.circuit, fl.fbp, fl.sky);
    }
    std::fprintf(f, "\n  ],\n");
    std::fprintf(f, "  \"markers\": [");
    for (std::size_t i = 0; i < markers_.size(); ++i) {
        const MarkerEdge& m = markers_[i];
        std::fprintf(f, "%s\n    {\"what\": \"%s\", \"from\": \"0x%X\", \"to\": \"0x%X\", \"vblank\": %llu, \"cycles\": %llu, \"sky\": %u}",
                     i ? "," : "", m.what, m.from, m.to, static_cast<unsigned long long>(m.vblank),
                     static_cast<unsigned long long>(m.cycles), m.sky);
    }
    std::fprintf(f, "\n  ],\n");
    std::fprintf(f, "  \"frame_png\": %s,\n  \"frame_hash\": \"0x%016llX\",\n", png_ok ? "\"frame.png\"" : "null",
                 static_cast<unsigned long long>(gs::frame_hash(frame)));
    std::fprintf(f, "  \"sif\": {\"set_dma_calls\": %llu, \"iop_unknown_events\": %llu, \"iop_sound_requests\": %llu},\n",
                 static_cast<unsigned long long>(sif_->stats().set_dma_calls),
                 static_cast<unsigned long long>(sif_->iop().unknown_total()),
                 static_cast<unsigned long long>(sif_->iop().sound_requests()));
    {
        // Sound requests by verb (hle::sif::sound_verb: SK SOUND/HSYNTH/SESQ, libsd codes, CRI DTX), keys sorted.
        std::fprintf(f, "  \"iop_sound_census\": {");
        bool first_key = true;
        for (const auto& [k, n] : sif_->iop().sound_census()) {
            std::fprintf(f, "%s\n    \"%s\": %llu", first_key ? "" : ",", k.c_str(), static_cast<unsigned long long>(n));
            first_key = false;
        }
        std::fprintf(f, "\n  },\n");
    }
    {
        const ipu::IpuStats& is = ipu_->core().stats();
        static const char* kCmd[10] = {"BCLR", "IDEC", "BDEC", "VDEC", "FDEC", "SETIQ", "SETVQ", "CSC", "PACK", "SETTH"};
        std::fprintf(f, "  \"ipu\": {\"commands\": {");
        for (int c = 0; c < 10; ++c)
            std::fprintf(f, "%s\"%s\": %llu", c ? ", " : "", kCmd[c], static_cast<unsigned long long>(is.commands[c]));
        std::fprintf(f, "}, \"in_qwords\": %llu, \"out_qwords\": %llu, \"input_stalls\": %llu, \"output_stalls\": %llu, "
                        "\"errors\": %llu, \"macroblocks\": %llu, \"interrupts\": %llu},\n",
                     static_cast<unsigned long long>(is.in_qwords), static_cast<unsigned long long>(is.out_qwords),
                     static_cast<unsigned long long>(is.input_stalls), static_cast<unsigned long long>(is.output_stalls),
                     static_cast<unsigned long long>(is.errors), static_cast<unsigned long long>(is.macroblocks),
                     static_cast<unsigned long long>(is.interrupts));
    }
    {
        // CRI_ADXI model counters and the host mix fingerprint (NullSink, always fed): virtual-time functions.
        const hle::sif::AdxiStats as = sif_->iop().adxi_stats();
        std::fprintf(f, "  \"adxi\": {\"ticks\": %llu, \"dtx_blocks_in\": %llu, \"dtx_blocks_out\": %llu, \"urpc_calls\": %llu, "
                        "\"sjx_chunks_in\": %llu, \"sjx_chunks_out\": %llu, \"rna_commands\": %llu, \"psm_passes\": %llu, "
                        "\"pcm_bytes_consumed\": %llu, \"underrun_samples\": %llu, \"sj_errors\": %llu, \"dtx_open\": %u, "
                        "\"rna_playing\": %u},\n",
                     static_cast<unsigned long long>(as.ticks), static_cast<unsigned long long>(as.dtx_blocks_in),
                     static_cast<unsigned long long>(as.dtx_blocks_out), static_cast<unsigned long long>(as.urpc_calls),
                     static_cast<unsigned long long>(as.sjx_chunks_in), static_cast<unsigned long long>(as.sjx_chunks_out),
                     static_cast<unsigned long long>(as.rna_commands), static_cast<unsigned long long>(as.psm_passes),
                     static_cast<unsigned long long>(as.pcm_bytes_consumed), static_cast<unsigned long long>(as.underrun_samples),
                     static_cast<unsigned long long>(as.sj_errors), as.dtx_open, as.rna_playing);
        const audio::NullSink& fp = audio_->fingerprint();
        std::fprintf(f, "  \"audio\": {\"frames\": %llu, \"first_frame\": %llu, \"end_frame\": %llu, \"gap_frames\": %llu, "
                        "\"non_silent_frames\": %llu, \"first_non_silent_frame\": %lld, \"peak\": %d, \"hash\": \"0x%016llX\"},\n",
                     static_cast<unsigned long long>(fp.frames()), static_cast<unsigned long long>(fp.first_frame()),
                     static_cast<unsigned long long>(fp.end_frame()), static_cast<unsigned long long>(fp.gap_frames()),
                     static_cast<unsigned long long>(fp.non_silent_frames()),
                     fp.first_non_silent_frame() == ~0ull ? -1ll : static_cast<long long>(fp.first_non_silent_frame()), fp.peak(),
                     static_cast<unsigned long long>(fp.hash()));
        // ADR-0014: the interpreted SK stack and the SPU2 voice model (virtual-time functions as well).
        const hle::sif::SkStats sk = sif_->iop().sk_stats();
        std::fprintf(f, "  \"sk\": {\"mode\": \"%s\", \"layout\": \"%s\", \"interp\": \"%s\", \"modules\": %s, \"modules_loaded\": %u, \"rpc_routed\": %llu, "
                        "\"rpc_pending\": %llu, \"tick_runs\": %llu, \"instructions\": %llu, \"key_ons\": %llu, \"key_offs\": %llu, "
                        "\"key_offs_sounding\": %llu, \"voices_active\": %u, \"voices_active_max\": %u, \"voice_longest_frames\": %llu, "
                        "\"volume_sweeps\": %llu, \"sd_inits\": %u, \"voice_frames\": %llu, \"first_voice_frame\": %lld, \"mix_passes\": %llu, "
                        "\"mix_passes_skipped\": %llu, \"mix_stream_late\": %llu, \"fault\": \"%s\"},\n",
                     cfg_.sk_mode.c_str(), cfg_.iop_layout.c_str(), cfg_.spu2_interp.c_str(), sk.modules ? "true" : "false", sk.modules_loaded,
                     static_cast<unsigned long long>(sk.rpc_routed), static_cast<unsigned long long>(sk.rpc_pending),
                     static_cast<unsigned long long>(sk.tick_runs), static_cast<unsigned long long>(sk.instructions),
                     static_cast<unsigned long long>(sk.key_ons), static_cast<unsigned long long>(sk.key_offs),
                     static_cast<unsigned long long>(sk.key_offs_sounding), sk.voices_active, sk.voices_active_max,
                     static_cast<unsigned long long>(sk.voice_longest_frames), static_cast<unsigned long long>(sk.volume_sweeps), sk.sd_inits,
                     static_cast<unsigned long long>(sk.voice_frames),
                     sk.first_voice_frame == ~0ull ? -1ll : static_cast<long long>(sk.first_voice_frame),
                     static_cast<unsigned long long>(sk.mix_passes), static_cast<unsigned long long>(sk.mix_passes_skipped),
                     static_cast<unsigned long long>(sk.mix_stream_late), sk.fault.c_str());
    }
    std::fprintf(f, "  \"gs_census\": {");
    {
        bool first_c = true;
        for (const auto& [k, n] : gs_census()) {
            std::fprintf(f, "%s\n    \"%s\": %llu", first_c ? "" : ",", k.c_str(), static_cast<unsigned long long>(n));
            first_c = false;
        }
    }
    std::fprintf(f, "\n  },\n");
    std::fprintf(f, "  \"unhandled_hw_accesses\": %llu,\n  \"events_processed\": %llu\n}\n",
                 static_cast<unsigned long long>(kernel_->unhandled_accesses()),
                 static_cast<unsigned long long>(kernel_->events_processed()));
    const bool ok = std::fclose(f) == 0;
    if (!ok) error = "cannot finish capture.json";
    return ok;
}

// ---- GS feature census (diagnostics; the GS core calls this for state-register writes) ----------------------

namespace {
const char* psm_name(u32 psm) {
    switch (psm) {
    case 0x00: return "CT32";
    case 0x01: return "CT24";
    case 0x02: return "CT16";
    case 0x0A: return "CT16S";
    case 0x13: return "T8";
    case 0x14: return "T4";
    case 0x1B: return "T8H";
    case 0x24: return "T4HL";
    case 0x2C: return "T4HH";
    case 0x30: return "Z32";
    case 0x31: return "Z24";
    case 0x32: return "Z16";
    case 0x3A: return "Z16S";
    default: return "?";
    }
}
std::string fmt(const char* f, unsigned long long a, unsigned long long b = 0, unsigned long long c = 0,
                unsigned long long d = 0, unsigned long long e = 0, unsigned long long g = 0) {
    char buf[160];
    std::snprintf(buf, sizeof buf, f, a, b, c, d, e, g);
    return buf;
}

// The bits of a state-register value its census key depends on; false = the register is not counted by key.
bool census_mask(std::uint32_t reg, std::uint64_t& mask) {
    switch (reg) {
    case 0x00: mask = 0x1FFull; return true;                                            // PRIM: type + 6 flags
    case 0x06: case 0x07:                                                               // TEX0: PSM TCC TFX CPSM CSM CLD
        mask = (0x3Full << 20) | (1ull << 34) | (3ull << 35) | (0xFull << 51) | (1ull << 55) | (7ull << 61);
        return true;
    case 0x08: case 0x09: mask = 0xFull; return true;                                   // CLAMP: WMS WMT
    case 0x14: case 0x15: mask = 0x3FDull; return true;                                 // TEX1: LCM MXL MMAG MMIN MTBA
    case 0x22: mask = 3; return true;                                                   // SCANMSK
    case 0x42: case 0x43: mask = 0xFFull | (0xFFull << 32); return true;                // ALPHA: A B C D FIX
    case 0x45: case 0x46: case 0x49: case 0x4A: case 0x4B: mask = 1; return true;       // DTHE COLCLAMP PABE FBA
    case 0x47: case 0x48: mask = 0x7700Full; return true;                               // TEST
    case 0x4C: case 0x4D: mask = 0x3Full << 24; return true;                            // FRAME: PSM
    case 0x4E: case 0x4F: mask = (0xFull << 24) | (1ull << 32); return true;            // ZBUF: PSM ZMSK
    case 0x16: case 0x17: case 0x1C: case 0x34: case 0x35: case 0x36: case 0x37: case 0x3B: case 0x3D:
    case 0x60: case 0x61: case 0x62:
        mask = 0; return true;                                                          // counted by register only
    default: return false;
    }
}

// The census key of a state-register value (empty: not counted here). Only the bits census_mask() keeps are read.
std::string census_name(std::uint32_t reg, std::uint64_t v) {
    switch (reg) {
    case 0x00: {  // PRIM: type + IIP TME FGE ABE AA1 FST
        static const char* kPrim[8] = {"point", "line", "linestrip", "tri", "tristrip", "trifan", "sprite", "prohibited"};
        return std::string("prim ") + kPrim[v & 7u] + fmt(" iip%llu tme%llu fge%llu abe%llu aa1%llu fst%llu", (v >> 3) & 1u, (v >> 4) & 1u,
                                                         (v >> 5) & 1u, (v >> 6) & 1u, (v >> 7) & 1u, (v >> 8) & 1u);
    }
    case 0x06: case 0x07:  // TEX0: PSM, TFX, TCC, CPSM, CSM, CLD
        return std::string("tex0 psm ") + psm_name(static_cast<u32>(v >> 20) & 0x3Fu) +
                fmt(" tfx%llu tcc%llu", (v >> 35) & 3u, (v >> 34) & 1u) +
                (((v >> 20) & 0x3Fu) == 0x13 || ((v >> 20) & 0x3Fu) == 0x14 || ((v >> 20) & 0x3Fu) == 0x1B ||
                         ((v >> 20) & 0x3Fu) == 0x24 || ((v >> 20) & 0x3Fu) == 0x2C
                     ? std::string(" clut ") + psm_name(static_cast<u32>(v >> 51) & 0xFu) + fmt(" csm%llu cld%llu", (v >> 55) & 1u, (v >> 61) & 7u)
                     : std::string());
    case 0x08: case 0x09:
        return fmt("clamp wms%llu wmt%llu", v & 3u, (v >> 2) & 3u);
    case 0x14: case 0x15:
        return fmt("tex1 lcm%llu mxl%llu mmag%llu mmin%llu mtba%llu", v & 1u, (v >> 2) & 7u, (v >> 5) & 1u, (v >> 6) & 7u, (v >> 9) & 1u);
    case 0x16: case 0x17: return "tex2";
    case 0x1C: return "texclut";
    case 0x22: return fmt("scanmsk %llu", v & 3u);
    case 0x34: case 0x35: case 0x36: case 0x37: return "miptbp";
    case 0x3B: return "texa";
    case 0x3D: return "fogcol";
    case 0x42: case 0x43: return fmt("alpha a%llu b%llu c%llu d%llu fix%llu", v & 3u, (v >> 2) & 3u, (v >> 4) & 3u, (v >> 6) & 3u, (v >> 32) & 0xFFu);
    case 0x45: return fmt("dthe %llu", v & 1u);
    case 0x46: return fmt("colclamp %llu", v & 1u);
    case 0x47: case 0x48:
        return fmt("test ate%llu atst%llu afail%llu date%llu zte%llu ztst%llu", v & 1u, (v >> 1) & 7u, (v >> 12) & 3u, (v >> 14) & 1u, (v >> 16) & 1u, (v >> 17) & 3u);
    case 0x49: return fmt("pabe %llu", v & 1u);
    case 0x4A: case 0x4B: return fmt("fba %llu", v & 1u);
    case 0x4C: case 0x4D: return std::string("frame psm ") + psm_name(static_cast<u32>(v >> 24) & 0x3Fu);
    case 0x4E: case 0x4F: return std::string("zbuf psm ") + psm_name(0x30u | (static_cast<u32>(v >> 24) & 0xFu)) + fmt(" zmsk%llu", (v >> 32) & 1u);
    case 0x60: case 0x61: case 0x62: return fmt("signal/finish/label %llx", reg);
    default: return std::string();
    }
}

} // namespace

void GameHost::observe_gs_reg(std::uint32_t reg, std::uint64_t v) {
    gs::GsPipeline* pipe = gs_->pipeline();
    const u32 path = pipe ? pipe->gs_path() : gs_->gif().active_path();
    if (cfg_.trace_gs_to) {  // --trace-gs: the placement registers, same selection as gsdump_regs.py
        const u64 vb = kernel_->bus().time().vblanks;
        if (vb >= cfg_.trace_gs_from && vb <= cfg_.trace_gs_to) {
            switch (reg) {
            case 0x06: case 0x07: case 0x16: case 0x17: case 0x4C: case 0x4D: case 0x4E: case 0x4F:
            case 0x50: case 0x51: case 0x52: case 0x53:
                log(fmt("[gs] vblank %llu P%u reg 0x%02X = 0x%016llX img_in=%llu xfer=%d", static_cast<unsigned long long>(vb),
                        path, reg, static_cast<unsigned long long>(v),
                        static_cast<unsigned long long>(gs_->core().stats().image_qwords_in),
                        gs_->core().host_to_local_active() ? 1 : 0) +
                    fmt(" m3=%d p3q=%u p2q=%d yields=%llu mstalls=%llu", gs_->gif().path3_masked() ? 1 : 0,
                        (gs_->gif().stat() >> 6) & 1u, gs_->gif().path2_waiting() ? 1 : 0,
                        static_cast<unsigned long long>(gs_->gif().stats().path3_yields),
                        static_cast<unsigned long long>(gs_->gif().stats().path3_mask_stalls)));
                break;
            default:
                break;
            }
        }
    }
    // The census counts (register, the value's census bits) pairs; the strings are built only when the census is read
    // (gs_census, a machine state): building a std::string map key per state write cost ~0.4 % of the battle route
    // (docs/ANALYSIS/23 §8). Same keys and counts as before.
    std::uint64_t mask = 0;
    if (census_mask(reg, mask)) {
        ++census_fast_[CensusKey{v & mask, reg}];
        return;
    }
    switch (reg) {
    case 0x50: bitbltbuf_ = v; break;
    case 0x52: trxreg_ = v; break;
    case 0x53: {
        const u64 xdir = v & 3u;
        const u64 w = trxreg_ & 0xFFFu, h = (trxreg_ >> 32) & 0xFFFu;
        if (xdir == 0) {
            const std::string k = std::string("upload ") + psm_name(static_cast<u32>(bitbltbuf_ >> 56) & 0x3Fu) + fmt(" path%llu", path);
            census_[k]++;
            census_[k + " pixels"] += w * h;
        } else {
            census_[fmt("trxdir %llu", xdir)]++;
        }
        break;
    }
    default: break;
    }
}

void GameHost::fold_census(std::map<std::string, std::uint64_t>& m) const {
    for (const auto& [k, n] : census_fast_) m[census_name(k.reg, k.v)] += n;
}

std::map<std::string, std::uint64_t> GameHost::gs_census() const {
    gs_quiesce();
    std::map<std::string, std::uint64_t> m = census_;
    fold_census(m);
    const gs::GsCoreStats& cs = gs_->core().stats();
    m["core primitives"] = cs.primitives;
    m["core unknown_reg_writes"] = cs.unknown_reg_writes;
    m["core prohibited_prims"] = cs.prohibited_prims;
    m["core image_qwords_in"] = cs.image_qwords_in;
    m["core image_qwords_ignored"] = cs.image_qwords_ignored;
    m["core local_copies"] = cs.local_copies;
    m["core clut_loads"] = cs.clut_loads;
    m["core invalid_psm"] = cs.invalid_psm;
    const gs::GifStats& gst = gs_->gif().stats();
    static const char* kFlg[4] = {"packed", "reglist", "image", "disabled"};
    for (int p = 1; p <= 3; ++p)
        for (int f = 0; f < 4; ++f)
            if (gst.tags[p][f]) m[std::string("gif path") + std::to_string(p) + " tags " + kFlg[f]] = gst.tags[p][f];
    for (int p = 1; p <= 3; ++p) m[std::string("gif path") + std::to_string(p) + " qwords"] = gst.qwords[p];
    m["gif path1_truncated"] = gst.path1_truncated;
    m["gif path1_queued"] = gst.path1_queued;
    m["gif path2_stalls"] = gst.path2_stalls;
    m["gif path3_mask_stalls"] = gst.path3_mask_stalls;
    m["gif path3_yields"] = gst.path3_yields;
    m["gif path3_window_stops"] = gst.path3_window_stops;
    const gs::VifStats& vs = gs_->vif1().stats();
    for (int c = 0; c < 128; ++c)
        if (vs.codes[c]) m[fmt("vif code 0x%02llx", static_cast<unsigned long long>(c))] = vs.codes[c];
    m["vif vu_runs"] = vs.vu_runs;
    m["vif vu_pairs"] = vs.vu_pairs;
    m["vif traps"] = vs.traps;
    return m;
}

void GameHost::print_summary() const {
    gs_quiesce();
    const hle::Timebase& t = kernel_->bus().time();
    std::printf("p3fes: cycles %llu (%.3f virtual s), hlines %llu, vblanks %llu, field %u, flips %llu, wall %.3f s\n",
                static_cast<unsigned long long>(t.cycles), static_cast<double>(t.cycles) / 294912000.0,
                static_cast<unsigned long long>(t.hlines), static_cast<unsigned long long>(t.vblanks), t.field,
                static_cast<unsigned long long>(gs_->flip_count()), wall_seconds());
    std::printf("p3fes: g_skyFrameCount %u, g_rwDMAFlipPending %u, g_rwDMAFlipBuf %u, adxt_vsync_cnt %u, kwln_frame %u\n",
                guest_u32(kSkyFrameCount), guest_u8(kRwFlipPending), guest_u8(kRwFlipBuf), guest_u32(kAdxVsyncCnt),
                guest_u32(kKwlnFrame));
    if (mods_) {  // ADR-0016 (only with --mods): what was served, and which disc files the guest read
        const auto& rd = mods_->files_read();
        std::size_t served = 0;
        for (const hle::ModOverride& o : mods_->scan().overrides) served += mods_->was_read(o.disc_path) ? 1 : 0;
        std::printf("p3fes: mods: %zu file(s) replaced, %zu of them read by the guest; %zu disc file(s) read since the last reload%s\n",
                    mods_->scan().overrides.size(), served, rd.size(), rd.size() > 48 ? " (first 48 listed)" : "");
        for (std::size_t i = 0; i < rd.size() && i < 48; ++i) std::printf("p3fes: mods:   read %s\n", rd[i].c_str());
    }
    std::printf("p3fes: threads (current %d):", kernel_->current_thread());
    for (int tid = 1; tid < 256; ++tid) {
        const hle::ThreadView v = kernel_->thread(tid);
        if (v.status == 0) continue;
        std::printf(" %d:%s/p%d", tid, status_name(v.status), v.priority);
    }
    std::printf("\n");
    const auto mods = sif_->iop().modules();
    std::printf("p3fes: IOP modules loaded %zu, SIF set_dma %llu, IOP unknown events %llu, sound requests %llu\n", mods.size(),
                static_cast<unsigned long long>(sif_->stats().set_dma_calls),
                static_cast<unsigned long long>(sif_->iop().unknown_total()),
                static_cast<unsigned long long>(sif_->iop().sound_requests()));
    {
        std::string census;
        for (const auto& [k, n] : sif_->iop().sound_census()) census += " " + k + "=" + std::to_string(n);
        if (!census.empty()) std::printf("p3fes: sound requests by verb:%s\n", census.c_str());
    }
    for (const auto& u : sif_->iop().unknown_events())
        std::printf("p3fes:   IOP unknown %s id 0x%08X fno %u x%llu\n",
                    u.kind == hle::sif::UnknownEvent::Kind::Server     ? "server"
                    : u.kind == hle::sif::UnknownEvent::Kind::Function ? "function"
                    : u.kind == hle::sif::UnknownEvent::Kind::Command  ? "command"
                                                                       : "dma",
                    u.id, u.fno, static_cast<unsigned long long>(u.count));
    {
        const ipu::IpuStats& is = ipu_->core().stats();
        std::printf("p3fes: IPU commands BCLR %llu IDEC %llu BDEC %llu VDEC %llu FDEC %llu SETIQ %llu SETVQ %llu CSC %llu PACK %llu "
                    "SETTH %llu; in %llu qw, out %llu qw, macroblocks %llu, errors %llu, stalls in/out %llu/%llu\n",
                    static_cast<unsigned long long>(is.commands[0]), static_cast<unsigned long long>(is.commands[1]),
                    static_cast<unsigned long long>(is.commands[2]), static_cast<unsigned long long>(is.commands[3]),
                    static_cast<unsigned long long>(is.commands[4]), static_cast<unsigned long long>(is.commands[5]),
                    static_cast<unsigned long long>(is.commands[6]), static_cast<unsigned long long>(is.commands[7]),
                    static_cast<unsigned long long>(is.commands[8]), static_cast<unsigned long long>(is.commands[9]),
                    static_cast<unsigned long long>(is.in_qwords), static_cast<unsigned long long>(is.out_qwords),
                    static_cast<unsigned long long>(is.macroblocks), static_cast<unsigned long long>(is.errors),
                    static_cast<unsigned long long>(is.input_stalls), static_cast<unsigned long long>(is.output_stalls));
    }
    std::printf("p3fes: memory card: %s\n", memcard_desc_.c_str());
    {
        const hle::sif::AdxiStats as = sif_->iop().adxi_stats();
        std::printf("p3fes: CRI_ADXI ticks %llu, DTX blocks in/out %llu/%llu, urpc %llu, SJX chunks in/out %llu/%llu, RNA commands "
                    "%llu, PSM passes %llu, PCM consumed %llu B, underrun samples %llu, SJ errors %llu, DTX open %u, RNA playing %u\n",
                    static_cast<unsigned long long>(as.ticks), static_cast<unsigned long long>(as.dtx_blocks_in),
                    static_cast<unsigned long long>(as.dtx_blocks_out), static_cast<unsigned long long>(as.urpc_calls),
                    static_cast<unsigned long long>(as.sjx_chunks_in), static_cast<unsigned long long>(as.sjx_chunks_out),
                    static_cast<unsigned long long>(as.rna_commands), static_cast<unsigned long long>(as.psm_passes),
                    static_cast<unsigned long long>(as.pcm_bytes_consumed), static_cast<unsigned long long>(as.underrun_samples),
                    static_cast<unsigned long long>(as.sj_errors), as.dtx_open, as.rna_playing);
    }
    {
        const hle::sif::SkStats sk = sif_->iop().sk_stats();
        std::printf("p3fes: SK %s/%s/%s: modules %s (%u loaded), RPC routed %llu (pending %llu), ticks %llu, %llu instructions, key-ons %llu, "
                    "key-offs %llu (%llu sounding), voices active %u (max %u, longest %llu frames, %llu sweeps, %u inits), voice frames %llu (first %lld), "
                    "mix passes %llu (+%llu silent, %llu stream frames late)%s%s\n",
                    cfg_.sk_mode.c_str(), cfg_.iop_layout.c_str(), cfg_.spu2_interp.c_str(), sk.modules ? "on" : "off", sk.modules_loaded,
                    static_cast<unsigned long long>(sk.rpc_routed), static_cast<unsigned long long>(sk.rpc_pending),
                    static_cast<unsigned long long>(sk.tick_runs), static_cast<unsigned long long>(sk.instructions),
                    static_cast<unsigned long long>(sk.key_ons), static_cast<unsigned long long>(sk.key_offs),
                    static_cast<unsigned long long>(sk.key_offs_sounding), sk.voices_active, sk.voices_active_max,
                    static_cast<unsigned long long>(sk.voice_longest_frames), static_cast<unsigned long long>(sk.volume_sweeps), sk.sd_inits,
                    static_cast<unsigned long long>(sk.voice_frames), sk.first_voice_frame == ~0ull ? -1ll : static_cast<long long>(sk.first_voice_frame),
                    static_cast<unsigned long long>(sk.mix_passes), static_cast<unsigned long long>(sk.mix_passes_skipped),
                    static_cast<unsigned long long>(sk.mix_stream_late), sk.fault.empty() ? "" : ", FAULT ", sk.fault.c_str());
    }
    if (audio_) {
        const audio::NullSink& fp = audio_->fingerprint();
        std::printf("p3fes: %s; first non-silent frame %lld\n", audio_->describe().c_str(),
                    fp.first_non_silent_frame() == ~0ull ? -1ll : static_cast<long long>(fp.first_non_silent_frame()));
    }
    if (flips_.size() >= 2)  // flip 1 is SkyStart's PutDispEnv; flip 2 is RenderWare's first (Milestone 1)
        std::printf("p3fes: first RW flip at vblank %llu (%.3f virtual s), wall %.3f s\n",
                    static_cast<unsigned long long>(flips_[1].vblank), static_cast<double>(flips_[1].cycles) / 294912000.0,
                    flips_[1].wall);
    for (const MarkerEdge& m : markers_)
        std::printf("p3fes: marker %s 0x%X -> 0x%X at vblank %llu (%.3f virtual s, sky %u), wall %.3f s\n", m.what, m.from, m.to,
                    static_cast<unsigned long long>(m.vblank), static_cast<double>(m.cycles) / 294912000.0, m.sky, m.wall);
    const auto un = kernel_->unhandled_log();
    std::printf("p3fes: unhandled hw accesses %llu", static_cast<unsigned long long>(kernel_->unhandled_accesses()));
    std::map<std::pair<u32, bool>, unsigned> uniq;
    for (const hle::UnhandledAccess& a : un) ++uniq[{a.pa, a.write}];
    for (const auto& [k, n] : uniq) std::printf(" %s%08X×%u", k.second ? "W" : "R", k.first, n);
    std::printf("\n");
}

} // namespace p3fes::app
