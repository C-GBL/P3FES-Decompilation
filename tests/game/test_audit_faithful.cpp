// p3fes_audit_faithful (tests/game/audit_faithful.cmake): is every hand-written function register- and frame-faithful?
//
// For each function of game/replaced.txt the hand-written body (fn_<name>_<addr8>, game/) and its recompiled body
// (fn_<name>_<addr8>__recomp) run from the same guest machine inside the whole recompiled program, through
// tests/game/handgen_pairs.h's run_one (the whole register file and cycle count at every check point, the stop, the bus
// log). Unlike the slices' own pair tests, nothing is masked: all 32 MiB of RAM INCLUDING the stack below $sp (a frame
// that stays live on a waiting thread's stack -- threads whose stacks live in .data or the heap -- is memory the replay
// gates compare), the scratchpad, the BIOS window. Every pair runs (no early exit), and each function gets one verdict
// line with its difference classes:
//   frame     RAM differs inside the function's own frame [$sp - N, $sp) (N from its prologue): missing frame / spills
//   deep      RAM differs below the own frame: a callee's frame / spills (or the function's $sp is off)
//   ram       RAM differs outside the stack window [$sp - 64 KiB, $sp): real logic (or a caller-frame write)
//   spr bus bios vuctl   scratchpad / hardware bus / BIOS window / VU control writes differ: real logic
//   stop      the runs stop differently (stopped vs returned, stop pc, message, syscalls): real logic
//   nchk      the check-point counts differ (a missing / extra charge, back-edge or call)
//   {cp,end}_{ra,saved,v0,scratch,u128,hilo,fpu,vu0,sa,cycles}: the register file at a check point / at the return or
//             stop: $ra (a missing link), $s0-$s7/$fp/$gp/$sp, $v0, $at/$v1/$a0-$a3/$t0-$t9/$k0/$k1, only the upper 64
//             bits of a GPR, HI/LO, FPRs/FCR31/ACC, VU0 macro registers, SA, cycles alone.
// Output (stdout, and P3FES_AUDIT_OUT): index, name, start, frame size, pairs, differing pairs, pairs with a stop,
// faithful|differs, the classes of all pairs, the classes of the pairs where both runs returned, the first instance of
// each class.
// Environment: P3FES_AUDIT_SEEDS (random worlds per function, default 16), P3FES_AUDIT_SNAPSHOTS (comma list of replay
// snapshot directories under extracted/_ours, beside the ELF's disc/ directory: one more set of P3FES_AUDIT_SNAPSHOT_SEEDS pairs each, default 4, on the
// snapshot's RAM with the random world on top), P3FES_AUDIT_ONLY (comma list of names), P3FES_AUDIT_FROM / _TO (case
// indices), P3FES_AUDIT_TRACE=1 (which body of which pair runs, on stderr), P3FES_AUDIT_OUT (TSV, appended and flushed per function), P3FES_AUDIT_LIST=1 (print the cases and stop).
// stderr gets "AUDIT BEGIN <index> <name>" before each function (the driver's crash / hang bookkeeping).
#include "handgen_pairs.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <memory>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace p3fes;
using namespace p3fes::game_test;

#include "audit_cases.inc"  // namespace p3fes::recomp_gen declarations; kCases[] = {name, addr, hand, recomp}

