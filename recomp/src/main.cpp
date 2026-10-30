// p3fes_recomp: static recompiler entry point (Phase 3).
//
//   p3fes_recomp --elf <SLUS_216.21> --functions <symbols/functions.json>
//                [--chunks <function_chunks.txt>] [--jumptables <jumptables.json>]
//                (--dump-decode <out.txt> | --out <dir> [--only a,b,...] [--band lo-hi]
//                                                       [--group-size N] [--stable-units] [--annotate] [--keep-going]
//                                                       [--no-cycles] [--no-check-events])
//
// --dump-decode writes one line per instruction word ("<va> <word> <base> <variant>") for the
// oracle test (recomp/tests/oracle_decode.py).
// --out emits C++ (recomp/README.md): one function per IDA function, grouped into files of
// --group-size functions, plus dispatch.cpp, functions.h, missing_stubs.cpp and manifest.json.
// Both modes exit 1 on any Invalid word inside a function body; --out also exits 1 on an
// unresolved structural case (branch target in no function, branch in a delay slot, ...) and
// names the VA. --keep-going writes the output anyway with traps at the problem sites.
// ADR-0013 (on by default): `ctx.cycles += N;` at the start of every basic block and
// rt::check_events(ctx) once per function invocation and before every loop back-edge;
// --no-cycles / --no-check-events turn them off (recomp/README.md "Cycle accounting").
#include "elf_image.h"
#include "emit_driver.h"
#include "function_list.h"
#include "r5900_decode.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

