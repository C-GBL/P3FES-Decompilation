# p3fes_gs: the GS (software rasteriser into 4 MiB local memory), its privileged registers, the GIF (PATH1/2/3),
# VIF1 (+ VU1 start through p3fes_vu1) and the CRTC output (runtime/gs/README.md). Pure C++20 with no OS
# dependencies, so tests and tools link it alone; the D3D11 presenter stays in p3fes_runtime.
add_library(p3fes_gs STATIC
    ../include/p3fes/gs/gs_types.h
    ../include/p3fes/gs/gs_mem.h
    ../include/p3fes/gs/gs_core.h
    ../include/p3fes/gs/gs_priv.h
    ../include/p3fes/gs/gs_output.h
    ../include/p3fes/gs/gif.h
    ../include/p3fes/gs/gif_builder.h
    ../include/p3fes/gs/vif1.h
    ../include/p3fes/gs/gs_system.h
    ../include/p3fes/gs/gs_selftest.h
    ../include/p3fes/gs/gs_stream.h
    ../include/p3fes/gs/gs_ops.h
    ../include/p3fes/gs/gs_pipe.h
    ../include/p3fes/gs/gs_pipeline.h
    gs_raster.h
    gs_mem.cpp
    gs_core.cpp
    gs_raster.cpp
    gs_raster_ref.cpp
    gs_priv.cpp
    gs_output.cpp
    gif.cpp
    vif1.cpp
    gs_system.cpp
    gs_state.cpp
    gs_selftest.cpp
    gs_stream.cpp
    gs_ops.cpp
    gs_pipeline.cpp
)
add_library(p3fes::gs ALIAS p3fes_gs)
target_include_directories(p3fes_gs PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
)
target_link_libraries(p3fes_gs PUBLIC p3fes_common_options p3fes_vu1)

# p3fes_runtime presents the composed GS output (runtime/src/gs/d3d11_backend.cpp); linked from here so
# runtime/CMakeLists.txt only gains an add_subdirectory line (CMP0079, as runtime/vu1 does). The presenter compiles
# its two shaders with D3DCompile (d3dcompiler_47.dll ships with Windows 10+).
target_link_libraries(p3fes_runtime PUBLIC p3fes_gs d3dcompiler user32)

# p3fes_gs_d3d11: the D3D11 GS back end (docs/ANALYSIS/25_d3d11_gs_backend.md): GS local memory as one GPU buffer,
# the GS pixel pipeline in HLSL, a render thread that owns the device and the window's swap chain. Windowed play
# only; headless runs and the gates use the software rasteriser.
add_library(p3fes_gs_d3d11 STATIC
    ../include/p3fes/gs/gs_d3d11.h
    ../include/p3fes/gs/gs_d3d11_hlsl.h
    d3d11/gs_d3d11.cpp
)
target_link_libraries(p3fes_gs_d3d11 PUBLIC p3fes_gs d3d11 dxgi d3dcompiler avrt dwmapi)

# p3fes_gscmp: compare a composed frame (PNG) with a reference screenshot (PCSX2's Screenshot.png) with a
# tolerance; PNG decoding through the Windows Imaging Component.
add_executable(p3fes_gscmp tools/gscmp.cpp)
target_link_libraries(p3fes_gscmp PRIVATE p3fes_gs windowscodecs ole32)

# p3fes_gsdecode: decode a texture/buffer out of a VRAM image (our gsMemory.bin or PCSX2's GS.bin) with the core's
# own swizzle and write a PNG -- checks a format's read path against memory another implementation filled.
add_executable(p3fes_gsdecode tools/gsdecode.cpp)
target_link_libraries(p3fes_gsdecode PRIVATE p3fes_gs)

# p3fes_gsreplay: replay a `p3fes --gs-record` stream through the software GS and the D3D11 back end and compare the
# two memories and pictures (docs/ANALYSIS/25_d3d11_gs_backend.md §6). A diagnostic tool.
add_executable(p3fes_gsreplay tools/gsreplay.cpp)
target_link_libraries(p3fes_gsreplay PRIVATE p3fes_gs_d3d11)
