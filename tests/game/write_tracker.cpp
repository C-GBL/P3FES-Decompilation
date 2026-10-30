// WriteTracker (write_tracker.h): VirtualProtect + a first-in-line vectored exception handler.
#include "write_tracker.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

#include <algorithm>
#include <cstdlib>
#include <cstring>

namespace p3fes::game_test {

namespace {
// The live trackers, on disjoint ranges (pair_harness.h's run_pair_hw keeps two: its RAM range and the BIOS window),
// and the one handler they share.
constexpr int kMaxTrackers = 4;
WriteTracker* g_active[kMaxTrackers] = {};
int g_live = 0;
void* g_handler = nullptr;

LONG CALLBACK on_exception(EXCEPTION_POINTERS* ep) {
    const EXCEPTION_RECORD* r = ep->ExceptionRecord;
    if (r->ExceptionCode != EXCEPTION_ACCESS_VIOLATION || r->NumberParameters < 2 || r->ExceptionInformation[0] != 1)
        return EXCEPTION_CONTINUE_SEARCH;  // not a write fault
    for (WriteTracker* t : g_active)
        if (t != nullptr && t->on_write_fault(r->ExceptionInformation[1])) return EXCEPTION_CONTINUE_EXECUTION;
    return EXCEPTION_CONTINUE_SEARCH;
}
}  // namespace

WriteTracker::WriteTracker(std::uint8_t* lo, std::uint8_t* hi, bool keep_originals) : lo_(lo), hi_(hi) {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    page_ = si.dwPageSize;
    const auto a = reinterpret_cast<std::uintptr_t>(lo), b = reinterpret_cast<std::uintptr_t>(hi);
    first_ = (a + page_ - 1) / page_ * page_;
    const std::uintptr_t last = b / page_ * page_;
    pages_ = last > first_ ? (last - first_) / page_ : 0;
    if (pages_ == 0) first_ = b;
    dirty_.assign(pages_, 0);
    since_.assign(pages_, 0);
    writable_.assign(pages_, 1);  // until the protect() below
    if (keep_originals) {
        kept_.assign(pages_, 0);
        orig_.reset(new std::uint8_t[pages_ * page_ + 1]);  // default-initialised: untouched until a page is kept
    }
    int slot = -1;
    for (int i = 0; i < kMaxTrackers; ++i) {
        const WriteTracker* t = g_active[i];
        if (t == nullptr) {
            if (slot < 0) slot = i;
        } else if (lo_ < t->hi_ && t->lo_ < hi_) {
            std::abort();  // two trackers on one byte
        }
    }
    if (slot < 0) std::abort();  // kMaxTrackers live at once
    if (g_live++ == 0) {
        g_handler = AddVectoredExceptionHandler(1, &on_exception);
        if (g_handler == nullptr) std::abort();
    }
    g_active[slot] = this;
    handler_ = g_handler;
    protect(0, pages_, true);
}

WriteTracker::~WriteTracker() {
    protect(0, pages_, false);
    for (WriteTracker*& t : g_active)
        if (t == this) t = nullptr;
    if (--g_live == 0) {
        RemoveVectoredExceptionHandler(g_handler);
        g_handler = nullptr;
    }
}

std::vector<WriteTracker::Span> WriteTracker::dirty() const {
    std::vector<Span> v;
    auto add = [&](std::size_t off, std::size_t len) {
        if (!v.empty() && v.back().off + v.back().len == off) v.back().len += len;
        else v.push_back({off, len});
    };
    const std::size_t head = static_cast<std::size_t>(first_ - reinterpret_cast<std::uintptr_t>(lo_));
    if (head) add(0, head);
    for (std::size_t p = 0; p < pages_;) {
        if (!dirty_[p]) {
            ++p;
            continue;
        }
        std::size_t q = p;
        while (q < pages_ && dirty_[q]) ++q;
        add(head + p * page_, (q - p) * page_);
        p = q;
    }
    const std::size_t tail = head + pages_ * page_, size = static_cast<std::size_t>(hi_ - lo_);
    if (tail < size) add(tail, size - tail);
    return v;
}

void WriteTracker::rearm() {
    for (std::size_t p = 0; p < pages_;) {
        if (!dirty_[p]) {
            ++p;
            continue;
        }
        std::size_t q = p;
        while (q < pages_ && dirty_[q]) dirty_[q++] = 0;
        protect(p, q, true);
        p = q;
    }
}

void WriteTracker::protect(std::size_t p, std::size_t q, bool read_only) {
    if (q <= p) return;
    DWORD old;
    if (!VirtualProtect(reinterpret_cast<void*>(first_ + p * page_), (q - p) * page_, read_only ? PAGE_READONLY : PAGE_READWRITE, &old))
        std::abort();
    std::fill(writable_.begin() + static_cast<std::ptrdiff_t>(p), writable_.begin() + static_cast<std::ptrdiff_t>(q),
              static_cast<std::uint8_t>(read_only ? 0 : 1));
}

bool WriteTracker::on_write_fault(std::uintptr_t a) {
    if (a < first_ || a >= first_ + pages_ * page_) return false;  // not ours
    const std::size_t p = (a - first_) / page_;
    if (!kept_.empty() && !kept_[p]) {  // the page is still read-only: its bytes before this write
        std::memcpy(orig_.get() + p * page_, reinterpret_cast<const void*>(first_ + p * page_), page_);
        kept_[p] = 1;
    }
    DWORD old;
    if (!VirtualProtect(reinterpret_cast<void*>(first_ + p * page_), page_, PAGE_READWRITE, &old)) return false;
    dirty_[p] = 1;
    since_[p] = 1;
    writable_[p] = 1;
    ++faults_;
    return true;
}

void WriteTracker::protect_marked(const std::vector<std::uint8_t>& marks, bool read_only) {
    for (std::size_t p = 0; p < pages_;) {
        if (!marks[p]) {
            ++p;
            continue;
        }
        std::size_t q = p;
        while (q < pages_ && marks[q]) ++q;
        protect(p, q, read_only);
        p = q;
    }
}

void WriteTracker::clear_since() { std::fill(since_.begin(), since_.end(), std::uint8_t{0}); }

void WriteTracker::unprotect_since() {
    std::vector<std::uint8_t> m(pages_);
    for (std::size_t p = 0; p < pages_; ++p) m[p] = since_[p] && !writable_[p];
    protect_marked(m, false);
}

void WriteTracker::restart() {
    const std::vector<std::uint8_t> w = writable_;
    protect_marked(w, true);
    std::fill(dirty_.begin(), dirty_.end(), std::uint8_t{0});
    std::fill(kept_.begin(), kept_.end(), std::uint8_t{0});
}

// --- BaseRange ----------------------------------------------------------------------------------------------------------
BaseRange::BaseRange(std::uint8_t* lo, std::uint8_t* hi)
    : lo_(lo), size_(static_cast<std::size_t>(hi - lo)), base_(lo, hi), tracker_(lo, hi, true) {
    tail_off_ = tracker_.head() + tracker_.pages() * tracker_.page_size();
}

void BaseRange::rebase() {
    base_.assign(lo_, lo_ + size_);
    tracker_.restart();
    tracker_.clear_since();
}

void BaseRange::restore() {
    tracker_.unprotect_since();  // the copies below then fault nowhere
    const std::vector<std::uint8_t>& since = tracker_.since();
    const std::size_t head = tracker_.head(), page = tracker_.page_size();
    std::memcpy(lo_, base_.data(), head);  // the partial end pages are never tracked: always copied
    std::memcpy(lo_ + tail_off_, base_.data() + tail_off_, size_ - tail_off_);
    for (std::size_t p = 0; p < tracker_.pages();) {
        if (!since[p]) {
            ++p;
            continue;
        }
        std::size_t q = p;
        while (q < tracker_.pages() && since[q]) ++q;
        std::memcpy(lo_ + head + p * page, base_.data() + head + p * page, (q - p) * page);
        restored_pages_ += q - p;
        p = q;
    }
    tracker_.restart();  // read-only again: the next pair's writes are seen
    tracker_.clear_since();
}

void BaseRange::begin() {
    tracker_.restart();  // set-up writes since restore() are the starting bytes; the next write to a page keeps them
    head_bytes_.assign(lo_, lo_ + tracker_.head());
    tail_bytes_.assign(lo_ + tail_off_, lo_ + size_);
    first_spans_.clear();
    first_bytes_.clear();
}

std::size_t BaseRange::next_boundary(std::size_t off) const {
    const std::size_t head = tracker_.head();
    if (off < head) return head;
    if (off >= tail_off_) return size_;
    return head + ((off - head) / tracker_.page_size() + 1) * tracker_.page_size();
}

const std::uint8_t* BaseRange::start_bytes(std::size_t off) const {
    const std::size_t head = tracker_.head();
    if (off < head) return head_bytes_.data() + off;
    if (off >= tail_off_) return tail_bytes_.data() + (off - tail_off_);
    const std::size_t p = (off - head) / tracker_.page_size();
    const std::uint8_t* page = tracker_.original(p);
    if (page == nullptr) std::abort();  // a page reported written always has its original
    return page + (off - head) % tracker_.page_size();
}

void BaseRange::between() {
    first_spans_ = tracker_.dirty();
    first_bytes_.clear();
    for (const WriteTracker::Span& s : first_spans_) {
        first_bytes_.insert(first_bytes_.end(), lo_ + s.off, lo_ + s.off + s.len);
        for (std::size_t at = s.off, end = s.off + s.len; at < end;) {
            const std::size_t next = std::min(next_boundary(at), end);
            std::memcpy(lo_ + at, start_bytes(at), next - at);
            at = next;
        }
    }
    tracker_.rearm();
}

std::uint8_t BaseRange::first_body_byte(std::size_t off) const {
    std::size_t k = 0;
    for (const WriteTracker::Span& s : first_spans_) {
        if (off >= s.off && off < s.off + s.len) return first_bytes_[k + (off - s.off)];
        k += s.len;
    }
    return *start_bytes(off);
}

std::size_t BaseRange::first_difference() const {
    std::size_t best = size_;
    auto diff = [](const std::uint8_t* a, const std::uint8_t* b, std::size_t n) {
        if (std::memcmp(a, b, n) == 0) return n;
        std::size_t i = 0;
        while (a[i] == b[i]) ++i;
        return i;
    };
    std::size_t k = 0;
    for (const WriteTracker::Span& s : first_spans_) {
        const std::size_t d = diff(first_bytes_.data() + k, lo_ + s.off, s.len);
        if (d < s.len) best = std::min(best, s.off + d);
        k += s.len;
    }
    auto check_start = [&](std::size_t at, std::size_t end) {
        while (at < end && at < best) {
            const std::size_t next = std::min(next_boundary(at), end);
            const std::size_t d = diff(start_bytes(at), lo_ + at, next - at);
            if (d < next - at) best = std::min(best, at + d);
            at = next;
        }
    };
    for (const WriteTracker::Span& s : tracker_.dirty()) {
        std::size_t at = s.off;
        const std::size_t end = s.off + s.len;
        for (const WriteTracker::Span& c : first_spans_) {
            if (c.off + c.len <= at) continue;
            if (c.off >= end) break;
            if (c.off > at) check_start(at, c.off);
            at = c.off + c.len;
            if (at >= end) break;
        }
        if (at < end) check_start(at, end);
    }
    return best;
}

PairRange::PairRange(std::uint8_t* lo, std::uint8_t* hi)
    : lo_(lo), size_(static_cast<std::size_t>(hi - lo)), tail_off_(0), tracker_(lo, hi, true) {
    tail_off_ = tracker_.head() + tracker_.pages() * tracker_.page_size();
    head_bytes_.assign(lo_, lo_ + tracker_.head());
    tail_bytes_.assign(lo_ + tail_off_, lo_ + size_);
}

std::size_t PairRange::next_boundary(std::size_t off) const {
    const std::size_t head = tracker_.head();
    if (off < head) return head;
    if (off >= tail_off_) return size_;
    return head + ((off - head) / tracker_.page_size() + 1) * tracker_.page_size();
}

const std::uint8_t* PairRange::start_bytes(std::size_t off) const {
    const std::size_t head = tracker_.head();
    if (off < head) return head_bytes_.data() + off;
    if (off >= tail_off_) return tail_bytes_.data() + (off - tail_off_);
    const std::size_t p = (off - head) / tracker_.page_size();
    const std::uint8_t* page = tracker_.original(p);
    if (page == nullptr) std::abort();  // a page reported written always has its original
    return page + (off - head) % tracker_.page_size();
}

void PairRange::between() {
    first_spans_ = tracker_.dirty();
    first_bytes_.clear();
    for (const WriteTracker::Span& s : first_spans_) {
        first_bytes_.insert(first_bytes_.end(), lo_ + s.off, lo_ + s.off + s.len);
        for (std::size_t at = s.off, end = s.off + s.len; at < end;) {
            const std::size_t next = std::min(next_boundary(at), end);
            std::memcpy(lo_ + at, start_bytes(at), next - at);
            at = next;
        }
    }
    tracker_.rearm();
}

std::uint8_t PairRange::first_body_byte(std::size_t off) const {
    std::size_t k = 0;
    for (const WriteTracker::Span& s : first_spans_) {
        if (off >= s.off && off < s.off + s.len) return first_bytes_[k + (off - s.off)];
        k += s.len;
    }
    return *start_bytes(off);  // not written by the first body: the starting byte (kept once the second wrote it)
}

std::size_t PairRange::first_difference() const {
    std::size_t best = size_;
    auto diff = [](const std::uint8_t* a, const std::uint8_t* b, std::size_t n) {
        if (std::memcmp(a, b, n) == 0) return n;
        std::size_t i = 0;
        while (a[i] == b[i]) ++i;
        return i;
    };
    // where the first body wrote: its bytes
    std::size_t k = 0;
    for (const WriteTracker::Span& s : first_spans_) {
        const std::size_t d = diff(first_bytes_.data() + k, lo_ + s.off, s.len);
        if (d < s.len) best = std::min(best, s.off + d);
        k += s.len;
    }
    // where only the second body wrote: the starting bytes (the first body left them there)
    auto check_start = [&](std::size_t at, std::size_t end) {
        while (at < end && at < best) {
            const std::size_t next = std::min(next_boundary(at), end);
            const std::size_t d = diff(start_bytes(at), lo_ + at, next - at);
            if (d < next - at) best = std::min(best, at + d);
            at = next;
        }
    };
    for (const WriteTracker::Span& s : tracker_.dirty()) {
        std::size_t at = s.off;
        const std::size_t end = s.off + s.len;
        for (const WriteTracker::Span& c : first_spans_) {  // [at, end) minus the first body's spans (both ascending)
            if (c.off + c.len <= at) continue;
            if (c.off >= end) break;
            if (c.off > at) check_start(at, c.off);
            at = c.off + c.len;
            if (at >= end) break;
        }
        if (at < end) check_start(at, end);
    }
    return best;
}

}  // namespace p3fes::game_test
