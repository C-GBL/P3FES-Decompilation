// kwlnTask.c: the task kernel every game module runs on (docs/ANALYSIS/10_frame_loop_gs.md section 3,
// 20_menu_ui.md section 2.1), hand-decompiled from SLUS_216.21 (game/src/kwln/task.cpp).
//
// A task is a 0x68-byte H_Malloc record (KwlnTask below). It sits in exactly one of three doubly linked
// lists chosen by the state nibble of +0x1C -- 1 "starting" (waits +0x2C frames), 2 "running" (updated
// every frame), 3 "ending" (waits +0x30 frames, then the destroy callback runs and the record is freed) --
// kept in priority order (unsigned +0x20 ascending, FIFO among equals), and independently in a parent /
// first-child / next-sibling tree (+0x4C/+0x50/+0x54) that only the destroy-with-hierarchy helpers use.
// kwlnTaskMain (once per frame from kwlnUpdate) ages the starting list, runs every running task's update
// callback in list order (kwlnTaskUpdateAll -> kwlnTaskUpdate) and retires the ending list.
//
// Functions bear the names symbols/functions.json gives them: since IDA master update #4 the names of
// symbols/deltas/kwln_task.sym (tge-pr4 hints verified here from the instructions where one exists; our own otherwise).
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"
#include "p3fes_recomp_rt.h"

#include <cstddef>
#include <cstdint>

