# p3fes_native: the native renderer's play-mode fast path (docs/ANALYSIS/31_native_renderer.md): the semantic
# model of RenderWare's g3 VU1 programs and its checker. Pure C++20 over p3fes_vu1 (no OS dependencies).
add_library(p3fes_native STATIC
    g3_model.h
    g3_model.cpp
    native_vu.h
    native_vu.cpp
)
target_include_directories(p3fes_native PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(p3fes_native PUBLIC p3fes_vu1 p3fes_gs)

add_executable(p3fes_native_check tools/native_check.cpp)
target_link_libraries(p3fes_native_check PRIVATE p3fes_native p3fes_vu1)

# p3fes_native_gpucheck: the GPU vertex stage (gs_native_hlsl.h) against the CPU model on captured batches.
add_executable(p3fes_native_gpucheck tools/native_gpucheck.cpp)
target_link_libraries(p3fes_native_gpucheck PRIVATE p3fes_native p3fes_gs p3fes_vu1 d3d11 d3dcompiler)
