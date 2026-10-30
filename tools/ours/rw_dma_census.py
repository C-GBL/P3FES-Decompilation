"""Walk RenderWare's sky DMA queue in an eeMemory.bin snapshot and count what one frame sends to VIF1/VU1/GS.

Usage (plain CPython, `-I`; inputs are gitignored snapshots):
  python -I tools/ours/rw_dma_census.py <snapshot dir or eeMemory.bin> [--elf SLUS_216.21] [--json OUT]

What it reads (docs/ANALYSIS/22_rendering.md section 5 for the layout, all observed in IDA):
  * the RW DMA buffer globals ($gp = 0x7D2CF0): gp-17304 aligned buffer base, gp-17160 / gp-17156 the
    two half-buffers (each starts with a 15-entry queue block), gp-17164 the half size, gp-17192 the
    queue write pointer (_rwDMADmaOpen 0x4D67B0, _rwDMAClosePkt 0x4D4A60, _rwDMAOpenVIFPkt 0x4D59D0);
  * queue entries {u32 type|flags, u32 addr}: type 1 = VIF1 (flags 0x1100 chain + TTE), 2 = GIF chain,
    0x21 = image upload (VIF1+GIF), 64/65 flip, 66 counter, 67 nop, 79 callback, 127 = jump to addr;
  * DMA source-chain tags (cnt/next/ref/refs/call/ret/end/refe) with the two VIF codes of every tag
    (TTE), and the VIF1 code stream they carry (UNPACK, MPG, MSCAL/MSCALF/MSCNT, DIRECT, STxxx...).
For every half-buffer it prints the queue entries by type, the VU1 programs that were called (by the
VA of their `ret` packet, named from the 114-program table of docs/ANALYSIS/14), the MSCAL/MSCALF/MSCNT
count per (program, entry address), the UNPACK / DIRECT / MPG quadword totals, and the GIF tags seen in
DIRECT data (PRIM / IMAGE / A+D counts).
"""
import argparse, json, os, struct, sys
from collections import Counter, defaultdict

GP = 0x7D2CF0

