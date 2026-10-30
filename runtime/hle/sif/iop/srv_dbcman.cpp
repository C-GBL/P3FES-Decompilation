// DBCMAN.IRX (libdbc's IOP side) with the MC2_S1.IRX memory-card driver behind it (mc_mc2s1.h), over the
// card in MEMORY CARD slot 1 (IopConfig::memcard; docs/ANALYSIS/17_memory_card.md). Read from the two
// modules on the disc (LIB31/DBCMAN.IRX, LIB31/MC2_S1.IRX, .text offsets with the module at 0) and from the
// EE client, libdbc 0x51C360-0x51D584.
//
// Servers (sceDbcInit 0x51C3B8): 0x80001300 (base, 144-byte buffer 0x996840 both ways), 0x8000131C
// (sceDbcSendData3, NOWAIT with end function, 1168 bytes at 0x996900) and 0x8000131E/F (sceDbcSendData2,
// 144 bytes, no game caller). Base functions are rpc numbers 0x800013xx dispatched by DBCMAN's table at
// .rodata 0x2560 (index fn - 0x80001301; .text 0x1C88):
//   0x1301 CreateSocket   -> +36 socket index (or -21); links a matching device      (.text 0x1940 / 0x54C)
//   0x1302 DeleteSocket   -> +4  1 / -22                                            (.text 0x1978 / 0x5A4)
//   0x1303 GetDepNumber   -> +4  linked device index / -12                          (.text 0x19AC / 0x5F4)
//   0x1304 SetWorkAddr    -> +0  1; DMAs the connection table to the EE             (.text 0x1C28 / 0x8D0)
//   0x1315/0x1316 Init/ResetSocket -> +4 1 / -22 / -23                              (.text 0x19E0 / 0x1A14)
//   0x1317 GetDeviceStatus -> +4 0 ("status function is not support")              (.text 0x1A48 / 0x718)
//   0x1319 SendData       -> +140 the driver's result (the MC2 command path)       (.text 0x1AF8 / 0x7D0)
//   0x131A ReceiveData    -> +140 1 (MC2_S1 driver entry 3 returns 1)               (.text 0x1B34 / 0x850)
//   0x131D SearchPortSpecific -> +4 socket linked to the port's device / -22 / -12 (.text 0x1A7C / 0x624)
//   0x1363 GetModVersion  -> +0 0x0320 (DBCMAN .data 0x2714; the PCSX2 IOP state holds the same)
//   anything else (incl. 0x1305 GetIopDmabuff and 0x1318 SRData) is the table's default: the buffer back
//   unchanged (SRData: no game caller, its +272 result lies outside the 144-byte reply; logged).
//
// Connection state reaches the EE only by DMA: DBCMAN keeps one word per socket (1 = linked to a device)
// and copies 128 bytes from it -- the 16-word table, 8 bytes, device record 0 and the start of record 1 --
// to the work address after SetWorkAddr, a link or an unlink (.text 0xA4). sceDbcGetConnection 0x51CAD0
// reports connected iff work[socket] == 1; _sceMcFatGetInfo 0x515D80 answers 0x81010013 otherwise.
#include <algorithm>
#include <cstring>
#include <deque>
#include <string>

#include "iop_core.h"
#include "mc_mc2s1.h"
#include "p3fes/hle/memcard/iop_slot.h"
#include "p3fes/state_io.h"

