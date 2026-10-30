// SIF registers, syscalls, the sifcmd/sifrpc handshakes, the reboot sequence, SIF0 delivery rules and
// unknown-id handling, driven through EeSide (the game's EE-side protocol re-enacted).
#include <doctest.h>

#include "sif_harness.h"

using namespace p3fes;
using namespace p3fes::test;

TEST_CASE("sif registers: power-on state and the EE-side write rules") {
    EeSide e;
    CHECK(e.get_reg(reg::kSmFlag) == flag::kAllBooted);  // IOP up: SIFINIT | CMDINIT | BOOTEND
    CHECK(e.get_reg(reg::kSubAddr) != 0);                 // the IOP's sifcmd buffer
    CHECK(e.get_reg(reg::kSysSubAddr) == 0);
    CHECK(e.get_reg(reg::kSysRpcInit) == 0);
    // SMFLAG: EE writes clear (sceSifResetIop's SetReg(4, 0x40000) etc.)
    e.set_reg(reg::kSmFlag, flag::kBootEnd);
    CHECK(e.get_reg(reg::kSmFlag) == (flag::kSifInit | flag::kCmdInit));
    // MSFLAG: EE writes set
    e.set_reg(reg::kMsFlag, 0x100);
    e.set_reg(reg::kMsFlag, 0x001);
    CHECK(e.get_reg(reg::kMsFlag) == 0x101);
    // MSCOM read/write, SMCOM not EE-writable
    e.set_reg(reg::kMainAddr, 0x12345678);
    CHECK(e.get_reg(reg::kMainAddr) == 0x12345678);
    const u32 smcom = e.get_reg(reg::kSubAddr);
    e.set_reg(reg::kSubAddr, 0xDEAD);
    CHECK(e.get_reg(reg::kSubAddr) == smcom);
    // software registers 0x80000000..0x8000001F
    e.set_reg(0x80000002u, 1);
    e.set_reg(0x8000001Fu, 0xABCD);
    CHECK(e.get_reg(0x80000002u) == 1);
    CHECK(e.get_reg(0x8000001Fu) == 0xABCD);
    CHECK(e.get_reg(0x80000020u) == 0);
    // MMIO view is the same register file
    CHECK(e.bus.read32(kRegSmflg) == e.get_reg(reg::kSmFlag));
    e.bus.write32(kRegSmflg, flag::kSifInit);
    CHECK(e.get_reg(reg::kSmFlag) == flag::kCmdInit);
    e.bus.write32(kRegMsflg, 0x2);
    CHECK(e.get_reg(reg::kMsFlag) == 0x103);
    e.bus.write32(kRegCtrl, 0x80000002u);
    CHECK(e.bus.read32(kRegCtrl) == 0x80000002u);
    e.bus.write32(kRegBd6, 0x55);
    CHECK(e.bus.read32(kRegBd6) == 0x55);
    CHECK(e.bus.find(0x1000F270u) == nullptr);
    CHECK(e.bus.handlers[5] == &e.sif.sif0_channel());
    CHECK(e.bus.handlers[6] == &e.sif.sif1_channel());
}

TEST_CASE("sif syscalls: DMA ids, status, stop/dchain, Deci2Call, values sign-extended") {
    EeSide e;
    CHECK(e.sys(0x77, ee::kDmaList, 0) == 0);  // count 0 rejected
    CHECK(e.sif.stats().set_dma_rejected == 1);
    const u32 id1 = e.set_dma({DmaTransfer{ee::kSendScratch, 0x00100000, 32, 0}}, false);
    const u32 id2 = e.set_dma({DmaTransfer{ee::kSendScratch, 0x00100000, 32, 0}}, false);
    CHECK(id1 != 0);
    CHECK(id2 != 0);
    CHECK(id1 != id2);
    CHECK(static_cast<s64>(e.sys(0x76, id1)) < 0);   // done
    CHECK(static_cast<s64>(e.sys(-0x76, id2)) < 0);  // i-form shares the slot
    CHECK(e.sif.sif0_started());
    e.sys(0x6B);
    CHECK_FALSE(e.sif.sif0_started());
    e.sys(-0x78);
    CHECK(e.sif.sif0_started());
    e.set_reg(0x80000003u, 0x80001234u);
    CHECK(e.sys(0x7A, 0x80000003u) == 0xFFFFFFFF80001234ull);
}

