// Phase 5 pair tests for the script-VM second wave (game/src/script/script_vm2.cpp): each hand-written
// function and the recompiled body it replaces run on identical guest machines (pair_harness.h: $v0,
// callee-saved registers, virtual cycles, check-point count, the arena and the caller's stack) and must
// also leave the same bytes in every guest region the VM and its callees touch outside the arena (the
// VM's .bss words, the flag array, RpRandom's state, the kwln list heads, the H_Dbprt log ring, low RAM
// for null-pointer stores). The documented rules (docs/ANALYSIS/18_script_vm.md sections 2.1, 2.4, 3) are
// checked on the host independently of both bodies.
//
// scrTraceCode runs generated, well-formed BF programs (every opcode but COMM ids outside this slice,
// with forward-only jumps, CALL/END subroutines, JUMP to a terminal procedure, SWITCH, SYNC/WAIT yields)
// frame by frame until the script ends, through scrTraceCode, scrForceTraceCode and scrScriptProcess.
// Generated programs keep their stack typed: IF, NOT, MINUS and scrOperation leave a slot with a rejected
// tag on the stack, which in a random program desynchronises CALL/END and runs the pc off the program.
// The g_scrTraceFlag == 1 path (H_Dbprt -> vsprintf -> newlib's vfprintf) is not run: nothing in the ELF
// writes the flag (scrTraceCode's `lw` is its only reference), and vfprintf reaches the newlib stdio core.
// scrStartScript2 is driven only into scrStartScript's early K_Abort returns (no procedure / no
// instruction section, start procedure out of range): its success path allocates through H_Malloc, which
// needs the MW heap and DIntr/EIntr syscalls this harness does not have; the arguments scrStartScript got
// are compared through $a3..$t3, which its abort path leaves alone. The real BF files of the disc
// (extracted/DATA/FIELD/SCRIPT beside the ELF) go through scrStartScript2 and scrFindPrcdIdxByName.
#include "pair_harness.h"

#include "p3fes/game/script_vm.h"
#include "p3fes/game/script_vm2.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
#define P3FES_DECL_PAIR(name) \
    void name(EEContext&);    \
    void name##__recomp(EEContext&);
P3FES_DECL_PAIR(fn_scrTraceCode_0035ebf0)
P3FES_DECL_PAIR(fn_scrScriptProcess_0035c270)
P3FES_DECL_PAIR(fn_scrForceTraceCode_0035c250)
P3FES_DECL_PAIR(fn_scrStartScript2_0035b930)
P3FES_DECL_PAIR(fn_sub_35BD20_0035bd20)
P3FES_DECL_PAIR(fn_scrFindPrcdIdxByName_0035c090)
P3FES_DECL_PAIR(fn_scrSetUserData_0035c1a0)
P3FES_DECL_PAIR(fn_sub_35ADD0_0035add0)
P3FES_DECL_PAIR(fn_sub_35ADF0_0035adf0)
P3FES_DECL_PAIR(fn_dds3GetProcessWorkData_0035ae10)
P3FES_DECL_PAIR(fn_sub_35AE30_0035ae30)
P3FES_DECL_PAIR(fn_scrCommand_BIT_CHK_0035aeb0)
P3FES_DECL_PAIR(fn_scrCommand_BIT_ON_0035aef0)
P3FES_DECL_PAIR(fn_scrCommand_BIT_OFF_0035af50)
P3FES_DECL_PAIR(fn_scrCommand_RAND_0035afb0)
P3FES_DECL_PAIR(fn_scrCommand_SYNC_0035b000)
P3FES_DECL_PAIR(fn_scrCommand_WAIT_0035b030)
P3FES_DECL_PAIR(fn_scrCommand_SWITCH_0035b110)
P3FES_DECL_PAIR(fn_sub_35B1B0_0035b1b0)
P3FES_DECL_PAIR(fn_sub_35B1F0_0035b1f0)
P3FES_DECL_PAIR(fn_sub_35B230_0035b230)
P3FES_DECL_PAIR(fn_sub_35B270_0035b270)
P3FES_DECL_PAIR(fn_sub_35B400_0035b400)
P3FES_DECL_PAIR(fn_scrCommand_SCR_EXISTS_0035b440)
P3FES_DECL_PAIR(fn_scrCommand_SCR_GET_TIMER_0035b4a0)
P3FES_DECL_PAIR(fn_sub_35B520_0035b520)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

using namespace p3fes::game;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

// --- the arena layout -----------------------------------------------------------------------------------
constexpr u32 kTask = kArena + 0x000;          // ScrTask (252 bytes)
constexpr u32 kInsns = kArena + 0x100;         // 384 instruction words
constexpr u32 kMaxWords = 0x600 / 4;
constexpr u32 kJumpLabels = kArena + 0x700;    // 24 x 32-byte label records
constexpr u32 kJumpLabelCount = 24;
constexpr u32 kProcLabels = kArena + 0xA00;    // 4 x 32
constexpr u32 kProcLabelCount = 4;
constexpr u32 kDescs = kArena + 0xA80;         // 5 section descriptors (task->sections)
constexpr u32 kLocalInts = kArena + 0xB00;     // 32 s32
constexpr u32 kLocalFloats = kArena + 0xB80;   // 32 f32
constexpr u32 kStrings = kArena + 0xC00;       // 256 bytes
constexpr u32 kProcs = kArena + 0xD00;         // 4 kwln task records, 0x50 apart
constexpr u32 kProcStride = 0x50;
constexpr u32 kRandTable = kArena + 0xE40;     // RpRandom's 55-word table
constexpr u32 kGlobals = kArena + 0x1000;      // g_scrGlobals: ints, floats at +1024
constexpr u32 kScratch = kArena + 0x1800;      // synthetic BF headers, name strings

constexpr u32 kRealBf = 0x01810000u;           // a disc BF file (outside the arena, read only)

// --- guest regions outside the arena ------------------------------------------------------------------
constexpr u32 kVmBss = 0x7CE580u;          // task list, scrOperation scratch, g_scrCurrentTask 0x7CE5A8
constexpr u32 kKwlnHeads = 0x7CE060u;      // kwlnTaskExists' three list heads 0x7CE064 / 0x7CE070 / 0x7CE07C
constexpr u32 kKwlnList0 = 0x7CE064u, kKwlnList1 = 0x7CE07Cu, kKwlnList2 = 0x7CE070u;
constexpr u32 kRandIndex = 0x7CE478u;      // RpRandom: offset of the state block from 0x960070 ($gp - 17784)
constexpr u32 kRandState = 0x960070u;      // { base, p1, p2, end }
constexpr u32 kLogCount = 0x7CDE44u;       // H_Dbprt ring fill (s8, $gp - 20012)
constexpr u32 kLogRing = 0x7E0A30u;        // H_Dbprt ring: 15 x 256 bytes
constexpr u32 kFlags = 0x83A21Cu;          // datSetFlag / datGetFlag bit array
constexpr u32 kPadWords = 0x7E0940u;

