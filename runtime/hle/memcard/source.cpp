// Card sources and the copy-on-write backing (source.h).
#include "p3fes/hle/memcard/source.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <system_error>
#include <vector>

namespace p3fes::hle::memcard {
namespace fs = std::filesystem;
namespace {

std::string trim(std::string s) {
    auto not_space = [](unsigned char c) { return !std::isspace(c); };
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), not_space));
    s.erase(std::find_if(s.rbegin(), s.rend(), not_space).base(), s.end());
    return s;
}

std::string lower(std::string s) {
    for (char& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return s;
}

// Reads an image of exactly kImageSize bytes; false + error otherwise.
bool read_image(const fs::path& p, std::vector<u8>& out, std::string& error) {
    std::error_code ec;
    if (!fs::is_regular_file(p, ec)) {
        error = p.string() + ": not a regular file (PCSX2 folder memory cards are not supported)";
        return false;
    }
    const auto size = fs::file_size(p, ec);
    if (ec || size != kImageSize) {
        error = p.string() + ": " + std::to_string(ec ? 0 : size) + " bytes; only the raw 8 MiB card with ECC (" +
                std::to_string(kImageSize) + " bytes) is supported";
        return false;
    }
    std::ifstream f(p, std::ios::binary);  // read-only
    if (!f) {
        error = p.string() + ": cannot open for reading";
        return false;
    }
    out.resize(kImageSize);
    f.read(reinterpret_cast<char*>(out.data()), static_cast<std::streamsize>(out.size()));
    if (f.gcount() != static_cast<std::streamsize>(out.size())) {
        error = p.string() + ": short read";
        return false;
    }
    return true;
}

bool is_inside(const fs::path& file, const fs::path& dir) {
    std::error_code ec;
    std::string f = lower(fs::weakly_canonical(fs::absolute(file, ec), ec).generic_string());
    std::string d = lower(fs::weakly_canonical(fs::absolute(dir, ec), ec).generic_string());
    if (!d.empty() && d.back() != '/') d.push_back('/');
    return f.size() > d.size() && f.compare(0, d.size(), d) == 0;
}

// Writes pages into `path`. The first store creates the file as a full copy of the card (so the copy is a
// complete image even if only one page changed); later stores rewrite only the dirty pages.
class FileBacking final : public CardBacking {
public:
    FileBacking(fs::path path, bool exists) : path_(std::move(path)), exists_(exists) {}
    bool store(const Card& card, std::span<const u32> dirty, std::string& error) override {
        std::error_code ec;
        if (!exists_) {
            fs::create_directories(path_.parent_path(), ec);
            std::ofstream f(path_, std::ios::binary | std::ios::trunc);
            f.write(reinterpret_cast<const char*>(card.image().data()), static_cast<std::streamsize>(card.image().size()));
            if (!f) {
                error = path_.string() + ": cannot write the copy-on-write image";
                return false;
            }
            exists_ = true;
            return true;
        }
        std::fstream f(path_, std::ios::binary | std::ios::in | std::ios::out);
        if (!f) {
            error = path_.string() + ": cannot open for update";
            return false;
        }
        for (u32 page : dirty) {
            const auto raw = card.raw_page(page);
            f.seekp(static_cast<std::streamoff>(page) * kRawPageSize);
            f.write(reinterpret_cast<const char*>(raw.data()), static_cast<std::streamsize>(raw.size()));
        }
        f.flush();
        if (!f) {
            error = path_.string() + ": write failed";
            return false;
        }
        return true;
    }
    std::string describe() const override { return path_.string(); }

private:
    fs::path path_;
    bool exists_;
};

}  // namespace

