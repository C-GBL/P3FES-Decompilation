// IOP servers driven the way the game's clients drive them (request layouts: the client VAs cited in
// runtime/hle/sif/iop/*.cpp).
#include <doctest.h>

#include <cstring>
#include <string>

#include "sif_harness.h"

using namespace p3fes;
using namespace p3fes::test;

namespace {
std::vector<u8> lf_load_arg(const std::string& path, const std::string& args) {
    std::vector<u8> b(512, 0);  // _lf_module_load_arg at 0x969EC0
    store32(b, 0, static_cast<u32>(args.size()));
    std::memcpy(b.data() + 8, path.data(), path.size());
    std::memcpy(b.data() + 260, args.data(), args.size());
    return b;
}
}  // namespace

TEST_CASE("loadfile: version 3100 and the 15 IRX loads of kwlnInitPS2Systems in order") {
    EeSide e;
    e.init_rpc();
    const u32 cd = e.bind(0x80000006u);
    const auto ver = e.call_sync(cd, 0xFF, {}, 4);
    CHECK(std::memcmp(ver.data(), "3100", 4) == 0);  // 0x50BBE8 rejects anything else
    const char* names[] = {"SIO2MAN", "SIO2D",   "PADMAN",  "DBCMAN",  "MC2_S1",   "LIBSD",    "CRI_ADXI", "SDRDRV",
                           "MODHSYN", "MODMSIN", "MODSESQ", "SKSOUND", "SKHSYNTH", "SKHSYNTH", "SKSESQ"};
    const std::string cri_args("sdinit=0 spucore=1\0\0", 20);
    const std::string sesq_args("maxtrack=16\0maxentry=16\0", 24);
    for (int i = 0; i < 15; ++i) {
        const std::string path = std::string("cdrom0:\\LIB31\\") + names[i] + ".IRX;1";
        const std::string args = i == 6 ? cri_args : i == 14 ? sesq_args : std::string();
        const auto r = e.call_sync(cd, 0, lf_load_arg(path, args), 8);
        CHECK(static_cast<s32>(load32(r, 0)) == i + 1);  // >= 0 ends the retry loop; sequential
        CHECK(load32(r, 4) == 0);                        // *modres
    }
    const auto mods = e.sif.iop().modules();
    REQUIRE(mods.size() == 15);
    CHECK(mods[0].path == "cdrom0:\\LIB31\\SIO2MAN.IRX;1");
    CHECK(mods[12].path == mods[13].path);  // the duplicate SKHSYNTH
    CHECK(mods[13].id == 14);
    CHECK(mods[6].args == cri_args);
    CHECK(mods[14].args == sesq_args);
    CHECK(mods[14].path == "cdrom0:\\LIB31\\SKSESQ.IRX;1");
}

TEST_CASE("heaplib: allocations distinct and non-zero, free, queries") {
    EeSide e;
    e.init_rpc();
    const u32 cd = e.bind(0x80000003u);
    std::vector<u32> addrs;
    for (u32 size : {2256u, 64u + (32u << 10), 1u, 100000u}) {
        const auto r = e.call_sync(cd, 1, words({size}), 4);  // AllocIopHeap
        addrs.push_back(load32(r, 0));
    }
    for (int i = 0; i < 6; ++i) {
        const auto r = e.call_sync(cd, 4, words({4096, 0, 0}), 4);  // AllocSysMemory(0, size, 0), H_Sndcom_Update
        addrs.push_back(load32(r, 0));
    }
    for (std::size_t i = 0; i < addrs.size(); ++i) {
        CHECK(addrs[i] != 0);
        CHECK(addrs[i] < 0x200000u);
        CHECK((addrs[i] & 0xFF) == 0);
        for (std::size_t j = 0; j < i; ++j) CHECK(addrs[i] != addrs[j]);
    }
    const u32 free_before = e.sif.iop().heap_free_total();
    CHECK(load32(e.call_sync(cd, 2, words({addrs[3]}), 4), 0) == 0);  // FreeSysMemory
    CHECK(e.sif.iop().heap_free_total() > free_before);
    CHECK(static_cast<s32>(load32(e.call_sync(cd, 2, words({addrs[3]}), 4), 0)) == -1);  // double free
    CHECK(load32(e.call_sync(cd, 5, {}, 4), 0) == 0x200000u);                           // QueryMemSize
    CHECK(load32(e.call_sync(cd, 7, {}, 4), 0) == e.sif.iop().heap_free_total());
    const auto huge = e.call_sync(cd, 1, words({0x01000000u}), 4);
    CHECK(load32(huge, 0) == 0);  // exhausted -> 0, as heaplib reports it
}

