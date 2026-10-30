# p3fes_rt: the rt adapter -- the implementation of every p3fes::rt declaration in
# recomp/include/p3fes_recomp_rt.h (what the generated code calls) over the R5900 semantics headers
# runtime/include/p3fes/ee/*.h and EEMemory. It owns register semantics and guest RAM access and
# models no device: hardware-register windows, syscalls, check points, traps and fatal stops go to
# the RtHooks instance installed with p3fes::set_hooks() (ADR-0013 §3). See README.md here.
#
# lookup_func is not defined here: it lives in the generated dispatch.cpp (p3fes_program, or a
# test's own emitted subset).

add_library(p3fes_rt STATIC
    include/p3fes/rt/rt_adapter.h
    rt_internal.h
    rt_hooks.cpp
    rt_core.cpp
    rt_mem.cpp
    rt_mmi.cpp
    rt_fpu.cpp
    rt_vu0.cpp
)
add_library(p3fes::rt ALIAS p3fes_rt)
target_include_directories(p3fes_rt
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)
# p3fes_runtime: EEMemory (ee_memory.cpp) and the semantics headers; p3fes_recomp_rt_api: the
# include path of p3fes_recomp_rt.h (defined in recomp/, resolved at generate time).
target_link_libraries(p3fes_rt PUBLIC p3fes_common_options p3fes_runtime p3fes_recomp_rt_api)
