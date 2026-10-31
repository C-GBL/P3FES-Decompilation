// The tables the generated SK code comes with (sk_gen.h, written at build time by tools/ours/modernize/skgen.py from
// the user's LIB31 files -- derived from game data, so never committed; README.md "Generated code").
#pragma once

#include "sk_cpu.h"

namespace p3fes::native::sound::sk {

struct ModuleImage {
    const char* file;  // LIB31 file name
    u32 base;          // image base in IOP RAM (IopLayout::Pcsx2, runtime/hle/sif/iop/srv_sdr.h kSkModulesPcsx2)
    u32 entry, gp, text, data, bss;
    u64 text_fnv;      // FNV-1a 64 of the unrelocated text the code was made from (NativeSk::install checks it)
};

// A generated function by its IOP address (sk_gen.h kFunctions, ascending: call_address, the thread entries).
struct FnEntry {
    u32 addr;
    Fn fn;
};

}  // namespace p3fes::native::sound::sk
