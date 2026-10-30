// Empty compiled-program table: the build without P3FES_VU1_AOT (vu1_aot.h). Mode::Aot then runs the interpreter.
#include "p3fes/vu1/vu1_aot.h"

namespace p3fes::vu1 {

std::size_t aot_program_count() noexcept { return 0; }
const AotProgram* aot_programs() noexcept { return nullptr; }

} // namespace p3fes::vu1