TEST_CASE("sif: SIF1 copies whole quadwords into IOP RAM") {
    EeSide e;
    std::vector<u8> src(40);
    for (std::size_t i = 0; i < src.size(); ++i) src[i] = static_cast<u8>(i + 1);
    e.write(ee::kSendScratch, src);
    e.set_dma({DmaTransfer{ee::kSendScratch | 0x20000000u, 0x00100000, 33, 0}}, false);  // uncached EE alias
    auto ram = e.sif.iop().ram();
    for (u32 i = 0; i < 40; ++i) CHECK(ram[0x100000 + i] == src[i]);  // 33 -> 48 bytes moved
    CHECK(ram[0x100000 + 40] == 0);
    CHECK(e.sif.iop().stats().sif1_transfers == 1);
}

TEST_CASE("sif handshake: sceSifInitCmd + sceSifInitRpc complete through one SIF0 packet") {
    EeSide e;
    e.init_cmd();
    CHECK(e.iopbuf == e.get_reg(reg::kSubAddr));
    CHECK(e.get_reg(reg::kSysSubAddr) == e.iopbuf);
    CHECK(e.get_reg(reg::kSysMainAddr) == ee::kCmdData);
    CHECK(e.sif.iop().ee_receive_buffer() == ee::kRecvBuf);
    CHECK(e.bus.completions.empty());  // INIT_CMD(opt 0) has no answer
    e.init_rpc();
    CHECK(e.sregs[0] == 1);
    CHECK(e.get_reg(reg::kSysRpcInit) == 1);
    REQUIRE(e.packets.size() == 1);
    CHECK(load32(e.packets[0], 8) == cid::kSetSreg);
    CHECK(e.bus.completions == std::vector<unsigned>{5});
    CHECK(e.sif.iop().stats().sync_packets >= 2);  // libsifcmd's 0x80000004 rides along every SetDma
    // second sceSifInitRpc in the same boot: RPCINIT already set -> no traffic (B-17 path)
    const auto sent = e.sif.iop().stats().commands;
    if (!e.get_reg(reg::kSysRpcInit)) e.init_rpc();
    CHECK(e.sif.iop().stats().commands == sent);
}

