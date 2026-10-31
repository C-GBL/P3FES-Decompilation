// Layer 6's inventory report (`--kernel-census FILE`, docs/MODERNIZE_PLAN.md "Layer 6 status"): the kernel's
// KernelCensus of one run as text, every count with the guest functions that caused it (GuestSymbols). Host-only.
#include "kernel_census.h"

#include <algorithm>
#include <cinttypes>
#include <cstdio>
#include <utility>
#include <vector>

namespace p3fes::app {

namespace {

using hle::KernelCensus;

// Hardware register names for the census (EE / GS windows; only the ones the routes touch need a name).
const char* reg_name(std::uint32_t pa) {
    struct R {
        std::uint32_t pa;
        const char* name;
    };
    static constexpr R kRegs[] = {
        {0x10000000u, "T0_COUNT"},   {0x10000010u, "T0_MODE"},    {0x10000020u, "T0_COMP"},   {0x10000030u, "T0_HOLD"},
        {0x10000800u, "T1_COUNT"},   {0x10000810u, "T1_MODE"},    {0x10000820u, "T1_COMP"},   {0x10000830u, "T1_HOLD"},
        {0x10001000u, "T2_COUNT"},   {0x10001010u, "T2_MODE"},    {0x10001020u, "T2_COMP"},   {0x10001030u, "T2_HOLD"},
        {0x10001800u, "T3_COUNT"},   {0x10001810u, "T3_MODE"},    {0x10001820u, "T3_COMP"},
        {0x10002000u, "IPU_CMD"},    {0x10002010u, "IPU_CTRL"},   {0x10002020u, "IPU_BP"},    {0x10002030u, "IPU_TOP"},
        {0x10003000u, "GIF_CTRL"},   {0x10003010u, "GIF_MODE"},   {0x10003020u, "GIF_STAT"},
        {0x10003800u, "VIF0_STAT"},  {0x10003810u, "VIF0_FBRST"}, {0x10003820u, "VIF0_ERR"},
        {0x10003C00u, "VIF1_STAT"},  {0x10003C10u, "VIF1_FBRST"}, {0x10003C20u, "VIF1_ERR"},
        {0x10004000u, "VIF0_FIFO"},  {0x10005000u, "VIF1_FIFO"},  {0x10006000u, "GIF_FIFO"},
        {0x10007000u, "IPU_OUT"},    {0x10007010u, "IPU_IN"},
        {0x10008000u, "D0_CHCR"},    {0x10009000u, "D1_CHCR"},    {0x10009010u, "D1_MADR"},   {0x10009020u, "D1_QWC"},
        {0x10009030u, "D1_TADR"},    {0x1000A000u, "D2_CHCR"},    {0x1000A010u, "D2_MADR"},   {0x1000A020u, "D2_QWC"},
        {0x1000A030u, "D2_TADR"},    {0x1000B000u, "D3_CHCR"},    {0x1000B010u, "D3_MADR"},   {0x1000B020u, "D3_QWC"},
        {0x1000B400u, "D4_CHCR"},    {0x1000B410u, "D4_MADR"},    {0x1000B420u, "D4_QWC"},    {0x1000B430u, "D4_TADR"},
        {0x1000C000u, "D5_CHCR"},    {0x1000C400u, "D6_CHCR"},    {0x1000C410u, "D6_MADR"},   {0x1000C420u, "D6_QWC"},
        {0x1000C430u, "D6_TADR"},    {0x1000D000u, "D8_CHCR"},    {0x1000D010u, "D8_MADR"},   {0x1000D020u, "D8_QWC"},
        {0x1000D080u, "D8_SADR"},    {0x1000D400u, "D9_CHCR"},    {0x1000D410u, "D9_MADR"},   {0x1000D420u, "D9_QWC"},
        {0x1000D430u, "D9_TADR"},    {0x1000D480u, "D9_SADR"},
        {0x1000E000u, "D_CTRL"},     {0x1000E010u, "D_STAT"},     {0x1000E020u, "D_PCR"},     {0x1000E030u, "D_SQWC"},
        {0x1000E040u, "D_RBSR"},     {0x1000E050u, "D_RBOR"},     {0x1000F000u, "INTC_STAT"}, {0x1000F010u, "INTC_MASK"},
        {0x1000F200u, "SIF_MSCOM"},  {0x1000F210u, "SIF_SMCOM"},  {0x1000F220u, "SIF_MSFLG"}, {0x1000F230u, "SIF_SMFLG"},
        {0x1000F240u, "SIF_CTRL"},   {0x1000F260u, "SIF_BD6"},    {0x1000F520u, "D_ENABLER"}, {0x1000F590u, "D_ENABLEW"},
        {0x12000000u, "GS_PMODE"},   {0x12000020u, "GS_SMODE2"},  {0x12000070u, "GS_DISPFB1"}, {0x12000080u, "GS_DISPLAY1"},
        {0x12000090u, "GS_DISPFB2"}, {0x120000A0u, "GS_DISPLAY2"}, {0x120000E0u, "GS_BGCOLOR"}, {0x12001000u, "GS_CSR"},
        {0x12001010u, "GS_IMR"},     {0x12001040u, "GS_BUSDIR"},
    };
    for (const R& r : kRegs)
        if (r.pa == pa) return r.name;
    return "";
}

const char* intc_name(unsigned c) {
    static constexpr const char* k[] = {"GS", "SBUS", "VBLANK_START", "VBLANK_END", "VIF0", "VIF1", "VU0", "VU1",
                                        "IPU", "TIMER0", "TIMER1", "TIMER2", "TIMER3", "SFIFO", "VU0WD"};
    return c < 15 ? k[c] : "?";
}
const char* dmac_name(unsigned c) {
    static constexpr const char* k[] = {"VIF0", "VIF1", "GIF", "fromIPU", "toIPU", "SIF0", "SIF1", "SIF2", "fromSPR", "toSPR"};
    return c < 10 ? k[c] : "?";
}

std::string who(const GuestSymbols& syms, std::uint32_t va) { return va ? syms.describe(va) : std::string("(none)"); }

// The `n` largest (key, count) pairs of `m` whose key matches `pick`, largest first.
template <typename Map, typename Pick>
std::vector<std::pair<std::uint64_t, std::uint64_t>> top(const Map& m, Pick pick, std::size_t n) {
    std::vector<std::pair<std::uint64_t, std::uint64_t>> v;
    for (const auto& [k, c] : m)
        if (pick(k)) v.emplace_back(k, c);
    std::sort(v.begin(), v.end(), [](const auto& a, const auto& b) { return a.second != b.second ? a.second > b.second : a.first < b.first; });
    if (v.size() > n) v.resize(n);
    return v;
}

}  // namespace

void write_kernel_census(std::FILE* f, const hle::KernelCensus& c, const GuestSymbols& syms, const KernelCensusContext& x) {
    const auto ull = [](std::uint64_t v) { return static_cast<unsigned long long>(v); };
    const double vb = c.vblanks ? static_cast<double>(c.vblanks) : 1.0;
    std::fprintf(f, "# p3fes kernel census v1 (docs/MODERNIZE_PLAN.md \"Layer 6 status\")\n");
    std::fprintf(f, "route %s\nnative %s\nvblanks %llu\ncycles %llu\nflips %llu\n", x.route.c_str(), x.native.c_str(),
                 ull(c.vblanks), ull(x.cycles), ull(x.flips));
    std::fprintf(f, "\n## scheduler\n");
    std::fprintf(f, "thread creates %llu, starts %llu, exits %llu\n", ull(c.thread_creates), ull(c.thread_starts), ull(c.thread_exits));
    std::fprintf(f, "fiber switches %llu (%.1f / vblank), interrupt-exit preemptions %llu\n", ull(c.switches), c.switches / vb,
                 ull(c.preemptions));
    std::fprintf(f, "idle steps %llu (%.2f / vblank), idle cycles %llu (%.1f %% of virtual time)\n", ull(c.idle_steps), c.idle_steps / vb,
                 ull(c.idle_cycles), x.cycles ? 100.0 * static_cast<double>(c.idle_cycles) / static_cast<double>(x.cycles) : 0.0);
    std::fprintf(f, "slow check points %llu (%.1f / vblank), masked re-tests %llu, device-service passes %llu\n", ull(c.slow_checks),
                 c.slow_checks / vb, ull(c.masked_polls), ull(c.services));
    std::uint64_t calls = 0;
    for (unsigned s = 0; s < 256; ++s) calls += c.syscalls[s] + c.isyscalls[s];
    std::fprintf(f, "kernel calls %llu, of them direct kernel calls %llu (layer 6: the game's stubs call the kernel without `syscall`)\n",
                 ull(calls), ull(c.direct_calls));

    std::fprintf(f, "\n## syscalls (slot name: calls [i* calls]; callers by $ra)\n");
    for (unsigned s = 0; s < 256; ++s) {
        if (!c.syscalls[s] && !c.isyscalls[s]) continue;
        std::fprintf(f, "0x%02X %-24s %10llu", s, hle::syscall_name(s), ull(c.syscalls[s]));
        if (c.isyscalls[s]) std::fprintf(f, "  i* %llu", ull(c.isyscalls[s]));
        std::fprintf(f, "  (%.2f / vblank)\n", (c.syscalls[s] + c.isyscalls[s]) / vb);
        for (const auto& [k, n] : top(c.syscall_sites, [s](std::uint64_t k) { return ((k >> 32) & 0xFFu) == s; }, 6))
            std::fprintf(f, "       %s%-50s %llu\n", (k >> 40) ? "i* " : "   ", who(syms, static_cast<std::uint32_t>(k)).c_str(), ull(n));
    }

    std::fprintf(f, "\n## interrupts (handler chains run; handlers called)\n");
    for (unsigned i = 0; i < 15; ++i)
        if (c.intc_chains[i]) std::fprintf(f, "INTC %2u %-13s %10llu  (%.2f / vblank)\n", i, intc_name(i), ull(c.intc_chains[i]), c.intc_chains[i] / vb);
    for (unsigned i = 0; i < 16; ++i)
        if (c.dmac_chains[i]) std::fprintf(f, "DMAC %2u %-13s %10llu  (%.2f / vblank)\n", i, dmac_name(i), ull(c.dmac_chains[i]), c.dmac_chains[i] / vb);
    for (const auto& [k, n] : top(c.handler_runs, [](std::uint64_t) { return true; }, 32))
        std::fprintf(f, "  handler %-50s %llu\n", who(syms, static_cast<std::uint32_t>(k)).c_str(), ull(n));

    std::fprintf(f, "\n## DMAC (starts, of them chain mode, qwords, stalls, re-arms in the completion window, CHCR reads while busy)\n");
    for (unsigned i = 0; i < 10; ++i)
        if (c.dma_starts[i] || c.dma_busy_polls[i])
            std::fprintf(f, "ch%u %-8s starts %8llu chain %8llu qw %10llu stalls %6llu rearms %6llu busy-polls %8llu\n", i, dmac_name(i),
                         ull(c.dma_starts[i]), ull(c.dma_chain_starts[i]), ull(c.dma_qwords[i]), ull(c.dma_stalls[i]), ull(c.dma_rearms[i]),
                         ull(c.dma_busy_polls[i]));
    std::fprintf(f, "DMAC control registers: reads %llu, writes %llu\n", ull(c.dmac_ctrl_regs.reads), ull(c.dmac_ctrl_regs.writes));

    std::fprintf(f, "\n## timers and INTC registers\n");
    for (unsigned i = 0; i < 4; ++i)
        if (c.timer_regs[i].reads || c.timer_regs[i].writes || c.timer_irqs[i])
            std::fprintf(f, "T%u reads %llu writes %llu interrupts %llu\n", i, ull(c.timer_regs[i].reads), ull(c.timer_regs[i].writes),
                         ull(c.timer_irqs[i]));
    std::fprintf(f, "INTC_STAT/MASK reads %llu writes %llu\n", ull(c.intc_regs.reads), ull(c.intc_regs.writes));

    std::fprintf(f, "\n## semaphores (id: creates, waits [blocked], signals [in handlers], polls, deletes; {max, init}; creator)\n");
    for (const auto& [id, u] : c.semas)
        std::fprintf(f, "sema %3d: creates %llu waits %llu [%llu] signals %llu [%llu] polls %llu deletes %llu {%d, %d} %s\n", id,
                     ull(u.creates), ull(u.waits), ull(u.blocked), ull(u.signals), ull(u.isignals), ull(u.polls), ull(u.deletes), u.max,
                     u.init, who(syms, u.creator).c_str());

    std::fprintf(f, "\n## hardware registers the guest reads / writes (by 16-byte register; callers by $ra)\n");
    std::vector<std::pair<std::uint32_t, KernelCensus::Count2>> regs(c.bus.begin(), c.bus.end());
    std::sort(regs.begin(), regs.end(), [](const auto& a, const auto& b) {
        return a.second.reads + a.second.writes > b.second.reads + b.second.writes;
    });
    for (const auto& [pa, n] : regs) {
        std::fprintf(f, "0x%08X %-12s reads %10llu writes %10llu  (%.1f / vblank)\n", pa, reg_name(pa), ull(n.reads), ull(n.writes),
                     (n.reads + n.writes) / vb);
        for (const auto& [k, cnt] : top(c.bus_sites, [pa](std::uint64_t k) { return static_cast<std::uint32_t>(k >> 32) == pa; }, 4))
            std::fprintf(f, "       %-50s %llu\n", who(syms, static_cast<std::uint32_t>(k)).c_str(), ull(cnt));
    }
}

}  // namespace p3fes::app