# 114 VU1 program packets (ret-tag VAs) and their family, docs/ANALYSIS/14 section 1 (036-039, there "unknown_tbl4", are
# the RW Im2D programs: docs/ANALYSIS/22 section 6).
PROGRAMS = {}
_fam = [
    (0x5a1d80, "unreferenced"), (0x5a2180, "unreferenced"), (0x5a2640, "unreferenced"), (0x5a2ae0, "unreferenced"),
    (0x5a3020, "unreferenced"), (0x5a3570, "unreferenced"), (0x5a3be0, "unreferenced"), (0x5a46a0, "unreferenced"),
    (0x5a4e90, "unreferenced"), (0x5a5410, "unreferenced"), (0x5a5a80, "unreferenced"), (0x5a61c0, "unreferenced"),
    (0x5a6b40, "unreferenced"), (0x5a7440, "unreferenced"), (0x5a7de0, "unreferenced"), (0x5a8b10, "unreferenced"),
    (0x5a9770, "unreferenced"), (0x5ac320, "unreferenced"), (0x5af2b0, "unreferenced"), (0x5b1e90, "unreferenced"),
    (0x5b4b70, "unreferenced"), (0x5b6f10, "unreferenced"), (0x5b9330, "unreferenced"), (0x5bc1a0, "unreferenced"),
    (0x5bf1b0, "unreferenced"), (0x5c2050, "unreferenced"), (0x5c4ff0, "unreferenced"), (0x5c7750, "unreferenced"),
    (0x5c9f30, "ptank_spr2d"), (0x5ca360, "ptank_spr2d"), (0x5ca720, "ptank_spr2d"), (0x5cab00, "ptank_spr2d"),
    (0x5cae60, "ptank_spr3d"), (0x5cb8e0, "ptank_spr3d"), (0x5cc190, "ptank_spr3d"), (0x5ccb60, "ptank_spr3d"),
    (0x5cd3b0, "im2d"), (0x5cd5b0, "im2d"), (0x5cd820, "im2d"), (0x5cd980, "im2d"),
    (0x5cdb10, "null_transform"),
    (0x6b5e90, "g3_generic"), (0x6b8d40, "g3_generic"), (0x6bc700, "g3_generic"), (0x6be190, "g3_generic"),
    (0x6bfee0, "g3_generic"), (0x6c2940, "g3_generic"),
    (0x6c5430, "g3_matfx"), (0x6c8060, "g3_matfx"), (0x6caa60, "g3_matfx"), (0x6ce620, "g3_matfx"), (0x6d16d0, "g3_matfx"),
    (0x6d4280, "g3_matfx"), (0x6d6c00, "g3_matfx"), (0x6da720, "g3_matfx"), (0x6dd750, "g3_matfx"), (0x6e04c0, "g3_matfx"),
    (0x6e3010, "g3_matfx"), (0x6e6d20, "g3_matfx"), (0x6e9f20, "g3_matfx"), (0x6ec940, "g3_matfx"), (0x6ef130, "g3_matfx"),
    (0x6f2ae0, "g3_matfx"),
    (0x6f5980, "g3_skin"), (0x6f8b10, "g3_skin"), (0x6fc7a0, "g3_skin"), (0x6fe500, "g3_skin"), (0x700520, "g3_skin"),
    (0x703250, "g3_skin"),
    (0x706010, "g3_skin_matfx"), (0x708ea0, "g3_skin_matfx"), (0x70bb00, "g3_skin_matfx"), (0x70f920, "g3_skin_matfx"),
    (0x712c30, "g3_skin_matfx"), (0x715a40, "g3_skin_matfx"), (0x718620, "g3_skin_matfx"), (0x71c3a0, "g3_skin_matfx"),
    (0x71f630, "g3_skin_matfx"), (0x722600, "g3_skin_matfx"), (0x7253b0, "g3_skin_matfx"), (0x729320, "g3_skin_matfx"),
    (0x72c780, "g3_skin_matfx"), (0x72f470, "g3_skin_matfx"), (0x731f30, "g3_skin_matfx"), (0x735bb0, "g3_skin_matfx"),
    (0x738d20, "rt2d_stroke"), (0x73ae90, "rt2d_stroke"), (0x73cf60, "rt2d_font"), (0x73f230, "rt2d_font"),
    (0x741470, "rt2d_fill"), (0x7437c0, "rt2d_fill"),
    (0x745a70, "g3_matfx"), (0x748610, "g3_matfx"), (0x74b110, "g3_matfx"), (0x74eb80, "g3_matfx"), (0x751ae0, "g3_matfx"),
    (0x7545c0, "g3_matfx"), (0x756e80, "g3_matfx"), (0x75a900, "g3_matfx"),
    (0x75d860, "g3_skin_matfx"), (0x7606d0, "g3_skin_matfx"), (0x7634a0, "g3_skin_matfx"), (0x7671e0, "g3_skin_matfx"),
    (0x76a410, "g3_skspt_uva"), (0x76c4e0, "g3_skspt_uva"),
    (0x76e2f0, "g3_skin_matfx"), (0x7710a0, "g3_skin_matfx"), (0x773c30, "g3_skin_matfx"), (0x777980, "g3_skin_matfx"),
    (0x77cb40, "ptank_xform"), (0x77cee0, "ptank_xform"), (0x77d200, "ptank_xform"), (0x77d590, "ptank_xform"),
    (0x77d910, "ptank_xform"),
]
for i, (va, fam) in enumerate(_fam):
    PROGRAMS[va] = f"{i:03d}_{fam}@{va:06x}"


class Mem:
    def __init__(self, path):
        self.b = open(path, "rb").read()

    def u32(self, va):
        pa = va & 0x1FFFFFFF
        return struct.unpack_from("<I", self.b, pa)[0]

    def u64(self, va):
        pa = va & 0x1FFFFFFF
        return struct.unpack_from("<Q", self.b, pa)[0]

    def g(self, off):
        return self.u32(GP + off)

    def ok(self, va):
        return (va & 0x1FFFFFFF) + 16 <= len(self.b) and (va & 0xF0000000) != 0x70000000


UNPACK_BITS = {0: 32, 1: 16, 2: 8, 3: 4}


