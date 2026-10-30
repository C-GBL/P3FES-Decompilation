#!/usr/bin/env python3
"""Minimal PINE (PCSX2 IPC) client, stdlib only.

Protocol (PCSX2 pcsx2/PINE.h; exercised against the 2.8.2 server, see docs/PCSX2.md):
  transport : TCP 127.0.0.1:<slot> on Windows (default slot 28011 = [EmuCore] PINESlot);
              Unix domain socket $XDG_RUNTIME_DIR/pcsx2.sock[.<slot>] elsewhere.
  request   : u32 size (little-endian, counts the size field itself) | u8 opcode | payload
  reply     : u32 size | u8 result (0 = OK, 0xFF = FAIL) | payload
  Several requests may be concatenated in one message (batching); this client sends one at a time.
  Opcodes   : 0 MsgRead8  1 MsgRead16  2 MsgRead32  3 MsgRead64   (payload u32 addr -> value)
              4 MsgWrite8 5 MsgWrite16 6 MsgWrite32 7 MsgWrite64  (payload u32 addr, value)
              8 MsgVersion -> string          9 MsgSaveState (u8 slot)   10 MsgLoadState (u8 slot)
              11 MsgTitle -> string          12 MsgID -> string          13 MsgUUID -> string
              14 MsgGameVersion -> string    15 MsgStatus -> u32 (0 Running, 1 Paused, 2 Shutdown)
  strings   : u32 size | char[size] (size includes the terminating NUL).
  addresses : EE *virtual* addresses resolved through the guest's TLB (observed on 2.8.2): game VAs in
              kuseg (0x00100000..) read directly; the kernel area must be read via kseg0 (0x80075000
              works, 0x00075000 reads 0 because the EE leaves kuseg 0x0-0x7FFFF unmapped); 0x00082000
              works. Out-of-range reads return 0 rather than an error. See docs/PCSX2.md.

CLI:
  python pine.py status|version|title|id|uuid|gameversion
  python pine.py read8|read16|read32|read64 <hexaddr>
  python pine.py write8|write16|write32|write64 <hexaddr> <hexvalue>
  python pine.py dump <hexaddr> <length> [outfile]      # read a byte range (chunked 64-bit reads)
  python pine.py savestate <slot> | loadstate <slot>
  python pine.py wait-nonzero <hexaddr> [timeout_s]     # poll a u32 until it is non-zero
"""
import socket
import struct
import sys
import time

MsgRead8, MsgRead16, MsgRead32, MsgRead64 = 0, 1, 2, 3
MsgWrite8, MsgWrite16, MsgWrite32, MsgWrite64 = 4, 5, 6, 7
(MsgVersion, MsgSaveState, MsgLoadState, MsgTitle, MsgID, MsgUUID,
 MsgGameVersion, MsgStatus) = 8, 9, 10, 11, 12, 13, 14, 15
STATUS = {0: "Running", 1: "Paused", 2: "Shutdown"}


class PineError(RuntimeError):
    pass


