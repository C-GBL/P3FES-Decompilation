// CDVD HLE: the cdvdfsv command surface the game's libcdvd talks to, served from a DiscSource.
//
// Contract: docs/RUNTIME_CONTRACT.md §2.1 (L-01..L-06) and §4.1 (I-04..I-08);
// docs/ANALYSIS/11_file_io.md §3 and §5. Libcdvd behaviour cited below was read from the game's
// own copy (ida/logs/file_io_cdvd.txt); constants are ps2sdk libcdvd-common.h names.
//
// N-commands (read, seek) are asynchronous with one request in flight, exactly like the game's
// libcdvd: issuing one takes the ncmd semaphore (`_sceCd_ncmd_prechk 0x50FF58`) and sets
// `sceCd_c_cb_sem 0x780BB4` = 1 (`sceCdRead 0x510B80`); a second N-command while one is in flight
// is rejected (Issue::Busy, what the game sees as "Ncmd fail sema" and sceCdRead returning 0).
// Data reaches the destination only when the request completes, in service()/sync(). Completion
// runs the hooks once, in the order of `_sceCd_cd_callback 0x50F698` (no EE callback thread:
// `sceCdInitEeCB` is never called):
//     1. hooks.signal_ncmd_sema  -> iSignalSema(sceCd_ncmd_semid 0x780BA8)
//     2. hooks.clear_cb_sem      -> sceCd_c_cb_sem 0x780BB4 = 0
// so recompiled libcdvd's `sceCdSync(1)` (which polls sceCd_c_cb_sem and the RPC status) sees the
// request end and the next `_sceCd_ncmd_prechk` finds the semaphore available. This class has no
// threads and touches no guest memory except the destination span it was given.
//
// Error mapping (formats::Result): Unsupported = a request the HLE does not model (datapattern
// != 0, zero sectors, read_toc); Overrun = LSN range outside the disc or destination too small;
// DiscSource errors pass through. Guest-visible outcomes (Busy, libcdvd error codes) are values.
#pragma once

#include <functional>
#include <optional>
#include <span>
#include <string_view>

#include "p3fes/ee_memory.h"
#include "p3fes/hle/disc_source.h"

namespace p3fes {
class StateIo;  // p3fes/state_io.h
}

namespace p3fes::hle {

// libcdvd constants (tools/third_party/ps2sdk common/include/libcdvd-common.h @ 329e2bb).
namespace cd {
inline constexpr int kErrNone = 0x00;     // SCECdErNO
inline constexpr int kErrAbort = 0x01;    // SCECdErABRT (sceCdBreak)
inline constexpr int kErrRead = 0x30;     // SCECdErREAD (host read failed)
inline constexpr u8 kSecS2048 = 0;        // SCECdSecS2048
inline constexpr u8 kSecS2328 = 1;        // SCECdSecS2328 (sceCdRead sizes 2328*n)
inline constexpr u8 kSecS2340 = 2;        // SCECdSecS2340 (sceCdRead sizes 2340*n)
inline constexpr int kMmodeCd = 1;        // SCECdMmodeCd
inline constexpr int kMmodeDvd = 2;       // SCECdMmodeDvd (the game calls sceCdMmode(2))
inline constexpr int kDiskTypePs2Dvd = 0x14;  // SCECdPS2DVD (RUNTIME_CONTRACT L-06)
inline constexpr int kReady = 2;          // SCECdComplete (sceCdDiskReady, I-08)
inline constexpr int kStatPause = 0x0A;   // SCECdStatPause
inline constexpr int kStatRead = 0x06;    // SCECdStatRead
inline constexpr int kStatSeek = 0x12;    // SCECdStatSeek
inline constexpr int kInitExit = 5;       // sceCdInit(SCECdEXIT)
inline constexpr std::size_t kMaxSearchPath = 255;  // sceCdLayerSearchFile copies <= 255 chars + NUL
}  // namespace cd

// sceCdRMode {trycount, spindlctrl, datapattern, pad}. The game always passes {0,0,0} on its data
// path (srd_exec_dvd 0x558138); ADX streams toggle spindlctrl (recorded, no effect).
struct ReadMode {
    u8 trycount = 0;
    u8 spindlctrl = 0;
    u8 datapattern = cd::kSecS2048;
};

// sceCdCbfunc_num of the in-flight N-command (sceCdRead sets 1, sceCdSeek sets 4).
enum class NcmdKind : u8 { Read = 1, Seek = 4 };

// Outcome of issuing an N-command. Busy: one is already in flight (libcdvd returns 0).
enum class Issue : u8 { Accepted, Busy };

// sceCdSync(mode): Block = 0 waits for completion, Poll = 1 returns immediately.
enum class SyncMode : u8 { Block = 0, Poll = 1 };

struct NcmdCompletion {
    NcmdKind kind = NcmdKind::Read;
    u32 lsn = 0;
    u32 sectors = 0;           // 0 for a seek
    int error = cd::kErrNone;  // what sceCdGetError reports afterwards
};

// Kernel-HLE bindings for the completion side effects (see file comment). Empty hooks are allowed
// (an HLE that intercepts sceCdSync itself can use sync()'s return value instead).
struct CompletionHooks {
    std::function<void(const NcmdCompletion&)> signal_ncmd_sema;
    std::function<void(const NcmdCompletion&)> clear_cb_sem;
};

struct SearchOutcome {
    Issue issue = Issue::Accepted;  // Busy: an N-command is in flight (sceCdLayerSearchFile returns 0)
    std::optional<DiscFile> file;   // nullopt: absent from the disc directory (returns 0)
};

class CdvdHle {
public:
    // `disc` must outlive this object.
    explicit CdvdHle(DiscSource& disc, CompletionHooks hooks = {});

