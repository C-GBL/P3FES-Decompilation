// Phase 5 slice nm_message: nmlist.c / nmSequence.c / nmCmdList.c and the shared message-window helpers, the band
// 0x3C4430-0x3C7794 of docs/ANALYSIS/27_unmapped_bands.md (queue_bands.txt "slice nm_message"). The nm* helpers are
// live on all three replay routes (battle, dorm, M1).
//
// What is here, by group (the data layouts are read from the instructions; names in brackets are proposals, not
// imported -- symbols/deltas/nm_message.sym):
//
//   [nmlist]  a doubly linked node list and the object that owns one.
//     list header (embedded, 16 bytes): +0 head, +4 tail, +8 cursor, +12 u16 count, +14 s16 flags (bit 1: the cursor
//               ran off an end).
//     node (RwHeapMalloc(24 + payload), sub_3C4430): +0 key (the node itself when none is given), +8 allocation size,
//               +12 prev, +16 next, +20 payload pointer (node + 24, or 0 when there is no payload).
//     list object (RwHeapMalloc(40 + payload), sub_3C44D0): +4 the list header (head +4, tail +8, cursor +12, count
//               +16, flags +18), +20 on-insert callback (obj, node), +24 on-remove callback (obj, node), +28 the
//               remove-filter (obj, node) -> bool, +32 allocation size, +36 payload pointer (obj + 40).
//   [nmSequence] a list object whose payload (+36) holds a second, key-sorted list of pending steps (+16) and the list
//               of finished steps (+32); each step's payload holds a byte-sum key, a 16-byte name, four words, two
//               u16 counters (+44 delay, +46 life) and a flag word (+20: bit 2 queued, bit 3 done). sub_3C5490 is the
//               per-frame update; the step callbacks (+20 / +28 / +32 / +36 of the step's owner payload) are called
//               through jalr.
//   [nmCmdList] the menu / command window (sub_3C58F0): a list object whose rows are its nodes (row payload: +0 / +4
//               screen x / y, +8 a highlight, +12 the row number from 1, +16 colour, +28 the user area) and whose payload
//               is the window state --
//               +0 flag word: bit 0 closed by a close-now request, 1 active, 2 ready for input, 3 idle (no fade
//                  running), 4 decided, 5 cancelled, 6 draw the rows, 7 fading in, 8 fading out, 9 report the decided
//                  row (create flag 0), 10 input held off, 11 horizontal, 12 no draw in the update, 13 / 14 the cursor
//                  moved down / up, 15 / 16 paged down / up, 20 / 21 / 22 the open / close / close-now requests;
//               +4 s16 fade frame, +6 / +8 s16 fade-in / fade-out lengths (5), +10 s16 state (the jump table 0x7BB4C0 of
//               sub_3C69D0), +12 the row spacing, +16 the row counter, +20 / +24 position, +28 alpha, +32 visible rows,
//               +36 / +40 the scroll-bar ratios, +44 the first visible row (a node), the callbacks +48 row draw (x, y,
//               colour, list, row), +52 window draw (x, y, alpha, list), +56 update (list), +60 input (list), +64 row
//               removed (list, row), and +68 the user area. The pad words it reads are documented at sub_3C63F0.
//   [msgwin]  the shared message-window record at 0x95BE90 (returned by sub_3C7D50): +0 the itfMesMng handle (-1 none),
//               +4 u8 busy (1 from a request to the close), +5 u8, +8 the selection default, +12 u8 window type, +13 s8
//               the last selection.
//
// Kept recompiled (called through their generated entry points): the eight functions of the band that reach the
// RenderWare memory functions through 0x960178 / 0x96017C (RwHeapMalloc / RwFree): sub_3C4430, sub_3C44D0,
// sub_3C45F0, sub_3C4650, sub_3C49E0, sub_3C4A90, sub_3C4F30, sub_3C4FC0 -- the brief's heap rule.
//
// Register contract (docs/PHASE5_AGENT_BRIEF.md, waves 6, 7 and 10): every check point can preempt the thread and the
// kernel then saves the whole register file in guest memory, callees spill what they receive and game code reads
// registers a callee left behind. So these bodies are register-faithful: at every check point, every call and every
// return each GPR (128 bits), HI/LO, FPR, ACC and FCR31 holds what the original holds there, and the prologues write
// the original spills (the compiler's 128-bit frame slots included). The bodies work on the guest registers directly
// (the Cpu view below, one named variable per register, as core3.cpp), with the data flow named in comments; the
// per-block virtual time follows the recompiled bodies (ADR-0013).
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"
#include "p3fes_recomp_rt.h"

