# p3fes_gs_threads_route: a recorded stretch of the real game (the M1 route: boot to the title's 11th frame, software
# GS) run synchronously (--gs-threads off) and through the threaded graphics pipeline with two workers and inline,
# twice each; every run's eeMemory.bin, gsMemory.bin and frame.png must be byte-identical to the synchronous run's
# (p3fes/gs/gs_pipeline.h: the pipeline changes nothing the guest or the snapshot sees). Skips (exit 77) without the
# ELF or the disc image.
#   cmake -DEXE=<p3fes.exe> -DELF=<SLUS_216.21> -DISO=<persona3fes.iso> -DOUT=<dir> -P gs_threads_route.cmake
if(NOT EXISTS "${ELF}" OR NOT EXISTS "${ISO}")
    message("p3fes_gs_threads_route: skipped (no ELF '${ELF}' or disc image '${ISO}')")
    cmake_language(EXIT 77)
endif()
file(REMOVE_RECURSE "${OUT}")
file(MAKE_DIRECTORY "${OUT}")
set(runs off 2 0 2b 0b)
foreach(r IN LISTS runs)
    string(REGEX REPLACE "b$" "" threads "${r}")
    execute_process(
        COMMAND "${EXE}" --elf "${ELF}" --iso "${ISO}" --headless --quiet --memcard none --gs-threads ${threads}
                --snapshot-at sky:11 "${OUT}/${r}"
        WORKING_DIRECTORY "${OUT}"
        RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
    if(NOT rc EQUAL 0)
        message(FATAL_ERROR "p3fes --gs-threads ${threads} failed (${rc}):\n${out}\n${err}")
    endif()
    string(REGEX MATCH "gs-threads: [^\n]*" line "${out}")
    message("run ${r}: ${line}")
endforeach()
foreach(f eeMemory.bin gsMemory.bin frame.png)
    file(SHA256 "${OUT}/off/${f}" ref)
    foreach(r IN LISTS runs)
        file(SHA256 "${OUT}/${r}/${f}" h)
        if(NOT h STREQUAL ref)
            message(FATAL_ERROR "${f}: run '${r}' differs from the synchronous run")
        endif()
    endforeach()
    message("${f}: identical in all runs (${ref})")
endforeach()