struct Region {
    u32 va;
    u32 len;
};
const std::vector<Region>& regions() {
    static const std::vector<Region> r = {
        {kArena, kArenaSize},     {0, 0x200},                  {kVmBss, 0x30},        {kKwlnHeads, 0x20},
        {kRandIndex & ~0xFu, 16}, {kRandState, 16},             {kLogCount & ~0xFu, 16}, {kLogRing, 0xF00},
        {kFlags - 0x100, 0x500},  {scr2::kTraceFlag & ~0xFu, 16}, {scr::kGlobalsPtr & ~0xFu, 16},
    };
    return r;
}

u32 load32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
void store32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void fill_random(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i < len; ++i) m.at(va)[i] = static_cast<u8>(rng());
}
s32 rand_range(std::mt19937& rng, s32 lo, s32 hi) {  // inclusive
    return lo + static_cast<s32>(rng() % static_cast<u32>(hi - lo + 1));
}
u32 fbits(float f) {
    u32 v;
    std::memcpy(&v, &f, 4);
    return v;
}
float bitsf(u32 v) {
    float f;
    std::memcpy(&f, &v, 4);
    return f;
}

// A pair over every region: snapshot, run the hand version, restore, run the recompiled body, compare
// (pair_harness expect_same plus each region and the registers listed in `regs`). Afterwards the
// recompiled run's output is in place, so a sequence of pairs advances the guest state.
struct Pair2 {
    Outcome hand, recomp;
    u64 hand_gpr[32] = {}, recomp_gpr[32] = {};
    bool faulted = false;  // both bodies stopped at the same fault (pair_harness.h fault_of)
};
int g_faulted_pairs = 0;
Pair2 pair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, std::initializer_list<unsigned> regs = {}) {
    std::vector<std::vector<u8>> before, after_hand;
    for (const Region& r : regions()) before.push_back(m.bytes(r.va, r.len));
    Pair2 p;
    const std::string fh = fault_of([&] { p.hand = run(m, hand, args, seed); });
    for (unsigned i = 0; i < 32; ++i) p.hand_gpr[i] = m.ctx.gpr[i].u64[0];
    for (const Region& r : regions()) after_hand.push_back(m.bytes(r.va, r.len));
    std::size_t i = 0;
    for (const Region& r : regions()) std::memcpy(m.at(r.va), before[i++].data(), r.len);
    const std::string fr = fault_of([&] { p.recomp = run(m, recomp, args, seed); });
    for (unsigned k = 0; k < 32; ++k) p.recomp_gpr[k] = m.ctx.gpr[k].u64[0];
    if (!fh.empty() || !fr.empty()) {  // a pointer of the random world the original itself faults on
        INFO(what);
        CHECK(fh == fr);
        ++g_faulted_pairs;
        p.faulted = true;
        return p;
    }
    expect_same(p.hand, p.recomp, what);
    INFO(what);
    i = 0;
    for (const Region& r : regions()) {
        INFO("region 0x" << std::hex << r.va);
        CHECK(after_hand[i++] == m.bytes(r.va, r.len));
    }
    for (unsigned r : regs) {
        INFO("register " << r);
        CHECK(p.hand_gpr[r] == p.recomp_gpr[r]);
    }
    return p;
}

// --- the VM state ---------------------------------------------------------------------------------------
// Random arena, a task wired to the arena's sections, the globals pointer, RpRandom's state, the kwln
// lists (records 0..2 linked into the three lists in random order, record 3 dead), the log ring and the
// trace flag off.
struct Vm {
    bool live[4] = {};
};
Vm seed_vm(Machine& m, std::mt19937& rng) {
    fill_random(m, kArena, kArenaSize, rng);
    fill_random(m, 0, 0x200, rng);
    fill_random(m, kVmBss, 0x30, rng);
    fill_random(m, kLogRing, 0xF00, rng);
    fill_random(m, kFlags - 0x100, 0x500, rng);
    fill_random(m, kPadWords, 0x10, rng);
    store32(m, scr::kGlobalsPtr, kGlobals);
    store32(m, scr2::kTraceFlag, 0);
    store32(m, kLogCount & ~3u, 0);
    m.at(kLogCount)[0] = static_cast<u8>(rng() % 16);
    // RpRandom: state block at 0x960070 + 0, pointers into the arena table.
    store32(m, kRandIndex, 0);
    store32(m, kRandState + 0, kRandTable);
    store32(m, kRandState + 4, kRandTable + 4 * (rng() % 55));
    store32(m, kRandState + 8, kRandTable + 4 * (rng() % 55));
    store32(m, kRandState + 12, kRandTable + 4 * 55);
    // The task.
    const u32 t = kTask;
    store32(m, t + scr::kPc, 0);
    store32(m, t + scr::kSp, 0);
    store32(m, t + offsetof(ScrTask, image), kScratch);
    store32(m, t + scr::kSections, kDescs);
    store32(m, t + scr::kProcLabels, kProcLabels);
    store32(m, t + scr::kJumpLabels, kJumpLabels);
    store32(m, t + scr::kInsn, kInsns);
    store32(m, t + offsetof(ScrTask, message_data), 0);
    store32(m, t + scr::kStrings, kStrings);
    store32(m, t + offsetof(ScrTask, start_proc), 0);
    store32(m, t + scr::kMessageId, 0xFFFFFFFFu);
    store32(m, t + offsetof(ScrTask, frames), 0);
    store32(m, t + scr::kCmdTimer, 0);
    store32(m, t + scr::kLocalInts, kLocalInts);
    store32(m, t + scr::kLocalFloats, kLocalFloats);
    store32(m, t + offsetof(ScrTask, process), kProcs);
    for (u32 i = 0; i < 5; ++i) {
        const u32 d = kDescs + i * 16;
        store32(m, d + 0, i);
        store32(m, d + 4, 32);
        store32(m, d + 8, i == 1 ? kJumpLabelCount : (i == 0 ? kProcLabelCount : 64));
        store32(m, d + 12, 0);
    }
    store32(m, scr::kCurrentTask, kTask);
    // kwln records: +40 timer, +60 work data, +64 next.
    Vm vm;
    u32 heads[3] = {0, 0, 0};
    for (int i = 2; i >= 0; --i) {
        const u32 rec = kProcs + static_cast<u32>(i) * kProcStride;
        const unsigned list = rng() % 3;
        store32(m, rec + 64, heads[list]);
        heads[list] = rec;
        vm.live[i] = true;
    }
    store32(m, kProcs + 3 * kProcStride + 64, 0);
    store32(m, kKwlnList0, heads[0]);
    store32(m, kKwlnList1, heads[1]);
    store32(m, kKwlnList2, heads[2]);
    store32(m, kProcs + 60, kTask);  // record 0 runs the task
    return vm;
}
u32 proc_rec(unsigned i) { return kProcs + i * kProcStride; }

