# p3fes_native_kernel: modernize layer 6 (docs/MODERNIZE_PLAN.md "Layer 6 status", ADR-0017), the host side of
# `--native kernel` (p3fes/native/kernel_service.h): the game's libkernel stubs call the host kernel directly, the
# thread contexts live on the host only, and the (b) timing set of `--native-kernel-timing host`. Pure C++20 over
# p3fes_kernel.
add_library(p3fes_native_kernel STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/p3fes/native/kernel_service.h
    native_kernel.h
    native_kernel.cpp
)
target_include_directories(p3fes_native_kernel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
target_link_libraries(p3fes_native_kernel PUBLIC p3fes_common_options p3fes_kernel)
