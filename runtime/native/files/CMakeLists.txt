# p3fes_native_files: modernize layer 1 (docs/MODERNIZE_PLAN.md §3, ADR-0017), the host's native files service the
# game's CD wrappers call under `--native files` (p3fes/native/files_service.h). Pure C++20 over p3fes_cdvd.
add_library(p3fes_native_files STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/p3fes/native/files_service.h
    native_files.h
    native_files.cpp
)
target_include_directories(p3fes_native_files PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(p3fes_native_files PUBLIC p3fes_common_options p3fes_cdvd)

# p3fes_native_files_check: checks (a) and (b) of layer 1 -- every read of faithful read logs served by path, and
# the whole-disc sweep (native by path vs the sector path vs extracted/).
add_executable(p3fes_native_files_check tools/native_files_check.cpp)
target_link_libraries(p3fes_native_files_check PRIVATE p3fes_native_files)