TEST_CASE("fileio: rom0:ROMVER served through the 0x80000011 result path") {
    EeSide e;
    e.init_rpc();
    const u32 cd = e.bind(0x80000001u);
    // sceFsInit fn 0xFF: {result buffer, +1088} -> {"3100", mode}
    const auto init = e.call_sync(cd, 0xFF, words({ee::kFsResultBuf, ee::kFsResultBuf + 1088}), 8);
    CHECK(std::memcmp(init.data(), "3100", 4) == 0);
    CHECK(load32(init, 4) != 2);
    // sceOpen("rom0:ROMVER", 1): {+0 sema, +4 result addr, +8 4, +12 mode, +16 0, +20 path}
    const u32 res = 0x01F02000;
    std::vector<u8> open(1048, 0);
    store32(open, 0, 3);
    store32(open, 4, res);
    store32(open, 8, 4);
    store32(open, 12, 1);
    std::memcpy(open.data() + 20, "rom0:ROMVER", 11);
    const auto acc = e.call_sync(cd, 0, open, 4);
    CHECK(load32(acc, 0) != 0);  // accepted (sceOpen 0x508854 checks)
    CHECK(e.fs_results == 1);    // result command followed the RPC end in the same pump
    const s32 fd = static_cast<s32>(e.r32(res));
    CHECK(fd >= 0);
    // checkModelVersion 0x4F90B8: one-byte sceRead into consecutive stack bytes until NUL
    const u32 stack = 0x01F03005;  // deliberately not aligned
    std::string text;
    for (int i = 0; i < 32; ++i) {
        std::vector<u8> rd(32, 0);
        store32(rd, 0, 3);
        store32(rd, 4, res);
        store32(rd, 8, 4);
        store32(rd, 12, static_cast<u32>(fd));
        store32(rd, 16, stack + static_cast<u32>(i));
        store32(rd, 20, 1);
        e.call_sync(cd, 2, rd, 4);
        REQUIRE(e.r32(res) == 1);
        const u8 c = e.read(stack + static_cast<u32>(i), 1)[0];
        if (c == 0) break;
        text.push_back(static_cast<char>(c));
    }
    CHECK(text == "0230AC20080220\n");  // the user's BIOS ROMVER (v02.30 USA): a "new" model
    std::vector<u8> cl(20, 0);
    store32(cl, 0, 3);
    store32(cl, 4, res);
    store32(cl, 8, 4);
    store32(cl, 12, static_cast<u32>(fd));
    e.call_sync(cd, 1, cl, 4);
    CHECK(e.r32(res) == 0);
    // unknown path -> -ENOENT, counted
    std::memcpy(open.data() + 20, "cdrom0:\\SLPM_664.45;1", 21);
    e.call_sync(cd, 0, open, 4);
    CHECK(static_cast<s32>(e.r32(res)) < 0);
}

