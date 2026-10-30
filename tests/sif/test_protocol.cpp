// Packet layouts: encode/decode round trips and the offsets against the ps2sdk struct layouts
// (sifcmd-common.h / sifrpc-common.h / sifdma.h @ 329e2bb) and the game's own accesses.
#include <doctest.h>

#include <cstddef>

#include "../../runtime/hle/sif/iop/iop_core.h"
#include "../../runtime/hle/sif/iop/srv_cdvdfsv.h"
#include "../../runtime/hle/sif/iop/srv_padman.h"
#include "p3fes/hle/sif/protocol.h"

using namespace p3fes;
using namespace p3fes::hle::sif;

namespace {
// Mirrors of the ps2sdk structs (32-bit IOP/EE ABI: pointers are u32 here).
struct PsCmdHeader { u32 psize_dsize; u32 dest; s32 cid; u32 opt; };
struct PsRpcCallPkt { PsCmdHeader sifcmd; s32 rec_id; u32 pkt_addr; s32 rpc_id; u32 cd; s32 rpc_number; s32 send_size;
                      u32 recvbuf; s32 recv_size; s32 rmode; u32 sd; };
struct PsRpcRendPkt { PsCmdHeader sifcmd; s32 rec_id; u32 pkt_addr; s32 rpc_id; u32 cd; u32 cid; u32 sd; u32 buf, cbuf; };
struct PsRpcBindPkt { PsCmdHeader sifcmd; s32 rec_id; u32 pkt_addr; s32 rpc_id; u32 cd; s32 sid; };
struct PsDmaTransfer { u32 src, dest; s32 size, attr; };
struct PsResetPkt { PsCmdHeader header; s32 arglen; s32 mode; char arg[80]; };
}  // namespace

TEST_CASE("sif protocol: offsets agree with the ps2sdk layouts") {
    CHECK(offsetof(PsRpcCallPkt, rec_id) == kRpcRecId);
    CHECK(offsetof(PsRpcCallPkt, pkt_addr) == kRpcPktAddr);
    CHECK(offsetof(PsRpcCallPkt, rpc_id) == kRpcRpcId);
    CHECK(offsetof(PsRpcCallPkt, cd) == kRpcClient);
    CHECK(offsetof(PsRpcCallPkt, rpc_number) == kCallRpcNumber);
    CHECK(offsetof(PsRpcCallPkt, send_size) == kCallSendSize);
    CHECK(offsetof(PsRpcCallPkt, recvbuf) == kCallRecvBuf);
    CHECK(offsetof(PsRpcCallPkt, recv_size) == kCallRecvSize);
    CHECK(offsetof(PsRpcCallPkt, rmode) == kCallRmode);
    CHECK(offsetof(PsRpcCallPkt, sd) == kCallServer);
    CHECK(offsetof(PsRpcRendPkt, cid) == kEndCid);
    CHECK(offsetof(PsRpcRendPkt, sd) == kEndServer);
    CHECK(offsetof(PsRpcRendPkt, buf) == kEndBuf);
    CHECK(offsetof(PsRpcRendPkt, cbuf) == kEndCbuf);
    CHECK(offsetof(PsRpcBindPkt, sid) == kBindSid);
    CHECK(sizeof(PsDmaTransfer) == kDmaTransferSize);
    CHECK(sizeof(PsResetPkt) == kResetSize);
    CHECK(offsetof(PsResetPkt, arg) == kResetArg);
    CHECK(sizeof(PsRpcCallPkt) <= kRpcPacketSize);
}

TEST_CASE("sif protocol: command header round trip, psize in the low byte") {
    CmdHeader h{64, 0x123456, 0x01F00010, cid::kRpcCall, 7};
    std::array<u8, 16> b{};
    encode_cmd_header(h, b);
    CHECK(b[0] == 64);  // sceSifCmdIntrHdlr reads psize with lbu at +0 (obs 0x5066CC)
    CHECK(load32(b, 0) == (64u | (0x123456u << 8)));
    const CmdHeader d = decode_cmd_header(b);
    CHECK(d.psize == 64);
    CHECK(d.dsize == 0x123456);
    CHECK(d.dest == 0x01F00010);
    CHECK(d.cid == cid::kRpcCall);
    CHECK(d.opt == 7);
}

TEST_CASE("sif protocol: bind / call / end packets round trip") {
    RpcBind b{0x10005, 0x966CC0, 42, 0x968000, 0x80000592u};
    const RpcPacket bp = encode_rpc_bind(b);
    CHECK(decode_cmd_header(bp).cid == cid::kRpcBind);
    CHECK(decode_cmd_header(bp).psize == 64);
    const RpcBind b2 = decode_rpc_bind(bp);
    CHECK(b2.rec_id == b.rec_id);
    CHECK(b2.pkt_addr == b.pkt_addr);
    CHECK(b2.rpc_id == b.rpc_id);
    CHECK(b2.client == b.client);
    CHECK(b2.sid == b.sid);

    RpcCall c{5, 0x966D00, 9, 0x781D50, 1, 24, 0, 0, 1, 0x20040};
    const RpcPacket cp = encode_rpc_call(c, 24, 0x20100);
    const CmdHeader ch = decode_cmd_header(cp);
    CHECK(ch.dsize == 24);
    CHECK(ch.dest == 0x20100);
    const RpcCall c2 = decode_rpc_call(cp);
    CHECK(c2.rpc_number == 1);
    CHECK(c2.send_size == 24);
    CHECK(c2.rmode == 1);
    CHECK(c2.server == 0x20040);
    CHECK(c2.client == 0x781D50);

    RpcEnd e{1, 2, 3, 0x96DCC0, cid::kRpcBind, 0x20000, 0x20040, 0};
    const RpcPacket ep = encode_rpc_end(e, 128, 0x96DF00);
    CHECK(decode_cmd_header(ep).cid == cid::kRpcEnd);
    CHECK(decode_cmd_header(ep).dsize == 128);
    const RpcEnd e2 = decode_rpc_end(ep);
    CHECK(e2.client == 0x96DCC0);
    CHECK(e2.request_cid == cid::kRpcBind);
    CHECK(e2.server == 0x20000);
    CHECK(e2.buf == 0x20040);
}

