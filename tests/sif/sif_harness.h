// Test harness for runtime/hle/sif: a fake HwBus (records dma_complete, owns the time base, routes
// MMIO) and `EeSide`, a C++ re-enactment of what SLUS_216.21's own EE libraries do on the SIF --
// sceSifInitCmd 0x506148, sceSifInitRpc 0x5068A8, _sceSifSendCmd 0x5064F8 + the 16-byte sync packet of
// sceSifSetDma 0x506088, sceSifCmdIntrHdlr 0x5066B0, _request_end 0x506BA8, sceSifBindRpc 0x507050,
// sceSifCallRpc 0x507230, sceSifCheckStatRpc 0x507430, _sceFs_Rcv_Intr 0x507C38,
// _sceCd_cd_read_intr 0x50F8A8 -- at the game's own EE addresses (read from the ELF's instructions).
// It is the "EE" the HLE answers; the HLE is never told it is a test.
#pragma once

#include <doctest.h>

#include <array>
#include <cstring>
#include <functional>
#include <map>
#include <span>
#include <string>
#include <vector>

#include "p3fes/ee_context.h"
#include "p3fes/ee_memory.h"
#include "p3fes/hle/disc_source.h"
#include "p3fes/hle/hw_bus.h"
#include "p3fes/hle/sif/protocol.h"
#include "p3fes/hle/sif/sif.h"

namespace p3fes::test {

using namespace p3fes::hle;
using namespace p3fes::hle::sif;

class FakeBus final : public HwBus {
public:
    struct Range {
        u32 begin, end;
        HwDevice* dev;
    };
    std::vector<Range> ranges;
    std::array<DmaChannelHandler*, 10> handlers{};
    std::vector<unsigned> completions;  // every dma_complete(ch), in order
    unsigned pending_ch5 = 0;           // not yet "delivered" to the EE handler
    Timebase tb{};

    void map(u32 b, u32 e, HwDevice* d) override { ranges.push_back({b, e, d}); }
    void set_dma_handler(unsigned ch, DmaChannelHandler* h) override { handlers.at(ch) = h; }
    void raise_intc(unsigned) override {}
    void dma_complete(unsigned ch) override {
        completions.push_back(ch);
        if (ch == 5) ++pending_ch5;
    }
    const Timebase& time() const override { return tb; }
    HwDevice* find(u32 pa) {
        for (auto& r : ranges)
            if (pa >= r.begin && pa < r.end) return r.dev;
        return nullptr;
    }
    u32 read32(u32 pa) override { return find(pa) ? find(pa)->read32(pa) : 0; }
    void write32(u32 pa, u32 v) override {
        if (auto* d = find(pa)) d->write32(pa, v);
    }
    u64 read64(u32 pa) override { return read32(pa); }
    void write64(u32 pa, u64 v) override { write32(pa, static_cast<u32>(v)); }
    u128 read128(u32 pa) override { return u128::from_u64(read32(pa)); }
    void write128(u32 pa, const u128& v) override { write32(pa, v.u32[0]); }
    u8 read8(u32 pa) override { return static_cast<u8>(read32(pa)); }
    u16 read16(u32 pa) override { return static_cast<u16>(read32(pa)); }
    void write8(u32 pa, u8 v) override { write32(pa, v); }
    void write16(u32 pa, u16 v) override { write32(pa, v); }

    void advance(u64 cycles) { tb.cycles += cycles; }
    void vblank() { ++tb.vblanks; }
};

// The game's EE-side addresses (obs).
namespace ee {
inline constexpr u32 kCmdData = 0x00966A58;   // _sif_cmd_data
inline constexpr u32 kRecvBuf = 0x00966980;   // its pktbuf (sent to the IOP)
inline constexpr u32 kPktTable = 0x00966C80;  // sifrpc packet table, 32 x 64
inline constexpr u32 kSyncPkt = 0x007BDD00;   // libsifcmd's 16-byte sync packet
inline constexpr u32 kDmaList = 0x01F00000;   // scratch (main-thread stack band)
inline constexpr u32 kSendScratch = 0x01F01000;
inline constexpr u32 kClients = 0x00968000;   // our client structs, 64 B apart
inline constexpr u32 kFsResultBuf = 0x00968C80;  // fileio result buffer (sceFsInit 0x5082B0)
}  // namespace ee

class EeSide {
public:
    FakeBus bus;
    EEMemory mem;
    EEContext ctx;
    SifHle sif;
    std::array<u32, 32> sregs{};
    u32 iopbuf = 0;
    u32 pid = 1;
    std::vector<std::vector<u8>> packets;  // every packet the EE handler dispatched (copies)
    std::map<u32, int> signaled;           // client -> request_end semaphore signals
    std::function<void(u32 end_param)> on_end;  // CALL end function
    u32 next_client = ee::kClients;