namespace p3fes::hle::sif::detail {
namespace {

constexpr u32 kSidBase = 0x80001300u, kSidSend3 = 0x8000131Cu, kSidSend2a = 0x8000131Eu, kSidSend2b = 0x8000131Fu;
constexpr u32 kModVersion = 0x0320u;
constexpr int kSockets = 16, kDevices = 16;
constexpr s32 kErrNoSocket = -21, kErrBadSocket = -22, kErrNoDevice = -23, kErrNotLinked = -12;

// MC2_S1's DBCMAN device (registered at module start, .text 0x1C80 -> dbcman_4 = .text 0x978 of DBCMAN):
// type 2, field +8 0, its driver table at IOP 0x00062E30 (an IOP identity value: MC2_S1 loaded at 0x5DF30
// in the PCSX2 atlus_logo state, table at +0x4F00 -- obs from that state's iopMemory.bin; it reaches the EE
// in the work-area DMA), port/slot -1 until a card is attached (dbcman_6 = .text 0x1BC: port 2, slot 0).
constexpr u32 kMc2DeviceType = 2, kMc2DriverTable = 0x00062E30u;
constexpr s32 kMc2Port = 2, kMc2Slot = 0;

struct Socket {
    s32 state = 0;  // 0 free, 1 created, 2 linked (DBCMAN .bss 0x2A40, 48 bytes each)
    u32 flags = 0, type = 0;
    s32 port = 0, slot = 0;
    u32 field14 = 0;
    std::array<u8, 16> name{};
    std::array<u32, 2> ee_buf{};
};

struct Device {
    s32 state = 0;  // 0 free, 1 registered, 2 attached, 3 linked (DBCMAN .bss 0x27C0, 40 bytes each)
    u32 type = 0, field8 = 0, driver = 0;
    s32 port = -1, slot = -1;
    std::array<u8, 16> name{};
};

struct Pending {
    u32 ticket = 0;
    u64 deadline = 0;
    RpcReply reply;
};

class DbcmanServer final : public RpcServer {
public:
    std::string_view name() const override { return "dbcman"; }

    void state(StateIo& io, IopCore& core) override {
        io(configured_, latency_, work_addr_, sockets_, devices_, conn_, logged_link_, logged_flush_error_, link_);
        u64 n = pending_.size();
        io(n);
        if (io.loading()) pending_.assign(static_cast<std::size_t>(n), Pending{});
        for (Pending& p : pending_) io(p.ticket, p.deadline, p.reply.rdata, p.reply.writes);
        bool has_mc2 = mc2_ != nullptr;
        io(has_mc2);
        if (io.loading() && has_mc2) {
            // configure()'s construction, without its reboot/device registration (the state carries those).
            const auto& cfg = core.config().memcard;
            slot_cfg_ = cfg;
            mc2_ = std::make_unique<Mc2s1Model>(cfg ? cfg->slot1 : nullptr, cfg ? cfg->rtc : memcard::IopSlotConfig{}.rtc);
        } else if (io.loading()) {
            mc2_.reset();
            slot_cfg_.reset();
        }
        if (mc2_) mc2_->state(io);
    }

    bool call(IopCore& core, const RpcRequest& req, RpcReply& reply, u32 ticket) override {
        configure(core);
        reply.rdata.assign(req.data.begin(), req.data.end());  // DBCMAN answers in the received buffer
        switch (req.sid) {
        case kSidBase:
            base(core, req, reply);
            return true;
        case kSidSend3:
            // .text 0x1BCC: at most 1168 bytes; result word at +1164.
            if (req.data.size() > 1168) {
                core.note_unknown(UnknownEvent::Kind::Function, req.sid, req.fno, "send_data3 longer than 1168 bytes (buffer back unchanged)");
                return true;
            }
            reply.rdata.resize(1168, 0);
            run_mc2(core, reply, 1164);
            return defer(core, ticket, reply);
        case kSidSend2a:
        case kSidSend2b:
            if (req.data.size() > 144) {  // .text 0x1B70
                core.note_unknown(UnknownEvent::Kind::Function, req.sid, req.fno, "send_data2 longer than 144 bytes (buffer back unchanged)");
                return true;
            }
            reply.rdata.resize(144, 0);
            run_mc2(core, reply, 140);
            return defer(core, ticket, reply);
        default:
            core.note_unknown(UnknownEvent::Kind::Function, req.sid, req.fno, "DBCMAN server id not modelled (echoed)");
            return true;
        }
    }

    void tick(IopCore& core, u64 now, const Timebase& /*tb*/) override {
        while (!pending_.empty() && now >= pending_.front().deadline) {
            Pending p = std::move(pending_.front());
            pending_.pop_front();
            core.complete(p.ticket, std::move(p.reply));
        }
    }

    u64 next_deadline() const override { return pending_.empty() ? kNever : pending_.front().deadline; }