class Pine:
    def __init__(self, host="127.0.0.1", port=28011, timeout=5.0):
        self.sock = socket.create_connection((host, port), timeout=timeout)

    def close(self):
        self.sock.close()

    def __enter__(self):
        return self

    def __exit__(self, *exc):
        self.close()

    def _recv_exact(self, n):
        buf = bytearray()
        while len(buf) < n:
            chunk = self.sock.recv(n - len(buf))
            if not chunk:
                raise PineError("connection closed by PCSX2")
            buf += chunk
        return bytes(buf)

    def _call(self, opcode, payload=b""):
        self.sock.sendall(struct.pack("<IB", 5 + len(payload), opcode) + payload)
        size, result = struct.unpack("<IB", self._recv_exact(5))
        body = self._recv_exact(size - 5) if size > 5 else b""
        if result != 0:
            raise PineError(f"opcode {opcode} failed (result 0x{result:02X})")
        return body

    # --- memory ---
    def read8(self, addr):
        return struct.unpack("<B", self._call(MsgRead8, struct.pack("<I", addr)))[0]

    def read16(self, addr):
        return struct.unpack("<H", self._call(MsgRead16, struct.pack("<I", addr)))[0]

    def read32(self, addr):
        return struct.unpack("<I", self._call(MsgRead32, struct.pack("<I", addr)))[0]

    def read64(self, addr):
        return struct.unpack("<Q", self._call(MsgRead64, struct.pack("<I", addr)))[0]

    def write8(self, addr, v):
        self._call(MsgWrite8, struct.pack("<IB", addr, v))

    def write16(self, addr, v):
        self._call(MsgWrite16, struct.pack("<IH", addr, v))

    def write32(self, addr, v):
        self._call(MsgWrite32, struct.pack("<II", addr, v))

    def write64(self, addr, v):
        self._call(MsgWrite64, struct.pack("<IQ", addr, v))

    def read_many(self, reqs):
        """Batched reads in ONE PINE message (the server parses opcodes until the message size is consumed
        and concatenates the replies), so all values come from the same server-side pass.
        reqs: iterable of (width_bits, addr) with width in 8/16/32/64. Returns a list of ints."""
        op = {8: MsgRead8, 16: MsgRead16, 32: MsgRead32, 64: MsgRead64}
        fmt = {8: "<B", 16: "<H", 32: "<I", 64: "<Q"}
        reqs = list(reqs)
        payload = b"".join(struct.pack("<BI", op[w], a) for w, a in reqs)
        self.sock.sendall(struct.pack("<I", 4 + len(payload)) + payload)
        size, result = struct.unpack("<IB", self._recv_exact(5))
        body = self._recv_exact(size - 5) if size > 5 else b""
        if result != 0:
            raise PineError(f"batched read failed (result 0x{result:02X})")
        out, off = [], 0
        for w, _ in reqs:
            out.append(struct.unpack_from(fmt[w], body, off)[0])
            off += w // 8
        if off != len(body):
            raise PineError(f"batched read: reply has {len(body)} payload bytes, expected {off}")
        return out

    def read_bytes(self, addr, length):
        """Read an arbitrary byte range using 64-bit reads (plus a byte tail)."""
        out = bytearray()
        a = addr
        while length - len(out) >= 8:
            out += struct.pack("<Q", self.read64(a))
            a += 8
        while len(out) < length:
            out.append(self.read8(a))
            a += 1
        return bytes(out)

    # --- strings / control ---
    def _string(self, opcode):
        body = self._call(opcode)
        (n,) = struct.unpack_from("<I", body, 0)
        return body[4:4 + n].split(b"\0", 1)[0].decode("utf-8", "replace")

    def version(self):
        return self._string(MsgVersion)

    def title(self):
        return self._string(MsgTitle)

    def game_id(self):
        return self._string(MsgID)

    def uuid(self):
        return self._string(MsgUUID)

    def game_version(self):
        return self._string(MsgGameVersion)

    def status(self):
        return struct.unpack("<I", self._call(MsgStatus))[0]

    def save_state(self, slot):
        self._call(MsgSaveState, struct.pack("<B", slot))

    def load_state(self, slot):
        self._call(MsgLoadState, struct.pack("<B", slot))


def connect_retry(port=28011, total=30.0):
    deadline = time.time() + total
    while True:
        try:
            return Pine(port=port)
        except OSError:
            if time.time() > deadline:
                raise
            time.sleep(0.5)


def main(argv):
    if not argv:
        print(__doc__)
        return 2
    cmd, *rest = argv
    with connect_retry(total=5.0) as p:
        if cmd == "status":
            s = p.status()
            print(f"{s} ({STATUS.get(s, '?')})")
        elif cmd in ("version", "title", "id", "uuid", "gameversion"):
            print({"version": p.version, "title": p.title, "id": p.game_id, "uuid": p.uuid,
                   "gameversion": p.game_version}[cmd]())
        elif cmd.startswith("read"):
            addr = int(rest[0], 16)
            width = int(cmd[4:])
            v = {8: p.read8, 16: p.read16, 32: p.read32, 64: p.read64}[width](addr)
            print(f"0x{addr:08X} = 0x{v:0{width // 4}X}")
        elif cmd.startswith("write"):
            addr, v = int(rest[0], 16), int(rest[1], 16)
            width = int(cmd[5:])
            {8: p.write8, 16: p.write16, 32: p.write32, 64: p.write64}[width](addr, v)
            print("ok")
        elif cmd == "dump":
            addr, length = int(rest[0], 16), int(rest[1], 0)
            data = p.read_bytes(addr, length)
            if len(rest) > 2:
                with open(rest[2], "wb") as f:
                    f.write(data)
                print(f"wrote {len(data)} bytes to {rest[2]}")
            else:
                for off in range(0, len(data), 16):
                    chunk = data[off:off + 16]
                    text = "".join(chr(b) if 32 <= b < 127 else "." for b in chunk)
                    print(f"{addr + off:08X}  {chunk.hex(' ')}  {text}")
        elif cmd == "savestate":
            p.save_state(int(rest[0]))
            print("ok")
        elif cmd == "loadstate":
            p.load_state(int(rest[0]))
            print("ok")
        elif cmd == "wait-nonzero":
            addr = int(rest[0], 16)
            timeout = float(rest[1]) if len(rest) > 1 else 120.0
            deadline = time.time() + timeout
            while time.time() < deadline:
                v = p.read32(addr)
                if v:
                    print(f"0x{addr:08X} = 0x{v:08X}")
                    return 0
                time.sleep(0.5)
            print("timeout")
            return 1
        else:
            print(f"unknown command {cmd}")
            return 2
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