namespace {

void print_usage(std::FILE* to) {
    std::fputs(
        "usage: p3fes_recomp --elf <path> --functions <functions.json> [--chunks <file>] [--jumptables <file>]\n"
        "                    (--dump-decode <out.txt> | --out <dir> [emit options])\n"
        "\n"
        "  --elf <path>          PS2 EE ELF (SLUS_216.21; SHA-256 verified; never committed)\n"
        "  --functions <path>    IDA function list (symbols/functions.json)\n"
        "  --chunks <path>       IDA chunk + data-item list (symbols/function_chunks.txt);\n"
        "                        without it every function is taken as [start, start+size)\n"
        "  --jumptables <path>   IDA switch tables (symbols/jumptables.json); required for --out\n"
        "  --dump-decode <path>  write '<va> <word> <base> <variant>' per decoded word\n"
        "  --out <dir>           emit C++ into <dir> (recomp/generated)\n"
        "emit options:\n"
        "  --only <a,b,...>      emit only these function starts (hex or decimal)\n"
        "  --band <lo>-<hi>      emit only functions starting in [lo, hi)\n"
        "  --group-size <N>      functions per generated .cpp (default 200)\n"
        "  --stable-units        group by the whole program's bands of N functions (position in functions.json),\n"
        "                        not by the selection: a subset's units keep their names and text when the\n"
        "                        selection changes elsewhere (a full run writes the same units either way)\n"
        "  --annotate            trailing '// <pc> <mnemonic>' comments\n"
        "  --keep-going          write output despite structural problems (traps at the sites)\n"
        "  --no-cycles           omit the per-block `ctx.cycles += N;` (virtual time, ADR-0013)\n"
        "  --no-check-events     omit rt::check_events at function entries and loop back-edges\n"
        "  --no-selectors        call replaced functions directly (no reference-mode selectors; measurements)\n"
        "  --replace <path>      Phase 5 list of hand-decompiled functions (game/replaced.txt: '<hex start> <IDA name>'\n"
        "                        per line, '#' comments): each is emitted as fn_<name>_<addr>__recomp and the plain\n"
        "                        symbol is left to game/; the name must match functions.json. A function with\n"
        "                        mid-body entries lists them as '@0x<pc>' tokens (exactly the program's set)\n"
        "  --help                show this message\n",
        to);
}

struct Args {
    const char* elf = nullptr;
    const char* functions = nullptr;
    const char* chunks = nullptr;
    const char* jumptables = nullptr;
    const char* dump = nullptr;
    const char* out = nullptr;
    const char* only = nullptr;
    const char* band = nullptr;
    const char* group = nullptr;
    const char* replace = nullptr;
    bool annotate = false;
    bool stable_units = false;
    bool no_selectors = false;
    bool keep_going = false;
    bool no_cycles = false;
    bool no_check_events = false;
};

bool parse_args(int argc, char** argv, Args& a) {
    for (int i = 1; i < argc; ++i) {
        auto next = [&](const char*& dst) {
            if (i + 1 >= argc) return false;
            dst = argv[++i];
            return true;
        };
        if (std::strcmp(argv[i], "--elf") == 0) { if (!next(a.elf)) return false; }
        else if (std::strcmp(argv[i], "--functions") == 0) { if (!next(a.functions)) return false; }
        else if (std::strcmp(argv[i], "--chunks") == 0) { if (!next(a.chunks)) return false; }
        else if (std::strcmp(argv[i], "--jumptables") == 0) { if (!next(a.jumptables)) return false; }
        else if (std::strcmp(argv[i], "--dump-decode") == 0) { if (!next(a.dump)) return false; }
        else if (std::strcmp(argv[i], "--out") == 0) { if (!next(a.out)) return false; }
        else if (std::strcmp(argv[i], "--only") == 0) { if (!next(a.only)) return false; }
        else if (std::strcmp(argv[i], "--band") == 0) { if (!next(a.band)) return false; }
        else if (std::strcmp(argv[i], "--group-size") == 0) { if (!next(a.group)) return false; }
        else if (std::strcmp(argv[i], "--replace") == 0) { if (!next(a.replace)) return false; }
        else if (std::strcmp(argv[i], "--annotate") == 0) a.annotate = true;
        else if (std::strcmp(argv[i], "--stable-units") == 0) a.stable_units = true;
        else if (std::strcmp(argv[i], "--keep-going") == 0) a.keep_going = true;
        else if (std::strcmp(argv[i], "--no-cycles") == 0) a.no_cycles = true;
        else if (std::strcmp(argv[i], "--no-check-events") == 0) a.no_check_events = true;
        else if (std::strcmp(argv[i], "--no-selectors") == 0) a.no_selectors = true;
        else return false;
    }
    return a.elf && a.functions && (a.dump || a.out) && !(a.dump && a.out);
}

bool parse_u32(const char* s, const char** end_out, std::uint32_t& v) {
    char* end = nullptr;
    const unsigned long long x = std::strtoull(s, &end, 0);
    if (end == s || x > 0xFFFFFFFFull) return false;
    v = static_cast<std::uint32_t>(x);
    if (end_out) *end_out = end;
    return true;
}

int run_dump(const char* path, const p3fes::recomp::ElfImage& elf, const p3fes::recomp::FunctionList& fl, std::size_t mismatches) {
    using namespace p3fes::recomp;
    std::FILE* out = std::fopen(path, "wb");
    if (!out) {
        std::fprintf(stderr, "p3fes_recomp: cannot write %s\n", path);
        return 1;
    }
    std::size_t words = 0, invalid = 0, data_skipped = 0, unbacked = 0, funcs_walked = 0;
    std::uint32_t first_invalid = 0, first_unbacked = 0;
    char variant[48];
    std::vector<Range> single;
    for (const Function& f : fl.functions) {
        const std::vector<Range>* chunks = &f.chunks;
        if (chunks->empty()) {
            single.assign(1, Range{f.start, f.start + f.size});
            chunks = &single;
        }
        ++funcs_walked;
        for (const Range& r : *chunks) {
            for (std::uint32_t va = r.start; va + 4 <= r.end; va += 4) {
                if (f.is_data(va)) { ++data_skipped; continue; }
                const auto w = elf.word_at(va);
                if (!w) {
                    if (!unbacked) first_unbacked = va;
                    ++unbacked;
                    continue;
                }
                const Insn insn = decode(*w, va);
                ++words;
                if (insn.op == Op::Invalid) {
                    if (!invalid) first_invalid = va;
                    ++invalid;
                }
                variant_mnemonic(insn, variant, sizeof variant);
                std::fprintf(out, "%08x %08x %s %s\n", va, *w, mnemonic(insn.op), variant);
            }
        }
    }
    std::fclose(out);
    std::fprintf(stderr,
                 "p3fes_recomp: %zu functions (%s), %zu words decoded, %zu data words skipped, %zu invalid%s%s\n",
                 funcs_walked, fl.has_chunks ? "IDA chunks" : "start+size only", words, data_skipped, invalid,
                 fl.has_chunks && mismatches ? " [function set differs between functions.json and chunk list]" : "",
                 unbacked ? " [some addresses had no file bytes]" : "");
    if (fl.has_chunks && mismatches)
        std::fprintf(stderr, "p3fes_recomp: %zu function starts appear in only one of the two inputs\n", mismatches);
    if (unbacked) std::fprintf(stderr, "p3fes_recomp: first address without file bytes: 0x%08x\n", first_unbacked);
    if (invalid) {
        std::fprintf(stderr, "p3fes_recomp: first invalid word at 0x%08x; refusing to continue (fail closed)\n", first_invalid);
        return 1;
    }
    return 0;
}

}  // namespace