    void reboot() override {
        // DBCMAN and MC2_S1 are loaded again after the IOP reboot (sceSifLoadModule #4, #5).
        work_addr_ = 0;
        sockets_ = {};
        devices_ = {};
        conn_.fill(0);
        pending_.clear();
        configured_ = false;  // device 0 is registered (and attached) again from the config
    }

private:
    bool configured_ = false;
    std::shared_ptr<const memcard::IopSlotConfig> slot_cfg_;
    std::unique_ptr<Mc2s1Model> mc2_;
    u64 latency_ = 1;
    u32 work_addr_ = 0;
    std::array<Socket, kSockets> sockets_{};
    std::array<Device, kDevices> devices_{};
    std::array<u32, kSockets> conn_{};
    std::deque<Pending> pending_;
    bool logged_link_ = false, logged_flush_error_ = false;

    void configure(IopCore& core) {
        if (configured_) return;
        configured_ = true;
        const auto& cfg = core.config().memcard;
        if (cfg != slot_cfg_ || !mc2_) {
            slot_cfg_ = cfg;
            mc2_ = std::make_unique<Mc2s1Model>(cfg ? cfg->slot1 : nullptr, cfg ? cfg->rtc : memcard::IopSlotConfig{}.rtc);
            latency_ = std::max<u64>(1, cfg ? cfg->command_latency_cycles : 1);
        }
        mc2_->reboot();
        Device& d = devices_[0];
        d.state = 1;
        d.type = kMc2DeviceType;
        d.field8 = 0;
        d.driver = kMc2DriverTable;
        if (mc2_->card()) {  // card detected by MC2_S1's thread right after its start (.text 0x334)
            d.state = 2;
            d.port = kMc2Port;
            d.slot = kMc2Slot;
        }
    }

    // ---- connection table -------------------------------------------------------------------------
    std::vector<u8> conn_block() const {
        std::vector<u8> b(128, 0);
        for (int i = 0; i < kSockets; ++i) store32(b, 4 * static_cast<std::size_t>(i), conn_[static_cast<std::size_t>(i)]);
        auto put_device = [&](std::size_t off, const Device& d, std::size_t len) {
            std::array<u8, 40> r{};
            store32(r, 0, static_cast<u32>(d.state));
            store32(r, 4, d.type);
            store32(r, 8, d.field8);
            store32(r, 12, d.driver);
            store32(r, 16, static_cast<u32>(d.port));
            store32(r, 20, static_cast<u32>(d.slot));
            std::memcpy(r.data() + 24, d.name.data(), d.name.size());
            std::memcpy(b.data() + off, r.data(), len);
        };
        put_device(72, devices_[0], 40);  // IOP 0x27C0 = table 0x2778 + 72
        put_device(112, devices_[1], 16);
        return b;
    }
    void dma_conn(std::vector<EeWrite>& w) const {
        if (work_addr_ != 0) w.push_back(EeWrite{work_addr_, conn_block()});
    }

    // ---- sockets / devices ------------------------------------------------------------------------------
    static bool name_match(const std::array<u8, 16>& dev, const std::array<u8, 16>& sock) {
        // .text 0xCC4-0xCF4: byte by byte up to and including the device name's NUL.
        for (std::size_t i = 0; i < dev.size(); ++i) {
            if (dev[i] != sock[i]) return false;
            if (dev[i] == 0) return true;
        }
        return true;
    }
    static bool matches(const Socket& s, const Device& d) {
        // .text 0xC00 / 0x1148: flag bit 0 type, bit 1 port + slot, bit 2 the +8/+0x14 field, bit 3 the name.
        if ((s.flags & 1) && d.type != s.type) return false;
        if ((s.flags & 2) && (d.port != s.port || d.slot != s.slot)) return false;
        if ((s.flags & 4) && d.field8 != s.field14) return false;
        if ((s.flags & 8) && !name_match(d.name, s.name)) return false;
        return true;
    }
    int linked_device(int s) const {
        if (s < 0 || s >= kSockets || sockets_[static_cast<std::size_t>(s)].state != 2) return -1;
        return link_[static_cast<std::size_t>(s)];
    }
    int socket_of_device(int dev) const {
        for (int s = 0; s < kSockets; ++s)
            if (sockets_[static_cast<std::size_t>(s)].state == 2 && link_[static_cast<std::size_t>(s)] == dev) return s;
        return -1;
    }
    std::array<int, kSockets> link_{};

