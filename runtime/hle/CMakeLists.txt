# p3fes_cdvd: sector-level CDVD HLE (ADR-0008 §1; RUNTIME_CONTRACT L-01..L-06, I-04..I-08).
# DiscSource (user's ISO or extracted/disc) + CdvdHle (cdvdfsv command surface). Win32 file I/O
# only; no threads, no backends, so the kernel HLE, tools and tests can link it on its own.
# See README.md in this directory.

add_library(p3fes_cdvd STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/p3fes/hle/disc_source.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/p3fes/hle/cdvd.h
    host_file.h
    host_file.cpp
    iso9660.h
    iso9660.cpp
    disc_source.cpp
    iso_file_source.cpp
    extracted_volumes_source.cpp
    cdvd.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/p3fes/hle/mods_overlay.h
    mods_overlay.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/p3fes/hle/read_log.h
    read_log.cpp
)
add_library(p3fes::cdvd ALIAS p3fes_cdvd)
target_include_directories(p3fes_cdvd PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
)
target_link_libraries(p3fes_cdvd PUBLIC p3fes_common_options)

# SIF + IOP RPC HLE (ADR-0013 §3): runtime/hle/sif/, library p3fes_sif.
add_subdirectory(sif)
# Memory card (8 MiB NAND image, ECC, file system, card sources) behind DBCMAN: runtime/hle/memcard/,
# library p3fes_memcard; links itself into p3fes_sif, so it comes after it.
add_subdirectory(memcard)
