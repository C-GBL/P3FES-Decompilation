// IOPRP310 system servers: loadfile 0x80000006, heaplib 0x80000003, fileio 0x80000001.
// Client facts (obs, ps2dev objdump of SLUS_216.21):
//   loadfile: _lf_bind 0x50BAE8 asks fn 0xFF for a 4-byte version and 0x50BBE8 rejects anything but
//     "3100" (0x77F48C) or the string at *0x77F564; sceSifLoadModule -> _sceSifLoadModule 0x50C2C0
//     sends fn 0 with 512 bytes {+0 arglen, +4 modres, +8 path[252], +260 args[252]} and receives 8:
//     {module id or negative error, module start result}; kwlnInitPS2Systems retries while < 0.
//   heaplib (sceSifInitIopHeap 0x50B598, binds until the server is non-zero): fn 1 AllocIopHeap
//     {size} -> addr, fn 2 Free {addr} -> 0, fn 3 LoadIopHeap {addr, path}, fn 4 AllocSysMemory
//     {size, type, addr} -> addr (0x50B690), fn 5..9 Query* (5 = QueryMemSize 0x50B898; 6..9 numbering
//     from ps2sdk iopheap, Q-14).
//   fileio: sceFsInit 0x508170 binds, then fn 0xFF {EE result buffer 0x968C80, +1088} -> {version
//     "3100" (checked by _fs_version 0x508378), mode}; mode 2 would select per-request buffers
//     (0x508348). Operations (sceOpen 0x508670 fn 0, sceClose fn 1, sceRead 0x508CB8 fn 2, write 3,
//     lseek 4, ...) send {+0 sema, +4 result EE addr, +8 result size, +12.. args} and expect recv word0
//     != 0 ("accepted"); the result arrives later as SIF command 0x80000011 whose extra data is the
//     result block at the EE buffer: {+0 sema, +4 fn, +8 result addr, +12 result size, +16 result,
//     read only: +20 head len, +24 tail len, +28 head dst, +32 tail dst, +36 head[64], +100 tail[64]}
//     (_sceFs_Rcv_Intr 0x507C38 copies, then iSignalSema(+0)).
#include <algorithm>
#include <cctype>
#include <cstring>
#include <map>
#include <string>

#include "iop_core.h"
#include "p3fes/state_io.h"