    bool socket_valid(u32 s) const { return s < static_cast<u32>(kSockets) && sockets_[s].state > 0; }

    void create_socket(IopCore& core, RpcReply& reply) {
        auto& b = reply.rdata;
        int idx = -1;
        for (int i = 0; i < kSockets; ++i)
            if (sockets_[static_cast<std::size_t>(i)].state <= 0) {
                idx = i;
                break;
            }
        if (idx < 0) {
            put_word(b, 36, static_cast<u32>(kErrNoSocket));
            return;
        }
        Socket& s = sockets_[static_cast<std::size_t>(idx)];
        s = Socket{};
        s.state = 1;
        s.flags = load32(b, 0);
        s.type = load32(b, 4);
        s.port = static_cast<s32>(load32(b, 8));
        s.slot = static_cast<s32>(load32(b, 12));
        s.field14 = load32(b, 16);
        std::memcpy(s.name.data(), b.data() + 20, 16);
        s.ee_buf = {load32(b, 40), load32(b, 44)};
        for (int d = 0; d < kDevices; ++d) {
            Device& dev = devices_[static_cast<std::size_t>(d)];
            if (dev.state == 2 && matches(s, dev)) {  // .text 0x154C: link to the first attached match
                dev.state = 3;
                s.state = 2;
                link_[static_cast<std::size_t>(idx)] = d;
                conn_[static_cast<std::size_t>(idx)] = 1;
                dma_conn(reply.writes);
                if (!logged_link_) {
                    logged_link_ = true;
                    core.log("[iop] dbcman: socket " + std::to_string(idx) + " linked to the memory card in slot 1 (" +
                             (mc2_->card() ? mc2_->card()->name() : std::string("?")) + ")");
                }
                break;
            }
        }
        put_word(b, 36, static_cast<u32>(idx));
    }

    void delete_socket(RpcReply& reply) {
        const u32 s = load32(reply.rdata, 0);
        if (!socket_valid(s)) {
            put_word(reply.rdata, 4, static_cast<u32>(kErrBadSocket));
            return;
        }
        if (sockets_[s].state == 2) devices_[static_cast<std::size_t>(link_[s])].state = 2;  // .text 0x1618
        sockets_[s] = Socket{};
        conn_[s] = 0;
        dma_conn(reply.writes);
        put_word(reply.rdata, 4, 1);
    }

    void base(IopCore& core, const RpcRequest& req, RpcReply& reply) {
        auto& b = reply.rdata;
        if (b.size() < 144) b.resize(144, 0);
        switch (req.fno) {
        case 0x80001301u:
            create_socket(core, reply);
            break;
        case 0x80001302u:
            delete_socket(reply);
            break;
        case 0x80001303u: {
            const int d = linked_device(static_cast<int>(load32(b, 0)));
            put_word(b, 4, d >= 0 ? static_cast<u32>(d) : static_cast<u32>(kErrNotLinked));
            break;
        }
        case 0x80001304u:
            work_addr_ = load32(b, 4);
            dma_conn(reply.writes);
            put_word(b, 0, 1);
            break;
        case 0x80001315u:
        case 0x80001316u:
        case 0x8000131Au: {
            const u32 s = load32(b, 0);
            const s32 r = !socket_valid(s) ? kErrBadSocket : linked_device(static_cast<int>(s)) < 0 ? kErrNoDevice : 1;
            put_word(b, req.fno == 0x8000131Au ? 140u : 4u, static_cast<u32>(r));
            break;
        }
        case 0x80001317u:
            put_word(b, 4, 0);
            break;
        case 0x80001319u:
            run_mc2(core, reply, 140);
            break;
        case 0x8000131Du: {
            // .text 0x624: flags := 2 (port + slot) in the request copy, then the first attached device on
            // that port/slot and the socket linked to it.
            put_word(b, 8, 2);
            const s32 port = static_cast<s32>(load32(b, 16)), slot = static_cast<s32>(load32(b, 20));
            int dev = -1;
            for (int d = 0; d < kDevices && dev < 0; ++d)
                if (devices_[static_cast<std::size_t>(d)].state >= 2 && devices_[static_cast<std::size_t>(d)].port == port &&
                    devices_[static_cast<std::size_t>(d)].slot == slot)
                    dev = d;
            const int s = dev >= 0 ? socket_of_device(dev) : -1;
            put_word(b, 4, static_cast<u32>(dev < 0 ? kErrNotLinked : s < 0 ? kErrBadSocket : s));
            break;
        }
        case 0x80001363u:
            put_word(b, 0, kModVersion);
            break;
        default:
            core.note_unknown(UnknownEvent::Kind::Function, req.sid, req.fno, "DBCMAN function outside its table (buffer back unchanged, as DBCMAN)");
            break;
        }
    }

