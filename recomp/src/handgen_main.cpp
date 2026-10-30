// p3fes_handgen: write the register-faithful C++ body of one or more functions (recomp/README.md "p3fes_handgen").
//
//   p3fes_handgen --elf <SLUS_216.21> --functions symbols/functions.json --chunks symbols/function_chunks.txt
//                 --jumptables symbols/jumptables.json [--sym symbols/p3fes.sym]
//                 --only <a,b,...|@file> [--slice <name>]
//                 [--out-cpp <file>] [--out-h <file>] [--out-replaced <file>] [--out-test <file>]
//                 [--header-include <p3fes/game/x.h>] [--body-suffix <s>] [--shim-suffix <s>] [--shim | --no-shim]
//
// Writes one translation unit with every requested function (game:: bodies; recomp_gen shims only with --shim-suffix
// or --shim), optionally a header with their declarations, the game/replaced.txt rows and a pair-test skeleton
// (tests/game/handgen_pairs.h). In the replacement flow (no --shim-suffix) the unit defines no entry point: the
// replaced functions' fn_<name>_<addr8> forwarders are generated from game/replaced.txt (game/forwarders.cmake,
// recomp/README.md "Forwarders"), so the rows are all a slice adds.
// Without --out-cpp the unit goes to stdout. Exit 1 when a function could not be generated (named on stderr).
#include "elf_image.h"
#include "emit_analyze.h"
#include "emit_cgen.h"
#include "function_list.h"
#include "handgen.h"
#include "handgen_test.h"

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace {

using namespace p3fes::recomp;

void usage(std::FILE* to) {
    std::fputs(
        "usage: p3fes_handgen --elf <path> --functions <functions.json> --chunks <function_chunks.txt>\n"
        "                     --jumptables <jumptables.json> [--sym <p3fes.sym>] --only <a,b,...|@file> [options]\n"
        "\n"
        "  --only <list>            function starts (hex), comma separated, or @file (one per line, '#' comments)\n"
        "  --slice <name>           slice name (test case names, the skeleton's file comment); default 'handgen'\n"
        "  --out-cpp <file>         the translation unit (default: stdout)\n"
        "  --out-h <file>           a header declaring the game:: bodies\n"
        "  --out-replaced <file>    the game/replaced.txt rows ('<hex start> <name>')\n"
        "  --out-test <file>        a pair-test skeleton (tests/game/test_<slice>.cpp)\n"
        "  --header-include <inc>   #include the unit adds for its own header (e.g. p3fes/game/my_slice.h)\n"
        "  --body-suffix <s>        appended to every game:: body's name (next to an existing typed version)\n"
        "  --shim-suffix <s>        write recomp_gen shims fn_X<s> (self-tests: pair fn_X<s> with the recompiled fn_X)\n"
        "  --shim / --no-shim       write the shims / none (default: only with --shim-suffix; the replacement flow's\n"
        "                           entry points are generated from game/replaced.txt, game/forwarders.cmake)\n"
        "  --replaced <file>        game/replaced.txt: with --shim-suffix, the skeleton pairs a listed function with its\n"
        "                           fn_X__recomp (a build emitted with --replace), the others with the plain fn_X\n",
        to);
}

bool write_file(const std::string& path, const std::string& text) {
    std::FILE* f = std::fopen(path.c_str(), "wb");
    if (!f) return false;
    const bool ok = std::fwrite(text.data(), 1, text.size(), f) == text.size();
    std::fclose(f);
    return ok;
}

bool parse_list(const char* arg, std::vector<std::uint32_t>& out) {
    std::string text;
    if (arg[0] == '@') {
        if (!read_file(arg + 1, text)) return false;
    } else {
        text = arg;
    }
    // Lines; '#' starts a comment; a line may hold several addresses separated by ',' or ';'.
    std::size_t pos = 0;
    while (pos < text.size()) {
        std::size_t eol = text.find('\n', pos);
        if (eol == std::string::npos) eol = text.size();
        std::string ln = text.substr(pos, eol - pos);
        pos = eol + 1;
        const std::size_t hash = ln.find('#');
        if (hash != std::string::npos) ln.erase(hash);
        std::size_t p = 0;
        while (p < ln.size()) {
            std::size_t e = ln.find_first_of(",;", p);
            if (e == std::string::npos) e = ln.size();
            const std::string item = ln.substr(p, e - p);
            p = e + 1;
            const std::size_t b = item.find_first_not_of(" \t\r");
            if (b == std::string::npos) continue;
            char* end = nullptr;
            const unsigned long long v = std::strtoull(item.c_str() + b, &end, 16);
            if (end == item.c_str() + b || item.find_first_not_of(" \t\r", static_cast<std::size_t>(end - item.c_str())) != std::string::npos)
                return false;
            out.push_back(static_cast<std::uint32_t>(v));
        }
    }
    return !out.empty();
}

}  // namespace