namespace p3fes::game {

namespace nm::detail {

namespace core = ee::core;

// --- R5900 integer results (32-bit operations sign-extend into the 64-bit register) ----------------------
constexpr u64 sx(u32 v) { return core::sext32(v); }
constexpr u64 si(s32 v) { return static_cast<u64>(static_cast<s64>(v)); }  // a negative immediate
constexpr s64 sgn(u64 v) { return static_cast<s64>(v); }                  // a register as a signed 64-bit value
constexpr u64 addu(u64 a, u64 b) { return core::add32(a, b); }
constexpr u64 addiu(u64 a, s32 i) { return core::add32i(a, i); }
constexpr u64 subu(u64 a, u64 b) { return core::sub32(a, b); }
constexpr u64 lui(u32 i) { return core::lui(i); }
constexpr u64 sll(u64 a, unsigned n) { return core::sll(a, n); }
constexpr u64 dsll32(u64 a, unsigned n) { return core::dsll32(a, n); }
constexpr u64 dsrl32(u64 a, unsigned n) { return core::dsrl32(a, n); }
constexpr u64 dsra32(u64 a, unsigned n) { return core::dsra32(a, n); }
constexpr u64 slt(u64 a, u64 b) { return core::slt(a, b); }
constexpr u64 sltu(u64 a, u64 b) { return core::sltu(a, b); }
constexpr u64 sltiu(u64 a, s32 i) { return core::sltiu(a, i); }
constexpr u32 w(u64 v) { return static_cast<u32>(v); }

// One GPR of the guest context. Reads go through volatile lvalues, and so does virtual time below (the wave-10 lesson
// of render_core3: MSVC 14.44 /O2 kept ctx.cycles in a host register across a call to a small helper that charges, and
// the helper's charges were lost). A volatile access is a compiler barrier under /volatile:ms and keeps every access
// real under clang-cl, so no guest state is cached across a helper or a call.
//
// Guest memory goes through the runtime's own load / store instructions (rt::lw .. rt::sq with $zero as the base and the
// address as the offset), so an access the original would fault on -- unaligned, unmapped -- stops the run the same way,
// and a hardware-window access reaches the bus with its check point. A load is written `reg = lw(address)`: lw() names
// the access and the assignment performs it into that register, as the instruction does.
enum class LoadKind : u8 { lw, lh, lhu, lb, ld };
struct Load {
    u64 addr;
    LoadKind kind;
};
inline s32 off_of(u64 addr) { return static_cast<s32>(static_cast<u32>(addr)); }

struct Gpr {
    EEContext& c;
    const unsigned r;
    operator u64() const noexcept { return static_cast<const volatile u64&>(c.gpr[r].u64[0]); }
    Gpr& operator=(u64 v) noexcept {
        core::set_gpr64(c, r, v);
        return *this;
    }
    Gpr& operator=(const Gpr& o) noexcept { return *this = static_cast<u64>(o); }
    Gpr& operator=(const Load& l) {
        const s32 off = off_of(l.addr);
        switch (l.kind) {
        case LoadKind::lw: rt::lw(c, r, GPR_ZERO, off); break;
        case LoadKind::lh: rt::lh(c, r, GPR_ZERO, off); break;
        case LoadKind::lhu: rt::lhu(c, r, GPR_ZERO, off); break;
        case LoadKind::lb: rt::lb(c, r, GPR_ZERO, off); break;
        case LoadKind::ld: rt::ld(c, r, GPR_ZERO, off); break;
        }
        return *this;
    }
};

// FPR numbers.
enum : unsigned {
    F0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15,
    F16, F17, F18, F19, F20, F21, F22, F23, F24, F25, F26, F27, F28, F29, F30, F31
};

// The guest machine as the bodies see it (src/ui/nm_message.cpp derives the bodies from it).
class Cpu {
public:
    explicit Cpu(EEContext& ctx) noexcept : c(ctx) {}

