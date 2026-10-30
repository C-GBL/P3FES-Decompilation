// tracediff snapshot mode: compare two EE RAM images (eeMemory.bin, 32 MiB,
// physical layout: offset = EE VA & 0x1FFFFFFF) after masking timing noise.
// See docs/TRACE_FORMAT.md §5 ("snapshot mode") and §4 (masks).
#pragma once

#include <cstdint>
#include <cstdio>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace tracediff::snapshot {

constexpr std::size_t kEeRamSize = 32u * 1024u * 1024u;  // eeMemory.bin
constexpr std::uint32_t kPhysMask = 0x1FFFFFFF;          // kuseg/kseg0/kseg1 -> physical

// Half-open byte range in physical EE RAM space.
struct Range {
    std::uint32_t begin = 0;
    std::uint32_t end = 0;  // exclusive
    std::uint32_t size() const { return end - begin; }
};

// A maximal run of differing bytes.
struct Run {
    std::uint32_t offset = 0;  // physical offset == kuseg VA
    std::uint32_t length = 0;
};

// Bands from the ELF layout (docs/ANALYSIS/00_elf_layout.md). Half-open.
struct Band {
    const char* name;
    std::uint32_t begin;
    std::uint32_t end;
};
// kernel 0x0-0x100000 | code | gap | data | gap | bss | heap | stack. "other"
// collects whatever falls between/outside (the two ELF gaps and 0x2000000+).
const std::vector<Band>& bands();
const char* band_of(std::uint32_t offset);

struct BandStat {
    std::string name;
    std::uint64_t differing_bytes = 0;
    std::uint64_t runs = 0;
};

// ---- mask file -------------------------------------------------------------
// One range per line; '#' starts a comment. Accepted forms (hex with or without
// 0x; addresses are EE VAs and are reduced with kPhysMask):
//   0x00000000-0x000FFFFF   inclusive end  (docs/TRACE_FORMAT.md §4 style)
//   0x007CE10C+4            start + length
//   0x007CE10C              a single 4-byte word
// Ranges are merged and clipped to the image.
struct Mask {
    std::vector<Range> ranges;  // normalized: sorted, non-overlapping, non-adjacent
    void add(Range r);
    void normalize();
    bool covers(std::uint32_t offset) const;
    std::uint64_t masked_bytes() const;
};

struct ParseError {
    int line = 0;
    std::string message;
};

// Parses mask text. On success returns the mask; on failure the first error.
std::optional<Mask> parse_mask(std::string_view text, ParseError* err = nullptr);
std::string format_mask(const Mask& m, std::string_view header_comment);

// The §4.3 default: ignore the EE kernel area 0x00000000-0x000FFFFF.
Mask default_mask();

// Dead-stack mask from a p3fes `capture.json` (runtime/app/game_host.cpp snapshot writer): for every
// thread listed under "threads" the bytes below its saved context frame, [stack, frame), hold nothing
// live (the frame itself, 0x280 bytes at `frame`, and everything above it up to stack + stack_size are
// live); for the thread named by "current_thread" (0 = idle, nothing running) the bound is the live
// "sp" instead when the capture records one. Callee spills below $sp are the one legitimate difference
// between a hand-decompiled function and its recompiled body (game/README.md), so the Phase 5 gate
// compares with this mask added. Returns nullopt when the text has no "threads" array. The parser is
// the minimal key scan the writer's fixed format needs, not a JSON parser.
std::optional<Mask> dead_stack_mask(std::string_view capture_json, std::string* why = nullptr);

// ---- comparison -------------------------------------------------------------
struct Report {
    std::uint64_t total_differing_bytes = 0;
    std::uint64_t run_count = 0;
    std::uint64_t masked_bytes = 0;
    std::vector<Run> runs;  // every run, in address order
    std::vector<BandStat> per_band;

    // Convenience views over `runs`.
    std::optional<Run> first_run() const;
    std::vector<Run> largest_runs(std::size_t n) const;
};

// Both images must be exactly kEeRamSize bytes (checked by the caller via
// load_image). Masked bytes are treated as equal; a run never spans a mask.
Report compare(const std::uint8_t* ref, const std::uint8_t* ours, std::size_t size, const Mask& mask);

// Reads a whole file; refuses anything that is not exactly kEeRamSize bytes.
// Returns an empty vector and fills `error` on failure.
std::vector<std::uint8_t> load_image(const std::string& path, std::string* error);

// Formats `n` bytes starting at offset `off` of `img` as "xx xx ...".
std::string hex_bytes(const std::uint8_t* img, std::size_t size, std::uint32_t off, std::size_t n);

// Derives a mask from the differing runs between two reference images taken at
// the same sync point: each run is widened by `pad` bytes on both sides and
// runs closer than `merge_gap` are merged (both in bytes).
Mask derive_mask(const Report& r, std::uint32_t pad, std::uint32_t merge_gap);

// JSON for the test harness (--json). Includes the first run, the `top` largest
// runs and the per-band table; never the byte contents.
std::string to_json(const Report& r, std::size_t top, const std::string& ref_path, const std::string& ours_path);

}  // namespace tracediff::snapshot
