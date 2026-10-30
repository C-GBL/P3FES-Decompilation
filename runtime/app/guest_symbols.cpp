#include "guest_symbols.h"

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <sstream>

namespace p3fes::app {

bool GuestSymbols::load(const std::filesystem::path& sym_file) {
    std::ifstream in(sym_file);
    if (!in) return false;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream ls(line);
        std::string a, sz, kind, name;
        if (!(ls >> a >> sz >> kind >> name)) continue;
        Entry e;
        e.va = static_cast<std::uint32_t>(std::stoul(a, nullptr, 16));
        e.size = static_cast<std::uint32_t>(std::stoul(sz, nullptr, 16));
        e.name = name;
        if (kind == "F") funcs_.push_back(std::move(e));
        else if (kind == "D") data_.push_back(std::move(e));
    }
    const auto by_va = [](const Entry& x, const Entry& y) { return x.va < y.va; };
    std::sort(funcs_.begin(), funcs_.end(), by_va);
    std::sort(data_.begin(), data_.end(), by_va);
    return !funcs_.empty();
}

const GuestSymbols::Entry* GuestSymbols::find(const std::vector<Entry>& v, std::uint32_t va) {
    auto it = std::upper_bound(v.begin(), v.end(), va, [](std::uint32_t x, const Entry& e) { return x < e.va; });
    if (it == v.begin()) return nullptr;
    --it;
    return &*it;
}

std::string GuestSymbols::describe(std::uint32_t va) const {
    char buf[160];
    const std::uint32_t a = va & 0x1FFFFFFFu;
    if (const Entry* f = find(funcs_, a); f && a < f->va + std::max<std::uint32_t>(f->size, 1)) {
        std::snprintf(buf, sizeof buf, "0x%08X %s+0x%X", va, f->name.c_str(), a - f->va);
        return buf;
    }
    if (const Entry* d = find(data_, a); d && a - d->va < 0x10000u) {
        std::snprintf(buf, sizeof buf, "0x%08X %s+0x%X", va, d->name.c_str(), a - d->va);
        return buf;
    }
    std::snprintf(buf, sizeof buf, "0x%08X", va);
    return buf;
}

std::string GuestSymbols::function_at(std::uint32_t va) const {
    const Entry* f = find(funcs_, va);
    return (f && f->va == va) ? f->name : std::string();
}

} // namespace p3fes::app
