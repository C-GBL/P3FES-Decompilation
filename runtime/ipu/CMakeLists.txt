# p3fes_ipu: the PS2 IPU (MPEG-1/2 macroblock decoder + colour-space converter) as an HwDevice with the DMAC
# channel 3 (fromIPU) / 4 (toIPU) data paths (runtime/ipu/README.md). Pure C++20, no OS dependencies: tests and
# tools link it alone; the host attaches it to the kernel's HwBus.
add_library(p3fes_ipu STATIC
    ../include/p3fes/ipu/ipu_regs.h
    ../include/p3fes/ipu/mpeg2.h
    ../include/p3fes/ipu/ipu_core.h
    ../include/p3fes/ipu/ipu_system.h
    vlc_tables.cpp
    mpeg2.cpp
    ipu_core.cpp
    ipu_system.cpp
)
add_library(p3fes::ipu ALIAS p3fes_ipu)
target_include_directories(p3fes_ipu PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
)
target_link_libraries(p3fes_ipu PUBLIC p3fes_common_options)
