// Test fixtures for runtime/formats/: load real files from the gitignored
// extracted/ tree. Tests must skip cleanly (doctest MESSAGE + return) when a
// file is absent so the suite stays green on a checkout without game data.
#pragma once

#include <doctest.h>

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

#include "p3fes/formats/bytes.h"

namespace p3fes::test {

inline std::filesystem::path extracted_dir() {
    if (const char* env = std::getenv("P3FES_EXTRACTED"); env && *env) return env;
#ifdef P3FES_EXTRACTED_DIR
    return P3FES_EXTRACTED_DIR;
#else
    return "extracted";
#endif
}

// Reads a file relative to extracted/; nullopt if missing or unreadable.
inline std::optional<std::vector<std::byte>> load_extracted(const std::string& rel) {
    const std::filesystem::path p = extracted_dir() / rel;
    std::error_code ec;
    if (!std::filesystem::is_regular_file(p, ec)) return std::nullopt;
    std::ifstream f(p, std::ios::binary);
    if (!f) return std::nullopt;
    std::vector<std::byte> data(static_cast<std::size_t>(std::filesystem::file_size(p, ec)));
    if (!data.empty() && !f.read(reinterpret_cast<char*>(data.data()), static_cast<std::streamsize>(data.size())))
        return std::nullopt;
    return data;
}

inline formats::Bytes span_of(const std::vector<std::byte>& v) { return formats::Bytes{v.data(), v.size()}; }

}  // namespace p3fes::test

// Loads `rel` into `var` (std::vector<std::byte>) or skips the current test case.
#define P3FES_REQUIRE_FIXTURE(var, rel)                                                   \
    auto var##_opt = ::p3fes::test::load_extracted(rel);                                  \
    if (!var##_opt) {                                                                     \
        MESSAGE("skipped: fixture not present: " << rel);                                 \
        return;                                                                           \
    }                                                                                     \
    const std::vector<std::byte>& var = *var##_opt
