CPMAddPackage(
    NAME taskflow
    GITHUB_REPOSITORY taskflow/taskflow # master
    GIT_TAG 2b79a32b097aec6d617279b2588b6969f16f91e6
    OPTIONS "TF_BUILD_TESTS OFF" "TF_BUILD_EXAMPLES OFF")

# cmake-format: off
set(system_libs
    Taskflow)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_taskflow
    ""
    ""
    "${system_libs}")
