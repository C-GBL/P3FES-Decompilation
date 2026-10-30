// Test stand-ins for the callees a pair cannot run for real: the heap (H_Malloc / H_Free, the RenderWare memory
// functions behind the slots 0x960178..0x96018C, newlib malloc / free / calloc / realloc), printf / sprintf, and the
// H_Cdvd file layer (request, update, read-sync, destroy, exists). Opt-in per test: nothing changes for a test that
// does not install a StandIns set.
//
// How it reaches the recompiled code (tests/rt/emit_units.cmake, -DSTAND_INS): in the test library every stub of a
// function the subset does not emit (printf, the H_Cdvd requests, ...) calls stand_in_or_missing(ctx, va) instead of
// rt::missing_function(va), and each function listed in tests/game/CMakeLists.txt `_stand_in_hooks` (the heap entry
// points and sprintf, which other tests run for real) starts with `if (g_stand_ins_active && stand_in_hook(ctx, va))
// return;`. The hand-written body calls the same generated symbol (guest::call / jal) and the recompiled body reaches
// it through its `jal` or through rt::lookup_func (the RW slots), so BOTH bodies of a pair meet the same stand-in.
//
// A replaced function can be stood in (since 2026-10-29): the test build's forwarder asks the stand-ins first. Its
// entry point fn_<name>_<addr8> is a forwarder generated from game/replaced.txt (game/forwarders.cmake, recomp/README.md
// "Forwarders"); the copy compiled into p3fes_game_tests starts with the same check as a hooked generated body. So a
// stand-in serves a callee whether it is still recompiled or hand-written, and replacing a function some test stands in
// leaves that test as it was. The pair runners call the function under test past its own stand-in
// (stand_in_entry.h): a pair still compares the real hand-written body when the set stands in its own address (FakeCd's
// H_Cdvd_* in install_standard, say).
//
// What a stand-in does at a call (StandIns::serve): records the call (address, $ra, $a0..$a3 / $t0..$t3), runs the
// callee's entry check point (rt::check_events: the register file a preemption would save is compared by
// HwCheck::compare_checkpoint_regs), charges its fixed cost, does its work on guest memory, sets $v0 and overwrites
// $at, $v1, $a0..$a3, $t0..$t9 with a pattern unique to the call (a body that relies on a scratch register surviving a
// call fails the pair instead of passing by luck). Its log is part of what a pair compares (run_pair_si).
//
// Guest memory: the heap arena (kStandInHeap, 3 MiB below the main-thread stack) is compared and restored
// like an HwCheck range, so what the bodies write into their blocks is compared too; addresses are deterministic.
// game/README.md "Pair tests with stand-ins" and docs/PHASE5_AGENT_BRIEF.md describe the use.
#pragma once

#include "pair_harness.h"

#include <array>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace p3fes::game_test {

// True while a set is installed (StandInsScope); the test library's hooked entry points test it first.
extern bool g_stand_ins_active;

// --- the call log ----------------------------------------------------------------------------------------------
struct StandInCall {
    u32 va = 0;                   // the function stood in for
    u32 ra = 0;                   // the caller's link
    std::array<u64, 8> args{};    // $a0..$a3, $t0..$t3 (low 64 bits) at the call
    u64 v0 = 0;                   // the result left in $v0
    std::string text;             // printf / sprintf: the formatted text; file layer: the path
    u64 extra = 0;                // heap: the block size; file layer: bytes loaded
    bool operator==(const StandInCall&) const = default;
};

class StandIns;
// A stand-in's work: reads its arguments from `call.args` (or the guest), writes guest memory, sets `call.v0`.
using StandInFn = std::function<void(EEContext&, StandIns&, StandInCall&)>;

class StandIns {
public:
    // Serve `va` with `fn` (replacing any earlier one). `cycles`: charged after the entry check point.
    void install(u32 va, std::string name, StandInFn fn, u64 cycles = 0);
    // A generic recorder: logs the call and returns `v0` (the "records the request" stand-in for any callee).
    void install_recorder(u32 va, std::string name, u64 v0 = 0, u64 cycles = 0);
    // A stop: after the callee's entry check point the run ends as at a callee this build does not emit
    // (rt::missing_function(va): stop_pc = va, the register file at the call). For a test whose checks expect the
    // missing-function stop at a callee that a later slice replaced (the forwarder now asks the stand-ins first).
    void install_stop(u32 va, std::string name);
    bool has(u32 va) const { return table_.count(va) != 0; }
    const std::string& name_of(u32 va) const;

    // Called by the hooks: false when no stand-in serves `va`.
    bool serve(EEContext& ctx, u32 va);

    std::vector<StandInCall> log;
    static constexpr std::size_t kMaxLog = 1u << 20;  // serve() throws past this (a body stuck in a loop of calls)
    std::size_t calls_to(u32 va) const;
    bool clobber_scratch = true;  // the post-call scratch pattern (see the file comment)
    u64 sequence = 0;             // calls served (also the clobber pattern's counter)

private:
    struct Entry {
        std::string name;
        StandInFn fn;
        u64 cycles;
    };
    std::map<u32, Entry> table_;
};

