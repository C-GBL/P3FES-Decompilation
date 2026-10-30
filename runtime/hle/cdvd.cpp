// CdvdHle: cdvdfsv command surface over a DiscSource. See p3fes/hle/cdvd.h for the contract.
#include "p3fes/hle/cdvd.h"

namespace p3fes::hle {

CdvdHle::CdvdHle(DiscSource& disc, CompletionHooks hooks) : disc_(disc), hooks_(std::move(hooks)) {}

int CdvdHle::init(int /*mode*/) {
    error_ = cd::kErrNone;
    return 1;
}

Result<Issue> CdvdHle::read(u32 lsn, u32 sectors, std::span<std::byte> dst, ReadMode mode) {
    // libcdvd checks the ncmd semaphore before looking at the arguments (_sceCd_ncmd_prechk).
    if (pending_) return Issue::Busy;
    if (mode.datapattern != cd::kSecS2048)
        return Error{FormatError::Unsupported,
                     "sceCdRead datapattern 1/2 (2328/2340-byte sectors) is not modelled; the game only uses 0"};
    if (sectors == 0) return Error{FormatError::Unsupported, "sceCdRead of 0 sectors is not modelled"};
    if (static_cast<u64>(lsn) + sectors > disc_.sector_count())
        return Error{FormatError::Overrun, "sceCdRead range outside the disc"};
    const std::size_t bytes = static_cast<std::size_t>(sectors) * kSectorSize;
    if (dst.size() < bytes) return Error{FormatError::Overrun, "sceCdRead destination smaller than sectors*2048"};
    last_read_mode_ = mode;
    pending_ = Pending{NcmdKind::Read, lsn, sectors, dst.first(bytes), latency_, false};
    return Issue::Accepted;
}

Result<Issue> CdvdHle::seek(u32 lsn) {
    if (pending_) return Issue::Busy;
    if (lsn >= disc_.sector_count()) return Error{FormatError::Overrun, "sceCdSeek LSN outside the disc"};
    pending_ = Pending{NcmdKind::Seek, lsn, 0, {}, latency_, false};
    return Issue::Accepted;
}

bool CdvdHle::service() {
    if (!pending_) return false;
    if (pending_->steps_left > 0) {
        --pending_->steps_left;
        return false;
    }
    complete();
    return true;
}

int CdvdHle::sync(SyncMode mode) {
    if (mode == SyncMode::Block) {
        if (pending_) complete();
        return 0;
    }
    service();
    return pending_ ? 1 : 0;
}

int CdvdHle::break_ncmd() {
    if (pending_) {
        pending_->aborted = true;
        pending_->steps_left = 0;
    }
    return 1;
}

void CdvdHle::complete() {
    const Pending p = *pending_;
    NcmdCompletion c{p.kind, p.lsn, p.sectors, cd::kErrNone};
    last_host_error_.reset();
    if (p.aborted) {
        c.error = cd::kErrAbort;
    } else if (p.kind == NcmdKind::Read) {
        auto rd = disc_.read_sectors(p.lsn, p.sectors, p.dst);
        if (!rd) {
            c.error = cd::kErrRead;
            last_host_error_ = rd.error();
        }
    }
    error_ = c.error;
    // Release the slot before the hooks run: after _sceCd_cd_callback the next N-command may be
    // issued immediately (the hooks may do so re-entrantly).
    pending_.reset();
    ++completions_;
    if (hooks_.signal_ncmd_sema) hooks_.signal_ncmd_sema(c);
    if (hooks_.clear_cb_sem) hooks_.clear_cb_sem(c);
}

int CdvdHle::status() const {
    if (!pending_) return cd::kStatPause;
    return pending_->kind == NcmdKind::Read ? cd::kStatRead : cd::kStatSeek;
}

int CdvdHle::mmode(int media) {
    if (media != cd::kMmodeCd && media != cd::kMmodeDvd) return 0;
    media_mode_ = media;
    return 1;
}

Result<std::size_t> CdvdHle::read_toc(std::span<std::byte> /*dst*/) {
    return Error{FormatError::Unsupported,
                 "sceCdGetToc is not modelled: no caller in SLUS_216.21 and the DVD TOC layout is unobserved"};
}

Result<SearchOutcome> CdvdHle::search_file(std::string_view path) {
    if (path.size() > cd::kMaxSearchPath)
        return Error{FormatError::Unsupported, "search path longer than libcdvd's 255 characters"};
    if (pending_) return SearchOutcome{Issue::Busy, std::nullopt};
    auto found = disc_.find_file(path);
    if (!found) return found.error();
    return SearchOutcome{Issue::Accepted, std::move(found).value()};
}

}  // namespace p3fes::hle
