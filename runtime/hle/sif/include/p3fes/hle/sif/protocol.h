// SIF wire formats: register numbers, flag bits, command ids, SIF DMA transfer descriptors and the
// sifcmd / sifrpc packet layouts, as the game's own SDK 3.1 libsifcmd/libsifrpc use them.
//
// Sources (layouts and field names only, no text copied):
//   * ps2sdk @ 329e2bb (AFL-2.0): common/include/sifcmd-common.h (SifCmdHeader_t, SIF_CMD_*),
//     common/include/sifrpc-common.h (SifRpcBindPkt_t, SifRpcCallPkt_t, SifRpcRendPkt_t,
//     SifRpcOtherDataPkt_t), ee/kernel/include/sifdma.h (SifDmaTransfer_t, SIF_REG_*, SIF_STAT_*,
//     SIF_DMA_*).
//   * The recompiled EE libraries in SLUS_216.21, read with ps2dev objdump (obs, VAs below). Where
//     the game and ps2sdk differ the game wins and the difference is noted.
// Tags: obs = read from the game's instructions/bytes; der = derived from obs; inf = inferred.
#pragma once

#include <array>
#include <cstddef>
#include <cstring>
#include <span>

#include "p3fes/ee_types.h"

namespace p3fes::hle::sif {

// ---- little-endian field access ----------------------------------------------------------------
inline u32 load32(std::span<const u8> b, std::size_t off) {
    u32 v = 0;
    if (off + 4 <= b.size()) std::memcpy(&v, b.data() + off, 4);
    return v;
}
inline void store32(std::span<u8> b, std::size_t off, u32 v) {
    if (off + 4 <= b.size()) std::memcpy(b.data() + off, &v, 4);
}

// ---- SIF registers (sceSifSetReg / sceSifGetReg, syscalls 0x79 / 0x7A) ---------------------------
// 1..4 are the hardware mailboxes at 0x1000F200 + 0x10*(n-1); 0x80000000.. are kernel software
// registers (sifdma.h: "implemented in software").
namespace reg {
inline constexpr u32 kMainAddr = 1;            // MSCOM 0x1000F200 (EE -> IOP)
inline constexpr u32 kSubAddr = 2;             // SMCOM 0x1000F210 (IOP -> EE): IOP sifcmd buffer
inline constexpr u32 kMsFlag = 3;              // MSFLG 0x1000F220
inline constexpr u32 kSmFlag = 4;              // SMFLG 0x1000F230
inline constexpr u32 kSystem = 0x80000000u;
inline constexpr u32 kSysSubAddr = 0x80000000u;   // IOP sifcmd buffer as remembered by the EE
inline constexpr u32 kSysMainAddr = 0x80000001u;  // &_sif_cmd_data (0x966A58 in this game, obs 0x506370)
inline constexpr u32 kSysRpcInit = 0x80000002u;   // sifrpc handshake done (obs 0x5069C4, 0x506A28)
inline constexpr u32 kSystemCount = 32;           // inf: size of the kernel's software table
}  // namespace reg

// SMFLG / MSFLG bits.
namespace flag {
inline constexpr u32 kSifInit = 0x10000u;
inline constexpr u32 kCmdInit = 0x20000u;   // polled by sceSifInitCmd 0x50633C
inline constexpr u32 kBootEnd = 0x40000u;   // polled by sceSifSyncIop 0x50C9C8
inline constexpr u32 kAllBooted = kSifInit | kCmdInit | kBootEnd;
}  // namespace flag

// Physical addresses of the SIF register block (EE side).
inline constexpr u32 kRegBase = 0x1000F200u;
inline constexpr u32 kRegMscom = 0x1000F200u;
inline constexpr u32 kRegSmcom = 0x1000F210u;
inline constexpr u32 kRegMsflg = 0x1000F220u;
inline constexpr u32 kRegSmflg = 0x1000F230u;
inline constexpr u32 kRegCtrl = 0x1000F240u;
inline constexpr u32 kRegBd6 = 0x1000F260u;
inline constexpr u32 kRegEnd = 0x1000F270u;  // exclusive end of the mapped range

// ---- SIF DMA (sceSifSetDma, syscall 0x77) -------------------------------------------------------
namespace dma_attr {
inline constexpr u32 kIntI = 0x02;
inline constexpr u32 kIntO = 0x04;  // interrupt the receiver when this transfer lands
inline constexpr u32 kErt = 0x40;   // end of the DMA chain
}  // namespace dma_attr

// SifDmaTransfer_t: 16 bytes, an array of `count` is passed in $a0.
struct DmaTransfer {
    u32 src = 0;   // EE address (kseg / uncached forms accepted)
    u32 dest = 0;  // IOP address
    u32 size = 0;  // bytes; the hardware moves whole quadwords (see Sif::sif1_copy_bytes)
    u32 attr = 0;
};
inline constexpr std::size_t kDmaTransferSize = 16;
inline DmaTransfer decode_dma_transfer(std::span<const u8> b) {
    return DmaTransfer{load32(b, 0), load32(b, 4), load32(b, 8), load32(b, 12)};
}
inline void encode_dma_transfer(const DmaTransfer& t, std::span<u8> b) {
    store32(b, 0, t.src);
    store32(b, 4, t.dest);
    store32(b, 8, t.size);
    store32(b, 12, t.attr);
}

// ---- sifcmd ---------------------------------------------------------------------------------------
// Command ids. System ids carry bit 31; the EE dispatches system ids through its 32-entry system
// table and the rest through the (here unused) user table (sceSifCmdIntrHdlr 0x5066B0, obs).
namespace cid {
inline constexpr u32 kSystem = 0x80000000u;
inline constexpr u32 kChangeSaddr = 0x80000000u;  // EE -> IOP and IOP -> EE: new receive buffer
inline constexpr u32 kSetSreg = 0x80000001u;      // set a software register on the receiver
inline constexpr u32 kInitCmd = 0x80000002u;      // opt 0: sifcmd init (+16 = EE buffer); opt 1: sifrpc init
inline constexpr u32 kResetCmd = 0x80000003u;     // IOP reboot request (sceSifResetIop 0x50C848)
// obs: the 16-byte packet libsifcmd appends to every sceSifSetDma (bytes at 0x7BDD00 =
// {psize 16, dsize 0, dest 0, cid 0x80000004, opt 0}; sceSifSetDmaInternal 0x505FC0). Not in ps2sdk.
inline constexpr u32 kDmaSync = 0x80000004u;
inline constexpr u32 kRpcEnd = 0x80000008u;
inline constexpr u32 kRpcBind = 0x80000009u;
inline constexpr u32 kRpcCall = 0x8000000Au;
inline constexpr u32 kRpcRdata = 0x8000000Cu;
inline constexpr u32 kFileioResult = 0x80000011u;  // obs: sceFsInit 0x5081C4 -> _sceFs_Rcv_Intr 0x507C38
inline constexpr u32 kCdvdPowerOff = 0x80000012u;  // obs: 0x50FBF8 (cdvd power-off callback)
inline constexpr u32 kFileioPowerOff = 0x80000013u;  // obs: sceFsInit 0x5081D8 -> _sceFs_Poff_Intr
inline constexpr u32 kPad = 0x80000019u;           // obs: scePadInit2 0x511390; EE sends it at shutdown
}  // namespace cid

// SifCmdHeader_t (16 bytes): psize:8 | dsize:24, dest, cid, opt.
struct CmdHeader {
    u32 psize = 0;  // packet bytes incl. this header (16..112 from the EE: _sceSifSendCmd 0x50652C)
    u32 dsize = 0;  // bytes of extra data sent ahead of the packet (24 bits)
    u32 dest = 0;   // where the extra data went
    u32 cid = 0;
    u32 opt = 0;
};
inline constexpr std::size_t kCmdHeaderSize = 16;
inline constexpr std::size_t kCmdPacketMax = 112;  // obs 0x506514: (psize - 16) < 97
inline CmdHeader decode_cmd_header(std::span<const u8> b) {
    const u32 w0 = load32(b, 0);
    return CmdHeader{w0 & 0xFFu, w0 >> 8, load32(b, 4), load32(b, 8), load32(b, 12)};
}
inline void encode_cmd_header(const CmdHeader& h, std::span<u8> b) {
    store32(b, 0, (h.psize & 0xFFu) | (h.dsize << 8));
    store32(b, 4, h.dest);
    store32(b, 8, h.cid);
    store32(b, 12, h.opt);
}

// Payload words of the system commands (after the 16-byte header).
inline constexpr std::size_t kChangeSaddrBuf = 16;  // ca_pkt.buf
inline constexpr std::size_t kSetSregIndex = 16;    // SifCmdSRegData_t.index
inline constexpr std::size_t kSetSregValue = 20;
inline constexpr std::size_t kSetSregSize = 24;
inline constexpr std::size_t kResetArglen = 16;     // SifCmdResetData_t.arglen
inline constexpr std::size_t kResetMode = 20;
inline constexpr std::size_t kResetArg = 24;        // char arg[80]
inline constexpr std::size_t kResetSize = 104;      // obs 0x50C910: psize 104

// ---- sifrpc ---------------------------------------------------------------------------------------
inline constexpr std::size_t kRpcPacketSize = 64;  // RPC_PACKET_SIZE; every bind/call/end is 64 bytes

// Common SifRpcPktHeader_t words after the sifcmd header.
inline constexpr std::size_t kRpcRecId = 16;
inline constexpr std::size_t kRpcPktAddr = 20;
inline constexpr std::size_t kRpcRpcId = 24;
inline constexpr std::size_t kRpcClient = 28;  // EE SifRpcClientData_t* (bind/call/end)

// SifRpcBindPkt_t (obs sceSifBindRpc 0x507050: sid stored at +32).
inline constexpr std::size_t kBindSid = 32;
// SifRpcCallPkt_t (obs sceSifCallRpc 0x507230: +32 rpc_number, +36 send_size, +40 recvbuf,
// +44 recv_size, +48 rmode, +52 server).
inline constexpr std::size_t kCallRpcNumber = 32;
inline constexpr std::size_t kCallSendSize = 36;
inline constexpr std::size_t kCallRecvBuf = 40;
inline constexpr std::size_t kCallRecvSize = 44;
inline constexpr std::size_t kCallRmode = 48;
inline constexpr std::size_t kCallServer = 52;
// SifRpcRendPkt_t (obs _request_end 0x506BA8 reads +28 cd, +32 cid, +36 sd, +40 buf).
inline constexpr std::size_t kEndCid = 32;
inline constexpr std::size_t kEndServer = 36;
inline constexpr std::size_t kEndBuf = 40;
inline constexpr std::size_t kEndCbuf = 44;
// SifRpcOtherDataPkt_t (sceSifGetOtherData; no caller in this game).
inline constexpr std::size_t kRdataRecvBuf = 28;
inline constexpr std::size_t kRdataSrc = 32;
inline constexpr std::size_t kRdataDest = 36;
inline constexpr std::size_t kRdataSize = 40;

using RpcPacket = std::array<u8, kRpcPacketSize>;

struct RpcBind {
    u32 rec_id = 0, pkt_addr = 0, rpc_id = 0, client = 0, sid = 0;
};
struct RpcCall {
    u32 rec_id = 0, pkt_addr = 0, rpc_id = 0, client = 0;
    u32 rpc_number = 0, send_size = 0, recv_buf = 0, recv_size = 0, rmode = 0, server = 0;
};
struct RpcEnd {
    u32 rec_id = 0, pkt_addr = 0, rpc_id = 0, client = 0;
    u32 request_cid = 0;  // kRpcBind / kRpcCall / kRpcRdata: what _request_end acts on
    u32 server = 0, buf = 0, cbuf = 0;
};
struct RpcRdata {
    u32 rec_id = 0, pkt_addr = 0, rpc_id = 0, recv_data = 0, src = 0, dest = 0, size = 0;
};

inline RpcBind decode_rpc_bind(std::span<const u8> p) {
    return RpcBind{load32(p, kRpcRecId), load32(p, kRpcPktAddr), load32(p, kRpcRpcId), load32(p, kRpcClient),
                   load32(p, kBindSid)};
}
inline RpcCall decode_rpc_call(std::span<const u8> p) {
    return RpcCall{load32(p, kRpcRecId),     load32(p, kRpcPktAddr),    load32(p, kRpcRpcId),
                   load32(p, kRpcClient),    load32(p, kCallRpcNumber), load32(p, kCallSendSize),
                   load32(p, kCallRecvBuf),  load32(p, kCallRecvSize),  load32(p, kCallRmode),
                   load32(p, kCallServer)};
}
inline RpcEnd decode_rpc_end(std::span<const u8> p) {
    return RpcEnd{load32(p, kRpcRecId), load32(p, kRpcPktAddr), load32(p, kRpcRpcId), load32(p, kRpcClient),
                  load32(p, kEndCid),   load32(p, kEndServer),  load32(p, kEndBuf),   load32(p, kEndCbuf)};
}
inline RpcRdata decode_rpc_rdata(std::span<const u8> p) {
    return RpcRdata{load32(p, kRpcRecId), load32(p, kRpcPktAddr), load32(p, kRpcRpcId), load32(p, kRdataRecvBuf),
                    load32(p, kRdataSrc), load32(p, kRdataDest),  load32(p, kRdataSize)};
}

// Encoders write the sifcmd header too (cid, psize = 64; dsize/dest describe extra data).
inline RpcPacket encode_rpc_bind(const RpcBind& b) {
    RpcPacket p{};
    encode_cmd_header(CmdHeader{kRpcPacketSize, 0, 0, cid::kRpcBind, 0}, p);
    store32(p, kRpcRecId, b.rec_id);
    store32(p, kRpcPktAddr, b.pkt_addr);
    store32(p, kRpcRpcId, b.rpc_id);
    store32(p, kRpcClient, b.client);
    store32(p, kBindSid, b.sid);
    return p;
}
inline RpcPacket encode_rpc_call(const RpcCall& c, u32 dsize = 0, u32 dest = 0) {
    RpcPacket p{};
    encode_cmd_header(CmdHeader{kRpcPacketSize, dsize, dest, cid::kRpcCall, 0}, p);
    store32(p, kRpcRecId, c.rec_id);
    store32(p, kRpcPktAddr, c.pkt_addr);
    store32(p, kRpcRpcId, c.rpc_id);
    store32(p, kRpcClient, c.client);
    store32(p, kCallRpcNumber, c.rpc_number);
    store32(p, kCallSendSize, c.send_size);
    store32(p, kCallRecvBuf, c.recv_buf);
    store32(p, kCallRecvSize, c.recv_size);
    store32(p, kCallRmode, c.rmode);
    store32(p, kCallServer, c.server);
    return p;
}
inline RpcPacket encode_rpc_end(const RpcEnd& e, u32 dsize = 0, u32 dest = 0) {
    RpcPacket p{};
    encode_cmd_header(CmdHeader{kRpcPacketSize, dsize, dest, cid::kRpcEnd, 0}, p);
    store32(p, kRpcRecId, e.rec_id);
    store32(p, kRpcPktAddr, e.pkt_addr);
    store32(p, kRpcRpcId, e.rpc_id);
    store32(p, kRpcClient, e.client);
    store32(p, kEndCid, e.request_cid);
    store32(p, kEndServer, e.server);
    store32(p, kEndBuf, e.buf);
    store32(p, kEndCbuf, e.cbuf);
    return p;
}

// sceSifCallRpc mode bits (sifrpc-common.h). rmode in the call packet: 1 = the IOP must answer
// with an RPC_END (blocking call, or NOWAIT with an end function); 0 = NOWAIT without end function:
// the IOP only DMAs the reply data and a 64-byte "rend" packet with rpc_id = rec_id = 0 over the
// EE's request packet (sceSifCheckStatRpc 0x507430 then reports done), no interrupt.
namespace rpc_mode {
inline constexpr u32 kNoWait = 0x01;
inline constexpr u32 kNoWbdc = 0x02;
}  // namespace rpc_mode

}  // namespace p3fes::hle::sif
