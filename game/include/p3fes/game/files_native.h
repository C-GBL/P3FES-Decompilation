// Modernize layer 1 (docs/MODERNIZE_PLAN.md §3, ADR-0017): the native branches of the game's CD wrappers, taken only
// while the host has installed a native files service (`--native files`, p3fes/native/files_service.h). Each faithful
// body calls one of these at its swap point and otherwise runs unchanged:
//   H_Cdvd_Update 0x100980 (sweep5a.cpp), state 0 of a request node: hcdvd_native_load
//   dvCiReqRd 0x55A490 (sweep5c.cpp), a read request on a CDV: handle: dvci_native_read
//   dvCiCdSearchFile 0x559DD8 (libs24.cpp), the sceCdLayerSearchFile call: dvci_native_search
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/ee_types.h"
#include "p3fes/native/files_service.h"

namespace p3fes::game {

// H_Cdvd_Update, a node in state 0 after H_Cdvd_SetRofsDir: finds "<CVM>:<dir><name>" (node +344 "VOL:NAME" /
// "BTL:NAME" / "BGM:NAME" -> DATA.CVM / BTL.CVM / BGM.CVM, the directory at node +600), sets the sizes (+280, +292),
// allocates the buffer through the heap hook at 0x960178 exactly as states 1 does ((sectors << 11) + 64, archives
// + 320; 64-aligned at +272, raw at +276), reads every sector of the file into it, zeroes the 256-byte PAK
// terminator of an archive, registers it (H_Cdvd_AddFile, node + 8) and sets state 4. false: not found, no memory
// or a host read error -- the node stays in state 0 (the pump stops there and retries next frame, as faithful).
bool hcdvd_native_load(EEContext& ctx, native::files::FileService& fs, u32 node);

// dvCiReqRd on handle `h` (72-byte dvCi handle, 0x7A1DF0 table: +2 state, +8 size in sectors, +12 position, +16
// request, +20 transferred, +24 buffer, +28 SRD, +32 the sceCdlFILE: LSN, size) for `nsct` > 0 sectors into `buf`:
// clamps to the file end as faithful, copies the sectors from the host file at once and leaves the handle complete
// (+2 = 1, +20 = n, +12 += n, no SRD), the state dvCiExecHndl gives a finished read. Returns n (dvCiReqRd's $v0).
// A host read error leaves state 3 (dvCiExecHndl's error state).
u32 dvci_native_read(EEContext& ctx, native::files::FileService& fs, u32 h, u32 nsct, u32 buf);

// sceCdLayerSearchFile(fp, name, layer) for dvCiCdSearchFile: the outer file `name` ("\DATA.CVM;1") from the host's
// directory, written to `fp` as cdvdfsv writes it (LSN, size, identifier[16], date[8], flags 0). 1 found, 0 not.
u32 dvci_native_search(EEContext& ctx, native::files::FileService& fs, u32 fp, u32 name);

}  // namespace p3fes::game