namespace {

constexpr u32 kWorld = 0x01810000u;  // as p3fes_handgen's skeleton (same seeds: same worlds as a slice's skeleton test)
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kStackWindow = 0x10000u;  // [kSp - 64 KiB, kSp): the stack the run may use; compared byte by byte

enum Class : unsigned {
    kFrame, kDeep, kRam, kSpr, kBus, kBios, kVuCtl, kStop, kNchk,
    kCpRa, kCpSaved, kCpV0, kCpScratch, kCpU128, kCpHiLo, kCpFpu, kCpVu0, kCpSa, kCpCycles,
    kEndRa, kEndSaved, kEndV0, kEndScratch, kEndU128, kEndHiLo, kEndFpu, kEndVu0, kEndSa, kEndCycles,
    kClassCount
};
const char* const kClassName[kClassCount] = {
    "frame", "deep", "ram", "spr", "bus", "bios", "vuctl", "stop", "nchk",
    "cp_ra", "cp_saved", "cp_v0", "cp_scratch", "cp_u128", "cp_hilo", "cp_fpu", "cp_vu0", "cp_sa", "cp_cycles",
    "end_ra", "end_saved", "end_v0", "end_scratch", "end_u128", "end_hilo", "end_fpu", "end_vu0", "end_sa", "end_cycles"};
const char* const kGprName[32] = {"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
                                  "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"};

struct Verdict {
    u64 classes = 0;              // bit per Class
    std::string detail[kClassCount];  // the first instance of each class
    void add(Class c, const std::string& d) {
        if (!(classes & (1ull << c))) detail[c] = d;
        classes |= 1ull << c;
    }
};

// Every difference of two register files, as classes (cp_ / end_ chosen by `base`: kCpRa or kEndRa).
void diff_regs(const hgp::Snap& a, const hgp::Snap& b, unsigned base, const std::string& where, Verdict& v) {
    auto add = [&](unsigned off, const std::string& d) { v.add(static_cast<Class>(base + off), where + d); };
    bool any = false;
    for (unsigned r = 1; r < 32; ++r) {
        const u128 &x = a.gpr[r], &y = b.gpr[r];
        if (same_u128(x, y)) continue;
        any = true;
        const std::string d = std::string("$") + kGprName[r] + " hand " + hex64(x.u64[1]) + ":" + hex64(x.u64[0]) + " recomp " +
                              hex64(y.u64[1]) + ":" + hex64(y.u64[0]);
        if (x.u64[0] == y.u64[0]) { add(kCpU128 - kCpRa, d); continue; }
        if (r == GPR_RA) add(0, d);
        else if ((r >= GPR_S0 && r <= GPR_S7) || r == GPR_FP || r == GPR_GP || r == GPR_SP) add(kCpSaved - kCpRa, d);
        else if (r == GPR_V0) add(kCpV0 - kCpRa, d);
        else add(kCpScratch - kCpRa, d);
    }
    if (!same_u128(a.hi, b.hi) || !same_u128(a.lo, b.lo)) {
        any = true;
        add(kCpHiLo - kCpRa, "hi " + hex64(a.hi.u64[0]) + "/" + hex64(b.hi.u64[0]) + " lo " + hex64(a.lo.u64[0]) + "/" + hex64(b.lo.u64[0]));
    }
    if (a.sa != b.sa) { any = true; add(kCpSa - kCpRa, "sa"); }
    for (unsigned i = 0; i < 32; ++i)
        if (a.fpr[i] != b.fpr[i]) {
            any = true;
            add(kCpFpu - kCpRa, "$f" + std::to_string(i) + " hand " + hex64(a.fpr[i]) + " recomp " + hex64(b.fpr[i]));
            break;
        }
    if (a.fcr31 != b.fcr31) { any = true; add(kCpFpu - kCpRa, "fcr31 hand " + hex64(a.fcr31) + " recomp " + hex64(b.fcr31)); }
    if (a.acc != b.acc) { any = true; add(kCpFpu - kCpRa, "acc"); }
    const VU0State &x = a.vu0, &y = b.vu0;
    if (std::memcmp(x.vf, y.vf, sizeof x.vf) != 0 || std::memcmp(x.vi, y.vi, sizeof x.vi) != 0 ||
        std::memcmp(x.acc, y.acc, sizeof x.acc) != 0 || x.q != y.q || x.p != y.p || x.i != y.i || x.r != y.r ||
        x.status != y.status || x.mac != y.mac || x.clip != y.clip) {
        any = true;
        add(kCpVu0 - kCpRa, "vu0");
    }
    if (!any && a.cycles != b.cycles)
        add(kCpCycles - kCpRa, "cycles hand " + std::to_string(a.cycles) + " recomp " + std::to_string(b.cycles));
}

// The frame size of the prologue's `addiu/daddiu $sp, $sp, -N` (first 24 words), 0 for a leaf without one.
u32 frame_size(Machine& m, u32 addr) {
    for (u32 i = 0; i < 24; ++i) {
        u32 w;
        std::memcpy(&w, m.at(addr + 4 * i), 4);
        if ((w >> 16) == 0x27BDu || (w >> 16) == 0x67BDu) {
            const s32 imm = static_cast<s16>(w & 0xFFFFu);
            if (imm < 0) return static_cast<u32>(-imm);
        }
    }
    return 0;
}

std::string off_text(s64 off) {
    char b[32];
    std::snprintf(b, sizeof b, "%s0x%llX", off < 0 ? "-" : "+", static_cast<unsigned long long>(off < 0 ? -off : off));
    return b;
}

bool g_trace = false;  // P3FES_AUDIT_TRACE: "AUDIT RUN hand|recomp seed N" on stderr before each run (which body crashes)
void trace_run(const char* body, u32 seed) {
    if (!g_trace) return;
    std::fprintf(stderr, "AUDIT RUN %s seed %u\n", body, seed);
    std::fflush(stderr);
}

// One pair, every difference classified. Afterwards the recompiled run's memory is in place.
// Returns true when both runs returned (no stop): the pairs whose classes make the "on returning runs" column.
bool audit_pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, u32 frame, Verdict& v, int& stops) {
    const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    u8* const ram0 = m.mem.main_ram();
    u8* const win = ram0 + (kSp - kStackWindow);
    std::vector<u8> stack_h, stack_r;
    hgp::Run h, r;
    {
        PairRange ram(ram0, ram0 + EEMemory::kMainRamSize);
        trace_run("hand", seed);
        h = hgp::run_one(m, hand, args, seed, {});
        stack_h.assign(win, win + kStackWindow);
        std::vector<u8> bios_h;
        if (!hgp::bios_clean(m)) {
            bios_h.assign(m.mem.bios(), m.mem.bios() + EEMemory::kBiosSize);
            std::memset(m.mem.bios(), 0, EEMemory::kBiosSize);
        }
        ram.between();
        std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
        trace_run("recomp", seed);
        r = hgp::run_one(m, recomp, args, seed, {});
        stack_r.assign(win, win + kStackWindow);
        const bool bios_r = !hgp::bios_clean(m);
        if (bios_r != !bios_h.empty() ||
            (bios_r && std::memcmp(bios_h.data(), m.mem.bios(), EEMemory::kBiosSize) != 0))
            v.add(kBios, "BIOS window written differently");
        if (bios_r) std::memset(m.mem.bios(), 0, EEMemory::kBiosSize);
        // RAM outside the stack window: hide the window (the hand run's bytes in place), take the first difference.
        std::memcpy(win, stack_h.data(), kStackWindow);
        if (const std::size_t first = ram.first_difference(); first != ram.size())
            v.add(kRam, "RAM " + hex64(first) + " hand " + std::to_string(ram.first_body_byte(first)) + " recomp " +
                            std::to_string(ram0[first]) + (first >= kSp && first < kSp + 0x100 ? " (caller frame)" : ""));
        std::memcpy(win, stack_r.data(), kStackWindow);
    }
    if (h.stopped || r.stopped) ++stops;
    // the stack window: the own frame, then below it
    {
        s64 lo_f = 0, hi_f = 0, lo_d = 0, hi_d = 0;
        int nf = 0, nd = 0;
        for (u32 i = 0; i < kStackWindow; ++i) {
            if (stack_h[i] == stack_r[i]) continue;
            const s64 off = static_cast<s64>(i) - static_cast<s64>(kStackWindow);  // relative to $sp at entry
            if (frame != 0 && -off <= static_cast<s64>(frame)) {
                if (nf++ == 0) lo_f = off;
                hi_f = off;
            } else {
                if (nd++ == 0) lo_d = off;
                hi_d = off;
            }
        }
        if (nf) v.add(kFrame, std::to_string(nf) + " bytes in $sp" + off_text(lo_f) + "..$sp" + off_text(hi_f) + " (frame " + off_text(-static_cast<s64>(frame)) + ")");
        if (nd) v.add(kDeep, std::to_string(nd) + " bytes in $sp" + off_text(lo_d) + "..$sp" + off_text(hi_d) + " (frame " + off_text(-static_cast<s64>(frame)) + ")");
    }
    if (h.stopped != r.stopped || h.stop_pc != r.stop_pc || h.what != r.what || h.syscalls != r.syscalls)
        v.add(kStop, std::string("hand ") + (h.stopped ? "stopped at " + hex64(h.stop_pc) + " (" + h.what + ")" : "returned") +
                         ", recomp " + (r.stopped ? "stopped at " + hex64(r.stop_pc) + " (" + r.what + ")" : "returned") +
                         " syscalls " + std::to_string(h.syscalls) + "/" + std::to_string(r.syscalls));
    if (h.snaps.size() != r.snaps.size())
        v.add(kNchk, "check points hand " + std::to_string(h.snaps.size()) + " recomp " + std::to_string(r.snaps.size()));
    const std::size_t n = std::min(h.snaps.size(), r.snaps.size());
    for (std::size_t i = 0; i < n; ++i) {
        Verdict one;
        diff_regs(h.snaps[i], r.snaps[i], kCpRa, "check point " + std::to_string(i) + "/" + std::to_string(n) + ": ", one);
        if (one.classes) {  // the first differing check point only (later ones follow from it)
            for (unsigned c = 0; c < kClassCount; ++c)
                if (one.classes & (1ull << c)) v.add(static_cast<Class>(c), one.detail[c]);
            break;
        }
    }
    diff_regs(h.end, r.end, kEndRa, r.stopped ? "at the stop: " : "at the return: ", v);
    if (first_difference(h.spr.data(), r.spr.data(), h.spr.size()) != h.spr.size()) v.add(kSpr, "scratchpad");
    bool bus_same = h.bus.size() == r.bus.size();
    for (std::size_t i = 0; bus_same && i < h.bus.size(); ++i) {
        const auto &a = h.bus[i], &b = r.bus[i];
        bus_same = a.write == b.write && a.bits == b.bits && a.pa == b.pa && a.lo == b.lo && a.hi == b.hi;
    }
    if (!bus_same) v.add(kBus, "bus log");
    if (h.vu_control != r.vu_control) v.add(kVuCtl, "VU control writes");
    (void)seed;
    return !h.stopped && !r.stopped;
}