    explicit EeSide(IopConfig cfg = {}, DiscSource* disc = nullptr) : sif(mem, bus, quiet(std::move(cfg)), disc) {
        ctx.memory = &mem;
        sif.attach();
        // libsifcmd's sync packet bytes (ELF .data at 0x7BDD00).
        const u32 sync[4] = {16, 0, 0x80000004u, 0};
        write(ee::kSyncPkt, std::as_bytes(std::span(sync)));
    }
    static IopConfig quiet(IopConfig c) {
        if (!c.log) c.log = [](std::string_view) {};
        return c;
    }

    // ---- memory ------------------------------------------------------------------------------------
    void write(u32 a, std::span<const std::byte> b) {
        u8* p = mem.resolve(a, static_cast<u32>(b.size()));
        REQUIRE(p != nullptr);
        std::memcpy(p, b.data(), b.size());
    }
    void write(u32 a, std::span<const u8> b) { write(a, std::as_bytes(b)); }
    void w32(u32 a, u32 v) { mem.write<u32>(a, v); }
    u32 r32(u32 a) const { return mem.read<u32>(a); }
    std::vector<u8> read(u32 a, u32 n) const {
        std::vector<u8> v(n);
        const u8* p = mem.resolve(a, n);
        REQUIRE(p != nullptr);
        std::memcpy(v.data(), p, n);
        return v;
    }

    // ---- syscalls ------------------------------------------------------------------------------------
    u64 sys(int n, u32 a0 = 0, u32 a1 = 0) {
        ctx.gpr[GPR_A0].u64[0] = a0;
        ctx.gpr[GPR_A1].u64[0] = a1;
        return sif.syscall(ctx, n);
    }
    u32 get_reg(u32 r) { return static_cast<u32>(sys(0x7A, r)); }
    void set_reg(u32 r, u32 v) { sys(0x79, r, v); }

    // sceSifSetDma public API: the list plus libsifcmd's sync packet when `sync`.
    u32 set_dma(std::vector<DmaTransfer> ts, bool sync = true) {
        if (sync) ts.push_back(DmaTransfer{ee::kSyncPkt, iopbuf, 16, 0x44});
        std::vector<u8> list(ts.size() * kDmaTransferSize);
        for (std::size_t i = 0; i < ts.size(); ++i) encode_dma_transfer(ts[i], std::span(list).subspan(i * 16, 16));
        write(ee::kDmaList, list);
        return static_cast<u32>(sys(0x77, ee::kDmaList, static_cast<u32>(ts.size())));
    }

    // _sceSifSendCmd 0x5064F8: header fields, extra data first, the packet to the IOP buffer (0x44).
    u32 send_cmd(u32 cid, u32 pkt_ee, u32 psize, u32 src = 0, u32 dest = 0, u32 size = 0) {
        std::vector<DmaTransfer> ts;
        u32 w0 = psize & 0xFF;
        if (size > 0) {
            w0 |= size << 8;
            w32(pkt_ee + 4, dest);
            ts.push_back(DmaTransfer{src, dest, size, 0});
        } else {
            w32(pkt_ee + 4, 0);
        }
        w32(pkt_ee + 0, w0);
        w32(pkt_ee + 8, cid);
        ts.push_back(DmaTransfer{pkt_ee, iopbuf, psize, 0x44});
        return set_dma(std::move(ts));
    }