// The COMM argument stack of the task: arg i in slot sp - 1 - i.
void set_args(Machine& m, const std::vector<u32>& args, const std::vector<s8>& tags) {
    const u32 sp = static_cast<u32>(args.size());
    store32(m, kTask + scr::kSp, sp);
    for (u32 i = 0; i < sp; ++i) {
        const u32 slot = sp - 1 - i;
        m.at(kTask + scr::kTags + slot)[0] = static_cast<u8>(tags[i]);
        store32(m, kTask + scr::kValues + slot * 4, args[i]);
    }
}
std::vector<s8> int_tags(std::size_t n) { return std::vector<s8>(n, scr::kTagInt); }
u32 ret_value(const Machine& m) { return load32(m, kTask + scr::kValues + scr::kReturnSlot * 4); }
s8 ret_tag(const Machine& m) { return static_cast<s8>(m.mem.main_ram()[kTask + scr::kTags + scr::kReturnSlot]); }
bool host_flag(const Machine& m, u32 bit) { return ((load32(m, kFlags + (bit >> 5) * 4) >> (bit & 31)) & 1u) != 0; }

// --- the BF program generator -----------------------------------------------------------------------
enum Op : u16 {
    kPUSHI = 0, kPUSHF = 1, kPUSHIX = 2, kPUSHIF = 3, kPUSHREG = 4, kPOPIX = 5, kPOPFX = 6, kPROC = 7, kCOMM = 8,
    kEND = 9, kJUMP = 10, kCALL = 11, kRUN = 12, kGOTO = 13, kADD = 14, kLE = 27, kMINUS = 18, kNOT = 19, kIF = 28,
    kPUSHIS = 29, kPUSHLIX = 30, kPUSHLFX = 31, kPOPLIX = 32, kPOPLFX = 33, kPUSHSTR = 34,
};
u32 word(u16 op, s32 operand) { return static_cast<u32>(op) | (static_cast<u32>(static_cast<u16>(operand)) << 16); }

struct Program {
    std::vector<u32> words;
    std::vector<u32> jump_targets;   // jump label i -> instruction index
    u32 proc_targets[kProcLabelCount] = {};
    int comms = 0, calls = 0, jumps = 0, yields_possible = 0;
};

class Generator {
public:
    explicit Generator(std::mt19937& rng) : rng_(rng) {}

