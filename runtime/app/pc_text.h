// PC wording for the memory-card messages (HostConfig::pc_text, --pc-text on|off). Pure C++, no game data.
//
// The port's "memory card" is a file on disk (%APPDATA%\P3FES\saves\Mcd001.ps2 by default), so text such as
// "Checking memory card (8MB) (for PlayStation(R)2)..." or "No memory card (for PS2) inserted in MEMORY CARD slot 1."
// makes no sense to a PC player. Every one of those messages is plain ASCII in the ELF's data, in one table: the
// message-window table `*0x7CDAC8` (= 0x6B3E00, `*0x7CDACC` = 29 rows of {u32 lines, u32 line count, u16 type, u16
// default choice}) that mcWndDrawText (sub_420A20, game/src/data/savedata.cpp) reads. The draw code uses the row's
// line count (the arrays are not NULL-terminated), centres the lines horizontally at the window's x + 352 and
// vertically around its y + 200, and places the choice below the last line; the window box is a fixed sprite.
// No disc file (BMD/PM1/BF, 12,019 files scanned) carries memory-card text; only the save screens' "SAVE DATA" sprite.
//
// The patch rewrites line strings in place (each new text no longer than the string it replaces, so it stays inside
// that string's own bytes; the rest is zero-filled), repoints line-array entries at other line strings of the same
// table band, and lowers line counts. Nothing is relocated: no new guest memory is used.
//
// Guarantees: every entry's old bytes are checked before anything is written; if the image holds neither the
// original bytes everywhere nor the patched bytes everywhere, nothing is written (Status::Mismatch, with the first
// differing entry in `detail`). Applying twice is a no-op (Status::AlreadyApplied).
//
// The patch changes guest memory, so it is OFF in headless runs (the replay gates compare eeMemory.bin byte for
// byte) and ON by default in windowed play and in GameHost users that do not say otherwise (the editor).
#pragma once

#include <cstddef>
#include <cstdint>
#include <span>
#include <string>
#include <string_view>

namespace p3fes::app::pc_text {

// A line string rewritten in place: [va, va + old_text.size()] holds old_text + NUL; afterwards new_text, then NULs
// up to the same end (new_text.size() <= old_text.size()).
struct StringPatch {
    std::uint32_t va;
    std::string_view old_text;
    std::string_view new_text;
};

// One little-endian word (a line pointer or a line count).
struct WordPatch {
    std::uint32_t va;
    std::uint32_t old_value;
    std::uint32_t new_value;
    const char* what;
};

std::span<const StringPatch> string_patches();
std::span<const WordPatch> word_patches();

// The message-window table (tests decode it before and after).
inline constexpr std::uint32_t kTableVa = 0x6B3E00u;
inline constexpr std::uint32_t kTableRows = 29;
inline constexpr std::uint32_t kBlankLineVa = 0x7CDA80u;  // the table's blank line, the 2-byte space 0x80 0x80

enum class Status { Applied, AlreadyApplied, Mismatch };

struct Result {
    Status status = Status::Mismatch;
    std::size_t entries = 0;  // patch entries checked
    std::string detail;       // Mismatch: which entry and what the image holds
};

// `image` = the ELF's program bytes as loaded, starting at guest address `image_va`.
Result apply(std::span<std::uint8_t> image, std::uint32_t image_va);

// Characters the new texts may use (all drawn by the game's font from its ASCII range; checked by the unit test).
bool safe_char(char c);

const char* to_string(Status s);

} // namespace p3fes::app::pc_text
