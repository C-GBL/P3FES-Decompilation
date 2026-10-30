// Page-granular write tracking of a host byte range, for pair tests that restore and compare a large guest window
// per pair (test_battle_calc.cpp: 4 MiB of .data/.bss, ~2 ms of copying per pair while a pair's bodies write a
// handful of pages; test_render_rw2.cpp: the whole 32 MiB of RAM). WriteTracker makes the whole pages of [lo, hi) read-only; the first write to such a page
// faults into a vectored exception handler that records the page and makes it writable again, so the code under
// test (recompiled or hand-written) and the host test code run unchanged, at full speed on clean pages. Every
// user-mode write to the range is seen. The partial pages at both ends (the range need not be page-aligned) are
// reported as written every time. Kernel writes into the range (ReadFile into guest RAM) would fail instead of
// faulting: keep a tracker only around code that does none (pair tests do none).
//
// Windows only (write_tracker.cpp: VirtualProtect + AddVectoredExceptionHandler); up to four live trackers, on
// disjoint ranges (one handler serves them all).
#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

namespace p3fes::game_test {

class WriteTracker {
public:
    // A span of the range: offset and length from `lo`.
    struct Span {
        std::size_t off;
        std::size_t len;
    };

    // Protects the whole pages of [lo, hi). keep_originals: the first write to a page after construction also keeps
    // the page's bytes from before it (original()).
    WriteTracker(std::uint8_t* lo, std::uint8_t* hi, bool keep_originals = false);
    ~WriteTracker();  // writable again
    WriteTracker(const WriteTracker&) = delete;
    WriteTracker& operator=(const WriteTracker&) = delete;

    // The spans written since the last rearm (coalesced, ascending), the partial end pages always included.
    std::vector<Span> dirty() const;
    // Read-only again for every page written since the last rearm (kept originals stay).
    void rearm();
    std::uint64_t faults() const { return faults_; }
    // Geometry: the partial page at the start (bytes), the page size, the whole pages tracked.
    std::size_t head() const { return static_cast<std::size_t>(first_ - reinterpret_cast<std::uintptr_t>(lo_)); }
    std::size_t page_size() const { return static_cast<std::size_t>(page_); }
    std::size_t pages() const { return pages_; }
    // keep_originals: the bytes of whole page `p` before its first write (nullptr when it was never written).
    const std::uint8_t* original(std::size_t p) const { return kept_.empty() || !kept_[p] ? nullptr : orig_.get() + p * page_; }
    // The exception handler's part: a write fault at `addr`; true when it was a tracked page (now writable).
    bool on_write_fault(std::uintptr_t addr);

    // A second, longer-lived record (BaseRange): the whole pages written since the last clear_since(), whatever
    // rearm() did in between; every page writable now is among them.
    const std::vector<std::uint8_t>& since() const { return since_; }
    void clear_since();
    void unprotect_since();  // writable: every page written since clear_since() (BaseRange::restore copies into them)
    // Read-only again for every writable page, the phase record cleared and the kept originals forgotten: the next
    // write to any page keeps its bytes from now (a fresh PairRange on this tracker).
    void restart();

private:
    void protect(std::size_t p, std::size_t q, bool read_only);
    void protect_marked(const std::vector<std::uint8_t>& marks, bool read_only);  // every page marked, in runs