    Program make() {
        Program p;
        prog_ = &p;
        std::vector<std::pair<u32, u32>> refs;  // (label, source word index)
        std::vector<u32> zero_boundaries;
        int depth = 0;
        const int n = rand_range(rng_, 4, 40);
        bool ended = false;
        for (int s = 0; s < n && !ended && p.words.size() < 220; ++s) {
            if (depth == 0) zero_boundaries.push_back(static_cast<u32>(p.words.size()));
            const unsigned k = rng_() % 100;
            if (k < 22 && depth < 8) {
                push(depth);
            } else if (k < 32 && depth >= 1) {
                pop(depth);
            } else if (k < 44 && depth >= 2) {
                emit(word(binop(), rand_range(rng_, -3, 3)));
                --depth;
            } else if (k < 49 && depth >= 1) {
                emit(word((rng_() & 1) ? kMINUS : kNOT, 0));
            } else if (k < 52) {
                emit(word((rng_() % 4) ? kPROC : kRUN, rand_range(rng_, -5, 5)));
            } else if (k < 66 && depth <= 4) {
                comm(depth);
            } else if (k < 72 && depth == 1 && refs.size() < kJumpLabelCount) {
                refs.emplace_back(static_cast<u32>(refs.size()), static_cast<u32>(p.words.size()));
                emit(word(kIF, static_cast<s32>(refs.back().first)));
                --depth;
            } else if (k < 76 && depth == 0 && refs.size() < kJumpLabelCount) {
                refs.emplace_back(static_cast<u32>(refs.size()), static_cast<u32>(p.words.size()));
                emit(word(kGOTO, static_cast<s32>(refs.back().first)));
            } else if (k < 80 && depth == 0 && refs.size() + 7 <= kJumpLabelCount) {
                // SWITCH(sel, l0..l6): seven labels (some -1), the selector last (it is argument 0).
                const u32 src = static_cast<u32>(p.words.size());
                for (int l = 6; l >= 0; --l) {
                    if (rng_() % 4 == 0) {
                        emit(word(kPUSHIS, -1));
                    } else {
                        refs.emplace_back(static_cast<u32>(refs.size()), src);
                        emit(word(kPUSHIS, static_cast<s32>(refs.back().first)));
                    }
                }
                emit(word(kPUSHIS, rand_range(rng_, -1, 6)));
                refs_src_fix(refs, src, static_cast<u32>(p.words.size()));
                emit(word(kCOMM, 15));
                ++p.comms;
            } else if (k < 88 && depth <= 8) {
                emit(word(kCALL, rand_range(rng_, 1, 2)));
                ++p.calls;
            } else if (k < 90 && depth == 0) {
                emit(word(kJUMP, 3));
                ++p.jumps;
                ended = true;
            } else if (depth < 8) {
                push(depth);
            }
        }
        if (!ended) {
            while (depth > 0) pop(depth);
            zero_boundaries.push_back(static_cast<u32>(p.words.size()));
            emit(word(kEND, 0));
        }
        // Forward targets at depth 0 (the final END is one of them unless the program ends in JUMP).
        p.jump_targets.assign(kJumpLabelCount, 0);
        for (auto [label, src] : refs) {
            std::vector<u32> cand;
            for (u32 b : zero_boundaries)
                if (b > src) cand.push_back(b);
            p.jump_targets[label] = cand.empty() ? static_cast<u32>(p.words.size() - 1) : cand[rng_() % cand.size()];
        }
        for (u32 l = static_cast<u32>(refs.size()); l < kJumpLabelCount; ++l) p.jump_targets[l] = static_cast<u32>(p.words.size() - 1);
        // Procedures: 0 = main, 1 and 2 = balanced subroutines ending in END, 3 = the terminal block.
        p.proc_targets[0] = 0;
        for (int sub = 1; sub <= 2; ++sub) {
            p.proc_targets[sub] = static_cast<u32>(p.words.size());
            int d = 0;
            const int len = rand_range(rng_, 0, 8);
            for (int s = 0; s < len; ++s) {
                const unsigned k = rng_() % 10;
                if (k < 4 && d < 5) push(d);
                else if (k < 6 && d >= 1) pop(d);
                else if (k < 8 && d >= 2) { emit(word(binop(), 0)); --d; }
                else if (d <= 2) comm(d);
            }
            while (d > 0) pop(d);
            emit(word(kEND, 0));
        }
        p.proc_targets[3] = static_cast<u32>(p.words.size());
        emit(word(kPUSHIS, rand_range(rng_, -100, 100)));
        emit(word(kPOPLIX, rand_range(rng_, 0, 31)));
        emit(word(kEND, 0));
        return p;
    }

private:
    void emit(u32 w) { prog_->words.push_back(w); }
    // ADD SUB MUL DIV OR AND EQ NEQ S L SE LE (14..17, 20..27; 18/19 are the unary MINUS/NOT).
    u16 binop() {
        static constexpr u16 kBinops[12] = {14, 15, 16, 17, 20, 21, 22, 23, 24, 25, 26, 27};
        return kBinops[rng_() % 12];
    }
    // SWITCH: its label references count from the COMM word (the jump happens there).
    static void refs_src_fix(std::vector<std::pair<u32, u32>>& refs, u32 from, u32 to) {
        for (auto& r : refs)
            if (r.second == from) r.second = to;
    }
    void push(int& depth) {
        switch (rng_() % 9) {
        case 0: emit(word(kPUSHI, 0)); emit(rng_() % 2 ? rng_() : static_cast<u32>(rand_range(rng_, -9, 9))); break;
        case 1: emit(word(kPUSHF, 0)); emit(fbits(static_cast<float>(rand_range(rng_, -1000, 1000)) / 7.0f)); break;
        case 2: emit(word(kPUSHIX, rand_range(rng_, 0, 63))); break;
        case 3: emit(word(kPUSHIF, rand_range(rng_, 0, 63))); break;
        case 4: emit(word(kPUSHREG, 0)); break;
        case 5: emit(word(kPUSHLIX, rand_range(rng_, 0, 31))); break;
        case 6: emit(word(kPUSHLFX, rand_range(rng_, 0, 31))); break;
        case 7:  // a string pointer (tag 5) only ever goes straight into a pop: IF, NOT, MINUS and scrOperation do not pop a
                 // slot whose tag they reject, which would desynchronise the stack of a generated program
            emit(word(kPUSHSTR, rand_range(rng_, 0, 200)));
            emit(word(kPOPLIX, rand_range(rng_, 0, 31)));
            emit(word(kPUSHIS, rand_range(rng_, -40, 40)));
            break;
        default: emit(word(kPUSHIS, rand_range(rng_, -40, 40))); break;
        }
        ++depth;
    }
    void pop(int& depth) {
        static constexpr u16 kPops[4] = {kPOPIX, kPOPFX, kPOPLIX, kPOPLFX};
        const u16 op = kPops[rng_() % 4];
        emit(word(op, (op == kPOPIX || op == kPOPFX) ? rand_range(rng_, 0, 63) : rand_range(rng_, 0, 31)));
        --depth;
    }
    void push_int(s32 v) {
        if (v >= -32768 && v <= 32767 && (rng_() & 1)) {
            emit(word(kPUSHIS, v));
        } else {
            emit(word(kPUSHI, 0));
            emit(static_cast<u32>(v));
        }
    }
    // A COMM of this slice with its arguments pushed first (argument 0 last); the stack is unchanged
    // after it (CodeFunc_Comm drops argc slots once the command is done).
    void comm(int& depth) {
        (void)depth;
        s32 bit = rand_range(rng_, 0, 0x15FF);
        if (bit == 4982) bit = 4981;  // datSetFlag printfs for flag 4982 (no printf in this harness)
        switch (rng_() % 13) {
        case 0: push_int(bit); emit(word(kCOMM, 7)); break;     // BIT_CHK
        case 1: push_int(bit); emit(word(kCOMM, 8)); break;     // BIT_ON
        case 2: push_int(bit); emit(word(kCOMM, 9)); break;     // BIT_OFF
        case 3: push_int(rand_range(rng_, -1, 100)); emit(word(kCOMM, 10)); break;  // RAND
        case 4: emit(word(kCOMM, 11)); ++prog_->yields_possible; break;             // SYNC
        case 5: push_int(rand_range(rng_, -1, 3)); emit(word(kCOMM, 12)); ++prog_->yields_possible; break;  // WAIT
        case 6: push_int(static_cast<s32>(rng_())); emit(word(kCOMM, static_cast<s32>(19 + (rng_() & 1)))); break;
        case 7:
            push_int(rand_range(rng_, -5, 5));
            push_int(rand_range(rng_, -5, 5));
            push_int(rand_range(rng_, -5, 5));
            emit(word(kCOMM, 21));
            break;
        case 8: push_int(rand_range(rng_, 0, 9)); emit(word(kCOMM, 22)); break;
        case 9: push_int(static_cast<s32>(proc_or_dead())); emit(word(kCOMM, 26)); break;  // SCR_EXISTS
        case 10: push_int(static_cast<s32>(proc_or_dead())); emit(word(kCOMM, 27)); break; // SCR_GET_TIMER
        case 11: push_int(static_cast<s32>(dead_proc())); emit(word(kCOMM, 25)); break;    // SCR_KILL_SYNC, gone
        default:
            emit(word(kPUSHF, 0));
            emit(fbits(static_cast<float>(rand_range(rng_, 0, 10000)) / 3.0f));
            emit(word(kCOMM, 46));  // SQRT
            break;
        }
        ++prog_->comms;
    }
    u32 proc_or_dead() { return rng_() % 5 == 0 ? 0u : proc_rec(rng_() % 4); }
    u32 dead_proc() { return rng_() % 2 ? 0u : proc_rec(3); }

    std::mt19937& rng_;
    Program* prog_ = nullptr;
};

void install(Machine& m, const Program& p) {
    REQUIRE(p.words.size() <= kMaxWords);
    for (u32 i = 0; i < p.words.size(); ++i) store32(m, kInsns + i * 4, p.words[i]);
    for (u32 i = 0; i < kJumpLabelCount; ++i) store32(m, kJumpLabels + i * 32 + scr::kLabelInsn, p.jump_targets[i]);
    for (u32 i = 0; i < kProcLabelCount; ++i) store32(m, kProcLabels + i * 32 + scr::kLabelInsn, p.proc_targets[i]);
}

// --- BF headers --------------------------------------------------------------------------------------
struct Desc {
    u32 type, size, count, offset;
};
void write_bf(Machine& m, u32 va, const std::vector<Desc>& descs, s32 count_field, const char magic[4]) {
    std::memcpy(m.at(va + 8), magic, 4);
    store32(m, va + 0x10, static_cast<u32>(count_field));
    for (std::size_t i = 0; i < descs.size(); ++i) {
        const u32 d = va + 0x20 + static_cast<u32>(i) * 16;
        store32(m, d + 0, descs[i].type);
        store32(m, d + 4, descs[i].size);
        store32(m, d + 8, descs[i].count);
        store32(m, d + 12, descs[i].offset);
    }
}
// The host restatement of the resolver (section 0 of the doc): per type the last descriptor wins,
// type 3 only with a non-zero count, any type above 4 stops everything.
struct Resolved {
    bool ok = true;
    u32 proc = 0, jump = 0, insn = 0, messages = 0, strings = 0;
};
Resolved host_resolve(const Machine& m, u32 image) {
    Resolved r;
    const s32 count = static_cast<s32>(load32(m, image + 0x10));
    for (s32 i = 0; i < count; ++i) {
        const u32 d = image + 0x20 + static_cast<u32>(i) * 16;
        const u32 type = load32(m, d), n = load32(m, d + 8), at = image + load32(m, d + 12);
        switch (type) {
        case 0: r.proc = at; break;
        case 1: r.jump = at; break;
        case 2: r.insn = at; break;
        case 3: if (n != 0) r.messages = at; break;
        case 4: r.strings = at; break;
        default: r.ok = false; return r;
        }
    }
    return r;
}

