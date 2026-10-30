// The test stand-ins themselves (stand_ins.h): opt-in (a test that installs nothing sees the old missing-function
// stops and the real emitted heap / sprintf bodies), the printf formatter against the recompiled sprintf on the same
// guest arguments, the guest heap, the RW slot path through rt::lookup_func, and the file layer on a real file.
#include <doctest.h>

#include "stand_ins.h"

#include "p3fes/game/guest.h"
#include "p3fes/game/hcdvd.h"

#include <filesystem>
#include <fstream>

namespace p3fes::recomp_gen {
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_vsprintf_005288c8(p3fes::EEContext&);
void fn_sub_191AF0_00191af0(p3fes::EEContext&);
void fn_sub_191A10_00191a10(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_H_Cdvd_Update_00100980(p3fes::EEContext&);
void fn_H_Cdvd_ReadSync_001023a0(p3fes::EEContext&);
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);  // replaced (game/): its entry point is a generated forwarder
}  // namespace p3fes::recomp_gen

namespace p3fes::game_test {
bool stand_in_hook(::p3fes::EEContext& ctx, std::uint32_t va);  // the forwarders' first step (stand_ins.cpp)
namespace {

namespace rg = p3fes::recomp_gen;

Machine* machine() {
    static Machine* m = [] {
        auto* mm = new Machine;
        if (mm->load_elf(elf_path()) != nullptr) {
            delete mm;
            return static_cast<Machine*>(nullptr);
        }
        return mm;
    }();
    return m;
}

#define NEED_MACHINE()                                                  \
    Machine* mp = machine();                                            \
    if (!mp) {                                                          \
        MESSAGE("SKIP: no ELF at " << elf_path());                      \
        return;                                                         \
    }                                                                   \
    Machine& m = *mp

// A fresh context with $sp / $gp set and the arguments in $a0..$a3, $t0..$t3 and the stack slots.
void set_call(Machine& m, const std::vector<u64>& regs_and_stack) {
    std::mt19937 rng{1};
    m.fresh_context({0, 0, 0, 0}, rng);
    for (std::size_t i = 0; i < regs_and_stack.size(); ++i) {
        const u64 v = regs_and_stack[i];
        if (i < 4) m.ctx.gpr[GPR_A0 + i].u64[0] = v;
        else if (i < 8) m.ctx.gpr[GPR_T0 + (i - 4)].u64[0] = v;
        else std::memcpy(m.at(kSp + 8u * static_cast<u32>(i - 8)), &v, 8);
    }
}

}  // namespace

// printf is hand-written since finalB (game/src/fx/finalB.cpp), so its forwarder no longer stops when nothing serves it:
// it runs the body (newlib's printf into the stdout FILE, which waits on the IOP). The opt-in rule is therefore checked
// on the hook the forwarder asks first (stand_in_hook): nothing installed, or a set without printf, answers "not stood
// in" and logs nothing; an installed printf serves the forwarder.
TEST_CASE("stand-ins: opt-in -- nothing installed serves nothing; an installed printf serves the forwarder") {
    NEED_MACHINE();
    rt_test::HooksScope hs{&m.hooks};
    rt::bind_context(&m.ctx);
    m.put(kArena, "hello %d/%s\n");
    m.put(kArena + 0x40, "world");
    set_call(m, {kArena, sx(-7), kArena + 0x40});
    CHECK(!g_stand_ins_active);
    CHECK(!stand_in_hook(m.ctx, 0x5225A8u));  // nothing installed: the forwarder would run the body
    StandIns other;  // a set without printf: not served either, nothing logged
    other.install_recorder(0x100D80u, "H_Cdvd_Request", 0);
    {
        StandInsScope s(other);
        CHECK(g_stand_ins_active);
        CHECK(!stand_in_hook(m.ctx, 0x5225A8u));
        CHECK(stand_in_hook(m.ctx, 0x100D80u));  // what it does hold is served
    }
    CHECK(other.log.size() == 1u);
    CHECK(other.log[0].va == 0x100D80u);
    StandIns si;
    install_printf(si);
    set_call(m, {kArena, sx(-7), kArena + 0x40});
    m.ctx.gpr[GPR_RA].u64[0] = 0x123450u;
    const int checks0 = m.hooks.checks;
    {
        StandInsScope s(si);
        rg::fn_printf_005225a8(m.ctx);
    }
    REQUIRE(si.log.size() == 1);
    CHECK(si.log[0].text == "hello -7/world\n");
    CHECK(si.log[0].ra == 0x123450u);
    CHECK(si.log[0].args[0] == kArena);
    CHECK(m.ctx.gpr[GPR_V0].u64[0] == 15u);
    CHECK(m.hooks.checks == checks0 + 1);  // the callee's entry check point
    CHECK(m.ctx.gpr[GPR_A0].u64[0] != kArena);  // scratch registers overwritten
    CHECK(!g_stand_ins_active);
}

TEST_CASE("stand-ins: a replaced function is stood in through its forwarder; a pair runner calls it past its own") {
    // strlen (0x524388) is replaced: fn_strlen_00524388 is the test build's generated forwarder (game/forwarders.cmake),
    // which asks the installed stand-ins first (recomp/README.md "Forwarders").
    NEED_MACHINE();
    rt_test::HooksScope hs{&m.hooks};
    rt::bind_context(&m.ctx);
    constexpr u32 kStrlen = 0x524388u;
    m.put(kArena, "hello");
    CHECK(forwarder_table().count(&rg::fn_strlen_00524388) == 1);
    set_call(m, {kArena});
    rg::fn_strlen_00524388(m.ctx);  // nothing installed: the hand-written body
    CHECK(m.ctx.gpr[GPR_V0].u64[0] == 5u);
    StandIns si;
    si.install_recorder(kStrlen, "strlen", 77);
    {
        StandInsScope s(si);
        set_call(m, {kArena});
        rg::fn_strlen_00524388(m.ctx);  // a generated call site's path: served by the stand-in
        CHECK(m.ctx.gpr[GPR_V0].u64[0] == 77u);
        CHECK(si.calls_to(kStrlen) == 1);
        // the runners' path: the function under test runs for real, past the stand-in for its own address
        const Outcome o = run(m, &rg::fn_strlen_00524388, Args{kArena, 0, 0, 0}, 1);
        CHECK(o.v0 == 5u);
        CHECK(si.calls_to(kStrlen) == 1);
        CHECK(g_entry_bypass_va == 0);  // the bypass is gone after the run
        rt_test::HooksScope hs2{&m.hooks};  // (run() installed and removed its own)
        rt::bind_context(&m.ctx);
        set_call(m, {kArena});
        rg::fn_strlen_00524388(m.ctx);  // and the next call is served again
        CHECK(m.ctx.gpr[GPR_V0].u64[0] == 77u);
        CHECK(si.calls_to(kStrlen) == 2);
    }
}

TEST_CASE("stand-ins: the printf formatter equals the recompiled sprintf on the same guest arguments") {
    NEED_MACHINE();
    rt_test::HooksScope hs{&m.hooks};
    rt::bind_context(&m.ctx);
    const u32 fmt = kArena, out = kArena + 0x400, s1 = kArena + 0x200, s2 = kArena + 0x240;
    m.put(s1, "Persona");
    m.put(s2, "FES");
    struct Case {
        const char* f;
        std::vector<u64> a;
    };
    std::mt19937 rng{20261021};
    auto r32 = [&] { return sx(rng()); };
    auto r64 = [&] { return (static_cast<u64>(rng()) << 32) | rng(); };
    int compared = 0, stopped = 0;
    for (int round = 0; round < 300; ++round) {
        const std::vector<Case> cases = {
            {"%d|%i|%u|%x|%X|%o", {r32(), r32(), r32(), r32(), r32(), r32()}},
            {"%5d|%-5d|%05d|%+d|% d|%d", {sx(rng() % 2000) - 1000, sx(rng() % 100), sx(rng() % 100000), r32(), r32(), r32()}},
            {"%.3d|%8.3x|%#x|%#o|%#X|%3u", {sx(rng() % 50), r32(), r32(), r32(), sx(rng() % 9), r32()}},
            {"%s|%10s|%-10s|%.2s|%s.", {s1, s2, s1, s1, 0}},
            {"%c|%3c|%-3c|%c", {sx('A' + rng() % 26), sx('a' + rng() % 26), sx('0' + rng() % 10), sx(rng() & 0xFF)}},
            {"%hd|%hhd|%hu|%hx|%hhx|%hhu", {r32(), r32(), r32(), r32(), r32(), r32()}},
            {"%ld|%lu|%lx|%lld|%llx|%llu", {r32(), r64(), r64(), r64(), r64(), r64()}},
            {"%p|%%|%08x|%-8x|%8X|%p", {r32(), r32(), r32(), r32(), sx(rng() & 0x01FFFFFF)}},
            {"%*d|%-*d|%.*s|%*s", {sx(rng() % 12), r32(), sx(rng() % 12), r32(), sx(rng() % 8), s1, sx(rng() % 12), s2}},
            {"%d %d %d %d %d %d %d %d %d %d", {r32(), r32(), r32(), r32(), r32(), r32(), r32(), r32(), r32(), r32()}},
            {"%f|%.2f|%e|%g|%10.3f|%-8.1e|%G", {}},
        };
        for (const Case& c : cases) {
            std::vector<u64> args = c.a;
            if (std::string(c.f).find('f') != std::string::npos && args.empty()) {
                for (int k = 0; k < 7; ++k) {
                    const double d = (static_cast<double>(static_cast<s32>(rng())) / 1024.0) * ((rng() & 1) ? 1.0 : 1e-6);
                    u64 bits;
                    std::memcpy(&bits, &d, 8);
                    args.push_back(bits);
                }
            }
            m.put(fmt, c.f);
            std::vector<u64> call = {out, fmt};
            call.insert(call.end(), args.begin(), args.end());
            set_call(m, call);
            std::string real;
            try {
                rg::fn_sprintf_00523ac8(m.ctx);
                real = m.str(out, 4096);
            } catch (const rt_test::FatalEvent& e) {
                if (stopped == 0) MESSAGE("first stop in the real sprintf: " << e.what);
                ++stopped;  // the float conversions reach dtoa helpers this library does not emit
                continue;
            }
            set_call(m, call);
            const std::string mine = guest_format(m.ctx, fmt, 2).c_str();  // a %c of 0 ends the guest string there
            INFO(std::string(c.f) << " -> real '" << real << "' stand-in '" << mine << "'");
            CHECK(mine == real);
            ++compared;
        }
    }
    MESSAGE("formatter: " << compared << " formats compared with the recompiled sprintf, " << stopped
                          << " stopped in the real one (not emitted dtoa)");
    CHECK(compared >= 3000);
}

TEST_CASE("stand-ins: vsprintf reads its va_list (8-byte slots) like the recompiled vsprintf") {
    NEED_MACHINE();
    rt_test::HooksScope hs{&m.hooks};
    rt::bind_context(&m.ctx);
    const u32 fmt = kArena, out = kArena + 0x400, ap = kArena + 0x600, s1 = kArena + 0x200;
    m.put(fmt, "%d|%s|%x|%c|%lld|%5u|%-4d|");
    m.put(s1, "nmlist");
    std::mt19937 rng{7};
    StandIns si;
    install_sprintf(si);
    int compared = 0;
    for (int i = 0; i < 200; ++i) {
        const u64 slots[] = {sx(rng()), s1, sx(rng()), sx('a' + rng() % 26), (static_cast<u64>(rng()) << 32) | rng(),
                             sx(rng() % 100000), sx(rng() % 2000) - 1000};
        for (std::size_t k = 0; k < 7; ++k) std::memcpy(m.at(ap + 8u * static_cast<u32>(k)), &slots[k], 8);
        set_call(m, {out, fmt, ap});
        rg::fn_vsprintf_005288c8(m.ctx);  // no set installed: the recompiled vsprintf
        const std::string real = m.str(out);
        set_call(m, {out, fmt, ap});
        {
            StandInsScope s(si);
            rg::fn_vsprintf_005288c8(m.ctx);
        }
        CHECK(m.str(out) == real);
        CHECK(si.log.back().text == real);
        ++compared;
    }
    CHECK(compared == 200);
}

TEST_CASE("stand-ins: the guest heap -- alignment, first fit, coalescing, reserve, the H_Malloc / RW entry points") {
    GuestHeap h(0x01C00000u, 0x10000u);
    const u32 a = h.alloc(1), b = h.alloc(100), c = h.alloc(16);
    CHECK(a == 0x01C00000u);
    CHECK(b == 0x01C00010u);
    CHECK(c == 0x01C00080u);
    CHECK(h.size_of(b) == 112u);
    CHECK(h.free(b));
    CHECK(!h.free(b));
    CHECK(h.bad_frees == 1u);
    CHECK(h.alloc(64) == 0x01C00010u);  // first fit into the hole
    const u32 big = h.alloc(0x100, 0x40);
    CHECK(big % 0x40 == 0);
    CHECK(h.alloc(0x20000) == 0u);  // exhausted
    CHECK(h.free(a));
    CHECK(h.free(c));
    h.reserve(0x01C08000u, 0x30);
    CHECK(h.size_of(0x01C08000u) == 0x30u);
    CHECK(h.alloc(0x7000, 0x1000) != 0x01C08000u);

    NEED_MACHINE();
    rt_test::HooksScope hs{&m.hooks};
    rt::bind_context(&m.ctx);
    StandInWorld w;
    install_standard(w);
    write_rw_slots(m);
    {
        StandInsScope s(w.si);
        set_call(m, {0x30});
        rg::fn_sub_191AF0_00191af0(m.ctx);  // H_Malloc (emitted: the hook at its entry)
        const u32 p = static_cast<u32>(m.ctx.gpr[GPR_V0].u64[0]);
        CHECK(p == kStandInHeap);
        set_call(m, {0x200, 0x40000});
        u32 slot;
        std::memcpy(&slot, m.at(kRwSlots), 4);
        rt::lookup_func(slot)(m.ctx);  // RwMalloc through the slot, as `lw v0, 0x178(v0); jalr v0` does
        const u32 q = static_cast<u32>(m.ctx.gpr[GPR_V0].u64[0]);
        CHECK(q == kStandInHeap + 0x30);
        set_call(m, {p});
        rg::fn_sub_191A10_00191a10(m.ctx);  // H_Free
        CHECK(w.heap.size_of(p) == 0u);
        CHECK(w.heap.size_of(q) == 0x200u);
    }
    REQUIRE(w.si.log.size() == 3);
    CHECK(w.si.log[0].va == kHMalloc);
    CHECK(w.si.log[1].va == 0x104140u);
    CHECK(w.si.log[1].extra == 0x200u);
    CHECK(w.si.log[2].va == kHFree);
}

TEST_CASE("stand-ins: the file layer serves a real file -- request, dedup, update, read-sync, cache, destroy") {
    NEED_MACHINE();
    rt_test::HooksScope hs{&m.hooks};
    rt::bind_context(&m.ctx);
    StandInWorld w;
    install_standard(w);
    const char* rel = "battle/panel/bp_tutorial.bin";
    const std::string host = w.cd.host_path(FakeCd::build_path(rel));
    if (host.empty()) {
        MESSAGE("SKIP: " << rel << " not under " << w.cd.root);
        return;
    }
    std::ifstream f(host, std::ios::binary);
    const std::vector<u8> bytes((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    std::memset(m.at(game::kHCdvdListHead), 0, 16);
    std::memset(m.at(game::kHCdvdCache), 0, 148 * 256);
    m.put(kArena, rel);
    u32 node = 0, again = 0;
    {
        StandInsScope s(w.si);
        set_call(m, {kArena, 1});
        rg::fn_H_Cdvd_Request_00100d80(m.ctx);
        node = static_cast<u32>(m.ctx.gpr[GPR_V0].u64[0]);
        set_call(m, {kArena, 1});
        rg::fn_H_Cdvd_Request_00100d80(m.ctx);
        again = static_cast<u32>(m.ctx.gpr[GPR_V0].u64[0]);
        CHECK(game::guest::load<u32>(m.ctx, node + 12) == 0u);
        set_call(m, {node});
        rg::fn_H_Cdvd_ReadSync_001023a0(m.ctx);
    }
    CHECK(node == kStandInHeap);
    CHECK(again == node);
    CHECK(m.str(node + 16) == "VOL:\\BATTLE\\PANEL\\BP_TUTORIAL.BIN");
    CHECK(game::guest::load<u32>(m.ctx, node + 12) == game::kHCdvdStateLoaded);
    CHECK(game::guest::load<s16>(m.ctx, node + 858) == 2);
    const u32 data = game::guest::load<u32>(m.ctx, node + 272);
    CHECK(data % 64 == 0);
    CHECK(game::guest::load<u32>(m.ctx, node + 292) == bytes.size());
    CHECK(std::memcmp(m.at(data), bytes.data(), bytes.size()) == 0);
    u32 used = 0;
    for (u32 i = 0; i < 256; ++i) used += game::guest::load<u32>(m.ctx, game::kHCdvdCache + 148 * i) != 0 ? 1u : 0u;
    CHECK(used == static_cast<u32>(game::guest::load<s16>(m.ctx, node + 856)));
    CHECK(used > 0);
    {
        StandInsScope s(w.si);
        set_call(m, {node});
        rg::fn_H_Cdvd_Destroy_00100ec0(m.ctx);  // loaded: deferred
        set_call(m, {node});
        rg::fn_H_Cdvd_Destroy_00100ec0(m.ctx);
        set_call(m, {});
        rg::fn_H_Cdvd_Update_00100980(m.ctx);  // applies both: refcount 0 -> released
    }
    CHECK(w.heap.live().empty());
    CHECK(game::guest::load<u32>(m.ctx, game::kHCdvdListHead + 4) == 0u);
    used = 0;
    for (u32 i = 0; i < 256; ++i) used += game::guest::load<u32>(m.ctx, game::kHCdvdCache + 148 * i) != 0 ? 1u : 0u;
    CHECK(used == 0u);
    MESSAGE("file layer: " << std::string(rel) << " (" << bytes.size() << " bytes) loaded, " << w.si.log.size() << " calls logged");
}

}  // namespace p3fes::game_test
