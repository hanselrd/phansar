# cmake-format: off
set(libs
    ph_common_log
    ph_vendor_hedley)
# cmake-format: on

ph_add_generic_interface_library(ph_common_macros "${libs}" "")