std::vector<u8> read_file(const std::filesystem::path& p) {
    std::ifstream in(p, std::ios::binary);
    if (!in) return {};
    return std::vector<u8>((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
}

}  // namespace

// ------------------------------------------------------------------------------------------------------

TEST_CASE("game(script_vm2): the constants are what the ELF holds") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    CHECK(m.str(scr2::kFileScriptProcess) == "scrScriptProcess.c");
    CHECK(m.str(scr2::kFileCommonCommand) == "scrCommonCommand.c");
    CHECK(m.str(scr2::kFileTraceCode) == "scrTraceCode.c");
    CHECK(m.str(scr2::kMsgInvalidScriptData) == "invalid script data!!\n");
    CHECK(m.str(scr2::kMsgInvalidType) == "scrStartScript2(..) Invalid type!!\n");
    CHECK(m.str(scr2::kMsgErrorScript) == "scrScriptProcess(..) error script!\n");
    CHECK(m.str(scr2::kMsgTrace) == ">>>SCRIPT TRACE <0x%X>\n");
    // sScrOpcodeTbl: the 35 handlers of the doc's table (section 2.2), in BfOpcode order.
    static constexpr u32 kHandlers[35] = {0x35C300, 0x35C450, 0x35C500, 0x35C5B0, 0x35C870, 0x35C900, 0x35CA70,
                                          0x35CF00, 0x35CF20, 0x35D040, 0x35D1D0, 0x35D210, 0x35D2C0, 0x35D310,
                                          0x35DFE0, 0x35E020, 0x35E060, 0x35E0A0, 0x35E0E0, 0x35E250, 0x35E650,
                                          0x35E690, 0x35E6D0, 0x35E710, 0x35E750, 0x35E790, 0x35E7D0, 0x35E810,
                                          0x35E850, 0x35C3B0, 0x35C660, 0x35C710, 0x35CC00, 0x35CD70, 0x35C7C0};
    for (u32 i = 0; i < 35; ++i) CHECK(load32(m, scr2::kOpcodeTable + i * 4) == kHandlers[i]);
    // sScrCommandTable { fn, argc }: the ids of this slice.
    struct Comm {
        u32 id, fn, argc;
    };
    static constexpr Comm kComms[] = {{7, 0x35AEB0, 1},  {8, 0x35AEF0, 1},  {9, 0x35AF50, 1},  {10, 0x35AFB0, 1},
                                      {11, 0x35B000, 0}, {12, 0x35B030, 1}, {15, 0x35B110, 8}, {19, 0x35B1B0, 1},
                                      {20, 0x35B1F0, 1}, {21, 0x35B230, 3}, {22, 0x35B270, 1}, {25, 0x35B400, 1},
                                      {26, 0x35B440, 1}, {27, 0x35B4A0, 1}, {46, 0x35B520, 1}};
    for (const Comm& c : kComms) {
        INFO("COMM " << c.id);
        CHECK(load32(m, 0x7B92B0u + c.id * 8) == c.fn);
        CHECK(load32(m, 0x7B92B0u + c.id * 8 + 4) == c.argc);
    }
    CHECK(load32(m, scr2::kTraceFlag) == 0);  // tracing is off in the retail image
}

TEST_CASE("game(script_vm2): the dds3 accessors and scrSetUserData equal their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x5C2D0001u};
    int found = 0, missing = 0;
    for (int it = 0; it < 1500; ++it) {
        const Vm vm = seed_vm(m, rng);
        const unsigned which = rng() % 6;
        const u32 id = which < 4 ? proc_rec(which) : (which == 4 ? 0u : kArena + (rng() & 0x1FFC));
        const bool live = which < 4 && vm.live[which];
        const u32 seed = rng();
        Pair2 p = pair(m, PAIR(fn_sub_35ADD0_0035add0), Args{sx(id), rng(), rng(), rng()}, seed, "dds3ProcessExists");
        CHECK(p.hand.v0 == (live ? 1u : 0u));
        (live ? found : missing)++;
        p = pair(m, PAIR(fn_sub_35ADF0_0035adf0), Args{sx(id), rng(), rng(), rng()}, seed, "dds3GetProcessTimer");
        CHECK(p.hand.v0 == sx(load32(m, id + 40)));
        p = pair(m, PAIR(fn_dds3GetProcessWorkData_0035ae10), Args{sx(id), rng(), rng(), rng()}, seed, "dds3GetProcessWorkData");
        CHECK(p.hand.v0 == sx(load32(m, id + 60)));
        const u32 work = (rng() % 4) ? kArena + (rng() & 0xF00) : 0u;
        const u64 value = (static_cast<u64>(rng()) << 32) | rng();
        pair(m, PAIR(fn_sub_35AE30_0035ae30), Args{sx(id), value, rng(), rng()}, seed, "dds3SetProcessWorkData");
        CHECK(load32(m, id + 60) == static_cast<u32>(value));
        store32(m, id + 60, work);
        p = pair(m, PAIR(fn_scrSetUserData_0035c1a0), Args{sx(id), value, rng(), rng()}, seed, "scrSetUserData");
        CHECK(load32(m, work + offsetof(ScrTask, user_data)) == static_cast<u32>(value));
        CHECK(p.hand.v0 == sx(work));
    }
    CHECK(found > 500);
    CHECK(missing > 300);
}

