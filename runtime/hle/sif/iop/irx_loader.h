// IRX loader for the IOP modules the HLE interprets (ADR-0014; docs/ANALYSIS/19 §2.1). An IRX is a
// little-endian MIPS relocatable ELF (e_type 0xFF80) with one PT_LOAD, a `.iopmod` section
// {moduleinfo ptr, entry, gp, text size, data size, bss size, version u16, name[]} and REL sections
// (sh_type 9) whose entries carry R_MIPS_32 (2), R_MIPS_26 (4), R_MIPS_HI16 (5) and R_MIPS_LO16 (6)
// against the load base (the image is linked at 0). HI16 pairs positionally with the LO16 that follows
// it: value = (hi << 16) + sext(lo) + base, lo' = value & 0xFFFF, hi' = (value + 0x8000) >> 16 (all
// six modules have every HI16 followed by exactly one LO16, checked with a reader over the files).
//
// Imports: a table {0x41E00000, 0, version, name[8]} followed by 8-byte stubs `jr ra; li $0, ordinal`
// ended by a zero pair; `bind_imports` rewrites each stub's first word to a jump into the exporting
// module's function (guest library) or to a host-call word (HLE library, r3000.h), and lists what
// stayed unresolved. Exports: {0x41C00000, 0, version, name[8]} then function pointers until 0 --
// readable only after relocation (a function at offset 0 is otherwise indistinguishable from the end).
//
// Layout facts: ps2sdk @ 329e2bb `iop/kernel/include/irx.h` / `loadcore.h` (AFL-2.0; offsets only) and
// tools/ours/ida/open_irx.py, which already parsed `.iopmod` and the stub tables for the study. The
// relocation pairing rule and the stub-patching shape agree with the MIT reference ps2-web-recomp
// `runtime/src/iop/kernel.cpp` @ c0f476e (`relocate`, `link_imports`), consulted as a cross-check.
#pragma once

#include <map>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "iop_core.h"

namespace p3fes::hle::sif::iop {

inline constexpr u32 kImportMagic = 0x41E00000u;
inline constexpr u32 kExportMagic = 0x41C00000u;

struct IrxImport {
    std::string library;
    u16 version = 0;
    u32 table = 0;               // IOP address of the table header
    std::vector<u16> ordinals;   // in stub order
    std::vector<u32> stubs;      // IOP address of each stub (8 bytes)
};

struct IrxExport {
    std::string library;
    u16 version = 0;
    u32 table = 0;
    std::vector<u32> functions;  // IOP addresses, index = ordinal (0 = _start, 1..3 = loadcore slots)
};

struct IrxModule {
    std::string name;      // .iopmod name ("StandardKit/Sound/Foundation")
    u16 version = 0;       // .iopmod version (0x203)
    u32 base = 0;          // load address
    u32 entry = 0;         // absolute
    u32 gp = 0;            // absolute
    u32 text_size = 0, data_size = 0, bss_size = 0;
    u32 image_size = 0;    // bytes occupied from base (max(memsz, text + data + bss))
    std::map<u32, u32> relocations;  // R_MIPS type -> count applied
    std::vector<IrxImport> imports;
    std::vector<IrxExport> exports;
};

// Parses `file`, copies the PT_LOAD image to `base` (bss cleared), applies the relocations and reads
// the import/export tables. `error` names the first problem; nullopt then.
std::optional<IrxModule> load_irx(detail::IopRam& ram, std::span<const u8> file, u32 base, std::string& error);

// Memory the module needs at `load_irx` time (so a caller can allocate before loading).
std::optional<u32> irx_image_size(std::span<const u8> file, std::string& error);

// How an import is served: a guest function (another module's export) or a host call id.
struct ImportTarget {
    enum class Kind { Guest, Host, Unresolved } kind = Kind::Unresolved;
    u32 value = 0;  // guest address or host-call id
};
class ImportBinder {
public:
    virtual ~ImportBinder() = default;
    virtual ImportTarget resolve(std::string_view library, u16 ordinal) = 0;
};

struct UnresolvedImport {
    std::string library;
    u16 ordinal = 0;
};

// Patches every stub of `m`: guest -> `j target; nop`, host -> host-call word (the `li $0, n` stays),
// unresolved -> host-call word `trap_id` (the kernel's "unresolved import" trap) and an entry in the
// returned list. Idempotent for stubs already bound to a guest target.
std::vector<UnresolvedImport> bind_imports(detail::IopRam& ram, IrxModule& m, ImportBinder& binder, u32 trap_id);

}  // namespace p3fes::hle::sif::iop
