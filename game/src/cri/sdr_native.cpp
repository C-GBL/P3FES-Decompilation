// Modernize layer 3, steps 2-3 (docs/MODERNIZE_PLAN.md section 3, ADR-0017): the native branches of the game's
// sound-command layer (game/include/p3fes/game/sound_native.h). Reached only while the native sound service runs the
// SK stack natively (p3fes::native::sound::service()->sk_native(), `--native sound`).
//
// The game talks to its sound-effect driver through two SIF entry points only: the module loads of
// kwlnInitPS2Systems (sceSifLoadModule) and libsdr's sceSdRemote, whose one sceSifCallRpc to SDRDRV (0x80000701)
// carries every libsd remote call and every Standard Kit command (sceSkSs*: SOUND_Control / Send, HSYNTH / SESQ Bind,
// SESQ_Control / Status). Natively the same bytes go to the native SK stack (runtime/native/sound/sk) and its answer is
// written where the RPC would have put it; every other instruction of the callers is the faithful code.
#include <string>
#include <vector>

#include "p3fes/ee_memory.h"
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/sound_native.h"

namespace p3fes::game {

void sk_native_load_module(EEContext& ctx, native::sound::SoundService& s) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    std::string path;
    for (u32 p = a0.u(); path.size() < 252; ++p) {  // loadfile's request carries at most 252 path bytes
        const char ch = static_cast<char>(ctx.memory->read<u8>(p));
        if (!ch) break;
        path.push_back(ch);
    }
    std::vector<u8> args(a1.u() <= 252 ? a1.u() : 252u);
    for (u32 i = 0; i < args.size(); ++i) args[i] = ctx.memory->read<u8>(a2.u() + i);
    v0 = static_cast<u32>(s.sk_load_module(ctx.cycles, path, args));
}

void sdr_native_call(EEContext& ctx, native::sound::SoundService& s) {
    using namespace hg;
    // sceSifCallRpc(client a0, fno a1, mode a2, send a3, ssize t0, recv t1, rsize t2, end t3, end-arg sp+0)
    Gpr v0{ctx, 2}, a1{ctx, 5}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    std::vector<u8> send(t0.u());
    for (u32 i = 0; i < send.size(); ++i) send[i] = ctx.memory->read<u8>(a3.u() + i);
    std::vector<u8> recv(t1.u() != 0 ? t2.u() : 0u);
    s.sd_remote(ctx.cycles, a1.u(), send, recv);
    for (u32 i = 0; i < recv.size(); ++i) ctx.memory->write<u8>(t1.u() + i, recv[i]);
    v0 = 0;
}

}  // namespace p3fes::game