    EEContext& c;
    Gpr zero{c, 0}, at{c, 1}, v0{c, 2}, v1{c, 3}, a0{c, 4}, a1{c, 5}, a2{c, 6}, a3{c, 7};
    Gpr t0{c, 8}, t1{c, 9}, t2{c, 10}, t3{c, 11}, t4{c, 12}, t5{c, 13}, t6{c, 14}, t7{c, 15};
    Gpr s0{c, 16}, s1{c, 17}, s2{c, 18}, s3{c, 19}, s4{c, 20}, s5{c, 21}, s6{c, 22}, s7{c, 23};
    Gpr t8{c, 24}, t9{c, 25}, gp{c, 28}, sp{c, 29}, fp{c, 30}, ra{c, 31};

    // virtual time (enter / backedge are not noexcept: a check point's fatal event must unwind through the bodies)
    void enter(u64 n) {
        rt::check_events(c);
        charge(n);
    }
    void charge(u64 n) noexcept {
        volatile u64& t = c.cycles;
        t = t + n;
    }
    void backedge() { rt::check_events(c); }

    // loads / stores through the runtime's instructions (addresses are 32-bit; LQ / SQ force a quadword boundary)
    static Load lw(u64 a) noexcept { return {a, LoadKind::lw}; }
    static Load lh(u64 a) noexcept { return {a, LoadKind::lh}; }
    static Load lhu(u64 a) noexcept { return {a, LoadKind::lhu}; }
    static Load lb(u64 a) noexcept { return {a, LoadKind::lb}; }
    static Load ld(u64 a) noexcept { return {a, LoadKind::ld}; }
    void lq(const Gpr& d, u64 a) { rt::lq(c, d.r, GPR_ZERO, off_of(a)); }
    void sw(u64 a, const Gpr& v) { rt::sw(c, v.r, GPR_ZERO, off_of(a)); }
    void sh(u64 a, const Gpr& v) { rt::sh(c, v.r, GPR_ZERO, off_of(a)); }
    void sb(u64 a, const Gpr& v) { rt::sb(c, v.r, GPR_ZERO, off_of(a)); }
    void sd(u64 a, const Gpr& v) { rt::sd(c, v.r, GPR_ZERO, off_of(a)); }
    void sq(u64 a, const Gpr& v) { rt::sq(c, v.r, GPR_ZERO, off_of(a)); }

    // FPU (the runtime's instruction semantics: EE singles, ACC, FCR31 flags)
    void lwc1(unsigned f, u64 a) { rt::lwc1(c, f, GPR_ZERO, off_of(a)); }
    void swc1(unsigned f, u64 a) { rt::swc1(c, f, GPR_ZERO, off_of(a)); }
    void mtc1(const Gpr& g, unsigned f) noexcept { rt::mtc1(c, g.r, f); }
    void mov_s(unsigned d, unsigned s) noexcept { rt::mov_s(c, d, s); }
    void add_s(unsigned d, unsigned s, unsigned t) noexcept { rt::add_s(c, d, s, t); }
    void sub_s(unsigned d, unsigned s, unsigned t) noexcept { rt::sub_s(c, d, s, t); }
    void mul_s(unsigned d, unsigned s, unsigned t) noexcept { rt::mul_s(c, d, s, t); }
    void div_s(unsigned d, unsigned s, unsigned t) noexcept { rt::div_s(c, d, s, t); }
    void sqrt_s(unsigned d, unsigned t) noexcept { rt::sqrt_s(c, d, t); }
    void mula_s(unsigned s, unsigned t) noexcept { rt::mula_s(c, s, t); }
    void madda_s(unsigned s, unsigned t) noexcept { rt::madda_s(c, s, t); }
    void madd_s(unsigned d, unsigned s, unsigned t) noexcept { rt::madd_s(c, d, s, t); }
    void c_lt_s(unsigned s, unsigned t) noexcept { rt::c_lt_s(c, s, t); }
    void c_le_s(unsigned s, unsigned t) noexcept { rt::c_le_s(c, s, t); }
    bool cop1_cond() const noexcept { return rt::cop1_cond(c); }

    // HI/LO (pipe 0)
    void mult(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::mult(c, d.r, s.r, t.r); }
    void div(const Gpr& s, const Gpr& t) noexcept { rt::div(c, s.r, t.r); }
    void mflo(Gpr& d) noexcept { rt::mflo(c, d.r); }

