# p3fes_hfr: frame interpolation for the high-frame-rate display (docs/ANALYSIS/32_high_frame_rate.md): batch
# matching between two game frames, clip-space vertex blending, transform (rotation / stretch / translation)
# blending. Pure C++20 over p3fes_gs's op lists; the D3D11 render-thread part is p3fes_hfr_d3d11.
add_library(p3fes_hfr STATIC
    hfr_interp.h
    hfr_interp.cpp
)
target_include_directories(p3fes_hfr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(p3fes_hfr PUBLIC p3fes_gs)

# p3fes_hfr_d3d11: the render-thread interpolator (GsD3D11Renderer::set_interpolator): per-frame records, replay of a
# frame's op list with blended native batches into a scratch GS memory bank, the in-between picture. Windowed play.
add_library(p3fes_hfr_d3d11 STATIC
    hfr_d3d11.h
    hfr_d3d11.cpp
)
target_link_libraries(p3fes_hfr_d3d11 PUBLIC p3fes_hfr p3fes_gs_d3d11 d3d11 d3dcompiler)
