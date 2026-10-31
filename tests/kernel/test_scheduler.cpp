// Scheduler and semaphores: docs/ANALYSIS/15 §3-4 and §8 H-08..H-17; the idle rule (ADR-0013 §2); the
// fiber lifecycle regressions (docs/testing.md "lifecycle regressions" style: create/exit/restart, exit
// with delete, deleting a sleeping thread, terminate from another thread and from an interrupt handler
// while the victim's fiber hosts the idle loop, shutdown with threads mid-sleep, stop-and-destroy).
#include "kernel_test_util.h"

#include <string>

using namespace kt;

namespace {

std::vector<std::string> L;
s64 g_tid[8] = {};
s64 g_val[8] = {};
void lg(const std::string& s) { L.push_back(s); }
void ei(EEContext& c) { c.cop0[12] |= 1u << 16; }
s64 self(EEContext& c) { return sys(c, kGetThreadId); }

constexpr u32 kTA = 0x00400000u, kTB = 0x00400100u, kTC = 0x00400200u;
constexpr u32 kH = 0x00401000u;
constexpr u32 kRoot = 0x00100220u;  // crt0 root_func: ExitThread
constexpr u32 kStack = 0x01000000u;
constexpr u32 kSemaInfo = 0x00230000u, kThInfo = 0x00230100u;

void register_root() {
    register_fn(kRoot, [](EEContext& c) {
        sys(c, kExitThread);
        CHECK(false);  // ExitThread never returns
    });
}

RunResult run_main(Rig& r, GuestFn f) {
    const RunResult res = r.k->run(f);
    CHECK_MESSAGE(r.fatals.empty(), (r.fatals.empty() ? std::string() : r.fatals.front()));
    return res;
}

u64 vblank_cycle(u64 k) { return (k * 24600576ull + 4) / 5; }

} // namespace

TEST_CASE("H-08/H-09/H-10: strict priority, FIFO per level, immediate preemption, same-priority yield, rotate") {
    L.clear();
    register_fn(kTA, [](EEContext& c) {
        lg("A");
        sys(c, kSleepThread);
        lg("A-woke");
    });
    register_fn(kTB, [](EEContext& c) {
        lg("B");
        CHECK(sys(c, kChangeThreadPriority, 0, 10) == 10);  // same priority: yield to C
        lg("B-end");
    });
    register_fn(kTC, [](EEContext& c) {
        lg("C");
        sys(c, kChangeThreadPriority, 0, 10);
        lg("C-end");
    });
    Rig r;
    const RunResult res = run_main(r, [](EEContext& c) {
        CHECK(self(c) == 1);
        CHECK(sys(c, kChangeThreadPriority, 0, 10) == 0);  // main starts at priority 0 (H-15)
        g_tid[0] = create_thread(c, kTA, 5, kStack, 0x1000, 0, 0);
        g_tid[1] = create_thread(c, kTB, 10, kStack + 0x10000, 0x1000, 0, 1);
        g_tid[2] = create_thread(c, kTC, 10, kStack + 0x20000, 0x1000, 0, 2);
        CHECK(g_tid[0] == 2);  // ids from the FIFO free list
        CHECK(g_tid[1] == 3);
        CHECK(g_tid[2] == 4);
        CHECK(sys(c, kStartThread, g_tid[0], 0) == g_tid[0]);  // higher priority: runs at once
        lg("m1");
        sys(c, kStartThread, g_tid[1], 0);  // same priority: queued behind main
        sys(c, kStartThread, g_tid[2], 0);
        lg("m2");
        CHECK(sys(c, kChangeThreadPriority, 0, 10) == 10);  // yield: B, then C
        lg("m3");
        CHECK(sys(c, kRotateThreadReadyQueue, 10) == 10);  // main is the head: rotate = yield
        lg("m4");
        CHECK(sys(c, kRotateThreadReadyQueue, 128) == -1);
        CHECK(sys(c, kChangeThreadPriority, 0, 128) == -1);
        CHECK(sys(c, kWakeupThread, g_tid[0]) == g_tid[0]);  // A (prio 5) preempts
        lg("m5");
    });
    CHECK(res.status == RunStatus::MainExited);
    CHECK(L == std::vector<std::string>{"A", "m1", "m2", "B", "C", "m3", "B-end", "C-end", "m4", "A-woke", "m5"});
}

