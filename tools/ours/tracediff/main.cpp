// tracediff: find the first divergence between PCSX2 (reference) and our runtime.
//
// Modes (docs/TRACE_FORMAT.md §5):
//   snapshot       two 32 MiB eeMemory.bin images + masks -> differing runs, per band
//   snapshot-mask  derive a timing-noise mask from two reference images taken at
//                  the same sync point
//   <ref.p3tr> <ours.p3tr>   stream mode (not implemented yet; see §5)
//
// Exit codes: 0 identical (after masking), 1 divergence found, 2 usage/format error.
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "snapshot.h"

namespace snap = tracediff::snapshot;

namespace {

int usage(FILE* to) {
    std::fputs(
        "usage:\n"
        "  tracediff snapshot <ref/eeMemory.bin> <ours/eeMemory.bin> [--mask <file>]... [--no-default-mask]\n"
        "                     [--dead-stack <capture.json>]... [--context N] [--top N] [--json out.json]\n"
        "      Compares two 32 MiB EE RAM images after masking. Default mask: kernel area\n"
        "      0x00000000-0x000FFFFF (TRACE_FORMAT.md section 4.3). --mask files list ranges to ignore\n"
        "      (one per line: 0xA-0xB inclusive, 0xA+LEN, or 0xA for one word; '#' comments).\n"
        "      --context N: hex bytes shown for the first run (default 16). --top N: largest runs (20).\n"
        "      --dead-stack: also ignore each thread's stack below its saved frame / live sp, read from a\n"
        "      p3fes capture.json (the Phase 5 gate: hand-written functions do not spill below $sp).\n"
        "  tracediff snapshot-mask <ref_t0/eeMemory.bin> <ref_t1/eeMemory.bin> --out mask.txt\n"
        "                     [--pad N] [--merge-gap N] [--mask <file>]...\n"
        "      Bytes that differ between two reference captures at the SAME sync point are timing\n"
        "      noise; writes them as a mask (runs widened by --pad bytes, merged within --merge-gap).\n"
        "  tracediff <ref.p3tr> <ours.p3tr> [...]\n"
        "      Stream mode: not implemented yet (Phase 4).\n"
        "exit codes: 0 identical, 1 divergence, 2 usage/format error\n",
        to);
    return to == stdout ? 0 : 2;
}

bool read_text(const std::string& path, std::string* out) {
    std::ifstream f(path, std::ios::binary);
    if (!f) return false;
    std::ostringstream ss;
    ss << f.rdbuf();
    *out = ss.str();
    return true;
}

// Loads --mask files into `mask` (plus the default unless disabled).
bool build_mask(const std::vector<std::string>& mask_files, bool use_default, snap::Mask* mask) {
    if (use_default) *mask = snap::default_mask();
    for (const std::string& mf : mask_files) {
        std::string text;
        if (!read_text(mf, &text)) {
            std::fprintf(stderr, "tracediff: cannot read mask file %s\n", mf.c_str());
            return false;
        }
        snap::ParseError err;
        auto m = snap::parse_mask(text, &err);
        if (!m) {
            std::fprintf(stderr, "tracediff: %s:%d: %s\n", mf.c_str(), err.line, err.message.c_str());
            return false;
        }
        for (const snap::Range& r : m->ranges) mask->add(r);
    }
    mask->normalize();
    return true;
}

bool load_pair(const std::string& a, const std::string& b, std::vector<std::uint8_t>* ia, std::vector<std::uint8_t>* ib) {
    std::string err;
    *ia = snap::load_image(a, &err);
    if (ia->empty()) {
        std::fprintf(stderr, "tracediff: %s\n", err.c_str());
        return false;
    }
    *ib = snap::load_image(b, &err);
    if (ib->empty()) {
        std::fprintf(stderr, "tracediff: %s\n", err.c_str());
        return false;
    }
    return true;
}

long parse_num(const char* s, long dflt) {
    char* end = nullptr;
    long v = std::strtol(s, &end, 0);
    return (end && *end == '\0') ? v : dflt;
}

int cmd_snapshot(int argc, char** argv) {
    if (argc < 4) return usage(stderr);
    std::string ref = argv[2], ours = argv[3];
    std::vector<std::string> mask_files, dead_stack_files;
    bool use_default = true;
    long context = 16, top = 20;
    std::string json_out;
    for (int i = 4; i < argc; ++i) {
        std::string a = argv[i];
        if (a == "--mask" && i + 1 < argc) mask_files.push_back(argv[++i]);
        else if (a == "--dead-stack" && i + 1 < argc) dead_stack_files.push_back(argv[++i]);
        else if (a == "--no-default-mask") use_default = false;
        else if (a == "--context" && i + 1 < argc) context = parse_num(argv[++i], 16);
        else if (a == "--top" && i + 1 < argc) top = parse_num(argv[++i], 20);
        else if (a == "--json" && i + 1 < argc) json_out = argv[++i];
        else {
            std::fprintf(stderr, "tracediff: unknown option %s\n", a.c_str());
            return usage(stderr);
        }
    }
    if (context < 0 || top < 0) return usage(stderr);

    snap::Mask mask;
    if (!build_mask(mask_files, use_default, &mask)) return 2;
    std::uint64_t dead_stack_bytes = 0;
    for (const std::string& cf : dead_stack_files) {
        std::ifstream in(cf, std::ios::binary);
        if (!in) {
            std::fprintf(stderr, "tracediff: cannot read capture %s\n", cf.c_str());
            return 2;
        }
        std::string text((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        std::string why;
        auto ds = snap::dead_stack_mask(text, &why);
        if (!ds) {
            std::fprintf(stderr, "tracediff: %s: %s\n", cf.c_str(), why.c_str());
            return 2;
        }
        dead_stack_bytes += ds->masked_bytes();
        for (const snap::Range& r : ds->ranges) mask.add(r);
        mask.normalize();
    }
    std::vector<std::uint8_t> a, b;
    if (!load_pair(ref, ours, &a, &b)) return 2;

    snap::Report rep = snap::compare(a.data(), b.data(), a.size(), mask);

    std::printf("tracediff snapshot\n  ref : %s\n  ours: %s\n", ref.c_str(), ours.c_str());
    if (!dead_stack_files.empty())
        std::printf("  dead stack: %llu bytes from %zu capture(s)\n", static_cast<unsigned long long>(dead_stack_bytes),
                    dead_stack_files.size());
    std::printf("  masked: %llu bytes in %zu range(s)\n", static_cast<unsigned long long>(rep.masked_bytes), mask.ranges.size());
    std::printf("  differing bytes: %llu   differing runs: %llu\n", static_cast<unsigned long long>(rep.total_differing_bytes),
                static_cast<unsigned long long>(rep.run_count));
    if (auto f = rep.first_run()) {
        std::printf("  first run: VA 0x%08X (%s) length %u\n", f->offset, snap::band_of(f->offset), f->length);
        std::size_t n = static_cast<std::size_t>(context);
        std::printf("    ref : %s\n    ours: %s\n", snap::hex_bytes(a.data(), a.size(), f->offset, n).c_str(),
                    snap::hex_bytes(b.data(), b.size(), f->offset, n).c_str());
        std::printf("  %ld largest runs:\n", top);
        for (const snap::Run& r : rep.largest_runs(static_cast<std::size_t>(top)))
            std::printf("    0x%08X  len %10u  %s\n", r.offset, r.length, snap::band_of(r.offset));
    }
    std::printf("  per band:\n");
    for (const snap::BandStat& bs : rep.per_band)
        std::printf("    %-7s %12llu bytes %10llu runs\n", bs.name.c_str(), static_cast<unsigned long long>(bs.differing_bytes),
                    static_cast<unsigned long long>(bs.runs));

    if (!json_out.empty()) {
        std::ofstream jf(json_out, std::ios::binary);
        if (!jf) {
            std::fprintf(stderr, "tracediff: cannot write %s\n", json_out.c_str());
            return 2;
        }
        jf << snap::to_json(rep, static_cast<std::size_t>(top), ref, ours);
    }
    return rep.total_differing_bytes == 0 ? 0 : 1;
}

int cmd_snapshot_mask(int argc, char** argv) {
    if (argc < 4) return usage(stderr);
    std::string t0 = argv[2], t1 = argv[3];
    std::string out;
    std::vector<std::string> mask_files;
    long pad = 0, merge_gap = 0;
    for (int i = 4; i < argc; ++i) {
        std::string a = argv[i];
        if (a == "--out" && i + 1 < argc) out = argv[++i];
        else if (a == "--pad" && i + 1 < argc) pad = parse_num(argv[++i], 0);
        else if (a == "--merge-gap" && i + 1 < argc) merge_gap = parse_num(argv[++i], 0);
        else if (a == "--mask" && i + 1 < argc) mask_files.push_back(argv[++i]);
        else {
            std::fprintf(stderr, "tracediff: unknown option %s\n", a.c_str());
            return usage(stderr);
        }
    }
    if (out.empty() || pad < 0 || merge_gap < 0) return usage(stderr);

    // The kernel area is always excluded from the comparison, and also from the
    // derived mask (consumers add the default mask themselves).
    snap::Mask exclude;
    if (!build_mask(mask_files, true, &exclude)) return 2;
    std::vector<std::uint8_t> a, b;
    if (!load_pair(t0, t1, &a, &b)) return 2;

    snap::Report rep = snap::compare(a.data(), b.data(), a.size(), exclude);
    snap::Mask derived = snap::derive_mask(rep, static_cast<std::uint32_t>(pad), static_cast<std::uint32_t>(merge_gap));

    std::ostringstream hdr;
    hdr << "tracediff snapshot-mask: timing noise between two reference captures at the same sync point\n"
        << "t0: " << t0 << "\n"
        << "t1: " << t1 << "\n"
        << "differing bytes " << rep.total_differing_bytes << " in " << rep.run_count << " runs; pad " << pad
        << ", merge-gap " << merge_gap << " -> " << derived.ranges.size() << " mask range(s), "
        << derived.masked_bytes() << " bytes\n"
        << "format: 0xBEGIN-0xEND (inclusive, EE VA); does not include the default kernel mask";
    std::ofstream f(out, std::ios::binary);
    if (!f) {
        std::fprintf(stderr, "tracediff: cannot write %s\n", out.c_str());
        return 2;
    }
    f << snap::format_mask(derived, hdr.str());
    std::printf("tracediff snapshot-mask\n  t0: %s\n  t1: %s\n  noise: %llu bytes in %llu runs\n  mask: %zu range(s), %llu bytes -> %s\n",
                t0.c_str(), t1.c_str(), static_cast<unsigned long long>(rep.total_differing_bytes),
                static_cast<unsigned long long>(rep.run_count), derived.ranges.size(),
                static_cast<unsigned long long>(derived.masked_bytes()), out.c_str());
    std::printf("  per band:\n");
    for (const snap::BandStat& bs : rep.per_band)
        std::printf("    %-7s %12llu bytes %10llu runs\n", bs.name.c_str(), static_cast<unsigned long long>(bs.differing_bytes),
                    static_cast<unsigned long long>(bs.runs));
    return 0;
}

}  // namespace

int main(int argc, char** argv) {
    if (argc < 2) return usage(stdout);
    std::string mode = argv[1];
    if (mode == "-h" || mode == "--help" || mode == "help") return usage(stdout);
    if (mode == "snapshot") return cmd_snapshot(argc, argv);
    if (mode == "snapshot-mask") return cmd_snapshot_mask(argc, argv);
    std::fputs("tracediff: stream mode (<ref.p3tr> <ours.p3tr>) is not implemented yet (Phase 4).\n", stderr);
    return 2;
}