class Vif:
    """Streaming VIF1 decoder: feed 32-bit words in transfer order."""

    def __init__(self, stats):
        self.s = stats
        self.need = 0          # data words still owed to the current command
        self.cmd = None
        self.direct_left = 0   # words of DIRECT data left (GIF parse)
        self.gif = Gif(stats)
        self.program = None    # VA of the last called program packet

    def word(self, w):
        if self.need:
            self.need -= 1
            if self.cmd == "DIRECT":
                self.gif.word(w)
            return
        cmd = (w >> 24) & 0x7F
        num = (w >> 16) & 0xFF
        imm = w & 0xFFFF
        s = self.s
        if cmd == 0x00:
            s["vif_NOP"] += 1
        elif cmd == 0x01:
            s["vif_STCYCL"] += 1
        elif cmd in (0x02, 0x03, 0x04, 0x05, 0x07):
            s[f"vif_{ {2:'OFFSET',3:'BASE',4:'ITOP',5:'STMOD',7:'MARK'}[cmd] }"] += 1
        elif cmd == 0x06:
            s["vif_MSKPATH3"] += 1
        elif cmd in (0x10, 0x11, 0x13):
            s["vif_FLUSH"] += 1
        elif cmd in (0x14, 0x15, 0x17):
            name = {0x14: "MSCAL", 0x15: "MSCALF", 0x17: "MSCNT"}[cmd]
            prog = PROGRAMS.get(self.program, f"inline@{self.program:06x}" if self.program else "none")
            s["mscal"][f"{prog} {name} {imm if cmd != 0x17 else '-'}"] += 1
            s["vif_MSCALx"] += 1
        elif cmd == 0x20:
            self.need, self.cmd = 1, "STMASK"
        elif cmd in (0x30, 0x31):
            self.need, self.cmd = 4, "STROW"
        elif cmd == 0x4A:
            n = num or 256
            self.need, self.cmd = 2 * n, "MPG"
            s["mpg_qw"] += n / 2
            prog = PROGRAMS.get(self.program, None)
            if prog is None:
                s["mpg_outside_known_packet"] += 1
        elif cmd in (0x50, 0x51):
            n = imm or 65536
            self.need, self.cmd = 4 * n, "DIRECT"
            s["direct_qw"] += n
            self.gif.reset()
        elif cmd >= 0x60:
            vn = (cmd >> 2) & 3
            vl = cmd & 3
            n = num or 256
            bits = UNPACK_BITS[vl] * (vn + 1) * n
            words = (bits + 31) // 32
            self.need, self.cmd = words, "UNPACK"
            s["unpack_qw_out"] += n
            s["unpack_words_in"] += words
            s["unpack_fmt"][f"V{vn+1}-{UNPACK_BITS[vl]}{'m' if cmd & 0x10 else ''}"] += 1
        else:
            s["vif_unknown"][hex(cmd)] += 1


