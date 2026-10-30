# p3fes_vu1: VU1 micro-instruction decoder and interpreter (Phase 3; docs/ANALYSIS/09_vu1_micro_census.md,
# runtime/include/p3fes/vu1/README.md). Pure C++20, no OS dependencies, so tools and tests link it alone.
add_library(p3fes_vu1_base STATIC
    ../include/p3fes/vu1/vu1_decode.h
    vu1_decode.cpp
    vu1_qtiming.h
    vu1_qtiming.cpp
)
target_include_directories(p3fes_vu1_base PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
)
target_link_libraries(p3fes_vu1_base PUBLIC p3fes_common_options)

add_library(p3fes_vu1 STATIC
    ../include/p3fes/vu1/vu1_interp.h
    ../include/p3fes/vu1/vu1_profile.h
    ../include/p3fes/vu1/vu1_aot.h
    vu1_semantics.h
    vu1_aot_rt.h
    vu1_interp.cpp
    vu1_profile.cpp
    vu1_aot.cpp
)
add_library(p3fes::vu1 ALIAS p3fes_vu1)
target_include_directories(p3fes_vu1 PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
)
target_include_directories(p3fes_vu1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(p3fes_vu1 PUBLIC p3fes_vu1_base)

# Ahead-of-time compiled microprograms (runtime/include/p3fes/vu1/vu1_aot.h, docs/ANALYSIS/24_vu1_acceleration.md).
# Off by default: the generated sources embed game code, so they come from the gitignored dumps
# (tools/ours/vu1/vu1_dump.py --elf <SLUS_216.21>) at build time and stay in the build tree.
option(P3FES_VU1_AOT "Compile the VU1 microprograms ahead of time (needs the dumps, P3FES_VU1_AOT_DUMPS)" OFF)
set(P3FES_VU1_AOT_DUMPS "${PROJECT_SOURCE_DIR}/ida/logs/vu1" CACHE PATH "Directory of the <code_va>.bin microcode dumps")
set(P3FES_VU1_AOT_ONLY "" CACHE STRING "Comma-separated code VAs (hex, as the dump names) to compile; empty = all")
add_executable(p3fes_vu1_aotgen aotgen/vu1_aotgen.cpp)
target_link_libraries(p3fes_vu1_aotgen PRIVATE p3fes_vu1_base)
if(P3FES_VU1_AOT)
    set(_aot_dir "${CMAKE_CURRENT_BINARY_DIR}/aot_generated")
    if(P3FES_VU1_AOT_ONLY)
        string(REPLACE "," ";" _aot_vas "${P3FES_VU1_AOT_ONLY}")
        set(_aot_only_arg --only "${P3FES_VU1_AOT_ONLY}")
    else()
        file(GLOB _aot_dumps RELATIVE "${P3FES_VU1_AOT_DUMPS}" "${P3FES_VU1_AOT_DUMPS}/*.bin")
        set(_aot_vas "")
        foreach(_d IN LISTS _aot_dumps)
            string(REPLACE ".bin" "" _va "${_d}")
            list(APPEND _aot_vas "${_va}")
        endforeach()
        set(_aot_only_arg "")
    endif()
    list(LENGTH _aot_vas _aot_n)
    if(_aot_n EQUAL 0)
        message(FATAL_ERROR "P3FES_VU1_AOT: no dumps in ${P3FES_VU1_AOT_DUMPS} (run tools/ours/vu1/vu1_dump.py)")
    endif()
    set(_aot_outs "${_aot_dir}/vu1_aot_programs.cpp")
    set(_aot_deps "")
    foreach(_va IN LISTS _aot_vas)
        list(APPEND _aot_outs "${_aot_dir}/vu1_aot_${_va}.cpp")
        list(APPEND _aot_deps "${P3FES_VU1_AOT_DUMPS}/${_va}.bin")
    endforeach()
    add_custom_command(
        OUTPUT ${_aot_outs}
        COMMAND p3fes_vu1_aotgen --dumps "${P3FES_VU1_AOT_DUMPS}" --census "${PROJECT_SOURCE_DIR}/symbols/vu1_micro_census.json"
                --out "${_aot_dir}" ${_aot_only_arg}
        DEPENDS p3fes_vu1_aotgen ${_aot_deps} "${PROJECT_SOURCE_DIR}/symbols/vu1_micro_census.json"
        COMMENT "p3fes_vu1_aotgen: ${_aot_n} VU1 programs -> C++"
        VERBATIM)
    target_sources(p3fes_vu1 PRIVATE ${_aot_outs})
    # SSE4.1 intrinsics (vu1_aot_rt.h; checked at run time by aot_cpu_ok()): MSVC accepts them as is, clang wants the
    # target feature
    set(_aot_opts "")
    if(MSVC)
        list(APPEND _aot_opts /bigobj)
    endif()
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        list(APPEND _aot_opts -msse4.1 /fp:strict)
    endif()
    # AVX2 (default): the same intrinsics in VEX encoding (three-operand: the register copies of the two-operand SSE
    # forms disappear); aot_cpu_ok() then also requires AVX2 and OS YMM support, else the interpreter runs.
    set(P3FES_VU1_AOT_ARCH "AVX2" CACHE STRING "Instruction set of the compiled VU1 programs: AVX2 or SSE41")
    if(P3FES_VU1_AOT_ARCH STREQUAL "AVX2")
        if(MSVC AND NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
            list(APPEND _aot_opts /arch:AVX2)
        else()
            list(APPEND _aot_opts -mavx2)
        endif()
        target_compile_definitions(p3fes_vu1 PRIVATE P3FES_VU1_AOT_AVX2=1)
    endif()
    set_source_files_properties(${_aot_outs} PROPERTIES COMPILE_OPTIONS "${_aot_opts}")
    target_compile_definitions(p3fes_vu1 PUBLIC P3FES_VU1_AOT=1)
    message(STATUS "P3FES_VU1_AOT: ${_aot_n} programs from ${P3FES_VU1_AOT_DUMPS}")
else()
    target_sources(p3fes_vu1 PRIVATE vu1_aot_none.cpp)
endif()

# p3fes_runtime provides VU1 to the host (BUILDING.md "Targets"); linked from here so runtime/CMakeLists.txt only
# gains an add_subdirectory line (CMP0079).
target_link_libraries(p3fes_runtime PUBLIC p3fes_vu1)