    // calls: `jal fn` at pc ($ra = pc + 8; a delay slot's instruction is written before the call) and `jalr target`
    // at pc (through the dispatch table; $ra = pc + 8)
    void jal(u32 pc, rt::Fn fn) {
        rt::jal(c, pc);
        fn(c);
    }
    void jalr(u32 pc, u32 target) {
        rt::jalr(c, GPR_RA, pc);
        rt::lookup_func(target)(c);
    }

    // the K_Assert(file, line) call of the band (`lui a0, 0x6A; addiu a0, a0, file; li a1, line; jal 0x19D3F0`):
    // `jr $ra` in retail, the failed check continues
    void k_assert(u32 file, u32 line, u32 pc);
    // the prologue / epilogue pair every non-leaf of the band uses: a frame of 16 * (n + 1) bytes, s0..s(n-1) spilled
    // in 128 bits at 16 * i, $ra at 16 * n (`addiu sp, -size; sd ra; sq s(n-1) .. sq s0` / `ld ra; lq ..; addiu sp`)
    void open_frame(unsigned n);
    void close_frame(unsigned n);
};

}  // namespace nm::detail

// K_Assert file arguments.
constexpr u32 kNmListFile = 0x6A3DE8u;      // "nmlist.c"
constexpr u32 kNmSequenceFile = 0x6A3DF8u;  // "nmSequence.c"
constexpr u32 kNmCmdListFile = 0x6A3E08u;   // "nmCmdList.c"
constexpr u32 kMsgWinRecord = 0x95BE90u;    // the shared message-window record (sub_3C7D50)

// --- the public entry points ---------------------------------------------------------------------------------------
// Each function keeps its symbols/functions.json name; the bracketed role is a proposal. They take their guest arguments
// as 64-bit register values ($a0.., then $t0) and return $v0 (for the void ones, $v0 is whatever the original left).
// The recompiled program's entry points (`fn_<name>_<addr8>`) are defined in src/ui/nm_message.cpp.

// [nmlist]
u64 nmListInsertAfter(EEContext& ctx, u64 list, u64 after, u64 node);   // [nmListInsertAfter]: after == 0 inserts at the head
u64 nmListUnlink(EEContext& ctx, u64 list, u64 node);              // [nmListUnlink]: returns the node after (or before)
u64 nmListAppendNew(EEContext& ctx, u64 obj, u64 key, u64 size);      // [nmListAppendNew]: node of `size` payload at the tail
u64 nmListFindByKey(EEContext& ctx, u64 obj, u64 list, u64 key);      // [nmListFindByKey] (node +0)
u64 nmListFindByWord4(EEContext& ctx, u64 obj, u64 list, u64 value);    // [nmListFindByWord4] (node +4)
u64 nmListCursorNext(EEContext& ctx, u64 obj, u64 list);               // [nmListCursorNext]: stops at the tail (flag bit 1)
u64 nmListCursorPrev(EEContext& ctx, u64 obj, u64 list);               // [nmListCursorPrev]: stops at the head
u64 nmListCursorClearEnd(EEContext& ctx, u64 obj, u64 list);               // [nmListCursorClearEnd]
u64 sub_3C4DE0(EEContext& ctx, u64 obj, u64 list, u64 node);     // [nmListCursorSet]: returns 0
u64 nmListCursorSeek(EEContext& ctx, u64 obj, u64 list, u64 index);    // [nmListCursorSeek]: index -1 = the tail
u64 nmListCursorHead(EEContext& ctx, u64 obj, u64 list);               // [nmListCursorHead]
u64 sub_3C4E60(EEContext& ctx, u64 obj, u64 list);               // [nmListCursorTail]
u64 nmListRemoveFiltered(EEContext& ctx, u64 obj);                         // [nmListRemoveFiltered]: frees every node the filter picks
u64 nmByteSum(EEContext& ctx, u64 str);                         // [nmByteSum]: the signed byte sum of a C string
u64 nmListRebuild(EEContext& ctx, u64 obj, u64 nodes, u64 count);   // [nmListRebuild]: relinks an array of nodes in order
// [nmSequence]
u64 nmSeqNullStep(EEContext& ctx);                                  // [nmSeqNullStep]: returns 0
u64 nmSequenceCreate(EEContext& ctx, u64 func, u64 size);              // [nmSequenceCreate]
u64 sub_3C5210(EEContext& ctx);                                  // [nmSeqDefaultFunc]: returns 0
u64 nmSequenceDestroy(EEContext& ctx, u64 obj);                         // [nmSequenceDestroy]: tail of sub_3C45F0
u64 nmSequenceAddStep(EEContext& ctx, u64 obj, u64 key, u64 desc, u64 delay, u64 life);  // [nmSequenceAddStep]
u64 sub_3C53E0(EEContext& ctx, u64 list, u64 key, u64 node);     // [nmListInsertSorted] (by node +0, ascending)
u64 nmObjPayloadWord12(EEContext& ctx, u64 obj);                         // [nmObjPayloadWord12]
u64 sub_3C5470(EEContext& ctx, u64 node);                        // [nmNodePayloadWord40]
u64 nmNodePayloadArea40(EEContext& ctx, u64 node);                        // [nmNodePayloadArea40]
u64 sub_3C5490(EEContext& ctx, u64 obj);                         // [nmSequenceUpdate]
u64 nmSequenceCallAll36(EEContext& ctx, u64 obj);                         // [nmSequenceCallAll36]
u64 sub_3C57E0(EEContext& ctx, u64 obj, u64 node);               // [nmSeqStepOnInsert]: step owner +24
u64 nmSeqStepOnRemove(EEContext& ctx, u64 obj, u64 node);               // [nmSeqStepOnRemove]: step owner +28
u64 nmSeqStepRun(EEContext& ctx, u64 obj, u64 node);               // [nmSeqStepRun]: step owner +32, returns its result
u64 nmSeqStepCall36(EEContext& ctx, u64 obj, u64 node);               // [nmSeqStepCall36]: step owner +36
u64 nullsub_56(EEContext& ctx);
u64 nullsub_57(EEContext& ctx);
u64 nullsub_54(EEContext& ctx);
u64 nullsub_55(EEContext& ctx);
u64 nullsub_58(EEContext& ctx);
// [nmCmdList]
u64 sub_3C58F0(EEContext& ctx, u64 flags, u64 size, u64 rows, u64 spacing);  // [nmCmdListCreate]
u64 nmCmdListDestroy(EEContext& ctx, u64 obj);                         // [nmCmdListDestroy]: tail of sub_3C45F0
u64 nmCmdListAddRow(EEContext& ctx, u64 obj, u64 key, u64 size, u64 name);  // [nmCmdListAddRow]
u64 sub_3C5AF0(EEContext& ctx, u64 obj);                         // [nmCmdListCursorUp]: scrolls the first visible row
u64 nmCmdListCursorDown(EEContext& ctx, u64 obj);                         // [nmCmdListCursorDown]
u64 sub_3C5C50(EEContext& ctx, u64 obj);                         // [nmCmdListPageDown]
u64 nmCmdListSelect(EEContext& ctx, u64 obj, u64 node, u64 line);     // [nmCmdListSelect]: puts `node` on screen line `line`
u64 nmCmdListSetDrawFunc(EEContext& ctx, u64 obj, u64 func);               // [nmCmdListSetDrawFunc] (+52)
u64 nmCmdListSetUpdateFunc(EEContext& ctx, u64 obj, u64 func);               // [nmCmdListSetUpdateFunc] (+56)
u64 nmCmdListSetRowDrawFunc(EEContext& ctx, u64 obj, u64 func);               // [nmCmdListSetRowDrawFunc] (+48)
u64 nmCmdListSetRowRemoveFunc(EEContext& ctx, u64 obj, u64 func);               // [nmCmdListSetRowRemoveFunc] (+64)
u64 nmCmdListRemoveRow(EEContext& ctx, u64 obj, u64 node);               // [nmCmdListRemoveRow]: renumbers the rows after it
u64 nmCmdListOnInsert(EEContext& ctx, u64 obj, u64 node);               // [nmCmdListOnInsert]: numbers the new row
u64 nmCmdListOnRemove(EEContext& ctx, u64 obj, u64 node);               // [nmCmdListOnRemove]: payload +64
u64 nmCmdListDrawRow(EEContext& ctx, u64 obj, u64 node);               // [nmCmdListDrawRow]: the row's position and colour
u64 nmCmdListUpdate(EEContext& ctx, u64 obj);                         // [nmCmdListUpdate]: the per-frame update, returns the result
u64 nmCmdListDraw(EEContext& ctx, u64 obj);                         // [nmCmdListDraw]
u64 sub_3C63F0(EEContext& ctx, u64 obj);                         // [nmCmdListInput]: the pad handling (0x7E094C..0x7E095A)
u64 nmCmdListStartFade(EEContext& ctx, u64 obj);                         // [nmCmdListStartFade]
u64 sub_3C69D0(EEContext& ctx, u64 obj);                         // [nmCmdListFadeStep]: the state machine (table 0x7BB4C0)
u64 nmCmdListScrollBar(EEContext& ctx, u64 obj);                         // [nmCmdListScrollBar]: the two 16.16 ratios at +36 / +40
u64 nmCmdListDecidedRow(EEContext& ctx, u64 obj);                         // [nmCmdListDecidedRow]: the cursor when bit 4
u64 nmCmdListCancelled(EEContext& ctx, u64 obj);                         // [nmCmdListCancelled]: bit 5
u64 nmCmdListPagedDown(EEContext& ctx, u64 obj);                         // [nmCmdListPagedDown]: bit 15
u64 nmCmdListMovedUp(EEContext& ctx, u64 obj);                         // [nmCmdListMovedUp]: bit 16
u64 nmCmdListMovedDownRow(EEContext& ctx, u64 obj);                         // [nmCmdListMovedDownRow]: the cursor when bit 13
u64 nmCmdListScrolledRow(EEContext& ctx, u64 obj);                         // [nmCmdListScrolledRow]: the cursor when bit 14
u64 nmCmdListSetPosition(EEContext& ctx, u64 obj, u64 x, u64 y);           // [nmCmdListSetPosition]
u64 sub_3C6D60(EEContext& ctx, u64 obj, u64 flags);              // [nmCmdListSetFlags]: returns 0
u64 nmCmdListStatus(EEContext& ctx, u64 obj);                         // [nmCmdListStatus]: the packed status word
u64 nmCmdListStatus28(EEContext& ctx, u64 obj);                         // [nmCmdListStatus28]: the same, low 28 bits only
u64 nmCmdListHold(EEContext& ctx, u64 obj);                         // [nmCmdListHold]: bit 10
u64 nmCmdListRelease(EEContext& ctx, u64 obj);                         // [nmCmdListRelease]
u64 sub_3C6EE0(EEContext& ctx, u64 obj);                         // [nmCmdListOpen]: bit 20 unless active
u64 nmCmdListClose(EEContext& ctx, u64 obj);                         // [nmCmdListClose]: bit 21 when active and not closing
u64 nmCmdListCloseNow(EEContext& ctx, u64 obj);                         // [nmCmdListCloseNow]: bits 22 and 21
u64 nmCmdListVisibleRows(EEContext& ctx, u64 obj);                         // [nmCmdListVisibleRows]: min(rows, count)
u64 nmCmdListCursorLine(EEContext& ctx, u64 obj);                         // [nmCmdListCursorLine]: the cursor's screen line
u64 nmCmdListSort(EEContext& ctx, u64 obj, u64 compare);            // [nmCmdListSort]: qsort, renumber, scroll to the top
u64 sub_3C7070(EEContext& ctx, u64 out, u64 q0, u64 q1);         // [quaternion slerp]: t in $f12
// [msgwin]
u64 msgWinReset(EEContext& ctx);                                  // [msgWinReset]: resets the record 0x95BE90
u64 msgWinRecordInit(EEContext& ctx, u64 rec);                         // [msgWinRecordInit]
u64 sub_3C72D0(EEContext& ctx, u64 bmd);                         // [msgWinOpen]: binds a BMD unless a handle exists
u64 msgWinSetStateFlags(EEContext& ctx, u64 flags);                       // [msgWinSetStateFlags]
u64 sub_3C73E0(EEContext& ctx, u64 flags);                       // [msgWinClearStateFlags]
u64 msgWinRequestMessage(EEContext& ctx, u64 message);                     // [msgWinRequestMessage]
u64 sub_3C74E0(EEContext& ctx, u64 selection);                   // [msgWinRequestSelection]
u64 msgWinSetType(EEContext& ctx, u64 type);                        // [msgWinSetType] (+12)
u64 msgWinGetSelection(EEContext& ctx);                                  // [msgWinGetSelection]: -1 without a handle
u64 msgWinLastSelection(EEContext& ctx);                                  // [msgWinLastSelection] (+13)
u64 msgWinClose(EEContext& ctx, u64 close_panel);                 // [msgWinClose]
u64 sub_3C7700(EEContext& ctx);                                  // [msgWinCloseAll]

}  // namespace p3fes::game
