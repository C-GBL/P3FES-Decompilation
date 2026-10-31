// Modernize layer 3 (docs/MODERNIZE_PLAN.md §3, ADR-0017): the native branches of CRI's PS2 sound output (PS2RNA),
// taken only while the host has installed a native sound service (`--native sound`, p3fes/native/sound_service.h).
// Each is called at the top of its faithful body, which then returns:
//   PS2RNA_Init 0x55FF70 (libs25.cpp)      ps2rna_native_init
//   sub_560698 Finish (libs26.cpp)         ps2rna_native_finish
//   PS2RNA_Create 0x560758 (libs14.cpp)    ps2rna_native_create
//   sub_560AF8 Destroy (libs14.cpp)        ps2rna_native_destroy
//   sub_560C88 transfer switch (libs14)    ps2rna_native_transfer
//   sub_560EB0 / sub_560F18 (libs14)       ps2rna_native_num_data / ps2rna_native_num_room
//   PS2RNA_ExecServer 0x561138 (libs14)    ps2rna_native_exec_server
// and the game's IOP bring-up (kwlnInitPS2Systems 0x197030, libs24.cpp) does not load CRI_ADXI.IRX.
// The PS2RNA records (16 x 100 bytes at 0x7AB850) keep the faithful layout; what differs from the faithful run is the
// layer's own state: the PSJ / DTR / DTX / SJX objects and IOP addresses that are never made, the RNA DTX buffer
// (the command builder's scratch) and the restart / transfer timing (tools/ours/modernize/layer3_sound_mask.txt).
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/ee_types.h"
#include "p3fes/native/sound_service.h"

namespace p3fes::game {

void ps2rna_native_init(EEContext& ctx, native::sound::SoundService& s);
void ps2rna_native_finish(EEContext& ctx, native::sound::SoundService& s);
// (sjs = the players' output-joint array, nch) -> the record's address, 0 when the table is full ($v0).
u32 ps2rna_native_create(EEContext& ctx, native::sound::SoundService& s, u32 sjs, u32 nch);
void ps2rna_native_destroy(EEContext& ctx, native::sound::SoundService& s, u32 rna);
void ps2rna_native_transfer(EEContext& ctx, native::sound::SoundService& s, u32 rna, u32 sw);
u32 ps2rna_native_num_data(EEContext& ctx, native::sound::SoundService& s, u32 rna);
u32 ps2rna_native_num_room(EEContext& ctx, native::sound::SoundService& s, u32 rna);
void ps2rna_native_exec_server(EEContext& ctx, native::sound::SoundService& s);

// Steps 2-3, the SK sound effects and the libsd remote calls (game/src/cri/sdr_native.cpp), taken while
// s.sk_native(): the game's sound-command layer reaches the native SK stack instead of the IOP --
//   kwlnInitPS2Systems 0x197030 (libs24.cpp)  the LIBSD / SDRDRV / MODHSYN / MODMSIN / MODSESQ / SKSOUND / SKHSYNTH x2 /
//                                              SKSESQ loads: sk_native_load_module instead of sceSifLoadModule
//   sceSdRemoteInit 0x512868 (sweep5b.cpp)     no bind of SDRDRV's RPC (nothing calls it)
//   sceSdRemote 0x5129C0 (sweep5a.cpp)         its three sceSifCallRpc sites: sdr_native_call
// sceSifLoadModule's arguments (path a0, arglen a1, args a2) -> the module id in $v0.
void sk_native_load_module(EEContext& ctx, native::sound::SoundService& s);
// sceSifCallRpc's arguments as sceSdRemote passes them (fno a1, send a3 / t0, recv t1 / t2): the reply written to
// recv, $v0 = 0 (a call that returned).
void sdr_native_call(EEContext& ctx, native::sound::SoundService& s);
// The service when the SK stack runs natively, else nullptr (the faithful SIF path).
inline native::sound::SoundService* sk_service() {
    native::sound::SoundService* s = native::sound::service();
    return s && s->sk_native() ? s : nullptr;
}

}  // namespace p3fes::game