class Gif:
    """GIF tag parser for DIRECT payloads (PACKED/REGLIST/IMAGE)."""

    def __init__(self, stats):
        self.s = stats
        self.reset()

    def reset(self):
        self.buf = []
        self.left = 0  # words of data after the current tag

    def word(self, w):
        if self.left:
            self.left -= 1
            return
        self.buf.append(w)
        if len(self.buf) < 4:
            return
        lo = self.buf[0] | (self.buf[1] << 32)
        hi = self.buf[2] | (self.buf[3] << 32)
        self.buf = []
        nloop = lo & 0x7FFF
        pre = (lo >> 46) & 1
        prim = (lo >> 47) & 0x7FF
        flg = (lo >> 58) & 3
        nreg = (lo >> 60) & 0xF or 16
        if flg == 0:
            self.left = nloop * nreg * 4
            regs = [(hi >> (4 * i)) & 0xF for i in range(nreg)]
            if all(r == 0xE for r in regs):
                self.s["gif_AD_regs"] += nloop * nreg
            else:
                self.s["gif_packed_tags"] += 1
            if pre:
                self.s["gif_prim"][prim & 7] += 1
        elif flg == 1:
            self.left = ((nloop * nreg + 1) // 2) * 4
            self.s["gif_reglist_tags"] += 1
        else:
            self.left = nloop * 4
            self.s["gif_image_qw"] += nloop


def new_stats():
    return defaultdict(int, mscal=Counter(), unpack_fmt=Counter(), vif_unknown=Counter(), gif_prim=Counter(),
                       queue=Counter(), calls=Counter(), refs_bytes=Counter(),
                       instance_call_targets=set(), vif_chain_starts=set())


def walk_chain(mem, addr, stats, tte=True, vif=None, limit=200000):
    """DMAC source-chain walk; feeds the VIF decoder with tag VIF codes + payload words."""
    stack = []
    p = addr
    steps = 0
    while steps < limit:
        steps += 1
        if not mem.ok(p):
            stats["chain_bad_address"] += 1
            return
        lo = mem.u64(p)
        hi = mem.u64(p + 8)
        qwc = lo & 0xFFFF
        tid = (lo >> 28) & 7
        a = (lo >> 32) & 0x7FFFFFF0
        spr = (lo >> 63) & 1
        stats[f"tag_{['refe','cnt','next','ref','refs','call','ret','end'][tid]}"] += 1
        if vif and tte:
            vif.word(hi & 0xFFFFFFFF)
            vif.word(hi >> 32)

        def feed(src, n):
            if not vif or n == 0:
                return
            if spr or not mem.ok(src):
                stats["payload_unreadable_qw"] += n
                return
            base = src & 0x1FFFFFFF
            words = struct.unpack_from(f"<{4*n}I", mem.b, base)
            for w in words:
                vif.word(w)

        if tid == 1:      # cnt
            feed(p + 16, qwc); p = p + 16 + 16 * qwc
        elif tid == 2:    # next
            feed(p + 16, qwc); p = a
        elif tid in (3, 4):  # ref / refs
            stats["refs_bytes"][f"{a:08x}"[:4]] += 16 * qwc
            stats["ref_qw"] += qwc
            feed(a, qwc); p = p + 16
        elif tid == 0:    # refe
            stats["ref_qw"] += qwc
            feed(a, qwc); return
        elif tid == 5:    # call
            feed(p + 16, qwc)
            stack.append(p + 16 + 16 * qwc)
            if a in PROGRAMS:
                stats["calls"][PROGRAMS[a]] += 1
                if vif:
                    vif.program = a
            else:
                stats["instance_calls"] += 1
                stats["instance_call_targets"].add(a)
            p = a
        elif tid == 6:    # ret
            feed(p + 16, qwc)
            if not stack:
                return
            p = stack.pop()
        else:             # end
            feed(p + 16, qwc); return
    stats["chain_step_limit"] += 1


def walk_chain_gif(mem, addr, stats, limit=200000):
    """GIF-channel chain: payload words go to the GIF tag parser (no VIF codes)."""
    gif = Gif(stats)
    p = addr
    stack = []
    for _ in range(limit):
        if not mem.ok(p):
            stats["chain_bad_address"] += 1
            return
        lo = mem.u64(p)
        qwc = lo & 0xFFFF
        tid = (lo >> 28) & 7
        a = (lo >> 32) & 0x7FFFFFF0
        src, nxt = (p + 16, p + 16 + 16 * qwc)
        if tid in (0, 3, 4):
            src, nxt = a, p + 16
        elif tid == 2:
            nxt = a
        elif tid == 5:
            stack.append(nxt); nxt = a
        elif tid == 6:
            nxt = stack.pop() if stack else None
        if mem.ok(src) and qwc:
            for w in struct.unpack_from(f"<{4*qwc}I", mem.b, src & 0x1FFFFFFF):
                gif.word(w)
        stats["path3_qw"] += qwc
        if tid in (0, 7) or nxt is None:
            return
        p = nxt


def census_half(mem, start, stop_at, stats):
    """Walk one half-buffer's queue from `start`; stop at `stop_at` (write pointer) or at the first flip."""
    p = start
    n = 0
    while n < 20000:
        n += 1
        if stop_at and p == stop_at:
            stats["queue_end"] = "write pointer"
            return
        t = mem.u32(p)
        a = mem.u32(p + 4)
        typ = t & 0xFF
        stats["queue"][typ] += 1
        if t == 0 and a == 0:
            stats["queue_end"] = "empty entry"
            return
        if typ == 127:
            p = a
            continue
        if typ == 1:
            stats["vif_chain_starts"].add(a)
            vif = Vif(stats)
            if t & 0x300:
                walk_chain(mem, a, stats, tte=bool(t & 0x1000), vif=vif)
            else:
                stats["vif_normal_qw"] += (t & 0xFFFF000) >> 12
        elif typ == 2:
            if t & 0x300:
                walk_chain(mem, a, stats, tte=False, vif=None)
            stats["gif_path3_entries"] += 1
        elif typ == 0x21:   # VIF1 half of a simultaneous VIF1 + GIF(IMAGE) kick (_rwDMAHandler, CHCR 0x145)
            stats["image_upload_entries"] += 1
            stats["vif_chain_starts"].add(a)
            vif = Vif(stats)
            walk_chain(mem, a, stats, tte=bool(t & 0x1000), vif=vif)
        elif typ == 0x22:   # its GIF (PATH3) chain: count the IMAGE / A+D data it carries
            stats["gif_path3_entries"] += 1
            walk_chain_gif(mem, a, stats)
        elif typ in (64, 65):
            stats["queue_end"] = f"flip {typ}"
            p += 8
            return
        p += 8
    stats["queue_end"] = "entry limit"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("snap")
    ap.add_argument("--json", default=None)
    a = ap.parse_args()
    path = a.snap if a.snap.endswith(".bin") else os.path.join(a.snap, "eeMemory.bin")
    mem = Mem(path)
    base = mem.g(-17304)
    h0 = mem.g(-17160)
    h1 = mem.g(-17156)
    half = mem.g(-17164)
    wq = mem.g(-17192)
    cur = h0 if h0 <= wq < h0 + half else h1
    print(f"buffer base {base:08x} half0 {h0:08x} half1 {h1:08x} half size {half:#x} queue write {wq:08x} (in half{0 if cur == h0 else 1})")
    out = {}
    for name, start in (("half0", h0), ("half1", h1)):
        st = new_stats()
        census_half(mem, start, wq if start == cur else None, st)
        st["building"] = start == cur
        out[name] = st
        print(f"== {name} ({'being built' if start == cur else 'complete/previous'}) end: {st.get('queue_end')}")
        print("  queue types:", dict(st["queue"]), "VIF chain starts:", " ".join(f"{x:08x}" for x in sorted(st["vif_chain_starts"])))
        print("  VU1 program calls:", dict(st["calls"].most_common()))
        fam = Counter()
        for k, v in st["mscal"].items():
            f = k.split()[0]
            fam[f.split("@")[0].split("_", 1)[-1] if "@" in f else f] += v
        print("  instance-data calls:", st["instance_calls"], "distinct", len(st["instance_call_targets"]))
        print("  MSCAL/MSCALF/MSCNT by family:", dict(fam.most_common()))
        print("  MSCAL by program/entry:")
        for k, v in sorted(st["mscal"].items(), key=lambda kv: -kv[1]):
            print(f"    {v:6d}  {k}")
        keys = ["tag_cnt", "tag_next", "tag_ref", "tag_refs", "tag_call", "tag_ret", "tag_end", "ref_qw", "unpack_qw_out",
                "unpack_words_in", "direct_qw", "mpg_qw", "mpg_outside_known_packet", "gif_AD_regs", "gif_packed_tags",
                "gif_image_qw", "gif_reglist_tags", "image_upload_entries", "gif_path3_entries", "payload_unreadable_qw",
                "chain_bad_address", "vif_MSKPATH3", "vif_FLUSH"]
        print("  ", {k: st[k] for k in keys if st.get(k)})
        print("  unpack formats:", dict(st["unpack_fmt"]), " GIF prim types (PRE):", dict(st["gif_prim"]))
        if st["vif_unknown"]:
            print("  unknown VIF:", dict(st["vif_unknown"]))
    if a.json:
        json.dump({k: {kk: (dict(vv) if isinstance(vv, Counter) else sorted(vv) if isinstance(vv, set) else vv) for kk, vv in v.items()} for k, v in out.items()},
                  open(a.json, "w"), indent=1)


if __name__ == "__main__":
    main()