    CdvdHle(const CdvdHle&) = delete;
    CdvdHle& operator=(const CdvdHle&) = delete;

    // --- cdvdfsv init (0x80000592) ----------------------------------------------------------
    // sceCdInit(mode): clears the drive error; 1 = success (contract I-04). Does not cancel an
    // in-flight N-command (libcdvd only syncs S-commands first, sceCdSyncS(1) in 0x510460).
    int init(int mode);

    // --- N-commands (0x80000595) ------------------------------------------------------------
    // sceCdRead(lsn, sectors, buf, mode) (ncmd fn 1). `dst` is the resolved guest buffer (see
    // guest_read_buffer) and must stay valid until completion; it is written only then.
    // Unsupported: mode.datapattern != 0 (2328/2340-byte sectors) or sectors == 0.
    // Overrun: [lsn, lsn+sectors) outside the disc or dst smaller than sectors*2048.
    Result<Issue> read(u32 lsn, u32 sectors, std::span<std::byte> dst, ReadMode mode);

    // sceCdSeek(lsn) (ncmd fn 5): completes like a read without transferring data.
    Result<Issue> seek(u32 lsn);

    // sceCdSync(mode): 0 = no N-command in flight (any pending one has completed), 1 = still
    // busy (Poll only). Poll runs one service() step first; Block completes the request now.
    int sync(SyncMode mode);

    // One step of the "IOP": advances the in-flight request by one latency step or completes it.
    // Returns true when this call delivered a completion. A kernel HLE that leaves sceCdSync to
    // recompiled code calls this from its scheduler (e.g. per vblank).
    bool service();

    // sceCdBreak: aborts the in-flight N-command; it completes on the next service()/sync() with
    // SCECdErABRT and no data. 1 = success (also when idle).
    int break_ncmd();

    // Number of service() steps a request stays in flight before completing (default 0: the
    // first service()/Poll completes it). Applies to requests issued afterwards.
    void set_latency(u32 service_steps) { latency_ = service_steps; }

    // --- S-commands (0x80000593) ------------------------------------------------------------
    int get_error() const { return error_; }                     // sceCdGetError
    int get_disk_type() const { return cd::kDiskTypePs2Dvd; }    // sceCdGetDiskType(2)
    int status() const;                                          // sceCdStatus
    int mmode(int media);  // sceCdMmode: records CD/DVD and returns 1; 0 for other values
    int media_mode() const { return media_mode_; }               // 0 until mmode()

    // sceCdDiskReady(mode) (0x8000059C / 0x8000059A): the image is always ready.
    int disk_ready(int /*mode*/) const { return cd::kReady; }

    // sceCdGetToc: stubbed. SLUS_216.21 links no caller (11 §3) and the PS2 DVD TOC layout has not
    // been observed for this disc, so this fails closed with Unsupported instead of inventing bytes.
    Result<std::size_t> read_toc(std::span<std::byte> dst);

    // --- searchfile (0x80000597) ------------------------------------------------------------
    // sceCdSearchFile / sceCdLayerSearchFile(fp, path, layer 0): Busy while an N-command is in
    // flight (libcdvd checks the ncmd semaphore and sceCdSync(1)); Unsupported for paths longer
    // than libcdvd's 255 characters; otherwise DiscSource::find_file().
    Result<SearchOutcome> search_file(std::string_view path);

    // --- state for the kernel HLE and tests ---------------------------------------------------
    bool busy() const { return pending_.has_value(); }  // == sceCd_c_cb_sem set, ncmd sema taken
    const ReadMode& last_read_mode() const { return last_read_mode_; }
    std::optional<Error> last_host_error() const { return last_host_error_; }  // cause of kErrRead
    u64 completions() const { return completions_; }
    DiscSource& disc() { return disc_; }
    // Machine state (iop_state.cpp). A pending read's destination is a host span: the caller encodes it
    // (`encode`, saving) and turns the stored value back into a span (`decode`, loading).
    void state(StateIo& io, const std::function<u64(std::span<std::byte>)>& encode,
               const std::function<std::span<std::byte>(u64, std::size_t)>& decode);

private:
    struct Pending {
        NcmdKind kind;
        u32 lsn;
        u32 sectors;
        std::span<std::byte> dst;
        u32 steps_left;
        bool aborted;
    };

    void complete();

    DiscSource& disc_;
    CompletionHooks hooks_;
    std::optional<Pending> pending_;
    ReadMode last_read_mode_{};
    std::optional<Error> last_host_error_;
    u64 completions_ = 0;
    u32 latency_ = 0;
    int error_ = cd::kErrNone;
    int media_mode_ = 0;
};

// Resolves sceCdRead's guest `buf` for read(): `sectors`*2048 bytes at guest address `buf`
// through EEMemory::resolve (KSEG0/KSEG1/uncached mirrors fold onto main RAM; libcdvd's own
// end-callback writes through the 0x20000000 uncached mirror). Overrun if the range is not
// backed by one region. The game's buffers are 64-byte aligned (L-03); alignment is not required.
// Inline so p3fes_cdvd itself does not depend on p3fes_runtime; callers link p3fes_runtime.
inline Result<std::span<std::byte>> guest_read_buffer(EEMemory& mem, u32 buf, u32 sectors) {
    const u64 len = static_cast<u64>(sectors) * kSectorSize;
    if (len > 0xFFFFFFFFull) return Error{FormatError::Overrun, "sceCdRead length exceeds the EE address space"};
    u8* p = mem.resolve(buf, static_cast<u32>(len));
    if (p == nullptr) return Error{FormatError::Overrun, "sceCdRead buffer is not inside one EE memory region"};
    return std::span<std::byte>{reinterpret_cast<std::byte*>(p), static_cast<std::size_t>(len)};
}

}  // namespace p3fes::hle
