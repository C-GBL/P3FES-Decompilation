// PC wording for the memory-card messages: the patch table and its checked application (pc_text.h).
#include "pc_text.h"

#include <array>
#include <cstdio>
#include <cstring>

namespace p3fes::app::pc_text {
namespace {

// Line strings of the message-window table band 0x6B33F0-0x6B3DF0 (rows below are the table's row numbers).
constexpr std::array<StringPatch, 12> kStrings{{
    // rows 0 and 16, line 0 (no card)
    {0x6B33F0u, "No memory card (for PS2)", "No save data was found."},
    // row 16, line 1 (row 0 no longer uses it)
    {0x6B3410u, "inserted in MEMORY CARD slot 1.", "Your progress cannot be saved."},
    // row 1 (unformatted card)
    {0x6B3440u, "The memory card (for PS2) in", "The save data is not set up."},
    {0x6B3460u, "MEMORY CARD slot 1 is", "Set it up now?"},
    // row 2 (formatting)
    {0x6B34B0u, "Formatting memory card (for PS2)", "Setting up save data..."},
    // rows 2 and 7 (do not switch off)
    {0x6B3500u, "Do not remove memory card", "Do not close the game."},
    // row 3
    {0x6B3590u, "Format failed.", "Setup failed."},
    // row 5 (create the game's file; was rows 5 and 6, line 1)
    {0x6B3640u, "memory card (for PS2) in", "Create new save data?"},
    // row 7 (saving)
    {0x6B3730u, "Saving data on memory card", "Saving data..."},
    // row 15 (the boot check)
    {0x6B3860u, "Checking memory card (8MB)", "Checking save data..."},
    // rows 21 and 6 (not enough free space)
    {0x6B3B20u, "Insufficient free space on memory card", "There is not enough free space"},
    {0x6B3B50u, "(for PS2) in MEMORY CARD slot 1.", "to save data."},
}};

constexpr std::uint32_t kBlank = kBlankLineVa;
constexpr std::uint32_t row_count_va(std::uint32_t row) { return kTableVa + 12u * row + 4u; }

constexpr std::array<WordPatch, 21> kWords{{
    // row 0: "No save data was found." / blank
    {0x6B3434u, 0x6B3410u, kBlank, "row 0 line 1"},
    {row_count_va(0), 3, 2, "row 0 count"},
    // row 1: "The save data is not set up." / "Set it up now?" / blank
    {0x6B34A8u, 0x6B3480u, kBlank, "row 1 line 2"},
    {row_count_va(1), 4, 3, "row 1 count"},
    // row 2: "Setting up save data..." / blank / "Do not close the game." / blank
    {0x6B3574u, 0x6B34E0u, kBlank, "row 2 line 1"},
    {0x6B357Cu, 0x6B3520u, kBlank, "row 2 line 3"},
    {row_count_va(2), 7, 4, "row 2 count"},
    // row 5: "Create new save data?"
    {0x6B3678u, 0x6B3620u, 0x6B3640u, "row 5 line 0"},
    {row_count_va(5), 3, 1, "row 5 count"},
    // row 6: "There is not enough free space" / "to save data." (row 21's two lines)
    {0x6B3710u, 0x6B3690u, 0x6B3B20u, "row 6 line 0"},
    {0x6B3714u, 0x6B3640u, 0x6B3B50u, "row 6 line 1"},
    {row_count_va(6), 5, 2, "row 6 count"},
    // row 7: "Saving data..." / blank / "Do not close the game." / blank
    {0x6B37C4u, 0x6B3750u, kBlank, "row 7 line 1"},
    {0x6B37C8u, 0x6B3770u, 0x6B3500u, "row 7 line 2"},
    {row_count_va(7), 8, 4, "row 7 count"},
    // row 15 (boot): "Checking save data..."
    {row_count_va(15), 2, 1, "row 15 count"},
    // row 16: "No save data was found." / "Your progress cannot be saved." / "Start the game anyway?"
    {0x6B3928u, 0x6B38A0u, 0x6B3900u, "row 16 line 2"},
    {row_count_va(16), 6, 3, "row 16 count"},
    // row 21: "There is not enough free space" / "to save data." / blank / "Start the game anyway?" / blank
    {0x6B3BC8u, 0x6B3B80u, kBlank, "row 21 line 2"},
    {0x6B3BCCu, 0x6B3BA8u, 0x6B3900u, "row 21 line 3"},
    {row_count_va(21), 7, 5, "row 21 count"},
}};

std::string hex(std::uint32_t v) {
    char b[16];
    std::snprintf(b, sizeof b, "0x%06X", v);
    return b;
}

std::uint32_t rd32(const std::uint8_t* p) {
    return static_cast<std::uint32_t>(p[0]) | static_cast<std::uint32_t>(p[1]) << 8 | static_cast<std::uint32_t>(p[2]) << 16 |
           static_cast<std::uint32_t>(p[3]) << 24;
}

void wr32(std::uint8_t* p, std::uint32_t v) {
    for (int i = 0; i < 4; ++i) p[i] = static_cast<std::uint8_t>(v >> (8 * i));
}

// Bytes [p, p + n) equal `text` followed by NULs.
bool holds(const std::uint8_t* p, std::size_t n, std::string_view text) {
    if (text.size() >= n) return false;
    if (std::memcmp(p, text.data(), text.size()) != 0) return false;
    for (std::size_t i = text.size(); i < n; ++i)
        if (p[i] != 0) return false;
    return true;
}

std::string printable(const std::uint8_t* p, std::size_t n) {
    std::string s;
    for (std::size_t i = 0; i < n; ++i) {
        const unsigned c = p[i];
        if (c >= 0x20 && c < 0x7F) s += static_cast<char>(c);
        else {
            char b[8];
            std::snprintf(b, sizeof b, "\\x%02X", c);
            s += b;
        }
    }
    return s;
}

} // namespace

std::span<const StringPatch> string_patches() { return kStrings; }
std::span<const WordPatch> word_patches() { return kWords; }

bool safe_char(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == ' ' || c == '.' || c == ',' ||
           c == '?' || c == '!' || c == '\'';
}

const char* to_string(Status s) {
    switch (s) {
    case Status::Applied: return "applied";
    case Status::AlreadyApplied: return "already applied";
    case Status::Mismatch: return "refused (the ELF's bytes differ)";
    }
    return "?";
}

Result apply(std::span<std::uint8_t> image, std::uint32_t image_va) {
    Result r;
    r.entries = kStrings.size() + kWords.size();
    auto at = [&](std::uint32_t va, std::size_t n) -> std::uint8_t* {
        if (va < image_va || va - image_va > image.size() || image.size() - (va - image_va) < n) return nullptr;
        return image.data() + (va - image_va);
    };
    // Pass 1: every entry is either all old or all new, and all entries agree.
    std::size_t olds = 0, news = 0;
    for (const StringPatch& s : kStrings) {
        const std::size_t n = s.old_text.size() + 1;
        const std::uint8_t* p = at(s.va, n);
        if (!p || s.new_text.size() > s.old_text.size()) {
            r.detail = "string " + hex(s.va) + ": outside the image or longer than the original";
            return r;
        }
        if (holds(p, n, s.old_text)) ++olds;
        else if (holds(p, n, s.new_text)) ++news;
        else {
            r.detail = "string " + hex(s.va) + ": expected \"" + std::string(s.old_text) + "\", found \"" + printable(p, n) + "\"";
            return r;
        }
    }
    for (const WordPatch& w : kWords) {
        const std::uint8_t* p = at(w.va, 4);
        if (!p) {
            r.detail = std::string(w.what) + " " + hex(w.va) + ": outside the image";
            return r;
        }
        const std::uint32_t v = rd32(p);
        if (v == w.old_value) ++olds;
        else if (v == w.new_value) ++news;
        else {
            r.detail = std::string(w.what) + " " + hex(w.va) + ": expected " + hex(w.old_value) + ", found " + hex(v);
            return r;
        }
    }
    if (news == r.entries) {
        r.status = Status::AlreadyApplied;
        return r;
    }
    if (olds != r.entries) {
        r.detail = std::to_string(olds) + " entries hold the original bytes, " + std::to_string(news) + " the new ones (partly patched image)";
        return r;
    }
    // Pass 2: write.
    for (const StringPatch& s : kStrings) {
        std::uint8_t* p = at(s.va, s.old_text.size() + 1);
        std::memset(p, 0, s.old_text.size() + 1);
        std::memcpy(p, s.new_text.data(), s.new_text.size());
    }
    for (const WordPatch& w : kWords) wr32(at(w.va, 4), w.new_value);
    r.status = Status::Applied;
    return r;
}

} // namespace p3fes::app::pc_text
