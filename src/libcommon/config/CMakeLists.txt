# cmake-format: off
set(sources
    common_config.cpp)

set(libs
    ph_vendor_docopt
    ph_vendor_fmt
    ph_vendor_spdlog)
# cmake-format: on

ph_add_generic_library(ph_common_config "${sources}" "${libs}" "")
