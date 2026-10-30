# p3fes_kernel: the EE kernel / timing HLE (ADR-0013 §3; docs/ANALYSIS/15_ee_kernel_semantics.md).
# HwBus + time base, INTC + timers, DMAC register block + tag chains + SPR channels, EE syscalls, the fiber
# scheduler and the RtHooks implementation. Its own fibers (fiber.h, MASM); no backends. See README.md here.
#
# Link contract: the library calls p3fes::rt::lookup_func (recomp/include/p3fes_recomp_rt.h) for handler and
# thread entry addresses unless KernelOptions::lookup is set; the final executable provides it (the generated
# dispatch.cpp, or a test table).
# The fibers' stack switch (fiber.h) is MASM; an object library of its own so the C++ options of
# p3fes_common_options never reach ml64.
enable_language(ASM_MASM)
add_library(p3fes_kernel_fiber_asm OBJECT fiber_switch_x64.asm)

add_library(p3fes_kernel STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/p3fes/hle/kernel.h
    kernel_core.h
    fiber.h
    bus_timebase.cpp
    intc_timers.cpp
    dmac.cpp
    interrupts.cpp
    scheduler.cpp
    syscalls.cpp
    kernel.cpp
    kernel_state.cpp
    $<TARGET_OBJECTS:p3fes_kernel_fiber_asm>
)
add_library(p3fes::kernel ALIAS p3fes_kernel)
target_include_directories(p3fes_kernel PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
)
# p3fes_runtime: EEMemory. p3fes_recomp_rt_api (recomp/): the rt::lookup_func declaration.
target_link_libraries(p3fes_kernel
    PUBLIC p3fes_common_options p3fes_runtime
    PRIVATE p3fes_recomp_rt_api
)