std::optional<fs::path> pcsx2_slot1_card(const fs::path& ini, std::string* why) {
    auto fail = [&](std::string w) -> std::optional<fs::path> {
        if (why) *why = std::move(w);
        return std::nullopt;
    };
    std::ifstream f(ini);
    if (!f) return fail(ini.string() + ": cannot read PCSX2.ini");
    std::string section, line;
    std::string folder = "memcards", filename = "Mcd001.ps2";
    bool enabled = true;
    while (std::getline(f, line)) {
        line = trim(line);
        if (line.empty() || line[0] == ';' || line[0] == '#') continue;
        if (line.front() == '[' && line.back() == ']') {
            section = lower(line.substr(1, line.size() - 2));
            continue;
        }
        const auto eq = line.find('=');
        if (eq == std::string::npos) continue;
        const std::string key = lower(trim(line.substr(0, eq)));
        const std::string val = trim(line.substr(eq + 1));
        if (section == "folders" && key == "memorycards") folder = val;
        if (section == "memorycards" && key == "slot1_enable") enabled = lower(val) == "true";
        if (section == "memorycards" && key == "slot1_filename") filename = val;
    }
    if (!enabled) return fail(ini.string() + ": [MemoryCards] Slot1_Enable is false");
    // A portable PCSX2 resolves relative folders against its own directory (the parent of inis/).
    fs::path dir = folder;
    if (dir.is_relative()) dir = ini.parent_path().parent_path() / dir;
    fs::path card = dir / filename;
    std::error_code ec;
    if (!fs::exists(card, ec)) return fail(card.string() + ": PCSX2's slot-1 card does not exist");
    return card;
}

OpenResult open_in_place(const fs::path& file) {
    OpenResult r;
    std::vector<u8> img;
    if (!read_image(file, img, r.error)) return r;
    r.card = Card::from_image(std::move(img), file.filename().string());
    r.card->set_backing(std::make_unique<FileBacking>(file, true));
    r.ok = true;
    r.description = file.string() + " (ours, written in place)";
    return r;
}

OpenResult open_or_create(const fs::path& file, const DateTime& format_time) {
    std::error_code ec;
    if (fs::exists(file, ec)) {
        OpenResult r = open_in_place(file);
        if (r.ok) r.description = file.string() + " (the port's saves, written in place)";
        return r;
    }
    OpenResult r;
    fs::create_directories(file.parent_path(), ec);
    auto card = Card::blank(file.filename().string());
    format(*card, format_time);
    {
        std::ofstream f(file, std::ios::binary | std::ios::trunc);
        f.write(reinterpret_cast<const char*>(card->image().data()), static_cast<std::streamsize>(card->image().size()));
        if (!f) {
            r.error = file.string() + ": cannot create the card image";
            return r;
        }
    }
    r = open_in_place(file);
    if (r.ok) r.description = file.string() + " (created now, formatted; the port's saves, written in place)";
    return r;
}

OpenResult open_copy_on_write(const fs::path& source, const fs::path& cow_dir) {
    const fs::path copy = cow_dir / source.filename();
    std::error_code ec;
    if (fs::exists(copy, ec)) {
        OpenResult r = open_in_place(copy);
        if (r.ok) r.description = copy.string() + " (copy-on-write image of " + source.string() + " from an earlier run)";
        return r;
    }
    OpenResult r;
    std::vector<u8> img;
    if (!read_image(source, img, r.error)) return r;
    r.card = Card::from_image(std::move(img), source.filename().string());
    r.card->set_backing(std::make_unique<FileBacking>(copy, false));
    r.ok = true;
    r.description = source.string() + " (read-only; changes go to " + copy.string() + ")";
    return r;
}

OpenResult open_memcard(std::string_view spec_in, const SourceOptions& opt) {
    const std::string spec(spec_in);
    const std::string key = lower(spec);
    OpenResult r;
    if (key == "none") {
        r.ok = true;
        r.description = "no memory card in slot 1";
        return r;
    }
    if (key == "new") {
        r.card = Card::blank("new");
        format(*r.card, opt.format_time);
        r.ok = true;
        r.description = "freshly formatted card (in memory, not saved)";
        return r;
    }
    if (key == "blank") {
        r.card = Card::blank("blank");
        r.ok = true;
        r.description = "erased, unformatted card (in memory, not saved)";
        return r;
    }
    if (key.empty() || key == "pcsx2") {
        std::string why;
        const auto p = pcsx2_slot1_card(opt.pcsx2_ini, &why);
        if (!p) {
            r.error = why;
            return r;
        }
        return open_copy_on_write(*p, opt.cow_dir);
    }
    const fs::path p(spec);
    if (is_inside(p, opt.cow_dir)) return open_in_place(p);
    return open_copy_on_write(p, opt.cow_dir);
}

}  // namespace p3fes::hle::memcard
