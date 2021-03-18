CPMAddPackage(
    NAME taskflow
    GITHUB_REPOSITORY taskflow/taskflow # master
    GIT_TAG 9e50cf2a7b33b90713c20585498369caf299bf08
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