    // .text 0x7D0: socket -> linked device -> driver entry 5 (MC2_S1) with {cmd +4, size +8, data +12}.
    void run_mc2(IopCore& core, RpcReply& reply, std::size_t result_off) {
        auto& b = reply.rdata;
        const u32 s = load32(b, 0);
        s32 result;
        if (!socket_valid(s)) {
            result = kErrBadSocket;
        } else if (linked_device(static_cast<int>(s)) < 0) {
            result = kErrNoDevice;
        } else {
            const u32 dev = static_cast<u32>(linked_device(static_cast<int>(s)));
            const std::array<u32, 2> bufs = sockets_[s].ee_buf;
            Mc2s1Model::Io io;
            io.to_buf0 = [&](u32 off, std::span<const u8> bytes) {
                // dbcman_9 (.text 0x428): offset 64-aligned, size a multiple of 128, else nothing moves.
                if ((off & 63u) != 0 || (bytes.size() & 127u) != 0) return;
                reply.writes.push_back(EeWrite{bufs[0] + off, std::vector<u8>(bytes.begin(), bytes.end())});
            };
            io.to_buf = [&](u32 index, std::span<const u8> bytes) {
                if ((bytes.size() & 127u) != 0) return;  // dbcman_8 (.text 0x31C)
                reply.writes.push_back(EeWrite{bufs[index & 1u], std::vector<u8>(bytes.begin(), bytes.end())});
            };
            io.from_ee = [&](u32 addr, std::span<u8> out) {
                if (core.ee_load(addr, out)) return true;
                core.note_unknown(UnknownEvent::Kind::Dma, addr, static_cast<u32>(out.size()), "MC2 page source outside EE memory (stale data programmed)");
                return false;
            };
            io.unmodelled = [&](u32 cmd, const char* what) { core.note_unknown(UnknownEvent::Kind::Function, kSidSend3, cmd, what); };
            const u32 cmd = load32(b, 4);
            u32 size = load32(b, 8);
            result = mc2_->send(dev, cmd, size, std::span<u8>(b).subspan(12, mc2req::kSize), io);
            store32(b, 8, size);
            if (core.config().trace)
                core.log("[iop] mc2 cmd " + std::to_string(cmd) + " page " + std::to_string(static_cast<s32>(load32(b, 12))) + " count " +
                         std::to_string(static_cast<s32>(load32(b, 16))) + " -> " + std::to_string(result));
            memcard::Card* card = mc2_->card();
            std::string err;
            if (card && card->dirty() && !card->flush(&err) && !logged_flush_error_) {
                logged_flush_error_ = true;
                core.log("[iop] dbcman: memory card not saved: " + err);
            }
        }
        if (b.size() < result_off + 4) b.resize(result_off + 4, 0);
        store32(b, result_off, static_cast<u32>(result));
    }

    bool defer(IopCore& core, u32 ticket, RpcReply& reply) {
        pending_.push_back(Pending{ticket, core.now() + latency_, std::move(reply)});
        return false;
    }
};

}  // namespace

std::unique_ptr<RpcServer> make_dbcman_server() { return std::make_unique<DbcmanServer>(); }

}  // namespace p3fes::hle::sif::detail