    // "Check point": the kernel delivers each pending DMAC ch5 completion to sceSifCmdIntrHdlr.
    int pump() {
        int n = 0;
        while (bus.pending_ch5 > 0) {
            --bus.pending_ch5;
            interrupt();
            ++n;
        }
        return n;
    }
    // sceSifCmdIntrHdlr 0x5066B0.
    void interrupt() {
        u8* rb = mem.resolve(ee::kRecvBuf, 128);
        const u32 psize = rb[0];
        if (psize == 0) return;
        const u32 quads = (psize + 15) / 16;
        std::vector<u8> pkt(rb, rb + quads * 16);
        rb[0] = 0;
        sys(-0x78);  // isceSifSetDChain
        packets.push_back(pkt);
        const u32 cid = load32(pkt, 8);
        if (cid == cid::kSetSreg) sregs.at(load32(pkt, 16) & 31) = load32(pkt, 20);
        if (cid == cid::kRpcEnd) request_end(pkt);
        if (cid == cid::kFileioResult) fs_result();
    }
    // _request_end 0x506BA8 (SCE client layout: +0 pkt, +4 rpc_id, +8 sema, +20 buf, +28 end fn,
    // +32 end param, +36 server).
    void request_end(const std::vector<u8>& pkt) {
        const u32 cd = load32(pkt, 28);
        const u32 req = load32(pkt, 32);
        if (req == cid::kRpcCall) {
            if (r32(cd + 28) != 0 && on_end) on_end(r32(cd + 32));
        } else if (req == cid::kRpcBind) {
            w32(cd + 36, load32(pkt, 36));
            w32(cd + 20, load32(pkt, 40));
        }
        if (static_cast<s32>(r32(cd + 8)) >= 0) ++signaled[cd];
        const u32 p = r32(cd + 0);
        if (p) {
            w32(p + 24, 0);
            w32(p + 16, r32(p + 16) & ~1u);
        }
        w32(cd + 0, 0);
    }
    // _sceFs_Rcv_Intr 0x507C38 with one result buffer.
    int fs_results = 0;
    void fs_result() {
        const u32 b = ee::kFsResultBuf;
        ++fs_results;
        const u32 res = r32(b + 8), size = r32(b + 12);
        if (static_cast<s32>(r32(b + 0)) >= 0 && size) write(res, read(b + 16, size));
        if (r32(b + 4) == 2) {  // read: head/tail
            const u32 hl = r32(b + 20), tl = r32(b + 24), hd = r32(b + 28), td = r32(b + 32);
            if (hl) write(hd, read(b + 36, hl));
            if (tl) write(td, read(b + 100, tl));
        }
    }

    // ---- sifcmd / sifrpc init ------------------------------------------------------------------------
    // sceSifInitCmd 0x506148 (the path where the kernel's 0x80000000 is still 0).
    void init_cmd() {
        sys(0x78);  // D5_CHCR.STR clear -> sceSifSetDChain
        iopbuf = get_reg(reg::kSysSubAddr);
        if (iopbuf != 0) {
            w32(ee::kSendScratch + 16, ee::kRecvBuf);
            send_cmd(cid::kChangeSaddr, ee::kSendScratch, 20);
            return;
        }
        int spins = 0;
        while (!(get_reg(reg::kSmFlag) & flag::kCmdInit)) REQUIRE(++spins < 1000);
        iopbuf = get_reg(reg::kSubAddr);
        set_reg(reg::kSysSubAddr, iopbuf);
        set_reg(reg::kSysMainAddr, ee::kCmdData);
        w32(ee::kSendScratch + 12, 0);
        w32(ee::kSendScratch + 16, ee::kRecvBuf);
        send_cmd(cid::kInitCmd, ee::kSendScratch, 20);
    }
    // sceSifInitRpc 0x5068A8.
    void init_rpc() {
        init_cmd();
        for (u32 i = 0; i < 32; ++i) w32(ee::kPktTable + i * 64 + 16, 0);
        if (get_reg(reg::kSysRpcInit)) return;
        const u32 p = ee::kPktTable + 64;
        w32(p + 12, 1);
        send_cmd(cid::kInitCmd, p, 16);
        int spins = 0;
        while (sregs[0] == 0) {
            pump();
            REQUIRE(++spins < 1000);
        }
        set_reg(reg::kSysRpcInit, 1);
    }