TEST_CASE("H-10: ChangeThreadPriority returns the old priority, rejects DORMANT, lowering below a ready thread switches") {
    L.clear();
    register_fn(kTA, [](EEContext& c) {
        lg("T");
        CHECK(sys(c, kChangeThreadPriority, 0, 30) == 10);  // below main (20): main runs at once
        lg("T2");
        ThreadView v = g_rig->k->thread(static_cast<int>(self(c)));
        CHECK(v.priority == 1);
        CHECK(v.init_priority == 10);
    });
    Rig r;
    run_main(r, [](EEContext& c) {
        sys(c, kChangeThreadPriority, 0, 20);
        g_tid[0] = create_thread(c, kTA, 10, kStack);
        CHECK(sys(c, kChangeThreadPriority, g_tid[0], 5) == -1);  // DORMANT
        CHECK(sys(c, kChangeThreadPriority, 77, 5) == -1);        // free tid
        sys(c, kStartThread, g_tid[0], 0);
        lg("m");
        CHECK(g_rig->k->thread(static_cast<int>(g_tid[0])).status == 2);  // READY at 30
        CHECK(sys(c, kChangeThreadPriority, g_tid[0], 1) == 30);         // above main: switches
        lg("m-end");
    });
    CHECK(L == std::vector<std::string>{"T", "m", "T2", "m-end"});
}

TEST_CASE("H-11: wakeup counts are unbounded, SleepThread consumes one, waking the RUN thread is lost") {
    L.clear();
    register_fn(kTA, [](EEContext& c) {
        const s64 me = self(c);
        CHECK(sys(c, kSleepThread) == me);  // consumes pending wakeup 1
        CHECK(sys(c, kSleepThread) == me);  // consumes pending wakeup 2
        lg("T-consumed");
        CHECK(sys(c, -0x34 /*iWakeupThread from thread context*/, 1) == 1);  // main READY, no preemption
        lg("T-after-i");
        CHECK(sys(c, kSleepThread) == me);  // blocks; main runs
        lg("T-woke");
    });
    Rig r;
    run_main(r, [](EEContext& c) {
        sys(c, kChangeThreadPriority, 0, 10);
        g_tid[0] = create_thread(c, kTA, 20, kStack);
        sys(c, kStartThread, g_tid[0], 0);  // lower priority: does not run yet
        for (int i = 0; i < 3; ++i) CHECK(sys(c, kWakeupThread, g_tid[0]) == g_tid[0]);  // READY -> count
        CHECK(g_rig->k->thread(static_cast<int>(g_tid[0])).wakeup_count == 3);
        CHECK(sys(c, kCancelWakeupThread, g_tid[0]) == 3);
        CHECK(sys(c, kCancelWakeupThread, g_tid[0]) == 0);
        for (int i = 0; i < 2; ++i) sys(c, kWakeupThread, g_tid[0]);
        CHECK(sys(c, kWakeupThread, 0) == -1);  // self (RUN): lost
        CHECK(sys(c, kWakeupThread, 1) == -1);
        CHECK(g_rig->k->thread(1).wakeup_count == 0);
        CHECK(sys(c, kWakeupThread, 200) == -1);  // free
        lg("m-sleep");
        CHECK(sys(c, kSleepThread) == 1);  // T runs, consumes 2, i-wakes main, sleeps
        lg("m-woke");
        const ThreadView v = g_rig->k->thread(static_cast<int>(g_tid[0]));
        CHECK(v.status == 4);
        CHECK(v.wait_type == 1);
        CHECK(sys(c, kReferThreadStatus, g_tid[0], kThInfo) == 4);
        CHECK(g_rig->r32(kThInfo + 0) == 4);
        CHECK(g_rig->r32(kThInfo + 4) == kTA);
        CHECK(g_rig->r32(kThInfo + 8) == kStack);
        CHECK(g_rig->r32(kThInfo + 0x14) == 20);
        CHECK(g_rig->r32(kThInfo + 0x18) == 20);
        CHECK(g_rig->r32(kThInfo + 0x24) == 1);  // waitType sleep
        CHECK(g_rig->r32(kThInfo + 0x2C) == 0);  // wakeupCount
        CHECK(sys(c, kReferThreadStatus, 0, 0) == 1);  // self, info NULL: status only
        CHECK(sys(c, kWakeupThread, g_tid[0]) == g_tid[0]);  // T (prio 20) READY, main keeps running
        lg("m-end");
    });
    CHECK(L == std::vector<std::string>{"m-sleep", "T-consumed", "T-after-i", "m-woke", "m-end"});
}