namespace p3fes::hle::sif::detail {
namespace {

constexpr u8 kVersion3100[4] = {'3', '1', '0', '0'};

// ---- loadfile --------------------------------------------------------------------------------------
class LoadfileServer final : public RpcServer {
public:
    std::string_view name() const override { return "loadfile"; }
    void state(StateIo& /*io*/, IopCore& /*core*/) override {}  // stateless (modules: IopCore / SDRDRV)
    bool call(IopCore& core, const RpcRequest& req, RpcReply& reply, u32 /*ticket*/) override {
        switch (req.fno) {
        case 0xFF:
            reply.rdata.assign(std::begin(kVersion3100), std::end(kVersion3100));
            return true;
        case 0: {  // LF_F_MOD_LOAD
            const u32 arglen = std::min<u32>(req_word(req, 0), 252u);
            LoadedModule m;
            m.id = core.next_module_id();
            m.path = c_string(req.data, 8, 252);
            for (u32 i = 0; i < arglen && 260u + i < req.data.size(); ++i) m.args.push_back(static_cast<char>(req.data[260u + i]));
            core.log("[iop] loadfile: module " + std::to_string(m.id) + " " + m.path +
                     (arglen ? " (" + std::to_string(arglen) + " arg bytes)" : std::string()));
            // ADR-0014: the six SK/libsd modules are interpreted in place (srv_sdr.h). The reply keeps
            // modres 0 either way: the game never reads it, and the increment-1 snapshots were taken with 0.
            core.load_sk_module(m.path, std::string_view(m.args));
            put_word(reply.rdata, 0, static_cast<u32>(m.id));
            put_word(reply.rdata, 4, 0);  // MODULE_RESIDENT_END
            core.record_module(std::move(m));
            return true;
        }
        default:
            // LoadElf / StopModule / Unload / SearchModule*: linked, unreferenced (`12` §2.1).
            core.note_unknown(UnknownEvent::Kind::Function, req.sid, req.fno, "loadfile function not modelled (answered 0)");
            return true;
        }
    }
};

// ---- heaplib -----------------------------------------------------------------------------------------
class HeapServer final : public RpcServer {
public:
    std::string_view name() const override { return "heaplib"; }
    void state(StateIo& /*io*/, IopCore& /*core*/) override {}  // stateless (the heap is IopRam's)
    bool call(IopCore& core, const RpcRequest& req, RpcReply& reply, u32 /*ticket*/) override {
        IopRam& ram = core.ram();
        u32 r = 0;
        switch (req.fno) {
        case 1: r = ram.alloc(req_word(req, 0), 0, 0); break;                                  // AllocIopHeap
        case 2: r = ram.free(req_word(req, 0)) ? 0u : static_cast<u32>(-1); break;              // Free*
        case 4: r = ram.alloc(req_word(req, 0), req_word(req, 4), req_word(req, 8)); break;    // AllocSysMemory
        case 5: r = kIopRamSize; break;                                                         // QueryMemSize
        case 6: r = ram.free_max(); break;                                                      // QueryMaxFreeMemSize (inf #)
        case 7: r = ram.free_total(); break;                                                    // QueryTotalFreeMemSize (inf #)
        case 8: r = ram.block_size(req_word(req, 0)) ? req_word(req, 0) : 0u; break;           // QueryBlockTopAddress (inf)
        case 9: r = ram.block_size(req_word(req, 0)); break;                                    // QueryBlockSize (inf)
        case 3:  // LoadIopHeap(path): no caller in the game; there is no IOP file system to load from.
            core.note_unknown(UnknownEvent::Kind::Function, req.sid, req.fno, "LoadIopHeap " + c_string(req.data, 4, 252) + " (failed)");
            r = static_cast<u32>(-1);
            break;
        default:
            core.note_unknown(UnknownEvent::Kind::Function, req.sid, req.fno, "heaplib function not modelled (answered 0)");
            break;
        }
        if ((req.fno == 1 || req.fno == 4) && r == 0)
            core.log("[iop] heaplib: allocation of " + std::to_string(req_word(req, 0)) + " bytes failed (IOP heap exhausted)");
        put_word(reply.rdata, 0, r);
        return true;
    }
};

// ---- fileio ------------------------------------------------------------------------------------------
constexpr s32 kENOENT = -2;
constexpr s32 kEBADF = -9;
constexpr s32 kENODEV = -19;
constexpr std::size_t kResultBlockBase = 20;   // header words + result
constexpr std::size_t kResultBlockRead = 164;  // + head/tail block

class FileioServer final : public RpcServer {
public:
    std::string_view name() const override { return "fileio"; }
    void state(StateIo& io, IopCore& /*core*/) override {
        u64 n = files_.size();
        io(n);
        if (io.saving()) {
            for (auto& [fd, f] : files_) {
                s32 k = fd;
                io(k, f.path, f.data, f.pos);
            }
        } else {
            files_.clear();
            for (u64 i = 0; i < n && io.ok(); ++i) {
                s32 k = 0;
                File f;
                io(k, f.path, f.data, f.pos);
                files_[k] = std::move(f);
            }
        }
        io(deferred_, result_buf_, next_fd_);
    }

    bool call(IopCore& core, const RpcRequest& req, RpcReply& reply, u32 /*ticket*/) override {
        switch (req.fno) {
        case 0xFF:  // init: remember the EE result buffer
            result_buf_ = req_word(req, 0);
            reply.rdata.assign(std::begin(kVersion3100), std::end(kVersion3100));
            put_word(reply.rdata, 4, 1);  // inf: not 2 -> one shared result buffer (0x508348)
            return true;
        case 0xFE:  // sceFsSetIopBuf / sceFsSetIopPrio: bookkeeping on the IOP
        case 0xFD:
            core.note_unknown(UnknownEvent::Kind::Function, req.sid, req.fno, "fileio tuning call (accepted)");
            put_word(reply.rdata, 0, 1);
            return true;
        default:
            break;
        }
        // Asynchronous operation: accept now, answer with command 0x80000011 behind the RPC end.
        put_word(reply.rdata, 0, 1);
        std::vector<u8> block(kResultBlockBase, 0);
        store32(block, 0, req_word(req, 0));   // sema
        store32(block, 4, req.fno);
        store32(block, 8, req_word(req, 4));   // result address
        store32(block, 12, req_word(req, 8));  // result size
        s32 result = kENODEV;
        switch (req.fno) {
        case 0: result = open(core, req); break;
        case 1: result = files_.erase(static_cast<s32>(req_word(req, 12))) ? 0 : kEBADF; break;
        case 2: result = read(core, req, block); break;
        case 3: result = write(core, req); break;
        case 4: result = lseek(req); break;
        default:
            core.note_unknown(UnknownEvent::Kind::Function, req.sid, req.fno, "fileio operation not modelled (-ENODEV)");
            break;
        }
        store32(block, 16, static_cast<u32>(result));
        if (result_buf_ == 0) {
            core.log("[iop] fileio: operation before sceFsInit's result buffer is known (dropped)");
            return true;
        }
        // The result packet must follow the RPC end: queue it after this call's reply is queued.
        deferred_.push_back(std::move(block));
        return true;
    }

