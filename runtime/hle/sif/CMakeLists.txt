# p3fes_sif: SIF registers + syscalls + SIF0/SIF1 data paths and the IOP RPC-server HLE
# (ADR-0013 §3; RUNTIME_CONTRACT K-14, I-01..I-42). See README.md in this directory.
# Depends on p3fes_cdvd (cdvdfsv is served from CdvdHle), p3fes_runtime (EEMemory) and p3fes_audio
# (host audio interfaces for the CRI_ADXI model).

add_library(p3fes_sif STATIC
    include/p3fes/hle/sif/protocol.h
    include/p3fes/hle/sif/iop.h
    include/p3fes/hle/sif/sif.h
    sif.cpp
    iop/iop_core.h
    iop/iop_core.cpp
    iop/srv_system.cpp
    iop/srv_cdvdfsv.h
    iop/srv_cdvdfsv.cpp
    iop/srv_padman.h
    iop/srv_padman.cpp
    iop/srv_dbcman.cpp
    iop/srv_sdr.h
    iop/srv_sdr.cpp
    iop/srv_adxi.h
    iop/srv_adxi.cpp
    iop/mc_mc2s1.h
    iop/mc_mc2s1.cpp
    # ADR-0014 B-lite: the SK/libsd IRX modules interpreted in place (README.md "SK modules").
    iop/r3000.h
    iop/r3000.cpp
    iop/irx_loader.h
    iop/irx_loader.cpp
    iop/libsd_hle.h
    iop/libsd_hle.cpp
    iop/iop_kernel_hle.h
    iop/iop_kernel_hle.cpp
    iop/iop_state.cpp
)
add_library(p3fes::sif ALIAS p3fes_sif)
target_include_directories(p3fes_sif PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
# p3fes_audio: the AudioSink / StreamTap interfaces the CRI_ADXI mixer model renders into.
target_link_libraries(p3fes_sif PUBLIC p3fes_common_options p3fes_cdvd p3fes_runtime p3fes_audio)
