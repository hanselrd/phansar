set(sources
    common_log.cpp)

set(libs
    ph_vendor_plibsys
    ph_vendor_spdlog)

ph_add_generic_library(ph_common_log "${sources}" "${libs}" "")