    // _sceRpcGetPacket 0x506A70.
    u32 get_packet() {
        for (u32 rid = 0; rid < 32; ++rid) {
            const u32 p = ee::kPktTable + rid * 64;
            if (r32(p + 16) & 1) continue;
            w32(p + 16, (rid << 16) | 5);
            const u32 id = pid;
            pid = pid ? pid + 1 : 2;
            w32(p + 24, id);
            w32(p + 20, p);
            return p;
        }
        FAIL("rpc packet table full");
        return 0;
    }
    u32 new_client() {
        const u32 cd = next_client;
        next_client += 64;
        for (u32 i = 0; i < 64; i += 4) w32(cd + i, 0);
        return cd;
    }
    // sceSifCheckStatRpc 0x507430.
    bool check_stat(u32 cd) const {
        const u32 p = r32(cd);
        if (!p) return false;
        if (r32(cd + 4) != r32(p + 24)) return false;
        return (r32(p + 16) & 1) != 0;
    }
    // sceSifBindRpc in blocking mode, looped like every client does until the server is non-zero.
    u32 bind(u32 sid) {
        const u32 cd = new_client();
        for (int tries = 0; tries < 8; ++tries) {
            const u32 p = get_packet();
            w32(cd + 16, 0);
            w32(cd + 36, 0);
            w32(cd + 0, p);
            w32(cd + 4, r32(p + 24));
            w32(cd + 8, 1);  // a semaphore id
            w32(p + 32, sid);
            w32(p + 20, p);
            w32(p + 28, cd);
            send_cmd(cid::kRpcBind, p, 64);
            pump();
            if (r32(cd + 36) != 0) return cd;
        }
        FAIL("bind never returned a server");
        return cd;
    }
    // sceSifCallRpc. Returns false if the call did not complete (blocking mode) in one pump.
    bool call(u32 cd, u32 fno, u32 mode, u32 send_ee, u32 ssize, u32 recv_ee, u32 rsize, u32 end_fn = 0,
              u32 end_param = 0) {
        const u32 p = get_packet();
        w32(cd + 32, end_param);
        w32(cd + 4, r32(p + 24));
        w32(cd + 0, p);
        w32(cd + 28, end_fn);
        w32(p + 32, fno);
        w32(p + 36, ssize);
        w32(p + 40, recv_ee);
        w32(p + 44, rsize);
        w32(p + 20, p);
        w32(p + 52, r32(cd + 36));
        w32(p + 28, cd);
        if (mode & 1) {
            w32(p + 48, end_fn ? 1 : 0);
            w32(cd + 8, static_cast<u32>(-1));
        } else {
            w32(p + 48, 1);
            w32(cd + 8, 2);
        }
        const int before = signaled[cd];
        send_cmd(cid::kRpcCall, p, 64, send_ee, r32(cd + 20), ssize);
        if (mode & 1) return true;
        pump();
        return signaled[cd] > before;
    }
    // Convenience: blocking call with send bytes placed at kSendScratch + 0x200, reply at +0x800.
    std::vector<u8> call_sync(u32 cd, u32 fno, std::span<const u8> send, u32 rsize) {
        const u32 s = ee::kSendScratch + 0x200, r = ee::kSendScratch + 0x800;
        if (!send.empty()) write(s, send);
        for (u32 i = 0; i < rsize; i += 4) w32(r + i, 0xCDCDCDCDu);
        REQUIRE(call(cd, fno, 0, s, static_cast<u32>(send.size()), r, rsize));
        return rsize ? read(r, rsize) : std::vector<u8>{};
    }
};

inline std::vector<u8> words(std::initializer_list<u32> w) {
    std::vector<u8> v(w.size() * 4);
    std::size_t i = 0;
    for (u32 x : w) {
        store32(v, i, x);
        i += 4;
    }
    return v;
}

// An in-memory disc: sector n byte i = pattern(n, i); three root files at fixed LSNs.
class SynthDisc final : public DiscSource {
public:
    SynthDisc() {
        id_.sectors = kSectors;
        id_.kind = DiscSourceKind::IsoImage;
    }
    static constexpr u32 kSectors = 4096;
    static u8 pattern(u32 lsn, u32 i) { return static_cast<u8>((lsn * 13u + i * 5u + 1u) & 0xFFu); }
    Result<std::size_t> read_sectors(u32 lsn, u32 count, std::span<std::byte> dst) override {
        auto c = check_read(lsn, count, dst);
        if (!c) return c;
        for (u32 s = 0; s < count; ++s)
            for (u32 i = 0; i < kSectorSize; ++i) dst[static_cast<std::size_t>(s) * kSectorSize + i] = std::byte{pattern(lsn + s, i)};
        ++reads;
        return static_cast<std::size_t>(count) * kSectorSize;
    }
    u32 sector_count() const override { return kSectors; }
    const DiscIdentity& identity() const override { return id_; }
    Result<std::optional<DiscFile>> find_file(std::string_view path) override {
        if (path == "\\DATA.CVM;1") return std::optional<DiscFile>{DiscFile{1000, 3 * kSectorSize + 17, "DATA.CVM;1", {108, 1, 4, 14, 55, 42, 36}}};
        if (path == "\\BGM.CVM;1") return std::optional<DiscFile>{DiscFile{2000, kSectorSize, "BGM.CVM;1"}};
        return std::optional<DiscFile>{};
    }
    int reads = 0;

private:
    DiscIdentity id_;
};

}  // namespace p3fes::test
