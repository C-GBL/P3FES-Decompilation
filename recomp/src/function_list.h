// The recompiler's function scope: IDA's function list and chunk ranges (ADR-0004, ADR-0011 §2).
//
// Two inputs, both exported from IDA and both owned by the symbol exporters:
//   * symbols/functions.json  — [{"a":"0x100008","s":520,"n":"start"}, ...]: start, total size
//                               of all chunks, name. Authority for the function set and names.
//   * a chunk list            — one function per line:
//                                 <start_hex> <name> C <s>-<e> [<s>-<e> ...] [D <ea>:<size> ...]
//                               `C` ranges are IDA chunks (half-open), `D` entries are IDA data
//                               items inside those chunks (addresses the recompiler must skip, not
//                               decode; ADR-0011 §2). symbols/function_chunks.txt, regenerated from the master by tools/ours/ida/export_function_chunks.py.
// Without a chunk list a function is assumed to be the single range [a, a + s), which is wrong
// for the 173 multi-chunk functions; callers must say which they used.
#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace p3fes::recomp {

struct Range {
    std::uint32_t start = 0;
    std::uint32_t end = 0;  // half-open
};

struct DataItem {
    std::uint32_t ea = 0;
    std::uint32_t size = 0;
};

struct Function {
    std::uint32_t start = 0;
    std::uint32_t size = 0;  // total of all chunks, as exported
    std::string name;
    std::vector<Range> chunks;     // empty until a chunk list is applied
    std::vector<DataItem> data;    // data items inside the chunks (sorted by ea)

    // True if `ea` lies inside a data item (must not be decoded).
    bool is_data(std::uint32_t ea) const noexcept;
};

struct FunctionList {
    std::vector<Function> functions;  // sorted by start
    bool has_chunks = false;          // a chunk list was applied

    // Parse symbols/functions.json text. Returns nullptr or a static error message.
    const char* load_functions_json(const std::string& text);

    // Parse a chunk list (format above) and attach chunks/data items to the functions whose start
    // matches. Functions present in the chunk list but absent from the list are appended
    // (the chunk list is a snapshot of the same database and may predate functions.json).
    // Returns nullptr or a static error message; *mismatches receives the count of starts that
    // appear in only one of the two inputs.
    const char* apply_chunk_list(const std::string& text, std::size_t* mismatches);

    const Function* find(std::uint32_t start) const noexcept;
};

// Read a whole file into `out`; false if it cannot be opened/read.
bool read_file(const char* path, std::string& out);

}  // namespace p3fes::recomp