int main(int argc, char** argv) {
    const char *elf_path = nullptr, *functions = nullptr, *chunks = nullptr, *jumptables = nullptr, *sym = nullptr, *only = nullptr;
    std::string slice = "handgen", out_cpp, out_h, out_replaced, out_test, header_include, replaced_path;
    HandgenOptions opt;
    int shim = -1;  // --shim 1, --no-shim 0, default: with --shim-suffix only
    for (int i = 1; i < argc; ++i) {
        auto next = [&]() -> const char* { return i + 1 < argc ? argv[++i] : nullptr; };
        const std::string a = argv[i];
        const char* v = nullptr;
        if (a == "--help" || a == "-h") { usage(stdout); return 0; }
        else if (a == "--no-shim") shim = 0;
        else if (a == "--shim") shim = 1;
        else if (!(v = next())) { usage(stderr); return 2; }
        else if (a == "--elf") elf_path = v;
        else if (a == "--functions") functions = v;
        else if (a == "--chunks") chunks = v;
        else if (a == "--jumptables") jumptables = v;
        else if (a == "--sym") sym = v;
        else if (a == "--only") only = v;
        else if (a == "--slice") slice = v;
        else if (a == "--out-cpp") out_cpp = v;
        else if (a == "--out-h") out_h = v;
        else if (a == "--out-replaced") out_replaced = v;
        else if (a == "--out-test") out_test = v;
        else if (a == "--header-include") header_include = v;
        else if (a == "--body-suffix") opt.body_suffix = v;
        else if (a == "--shim-suffix") opt.shim_suffix = v;
        else if (a == "--replaced") replaced_path = v;
        else { usage(stderr); return 2; }
    }
    if (!elf_path || !functions || !chunks || !jumptables || !only) {
        usage(stderr);
        return 2;
    }
    opt.shim = shim < 0 ? !opt.shim_suffix.empty() : shim == 1;
    const auto t0 = std::chrono::steady_clock::now();

    ElfImage elf;
    const ElfImage::LoadResult lr = elf.load(elf_path);
    if (lr.error) {
        std::fprintf(stderr, "p3fes_handgen: %s: %s\n", elf_path, lr.error);
        return 1;
    }
    FunctionList fl;
    std::string text;
    if (!read_file(functions, text) || fl.load_functions_json(text)) {
        std::fprintf(stderr, "p3fes_handgen: cannot load %s\n", functions);
        return 1;
    }
    std::size_t mismatches = 0;
    if (!read_file(chunks, text) || fl.apply_chunk_list(text, &mismatches)) {
        std::fprintf(stderr, "p3fes_handgen: cannot load %s\n", chunks);
        return 1;
    }
    SwitchTables switches;
    if (!read_file(jumptables, text) || switches.load_json(text)) {
        std::fprintf(stderr, "p3fes_handgen: cannot load %s\n", jumptables);
        return 1;
    }
    SymbolTable syms;
    const SymbolTable* symp = nullptr;
    if (sym) {
        if (!read_file(sym, text) || syms.load_sym(text)) {
            std::fprintf(stderr, "p3fes_handgen: cannot load %s\n", sym);
            return 1;
        }
        symp = &syms;
    }
    std::vector<std::uint32_t> starts;
    if (!parse_list(only, starts)) {
        std::fprintf(stderr, "p3fes_handgen: --only: bad address list '%s'\n", only);
        return 2;
    }

    std::set<std::uint32_t> replaced_set;  // --replaced game/replaced.txt: which skeleton entries pair with __recomp
    if (!replaced_path.empty()) {
        std::string rtext;
        if (!read_file(replaced_path.c_str(), rtext)) {
            std::fprintf(stderr, "p3fes_handgen: cannot read %s\n", replaced_path.c_str());
            return 1;
        }
        std::size_t pos = 0;  // '<hex start> <name>' rows, '#' comments
        while (pos < rtext.size()) {
            std::size_t eol = rtext.find('\n', pos);
            if (eol == std::string::npos) eol = rtext.size();
            const std::string ln = rtext.substr(pos, eol - pos);
            pos = eol + 1;
            const std::size_t b = ln.find_first_not_of(" \t");
            if (b == std::string::npos || ln[b] == '#') continue;
            replaced_set.insert(static_cast<std::uint32_t>(std::strtoul(ln.c_str() + b, nullptr, 16)));
        }
    }

    ElfWordSource words(elf);
    Program prog(fl, words, switches);
    prog.compute_entries_and_returns(nullptr);

    std::vector<HandgenFunction> fns;
    int failed = 0;
    std::set<std::uint32_t> seen;
    for (std::uint32_t s : starts) {
        if (!seen.insert(s).second) continue;
        const Function* f = fl.find(s);
        if (!f) {
            std::fprintf(stderr, "p3fes_handgen: no function starts at 0x%x\n", s);
            ++failed;
            continue;
        }
        const FunctionAnalysis an = analyze_function(prog, *f);
        HandgenFunction hf = handgen_function(prog, an, &elf, symp, opt);
        if (!hf.error.empty()) {
            std::fprintf(stderr, "p3fes_handgen: %s @ 0x%x: not generated: %s\n", f->name.c_str(), s, hf.error.c_str());
            ++failed;
            continue;
        }
        fns.push_back(std::move(hf));
    }

    // --- the translation unit ---
    std::string cpp;
    cpp += "// Generated by p3fes_handgen (slice " + slice + ") from SLUS_216.21 and symbols/: the faithful starting point of a\n"
           "// hand decompilation. Every body keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and\n"
           "// check points (game/include/p3fes/game/hg_cpu.h); rename, restructure, comment and type it on top of that, and keep\n"
           "// the pair tests green (docs/PHASE5_AGENT_BRIEF.md \"Using p3fes_handgen\").\n";
    cpp += "#include \"p3fes/game/hg_cpu.h\"\n";
    if (!header_include.empty()) cpp += "#include \"" + header_include + "\"\n";
    cpp += "\nnamespace p3fes::recomp_gen {\n";
    std::set<std::string> decls;
    for (const HandgenFunction& f : fns) {
        for (const std::string& d : f.callees) decls.insert(d);
        if (opt.shim) {
            decls.insert("void " + f.symbol + opt.shim_suffix + "(p3fes::EEContext&);");
            for (const HandgenFunction::Entry& e : f.entries) decls.insert("void " + e.symbol + opt.shim_suffix + "(p3fes::EEContext&);");
        }
    }
    for (const std::string& d : decls) cpp += d + "\n";
    cpp += "}  // namespace p3fes::recomp_gen\n\nnamespace p3fes::game {\n\nnamespace gen = ::p3fes::recomp_gen;\n\n";
    for (const HandgenFunction& f : fns) cpp += f.body + "\n";
    cpp += "}  // namespace p3fes::game\n";
    if (opt.shim) {
        cpp += "\n// The recompiled program's entry points (the dispatch table and every generated call site use them).\n";
        for (const HandgenFunction& f : fns) {
            cpp += f.shim;
            for (const HandgenFunction::Entry& e : f.entries) cpp += e.shim;
        }
    } else {
        cpp += "\n// The recompiled program's entry points fn_<name>_<addr8> are generated from game/replaced.txt (game/forwarders.cmake).\n";
    }

    if (out_cpp.empty()) {
        std::fwrite(cpp.data(), 1, cpp.size(), stdout);
    } else if (!write_file(out_cpp, cpp)) {
        std::fprintf(stderr, "p3fes_handgen: cannot write %s\n", out_cpp.c_str());
        return 1;
    }
    if (!out_h.empty()) {
        std::string h = "// Generated by p3fes_handgen (slice " + slice + "): the register-ABI bodies (arguments in $a0.., result in $v0).\n"
                        "#pragma once\n\n#include \"p3fes/ee_context.h\"\n\nnamespace p3fes::game {\n\n";
        for (const HandgenFunction& f : fns) h += f.decl;
        h += "\n}  // namespace p3fes::game\n";
        if (!write_file(out_h, h)) {
            std::fprintf(stderr, "p3fes_handgen: cannot write %s\n", out_h.c_str());
            return 1;
        }
    }
    if (!out_replaced.empty()) {
        std::string r = "# " + slice + " (p3fes_handgen)\n";
        for (const HandgenFunction& f : fns) r += f.replaced_row + "\n";
        if (!write_file(out_replaced, r)) {
            std::fprintf(stderr, "p3fes_handgen: cannot write %s\n", out_replaced.c_str());
            return 1;
        }
    }
    if (!out_test.empty()) {
        // The recompiled body: fn_X__recomp in the replacement flow (no shim suffix: the function goes into
        // game/replaced.txt) and for a listed function of --replaced; otherwise the plain recompiled fn_X.
        std::vector<TestEntry> entries;
        for (const HandgenFunction& f : fns) {
            const bool replaced = opt.shim_suffix.empty() || replaced_set.count(f.start);
            entries.push_back({f.start, f.name, f.symbol + opt.shim_suffix, f.symbol + (replaced ? "__recomp" : "")});
            // each mid-body entry is its own pair: the entry's wrapper against the recompiled entry form at that address
            for (const HandgenFunction::Entry& e : f.entries)
                entries.push_back({e.pc, e.name, e.symbol + opt.shim_suffix, e.symbol + (replaced ? "__recomp" : "")});
        }
        const std::string t = pair_test_skeleton(slice, entries, header_include);
        if (!write_file(out_test, t)) {
            std::fprintf(stderr, "p3fes_handgen: cannot write %s\n", out_test.c_str());
            return 1;
        }
    }

    HandgenStats tot;
    std::size_t mid_entries = 0;
    for (const HandgenFunction& f : fns) {
        mid_entries += f.entries.size();
        const HandgenStats& s = f.stats;
        tot.blocks += s.blocks; tot.statements += s.statements; tot.charges += s.charges; tot.backedges += s.backedges;
        tot.loops += s.loops; tot.ifs += s.ifs; tot.switches += s.switches; tot.gotos += s.gotos; tot.labels += s.labels;
        tot.calls += s.calls; tot.hoisted_slots += s.hoisted_slots; tot.ordered_slots += s.ordered_slots;
    }
    const double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
    std::fprintf(stderr,
                 "p3fes_handgen: %zu functions generated (%zu mid-body entries), %d refused; %zu blocks, %zu statements, %zu loops, %zu ifs, "
                 "%zu switches, %zu calls, %zu gotos (%zu labels), %zu back-edge checks; delay slots %zu hoisted / %zu ordered; %.0f ms\n",
                 fns.size(), mid_entries, failed, tot.blocks, tot.statements, tot.loops, tot.ifs, tot.switches, tot.calls, tot.gotos, tot.labels,
                 tot.backedges, tot.hoisted_slots, tot.ordered_slots, ms);
    return failed ? 1 : 0;
}