TEST_CASE("padman: init, port open, DUALSHOCK2 frames per vblank, mode change, host input") {
    EeSide e;
    e.init_rpc();
    const u32 cd = e.bind(0x80000100u);
    const u32 cd2 = e.bind(0x80000101u);
    CHECK(e.r32(cd2 + 36) != 0);  // bound, never called (`12` §2.1)
    auto pad_call = [&](std::initializer_list<u32> w) {
        std::vector<u8> b(128, 0);
        std::size_t i = 0;
        for (u32 x : w) {
            store32(b, i, x);
            i += 4;
        }
        return e.call_sync(cd, 1, b, 128);
    };
    CHECK((load32(pad_call({18}), 12) >> 8) == 4);  // GetModVersion: scePadInit requires major 4
    CHECK(load32(pad_call({16, 0, 0, 0, 0, 0x782754}), 12) == 1);  // Init2
    const u32 buf0 = 0x00900000, buf1 = 0x00900100;
    // scePadPortOpen initialises both frames itself (0x511660): counter 0, state EXECCMD, reqState BUSY
    for (u32 b : {buf0, buf1})
        for (u32 f = 0; f < 2; ++f) {
            e.w32(b + f * 128 + 88, 0);
            e.mem.write<u8>(b + f * 128 + 112, 5);
            e.mem.write<u8>(b + f * 128 + 113, 2);
        }
    const auto po = pad_call({1, 0, 0, 0, buf0});
    CHECK(load32(po, 12) == 1);
    CHECK(load32(po, 20) != 0);  // IOP buffer for _send_to_iop
    pad_call({1, 1, 0, 0, buf1});
    CHECK(load32(pad_call({12}), 12) == 2);
    CHECK(load32(pad_call({13, 0}), 12) == 1);
    auto newest = [&](u32 b) {  // scePadGetDmaStr 0x511830
        const u32 f0 = e.r32(b + 88), f1 = e.r32(b + 216);
        return e.read(b + (f0 < f1 ? 128u : 0u), 128);
    };
    PadInput in;
    in.buttons = pad_button::kStart;
    e.sif.iop().set_pad_input(0, in);
    // PADMAN's first frame after PortOpen carries counter 0 into the second half, so the EE keeps
    // reading libpad's own initialisation until the second frame (as with padPortOpen's frame = 0).
    e.bus.vblank();
    e.sif.service();
    CHECK(newest(buf0)[112] == 5);
    e.bus.vblank();
    e.sif.service();
    auto f = newest(buf0);
    CHECK(f[112] == 6);     // scePadStateStable
    CHECK(f[1] == 0x41);    // digital until the game selects DUALSHOCK
    CHECK(f[2] == static_cast<u8>(~pad_button::kStart & 0xFF));
    CHECK(f[3] == 0xFF);
    CHECK(load32(f, 96) == 32);
    CHECK(newest(buf1)[112] == 0);  // port 1: no controller (inf default)
    // scePadSetMainMode(0, 0, 1, 3)
    CHECK(load32(pad_call({6, 0, 0, 1, 3}), 20) == 1);
    e.bus.vblank();
    e.sif.service();
    f = newest(buf0);
    CHECK(f[113] == 2);  // reqState BUSY for one frame -> scePadGetState reports EXECCMD
    e.bus.vblank();
    e.sif.service();
    f = newest(buf0);
    CHECK(f[113] == 0);
    CHECK(f[1] == 0x73);
    CHECK((f[101] >> 4) == 7);
    CHECK(f[4] == 0x80);
    CHECK(f[5] == 0x80);
    CHECK(f[6] == 0x80);
    CHECK(f[7] == 0x80);
    const u32 c1 = std::max(e.r32(buf0 + 88), e.r32(buf0 + 216));
    e.sif.service();  // no new vblank -> no new frame
    CHECK(std::max(e.r32(buf0 + 88), e.r32(buf0 + 216)) == c1);
    e.bus.vblank();
    e.sif.service();
    CHECK(std::max(e.r32(buf0 + 88), e.r32(buf0 + 216)) == c1 + 1);
    CHECK(e.sif.iop().stats().pad_frames >= 4);
}

