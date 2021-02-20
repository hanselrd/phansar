CPMAddPackage(
    NAME taskflow
    GITHUB_REPOSITORY taskflow/taskflow # master
    GIT_TAG 33353d2b061eecc9e3671b78e2b8bb141128a6bc
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
