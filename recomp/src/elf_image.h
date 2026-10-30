// Read-only view of the game's EE ELF (SLUS_216.21) for the recompiler.
//
// The file is never committed (GOAL.md ground rules); the caller passes its path. Before any
// word is served the SHA-256 of the whole file is compared with the digest recorded in
// docs/INVENTORY.md; a mismatch is a hard refusal, not a warning. The VA <-> file mapping is
// parsed from the ELF32 program headers (docs/ANALYSIS/00_elf_layout.md: a single PT_LOAD
// with bytes at p_offset 0x80 for p_vaddr 0x100000, filesz == memsz) rather than hard-coded,
// and then checked against those documented facts.
//
// No exceptions: load() returns a LoadResult whose `error` is non-null on failure.
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <vector>

namespace p3fes::recomp {

// SHA-256 of SLUS_216.21 (docs/INVENTORY.md), lowercase hex.
inline constexpr char kSlusSha256[] = "d1b163eb20cb72d8764d2b94a8751abfc9e82fce7ae9e692dfaf97d64e3957bc";

struct ElfSegment {
    std::uint32_t vaddr = 0;
    std::uint32_t offset = 0;
    std::uint32_t filesz = 0;
    std::uint32_t memsz = 0;
    std::uint32_t flags = 0;
};

class ElfImage {
public:
    struct LoadResult {
        const char* error = nullptr;  // nullptr on success; otherwise a static message
        char sha256_hex[65] = {};     // digest of the file that was read (even on digest mismatch)
    };

    // Reads the file, verifies its SHA-256 against `expected_sha256_hex` (default: the SLUS
    // digest) and parses the program headers. On any failure the image stays empty.
    LoadResult load(const char* path, const char* expected_sha256_hex = kSlusSha256);

    bool loaded() const noexcept { return !bytes_.empty(); }
    std::uint32_t entry() const noexcept { return entry_; }
    const std::vector<ElfSegment>& segments() const noexcept { return segments_; }

    // Little-endian 32-bit word at `va`; nullopt when `va` is unaligned or has no file bytes.
    std::optional<std::uint32_t> word_at(std::uint32_t va) const noexcept;

    // File offset backing `va`, or nullopt if no PT_LOAD with file bytes covers it.
    std::optional<std::size_t> file_offset(std::uint32_t va) const noexcept;

    // Pointer to `len` contiguous bytes at `va`, or nullptr when the range is not backed.
    const std::uint8_t* bytes_at(std::uint32_t va, std::size_t len) const noexcept;

    std::size_t file_size() const noexcept { return bytes_.size(); }

private:
    std::vector<std::uint8_t> bytes_;
    std::vector<ElfSegment> segments_;
    std::uint32_t entry_ = 0;
};

// SHA-256 of `len` bytes into `out_hex` (65 bytes, lowercase, NUL-terminated).
void sha256_hex(const std::uint8_t* data, std::size_t len, char out_hex[65]) noexcept;

}  // namespace p3fes::recomp
