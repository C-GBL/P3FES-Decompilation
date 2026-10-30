# In-house tooling (GOAL.md: "write a minimal one in tools/ours/").
#
# tracediff (Phase 4): finds the first divergence between a PCSX2 reference and
# our runtime. Snapshot mode (two 32 MiB eeMemory.bin images + masks) is
# implemented (docs/TRACE_FORMAT.md §5); stream mode (.p3tr) is still a stub.

add_library(tracediff_snapshot STATIC
    tracediff/snapshot.h
    tracediff/snapshot.cpp
)
target_include_directories(tracediff_snapshot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tracediff)
target_link_libraries(tracediff_snapshot PUBLIC p3fes_common_options)

add_executable(tracediff
    tracediff/main.cpp
)
target_link_libraries(tracediff PRIVATE tracediff_snapshot)

# doctest unit tests (ctest: tracediff_tests). Synthetic 32 MiB images only; no
# game data is read.
add_executable(tracediff_tests
    tracediff/tests/test_snapshot.cpp
)
target_include_directories(tracediff_tests PRIVATE ${CMAKE_SOURCE_DIR}/tests/vendor)
target_link_libraries(tracediff_tests PRIVATE tracediff_snapshot)
add_test(NAME tracediff_tests COMMAND tracediff_tests)
