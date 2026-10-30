// Phase 5 slice field6, part misc (game/src/field/field6_misc.cpp): the screen filter draw and the after-effect
// packs. Register ABI.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

// sub_1D4610 0x1D4610 [K_FldFilter_Draw]:
//   (no args) Draws the field's screen filter when an entry is selected (gp 0x7CE2A0 != 0): advances the blend
//   (0x7CE2A8 += 1 / 0x7CE2AC up to 1.0, then the shown entry 0x7CE2A4 = the target), sets the render states
//   (Z test / write off, the blend of the entry's mode +0: 0 -> 68, 1 -> 72, 2 -> 66, 3 -> 6 through
//   RpSkyRenderStateSet(2, ..)), and draws the 7 x 8 cells of the 292-byte entry: each cell's four RGBA
//   corners (+4 / +8 / +40 / +44 of its 36-byte record) get the brightness 0x7CE29C added to alpha (clamped
//   0..255), are blended with the previous entry's while the blend is < 1.0 (x (1 - t) + y t on the FPU
//   accumulator), scaled by 0x7CC2C8 / 255 unless it is 255 (MMI mult1 / div), written into the cell's Im2D
//   quad 0x872240 + 2048 row + 256 column (the colour floats +32..+44 of each vertex) and drawn as a 4-vertex
//   strip (pfn_RwIm2DRenderPrimitive(4, quad, 4)).
void sub_1D4610(EEContext& ctx);
// sub_1EDF10 0x1EDF10 [afpackDrawPack]:
//   (pack) Draws one after-effect pack: saves six render states (20, 10, 11, 8, 6, 14), sets the pack blend (9
//   = 2, 20 = 1, 8 = 0, 6 = 1, 14 = 0, 12 = 1), then for each of the pack's effects (pack data +4 s16 count):
//   the blend (RpSkyRenderStateSet 2 = 72, 3 = 464897), sub_4CB930 on the effect's atomic; unless the effect's
//   control flag 8 is set the atomic is put on the owner model's frame (sub_318B60(model) or, for a model with
//   +216 bit 15, +144) by sub_4CB7F0; then the atomic's render callback (+72) is called through jalr.
void sub_1EDF10(EEContext& ctx);
// sub_1EF060 0x1EF060 [afpackUpdateAll]:
//   (no args) -> 0.
void sub_1EF060(EEContext& ctx);

}  // namespace p3fes::game
