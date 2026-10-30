# Emit + compile + link a reviewed subset of real functions (recomp/README.md "Tests").
#
#   cmake -DRECOMP=<p3fes_recomp.exe> -DCXX=<cl|clang-cl> -DSRC=<repo> -DOUT=<dir> -P compile_subset.cmake
#
# Exit codes: 0 pass, 77 skipped (ELF absent), 1 failure. Runs inside the VS developer shell
# (ctest inherits it) because cl.exe / clang-cl need INCLUDE and LIB. The output goes to OUT
# (a build directory), never to recomp/generated/.
#
# The subset, each a case the emitter must handle (addresses are IDA function starts):
#   0x100008 start                 crt0: jal chain, syscalls
#   0x193980 main                  falls through into code IDA left outside every function (-> rt::unreachable)
#   0x1984c0 kwlnMain              loop with calls and an unconditional `b`
#   0x3e0c20 sub_3E0C20            switch-heavy (jump tables), 20 KiB body
#   0x4e53e0 sub_4E53E0            top-MMI function (docs/ANALYSIS/08), 8 IDA data words inside the body
#   0x54d080 valloc                multi-chunk (3 chunks, tail chunks below the start)
#   0x5830d0 sub_5830D0            multi-chunk (3 chunks) with 3 IDA data words
#   0x526238 vfprintf              mid-body entry 0x5262b0 (entry-dispatch form) + data words + 89-case switch
#   0x528920 _vsprintf_r           calls vfprintf's mid-body entry
#   0x45edc0 sub_45EDC0            one of the 15 RenderWare `lw $v0; jr $v0` tail calls
#   0x46bfb0 sub_46BFB0            the census' headless word (0x46c14c, unreached nop after `b`)
#   0x4c72a0 sub_4C72A0            `jr $ra` whose delay slot lies in the next function
#   0x5067f8 sub_5067F8            a branch whose target is another branch's delay slot
#   0x50d040 _kTLBException        eret
#   0x4fc168 _sceMpegPictureData0  likely branches (SDK band)
set(SUBSET "0x100008,0x193980,0x1984c0,0x3e0c20,0x4e53e0,0x54d080,0x5830d0,0x526238,0x528920,0x45edc0,0x46bfb0,0x4c72a0,0x5067f8,0x50d040,0x4fc168")

if(DEFINED ENV{P3FES_ELF})
    set(ELF "$ENV{P3FES_ELF}")
else()
    set(ELF "${SRC}/extracted/disc/SLUS_216.21")
endif()
if(NOT EXISTS "${ELF}")
    message(STATUS "SKIP: ELF not found at ${ELF} (set P3FES_ELF)")
    cmake_language(EXIT 77)  # ctest SKIP_RETURN_CODE
endif()

file(REMOVE_RECURSE "${OUT}")
file(MAKE_DIRECTORY "${OUT}")

message(STATUS "emit: ${RECOMP} --only ${SUBSET}")
execute_process(
    COMMAND "${RECOMP}" --elf "${ELF}" --functions "${SRC}/symbols/functions.json"
            --chunks "${SRC}/symbols/function_chunks.txt" --jumptables "${SRC}/symbols/jumptables.json"
            --out "${OUT}/generated" --only "${SUBSET}" --group-size 4 --annotate
    RESULT_VARIABLE rc OUTPUT_VARIABLE so ERROR_VARIABLE se)
message(STATUS "${se}")
if(NOT rc EQUAL 0)
    message(FATAL_ERROR "p3fes_recomp --out failed (${rc})")
endif()

file(GLOB units "${OUT}/generated/fn_*.cpp")
list(LENGTH units nfn)
if(nfn EQUAL 0)
    message(FATAL_ERROR "no generated units in ${OUT}/generated")
endif()
list(APPEND units "${OUT}/generated/dispatch.cpp" "${OUT}/generated/missing_stubs.cpp"
     "${SRC}/recomp/rt_stubs/rt_stubs.cpp" "${SRC}/recomp/linkcheck/linkcheck_main.cpp")
# The same switches as p3fes_common_options plus /WX: the generated code must be warning-free at
# /W4; the only silenced diagnostic is the unused-label warning, in generated/gen_prelude.h.
set(flags /nologo /c /W4 /WX /std:c++20 /permissive- /EHsc /utf-8 /bigobj
          /DWIN32_LEAN_AND_MEAN /DNOMINMAX /DUNICODE /D_UNICODE /D_CRT_SECURE_NO_WARNINGS
          "/I${OUT}/generated" "/I${SRC}/recomp/include" "/I${SRC}/runtime/include")
get_filename_component(cxx_name "${CXX}" NAME_WE)
if(cxx_name STREQUAL "clang-cl")
    list(APPEND flags -Wno-unused-command-line-argument)
else()
    list(APPEND flags /Zc:__cplusplus /Zc:preprocessor)
endif()
if(DEFINED OPT)
    list(APPEND flags ${OPT})  # e.g. -DOPT=/O2 to check the optimiser's diagnostics (C4702, C4883)
endif()

set(objs)
set(warnings 0)
string(TIMESTAMP start_s "%s")
foreach(u IN LISTS units)
    get_filename_component(base "${u}" NAME_WE)
    set(obj "${OUT}/${base}.obj")
    execute_process(COMMAND "${CXX}" ${flags} "/Fo${obj}" "${u}"
                    RESULT_VARIABLE rc OUTPUT_VARIABLE so ERROR_VARIABLE se)
    # cl: "file(12): warning C4100: ..."; clang-cl: "file(12,3): warning: ... [-W...]"
    string(REGEX MATCHALL ": warning[ :]" w "${so}${se}")
    list(LENGTH w nw)
    math(EXPR warnings "${warnings} + ${nw}")
    if(NOT rc EQUAL 0)
        message(STATUS "${so}\n${se}")
        message(FATAL_ERROR "compile failed: ${u}")
    endif()
    list(APPEND objs "${obj}")
endforeach()
string(TIMESTAMP end_s "%s")
math(EXPR elapsed "${end_s} - ${start_s}")
list(LENGTH units nunits)
message(STATUS "compiled ${nunits} units with ${cxx_name} in ${elapsed}s, ${warnings} warnings (with /WX)")

execute_process(COMMAND "${CXX}" /nologo ${objs} "/Fe${OUT}/linkcheck.exe"
                RESULT_VARIABLE rc OUTPUT_VARIABLE so ERROR_VARIABLE se)
if(NOT rc EQUAL 0)
    message(STATUS "${so}\n${se}")
    message(FATAL_ERROR "link failed")
endif()
message(STATUS "linked ${OUT}/linkcheck.exe")
# Dispatch smoke: lookup_func only searches the table (no adapter call), so it runs on the stubs.
foreach(va 0x100008 0x5262b0)
    execute_process(COMMAND "${OUT}/linkcheck.exe" ${va} RESULT_VARIABLE rc OUTPUT_VARIABLE so ERROR_VARIABLE se)
    if(NOT rc EQUAL 0)
        message(FATAL_ERROR "lookup_func(${va}) failed: ${so}${se}")
    endif()
    message(STATUS "${so}")
endforeach()
if(NOT warnings EQUAL 0)
    message(FATAL_ERROR "${warnings} warnings")
endif()
