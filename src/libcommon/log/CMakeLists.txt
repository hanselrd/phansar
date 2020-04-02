set(sources
    common_log.cpp)

set(libs
    ph_vendor)

ph_add_generic_library(ph_common_log "${sources}" "${libs}" "")
