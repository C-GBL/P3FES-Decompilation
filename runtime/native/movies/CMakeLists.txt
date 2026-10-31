# p3fes_native_movies: modernize layer 4 (docs/MODERNIZE_PLAN.md section 3, ADR-0017), the host side of
# `--native movies` (p3fes/native/movies_service.h): the MPEG video decoder libmpeg runs on the EE, on the host, over
# the IPU's own core (p3fes_ipu's mpeg2:: functions; IpuCore drives the sweep's oracle). Pure C++20.
add_library(p3fes_native_movies STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/p3fes/native/movies_service.h
    mpeg_video.h
    mpeg_video.cpp
    native_movies.h
    native_movies.cpp
)
target_include_directories(p3fes_native_movies PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
target_link_libraries(p3fes_native_movies PUBLIC p3fes_common_options p3fes_ipu)

# p3fes_native_movies_check: check 1 of layer 4 -- every .SFD of the disc decoded through the native engine and
# through the emulated IPU (IpuCore, driven the way libmpeg drives it), picture for picture; and the ADX track of
# each movie decoded by our ADX decoder (against a run's --dump-wav).
add_executable(p3fes_native_movies_check tools/native_movies_check.cpp)
target_link_libraries(p3fes_native_movies_check PRIVATE p3fes_native_movies p3fes_audio)