TEST_CASE("game(script_vm2): the generic COMM functions equal their recompiled bodies and the documented rules") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x5C2D0002u};
    int jumped = 0, waits_done = 0, sqrt_checked = 0;
    for (int it = 0; it < 1200; ++it) {
        const Vm vm = seed_vm(m, rng);
        const u32 seed = rng();
        const u32 timer = (rng() % 3) ? static_cast<u32>(rand_range(rng, 0, 6)) : rng();
        store32(m, kTask + scr::kCmdTimer, timer);
        // BIT_ON / BIT_CHK / BIT_OFF / BIT_CHK on one flag; now and then a flag outside 0..0x15FF (asserted,
        // still set: the write lands next to the array) but never 4982 (datSetFlag printfs for it).
        u32 bit = static_cast<u32>(rand_range(rng, 0, 0x15FF));
        if (it % 10 == 0) bit = static_cast<u32>(rand_range(rng, 0x1600, 0x17FF));
        if (it % 10 == 5) bit = static_cast<u32>(rand_range(rng, -64, -1));
        if (bit == 4982) bit = 4983;
        const bool in_range = bit < 0x1600u;
        set_args(m, {bit}, int_tags(1));
        pair(m, PAIR(fn_scrCommand_BIT_ON_0035aef0), Args{rng(), rng(), rng(), rng()}, seed, "BIT_ON");
        if (in_range) CHECK(host_flag(m, bit));
        Pair2 p = pair(m, PAIR(fn_scrCommand_BIT_CHK_0035aeb0), Args{rng(), rng(), rng(), rng()}, seed, "BIT_CHK on");
        CHECK(p.hand.v0 == 1);
        if (in_range) CHECK(ret_value(m) != 0);
        CHECK(ret_tag(m) == scr::kTagInt);
        pair(m, PAIR(fn_scrCommand_BIT_OFF_0035af50), Args{rng(), rng(), rng(), rng()}, seed, "BIT_OFF");
        if (in_range) CHECK(!host_flag(m, bit));
        pair(m, PAIR(fn_scrCommand_BIT_CHK_0035aeb0), Args{rng(), rng(), rng(), rng()}, seed, "BIT_CHK off");
        if (in_range) CHECK(ret_value(m) == 0);
        // RAND: remainder of RpRandom() by arg0 + 1 (a zero divisor for arg0 == -1).
        const u32 range_arg = (it % 7 == 0) ? 0xFFFFFFFFu : static_cast<u32>(rand_range(rng, 0, 1000));
        set_args(m, {range_arg}, int_tags(1));
        pair(m, PAIR(fn_scrCommand_RAND_0035afb0), Args{rng(), rng(), rng(), rng()}, seed, "RAND");
        if (range_arg != 0xFFFFFFFFu) CHECK(ret_value(m) <= range_arg);
        // SYNC / WAIT against the command timer.
        p = pair(m, PAIR(fn_scrCommand_SYNC_0035b000), Args{rng(), rng(), rng(), rng()}, seed, "SYNC");
        CHECK(p.hand.v0 == (timer != 0 ? 1u : 0u));
        const s32 wait = (it % 4 == 0) ? rand_range(rng, -3, 0) : rand_range(rng, 1, 8);
        set_args(m, {static_cast<u32>(wait)}, int_tags(1));
        p = pair(m, PAIR(fn_scrCommand_WAIT_0035b030), Args{rng(), rng(), rng(), rng()}, seed, "WAIT");
        const bool done = wait <= 0 || static_cast<s32>(timer) >= wait;
        CHECK(p.hand.v0 == (done ? 1u : 0u));
        waits_done += done ? 1 : 0;
        // SWITCH(sel, l0..l6): selectors outside 0..6 included (7 and 8 read past the arguments).
        std::vector<u32> sw(8);
        sw[0] = static_cast<u32>(rand_range(rng, -3, 8));
        for (int l = 1; l < 8; ++l) sw[l] = static_cast<u32>(rand_range(rng, -2, static_cast<s32>(kJumpLabelCount) + 4));
        set_args(m, sw, int_tags(8));
        const u32 pc_before = load32(m, kTask + scr::kPc);
        p = pair(m, PAIR(fn_scrCommand_SWITCH_0035b110), Args{rng(), rng(), rng(), rng()}, seed, "SWITCH");
        if (!p.faulted) CHECK(p.hand.v0 == 1);  // (selectors 7 / 8 read past the arguments: the original may fault)
        const s32 sel = static_cast<s32>(sw[0]);
        if (sel >= 0 && sel < 7) {
            const s32 label = static_cast<s32>(sw[sel + 1]);
            if (label >= 0) {
                CHECK(load32(m, kTask + scr::kPc) == load32(m, kJumpLabels + static_cast<u32>(label) * 32 + scr::kLabelInsn));
                ++jumped;
            } else {
                CHECK(load32(m, kTask + scr::kPc) == pc_before);
            }
        } else if (sel < 0) {
            CHECK(load32(m, kTask + scr::kPc) == pc_before);
        }
        // The pad words, the no-ops.
        const u32 mask = rng();
        set_args(m, {mask}, int_tags(1));
        pair(m, PAIR(fn_sub_35B1B0_0035b1b0), Args{rng(), rng(), rng(), rng()}, seed, "COMM 19");
        CHECK(ret_value(m) == (mask & (load32(m, scr2::kPadWordA & ~3u) >> 16)));
        pair(m, PAIR(fn_sub_35B1F0_0035b1f0), Args{rng(), rng(), rng(), rng()}, seed, "COMM 20");
        CHECK(ret_value(m) == (mask & (load32(m, scr2::kPadWordB) & 0xFFFFu)));
        set_args(m, {rng(), rng(), rng()}, {scr::kTagInt, scr::kTagFloat, static_cast<s8>(rng() % 6)});
        p = pair(m, PAIR(fn_sub_35B230_0035b230), Args{rng(), rng(), rng(), rng()}, seed, "COMM 21");
        if (!p.faulted) CHECK(p.hand.v0 == 1);  // (a random third tag: the original may fault reading it)
        p = pair(m, PAIR(fn_sub_35B270_0035b270), Args{rng(), rng(), rng(), rng()}, seed, "COMM 22");
        CHECK(p.hand.v0 == 1);
        // The process commands.
        const unsigned which = rng() % 6;
        const u32 id = which < 4 ? proc_rec(which) : (which == 4 ? 0u : rng());
        const bool live = which < 4 && vm.live[which];
        set_args(m, {id}, int_tags(1));
        p = pair(m, PAIR(fn_sub_35B400_0035b400), Args{rng(), rng(), rng(), rng()}, seed, "SCR_KILL_SYNC");
        CHECK(p.hand.v0 == (live ? 0u : 1u));
        pair(m, PAIR(fn_scrCommand_SCR_EXISTS_0035b440), Args{rng(), rng(), rng(), rng()}, seed, "SCR_EXISTS");
        CHECK(ret_value(m) == (live ? 1u : 0u));
        pair(m, PAIR(fn_scrCommand_SCR_GET_TIMER_0035b4a0), Args{rng(), rng(), rng(), rng()}, seed, "SCR_GET_TIMER");
        CHECK(ret_value(m) == (live ? load32(m, id + 40) : 0u));
        // SQRT: float and int arguments, negative ones too.
        const bool as_float = (rng() % 4) != 0;
        const float x = static_cast<float>(rand_range(rng, -100, 100000)) / 9.0f;
        set_args(m, {as_float ? fbits(x) : static_cast<u32>(rand_range(rng, -50, 5000))}, {as_float ? scr::kTagFloat : scr::kTagInt});
        pair(m, PAIR(fn_sub_35B520_0035b520), Args{rng(), rng(), rng(), rng()}, seed, "SQRT");
        CHECK(ret_tag(m) == scr::kTagFloat);
        if (as_float && x > 0.0f) {
            const float got = bitsf(ret_value(m)), want = std::sqrt(x);
            CHECK(std::fabs(got - want) <= want * 1e-6f);
            ++sqrt_checked;
        }
    }
    CHECK(jumped > 300);
    CHECK(waits_done > 200);
    CHECK(sqrt_checked > 500);
}

