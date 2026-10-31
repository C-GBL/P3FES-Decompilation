# p3fes_native_graphics: modernize layer 5 (docs/MODERNIZE_PLAN.md "Layer 5 status", ADR-0017), the host's stand-in for
# the VU1 programs of the game's draw submission under `--native graphics` (p3fes/native/graphics_service.h). Step 1:
# RenderWare's Im2D triangles (VU1 program 039). Pure C++20 over p3fes_vu1 / p3fes_gs (no OS calls).
add_library(p3fes_native_graphics STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/p3fes/native/graphics_service.h
    native_im2d.h
    native_im2d.cpp
    native_g3.h
    native_g3.cpp
)
target_include_directories(p3fes_native_graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
target_link_libraries(p3fes_native_graphics PUBLIC p3fes_common_options p3fes_vu1 p3fes_gs)
target_include_directories(p3fes_native_graphics PRIVATE ${PROJECT_SOURCE_DIR}/runtime/vu1)  # vu1_aot_rt.h, vu1_semantics.h
# native_im2d.cpp uses the compiled VU1 programs' SSE4.1 kernels (vu1_aot_rt.h; checked at run time by aot_cpu_ok):
# clang wants the target feature, and both compilers must keep the kernels' float expressions as written.
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set_source_files_properties(native_im2d.cpp PROPERTIES COMPILE_OPTIONS "-msse4.1;/fp:strict")
endif()