int main(int argc, char** argv) {
    using namespace p3fes::recomp;

    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--help") == 0 || std::strcmp(argv[i], "-h") == 0) {
            print_usage(stdout);
            return 0;
        }
    }
    Args args;
    if (!parse_args(argc, argv, args)) {
        print_usage(argc > 1 ? stderr : stdout);
        return argc > 1 ? 2 : 0;
    }

    ElfImage elf;
    const ElfImage::LoadResult lr = elf.load(args.elf);
    if (lr.error) {
        std::fprintf(stderr, "p3fes_recomp: %s: %s (sha256 %s)\n", args.elf, lr.error, lr.sha256_hex);
        return 1;
    }

    FunctionList fl;
    std::string text;
    if (!read_file(args.functions, text)) {
        std::fprintf(stderr, "p3fes_recomp: cannot read %s\n", args.functions);
        return 1;
    }
    if (const char* err = fl.load_functions_json(text)) {
        std::fprintf(stderr, "p3fes_recomp: %s: %s\n", args.functions, err);
        return 1;
    }
    std::size_t mismatches = 0;
    if (args.chunks) {
        if (!read_file(args.chunks, text)) {
            std::fprintf(stderr, "p3fes_recomp: cannot read %s\n", args.chunks);
            return 1;
        }
        if (const char* err = fl.apply_chunk_list(text, &mismatches)) {
            std::fprintf(stderr, "p3fes_recomp: %s: %s\n", args.chunks, err);
            return 1;
        }
    }

    if (args.dump) return run_dump(args.dump, elf, fl, mismatches);

    // --out
    if (!args.jumptables) {
        std::fprintf(stderr, "p3fes_recomp: --out requires --jumptables <symbols/jumptables.json>\n");
        return 2;
    }
    SwitchTables switches;
    if (!read_file(args.jumptables, text)) {
        std::fprintf(stderr, "p3fes_recomp: cannot read %s\n", args.jumptables);
        return 1;
    }
    if (const char* err = switches.load_json(text)) {
        std::fprintf(stderr, "p3fes_recomp: %s: %s\n", args.jumptables, err);
        return 1;
    }
    if (!fl.has_chunks)
        std::fprintf(stderr, "p3fes_recomp: warning: no --chunks; multi-chunk functions and data words are not known\n");
    if (mismatches)
        std::fprintf(stderr, "p3fes_recomp: warning: %zu function starts appear in only one of functions.json / chunk list\n", mismatches);

    EmitOptions opt;
    opt.out_dir = args.out;
    opt.annotate = args.annotate;
    opt.keep_going = args.keep_going;
    opt.cycles = !args.no_cycles;
    opt.check_events = !args.no_check_events;
    opt.elf_sha256 = lr.sha256_hex;
    std::string only_text;  // --only @file: the list read from a file (a long list overflows the Windows command line)
    if (args.only && args.only[0] == '@') {
        std::FILE* f = std::fopen(args.only + 1, "rb");
        if (!f) {
            std::fprintf(stderr, "p3fes_recomp: --only: cannot open '%s'\n", args.only + 1);
            return 2;
        }
        char buf[4096];
        for (std::size_t n; (n = std::fread(buf, 1, sizeof buf, f)) > 0;) {
            for (std::size_t i = 0; i < n; ++i) {
                const char c = buf[i];
                if (c == ' ' || c == '\t' || c == '\r') continue;
                only_text += (c == '\n' || c == ';') ? ',' : c;
            }
        }
        std::fclose(f);
        while (!only_text.empty() && only_text.back() == ',') only_text.pop_back();
        while (!only_text.empty() && only_text.front() == ',') only_text.erase(0, 1);
        args.only = only_text.c_str();
    }
    if (args.only) {
        const char* p = args.only;
        while (*p) {
            std::uint32_t v = 0;
            const char* end = nullptr;
            if (!parse_u32(p, &end, v)) {
                std::fprintf(stderr, "p3fes_recomp: --only: bad address list '%s'\n", args.only);
                return 2;
            }
            opt.only.push_back(v);
            p = end;
            if (*p == ',') ++p;
            else if (*p) {
                std::fprintf(stderr, "p3fes_recomp: --only: bad address list '%s'\n", args.only);
                return 2;
            }
        }
    }
    if (args.band) {
        const char* end = nullptr;
        if (!parse_u32(args.band, &end, opt.band_lo) || *end != '-' || !parse_u32(end + 1, &end, opt.band_hi) || *end ||
            opt.band_hi <= opt.band_lo) {
            std::fprintf(stderr, "p3fes_recomp: --band: expected <lo>-<hi>, got '%s'\n", args.band);
            return 2;
        }
        opt.has_band = true;
    }
    if (args.replace) {
        std::string rtext;
        if (!read_file(args.replace, rtext)) {
            std::fprintf(stderr, "p3fes_recomp: cannot read %s\n", args.replace);
            return 1;
        }
        std::size_t pos = 0, lineno = 0;
        while (pos < rtext.size()) {
            std::size_t eol = rtext.find('\n', pos);
            if (eol == std::string::npos) eol = rtext.size();
            std::string line = rtext.substr(pos, eol - pos);
            pos = eol + 1;
            ++lineno;
            if (!line.empty() && line.back() == '\r') line.pop_back();
            const std::size_t hash = line.find('#');
            if (hash != std::string::npos) line.erase(hash);
            std::size_t b = 0;
            while (b < line.size() && (line[b] == ' ' || line[b] == '\t')) ++b;
            if (b == line.size()) continue;
            std::uint32_t va = 0;
            const char* end = nullptr;
            if (!parse_u32(line.c_str() + b, &end, va) || (*end != ' ' && *end != '\t' && *end != 0)) {
                std::fprintf(stderr, "p3fes_recomp: %s:%zu: expected '<hex start> <name>'\n", args.replace, lineno);
                return 2;
            }
            while (*end == ' ' || *end == '\t') ++end;
            std::string name;
            while (*end && *end != ' ' && *end != '\t') name += *end++;
            // mid-body entries the game defines as well: `@0x<pc>` tokens (recomp/README.md "Replacements")
            std::vector<std::uint32_t> entries;
            for (;;) {
                while (*end == ' ' || *end == '\t') ++end;
                if (!*end) break;
                std::uint32_t e = 0;
                const char* e_end = nullptr;
                if (*end != '@' || !parse_u32(end + 1, &e_end, e) || (*e_end != ' ' && *e_end != '\t' && *e_end != 0)) {
                    std::fprintf(stderr, "p3fes_recomp: %s:%zu: expected '<hex start> <name> [@0x<entry pc>...]'\n", args.replace, lineno);
                    return 2;
                }
                entries.push_back(e);
                end = e_end;
            }
            opt.replace.push_back({va, name, entries});
        }
    }
    if (args.group) {
        std::uint32_t g = 0;
        if (!parse_u32(args.group, nullptr, g) || g == 0) {
            std::fprintf(stderr, "p3fes_recomp: --group-size: bad value '%s'\n", args.group);
            return 2;
        }
        opt.group_size = g;
    }
    opt.stable_units = args.stable_units;
    opt.selectors = !args.no_selectors;

    ElfWordSource words(elf);
    Program prog(fl, words, switches);
    EmitReport report;
    std::string error;
    const bool ok = emit_program(prog, opt, report, error);

    std::fprintf(stderr,
                 "p3fes_recomp: %zu functions, %zu selected, %zu emitted into %zu files (%zu replaced by game/); %zu mid-body entry points in %zu functions\n",
                 report.functions_total, report.functions_selected, report.functions_emitted, report.files, report.replaced,
                 report.entry_points, report.functions_with_entries);
    const FunctionStats& s = report.stats;
    std::fprintf(stderr,
                 "p3fes_recomp: %zu words, %zu data words skipped, %zu switches (%zu targets), %zu mid-body calls, "
                 "%zu static tail calls, %zu jalr, %zu indirect tail jumps, %zu chunk ends into no function\n",
                 s.words, s.data_words, s.switches, s.switch_targets, s.mid_body_calls, s.tail_calls, s.indirect_calls,
                 s.indirect_tails, s.unreachable_ends);
    std::fprintf(stderr,
                 "p3fes_recomp: ADR-0013: %zu cycle adds (%zu words charged)%s, %zu entry checks, %zu back-edge checks%s\n",
                 report.gen.cycle_adds, report.gen.cycle_words, opt.cycles ? "" : " [--no-cycles]",
                 report.gen.entry_checks, report.gen.backedge_checks, opt.check_events ? "" : " [--no-check-events]");
    for (const auto& [from, to] : report.unowned)
        std::fprintf(stderr, "p3fes_recomp: target 0x%08x (from 0x%08x) lies in no function\n", to, from);
    for (const FunctionProblem& fp : report.problems)
        std::fprintf(stderr, "p3fes_recomp: %s @ 0x%08x: %s at 0x%08x (target 0x%08x)\n", fp.fn->name.c_str(), fp.fn->start,
                     problem_name(fp.problem.kind), fp.problem.pc, fp.problem.target);
    if (!ok) {
        std::fprintf(stderr, "p3fes_recomp: %s\n", error.c_str());
        return 1;
    }
    if (!report.problems.empty()) {
        std::fprintf(stderr, "p3fes_recomp: %zu problems in %zu functions emitted as traps (--keep-going)\n",
                     report.problems.size(), report.problem_functions);
    }
    return 0;
}
