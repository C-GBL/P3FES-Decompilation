// Private: cdvdfsv (sids 0x80000592/593/595/597/59A/59C) over the sector-level CdvdHle.
// Command set = what SLUS_216.21's libcdvd sends (obs, sceSifCallRpc sites on each client):
//   0x80000592 fn 0   sceCdInit 0x510460          send {mode}       recv 16 {ret, fsv ver, man ver, debug}
//   0x80000593 fn 3   sceCdGetDiskType 0x510E30   recv 4
//              fn 4   sceCdGetError 0x510EF0      recv 4
//              fn 22  sceCdBreak 0x510F88         recv 4
//              fn 34  sceCdMmode 0x511040         send {media} recv 4 (fn/sizes from the table at 0x782728)
//   0x80000595 fn 1   sceCdRead 0x510B80          send 24 {lsn, n, buf, rmode, remain*, readpos*}, NOWAIT
//                                                 + end callback _sceCd_cd_read_intr 0x50F8A8, recv 0
//              fn 5   sceCdSeek 0x510D60          send {lsn}, NOWAIT + end callback _sceCd_cd_callback
//              fn 14  N-cmd disk ready 0x5100B0   recv 4 (sceCdRead fails if it answers 6)
//   0x80000597 fn 0   sceCdLayerSearchFile 0x50FC38  send 300, recv 4; fp DMA'd back to +292
//   0x8000059A/C fn 0 sceCdDiskReady(_old)         send {mode} recv 4
// Everything else is answered with ret 0 and logged as unknown (real cdvdfsv does the same for codes
// it does not know).
#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "iop_core.h"
#include "p3fes/hle/cdvd.h"

namespace p3fes::hle::sif::detail {

namespace cdvd_sid {
inline constexpr u32 kInit = 0x80000592u;
inline constexpr u32 kScmd = 0x80000593u;
inline constexpr u32 kNcmd = 0x80000595u;
inline constexpr u32 kSearch = 0x80000597u;
inline constexpr u32 kDiskReadyOld = 0x8000059Au;
inline constexpr u32 kDiskReady = 0x8000059Cu;
}  // namespace cdvd_sid

// cdvdfsv_unaligned_data_outpacket_t (ps2sdk common/include/libcdvd-rpc.h @ 329e2bb), the 144-byte
// block the IOP DMAs to the read request's +16 address; _sceCd_cd_read_intr 0x50F8A8 copies
// b1len bytes from +16 to b1dst and b2len bytes from +80 to b2dst (obs).
inline constexpr std::size_t kUnalignedBlockSize = 144;
// sceCdlFILE (32 B: lsn, size, name[16], date[8]) + the cdvdman file-table flags word: the 36 bytes
// the IOP DMAs back (ps2sdk cdvdfsv: sizeof(sceCdlFILE) + 4; obs: the EE copies 36 bytes, 0x50FE4C).
inline constexpr std::size_t kCdlFileReplySize = 36;
inline constexpr std::size_t kSearchPacketSize = 300;
inline constexpr std::size_t kSearchPath = 36;
inline constexpr std::size_t kSearchEeDest = 292;
inline constexpr std::size_t kSearchLayer = 296;

// The ISO9660 recording time of a directory record (7 bytes: years since 1900, month, day, hour,
// minute, second, GMT offset) -> sceCdlFILE.date (date[1] s, [2] min, [3] h, [4] day, [5] month,
// [6..7] year little-endian; date[0] is not written by cdvdman (stale), here 0). Formatting per the
// ps2sdk cdvdman CD_cachefile reimplementation (inf for the SCE module).
std::array<u8, 8> cdl_date_from_iso(std::span<const u8, 7> rec);

// Builds the 36-byte reply for a found file. name: identifier as recorded ("DATA.CVM;1"),
// NUL-terminated, truncated to 15 chars, zero padded (inf: the padding bytes are the IOP's stale
// file-table contents). When nothing is found the IOP DMAs its copy of the request's first 36 bytes.
std::array<u8, kCdlFileReplySize> encode_cdl_file(u32 lsn, u32 size, std::string_view identifier,
                                                  const std::array<u8, 8>& date, u32 flags);

class CdvdfsvServer final : public RpcServer {
public:
    explicit CdvdfsvServer(DiscSource* disc);
    std::string_view name() const override { return "cdvdfsv"; }
    bool call(IopCore& core, const RpcRequest& req, RpcReply& reply, u32 ticket) override;
    void tick(IopCore& core, u64 now, const Timebase& tb) override;
    u64 next_deadline() const override;
    void reboot() override;
    void state(StateIo& io, IopCore& core) override;

    CdvdHle* cdvd() { return cdvd_.get(); }
    u64 hook_signals() const { return hook_signals_; }

private:
    struct Pending {
        u32 ticket = 0;
        NcmdKind kind = NcmdKind::Read;
        u32 lsn = 0, sectors = 0, paddr = 0, remain_ee = 0, readpos_ee = 0;
        bool staged = false;          // unaligned destination: data goes through staging_
        std::vector<std::byte> staging;
        u64 deadline = 0;
    };

    std::unique_ptr<CdvdHle> cdvd_;
    std::optional<Pending> pending_;
    std::array<u8, kUnalignedBlockSize> eereadx_{};  // the IOP's static block (stale between reads)
    int error_override_ = -1;  // libcdvd error for N-commands the HLE refused (-1: ask CdvdHle)
    u64 hook_signals_ = 0;
    bool warned_no_disc_ = false;

    bool ncmd(IopCore& core, const RpcRequest& req, RpcReply& reply, u32 ticket);
    void scmd(IopCore& core, const RpcRequest& req, RpcReply& reply);
    void search(IopCore& core, const RpcRequest& req, RpcReply& reply);
    void finish_pending(IopCore& core);
    void build_completion(const Pending& p, bool ok, RpcReply& reply);
    void report_read(IopCore& core, const Pending& p, int err);  // IopConfig::cd_read_sink (observation only)
    int error() const;
};

}  // namespace p3fes::hle::sif::detail
