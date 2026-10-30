# p3fes_gs_tests: doctest tests for runtime/gs (GS local memory and swizzle, GIF, rasteriser, textures/CLUT, VIF1 +
# VU1 start, privileged registers, CRTC output). No game data: every input is synthetic.
add_executable(p3fes_gs_tests
    gs_test_main.cpp
    gs_test_util.h
    test_gs_mem.cpp
    test_gif.cpp
    test_gs_draw.cpp
    test_gs_tex.cpp
    test_gs_fast.cpp
    test_vif1.cpp
    test_gs_priv.cpp
    test_gs_output.cpp
    test_gs_stream.cpp
    test_gs_gpu.cpp
    test_gs_pipeline.cpp
    test_frame_interp.cpp
)
target_include_directories(p3fes_gs_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../vendor)
target_link_libraries(p3fes_gs_tests PRIVATE p3fes_common_options p3fes_gs p3fes_gs_d3d11 p3fes_hfr)

add_test(NAME p3fes_gs_tests COMMAND p3fes_gs_tests)

# The threaded graphics pipeline on a stretch of the real game (needs the recompiled program, the ELF and the disc
# image; skips without): the M1 route synchronous vs threaded, byte for byte (gs_threads_route.cmake).
if(TARGET p3fes AND P3FES_RECOMP_GENERATED)
    get_filename_component(_p3fes_main_dir "${P3FES_RT_EXEC_ELF}" DIRECTORY)   # <main>/extracted/disc
    get_filename_component(_p3fes_main_dir "${_p3fes_main_dir}" DIRECTORY)
    get_filename_component(_p3fes_main_dir "${_p3fes_main_dir}" DIRECTORY)
    add_test(NAME p3fes_gs_threads_route
        COMMAND ${CMAKE_COMMAND} -DEXE=$<TARGET_FILE:p3fes> -DELF=${P3FES_RT_EXEC_ELF}
                -DISO=${_p3fes_main_dir}/input/persona3fes.iso -DOUT=${CMAKE_CURRENT_BINARY_DIR}/gs_threads_route
                -P ${CMAKE_CURRENT_SOURCE_DIR}/gs_threads_route.cmake)
    set_tests_properties(p3fes_gs_threads_route PROPERTIES SKIP_RETURN_CODE 77 TIMEOUT 600)
endif()