std::vector<u8> read_file_bytes(const std::string& path) {
    std::ifstream f(path, std::ios::binary);
    if (!f) return {};
    return std::vector<u8>(std::istreambuf_iterator<char>(f), {});
}

std::vector<std::string> split(const char* s) {
    std::vector<std::string> out;
    if (!s) return out;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, ','))
        if (!item.empty()) out.push_back(item);
    return out;
}

u32 env_u32(const char* name, u32 dflt) {
    const char* s = std::getenv(name);
    return s ? static_cast<u32>(std::strtoul(s, nullptr, 0)) : dflt;
}

}  // namespace

TEST_CASE("audit: every hand-written function against its recompiled body (whole register file, all RAM incl. the dead stack)") {
    constexpr std::size_t kCount = sizeof kCases / sizeof kCases[0];
    if (std::getenv("P3FES_AUDIT_LIST")) {
        for (std::size_t i = 0; i < kCount; ++i) std::printf("%zu\t%s\t0x%X\n", i, kCases[i].name, kCases[i].addr);
        return;
    }
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const std::vector<u8> pristine(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
    std::vector<std::pair<std::string, std::vector<u8>>> snapshots;
    for (const std::string& d : split(std::getenv("P3FES_AUDIT_SNAPSHOTS"))) {
        std::vector<u8> bytes = read_file_bytes((std::filesystem::path(elf_path()).parent_path().parent_path() / "_ours" / d / "eeMemory.bin").string());
        if (bytes.size() != EEMemory::kMainRamSize) {
            MESSAGE("snapshot " << d << " missing: skipped");
            continue;
        }
        snapshots.emplace_back(d, std::move(bytes));
    }
    g_trace = std::getenv("P3FES_AUDIT_TRACE") != nullptr;
    const u32 seeds = env_u32("P3FES_AUDIT_SEEDS", 16);
    const u32 snap_seeds = env_u32("P3FES_AUDIT_SNAPSHOT_SEEDS", 4);
    const std::vector<std::string> only = split(std::getenv("P3FES_AUDIT_ONLY"));
    const std::size_t from = env_u32("P3FES_AUDIT_FROM", 0), to = std::min<std::size_t>(env_u32("P3FES_AUDIT_TO", 0xFFFFFFFFu), kCount);
    FILE* out = nullptr;
    if (const char* p = std::getenv("P3FES_AUDIT_OUT")) out = std::fopen(p, "ab");
    std::size_t faithful = 0, differs = 0;
    for (std::size_t idx = from; idx < to; ++idx) {
        const Case& c = kCases[idx];
        if (!only.empty() && std::find(only.begin(), only.end(), std::string(c.name)) == only.end()) continue;
        std::fprintf(stderr, "AUDIT BEGIN %zu %s\n", idx, c.name);
        std::fflush(stderr);
        std::memcpy(m->mem.main_ram(), pristine.data(), pristine.size());
        std::memset(m->mem.scratchpad(), 0, 0x4000);
        const u32 frame = frame_size(*m, c.addr);
        Verdict v;
        u64 clean = 0;  // classes of the pairs where both runs returned
        int stops = 0, bad = 0, pairs = 0;
        auto one = [&](u32 seed, u32 world_seed) {
            std::mt19937 rng{world_seed};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            Verdict pv;
            if (audit_pair(*m, c.hand, c.recomp, args, seed, frame, pv, stops)) clean |= pv.classes;
            if (pv.classes) ++bad;
            for (unsigned k = 0; k < kClassCount; ++k)
                if (pv.classes & (1ull << k)) v.add(static_cast<Class>(k), pv.detail[k] + " [seed " + std::to_string(seed) + "]");
            ++pairs;
        };
        for (u32 seed = 1; seed <= seeds; ++seed) one(seed, seed * 7919u + c.addr);
        for (const auto& [name, bytes] : snapshots) {
            std::memcpy(m->mem.main_ram(), bytes.data(), bytes.size());
            std::memset(m->mem.scratchpad(), 0, 0x4000);
            for (u32 s = 1; s <= snap_seeds; ++s) one(1000 + s, s * 104729u + c.addr);
        }
        std::string classes, details, clean_classes;
        for (unsigned k = 0; k < kClassCount; ++k)
            if (v.classes & (1ull << k)) {
                classes += (classes.empty() ? "" : ",") + std::string(kClassName[k]);
                details += (details.empty() ? "" : " | ") + std::string(kClassName[k]) + ": " + v.detail[k];
                if (clean & (1ull << k)) clean_classes += (clean_classes.empty() ? "" : ",") + std::string(kClassName[k]);
            }
        (v.classes ? differs : faithful) += 1;
        char head[160];
        std::snprintf(head, sizeof head, "%zu\t%s\t0x%X\t%u\t%d\t%d\t%d\t%s\t", idx, c.name, c.addr, frame, pairs, bad, stops,
                      v.classes ? "differs" : "faithful");
        const std::string line = head + (classes.empty() ? std::string("-") : classes) + "\t" +
                                 (clean_classes.empty() ? std::string("-") : clean_classes) + "\t" +
                                 (details.empty() ? std::string("-") : details) + "\n";
        std::fputs(line.c_str(), stdout);
        std::fflush(stdout);
        if (out) {
            std::fputs(line.c_str(), out);
            std::fflush(out);
        }
    }
    if (out) std::fclose(out);
    MESSAGE("audit: " << faithful << " faithful, " << differs << " differ");
    CHECK(differs == 0);
}
