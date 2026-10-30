// VU1 workload accounting and resident-program identification (vu1_profile.h).
#include "p3fes/vu1/vu1_profile.h"

#include "p3fes/vu1/vu1_interp.h"

#include <algorithm>
#include <chrono>
#include <cstring>
#include <filesystem>
#include <fstream>

namespace p3fes::vu1 {

u64 vu1_now_ns() noexcept {
    return static_cast<u64>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch())
            .count());
}

void ProgramIndex::add(std::string name, std::vector<u8> image) {
    image.resize(std::min<std::size_t>(image.size() & ~std::size_t{7}, kMicroBytes));
    Entry e;
    e.name = std::move(name);
    e.image = std::move(image);
    if (e.image.size() >= 8) std::memcpy(&e.head, e.image.data(), 8);
    entries_.push_back(std::move(e));
    cached_generation_ = 0;
}

int ProgramIndex::identify(const MicroMemory& micro) {
    if (cached_generation_ == micro.generation()) return cached_;
    ++identifications_;
    const u8* m = micro.bytes().data();
    u64 head;
    std::memcpy(&head, m, 8);
    int best = -1;
    std::size_t best_len = 0;
    for (std::size_t k = 0; k < entries_.size(); ++k) {
        const Entry& e = entries_[k];
        if (e.image.size() < 8 || e.head != head || e.image.size() <= best_len) continue;
        if (std::memcmp(m, e.image.data(), e.image.size()) == 0) {
            best = static_cast<int>(k);
            best_len = e.image.size();
        }
    }
    cached_generation_ = micro.generation();
    cached_ = best;
    return best;
}