TEST_CASE("H-09/H-11: iWakeupThread from a handler preempts at interrupt exit; waking the interrupted thread is lost") {
    L.clear();
    register_fn(kTA, [](EEContext& c) {
        for (;;) {
            sys(c, kSleepThread);
            lg("T@" + std::to_string(g_rig->k->time().vblanks));
        }
    });
    register_fn(kH, [](EEContext& c) {
        const u64 v = g_rig->k->time().vblanks;
        if (v == 1) g_val[0] = sys(c, -0x34, g_tid[0]);  // a higher-priority sleeper: flag a reschedule
        if (v == 2) g_val[1] = sys(c, -0x34, 1);         // the interrupted (RUN) main thread: -1, lost
        set_reg(c, GPR_V0, 0);
    });
    Rig r;
    run_main(r, [](EEContext& c) {
        sys(c, kChangeThreadPriority, 0, 20);
        g_tid[0] = create_thread(c, kTA, 10, kStack);
        sys(c, kStartThread, g_tid[0], 0);  // runs, sleeps
        sys(c, kAddIntcHandler, 2, kH, 0, 0);
        sys(c, kEnableIntc, 2);
        ei(c);
        while (g_rig->k->time().vblanks < 1) work(c, 10'000);
        lg("m@1");  // T ran inside the check point that delivered vblank 1, before this line
        while (g_rig->k->time().vblanks < 2) work(c, 10'000);
        CHECK(g_rig->k->thread(1).wakeup_count == 0);
        lg("m@2");
    });
    CHECK(g_val[0] == g_tid[0]);
    CHECK(g_val[1] == -1);
    CHECK(L == std::vector<std::string>{"T@1", "m@1", "m@2"});
}

TEST_CASE("H-16: semaphores - FIFO waiters regardless of priority/attr, no max clamp, WaitSema -1 on delete") {
    L.clear();
    auto waiter = [](EEContext& c) {
        // s32: a released wait returns $v0 = 0x00000000FFFFFFFF (`sw -1` into the context frame, BIOS 0x80003A58).
        const s32 r = static_cast<s32>(sys(c, kWaitSema, g_val[0]));
        lg(std::to_string(self(c)) + ":" + std::to_string(r));
    };
    register_fn(kTA, waiter);
    register_fn(kTB, waiter);
    register_fn(kTC, waiter);
    Rig r;
    run_main(r, [](EEContext& c) {
        sys(c, kChangeThreadPriority, 0, 30);
        g_val[0] = create_sema(c, 0, 1, /*attr: priority order*/ 1);
        CHECK(g_val[0] == 0);  // ids start at 0
        g_tid[0] = create_thread(c, kTA, 20, kStack, 0x1000, 0, 0);
        g_tid[1] = create_thread(c, kTB, 10, kStack + 0x10000, 0x1000, 0, 1);
        g_tid[2] = create_thread(c, kTC, 15, kStack + 0x20000, 0x1000, 0, 2);
        for (int i = 0; i < 3; ++i) sys(c, kStartThread, g_tid[i], 0);  // each runs and blocks: FIFO A, B, C
        CHECK(sys(c, kReferSemaStatus, g_val[0], kSemaInfo) == g_val[0]);
        CHECK(g_rig->r32(kSemaInfo + 0) == 0);
        CHECK(g_rig->r32(kSemaInfo + 4) == 1);
        CHECK(g_rig->r32(kSemaInfo + 0xC) == 3);
        CHECK(g_rig->r32(kSemaInfo + 0x10) == 1);
        CHECK(sys(c, kSignalSema, g_val[0]) == g_val[0]);  // first waiter A (prio 20), not B (prio 10)
        CHECK(sys(c, kSignalSema, g_val[0]) == g_val[0]);  // B
        CHECK(sys(c, kDeleteSema, g_val[0]) == g_val[0]);  // C released with -1
        // WaitSema on a deleted id: the worker's -1 is discarded and the wrapper restores the context frame,
        // whose $v0 is $a0 (BIOS 0x80003444 `move v0,a0`, 0x80003494 restore): the id comes back.
        CHECK(sys(c, kWaitSema, g_val[0]) == g_val[0]);
        CHECK(sys(c, kSignalSema, g_val[0]) == -1);
        // No max clamp; PollSema; init < 0 refused; the freed id 0 is reused first (LIFO free list:
        // iDeleteSema 0x80004B7C pushes the head that CreateSema 0x800049B8 pops).
        const s64 s = create_sema(c, 0, 1);
        CHECK(s == 0);
        for (int i = 0; i < 3; ++i) sys(c, kSignalSema, s);
        sys(c, kReferSemaStatus, s, kSemaInfo);
        CHECK(g_rig->r32(kSemaInfo) == 3);
        CHECK(sys(c, kPollSema, s) == s);
        CHECK(sys(c, -0x46 /*iPollSema*/, s) == s);
        CHECK(sys(c, kPollSema, s) == s);
        CHECK(sys(c, kPollSema, s) == -1);
        CHECK(create_sema(c, -1, 1) == -1);
        CHECK(sys(c, kWaitSema, 300) == 300);  // invalid id: $a0 from the frame, as above
        // iSignalSema from thread context: the waiter is readied, no preemption until a switching call.
        const s64 s2 = create_sema(c, 0, 1, 0, 1);
        g_val[0] = s2;
        g_tid[3] = create_thread(c, kTA, 10, kStack + 0x30000, 0x1000, 0, 3);
        sys(c, kStartThread, g_tid[3], 0);
        CHECK(sys(c, kiSignalSema, s2) == s2);
        lg("m-after-isignal");
        sys(c, kRotateThreadReadyQueue, 30);
        lg("m-end");
    });
    REQUIRE(L.size() == 6);
    CHECK(L[0] == std::to_string(g_tid[0]) + ":0");
    CHECK(L[1] == std::to_string(g_tid[1]) + ":0");
    CHECK(L[2] == std::to_string(g_tid[2]) + ":-1");
    CHECK(L[3] == "m-after-isignal");
    CHECK(L[4] == std::to_string(g_tid[3]) + ":1");  // s2 got id 1 (LIFO: 0 was reused by s)
    CHECK(L[5] == "m-end");
}

TEST_CASE("H-12/H-13/H-14: SetupThread, SetupHeap(-1), EndOfHeap, argv block, thread entry return -> root -> ExitThread") {
    L.clear();
    register_root();
    register_fn(kTA, [](EEContext& c) {
        CHECK(c.gpr[GPR_A0].u32[0] == 0xA5A5u);              // StartThread's arg
        CHECK(c.gpr[GPR_SP].u32[0] == kStack + 0x1000 - 0x20);  // stack + size - 0x20
        CHECK(c.gpr[GPR_FP].u32[0] == kStack + 0x1000 - 0x20);
        CHECK(c.gpr[GPR_GP].u32[0] == 0x7D2CF0u);
        CHECK(c.gpr[GPR_RA].u32[0] == kRoot);  // creator's root_func
        CHECK(sys(c, kEndOfHeap) == 0x01F60000);  // heap end inherited
        lg("T");
        // returning lands on root_func -> ExitThread -> DORMANT
    });
    Rig r;
    run_main(r, [](EEContext& c) {
        constexpr u32 args = 0x0095C280u;
        CHECK(sys(c, kSetupThread, 0x7D2CF0, -1, 0xA0000, args, kRoot) == 0x02000000 - 0x1000 - 0x2A0);
        CHECK(sys(c, kSetupThread, 0x7D2CF0, 0x01F60000, 0xA0000, args, kRoot) == 0x02000000 - 0x2A0);
        CHECK(g_rig->r32(args) == 1);
        CHECK(g_rig->r32(args + 4) == args + 0x44);
        CHECK(g_rig->r32(args + 8) == 0);
        char buf[32] = {};
        for (u32 i = 0; i < 31; ++i) buf[i] = static_cast<char>(g_rig->mem.read<u8>(args + 0x44 + i));
        CHECK(std::string(buf) == "cdrom0:\\SLUS_216.21;1");
        CHECK(sys(c, kSetupHeap, 0x009ACC80, -1) == 0x01F60000);  // size < 0: the stack base
        CHECK(sys(c, kEndOfHeap) == 0x01F60000);
        g_tid[0] = create_thread(c, kTA, 10, kStack);
        CHECK(sys(c, kStartThread, g_tid[0], 0xA5A5) == g_tid[0]);  // runs at once (10 < 0? no: main is 0)
        CHECK(L.empty());                                            // main is priority 0: T waits
        sys(c, kChangeThreadPriority, 0, 20);                        // now T (10) runs
        CHECK(L == std::vector<std::string>{"T"});
        CHECK(g_rig->k->thread(static_cast<int>(g_tid[0])).status == 0x10);  // DORMANT, restartable
        CHECK(sys(c, kSetupHeap, 0x00100000, 0x1000) == 0x00101000);
    });
}

TEST_CASE("idle rule: with every thread blocked, virtual time jumps to the next deadline; idle is tid 0") {
    register_fn(kH, [](EEContext& c) {
        g_val[0] = sys(c, -0x2F);  // iGetThreadId inside the handler: the idle thread
        g_val[1] = static_cast<s64>(c.cycles);
        sys(c, -0x34, 1);
        set_reg(c, GPR_V0, 0);
    });
    Rig r;
    run_main(r, [](EEContext& c) {
        sys(c, kAddIntcHandler, 2, kH, 0, 0);
        sys(c, kEnableIntc, 2);
        ei(c);
        c.cycles = 1000;
        CHECK(sys(c, kSleepThread) == 1);
        CHECK(c.cycles == vblank_cycle(1));  // advanced straight to VBLANK_START, no spinning
        CHECK(g_val[1] == static_cast<s64>(vblank_cycle(1)));
        CHECK(g_val[0] == 0);
    });
}

TEST_CASE("idle rule: a deadlock (nothing can wake a thread) is fatal after idle_limit_cycles") {
    KernelOptions o;
    o.idle_limit_cycles = 30'000'000;
    Rig r(o);
    const RunResult res = r.k->run([](EEContext& c) {
        sys(c, kSleepThread);
        CHECK(false);
    });
    CHECK(res.status == RunStatus::Fatal);
    REQUIRE(r.fatals.size() == 1);
    CHECK(r.fatals[0].find("deadlock") != std::string::npos);
    CHECK(r.ctx.cycles <= 30'000'000ull + 4'920'116ull);
}

TEST_CASE("H-17: Suspend/Resume states; SuspendThread(self) traps; TerminateThread(self) -> -1; ReleaseWaitThread -> -1") {
    L.clear();
    register_fn(kTA, [](EEContext& c) {
        g_val[2] = static_cast<s32>(sys(c, kWaitSema, g_val[0]));  // released: low word -1 (`sw -1`)
        lg("T:" + std::to_string(g_val[2]));
    });
    Rig r;
    run_main(r, [](EEContext& c) {
        sys(c, kChangeThreadPriority, 0, 10);
        g_val[0] = create_sema(c, 0, 1);
        g_tid[0] = create_thread(c, kTA, 20, kStack);
        const int t = static_cast<int>(g_tid[0]);
        sys(c, kStartThread, t, 0);
        CHECK(sys(c, kSuspendThread, t) == t);
        CHECK(g_rig->k->thread(t).status == 8);
        CHECK(sys(c, kSuspendThread, t) == -1);
        CHECK(sys(c, kResumeThread, t) == t);
        CHECK(g_rig->k->thread(t).status == 2);
        sys(c, kChangeThreadPriority, 0, 30);  // T runs, blocks on the semaphore
        CHECK(g_rig->k->thread(t).status == 4);
        CHECK(sys(c, kSuspendThread, t) == t);
        CHECK(g_rig->k->thread(t).status == 0xC);  // WAITSUSPEND
        CHECK(sys(c, kWakeupThread, t) == t);      // sema wait: counted, not woken
        CHECK(g_rig->k->thread(t).wakeup_count == 1);
        CHECK(sys(c, kReleaseWaitThread, t) == t);  // WAITSUSPEND -> SUSPEND
        CHECK(g_rig->k->thread(t).status == 8);
        CHECK(sys(c, kResumeThread, t) == t);  // READY at 20 < 30: runs now, WaitSema returns -1
        lg("m");
        CHECK(sys(c, kTerminateThread, 0) == -1);
        CHECK(sys(c, kTerminateThread, 1) == -1);  // self
        CHECK(sys(c, kResumeThread, 1) == -1);
        CHECK(sys(c, kReleaseWaitThread, 1) == -1);
        CHECK(sys(c, 0x27) == 1);  // DisableDispatchThread: not supported, returns the tid
    });
    CHECK(L == std::vector<std::string>{"T:-1", "m"});
    CHECK(r.logs.size() == 1);
}

TEST_CASE("H-17: SuspendThread(self) is fatal; a positive switching syscall inside a handler is fatal") {
    {
        Rig r;
        const RunResult res = r.k->run([](EEContext& c) {
            sys(c, kSuspendThread, 1);
            CHECK(false);
        });
        CHECK(res.status == RunStatus::Fatal);
        REQUIRE(r.fatals.size() == 1);
        CHECK(r.fatals[0].find("H-17") != std::string::npos);
    }
    {
        register_fn(kH, [](EEContext& c) {
            sys(c, kWakeupThread, 1);  // positive form inside a handler
            set_reg(c, GPR_V0, 0);
        });
        Rig r;
        const RunResult res = r.k->run([](EEContext& c) {
            sys(c, kAddIntcHandler, 2, kH, 0, 0);
            sys(c, kEnableIntc, 2);
            ei(c);
            for (;;) work(c, 100'000);
        });
        CHECK(res.status == RunStatus::Fatal);
        REQUIRE(r.fatals.size() == 1);
        CHECK(r.fatals[0].find("inside an interrupt handler") != std::string::npos);
    }
}

TEST_CASE("lifecycle: create -> exit -> restart gets a fresh fiber and priority; ExitDeleteThread frees the tid") {
    L.clear();
    register_fn(kTA, [](EEContext& c) {
        lg("A" + std::to_string(g_rig->k->thread(static_cast<int>(self(c))).priority));
        sys(c, kChangeThreadPriority, 0, 3);
        sys(c, kExitThread);
        CHECK(false);
    });
    register_fn(kTB, [](EEContext& c) {
        lg("B");
        sys(c, kExitDeleteThread);
        CHECK(false);
    });
    Rig r;
    run_main(r, [](EEContext& c) {
        sys(c, kChangeThreadPriority, 0, 10);
        g_tid[0] = create_thread(c, kTA, 5, kStack);
        const int a = static_cast<int>(g_tid[0]);
        CHECK_FALSE(g_rig->k->thread(a).has_fiber);  // fibers are created on first activation
        sys(c, kStartThread, a, 0);
        CHECK(g_rig->k->thread(a).status == 0x10);
        CHECK_FALSE(g_rig->k->thread(a).has_fiber);
        CHECK(sys(c, kStartThread, a, 0) == a);  // restartable, priority reset to the initial 5 (runs, exits)
        CHECK(sys(c, kStartThread, 1, 0) == -1);  // self
        g_tid[1] = create_thread(c, kTB, 5, kStack + 0x10000, 0x1000, 0, 1);
        const int b = static_cast<int>(g_tid[1]);
        sys(c, kStartThread, b, 0);
        CHECK(g_rig->k->thread(b).status == 0);  // TCB freed
        CHECK(sys(c, kStartThread, b, 0) == -1);
        CHECK(sys(c, kDeleteThread, a) == a);  // DORMANT: deletable
        CHECK(sys(c, kDeleteThread, a) == -1);
        // FIFO free list: the next ids are the never-used ones; freed b and a come last.
        CHECK(create_thread(c, kTA, 5, kStack, 0x1000, 0, 2) == 4);
    });
    CHECK(L == std::vector<std::string>{"A5", "A5", "B"});
}

TEST_CASE("lifecycle: deleting a sleeping thread needs Terminate first; terminate from another thread fixes sema waiters") {
    L.clear();
    register_fn(kTA, [](EEContext& c) {
        sys(c, kSleepThread);
        lg("A-woke");  // never: terminated while asleep
    });
    register_fn(kTB, [](EEContext& c) {
        sys(c, kWaitSema, g_val[0]);
        lg("B-got");  // never
    });
    register_fn(kTC, [](EEContext& c) {
        CHECK(sys(c, kTerminateThread, g_tid[1]) == g_tid[1]);  // from another (non-main) thread
        lg("C");
    });
    Rig r;
    run_main(r, [](EEContext& c) {
        sys(c, kChangeThreadPriority, 0, 30);
        g_val[0] = create_sema(c, 0, 5);
        g_tid[0] = create_thread(c, kTA, 10, kStack, 0x1000, 0, 0);
        g_tid[1] = create_thread(c, kTB, 10, kStack + 0x10000, 0x1000, 0, 1);
        g_tid[2] = create_thread(c, kTC, 10, kStack + 0x20000, 0x1000, 0, 2);
        sys(c, kStartThread, g_tid[0], 0);
        sys(c, kStartThread, g_tid[1], 0);
        const int a = static_cast<int>(g_tid[0]);
        CHECK(g_rig->k->thread(a).has_fiber);
        CHECK(sys(c, kDeleteThread, a) == -1);  // asleep, not DORMANT
        CHECK(sys(c, kTerminateThread, a) == a);
        CHECK_FALSE(g_rig->k->thread(a).has_fiber);  // suspended fiber deleted at once
        CHECK(sys(c, kDeleteThread, a) == a);
        sys(c, kReferSemaStatus, g_val[0], kSemaInfo);
        CHECK(g_rig->r32(kSemaInfo + 0xC) == 1);
        sys(c, kStartThread, g_tid[2], 0);  // C terminates B
        sys(c, kReferSemaStatus, g_val[0], kSemaInfo);
        CHECK(g_rig->r32(kSemaInfo + 0xC) == 0);  // waiter count fixed
        CHECK(sys(c, kSignalSema, g_val[0]) == g_val[0]);
        sys(c, kReferSemaStatus, g_val[0], kSemaInfo);
        CHECK(g_rig->r32(kSemaInfo) == 1);  // no waiter left: counted
        CHECK(g_rig->k->thread(static_cast<int>(g_tid[1])).status == 0x10);
        // A READY thread that never ran has no fiber: terminate it.
        sys(c, kChangeThreadPriority, 0, 5);
        sys(c, kStartThread, g_tid[1], 0);
        CHECK_FALSE(g_rig->k->thread(static_cast<int>(g_tid[1])).has_fiber);
        CHECK(sys(c, kTerminateThread, g_tid[1]) == g_tid[1]);
    });
    CHECK(L == std::vector<std::string>{"C"});
}

TEST_CASE("lifecycle: an interrupt handler terminates the thread whose fiber is running the idle loop") {
    L.clear();
    register_fn(kTA, [](EEContext& c) {
        lg("T" + std::to_string(g_val[3]++));
        sys(c, kSleepThread);  // the last thread to block: the idle loop runs on this fiber
        lg("T-woke");          // never
    });
    register_fn(kH, [](EEContext& c) {
        if (g_rig->k->time().vblanks == 1) {
            g_val[0] = sys(c, -0x26 /*iTerminateThread*/, g_tid[0]);
            g_val[1] = sys(c, -0x34, 1);
        }
        set_reg(c, GPR_V0, 0);
    });
    g_val[3] = 0;
    Rig r;
    run_main(r, [](EEContext& c) {
        sys(c, kChangeThreadPriority, 0, 10);
        sys(c, kAddIntcHandler, 2, kH, 0, 0);
        sys(c, kEnableIntc, 2);
        ei(c);
        g_tid[0] = create_thread(c, kTA, 20, kStack);
        sys(c, kStartThread, g_tid[0], 0);
        sys(c, kSleepThread);  // T runs and sleeps; idle on T's fiber; vblank 1 terminates T, wakes main
        CHECK(g_val[0] == g_tid[0]);
        CHECK(g_val[1] == 1);
        CHECK(g_rig->k->thread(static_cast<int>(g_tid[0])).status == 0x10);
        CHECK_FALSE(g_rig->k->thread(static_cast<int>(g_tid[0])).has_fiber);
        sys(c, kStartThread, g_tid[0], 0);
        sys(c, kChangeThreadPriority, 0, 30);  // restarted T runs on a new fiber
        lg("m");
    });
    CHECK(L == std::vector<std::string>{"T0", "T1", "m"});
}

TEST_CASE("lifecycle: shutdown with threads mid-sleep and mid-wait; stop, resume, destroy while stopped") {
    register_fn(kTA, [](EEContext& c) { sys(c, kSleepThread); });
    register_fn(kTB, [](EEContext& c) { sys(c, kWaitSema, g_val[0]); });
    {
        Rig r;
        const RunResult res = run_main(r, [](EEContext& c) {
            sys(c, kChangeThreadPriority, 0, 30);
            g_val[0] = create_sema(c, 0, 1);
            sys(c, kStartThread, create_thread(c, kTA, 10, kStack, 0x1000, 0, 0), 0);
            sys(c, kStartThread, create_thread(c, kTB, 10, kStack + 0x10000, 0x1000, 0, 1), 0);
        });
        CHECK(res.status == RunStatus::MainExited);
        CHECK(r.k->thread(2).has_fiber);
        CHECK(r.k->thread(3).has_fiber);
    }  // ~Kernel deletes both suspended fibers and the zombie of main
    {
        Rig r;
        r.k->start([](EEContext& c) {
            ei(c);
            sys(c, kChangeThreadPriority, 0, 30);
            sys(c, kStartThread, create_thread(c, kTA, 10, kStack), 0);
            for (int i = 0; i < 1000; ++i) work(c, 50'000);
        });
        const RunResult s1 = r.k->run_until([] { return g_rig->k->time().vblanks >= 2; });
        CHECK(s1.status == RunStatus::Stopped);
        CHECK(r.k->time().vblanks == 2);
        CHECK(r.k->step_to_next_event().status == RunStatus::Stopped);
        CHECK(r.k->events_processed() == 4);  // VBLANK_START/END of fields 1-2
        const RunResult s2 = r.k->run_until(nullptr);
        CHECK(s2.status == RunStatus::MainExited);
        CHECK(r.ctx.cycles >= 50'000'000ull);
    }
    {
        Rig r;
        r.k->start([](EEContext& c) {
            sys(c, kChangeThreadPriority, 0, 30);
            sys(c, kStartThread, create_thread(c, kTA, 10, kStack), 0);
            for (;;) work(c, 50'000);
        });
        CHECK(r.k->run_until([] { return g_rig->k->time().vblanks >= 1; }).status == RunStatus::Stopped);
    }  // destroyed while the main fiber is suspended in a check point
    CHECK(true);
}

TEST_CASE("H-12: the main thread exiting through ExitThread ends the run") {
    Rig r;
    const RunResult res = run_main(r, [](EEContext& c) {
        sys(c, kExitThread);
        CHECK(false);
    });
    CHECK(res.status == RunStatus::MainExited);
    CHECK(res.message == "main thread exited");
}

// KernelOptions::context_frames (BIOS v02.30: kctx_save_on_thread_stack 0x80003680, restore 0x80003800,
// CreateThread 0x80003DBC, iStartThread 0x80003FD4, ChangeThreadPriority 0x800035D8, interrupt exit 0x8000363C).
TEST_CASE("context frames: switching syscalls and interrupt-exit preemption save the context at sp - 0x280; new threads start from their frame") {
    L.clear();
    register_root();
    static constexpr u32 kMainSp = 0x01800000u;
    static constexpr u32 kFrame = kStack + 0x1000 - 0x2A0;  // the new thread's frame
    register_fn(kTA, [](EEContext& c) {
        // Registers come from the frame memory, not from zero: the 32-bit stores of CreateThread / StartThread
        // leave the rest of each 128-bit slot as it was in memory.
        CHECK(c.gpr[GPR_A0].u32[0] == 0x1234u);
        CHECK(c.gpr[GPR_A0].u32[1] == 0xCAFEF00Du);
        CHECK(c.gpr[GPR_S0].u32[0] == 0x5EED0000u);
        CHECK(c.gpr[GPR_SP].u32[0] == kStack + 0x1000 - 0x20);
        CHECK(c.gpr[GPR_GP].u32[0] == 0x7D2CF0u);
        // The main thread's frame from its ChangeThreadPriority (below): s1 and the 128-bit v0 slot.
        CHECK(g_rig->r32(kMainSp - 0x280 + 16 * 17) == 0x1111u);
        CHECK(g_rig->mem.read<u64>(kMainSp - 0x280 + 32) == 0);  // `sd v0`: the old priority (0)
        CHECK(g_rig->mem.read<u64>(kMainSp - 0x280 + 40) == 0xABCDu);
        CHECK(g_rig->r32(kMainSp - 0x280 + 464) == kMainSp);
        lg("A");
        for (;;) {
            sys(c, kSleepThread);
            lg("A-woke");
        }
    });
    register_fn(kH, [](EEContext& c) {
        if (g_rig->k->time().vblanks == 1) sys(c, -0x34, g_tid[0]);  // iWakeupThread: preempts at interrupt exit
        set_reg(c, GPR_V0, 0);
    });
    Rig r;
    run_main(r, [](EEContext& c) {
        set_reg(c, GPR_SP, kMainSp);
        set_reg(c, GPR_S1, 0x1111);
        g_tid[0] = create_thread(c, kTA, 10, kStack);
        CHECK(g_rig->r32(kFrame + 448) == 0x7D2CF0u);                 // gp
        CHECK(g_rig->r32(kFrame + 464) == kStack + 0x1000 - 0x20);   // sp
        CHECK(g_rig->r32(kFrame + 480) == kStack + 0x1000 - 0x20);   // fp
        CHECK(g_rig->k->thread(static_cast<int>(g_tid[0])).frame == kFrame);
        g_rig->w32(kFrame + 64 + 4, 0xCAFEF00Du);  // seed the frame: what the thread will start with
        g_rig->w32(kFrame + 16 * 16, 0x5EED0000u);
        set_reg(c, GPR_V0, 0x77);
        CHECK(sys(c, kStartThread, g_tid[0], 0x1234) == g_tid[0]);  // returns the frame's $v0 = $a0
        CHECK(g_rig->r32(kFrame + 64) == 0x1234u);                  // `sw a1, 64(frame)`
        CHECK(g_rig->r32(kMainSp - 0x280 + 32) == static_cast<u32>(g_tid[0]));  // StartThread: `move v0,a0`
        c.gpr[GPR_V0].u64[1] = 0xABCDu;
        CHECK(sys(c, kChangeThreadPriority, 0, 20) == 0);  // A (10) runs here and sleeps
        CHECK(L == std::vector<std::string>{"A"});
        // Interrupt-exit preemption: the vblank handler wakes A while main runs; main's live registers land in
        // a frame at its sp - 0x280 before A runs.
        sys(c, kAddIntcHandler, 2, kH, 0, 0);
        sys(c, kEnableIntc, 2);
        ei(c);
        set_reg(c, GPR_S2, 0x2222);
        g_rig->w32(kMainSp - 0x280 + 16 * 18, 0);
        while (g_rig->k->time().vblanks < 1) work(c, 10'000);
        CHECK(L == std::vector<std::string>{"A", "A-woke"});
        CHECK(g_rig->r32(kMainSp - 0x280 + 16 * 18) == 0x2222u);
    });
}

TEST_CASE("context frames off: no guest-memory writes below sp, the BIOS restore's start registers (KernelOptions::context_frames)") {
    L.clear();
    register_root();
    register_fn(kTA, [](EEContext& c) {
        // Layer 6 (--native kernel): the registers the BIOS restore would load from the fresh frame -- the bytes at
        // stack + size - 0x2A0 as the guest left them (nothing is written there) with gp/sp/fp/ra and $a0 = the arg.
        CHECK(c.gpr[GPR_S0].u64[0] == 0x5EED0000u);
        CHECK(c.gpr[GPR_A0].u64[0] == 0x55u);
        CHECK(c.gpr[GPR_SP].u64[0] == kStack + 0x1000 - 0x20);
        CHECK(c.gpr[GPR_FP].u64[0] == kStack + 0x1000 - 0x20);
        lg("A");
    });
    KernelOptions o;
    o.context_frames = false;
    Rig r(o);
    run_main(r, [](EEContext& c) {
        set_reg(c, GPR_SP, 0x01800000);
        set_reg(c, GPR_S1, 0x1111);
        g_rig->w32(kStack + 0x1000 - 0x2A0 + 16 * 16, 0x5EED0000u);
        g_tid[0] = create_thread(c, kTA, 10, kStack);
        CHECK(g_rig->r32(kStack + 0x1000 - 0x2A0 + 448) == 0);
        sys(c, kStartThread, g_tid[0], 0x55);
        sys(c, kChangeThreadPriority, 0, 20);
        CHECK(g_rig->r32(0x01800000 - 0x280 + 16 * 17) == 0);
    });
    CHECK(L == std::vector<std::string>{"A"});
}