TEST_CASE("game(script_vm2): scrTraceCode, scrForceTraceCode and scrScriptProcess run generated programs like their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x5C2D0003u};
    int programs = 0, ended = 0, frames_total = 0, comms = 0, calls = 0, jumps = 0, steps = 0;
    for (int it = 0; it < 500; ++it) {
        seed_vm(m, rng);
        Generator gen(rng);
        const Program prog = gen.make();
        install(m, prog);
        m.at(kTask + scr::kTags + scr::kReturnSlot)[0] = static_cast<u8>(rng() % 2);  // PUSHREG pushes a typed slot
        // Locals and globals: mostly small ints and floats, so the operations take every path.
        for (u32 i = 0; i < 32; ++i) store32(m, kLocalInts + i * 4, static_cast<u32>(rand_range(rng, -5, 5)));
        for (u32 i = 0; i < 32; ++i) store32(m, kLocalFloats + i * 4, fbits(static_cast<float>(rand_range(rng, -50, 50)) / 4.0f));
        for (u32 i = 0; i < 64; ++i) store32(m, kGlobals + i * 4, static_cast<u32>(rand_range(rng, -5, 5)));
        for (u32 i = 0; i < 64; ++i) store32(m, kGlobals + 1024 + i * 4, fbits(static_cast<float>(rand_range(rng, -50, 50)) / 4.0f));
        ++programs;
        comms += prog.comms;
        calls += prog.calls;
        jumps += prog.jumps;
        int yields = 0;
        bool done = false;
        for (int frame = 0; frame < 64 && !done; ++frame) {
            const u32 seed = rng();
            const unsigned how = rng() % 3;
            u64 v0;
            if (how == 0) {
                v0 = pair(m, PAIR(fn_scrTraceCode_0035ebf0), Args{sx(kTask), rng(), rng(), rng()}, seed, "scrTraceCode").hand.v0;
                done = v0 == 2;
            } else if (how == 1) {
                v0 = pair(m, PAIR(fn_scrForceTraceCode_0035c250), Args{sx(kTask), rng(), rng(), rng()}, seed, "scrForceTraceCode").hand.v0;
                done = v0 == 2;
            } else {
                v0 = pair(m, PAIR(fn_scrScriptProcess_0035c270), Args{sx(proc_rec(0)), rng(), rng(), rng()}, seed, "scrScriptProcess").hand.v0;
                CHECK((v0 == sx(0xFFFFFFFFu) || v0 == 0));
                done = v0 == sx(0xFFFFFFFFu);
            }
            ++steps;
            if (!done) ++yields;
        }
        // Rules (section 2.1): every yield counted one frame; the end clears the command timer.
        CHECK(static_cast<s32>(load32(m, kTask + offsetof(ScrTask, frames))) == yields);
        if (done) {
            ++ended;
            CHECK(load32(m, kTask + scr::kCmdTimer) == 0);
        }
        frames_total += yields;
    }
    MESSAGE("scrTraceCode: " << programs << " programs, " << ended << " ended, " << steps << " frames run (" << frames_total
                             << " yields), " << comms << " COMMs, " << calls << " CALLs, " << jumps << " JUMPs");
    CHECK(ended > 450);
    CHECK(frames_total > 300);
}

TEST_CASE("game(script_vm2): scrStartScript2 and sub_35BD20 resolve synthetic BF headers like their recompiled bodies") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x5C2D0005u};
    int bad_magic = 0, bad_type = 0, resolved = 0, null_image = 0;
    for (int it = 0; it < 3000; ++it) {
        seed_vm(m, rng);
        const u32 image = kScratch + 0x10 * (rng() % 8);
        const unsigned n = rng() % 8;
        std::vector<Desc> descs;
        const bool want_unknown = it % 9 == 0;
        for (unsigned i = 0; i < n; ++i) {
            u32 type = rng() % 5;
            if (want_unknown && i == n - 1) type = 5 + rng() % 100;
            descs.push_back({type, rng() % 64, (rng() % 3) ? rng() % 40 : 0u, (rng() % 0x2000) & ~3u});
        }
        char magic[4] = {'F', 'L', 'W', '0'};
        if (it % 11 == 0) magic[rng() % 4] ^= static_cast<char>(1 + rng() % 0x7F);
        const s32 count_field = (it % 13 == 0) ? rand_range(rng, -2, 0) : static_cast<s32>(n);
        write_bf(m, image, descs, count_field, magic);
        // Keep scrStartScript on its early returns: no procedure or no instruction section (155), or a start
        // procedure outside 0..desc[0].count-1 (159). Its success path allocates (H_Malloc).
        Resolved r = host_resolve(m, image);
        const bool magic_ok = std::memcmp(magic, "FLW0", 4) == 0;
        u32 start;
        const u32 desc0_count = load32(m, image + 0x20 + 8);
        if (r.proc != 0 && r.insn != 0) {
            start = (rng() & 1) ? static_cast<u32>(rand_range(rng, -50, -1)) : desc0_count + static_cast<u32>(rng() % 5);
        } else {
            start = rng();
        }
        const bool null = it % 97 == 0;
        const u32 arg = null ? 0u : image;
        if (null) {
            r = host_resolve(m, 0);
            ++null_image;
        }
        // Only when scrStartScript is reached do $a2..$t3 carry anything a caller could see: on the abort paths
        // before it the original leaves its type-compare constants (1..4) and a descriptor pointer there.
        const bool reached = !null && magic_ok && r.ok;
        Pair2 p = reached ? pair(m, PAIR(fn_scrStartScript2_0035b930), Args{sx(arg), sx(start), rng(), rng()}, rng(), "scrStartScript2", {6, 7, 8, 9, 10, 11})
                          : pair(m, PAIR(fn_scrStartScript2_0035b930), Args{sx(arg), sx(start), rng(), rng()}, rng(), "scrStartScript2 (abort)");
        CHECK(p.hand.v0 == 0);
        if (!null && !magic_ok) ++bad_magic;
        if (!null && magic_ok && !r.ok) ++bad_type;
        if (reached) {
            ++resolved;
            // scrStartScript's abort paths leave $a3..$t3 as the resolver passed them.
            CHECK(static_cast<u32>(p.hand_gpr[7]) == r.jump);
            CHECK(static_cast<u32>(p.hand_gpr[8]) == r.insn);
            CHECK(static_cast<u32>(p.hand_gpr[9]) == r.messages);
            CHECK(static_cast<u32>(p.hand_gpr[10]) == r.strings);
            CHECK(static_cast<u32>(p.hand_gpr[11]) == start);
            CHECK(static_cast<u32>(p.hand_gpr[6]) == ((r.proc != 0 && r.insn != 0) ? 159u : 155u));
        }
        // sub_35BD20 = scrStartScript2(image, 0): only where start 0 is out of range or a section is missing.
        if (reached && (r.proc == 0 || r.insn == 0 || desc0_count == 0))
            pair(m, PAIR(fn_sub_35BD20_0035bd20), Args{sx(arg), rng(), rng(), rng()}, rng(), "sub_35BD20", {6, 7, 8, 9, 10, 11});
        else if (!reached)
            pair(m, PAIR(fn_sub_35BD20_0035bd20), Args{sx(arg), rng(), rng(), rng()}, rng(), "sub_35BD20 (abort)");
    }
    MESSAGE("scrStartScript2: " << resolved << " resolved, " << bad_magic << " bad magic, " << bad_type << " unknown type, " << null_image
                                << " null image");
    CHECK(resolved > 1500);
    CHECK(bad_magic > 150);
    CHECK(bad_type > 150);
}