namespace p3fes::game {

namespace kwln {

// The task record (0x68 bytes, H_Malloc'd by kwlnTaskInit / kwlnTaskInitEx; every field is written there).
struct KwlnTask {
    char name[24];      // +0x00 copied from the creator, [23] forced to 0
    s32 name_sum;       // +0x18 sum of the signed name bytes (kwlnTaskGetTaskByName's quick reject)
    u32 state;          // +0x1C low nibble: 0 dead, 1 starting, 2 running, 3 ending; bit 4 = neutral pads,
                        //       bit 5 = paused; bits 4..27 are the flags kwlnTaskSetFlags* set and clear
    u32 priority;       // +0x20 list order (unsigned); 0x816..0x1CE5 etc. are the pause bands of kwlnTaskUpdate
    u32 unk24;          // +0x24 cleared on start
    u32 timer;          // +0x28 frames run (kwlnTaskGetTimer), cleared on start
    s32 start_wait;     // +0x2C frames in the starting list (0 = start at once)
    s32 end_wait;       // +0x30 frames in the ending list (2 by default)
    u32 update;         // +0x34 update callback(task): 0 keep running, -1 finish, other = next update callback
    u32 destroy;        // +0x38 destroy callback(task), may be 0
    u32 work;           // +0x3C work area (kwlnTaskGet/SetWorkData)
    u32 next;           // +0x40 state list
    u32 prev;           // +0x44 state list
    u32 prev2;          // +0x48 copy of prev written on insertion (never cleared by the unlink)
    u32 parent;         // +0x4C tree
    u32 child;          // +0x50 tree: first child
    u32 sibling;        // +0x54 tree: next sibling
    u32 unk58[4];       // +0x58 zeroed
};
static_assert(sizeof(KwlnTask) == 0x68);
static_assert(offsetof(KwlnTask, state) == 0x1C);
static_assert(offsetof(KwlnTask, work) == 0x3C);
static_assert(offsetof(KwlnTask, sibling) == 0x54);

constexpr u32 kOffName = 0x00, kOffNameSum = 0x18, kOffState = 0x1C, kOffPriority = 0x20, kOff24 = 0x24,
              kOffTimer = 0x28, kOffStartWait = 0x2C, kOffEndWait = 0x30, kOffUpdate = 0x34, kOffDestroy = 0x38,
              kOffWork = 0x3C, kOffNext = 0x40, kOffPrev = 0x44, kOffPrev2 = 0x48, kOffParent = 0x4C,
              kOffChild = 0x50, kOffSibling = 0x54;
constexpr u32 kTaskSize = 0x68;

constexpr u32 kStateMask = 0xFu;
constexpr u32 kStateStarting = 1, kStateRunning = 2, kStateEnding = 3;
constexpr u32 kFlagNeutralPads = 0x10u;  // kwlnTaskUpdate gives the task neutral pads instead of gWorkPads
constexpr u32 kFlagPaused = 0x20u;       // kwlnTaskUpdate skips the task
constexpr u32 kFlagBits = 0x0FFFFFF0u;   // what kwlnTaskSetFlags* may change

// $gp-relative kernel variables (gp = 0x7D2CF0 in retail). One {head, tail, count} triple per state list.
struct ListVars {
    s32 head;
    s32 tail;
    s32 count;
};
constexpr ListVars kStartingList{-0x4C8C, -0x4C88, -0x4C84};  // 0x7CE064
constexpr ListVars kEndingList{-0x4C80, -0x4C7C, -0x4C78};    // 0x7CE070
constexpr ListVars kRunningList{-0x4C74, -0x4C70, -0x4C6C};   // 0x7CE07C
constexpr s32 kGpUpdatingTask = -0x4C68;  // the task whose update callback runs (kwlnTaskGetUpdating)
constexpr s32 kGpPauseBandA = -0x4C64;    // set: priorities 0x833..0x103D are skipped
constexpr s32 kGpPauseBandB = -0x4C60;    // set: priorities 0x1064..0x1CD9 are skipped
constexpr s32 kGpKwlnFlags = -0x4BD0;     // kwlnGetFlags: bit 30/31 skip priorities 0x816..0x1CE5
constexpr u32 kListCountLimit = 10000;    // AddToList asserts count < 10001

constexpr u32 kPads = 0x7E0940u;      // gPads: the two 54-byte pad records the update callbacks read
constexpr u32 kWorkPads = 0x7E09B0u;  // gWorkPads: what H_Pad_Update produced this frame
constexpr u32 kPadsSize = 108;

// Strings of kwlnTask.c (K_Assert / K_Abort / printf arguments).
constexpr u32 kStrStatInvalid = 0x5E4E80u;    // "Process stat Invalid!!"
constexpr u32 kStrSourceFile = 0x5E4E98u;     // "kwlnTask.c"
constexpr u32 kStrStatInvalidNl = 0x5E4EB0u;  // "Process stat Invalid!!\n"
constexpr u32 kStrIdInvalid = 0x5E4F00u;      // "ProcessID invalid!!\n"

// --- register-faithful helpers ------------------------------------------------------------------------------
// The kernel's frames are live on the main thread's stack whenever a task callback runs (the dorm snapshot
// is taken while a draw task waits in RenderWare), and the callbacks' own frames hold the s-registers and
// $ra of these functions. So the hand versions keep the original register discipline at every call: the
// s-registers hold what the original kept there, $ra gets the link value of the original jal/jalr, and the
// prologue's spills are written to the guest stack (Frame) and reloaded by the epilogue. The caller-saved
// registers the original writes ($at, $v0/$v1, $a0..$a3, $t0..$t6) also hold the original's values at every
// call and at the return: game code reads some of them (task.cpp's header comment has the cases).

inline u32 gp(const EEContext& ctx) noexcept { return ee::core::gpr32(ctx, GPR_GP); }
inline u32 gpvar(const EEContext& ctx, s32 off) noexcept { return gp(ctx) + static_cast<u32>(off); }
inline u32 lw(const EEContext& ctx, u32 va) noexcept { return guest::load<u32>(ctx, va); }
inline void sw(EEContext& ctx, u32 va, u32 v) noexcept { guest::store<u32>(ctx, va, v); }
inline u32 reg(const EEContext& ctx, unsigned r) noexcept { return ee::core::gpr32(ctx, r); }
inline u64 reg64(const EEContext& ctx, unsigned r) noexcept { return ee::core::gpr64(ctx, r); }
inline void setreg(EEContext& ctx, unsigned r, u32 v) noexcept { ee::core::set_gpr64(ctx, r, ee::core::sext32(v)); }
inline void setreg64(EEContext& ctx, unsigned r, u64 v) noexcept { ee::core::set_gpr64(ctx, r, v); }

// `jal fn` at `pc` ($ra = pc + 8), or `jalr target` at `pc` through the dispatch table.
inline void jal(EEContext& ctx, u32 pc, rt::Fn fn) {
    rt::jal(ctx, pc);
    fn(ctx);
}
inline void jalr(EEContext& ctx, u32 pc, u32 target) {
    rt::jalr(ctx, GPR_RA, pc);
    rt::lookup_func(target)(ctx);
}

// The prologue `addiu sp, sp, -size; sd ra, off; sq sN, off...` and its epilogue (`ld`/`lq` back from the
// guest stack, `addiu sp, sp, size`) on destruction.
class Frame {
public:
    Frame(EEContext& ctx, u32 size) noexcept : ctx_(ctx), size_(size) { rt::addiu(ctx_, GPR_SP, GPR_SP, -static_cast<s32>(size)); }
    ~Frame() {
        for (unsigned i = 0; i < n_; ++i) {
            if (slot_[i].quad) rt::lq(ctx_, slot_[i].r, GPR_SP, static_cast<s32>(slot_[i].off));
            else rt::ld(ctx_, slot_[i].r, GPR_SP, static_cast<s32>(slot_[i].off));
        }
        rt::addiu(ctx_, GPR_SP, GPR_SP, static_cast<s32>(size_));
    }
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;