TEST_CASE("dbcman: version, socket, and no memory card") {
    EeSide e;
    e.init_rpc();
    const u32 cd = e.bind(0x80001300u);
    for (u32 sid : {0x8000131Cu, 0x8000131Eu, 0x8000131Fu}) CHECK(e.r32(e.bind(sid) + 36) != 0);
    auto dbc = [&](u32 fno, std::initializer_list<u32> w) {
        std::vector<u8> b(144, 0);
        std::size_t i = 0;
        for (u32 x : w) {
            store32(b, i, x);
            i += 4;
        }
        return e.call_sync(cd, fno, b, 144);
    };
    CHECK((load32(dbc(0x80001363u, {}), 0) >> 4) == 50);  // sceDbcInit 0x51C478
    const u32 work = 0x00997140;
    for (u32 i = 0; i < 64; i += 4) e.w32(work + i, 0);
    dbc(0x80001304u, {work});
    const auto s = dbc(0x80001301u, {2, 2, 0, 0, 0});
    CHECK(static_cast<s32>(load32(s, 36)) >= 0);
    e.bus.vblank();
    e.sif.service();
    // sceDbcGetConnection 0x51CAD0: connected only if work[socket] == 1 -> stays 0 (no card)
    CHECK(e.r32(work + 4 * load32(s, 36)) != 1);
    CHECK(load32(dbc(0x80001317u, {0}), 4) == 0);
}

TEST_CASE("sound: SDRDRV SetParam / SK blocks and DTX answer, and are logged") {
    EeSide e;
    e.init_rpc();
    const u32 sd = e.bind(0x80000701u);
    // sceSdRemote(1, 0x8010, 2432, 16383): 64-byte args block, reply 16
    const auto p = e.call_sync(sd, 0x8010, words({0x96E000, 2432, 16383, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}), 16);
    CHECK(load32(p, 0) == 0);
    auto sk = [&](u32 module, u32 fn, std::initializer_list<u32> args) {
        std::vector<u8> blk(64, 0);
        store32(blk, 0, module);
        store32(blk, 4, fn);
        std::size_t i = 8;
        for (u32 a : args) {
            store32(blk, i, a);
            i += 4;
        }
        return static_cast<s32>(load32(e.call_sync(sd, 0x90F0, blk, 16), 0));
    };
    CHECK(sk(0, 2, {0, 143, 0}) == 0);  // SOUND_Control
    const s32 h1 = sk(0x1000000, 0, {3, static_cast<u32>(-1), 0x100000, 100, 0x5000, 200});
    const s32 h2 = sk(0x1000000, 0, {5, static_cast<u32>(-1), static_cast<u32>(h1), 0});
    const s32 q1 = sk(0x4000000, 0, {0, static_cast<u32>(-1), 0x110000, 300});
    const s32 ctl = sk(0x4000000, 0, {5, static_cast<u32>(h2), static_cast<u32>(q1)});
    // The IRXs' 0-based slot indices (SKHSYNTH 0x8C8 / 0xACC, SKSESQ 0x818 / 0xA88: the SESQ port
    // bind returns the HSYNTH port it was given); test_adxi.cpp covers the full flow.
    CHECK(h1 == 0);
    CHECK(h2 == 0);
    CHECK(q1 == 0);
    CHECK(ctl == h2);
    const s32 voice = sk(0x4000000, 2, {static_cast<u32>(ctl), 0, 10, 4});  // SESQ_Control play -> handle
    CHECK(voice >= 0);
    CHECK(sk(0x4000000, 3, {static_cast<u32>(ctl), 1, 10, static_cast<u32>(voice)}) == 0);
    const auto log = e.sif.iop().sound_log();
    REQUIRE(log.size() == 8);
    CHECK(log[0].fno == 0x8010);
    CHECK(log[0].args[0] == 2432);
    CHECK(log[1].sk_module == 0);
    CHECK(log[1].sk_function == 2);
    CHECK(log[1].args[1] == 143);
    CHECK(log[2].sk_module == 0x1000000);
    CHECK(log[2].result == h1);
    // CRI DTX: create must be non-zero (DTX_Create 0x559718)
    const u32 dtx = e.bind(0x90000200u);
    CHECK(load32(e.call_sync(dtx, 2, words({0, 0x980000, 0x120000, 0x800}), 4), 0) != 0);
    CHECK(load32(e.call_sync(dtx, 1024 + 12, words({48000}), 4), 0) == 0);
    CHECK(e.sif.iop().sound_requests() == 10);
}
