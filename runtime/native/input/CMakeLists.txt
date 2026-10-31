# p3fes_native_input: modernize layer 2 (docs/MODERNIZE_PLAN.md section 3, ADR-0017), the host's DUALSHOCK 2 the game's
# pad wrapper asks under `--native input` (p3fes/native/input_service.h). Pure C++20, no OS calls.
add_library(p3fes_native_input STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/p3fes/native/input_service.h
    native_pad.h
    native_pad.cpp
)
target_include_directories(p3fes_native_input PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
target_link_libraries(p3fes_native_input PUBLIC p3fes_common_options)