// Installs a set for the scope (one at a time; nesting restores the outer one).
class StandInsScope {
public:
    explicit StandInsScope(StandIns& s);
    ~StandInsScope();
    StandInsScope(const StandInsScope&) = delete;
    StandInsScope& operator=(const StandInsScope&) = delete;

private:
    StandIns* prev_;
};

// --- printf / sprintf -------------------------------------------------------------------------------------------
// The guest's printf family over EE varargs (EABI, the libc's own spills: the arguments after the fixed ones in
// $a1..$a3 / $t0..$t3 in 8-byte units, then the caller's stack from $sp + 0 in 8-byte slots; a double is one 64-bit
// slot holding its bits). Conversions d i u o x X c s p f F e E g G %, flags -+ #0, width / precision (also *),
// lengths h / hh (both short in this newlib), l / ll / q / L / j (the whole 64-bit slot: long is 64 bits), z / t.
// newlib's output for these; tests/game/test_stand_ins.cpp checks it against the
// recompiled sprintf on the same guest arguments.
std::string guest_format(EEContext& ctx, u32 fmt_va, unsigned first_vararg /* register index 0..7 of $a0..$t3 */);

constexpr u32 kPrintf = 0x5225A8u;   // printf(fmt, ...) -> chars written; hand-written since finalB (test_ui2 records it)
constexpr u32 kSprintf = 0x523AC8u;  // sprintf(buf, fmt, ...) -> chars written (the NUL stored)
constexpr u32 kVsprintf = 0x5288C8u; // vsprintf(buf, fmt, va_list)
// printf: records the format pointer (args[0]), the arguments and the formatted text, returns its length.
void install_printf(StandIns& s, u64 cycles = 0);
// sprintf / vsprintf: write the formatted text and its NUL into the guest buffer, return the length.
void install_sprintf(StandIns& s, u64 cycles = 0);

// --- the heap ---------------------------------------------------------------------------------------------------
// The arena: zero in the tests' machine and in every replay snapshot checked (battle_ref_6150, b_5800, dorm_replay_4900,
// dorm_l1_4650, fusion_ref_6300, climb_ref_39820: all zero from 0x1BC0000 up to the main-thread stack at 0x1F60000).
constexpr u32 kStandInHeap = 0x01C00000u;
constexpr u32 kStandInHeapSize = 0x00300000u;

// RenderWare's memory-function slots and what retail keeps in them (every replay snapshot).
constexpr u32 kRwSlots = 0x960178u;  // malloc, free, realloc, calloc, free-list alloc, free-list free
constexpr std::array<u32, 6> kRwSlotFns = {0x104140u, 0x104280u, 0x103F50u, 0x104040u, 0x4C3D10u, 0x4C3EE0u};
constexpr u32 kHMalloc = 0x191AF0u;  // H_Malloc(size) -> 16-aligned block or 0
constexpr u32 kHFree = 0x191A10u;    // H_Free(ptr)

// A deterministic first-fit allocator over a guest arena: blocks rounded to 16 bytes (the retail H_Malloc / RwMalloc
// alignment; larger alignments on request), adjacent free blocks coalesced, no guest-visible header (sizes are kept
// on the host), freshly allocated bytes left as the arena holds them (calloc zeroes). Same calls -> same addresses.
class GuestHeap {
public:
    explicit GuestHeap(u32 base = kStandInHeap, u32 size = kStandInHeapSize);
    u32 alloc(u32 size, u32 align = 16);  // 0 when the arena is exhausted (size 0 -> a 16-byte block)
    bool free(u32 p);                     // false: `p` is not a live block (nothing happens; counted in bad_frees)
    u32 size_of(u32 p) const;             // 0 for a pointer that is not a live block's start
    void reserve(u32 p, u32 size);        // marks [p, p + size) used (a block taken from a snapshot)
    GuestRange range() const { return {base_, size_}; }
    u32 base() const { return base_; }
    const std::map<u32, u32>& live() const { return live_; }
    u32 bad_frees = 0;

    // The stand-ins (each records size / pointer in StandInCall::extra / v0):
    void install_h_malloc(StandIns& s, u64 cycles = 0);  // H_Malloc 0x191AF0, H_Free 0x191A10
    // RwMalloc 0x104140 (size, hint), RwFree 0x104280 (ptr), RwRealloc 0x103F50 (ptr, size, hint), RwCalloc 0x104040
    // (n, size, hint), _rwFreeListAllocReal 0x4C3D10 (freelist, hint: entrySize at +0, alignment at +12) and
    // _rwFreeListFreeReal 0x4C3EE0 (freelist, ptr).
    void install_rw(StandIns& s, u64 cycles = 0);
    void install_libc(StandIns& s, u64 cycles = 0);       // malloc 0x520728, free 0x520748, calloc 0x51E150, realloc 0x522F98
    void install_all(StandIns& s, u64 cycles = 0);

private:
    u32 base_, size_;
    std::map<u32, u32> live_;  // start -> rounded size
    std::map<u32, u32> free_;  // start -> size (coalesced)
};

