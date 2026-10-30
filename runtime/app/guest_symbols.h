// Guest symbol lookup for host diagnostics (fatal reports, traces): `symbols/p3fes.sym` (the committed
// IDA export, `<addr8> <size8> <F|D|L> <name> ...`) read once at start-up. Optional: without the file every
// lookup prints the bare address. Never consulted on the guest path.
#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

namespace p3fes::app {

class GuestSymbols {
public:
    // Loads functions (F) and named data (D); false if the file cannot be read (the table stays empty).
    bool load(const std::filesystem::path& sym_file);
    bool empty() const noexcept { return funcs_.empty(); }

    // "name+0xoff" of the function containing `va` (or of the nearest data item for a data address);
    // "0xVA" when nothing covers it.
    std::string describe(std::uint32_t va) const;
    // Name of the function that starts exactly at `va`, or "" when none.
    std::string function_at(std::uint32_t va) const;

private:
    struct Entry {
        std::uint32_t va = 0, size = 0;
        std::string name;
    };
    static const Entry* find(const std::vector<Entry>& v, std::uint32_t va);
    std::vector<Entry> funcs_, data_;
};

} // namespace p3fes::app