std::size_t load_program_dumps(ProgramIndex& index, const std::string& dir) {
    namespace fs = std::filesystem;
    std::error_code ec;
    std::vector<fs::path> files;
    for (const auto& de : fs::directory_iterator(dir, ec))
        if (de.is_regular_file() && de.path().extension() == ".bin") files.push_back(de.path());
    std::sort(files.begin(), files.end());
    std::size_t n = 0;
    for (const fs::path& p : files) {
        std::ifstream f(p, std::ios::binary);
        std::vector<u8> data((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
        if (data.size() < 8) continue;
        index.add(p.stem().string(), std::move(data));
        ++n;
    }
    return n;
}

namespace {
constexpr char kMagic[8] = {'P', '3', 'V', 'U', '1', 'I', 'N', '1'};
}

bool save_run_input(const std::string& path, const VU1State& s, u32 start_pc, const std::string& program) {
    std::ofstream f(path, std::ios::binary);
    if (!f) return false;
    const auto put = [&](const void* p, std::size_t n) { f.write(static_cast<const char*>(p), static_cast<std::streamsize>(n)); };
    put(kMagic, 8);
    const u32 name_len = static_cast<u32>(program.size());
    put(&name_len, 4);
    put(program.data(), name_len);
    put(&start_pc, 4);
    put(s.vf, sizeof s.vf);
    put(s.vi, sizeof s.vi);
    put(s.acc, sizeof s.acc);
    const u32 scalars[11] = {s.q, s.p, s.i, s.r, s.mac, s.status, s.clip, s.top, s.itop, s.tpc, s.pc};
    put(scalars, sizeof scalars);
    put(s.micro.bytes().data(), kMicroBytes);
    put(s.data, kDataBytes);
    return static_cast<bool>(f);
}

bool load_run_input(const std::string& path, VU1State& s, u32& start_pc, std::string& program) {
    std::ifstream f(path, std::ios::binary);
    if (!f) return false;
    const auto get = [&](void* p, std::size_t n) { return static_cast<bool>(f.read(static_cast<char*>(p), static_cast<std::streamsize>(n))); };
    char magic[8];
    u32 name_len = 0;
    if (!get(magic, 8) || std::memcmp(magic, kMagic, 8) != 0 || !get(&name_len, 4) || name_len > 256) return false;
    program.resize(name_len);
    if (!get(program.data(), name_len) || !get(&start_pc, 4)) return false;
    u32 scalars[11];
    if (!get(s.vf, sizeof s.vf) || !get(s.vi, sizeof s.vi) || !get(s.acc, sizeof s.acc) || !get(scalars, sizeof scalars))
        return false;
    s.q = scalars[0]; s.p = scalars[1]; s.i = scalars[2]; s.r = scalars[3]; s.mac = scalars[4]; s.status = scalars[5];
    s.clip = scalars[6]; s.top = scalars[7]; s.itop = scalars[8]; s.tpc = scalars[9]; s.pc = scalars[10];
    std::vector<u8> micro(kMicroBytes);
    if (!get(micro.data(), kMicroBytes) || !get(s.data, kDataBytes)) return false;
    s.micro.write(0, micro);
    return true;
}

void VU1Profile::reset_counters() {
    runs.clear();
    rebuilds = rebuild_ns = q_kind_calls = q_kind_ns = q_delay_calls = q_delay_ns = micro_writes = 0;
}

void VU1Profile::write(std::FILE* f, const char* label, double wall_seconds, u64 vblanks) const {
    std::vector<std::pair<std::pair<int, u32>, VU1RunCounters>> rows(runs.begin(), runs.end());
    std::sort(rows.begin(), rows.end(), [](const auto& a, const auto& b) { return a.second.ns > b.second.ns; });
    VU1RunCounters tot;
    for (const auto& [k, c] : rows) {
        tot.runs += c.runs;
        tot.pairs += c.pairs;
        tot.kicks += c.kicks;
        tot.kick_qwords += c.kick_qwords;
        tot.ns += c.ns;
        tot.kick_ns += c.kick_ns;
        tot.cold += c.cold;
    }
    std::fprintf(f, "## %s: wall %.3f s, vblanks %llu\n", label, wall_seconds, static_cast<unsigned long long>(vblanks));
    std::fprintf(f, "# program start_pc runs pairs kicks kick_qwords vu1_ms ns_per_pair cold_runs gs_kick_ms\n");
    for (const auto& [k, c] : rows) {
        const std::string name = k.first >= 0 ? programs.name(k.first) : std::string("unknown");
        std::fprintf(f, "%s 0x%04x %llu %llu %llu %llu %.3f %.2f %llu %.3f\n", name.c_str(), k.second,
                     static_cast<unsigned long long>(c.runs), static_cast<unsigned long long>(c.pairs),
                     static_cast<unsigned long long>(c.kicks), static_cast<unsigned long long>(c.kick_qwords),
                     static_cast<double>(c.ns) / 1e6, c.pairs ? static_cast<double>(c.ns) / static_cast<double>(c.pairs) : 0.0,
                     static_cast<unsigned long long>(c.cold), static_cast<double>(c.kick_ns) / 1e6);
    }
    std::fprintf(f, "TOTAL runs %llu pairs %llu kicks %llu kick_qwords %llu vu1_ms %.3f (%.1f%% of wall) cold_runs %llu gs_kick_ms %.3f (%.1f%% of wall)\n",
                 static_cast<unsigned long long>(tot.runs), static_cast<unsigned long long>(tot.pairs),
                 static_cast<unsigned long long>(tot.kicks), static_cast<unsigned long long>(tot.kick_qwords),
                 static_cast<double>(tot.ns) / 1e6,
                 wall_seconds > 0 ? 100.0 * static_cast<double>(tot.ns) / 1e9 / wall_seconds : 0.0,
                 static_cast<unsigned long long>(tot.cold), static_cast<double>(tot.kick_ns) / 1e6,
                 wall_seconds > 0 ? 100.0 * static_cast<double>(tot.kick_ns) / 1e9 / wall_seconds : 0.0);
    std::fprintf(f, "CACHES micro_writes %llu rebuilds %llu rebuild_ms %.3f q_kind %llu q_kind_ms %.3f q_delay %llu q_delay_ms %.3f\n\n",
                 static_cast<unsigned long long>(micro_writes), static_cast<unsigned long long>(rebuilds),
                 static_cast<double>(rebuild_ns) / 1e6, static_cast<unsigned long long>(q_kind_calls),
                 static_cast<double>(q_kind_ns) / 1e6, static_cast<unsigned long long>(q_delay_calls),
                 static_cast<double>(q_delay_ns) / 1e6);
}

} // namespace p3fes::vu1
