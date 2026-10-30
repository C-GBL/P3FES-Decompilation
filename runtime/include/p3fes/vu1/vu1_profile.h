// VU1 workload accounting and resident-program identification (docs/ANALYSIS/24_vu1_acceleration.md).
//
// `ProgramIndex` names the microprogram resident in micro memory: a table of known images, each loaded at micro
// address 0 (every game program is uploaded there, 14 §1), matched by content and cached per
// `MicroMemory::generation()`. The profiler uses it to attribute runs to programs; the ahead-of-time path
// (vu1_aot.h) uses the same matching to decide whether compiled code may run.
//
// `VU1Profile` is opt-in: `VU1Interpreter::set_profile(&p)` turns it on, nullptr (the default) turns it off. When
// off, the interpreter pays one null test per MSCAL/MSCNT and per cache rebuild, never per pair.
#pragma once

#include "p3fes/ee_types.h"
#include "p3fes/vu1/vu1_decode.h"

#include <cstdio>
#include <map>
#include <span>
#include <string>
#include <utility>
#include <vector>

namespace p3fes::vu1 {

class MicroMemory;

class ProgramIndex {
public:
    // `image` is the program as uploaded from micro address 0 (whole pairs).
    void add(std::string name, std::vector<u8> image);
    // Index of the longest registered image that micro memory starts with, or -1. Cached per micro generation.
    int identify(const MicroMemory& micro);
    std::size_t size() const noexcept { return entries_.size(); }
    const std::string& name(int k) const { return entries_[static_cast<std::size_t>(k)].name; }
    std::span<const u8> image(int k) const { return entries_[static_cast<std::size_t>(k)].image; }
    u64 identifications() const noexcept { return identifications_; } // cache misses (generation changes seen)

private:
    struct Entry {
        std::string name;
        std::vector<u8> image;
        u64 head = 0; // first pair, for a quick reject
    };
    std::vector<Entry> entries_;
    u64 cached_generation_ = 0;
    int cached_ = -1;
    u64 identifications_ = 0;
};

// Loads every `<code_va>.bin` dump in `dir` (tools/ours/vu1/vu1_dump.py writes them) under the name
// "<code_va>". Returns the number loaded.
std::size_t load_program_dumps(ProgramIndex& index, const std::string& dir);

struct VU1RunCounters {
    u64 runs = 0;
    u64 pairs = 0;
    u64 kicks = 0;
    u64 kick_qwords = 0;
    u64 ns = 0;      // wall time inside mscal/mscnt minus kick_ns (cache rebuilds included)
    u64 kick_ns = 0; // wall time inside IGifSink::kick (the GS drawing the kicked packets synchronously)
    u64 cold = 0;    // runs that started on a micro generation the interpreter had not decoded yet
};

struct VU1Profile {
    ProgramIndex programs;
    // (program index or -1, start byte pc) -> counters
    std::map<std::pair<int, u32>, VU1RunCounters> runs;
    u64 rebuilds = 0, rebuild_ns = 0;   // full decode + jump list of micro memory (once per new generation)
    u64 q_kind_calls = 0, q_kind_ns = 0;   // static Q-read classification (per Q-reading pc, per generation)
    u64 q_delay_calls = 0, q_delay_ns = 0; // straight-line Q latency (per DIV/RSQRT pc, per generation)
    u64 micro_writes = 0;                 // MPG uploads seen (generation bumps)
    u64 kick_ns_pending = 0;              // scratch: kick time of the run in progress
    // Optional capture of run inputs (save_run_input) for differential tests: the first `capture_per_key` runs of
    // every (program, start pc) are written to `capture_dir` while capture_per_key > 0.
    std::string capture_dir;
    u32 capture_per_key = 0;
    u64 captured = 0;
    std::map<std::pair<int, u32>, u32> capture_counts;

    void reset_counters();
    // One block of text: per-program rows sorted by time, then the totals.
    void write(std::FILE* f, const char* label, double wall_seconds, u64 vblanks) const;
};

struct VU1State;

// The input of one MSCAL/MSCNT: everything a run reads (registers, flags, TOP/ITOP, TPC, micro and data memory) and
// its start pc. The flag/Q pipe and the branch-delay snapshot are reset by every run start and are not saved.
// Binary, little-endian, magic "P3VU1IN1"; game-derived data: keep it under extracted/ or a scratch directory.
bool save_run_input(const std::string& path, const VU1State& s, u32 start_pc, const std::string& program);
bool load_run_input(const std::string& path, VU1State& s, u32& start_pc, std::string& program);

// Monotonic nanoseconds (std::chrono::steady_clock).
u64 vu1_now_ns() noexcept;

} // namespace p3fes::vu1