TEST_CASE("sif protocol: DMA transfer descriptor round trip") {
    DmaTransfer t{0x96A100, 0x1E000, 104, 0x44};
    std::array<u8, 16> b{};
    encode_dma_transfer(t, b);
    const DmaTransfer d = decode_dma_transfer(b);
    CHECK(d.src == t.src);
    CHECK(d.dest == t.dest);
    CHECK(d.size == t.size);
    CHECK(d.attr == (dma_attr::kErt | dma_attr::kIntO));
}

TEST_CASE("sif protocol: unaligned split follows cdvdfsv's head/body/tail rule") {
    using hle::sif::detail::split_unaligned;
    auto a = split_unaligned(0x100000, 2048);
    CHECK(a.head == 0);
    CHECK(a.body == 2048);
    CHECK(a.tail == 0);
    CHECK(a.tail_addr == 0x100800);
    auto u = split_unaligned(0x100005, 2048);
    CHECK(u.head == 59);
    CHECK(u.tail == 5);
    CHECK(u.body == 2048 - 64);
    CHECK(u.tail_addr == 0x100800);
    CHECK(((0x100005 + u.head) & 63) == 0);
    auto one = split_unaligned(0x1F00F31, 1);  // fileio's byte reads into the stack
    CHECK(one.head == 1);
    CHECK(one.body == 0);
    CHECK(one.tail == 0);
}

TEST_CASE("sif protocol: sceCdlFILE reply formatting") {
    using namespace hle::sif::detail;
    const u8 rec[7] = {106, 1, 4, 13, 45, 30, 0};  // 2006-01-04 13:45:30
    const auto date = cdl_date_from_iso(std::span<const u8, 7>(rec));
    CHECK(date[0] == 0);
    CHECK(date[1] == 30);
    CHECK(date[2] == 45);
    CHECK(date[3] == 13);
    CHECK(date[4] == 4);
    CHECK(date[5] == 1);
    CHECK((date[6] | (date[7] << 8)) == 2006);
    const auto fp = encode_cdl_file(584'363, 3'367'428'096u, "DATA.CVM;1", date, 0);
    CHECK(load32(fp, 0) == 584'363u);
    CHECK(load32(fp, 4) == 3'367'428'096u);
    CHECK(std::string(reinterpret_cast<const char*>(fp.data() + 8)) == "DATA.CVM;1");
    CHECK(fp[8 + 10] == 0);
    CHECK(fp[24 + 1] == 30);
    CHECK(load32(fp, 32) == 0);
    const auto longname = encode_cdl_file(1, 1, "ABCDEFGHIJKLMNOPQRS;1", date, 2);
    CHECK(longname[8 + 14] == 'O');
    CHECK(longname[8 + 15] == 0);  // truncated to 15 + NUL (inf)
    CHECK(load32(longname, 32) == 2);
}

TEST_CASE("sif protocol: PADMAN frame encoding") {
    using namespace hle::sif::detail;
    PadPortState p;
    p.counter = 7;
    p.mode_id = kPadIdDualShock;
    p.mode_offs = 1;
    p.input.buttons = hle::sif::pad_button::kStart | hle::sif::pad_button::kCross;
    p.input.lx = 0x10;
    const auto f = encode_pad_frame(p);
    CHECK(load32(f, pad_frame::kFrame) == 7);
    CHECK(f[0] == 0x00);
    CHECK(f[1] == 0x73);
    CHECK(f[2] == static_cast<u8>(~0x08u));  // Start, active low
    CHECK(f[3] == static_cast<u8>(~0x40u));  // Cross
    CHECK(f[4] == 0x80);
    CHECK(f[6] == 0x10);
    CHECK(load32(f, pad_frame::kLength) == 32);
    CHECK(f[pad_frame::kState] == pad_state::kStable);
    CHECK(f[pad_frame::kCurrentTask] == 1);
    CHECK(f[pad_frame::kModeConfig] >= 2);
    CHECK((f[pad_frame::kModeCurId] >> 4) == 7);  // InfoMode(PAD_MODECURID) = type 7 (DUALSHOCK)
    PadPortState off;
    off.input.connected = false;
    const auto g = encode_pad_frame(off);
    CHECK(g[pad_frame::kState] == pad_state::kDisconnected);
    CHECK(g[2] == 0xFF);
}
