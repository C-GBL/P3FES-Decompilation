# p3fes_native_sound: modernize layer 3 (docs/MODERNIZE_PLAN.md section 3, ADR-0017), the host side of `--native sound`
# (p3fes/native/sound_service.h): the native ADX output and mixer, and (steps 2-3) the SK sound-effect stack on native
# code (sk/README.md). Pure C++20 over p3fes_audio's sink interfaces.
#
# The SK stack's code is generated at build time by tools/ours/modernize/skgen.py from the user's LIB31 IRX files
# (derived from game data: like recomp/generated it is never committed). P3FES_LIB31_DIR names them; without them (or
# without a Python 3 interpreter) the library builds a stub table and --native sound keeps the interpreted SK modules.
set(P3FES_LIB31_DIR "${CMAKE_SOURCE_DIR}/extracted/disc/LIB31" CACHE PATH
    "The user's extracted LIB31 (the SK modules the native SK stack is generated from)")
if(NOT P3FES_PYTHON)
    if(DEFINED ENV{P3FES_PYTHON})
        set(P3FES_PYTHON "$ENV{P3FES_PYTHON}")
    else()
        find_package(Python3 COMPONENTS Interpreter QUIET)
        if(Python3_Interpreter_FOUND)
            set(P3FES_PYTHON "${Python3_EXECUTABLE}")
        endif()
    endif()
endif()
set(P3FES_PYTHON "${P3FES_PYTHON}" CACHE FILEPATH "Python 3 for build-time generators (skgen.py)")

set(_sk_gen_dir ${CMAKE_CURRENT_BINARY_DIR}/sk_gen)
set(_sk_modules SDRDRV MODHSYN MODSESQ SKSOUND SKHSYNTH SKSESQ)
set(_sk_gen_src)
set(_sk_irx)
set(_sk_have TRUE)
foreach(m IN LISTS _sk_modules)
    string(TOLOWER ${m} lower)
    list(APPEND _sk_gen_src ${_sk_gen_dir}/sk_gen_${lower}.cpp)
    list(APPEND _sk_irx ${P3FES_LIB31_DIR}/${m}.IRX)
    if(NOT EXISTS ${P3FES_LIB31_DIR}/${m}.IRX)
        set(_sk_have FALSE)
    endif()
endforeach()
if(NOT P3FES_PYTHON)
    set(_sk_have FALSE)
endif()
file(MAKE_DIRECTORY ${_sk_gen_dir})
if(_sk_have)
    add_custom_command(
        OUTPUT ${_sk_gen_dir}/sk_gen.h ${_sk_gen_src}
        COMMAND ${P3FES_PYTHON} -I ${CMAKE_SOURCE_DIR}/tools/ours/modernize/skgen.py --lib ${P3FES_LIB31_DIR} --out ${_sk_gen_dir}
                --report ${_sk_gen_dir}/skgen_report.txt
        DEPENDS ${CMAKE_SOURCE_DIR}/tools/ours/modernize/skgen.py ${CMAKE_CURRENT_SOURCE_DIR}/sk/sk_imports.h ${_sk_irx}
        COMMENT "skgen: the SK modules as native C++ (from ${P3FES_LIB31_DIR})"
        VERBATIM)
    message(STATUS "native SK: generated at build time from ${P3FES_LIB31_DIR}")
else()
    set(_sk_gen_src)
    # No module files: an empty table (NativeSk::install refuses; --native sound keeps the interpreted modules).
    file(WRITE ${_sk_gen_dir}/sk_gen.h.in
        "// skgen.py did not run (no LIB31 at ${P3FES_LIB31_DIR} or no Python): the native SK stack is not available.\n"
        "#pragma once\n#include \"sk_cpu.h\"\n#include \"sk_imports.h\"\n#include \"sk_modules.h\"\n"
        "namespace p3fes::native::sound::sk {\n"
        "inline constexpr bool kGenerated = false;\n"
        "inline constexpr ModuleImage kModules[1] = {{\"SDRDRV.IRX\", 0x00083230u, 0, 0, 0, 0, 0, 0}};\n"
        "inline constexpr FnEntry kFunctions[1] = {{0u, nullptr}};\n"
        "}  // namespace p3fes::native::sound::sk\n")
    configure_file(${_sk_gen_dir}/sk_gen.h.in ${_sk_gen_dir}/sk_gen.h COPYONLY)
    message(STATUS "native SK: not generated (P3FES_LIB31_DIR=${P3FES_LIB31_DIR}, P3FES_PYTHON=${P3FES_PYTHON}); --native sound keeps the interpreted SK")
endif()

add_library(p3fes_native_sound STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/p3fes/native/sound_service.h
    native_sound.h
    native_sound.cpp
    # steps 2-3: the SK stack on native code (sk/README.md)
    sk/sk_cpu.h
    sk/sk_modules.h
    sk/sk_imports.h
    sk/sk_host.h
    sk/sk_host.cpp
    sk/sk_imports.cpp
    ${_sk_gen_dir}/sk_gen.h
    ${_sk_gen_src}
)
target_include_directories(p3fes_native_sound PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/sk ${_sk_gen_dir}
                           ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
target_link_libraries(p3fes_native_sound PUBLIC p3fes_common_options p3fes_audio)

# p3fes_native_sound_check: check 1 of layer 3 -- the stream PCM of a run's --dump-wav against our ADX decoder on the
# files its read log names, the whole-disc decode sweep, vgmstream-cli as a second opinion.
add_executable(p3fes_native_sound_check tools/native_sound_check.cpp)
target_link_libraries(p3fes_native_sound_check PRIVATE p3fes_audio)