    void tick(IopCore& core, u64 /*now*/, const Timebase& /*tb*/) override {
        for (auto& b : deferred_) core.send_command(cid::kFileioResult, {}, {EeWrite{result_buf_, std::move(b)}});
        deferred_.clear();
    }
    u64 next_deadline() const override { return deferred_.empty() ? kNever : 0; }
    void reboot() override {
        files_.clear();
        deferred_.clear();
        result_buf_ = 0;
        next_fd_ = 3;
    }

private:
    struct File {
        std::string path;
        std::vector<u8> data;
        u32 pos = 0;
    };
    std::map<s32, File> files_;
    std::vector<std::vector<u8>> deferred_;
    u32 result_buf_ = 0;
    s32 next_fd_ = 3;

    static bool ieq(std::string_view a, std::string_view b) {
        if (a.size() != b.size()) return false;
        for (std::size_t i = 0; i < a.size(); ++i)
            if (std::tolower(static_cast<unsigned char>(a[i])) != std::tolower(static_cast<unsigned char>(b[i]))) return false;
        return true;
    }

    s32 open(IopCore& core, const RpcRequest& req) {
        const std::string path = c_string(req.data, 20, 1024);
        if (ieq(path, "rom0:ROMVER")) {
            const auto& rv = core.config().romver;
            File f{path, std::vector<u8>(rv.begin(), rv.end()), 0};
            const s32 fd = next_fd_++;
            files_[fd] = std::move(f);
            return fd;
        }
        core.note_unknown(UnknownEvent::Kind::Function, req.sid, 0, "fileio open of an unmodelled path \"" + path + "\" (-ENOENT)");
        return kENOENT;
    }

    s32 read(IopCore& core, const RpcRequest& req, std::vector<u8>& block) {
        auto it = files_.find(static_cast<s32>(req_word(req, 12)));
        if (it == files_.end()) return kEBADF;
        File& f = it->second;
        const u32 buf = req_word(req, 16);
        const u32 want = req_word(req, 20);
        const u32 n = std::min<u32>(want, static_cast<u32>(f.data.size()) - std::min<u32>(f.pos, static_cast<u32>(f.data.size())));
        const u8* src = f.data.data() + f.pos;
        f.pos += n;
        block.resize(kResultBlockRead, 0);
        const UnalignedSplit s = split_unaligned(buf, n);
        store32(block, 20, s.head);
        store32(block, 24, s.tail);
        store32(block, 28, buf);
        store32(block, 32, s.tail_addr);
        std::memcpy(block.data() + 36, src, s.head);
        if (s.body) core.ee_store(buf + s.head, std::span<const u8>(src + s.head, s.body));
        std::memcpy(block.data() + 100, src + s.head + s.body, s.tail);
        return static_cast<s32>(n);
    }

    s32 write(IopCore& core, const RpcRequest& req) {
        // inf layout (no game caller traced): +12 fd, +16 EE buffer, +20 size. fd 1/2 = tty.
        const s32 fd = static_cast<s32>(req_word(req, 12));
        const u32 size = std::min<u32>(req_word(req, 20), 4096u);
        if (fd == 1 || fd == 2) {
            std::vector<u8> text(size);
            if (core.ee_load(req_word(req, 16), text)) core.log("[iop tty] " + std::string(text.begin(), text.end()));
            return static_cast<s32>(size);
        }
        return kEBADF;
    }

    s32 lseek(const RpcRequest& req) {
        auto it = files_.find(static_cast<s32>(req_word(req, 12)));
        if (it == files_.end()) return kEBADF;
        File& f = it->second;
        const s32 off = static_cast<s32>(req_word(req, 16));
        const u32 whence = req_word(req, 20);
        const s64 base = whence == 1 ? f.pos : whence == 2 ? static_cast<s64>(f.data.size()) : 0;
        const s64 p = std::clamp<s64>(base + off, 0, static_cast<s64>(f.data.size()));
        f.pos = static_cast<u32>(p);
        return static_cast<s32>(p);
    }
};

}  // namespace

std::unique_ptr<RpcServer> make_loadfile_server() { return std::make_unique<LoadfileServer>(); }
std::unique_ptr<RpcServer> make_heap_server() { return std::make_unique<HeapServer>(); }
std::unique_ptr<RpcServer> make_fileio_server() { return std::make_unique<FileioServer>(); }

}  // namespace p3fes::hle::sif::detail
