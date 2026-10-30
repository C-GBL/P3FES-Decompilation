// Test stand-ins (stand_ins.h): the hooks the test library's stubs and listed entry points call, the call log, the
// guest printf formatter, the guest heap and the H_Cdvd file layer.
#include "stand_ins.h"

#include "p3fes/game/fs3.h"
#include "p3fes/game/hcdvd.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <process.h>
#include <stdexcept>

namespace p3fes::game_test {

// --- the hooks (declared by the test library's gen_prelude.h, tests/rt/emit_units.cmake) -------------------------
bool g_stand_ins_active = false;

namespace {
StandIns* g_current = nullptr;

u32 lw(const EEContext& ctx, u32 va) { return ctx.memory->read<u32>(va); }
void sw(EEContext& ctx, u32 va, u32 v) { ctx.memory->write<u32>(va, v); }
s16 lh(const EEContext& ctx, u32 va) { return ctx.memory->read<s16>(va); }
void sh(EEContext& ctx, u32 va, s16 v) { ctx.memory->write<s16>(va, v); }
u64 sx32(u32 v) { return static_cast<u64>(static_cast<s64>(static_cast<s32>(v))); }

std::string guest_string(const EEContext& ctx, u32 va, std::size_t max = 4096) {
    std::string s;
    for (std::size_t i = 0; i < max; ++i) {
        const char c = static_cast<char>(ctx.memory->read<u8>(va + static_cast<u32>(i)));
        if (c == 0) break;
        s.push_back(c);
    }
    return s;
}
}  // namespace

// P3FES_STANDIN_LOG=<file>: every address a stand-in served in this process, one hex address per line, written at
// exit to <file>.<pid> (ctest runs many processes at once). These are the functions some test meets as a stand-in,
// the run-time "absent" recorders included; tools/ours/phase5/standins.py reports them in the packet of the slice that
// takes one (since the hooked forwarders, 2026-10-29, they are no longer held out of packets).
namespace {
struct ServedLog {
    const char* path = std::getenv("P3FES_STANDIN_LOG");
    std::vector<u32> seen;
    ~ServedLog() {
        if (path == nullptr || *path == 0) return;
        std::sort(seen.begin(), seen.end());
        seen.erase(std::unique(seen.begin(), seen.end()), seen.end());
        const std::string file = std::string(path) + "." + std::to_string(_getpid());
        if (std::FILE* f = std::fopen(file.c_str(), "w")) {
            for (u32 va : seen) std::fprintf(f, "0x%X\n", va);
            std::fclose(f);
        }
    }
};
ServedLog g_served;

bool serve_logged(EEContext& ctx, u32 va) {
    if (g_current == nullptr || !g_current->serve(ctx, va)) return false;
    if (g_served.path != nullptr) g_served.seen.push_back(va);
    return true;
}
}  // namespace

// The hooked entries: generated bodies listed in _stand_in_hooks and, since 2026-10-29, every generated forwarder of a
// replaced function (game/forwarders.cmake). A pair runner's EntryBypass lets the function under test past its own
// stand-in (stand_in_entry.h).
bool stand_in_hook(EEContext& ctx, std::uint32_t va) {
    if (consume_entry_bypass(va)) return false;
    return serve_logged(ctx, va);
}

void stand_in_or_missing(EEContext& ctx, std::uint32_t va) {
    if (serve_logged(ctx, va)) return;
    rt::missing_function(va);
}

StandInsScope::StandInsScope(StandIns& s) : prev_(g_current) {
    g_current = &s;
    g_stand_ins_active = true;
}
StandInsScope::~StandInsScope() {
    g_current = prev_;
    g_stand_ins_active = prev_ != nullptr;
}

// --- StandIns ------------------------------------------------------------------------------------------------------
void StandIns::install(u32 va, std::string name, StandInFn fn, u64 cycles) {
    table_[va] = Entry{std::move(name), std::move(fn), cycles};
}

void StandIns::install_recorder(u32 va, std::string name, u64 v0, u64 cycles) {
    install(va, std::move(name), [v0](EEContext&, StandIns&, StandInCall& c) { c.v0 = v0; }, cycles);
}

void StandIns::install_stop(u32 va, std::string name) {
    install(va, std::move(name), [va](EEContext&, StandIns&, StandInCall&) { rt::missing_function(va); });
}

const std::string& StandIns::name_of(u32 va) const {
    static const std::string none;
    auto it = table_.find(va);
    return it == table_.end() ? none : it->second.name;
}

std::size_t StandIns::calls_to(u32 va) const {
    return static_cast<std::size_t>(std::count_if(log.begin(), log.end(), [va](const StandInCall& c) { return c.va == va; }));
}

bool StandIns::serve(EEContext& ctx, u32 va) {
    auto it = table_.find(va);
    if (it == table_.end()) return false;
    StandInCall c;
    c.va = va;
    c.ra = static_cast<u32>(ctx.gpr[GPR_RA].u64[0]);
    for (unsigned i = 0; i < 4; ++i) c.args[i] = ctx.gpr[GPR_A0 + i].u64[0];
    for (unsigned i = 0; i < 4; ++i) c.args[4 + i] = ctx.gpr[GPR_T0 + i].u64[0];
    rt::check_events(ctx);  // the callee's entry check point
    ctx.cycles += it->second.cycles;
    it->second.fn(ctx, *this, c);
    ctx.gpr[GPR_V0].u64[0] = c.v0;
    ++sequence;
    if (clobber_scratch) {
        static constexpr unsigned kScratch[] = {GPR_AT, GPR_V1, GPR_A0, GPR_A1, GPR_A2, GPR_A3, GPR_T0, GPR_T1, GPR_T2,
                                                GPR_T3, GPR_T4, GPR_T5, GPR_T6, GPR_T7, GPR_T8, GPR_T9};
        for (unsigned r : kScratch)
            ctx.gpr[r].u64[0] = sx32(0xC1B00000u | (static_cast<u32>(sequence & 0xFFFu) << 8) | r);
    }
    // a body that never leaves a loop of stand-in calls would grow the log until the host runs out of memory: stop
    // it with the callee named instead
    if (log.size() >= kMaxLog) throw std::runtime_error("stand-in log over " + std::to_string(kMaxLog) + " calls, last " + it->second.name);
    log.push_back(std::move(c));
    return true;
}

void expect_same_log(const StandIns& hand, const StandIns& recomp, const char* what) {
    INFO(std::string(what));
    CHECK(hand.log.size() == recomp.log.size());
    const std::size_t n = std::min(hand.log.size(), recomp.log.size());
    for (std::size_t i = 0; i < n; ++i) {
        const StandInCall& a = hand.log[i];
        const StandInCall& b = recomp.log[i];
        if (a == b) continue;
        unsigned arg = 8;
        for (unsigned k = 0; k < 8 && arg == 8; ++k)
            if (a.args[k] != b.args[k]) arg = k;
        INFO("stand-in call " << i << " (" << hand.name_of(a.va) << "): hand va " << hex64(a.va) << " ra " << hex64(a.ra)
                              << " v0 " << hex64(a.v0) << " text '" << a.text << "'; recomp va " << hex64(b.va) << " ra "
                              << hex64(b.ra) << " v0 " << hex64(b.v0) << " text '" << b.text << "'; first differing argument "
                              << arg << (arg < 8 ? " hand " + hex64(a.args[arg]) + " recomp " + hex64(b.args[arg]) : std::string()));
        CHECK(false);
        break;
    }
}

// --- printf ---------------------------------------------------------------------------------------------------------
std::string guest_format(EEContext& ctx, u32 fmt_va, unsigned first_vararg) {
    unsigned next = first_vararg;
    const u32 sp = static_cast<u32>(ctx.gpr[GPR_SP].u64[0]);
    auto arg64 = [&]() -> u64 {
        const unsigned k = next++;
        if (k < 4) return ctx.gpr[GPR_A0 + k].u64[0];
        if (k < 8) return ctx.gpr[GPR_T0 + (k - 4)].u64[0];
        return ctx.memory->read<u64>(sp + 8u * (k - 8));
    };
    const std::string fmt = guest_string(ctx, fmt_va, 1 << 16);
    std::string out;
    char buf[512];
    for (std::size_t i = 0; i < fmt.size(); ++i) {
        if (fmt[i] != '%') {
            out.push_back(fmt[i]);
            continue;
        }
        std::string spec = "%";
        std::size_t j = i + 1;
        bool left = false, plus = false, space = false;  // (# and 0 stay in `spec` for the host formatter)
        for (; j < fmt.size() && std::strchr("-+ #0", fmt[j]); ++j) {
            spec.push_back(fmt[j]);
            left |= fmt[j] == '-';
            plus |= fmt[j] == '+';
            space |= fmt[j] == ' ';
        }
        int width = -1, prec = -1;
        if (j < fmt.size() && fmt[j] == '*') {
            width = static_cast<s32>(arg64());
            if (width < 0) {
                left = true;
                spec.push_back('-');
                width = -width;
            }
            ++j;
        } else {
            for (width = 0; j < fmt.size() && fmt[j] >= '0' && fmt[j] <= '9'; ++j) width = width * 10 + (fmt[j] - '0');
            if (width == 0) width = -1;
        }
        if (j < fmt.size() && fmt[j] == '.') {
            ++j;
            if (j < fmt.size() && fmt[j] == '*') {
                prec = static_cast<s32>(arg64());
                ++j;
            } else {
                for (prec = 0; j < fmt.size() && fmt[j] >= '0' && fmt[j] <= '9'; ++j) prec = prec * 10 + (fmt[j] - '0');
            }
        }
        if (width >= 0) spec += std::to_string(width);
        if (prec >= 0) spec += "." + std::to_string(prec);
        // Lengths as this newlib build reads them (checked against the recompiled sprintf): h and hh both short, l, ll,
        // q, L and j the whole 64-bit slot (long is 64 bits here), none / z / t the low 32 bits.
        int len = 0;  // -1 h / hh, 0 int, 2 l / ll / q / L / j
        for (; j < fmt.size(); ++j) {
            const char c = fmt[j];
            if (c == 'h') len = -1;
            else if (c == 'l') len = 2;
            else if (c == 'q' || c == 'L' || c == 'j') len = 2;
            else if (c == 'z' || c == 't') len = 0;
            else break;
        }
        if (j >= fmt.size()) break;
        const char conv = fmt[j];
        i = j;
        switch (conv) {
        case '%': out.push_back('%'); break;
        case 'd': case 'i': {
            const u64 v = arg64();
            const long long x = len >= 2 ? static_cast<long long>(v)
                                : len == -1 ? static_cast<short>(v)
                                            : static_cast<long long>(static_cast<s32>(v));
            std::snprintf(buf, sizeof buf, (spec + "lld").c_str(), x);
            out += buf;
            break;
        }
        case 'u': case 'o': case 'x': case 'X': {
            const u64 v = arg64();
            const unsigned long long x = len >= 2 ? v
                                         : len == -1 ? static_cast<unsigned short>(v)
                                                     : static_cast<unsigned long long>(static_cast<u32>(v));
            std::snprintf(buf, sizeof buf, (spec + "ll" + conv).c_str(), x);
            out += buf;
            break;
        }
        case 'c': {
            const char ch = static_cast<char>(arg64());
            std::string s(1, ch);
            if (width > 1) s = left ? s + std::string(width - 1, ' ') : std::string(width - 1, ' ') + s;
            out += s;
            break;
        }
        case 's': {
            const u32 p = static_cast<u32>(arg64());
            std::string s = p == 0 ? std::string("(null)") : guest_string(ctx, p, 1 << 16);
            if (prec >= 0 && s.size() > static_cast<std::size_t>(prec)) s.resize(static_cast<std::size_t>(prec));
            if (width > 0 && s.size() < static_cast<std::size_t>(width))
                s = left ? s + std::string(width - s.size(), ' ') : std::string(width - s.size(), ' ') + s;
            out += s;
            break;
        }
        case 'p': {  // newlib: 0x + lower-case hex of the whole 64-bit slot
            std::snprintf(buf, sizeof buf, "0x%llx", static_cast<unsigned long long>(arg64()));
            std::string s = buf;
            if (width > 0 && s.size() < static_cast<std::size_t>(width))
                s = left ? s + std::string(width - s.size(), ' ') : std::string(width - s.size(), ' ') + s;
            out += s;
            break;
        }
        case 'f': case 'F': case 'e': case 'E': case 'g': case 'G': {
            const u64 bits = arg64();
            double d;
            std::memcpy(&d, &bits, sizeof d);
            if (std::isinf(d) || std::isnan(d)) {
                const bool up = conv == 'F' || conv == 'E' || conv == 'G';
                std::string s = std::isnan(d) ? (up ? "NAN" : "nan") : (up ? "INF" : "inf");
                if (!std::isnan(d) && d < 0) s = "-" + s;
                else if (!std::isnan(d) && plus) s = "+" + s;
                else if (!std::isnan(d) && space) s = " " + s;
                if (width > 0 && s.size() < static_cast<std::size_t>(width))
                    s = left ? s + std::string(width - s.size(), ' ') : std::string(width - s.size(), ' ') + s;
                out += s;
            } else {
                std::snprintf(buf, sizeof buf, (spec + conv).c_str(), d);
                out += buf;
            }
            break;
        }
        case 'n': (void)arg64(); break;
        default:  // unknown conversion: newlib prints the character
            out.push_back(conv);
            break;
        }
    }
    return out;
}

void install_printf(StandIns& s, u64 cycles) {
    s.install(kPrintf, "printf", [](EEContext& ctx, StandIns&, StandInCall& c) {
        c.text = guest_format(ctx, static_cast<u32>(c.args[0]), 1);
        c.v0 = c.text.size();
    }, cycles);
}

void install_sprintf(StandIns& s, u64 cycles) {
    s.install(kSprintf, "sprintf", [](EEContext& ctx, StandIns&, StandInCall& c) {
        c.text = guest_format(ctx, static_cast<u32>(c.args[1]), 2);
        const u32 buf = static_cast<u32>(c.args[0]);
        for (std::size_t i = 0; i <= c.text.size(); ++i)
            ctx.memory->write<u8>(buf + static_cast<u32>(i), i < c.text.size() ? static_cast<u8>(c.text[i]) : 0u);
        c.v0 = c.text.size();
    }, cycles);
    // vsprintf(buf, fmt, ap): the va_list points at 8-byte slots in guest memory.
    s.install(kVsprintf, "vsprintf", [](EEContext& ctx, StandIns&, StandInCall& c) {
        // Re-read the slots as if they were stack arguments: point a scratch view at them.
        const u32 ap = static_cast<u32>(c.args[2]);
        const u64 sp_saved = ctx.gpr[GPR_SP].u64[0];
        ctx.gpr[GPR_SP].u64[0] = ap;
        c.text = guest_format(ctx, static_cast<u32>(c.args[1]), 8);  // every argument from the "stack" (the va_list)
        ctx.gpr[GPR_SP].u64[0] = sp_saved;
        const u32 buf = static_cast<u32>(c.args[0]);
        for (std::size_t i = 0; i <= c.text.size(); ++i)
            ctx.memory->write<u8>(buf + static_cast<u32>(i), i < c.text.size() ? static_cast<u8>(c.text[i]) : 0u);
        c.v0 = c.text.size();
    }, cycles);
}

// --- the heap -------------------------------------------------------------------------------------------------------
GuestHeap::GuestHeap(u32 base, u32 size) : base_(base), size_(size) { free_[base] = size; }

u32 GuestHeap::alloc(u32 size, u32 align) {
    const u32 rs = (std::max<u32>(size, 1u) + 15u) & ~15u;
    if (align < 16) align = 16;
    for (auto it = free_.begin(); it != free_.end(); ++it) {
        const u32 s = it->first, n = it->second;
        const u32 a = (s + align - 1) & ~(align - 1);
        if (a < s || a - s > n || n - (a - s) < rs) continue;
        free_.erase(it);
        if (a > s) free_[s] = a - s;
        if (a + rs < s + n) free_[a + rs] = s + n - (a + rs);
        live_[a] = rs;
        return a;
    }
    return 0;
}

bool GuestHeap::free(u32 p) {
    auto it = live_.find(p);
    if (it == live_.end()) {
        ++bad_frees;
        return false;
    }
    u32 s = p, n = it->second;
    live_.erase(it);
    auto next = free_.lower_bound(s);
    if (next != free_.end() && next->first == s + n) {
        n += next->second;
        next = free_.erase(next);
    }
    if (next != free_.begin()) {
        auto prev = std::prev(next);
        if (prev->first + prev->second == s) {
            s = prev->first;
            n += prev->second;
            free_.erase(prev);
        }
    }
    free_[s] = n;
    return true;
}

u32 GuestHeap::size_of(u32 p) const {
    auto it = live_.find(p);
    return it == live_.end() ? 0u : it->second;
}

void GuestHeap::reserve(u32 p, u32 size) {
    const u32 lo = p & ~15u, hi = (p + size + 15u) & ~15u;
    for (auto it = free_.begin(); it != free_.end();) {
        const u32 s = it->first, e = it->first + it->second;
        if (e <= lo || s >= hi) {
            ++it;
            continue;
        }
        it = free_.erase(it);
        if (s < lo) free_[s] = lo - s;
        if (e > hi) free_[hi] = e - hi;
    }
    live_[lo] = hi - lo;
}

namespace {
void zero_guest(EEContext& ctx, u32 va, u32 n) {
    for (u32 i = 0; i < n; ++i) ctx.memory->write<u8>(va + i, 0);
}
void copy_guest(EEContext& ctx, u32 dst, u32 src, u32 n) {
    std::vector<u8> tmp(n);
    for (u32 i = 0; i < n; ++i) tmp[i] = ctx.memory->read<u8>(src + i);
    for (u32 i = 0; i < n; ++i) ctx.memory->write<u8>(dst + i, tmp[i]);
}
}  // namespace

void GuestHeap::install_h_malloc(StandIns& s, u64 cycles) {
    s.install(kHMalloc, "H_Malloc", [this](EEContext&, StandIns&, StandInCall& c) {
        c.extra = static_cast<u32>(c.args[0]);
        c.v0 = sx32(alloc(static_cast<u32>(c.args[0])));
    }, cycles);
    s.install(kHFree, "H_Free", [this](EEContext&, StandIns&, StandInCall& c) {
        c.extra = size_of(static_cast<u32>(c.args[0]));
        free(static_cast<u32>(c.args[0]));
        c.v0 = 0;
    }, cycles);
}

void GuestHeap::install_rw(StandIns& s, u64 cycles) {
    s.install(0x104140u, "RwMalloc", [this](EEContext&, StandIns&, StandInCall& c) {
        c.extra = static_cast<u32>(c.args[0]);
        c.v0 = sx32(alloc(static_cast<u32>(c.args[0])));
    }, cycles);
    s.install(0x104280u, "RwFree", [this](EEContext&, StandIns&, StandInCall& c) {
        c.extra = size_of(static_cast<u32>(c.args[0]));
        if (c.args[0] != 0) free(static_cast<u32>(c.args[0]));
        c.v0 = 0;
    }, cycles);
    s.install(0x103F50u, "RwRealloc", [this](EEContext& ctx, StandIns&, StandInCall& c) {
        const u32 old = static_cast<u32>(c.args[0]), size = static_cast<u32>(c.args[1]);
        c.extra = size;
        const u32 p = alloc(size);
        if (old != 0 && p != 0) {
            copy_guest(ctx, p, old, std::min(size_of(old), size));
            free(old);
        }
        c.v0 = sx32(p);
    }, cycles);
    s.install(0x104040u, "RwCalloc", [this](EEContext& ctx, StandIns&, StandInCall& c) {
        const u32 n = static_cast<u32>(c.args[0]) * static_cast<u32>(c.args[1]);
        c.extra = n;
        const u32 p = alloc(n);
        if (p != 0) zero_guest(ctx, p, n);
        c.v0 = sx32(p);
    }, cycles);
    s.install(0x4C3D10u, "_rwFreeListAllocReal", [this](EEContext& ctx, StandIns&, StandInCall& c) {
        const u32 fl = static_cast<u32>(c.args[0]);
        const u32 entry = lw(ctx, fl), align = lw(ctx, fl + 12);
        c.extra = entry;
        c.v0 = sx32(alloc(entry, align > 16 && (align & (align - 1)) == 0 ? align : 16));
    }, cycles);
    s.install(0x4C3EE0u, "_rwFreeListFreeReal", [this](EEContext&, StandIns&, StandInCall& c) {
        c.extra = size_of(static_cast<u32>(c.args[1]));
        free(static_cast<u32>(c.args[1]));
        c.v0 = 0;
    }, cycles);
}

void GuestHeap::install_libc(StandIns& s, u64 cycles) {
    s.install(0x520728u, "malloc", [this](EEContext&, StandIns&, StandInCall& c) {
        c.extra = static_cast<u32>(c.args[0]);
        c.v0 = sx32(alloc(static_cast<u32>(c.args[0])));
    }, cycles);
    s.install(0x520748u, "free", [this](EEContext&, StandIns&, StandInCall& c) {
        c.extra = size_of(static_cast<u32>(c.args[0]));
        if (c.args[0] != 0) free(static_cast<u32>(c.args[0]));
        c.v0 = 0;
    }, cycles);
    s.install(0x51E150u, "calloc", [this](EEContext& ctx, StandIns&, StandInCall& c) {
        const u32 n = static_cast<u32>(c.args[0]) * static_cast<u32>(c.args[1]);
        c.extra = n;
        const u32 p = alloc(n);
        if (p != 0) zero_guest(ctx, p, n);
        c.v0 = sx32(p);
    }, cycles);
    s.install(0x522F98u, "realloc", [this](EEContext& ctx, StandIns&, StandInCall& c) {
        const u32 old = static_cast<u32>(c.args[0]), size = static_cast<u32>(c.args[1]);
        c.extra = size;
        const u32 p = alloc(size);
        if (old != 0 && p != 0) {
            copy_guest(ctx, p, old, std::min(size_of(old), size));
            free(old);
        }
        c.v0 = sx32(p);
    }, cycles);
}

void GuestHeap::install_all(StandIns& s, u64 cycles) {
    install_h_malloc(s, cycles);
    install_rw(s, cycles);
    install_libc(s, cycles);
}

void write_rw_slots(Machine& m) {
    for (std::size_t i = 0; i < kRwSlotFns.size(); ++i)
        std::memcpy(m.at(kRwSlots + 4u * static_cast<u32>(i)), &kRwSlotFns[i], 4);
}

std::vector<u8> read_snapshot(const char* dir) {
    const auto p = std::filesystem::path(elf_path()).parent_path().parent_path() / "_ours" / dir / "eeMemory.bin";
    std::ifstream f(p, std::ios::binary);
    if (!f) return {};
    std::vector<u8> v(EEMemory::kMainRamSize);
    f.read(reinterpret_cast<char*>(v.data()), static_cast<std::streamsize>(v.size()));
    if (f.gcount() != static_cast<std::streamsize>(v.size())) return {};
    return v;
}

std::vector<std::pair<u32, u32>> h_malloc_blocks(const Machine& m) {
    std::vector<std::pair<u32, u32>> out;
    auto word = [&](u32 va) {
        u32 v;
        std::memcpy(&v, m.mem.main_ram() + va, 4);
        return v;
    };
    const u32 base = word(kGp - 19620u), count = word(kGp - 19628u);
    if (base == 0 || base >= EEMemory::kMainRamSize || count > 100000) return out;
    for (u32 i = 0; i < count; ++i) {
        const u32 start = word(base + 8u * i), size = word(base + 8u * i + 4u);
        if (size != 0) out.emplace_back(start, size);
    }
    return out;
}

void copy_from_snapshot(Machine& m, const std::vector<u8>& snap, u32 va, u32 len) {
    if (snap.size() < static_cast<std::size_t>(va) + len) return;
    std::memcpy(m.at(va), snap.data() + va, len);
}

// --- the file layer -----------------------------------------------------------------------------------------------
std::string extracted_root() {
    if (const char* e = std::getenv("P3FES_EXTRACTED")) return e;
    return std::filesystem::path(elf_path()).parent_path().parent_path().string();
}

FakeCd::FakeCd(GuestHeap& heap, std::string r) : root(r.empty() ? extracted_root() : std::move(r)), heap_(heap) {}

std::string FakeCd::build_path(const std::string& path) {
    std::string s = "VOL:\\";
    for (std::size_t i = 0; i < path.size() && i < game::kHCdvdPathMax; ++i) {
        char c = path[i];
        if (c == '/') c = '\\';
        if (c >= 'a' && c <= 'z') c = static_cast<char>(c - 'a' + 'A');
        s.push_back(c);
    }
    return s;
}

std::string FakeCd::host_path(const std::string& guest_path) const {
    std::string rel = guest_path;
    std::string vol;
    const std::size_t colon = rel.find(':');
    if (colon != std::string::npos) {
        vol = rel.substr(0, colon);
        rel = rel.substr(colon + 1);
    }
    while (!rel.empty() && (rel[0] == '\\' || rel[0] == '/')) rel.erase(0, 1);
    for (char& c : rel) {
        if (c == '\\') c = '/';
        if (c >= 'a' && c <= 'z') c = static_cast<char>(c - 'a' + 'A');
    }
    std::vector<std::string> vols = {"DATA", "BTL", "BGM"};
    if (vol == "BTL") vols = {"BTL", "DATA", "BGM"};
    if (vol == "BGM") vols = {"BGM", "DATA", "BTL"};
    for (const std::string& v : vols) {
        const std::filesystem::path p = std::filesystem::path(root) / v / rel;
        std::error_code ec;
        if (std::filesystem::is_regular_file(p, ec)) return p.string();
    }
    return {};
}

bool FakeCd::load_node(EEContext& ctx, u32 node) {
    if (!load) return false;
    const std::string gpath = guest_string(ctx, node + 16, 256);
    const std::string hp = host_path(gpath);
    if (hp.empty()) {
        missing.push_back(gpath);
        return false;
    }
    std::ifstream f(hp, std::ios::binary);
    std::vector<u8> bytes((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    const u32 size = static_cast<u32>(bytes.size());
    const bool archive = lw(ctx, node + 336) != 0;
    const u32 sct = (size + 2047u) >> 11;
    const u32 raw = heap_.alloc((sct << 11) + (archive ? 320u : 64u));
    if (raw == 0) return false;
    const u32 data = (raw + 63u) & ~63u;
    sw(ctx, node + 276, raw);
    sw(ctx, node + 272, data);
    sw(ctx, node + 292, size);
    sw(ctx, node + 280, size);
    // Through a host buffer (never a kernel read into guest RAM: write_tracker.h's protected pages).
    u8* dst = ctx.memory->main_ram();
    std::memcpy(dst + data, bytes.data(), bytes.size());
    if (archive) std::memset(dst + data + size, 0, 256);
    sh(ctx, node + 862, 1);
    // H_Cdvd_Update's state-3 step: register the file (or the archive's entries) in sCdvdCache, then state 4.
    game::H_Cdvd_AddFile(ctx, node + 8);
    sw(ctx, node + 12, game::kHCdvdStateLoaded);
    return true;
}

void FakeCd::release(EEContext& ctx, u32 node) {
    const u32 prev = lw(ctx, node), next = lw(ctx, node + 4);
    sw(ctx, prev + 4, next);
    if (next != 0) sw(ctx, next, prev);
    if (lw(ctx, node + 272) != 0 && lw(ctx, node + 8) == 0) {
        heap_.free(lw(ctx, node + 276));
        sw(ctx, node + 272, 0);
        sw(ctx, node + 276, 0);
    }
    for (u32 i = 0; i < game::kHCdvdCacheSlots; ++i) {
        const u32 slot = game::kHCdvdCache + 148u * i;
        if (lw(ctx, slot) != 0 && lw(ctx, slot + 4) == node + 8) sw(ctx, slot, 0);
    }
    if (lw(ctx, node + 340) != 0) sw(ctx, node + 340, 0);
    heap_.free(node);
}

void FakeCd::update(EEContext& ctx) {
    // The retail walk: loaded nodes pass (their deferred destroys applied), the first unloaded one is served and
    // ends the call unless it loads (the fake completes a read at once).
    u32 n = lw(ctx, game::kHCdvdListHead + 4);
    while (n != 0) {
        u32 state = lw(ctx, n + 12);
        if (state == 0) {
            if (!load_node(ctx, n)) return;
            state = lw(ctx, n + 12);
        }
        if (state != game::kHCdvdStateLoaded) return;
        const u32 next = lw(ctx, n + 4);
        sh(ctx, n + 858, static_cast<s16>(lh(ctx, n + 858) - lh(ctx, n + 860)));
        sh(ctx, n + 860, 0);
        if (lh(ctx, n + 858) <= 0) release(ctx, n);
        n = next;
    }
}

void FakeCd::install(StandIns& s, u64 cycles) {
    s.install(kHCdvdRequestFn, "H_Cdvd_Request", [this](EEContext& ctx, StandIns&, StandInCall& c) {
        const u32 path = static_cast<u32>(c.args[0]);
        const std::string built = build_path(guest_string(ctx, path, 1024));
        c.text = built;
        u32 s0 = game::kHCdvdListHead;
        if (lw(ctx, s0 + 4) != 0) {
            for (;;) {
                if (guest_string(ctx, s0 + 16, 256) == built) {
                    sh(ctx, s0 + 858, static_cast<s16>(lh(ctx, s0 + 858) + 1));
                    c.v0 = sx32(s0);
                    return;
                }
                const u32 next = lw(ctx, s0 + 4);
                if (next == 0) break;
                s0 = next;
            }
        }
        const u32 node = heap_.alloc(sizeof(game::HCdvdRequest));
        c.extra = node;
        if (node == 0) {
            c.v0 = 0;
            return;
        }
        zero_guest(ctx, node, sizeof(game::HCdvdRequest));
        game::H_Cdvd_BuildPathUppercase(ctx, path, node + 16);
        game::H_Cdvd_BuildVolumePaths(ctx, node + 16, node + 344, node + 600);
        sw(ctx, node + 12, 0);
        sw(ctx, s0 + 4, node);
        sw(ctx, node, s0);
        sw(ctx, node + 4, 0);
        sw(ctx, node + 272, 0);
        sw(ctx, node + 8, 0);
        sw(ctx, node + 336, static_cast<u32>(c.args[1]));
        sh(ctx, node + 858, 1);
        sw(ctx, node + 340, 0);
        nodes.push_back(node);
        c.v0 = sx32(node);
    }, cycles);
    s.install(kHCdvdUpdateFn, "H_Cdvd_Update", [this](EEContext& ctx, StandIns&, StandInCall& c) {
        update(ctx);
        c.v0 = 0;
    }, cycles);
    s.install(kHCdvdReadSyncFn, "H_Cdvd_ReadSync", [this](EEContext& ctx, StandIns&, StandInCall& c) {
        const u32 node = static_cast<u32>(c.args[0]);
        c.text = guest_string(ctx, node + 16, 256);
        if (lw(ctx, node + 12) != game::kHCdvdStateLoaded) update(ctx);
        c.extra = lw(ctx, node + 12) == game::kHCdvdStateLoaded ? lw(ctx, node + 292) : 0u;
        c.v0 = lw(ctx, node + 12) == game::kHCdvdStateLoaded ? 1u : 0u;  // H_Cdvd_IsFileLoaded's last result
    }, cycles);
    s.install(kHCdvdDestroyFn, "H_Cdvd_Destroy", [this](EEContext& ctx, StandIns&, StandInCall& c) {
        const u32 node = static_cast<u32>(c.args[0]);
        c.text = guest_string(ctx, node + 16, 256);
        c.v0 = 1;
        if (lw(ctx, node + 12) != 0) {
            sh(ctx, node + 860, static_cast<s16>(lh(ctx, node + 860) + 1));
            return;
        }
        sh(ctx, node + 858, static_cast<s16>(lh(ctx, node + 858) - 1));
        if (lh(ctx, node + 858) > 0) return;
        release(ctx, node);
    }, cycles);
}

// --- worlds and pairs ---------------------------------------------------------------------------------------------
void install_standard(StandInWorld& w) {
    w.heap.install_all(w.si);
    install_printf(w.si);
    install_sprintf(w.si);
    w.cd.install(w.si);
}

namespace {
Fn g_body[2];
StandInWorld* g_world[2];
void thunk_hand(EEContext& ctx) {
    StandInsScope s(g_world[0]->si);
    g_body[0](ctx);
}
void thunk_recomp(EEContext& ctx) {
    StandInsScope s(g_world[1]->si);
    g_body[1](ctx);
}
}  // namespace

SiPair run_pair_si(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, HwCheck hw,
                   const WorldSetup& setup, std::initializer_list<Reset> resets) {
    INFO(std::string(what) << " (seed " << seed << ")");  // also reported when a body stops the run with a fatal event
    SiPair p;
    p.hand = std::make_unique<StandInWorld>();
    p.recomp = std::make_unique<StandInWorld>();
    setup(*p.hand);
    setup(*p.recomp);
    const GuestRange arena = p.hand->heap.range();
    const bool covered = std::any_of(hw.ranges.begin(), hw.ranges.end(), [&](const GuestRange& r) {
        return r.va <= arena.va && arena.va + arena.len <= r.va + r.len;
    });
    if (!covered) hw.ranges.insert(hw.ranges.begin(), arena);
    g_body[0] = hand;
    g_body[1] = recomp;
    g_world[0] = p.hand.get();
    g_world[1] = p.recomp.get();
    p.hw = run_pair_hw(m, &thunk_hand, &thunk_recomp, args, seed, what, hw, resets);
    expect_same_log(p.hand->si, p.recomp->si, what);
    CHECK(p.hand->heap.live() == p.recomp->heap.live());
    CHECK(p.hand->heap.bad_frees == p.recomp->heap.bad_frees);
    CHECK(p.hand->cd.nodes == p.recomp->cd.nodes);
    return p;
}

}  // namespace p3fes::game_test
