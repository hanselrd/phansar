CPMAddPackage(
    NAME taskflow
    GITHUB_REPOSITORY taskflow/taskflow # master
    GIT_TAG 4fafc47dbfc365f7e7a5a03e5ce176809d6b34d9
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