    std::uint8_t* lo_;
    std::uint8_t* hi_;
    std::uintptr_t page_ = 4096;
    std::uintptr_t first_ = 0;  // the first whole page
    std::size_t pages_ = 0;     // whole pages tracked
    std::vector<std::uint8_t> dirty_;
    std::vector<std::uint8_t> kept_;          // keep_originals: page p's original is in orig_
    std::unique_ptr<std::uint8_t[]> orig_;    // keep_originals: pages_ pages (only the kept ones are touched)
    std::vector<std::uint8_t> since_;         // written since clear_since()
    std::vector<std::uint8_t> writable_;      // not read-only now
    std::uint64_t faults_ = 0;
    void* handler_ = nullptr;
};

// One guest range of a single pair, compared after both bodies and restored between them, on a WriteTracker that
// keeps each page's bytes from before its first write: equal to copying the range before the first body, copying it
// after the first body, restoring the first copy, and finding the first byte where the range differs from the second
// copy after the second body -- but only the pages written are copied and compared. Exact: a page nobody wrote holds
// the starting bytes after both bodies. Arm it (construct it) where the first copy would have been taken; the range
// keeps the second body's bytes after it. Used by pair_harness.h's run_pair_hw for ranges of 1 MiB and more (the
// whole 32 MiB of RAM in test_render_rw2.cpp) and by the data windows of test_battle_calc.cpp (4 MiB),
// test_battle_rest.cpp (2 MiB) and test_script_comm_a.cpp (3.5 MiB).
class PairRange {
public:
    PairRange(std::uint8_t* lo, std::uint8_t* hi);
    void between();                         // after the first body: keep what it left, restore the starting bytes
    std::size_t first_difference() const;   // after the second body: the first byte differing from what the first
                                            // body left (size() when none)
    std::uint8_t first_body_byte(std::size_t off) const;  // what the first body left at `off` (for messages)
    std::size_t size() const { return size_; }

private:
    const std::uint8_t* start_bytes(std::size_t off) const;  // the starting bytes from `off` to next_boundary(off)
    std::size_t next_boundary(std::size_t off) const;         // the end of off's page or end piece

    std::uint8_t* lo_;
    std::size_t size_;
    std::size_t tail_off_;
    std::vector<std::uint8_t> head_bytes_, tail_bytes_;  // the partial end pages' starting bytes
    std::vector<WriteTracker::Span> first_spans_;        // written by the first body
    std::vector<std::uint8_t> first_bytes_;              // ... and its bytes there, span after span
    WriteTracker tracker_;                               // last: armed after the end pieces are copied
};

// A guest range kept at a base image across many pairs (a test world's whole RAM, restored before every pair) plus
// PairRange's exact pair protocol, on one long-lived tracker: restore() copies back only the pages written since the
// last restore (copying the whole 32 MiB per pair was most of test_battle_cmd_menu's time), and begin() / between() /
// first_difference() / first_body_byte() are PairRange's construction / between() / ... -- the same results. Pages the
// host writes between restore() and begin() (a fixture's set-up) are the pair's starting bytes, as with PairRange.
// No other tracker on its range while a BaseRange lives; same kernel-write caveat as WriteTracker.
class BaseRange {
public:
    BaseRange(std::uint8_t* lo, std::uint8_t* hi);  // the current bytes become the base
    void rebase();                                  // the current bytes become the base (one full copy)
    void restore();                                 // the range equals the base again (the pages written since)
    void begin();                                   // a pair starts: where a PairRange would be constructed
    void between();                                 // after the first body (PairRange::between)
    std::size_t first_difference() const;           // after the second body (PairRange::first_difference)
    std::uint8_t first_body_byte(std::size_t off) const;
    std::size_t size() const { return size_; }
    std::uint64_t restored_pages() const { return restored_pages_; }  // statistics: pages copied by restore()

private:
    const std::uint8_t* start_bytes(std::size_t off) const;
    std::size_t next_boundary(std::size_t off) const;

    std::uint8_t* lo_;
    std::size_t size_;
    std::size_t tail_off_ = 0;
    std::vector<std::uint8_t> base_;                     // the base image
    std::vector<std::uint8_t> head_bytes_, tail_bytes_;  // the partial end pages at begin()
    std::vector<WriteTracker::Span> first_spans_;
    std::vector<std::uint8_t> first_bytes_;
    std::uint64_t restored_pages_ = 0;
    WriteTracker tracker_;                               // last: armed after the base is copied
};

}  // namespace p3fes::game_test
