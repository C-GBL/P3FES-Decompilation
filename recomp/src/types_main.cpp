// p3fes_types: whole-program struct-layout recovery (types.h, docs/ANALYSIS/28_types.md).
//
//   p3fes_types --elf <SLUS_216.21> --functions symbols/functions.json --chunks symbols/function_chunks.txt
//               --jumptables symbols/jumptables.json [--anchors tools/ours/types/anchors.txt]
//               [--max-conflicts N] --out <types.raw.json>
//
// The raw JSON is post-processed by tools/ours/types/types_build.py (types.json, headers, validation).
#include "elf_image.h"
#include "emit_program.h"
#include "function_list.h"
#include "types.h"

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>

namespace {

using namespace p3fes::recomp;

void usage(std::FILE* to) {
    std::fputs("usage: p3fes_types --elf <path> --functions <functions.json> --chunks <function_chunks.txt>\n"
               "                   --jumptables <jumptables.json> [--anchors <file>] [--max-conflicts N] --out <file>\n"
               "  anchors: one per line '<StructName> param|ret|gslot|gobj <hex addr> [arg index]' or\n"
               "           'size <StructName> <bytes>' ('#' comments)\n",
               to);
}

bool parse_anchors(const std::string& text, std::vector<types::Anchor>& out, std::map<std::string, std::uint32_t>& sizes) {
    std::istringstream in(text);
    std::string line;
    int ln = 0;
    while (std::getline(in, line)) {
        ++ln;
        const std::size_t h = line.find('#');
        if (h != std::string::npos) line.erase(h);
        std::istringstream ls(line);
        types::Anchor a;
        std::string addr;
        if (!(ls >> a.name)) continue;
        if (a.name == "size") {  // 'size <StructName> <bytes>'
            std::string nm;
            std::uint32_t sz = 0;
            if (ls >> nm >> sz) sizes[nm] = sz;
            continue;
        }
        if (!(ls >> a.how >> addr)) {
            std::fprintf(stderr, "p3fes_types: anchors line %d: expected '<name> <how> <addr> [index]'\n", ln);
            return false;
        }
        a.addr = static_cast<std::uint32_t>(std::strtoul(addr.c_str(), nullptr, 16));
        ls >> a.index;
        if (a.how != "param" && a.how != "ret" && a.how != "gslot" && a.how != "gobj") {
            std::fprintf(stderr, "p3fes_types: anchors line %d: unknown kind '%s'\n", ln, a.how.c_str());
            return false;
        }
        out.push_back(a);
    }
    return true;
}

}  // namespace

int main(int argc, char** argv) {
    const char *elf_path = nullptr, *functions = nullptr, *chunks = nullptr, *jumptables = nullptr, *anchors = nullptr,
               *out = nullptr;
    types::SolveOptions opt;
    for (int i = 1; i < argc; ++i) {
        const std::string a = argv[i];
        if (a == "--help" || a == "-h") { usage(stdout); return 0; }
        if (i + 1 >= argc) { usage(stderr); return 2; }
        const char* v = argv[++i];
        if (a == "--elf") elf_path = v;
        else if (a == "--functions") functions = v;
        else if (a == "--chunks") chunks = v;
        else if (a == "--jumptables") jumptables = v;
        else if (a == "--anchors") anchors = v;
        else if (a == "--out") out = v;
        else if (a == "--max-conflicts") opt.max_conflicts = std::atoi(v);
        else { usage(stderr); return 2; }
    }
    if (!elf_path || !functions || !chunks || !jumptables || !out) {
        usage(stderr);
        return 2;
    }
    const auto t0 = std::chrono::steady_clock::now();
    ElfImage elf;
    const ElfImage::LoadResult lr = elf.load(elf_path);
    if (lr.error) {
        std::fprintf(stderr, "p3fes_types: %s: %s\n", elf_path, lr.error);
        return 1;
    }
    FunctionList fl;
    std::string text;
    if (!read_file(functions, text) || fl.load_functions_json(text)) {
        std::fprintf(stderr, "p3fes_types: cannot load %s\n", functions);
        return 1;
    }
    std::size_t mismatches = 0;
    if (!read_file(chunks, text) || fl.apply_chunk_list(text, &mismatches)) {
        std::fprintf(stderr, "p3fes_types: cannot load %s\n", chunks);
        return 1;
    }
    SwitchTables switches;
    if (!read_file(jumptables, text) || switches.load_json(text)) {
        std::fprintf(stderr, "p3fes_types: cannot load %s\n", jumptables);
        return 1;
    }
    if (anchors) {
        if (!read_file(anchors, text) || !parse_anchors(text, opt.anchors, opt.sizes)) {
            std::fprintf(stderr, "p3fes_types: cannot load %s\n", anchors);
            return 1;
        }
    }
    ElfWordSource words(elf);
    Program prog(fl, words, switches);
    prog.compute_entries_and_returns(nullptr);
    const auto t1 = std::chrono::steady_clock::now();

    types::Facts facts;
    types::AnalyzeStats ast;
    types::analyze_program(prog, facts, ast);
    const auto t2 = std::chrono::steady_clock::now();
    const double p1 = std::chrono::duration<double>(t2 - t1).count();

    types::SolveStats sst;
    if (!types::solve_and_write(prog, facts, opt, sst, out, ast, p1)) {
        std::fprintf(stderr, "p3fes_types: cannot write %s\n", out);
        return 1;
    }
    const auto t3 = std::chrono::steady_clock::now();
    std::fprintf(stderr,
                 "p3fes_types: %zu functions (%zu analysed, %zu skipped), %zu instructions, %zu type vars, %zu accesses, "
                 "%zu global accesses, %zu constraints; %zu unions, %zu vetoes (%zu anchor), %zu anchors; "
                 "load %.2f s, phase 1 %.2f s, solve+write %.2f s\n",
                 ast.functions, ast.analysed, ast.skipped, ast.instructions, facts.tvs.size(), facts.accesses.size(),
                 facts.gaccesses.size(), facts.cons.size(), sst.unions, sst.vetoes, sst.vetoes_anchor,
                 sst.anchors_applied, std::chrono::duration<double>(t1 - t0).count(), p1,
                 std::chrono::duration<double>(t3 - t2).count());
    return 0;
}
