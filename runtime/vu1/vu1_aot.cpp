// Resident-program check for the ahead-of-time compiled VU1 programs (vu1_aot.h).
#include "p3fes/vu1/vu1_aot.h"

#include <algorithm>
#include <cstdlib>
#include <map>
#include <cstring>

#if defined(_MSC_VER)
#include <intrin.h>
#endif

namespace p3fes::vu1 {

namespace {
bool detect_sse41() noexcept {
#if defined(_MSC_VER) && (defined(_M_X64) || defined(_M_IX86))
    int r[4];
    __cpuid(r, 1);
    if (!(r[2] & (1 << 19))) return false; // SSE4.1
#if defined(P3FES_VU1_AOT_AVX2)
    // the compiled programs are built /arch:AVX2: AVX2, and the OS saves YMM state
    if (!(r[2] & (1 << 27)) || !(r[2] & (1 << 28)) || (_xgetbv(0) & 6u) != 6u) return false;
    __cpuidex(r, 7, 0);
    if (!(r[1] & (1 << 5))) return false;
#endif
    return true;
#elif defined(__GNUC__) || defined(__clang__)
#if defined(P3FES_VU1_AOT_AVX2)
    if (!__builtin_cpu_supports("avx2")) return false;
#endif
    return __builtin_cpu_supports("sse4.1");
#else
    return false;
#endif
}
const bool g_cpu_sse41 = detect_sse41();
} // namespace

bool aot_cpu_ok() noexcept { return g_cpu_sse41; }
u64 detail::g_aot_slow_ops = 0;
u32 detail::g_aot_cur_va = 0;
bool detail::g_aot_slow_trace = [] {
    const char* e = std::getenv("P3FES_VU1_SLOW_SITES");
    return e && e[0] == '1';
}();

namespace {
std::map<u64, u64>& slow_sites() {
    static std::map<u64, u64> m;
    return m;
}
} // namespace

void detail::aot_note_slow(u32 code_va, u32 pc) noexcept { ++slow_sites()[(static_cast<u64>(code_va) << 32) | pc]; }

std::vector<AotSlowSite> aot_slow_sites(std::size_t max) {
    std::vector<AotSlowSite> v;
    for (const auto& [k, n] : slow_sites()) v.push_back({static_cast<u32>(k >> 32), static_cast<u32>(k), n});
    std::sort(v.begin(), v.end(), [](const AotSlowSite& a, const AotSlowSite& b) { return a.count > b.count; });
    if (v.size() > max) v.resize(max);
    return v;
}

namespace {

// Relative branch (B BAL IB*) as collect_jumps sees it: the I flag clear and a branch opcode.
bool relative_branch_target(u32 lo, u32 hi, u32 byte_pc, u32& target) {
    if (hi & kFlagI) return false;
    const u32 op = lo >> 25;
    if (op != 0x20 && op != 0x21 && (op < 0x28 || op > 0x2F)) return false;
    const LowerInsn l = decode_lower(lo, false);
    if (!is_branch(l.op) || is_jump_register(l.op)) return false;
    target = branch_target(l, byte_pc) >> 3;
    return true;
}

// The pairs outside the image that the precomputed analysis read are the ones it assumed.
bool outside_reads_hold(const AotProgram& p, const MicroMemory& micro) {
    for (u32 k = 0; k < p.outside_count; ++k) {
        const AotOutsideRead& r = p.outside[k];
        if (micro.lower_word(r.pair * 8u) != r.lo || micro.upper_word(r.pair * 8u) != r.hi) return false;
    }
    return true;
}

// Relative branches outside the image that target pairs whose predecessors the Q analysis enumerated (2048-bit set);
// returns whether there is any.
bool outside_jumps_into(const AotProgram& p, const MicroMemory& micro, u64 (&targets)[kMicroPairs / 64]) {
    bool any = false;
    for (auto& w : targets) w = 0;
    for (u32 k = p.pairs; k < kMicroPairs; ++k) {
        u32 target = 0;
        if (relative_branch_target(micro.lower_word(k * 8u), micro.upper_word(k * 8u), k * 8u, target) &&
            (p.expanded[target / 64] >> (target % 64)) & 1u) {
            targets[target / 64] |= 1ull << (target % 64);
            any = true;
        }
    }
    return any;
}

// Hash of the bytes outside an image (n is a multiple of 8): four independent multiply chains over 64-bit words, so
// the ~16 KiB of a pipeline switch hash in well under a microsecond.
u64 fnv1a(const u8* b, std::size_t n) {
    u64 h[4] = {1469598103934665603ull, 0x9E3779B97F4A7C15ull, 0xC2B2AE3D27D4EB4Full, 0x165667B19E3779F9ull};
    std::size_t k = 0;
    for (; k + 32 <= n; k += 32)
        for (int l = 0; l < 4; ++l) {
            u64 w;
            std::memcpy(&w, b + k + l * 8, 8);
            h[l] = (h[l] ^ w) * 1099511628211ull;
        }
    for (; k + 8 <= n; k += 8) {
        u64 w;
        std::memcpy(&w, b + k, 8);
        h[0] = (h[0] ^ w) * 1099511628211ull;
    }
    return (h[0] ^ (h[1] >> 1) ^ (h[2] << 1) ^ (h[3] >> 3)) * 0x9E3779B97F4A7C15ull;
}

} // namespace

const AotProgram* AotIndex::resident(const MicroMemory& micro, AotQVerifier verify, void* ctx) {
    if (generation_ == micro.generation()) return cached_;
    generation_ = micro.generation();
    cached_ = nullptr;
    ++checks_;
    const AotProgram* table = aot_programs();
    const u8* m = micro.bytes().data();
    const AotProgram* best = nullptr;
    for (std::size_t k = 0; k < aot_program_count(); ++k) {
        const AotProgram& p = table[k];
        if (best && p.pairs <= best->pairs) continue;
        if (std::memcmp(m, p.image, 8) != 0) continue;
        if (std::memcmp(m, p.image, p.pairs * 8u) == 0) best = &p;
    }
    if (best && !outside_reads_hold(*best, micro)) {
        ++rejected_;
        best = nullptr;
    }
    if (best) {
        // The verdict depends only on the bytes outside the image (the image is fixed), so it is cached by them and
        // looked up first: RenderWare re-uploads the same few programs over the same leftovers on every pipeline
        // switch, and the scan below (a decode of every pair outside the image) costs more than the compare.
        const u8* out = m + best->pairs * 8u;
        const std::size_t n = kMicroBytes - best->pairs * 8u;
        const u64 h = fnv1a(out, n);
        const Verdict* found = nullptr;
        for (const Verdict& v : verdicts_)
            if (v.program == best && v.hash == h && v.outside.size() == n && std::memcmp(v.outside.data(), out, n) == 0) {
                found = &v;
                break;
            }
        bool ok = true;
        if (found) {
            ++verify_hits_;
            ok = found->ok;
        } else {
            u64 targets[kMicroPairs / 64];
            if (outside_jumps_into(*best, micro, targets)) {
                ++verified_;
                ok = verify && verify(ctx, *best, targets);
            }
            if (verdicts_.size() >= 256) verdicts_.clear();
            verdicts_.push_back(Verdict{best, h, std::vector<u8>(out, out + n), ok});
        }
        if (!ok) {
            ++rejected_;
            best = nullptr;
        }
    }
    cached_ = best;
    return cached_;
}

} // namespace p3fes::vu1