TEST_CASE("game(script_vm2): scrFindPrcdIdxByName equals its recompiled body on synthetic headers") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::mt19937 rng{0x5C2D0006u};
    int hits = 0, misses = 0, no_section = 0;
    for (int it = 0; it < 1500; ++it) {
        seed_vm(m, rng);
        const u32 image = kScratch;
        const u32 labels_off = 0x100;
        const u32 count = rng() % 12;
        // Up to eight descriptors; the procedure section is somewhere among them or nowhere, and only the
        // first +0x10 of them are looked at (a count of 0 or a negative one finds nothing).
        const unsigned n = 1 + rng() % 8;
        const int proc_at = (rng() % 4) ? static_cast<int>(rng() % n) : -1;
        std::vector<Desc> descs;
        for (unsigned i = 0; i < n; ++i)
            descs.push_back({static_cast<int>(i) == proc_at ? 0u : 1u + rng() % 6, 32, static_cast<int>(i) == proc_at ? count : rng() % 9, labels_off});
        const s32 count_field = (it % 17 == 0) ? rand_range(rng, -3, -1) : static_cast<s32>(rng() % (n + 1));
        write_bf(m, image, descs, count_field, "FLW0");
        // Names from a small alphabet so that duplicates and prefixes occur.
        std::vector<std::string> names;
        for (u32 j = 0; j < count; ++j) {
            std::string s;
            const int len = rand_range(rng, 0, 5);
            for (int c = 0; c < len; ++c) s.push_back(static_cast<char>('a' + rng() % 3));
            names.push_back(s);
            std::memset(m.at(image + labels_off + j * 32), 0, 24);
            m.put(image + labels_off + j * 32, s);
        }
        std::string query;
        if (count && rng() % 3) {
            query = names[rng() % count];
        } else {
            const int len = rand_range(rng, 0, 6);
            for (int c = 0; c < len; ++c) query.push_back(static_cast<char>('a' + rng() % 3));
        }
        const u32 name_va = kScratch + 0x600;
        m.put(name_va, query);
        const bool null = it % 50 == 0;
        Pair2 p = pair(m, PAIR(fn_scrFindPrcdIdxByName_0035c090), Args{null ? 0u : sx(image), sx(name_va), rng(), rng()}, rng(),
                       "scrFindPrcdIdxByName");
        s32 want = -1;
        if (!null && proc_at >= 0 && proc_at < count_field) {
            for (u32 j = 0; j < count; ++j)
                if (names[j] == query) {
                    want = static_cast<s32>(j);
                    break;
                }
        } else {
            ++no_section;
        }
        CHECK(p.hand.v0 == sx(static_cast<u32>(want)));
        (want >= 0 ? hits : misses)++;
    }
    CHECK(hits > 250);
    CHECK(misses > 300);
    CHECK(no_section > 200);
}

TEST_CASE("game(script_vm2): the disc's BF files through scrStartScript2 and scrFindPrcdIdxByName") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    const std::filesystem::path root = std::filesystem::path(elf_path()).parent_path().parent_path();
    const char* const files[] = {"DATA/FIELD/SCRIPT/FIELD.BF",   "DATA/FIELD/SCRIPT/LMAP.BF",     "DATA/FIELD/SCRIPT/VILLAGE.BF",
                                 "DATA/FIELD/SCRIPT/EVERYDAY.BF", "DATA/FIELD/SCRIPT/FUKA.BF",     "DATA/FIELD/SCRIPT/DUNGEONAT00.BF",
                                 "DATA/FIELD/SCRIPT/YUKARI.BF",   "DATA/SCRIPT/EVENT/E601.BF"};
    std::mt19937 rng{0x5C2D0007u};
    int found = 0, lookups = 0;
    for (const char* rel : files) {
        const std::vector<u8> bf = read_file(root / rel);
        if (bf.empty()) {
            MESSAGE("SKIP: no real BF at " << (root / rel).string());
            continue;
        }
        INFO(rel);
        ++found;
        seed_vm(m, rng);
        REQUIRE(bf.size() < 0x80000);
        fill_random(m, kRealBf, static_cast<u32>(bf.size()) + 64, rng);
        std::memcpy(m.at(kRealBf), bf.data(), bf.size());
        REQUIRE(std::memcmp(bf.data() + 8, "FLW0", 4) == 0);
        const Resolved r = host_resolve(m, kRealBf);
        REQUIRE(r.ok);
        CHECK(r.proc != 0);
        CHECK(r.insn != 0);
        const u32 procs = load32(m, kRealBf + 0x20 + 8);
        // Start procedure out of range (scrStartScript returns 0 at line 159 before allocating).
        for (u32 start : {procs, procs + 3, 0xFFFFFFFFu}) {
            Pair2 p = pair(m, PAIR(fn_scrStartScript2_0035b930), Args{sx(kRealBf), sx(start), rng(), rng()}, rng(), "scrStartScript2 (disc)",
                           {6, 7, 8, 9, 10, 11});
            CHECK(p.hand.v0 == 0);
            CHECK(static_cast<u32>(p.hand_gpr[6]) == 159u);
            CHECK(static_cast<u32>(p.hand_gpr[7]) == r.jump);
            CHECK(static_cast<u32>(p.hand_gpr[8]) == r.insn);
            CHECK(static_cast<u32>(p.hand_gpr[9]) == r.messages);
            CHECK(static_cast<u32>(p.hand_gpr[10]) == r.strings);
        }
        // Every procedure name (by its own label record and by a copy), plus names that are not there.
        const u32 stride = std::max<u32>(1, procs / 120);
        for (u32 j = 0; j < procs; j += stride) {
            const u32 label = r.proc + j * 32;
            const std::string name = m.str(label, 24);
            u32 first = j;
            for (u32 k = 0; k < j; ++k)
                if (m.str(r.proc + k * 32, 24) == name) {
                    first = k;
                    break;
                }
            Pair2 p = pair(m, PAIR(fn_scrFindPrcdIdxByName_0035c090), Args{sx(kRealBf), sx(label), rng(), rng()}, rng(),
                           "scrFindPrcdIdxByName (disc)");
            CHECK(p.hand.v0 == first);
            m.put(kScratch, name + (j % 2 ? "_X" : ""));
            p = pair(m, PAIR(fn_scrFindPrcdIdxByName_0035c090), Args{sx(kRealBf), sx(kScratch), rng(), rng()}, rng(),
                     "scrFindPrcdIdxByName (disc, copy)");
            if (j % 2 == 0) CHECK(p.hand.v0 == first);
            lookups += 2;
        }
    }
    MESSAGE("disc BF: " << found << " files, " << lookups << " procedure lookups");
}

#endif  // P3FES_GAME_HAVE_GENERATED