    void sd(unsigned r, u32 off) noexcept { save(r, off, false); }
    void sq(unsigned r, u32 off) noexcept { save(r, off, true); }

private:
    void save(unsigned r, u32 off, bool quad) noexcept {
        if (quad) rt::sq(ctx_, r, GPR_SP, static_cast<s32>(off));
        else rt::sd(ctx_, r, GPR_SP, static_cast<s32>(off));
        slot_[n_++] = {r, off, quad};
    }
    struct Slot {
        unsigned r;
        u32 off;
        bool quad;
    };
    EEContext& ctx_;
    u32 size_;
    Slot slot_[10] = {};
    unsigned n_ = 0;
};

}  // namespace kwln

// --- the replaced functions (IDA name now; proposed name; role) ------------------------------------------------
// Pointer arguments the original only used as load/store bases are taken as 32-bit values; arguments it copied
// into s-registers or compared as whole registers are taken as the 64-bit register values (every caller
// produces them with lw/addiu/move, so they are sign-extended 32-bit values). The functions taking only
// EEContext& read their arguments from the registers ($a0..$a3, $t0..$t2) as the original did.

void kwlnTaskRemoveFromList(EEContext& ctx);  // [register ABI] kwlnTaskRemoveFromList: unlink from its state list
void kwlnTaskAddToList(EEContext& ctx);  // [register ABI] kwlnTaskAddToList: insert into its state list by priority
void kwlnTaskUpdate(EEContext& ctx);  // [register ABI] kwlnTaskUpdate: run one task's update callback (0 = it ended)
void kwlnTaskUpdateAll(EEContext& ctx);             // kwlnTaskUpdateAll: the per-frame walk of the running list
void kwlnTaskDestroyHierarchy(EEContext& ctx);  // [register ABI] kwlnTaskDestroyHierarchy: destroy a sibling chain and subtrees
void kwlnTaskDestroy(EEContext& ctx);  // [register ABI] kwlnTaskDestroy: move to the ending list (free at once if end_wait 0)
void kwlnTaskSetFlagsRecursive(EEContext& ctx);  // [register ABI] kwlnTaskSetFlagsRecursive
void kwlnTaskSetFlagsByMode(EEContext& ctx);  // [register ABI] kwlnTaskSetFlagsByMode
u32 kwlnTaskMain(EEContext& ctx);                                         // one frame of the kernel, returns 1
void kwlnTaskCreate(EEContext& ctx);  // (parent, name, prio, update, destroy, work): Init + AddChild
void kwlnTaskCreateWithAutoPriority(EEContext& ctx);      // kwlnTaskCreateWithAutoPriority: same, prio above the ancestors'
void kwlnTaskInit(EEContext& ctx);  // [register ABI] kwlnTaskInit
u64 kwlnTaskInitEx(EEContext& ctx, u64 name, u64 prio, u64 start_wait, u64 end_wait, u64 update, u64 destroy,
               u64 work);             // kwlnTaskInitEx
u64 kwlnTaskDestroyWithHierarchyByName(EEContext& ctx);       // kwlnTaskDestroyWithHierarchyByName(name in $a0)
void kwlnTaskDestroyWithHierarchy(EEContext& ctx);  // [register ABI] kwlnTaskDestroyWithHierarchy (0 = bad id)
u32 kwlnTaskGetState(EEContext& ctx, u64 task);
void kwlnTaskGetTaskByName(EEContext& ctx);  // [register ABI] kwlnTaskGetTaskByName
u32 kwlnTaskGetUpdating(EEContext& ctx);            // kwlnTaskGetUpdating
u32 kwlnTaskExists(EEContext& ctx, u64 task);
void kwlnTaskGetTimer(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
void kwlnTaskSetWorkData(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
void kwlnTaskGetWorkData(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
void kwlnTaskAddChild(EEContext& ctx);  // [register ABI] kwlnTaskAddChild (append as last child)
void kwlnTaskDetachParent(EEContext& ctx);  // [register ABI] kwlnTaskDetachParent
void kwlnTaskDetachAllChildren(EEContext& ctx);  // [register ABI] kwlnTaskDetachAllChildren
void kwlnTaskSetFlags(EEContext& ctx);                         // kwlnTaskSetFlags(task, mask, mode)
void kwlnTaskClearFlags(EEContext& ctx);                         // kwlnTaskClearFlags(task, mask, mode)
u32 kwlnTaskIsBandAEnabled(EEContext& ctx);                          // kwlnTaskIsBandAEnabled: pause word A != 1
void kwlnTaskSetBandBEnabled(EEContext& ctx, u64 enable);             // kwlnTaskSetBandBEnabled: pause word B = (enable != 1)
u32 kwlnTaskIsBandBEnabled(EEContext& ctx);                          // kwlnTaskIsBandBEnabled: pause word B != 1
void kwlnTaskMoveAfter(EEContext& ctx);  // [register ABI] kwlnTaskMoveAfter (running list, takes ref's priority)
void kwlnTaskMoveBefore(EEContext& ctx);  // [register ABI] kwlnTaskMoveBefore
u32 kwlnGetFlags(EEContext& ctx);                          // kwlnGetFlags
void kwlnSetFlags(EEContext& ctx, u64 mask, u64 on);       // kwlnSetFlags

}  // namespace p3fes::game
