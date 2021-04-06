CPMAddPackage(
    NAME taskflow
    GITHUB_REPOSITORY taskflow/taskflow # master
    GIT_TAG d104feb5f293e0063160c635e9def20ee5960539
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