TEST_CASE("sif reboot: sceSifRebootIop / sceSifSyncIop flag sequence completes, both orders") {
    for (const bool game_order : {true, false}) {
        CAPTURE(game_order);
        IopConfig cfg;
        cfg.reboot_cycles = 10'000;
        EeSide e(cfg);
        e.init_rpc();
        const u32 iopbuf = e.get_reg(reg::kSysSubAddr);
        // sceSifResetIop 0x50C848: StopDma, build the 104-byte packet, SetReg(4, BOOTEND) before the DMA
        // (game order) or after (ps2sdk SifIopReset order is the same; the reverse is tested too).
        e.sys(0x6B);
        const char* arg = "rom0:UDNL cdrom0:\\LIB31\\IOPRP310.IMG;1";
        const u32 pkt = 0x0096A100;
        for (u32 i = 0; i < 104; i += 4) e.w32(pkt + i, 0);
        const u32 len = static_cast<u32>(std::strlen(arg));
        e.write(pkt + 24, std::span(reinterpret_cast<const u8*>(arg), len));
        e.w32(pkt + 16, len);
        e.w32(pkt + 20, 0);
        e.w32(pkt + 8, cid::kResetCmd);
        e.w32(pkt + 0, 104);
        if (game_order) e.set_reg(reg::kSmFlag, flag::kBootEnd);
        REQUIRE(e.set_dma({DmaTransfer{pkt, iopbuf, 104, 0x44}}, false) != 0);
        if (!game_order) e.set_reg(reg::kSmFlag, flag::kBootEnd);
        e.set_reg(reg::kSmFlag, flag::kSifInit);
        e.set_reg(reg::kSmFlag, flag::kCmdInit);
        e.set_reg(reg::kSysRpcInit, 0);
        e.set_reg(reg::kSysSubAddr, 0);
        CHECK(e.sif.iop().rebooting());
        // sceSifSyncIop 0x50C9C8 polls BOOTEND
        int polls = 0;
        while (!(e.get_reg(reg::kSmFlag) & flag::kBootEnd)) {
            e.bus.advance(1'000);
            REQUIRE(++polls < 100);
        }
        CHECK(polls >= 9);
        CHECK_FALSE(e.sif.iop().rebooting());
        CHECK(e.get_reg(reg::kSmFlag) == flag::kAllBooted);
        CHECK(e.sif.iop().ee_receive_buffer() == 0);  // the new IOP does not know the EE buffer yet
        // post-reboot sceSifInitRpc (B-17): CMDINIT path again, then the RPCINIT handshake
        e.sregs.fill(0);
        e.sys(0x78);
        e.init_rpc();
        CHECK(e.sregs[0] == 1);
        CHECK(e.sif.iop().stats().reboots == 1);
        CHECK(e.bus.find(kRegSmflg) != nullptr);
    }
}

TEST_CASE("sif0: one packet per re-arm; the EE must consume before the next lands") {
    EeSide e;
    e.init_rpc();
    const u32 cd = e.bind(0x80000003u);  // heaplib
    // Two NOWAIT calls with end functions back to back, no pump in between.
    const u32 r1 = ee::kSendScratch + 0x900, r2 = ee::kSendScratch + 0x980;
    e.write(ee::kSendScratch + 0x200, words({256}));
    const auto before = e.bus.completions.size();
    e.call(cd, 1, 1, ee::kSendScratch + 0x200, 4, r1, 4, 0x500000, 1);
    // The second call reuses the client: give it its own client struct like a second caller would.
    const u32 cd2 = e.new_client();
    for (u32 i = 0; i < 64; i += 4) e.w32(cd2 + i, e.r32(cd + i));
    e.call(cd2, 1, 1, ee::kSendScratch + 0x200, 4, r2, 4, 0x500000, 2);
    CHECK(e.bus.completions.size() - before == 1);  // the second END waits behind the unconsumed first
    std::vector<u32> ends;
    e.on_end = [&](u32 p) { ends.push_back(p); };
    CHECK(e.pump() == 2);  // handler consumes #1, re-arms (isceSifSetDChain) -> #2 lands -> consumed
    CHECK(ends == std::vector<u32>{1, 2});
    CHECK(e.r32(r1) != 0);
    CHECK(e.r32(r2) != 0);
    CHECK(e.r32(r1) != e.r32(r2));
    CHECK_FALSE(e.check_stat(cd));
    CHECK_FALSE(e.check_stat(cd2));
}

TEST_CASE("sif0: nothing is delivered while SIF0 is stopped") {
    EeSide e;
    e.init_rpc();
    const u32 cd = e.bind(0x80000003u);
    e.sys(0x6B);  // sceSifStopDma
    e.write(ee::kSendScratch + 0x200, words({64}));
    e.call(cd, 1, 1, ee::kSendScratch + 0x200, 4, ee::kSendScratch + 0x900, 4, 0x500000, 7);
    CHECK(e.bus.pending_ch5 == 0);
    CHECK(e.sif.next_event_cycles() == ~0ull);  // waiting on the EE, not on time
    e.sys(0x78);
    CHECK(e.bus.pending_ch5 == 1);
}

TEST_CASE("sifrpc: bind -> call -> RPC end -> dma_complete(5) -> request_end, blocking mode") {
    EeSide e;
    e.init_rpc();
    const auto c0 = e.bus.completions.size();
    const u32 cd = e.bind(0x80000006u);  // loadfile
    CHECK(e.bus.completions.size() == c0 + 1);
    CHECK(e.r32(cd + 36) != 0);  // cd->server
    CHECK(e.r32(cd + 20) != 0);  // cd->buf (IOP receive buffer the next call's data goes to)
    CHECK(e.signaled[cd] == 1);
    CHECK_FALSE(e.check_stat(cd));
    const auto ver = e.call_sync(cd, 0xFF, {}, 4);
    CHECK(std::string(ver.begin(), ver.end()) == "3100");
    CHECK(e.signaled[cd] == 2);
    const RpcEnd end = decode_rpc_end(e.packets.back());
    CHECK(end.request_cid == cid::kRpcCall);
    CHECK(end.client == cd);
    CHECK(decode_cmd_header(e.packets.back()).dsize == 4);  // the reply travelled as extra data
}

TEST_CASE("sifrpc: NOWAIT without end function (rmode 0) frees the EE packet without an interrupt") {
    EeSide e;
    e.init_rpc();
    const u32 cd = e.bind(0x80000003u);
    const auto c0 = e.bus.completions.size();
    e.write(ee::kSendScratch + 0x200, words({128}));
    e.call(cd, 1, 1, ee::kSendScratch + 0x200, 4, ee::kSendScratch + 0x900, 4);
    CHECK(e.bus.completions.size() == c0);
    CHECK_FALSE(e.check_stat(cd));  // rend with rpc_id 0 landed on the request packet
    CHECK(e.r32(ee::kSendScratch + 0x900) != 0);  // the allocation result arrived
}

TEST_CASE("iop unknown ids: answered, counted, logged once") {
    std::vector<std::string> lines;
    IopConfig cfg;
    cfg.log = [&](std::string_view s) { lines.emplace_back(s); };
    EeSide e(cfg);
    e.init_rpc();
    const u32 cd = e.bind(0x8000F00Du);  // nothing binds this
    CHECK(e.r32(cd + 36) != 0);          // still answered, so the client's bind loop ends
    const auto r = e.call_sync(cd, 3, words({1, 2}), 8);
    CHECK(load32(r, 0) == 0);
    e.call_sync(cd, 3, words({1, 2}), 8);
    // an unknown command id
    e.w32(ee::kSendScratch + 16, 0);
    e.send_cmd(0x80000017u, ee::kSendScratch, 16);
    e.send_cmd(0x80000017u, ee::kSendScratch, 16);
    const auto ev = e.sif.iop().unknown_events();
    u64 server = 0, function = 0, command = 0;
    for (const auto& u : ev) {
        if (u.kind == UnknownEvent::Kind::Server && u.id == 0x8000F00Du) server = u.count;
        if (u.kind == UnknownEvent::Kind::Function && u.id == 0x8000F00Du && u.fno == 3) function = u.count;
        if (u.kind == UnknownEvent::Kind::Command && u.id == 0x80000017u) command = u.count;
    }
    CHECK(server == 1);
    CHECK(function == 2);
    CHECK(command == 2);
    int logged = 0;
    for (const auto& l : lines) logged += l.find("UNKNOWN") != std::string::npos ? 1 : 0;
    CHECK(logged == 3);  // first occurrence of each
    CHECK(e.sif.iop().unknown_total() == 5);
}

TEST_CASE("sif: register-started DMAC ch5/ch6 transfers are consumed and counted") {
    EeSide e;
    u128 q[2]{};
    CHECK(e.bus.handlers[6]->transfer(q, 2, 0) == 2);
    CHECK(e.sif.stats().unexpected_channel_transfers == 1);
}

TEST_CASE("sif: Deci2Call is a DECI2 manager without a host (libkernel TTY: open once, sends fail, ALREADYUSE)") {
    // Observed outcome in the PCSX2 first_flip state (TTY block 0x966650: socket -3 after the re-open, wlen 0x14
    // unsent, busy word 0); error values from ps2sdk deci2.h. Parameter blocks as sceDeci2Open 0x504440 builds them.
    EeSide e;
    const u32 blk = 0x00300000u;
    e.w32(blk + 0, 0x210);  // protocol (lhu)
    e.w32(blk + 4, 0x966650u);
    e.w32(blk + 8, 0x504720u);
    e.w32(blk + 12, 0x20966510u);
    const s32 sock = static_cast<s32>(e.sys(0x7C, 1, blk));
    CHECK(sock >= 0);
    CHECK(static_cast<s32>(e.sys(0x7C, 1, blk)) == -3);  // DECI2_ERR_ALREADYUSE
    e.w32(blk + 0x40, static_cast<u32>(sock));
    e.w32(blk + 0x44, 'H');
    CHECK(static_cast<s32>(e.sys(0x7C, 3, blk + 0x40)) == -10);  // ReqSend: DECI2_ERR_NOROUTE
    CHECK(static_cast<s32>(e.sys(0x7C, 4, blk + 0x40)) == 0);    // Poll
    e.w32(blk + 0x50, 77u);
    CHECK(static_cast<s32>(e.sys(0x7C, 3, blk + 0x50)) == -2);   // unknown socket: DECI2_ERR_INVALSOCK
    CHECK(static_cast<s32>(e.sys(0x7C, 2, blk + 0x40)) == 0);    // Close
    CHECK(static_cast<s32>(e.sys(0x7C, 4, blk + 0x40)) == -2);   // closed
    CHECK(static_cast<s32>(e.sys(0x7C, 1, blk)) >= 0);            // the protocol can be opened again
    CHECK(static_cast<s32>(e.sys(0x7C, 0x55, blk)) == -1);        // unknown function: DECI2_ERR_INVALID
}
