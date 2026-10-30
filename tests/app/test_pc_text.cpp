// PC wording of the memory-card messages (runtime/app/pc_text.h): the patch table, its checked application on a
// synthetic image (always) and on the user's ELF (skips without it), and the message table before -> after.
#include <doctest.h>

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include "pc_text.h"

using namespace p3fes::app;

namespace {

constexpr std::uint32_t kBase = 0x6B3000u;  // synthetic image: the table band and the blank line near gp
constexpr std::uint32_t kEnd = 0x7CE000u;

std::uint32_t rd32(const std::vector<std::uint8_t>& img, std::uint32_t base, std::uint32_t va) {
    const std::uint8_t* p = img.data() + (va - base);
    return static_cast<std::uint32_t>(p[0]) | static_cast<std::uint32_t>(p[1]) << 8 | static_cast<std::uint32_t>(p[2]) << 16 |
           static_cast<std::uint32_t>(p[3]) << 24;
}

void wr32(std::vector<std::uint8_t>& img, std::uint32_t base, std::uint32_t va, std::uint32_t v) {
    for (int i = 0; i < 4; ++i) img[va - base + i] = static_cast<std::uint8_t>(v >> (8 * i));
}

// An image holding exactly the patch table's old bytes (everything else 0xEE, so stray writes show).
std::vector<std::uint8_t> synthetic_original() {
    std::vector<std::uint8_t> img(kEnd - kBase, 0xEE);
    for (const pc_text::StringPatch& s : pc_text::string_patches()) {
        std::memcpy(img.data() + (s.va - kBase), s.old_text.data(), s.old_text.size());
        img[s.va - kBase + s.old_text.size()] = 0;
    }
    for (const pc_text::WordPatch& w : pc_text::word_patches()) wr32(img, kBase, w.va, w.old_value);
    return img;
}

std::string lower(std::string s) {
    for (char& c : s) c = static_cast<char>(c >= 'A' && c <= 'Z' ? c - 'A' + 'a' : c);
    return s;
}

const char* elf_path() {
    if (const char* p = std::getenv("P3FES_ELF")) return p;
#if defined(P3FES_ELF_DEFAULT)
    return P3FES_ELF_DEFAULT;
#else
    return "";
#endif
}

// The ELF's single PT_LOAD with file bytes (offset, vaddr, filesz from the first program header).
bool load_program(std::vector<std::uint8_t>& out, std::uint32_t& va) {
    std::ifstream f(elf_path(), std::ios::binary);
    if (!f) return false;
    const std::vector<std::uint8_t> file((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    if (file.size() < 0x80 || std::memcmp(file.data(), "\x7F" "ELF", 4) != 0) return false;
    auto u32 = [&](std::size_t o) { return rd32(file, 0, static_cast<std::uint32_t>(o)); };
    const std::uint32_t ph = u32(0x1C);
    const std::uint32_t off = u32(ph + 4), vaddr = u32(ph + 8), filesz = u32(ph + 16);
    if (off + static_cast<std::uint64_t>(filesz) > file.size()) return false;
    out.assign(file.begin() + off, file.begin() + off + filesz);
    va = vaddr;
    return true;
}

// The table's row as text: line strings in the game's encoding, a 2-byte code >= 0x80 shown as {HHLL}.
std::vector<std::string> row_lines(const std::vector<std::uint8_t>& img, std::uint32_t base, std::uint32_t row) {
    const std::uint32_t lines = rd32(img, base, pc_text::kTableVa + 12 * row);
    const std::uint32_t count = rd32(img, base, pc_text::kTableVa + 12 * row + 4);
    std::vector<std::string> out;
    for (std::uint32_t i = 0; i < count; ++i) {
        std::uint32_t p = rd32(img, base, lines + 4 * i) - base;
        std::string s;
        while (img[p]) {
            const unsigned c = img[p];
            if (c >= 0x80 && img[p + 1] != 0) {
                char b[8];
                std::snprintf(b, sizeof b, "{%02X%02X}", c, img[p + 1]);
                s += b;
                p += 2;
            } else {
                s += static_cast<char>(c);
                ++p;
            }
        }
        out.push_back(s);
    }
    return out;
}

} // namespace

TEST_CASE("pc_text: the table is well formed (fits in place, plain ASCII, no console wording)") {
    std::vector<std::pair<std::uint32_t, std::uint32_t>> ranges;  // [va, end) of every rewritten string
    for (const pc_text::StringPatch& s : pc_text::string_patches()) {
        CAPTURE(s.va);
        CHECK(s.new_text.size() <= s.old_text.size());
        CHECK(!s.new_text.empty());
        for (char c : s.new_text) CHECK(pc_text::safe_char(c));
        const std::string t = lower(std::string(s.new_text));
        for (const char* banned : {"memory card", "ps2", "playstation", "8mb", "slot", "console", "controller", "format"})
            CHECK(t.find(banned) == std::string::npos);
        ranges.push_back({s.va, s.va + static_cast<std::uint32_t>(s.old_text.size()) + 1});
    }
    std::sort(ranges.begin(), ranges.end());
    for (std::size_t i = 1; i < ranges.size(); ++i) CHECK(ranges[i - 1].second <= ranges[i].first);
    std::vector<std::uint32_t> words;
    for (const pc_text::WordPatch& w : pc_text::word_patches()) {
        CAPTURE(w.va);
        CHECK(w.va % 4 == 0);
        CHECK(w.old_value != w.new_value);
        for (const auto& r : ranges) CHECK((w.va + 4 <= r.first || w.va >= r.second));
        words.push_back(w.va);
    }
    std::sort(words.begin(), words.end());
    CHECK(std::adjacent_find(words.begin(), words.end()) == words.end());
}

TEST_CASE("pc_text: applies to the original bytes, only inside its entries, once") {
    std::vector<std::uint8_t> img = synthetic_original();
    const std::vector<std::uint8_t> before = img;
    const pc_text::Result r = pc_text::apply(img, kBase);
    REQUIRE(r.status == pc_text::Status::Applied);
    CHECK(r.entries == pc_text::string_patches().size() + pc_text::word_patches().size());

    // Exactly the expected image: new text + NULs over each old string, new words.
    std::vector<std::uint8_t> want = before;
    for (const pc_text::StringPatch& s : pc_text::string_patches()) {
        std::memset(want.data() + (s.va - kBase), 0, s.old_text.size() + 1);
        std::memcpy(want.data() + (s.va - kBase), s.new_text.data(), s.new_text.size());
    }
    for (const pc_text::WordPatch& w : pc_text::word_patches()) wr32(want, kBase, w.va, w.new_value);
    CHECK(img == want);

    const pc_text::Result again = pc_text::apply(img, kBase);
    CHECK(again.status == pc_text::Status::AlreadyApplied);
    CHECK(img == want);
}

TEST_CASE("pc_text: refuses an image that does not match, writing nothing") {
    SUBCASE("one string byte differs") {
        std::vector<std::uint8_t> img = synthetic_original();
        img[pc_text::string_patches()[3].va - kBase] ^= 0x20;
        const std::vector<std::uint8_t> before = img;
        const pc_text::Result r = pc_text::apply(img, kBase);
        CHECK(r.status == pc_text::Status::Mismatch);
        CHECK(r.detail.find("0x6B3460") != std::string::npos);
        CHECK(img == before);
    }
    SUBCASE("a string's terminator is not where the table says") {
        std::vector<std::uint8_t> img = synthetic_original();
        const pc_text::StringPatch& s = pc_text::string_patches()[0];
        img[s.va - kBase + s.old_text.size()] = '!';
        const std::vector<std::uint8_t> before = img;
        CHECK(pc_text::apply(img, kBase).status == pc_text::Status::Mismatch);
        CHECK(img == before);
    }
    SUBCASE("a line count differs") {
        std::vector<std::uint8_t> img = synthetic_original();
        const pc_text::WordPatch& w = pc_text::word_patches().back();
        wr32(img, kBase, w.va, w.old_value + 1);
        const std::vector<std::uint8_t> before = img;
        const pc_text::Result r = pc_text::apply(img, kBase);
        CHECK(r.status == pc_text::Status::Mismatch);
        CHECK(r.detail.find(w.what) != std::string::npos);
        CHECK(img == before);
    }
    SUBCASE("partly patched") {
        std::vector<std::uint8_t> img = synthetic_original();
        const pc_text::WordPatch& w = pc_text::word_patches()[0];
        wr32(img, kBase, w.va, w.new_value);
        const std::vector<std::uint8_t> before = img;
        const pc_text::Result r = pc_text::apply(img, kBase);
        CHECK(r.status == pc_text::Status::Mismatch);
        CHECK(r.detail.find("partly") != std::string::npos);
        CHECK(img == before);
    }
    SUBCASE("the image does not cover the table") {
        std::vector<std::uint8_t> img = synthetic_original();
        img.resize(0xE00);  // ends at 0x6B3E00: the strings fit, the table's words do not
        const std::vector<std::uint8_t> before = img;
        CHECK(pc_text::apply(img, kBase).status == pc_text::Status::Mismatch);
        CHECK(img == before);
    }
}

TEST_CASE("pc_text: the user's ELF, every memory-card message before -> after") {
    std::vector<std::uint8_t> img;
    std::uint32_t va = 0;
    if (!load_program(img, va)) {
        MESSAGE("skipped: no ELF at " << elf_path() << " (P3FES_ELF)");
        return;
    }
    REQUIRE(va == 0x100000u);
    REQUIRE(rd32(img, va, 0x7CDAC8u) == pc_text::kTableVa);
    REQUIRE(rd32(img, va, 0x7CDACCu) == pc_text::kTableRows);

    // Before (the disc's text), rows 0..21 and 28; rows 22..27 are the Japanese append-disc prompts of
    // H_FileSetup_UpdateTstDvdChkDrawTask, not memory-card messages, and stay as they are.
    using L = std::vector<std::string>;
    const std::string bl = "{8080}";
    const std::vector<L> old_rows = {
        {"No memory card (for PS2)", "inserted in MEMORY CARD slot 1.", bl},
        {"The memory card (for PS2) in", "MEMORY CARD slot 1 is", "unformatted. Format?", bl},
        {"Formatting memory card (for PS2)", "in MEMORY CARD slot 1.", "Do not remove memory card", "(for PS2) or controller, or reset/",
         "switch off console.", bl, bl},
        {"Format failed."},
        {"Save file already exists.", "Previous data will be overwritten.", "Overwrite the file?", bl},
        {"Create a new file on", "memory card (for PS2) in", "MEMORY CARD slot 1?"},
        {"Insufficient free space on", "memory card (for PS2) in", "MEMORY CARD slot 1.", "At least 78KB of free space",
         "is needed to save data."},
        {"Saving data on memory card", "(for PS2) in MEMORY CARD", "slot 1...", bl, "Do not remove memory card",
         "(for PS2) or controller, or", "reset/switch off console.", bl},
        {"Save failed."},
        {"Save successful."},
        {"Exit?"},
        {"Load this file?"},
        {"Loading data..."},
        {"Load successful."},
        {"Load failed."},
        {"Checking memory card (8MB)", "(for PlayStation{82CE}{8092})..."},
        {"No memory card (for PS2)", "inserted in MEMORY CARD slot 1.", "In order to save, you need", "a memory card (for PS2) with",
         "at least 78KB of free space.", "Start the game anyway?"},
        {"Save new cycle data?"},
        {"Some data from the previous cycle", "will be carried over to the new game", "if you load this file and restart.", bl,
         "Be aware that you will lose your", "old data if you overwrite it with", "the new cycle data."},
        {"Return to the title screen without", "saving the new cycle data?", bl},
        {"Data is corrupt and cannot be loaded."},
        {"Insufficient free space on memory card", "(for PS2) in MEMORY CARD slot 1.", "At least 78KB of free space is needed",
         "to save data.", bl, "Start the game anyway?", bl},
    };
    const std::vector<L> new_rows = {
        {"No save data was found.", bl},
        {"The save data is not set up.", "Set it up now?", bl},
        {"Setting up save data...", bl, "Do not close the game.", bl},
        {"Setup failed."},
        old_rows[4],
        {"Create new save data?"},
        {"There is not enough free space", "to save data."},
        {"Saving data...", bl, "Do not close the game.", bl},
        old_rows[8], old_rows[9], old_rows[10], old_rows[11], old_rows[12], old_rows[13], old_rows[14],
        {"Checking save data..."},
        {"No save data was found.", "Your progress cannot be saved.", "Start the game anyway?"},
        old_rows[17], old_rows[18], old_rows[19], old_rows[20],
        {"There is not enough free space", "to save data.", bl, "Start the game anyway?", bl},
    };
    std::vector<L> untouched;  // rows 22..28 must not change
    for (std::uint32_t row = 22; row < pc_text::kTableRows; ++row) untouched.push_back(row_lines(img, va, row));
    for (std::uint32_t row = 0; row < old_rows.size(); ++row) {
        CAPTURE(row);
        CHECK(row_lines(img, va, row) == old_rows[row]);
    }
    CHECK(row_lines(img, va, 28) == L{"Data could not be saved correctly."});

    const std::vector<std::uint8_t> before = img;
    const pc_text::Result r = pc_text::apply(img, va);
    REQUIRE_MESSAGE(r.status == pc_text::Status::Applied, r.detail);
    for (std::uint32_t row = 0; row < new_rows.size(); ++row) {
        CAPTURE(row);
        CHECK(row_lines(img, va, row) == new_rows[row]);
        for (const std::string& line : row_lines(img, va, row)) {
            const std::string t = lower(line);
            CHECK(t.find("memory card") == std::string::npos);
            CHECK(t.find("ps2") == std::string::npos);
            CHECK(t.find("playstation") == std::string::npos);
            CHECK(t.find("slot 1") == std::string::npos);
        }
    }
    for (std::uint32_t row = 22; row < pc_text::kTableRows; ++row) CHECK(row_lines(img, va, row) == untouched[row - 22]);

    // Every changed byte lies inside a patch entry.
    std::size_t changed = 0;
    for (std::size_t i = 0; i < img.size(); ++i) {
        if (img[i] == before[i]) continue;
        ++changed;
        const std::uint32_t a = va + static_cast<std::uint32_t>(i);
        bool inside = false;
        for (const pc_text::StringPatch& s : pc_text::string_patches())
            inside |= a >= s.va && a <= s.va + s.old_text.size();
        for (const pc_text::WordPatch& w : pc_text::word_patches()) inside |= a >= w.va && a < w.va + 4;
        CAPTURE(a);
        CHECK(inside);
    }
    CHECK(changed > 0);
    CHECK(pc_text::apply(img, va).status == pc_text::Status::AlreadyApplied);
}