// Writes the retail RW memory-function pointers into 0x960178..0x96018C (the ELF's .bss holds zeros there; a body
// that calls through them then reaches GuestHeap::install_rw's stand-ins, or the real functions when none is set).
void write_rw_slots(Machine& m);

// Replay snapshots (extracted/_ours/<dir>/eeMemory.bin beside the ELF's tree): the whole 32 MiB, empty when absent.
std::vector<u8> read_snapshot(const char* dir);
// The live blocks of H_Malloc's slot table in a machine holding a snapshot (gp-19620 base, gp-19628 count): {start, size}.
std::vector<std::pair<u32, u32>> h_malloc_blocks(const Machine& m);
// Copies [va, va + len) of a snapshot into the machine (real heap data for a test that wants it).
void copy_from_snapshot(Machine& m, const std::vector<u8>& snap, u32 va, u32 len);

// --- the H_Cdvd file layer ----------------------------------------------------------------------------------------
constexpr u32 kHCdvdRequestFn = 0x100D80u;   // H_Cdvd_Request(path, isArchive) -> node
constexpr u32 kHCdvdDestroyFn = 0x100EC0u;   // H_Cdvd_Destroy(node) -> 1
constexpr u32 kHCdvdUpdateFn = 0x100980u;    // H_Cdvd_Update(): the read pump
constexpr u32 kHCdvdReadSyncFn = 0x1023A0u;  // H_Cdvd_ReadSync(node): pump until loaded
constexpr u32 kHCdvdFileExistsFn = 0x1008B0u;// H_Cdvd_FileExists(path) -> 0 / 1

// The game's request list emulated on guest memory with the retail layout (game/include/p3fes/game/hcdvd.h:
// HCdvdRequest, the list behind sCdvdListHead 0x7E0380, sCdvdCache registration through the hand-written
// H_Cdvd_AddFile): Request dedups by the built path ("VOL:\" + upper-case, '/' -> '\') and bumps the refcount, or
// takes an 868-byte zeroed node from the heap and links it at the tail (state 0); Update loads every state-0 node
// whole from `root` (DATA/, BTL/, BGM/ under extracted/), the data 64-byte aligned in a heap block of
// (sectors << 11) + 64 bytes (+ 320 and 256 zero bytes after the data for an archive), registers it, state 4, and
// applies deferred destroys like the retail Update; ReadSync loads its node; Destroy follows the retail rules
// (deferred while state != 0; the last reference unlinks, frees, clears the cache slots). A file that is not there
// stays in state 0 (the retail layer would retry forever); `load` = false never loads (record only).
class FakeCd {
public:
    explicit FakeCd(GuestHeap& heap, std::string root = {});
    void install(StandIns& s, u64 cycles = 0);
    bool load = true;
    std::string root;            // extracted/ (default: beside the ELF, or $P3FES_EXTRACTED)
    std::vector<u32> nodes;      // every node Request created, in order
    std::vector<std::string> missing;  // host paths that were asked for but not found
    // The host file a guest path maps to ("" when not found).
    std::string host_path(const std::string& guest_path) const;
    // The built path of the retail layer: "VOL:\" + `path` upper-cased with '/' -> '\'.
    static std::string build_path(const std::string& path);

private:
    void update(EEContext& ctx);
    bool load_node(EEContext& ctx, u32 node);
    void release(EEContext& ctx, u32 node);
    GuestHeap& heap_;
};
std::string extracted_root();  // $P3FES_EXTRACTED, else the ELF's grandparent directory (extracted/)

// --- the world of one run, and the pair --------------------------------------------------------------------------
// Everything one run's stand-ins hold. A pair builds two identical worlds with the same setup.
struct StandInWorld {
    StandIns si;
    GuestHeap heap;
    FakeCd cd{heap};
    StandInWorld() = default;
    StandInWorld(const StandInWorld&) = delete;
    StandInWorld& operator=(const StandInWorld&) = delete;
};
using WorldSetup = std::function<void(StandInWorld&)>;
// The usual setup: heap (all entry points), printf and sprintf, the file layer.
void install_standard(StandInWorld& w);

struct SiPair {
    HwPair hw;
    std::unique_ptr<StandInWorld> hand, recomp;
};

// run_pair_hw with a fresh world (`setup`) installed around each body; the heap arena is added to the compared and
// restored ranges; afterwards both call logs, the heaps' live blocks and the file layers' nodes must be equal.
SiPair run_pair_si(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, HwCheck hw,
                   const WorldSetup& setup = install_standard, std::initializer_list<Reset> resets = {});
void expect_same_log(const StandIns& hand, const StandIns& recomp, const char* what);

}  // namespace p3fes::game_test
